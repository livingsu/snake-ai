#include "drawwidget.h"

drawWidget::drawWidget(QWidget *parent) : QWidget(parent)
{
    //设置图标
    this->setWindowIcon(QIcon(QPixmap(":/widget/picture/icon.jpg")));
    //设置背景
    QPalette pal;
    pal.setBrush(QPalette::Background,QBrush(QPixmap(":/history/picture/bg_history.png")));
    this->setPalette(pal);

    srand(time(NULL));
    this->timer=new QTimer;
    this->foodTimer=new QTimer;

    srand((unsigned)time(nullptr));
    //设置焦点在当前窗口并接受键盘事件
    setFocusPolicy(Qt::StrongFocus);

    msgBox.setIcon(QMessageBox::Critical);
    msgBox.setText("游戏结束！");
    msgBox.setStandardButtons(QMessageBox::Yes);
}

void drawWidget::initialize(modeState modestate,mapState mapstate){
    this->modeS=modestate;
    this->mapS=mapstate;

    qDebug()<<"游戏初始化"<<modestate<<" "<<mapstate;

    //地图设置
    if(mapstate==BASIC) map.setBasicMap();
    else map.setRandomMap();

    //单双人,ai模式设置
    snake_1.initializeSnake(map);
    if(modeS==SINGLEMODE){
        Food.initializeFood(snake_1,map);
        specialFood.initializeFood(snake_1,map,Food);
    }
    else if(modeS==DOUBLEMODE){
        snake_2.initializeSnake(snake_1,map);
        Food.initializeFood(snake_1,snake_2,map);
    }else {//ai模式
        //map.setAiMap();
        //if(mapS==RANDOM)map.setAiRandomMap();
        snake_1.initializeSnake(map);        
        Food.initializeFood(snake_1,map);//ai蛇是单人

    }
}

void drawWidget::keyPressEvent(QKeyEvent *e){
    if(snake_1.sState==NORMAL){
        if(e->key()==Qt::Key_Up){
            if(snake_1.dir==RIGHT||snake_1.dir==LEFT){
              snake_1.dir=UP;return;
            }
        }
        if(e->key()==Qt::Key_Down){
            if(snake_1.dir==RIGHT||snake_1.dir==LEFT){
              snake_1.dir=DOWN;return;
            }
        }
        if(e->key()==Qt::Key_Left){
            if(snake_1.dir==UP||snake_1.dir==DOWN){
              snake_1.dir=LEFT;return;
            }
        }
        if(e->key()==Qt::Key_Right){
            if(snake_1.dir==UP||snake_1.dir==DOWN){
              snake_1.dir=RIGHT;return;
            }
        }
    }
    else{
        if(e->key()==Qt::Key_Up){
            if(snake_1.dir==RIGHT||snake_1.dir==LEFT){
              snake_1.dir=DOWN;return;
            }
        }
        if(e->key()==Qt::Key_Down){
            if(snake_1.dir==RIGHT||snake_1.dir==LEFT){
              snake_1.dir=UP;return;
            }
        }
        if(e->key()==Qt::Key_Left){
            if(snake_1.dir==UP||snake_1.dir==DOWN){
              snake_1.dir=RIGHT;return;
            }
        }
        if(e->key()==Qt::Key_Right){
            if(snake_1.dir==UP||snake_1.dir==DOWN){
              snake_1.dir=LEFT;return;
            }
        }
    }
    if(modeS==DOUBLEMODE){
        if(snake_2.sState==NORMAL){
            if(e->key()==Qt::Key_W){
                if(snake_2.dir==RIGHT||snake_2.dir==LEFT){
                   snake_2.dir=UP;return;
                }
            }
            if(e->key()==Qt::Key_S){
                if(snake_2.dir==RIGHT||snake_2.dir==LEFT){
                   snake_2.dir=DOWN;return;
                }
            }
            if(e->key()==Qt::Key_A){
                if(snake_2.dir==UP||snake_2.dir==DOWN){
                   snake_2.dir=LEFT;return;
                }
            }
            if(e->key()==Qt::Key_D){
                if(snake_2.dir==UP||snake_2.dir==DOWN){
                   snake_2.dir=RIGHT;return;
                }
            }
        }
        else{
            if(e->key()==Qt::Key_W){
                if(snake_2.dir==RIGHT||snake_2.dir==LEFT){
                   snake_2.dir=DOWN;return;
                }
            }
            if(e->key()==Qt::Key_S){
                if(snake_2.dir==RIGHT||snake_2.dir==LEFT){
                   snake_2.dir=UP;return;
                }
            }
            if(e->key()==Qt::Key_A){
                if(snake_2.dir==UP||snake_2.dir==DOWN){
                   snake_2.dir=RIGHT;return;
                }
            }
            if(e->key()==Qt::Key_D){
                if(snake_2.dir==UP||snake_2.dir==DOWN){
                   snake_2.dir=LEFT;return;
                }
            }
        }
    }
}

