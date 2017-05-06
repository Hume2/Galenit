#ifndef COLOUR_H
#define COLOUR_H

#include <array>

class Colour
{
  public:
    Colour();
    Colour(float r_, float g_, float b_);

    float r, g, b;

    void cap();

    Colour& randomize(const Colour noise);

    void use() const;
};

//TOE = Truncated OctaahEdron
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
};

#endif // COLOUR_H
