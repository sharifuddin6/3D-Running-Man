#ifndef __GL_POLYGON__H
#define __GL_POLYGON__H 1

#include <QtOpenGL/QGLWidget>
#include "Player.h"

class GLPolygon
 { // class GLPolygon
  public:
    // constructor
    GLPolygon();

    // routine to tell it to render itself
    void Render();

    void RotateByX(float angleX);
    void RotateByY(float angleY);

    // draw polygons
    void drawCylinder(float x, float y, float z, float radius, float height);
    void drawCone(float x, float y, float z, float radius, float height);
    void drawAxis();
    void drawGrid();
    
    // compute position for the running man
    void computePosition(int frame);

    // setters
    void setLighting(bool value);
    void setSmoothing(bool value);
    void setTexture(bool value);

    // methods to find normals
    void cross_product(double *cross,double a[3], double b[3]);
    void normalise(double *vect);
    void get_face_normal(double *norm, double pointa[3],
                         double pointb[3], double pointc[3]);
    
    // frame iterator
    void idle();

  private:
    Player *player;

    float thetaX;
    float thetaY;

    int frameNo;

    bool textureEnabled;

 }; // class GLPolygon

#endif
