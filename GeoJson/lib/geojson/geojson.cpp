#include "geojson.hpp"

#include <assert.h>
#include <error/en.h>
#include <filereadstream.h>
#include <pointer.h>
#include <schema.h>

#include <iostream>

#include "GeoJSONSchema.hpp"
#include "range.hpp"

/////////////////////////////////////////////////////////////////////////////////////////////////////
//geojson_t::convert
/////////////////////////////////////////////////////////////////////////////////////////////////////

bool geojson_t::convert(const char* file_name) {
  {
    rapidjson::Document sd;
    if (sd.Parse(GeoJsonSchema).HasParseError()) {
      fprintf(stderr, "Schema Error(offset %u): %s\n", (unsigned)sd.GetErrorOffset(),
              GetParseError_En(sd.GetParseError()));
      return false;
    }

    rapidjson::SchemaDocument schema { sd };  // Compile a Document to SchemaDocument
                                              // sd is no longer needed here.

    const auto fp = fopen(file_name, "r");
    if (!fp) {
      std::cout << "cannot open " << file_name << std::endl;
      return false;
    }

    char readBuffer[65536];
    rapidjson::FileReadStream is { fp, readBuffer, sizeof(readBuffer) };

    rapidjson::SchemaValidatingReader<rapidjson::kParseDefaultFlags,
                                      rapidjson::FileReadStream,
                                      rapidjson::UTF8<>> reader(is, schema);
    doc->Populate(reader);
    fclose(fp);

    if (!reader.GetParseResult()) {
      // Not a valid JSON
      // When reader.GetParseResult().Code() == kParseErrorTermination,
      // it may be terminated by:
      // (1) the validator found that the JSON is invalid according to schema;
      // or (2) the input stream has I/O error.

      // Check the validation result
      if (!reader.IsValid()) {
        // Input JSON is invalid according to the schema
        // Output diagnostic information
        rapidjson::StringBuffer sb;
        reader.GetInvalidSchemaPointer().StringifyUriFragment(sb);
        printf("Invalid schema: %s\n", sb.GetString());
        printf("Invalid keyword: %s\n", reader.GetInvalidSchemaKeyword());
        sb.Clear();
        reader.GetInvalidDocumentPointer().StringifyUriFragment(sb);
        printf("Invalid document: %s\n", sb.GetString());
        return false;
      }
    }
  }

  const std::string docType{getPtrValue("/type")->GetString()};
  
  if (docType == "Feature") {
    parse_feature("");
  }
  
  if (docType == "FeatureCollection") {
    const auto numFeatures { getPtrValue("/features")->GetArray().Size() };
    std::cout << "features: " << numFeatures << std::endl;

    for (const auto n : util::lang::range(0, numFeatures)) {
      parse_feature("/features/" + std::to_string(n));
    }
  }

  doc.reset(nullptr);
  return true;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////
//geojson_t::parse_feature
/////////////////////////////////////////////////////////////////////////////////////////////////////

bool geojson_t::parse_feature(const std::string& prefix) {
  feature_t feature;
  //3 objects with keys: 
  // "type", 
  // "properties", 
  // "geometry"
  //"type" has a string value "Feature"
  //"properties" has a list of objects
  //"geometry" has 2 objects: 
  //key "type" with value string geometry type (e.g."Polygon") and
  //key "coordinates" an array

  if (auto tzidValue = getPtrValue(prefix, "/properties/tzid")) {
    feature.m_tzid = tzidValue->GetString();
    std::cout << "tzid: " << feature.m_tzid << std::endl;
  }

  if (auto nameValue = getPtrValue(prefix, "/properties/name")) {
    feature.m_name = nameValue->GetString();
    std::cout << "name: " << feature.m_name << std::endl;
  }

  parse_geometry(prefix, feature);

  m_feature.push_back(feature);
  return true;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////
//geojson_t::parse_geometry
//"geometry" has 2 objects: 
//key "type" with value string geometry type (e.g."Polygon") and
//key "coordinates" an array
/////////////////////////////////////////////////////////////////////////////////////////////////////

bool geojson_t::parse_geometry(const std::string& prefix, feature_t& feature) {
  const std::string geometry_type { getPtrValue(prefix, "/geometry/type")->GetString() };
  geometry_t geometry;

  /////////////////////////////////////////////////////////////////////////////////////////////////////
  // store geometry locally for points
  /////////////////////////////////////////////////////////////////////////////////////////////////////
  if (geometry_type == "Point") {
    const auto arr_coord = getPtrValue(prefix, "/geometry/coordinates")->GetArray();
    geometry.m_polygons.emplace_back(polygon_t {
      std::vector<coord_t>{{arr_coord[0].GetString(), arr_coord[1].GetString()}}
    });
  }

  /////////////////////////////////////////////////////////////////////////////////////////////////////
  // store geometry in parse_polygon() for polygons
  /////////////////////////////////////////////////////////////////////////////////////////////////////
  if (geometry_type == "Polygon") {
    parse_polygon(prefix + "/geometry/coordinates", geometry);
  }

  /////////////////////////////////////////////////////////////////////////////////////////////////////
  // "MultiPolygon" is an array that contains polygons
  /////////////////////////////////////////////////////////////////////////////////////////////////////
  if (geometry_type == "MultiPolygon") {
    for (const auto n :
         util::lang::range(0, getPtrValue(prefix, "/geometry/coordinates")->GetArray().Size())) {
      parse_polygon(prefix + "/geometry/coordinates/" + std::to_string(n), geometry);
    }
  }

  if (!geometry.m_polygons.empty()) {
    geometry.m_type = geometry_type;
    feature.m_geometry.push_back(geometry);
  }

  return true;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////
//geojson_t::parse_polygon
// "parse_polygon" 
// "Polygon"
// is an array of size 1 that contains another array and then an array of 2 numbers (lat, lon)
/////////////////////////////////////////////////////////////////////////////////////////////////////

bool geojson_t::parse_polygon(const std::string& jsonPtr, geometry_t& geometry) {
  polygon_t polygon;
  const auto coordinatesArray = getPtrValue(jsonPtr)->GetArray();
  for (const auto& coordArray : coordinatesArray) {
    polygon.push_back({});
    for (const auto& crd : coordArray.GetArray()) {
      polygon.back().emplace_back(crd[0].GetString(), crd[1].GetString());
    }
  }
  geometry.m_polygons.push_back(polygon);

  return true;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////
// geojson_t::getPtrValue
// "getPtrValue"
// given a prefix and pointer path return a value pointer
/////////////////////////////////////////////////////////////////////////////////////////////////////

inline rapidjson::Value* geojson_t::getPtrValue(const std::string& prefix,
                                                const std::string& ptrPath) const {
  return rapidjson::GetValueByPointer(*doc.get(),
                                      rapidjson::Pointer((prefix + ptrPath).c_str()));
}
