// ML-PRwork.cpp : 定义控制台应用程序的入口点。
//

#pragma once
#include "stdafx.h"
#include "DBSCAN.h"

#include <random>
#include <math.h>
#include <ctime>
#include <fstream>
#include <iostream>
#include "GMM.h"
using namespace std;
const int dataNum = 10;
const int dataDimension = 2;

int main()
{
	int i(0), j(0), k(0);
	vector<ClusterPoint> sample;
	for (i = 0; i < dataNum; i++)
	{
		vector<double> inputData;
		//double temp = i*0.8;
		cout << "please input the " << i << " data" << endl;
		for (j = 0; j < dataDimension; j++)
		{
			double input;
			cout << "please input " << dataDimension<< " dimension" << "data : ";
			cin >> input;
			inputData.push_back(input);
		}
		cout << endl;
		ClusterPoint tempPoint(inputData,dataDimension);
		sample.push_back(tempPoint);  //引用
	}
	for (i = 0; i < dataNum; i++)
	{
		cout << "the " << i << " sample point: ";
		for (j = 0; j < dataDimension; j++)
		{
			cout << sample[i].data[j]<<" ";
		}
		cout << endl;
	}
	cout << endl;
	DBSCAN obj(sample, 1.5, 3);
	obj.Clustering_analysis();
	cout << obj.sampleData[0].clusterID << " " << obj.sampleData[4].clusterID;

	system("pause");

	//int i(0), j(0), k(0);
	//vector<double> trainSet;
	//trainSet.resize(20);
	//GMM test;
	//double d;
	//srand(time(NULL));
	//for (i = 0; i < 20; i++)
	//{
	//	d = (rand() / (double)RAND_MAX) * 255;
	//	trainSet[i]=d;
	//}
	//test.Init_GMM(trainSet, 2, 10000, 0.0001);
	//test.Train_data();
	//cout<<test.Predict_data(10)<<endl;
	//system("pause");
	//return 0;

}
















