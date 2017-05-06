#include "toepos.h"

#include "point.h"

Toepos::Toepos():
  x(0),
  y(0),
  z(0),
  mesh(ASW)
{

}

Toepos::Toepos(int x_, int y_, int z_, Mesh mesh_):
  x(x_),
  y(y_),
  z(z_),
  mesh(mesh_)
{

}

Toepos::Toepos(Point3D point):
  x(point.x),
  y(point.y),
  z(point.z),
  mesh(ASW)
{
  //detect the correct toe
  float X = x - point.x;
  float Y = y - point.y;
  float Z = z - point.z;
  if (X+Y+Z - 0.75f < 0) {
    return;
  } else if(-X-Y-Z + 2.25f < 0) {
    x++;
    y++;
    z++;
  } else if(X+Y-Z + 0.25 < 0) {
    z++;
  } else if(X-Y+Z + 0.25 < 0) {
    y++;
  } else if(-X+Y+Z + 0.25 < 0) {
    x++;
  } else if(X-Y-Z + 1.25 < 0) {
    y++;
    z++;
  } else if(-X-Y+Z + 1.25 < 0) {
    x++;
    y++;
  } else if(-X+Y-Z + 1.25 < 0) {
    x++;
    z++;
  } else {
    mesh = ZOT;
  }
}

Toepos Toepos::operator +(const Toepos a) const {
  Toepos result(x + a.x, y + a.y, z + a.z, ASW);
  if (mesh != a.mesh) {
    result.mesh = ZOT;
  } else if (mesh == ZOT && a.mesh == ZOT) {
    result.x++;
    result.y++;
    result.z++;
  }
  return result;
}

Toepos& Toepos::operator +=(const Toepos a) {
  x += a.x;
  y += a.y;
  z += a.z;
  if (mesh != a.mesh) {
    mesh = ZOT;
  } else if (mesh == ZOT && a.mesh == ZOT) {
    x++;
    y++;
    z++;
    mesh = ASW;
  }
  return *this;
}
