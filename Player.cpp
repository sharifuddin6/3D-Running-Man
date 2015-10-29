#include "Player.h"
#include "cmath"
#include "iostream"
using namespace std;

Player::Player()
 {
  speed = 6.0;  // adjustable running speed
  size = 1.0;   // scalable height

  textureEnabled = true;

  // adjustable sizes
  body_height = size*0.1;
  armLength = size*0.1;
  legLength = size*0.14;

  hip_x=0.0;
  hip_y=0.0;
  hip_z=0.0;

 }

void Player::Render(int frame)
 {
  delta = speed*(frame * 2 * M_PI)/ 600;
  delta_l = sin(delta)/2 + 1;
  delta_r = cos(delta)/2 + 1;

  hip();

 }

void Player::drawCylinder(float x, float y, float z, float radius, float height)
 {

  int nSegments = 10;
  //computed normals
  double norm[3];

  for (float i = 0.0; i < nSegments; i += 1.0)
   {
    float angle = M_PI * i * 2.0 / nSegments ;
    float nextAngle = M_PI * (i + 1.0) * 2.0 / nSegments;

    /* compute sin & cosine */
    float x1 = radius * sin(angle), z1 = radius * cos(angle);
    float x2 = radius * sin(nextAngle), z2 = radius * cos(nextAngle);

    glBegin(GL_TRIANGLES);

    // draw top triangle
    double top_pointa[3] = { x + x1, y + height, z + z1 };   // A
    double top_pointb[3] = { x + x1, y, z + z1 };  // B
    double top_pointc[3] = { x + x2, y, z + z2 };  // C
    get_face_normal(norm, top_pointa, top_pointb, top_pointc);

    //colourise(1);
    glNormal3dv(norm);
    glVertex3dv(top_pointa);
    glVertex3dv(top_pointb);
    glVertex3dv(top_pointc);

    // draw bottom triangle
    double bot_pointa[3] = { x + x1, y + height, z + z1 };   // A
    double bot_pointb[3] = { x + x2, y, z + z2 };  // C
    double bot_pointc[3] = { x + x2, y + height, z + z2 };   // D
    get_face_normal(norm, bot_pointa, bot_pointb, bot_pointc);

    //colourise(1);
    glNormal3dv(norm);
    glVertex3dv(bot_pointa);
    glVertex3dv(bot_pointb);
    glVertex3dv(bot_pointc);

    //draw bottom face
    double bface_pointa[3] = { x + 0, y, z + 0 };    // center bottom
    double bface_pointb[3] = { x + x2, y, z + z2 };  // C
    double bface_pointc[3] = { x + x1, y, z + z1 };  // B
    get_face_normal(norm, bface_pointa, bface_pointb, bface_pointc);

    //colourise(2);
    glNormal3dv(norm);
    glVertex3dv(bface_pointa);
    glVertex3dv(bface_pointb);
    glVertex3dv(bface_pointc);

    //draw top face
    double tface_pointa[3] = { x + x1, y + height, z + z1 };   // A
    double tface_pointb[3] = { x + x2, y + height, z + z2 };   // D
    double tface_pointc[3] = { x + 0, y + height, z + 0 };     // center top
    get_face_normal(norm, tface_pointa, tface_pointb, tface_pointc);

    //colourise(3);
    glNormal3dv(norm);
    glVertex3dv(tface_pointa);
    glVertex3dv(tface_pointb);
    glVertex3dv(tface_pointc);
    glEnd();
   }

 }

