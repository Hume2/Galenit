#include "toe.h"

#include <GL/gl.h>

#include "point.h"

#include "../graphics/voxel.h"

Toe::Toe()
{

}

void Toe::draw(Point3D pos) {
  glTranslatef(pos.x, pos.y, pos.z);
  voxel::drawToe(colour);
  glTranslatef(-pos.x, -pos.y, -pos.z);
}

void Toe::draw_it(ToeColour c, Point3D pos) {
  glTranslatef(pos.x, pos.y, pos.z);
  voxel::drawToe(c);
  glTranslatef(-pos.x, -pos.y, -pos.z);
}
