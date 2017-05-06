#include "colour.h"

#include <algorithm>
#include <random>

#include <GL/gl.h>

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
  std::default_random_engine generator;

  std::uniform_real_distribution<float> dist_r(r - noise.r, r + noise.r);
  std::uniform_real_distribution<float> dist_g(g - noise.g, g + noise.g);
  std::uniform_real_distribution<float> dist_b(b - noise.b, b + noise.b);

  r = dist_r(generator);
  g = dist_g(generator);
  b = dist_b(generator);

  return *this;
}

void Colour::use() const {
  glColor3f(r, g, b);
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
