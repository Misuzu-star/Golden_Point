#ifndef OVER_PAGE_H
#define OVER_PAGE_H

#include <QMainWindow>
#include <QString>

namespace Ui {
class over_page;
}

class over_page : public QMainWindow
{
    Q_OBJECT

public:
    explicit over_page(QWidget *parent = nullptr,int Player_num=0,int Mode=0 );
    ~over_page();
    void sleep(int msec);

private:
    Ui::over_page *ui;
signals:
    void return_top();

};

#endif // OVER_PAGE_H
