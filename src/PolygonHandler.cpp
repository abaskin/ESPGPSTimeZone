#include "PolygonHandler.hpp"

void PolygonHandler::startDocument() {
}

void PolygonHandler::startArray(ElementPath path) {
  switch (m_polygonState) {
    case polygonState_t::polygonStart:
    case polygonState_t::pathEnd:
      m_polygonState = polygonState_t::pathStart;
      m_intersect = 0;
      break;
    default:
      if (!strcmp(path.getKey(), m_polygonName.c_str())) {
        m_polygonState = polygonState_t::polygonStart;
      }
      break;
  }
}

void PolygonHandler::startObject(ElementPath path) {
}

void PolygonHandler::value(ElementPath path, ElementValue value) {
  switch (m_polygonState) {
    case polygonState_t::pathStart:
      m_pathNum = path.get(-2)->getIndex();
      if (!strcmp(path.getKey(), "lat")) {
        m_latQueue.push((double)value.getFloat());
      }
      if (!strcmp(path.getKey(), "long")) {
        m_longQueue.push((double)value.getFloat());
      }
      break;
    default:
      break;
  }
}

void PolygonHandler::endArray(ElementPath path) {
  switch (m_polygonState) {
    case polygonState_t::pathStart:
      if (m_pathNum == 0) {
        m_result = (m_intersect % 2 == 1) ? true : false; // odd
      } else {
        m_result = (m_intersect % 2 == 0) ? true : false; // even
      }
      m_polygonState = polygonState_t::pathEnd;
      if (!m_result) {
        m_polygonState = polygonState_t::polygonEnd;
      }
      break;
    case polygonState_t::pathEnd:
      m_polygonState = polygonState_t::polygonEnd;
      break;
    default:
      break;
  }
}

void PolygonHandler::endObject(ElementPath path) {
  switch (m_polygonState) {
    case polygonState_t::pathStart:
      if (m_latQueue.size() == 2 && m_longQueue.size() == 2) {
        m_intersect += linesIntersect();
      }
      break;
    default:
      break;
  }
}

void PolygonHandler::endDocument() {
  m_polygonState = polygonState_t::polygonEnd;
}

void PolygonHandler::whitespace(char c) {
}

// ----------------------------------------------------------------------------

void PolygonHandler::setPolygon(const char* name, point lineA, point lineB) {
  m_polygonName = name;
  auto a{getCart(lineA)};
  auto b{getCart(lineB)};
  m_aLat = a[0]; m_aLong = a[1];
  s1_x = b[1] - m_aLong;
  s1_y = b[0] - m_aLat;
}

point PolygonHandler::getCart(point location) const {
  return wgs84::toCartesian(WGS84Reference, {location[0], location[1]});
}

bool PolygonHandler::inCircle(point center, point location, double radius) const {
  if (radius != 0.0) {
    auto [c_y, c_x] = getCart(center);
    auto [p_y, p_x] = getCart(location);
    return (p_x - c_x) * (p_x - c_x) + 
           (p_y - c_y) * (p_y - c_y) <= radius * radius;
  }
  return false;
}

uint32_t PolygonHandler::linesIntersect() {
  auto [p2_y, p2_x] = getCart({m_latQueue.front(), m_longQueue.front()});

  m_latQueue.pop();
  m_longQueue.pop();

  auto [by, bx] = getCart({m_latQueue.front(), m_longQueue.front()});

  double s2_x, s2_y;
  s2_x = bx - p2_x;
  s2_y = by - p2_y;

  double s, t;
  s = (-s1_y * (m_aLong - p2_x) + s1_x * (m_aLat - p2_y)) /
      (-s2_x * s1_y + s1_x * s2_y);
  t = (s2_x * (m_aLat - p2_y) - s2_y * (m_aLong - p2_x)) /
      (-s2_x * s1_y + s1_x * s2_y);

  m_radius = std::min(m_radius, 
    minDistance({bx, by}, {p2_x, p2_y}, {m_aLong, m_aLat}));

  return (s >= 0 && s <= 1 && t >= 0 && t <= 1) ? 1 : 0;
}

// Function to return the minimum distance
// between a line segment AB and a point E
double PolygonHandler::minDistance(point A, point B, point E) const {
  // vector AB
  point AB{B[0] - A[0], B[1] - A[1]};

  // vector BE
  point BE{E[0] - B[0], E[1] - B[1]};

  // vector AE
  point AE{E[0] - A[0], E[1] - A[1]};

  // Calculate the dot product
  double AB_BE{AB[0] * BE[0] + AB[1] * BE[1]},
         AB_AE{AB[0] * AE[0] + AB[1] * AE[1]};

  // Minimum distance from point E to the line segment
  // Case 1
  if (AB_BE > 0) {
    double y {E[1] - B[1]};
    double x {E[0] - B[0]};
    return sqrt(x * x + y * y);
  }

  // Case 2
  if (AB_AE < 0) {
    double y {E[1] - A[1]};
    double x {E[0] - A[0]};
    return sqrt(x * x + y * y);
  }

  // Case 3 Finding the perpendicular distance
  double x1 {AB[0]}, y1 {AB[1]},
         x2 {AE[0]}, y2 {AE[1]};
  double mod = sqrt(x1 * x1 + y1 * y1);
  return abs(x1 * y2 - y1 * x2) / mod;
}