//这是一个单例处理器，用来处理信号
#ifndef HANDLER_H
#define HANDLER_H

#include <QObject>
#include <QDebug>

class handler : public QObject
{
    Q_OBJECT
private:
    explicit handler(QObject *parent = nullptr);

signals:
    void countDownSignal(); //吃到特殊食物后发出倒计时信号

public slots:

public:
    static handler *getInstance(); //得到handler类的唯一实例
    void countDown();

private:
    static handler* hand;
};

#endif // HANDLER_H
