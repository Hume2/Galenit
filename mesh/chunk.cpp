#include "chunk.h"

#include "point.h"

#include "../graphics/colour.h"
#include "../graphics/voxel.h"

#include <random>
#include <GL/gl.h>

//ToeColour c_l_r(Colour(1, 1, 1), Colour(0, 1, 0));

Chunk::Chunk() :
  toes()
{
  for (int i = MESH-1; i >= 0; i--) {
    toes[i] = rand() % 50 == 0;
    toes[i+32768] = toes[i];
  }
  //c_l_r.noise(Colour(0.5f, 0.5f, 0.5f), true);
}

int& Chunk::operator [](const Toepos pos) {
  return toes[pos.x + pos.y*ROW + pos.z*PLANE + (pos.mesh == Toepos::ZOT ? MESH : 0)];
}

bool Chunk::is_opaque(int id) {
  return id;
}

bool Chunk::is_free(const Toepos pos) {
  if ((pos.x < 0) || (pos.y < 0) || (pos.z < 0) || (pos.x >= ROW) || (pos.y >= ROW) || (pos.z >= ROW) ) {
    return true;
  } else {
    return !is_opaque( (*this)[pos] );
  }
}

void Chunk::draw(ToeColour colour) {
  Point3D shift;
  Toepos pos, pos2;
  for (int i = 0; i < TOECOUNT; i++) {
    if(toes[i]) {
      for (int j = 1; j <= 14; j++) {
        pos2 = pos + dir::def[j];
        if (is_free(pos2)) {
          voxel::drawToeFace(j, colour);
        }
      }
      //voxel::drawToe(colour);
    }

    shift = Point3D(1.0f, 0.0f, 0.0f);
    pos.x++;
    if ((i+1)%32 == 0) {
      shift += Point3D(-ROW, 1.0f, 0.0f);
      pos.x -= ROW;
      pos.y++;

      if ((i+1)%1024 == 0) {
        shift += Point3D(0.0f, -ROW, 1.0f);
        pos.y -= ROW;
        pos.z++;

        if ((i+1)%32768 == 0) {
          pos.z -= ROW;
          pos.mesh = Toepos::ZOT;
          shift += Point3D(0.5f, 0.5f, -ROW + 0.5f);
        }
      }
    }
    glTranslatef(shift.x, shift.y, shift.z);
  }
  glTranslatef(-1.0, -1.0, -17.0);
}
