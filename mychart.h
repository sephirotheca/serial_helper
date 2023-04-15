#ifndef MYCHART_H
#define MYCHART_H

#include <QWidget>

// 包含line chart需要的头文件
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QValueAxis>
#include <QtCharts/QDateTimeAxis>
// 引用命名空间
QT_CHARTS_USE_NAMESPACE

class MyChart : public QWidget
{
    Q_OBJECT
public:
    explicit MyChart(QWidget *parent = nullptr);
    QChart * chart = NULL;
    QLineSeries * dseries = NULL;
    QDateTimeAxis * daxisX = NULL;

    void timerEvent(QTimerEvent *event);
signals:

};

#endif // MYCHART_H
