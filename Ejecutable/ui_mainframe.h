/********************************************************************************
** Form generated from reading UI file 'mainframe.ui'
**
** Created by: Qt User Interface Compiler version 6.0.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINFRAME_H
#define UI_MAINFRAME_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainFrame
{
public:
    QAction *actionCargar_Archivo;
    QAction *actionSalir;
    QAction *actionAcerca_De;
    QWidget *centralwidget;
    QGridLayout *gridLayout_2;
    QGraphicsView *graphicsArea;
    QGridLayout *gridLayout;
    QLineEdit *commandArea;
    QPushButton *executeButton;
    QTextEdit *historyArea;
    QMenuBar *menubar;
    QMenu *menuArchivo;
    QMenu *menuAcerca_De;

    void setupUi(QMainWindow *MainFrame)
    {
        if (MainFrame->objectName().isEmpty())
            MainFrame->setObjectName(QString::fromUtf8("MainFrame"));
        MainFrame->resize(757, 503);
        MainFrame->setStyleSheet(QString::fromUtf8("blue"));
        actionCargar_Archivo = new QAction(MainFrame);
        actionCargar_Archivo->setObjectName(QString::fromUtf8("actionCargar_Archivo"));
        actionCargar_Archivo->setCheckable(false);
        actionSalir = new QAction(MainFrame);
        actionSalir->setObjectName(QString::fromUtf8("actionSalir"));
        actionAcerca_De = new QAction(MainFrame);
        actionAcerca_De->setObjectName(QString::fromUtf8("actionAcerca_De"));
        centralwidget = new QWidget(MainFrame);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        gridLayout_2 = new QGridLayout(centralwidget);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        graphicsArea = new QGraphicsView(centralwidget);
        graphicsArea->setObjectName(QString::fromUtf8("graphicsArea"));

        gridLayout_2->addWidget(graphicsArea, 0, 0, 1, 1);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        commandArea = new QLineEdit(centralwidget);
        commandArea->setObjectName(QString::fromUtf8("commandArea"));

        gridLayout->addWidget(commandArea, 0, 1, 1, 1);

        executeButton = new QPushButton(centralwidget);
        executeButton->setObjectName(QString::fromUtf8("executeButton"));

        gridLayout->addWidget(executeButton, 0, 0, 1, 1);


        gridLayout_2->addLayout(gridLayout, 1, 0, 1, 1);

        historyArea = new QTextEdit(centralwidget);
        historyArea->setObjectName(QString::fromUtf8("historyArea"));
        historyArea->setReadOnly(true);

        gridLayout_2->addWidget(historyArea, 2, 0, 1, 1, Qt::AlignBottom);

        MainFrame->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainFrame);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 757, 20));
        menuArchivo = new QMenu(menubar);
        menuArchivo->setObjectName(QString::fromUtf8("menuArchivo"));
        menuAcerca_De = new QMenu(menubar);
        menuAcerca_De->setObjectName(QString::fromUtf8("menuAcerca_De"));
        MainFrame->setMenuBar(menubar);

        menubar->addAction(menuArchivo->menuAction());
        menubar->addAction(menuAcerca_De->menuAction());
        menuArchivo->addAction(actionCargar_Archivo);
        menuArchivo->addAction(actionSalir);
        menuAcerca_De->addAction(actionAcerca_De);

        retranslateUi(MainFrame);

        QMetaObject::connectSlotsByName(MainFrame);
    } // setupUi

    void retranslateUi(QMainWindow *MainFrame)
    {
        MainFrame->setWindowTitle(QCoreApplication::translate("MainFrame", "Generador de Procesos", nullptr));
        actionCargar_Archivo->setText(QCoreApplication::translate("MainFrame", "Cargar Archivo", nullptr));
#if QT_CONFIG(shortcut)
        actionCargar_Archivo->setShortcut(QCoreApplication::translate("MainFrame", "Ctrl+O", nullptr));
#endif // QT_CONFIG(shortcut)
        actionSalir->setText(QCoreApplication::translate("MainFrame", "Salir", nullptr));
        actionAcerca_De->setText(QCoreApplication::translate("MainFrame", "Acerca De", nullptr));
        executeButton->setText(QCoreApplication::translate("MainFrame", "Ejecutar", nullptr));
        menuArchivo->setTitle(QCoreApplication::translate("MainFrame", "Archivo", nullptr));
        menuAcerca_De->setTitle(QCoreApplication::translate("MainFrame", "Ayuda", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainFrame: public Ui_MainFrame {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINFRAME_H
