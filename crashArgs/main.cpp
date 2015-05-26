#include <QGuiApplication>
#include <QCommandLineParser>
#include <QCommandLineOption>
#include <QDir>
#include <QDebug>
#include <private/qquickview_p.h>

#include "config.h"

int main(int argc, char *argv[])
{
    char *arg1 = "-platform";
    char *arg2 = "windows:fontengine=freetype";

    int argc0 = argc + 2;
    char *argv0[argc0];

    for (int i = 0; i < argc; i++) {
        argv0[i] = argv[i];
    }

    argv0[argc] = arg1;
    argv0[argc + 1] = arg2;

    QGuiApplication app(argc0, argv0);
//    QGuiApplication app(argc, argv);
    app.addLibraryPath("plugins");

    QQuickView *view = new QQuickView;
    if (!view) {
        fprintf(stderr, "Error: create QQuickView failed.\n");
        exit(-1);
    }
    view->setWidth(800);
    view->setHeight(480);
    Config *config = new Config();

    QCoreApplication::setApplicationName("Text Image Grabber");
    QCoreApplication::setApplicationVersion("1.0");

    QCommandLineParser parser;
    parser.setApplicationDescription("\nGrab image of given text.");
    parser.addHelpOption();
    parser.addVersionOption();

    parser.addPositionalArgument("text", QCoreApplication::translate("main", "Text string to be grabbed into an image."));

    // font size value option
    QCommandLineOption fontSizeOption(QStringList() << "z" << "size",
                                      QCoreApplication::translate("main", "Font size in pixel. Default: [24]."),
                                      QCoreApplication::translate("main", "size"),
                                      QCoreApplication::translate("main", "24"));
    parser.addOption(fontSizeOption);

    // Process the actual command line arguments given by the user
    parser.process(app);

    // source is args.at(0), destination is args.at(1)
    const QStringList args = parser.positionalArguments();
    if (args.length() == 0) {
        parser.showHelp(-1);
    }
    QString text = args[0];

    QString fontSizeStr = parser.value(fontSizeOption);
    bool bSizeOk;
    int fontSize = fontSizeStr.toInt(&bSizeOk);
    if (!bSizeOk) {
        exit(-101);
    }

    config->setText(text);
    config->setPixelSize(fontSize);

    QQmlEngine engine;
    QQmlComponent component(&engine);
    qDebug() << config->GetQML();
    component.setData(config->GetQML().toStdString().c_str(), QUrl());
    QQuickItem* item = qobject_cast<QQuickItem*>(component.create());
    if (!item) {
        qDebug() << "fatal error when creating QQuickItem: " << component.errorString();
        exit(2);
    }
    item->setParentItem(view->contentItem());
    view->show();
    if (view) {
        QImage img = view->grabWindow();
        img.save("test.bmp");
    }
    view->hide();

    return app.exec();
}
