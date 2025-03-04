#ifndef WEBVIEWWINDOW_H
#define WEBVIEWWINDOW_H

#include <QMainWindow>
#include <QWebEngineView>
#include <QLabel>
#include <QPropertyAnimation>
#include "logger.h"

namespace Ui {
class WebViewWindow;
}

class WebViewWindow : public QMainWindow
{
    Q_OBJECT

public:
    WebViewWindow(const QString &url, QWidget *parent = nullptr);
    ~WebViewWindow();

private:
    Ui::WebViewWindow *ui;
    QWebEngineView *webView;
    QLabel *toastLabel;
    QPropertyAnimation *toastAnimation;

    void showToast(const QString &message);
};

#endif // WEBVIEWWINDOW_H
