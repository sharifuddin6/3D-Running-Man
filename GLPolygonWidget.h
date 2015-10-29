#ifndef __GL_POLYGON_WIDGET_H__
#define __GL_POLYGON_WIDGET_H__ 1


#include <QtOpenGL/QGLWidget>
#include "GLPolygon.h"
#include <iostream>
using namespace std;


class GLPolygonWidget: public QGLWidget
 { // class GLPolygonWidget
  public:
    GLPolygon *thePolygon;
    GLuint textureID;

    // constructor
    GLPolygonWidget(QWidget *parent, GLPolygon *newPolygon);

  protected:
    // called when OpenGL context is set up
    void initializeGL();
    // called every time the widget is resized
    void resizeGL(int w, int h);
    // called every time the widget needs painting
    void paintGL();

 }; // class GLPolygonWidget
 
#endif
