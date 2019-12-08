#include "play_page.h"
#include "ui_play_page.h"
#include "information.h"
#include "ranking.h"
#include "g_trend.h"
#include "histroy.h"
#include <QRegExpValidator>
#include <QRegExp>
#include <QGridLayout>
#include <QDialog>
#include <QFile>
#include <QTimer>
#include <QPropertyAnimation>
#include <QMovie>

play_page::play_page(QWidget *parent,int Player_num,int Mode) :
    QMainWindow(parent),
    ui(new Ui::play_page)
{
    ui->setupUi(this);
    this->setFixedSize(720,450);
    ui->scrollArea->setFixedSize(450,320);
    this->setCursor(QCursor(QPixmap(":/res/arrow_1.cur"),0,0));
    ui->menubar->setCursor(QCursor(QPixmap(":/res/arrow_2.cur"),0,0));
    ui->menuhelp->setCursor(QCursor(QPixmap(":/res/arrow_2.cur"),0,0));
    ui->menustart->setCursor(QCursor(QPixmap(":/res/arrow_2.cur"),0,0));
    ui->menulook->setCursor(QCursor(QPixmap(":/res/arrow_2.cur"),0,0));
    ui->line_G->setCursor(QCursor(QPixmap(":/res/text.cur"),-1,-1));

    QMovie *back = new QMovie(":/res/back_ground.gif");
    ui->label_back->setMovie(back);
    back->start();

    this->setting(Player_num,Mode);

    QPropertyAnimation *animation = new QPropertyAnimation(ui->label_round,"geometry");
    animation->setDuration(1200);
    animation->setStartValue(QRect(ui->label_round->x()-500,ui->label_round->y(),
                                   ui->label_round->width(),ui->label_round->height()));
    animation->setEndValue(QRect(ui->label_round->x(),ui->label_round->y(),
                                 ui->label_round->width(),ui->label_round->height()));
    animation->setEasingCurve(QEasingCurve::OutBack);
    animation->start();

    QFile file1("player.dat");
    QFile file2("round.dat");
    file1.open(QIODevice::WriteOnly);
    file2.open(QIODevice::WriteOnly);
    file1.close();
    file2.close();

    this->addPlayer();

    connect(ui->action_quit,&QAction::triggered,[=](){
        this->close();
    });

    connect(ui->action_back,&QAction::triggered,[=](){
        emit this->chooseBack();
    });

    connect(ui->action_trend,&QAction::triggered,[=](){
        g_trend trend;
        trend.exec();
    });

    connect(ui->action_rule,&QAction::triggered,[=](){
        information rule;
        rule.exec();
    });

    connect(ui->action_history,&QAction::triggered,[=](){
        histroy histroy_(nullptr,round,player_num);
        histroy_.exec();
    });

    connect(ui->action_score,&QAction::triggered,[=](){
        ranking rank(nullptr,player_num);
        rank.exec();
    });
    connect(ui->btn_show,&QPushButton::clicked,[=](){
        QTimer::singleShot(300,[=](){
            ranking rank(nullptr,player_num);
            rank.exec();
        });
    });

    ui->error->hide();
    connect(ui->calculate,&QPushButton::clicked,[=](){
        QTimer::singleShot(300,[=](){});
        bool can_cal = true;
        for(int i=0;i<player_num;i++){
            if((point+i)->text()==""||(name+i)->text()==""){
                can_cal=false;break;
            }
        }
        if(can_cal){
            ui->error->hide();
            this->Calculate();
            ++round;
            for(int i=0;i<player_num;i++){
                (name+i)->setReadOnly(true);
                (point+i)->setText("");
                if(round>mode){
                    (point+i)->setReadOnly(true);
                }
            }
            if(round<=mode){
                ui->label_round->setText(QString("回  合：%1").arg(round));
                animation->start();
            }
            else{
                ui->label_round->setText("回  合  结  束");
                ui->calculate->setText("下  一  步");
                connect(ui->calculate,&QPushButton::clicked,[=](){
                    QTimer::singleShot(200,[=](){});
                    this->hide();
                    next_page = new over_page(nullptr,Player_num,Mode);
                    next_page->show();
                    connect(next_page,&over_page::return_top,[=](){
                        this->close();
                        emit this->return_top();
                    });
                });
            }
        }
        else {
            ui->error->show();
        }
    });
}

