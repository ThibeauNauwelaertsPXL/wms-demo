/********************************************************************************
** Form generated from reading UI file 'configwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CONFIGWINDOW_H
#define UI_CONFIGWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_WebViewWindow
{
public:
    QWidget *centralwidget;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *WebViewWindow)
    {
        if (WebViewWindow->objectName().isEmpty())
            WebViewWindow->setObjectName("WebViewWindow");
        WebViewWindow->resize(800, 600);
        centralwidget = new QWidget(WebViewWindow);
        centralwidget->setObjectName("centralwidget");
        WebViewWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(WebViewWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 22));
        WebViewWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(WebViewWindow);
        statusbar->setObjectName("statusbar");
        WebViewWindow->setStatusBar(statusbar);

        retranslateUi(WebViewWindow);

        QMetaObject::connectSlotsByName(WebViewWindow);
    } // setupUi

    void retranslateUi(QMainWindow *WebViewWindow)
    {
        WebViewWindow->setWindowTitle(QCoreApplication::translate("WebViewWindow", "WebViewWindow", nullptr));
    } // retranslateUi

};

namespace Ui {
    class WebViewWindow: public Ui_WebViewWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONFIGWINDOW_H
