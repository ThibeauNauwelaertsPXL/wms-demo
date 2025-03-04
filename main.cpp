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

    // Toon eerst het configuratiescherm
    ConfigWindow configWindow;
    if (configWindow.exec() == QDialog::Accepted) {
        QString url = configWindow.getUrl();

        // Sla de configuratie op
        QSettings settings("Blooloc", "WMSIntegrator");
        settings.setValue("wmsUrl", url);

        // Start het hoofdvenster met de WebView
        WebViewWindow w(url);
        w.show();
        return a.exec();
    }

    return 0; // Sluit de app als de configuratie wordt geannuleerd
}
