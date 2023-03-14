#ifndef DATEWORKER_H
#define DATEWORKER_H

#include <QThread>
#include <QObject>
#include <QDebug>
#include <QTimer>
#include <QRandomGenerator>
class DateWorker : public QObject
{
    Q_OBJECT

public:
    explicit DateWorker(QObject *parent = nullptr);


    bool producer() const;
    void setProducer(bool newProducer);

signals:
    void produced(int value);
    void finished();

public slots:
    void consume(int value);
    void start();
    void quit();

private:
    QTimer *m_timer;
    bool m_producer;
    int m_count;

    void timeout();
};

#endif // DATEWORKER_H
