#include "webviewwindow.h"
#include "./ui_webviewwindow.h"
#include <QVBoxLayout>
#include <QSettings>
#include <QTimer>
#include <QGraphicsOpacityEffect>
#include <QPropertyAnimation>
#include <spdlog/spdlog.h>

WebViewWindow::WebViewWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::WebViewWindow)
{
    ui->setupUi(this);

    // Setup layout
    auto *centralWidget = new QWidget(this);
    auto *layout = new QVBoxLayout(centralWidget);

    // Create input fields
    urlInput = new QLineEdit(this);
    urlInput->setPlaceholderText("Enter WMS-URL...");

    loadButton = new QPushButton("Load WMS", this);
    auto *saveButton = new QPushButton("Save Settings", this);

    webView = new QWebEngineView(this);

    // Toast Message (Small & Smooth Animation)
    toastLabel = new QLabel(this);
    toastLabel->setStyleSheet(
        "background-color: rgba(50, 50, 50, 200); "
        "color: white; "
        "font-size: 12px; "
        "padding: 6px 10px; "
        "border-radius: 5px;"
        );
    toastLabel->setAlignment(Qt::AlignCenter);
    toastLabel->setFixedSize(180, 30);
    toastLabel->setVisible(false);

    // Toast Animation
    auto *opacityEffect = new QGraphicsOpacityEffect(this);
    toastLabel->setGraphicsEffect(opacityEffect);
    toastAnimation = new QPropertyAnimation(opacityEffect, "opacity");
    toastAnimation->setDuration(500);  // 500ms fade

    // Add widgets to layout
    layout->addWidget(urlInput);
    layout->addWidget(loadButton);
    layout->addWidget(saveButton);
    layout->addWidget(webView);

    setCentralWidget(centralWidget);

    // Connect button clicks
    connect(loadButton, &QPushButton::clicked, this, &WebViewWindow::loadWMS);
    connect(saveButton, &QPushButton::clicked, this, &WebViewWindow::saveSettings);

    // Load settings
    QSettings settings("Blooloc", "WMSIntegrator");
    urlInput->setText(settings.value("wmsUrl", "").toString());

    if (!urlInput->text().isEmpty()) {
        webView->load(QUrl(urlInput->text()));
    }

    spdlog::info("WebViewWindow initialized.");
}

void WebViewWindow::saveSettings() {
    QSettings settings("Blooloc", "WMSIntegrator");

    settings.setValue("wmsUrl", urlInput->text());

    spdlog::info("Settings saved: {}", urlInput->text().toStdString());

    showToast("Settings saved!");
}

void WebViewWindow::loadWMS() {
    QString url = urlInput->text();
    if (!url.isEmpty()) {
        QSettings settings("Blooloc", "WMSIntegrator");
        settings.setValue("wmsUrl", url);

        spdlog::info("Loading WMS URL: {}", url.toStdString());

        webView->load(QUrl(url));

        // Wacht tot de pagina geladen is en voer het script uit
        connect(webView, &QWebEngineView::loadFinished, this, [this](bool ok) {
            if (ok) {
                spdlog::info("Page loaded successfully.");

                QSettings settings("Blooloc", "WMSIntegrator");
                QString script = settings.value("script", "").toString();

                if (!script.isEmpty()) {
                    spdlog::info("Executing JavaScript.");
                    webView->page()->runJavaScript(script);
                }
            } else {
                spdlog::error("Failed to load WMS URL.");
            }
        });

        showToast("WMS Loaded!");
    } else {
        spdlog::warn("Load WMS button clicked, but URL is empty.");
    }
}

void WebViewWindow::showToast(const QString &message) {
    toastLabel->setText(message);
    toastLabel->move(width() - toastLabel->width() - 20, height() - toastLabel->height() - 20); // Bottom-right
    toastLabel->setVisible(true);

    // Fade In
    toastAnimation->setStartValue(0.0);
    toastAnimation->setEndValue(1.0);
    toastAnimation->start();

    // Wait 2.5s then fade out
    QTimer::singleShot(2500, [this]() {
        toastAnimation->setStartValue(1.0);
        toastAnimation->setEndValue(0.0);
        toastAnimation->start();
        connect(toastAnimation, &QPropertyAnimation::finished, toastLabel, &QLabel::hide);
    });

    spdlog::debug("Toast displayed: {}", message.toStdString());
}

WebViewWindow::~WebViewWindow() {
    spdlog::info("WebViewWindow destroyed.");
    delete ui;
}
