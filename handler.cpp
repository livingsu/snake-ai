#include "handler.h"

handler::handler(QObject *parent) : QObject(parent)
{

}

handler* handler::hand=new handler;

handler* handler::getInstance(){
    return hand;
}

void handler::countDown(){
    emit countDownSignal();
    qDebug()<<"countDown倒计时开始！！！";
}





