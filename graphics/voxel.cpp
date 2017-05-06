#include "voxel.h"

#include <GL/gl.h>

namespace voxel {

  void drawToeHexagon(char n, const ToeColour c) {
    glScalef((n & 1) ? 1.0f : -1.0f, (n & 2) ? 1.0f : -1.0f, (n & 4) ? 1.0f : -1.0f);

    const float v[7][3] = {
      { 0.25f, 0.25f, 0.25f},
      { 0.25f, 0.00f, 0.50f},
      { 0.50f, 0.00f, 0.25f},
      { 0.50f, 0.25f, 0.00f},
      { 0.25f, 0.50f, 0.00f},
      { 0.00f, 0.50f, 0.25f},
      { 0.00f, 0.25f, 0.50f}
    };

    glBegin(GL_TRIANGLE_FAN);
    for (int i = 0; i < 7; i++) {
      c.hexagons[n][i].use();
      glVertex3f( v[i][0], v[i][1], v[i][2]);
    }
    c.hexagons[n][1].use();
    glVertex3f( v[1][0], v[1][1], v[1][2]);
    glEnd();

    glScalef((n & 1) ? 1.0f : -1.0f, (n & 2) ? 1.0f : -1.0f, (n & 4) ? 1.0f : -1.0f);
  }

  void drawToeQuad(char n, const ToeColour c) {
    if (n & 1) {
      glScalef(-1.0f, -1.0f, -1.0f);
    }

    const float v[4][2] = {
      { 0.25f, 0.00f},
      { 0.00f, 0.25f},
      {-0.25f,-0.00f},
      {-0.00f,-0.25f},
    };
    const float z = 0.50f;

    glBegin(GL_QUADS);
    switch (n/2) {
      case 0:
        for (int i = 0; i < 4; i++) {
          c.quads[n][i].use();
          glVertex3f( v[i][0], v[i][1], z);
        }
        break;
      case 1:
        for (int i = 0; i < 4; i++) {
          c.quads[n][i].use();
          glVertex3f( v[i][0], z, v[i][1]);
        }
        break;
      case 2:
        for (int i = 0; i < 4; i++) {
          c.quads[n][i].use();
          glVertex3f(z, v[i][0], v[i][1]);
        }
        break;
      default:
        break;
    }
    glEnd();

    if (n & 1) {
      glScalef(-1.0f, -1.0f, -1.0f);
    }
  }

  void drawToe(const ToeColour c) {
    for (int i = 7; i >= 0; i--) {
      //glColor4f(1.0f, 0.0f, 1.0f/7*i, 0.0f);
      //Colour(1.0f, 0.0f, 1.0f/7*i).use();
      drawToeHexagon(i, c);
    }
    for (int i = 5; i >= 0; i--) {
      //Colour(0.0f, 1.0f, 1.0f/5*i).use();
      drawToeQuad(i, c);
    }
  }
}