void drawWidget::paintEvent(QPaintEvent *event){
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    if(gameS==UNDERWAY){
        painter.fillRect(0, 0, width(), height(), QGradient::JuicyCake);
        setFocus();
        QColor snakeColor(0,0,255),wallColor(0,0,0),foodColor(255,255,255);//蛇为蓝色，墙为黑色，食物为白色
        QRect rect;
        //画蛇1
        painter.setPen(Qt::black);
        for(auto i:snake_1.body){
            rect=QRect(i.x,i.y,10,10);
            painter.drawRect(rect);
            painter.fillRect(rect,snakeColor);
        }
        QColor snakeHead(255,0,0),snakeTail(0,255,0);//画ai蛇
        if(modeS==AIBFS||modeS==AIBFSP){
            rect=QRect(snake_1.body.front().x,snake_1.body.front().y,10,10);
            painter.drawRect(rect);
            painter.fillRect(rect,snakeHead);
            if(snake_1.body.length()>=2){
                rect=QRect(snake_1.body.back().x,snake_1.body.back().y,10,10);
                painter.drawRect(rect);
                painter.fillRect(rect,snakeTail);
            }
        }
        //画蛇2
        if(modeS==DOUBLEMODE){
            QColor snake_2_color(0,255,255);
            painter.setPen(snake_2_color);
            for(auto i:snake_2.body){
                rect=QRect(i.x,i.y,10,10);
                painter.drawRect(rect);
                painter.fillRect(rect,snake_2_color);
            }
        }
        //画墙
        painter.setPen(wallColor);
        for(auto i:map.getWall()){
            rect=QRect(i.x,i.y,10,10);
            painter.drawRect(rect);
            painter.fillRect(rect,wallColor);
        }
        //画正常食物
        painter.setPen(foodColor);
        rect=QRect(Food.position.x,Food.position.y,10,10);
        painter.drawRect(rect);
        painter.fillRect(rect,foodColor);

        //画特殊食物,为绿色
        QColor specialFoodColor(0,128,0);
        painter.setPen(specialFoodColor);
        if(modeS==SINGLEMODE){
            rect=QRect(specialFood.position.x,specialFood.position.y,10,10);
            painter.drawRect(rect);
            painter.fillRect(rect,specialFoodColor);
        }
        painter.end();
    }else if(gameS==FINISH){//游戏已经结束
        QPixmap pix;
        painter.translate(0,80);
        pix.load(":/game/picture/gameOver.jpg");
        painter.drawPixmap(0,0,pix.width(),pix.height(),pix);
    }
}

void drawWidget::setGameOver(){
    gameS=FINISH;
    update();
    timer->stop();
    emit gameOver();
    msgBox.exec();
}

