//游戏基本组件：地图、蛇、食物
#ifndef COMPOMENTS_H
#define COMPOMENTS_H

#include <QList>
#include <QRandomGenerator>
#include <QDebug>

enum direction{UP,DOWN,LEFT,RIGHT}; //蛇运动的方向
enum snakeState{NORMAL,REVERSE};//蛇状态：正向、反向

struct unit_block{  //小正方形，边长为10
    int x;
    int y;
    unit_block(){}
    unit_block(int m,int n):x(m),y(n){}
    bool operator==(const unit_block &obj)const{
        if(x==obj.x&&y==obj.y) return true;
        else return false;
    }
};

class mapOfGame{
private:
    QList<unit_block> wall;

private:
    unit_block setWallBlocks(int x,int y);//用于随机生成墙的方块（上下左右随机生成）
    void optimization();//地图优化

public:
    mapOfGame(){}
    QList<unit_block> getWall(){return wall;}
    void setBasicMap(); //设置基本的四周的墙,横坐标0~420，纵坐标0~420
    void setRandomMap();//随机地图 
    void setAiMap();
    void setAiRandomMap();
};

class snake{
public:
    direction dir;
    QList <unit_block> body;
    snakeState sState=NORMAL;

private:
    void setRandomDir();//设置随机方向
    void setRandomHeadPos(mapOfGame map);//设置随机蛇头位置
    void setRandomHeadPos(snake sk,mapOfGame map);
    bool snakeHeadConflict(int x,int y,mapOfGame map);//判断蛇头是否与地图冲突

public:
    snake(){}
    ~snake(){body.clear();}
    void initializeSnake(mapOfGame map); //初始化蛇需要显式调用该函数
    void initializeSnake(snake sk,mapOfGame map);//初始化双人模式中的第二条蛇
    bool collision(mapOfGame map); //判断蛇头是否撞地图和撞自己
    bool collision(snake sk); //判断蛇头是否撞其他的蛇
};

class food{
public:
    unit_block position;

private:
    bool foodConflict(snake sk,mapOfGame map);//判断食物坐标是否和地图、蛇冲突

public:
    food(){}
    void initializeFood(snake sk,mapOfGame map); //需要显式调用该函数以初始化食物，设置食物坐标与地图和蛇都不冲突，单人模式
    void initializeFood(snake sk,snake sk2,mapOfGame map); //双人模式
    void initializeFood(snake sk,mapOfGame map,food f);//单人模式设置特殊食物
};

#endif // COMPOMENTS_H
