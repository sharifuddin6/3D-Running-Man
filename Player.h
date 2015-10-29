#ifndef __PLAYER__H
#define __PLAYER__H 1

#include "QtOpenGL/QGLWidget"

class Player 
 {
  public:
    // constructor
    Player();

    // Render method
    void Render(int frame);

    // setter
    void setTextureEnabled(bool value);

  private:
    // variables
    float speed, size;
    float delta, delta_l, delta_r;
    float body_height, armLength, legLength;

    bool textureEnabled;

    // joint positions
    float hip_x, hip_y, hip_z;

    // polygon definition
    void drawSphere(float x, float y, float z, float radius);
    void drawCylinder(float x, float y, float z, float radius, float height);
    
    // limbs heirarchy
    void upperBody();
      void hip();
      void chest();
      void head();

    void upperArm_L();
      void lowerArm_L();
    void upperArm_R();
      void lowerArm_R();

    void upperLeg_L();
      void lowerLeg_L();
        void foot_L();
    void upperLeg_R();
      void lowerLeg_R();
        void foot_R();

    // methods to find normals
    void cross_product(double *cross,double a[3], double b[3]);
    void normalise(double *vect);
    void get_face_normal(double *norm, double pointa[3],
                         double pointb[3], double pointc[3]);
    
      
 };

#endif
