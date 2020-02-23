#include "gamewidget.h"
#include "ui_gamewidget.h"

static QTimer *timer=new QTimer;
static int countNum;//倒计时的数字

gameWidget::gameWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::gameWidget)
{
    ui->setupUi(this);

    //设置图标
    this->setWindowIcon(QIcon(QPixmap(":/widget/picture/icon.jpg")));
    //设置背景
    QPalette pal;
    pal.setBrush(QPalette::Background,QBrush(QPixmap(":/history/picture/bg_history.png")));
    this->setPalette(pal);

    srand(time(NULL));

    connect(this->ui->btn_return,SIGNAL(clicked(bool)),this,SLOT(returnPush()));
    connect(this->ui->btn_start,SIGNAL(clicked(bool)),this,SLOT(startPush()));

    this->myDrawWidget=new drawWidget(this);
    myDrawWidget->setParent(this);
    myDrawWidget->setFixedSize(430,430);
    myDrawWidget->move(10,10);

    //设置加分
    connect(this->myDrawWidget,&drawWidget::snake_1_eatFood,this,&gameWidget::addScore_1);
    connect(this->myDrawWidget,&drawWidget::snake_2_eatFood,this,&gameWidget::addScore_2);

    //设置倒计时功能
    connect(this->myDrawWidget,&drawWidget::countDownSignal,this,&gameWidget::countDown);

    connect(this->myDrawWidget,SIGNAL(gameOver()),this,SLOT(setInitial()));
    //倒计时连接
    connect(timer,SIGNAL(timeout()),this,SLOT(lcdFoodDisplay()));

    this->myDrawWidget->installEventFilter(this);

    connect(this->myDrawWidget->timer,SIGNAL(timeout()),this->myDrawWidget,SLOT(update()));
    connect(this->myDrawWidget->timer,SIGNAL(timeout()),this->myDrawWidget,SLOT(updateGame()));
    connect(this->myDrawWidget->foodTimer,SIGNAL(timeout()),this->myDrawWidget,SLOT(setSpecialFoodActive()));
    //背景音乐
    /*player = new QMediaPlayer;
    player->setMedia(QUrl::fromLocalFile("D:\\11638.wav"));
    player->setVolume(50);
*/
    connect(this->myDrawWidget,&drawWidget::slow,this,&gameWidget::setSlow);
}

gameWidget::~gameWidget()
{
    delete ui;
}

void gameWidget::returnPush(){
    emit returnSignal();
    this->myDrawWidget->timer->stop();
    this->myDrawWidget->gameS=NOTSTART;
    this->setInitial();
    this->close();
}

void gameWidget::startPush(){
    qDebug()<<"按下开关！";
    this->ui->btn_start->setEnabled(false);
    this->myDrawWidget->initialize(modeS,mapS);//游戏窗口初始化

    //player->play();

    this->myDrawWidget->gameS=UNDERWAY;
    if(this->modeS==AIBFS||this->modeS==AIBFSP)this->myDrawWidget->timer->start(8);
    else this->myDrawWidget->timer->start(100);
    if(modeS==SINGLEMODE)this->myDrawWidget->foodTimer->start(13000);//13秒出现一次特殊食物
}


void gameWidget::setInitial(){
    //player->stop();
    this->myDrawWidget->foodTimer->stop();
    this->ui->btn_start->setEnabled(true);
    this->score_1=0;
    this->score_2=0;
    this->ui->lcd_player1->display(score_1);
    this->ui->lcd_player1->display(score_1);
}

void gameWidget::addScore_1(){
    score_1+=1;
    this->ui->lcd_player1->display(score_1);
}

void gameWidget::addScore_2(){
    score_2+=1;
    this->ui->lcd_player2->display(score_2);
}

void gameWidget::countDown(){
    timer->start(1000);
    countNum=4;
}

void gameWidget::lcdFoodDisplay(){
    if(countNum>0){
       this->ui->lcd_food->display(countNum);
       qDebug()<<"lcd倒计时显示在显示屏上";
       countNum--;
    }
    else {
        this->ui->lcd_food->display(0);
        timer->stop();
    }
}

bool gameWidget::eventFilter(QObject *watched, QEvent *event){
    if(watched==myDrawWidget){
        if(myDrawWidget->modeS==AIBFS&&event->type()==QEvent::KeyPress)
         return true;
        else return false;
    }
    else return QWidget::eventFilter(watched,event);
}

void gameWidget::setSlow(){
    this->myDrawWidget->timer->start(30);
}
