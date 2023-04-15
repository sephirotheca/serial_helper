#include "mychart.h"
#include <QDebug>
#include <QDateTime>
#include <QTimer>
#include <QPushButton>
#include "mainwindow.h"
#include <QLabel>
#include <QTextEdit>

MyChart::MyChart(QWidget *parent) : QWidget(parent)
{
    setFixedSize(800,600);
    setAttribute(Qt::WA_DeleteOnClose, true);

    //QTimer *timer = new QTimer(this);
    this->startTimer(10);

    //设置按钮
    QPushButton * btn1 = new QPushButton;
    btn1->setParent(this);
    btn1->move(600,510);
    btn1->setText("设置");
    QLabel * minLabel = new QLabel;
    minLabel->setParent(this);
    minLabel->setText("设置最小：");
    minLabel->move(000,518);
    QLabel * maxLabel = new QLabel;
    maxLabel->setParent(this);
    maxLabel->setText("设置最大：");
    maxLabel->move(300,518);

    QTextEdit * minEdit = new QTextEdit;
    minEdit->setParent(this);
    minEdit->setText("00.00");
    minEdit->setGeometry(80,510,150,25);
    QTextEdit * maxEdit = new QTextEdit;
    maxEdit->setParent(this);
    maxEdit->setText("10.00");
    maxEdit->setGeometry(380,510,150,25);

    QLabel * read = new QLabel;
    read->setParent(this);
    read->setText("##接收数据格式如‘3.14\\r3.15\\r’\r\n##默认更新频率100hz，可以接收文本格式的数值\r\n##有bug建议欢迎反馈QQ2576864971");
    read->move(30,538);




    // 设置轴坐标
    daxisX = new QDateTimeAxis;
    daxisX->setTickCount(30);  // 设置轴坐标网格数
    daxisX->setFormat("h:mm:ss");//"h:mm:ss"

    QDateTime xMin,xMax;// 设置时间坐标轴范围
    xMin = QDateTime::currentDateTime();
    xMax = xMin.addSecs(-10);
    daxisX->setRange(xMin,xMax);

    // 设置轴坐标
    QValueAxis * daxisY = new QValueAxis;
    daxisY->setRange(0, 10);//数值显示0~10
    daxisY->setTickCount(5);  // 设置轴坐标网格数
    daxisY->setLabelFormat("%f");

    QPen dpen;
    dpen.setWidth(1);
    dpen.setColor(Qt::red);

    //折线
    dseries = new QLineSeries;
    dseries->setPen(dpen);

    QChart * dchart = new QChart;
    dchart->addSeries(dseries);
    dchart->setTitle("坐标图");
    dchart->setAxisX(daxisX,dseries);
    dchart->setAxisY(daxisY,dseries);
    dchart->legend()->hide(); // 隐藏图例

    QChartView * dchartView = new QChartView(dchart,this);
    dchartView->setRenderHint(QPainter::Antialiasing);//抗锯齿
    dchartView->resize(800,500);
    dchartView->move(0,0);

    connect(btn1,&QPushButton::clicked,[=](){
        float min = minEdit->toPlainText().toFloat();
        float max = maxEdit->toPlainText().toFloat();
        daxisY->setRange(min, max);//设置纵坐标轴
    });
}

void MyChart::timerEvent(QTimerEvent *event)
{
    extern QByteArray recBuf;
    //qDebug()<<receive;
    //a++;
    //qreal temp = 5;

    static int i = 0;
    if(i++ == 10)
    {
        i = 0;
        //QString str = QString("timer%1").arg(a);
        //QString str = "TIM";
        //qDebug() << str;
    }

    QDateTime t(QDateTime::currentDateTime());
    //qDebug()<<randnumber;
    //dseries->append(t.toMSecsSinceEpoch(),(qrand()%10));
    QString receive = QString(recBuf).split("\r")[1];
    dseries->append(t.toMSecsSinceEpoch(),receive.toFloat());

    QDateTime xMax;// 设置时间坐标轴范围
    xMax = QDateTime::currentDateTime();

    if(xMax > daxisX->max())
    {
        QDateTime xMin;
        xMin = xMax.addSecs(qint64(-10));
        daxisX->setRange(xMin,xMax);
    }
}

