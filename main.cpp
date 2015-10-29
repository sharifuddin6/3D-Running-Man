#include "GLPolygonWindow.h"
#include "GLPolygon.h"
#include "GLPolygonController.h"

#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
 { // main()

  // create the application
  QApplication app(argc, argv);

  // create polygon, window, and controller
  GLPolygon *polygon = new GLPolygon();
  GLPolygonWindow *window = new GLPolygonWindow(NULL, polygon);
  GLPolygonController *controller = new GLPolygonController(window, polygon);

  // window settings
  window->resize(600, 750);
  window->setWindowTitle("OpenGL: Running man");
  window->setFixedSize(600,750);
  window->show();

  // start it running
  app.exec();

  // clean up
  delete controller;
  delete window;
  delete polygon;

  return 0;

} // main()
