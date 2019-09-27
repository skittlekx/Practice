/********************************************************************************
** Form generated from reading UI file 'QtLearn.ui'
**
** Created by: Qt User Interface Compiler version 5.9.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QTLEARN_H
#define UI_QTLEARN_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QtLearnClass
{
public:
    QWidget *centralWidget;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *QtLearnClass)
    {
        if (QtLearnClass->objectName().isEmpty())
            QtLearnClass->setObjectName(QStringLiteral("QtLearnClass"));
        QtLearnClass->resize(1080, 643);
        centralWidget = new QWidget(QtLearnClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        QtLearnClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(QtLearnClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1080, 26));
        QtLearnClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(QtLearnClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        QtLearnClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(QtLearnClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        QtLearnClass->setStatusBar(statusBar);

        retranslateUi(QtLearnClass);

        QMetaObject::connectSlotsByName(QtLearnClass);
    } // setupUi

    void retranslateUi(QMainWindow *QtLearnClass)
    {
        QtLearnClass->setWindowTitle(QApplication::translate("QtLearnClass", "QtLearn", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class QtLearnClass: public Ui_QtLearnClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QTLEARN_H
