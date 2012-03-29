#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QKeyEvent"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    ui->OGLCanvas->SetDebugger(ui->DebugConsole);
    QObject::connect(this, SIGNAL(LeftKey()), ui->OGLCanvas, SLOT(LeftKey()));
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::keyPressEvent(QKeyEvent *keyEvent) {
    switch (keyEvent->key()) {
        case Qt::Key_Left:
            emit LeftKey();
            break;
        case Qt::Key_F11:
            // how to hide widgets?
            emit showFullScreen();
            break;
        case Qt::Key_F10:
            emit showNormal();
            break;
        default:
            QWidget::keyPressEvent(keyEvent);
            break;
    };
}
