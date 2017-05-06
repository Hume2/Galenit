#ifndef MESH_CHUNK_H
#define MESH_CHUNK_H

#include <array>

#include "toe.h"
#include "toepos.h"

class ToeColour;

class Chunk
{
  public:
    Chunk();

    static const int TOECOUNT = 32*32*32*2;

    std::array<int, TOECOUNT> toes;

    int& operator[] (const Toepos pos);

    void draw(ToeColour colour);
};

#endif // MESH_CHUNK_H
