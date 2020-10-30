#include "showdiv.h"
#include "ui_showdiv.h"

showdiv::showdiv(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::showdiv)
{
    ui->setupUi(this);
}

showdiv::~showdiv()
{
    delete ui;
}

void showdiv::getdiv(Mat &img)
{
    pScence = new QGraphicsScene;
    QPixmap pix = QPixmap::fromImage(Mat2QImage(img));
    QGraphicsPixmapItem *pixItem = new QGraphicsPixmapItem(pix);
    pScence->addItem(pixItem);
    ui->graphicsView->setScene(pScence);
    ui->graphicsView->show();
}

QImage showdiv::Mat2QImage(const Mat &src)
{
    cv::Mat temp; // make the same cv::Mat
    cv::Mat news;
    if(src.type()==CV_8UC1){
        medianBlur(src,src,9);
        applyColorMap(src,news,COLORMAP_JET);
    }
    else news=src;
    cvtColor(news, temp, CV_BGR2RGB); // cvtColor Makes a copt, that what i need
    QImage dest((const uchar *)temp.data, temp.cols, temp.rows, temp.step, QImage::Format_RGB888);
    dest.bits(); // enforce deep copy, see documentation
    // of QImage::QImage ( const uchar * data, int width, int height, Format format )
    return dest;
}
