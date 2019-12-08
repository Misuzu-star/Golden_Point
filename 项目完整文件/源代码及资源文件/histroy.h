#ifndef HISTROY_H
#define HISTROY_H

#include <QDialog>

namespace Ui {
class histroy;
}

class histroy : public QDialog
{
    Q_OBJECT

public:
    explicit histroy(QWidget *parent = nullptr,int round=0,int player_num=0);
    ~histroy();

private:
    Ui::histroy *ui;
};

#endif // HISTROY_H
