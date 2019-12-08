#include "over_page.h"
#include "ui_over_page.h"
#include "information.h"
#include "histroy.h"
#include "ranking.h"
#include <QTimer>
#include <QMovie>
#include <QTime>
#include <QMediaPlayer>
#include <QPropertyAnimation>

over_page::over_page(QWidget *parent,int Player_num,int Mode) :
    QMainWindow(parent),
    ui(new Ui::over_page)
{
    ui->setupUi(this);
    this->setFixedSize(720,450);
    this->setCursor(QCursor(QPixmap(":/res/arrow_1.cur"),0,0));
    ui->menubar->setCursor(QCursor(QPixmap(":/res/arrow_2.cur"),0,0));
    ui->menuhelp->setCursor(QCursor(QPixmap(":/res/arrow_2.cur"),0,0));
    ui->menustart->setCursor(QCursor(QPixmap(":/res/arrow_2.cur"),0,0));

    QMovie *back = new QMovie(":/res/back_ground.gif");
    ui->label_back->setMovie(back);
    back->start();

    ui->back->hide();
    ui->history->hide();
    ui->exit->hide();
    ui->score->hide();
    ui->label_text->hide();

    QMediaPlayer *music = new QMediaPlayer;
    music->setMedia(QUrl("qrc:/res/cheer.mp3"));
    music->setVolume(100);
    music->play();

    QPropertyAnimation *animation = new QPropertyAnimation(ui->label,"geometry");
    animation->setDuration(1200);
    animation->setStartValue(QRect(ui->label->x(),ui->label->y()+400,ui->label->width(),ui->label->height()));
    animation->setEndValue(QRect(ui->label->x(),ui->label->y(),ui->label->width(),ui->label->height()));
    animation->setEasingCurve(QEasingCurve::OutBounce);
    animation->start();

    qsrand(time_t(NULL));
    int *max = new int(3);
    int *count = new int(1);
    connect(ui->click,&QPushButton::clicked,[=](){
        QMovie *point_gif;
        if(*count<=*max){
            (*count)++;
            ui->label_text->hide();
            int point = qrand()%6+1;
            switch (point){
            case 1:
                point_gif = new QMovie(":/res/1.gif");
                ui->label_text->setText("排名末尾两位玩家给排名前三玩家各取一次快递！");break;
            case 2:
                point_gif = new QMovie(":/res/2.gif");
                ui->label_text->setText("排名末尾一位玩家单手做倒立动作！");break;
            case 3:
                point_gif = new QMovie(":/res/3.gif");
                ui->label_text->setText("排名末尾一位玩家请排名第一玩家喝一杯奶茶！");break;
            case 4:
                point_gif = new QMovie(":/res/4.gif");
                ui->label_text->setText("排名末尾一位玩家向其他玩家表演一段舞蹈！");break;
            case 5:
                point_gif = new QMovie(":/res/5.gif");
                ui->label_text->setText("排名末尾两位玩家互相拥抱安慰对方！");break;
            default:
                point_gif = new QMovie(":/res/6.gif");
                ui->label_text->setText("排名末尾两位玩家为前两名玩家按摩3分钟！");
            }
            ui->label_point->setMovie(point_gif);
            point_gif->start();
            sleep(1500);
            switch (*count) {
            case 2:
                ui->click->setText("再  抛  一  次");break;
            case 3:
                ui->click->setText("最  后  一  次");break;
            default:
                ui->click->hide();
            }
            ui->label_text->show();
        }
    });

    connect(ui->click_2,&QPushButton::clicked,[=](){
        ui->widget->hide();
        ui->back->show();
        ui->history->show();
        ui->exit->show();
        ui->score->show();
    });

    connect(ui->action_quit,&QAction::triggered,[=](){
        this->close();
    });
    connect(ui->action_rule,&QAction::triggered,[=](){
        information rule;
        rule.exec();
    });
    connect(ui->action_back,&QAction::triggered,[=](){
        this->close();
        emit this->return_top();
    });

    connect(ui->back,&QPushButton::clicked,[=](){
        QTimer::singleShot(300,[=](){
            this->close();
            emit this->return_top();
        });
    });
    connect(ui->exit,&QPushButton::clicked,[=](){
        QTimer::singleShot(300,[=](){
            this->close();
        });
    });
    connect(ui->history,&QPushButton::clicked,[=](){
        QTimer::singleShot(300,[=](){
            histroy his(nullptr,Mode+1,Player_num);
            his.exec();
        });
    });
    connect(ui->score,&QPushButton::clicked,[=](){
        QTimer::singleShot(300,[=](){
            ranking rank(nullptr,Player_num,true);
            rank.exec();
        });
    });
    connect(ui->score2,&QPushButton::clicked,[=](){
        QTimer::singleShot(300,[=](){
            ranking rank(nullptr,Player_num,true);
            rank.exec();
        });
    });
}

void over_page::sleep(int msec)
{
    QTime dieTime = QTime::currentTime().addMSecs(msec);
    while( QTime::currentTime() < dieTime )
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}

over_page::~over_page()
{
    delete ui;
}
