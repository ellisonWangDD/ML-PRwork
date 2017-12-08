#pragma once
#include <vector>
#include <ctime>
#include <iostream>
using namespace std;
class K_Means
{
public:
	void Init_K_Means(vector<vector<double>>& inputData,int _clusterNum);
	void Train_data();
	void Print_cluster();
	K_Means();
	~K_Means();
protected:
	vector<vector<double>> trainData;//训练数据
	vector<vector<double>> mean_vector;//均值向量
	vector<vector<double>> mean_vector_bkp;
	vector<vector<double>> distance;//距离
	vector<vector<vector<double>>> cluster; //样本簇
	int clusterNum;
	int clusterLabel;
	int dataNum;
	int vector_n;

};

