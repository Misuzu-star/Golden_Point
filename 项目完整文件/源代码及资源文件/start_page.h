#ifndef START_PAGE_H
#define START_PAGE_H

#include <QMainWindow>
#include "over_page.h"
#include "choose_page.h"

namespace Ui {
class start_page;
}

class start_page : public QMainWindow
{
    Q_OBJECT

public:
    explicit start_page(QWidget *parent = nullptr);
    choose_page *next_page;
    ~start_page();

private:
    Ui::start_page *ui;
};

#endif // START_PAGE_H
