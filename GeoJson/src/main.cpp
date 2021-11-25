#include <document.h>
#include <error/en.h>
#include <filereadstream.h>
#include <writer.h>

#include <boost/algorithm/string/replace.hpp>
#include <boost/regex.hpp>
#include <fstream>
#include <geojson.hpp>
#include <iostream>
#include <string>

int main() {
  constexpr char geoData[]{
      "~/Documents/PlatformIO/Projects/LED Clock "
      "GPS/SDCard/combined-with-oceans.json"};
  constexpr char tzFile[]{
      "~/Documents/PlatformIO/Projects/GeoJson/"
      "data/zones.json"};
  constexpr char outDir[]{
      "~/Documents/PlatformIO/Projects/LED Clock "
      "GPS/SDCard/TimeZoneJson/"};

  geojson_t geojson;
  if (!geojson.convert(geoData)) {
    return -1;
  }

  std::cout << "parsed geojson" << std::endl;

  const auto fp = fopen(tzFile, "r");
  if (!fp) {
    std::cout << "cannot open " << tzFile << std::endl;
    return -1;
  }

  char readBuffer[65536];
  rapidjson::FileReadStream is(fp, readBuffer, sizeof(readBuffer));

  rapidjson::Document tzJson;
  if (tzJson.ParseStream(is).HasParseError()) {
    fprintf(stderr, "Error(offset %u): %s\n",
            (unsigned)tzJson.GetErrorOffset(),
            GetParseError_En(tzJson.GetParseError()));
    return -1;
  }
  fclose(fp);

  std::cout << "loaded time zone data " << std::endl;

  for (const auto& feature : geojson.m_feature) {
    const auto geometry = feature.m_geometry[0];

    std::cout << feature.m_tzid << std::endl;

    rapidjson::Document json;
    json.SetObject();
    auto jAlloc { json.GetAllocator() };

    json.AddMember("tzName", rapidjson::StringRef(feature.m_tzid), jAlloc);
    json.AddMember("posix", rapidjson::StringRef(tzJson[feature.m_tzid].GetString()), jAlloc);

    rapidjson::Value limitList(rapidjson::kArrayType);
    rapidjson::Value polygonList(rapidjson::kArrayType);

    for (uint32_t polygonNum{0}; const auto& polygon : geometry.m_polygons) {
      std::string minLong{"181.0"}, minLat{"91.0"};
      std::string maxLong{"-181.0"}, maxLat{"-91.0"};
      rapidjson::Value paths(rapidjson::kArrayType);
      for (bool firstPath{true}; const auto& path : polygon) {
        rapidjson::Value coords(rapidjson::kArrayType);
        for (const auto& p : path) {
          rapidjson::Value coord(rapidjson::kObjectType);
          coord.AddMember("lat", rapidjson::StringRef(p.latStr), jAlloc);
          coord.AddMember("long", rapidjson::StringRef(p.longStr), jAlloc);
          coords.PushBack(coord, jAlloc);
          if (firstPath) {
            minLong = (std::stod(minLong) < p.longNum) ? minLong : p.longStr;
            maxLong = (std::stod(maxLong) > p.longNum) ? maxLong : p.longStr;
            minLat = (std::stod(minLat) < p.latNum) ? minLat : p.latStr;
            maxLat = (std::stod(maxLat) > p.latNum) ? maxLat : p.latStr;
          }
        }
        firstPath = false;
        paths.PushBack(coords, jAlloc);
      }

      const auto polygonID = "polygon" + std::to_string(polygonNum++);
      rapidjson::Value limit(rapidjson::kObjectType);
      limit.AddMember("minLat", rapidjson::StringRef(minLat), jAlloc);
      limit.AddMember("minLong", rapidjson::StringRef(minLong), jAlloc);
      limit.AddMember("maxLat", rapidjson::StringRef(maxLat), jAlloc);
      limit.AddMember("maxLong", rapidjson::StringRef(maxLong), jAlloc);
      limit.AddMember("id", rapidjson::StringRef(polygonID), jAlloc);
      limitList.PushBack(limit, jAlloc);
      rapidjson::Value polygonN(rapidjson::kObjectType);
      polygonN.AddMember(rapidjson::Value(polygonID, jAlloc).Move(), paths, jAlloc);
      polygonList.PushBack(polygonN, jAlloc);
    }

    json.AddMember("limit", limitList, jAlloc);
    json.AddMember("polygon", polygonList, jAlloc);

    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    json.Accept(writer);

    std::string jsonData { buffer.GetString(), buffer.GetSize() };

    boost::regex numStr(R"re("([-.0-9]+)")re");
    auto outJson = boost::regex_replace(jsonData, numStr, "$1");

    std::ofstream outFile(
        outDir +
        boost::replace_all_copy(feature.m_tzid, "/", "-") +
        ".json");
    outFile << outJson << std::endl;
  }

  return 0;
}
