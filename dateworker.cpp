#include "dateworker.h"

DateWorker::DateWorker(QObject *parent)
    : QObject{parent}
{
    m_producer=false;
    m_count=0;
}

bool DateWorker::producer() const
{
    return m_producer;
}

void DateWorker::setProducer(bool newProducer)
{
    m_producer = newProducer;
}

void DateWorker::consume(int value)
{
    qInfo()<< this<< "Consuming: "<< value<< QThread::currentThread();
}

void DateWorker::start()
{
    qInfo()<<this<<"Starting"<< QThread::currentThread();
    m_timer = new QTimer(this);
    connect(m_timer, &QTimer::timeout,this,&DateWorker::timeout);

    if(m_producer){
        qInfo()<< this<< "Starting timer"<< QThread::currentThread();
        m_timer->setInterval(100);
        m_timer->start();
    }
}

void DateWorker::quit()
{
    qInfo()<< this<< "Quiting"<< QThread::currentThread();
    m_timer->stop();
    emit finished();
}

void DateWorker::timeout()
{
    int value = QRandomGenerator::global()->bounded(1000);
    qInfo()<< this<< "Producing:  "<< value << QThread::currentThread();
    emit produced(value);
    m_count++;
    if(m_count == 5) quit();
}




