#include "colour.h"

#include <algorithm>
#include <random>

#include <GL/gl.h>

std::default_random_engine Colour::generator;

Colour::Colour():
  r(0.0f),
  g(0.0f),
  b(0.0f)
{

}

Colour::Colour(float r_, float g_, float b_):
  r(r_),
  g(g_),
  b(b_)
{

}

void Colour::cap() {
  r = std::min(r, 1.0f);
  g = std::min(g, 1.0f);
  b = std::min(b, 1.0f);

  r = std::max(r, 0.0f);
  g = std::max(g, 0.0f);
  b = std::max(b, 0.0f);
}

Colour& Colour::randomize(const Colour noise) {
  //std::default_random_engine generator;

  std::uniform_real_distribution<float> dist_r(r - noise.r, r + noise.r);
  std::uniform_real_distribution<float> dist_g(g - noise.g, g + noise.g);
  std::uniform_real_distribution<float> dist_b(b - noise.b, b + noise.b);

  r = dist_r(generator);
  g = dist_g(generator);
  b = dist_b(generator);

  cap();

  return *this;
}

void Colour::use() const {
  glColor3f(r, g, b);
}

Colour Colour::operator +(const Colour a) const {
  return Colour(r + a.r, g + a.g, b + a.b);
}

Colour& Colour::operator +=(const Colour a) {
  r += a.r;
  g += a.g;
  b += a.b;
  return *this;
}

ToeColour::ToeColour():
  hexagons(),
  quads()
{

}

ToeColour::ToeColour(const Colour c):
  hexagons(),
  quads()
{
  set_colour(c, c);
}

ToeColour::ToeColour(const Colour hexagon, const Colour quad):
  hexagons(),
  quads()
{
  set_colour(hexagon, quad);
}

ToeColour::ToeColour(std::array<Colour, 14> faces):
  hexagons(),
  quads()
{
  set_colour(faces);
}

ToeColour::ToeColour(std::array<Colour, 8> hexagon, std::array<Colour, 6> quad):
  hexagons(),
  quads()
{
  set_colour(hexagon, quad);
}

ToeColour& ToeColour::set_colour(const Colour c) {
  set_colour(c, c);
  return *this;
}

ToeColour& ToeColour::set_colour(const Colour hexagon, const Colour quad) {
  for (int i = 7; i >= 0; i--) {
    for (int j = 6; j >= 0; j--) {
      hexagons[i][j] = hexagon;
    }
  }
  for (int i = 5; i >= 0; i--) {
    for (int j = 3; j >= 0; j--) {
      quads[i][j] = quad;
    }
  }
  return *this;
}

ToeColour& ToeColour::set_colour(std::array<Colour, 14> faces) {
  for (int i = 7; i >= 0; i--) {
    for (int j = 6; j >= 0; j--) {
      hexagons[i][j] = faces[i];
    }
  }
  for (int i = 5; i >= 0; i--) {
    for (int j = 3; j >= 0; j--) {
      quads[i][j] = faces[j+8];
    }
  }
  return *this;
}

ToeColour& ToeColour::set_colour(std::array<Colour, 8> hexagon, std::array<Colour, 6> quad) {
  for (int i = 7; i >= 0; i--) {
    for (int j = 6; j >= 0; j--) {
      hexagons[i][j] = hexagon[i];
    }
  }
  for (int i = 5; i >= 0; i--) {
    for (int j = 3; j >= 0; j--) {
      quads[i][j] = quad[j];
    }
  }
  return *this;
}

ToeColour& ToeColour::noise(const Colour c) {
  const char p[24][5] = { //hexagon, hexxagon, quad, verticle6, verticle4
    {0,2,1,1,0},
    {0,2,5,2,1},
    {0,4,5,3,0},
    {0,4,3,4,0},
    {0,1,3,5,1},
    {0,1,1,6,1},
    {3,1,1,1,2},
    {3,1,4,2,3},
    {3,7,4,3,0},
    {3,7,2,4,0},
    {3,2,2,5,3},
    {3,2,1,6,3},
    {5,7,0,1,0},
    {5,7,4,2,1},
    {5,1,4,3,2},
    {5,1,3,4,2},
    {5,4,3,5,3},
    {5,4,0,6,3},
    {6,4,0,1,2},
    {6,4,5,2,3},
    {6,2,5,3,2},
    {6,2,2,4,2},
    {6,7,2,5,1},
    {6,7,0,6,1}
  };

  std::uniform_real_distribution<float> dist_r(-c.r, c.r);
  std::uniform_real_distribution<float> dist_g(-c.g, c.g);
  std::uniform_real_distribution<float> dist_b(-c.b, c.b);

  for (int i = 23; i >= 0; i--) {
    Colour delta(dist_r(Colour::generator), dist_g(Colour::generator), dist_b(Colour::generator));

    hexagons[p[i][0]][p[i][3]] += delta;
    hexagons[p[i][0]][p[i][3]].cap();

    hexagons[p[i][1]][p[i][3]] += delta;
    hexagons[p[i][1]][p[i][3]].cap();

    quads[p[i][2]][p[i][4]] += delta;
    quads[p[i][2]][p[i][4]].cap();
  }

  for (int i = 7; i >= 0; i--) {
    hexagons[i][0].randomize(c);
  }

  return *this;
}
