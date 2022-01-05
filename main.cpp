#include <QGuiApplication>
#include<QCoreApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "communicatorqml.h"
#include <QSerialPort>


int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;


    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    QQmlContext *context = engine.rootContext();
    communicatorQml *cm = new communicatorQml();
    //cm.setValue1(156);
    //cm.setValue2(156);
    //cm->setValue3(4);
    //context->setContextProperty("_val1",cm->getValue1());
    //context->setContextProperty("_val2",cm->getValue2());
    //context->setContextProperty("_val3",cm->getValue3());
    context->setContextProperty("_obj",cm);
    //QObject::connect(cm,&communicatorQml::Value1Changed,cm,&communicatorQml::dial1c2set);
    //QSerialPort *serial;
    //QObject::connect(serial,SIGNAL(readyRead()),cm,SLOT(setValue2(Value1())));
    QObject::connect(cm,SIGNAL(StartReadAgain()),cm,SLOT(readSerial()));
    engine.load(url);

    return app.exec();
}
