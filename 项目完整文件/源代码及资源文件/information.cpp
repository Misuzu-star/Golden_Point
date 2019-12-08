#include "information.h"
#include "ui_information.h"
#include <QTimer>
#include <QPropertyAnimation>

information::information(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::information)
{
    ui->setupUi(this);
    this->setCursor(QCursor(QPixmap(":/res/arrow_1.cur"),0,0));

    QPropertyAnimation *animation = new QPropertyAnimation(ui->next,"geometry");
    animation->setDuration(1200);
    animation->setStartValue(QRect(ui->next->x(),ui->next->y()-200,
                                   ui->next->width(),ui->next->height()));
    animation->setEndValue(QRect(ui->next->x(),ui->next->y(),
                                 ui->next->width(),ui->next->height()));
    animation->setEasingCurve(QEasingCurve::OutBounce);
    animation->start();

    connect(ui->next,&QPushButton::clicked,[=](){
        QTimer::singleShot(300,[=](){
            this->close();
        });
    });
}

information::~information()
{
    delete ui;
}
