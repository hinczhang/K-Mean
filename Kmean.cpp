#include "Kmean.h"

float GetDistance(uchar *a,uchar *b,int num)
{
    float dis = 0.0;

    for (int i = 0; i < num; i++) {
        dis += (a[i] - b[i])*(a[i] - b[i]);
    }
    return sqrt(dis);
}



bool isequal(vector<vector<float>>& s, vector<vector<float>>&old)
{
    if(old.size()==0)return false;
    for(int i=0;i<old.size();i++){
        for(int j=0;j<old[i].size();j++){
            if(abs(old[i][j]-s[i][j])>0.001)return false;
        }
    }
    return true;
}

vector<vector<float>> Meaning(RSImage &img,vector<vector<point>> &group,int num)
{
    vector<vector<float>>get(group.size());
    float **bas=new float*[group.size()];
    for(int i=0;i<group.size();i++){
        bas[i]=new float[num];
        memset(bas[i],0,num*sizeof(float));
    }
    int rows=img.basicImage.band[0].rows;
    int cols=img.basicImage.band[0].cols;
    for(int i=0;i<group.size();i++){
        for(int j=0;j<num;j++){
            for(int k=0;k<group[i].size();k++){
                bas[i][j]+=img.matrix[group[i][k].x*cols+group[i][k].y][j];
            }
        }
    }
    for(int i=0;i<group.size();i++){
        for(int j=0;j<num;j++){
            bas[i][j]/=group[i].size();
            get[i].push_back(bas[i][j]);
        }
    }
    return get;
}

bool K_Means(RSImage &img, vector<vector<point>> &group, vector<point> z)
{
    if(z.size()<=1)return false;


    int rows=img.basicImage.band[0].rows;
    int cols=img.basicImage.band[0].cols;
    int num=img.basicImage.bandNum;
    vector<vector<float>>mz(z.size());
    vector<vector<float>>oldz(z.size());
    for(int i=0;i<z.size();i++){
        for(int k=0;k<num;k++){
        mz[i].push_back(img.matrix[z[i].x*cols+z[i].y][k]);
        oldz[i].push_back(img.matrix[z[i].x*cols+z[i].y][k]);
        }
    }

    while(true){
        group.resize(z.size());
        for(int i=0;i<rows;i++){
            for(int j=0;j<cols;j++){
                int nMax=0;
                for(int k=0;k<z.size();k++){
                    if(GetDistance(img.matrix[i*cols+j],img.matrix[z[k].x*cols+z[k].y],num)<
                            GetDistance(img.matrix[i*cols+j],img.matrix[z[nMax].x*cols+z[nMax].y],num))
                        nMax=k;
                }
              point temp;temp.x=i,temp.y=j;
              group[nMax].push_back(temp);

            }
        }
        oldz=mz;
        mz=Meaning(img,group,num);
        bool flag=isequal(mz,oldz);
        if(flag)break;
        group.clear();
    }

    return true;

}
