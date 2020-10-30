#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include"rsimage.h"
#include<QMessageBox>
#include<QFileDialog>
#include<QLabel>
#include<qgraphicsitem.h>
#include<qgraphicsscene.h>
#include<qgraphicssceneevent.h>
#include"showdiv.h"
#include<QMouseEvent>
#include<QImage>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
protected:
    void mousePressEvent(QMouseEvent *event);
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    RSImage rs;

public slots:
    void LoadFile();
    void addNode();
    void run();

private:
    Ui::MainWindow *ui;
    QImage Mat2QImage(cv::Mat const& src);
    QGraphicsScene *pScence;
    QImage *img;
    int flag;
    QLabel* m_statusLabel;
    showdiv mydiv;
    QGraphicsPixmapItem *pixItem;
};

#endif // MAINWINDOW_H
