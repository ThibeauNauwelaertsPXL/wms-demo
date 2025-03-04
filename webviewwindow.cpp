#include "webviewwindow.h"
#include "./ui_webviewwindow.h"
#include <QVBoxLayout>
#include <QSettings>
#include <QTimer>
#include <QGraphicsOpacityEffect>
#include <QPropertyAnimation>
#include "Logger.h"

WebViewWindow::WebViewWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::WebViewWindow)
{
    ui->setupUi(this);
    Logger::init();

    auto *centralWidget = new QWidget(this);
    auto *layout = new QVBoxLayout(centralWidget);

    urlInput = new QLineEdit(this);
    urlInput->setPlaceholderText("Enter WMS URL (e.g., http://example.com:8080)...");

    loadButton = new QPushButton("Load WMS", this);
    webView = new QWebEngineView(this);

    toastLabel = new QLabel(this);
    toastLabel->setStyleSheet(
        "background-color: rgba(50, 50, 50, 200); "
        "color: white; "
        "font-size: 12px; "
        "padding: 6px 10px; "
        "border-radius: 5px;");
    toastLabel->setAlignment(Qt::AlignCenter);
    toastLabel->setFixedSize(180, 30);
    toastLabel->setVisible(false);

    auto *opacityEffect = new QGraphicsOpacityEffect(this);
    toastLabel->setGraphicsEffect(opacityEffect);
    toastAnimation = new QPropertyAnimation(opacityEffect, "opacity");
    toastAnimation->setDuration(500);

    layout->addWidget(urlInput);
    layout->addWidget(loadButton);
    layout->addWidget(webView);

    setCentralWidget(centralWidget);

    connect(loadButton, &QPushButton::clicked, this, &WebViewWindow::loadWMS);

    QSettings settings("Blooloc", "WMSIntegrator");
    urlInput->setText(settings.value("wmsUrl", "").toString());

    if (!urlInput->text().isEmpty()) {
        webView->load(QUrl(urlInput->text()));
    }

    connect(webView, &QWebEngineView::loadFinished, this, [this](bool ok) {
        if (ok) {
            Logger::getLogger()->info("Page loaded successfully.");

            QSettings settings("Blooloc", "WMSIntegrator");
            QString script = settings.value("script", "").toString();

            if (!script.isEmpty()) {
                Logger::getLogger()->info("Executing JavaScript.");
                webView->page()->runJavaScript(script);
            }
        } else {
            Logger::getLogger()->error("Failed to load page.");
        }
    });

    Logger::getLogger()->info("WebViewWindow initialized.");
}

WebViewWindow::~WebViewWindow() {
    Logger::getLogger()->info("WebViewWindow destroyed.");
    delete ui;
}

void WebViewWindow::loadWMS() {
    QString input = urlInput->text().trimmed();
    if (input.isEmpty()) {
        Logger::getLogger()->warn("Load WMS button clicked, but URL is empty.");
        return;
    }

    QUrl qurl(input);
    if (!qurl.isValid()) {
        Logger::getLogger()->error("Invalid URL: {}", input.toStdString());
        showToast("Invalid URL format.");
        return;
    }

    if (qurl.scheme().isEmpty()) {
        qurl.setScheme("http");
    }

    Logger::getLogger()->info("Attempting to load: {}", qurl.toString().toStdString());

    webView->stop();
    webView->page()->triggerAction(QWebEnginePage::ReloadAndBypassCache);

    QTimer::singleShot(100, this, [this, qurl]() {
        webView->load(qurl);
    });

    showToast("Loading new WMS site...");

    QSettings settings("Blooloc", "WMSIntegrator");
    settings.setValue("wmsUrl", qurl.toString());
}

void WebViewWindow::showToast(const QString &message) {
    toastLabel->setText(message);
    toastLabel->move(width() - toastLabel->width() - 20, height() - toastLabel->height() - 20);
    toastLabel->setVisible(true);

    toastAnimation->setStartValue(0.0);
    toastAnimation->setEndValue(1.0);
    toastAnimation->start();

    QTimer::singleShot(2500, [this]() {
        toastAnimation->setStartValue(1.0);
        toastAnimation->setEndValue(0.0);
        toastAnimation->start();
        connect(toastAnimation, &QPropertyAnimation::finished, toastLabel, &QLabel::hide);
    });

    Logger::getLogger()->debug("Toast displayed: {}", message.toStdString());
}
