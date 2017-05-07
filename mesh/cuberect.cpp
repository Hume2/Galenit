#include "cuberect.h"

#include <algorithm>

#include "toepos.h"

Cuberect::Cuberect():
  p1(),
  p2()
{

}

Cuberect::Cuberect(Cubepos p1_, Cubepos p2_):
  p1(p1_),
  p2(p2_)
{

}

Cuberect::Cuberect(Toepos p1_, Cubepos p2_):
  p1(p1_),
  p2(p2_)
{

}

Cuberect::Cuberect(Cubepos p1_, Toepos p2_):
  p1(p1_),
  p2(p2_)
{

}

Cuberect::Cuberect(Toepos p1_, Toepos p2_):
  p1(p1_),
  p2(p2_)
{

}

Cuberect::Cuberect(int x1, int y1, int z1, int x2, int y2, int z2):
  p1(x1, y1, z1),
  p2(x2, y2, z2)
{

}

void Cuberect::normalize() {
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

void Cuberect::resize(Cubepos size) {
  p2 = p1 + size;
}

Cubepos Cuberect::get_size() const {
  return p2 - p1;
}

bool Cuberect::collides(const Cuberect a) const {
  return (p2.x > a.p1.x || a.p2.x > p1.x) && (p2.y > a.p1.y || a.p2.y > p1.y) && (p2.z > a.p1.z || a.p2.z > p1.z);
}

bool Cuberect::is_inside(const Cubepos a) const {
  return (a.x > p1.x && a.x < p2.x) && (a.y > p1.y && a.y < p2.y) && (a.z > p1.z && a.z < p2.z);
}

bool Cuberect::operator ==(const Cuberect a) const {
  return (p1 == a.p1) && (p2 == a.p2);
}

bool Cuberect::operator !=(const Cuberect a) const {
  return (p1 != a.p1) || (p2 != a.p2);
}
