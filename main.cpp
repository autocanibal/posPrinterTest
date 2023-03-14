#include "mainwindow.h"
#include "dateworker.h"
#include <QThread>
#include <QDebug>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    QThread pThread;
    QThread cThread;

    DateWorker producer;
    DateWorker consumer;

    producer.moveToThread(&pThread);
    consumer.moveToThread(&cThread);

    producer.setProducer(true);

    pThread.setObjectName("Producer Thread");
    cThread.setObjectName("Consumer Thread");
    producer.setObjectName("Producer");
    consumer.setObjectName("Consumer");

    QObject::connect(&pThread, &QThread::started, &producer,&DateWorker::start);
    QObject::connect(&cThread, &QThread::started, &consumer,&DateWorker::start);

    QObject::connect(&producer, &DateWorker::produced, &consumer,&DateWorker::consume);
    QObject::connect(&producer, &DateWorker::finished, &consumer,&DateWorker::quit);

    cThread.start();
    pThread.start();

    return a.exec();
}
