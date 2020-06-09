

#include "CgQtGLRenderWidget.h"
#include "CgQtGui.h"
#include "CgQtMainApplication.h"
#include "../CgBase/CgEnums.h"
#include "../CgEvents/CgMouseEvent.h"
#include "../CgEvents/CgKeyEvent.h"
#include "../CgEvents/CgWindowResizeEvent.h"
#include "../CgEvents/CgLoadObjFileEvent.h"
#include "../CgEvents/CgTrackballEvent.h"
#include "../CgEvents/CgColorChangeEvent.h"
#include "../CgEvents/CgButtonPressedEvent.h"
#include "../CgEvents/CgCheckboxChangedEvent.h"
#include "../CgEvents/CgSelectionChangedEvent.h"
#include "../CgEvents/CgSORChangedEvent.h"
#include <QSlider>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QKeyEvent>
#include <QPushButton>
#include <QDesktopWidget>
#include <QApplication>
#include <QMessageBox>
#include <QLabel>
#include <QSpinBox>
#include <QCheckBox>
#include <QPushButton>
#include <QGroupBox>
#include <QButtonGroup>
#include <QRadioButton>
#include <QMenuBar>
#include <QActionGroup>
#include <QFileDialog>
#include <iostream>

CgQtGui::CgQtGui(CgQtMainApplication *mw)
    : m_mainWindow(mw)
{
    m_glRenderWidget = new CgQtGLRenderWidget;

    connect(m_glRenderWidget, SIGNAL(mouseEvent(QMouseEvent *)), this, SLOT(mouseEvent(QMouseEvent *)));
    connect(m_glRenderWidget, SIGNAL(viewportChanged(int, int)), this, SLOT(viewportChanged(int, int)));
    connect(m_glRenderWidget, SIGNAL(trackballChanged()), this, SLOT(slotTrackballChanged()));

    QVBoxLayout *mainLayout = new QVBoxLayout;
    QHBoxLayout *container = new QHBoxLayout;

    QWidget *opt = new QWidget;
    createOptionPanelExample1(opt);

    QWidget *otheropt = new QWidget;
    createOptionPanelExample2(otheropt);

    QTabWidget *m_tabs = new QTabWidget();
    m_tabs->addTab(opt, "&My Tab1");
    m_tabs->addTab(otheropt, "&My Tab2");
    container->addWidget(m_tabs);

    m_tabs->setMaximumWidth(400);

    container->addWidget(m_glRenderWidget);

    QWidget *w = new QWidget;
    w->setLayout(container);
    mainLayout->addWidget(w);

    setLayout(mainLayout);
    setWindowTitle(tr("Übung Computergrafik 1 -  SoSe 2020"));

    /* create Menu Bar */
    m_menuBar = new QMenuBar;
    QMenu *file_menu = new QMenu("&File");
    file_menu->addAction("&Open Mesh Model", this, SLOT(slotLoadMeshFile()));
    // todo: Add Quit-Action
    m_menuBar->addMenu(file_menu);
    QMenu *settings_menu = new QMenu("&Setting");
    QMenu *polygon_mode_menu = new QMenu("&Polygon Mode");

    QAction *m_custom_rot = settings_menu->addAction("&Custom Rotations", m_glRenderWidget, SLOT(slotCustomRotation()));
    m_custom_rot->setCheckable(true);
    m_custom_rot->setChecked(false);

    QAction *m_lighting = settings_menu->addAction("&Lighting on", m_glRenderWidget, SLOT(slotLighting()));
    m_lighting->setCheckable(true);
    m_lighting->setChecked(false);

    QActionGroup *polygonmode_group = new QActionGroup(this);
    polygonmode_group->setExclusive(true);

    QAction *points = polygon_mode_menu->addAction("&Points", m_glRenderWidget, SLOT(slotPolygonPoints()));
    points->setCheckable(true);
    points->setChecked(false);

    QAction *wireframe = polygon_mode_menu->addAction("&Wireframe", m_glRenderWidget, SLOT(slotPolygonWireframe()));
    wireframe->setCheckable(true);
    wireframe->setChecked(true);

    QAction *filled = polygon_mode_menu->addAction("&Filled", m_glRenderWidget, SLOT(slotPolygonFilled()));
    filled->setCheckable(true);
    filled->setChecked(false);

    polygonmode_group->addAction(points);
    polygonmode_group->addAction(wireframe);
    polygonmode_group->addAction(filled);

    // todo: Add Quit-Action
    m_menuBar->addMenu(file_menu);
    m_menuBar->addMenu(settings_menu);
    m_menuBar->addMenu(polygon_mode_menu);

    m_mainWindow->setMenuBar(m_menuBar);
}

