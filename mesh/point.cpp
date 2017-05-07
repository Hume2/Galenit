#include <assert.h>

#include "point.h"

#include "cubepos.h"
#include "toepos.h"

#include "../main.h"

Point2D::Point2D() :
  x(0),
  y(0)
{ }

Point2D::Point2D(const float x_, const float y_) :
  x(x_),
  y(y_)
{ }

Point2D::Point2D(const Point3D p) :
  x(p.x),
  y(p.y)
{ }

Point2D Point2D::operator +(const Point2D a) const {
  return Point2D(x + a.x, y + a.y);
}

Point2D Point2D::operator -() const {
  return Point2D(-x, -y);
}

Point2D Point2D::operator -(const Point2D a) const {
  return Point2D(x - a.x, y - a.y);
}

Point2D Point2D::operator *(const float a) const {
  return Point2D(x * a, y * a);
}

Point2D Point2D::operator /(const float a) const {
  return Point2D(x / a, y / a);
}

std::string Point2D::to_string() const {
  return "[" + std::to_string(x) + ", " + std::to_string(y) + "]";
}

bool Point2D::operator ==(const Point2D a) const {
  return x == a.x && y == a.x;
}

bool Point2D::operator !=(const Point2D a) const {
  return x != a.x || y != a.x;
}

Point2D& Point2D::operator +=(const Point2D a) {
  x += a.x;
  y += a.y;
  return *this;
}

Point2D& Point2D::operator -=(const Point2D a) {
  x -= a.x;
  y -= a.y;
  return *this;
}

Point2D& Point2D::operator *=(const float a) {
  x *= a;
  y *= a;
  return *this;
}

Point2D& Point2D::operator /=(const float a) {
  x /= a;
  y /= a;
  return *this;
}

bool Point2D::is_on_screen() const {
  return x < SCREEN_WIDTH && y < SCREEN_HEIGHT;
}

//------------------------------------------------------------------------------
// Point3D
//------------------------------------------------------------------------------

Point3D::Point3D() :
  x(0),
  y(0),
  z(0)
{ }

Point3D::Point3D(const float x_, const float y_, const float z_) :
  x(x_),
  y(y_),
  z(z_)
{ }

Point3D::Point3D(const Point2D p) :
  x(p.x),
  y(p.y),
  z(0)
{ }

Point3D::Point3D(const Cubepos p) :
  x(p.x),
  y(p.y),
  z(p.z)
{

}

Point3D::Point3D(const Toepos p) :
  x(p.x),
  y(p.y),
  z(p.z)
{
  if (p.mesh == Toepos::ZOT) {
    x += 0.5f;
    y += 0.5f;
    z += 0.5f;
  }
}

Point3D Point3D::operator +(const Point3D a) const {
  return Point3D(x + a.x, y + a.y, z + a.z);
}

Point3D Point3D::operator -() const {
  return Point3D(-x, -y, -z);
}

Point3D Point3D::operator -(const Point3D a) const {
  return Point3D(x - a.x, y - a.y, z - a.z);
}

Point3D Point3D::operator *(const float a) const {
  return Point3D(x * a, y * a, z * a);
}

Point3D Point3D::operator /(const float a) const {
  return Point3D(x / a, y / a, z / a);
}

std::string Point3D::to_string() const {
  return "[" + std::to_string(x) + ", " + std::to_string(y) + ", " + std::to_string(z) + "]";
}

bool Point3D::operator ==(const Point3D a) const {
  return x == a.x && y == a.x && z == a.z;
}

bool Point3D::operator !=(const Point3D a) const {
  return x != a.x || y != a.x || z != a.z;
}

Point3D& Point3D::operator +=(const Point3D a) {
  x += a.x;
  y += a.y;
  z += a.z;
  return *this;
}

Point3D& Point3D::operator -=(const Point3D a) {
  x -= a.x;
  y -= a.y;
  z -= a.z;
  return *this;
}

Point3D& Point3D::operator *=(const float a) {
  x *= a;
  y *= a;
  z *= a;
  return *this;
}

Point3D& Point3D::operator /=(const float a) {
  x /= a;
  y /= a;
  z /= a;
  return *this;
}
