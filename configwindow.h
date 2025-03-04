#ifndef CONFIGWINDOW_H
#define CONFIGWINDOW_H

#include <QDialog>
#include <QLineEdit>
#include <QPushButton>
#include <QFileDialog>

class ConfigWindow : public QDialog
{
    Q_OBJECT

public:
    ConfigWindow(QWidget *parent = nullptr);
    QString getUrl() const;
    QString getScriptPath() const;

private slots:
    void uploadScript();

private:
    QLineEdit *urlInput;
    QPushButton *uploadButton;
    QPushButton *saveButton;
    QString scriptFilePath;
};

#endif // CONFIGWINDOW_H
