#pragma once

#include <Arduino.h>
#include <FS.h>

#include <array>
#include <string>

#include "PolygonHandler.hpp"

constexpr size_t fileBufferSize{1024};

class GPSTimeZone {
  public:
    GPSTimeZone(fs::FS& fileSys, const char* path);
    bool findTZ(double lat, double longi);
    bool inCircle(double centerLat, double centerLong,
                  double locationLat, double locationLong, double radius) const;
    bool inCircle(std::array<double, 2> center, std::array<double, 2> location,
                  double radius) const;
    const char* tzName() const { return m_tzName.c_str(); }
    const char* posix() const { return m_posix.c_str(); }
    double radius() const { return m_radius; }

  private:
    fs::FS& m_fileSys;
    std::string m_dirName, m_tzName, m_posix;
    double m_radius;

    std::unique_ptr<PolygonHandler> m_handler{new PolygonHandler{}};
};