#include <ctime>
#include <random>
#include <string>

#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include <stdlib.h>
#include <unistd.h>

#include "main.h"

#include "graphics/voxel.h"
#include "mesh/chunk.h"

ToeColour clr(Colour(1, 1, 1, 0.5), Colour(0, 1, 0, 0.5));
Chunk ch;
float rot = 60;

GLuint texture[1];

bool light = false;// Světlo ON/OFF
bool lp;// Stisknuto L?
bool fp;// Stisknuto F?

GLfloat xrot;// X Rotace
GLfloat yrot;// Y Rotace
GLfloat xspeed;// Rychlost x rotace
GLfloat yspeed;// Rychlost y rotace
GLfloat z = -15.0f;// Hloubka v obrazovce

GLfloat LightAmbient[]= { 0.5f, 0.5f, 0.5f, 1.0f };// Okolní světlo
GLfloat LightDiffuse[]= { 1.0f, 1.0f, 1.0f, 1.0f };// Přímé světlo
GLfloat LightPosition[]= { 0.0f, 0.0f, 2.0f, 1.0f };// Pozice světla

GLuint filter;// Specifikuje používaný texturový filtr

#define ESCAPE 27

int window; 

struct Image {
    unsigned long sizeX;
    unsigned long sizeY;
    char *data;
};
typedef struct Image Image;

int ImageLoad(std::string filename, Image *image) {
  FILE *file;
  unsigned long size;
  unsigned long i;
  unsigned short int planes;
  unsigned short int bpp;
  char temp;

  if ((file = fopen(filename.c_str(), "rb"))==NULL)
  {
    printf("File Not Found : %s\n",filename.c_str());
    return 0;
  }

  fseek(file, 18, SEEK_CUR);

  if ((i = fread(&image->sizeX, 4, 1, file)) != 1) {
    printf("Error reading width from %s.\n", filename.c_str());
    return 0;
  }
  printf("Width of %s: %lu\n", filename.c_str(), image->sizeX);

  if ((i = fread(&image->sizeY, 4, 1, file)) != 1) {
    printf("Error reading height from %s.\n", filename.c_str());
    return 0;
  }
  printf("Height of %s: %lu\n", filename.c_str(), image->sizeY);

  size = image->sizeX * image->sizeY * 3;

  if ((fread(&planes, 2, 1, file)) != 1) {
    printf("Error reading planes from %s.\n", filename.c_str());
    return 0;
  }
  if (planes != 1) {
    printf("Planes from %s is not 1: %u\n", filename.c_str(), planes);
    return 0;
  }

  if ((i = fread(&bpp, 2, 1, file)) != 1) {
    printf("Error reading bpp from %s.\n", filename.c_str());
    return 0;
  }
  if (bpp != 24) {
    printf("Bpp from %s is not 24: %u\n", filename.c_str(), bpp);
    return 0;
  }

  fseek(file, 24, SEEK_CUR);

  image->data = (char *) malloc(size);
  if (image->data == NULL) {
    printf("Error allocating memory for color-corrected image data");
    return 0;
  }

  if ((i = fread(image->data, size, 1, file)) != 1) {
    printf("Error reading image data from %s.\n", filename.c_str());
    return 0;
  }

  for (i=0;i<size;i+=3) {
    temp = image->data[i];
    image->data[i] = image->data[i+2];
    image->data[i+2] = temp;
  }

  return 1;
}

bool LoadGLTextures() {
  Image *image1;

  image1 = (Image *) malloc(sizeof(Image));
  if (image1 == NULL) {
    printf("Error allocating space for image");
    exit(0);
  }

  if (!ImageLoad("tex.bmp", image1)) {
    exit(1);
  }

  glGenTextures(1, &texture[0]);
  glBindTexture(GL_TEXTURE_2D, texture[0]);

  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);

  glTexImage2D(GL_TEXTURE_2D, 0, 3, image1->sizeX, image1->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, image1->data);
  return true;
}

bool InitGL(int Width, int Height)
{
  glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
  glClearDepth(1.0);
  //glDepthFunc(GL_LESS);
  glEnable(GL_DEPTH_TEST);
  glShadeModel(GL_SMOOTH);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  gluPerspective(90.0f,(GLfloat)Width/(GLfloat)Height,0.1f,100.0f);

  glMatrixMode(GL_MODELVIEW);

  if (!LoadGLTextures()) {
    return false;
  }

  //glEnable(GL_TEXTURE_2D);// Zapne mapování textur
  glEnable(GL_BLEND);
  glDepthFunc(GL_LEQUAL);
  glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

  glLightfv(GL_LIGHT1, GL_AMBIENT, LightAmbient);
  glLightfv(GL_LIGHT1, GL_DIFFUSE, LightDiffuse);
  glLightfv(GL_LIGHT1, GL_POSITION,LightPosition);
  glEnable(GL_LIGHT1);

  glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);

  return true;
}

void ReSizeGLScene(int Width, int Height)
{
  if (Height==0)
    Height=1;

  glViewport(0, 0, Width, Height);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  gluPerspective(45.0f,(GLfloat)Width/(GLfloat)Height,0.1f,1000.0f);
  glMatrixMode(GL_MODELVIEW);
}

void DrawGLScene()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();

  glRotatef(yrot, 1, 0, 0);
  glRotatef(xrot, 0, 1, 0);
  glTranslatef(-15.0f, -15.0f, z);

  glBindTexture(GL_TEXTURE_2D, texture[0]);
  ch.draw(clr);

  glutSwapBuffers();

  xrot += xspeed;
  yrot += yspeed;
  //z += zspeed;
  //rot += 0.4;

}

void keyPressed(unsigned char key, int x, int y) 
{
  usleep(100);

  switch (key) {
    case ESCAPE:
      glutDestroyWindow(window);
      exit(1);
      break;

    case 76:
    case 108:
      printf("L/l pressed; light is: %d\n", light);
      light = light ? 0 : 1;
      printf("Light is now: %d\n", light);
      if (!light) {
        glDisable(GL_LIGHTING);
      } else {
        glEnable(GL_LIGHTING);
      }
      break;

    case 70:
    case 102:
      printf("F/f pressed; filter is: %d\n", filter);
      filter+=1;
      if (filter>2) {
        filter=0;
      }
      printf("Filter is now: %d\n", filter);
      break;

    default:
      break;
  }
}

void specialKeyPressed(int key, int x, int y)
{
  usleep(10);

  switch (key) {
    case GLUT_KEY_PAGE_UP:
      z-=0.02f;
      break;

    case GLUT_KEY_PAGE_DOWN:
      z+=0.02f;
      break;

    case GLUT_KEY_UP:
      yrot-=1.0f;
      break;

    case GLUT_KEY_DOWN:
      yrot+=1.0f;
      break;

    case GLUT_KEY_LEFT:
      xrot+=1.0f;
      break;

    case GLUT_KEY_RIGHT:
      xrot-=1.0f;
      break;

    default:
      break;
  }
}

int main(int argc, char **argv) 
{
  srandom(time(0));
  clr.noise(Colour(0.5, 1.0, 0.0), true);

  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_ALPHA | GLUT_DEPTH);
  glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
  glutInitWindowPosition(0, 0);

  window = glutCreateWindow("Galenit");

  glutDisplayFunc(&DrawGLScene);
  glutFullScreen();
  glutIdleFunc(&DrawGLScene);
  glutReshapeFunc(&ReSizeGLScene);
  glutKeyboardFunc(&keyPressed);
  glutSpecialFunc(&specialKeyPressed);

  InitGL(640, 480);
  glutMainLoop();

  return 1;
}

