#include "configwindow.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QSettings>

ConfigWindow::ConfigWindow(QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle("Configure WMS");

    auto *layout = new QVBoxLayout(this);

    urlInput = new QLineEdit(this);
    urlInput->setPlaceholderText("Enter WMS URL (e.g., http://example.com:8080)...");

    saveButton = new QPushButton("Save and Continue", this);

    layout->addWidget(new QLabel("WMS URL:"));
    layout->addWidget(urlInput);
    layout->addWidget(saveButton);

    connect(saveButton, &QPushButton::clicked, this, &ConfigWindow::accept);

    // Laad opgeslagen configuratie
    QSettings settings("Blooloc", "WMSIntegrator");
    urlInput->setText(settings.value("wmsUrl", "").toString());
}

QString ConfigWindow::getUrl() const {
    return urlInput->text();
}
