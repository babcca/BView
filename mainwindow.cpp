#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QKeyEvent"
#include "QFileDialog"

#include "functions/grayscale.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->connect(this, SIGNAL(LeftKey()), ui->OGLCanvas, SLOT(LeftKey()));
    this->connect(this, SIGNAL(RightKey()), ui->OGLCanvas, SLOT(RightKey()));
    this->connect(this, SIGNAL(SetDirectory(QString)), ui->OGLCanvas, SLOT(SetDirectory(QString)));
    ui->OGLCanvas->InitializeMenu(ui->menuBar);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::OpenFileExplorer() {
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::Directory);
    if(dialog.exec()) {
        auto selected = dialog.selectedFiles();
        QString dirPath = selected[0];
        emit SetDirectory(dirPath);
    }
}

void MainWindow::keyPressEvent(QKeyEvent *keyEvent) {
    switch (keyEvent->key()) {
        case Qt::Key_Left:
            emit LeftKey();
            break;
        case Qt::Key_Right:
            emit RightKey();
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
