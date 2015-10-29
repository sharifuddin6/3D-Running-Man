#include "GLPolygon.h"
#include "Player.h"
#include "cmath"
#include "iostream"
using namespace std;

GLPolygon::GLPolygon()
 {
  // initialise variables in constructor
  player = new Player();

  frameNo = 0;
  thetaX = 0;
  thetaY = 0;
  textureEnabled = true;

 }
 
void GLPolygon::Render()
 {
  // frame iterator
  idle();

  // clears widget and resets colour and depth
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
 
  // set the rotation
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glRotatef(thetaX, 1.0, 0.0, 0.0);
  glRotatef(thetaY, 0.0, 1.0, 0.0);

  // draw scene
  drawAxis();
  drawGrid();

  computePosition(frameNo);
  player->Render(frameNo);

  // flush to screen
  glFlush();
 }

// draw objects
void GLPolygon::drawCylinder(float x, float y, float z, float radius, float height)
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

void GLPolygon::drawCone(float x, float y, float z, float radius, float height)
 {
  int nSegments = 10;
  double norm[3];

  for (float i = 0.0; i < nSegments; i += 1.0)
   {
    float angle = M_PI * i * 2.0 / nSegments ;
    float nextAngle = M_PI * (i + 1.0) * 2.0 / nSegments;

    /* compute sin & cosine */
    float x1 = radius * sin(angle), z1 = radius * cos(angle);
    float x2 = radius * sin(nextAngle), z2 = radius * cos(nextAngle);

    glBegin(GL_TRIANGLES);

    // draw triangle
    double pointa[3] = { x + 0, y + height, z + 0 };     // A
    double pointb[3] = { x + x1, y, z + z1 };  // B
    double pointc[3] = { x + x2, y, z + z2 };  // C
    get_face_normal(norm, pointa, pointb, pointc);

    //colourise(1);
    glNormal3dv(norm);
    glVertex3dv(pointa);
    glVertex3dv(pointb);
    glVertex3dv(pointc);

    //draw bottom face
    double bface_pointa[3] = { x + 0, y, z + 0 };    // center bottom
    double bface_pointb[3] = { x + x2, y, z + z2 };  // C
    double bface_pointc[3] = { x + x1, y, z + z1 };  // B
    get_face_normal(norm, pointa, pointb, pointc);

    //colourise(2);
    glNormal3dv(norm);
    glVertex3dv(bface_pointa);
    glVertex3dv(bface_pointb);
    glVertex3dv(bface_pointc);

    glEnd();
   }

 }

void GLPolygon::drawAxis()
 {
  float x=0.0,y=0.0,z=0.0;
  float angle=90.0;
    
  // draw axis y
  glColor3f(0.9,0.0,0.0);
  drawCylinder(x,y,z, 0.005, 0.9);
  drawCone(x,y+0.9,z, 0.01, 0.05);

  // draw axis x
  glPushMatrix();
  glRotatef(angle, 0, 0, -1);
  glColor3f(0.0,0.9,0.0);
  drawCylinder(x,y,z, 0.005, 0.9);
  drawCone(x,y+0.9,z, 0.01, 0.05);
  glPopMatrix();
  
  // draw axis z
  glPushMatrix();
  glRotatef(angle, 1, 0, 0);
  glColor3f(0.0,0.0,0.9);
  drawCylinder(x,y,z, 0.005, 0.9);
  drawCone(x,y+0.9,z, 0.01, 0.05);
  glPopMatrix();
  
 } 

void GLPolygon::drawGrid()
 {
  float size = 0.8;

  glColor3f(.3,.3,.3);
  glBegin(GL_QUADS);
  glVertex3f( -size,-0.001, -size);
  glVertex3f( -size,-0.001,size);
  glVertex3f(size,-0.001,size);
  glVertex3f(size,-0.001,-size);
  glEnd();

  glBegin(GL_LINES);
  for(float i=-size;i<=size+0.1;i+=0.1) {
    if (i==0) { glColor3f(.6,.3,.3); } else { glColor3f(.25,.25,.25); };
    glVertex3f(i,0,-size);
    glVertex3f(i,0,size);
    if (i==0) { glColor3f(.3,.3,.6); } else { glColor3f(.25,.25,.25); };
    glVertex3f(-size,0,i);
    glVertex3f(size,0,i);
  };
  glEnd();

 }

void GLPolygon::computePosition(int frame)
 {
 // computePosition()
 float radius = 0.65;
 float theta = (frame * 2 * M_PI)/ 600;
 float posn_x = cos(theta)*radius;
 float posn_z = sin(theta)*radius;
 glTranslatef(posn_x, 0.0, posn_z);

 // rotation
 float angle = ((float)frame/600)*360;
 glRotatef(-angle, 0.0,1.0,0.0);

 }


// other functions
void GLPolygon::RotateByX(float angleX)
 {
  thetaX = angleX;
 }

void GLPolygon::RotateByY(float angleY)
 {
  thetaY = angleY;
 }

// setters
void GLPolygon::setLighting(bool value)
 {
  if(value)
    glEnable(GL_LIGHTING);
  else
    glDisable(GL_LIGHTING);
 }

void GLPolygon::setSmoothing(bool value)
 {
  if(value)
    glShadeModel(GL_SMOOTH);
  else
    glShadeModel(GL_FLAT);
 }

void GLPolygon::setTexture(bool value)
 {
  player->setTextureEnabled(value);
 }

// find cross product of two vectors
void GLPolygon::cross_product(double *cross,double a[3], double b[3])
{
  cross[0]=a[1]*b[2] - b[1]*a[2];
  cross[1]=a[2]*b[0] - b[2]*a[0];
  cross[2]=a[0]*b[1] - b[0]*a[1];
}

// normalise vector
void GLPolygon::normalise(double *vect)
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
void GLPolygon::get_face_normal ( double *norm, double pointa[3], double pointb[3], double pointc[3] )
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

// frame iterator
void GLPolygon::idle()
 {
  frameNo++; if(frameNo > 600) frameNo = 0;
 }
