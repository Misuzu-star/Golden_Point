#include "mybutton.h"
#include <QPropertyAnimation>
#include <QMediaPlayer>
#include <QTimer>

MyButton::MyButton(QWidget *parent) : QPushButton(parent)
{
    this->setStyleSheet("QPushButton{border-image:url(:/res/btn.png);}"
        "QPushButton:hover{border-image:url(:/res/btn_pressed.png);}"
        "QPushButton:pressed{border-image:url(:/res/btn_hover.png);}");

    connect(this,&QPushButton::clicked,[=](){
        QMediaPlayer *music = new QMediaPlayer;
        music->setMedia(QUrl("qrc:/res/click.mp3"));
        music->setVolume(100);
        music->play();
        this->Up();
        this->Down();
    });
}

void MyButton::Up(){
    QPropertyAnimation *animation = new QPropertyAnimation(this,"geometry");
    animation->setDuration(200);
    animation->setStartValue(QRect(this->x(),this->y(),this->width(),this->height()));
    animation->setEndValue(QRect(this->x(),this->y()-5,this->width(),this->height()));
    animation->setEasingCurve(QEasingCurve::OutBounce);
    animation->start();
}
void MyButton::Down(){
    QPropertyAnimation *animation = new QPropertyAnimation(this,"geometry");
    animation->setDuration(200);
    animation->setStartValue(QRect(this->x(),this->y()-5,this->width(),this->height()));
    animation->setEndValue(QRect(this->x(),this->y(),this->width(),this->height()));
    animation->setEasingCurve(QEasingCurve::OutBounce);
    animation->start();
}
