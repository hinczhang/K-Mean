#include "rsimage.h"

bool RSImage::LoadImg()
{
    int width = poDataset->GetRasterXSize();
    int height = poDataset->GetRasterYSize();
    int band = poDataset->GetRasterCount();
    basicImage.bandNum = band;
    if (band > 12||band<3)return false;
    float *tempImg = new float[width*height];
    GDALRasterBand *bandData;
    for (int i = 1; i <=band ; i++) {
        bandData = poDataset->GetRasterBand(i);
        GDALDataType DataType = bandData->GetRasterDataType();
        bandData->RasterIO(GF_Read, 0, 0, width, height, tempImg, width, height, DataType,0,0);
        Mat HT(height,width,CV_8UC1,tempImg);
        basicImage.band[i-1] = HT.clone();
    }
    vector<Mat> rgbChannels;
    rgbChannels.push_back(basicImage.band[2]);
    rgbChannels.push_back(basicImage.band[1]);
    rgbChannels.push_back(basicImage.band[0]);
    vector<Mat>temp(3);

    equalizeHist(rgbChannels[0],temp[0]);
    equalizeHist(rgbChannels[1],temp[1]);
    equalizeHist(rgbChannels[2],temp[2]);
    merge(temp, ShowImage);


    return true;
}



RSImage::RSImage()
{
    basicImage.bandNum = 0;
}

bool RSImage::RSLoad(const char *path)
{
    GDALAllRegister();
    poDataset =(GDALDataset *)GDALOpen(path, GA_ReadOnly);
    if (poDataset ==NULL)
        return false;
    else
    {
        if (LoadImg())return true;
        else
        return false;
    }
    LoadImg();
}

void RSImage::ObjectClear()
{
    poDataset = nullptr;
    ShowImage.release();
    for (int i = 0; i <  basicImage.bandNum; i++) {
        basicImage.band[i].release();
    }
    basicImage.bandNum = 0;
    pget.clear();
}

RSImage::~RSImage()
{

}

void RSImage::div()
{
    matrix=new uchar*[this->basicImage.band[0].rows*this->basicImage.band[0].cols];
    for(int i=0;i<this->basicImage.band[0].rows;i++){
        for(int j=0;j<this->basicImage.band[0].cols;j++){
            matrix[i*this->basicImage.band[0].cols+j]=new uchar[this->basicImage.bandNum];
            for(int k=0;k<this->basicImage.bandNum;k++)matrix[i*this->basicImage.band[0].cols+j][k]=
                    this->basicImage.band[k].at<uchar>(i,j);
        }
    }



}

Mat RSImage::showImg(vector<vector<point> > &group)
{
    Mat gray(ShowImage.size(),CV_8UC1);
    int Degree=255/group.size();
    for(int i=0;i<group.size();i++){
        for(int j=0;j<group[i].size();j++){
            gray.at<uchar>(group[i][j].x,group[i][j].y)=Degree*i+Degree;
        }
    }
    return gray;
}
