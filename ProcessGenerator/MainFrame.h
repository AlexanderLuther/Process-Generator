#ifndef MAINFRAME_H
#define MAINFRAME_H

#include <QMainWindow>
#include <iostream>
#include <vector>
#include "FilesDriver.h"
#include "CommandDriver.h"
#include "Command.h"
#include "Stem.h"
#include "CommandDriver.h"
#include "QFileDialog"
QT_BEGIN_NAMESPACE
namespace Ui { class MainFrame; }
QT_END_NAMESPACE

class MainFrame : public QMainWindow{
    Q_OBJECT

    private:
        Ui::MainFrame *ui;
        FilesDriver* filesDriver = new FilesDriver();
        CommandDriver* commandDriver = new CommandDriver(filesDriver);
        vector<Stem*>* stems = new vector<Stem*>();
        Command* command;

    public:
        MainFrame(QWidget *parent = nullptr);
        ~MainFrame();

    private slots:
        void on_executeButton_clicked();
        void on_actionCargar_Archivo_triggered();
};
#endif // MAINFRAME_H
