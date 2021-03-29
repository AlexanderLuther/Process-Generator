#include "MainFrame.h"
#include <QApplication>
#include <iostream>
#include <sys/wait.h>
#include <cstdio>
#include <unistd.h>

int main(int argc, char *argv[]){
    QApplication a(argc, argv);
    MainFrame w;
    w.show();
    return a.exec();
}
