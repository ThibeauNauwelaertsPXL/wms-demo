#ifndef WEBVIEWWINDOW_H
#define WEBVIEWWINDOW_H

#include <QMainWindow>
#include <QWebEngineView>
#include <QLineEdit>
#include <QPushButton>
#include <QSpinBox>
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
    WebViewWindow(QWidget *parent = nullptr);
    ~WebViewWindow();

    void setPort(int port);

private slots:
    void loadWMS();

private:
    Ui::WebViewWindow *ui;
    QWebEngineView *webView;
    QLineEdit *urlInput;
    QPushButton *loadButton;
    QLineEdit *portInput;
    QLabel *toastLabel;
    QPropertyAnimation *toastAnimation;

    int port;

    void showToast(const QString &message);
};

#endif // WEBVIEWWINDOW_H
