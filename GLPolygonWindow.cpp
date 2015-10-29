#include "GLPolygonWindow.h"

#include <iostream>
using namespace std;

GLPolygonWindow::GLPolygonWindow(QWidget *parent, GLPolygon *newPolygon): QWidget(parent)
 {
  // store pointer to the polygon
  thePolygon = newPolygon;
 
  // inline custom style
  QString style1 = "QGroupBox{border:1px solid gray;border-radius:5px;margin-top: 1ex;}QGroupBox::title{subcontrol-origin: margin;subcontrol-position:top left;padding:0 3px;}";

  // create menu bar
  menuBar = new QMenuBar(this);
  menuBar->setGeometry(QRect(0, 0, 600, 25));
  // create file menu
  fileMenu = menuBar->addMenu( "&File");
  // create the action
  actionQuit = new QAction("&Quit", this);
  // add the item to the menu
  fileMenu->addAction(actionQuit);


  // create a label (graphic widget)
  polygonWidget = new GLPolygonWidget(NULL, newPolygon);
  polygonWidget->setMinimumSize(550,550);

  // create a dial for rotation
  rotationDialX = new QDial;
  rotationDialX->setValue(0);
  rotationDialX->setRange(0,360);

  rotationDialY = new QDial;
  rotationDialY->setValue(0);
  rotationDialY->setRange(0,360);

  angleLabelY = new QLabel("Rot. Y: 0 °");
  angleLabelX = new QLabel("Rot. X: 0 °");

  // create checkbox
  lightingCheck = new QCheckBox;
  lightingCheck->setChecked(true);
  smoothingCheck = new QCheckBox;
  smoothingCheck->setEnabled(false); // currently disabled, no use yet
  textureCheck = new QCheckBox;
  textureCheck->setChecked(true);

  // Arrange components for graphics control
  QFormLayout *formLayout = new QFormLayout;
  formLayout->addRow(tr("&Enable Lighting:"), lightingCheck);
  formLayout->addRow(tr("&Enable Smooth shading:"), smoothingCheck);
  formLayout->addRow(tr("&Enable Texture:"), textureCheck);

  // Add to groupbox
  formGroupBox = new QGroupBox(tr("Application controls:"));
  formGroupBox->setStyleSheet(style1);
  formGroupBox->setLayout(formLayout);

  // QGroupBox *rotationGroupBoxX = new QGroupBox();
  controlLayoutX = new QVBoxLayout;
  controlLayoutX->addWidget(angleLabelX);
  controlLayoutX->addWidget(rotationDialX);

  // QGroupBox *rotationGroupBoxY = new QGroupBox();
  controlLayoutY = new QVBoxLayout;
  controlLayoutY->addWidget(angleLabelY);
  controlLayoutY->addWidget(rotationDialY);

  // Arrange components for lower part
  lowerLayout = new QHBoxLayout;
  lowerLayout->addWidget(formGroupBox);
  lowerLayout->addStretch();
  lowerLayout->addLayout(controlLayoutY);
  lowerLayout->addStretch();
  lowerLayout->addLayout(controlLayoutX);
  lowerLayout->addStretch();

  // Arrange components
  windowLayout = new QVBoxLayout;
  windowLayout->addStretch();
  windowLayout->addWidget(polygonWidget);
  windowLayout->addStretch();
  windowLayout->addLayout(lowerLayout);

  setLayout(windowLayout);

 }

GLPolygonWindow::~GLPolygonWindow()
 { // destructor
  delete polygonWidget;
  delete formGroupBox;

  delete controlLayoutX;
  delete controlLayoutY;
  delete lowerLayout;
  delete windowLayout;  
 } // destructor

void GLPolygonWindow::ResetInterface()
 {

 }
