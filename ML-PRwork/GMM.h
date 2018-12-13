#pragma once
#include<iostream>
#include <vector>
#include <stdlib.h>
#include <fstream>
#include <math.h>
#define PI 3.1415926535898
using namespace std;
class GMM //һά��������GMM
{
public:
	double Gaussian_distribution(double data,double mean,double standard_deviation);
	int Predict_data(double test_data);
	void Train_data();
	void Test_data();
	void Init_GMM(vector<double>& inputData,int _clusterNum,int _max_iteration,double _min_delta_error);
	
	GMM();
	~GMM();
protected:
	vector<double> trainData;
	vector<double> means;//��ֵ
	vector<double> sd; //��׼��
	vector<double> a_prob;//���ϵ��
	vector<double> a_prob_bkp;
	vector<vector<double>> cov_r;//����״̬������ʾ���
	vector<vector<double>> cov_r_bkp;
	vector<double> means_bkp;
	vector<double> sd_bkp;
	int max_iteration;
	double min_delta_error;
	int clusterNum;
	int dataNum;
	//bool InitFlag;

};

