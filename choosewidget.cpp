#include "choosewidget.h"
#include "ui_choosewidget.h"

chooseWidget::chooseWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::chooseWidget)
{
    ui->setupUi(this);
    //设置图标
    this->setWindowIcon(QIcon(QPixmap(":/widget/picture/icon.jpg")));
    //设置背景
    QPalette pal;
    pal.setBrush(QPalette::Background,QBrush(QPixmap(":/history/picture/bg_history.png")));
    this->setPalette(pal);

    game=new gameWidget();
    game->hide();
    connect(this->ui->btn_return,SIGNAL(clicked(bool)),this,SLOT(returnPush()));
    connect(this->ui->btn_continue,SIGNAL(clicked(bool)),this,SLOT(continuePush()));
    connect(this->game,&gameWidget::returnSignal,this,&chooseWidget::reshow);
}

chooseWidget::~chooseWidget()
{
    delete ui;
}

void chooseWidget::returnPush(){
    emit returnSignal();
    this->hide();
}

void chooseWidget::continuePush(){
    this->hide();
    game->show();

    qDebug()<<"继续开始";
    if(this->ui->comboBox_mode->currentText()=="双人模式")
        this->game->setModeState(DOUBLEMODE);
    else if(this->ui->comboBox_mode->currentText()=="单人模式")
        this->game->setModeState(SINGLEMODE);
    else if(this->ui->comboBox_mode->currentText()=="ai(bfs)")
        this->game->setModeState(AIBFS);
    else  this->game->setModeState(AIBFSP);

    if(this->ui->comboBox_map->currentText()=="基本地图")//随机地图
        this->game->setMapState(BASIC);
    else this->game->setMapState(RANDOM);

    qDebug()<<"继续！";
}

void chooseWidget::reshow(){
    this->game->close();
    this->show();
}

