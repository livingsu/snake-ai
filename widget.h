//游戏的欢迎界面，是其他界面的父界面
#ifndef WIDGET_H
#define WIDGET_H

#include <QIcon>
#include <QPalette>
#include <QBrush>
#include <QPixmap>
#include <QPushButton>
#include <QDebug>
#include <QMessageBox>
#include <QWidget>
#include <QCloseEvent>
#include <choosewidget.h>

#include <compoments.h>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    void closeEvent(QCloseEvent *event)override;
    ~Widget();

private slots:
    void startPush();

private:
    Ui::Widget *ui;
    chooseWidget *choose;
};

#endif // WIDGET_H
