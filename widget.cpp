#include "widget.h"
#include "ui_widget.h"

using namespace std;

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    //设置图标
    this->setWindowIcon(QIcon(QPixmap(":/widget/picture/icon.jpg")));
    //设置背景
    QPalette pal;
    pal.setBrush(QPalette::Background,QBrush(QPixmap(":/widget/picture/bg.jpg")));
    this->setPalette(pal);

    connect(this->ui->btn_start,SIGNAL(clicked(bool)),this,SLOT(startPush()));
    connect(this->ui->btn_exit,SIGNAL(clicked(bool)),this,SLOT(close()));

    choose=new chooseWidget();
    choose->hide();
    connect(choose,&chooseWidget::returnSignal,this,&Widget::show);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::closeEvent(QCloseEvent *event){
    QMessageBox msgBox;
    msgBox.setIcon(QMessageBox::Question);
    msgBox.setInformativeText("你想要退出游戏吗？");
    msgBox.setStandardButtons(QMessageBox::Yes|QMessageBox::No);
    int result=msgBox.exec();
    if(result==QMessageBox::No) event->ignore();
}

void Widget::startPush(){
    this->hide();
    choose->show();
}