QSlider *CgQtGui::createSlider()
{
    QSlider *slider = new QSlider(Qt::Vertical);
    slider->setRange(0, 360 * 16);
    slider->setSingleStep(16);
    slider->setPageStep(15 * 16);
    slider->setTickInterval(15 * 16);
    slider->setTickPosition(QSlider::TicksRight);
    return slider;
}

void CgQtGui::createOptionPanelExample1(QWidget *parent)
{
    QVBoxLayout *tab1_control = new QVBoxLayout();
    QHBoxLayout *subBox = new QHBoxLayout();

    /* Control which object type to draw */
    QGroupBox *myGroupBox = new QGroupBox("Choose the object to draw");
    // select object type
    myButtonGroup = new QButtonGroup(subBox);
    myButtonGroup->setExclusive(true);

    QRadioButton *radiobutton1 = new QRadioButton("Cube");
    QRadioButton *radiobutton2 = new QRadioButton("Solid of revolution");
    QRadioButton *radiobutton3 = new QRadioButton("Loaded Object");

    radiobutton1->setChecked(true);

    myButtonGroup->addButton(radiobutton1, Cg::Cube);
    myButtonGroup->addButton(radiobutton2, Cg::SolidOfRevolution);
    myButtonGroup->addButton(radiobutton3, Cg::LoadedObj);
    connect(myButtonGroup, SIGNAL(buttonClicked(int)), this, SLOT(slotObjectSelectionChanged(int)));

    QVBoxLayout *vbox = new QVBoxLayout;
    vbox->addWidget(radiobutton1);
    vbox->addWidget(radiobutton2);
    vbox->addWidget(radiobutton3);
    vbox->addStretch(1);
    myGroupBox->setLayout(vbox);
    subBox->addWidget(myGroupBox);
    tab1_control->addLayout(subBox);

    /*Example for using a label */
    QLabel *sor_options_label = new QLabel("Solid of revolution options");
    tab1_control->addWidget(sor_options_label);
    sor_options_label->setAlignment(Qt::AlignCenter);

    auto LateralStepsInput = new QSpinBox();
    tab1_control->addWidget(LateralStepsInput);
    LateralStepsInput->setMinimum(10);
    LateralStepsInput->setValue(20);
    LateralStepsInput->setMaximum(100000);
    LateralStepsInput->setPrefix("Lateral steps:  ");
    connect(LateralStepsInput, SIGNAL(valueChanged(int)), this, SLOT(slotLateralStepsChanged(int)));
    tab1_control->addWidget(LateralStepsInput);

    auto IterationsInput = new QSpinBox();
    tab1_control->addWidget(IterationsInput);
    IterationsInput->setMinimum(0);
    IterationsInput->setValue(0);
    IterationsInput->setPrefix("Iterations:  ");
    connect(IterationsInput, SIGNAL(valueChanged(int)), this, SLOT(slotIterationsChanged(int)));
    tab1_control->addWidget(IterationsInput);

    auto NInput = new QSpinBox();
    tab1_control->addWidget(NInput);
    NInput->setMinimum(1);
    NInput->setValue(2);
    NInput->setPrefix("N:  ");
    connect(NInput, SIGNAL(valueChanged(int)), this, SLOT(slotNChanged(int)));
    tab1_control->addWidget(NInput);

    QLabel *options_label = new QLabel("General Options");
    tab1_control->addWidget(options_label);
    options_label->setAlignment(Qt::AlignCenter);

    /* option for drawing face normals */
    auto face_normals = new QCheckBox("Show face normals");
    face_normals->setCheckable(true);
    face_normals->setChecked(false);
    connect(face_normals, SIGNAL(stateChanged(int)), this, SLOT(slotShowFaceNormalsChanged(int)));
    tab1_control->addWidget(face_normals);

    /* option for drawing face normals */
    auto vertex_normals = new QCheckBox("Show vertex normals");
    vertex_normals->setCheckable(true);
    vertex_normals->setChecked(false);
    connect(vertex_normals, SIGNAL(stateChanged(int)), this, SLOT(slotShowVertexNormalsChanged(int)));
    tab1_control->addWidget(vertex_normals);
    /* control RGB color scheme */

    auto RGBRedInput = new QSpinBox();
    tab1_control->addWidget(RGBRedInput);
    RGBRedInput->setMinimum(0);
    RGBRedInput->setMaximum(255);
    RGBRedInput->setValue(0);
    RGBRedInput->setPrefix("Red:  ");
    connect(RGBRedInput, SIGNAL(valueChanged(int)), this, SLOT(slotRGBRedInputChanged(int)));
    tab1_control->addWidget(RGBRedInput);

    auto RGBGreenInput = new QSpinBox();
    tab1_control->addWidget(RGBGreenInput);
    RGBGreenInput->setMinimum(0);
    RGBGreenInput->setMaximum(255);
    RGBGreenInput->setValue(255);
    RGBGreenInput->setPrefix("Green:  ");
    connect(RGBGreenInput, SIGNAL(valueChanged(int)), this, SLOT(slotRGBGreenInputChanged(int)));
    tab1_control->addWidget(RGBGreenInput);

    auto RGBBlueInput = new QSpinBox();
    tab1_control->addWidget(RGBBlueInput);
    RGBBlueInput->setMinimum(0);
    RGBBlueInput->setMaximum(255);
    RGBBlueInput->setValue(0);
    RGBBlueInput->setPrefix("Blue:  ");
    connect(RGBBlueInput, SIGNAL(valueChanged(int)), this, SLOT(slotRGBBlueInputChanged(int)));
    tab1_control->addWidget(RGBBlueInput);

    QPushButton *drawButton = new QPushButton("Draw!");
    tab1_control->addWidget(drawButton);

    connect(drawButton, SIGNAL(clicked()), this, SLOT(slotDrawButtonPressed()));
    /*Example for using a checkbox */

    // myCheckBox1 = new QCheckBox("enable Option 1");
    // myCheckBox1->setCheckable(true);
    // myCheckBox1->setChecked(false);
    // connect(myCheckBox1, SIGNAL(clicked()), this, SLOT(slotMyCheckBox1Changed()));
    // tab1_control->addWidget(myCheckBox1);

    /*Example for using a button */

    // QPushButton *myButton1 = new QPushButton("&drueck mich");
    // tab1_control->addWidget(myButton1);

    // connect(myButton1, SIGNAL(clicked()), this, SLOT(slotMyButton1Pressed()));

    parent->setLayout(tab1_control);
}

