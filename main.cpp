#include "configwindow.h"
#include "webviewwindow.h"
#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include <QSettings>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "WMS-integrator_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }

    // Show the configuration window
    ConfigWindow configWindow;
    if (configWindow.exec() == QDialog::Accepted) {
        QString url = configWindow.getUrl();
        QString scriptPath = configWindow.getScriptPath(); // Get the script file path

        // Save the configuration
        QSettings settings("Blooloc", "WMSIntegrator");
        settings.setValue("wmsUrl", url);
        settings.setValue("scriptPath", scriptPath); // Save the script file path

        // Start the main window with the WebView
        WebViewWindow w(url);
        w.show();
        return a.exec();
    }

    return 0; // Close the app if the configuration is canceled
}
