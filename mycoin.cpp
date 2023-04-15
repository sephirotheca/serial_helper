#include "mycoin.h"
#include <QDebug>
//MyCoin::MyCoin(QWidget *parent) : QPushButton(parent)
//{

//}

MyCoin::MyCoin(QString btnImg)
{
    QPixmap pix;
    bool ret = pix.load(btnImg);
    if(!ret)
    {
        qDebug()<<"图片加载失败";
        return;
    }

    this->setFixedSize(pix.width(),pix.height());
    this->setStyleSheet("QPushButton{border:0px;}");
    this->setIcon(pix);
    this->setIconSize(QSize(pix.width(),pix.height()));

    //初始化定时器对象
    timer1 = new QTimer(this);
    timer2 = new QTimer(this);

    //
    //监听正面翻反面的信号，并反转金币
    connect(timer1,&QTimer::timeout,[=](){
       QPixmap pix;
       QString str = QString(":/res/Coin000%1").arg(this->min++);
       pix.load(str);

       //设置按钮
       this->setFixedSize(pix.width(),pix.height());
       this->setStyleSheet("QPushButton{border:0px;}");
       this->setIcon(pix);
       this->setIconSize(QSize(pix.width(),pix.height()));

       //判断 如果翻完了，将min重置
       if(this->min > this->max)
       {
           this->min = 1;
           timer1->stop();
           isAnimation = false;
       }
    });


    //
    //监听反面翻正面的信号，并反转银币
    connect(timer2,&QTimer::timeout,[=](){
       QPixmap pix;
       QString str = QString(":/res/Coin000%1").arg(this->max--);
       pix.load(str);

       //设置按钮
       this->setFixedSize(pix.width(),pix.height());
       this->setStyleSheet("QPushButton{border:0px;}");
       this->setIcon(pix);
       this->setIconSize(QSize(pix.width(),pix.height()));

       //判断 如果翻完了，将max重置
       if(this->min > this->max)
       {
           this->max = 8;
           timer2->stop();
           isAnimation = false;
       }
    });
}

//改变正反面标志的方法
void MyCoin::changeFlag()
{
    //如果是正面 翻成反面
    if(this->flag)
    {
//        QString str = QString("翻转了金币");
//        qDebug()<<str;
        //开始翻正面的定时器
        timer1->start(30);
        isAnimation = true;
        this->flag = false;
    }
    else
    {
//        QString str = QString("翻转了银币");
//        qDebug()<<str;
        //开始翻反面的定时器
        timer2->start(30);
        isAnimation = true;
        this->flag = true;
    }
}

void MyCoin::mousePressEvent(QMouseEvent *e)
{
    if(this->isAnimation)
    {
        return;
    }
    else if(this->isWin==true)
    {
        return;
    }
    else
    {
        QPushButton::mousePressEvent(e);
    }

}
