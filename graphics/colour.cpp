#include "colour.h"

#include <algorithm>
#include <random>

#include <GL/gl.h>

std::default_random_engine Colour::generator;

Colour::Colour():
  r(0.0f),
  g(0.0f),
  b(0.0f),
  a(1.0f)
{

}

Colour::Colour(float r_, float g_, float b_):
  r(r_),
  g(g_),
  b(b_),
  a(1.0f)
{

}

Colour::Colour(float r_, float g_, float b_, float a_):
  r(r_),
  g(g_),
  b(b_),
  a(a_)
{

}

void Colour::cap() {
  r = std::min(r, 1.0f);
  g = std::min(g, 1.0f);
  b = std::min(b, 1.0f);
  a = std::min(a, 1.0f);

  r = std::max(r, 0.0f);
  g = std::max(g, 0.0f);
  b = std::max(b, 0.0f);
  a = std::max(a, 0.0f);
}

Colour& Colour::randomize(const Colour noise, bool bound) {
  std::uniform_real_distribution<float> dist_r(-noise.r, noise.r);

  if (bound) {
    float d = dist_r(generator);
    r += d;
    g += d;
    b += d;
  } else {
    std::uniform_real_distribution<float> dist_g(-noise.g, noise.g);
    std::uniform_real_distribution<float> dist_b(-noise.b, noise.b);

    r += dist_r(generator);
    g += dist_g(generator);
    b += dist_b(generator);
  }

  cap();

  return *this;
}

void Colour::use() const {
  glColor4f(r, g, b, a);
}

Colour Colour::operator +(const Colour c) const {
  return Colour(r + c.r, g + c.g, b + c.b, std::min(1.0f, a + c.a));
}

Colour& Colour::operator +=(const Colour c) {
  r += c.r;
  g += c.g;
  b += c.b;
  a = std::min(1.0f, a + c.a);
  return *this;
}

Colour Colour::operator *(const Colour c) const {
  return Colour(r * c.r, g * c.g, b * c.b, a * c.a);
}

Colour& Colour::operator *=(const Colour c) {
  r *= c.r;
  g *= c.g;
  b *= c.b;
  a *= c.a;
  return *this;
}

//------------------------------------------------------------------------------
// Toe Colour
//------------------------------------------------------------------------------

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

ToeColour& ToeColour::noise(const Colour c, bool bound) {
  const char p[24][5] = { //hexagon, hexxagon, quad, verticle6, verticle4
    {0,2,0,1,0},
    {0,2,4,2,1},
    {0,4,4,3,0},
    {0,4,2,4,0},
    {0,1,2,5,1},
    {0,1,0,6,1},
    {3,1,0,1,2},
    {3,1,5,2,3},
    {3,7,5,3,0},
    {3,7,3,4,0},
    {3,2,3,5,3},
    {3,2,0,6,3},
    {5,7,1,1,0},
    {5,7,5,2,1},
    {5,1,5,3,2},
    {5,1,2,4,2},
    {5,4,2,5,3},
    {5,4,1,6,3},
    {6,4,1,1,2},
    {6,4,4,2,3},
    {6,2,4,3,2},
    {6,2,3,4,2},
    {6,7,3,5,1},
    {6,7,1,6,1}
  };

  std::uniform_real_distribution<float> dist_r(-c.r, c.r);
  std::uniform_real_distribution<float> dist_g(-c.g, c.g);
  std::uniform_real_distribution<float> dist_b(-c.b, c.b);

  for (int i = 23; i >= 0; i--) {
    Colour delta;
    if (bound) {
      delta.r = dist_r(Colour::generator);
      delta.g = delta.r;
      delta.b = delta.r;
    } else {
      delta.r = dist_r(Colour::generator);
      delta.g = dist_g(Colour::generator);
      delta.b = dist_b(Colour::generator);
    }

    hexagons[p[i][0]][p[i][3]] += delta;
    hexagons[p[i][0]][p[i][3]].cap();

    hexagons[p[i][1]][p[i][3]] += delta;
    hexagons[p[i][1]][p[i][3]].cap();

    quads[p[i][2]][p[i][4]] += delta;
    quads[p[i][2]][p[i][4]].cap();
  }

  for (int i = 7; i >= 0; i--) {
    hexagons[i][0].randomize(c, bound);
  }

  return *this;
}

ToeColour ToeColour::operator+(const ToeColour a) const {
  ToeColour result;
  for (int i = 7; i >= 0; i--) {
    for (int j = 6; j >= 0; j--) {
      result.hexagons[i][j] = hexagons[i][j] + a.hexagons[i][j];
    }
  }
  for (int i = 5; i >= 0; i--) {
    for (int j = 3; j >= 0; j--) {
      result.quads[i][j] = quads[i][j] + a.quads[i][j];
    }
  }
  return result;
}

ToeColour ToeColour::operator*(const ToeColour a) const {
  ToeColour result;
  for (int i = 7; i >= 0; i--) {
    for (int j = 6; j >= 0; j--) {
      result.hexagons[i][j] = hexagons[i][j] * a.hexagons[i][j];
    }
  }
  for (int i = 5; i >= 0; i--) {
    for (int j = 3; j >= 0; j--) {
      result.quads[i][j] = quads[i][j] * a.quads[i][j];
    }
  }
  return result;
}

ToeColour& ToeColour::operator+=(const ToeColour a) {
  for (int i = 7; i >= 0; i--) {
    for (int j = 6; j >= 0; j--) {
      hexagons[i][j] += a.hexagons[i][j];
    }
  }
  for (int i = 5; i >= 0; i--) {
    for (int j = 3; j >= 0; j--) {
      quads[i][j] += a.quads[i][j];
    }
  }
  return *this;
}

ToeColour& ToeColour::operator*=(const ToeColour a) {
  for (int i = 7; i >= 0; i--) {
    for (int j = 6; j >= 0; j--) {
      hexagons[i][j] *= a.hexagons[i][j];
    }
  }
  for (int i = 5; i >= 0; i--) {
    for (int j = 3; j >= 0; j--) {
      quads[i][j] *= a.quads[i][j];
    }
  }
  return *this;
}
