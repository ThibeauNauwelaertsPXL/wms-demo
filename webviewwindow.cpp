#include "webviewwindow.h"
#include "./ui_webviewwindow.h"
#include <QVBoxLayout>
#include <QSettings>

WebViewWindow::WebViewWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::WebViewWindow)
{
    ui->setupUi(this);

    // Setup layout
    auto *centralWidget = new QWidget(this);
    auto *layout = new QVBoxLayout(centralWidget);

    // Create input field and button
    urlInput = new QLineEdit(this);
    urlInput->setPlaceholderText("Enter WMS-URL...");
    loadButton = new QPushButton("Load WMS", this);
    webView = new QWebEngineView(this);

    // Add widgets to layout
    layout->addWidget(urlInput);
    layout->addWidget(loadButton);
    layout->addWidget(webView);

    setCentralWidget(centralWidget);

    // Connect button click to loadWMS() function
    connect(loadButton, &QPushButton::clicked, this, &WebViewWindow::loadWMS);

    // Load last saved URL
    QSettings settings("Blooloc", "WMSIntegrator");
    QString lastUrl = settings.value("wmsUrl", "").toString();
    if (!lastUrl.isEmpty()) {
        webView->load(QUrl(lastUrl));
    }
}

void WebViewWindow::loadWMS() {
    QString url = urlInput->text();
    if (!url.isEmpty()) {
        // Save URL to QSettings
        QSettings settings("Blooloc", "WMSIntegrator");
        settings.setValue("wmsUrl", url);

        // Load the URL into the webview
        webView->load(QUrl(url));
    }
}

WebViewWindow::~WebViewWindow() {
    delete ui;
}
