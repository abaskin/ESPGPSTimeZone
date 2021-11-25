#include "GPSTimeZone.hpp"

#include <ArduinoJson.h>  // https://github.com/bblanchon/
#include <ArduinoStreamParser.h>  // <==== THE JSON Streaming Parser - Arduino STREAM WRAPPER

GPSTimeZone::GPSTimeZone(fs::FS& fileSys, const char* path)
  : m_fileSys(fileSys), m_dirName(path) {}

bool GPSTimeZone::findTZ(double lat, double longi) {
  std::unique_ptr<ArudinoStreamParser> parser{new ArudinoStreamParser{}};
  parser->setHandler(m_handler.get());

  DynamicJsonDocument json{9 * 1024};
  StaticJsonDocument<96> filter;
  filter[F("tzName")] = true;
  filter[F("posix")] = true;
  filter[F("limit")] = true;

  uint8_t fileBuffer[fileBufferSize];

  m_fileSys.begin();
  auto dir = m_fileSys.openDir(m_dirName.c_str());
  while (dir.next()) {
    std::string fileName{m_dirName + dir.fileName().c_str()};
    auto tzFile = m_fileSys.open(fileName.c_str(), "r");
    if (tzFile) {
      auto error =
          deserializeJson(json, tzFile, DeserializationOption::Filter(filter));
      if (error) {
        Serial.printf_P(PSTR("deserializeJson() failed: %S\n"), error.f_str());
        continue;
      }

      Serial.printf_P(PSTR("Checking %s\n"), json["tzName"].as<const char*>());
      for (const auto& l : json["limit"].as<JsonArrayConst>()) {
        std::string polyid = l["id"].as<const char*>();
        Serial.printf_P(PSTR("Checking %s\n"), polyid.c_str());
        if (lat >= l["minLat"] && lat <= l["maxLat"] && 
            longi >= l["minLong"] && longi <= l["maxLong"]) {
          Serial.printf_P(PSTR("Possibility in %s\n"), polyid.c_str());
          m_handler->setPolygon(polyid.c_str(), {lat, longi}, {lat, l["maxLong"]});
          tzFile.seek(0, SeekSet);
          while (!m_handler->done()) {
            auto readSize = tzFile.read(fileBuffer, sizeof(fileBuffer));
            if (readSize == 0) {
              break;
            }
            parser->write(fileBuffer, readSize);
          }
          Serial.printf_P(PSTR("result %d\n"), m_handler->result());
          if (m_handler->result()) break;
        }
      }
      tzFile.close();
    }
    if (m_handler->result()) break;
  }
  m_fileSys.end();

  if (m_handler->result()) {
    m_posix = json[F("posix")].as<const char*>();
    m_tzName = json[F("tzName")].as<const char*>();
    m_radius = (m_handler->paths() > 1) ? m_handler->radius() : 0;
  }

  return m_handler->result();
}

bool GPSTimeZone::inCircle(double centerLat, double centerLong,
                           double locationLat, double locationLong,
                           double radius) const {
  return m_handler->inCircle({centerLong, centerLat},
                             {locationLong, locationLat}, radius);
}

bool GPSTimeZone::inCircle(std::array<double, 2> center,
                           std::array<double, 2> location,
                           double radius) const {
  return m_handler->inCircle(center, location, radius);
}
