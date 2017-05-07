#ifndef GRAPHICS_COLOUR_H
#define GRAPHICS_COLOUR_H

#include <array>
#include <random>

class Colour
{
  public:
    Colour();
    Colour(float r_, float g_, float b_);
    Colour(float r_, float g_, float b_, float a_);

    float r, g, b, a;

    void cap();

    Colour& randomize(const Colour noise, bool bound);

    void use() const;

    Colour operator+(const Colour c) const;
    Colour& operator+=(const Colour c);

    Colour operator*(const Colour c) const;
    Colour& operator*=(const Colour c);

    static std::default_random_engine generator;
};

//TOE = Truncated OctahEdron
//česky KOT -u m. neživ. (Komolý OsmisTěn)

class ToeColour
{
  public:
    ToeColour();
    ToeColour(const Colour c);
    ToeColour(const Colour hexagon, const Colour quad);
    ToeColour(std::array<Colour, 14> faces);
    ToeColour(std::array<Colour, 8> hexagon, std::array<Colour, 6> quad);

    std::array<std::array<Colour, 7>, 8> hexagons;
    std::array<std::array<Colour, 4>, 6> quads;

    ToeColour& set_colour(const Colour c);
    ToeColour& set_colour(const Colour hexagon, const Colour quad);
    ToeColour& set_colour(std::array<Colour, 14> faces);
    ToeColour& set_colour(std::array<Colour, 8> hexagon, std::array<Colour, 6> quad);

    ToeColour& noise(const Colour c, bool bound);

    ToeColour operator+(const ToeColour a) const;
    ToeColour& operator+=(const ToeColour a);

    ToeColour operator*(const ToeColour a) const;
    ToeColour& operator*=(const ToeColour a);
};

#endif // GRAPHICS_COLOUR_H
