#ifndef MESH_TOE_H
#define MESH_TOE_H

#include "../graphics/colour.h"

class Point3D;

class Toe
{
  public:
    Toe();

    ToeColour colour;

    void draw(Point3D pos);
};

#endif // MESH_TOE_H
