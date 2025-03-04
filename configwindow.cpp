#include "configwindow.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QSettings>
#include <QFile>
#include <QMessageBox>

#include "configwindow.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QSettings>
#include <QFile>
#include <QMessageBox>

ConfigWindow::ConfigWindow(QWidget *parent)
    : QDialog(parent), scriptFilePath("")
{
    setWindowTitle("Configure WMS");

    auto *layout = new QVBoxLayout(this);

    urlInput = new QLineEdit(this);
    urlInput->setPlaceholderText("Enter WMS URL (e.g., http://example.com:8080)...");

    uploadButton = new QPushButton("Upload Script", this);
    saveButton = new QPushButton("Save and Continue", this);

    layout->addWidget(new QLabel("WMS URL:"));
    layout->addWidget(urlInput);
    layout->addWidget(uploadButton);
    layout->addWidget(saveButton);

    connect(uploadButton, &QPushButton::clicked, this, &ConfigWindow::uploadScript);
    connect(saveButton, &QPushButton::clicked, this, &ConfigWindow::accept);

    // Load saved configuration
    QSettings settings("Blooloc", "WMSIntegrator");
    urlInput->setText(settings.value("wmsUrl", "").toString());
    scriptFilePath = settings.value("scriptPath", "").toString(); // Load script file path
}

void ConfigWindow::uploadScript() {
    QString filePath = QFileDialog::getOpenFileName(this, "Select Script File", "", "JavaScript Files (*.js)");

    if (!filePath.isEmpty()) {
        scriptFilePath = filePath; // Store the file path
        QMessageBox::information(this, "Success", "Script file uploaded successfully.");
    }
}

QString ConfigWindow::getUrl() const {
    return urlInput->text();
}

QString ConfigWindow::getScriptPath() const {
    return scriptFilePath; // Return the script file path
}