void CgQtGui::createOptionPanelExample2(QWidget *parent)
{

    QVBoxLayout *tab2_control = new QVBoxLayout();
    QHBoxLayout *subBox = new QHBoxLayout();

    /*Example for using a button group */

    QGroupBox *myGroupBox = new QGroupBox("Radiobutton Group Example ");

    myButtonGroup = new QButtonGroup(subBox);
    myButtonGroup->setExclusive(true);

    QRadioButton *radiobutton1 = new QRadioButton("&Option1");
    QRadioButton *radiobutton2 = new QRadioButton("&Option2");
    QRadioButton *radiobutton3 = new QRadioButton("&Option3");
    QRadioButton *radiobutton4 = new QRadioButton("&Option4");
    QRadioButton *radiobutton5 = new QRadioButton("&Option5");

    radiobutton2->setChecked(true);

    myButtonGroup->addButton(radiobutton1, 0);
    myButtonGroup->addButton(radiobutton2, 1);
    myButtonGroup->addButton(radiobutton3, 2);
    myButtonGroup->addButton(radiobutton4, 3);
    myButtonGroup->addButton(radiobutton5, 4);

    QVBoxLayout *vbox = new QVBoxLayout;
    vbox->addWidget(radiobutton1);
    vbox->addWidget(radiobutton2);
    vbox->addWidget(radiobutton3);
    vbox->addWidget(radiobutton4);
    vbox->addWidget(radiobutton5);
    vbox->addStretch(1);
    myGroupBox->setLayout(vbox);
    subBox->addWidget(myGroupBox);
    tab2_control->addLayout(subBox);

    connect(myButtonGroup, SIGNAL(buttonClicked(int)), this, SLOT(slotButtonGroupSelectionChanged()));
    parent->setLayout(tab2_control);
}

void CgQtGui::slotButtonGroupSelectionChanged()
{
}

