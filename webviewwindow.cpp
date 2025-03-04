#include "webviewwindow.h"
#include "./ui_webviewwindow.h"
#include <QVBoxLayout>
#include <QSettings>
#include <QTimer>
#include <QGraphicsOpacityEffect>
#include <QPropertyAnimation>
#include "Logger.h"
#include <QFile>

WebViewWindow::WebViewWindow(const QString &url, QWidget *parent)
    : QMainWindow(parent), ui(new Ui::WebViewWindow)
{
    ui->setupUi(this);
    Logger::init();

    auto *centralWidget = new QWidget(this);
    auto *layout = new QVBoxLayout(centralWidget);

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

    layout->addWidget(webView);

    setCentralWidget(centralWidget);

    // Laad de URL die is doorgegeven vanuit het configuratiescherm
    if (!url.isEmpty()) {
        webView->load(QUrl(url));
    }

    // Inside WebViewWindow constructor, in the loadFinished lambda function
    connect(webView, &QWebEngineView::loadFinished, this, [this](bool ok) {
        if (ok) {
            Logger::getLogger()->info("Page loaded successfully.");

            QSettings settings("Blooloc", "WMSIntegrator");
            QString scriptPath = settings.value("scriptPath", "").toString(); // Get script file path

            if (!scriptPath.isEmpty()) {
                QFile file(scriptPath);
                if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
                    QString scriptContent = file.readAll();
                    file.close();

                    qDebug() << "Executing script from file:" << scriptPath;
                    Logger::getLogger()->info("Executing JavaScript from file.");

                    // Wrap the script in a try-catch block to handle errors
                    QString wrappedScript = R"(
                        try {
                            )" + scriptContent + R"(
                        } catch (e) {
                            console.error("Error executing script:", e);
                        }
                    )";

                    webView->page()->runJavaScript(wrappedScript);
                } else {
                    Logger::getLogger()->error("Failed to open script file.");
                    qDebug() << "Error: Failed to open script file!";
                }
            } else {
                Logger::getLogger()->warn("No scriptPath found in settings.");
                qDebug() << "Error: scriptPath is empty!";
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
