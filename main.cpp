//
// This code was created by Jeff Molofee '99 (ported to Linux/GLUT by Richard Campbell '99)
//
// If you've found this code useful, please let me know.
//
// Visit me at www.demonews.com/hosted/nehe 
// (email Richard Campbell at ulmont@bellsouth.net)
//
#include <ctime>
#include <random>
#include <string>

#include <GL/glut.h>    // Header File For The GLUT Library 
#include <GL/gl.h>	// Header File For The OpenGL32 Library
#include <GL/glu.h>	// Header File For The GLu32 Library
//#include <GL/glaux.h>
#include <stdlib.h>     // Header file for malloc/free.
#include <unistd.h>     // Header file for sleeping.

#include "main.h"

#include "graphics/voxel.h"
#include "mesh/chunk.h"

ToeColour clr(Colour(1, 1, 1), Colour(0, 1, 0));
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

/* ascii code for the escape key */
#define ESCAPE 27

/* The number of our GLUT window */
int window; 

/* Image type - contains height, width, and data */
struct Image {
    unsigned long sizeX;
    unsigned long sizeY;
    char *data;
};
typedef struct Image Image;

// quick and dirty bitmap loader...for 24 bit bitmaps with 1 plane only.
// See http://www.dcs.ed.ac.uk/~mxr/gfx/2d/BMP.txt for more info.
int ImageLoad(std::string filename, Image *image) {
  FILE *file;
  unsigned long size;                 // size of the image in bytes.
  unsigned long i;                    // standard counter.
  unsigned short int planes;          // number of planes in image (must be 1)
  unsigned short int bpp;             // number of bits per pixel (must be 24)
  char temp;                          // temporary color storage for bgr-rgb conversion.

  // make sure the file is there.
  if ((file = fopen(filename.c_str(), "rb"))==NULL)
  {
    printf("File Not Found : %s\n",filename.c_str());
    return 0;
  }

  // seek through the bmp header, up to the width/height:
  fseek(file, 18, SEEK_CUR);

  // read the width
  if ((i = fread(&image->sizeX, 4, 1, file)) != 1) {
    printf("Error reading width from %s.\n", filename.c_str());
    return 0;
  }
  printf("Width of %s: %lu\n", filename.c_str(), image->sizeX);

  // read the height
  if ((i = fread(&image->sizeY, 4, 1, file)) != 1) {
    printf("Error reading height from %s.\n", filename.c_str());
    return 0;
  }
  printf("Height of %s: %lu\n", filename.c_str(), image->sizeY);

  // calculate the size (assuming 24 bits or 3 bytes per pixel).
  size = image->sizeX * image->sizeY * 3;

  // read the planes
  if ((fread(&planes, 2, 1, file)) != 1) {
    printf("Error reading planes from %s.\n", filename.c_str());
    return 0;
  }
  if (planes != 1) {
    printf("Planes from %s is not 1: %u\n", filename.c_str(), planes);
    return 0;
  }

  // read the bpp
  if ((i = fread(&bpp, 2, 1, file)) != 1) {
    printf("Error reading bpp from %s.\n", filename.c_str());
    return 0;
  }
  if (bpp != 24) {
    printf("Bpp from %s is not 24: %u\n", filename.c_str(), bpp);
    return 0;
  }

  // seek past the rest of the bitmap header.
  fseek(file, 24, SEEK_CUR);

  // read the data.
  image->data = (char *) malloc(size);
  if (image->data == NULL) {
    printf("Error allocating memory for color-corrected image data");
    return 0;
  }

  if ((i = fread(image->data, size, 1, file)) != 1) {
    printf("Error reading image data from %s.\n", filename.c_str());
    return 0;
  }

  for (i=0;i<size;i+=3) { // reverse all of the colors. (bgr -> rgb)
    temp = image->data[i];
    image->data[i] = image->data[i+2];
    image->data[i+2] = temp;
  }

  // we're done.
  return 1;
}

// Load Bitmaps And Convert To Textures
bool LoadGLTextures() {
  // Load Texture
  Image *image1;

  // allocate space for texture
  image1 = (Image *) malloc(sizeof(Image));
  if (image1 == NULL) {
    printf("Error allocating space for image");
    exit(0);
  }

  if (!ImageLoad("tex.bmp", image1)) {
    exit(1);
  }

  // Create Texture
  glGenTextures(1, &texture[0]);
  glBindTexture(GL_TEXTURE_2D, texture[0]);   // 2d texture (x and y size)

  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR); // scale linearly when image bigger than texture
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST); // scale linearly when image smalled than texture

  // 2d texture, level of detail 0 (normal), 3 components (red, green, blue), x size from image, y size from image,
  // border 0 (normal), rgb color data, unsigned byte data, and finally the data itself.
  glTexImage2D(GL_TEXTURE_2D, 0, 3, image1->sizeX, image1->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, image1->data);
  return true;
}

