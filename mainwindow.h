#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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
    void RightKey();
    void SetDirectory(const QString & dirPath);

private slots:
    void OpenFileExplorer();

protected:
    void keyPressEvent(QKeyEvent * keyEvent);
private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
