#include "voxel.h"

#include <GL/gl.h>

namespace voxel {

  void drawToeHexagon(char n) {
    glScalef((n & 1) ? 1.0f : -1.0f, (n & 2) ? 1.0f : -1.0f, (n & 4) ? 1.0f : -1.0f);

    glBegin(GL_TRIANGLE_FAN);
    glVertex3f( 0.25f, 0.25f, 0.25f);
    glVertex3f( 0.25f, 0.00f, 0.50f);
    glVertex3f( 0.50f, 0.00f, 0.25f);
    glVertex3f( 0.50f, 0.25f, 0.00f);
    glVertex3f( 0.25f, 0.50f, 0.00f);
    glVertex3f( 0.00f, 0.50f, 0.25f);
    glVertex3f( 0.00f, 0.25f, 0.50f);
    glEnd();

    glScalef((n & 1) ? 1.0f : -1.0f, (n & 2) ? 1.0f : -1.0f, (n & 4) ? 1.0f : -1.0f);
  }

  void drawToeQuad(char n) {
    if (n & 1) {
      glScalef(-1.0f, -1.0f, -1.0f);
    }

    glBegin(GL_QUADS);
    switch (n/2) {
      case 0:
        glVertex3f( 0.25f, 0.00f, 0.50f);
        glVertex3f( 0.00f, 0.25f, 0.50f);
        glVertex3f(-0.25f,-0.00f, 0.50f);
        glVertex3f(-0.00f,-0.25f, 0.50f);
        break;
      case 1:
        glVertex3f( 0.25f, 0.50f, 0.00f);
        glVertex3f( 0.00f, 0.50f, 0.25f);
        glVertex3f(-0.25f, 0.50f,-0.00f);
        glVertex3f(-0.00f, 0.50f,-0.25f);
        break;
      case 2:
        glVertex3f( 0.50f, 0.25f, 0.00f);
        glVertex3f( 0.50f, 0.00f, 0.25f);
        glVertex3f( 0.50f,-0.25f,-0.00f);
        glVertex3f( 0.50f,-0.00f,-0.25f);
        break;
      default:
        break;
    }
    glEnd();

    if (n & 1) {
      glScalef(-1.0f, -1.0f, -1.0f);
    }
  }

  void drawToe() {
    for (int i = 7; i >= 0; i--) {
      drawToeHexagon(i);
    }
    for (int i = 5; i >= 0; i--) {
      drawToeQuad(i);
    }
  }
}
