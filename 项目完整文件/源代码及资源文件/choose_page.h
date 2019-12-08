#ifndef CHOOSE_PAGE_H
#define CHOOSE_PAGE_H

#include <QMainWindow>
#include "play_page.h"

namespace Ui {
class choose_page;
}

class choose_page : public QMainWindow
{
    Q_OBJECT

public:
    explicit choose_page(QWidget *parent = nullptr);
    play_page *next_page;
    play_page *next;
    ~choose_page();

private:
    Ui::choose_page *ui;
signals:
    void return_top();
    void chooseBack();
};

#endif // CHOOSE_PAGE_H
