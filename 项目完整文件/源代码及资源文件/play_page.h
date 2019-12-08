#ifndef PLAY_PAGE_H
#define PLAY_PAGE_H

#include <QMainWindow>
#include <QString>
#include <QLineEdit>
#include <QLabel>
#include "over_page.h"
#include "result.h"

namespace Ui {
class play_page;
}

class play_page : public QMainWindow
{
    Q_OBJECT

public:

    explicit play_page(QWidget *parent = nullptr,int Plarer_num=0,int Mode=0);
    void setting(int Player_num,int Mode);
    void addPlayer();
    void Calculate();
    void store();
    ~play_page();

private:
    Ui::play_page *ui;
    over_page *next_page;
    result *Result;
    int player_num=0;
    int mode=0;
    double G=0.0;
    int round=1;

    typedef  struct PLAYER{
        QString name;
        double point;
        int score = 0;
        int move = 0;
    } Player;
    Player *player;

    QLabel *label;
    QLineEdit *name;
    QLineEdit *point;
signals:
    void chooseBack();
    void return_top();
};
#endif // PLAY_PAGE_H
