#include "GLPolygonController.h"
#include <QCoreApplication>
#include <QString>
#include <iostream>
using namespace std;

GLPolygonController::GLPolygonController (GLPolygonWindow *newWindow, GLPolygon *newPolygon)
 { // constructor
  // store the pointers for later
  theWindow = newWindow;
  thePolygon = newPolygon;

  // connect the quit item
  connect(theWindow->actionQuit, SIGNAL(triggered()),
  QCoreApplication::instance(), SLOT(quit()) );

  // connect the dial
  connect(theWindow->rotationDialX, SIGNAL(valueChanged(int)),
          this, SLOT(dialChangedX(int)) );

  connect(theWindow->rotationDialY, SIGNAL(valueChanged(int)),
          this, SLOT(dialChangedY(int)) );

  // connect Checkboxes
  connect(theWindow->lightingCheck, SIGNAL(clicked(bool)), this, SLOT(lightingCheckChanged(bool)));
  connect(theWindow->smoothingCheck, SIGNAL(clicked(bool)), this, SLOT(smoothingCheckChanged(bool)));
  connect(theWindow->textureCheck, SIGNAL(clicked(bool)), this, SLOT(textureCheckChanged(bool)));

  // create the timer
  animationTimer = new QTimer(this);
  // create the timer’s signal to the desired slot
  connect(animationTimer, SIGNAL(timeout()), this, SLOT(nextFrame()));
  // set the timer to fire 60 times a second
  animationTimer->start( 16.67);


 } // constructor

void GLPolygonController::nextFrame()
 { // nextFrame()
  // force a refresh in the window
  thePolygon->Render();
  theWindow->ResetInterface();
  theWindow->polygonWidget->repaint();
 } // nextFrame()

// slots
void GLPolygonController::dialChangedX(int newValue)
 {
  QString angle = QString::number(newValue);
  theWindow->angleLabelX->setText("Rot. X: " + angle + " °");
  thePolygon->RotateByX(newValue);
  nextFrame();
 }

void GLPolygonController::dialChangedY(int newValue)
 {
  QString angle = QString::number(newValue);
  theWindow->angleLabelY->setText("Rot. Y: " + angle + " °");
  thePolygon->RotateByY(newValue);
  nextFrame();
 }

void GLPolygonController::lightingCheckChanged(bool value)
 {
  thePolygon->setLighting(value);
 }

void GLPolygonController::smoothingCheckChanged(bool value)
 {
  thePolygon->setSmoothing(value);
 }

void GLPolygonController::textureCheckChanged(bool value)
 {
  thePolygon->setTexture(value);
 }
