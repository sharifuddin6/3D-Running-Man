#ifndef GLPOLYGONWINDOW_HPP
#define GLPOLYGONWINDOW_HPP

#include "GLPolygonWidget.h"
#include "GLPolygon.h"

#include <QtWidgets/QMenuBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QFormLayout>

#include <QtWidgets/QLabel>
#include <QtWidgets/QDial>
#include <QtWidgets/QCheckBox>

#include <QObject>

using namespace std;

class GLPolygonWindow: public QWidget
 {
  Q_OBJECT

  public:
    GLPolygon *thePolygon;
  
    // constructor/destructor
    GLPolygonWindow(QWidget* parent, GLPolygon *newPolygon);
    ~GLPolygonWindow();

    // menu bar
    QMenuBar *menuBar;
    QMenu *fileMenu;     // file menu
    QAction *actionQuit;     // quit action

    // layout
    QBoxLayout *windowLayout;
      QHBoxLayout *lowerLayout;
        QFormLayout *formLayout;
        QVBoxLayout *controlLayoutX;
        QVBoxLayout *controlLayoutY;

    // graphic widget
    GLPolygonWidget *polygonWidget;

    // groupbox widget
    QGroupBox *formGroupBox;

    // checkbox widget
    QCheckBox *lightingCheck;
    QCheckBox *smoothingCheck;
    QCheckBox *textureCheck;

    QLabel *angleLabelX;
    QLabel *angleLabelY;


    // widget
    QDial *rotationDialX;
    QDial *rotationDialY;

    void ResetInterface();

 };

#endif
