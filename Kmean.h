#ifndef KMEAN_H
#define KMEAN_H
#include<iostream>
#include<vector>
#include"rsimage.h"
#include<iostream>
#include<vector>
using namespace std;





float GetDistance(uchar *a,uchar *b,int num);
bool K_Means(RSImage&img, vector<vector<point>>&group, vector<point>z);
bool isequal(vector<vector<float>>& s, vector<vector<float>>&old);
vector<vector<float>> Meaning(RSImage &img,vector<vector<point>> &group,int num);



#endif // KMEAN_H
