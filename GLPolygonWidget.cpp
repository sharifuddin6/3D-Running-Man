#include "GLPolygonWidget.h"

// constructor
GLPolygonWidget::GLPolygonWidget(QWidget *parent, GLPolygon *newPolygon)
 : QGLWidget(parent)
 { // constructor
  thePolygon = newPolygon;
 } // constructor

// called when OpenGL context is set up
void GLPolygonWidget::initializeGL()
 {
  // some constants to use
  static const GLfloat blackColour[4] = {0.0, 0.0, 0.0, 1.0}; // black
  static const GLfloat whiteColour[4] = {1.0, 1.0, 1.0, 1.0}; // white
  static const GLfloat greyColour[4] = {0.3, 0.3, 0.3, 1.0}; // grey
  static const GLfloat light_position[] = {-100.0, 100.0, 0.0, 1.0}; // light position

  // enable depth, and culling
  glEnable (GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);
  glDepthRange(1,-1);

  // set global lighting parameters first
  glShadeModel(GL_FLAT);   // use flat lighting
  glEnable(GL_COLOR_MATERIAL); // set material colours to match lighting
  
  // now set parameters for our one light source
  glEnable(GL_LIGHT0);
  glLightfv(GL_LIGHT0, GL_POSITION, light_position);
  glLightfv(GL_LIGHT0, GL_AMBIENT, greyColour);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, whiteColour);
  glLightfv(GL_LIGHT0, GL_SPECULAR, blackColour);
  
  glEnable(GL_LIGHTING);

  // smoothing on lines
  glEnable(GL_LINE_SMOOTH);
  glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
  glEnable (GL_BLEND);
  glBlendFunc (GL_SRC_ALPHA_SATURATE, GL_ONE);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  // set the widget background colour
  glClearColor(0.3, 0.3, 0.3, 0.0);


  // LOAD TEXTURES
  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

  glGenTextures(1, &textureID);
  glBindTexture(GL_TEXTURE_2D, textureID);

  int width, height;
  QString fileName = "assets/face.jpeg";
  QImage tmpImage = QImage(fileName, "JPG");
  QImage image = QGLWidget::convertToGLFormat(tmpImage);

  width = image.width();
  height = image.height();
  
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA,
               GL_UNSIGNED_BYTE, image.bits());

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

 }

// called every time the widget is resized
void GLPolygonWidget::resizeGL(int w, int h)
 {
  // set the viewport to the entire widget
  glViewport(0, 0, w, h);
 }
 
// called every time the widget needs painting
void GLPolygonWidget::paintGL()
 {
  glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
  glBindTexture(GL_TEXTURE_2D, textureID);

  thePolygon->Render();
 }
