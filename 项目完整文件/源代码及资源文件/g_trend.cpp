#include "g_trend.h"
#include "ui_g_trend.h"
#include <QFile>
#include <QTimer>
#include <QDebug>
#include <QPropertyAnimation>

g_trend::g_trend(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::g_trend)
{
    ui->setupUi(this);
    this->setFixedSize(540,360);
    this->setCursor(QCursor(QPixmap(":/res/arrow_1.cur"),0,0));

    QPropertyAnimation *animation = new QPropertyAnimation(ui->next,"geometry");
    animation->setDuration(1200);
    animation->setStartValue(QRect(ui->next->x(),ui->next->y()-300,
                                   ui->next->width(),ui->next->height()));
    animation->setEndValue(QRect(ui->next->x(),ui->next->y(),
                                 ui->next->width(),ui->next->height()));
    animation->setEasingCurve(QEasingCurve::OutBounce);
    animation->start();

    double G[10]={0,0,0,0,0,0,0,0,0,0};
    double high=0;
    int count=0;

    QFile file("G_value.dat");
    file.open(QIODevice::ReadOnly);
    QDataStream in(&file);
    if(!file.isOpen()){
        this->close();
    }
    else{
        double value;
        while(!file.atEnd()){
            in >> value;
            count++;
            this->AddData(G,10*value,count);
        }
        file.close();
        high=G[0];
        for(int i=1;i<10;i++){
            high = high>G[i]? high:G[i];
        }
        count = count<=10? count:10;
    }
    this->pain(G,high,count);

    connect(ui->next,&QPushButton::clicked,[=](){
        QTimer::singleShot(300,[=](){
            this->close();
        });
    });
}

void g_trend::AddData(double *G,double value,int count){
    if(count<=10){
        G[count-1]=value;
    }
    else{
        for(int i=1;i<10;i++){
            G[i-1]=G[i];
        }
        G[9]=value;
    }
}

void g_trend::pain(double *value,double high,int count){
    image = new QImage(480,300,QImage::Format_RGB32);
    QColor backColor = qRgb(176,196,222);//淡钢蓝
    image->fill(backColor);
    QPainter painter(image);
    painter.setRenderHint(QPainter::Antialiasing,true);
    int pointx=35, pointy=280;
    int width=460-pointx,height=260;

    painter.drawLine(pointx,pointy,width+pointx,pointy);
    painter.drawLine(pointx,pointy,pointx,pointy-height);

    double _maStep=high/10;
    for(int i=0;i<10;i++){
        painter.drawLine(pointx+i*width/10.0,pointy,pointx+i*width/10.0,pointy-3);
        painter.drawText(pointx+i*width/10,pointy+10,QString::number(i+1));

        painter.drawLine(pointx,pointy-i*height/10,width+pointx,pointy-i*height/10);
        painter.drawText(pointx-25,pointy-i*height/10,QString::number(double(_maStep*i/10.0),'f',2));
    }
    painter.drawText(pointx-25,pointy-height,QString::number(double(_maStep),'f',2));
    painter.drawLine(pointx,pointy-height,width+pointx,pointy-height);

    QPen pen,penPoint;
    pen.setColor(Qt::red);
    pen.setWidth(2);
    penPoint.setColor(Qt::blue);
    penPoint.setWidth(5);

    double kx=double(width/10);
    double ky=double(height/high);

    for(int i=0;i<count-1;i++)
        {
            painter.setPen(pen);
            painter.drawLine(pointx+kx*i,pointy-value[i]*ky,pointx+kx*(i+1),pointy-value[i+1]*ky);
            painter.setPen(penPoint);
            painter.drawPoint(pointx+kx*i,pointy-value[i]*ky);
        }
    painter.setPen(penPoint);
    painter.drawPoint(pointx+kx*(count-1),pointy-value[count-1]*ky);

}

g_trend::~g_trend()
{
    delete ui;
}
