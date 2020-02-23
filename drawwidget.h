#ifndef DRAWWIDGET_H
#define DRAWWIDGET_H

#include <QWidget>
#include <QDebug>
#include <QtGui>
#include <QTimer>
#include <QAbstractButton>
#include <QMessageBox>
#include <QList>
#include <QFocusEvent>
#include <cstdlib>
#include <cmath>
#include <ctime>
#include <stack>
#include <queue>
#include <limits.h>
#include "compoments.h"
using namespace std;

enum modeState{SINGLEMODE,DOUBLEMODE,AIBFS,AIBFSP};//模式：单人、双人、ai_bfs、ai_bfs_plus
enum mapState{BASIC,RANDOM}; //地图：基本、随机
enum gameState{NOTSTART,UNDERWAY,FINISH};//游戏：还没开始、正在进行、结束

class drawWidget : public QWidget
{
    Q_OBJECT
public:
    explicit drawWidget(QWidget *parent = nullptr);
    void initialize(modeState modestate,mapState mapstate);//游戏初始化
    bool eatFood(snake &sk,food &f); //蛇吃食物，若吃到了则返回true
    void moveSnake(snake &sk); //蛇移动
    void setGameOver();//设置游戏状态为结束
    bool bfs(snake sk,unit_block end);//生成bfs路径，若找到则为true
    bool canFindTail(snake sk);//可以找到从蛇头到蛇尾的一条路径
    bool available(snake sk,unit_block u);//判断是否是蛇或墙
    void followSnakeTail();//当能找到蛇尾并且找不到bfs路径或者虚拟蛇吃完食物后找不到蛇尾，就跟着蛇尾走(最远的一条路径)
    void wander();//如果找不到蛇尾，也找不到bfs路径，就dfs往较深的一步走
    int dfs(int sx,int sy);//求起点(坐标除以10)的最远路径，路径权值存在一个dp数组中
    void clearDp(){memset(dp,0,sizeof(dp));}//将dp清零

signals:
    void snake_1_eatFood();
    void snake_2_eatFood();
    void countDownSignal();
    void gameOver();
    void slow();

public slots:
    void updateGame();//对游戏内事件进行更新
    void setSpecialFoodActive();//设置特殊食物的状态为活跃
    void setSpecialFoodPositive();//设置特殊食物的状态为不存在
    void setSnakeNormal();//设置蛇1状态为反向
    void setSnake2Normal();

protected:
    void keyPressEvent(QKeyEvent *e)override;
    void paintEvent(QPaintEvent *event)override;//进行游戏画面绘制

public:
    mapOfGame map;
    snake snake_1;
    snake snake_2;
    food Food;
    food specialFood;//反方向键效果的食物
    QTimer *timer;
    QTimer *foodTimer;//每13秒产生反作用效果的食物

    gameState gameS=NOTSTART;
    modeState modeS=SINGLEMODE;
    mapState mapS=BASIC;

    QMessageBox msgBox;

    stack<unit_block> bfsPath;//ai自动寻路得到的路径
    QList<unit_block> headDir;//蛇头附近能找到蛇尾的方向位置

    int dp[43][43];//保存每个节点的可以到达的最远路径

};

#endif // DRAWWIDGET_H