void CgQtGui::slotRGBRedInputChanged(int value)
{
    CgBaseEvent *e = new CgColorChangeEvent(Cg::CgColorChangeEvent, Cg::Red, value);
    notifyObserver(e);
}

void CgQtGui::slotRGBGreenInputChanged(int value)
{
    CgBaseEvent *e = new CgColorChangeEvent(Cg::CgColorChangeEvent, Cg::Green, value);
    notifyObserver(e);
}
void CgQtGui::slotRGBBlueInputChanged(int value)
{
    CgBaseEvent *e = new CgColorChangeEvent(Cg::CgColorChangeEvent, Cg::Blue, value);
    notifyObserver(e);
}
void CgQtGui::slotLateralStepsChanged(int value)
{
    CgBaseEvent *e = new CgSORChangedEvent(Cg::CgSORChangedEvent, Cg::LateralSteps, value);
    notifyObserver(e);
}
void CgQtGui::slotIterationsChanged(int value)
{
    CgBaseEvent *e = new CgSORChangedEvent(Cg::CgSORChangedEvent, Cg::Iterations, value);
    notifyObserver(e);
}
void CgQtGui::slotNChanged(int value)
{
    CgBaseEvent *e = new CgSORChangedEvent(Cg::CgSORChangedEvent, Cg::N, value);
    notifyObserver(e);
}
void CgQtGui::slotShowFaceNormalsChanged(int state)
{
    CgBaseEvent *e = new CgCheckboxChangedEvent(Cg::CgCheckboxChangedEvent, Cg::FaceNormals, state);
    notifyObserver(e);
}

void CgQtGui::slotShowVertexNormalsChanged(int state)
{
    CgBaseEvent *e = new CgCheckboxChangedEvent(Cg::CgCheckboxChangedEvent, Cg::VertexNormals, state);
    notifyObserver(e);
}

void CgQtGui::slotObjectSelectionChanged(int object)
{
    CgBaseEvent *e = new CgSelectionChangedEvent(Cg::CgSelectionChangedEvent, Cg::Object, object);
    notifyObserver(e);
}
void CgQtGui::slotLoadMeshFile()
{

    QString file = QFileDialog::getOpenFileName(this, tr("Open Obj-File"), "", tr("Model Files (*.obj)"));

    CgBaseEvent *e = new CgLoadObjFileEvent(Cg::LoadObjFileEvent, file.toStdString());

    notifyObserver(e);
}

void CgQtGui::slotTrackballChanged()
{
    CgBaseEvent *e = new CgTrackballEvent(Cg::CgTrackballEvent, m_glRenderWidget->getTrackballRotation());
    notifyObserver(e);
}

void CgQtGui::slotDrawButtonPressed()
{
    CgBaseEvent *e = new CgButtonPressedEvent(Cg::CgButtonPressedEvent, Cg::Draw);
    notifyObserver(e);
}

void CgQtGui::mouseEvent(QMouseEvent *event)
{

    // std::cout << QApplication::keyboardModifiers() << std::endl;

    //  if(QApplication::keyboardModifiers().testFlag(Qt::ControlModifier)==true)
    //    std::cout << Cg::ControlModifier << endl;

    if (event->type() == QEvent::MouseButtonPress)
    {

        CgBaseEvent *e = new CgMouseEvent(Cg::CgMouseButtonPress,
                                          glm::vec2(event->localPos().x(), event->localPos().y()),
                                          (Cg::MouseButtons)event->button());

        notifyObserver(e);
    }

    if (event->type() == QEvent::MouseMove)
    {
        CgBaseEvent *e = new CgMouseEvent(Cg::CgMouseMove,
                                          glm::vec2(event->localPos().x(), event->localPos().y()),
                                          (Cg::MouseButtons)event->button());
        notifyObserver(e);
    }
}

void CgQtGui::keyPressEvent(QKeyEvent *event)
{
    CgBaseEvent *e = new CgKeyEvent(Cg::CgKeyPressEvent, (Cg::Key)event->key(), (Cg::KeyboardModifiers)event->nativeModifiers(), event->text().toStdString());
    notifyObserver(e);
}

void CgQtGui::viewportChanged(int w, int h)
{
    CgBaseEvent *e = new CgWindowResizeEvent(Cg::WindowResizeEvent, w, h);
    notifyObserver(e);
}

CgBaseRenderer *CgQtGui::getRenderer()
{
    return m_glRenderWidget;
}
