#ifndef CONFIGWINDOW_H
#define CONFIGWINDOW_H

#include <QDialog>
#include <QLineEdit>
#include <QPushButton>

class ConfigWindow : public QDialog
{
    Q_OBJECT

public:
    ConfigWindow(QWidget *parent = nullptr);
    QString getUrl() const;

private:
    QLineEdit *urlInput;
    QPushButton *saveButton;
};

#endif // CONFIGWINDOW_H
