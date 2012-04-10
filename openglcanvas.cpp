#include "openglcanvas.h"
#include "QKeyEvent"
#include "QLabel"
#include "QTimer"
#include "fileloaderfactory.h"
#include "bmpfileloader.h"

OpenGlCanvas::OpenGlCanvas(QWidget *parent) :
    QGLWidget(parent)
{
    FileFactory<ImageFileLoader *> fileFactory;
    fileFactory.AddFactory("bmp", [](){ return BMPFileLoader::CreateInstance(); });
    imageManager.SetFileFactory(fileFactory);
}

OpenGlCanvas::~OpenGlCanvas() {
    //delete timer;
}

void OpenGlCanvas::InitializeMenu(QMenuBar *menuBar) {
    //connect(menuBar, SIGNAL(triggered(QAction*)), this, SLOT(RedrawCanvas()));
    render.InitializeMenu(menuBar);
}

void OpenGlCanvas::SetDirectory(const QString & dirPath) {
    qDebug(dirPath.toStdString().c_str());
    imageManager.LoadDirectory(dirPath.toStdWString());
}

void OpenGlCanvas::initializeGL() {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, this->width(), this->height(), 0, 0, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glDisable(GL_DEPTH_TEST);
    glClearColor(0.0f, 0.5f, 0.5f, 0.7f);
}

void OpenGlCanvas::resizeGL(int width, int height) {
    qDebug("Resize %dx%d", width, height);
    glViewport(0,0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, width, height, 0, 0, 1);
    render.SetScreenSize(width, height);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

}


void OpenGlCanvas::paintGL() {
    RedrawCanvas();
}

void OpenGlCanvas::LeftKey() {
    qDebug("Left Key");
    ++imageManager.ActualImage;
    updateGL();
}


void OpenGlCanvas::RightKey() {
    qDebug("Right Key");
    --imageManager.ActualImage;
    updateGL();
}

void OpenGlCanvas::RedrawCanvas() {
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    //glRasterPos2i(500, 500);

    if (imageManager.ActualImage.initialized) {
        qDebug("Redraw");
        render.Render(&imageManager.ActualImage);
        //imageManager.ActualImage->DeleteFromCache();
    }
}
