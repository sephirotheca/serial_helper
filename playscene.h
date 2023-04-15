#ifndef PLAYSCENE_H
#define PLAYSCENE_H

#include <QMainWindow>
#include "mycoin.h"

class PlayScene : public QMainWindow
{
    Q_OBJECT
public:
    //explicit PlayScene(QWidget *parent = nullptr);

    PlayScene(int levelNum);

    int levelIndex;//内部成员属性，记录所选关卡

    //重写paintevent绘图事件
    void paintEvent(QPaintEvent *);

    int gameArray[4][4];
    int isWin;

    MyCoin * coinBtn[4][4];

signals:
    void chooseSceneBack();
};

#endif // PLAYSCENE_H
