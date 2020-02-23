#ifndef CHOOSEWIDGET_H
#define CHOOSEWIDGET_H

#include <QWidget>
#include <QComboBox>
#include <QRadioButton>
#include <gamewidget.h>
#include <QDebug>

namespace Ui {
class chooseWidget;
}

class chooseWidget : public QWidget
{
    Q_OBJECT

public:
    explicit chooseWidget(QWidget *parent = nullptr);
    ~chooseWidget();

signals:
    void returnSignal();

public slots:
    void returnPush();
    void continuePush();
    void reshow();

private:
    Ui::chooseWidget *ui;
    gameWidget *game;
};

#endif // CHOOSEWIDGET_H
