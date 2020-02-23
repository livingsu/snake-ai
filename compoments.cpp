#include "compoments.h"

//****************mapOfGame****************
void mapOfGame::setBasicMap(){ 
    wall.clear();
    for(int i=0;i<=420;i=i+10){
        unit_block w(i,0);
        wall.append(w);
    }
    for(int i=0;i<=420;i=i+10){
        unit_block w(i,420);
        wall.append(w);
    }
    for(int i=0;i<=420;i=i+10){
        unit_block w(0,i);
        wall.append(w);
    }
    for(int i=0;i<=420;i=i+10){
        unit_block w(420,i);
        wall.append(w);
    }
}
void mapOfGame::setRandomMap(){
    wall.clear();
    setBasicMap();
    int tmp=QRandomGenerator::global()->bounded(5)+20;//生成墙的数量
    for(int i=0;i<tmp;++i){
        int numOfBlocks=QRandomGenerator::global()->bounded(5)+10;
        unit_block u,tmp;
        u.x=QRandomGenerator::global()->bounded(41)*10+10;
        u.y=QRandomGenerator::global()->bounded(41)*10+10;
        wall.push_back(u);
        for(int j=0;j<numOfBlocks;++j){
            tmp=setWallBlocks(u.x,u.y);
            u=tmp;
            wall.push_back(tmp);
        }
    }
    for(int i=0;i<10;++i)
    optimization();
}

void mapOfGame::setAiMap(){
    wall.clear();
    setBasicMap();
    for(int i=10;i<=150;i=i+10){//i<=70
        for(int j=i;j<=420-i;j=j+10){
            unit_block u(j,i);
            wall.append(u);
        }
        for(int j=i;j<=420-i;j=j+10){
            unit_block u(j,420-i);
            wall.append(u);
        }
        for(int j=i;j<=420-i;j=j+10){
            unit_block u(i,j);
            wall.append(u);
        }
        for(int j=i;j<=420-i;j=j+10){
            unit_block u(420-i,j);
            wall.append(u);
        }
    }
}

void mapOfGame::setAiRandomMap(){
    wall.clear();
    setAiMap();
    int tmp=QRandomGenerator::global()->bounded(5)+10;//生成墙的数量
    for(int i=0;i<tmp;++i){
        int numOfBlocks=QRandomGenerator::global()->bounded(5)+8;
        unit_block u,tmp;
        u.x=QRandomGenerator::global()->bounded(28)*10+70;
        u.y=QRandomGenerator::global()->bounded(28)*10+70;
        wall.push_back(u);
        for(int j=0;j<numOfBlocks;++j){
            tmp=setWallBlocks(u.x,u.y);
            u=tmp;
            wall.push_back(tmp);
        }
    }
    for(int i=0;i<10;++i)
    optimization();
}

unit_block mapOfGame::setWallBlocks(int x, int y){
    int tmp=QRandomGenerator::global()->bounded(4);
    unit_block u;
    switch (tmp) {
    case 0:u.x=x; u.y=y+10;return u;
    case 1:u.x=x; u.y=y-10;return u;
    case 2:u.x=x+10; u.y=y;return u;
    default:u.x=x-10; u.y=y;return u;
    }
}

void mapOfGame::optimization(){
    for(int i=10;i<420;i=i+10){
        for(int j=10;j<420;j=j+10){
            unit_block left(i-10,j),right(i+10,j),up(i,j-10),down(i,j+10),it(i,j);
            if(wall.contains(left)&&wall.contains(right)&&wall.contains(up)&&!wall.contains(it)){//将三面都是墙而本身不是墙的方块设置为墙
                wall.append(it);
            }
            else if(wall.contains(left)&&wall.contains(right)&&wall.contains(down)&&!wall.contains(it)){
                wall.append(it);
            }
            else if(wall.contains(left)&&wall.contains(up)&&wall.contains(down)&&!wall.contains(it)){
                wall.append(it);
            }
            else if(wall.contains(right)&&wall.contains(up)&&wall.contains(down)&&!wall.contains(it)){
                wall.append(it);
            }
            else if(wall.contains(left)&&wall.contains(right)&&wall.contains(up)&&wall.contains(down)&&!wall.contains(it)){//将四面都是墙而本身不是墙的方块设置为墙
                wall.append(it);
            }
        }
    }
}