void drawWidget::updateGame(){
        static long num=0;
        qDebug()<<"updateGame调用了"<<num<<"次";
        num++;

        if(modeS==SINGLEMODE){
            if(snake_1.collision(map))setGameOver();
            //吃正常食物加分
            if(eatFood(snake_1,Food)) {
                emit snake_1_eatFood();
                Food.initializeFood(snake_1,map);
            }
            //吃特殊食物，设置状态为反向,持续时间为5秒,并重新生成特殊食物
            if(eatFood(snake_1,specialFood)) {
                snake_1.sState=REVERSE;
                QTimer::singleShot(5000,this,SLOT(setSnakeNormal()));
                emit countDownSignal();
                specialFood.initializeFood(snake_1,map,Food);
            }

            //蛇移动
            moveSnake(snake_1);
        }
        else if(modeS==DOUBLEMODE){
            if(snake_1.collision(map)||snake_2.collision(map)||snake_1.collision(snake_2))setGameOver();
            //吃正常食物加分
            if(eatFood(snake_1,Food)){
                emit snake_1_eatFood();
                Food.initializeFood(snake_1,snake_2,map);
            }
            if(eatFood(snake_2,Food)){
                emit snake_2_eatFood();
                Food.initializeFood(snake_1,snake_2,map);
            }

            //蛇移动
            moveSnake(snake_1);
            moveSnake(snake_2);
        }
        else if(modeS==AIBFS){ //ai模式:bfs
            if(snake_1.collision(map)){
                setGameOver();
                return;
            }
            if(!bfs(snake_1,Food.position)){
               QMessageBox msgBox_2;
               msgBox_2.setIcon(QMessageBox::Critical);
               msgBox_2.setText("找不到bfs路径！");
               msgBox_2.setStandardButtons(QMessageBox::Yes);
               gameS=FINISH;
               emit gameOver();
               timer->stop();
               msgBox_2.exec();
               return;
            }
            else if(bfsPath.empty()){
                snake_1.body.push_front(Food.position);
                emit snake_1_eatFood();
                Food.initializeFood(snake_1,map);
            }
            else{
                snake_1.body.pop_back();
                snake_1.body.push_front(bfsPath.top());
                bfsPath.pop();
            }
        }
        else{//ai:bfs plus
            if(snake_1.collision(map)){
                setGameOver();
                return;
            }

            if(snake_1.body.length()==41*41-5)emit slow();

            //打印地图和蛇以便于判断哪个环节出了问题
            char Map[43][43];//0表示可以走，-1表示墙或者蛇
            for(int i=0;i<43;++i)
                for(int j=0;j<43;++j)
                    Map[i][j]='0';

            for(auto i:map.getWall())//坐标除以10转化为该二维数组的坐标
                Map[i.x/10][i.y/10]='#';
            for(auto i:snake_1.body)
                Map[i.x/10][i.y/10]='1';

            Map[snake_1.body.front().x/10][snake_1.body.front().y/10]='@';
            Map[snake_1.body.back().x/10][snake_1.body.back().y/10]='&';
            Map[Food.position.x/10][Food.position.y/10]='4';

            for(int i=15;i<=27;++i)
            qDebug()<<Map[i][15]<<Map[i][16]<<Map[i][17]<<Map[i][18]<<Map[i][19]<<
                      Map[i][20]<<Map[i][21]<<Map[i][22]<<Map[i][23]<<Map[i][24]<<
                      Map[i][25]<<Map[i][26]<<Map[i][27];


            snake virtualSnake; //虚拟蛇
            virtualSnake.initializeSnake(map);
            virtualSnake.body.clear();

            for(auto i:snake_1.body){
                unit_block tmp(i.x,i.y);
                virtualSnake.body.push_back(tmp);
            }

            if(bfs(snake_1,Food.position)){ //找到吃食物的路线
                //派虚拟蛇去吃食物
                qDebug()<<"找到吃食物的路径";

                stack<unit_block> tmpPath=bfsPath;

                while(!tmpPath.empty()){
                    virtualSnake.body.pop_back();
                    virtualSnake.body.push_front(tmpPath.top());
                    tmpPath.pop();
                }
                virtualSnake.body.push_front(Food.position);

                if(snake_1.body.length()==41*41-1){
                    snake_1.body.push_front(Food.position);
                    emit snake_1_eatFood();
                    gameS=FINISH;//设置游戏状态为结束
                    timer->stop();
                    emit gameOver();
                    QMessageBox msgBox1;
                    msgBox1.setIcon(QMessageBox::Critical);
                    msgBox1.setText("恭喜你！ai蛇吃满了！");
                    msgBox1.setStandardButtons(QMessageBox::Yes);
                    msgBox1.exec();
                    return;
                }else if(canFindTail(virtualSnake)){//若虚拟蛇吃完食物后可以找到自己的蛇尾,就派真蛇去吃
                    qDebug()<<"能找到蛇尾";
                    bfs(snake_1,Food.position);
                    if(bfsPath.empty()){
                        snake_1.body.push_front(Food.position);
                        emit snake_1_eatFood();           
                        Food.initializeFood(snake_1,map);
                    }
                    else {
                        snake_1.body.pop_back();
                        snake_1.body.push_front(bfsPath.top());
                        bfsPath.pop();
                    }
                }
                else if(canFindTail(snake_1)){
                    qDebug()<<"虚拟蛇吃完食物不能找到蛇尾:跟蛇尾";
                    followSnakeTail();
                }
                else {
                    qDebug()<<"虚拟蛇吃完食物不能找到蛇尾:wander";
                    wander();
                }
            }
            else if(canFindTail(snake_1)){
                qDebug()<<"没找到吃食物的路径:跟蛇尾";
                followSnakeTail();
            }
            else {
                qDebug()<<"没找到吃食物的路径:wander";
                wander();
            }
        }
}

