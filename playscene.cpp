#include "playscene.h"
#include <QDebug>
#include <QMenuBar>
#include <QPainter>
#include "mypushbutton.h"
#include <QTimer>
#include <QLabel>
#include "mycoin.h"
#include "dataconfig.h"
#include <QPropertyAnimation>

//PlayScene::PlayScene(QWidget *parent) : QMainWindow(parent)
//{

//}

PlayScene::PlayScene(int levelNum)
{
//    QTimer *mTime = new QTimer;
//    connect(mTime,&QTimer::timeout,this,[=]()
//    {
//        qDebug()<<"playsence is existence";
//    });
//    mTime->start(100);

    setAttribute(Qt::WA_DeleteOnClose, true);
    QString str = QString("进入了第%1关").arg(levelNum);
    qDebug()<<str;
    this->levelIndex = levelNum;

    //初始化游戏场景
    //设置固定大小
    this->setFixedSize(320,588);
    //设置图标
    this->setWindowIcon(QPixmap(":/res/Coin0001.png"));
    //设置标题
    this->setWindowTitle("翻金币小游戏");
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
            qDebug()<<"翻金币场景点击了返回按钮";
            emit this->chooseSceneBack();
        });

    });

    //显示当前关卡数
    QLabel * label = new QLabel;
    label->setParent(this);
    QFont font;
    font.setFamily("华文新魏");
    font.setPointSize(16);
    //将字体设置到标签控件中
    label->setFont(font);
    QString str2 = QString("Level: %1").arg(this->levelIndex);
    //label->setText(QString::number(this->levelIndex));
    label->setText(str2);
    label->setGeometry(30,this->height()-50,120,50);


    //初始化每个关卡的二维数组
    dataConfig config;
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<4;j++)
        {
            this->gameArray[i][j]=config.mData[this->levelIndex][i][j];
        }
    }



    //胜利图片显示
    QLabel * winLabel = new QLabel;
    QPixmap tmpPix;
    tmpPix.load(":/res/LevelCompletedDialogBg.png") ;
    winLabel->setGeometry(0,0,tmpPix.width(),tmpPix.height());
    winLabel->setPixmap (tmpPix) ;
    winLabel->setParent (this) ;
    winLabel->move(this->width()*0.5-tmpPix.width()*0.5,-tmpPix.height());





    //显示金币背景图案
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<4;j++)
        {
            //绘制背景图
            QPixmap pix = QPixmap(":/res/BoardNode.png");
            QLabel *label = new QLabel;
            label->setGeometry (0,0,pix.width () ,pix.height());
            label->setPixmap (pix) ;
            label->setParent (this);
            label->move(57+i*50,200+j*50);

            //创建金币
            QString str;
            if(this->gameArray[i][j]==1)
            {
                //显示金币
                str = ":/res/Coin0001.png";
            }
            else
            {
                str = ":/res/Coin0008.png";
            }
            MyCoin * coin = new MyCoin(str);
            coin->setParent(this);
            coin->move(59+i*50,204+j*50);

            //给金币属性赋值
            coin->posX = i;
            coin->posY = j;
            coin->flag = this->gameArray[i][j];

            //将金币放入到金币的二维数组
            coinBtn[i][j] = coin;


            //点击金币 进行翻转
            connect(coin,&MyCoin::clicked,[=](){
                //coin->changeFlag();
                emit coin->changeFlag();
                this->gameArray[i][j] = !gameArray[i][j];
                //qDebug()<<this->gameArray[i][j];

                //翻转周围金币
                QTimer::singleShot(200,this,[=](){
                    if(0<=i-1 && i-1<4)//(i-1,j)
                    {
                        emit coinBtn[i-1][j]->changeFlag();
                        this->gameArray[i-1][j] = !gameArray[i-1][j];
                    }
                    if(0<=i+1 && i+1<4)
                    {
                        emit coinBtn[i+1][j]->changeFlag();
                        this->gameArray[i+1][j] = !gameArray[i+1][j];
                    }
                    if(0<=j-1 && j-1<4)
                    {
                        emit coinBtn[i][j-1]->changeFlag();
                        this->gameArray[i][j-1] = !gameArray[i][j-1];
                    }
                    if(0<=j+1 && j+1<4)
                    {
                        emit coinBtn[i][j+1]->changeFlag();
                        this->gameArray[i][j+1] = !gameArray[i][j+1];
                    }


                    //判断是否胜利
                    isWin = 0;
                    for(int i=0;i<4;i++)
                    {
                        for(int j=0;j<4;j++)
                        {
                            isWin+=this->gameArray[i][j];
                        }
                    }
                    if(isWin==16)
                    {
                        qDebug()<<"WIN!";
                        for(int i=0;i<4;i++)
                        {
                            for(int j=0;j<4;j++)
                            {
                                coinBtn[i][j]->isWin=true;
                            }
                        }

                        //将胜利的图片移动下来
                        QPropertyAnimation * animation = new QPropertyAnimation(winLabel,"geometry");
                        //设置时间间隔
                        animation->setDuration(1000);
                        //设置开始位置
                        animation->setStartValue(QRect(winLabel->x(),winLabel->y(),winLabel->width(),winLabel->height()));
                        //设置结束位置
                        animation->setEndValue(QRect(winLabel->x(),winLabel->y()+178,winLabel->width(),winLabel->height()));
                        //设置缓和曲线
                        animation->setEasingCurve(QEasingCurve::OutBounce);
                        //执行动画
                        animation->start();
                    }

                });
            });
        }
    }
}

void PlayScene::paintEvent(QPaintEvent *)
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
