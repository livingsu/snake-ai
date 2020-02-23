#ifndef GAMEWIDGET_H
#define GAMEWIDGET_H

#include <QWidget>
#include <QtMultimedia/QMediaPlayer>
#include <drawwidget.h>
#include <QDebug>


namespace Ui {
class gameWidget;
}

class gameWidget : public QWidget
{
    Q_OBJECT

public:
    explicit gameWidget(QWidget *parent = nullptr);
    void setModeState(modeState ms){
        this->modeS=ms;
        myDrawWidget->modeS=ms;}
    void setMapState(mapState ms){
        this->mapS=ms;
        myDrawWidget->mapS=ms;}
    ~gameWidget();

signals:
    void returnSignal();

public slots:
    void returnPush();
    void startPush();//开始游戏
    void setInitial();//设置按钮为初始状态
    void addScore_1();//给蛇1加分
    void addScore_2();
    void lcdFoodDisplay();//显示倒计时

private slots:
    void countDown();//设置倒计时
    void setSlow();

protected:
    bool eventFilter(QObject *watched,QEvent *event);//过滤掉ai模式下的键盘按键

private:
    Ui::gameWidget *ui;
    drawWidget *myDrawWidget;

    modeState modeS=SINGLEMODE;
    mapState mapS=BASIC;

    int score_1=0;
    int score_2=0;
   // QMediaPlayer *player;
};

#endif // GAMEWIDGET_H