bool drawWidget::eatFood(snake &sk,food &f){
    int headX=sk.body.front().x,headY=sk.body.front().y;
    int foodX=f.position.x,foodY=f.position.y;
    switch(sk.dir){   //吃食物
    case UP:
        if((headX==foodX)&&(headY==foodY+10)){
           sk.body.push_front(f.position);
           return true;
        }
        break;
    case DOWN:
        if((headX==foodX)&&(headY==foodY-10)){
            sk.body.push_front(f.position);
            return true;
        }
        break;
    case LEFT:
        if((headX==foodX+10)&&(headY==foodY)){
            sk.body.push_front(f.position);
            return true;
        }
        break;
    case RIGHT:
        if((headX==foodX-10)&&(headY==foodY)){
            sk.body.push_front(f.position);
            return true;
        }
        break;
    }
    return false;
}

void drawWidget::moveSnake(snake &sk){
    unit_block tmp=sk.body.back(),front=sk.body.front(); //蛇的移动
    sk.body.pop_back();
    switch (sk.dir) {
    case UP:    tmp.x=front.x;
                tmp.y=front.y-10;break;
    case DOWN:  tmp.x=front.x;
                tmp.y=front.y+10;break;
    case LEFT:  tmp.y=front.y;
                tmp.x=front.x-10;break;
    case RIGHT: tmp.y=front.y;
                tmp.x=front.x+10;break;
    }
    sk.body.push_front(tmp);
}

void drawWidget::setSpecialFoodActive(){
    QTimer::singleShot(8000,this,SLOT(setSpecialFoodPositive()));//食物持续存在的时间为8秒
}

void drawWidget::setSpecialFoodPositive(){
   // this->specialFood.fState=DISAPPEAR;
}

void drawWidget::setSnakeNormal(){
    this->snake_1.sState=NORMAL;
}

void drawWidget::setSnake2Normal(){
    this->snake_2.sState=NORMAL;
}

struct bfsNode{
    int prevx = 0;//保存前一个的坐标
    int prevy = 0;
    int price = 0;//权值,表示路径长度
};

