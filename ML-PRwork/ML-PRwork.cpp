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
#include "K_Means.h"
using namespace std;
int dataNum = 20;
int dataDimension = 2;
int modelNum;
int perModel_number;
int main()    
{
	int i(0), j(0), k(0);
	srand(time(NULL));//要设置随机数种子,否则每次rand()产生的序列都一样，需要包含<ctime>头文件
	vector<ClusterPoint> sample;
	fstream file("data.txt", ios::out | ios::in);//注意定义的位置,定义到函数里面,会导致清空file指针指向文档内容的位置
	vector<vector<double>> k_means_train_data;
	//if (!file.is_open())
	//{
	//	cout << "failed to open FILE" << endl;
	//	system("pause");
	//	return 0;
	//}
	cout << "please input data model amount(must settle in 1-10): " << endl;
	cin >> modelNum;
	cout << "please input sample amount in every model: " << endl;
	cin >> perModel_number;
	dataNum = modelNum*perModel_number;
	for (int count_modelNum = 0; count_modelNum < modelNum; count_modelNum++)
	{
		double temp_mean, temp_sd;
		cout << "please input the " << count_modelNum + 1 << " model 's parameter(mean,sd): " << endl;
		cin >> temp_mean;
		cin >> temp_sd;
		for (i = 0; i < perModel_number; i++)
		{
			vector<double> inputData;
			//cout << "please input the " << i << " data" << endl;
			for (j = 0; j < dataDimension; j++)
			{
				//if (!file.is_open())
				//{
				//	cout << "failed to open file data.txt" << endl;
				//	system("pause");
				//	return 0;
				//}
				double temp;//为什么会导致读入的精度确实一部分???
				for (j = 0; j < dataDimension; j++)
				{
					if (!file.eof())
					{
						temp = abs(DBSCAN::Generate_Gaussian_Ditribution(temp_mean, temp_sd));
						file << temp;   //使用fstream读入数据直接使用 文件>>var就可以,自动读入var相应的类型数据,但是不知道为什么会确实一部分精度
						inputData.push_back(temp);
					}
				}
			}
			cout << endl;
			k_means_train_data.push_back(inputData);
			ClusterPoint tempPoint(inputData, dataDimension);
			sample.push_back(tempPoint);  //引用
		}
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
	K_Means k_obj;
	k_obj.Init_K_Means(k_means_train_data, modelNum);
	k_obj.Train_data();
	k_obj.Print_cluster();
	DBSCAN obj(sample, 1.2, 2);
	//obj.Generate_Gaussian_Ditribution(2,1);
	obj.Clustering_analysis();
	//cout << obj.sampleData[0].clusterID << " " << obj.sampleData[4].clusterID;
	system("pause");
	return 0;
}

