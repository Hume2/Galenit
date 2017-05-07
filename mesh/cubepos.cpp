#include "cubepos.h"

#include "point.h"
#include "toepos.h"

Cubepos::Cubepos():
  x(0),
  y(0),
  z(0)
{

}

Cubepos::Cubepos(int x_, int y_, int z_):
  x(x_),
  y(y_),
  z(z_)
{

}

Cubepos::Cubepos(Point3D point):
  x(point.x),
  y(point.y),
  z(point.z)
{

}

Cubepos::Cubepos(Toepos point):
  x(point.x),
  y(point.y),
  z(point.z)
{

}

Cubepos Cubepos::operator +(const Cubepos a) const {
  return Cubepos(x + a.x, y + a.y, z + a.z);
}

Cubepos& Cubepos::operator +=(const Cubepos a) {
  x += a.x;
  y += a.y;
  z += a.z;
  return *this;
}

Cubepos Cubepos::operator -(const Cubepos a) const {
  return Cubepos(x - a.x, y - a.y, z - a.z);
}

Cubepos Cubepos::operator -() const {
  return Cubepos(-x, -y, -z);
}

Cubepos& Cubepos::operator -=(const Cubepos a) {
  x -= a.x;
  y -= a.y;
  z -= a.z;
  return *this;
}

bool Cubepos::operator ==(const Cubepos a) const {
  return (x == a.x) && (y == a.y) && (z == a.z);
}

bool Cubepos::operator !=(const Cubepos a) const {
  return (x != a.x) || (y != a.y) || (z != a.z);
}