bool drawWidget::bfs(snake sk,unit_block end){
    //首先清空path
    while(!bfsPath.empty()) {
        bfsPath.pop();
    }
    //将地图数字化为一个二维数组
    int bfsMap[43][43];//0表示可以走，-1表示墙或者蛇
    for(int i=0;i<43;++i)
        for(int j=0;j<43;++j)
            bfsMap[i][j]=0;

    for(auto i:map.getWall())//坐标除以10转化为该二维数组的坐标
        bfsMap[i.x/10][i.y/10]=-1;
    for(auto i:sk.body)
        bfsMap[i.x/10][i.y/10]=-1;

    //方向数组
    int dx[4] = { 1,0,-1,0 };
    int dy[4] = { 0,1,0,-1 };
    //建立一个保存前一个坐标的地图数组
    bfsNode bfsNodes[43][43];

    queue<unit_block>  que;
    unit_block Start((sk.body.front().x)/10,(sk.body.front().y)/10);
    unit_block End((end.x)/10,(end.y)/10);
    que.push(Start);
    while (!que.empty()) {
        unit_block cur = que.front();
        que.pop();
        for (int i = 0; i < 4; ++i) {
                int nx = cur.x + dx[i];
                int ny = cur.y + dy[i];
                unit_block curNext(nx, ny);
                if (0 < nx && nx < 43 && 0 < ny && ny < 43 && bfsMap[nx][ny] ==0) {                  
                    //第一次访问
                    if (bfsNodes[nx][ny].price == 0) {
                        que.push(curNext);
                        bfsNodes[nx][ny].price = bfsNodes[cur.x][cur.y] .price+ 1;
                        bfsNodes[nx][ny].prevx = cur.x;
                        bfsNodes[nx][ny].prevy = cur.y;
                    }
                    else {//第二次访问无需入队，只需更新最短路径
                        if (bfsNodes[nx][ny].price > bfsNodes[cur.x][cur.y].price + 1) {
                            bfsNodes[nx][ny].price = bfsNodes[cur.x][cur.y].price + 1;
                            bfsNodes[nx][ny].prevx = cur.x;
                            bfsNodes[nx][ny].prevy = cur.y;
                        }
                    }
                }
            }
            //若到达目的地，则回溯将路径储存起来，路径不包括蛇头和蛇尾
            if (cur.x == End.x && cur.y == End.y) {
                int x = End.x, y = End.y;
                int tmpx,tmpy;
                unit_block tmp;
                while (!(x==Start.x&&y==Start.y)) {
                    tmpx=x;
                    tmpy=y;
                    x = bfsNodes[tmpx][tmpy].prevx;
                    y=  bfsNodes[tmpx][tmpy].prevy;
                    if(!(x==Start.x&&y==Start.y)){ //排除蛇头
                        tmp.x = x*10;
                        tmp.y = y*10;
                        bfsPath.push(tmp);
                        //qDebug()<<"path:"<<tmp.x/10<<","<<tmp.y/10;
                    }
                }
                //qDebug()<<"bfs为真！！！";
                return true;
            }
        }
        //qDebug()<<"bfs为假！！！";
        return false;
}

bool drawWidget::canFindTail(snake sk){
    if(sk.body.length()==1)return true;
    headDir.clear();
    unit_block End(sk.body.back().x,sk.body.back().y);
    sk.body.pop_back();
    int dx[4] = { 1,0,-1,0 };
    int dy[4] = { 0,1,0,-1 };
    int possibleDir=0;
    for(int i=0;i<4;++i){
        unit_block Start(sk.body.front().x+10*dx[i],sk.body.front().y+10*dy[i]);
        if(available(sk,Start)){
            sk.body.push_front(Start);
            if(bfs(sk,End)){
                possibleDir++;
                headDir.append(Start);
            }
            sk.body.pop_front();
        }
    }
    if(possibleDir==0)return false;
    else return true;
}

bool drawWidget::available(snake sk,unit_block u){
    for(auto i:sk.body){
        if(u==i)return false;
    }
    for(auto i:map.getWall()){
        if(u==i)return false;
    }
    return true;
}

void drawWidget::followSnakeTail(){ 
    qDebug()<<"跟蛇尾:走离蛇尾最远的方向";

    int dis1,dis2,dis3;
    snake s1,s2,s3;
    for(auto i:snake_1.body)s1.body.push_back(i);
    unit_block End1=s1.body.back();
    s1.body.pop_back();

    for(auto i:snake_1.body) s2.body.push_back(i);
    unit_block End2=s2.body.back();
    s2.body.pop_back();

    for(auto i:snake_1.body) s3.body.push_back(i);
    unit_block End3=s3.body.back();
    s3.body.pop_back();

    if(headDir.length()==1){
        snake_1.body.push_front(headDir.first());
        snake_1.body.pop_back();
    }else if(headDir.length()==2){
        s1.body.push_front(headDir[0]);
        bfs(s1,End1);
        dis1=bfsPath.size();

        s2.body.push_front(headDir[1]);
        bfs(s2,End2);
        dis2=bfsPath.size();

        if(dis1>=dis2)snake_1.body.push_front(headDir[0]);
        else snake_1.body.push_front(headDir[1]);
        snake_1.body.pop_back();
    }else if(headDir.length()==3){
        s1.body.push_front(headDir[0]);
        bfs(s1,End1);
        dis1=bfsPath.size();

        s2.body.push_front(headDir[1]);
        bfs(s2,End2);
        dis2=bfsPath.size();

        s3.body.push_front(headDir[2]);
        bfs(s3,End3);
        dis3=bfsPath.size();

        if(dis1>=dis2&&dis1>=dis3)snake_1.body.push_front(headDir[0]);
        else if(dis2>=dis1&&dis2>=dis3)snake_1.body.push_front(headDir[1]);
        else if(dis3>=dis1&&dis3>=dis2)snake_1.body.push_front(headDir[2]);
        snake_1.body.pop_back();
    }
}

