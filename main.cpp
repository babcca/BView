#include <QtGui/QApplication>
#include "mainwindow.h"

#include "BViewQtOpenGl_gtest.cpp"

int main(int argc, char *argv[])
{
    TestAll(argc, argv);

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    
    return a.exec();
    //getchar();
    return 0;
}
