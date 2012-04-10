#ifndef OPENGLCANVAS_H
#define OPENGLCANVAS_H

#include <QGLWidget>
#include "QLabel"
#include "bimagemanager.h"
#include "brender.h"


class OpenGlCanvas : public QGLWidget
{
    Q_OBJECT
public:
    explicit OpenGlCanvas(QWidget *parent = 0);
    virtual ~OpenGlCanvas();
    void SetDebugger(QLabel * debugger);
protected:
    void initializeGL();
    void resizeGL(int width, int height);
    void paintGL();

signals:

public slots:
    void LeftKey();
    void RedrawCanvas();
    void ShowFps();
    void SetDirectory(const QString & dirPath);

private:
    static const int ONE_SECOND = 1000;
    static const int FPS_COUNT = 60;
    QLabel * debugger;
    QTimer * timer;
    int count;
    BImageManager imageManager;
    BRender render;

};

#endif // OPENGLCANVAS_H
