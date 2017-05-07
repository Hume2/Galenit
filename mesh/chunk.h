#ifndef MESH_CHUNK_H
#define MESH_CHUNK_H

#include <array>

#include "cuberect.h"
#include "toe.h"
#include "toepos.h"

class ToeColour;

class Chunk
{
  public:
    Chunk();

    static const int ROW = 32;
    static const int PLANE = ROW * ROW;
    static const int MESH = ROW * PLANE;
    static const int TOECOUNT = MESH * 2;

    //static const Cuberect SPACE = {{0, 0, 0}, {ROW, ROW, ROW}};

    std::array<int, TOECOUNT> toes;

    int& operator[] (const Toepos pos);

    void draw(ToeColour colour);

    bool is_opaque(int id);
    bool is_free(const Toepos pos);
};

#endif // MESH_CHUNK_H
