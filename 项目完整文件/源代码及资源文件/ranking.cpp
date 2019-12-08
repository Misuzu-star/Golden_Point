#include "ranking.h"
#include "ui_ranking.h"
#include <QString>
#include <QFile>

ranking::ranking(QWidget *parent,int player_num,bool isEnd) :
    QDialog(parent),
    ui(new Ui::ranking)
{
    ui->setupUi(this);
    this->setFixedSize(300,390);
    this->setCursor(QCursor(QPixmap(":/res/arrow_1.cur"),0,0));

    QString *name = new QString[player_num];
    double point;
    int *score = new int[player_num];
    int *move = new int[player_num];

    QFile file("player.dat");
    file.open(QIODevice::ReadOnly);
    if(!file.isOpen()){
        this->close();
    }
    else{
        QDataStream out(&file);
        for(int i=0;i<player_num;i++){
            out >> *(name+i) >> point >> *(score+i) >> *(move+i);
        }

        for(int i=0;i<player_num-1;i++){
            for(int j=0;j<player_num-1-i;j++){
                if(score[j]<score[j+1]){
                    int t_score = score[j+1];
                    score[j+1] = score[j];
                    score[j] = t_score;
                    int t_move = move[j+1];
                    move[j+1] = move[j];
                    move[j] = t_move;
                    QString t_name = name[j+1];
                    name[j+1] = name[j];
                    name[j] = t_name;
                }
            }
        }

        for(int i=0;i<player_num;i++){
            if(*(name+i)=="")
                break;
            else{
                ui->tableWidget->item(i,0)->setText(name[i]);
                if(!isEnd)
                    ui->tableWidget->item(i,1)->setText(QString::number(move[i]));
                else{
                    QStringList header;
                    header<<"玩家"<<"--"<<"总分";
                    ui->tableWidget->setHorizontalHeaderLabels(header);
                }
                ui->tableWidget->item(i,2)->setText(QString::number(score[i]));
            }
        }
        file.close();
    }

}

ranking::~ranking()
{
    delete ui;
}