//****************snake****************
void snake::initializeSnake(mapOfGame map){
    body.clear();   
    setRandomDir();
    setRandomHeadPos(map);
}
void snake::initializeSnake(snake sk, mapOfGame map){
    body.clear();
    setRandomDir();
    setRandomHeadPos(sk,map);
}

void snake::setRandomDir(){
    int tmp=QRandomGenerator::global()->bounded(4);//生成随机方向
    switch (tmp) {
    case 0:dir=UP;break;
    case 1:dir=DOWN;break;
    case 2:dir=LEFT;break;
    case 3:dir=RIGHT;break;
    }
}
void snake::setRandomHeadPos(mapOfGame map){
    int x,y;
    do{
        x=QRandomGenerator::global()->bounded(41)*10+10;
        y=QRandomGenerator::global()->bounded(41)*10+10;
    }while(snakeHeadConflict(x,y,map));
    unit_block head(x,y);
    body.append(head);
}
void snake::setRandomHeadPos(snake sk, mapOfGame map){
    int x,y;
    do{
        x=QRandomGenerator::global()->bounded(41)*10+10;
        y=QRandomGenerator::global()->bounded(41)*10+10;
    }while(snakeHeadConflict(x,y,map)||(x==sk.body.front().x&&y==sk.body.front().y));
    unit_block head(x,y);
    body.append(head);
}
bool snake::snakeHeadConflict(int x,int y,mapOfGame map){
    for(auto i:map.getWall()){
        if(i.x==x&&i.y==y)return true;
    }
    return false;
}

bool snake::collision(mapOfGame map){
    if(snakeHeadConflict(body.front().x,body.front().y,map))
        return true;
    else if(body.length()>=2){
        QList<unit_block>::iterator i=body.begin();
        ++i;
        for(;i!=body.end();++i){
            if(i->x==body.begin()->x&&i->y==body.begin()->y)return true;
        }
        return false;
    }
    else return false;
}
bool snake::collision(snake sk){
    QList<unit_block>::iterator i=sk.body.begin();
    for(;i!=sk.body.end();++i){
        if(i->x==body.begin()->x&&i->y==body.begin()->y)
        {   return true; }
    }
    return false;
}

//****************food****************
void food::initializeFood(snake sk, mapOfGame map){
    position.x=QRandomGenerator::global()->bounded(41)*10+10;
    position.y=QRandomGenerator::global()->bounded(41)*10+10;
    if(foodConflict(sk,map)){
        initializeFood(sk,map);
    }
}

void food::initializeFood(snake sk, snake sk2, mapOfGame map){
    position.x=QRandomGenerator::global()->bounded(41)*10+10;
    position.y=QRandomGenerator::global()->bounded(41)*10+10;
    if(foodConflict(sk,map)||foodConflict(sk2,map)){
        initializeFood(sk,map);
    }
}
void food::initializeFood(snake sk, mapOfGame map, food f){
    position.x=QRandomGenerator::global()->bounded(41)*10+10;
    position.y=QRandomGenerator::global()->bounded(41)*10+10;
    if(foodConflict(sk,map)||(position.x==f.position.x&&position.y==f.position.y)){
        initializeFood(sk,map,f);
    }
}
bool food::foodConflict(snake sk, mapOfGame map){
    for(auto i:sk.body){
        if(i.x==position.x&&i.y==position.y)return true;
    }
    for(auto i:map.getWall()){
        if(i.x==position.x&&i.y==position.y)return true;
    }
    return false;
}
