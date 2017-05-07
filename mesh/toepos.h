#ifndef MESH_TOEPOS_H
#define MESH_TOEPOS_H

class Cubepos;
class Point3D;

class Toepos
{
  public:
    enum Mesh{ASW, ZOT};
    enum Dir{ZERO, BACK, FRONT, UP, DOWN, RIGHT, LEFT, RUB, LUB, RDB, LDB, RUF, LUF, RDF, LDF};

    Toepos();
    Toepos(int x_, int y_, int z_, Mesh mesh_);
    Toepos(Point3D point);
    Toepos(Cubepos point);
    Toepos(Cubepos point, Mesh mesh_);

    int x,y,z;
    Mesh mesh;

    Toepos operator+(const Toepos a) const;
    Toepos operator-(const Toepos a) const;
    Toepos operator-() const;

    bool operator==(const Toepos a) const;
    bool operator!=(const Toepos a) const;

    Toepos& operator+=(const Toepos a);
    Toepos& operator-=(const Toepos a);
};

namespace dir{
  const Toepos def[15] = {
    /*ZERO =*/ {0, 0, 0, Toepos::ASW},

    /*BACK  =*/ { 0, 0, 1, Toepos::ASW},
    /*FRONT =*/ { 0, 0,-1, Toepos::ASW},
    /*UP    =*/ { 0, 1, 0, Toepos::ASW},
    /*DOWN  =*/ { 0,-1, 0, Toepos::ASW},
    /*RIGHT =*/ { 1, 0, 0, Toepos::ASW},
    /*LEFT  =*/ {-1, 0, 0, Toepos::ASW},

    /*RUB =*/ { 0, 0, 0, Toepos::ZOT},
    /*LUB =*/ {-1, 0, 0, Toepos::ZOT},
    /*RDB =*/ { 0,-1, 0, Toepos::ZOT},
    /*LDB =*/ {-1,-1, 0, Toepos::ZOT},
    /*RUF =*/ { 0, 0,-1, Toepos::ZOT},
    /*LUF =*/ {-1, 0,-1, Toepos::ZOT},
    /*RDF =*/ { 0,-1,-1, Toepos::ZOT},
    /*LDF =*/ {-1,-1,-1, Toepos::ZOT},
  };

  const Toepos::Dir up[5]    = {Toepos::UP,    Toepos::LUB, Toepos::RUB, Toepos::RUF, Toepos::LUF};
  const Toepos::Dir down[5]  = {Toepos::DOWN,  Toepos::LDB, Toepos::RDB, Toepos::RDF, Toepos::LDF};
  const Toepos::Dir left[5]  = {Toepos::LEFT,  Toepos::LUF, Toepos::LDF, Toepos::LUB, Toepos::LDB};
  const Toepos::Dir right[5] = {Toepos::RIGHT, Toepos::RUB, Toepos::RUF, Toepos::RDF, Toepos::RDB};
  const Toepos::Dir front[5] = {Toepos::FRONT, Toepos::RUF, Toepos::LUF, Toepos::LDF, Toepos::RDF};
  const Toepos::Dir back[5]  = {Toepos::BACK,  Toepos::LUB, Toepos::RUB, Toepos::LDB, Toepos::RDB};

  const Toepos::Dir ldf[7] = {Toepos::LDF, Toepos::LEFT,  Toepos::DOWN, Toepos::FRONT, Toepos::LUF, Toepos::RDF, Toepos::LDB};
  const Toepos::Dir ldb[7] = {Toepos::LDB, Toepos::LEFT,  Toepos::DOWN, Toepos::BACK,  Toepos::LDF, Toepos::LUB, Toepos::RDB};
  const Toepos::Dir luf[7] = {Toepos::LUF, Toepos::LEFT,  Toepos::UP,   Toepos::FRONT, Toepos::RUF, Toepos::LUF, Toepos::LDF};
  const Toepos::Dir lub[7] = {Toepos::LUB, Toepos::LEFT,  Toepos::UP,   Toepos::BACK,  Toepos::LUF, Toepos::LDB, Toepos::RUB};
  const Toepos::Dir rdf[7] = {Toepos::RDF, Toepos::RIGHT, Toepos::DOWN, Toepos::FRONT, Toepos::RDB, Toepos::RUF, Toepos::LDF};
  const Toepos::Dir rdb[7] = {Toepos::RDB, Toepos::RIGHT, Toepos::DOWN, Toepos::BACK,  Toepos::RUB, Toepos::LDB, Toepos::RDF};
  const Toepos::Dir ruf[7] = {Toepos::RUF, Toepos::RIGHT, Toepos::UP,   Toepos::FRONT, Toepos::RUB, Toepos::RDF, Toepos::LUF};
  const Toepos::Dir rub[7] = {Toepos::RUB, Toepos::RIGHT, Toepos::UP,   Toepos::FRONT, Toepos::LUB, Toepos::RDB, Toepos::RUF};
}

#endif // MESH_TOEPOS_H