void Player::drawSphere(float x, float y, float z, float radius)
{
 int nRings = 10;
 int nFacesPerRing = 10;
 float PI = -M_PI;

 //computed normals
 double norm[3];

 // draw rings
 for (int i=0; i<nRings; i++) {

   float phi = (-PI/2) + ((i* PI )/ nRings);
   float nextPhi = (-PI/2) + (((i+1)* PI )/ nRings);

   phi = -phi;
   nextPhi = -nextPhi;

   float cosPhi = cos(phi), sinPhi = sin(phi);
   float cosNextPhi = cos(nextPhi), sinNextPhi = sin(nextPhi);

   float texY0 = float(i)/float(nRings);
   float texY1 = float(i+1)/float(nRings);

   // draw faces for each ring
   for (int j=0; j<nFacesPerRing; j++) {

     float theta = j * ((2*PI)/nFacesPerRing);
     float nextTheta = (j+1) * ((2*PI)/nFacesPerRing);
     float cosTheta = cos(theta), sinTheta = sin(theta);
     float cosNextTheta = cos(nextTheta), sinNextTheta = sin(nextTheta);

     float texX0 = float(j)/float(nFacesPerRing);
     float texX1 = float(j+1)/float(nFacesPerRing);

     glBegin(GL_TRIANGLES);

       // draw bottom triangle
       double bot_pointa[3] = { x + radius * cosNextPhi * cosTheta, y + radius * sinNextPhi, z + radius * cosNextPhi * sinTheta };  // A
       double bot_pointb[3] = { x + radius * cosPhi * cosTheta, y + radius * sinPhi, z + radius * cosPhi * sinTheta };              // B
       double bot_pointc[3] = { x + radius * cosPhi * cosNextTheta, y + radius * sinPhi, z + radius * cosPhi * sinNextTheta };      // C
       get_face_normal(norm, bot_pointa, bot_pointb, bot_pointc);

       //colourise(1);
       glTexCoord2f(texX0,texY1);
       glNormal3dv(norm);
       glVertex3dv(bot_pointa);
       glTexCoord2f(texX0,texY0);
       glVertex3dv(bot_pointb);
       glTexCoord2f(texX1,texY0);
       glVertex3dv(bot_pointc);

       // draw top triangle
       double top_pointa[3] = { x + radius * cosNextPhi * cosTheta, y + radius * sinNextPhi, z + radius * cosNextPhi * sinTheta };         // A
       double top_pointb[3] = { x + radius * cosPhi * cosNextTheta, y + radius * sinPhi, z + radius * cosPhi * sinNextTheta };             // C
       double top_pointc[3] = { x + radius * cosNextPhi * cosNextTheta, y + radius * sinNextPhi, z + radius * cosNextPhi * sinNextTheta }; // D
       get_face_normal(norm, top_pointa, top_pointb, top_pointc);

       //colourise(1);
       glTexCoord2f(texX0,texY1);
       glNormal3dv(norm);
       glVertex3dv(top_pointa);
       glTexCoord2f(texX1,texY0);
       glVertex3dv(top_pointb);
       glTexCoord2f(texX1,texY1);
       glVertex3dv(top_pointc);

     glEnd();

   }
 }

}

// BODY GROUPS AND LIMBS
void Player::hip()
 {
    glColor3f(0.9,0.25,0.10);
    glPushMatrix();
    glTranslatef(hip_x,hip_y+legLength,hip_z);
    drawCylinder(0,0,0, 0.0325, body_height/2); // hip

      chest();

      upperLeg_L();

      upperLeg_R();

    glPopMatrix();

 }

void Player::chest()
 {
    glPushMatrix();
    glTranslatef(0, body_height/2, 0);
    drawCylinder(0,0,0, 0.04, body_height/2); // chest

      head();

      upperArm_L();

      upperArm_R();

    glPopMatrix();

 }

void Player::head()
 {
    if(textureEnabled) {
      glEnable(GL_TEXTURE_2D);
    }

    glColor3f(0.9,0.9,0.1);
    glPushMatrix();
    glTranslatef(0,body_height/2+0.05,0);
    glRotatef(90,0,1,0);
    drawSphere(0,0,0, 0.05);
    glPopMatrix();

    glDisable(GL_TEXTURE_2D);
 }

void Player::upperArm_L()
 {
    glColor3f(0.0,0.5,0.9);
    glPushMatrix();
    glTranslatef(0.05,body_height/2,0);
    drawSphere(0,0,0,0.015);
    glRotatef(180, 1,0,0);
    glRotatef(-70*sin(delta), 1, 0, 0);
    drawCylinder(0,0,0, 0.01, armLength/2);

      lowerArm_L();

    glPopMatrix();
 }

void Player::lowerArm_L()
 {
    glPushMatrix();
    glTranslatef(0,armLength/2,0);
    drawSphere(0,0,0,0.015);
    glRotatef(-35*delta_l, 1, 0, 0);
    drawCylinder(0,0,0, 0.01, armLength/2);
    glPopMatrix();
 }

