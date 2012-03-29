#include "openglcanvas.h"
#include "QKeyEvent"
#include "QLabel"
#include "QTimer"

OpenGlCanvas::OpenGlCanvas(QWidget *parent) :
    QGLWidget(parent),
    count(0)
{
    timer = new QTimer(this);
    timer->setInterval(ONE_SECOND/FPS_COUNT);
    this->connect(timer, SIGNAL(timeout()), this, SLOT(RedrawCanvas()));
    //timer->start();

}

OpenGlCanvas::~OpenGlCanvas() {
    delete timer;
}

void OpenGlCanvas::initializeGL() {
    glClearColor(0.0f, 0.5f, 0.5f, 0.7f);
}

void OpenGlCanvas::resizeGL(int w, int h) {
    debugger->setText("resize " + QString::number(w));
}

void OpenGlCanvas::paintGL() {
    RedrawCanvas();
}

void OpenGlCanvas::LeftKey() {
    debugger->setText("Ahoj");
}

void OpenGlCanvas::RedrawCanvas() {
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    count++;
    ShowFps();
}

void OpenGlCanvas::ShowFps() {
     //debugger->setText(QString::number(count));
}

void OpenGlCanvas::SetDebugger(QLabel * debugger) {
    this->debugger = debugger;
}
