#ifndef RSIMAGE_H
#define RSIMAGE_H


#include<gdal.h>
#include<gdal_priv.h>
#include<opencv2/core.hpp>
#include<opencv2/imgproc.hpp>
#include<opencv2/highgui.hpp>
#include<iostream>
#include<vector>

using namespace std;
using namespace cv;

struct point{
int x,y;
};


struct ImgBand {
    Mat band[12];
    int bandNum;
};

class RSImage
{
private:
    bool LoadImg();


public:
    RSImage();
    bool RSLoad(const char*path);
    void ObjectClear();
    void Loadbasic(int x,int y){
        point myp;
        myp.x=x,myp.y=y;
        pget.push_back(myp);
     }
    ~RSImage();
public:
    ImgBand basicImage;
    void show();
    GDALDataset *poDataset;
    Mat ShowImage;
    void div();
    Mat showImg(vector<vector<point>>&group);
    uchar **matrix;
vector<point>pget;
};
#endif // RSIMAGE_H