void Player::upperArm_R()
 {
    glColor3f(0.0,0.5,0.9);
    glPushMatrix();
    glTranslatef(-0.05,body_height/2,0);
    drawSphere(0,0,0,0.015);
    glRotatef(180, 1,0,0);
    glRotatef(70*sin(delta), 1, 0, 0);
    drawCylinder(0,0,0, 0.01, armLength/2);

      lowerArm_R();

    glPopMatrix();
 }

void Player::lowerArm_R()
 {
    glPushMatrix();
    glTranslatef(0,armLength/2,0);
    drawSphere(0,0,0,0.015);
    glRotatef(-35*delta_r, 1, 0, 0);
    drawCylinder(0,0,0, 0.01, armLength/2);
    glPopMatrix();
 }

void Player::upperLeg_L()
 {
    glColor3f(0.0,0.5,0.9);
    glPushMatrix();
    glTranslatef(0.03,0,0);
    drawSphere(0,0,0,0.02);
    glRotatef(180, 1,0,0);
    glRotatef(50*sin(delta), 1, 0, 0);
    drawCylinder(0,0,0, 0.01, legLength/2);

      lowerLeg_L();

        foot_L();

      glPopMatrix();
    glPopMatrix();
 }

void Player::lowerLeg_L()
 {
    glPushMatrix();
    glTranslatef(0,legLength/2,0);
    drawSphere(0,0,0,0.015);
    glRotatef(35*delta_l, 1, 0, 0);
    drawCylinder(0,0,0, 0.01, legLength/2);
 }

void Player::foot_L()
 {
    glColor3f(1.0,0.5,0.2);
    glPushMatrix();
    glTranslatef(0,legLength/2,0);
    drawSphere(0,0,0,0.015);
    glRotatef(-90, 1, 0, 0);
    drawCylinder(0,0,0, 0.01, legLength/4);
    glPopMatrix();
 }

void Player::upperLeg_R()
 {
    glColor3f(0.0,0.5,0.9);
    glPushMatrix();
    glTranslatef(-0.03,0,0);
    drawSphere(0,0,0,0.02);
    glRotatef(180, 1,0,0);
    glRotatef(-50*sin(delta), 1, 0, 0);
    drawCylinder(0,0,0, 0.01, legLength/2);

      lowerLeg_R();

        foot_R();

      glPopMatrix();
    glPopMatrix();
 }

void Player::lowerLeg_R()
 {
    glPushMatrix();
    glTranslatef(0,legLength/2,0);
    drawSphere(0,0,0,0.015);
    glRotatef(35*delta_r, 1, 0, 0);
    drawCylinder(0,0,0, 0.01, legLength/2);
 }

void Player::foot_R()
 {
    glColor3f(1.0,0.5,0.2);
    glPushMatrix();
    glTranslatef(0,legLength/2,0);
    drawSphere(0,0,0,0.015);
    glRotatef(-90, 1, 0, 0);
    drawCylinder(0,0,0, 0.01, legLength/4);
    glPopMatrix();
 }

// setter
void Player::setTextureEnabled(bool value)
 {
  textureEnabled = value;
 }

// find cross product of two vectors
void Player::cross_product(double *cross,double a[3], double b[3])
{
  cross[0]=a[1]*b[2] - b[1]*a[2];
  cross[1]=a[2]*b[0] - b[2]*a[0];
  cross[2]=a[0]*b[1] - b[0]*a[1];
}

// normalise vector
void Player::normalise(double *vect)
{
  double length = sqrt(        //A^2 + B^2 + C^2 = length^2
    pow(vect[0],2)+
    pow(vect[1],2)+
    pow(vect[2],2)
  );

  // normalise
  for (int a=0;a<3;++a) {
    vect[a]/=length;
  }

}

// calculate normals
void Player::get_face_normal ( double *norm, double pointa[3], double pointb[3], double pointc[3] )
{
  double vect[2][3];
  double point[3][3];

  // copies points into point[][]
  for (int a = 0; a < 3; ++a ) {
    point[0][a]=pointa[a];
    point[1][a]=pointb[a];
    point[2][a]=pointc[a];
  }

  // calculates vectors from point[0] to point[1]
  for (int a = 0; a < 2; ++a ) {
    // and point[0] to point[2]
    for (int b = 0; b < 3; ++b ) {
      vect[a][b] = point[2-a][b] - point[0][b];
    }
  }

  // calculates vector at 90° to 2 vectors
  cross_product ( norm, vect[0], vect[1] );

  // makes the vector length 1
  normalise ( norm );

}
