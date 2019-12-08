#include "choose_page.h"
#include "ui_choose_page.h"
#include "information.h"
#include <QTimer>
#include <QRegExpValidator>
#include <QRegExp>
#include <QMovie>

choose_page::choose_page(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::choose_page)
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

    connect(ui->action_back,&QAction::triggered,[=](){
        emit this->chooseBack();
    });

    connect(ui->action_rule,&QAction::triggered,[=](){
        information rule;
        rule.exec();
    });
    connect(ui->action_quit,&QAction::triggered,[=](){
        this->close();
    });

    ui->input->setCursor(QCursor(QPixmap(":/res/text.cur"),-1,-1));
    ui->error->hide();
    QRegExp regExp("[0-9]\\d+");
    ui->input->setValidator(new QRegExpValidator(regExp,this));

    next_page = new play_page;

    connect(ui->btn1,&QPushButton::clicked,[=](){
        int player_num=ui->input->text().toInt();
        if(player_num>=2 && player_num<=20){
            QTimer::singleShot(300,[=](){
                this->hide();
                delete next_page;
                next_page = new play_page(nullptr,player_num,8);
                next=next_page;
                next_page->show();

                connect(next_page,&play_page::chooseBack,[=](){
                    next_page->close();
                    this->show();
                });
                connect(next_page,&play_page::return_top,[=](){
                    this->close();
                    emit this->return_top();
                });
            });
        }
        else
            ui->error->show();
    });
    connect(ui->btn2,&QPushButton::clicked,[=](){
        int player_num=ui->input->text().toInt();
        if(player_num>=2 && player_num<=20){
            QTimer::singleShot(300,[=](){
                this->hide();
                delete next_page;
                next_page = new play_page(nullptr,player_num,12);
                next_page->show();

                connect(next_page,&play_page::chooseBack,[=](){
                    next_page->hide();
                    this->show();
                });
            });

        }
        else
            ui->error->show();
    });
    connect(ui->btn3,&QPushButton::clicked,[=](){
        int player_num=ui->input->text().toInt();
        if(player_num>=2 && player_num<=20){
            QTimer::singleShot(300,[=](){
                this->hide();
                delete next_page;
                next_page = new play_page(nullptr,player_num,16);
                next_page->show();

                connect(next_page,&play_page::chooseBack,[=](){
                    next_page->hide();
                    this->show();
                });
            });
        }
        else
            ui->error->show();
    });
    connect(ui->btn4,&QPushButton::clicked,[=](){
        int player_num=ui->input->text().toInt();
        if(player_num>=2 && player_num<=20){
            QTimer::singleShot(300,[=](){
                this->hide();
                delete next_page;
                next_page = new play_page(nullptr,player_num,20);
                next_page->show();

                connect(next_page,&play_page::chooseBack,[=](){
                    next_page->hide();
                    this->show();
                });
            });
        }
        else
            ui->error->show();
    });
}

choose_page::~choose_page()
{
    delete ui;
}
