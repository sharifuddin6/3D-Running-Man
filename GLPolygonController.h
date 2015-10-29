#ifndef __GL_POLYGON_CONTROLLER__H
#define __GL_POLYGON_CONTROLLER__H 1

#include "GLPolygon.h"
#include "GLPolygonWindow.h"
#include <qobject.h>
#include <QTimer>

class GLPolygonController : public QObject
 { // class GLPolygonController
  Q_OBJECT

  private:
    GLPolygon *thePolygon;
    GLPolygonWindow *theWindow;

  public:
    // constructor
    GLPolygonController(GLPolygonWindow *newWindow, GLPolygon *newPolygon);

    // the timer
    QTimer *animationTimer;

  public slots:
    void nextFrame();
    // slots for dealing with dial(s)
    void dialChangedX(int newValue);
    void dialChangedY(int newValue);

    void lightingCheckChanged(bool value);
    void smoothingCheckChanged(bool value);
    void textureCheckChanged(bool value);

 }; // class GLPolygonController
#endif