//int main()
//{
//	int D=1;
//	double number;
//	normal_distribution<double> gus_distribution(0, D);//第一个参数为平均灰度级，第二个参数为标准差
//	default_random_engine dre;//引擎
//	for (int i = 0; i < 50; i++)
//	{
//		number = gus_distribution(dre);
//		if (number>0&&number<1.0)
//			cout << number << endl;
//	}
//	1 #ifndef _GMM_H
//		2 #define _GMM_H
//	 #include <vector>
//	 #include <cmath>
//	 using namespace std;
//	 class GMM
//		 {
//		 public:
//			     void Init(const vector<double> &inputData, const int clustNum = 5, double eps = 0.01, double max_steps = 20);
//			     void train();
//			     int predicate(double x);//预测输入的数据属于哪一类
//			     void print();
//			 protected:
//				     int clusterNum;
//				     vector<double> means;
//				     vector<double> means_bkp;
//				     vector<double> sigmas;
//				     vector<double> sigmas_bkp;
//				     vector<double> probilities;
//				     vector<double> probilities_bkp;
//				     vector<vector<double>> memberships;
//				     vector<vector<double>> memberships_bkp;
//				     vector<double> data;
//				     int dataNum;
//				     double epslon;
//				     double max_steps;
//				 private:
//					     double gauss(const double x, const double m, const double sigma);
//					 };
//	 #endif
	//	 #include "GMM.h"
	//	 #include <iostream>
 //#include <fstream>
	//	 #include <stdlib.h>
	//	 #include <Windows.h>
	//	 using namespace std;
	//
	//	 void GMM::Init(const vector<double> &inputData, const int clustNum, double eps, double max_steps)
	//	 {
	//	     this->data = inputData;
	//	     this->dataNum = data.size();
	//	     this->clusterNum = clustNum;
	//	     this->epslon = eps;
	//	     this->max_steps = max_steps;
	//	     this->means.resize(clusterNum);
	//	     this->means_bkp.resize(clusterNum);
	//	     this->sigmas.resize(clusterNum);
	//	     this->sigmas_bkp.resize(clusterNum);
	//	     this->memberships.resize(clusterNum);
	//	     this->memberships_bkp.resize(clusterNum);
	//	     for (int i = 0; i<clusterNum; i++)
	//		     {
	//		         memberships[i].resize(data.size());
	//		         memberships_bkp[i].resize(data.size());
	//		     }
	//	     this->probilities.resize(clusterNum);
	//	     this->probilities_bkp.resize(clusterNum);
	//	     //initialize mixture probabilities
	//		     for (int i = 0; i<clusterNum; i++)
	//		     {
	//		         probilities[i] = probilities_bkp[i] = 1.0 / (double)clusterNum;
	//		         //init means
	//			         means[i] = means_bkp[i] = 255.0*i / (clusterNum);
	//		         //init sigma
	//			         sigmas[i] = sigmas_bkp[i] = 50;
	//		     }
	//	 }
	// void GMM::train()
	//	 {
	//	     //compute membership probabilities
	//		     int i, j, k, m;
	//	     double sum = 0, sum2;
	//	     int steps = 0;
	//	     bool go_on;
	//	     do
	//		     {
	//		     for (k = 0; k<clusterNum; k++)
	//			     {
	//			         //compute membership probabilities
	//				         for (j = 0; j<data.size(); j++)
	//				         {
	//				             //计算p(k|n)
	//					             sum = 0;
	//				             for (m = 0; m<clusterNum; m++)
	//					             {
	//					                 sum += probilities[m] * gauss(data[j], means[m], sigmas[m]);
	//					             }
	//				             //求分子
	//					             memberships[k][j] = probilities[k] * gauss(data[j], means[k], sigmas[k]) / sum;
	//				         }
	//			         //求均值
	//				             //求条件概率的和
	//				         sum = 0;
	//			         for (i = 0; i<dataNum; i++)
	//				         {
	//				             sum += memberships[k][i];
	//				         }
	//			         sum2 = 0;
	//			         for (j = 0; j<dataNum; j++)
	//				         {
	//				             sum2 += memberships[k][j] * data[j];
	//				         }
	//			         means[k] = sum2 / sum;
	//			         //求方差
	//				         sum2 = 0;
	//			         for (j = 0; j<dataNum; j++)
	//				         {
	//				             sum2 += memberships[k][j] * (data[j] - means[k])*(data[j] - means[k]);
	//				         }
	//			         sigmas[k] = sqrt(sum2 / sum);
	//			         //求概率
	//				         probilities[k] = sum / dataNum;
	//			     }//end for k
	//		     //check improvement
	//			     go_on = false;
	//		     for (k = 0; k<clusterNum; k++)
	//			     {
	//			         if (means[k] - means_bkp[k]>epslon)
	//				         {
	//				             go_on = true;
	//				             break;
	//				         }
	//			     }
	//		     //back up
	//			     this->means_bkp = means;
	//		     this->sigmas_bkp = sigmas;
	//		     this->probilities_bkp = probilities;
	//		     } while (go_on&&steps++<max_steps);//end do while
	//		 }
	//
	//	 double GMM::gauss(const double x, const double m, const double sigma)
	//	 {
	//	     return 1.0 / (sqrt(2 * 3.1415926)*sigma)*exp(-0.5*(x - m)*(x - m) / (sigma*sigma));
	//	 }
	// int GMM::predicate(double x)
	//	 {
	//	     double max_p = -100;
	//	     int i;
	//	     double current_p;
	//	     int bestIdx = 0;
	//	     for (i = 0; i<clusterNum; i++)
	//		     {
	//		         current_p = gauss(x, means[i], sigmas[i]);
	//		         if (current_p>max_p)
	//			         {
	//			             max_p = current_p;
	//			             bestIdx = i;
	//			         }
	//		     }
	//	     return bestIdx;
	//	 }
	// void GMM::print()
	//	 {
	//	     int i;
	//	     for (i = 0; i<clusterNum; i++)
	//		     {
	//		         cout << "Mean: " << means[i] << " Sigma: " << sigmas[i] << " Mixture Probability: " << probilities[i] << endl;
	//		     }
	//	 }


