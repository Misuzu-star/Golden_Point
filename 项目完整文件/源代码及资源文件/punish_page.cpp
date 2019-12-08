#include "punish_page.h"
#include "ui_punish_page.h"

punish_page::punish_page(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::punish_page)
{
    ui->setupUi(this);
}

punish_page::~punish_page()
{
    delete ui;
}
