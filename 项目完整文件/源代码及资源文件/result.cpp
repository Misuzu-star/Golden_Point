#include "result.h"
#include "ui_result.h"
#include <QTimer>
#include <QMovie>
#include <QMediaPlayer>
#include <QPropertyAnimation>

result::result(QWidget *parent,QString name,double G_value) :
    QDialog(parent),
    ui(new Ui::result)
{
    ui->setupUi(this);
    this->setFixedSize(480,200);
    this->setCursor(QCursor(QPixmap(":/res/arrow_1.cur"),0,0));

    ui->line1->setText(name);
    ui->line1->setCursor(QCursor(QPixmap(":/res/text.cur"),-1,-1));
    ui->line2->setText(QString::number(G_value));
    ui->line2->setCursor(QCursor(QPixmap(":/res/text.cur"),-1,-1));

    QMovie *celebration = new QMovie(":/res/celebration.gif");
    ui->label->setMovie(celebration);
    celebration->start();

    QMediaPlayer *music = new QMediaPlayer;
    music->setMedia(QUrl("qrc:/res/cheer.mp3"));
    music->setVolume(100);
    music->play();

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

result::~result()
{
    delete ui;
}
