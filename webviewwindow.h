#ifndef WEBVIEWWINDOW_H
#define WEBVIEWWINDOW_H

#include <QMainWindow>
#include <QWebEngineView>
#include <QLineEdit>
#include <QPushButton>

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
    void loadWMS(); // Slot to load the WMS URL

private:
    Ui::WebViewWindow *ui;
    QWebEngineView *webView;
    QLineEdit *urlInput;
    QPushButton *loadButton;
};

#endif // WEBVIEWWINDOW_H
