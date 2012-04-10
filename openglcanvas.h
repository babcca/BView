#ifndef OPENGLCANVAS_H
#define OPENGLCANVAS_H

#include <QGLWidget>
#include "QLabel"
#include "brender.h"
#include "bimagemanager.h"


class OpenGlCanvas : public QGLWidget
{
    Q_OBJECT
public:
    explicit OpenGlCanvas(QWidget *parent = 0);
    virtual ~OpenGlCanvas();
    void InitializeMenu(QMenuBar * menuBar);
protected:
    void initializeGL();
    void resizeGL(int width, int height);
    void paintGL();

signals:

public slots:
    void LeftKey();
    void RightKey();
    void RedrawCanvas();
    void SetDirectory(const QString & dirPath);

private:
    static const int ONE_SECOND = 1000;
    static const int FPS_COUNT = 60;
    BImageManager imageManager;

    BRender render;

};

#endif // OPENGLCANVAS_H