void play_page::store(){
    QFile file1("player.dat");
    QFile file("round.dat");
    QFile file2("G_value.dat");
    file1.open(QIODevice::WriteOnly);
    file.open(QIODevice::WriteOnly|QIODevice::Append);
    file2.open(QIODevice::WriteOnly|QIODevice::Append);
    QDataStream out1(&file1);
    QDataStream out(&file);
    QDataStream out2(&file2);
    out<<this->G;
    for(int i=0;i<player_num;i++){
        out1<<(player+i)->name<<(player+i)->point<<(player+i)->score<<(player+i)->move;
        out<<(player+i)->name<<(player+i)->point;
    }
    out2 << this->G;
    file1.close();
    file.close();
    file2.close();
}

void play_page::Calculate(){
    for(int i=0;i<player_num;i++){
        (player+i)->name = (name+i)->text();
        (player+i)->point = (point+i)->text().toDouble();
    }
    double sum=0.0;
    for(int i=0;i<player_num;i++){
        sum+=(player+i)->point;
    }
    G = sum/player_num*0.618;
    ui->line_G->setText(QString::number(G));

    double Near = player->point;
    double Far=player->point;
    QString winner;

    for(int i=1;i<player_num;i++){
        Far = qAbs((player+i)->point-G)<qAbs(Far-G) ? Far:(player+i)->point;
        Near = qAbs(Near-G)<qAbs((player+i)->point-G)? Near:(player+i)->point;
    }
    for(int i=0;i<player_num;i++){
        if(qAbs(Near-(player+i)->point)<1e-5){
            (player+i)->score+=2;
            (player+i)->move=2;
            winner=(player+i)->name;
        }
        else if(qAbs(Far-(player+i)->point)<1e-5){
            (player+i)->score-=2;
            (player+i)->move=-2;
        }
        else
            (player+i)->move=0;
    }
    this->store();
    Result = new result(this,winner,G);
    Result->exec();
}

void play_page::addPlayer(){
    player = new Player[player_num];
    label = new QLabel[player_num];
    name = new QLineEdit[player_num];
    point = new QLineEdit[player_num];

    QRegExp regExp("\\d{0,2}[.]\\d{0,6}");

    QGridLayout *layout = new QGridLayout();
    for(int i=0;i<player_num;i++){
        (name+i)->setFixedHeight(30);
        (name+i)->setPlaceholderText("输入玩家昵称");
        (name+i)->setText(QString("player%1").arg(i+1));
        (name+i)->setStyleSheet("background-color: rgb(255, 255, 255);");
        (name+i)->setCursor(QCursor(QPixmap(":/res/text.cur"),-1,-1));
        (name+i)->setFont(QFont("Microsoft YaHei",11,50));

        (point+i)->setFixedHeight(30);
        (point+i)->setPlaceholderText("输入0-100的整数或小数");
        (point+i)->setValidator(new QRegExpValidator(regExp,this));
        (point+i)->setEchoMode(QLineEdit::PasswordEchoOnEdit);
        (point+i)->setStyleSheet("background-color: rgb(255, 255, 255);");
        (point+i)->setCursor(QCursor(QPixmap(":/res/text.cur"),-1,-1));
        (point+i)->setFont(QFont("Microsoft YaHei",11,50));

        (label+i)->setText(QString("玩家%1:").arg(i+1));
        (label+i)->setStyleSheet("color: rgb(255, 255, 255);");
        (label+i)->setFont(QFont("Microsoft YaHei",11,50));

        layout->addWidget(label+i,i,0);
        layout->addWidget(name+i,i,1);
        layout->addWidget(point+i,i,2);
    }
    ui->scrollArea->widget()->setLayout(layout);
}

void play_page::setting(int Player_num,int Mode){
    player_num=Player_num;
    mode=Mode;
}

play_page::~play_page()
{
    delete ui;
}
