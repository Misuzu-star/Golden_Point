#include "histroy.h"
#include "ui_histroy.h"
#include <QFile>
#include <QString>
#include <QTimer>
#include <QPropertyAnimation>

histroy::histroy(QWidget *parent,int round,int player_num) :
    QDialog(parent),
    ui(new Ui::histroy)
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


    connect(ui->next,&QPushButton::clicked,[=](){
        QTimer::singleShot(300,[=](){
            this->close();
        });
    });

    QString name;
    double G;
    double point;

    QFile file("round.dat");
    file.open(QIODevice::ReadOnly);
    QDataStream in(&file);
    for(int i=0;i<round-1;i++){
        QTreeWidgetItem *Litem = new QTreeWidgetItem(QStringList()<<QString("第%1回合").arg(i+1));
        ui->treeWidget->addTopLevelItem(Litem);
        QTreeWidgetItem *player = new QTreeWidgetItem(QStringList()<<"玩家");
        in >> G;
        QTreeWidgetItem *G_value = new QTreeWidgetItem(QStringList()<<"G值"<<QString::number(G));
        Litem->addChild(G_value);
        Litem->addChild(player);
        for(int j=0;j<player_num;j++){
            in >> name >> point;
            QTreeWidgetItem *L = new QTreeWidgetItem(QStringList()<<name<<QString::number(point));
            player->addChild(L);
        }
    }
}

histroy::~histroy()
{
    delete ui;
}
