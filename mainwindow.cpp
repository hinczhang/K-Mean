#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_statusLabel = new QLabel;
    m_statusLabel->resize(100, 30);
    ui->statusBar->addPermanentWidget(m_statusLabel);
    flag=0;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::LoadFile()
{
    rs.ObjectClear();
    QString fileName;
    fileName = QFileDialog::getOpenFileName(this,
            tr("Load File"),
            "F:",
            tr("image(*bmp *jpg *tif);;"
                "test(*txt)"));

     if (rs.RSLoad(fileName.toLatin1().data())){
            QMessageBox::information(NULL, "Loading Result", "Succeed to load the file!",
                QMessageBox::Yes);
     }

     else{
         QMessageBox::information(NULL, "Loading Result", "Error 101: Fail to load the file!\nPlease check the type of the file or the path of the file.",
                QMessageBox::Yes);return;}

     pScence = new QGraphicsScene;
     img=new QImage;
     *img=Mat2QImage(rs.ShowImage);
     QPixmap pix = QPixmap::fromImage(*img);
     pixItem = new QGraphicsPixmapItem(pix);
     pScence->addItem(pixItem);
     ui->graphicsView->setScene(pScence);
     ui->graphicsView->show();
     flag=1;
}

void MainWindow::addNode()
{
    if(flag==1){
        flag=2;

    }
}

void MainWindow::run()
{
    if(flag==2){
        flag=0;
        vector<vector<point>>group;
        rs.div();
        if(K_Means(rs,group,rs.pget)){
        Mat showgray=rs.showImg(group);
        mydiv.getdiv(showgray);
        mydiv.exec();
        rs.ObjectClear();
        }
        else QMessageBox::information(NULL, "Loading Result", "Succeed to load the file!",
                                      QMessageBox::Yes);
    }
}



QImage MainWindow::Mat2QImage(const Mat &src)
{
    cv::Mat temp; // make the same cv::Mat
    cvtColor(src, temp, CV_BGR2RGB); // cvtColor Makes a copt, that what i need
    QImage dest((const uchar *)temp.data, temp.cols, temp.rows, temp.step, QImage::Format_RGB888);
    dest.bits(); // enforce deep copy, see documentation
    // of QImage::QImage ( const uchar * data, int width, int height, Format format )
    return dest;
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    if (flag != 0) {
            QPointF scenePos = ui->graphicsView->mapToScene(event->pos()-ui->graphicsView->pos()) - pixItem->pos();
            int x1 = scenePos.x();
            int y1 = scenePos.y();
            QString str = "(" + QString::number(x1) + "," + QString::number(y1) + ")";
            m_statusLabel->setText(str);
            if(flag==2){
                if(y1>=rs.ShowImage.rows||y1<0||x1<0||x1>rs.ShowImage.cols)return;
                rs.Loadbasic(y1,x1);

            QPainter *mpainter;
            mpainter=new QPainter(img);
            mpainter->setPen(QPen(QColor(0,255,255),4));
            mpainter->drawPoint(x1,y1);
            mpainter->end();

            QPixmap pix = QPixmap::fromImage(*img);

            pixItem->setPixmap(pix);

            ui->graphicsView->repaint();}
        }
}
