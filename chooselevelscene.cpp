#include "chooselevelscene.h"
#include <QMenuBar>
#include <QPixmap>
#include "mypushbutton.h"
#include <QDebug>
#include <QTimer>
#include <QLabel>
#include <QTimer>

ChooseLevelScene::ChooseLevelScene(QWidget *parent) : QMainWindow(parent)
{
//    QTimer *mTime = new QTimer;
//    connect(mTime,&QTimer::timeout,this,[=]()
//    {
//        qDebug()<<"choosslevelsence is existence";
//    });
//    mTime->start(100);




    setAttribute(Qt::WA_DeleteOnClose, true);
    //配置选择关卡场景
    this->setFixedSize(320,588);

    //设置图标
    this->setWindowIcon(QPixmap(":/res/Coin0001.png"));

    //设置标题
    this->setWindowTitle("休息一下吧");

    //创建菜单栏
    QMenuBar * bar = menuBar();
    setMenuBar(bar);

    //创建开始菜单
    QMenu * startMenu = bar->addMenu("开始");

    //创建退出 菜单项
    QAction * quitAction = startMenu->addAction("退出");

    //点击退出 实现退出游戏
    connect(quitAction,&QAction::triggered,[=](){
        this->close();
    });

    //返回按钮
    MyPushButton * backBtn = new MyPushButton(":/res/BackButton.png",":/res/BackButtonSelected.png");
    backBtn->setParent(this);
    backBtn->move(this->width()-backBtn->width(),this->height()-backBtn->height());

    //点击返回
    connect(backBtn,&MyPushButton::clicked,[=](){
        qDebug()<<"点击了返回按钮";

        //告诉主场景返回了，主场景监听chooseEventBack的返回按钮
        //延时返回
        QTimer::singleShot(10,this,[=](){
            emit this->chooseSenceBack();
        });
    });

    //创建关卡的按钮
    for(int i = 0;i<20;i++)
    {
        MyPushButton * menuBtn = new MyPushButton(":/res/LevelIcon.png");
        menuBtn->setParent(this);
        menuBtn->move(i%4*50+56,i/4*50+150);

        //监听每个按钮的点击事件
        connect(menuBtn,&MyPushButton::clicked,[=](){
            QString str = QString("您选择了第%1关").arg(i+1);
            qDebug()<<str;

            //播放选择关卡音效
            //

            //进入到游戏场景
            this->hide();//将选关场景隐藏
            play = new PlayScene(i+1);
            //设置游戏场景初始位置
            play->setGeometry(this->geometry());
            play->show();//显示游戏场景

            connect(play,&PlayScene::chooseSceneBack,[=](){
                this->setGeometry(play->geometry());
                this->show();
                play->hide();
                delete play;
                play=NULL;
            });
        });

        QLabel * label = new QLabel;
        label->setParent(this);
        label->setFixedSize(menuBtn->width(),menuBtn->height());
        label->setText(QString::number(i+1));
        label->move(i%4*50+55,i/4*50+148);

        //设置label上的文字对齐方式 水平居中和垂直居中
        label->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
        //设置让鼠标进行穿透
        label->setAttribute(Qt::WA_TransparentForMouseEvents);

    }
}


void ChooseLevelScene::paintEvent(QPaintEvent *)
{
    //加载背景
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/OtherSceneBg.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);

    //加载标题
    pix.load(":/res/Title.png");
    pix = pix.scaled(pix.width()*0.5,pix.height()*0.5);
    painter.drawPixmap(10,30,pix);
}

