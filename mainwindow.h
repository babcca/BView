#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "bfunctionmanager.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

signals:
    void LeftKey();
    void SetDirectory(const QString & dirPath);

private slots:
    void OpenFileExplorer();

protected:
    void keyPressEvent(QKeyEvent * keyEvent);
private:
    Ui::MainWindow *ui;
    BFilterManager fm;
};

#endif // MAINWINDOW_H
