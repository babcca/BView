#ifndef OPENGLCANVAS_H
#define OPENGLCANVAS_H

#include <QGLWidget>
#include "QLabel"

class OpenGlCanvas : public QGLWidget
{
    Q_OBJECT
public:
    explicit OpenGlCanvas(QWidget *parent = 0);
    virtual ~OpenGlCanvas();
    void SetDebugger(QLabel * debugger);
protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();

signals:

public slots:
    void LeftKey();
    void RedrawCanvas();
    void ShowFps();

private:
    static const int ONE_SECOND = 1000;
    static const int FPS_COUNT = 60;
    QLabel * debugger;
    QTimer * timer;
    int count;
};

#endif // OPENGLCANVAS_H
