#ifndef G_TREND_H
#define G_TREND_H

#include <QDialog>
#include <QPaintEvent>
#include <QtGui>

namespace Ui {
class g_trend;
}

class g_trend : public QDialog
{
    Q_OBJECT

public:
    explicit g_trend(QWidget *parent = nullptr);
    void pain(double *value,double high,int count);
    void AddData(double *G,double value,int count);
    ~g_trend();
protected:
    void paintEvent(QPaintEvent *){
        QPainter painter(this);
        painter.drawImage(30,0,*image);
    }
private:
    Ui::g_trend *ui;
    QImage *image;

};

#endif // G_TREND_H
