#ifndef WEBVIEWWINDOW_H
#define WEBVIEWWINDOW_H

#include <QMainWindow>
#include <QWebEngineView>
#include <QLineEdit>
#include <QPushButton>
#include <QSpinBox>
#include <QLabel>
#include <QPropertyAnimation>
#include "spdlog/spdlog.h"

namespace Ui {
class WebViewWindow;
}

class WebViewWindow : public QMainWindow
{
    Q_OBJECT

public:
    WebViewWindow(QWidget *parent = nullptr);
    ~WebViewWindow();

private slots:
    void loadWMS();
    void saveSettings();

private:
    Ui::WebViewWindow *ui;
    QWebEngineView *webView;
    QLineEdit *urlInput;
    QPushButton *loadButton;
    QSpinBox *portInput;
    QLabel *toastLabel;
    QPropertyAnimation *toastAnimation;

    void showToast(const QString &message);
};

#endif // WEBVIEWWINDOW_H