/* A general OpenGL initialization function.  Sets all of the initial parameters. */
bool InitGL(int Width, int Height)	        // We call this right after our OpenGL window is created.
{
  glClearColor(0.0f, 0.0f, 0.0f, 0.0f);		// This Will Clear The Background Color To Black
  glClearDepth(1.0);				// Enables Clearing Of The Depth Buffer
  //glDepthFunc(GL_LESS);				// The Type Of Depth Test To Do
  glEnable(GL_DEPTH_TEST);			// Enables Depth Testing
  glShadeModel(GL_SMOOTH);			// Enables Smooth Color Shading

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();				// Reset The Projection Matrix

  gluPerspective(90.0f,(GLfloat)Width/(GLfloat)Height,0.1f,100.0f);	// Calculate The Aspect Ratio Of The Window

  glMatrixMode(GL_MODELVIEW);

  if (!LoadGLTextures()) {// Nahraje texturu
    return false;
  }

  //glEnable(GL_TEXTURE_2D);// Zapne mapování textur
  glEnable(GL_BLEND);
  glDepthFunc(GL_LEQUAL);// Typ hloubkového testování
  glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);// Nejlepší perspektivní korekce

  glLightfv(GL_LIGHT1, GL_AMBIENT, LightAmbient);// Nastavení okolního světla
  glLightfv(GL_LIGHT1, GL_DIFFUSE, LightDiffuse);// Nastavení přímého světla
  glLightfv(GL_LIGHT1, GL_POSITION,LightPosition);// Nastavení pozice světla
  glEnable(GL_LIGHT1);// Zapne světlo

  //glColor4f(1.0f,1.0f,1.0f,0.5f);// Plný jas, 50% alfa
  glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);

  return true;
}

/* The function called when our window is resized (which shouldn't happen, because we're fullscreen) */
void ReSizeGLScene(int Width, int Height)
{
  if (Height==0)				// Prevent A Divide By Zero If The Window Is Too Small
    Height=1;

  glViewport(0, 0, Width, Height);		// Reset The Current Viewport And Perspective Transformation

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  gluPerspective(45.0f,(GLfloat)Width/(GLfloat)Height,0.1f,1000.0f);
  glMatrixMode(GL_MODELVIEW);
}

/* The main drawing function. */
void DrawGLScene()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);		// Clear The Screen And The Depth Buffer
  glLoadIdentity();				// Reset The View

  glTranslatef(-15.0f, -15.0f, z);
  glRotatef(yrot, 0, 1, 0);
  glRotatef(xrot, 1, 0, 0);

  //voxel::drawToe(clr);
  glBindTexture(GL_TEXTURE_2D, texture[0]);
  ch.draw(clr);

  // since this is double buffered, swap the buffers to display what just got drawn.
  glutSwapBuffers();

  xrot += xspeed;
  yrot += yspeed;
  //z += zspeed;
  //rot += 0.4;

}

/* The function called whenever a key is pressed. */
void keyPressed(unsigned char key, int x, int y) 
{
  /* avoid thrashing this procedure */
  usleep(100);

  switch (key) {
    case ESCAPE: // kill everything.
      /* shut down our window */
      glutDestroyWindow(window);

      /* exit the program...normal termination. */
      exit(1);
      break; // redundant.

    case 76:
    case 108: // switch the lighting.
      printf("L/l pressed; light is: %d\n", light);
      light = light ? 0 : 1;              // switch the current value of light, between 0 and 1.
      printf("Light is now: %d\n", light);
      if (!light) {
        glDisable(GL_LIGHTING);
      } else {
        glEnable(GL_LIGHTING);
      }
      break;

    case 70:
    case 102: // switch the filter.
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

/* The function called whenever a normal key is pressed. */
void specialKeyPressed(int key, int x, int y)
{
  /* avoid thrashing this procedure */
  usleep(100);

  switch (key) {
    case GLUT_KEY_PAGE_UP: // move the cube into the distance.
      z-=0.02f;
      break;

    case GLUT_KEY_PAGE_DOWN: // move the cube closer.
      z+=0.02f;
      break;

    case GLUT_KEY_UP: // decrease x rotation speed;
      xspeed-=0.01f;
      break;

    case GLUT_KEY_DOWN: // increase x rotation speed;
      xspeed+=0.01f;
      break;

    case GLUT_KEY_LEFT: // decrease y rotation speed;
      yspeed-=0.01f;
      break;

    case GLUT_KEY_RIGHT: // increase y rotation speed;
      yspeed+=0.01f;
      break;

    default:
      break;
  }
}

int main(int argc, char **argv) 
{
  srandom(time(0));
  clr.noise(Colour(0.5, 1.0, 0.0), true);

  /* Initialize GLUT state - glut will take any command line arguments that pertain to it or
     X Windows - look at its documentation at http://reality.sgi.com/mjk/spec3/spec3.html */
  glutInit(&argc, argv);

  /* Select type of Display mode:
     Double buffer
     RGBA color
     Alpha components supported
     Depth buffer */
  glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_ALPHA | GLUT_DEPTH);

  /* get a 640 x 480 window */
  glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);

  /* the window starts at the upper left corner of the screen */
  glutInitWindowPosition(0, 0);

  /* Open a window */
  window = glutCreateWindow("Jeff Molofee's GL Code Tutorial ... NeHe '99");

  /* Register the function to do all our OpenGL drawing. */
  glutDisplayFunc(&DrawGLScene);

  /* Go fullscreen.  This is as soon as possible. */
  glutFullScreen();

  /* Even if there are no events, redraw our gl scene. */
  glutIdleFunc(&DrawGLScene);

  /* Register the function called when our window is resized. */
  glutReshapeFunc(&ReSizeGLScene);

  /* Register the function called when the keyboard is pressed. */
  glutKeyboardFunc(&keyPressed);

  /* Register the function called when special keys (arrows, page down, etc) are pressed. */
  glutSpecialFunc(&specialKeyPressed);

  /* Initialize our window. */
  InitGL(640, 480);
  
  /* Start Event Processing Engine */
  glutMainLoop();

  return 1;
}

