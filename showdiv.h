#ifndef SHOWDIV_H
#define SHOWDIV_H

#include <QDialog>
#include"rsimage.h"
#include"Kmean.h"
#include<QMessageBox>
#include<QFileDialog>
#include<QLabel>
#include<qgraphicsitem.h>
#include<qgraphicsscene.h>
#include<qgraphicssceneevent.h>

namespace Ui {
class showdiv;
}

class showdiv : public QDialog
{
    Q_OBJECT

public:
    explicit showdiv(QWidget *parent = 0);
    ~showdiv();
    void getdiv(Mat &img);

private:
    Ui::showdiv *ui;
    QImage Mat2QImage(cv::Mat const& src);
    QGraphicsScene *pScence;
};

#endif // SHOWDIV_H
