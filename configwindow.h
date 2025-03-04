#ifndef CONFIGWINDOW_H
#define CONFIGWINDOW_H

#include <QDialog>
#include <QLineEdit>
#include <QPushButton>
#include <QTextEdit>

class ConfigWindow : public QDialog
{
    Q_OBJECT

public:
    ConfigWindow(QWidget *parent = nullptr);
    QString getUrl() const;
    QString getScript() const;

private:
    QLineEdit *urlInput;
    QTextEdit *scriptInput;
    QPushButton *saveButton;
};

#endif // CONFIGWINDOW_H
