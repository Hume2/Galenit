#include "rect.h"

#include <algorithm>

Rect2D::Rect2D():
  p1(),
  p2()
{

}

Rect2D::Rect2D(Point2D p1_, Point2D p2_):
  p1(p1_),
  p2(p2_)
{

}

Rect2D::Rect2D(float x1, float y1, float x2, float y2):
  p1(x1, y1),
  p2(x2, y2)
{

}

void Rect2D::normalize() {
  if (p2.x < p1.x) {
    std::swap(p2.x, p1.x);
  }

  if (p2.y < p1.y) {
    std::swap(p2.y, p1.y);
  }
}

void Rect2D::resize(Point2D size) {
  p2 = p1 + size;
}

Point2D Rect2D::get_size() const {
  return p2 - p1;
}

bool Rect2D::collides(const Rect2D a) const {
  return (p2.x > a.p1.x || a.p2.x > p1.x) && (p2.y > a.p1.y || a.p2.y > p1.y);
}

bool Rect2D::is_inside(const Point2D a) const {
  return (a.x > p1.x && a.x < p2.x) && (a.y > p1.y && a.y < p2.y);
}

bool Rect2D::operator ==(const Rect2D a) const {
  return (p1 == a.p1) && (p2 == a.p2);
}

bool Rect2D::operator !=(const Rect2D a) const {
  return (p1 != a.p1) || (p2 != a.p2);
}

//------------------------------------------------------------------------------
// Rect3D
//------------------------------------------------------------------------------

Rect3D::Rect3D():
  p1(),
  p2()
{

}

Rect3D::Rect3D(Point3D p1_, Point3D p2_):
  p1(p1_),
  p2(p2_)
{

}

Rect3D::Rect3D(float x1, float y1, float z1, float x2, float y2, float z2):
  p1(x1, y1, z1),
  p2(x2, y2, z2)
{

}

void Rect3D::normalize() {
  if (p2.x < p1.x) {
    std::swap(p2.x, p1.x);
  }

  if (p2.y < p1.y) {
    std::swap(p2.y, p1.y);
  }

  if (p2.z < p1.z) {
    std::swap(p2.z, p1.z);
  }
}

void Rect3D::resize(Point3D size) {
  p2 = p1 + size;
}

Point3D Rect3D::get_size() const {
  return p2 - p1;
}

bool Rect3D::collides(const Rect3D a) const {
  return (p2.x > a.p1.x || a.p2.x > p1.x) && (p2.y > a.p1.y || a.p2.y > p1.y) && (p2.z > a.p1.z || a.p2.z > p1.z);
}

bool Rect3D::is_inside(const Point3D a) const {
  return (a.x > p1.x && a.x < p2.x) && (a.y > p1.y && a.y < p2.y) && (a.z > p1.z && a.z < p2.z);
}

bool Rect3D::operator ==(const Rect3D a) const {
  return (p1 == a.p1) && (p2 == a.p2);
}

bool Rect3D::operator !=(const Rect3D a) const {
  return (p1 != a.p1) || (p2 != a.p2);
}