int drawWidget::dfs(int sx, int sy){
    int dfsMap[43][43];//0表示可以走，-1表示墙或者蛇
    for(int i=0;i<43;++i)
        for(int j=0;j<43;++j)
            dfsMap[i][j]=0;
    //坐标除以10转化为该二维数组的坐标
    for(auto i:map.getWall())dfsMap[i.x/10][i.y/10]=-1;
    for(auto i:snake_1.body)dfsMap[i.x/10][i.y/10]=-1;
    dfsMap[snake_1.body.front().x/10][snake_1.body.front().y/10]=0;
    //dfsMap[snake_1.body.back().x/10][snake_1.body.back().y/10]=0;//可走区域包括蛇头和蛇尾

    if (dp[sx][sy] > 0) return dp[sx][sy];
    dp[sx][sy] = 1;

    int dx[4] = { 0,1,0,-1 };
    int dy[4] = { 1,0,-1,0 };
    for (int i = 0; i < 4; ++i) {
        int nx = sx + dx[i], ny = sy + dy[i];
        if (nx > 0 && nx <43 && ny > 0 && ny <43&&dp[nx][ny]==0&&dfsMap[nx][ny]==0) {
            dp[sx][sy] = max(dp[sx][sy], dfs(nx, ny) + 1);
        }
    }
    return dp[sx][sy];
}

void drawWidget::wander(){
    qDebug()<<"autoMove!!";

    /*int dx[4] = { 1,0,-1,0 };
    int dy[4] = { 0,1,0,-1 };

    srand((unsigned)time(nullptr));
    int newPos[4]={0,1,2,3};
    for(int i=3;i>=0;--i){//生成0,1,2,3的随机排列，目的是随机选择一个可以走的位置走
        swap(newPos[rand()%(i+1)],newPos[i]);
    }

    for(int i=0;i<4;++i){
        unit_block newHead(snake_1.body.front().x+10*dx[newPos[i]],snake_1.body.front().y+10*dy[newPos[i]]);
        if(available(snake_1,newHead)){
            snake_1.body.push_front(newHead);
            snake_1.body.pop_back();
            return;
        }
    }
    gameS=FINISH;//设置游戏状态为结束
    timer->stop();
    emit gameOver();
    msgBox.exec();
    */

    qDebug()<<"dfs自动走";
    clearDp();
    dfs(snake_1.body.front().x/10,snake_1.body.front().y/10);

    for(int i=16;i<=26;++i){
    qDebug()<<dp[i][16]<<'\t'<<dp[i][17]<<'\t'<<dp[i][18]<<'\t'<<dp[i][19]<<'\t'<<dp[i][20]<<'\t'<<dp[i][21]<<'\t'<<dp[i][22]<<'\t'<<dp[i][23]<<'\t'<<dp[i][24]<<'\t'<<dp[i][25]<<'\t'<<dp[i][26]<<'\t';
    }

    int dx[4] = { 0,1,0,-1 };
    int dy[4] = { 1,0,-1,0 };

    for(int i=0;i<4;++i){
        unit_block new1(snake_1.body.front().x+10*dx[i],snake_1.body.front().y+10*dy[i]);
        if(available(snake_1,new1)&&(dp[new1.x/10][new1.y/10]+1==dp[snake_1.body.front().x/10][snake_1.body.front().y/10])){
            snake_1.body.push_front(new1);
            snake_1.body.pop_back();
            return;
        }
    }
    gameS=FINISH;//设置游戏状态为结束
    timer->stop();
    emit gameOver();
    msgBox.exec();
}
