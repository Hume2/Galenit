#ifndef MESH_CUBERECT_H
#define MESH_CUBERECT_H

#include "cubepos.h"

class Toepos;

class Cuberect
{
  public:
    Cuberect();
    Cuberect(Cubepos p1_, Cubepos p2_);
    Cuberect(Toepos p1_, Cubepos p2_);
    Cuberect(Cubepos p1_, Toepos p2_);
    Cuberect(Toepos p1_, Toepos p2_);
    Cuberect(int x1, int y1, int z1, int x2, int y2, int z2);

    Cubepos p1, p2;

    void normalize(); //sets the size to positive coordinates
    void resize(Cubepos size);

    Cubepos get_size() const;
    bool collides(const Cuberect a) const;
    bool is_inside(const Cubepos a) const;

    bool operator==(const Cuberect a) const;
    bool operator!=(const Cuberect a) const;
};

#endif // MESH_CUBERECT_H
