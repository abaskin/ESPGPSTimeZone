#pragma once

#include <WGS84toCartesian.hpp>

#include <queue>
#include <string>

#include "JsonHandler.h"

using point = std::array<double, 2>;

class PolygonHandler: public JsonHandler {
  public:
    virtual void startDocument();
    virtual void startArray(ElementPath path);
    virtual void startObject(ElementPath path);
    virtual void endArray(ElementPath path);
    virtual void endObject(ElementPath path);
    virtual void endDocument();
    virtual void value(ElementPath path, ElementValue value);
    virtual void whitespace(char c);

    void setPolygon(const char* name, point lineA, point lineB);
    bool inCircle(point center, point location, double radius) const;
    bool result() const { return m_result; }
    bool done() const { return m_polygonState == polygonState_t::polygonEnd; }
    double radius() const { return m_radius; }
    uint32_t paths() const { return m_pathNum + 1; }

   private:
    uint32_t linesIntersect();
    double minDistance(point A, point B, point E) const;
    point getCart(point location) const;

    enum class polygonState_t : uint8_t {
      ignore,
      polygonStart,
      polygonEnd,
      pathStart,
      pathEnd
    };
    polygonState_t m_polygonState { polygonState_t::ignore };

    const point WGS84Reference{11.565168, 104.923512};
    
    std::string m_polygonName;
    std::queue<double> m_latQueue, m_longQueue;
    double m_aLat, m_aLong, s1_x, s1_y;
    uint32_t m_pathNum, m_intersect;
    bool m_result { false };
    double m_radius{std::numeric_limits<double>::max()};
};