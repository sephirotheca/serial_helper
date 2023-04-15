#ifndef SETWIDGET_H
#define SETWIDGET_H

#include <QWidget>

class SetWidget : public QWidget
{
    Q_OBJECT
public:
    explicit SetWidget(QWidget *parent = nullptr);
    int getSliderValue();
    ~SetWidget();

    int p = 0;

signals:
    void sliderChange();
};

#endif // SETWIDGET_H
