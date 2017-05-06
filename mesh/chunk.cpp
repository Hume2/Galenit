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
  for (int i = TOECOUNT/2-1; i >= 0; i--) {
    toes[i] = rand() % 100 == 0;
    toes[i+32768] = toes[i];
  }
  //c_l_r.noise(Colour(0.5f, 0.5f, 0.5f), true);
}

int& Chunk::operator [](const Toepos pos) {
  return toes[pos.x + pos.y*32 + pos.z*1024 + (pos.mesh == Toepos::ZOT ? 32768 : 0)];
}

void Chunk::draw(ToeColour colour) {
  Point3D shift;
  for (int i = 0; i < TOECOUNT; i++) {
    if(toes[i]) {
      voxel::drawToe(colour);
    }

    shift = Point3D(1.0f, 0.0f, 0.0f);
    if ((i+1)%32 == 0) {
      shift += Point3D(-32.0f, 1.0f, 0.0f);
      if ((i+1)%1024 == 0) {
        shift += Point3D(0.0f, -32.0f, 1.0f);
        if ((i+1)%32768 == 0) {
          shift += Point3D(0.5f, 0.5f, -31.5f);
        }
      }
    }
    glTranslatef(shift.x, shift.y, shift.z);
  }
  glTranslatef(-1.0, -1.0, -17.0);
}
