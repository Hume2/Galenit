#ifndef MESH_CUBEPOS_H
#define MESH_CUBEPOS_H

class Point3D;

class Cubepos
{
  public:
    enum Dir{ZERO, BACK, FRONT, UP, DOWN, RIGHT, LEFT};

    Cubepos();
    Cubepos(int x_, int y_, int z_);
    Cubepos(Point3D point);

    int x, y, z;

    Cubepos operator+(const Cubepos a) const;
    Cubepos& operator+=(const Cubepos a);
};


namespace dir{
  const Cubepos cube[7] = {
    /*ZERO =*/ {0, 0, 0},

    /*BACK  =*/ { 0, 0, 1},
    /*FRONT =*/ { 0, 0,-1},
    /*UP    =*/ { 0, 1, 0},
    /*DOWN  =*/ { 0,-1, 0},
    /*RIGHT =*/ { 1, 0, 0},
    /*LEFT  =*/ {-1, 0, 0}
  };
}
#endif // MESH_CUBEPOS_H
