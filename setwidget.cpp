#include "setwidget.h"
#include <QDebug>
#include <QSlider>
#include <QLabel>
#include "mainwindow.h"

SetWidget::SetWidget(QWidget *parent) : QWidget(parent)
{
    //设置固定大小
    setFixedSize(320,200);
    setWindowTitle("设置");
    //qDebug()<<"widget";

    QLabel * label1 = new QLabel;
    label1->setParent(this);
    label1->setText("设置不透明度(0~1)");
    label1->move(0,5);

    QSlider * slider = new QSlider;
    slider->setOrientation(Qt::Horizontal);
    slider->orientation();
    slider->setParent(this);
    slider->setGeometry(150,2,160,22);
    //slider->value()
    connect(slider,&QSlider::valueChanged,[=](){
        p = slider->value();
        emit sliderChange();
    });

}

int SetWidget::getSliderValue()
{
    return 0;
    //return slider.value
}

SetWidget::~SetWidget()
{

}
