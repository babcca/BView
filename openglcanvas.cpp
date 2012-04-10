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

}

void OpenGlCanvas::InitializeMenu(QMenuBar *menuBar) {
   connect(menuBar, SIGNAL(triggered(QAction*)), this, SLOT(updateGL()));
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

    if (imageManager.ActualImage.initialized) {
        qDebug("Redraw");
        std::shared_ptr<Image> image = render.Render(&imageManager.ActualImage, this->width(), this->height());
        std::pair<float, float> centerPosition = render.GetCenterPosition(image.get(), this->width(), this->height());
        glRasterPos2i(centerPosition.first, centerPosition.second);

        int height = image->GetHeight();
        int width = image->GetWidth();
        int format = image->GetPixelFormat();
        std::shared_ptr<char> raw = image->ImageData.GetAllocatedMemory();
        glDrawPixels(width, height, format, GL_UNSIGNED_BYTE, raw.get());
        //imageManager.ActualImage->DeleteFromCache();
    }
}
