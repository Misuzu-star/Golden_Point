#include "start_page.h"
#include "ui_start_page.h"
#include "information.h"
#include <QTimer>
#include "g_trend.h"
#include <QMediaPlaylist>
#include <QMediaPlayer>
#include <QMovie>

start_page::start_page(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::start_page)
{
    ui->setupUi(this);
    this->setFixedSize(720,450);
    this->setCursor(QCursor(QPixmap(":/res/arrow_1.cur"),0,0));
    ui->menuBar->setCursor(QCursor(QPixmap(":/res/arrow_2.cur"),0,0));
    ui->menuhelp->setCursor(QCursor(QPixmap(":/res/arrow_2.cur"),0,0));
    ui->menustart->setCursor(QCursor(QPixmap(":/res/arrow_2.cur"),0,0));

    static int click = 1;

    QMediaPlaylist *list = new QMediaPlaylist;
    list->addMedia(QUrl("qrc:/res/bgm.mp3"));
    list->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);
    QMediaPlayer *music = new QMediaPlayer;
    music->setPlaylist(list);
    music->setVolume(100);
    music->play();

    QMovie *back = new QMovie(":/res/back_ground.gif");
    ui->label->setMovie(back);
    back->start();

    connect(ui->voice,&QPushButton::clicked,[=](){
        if(click==1){
            ui->voice->setStyleSheet("border-image: url(:/res/turn_on.png);");
            music->stop();
        }
        else{
            ui->voice->setStyleSheet("border-image: url(:/res/turn_off.png);");
            music->play();
        }
        click = click^3;
    });

    connect(ui->action_quit,&QAction::triggered,[=](){
        this->close();
    });

    connect(ui->action_rule,&QAction::triggered,[=](){
        information rule;
        rule.exec();
    });

    connect(ui->rules,&QPushButton::clicked,[=](){
        QTimer::singleShot(300,[=](){
            information rule;
            rule.exec();
        });

    });

    connect(ui->exit,&QPushButton::clicked,[=](){
        QTimer::singleShot(300,[=](){
            this->close();
        });
    });

    connect(ui->trend,&QPushButton::clicked,[=](){
        QTimer::singleShot(300,[=](){
            g_trend trend;
            trend.exec();
        });
    });

    connect(ui->start,&QPushButton::clicked,[=](){
        next_page = new choose_page;
        QTimer::singleShot(300,[=](){
            this->hide();
            next_page->show();
        });

        connect(next_page,&choose_page::chooseBack,[=](){
            QTimer::singleShot(100,[=](){
                next_page->hide();
                this->show();
            });
        });

        connect(next_page,&choose_page::return_top,[=](){
            this->show();
        });

    });
}

start_page::~start_page()
{
    delete ui;
}
