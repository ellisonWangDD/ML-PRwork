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
	vector<vector<double>> trainData;//ѵ������
	vector<vector<double>> mean_vector;//��ֵ����
	vector<vector<double>> mean_vector_bkp;
	vector<vector<double>> distance;//����
	vector<vector<vector<double>>> cluster; //������
	int clusterNum;
	int clusterLabel;
	int dataNum;
	int vector_n;

};

