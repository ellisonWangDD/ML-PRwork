// ML-PRwork.cpp : �������̨Ӧ�ó������ڵ㡣
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
	srand(time(NULL));//Ҫ�������������,����ÿ��rand()���������ж�һ������Ҫ����<ctime>ͷ�ļ�
	vector<ClusterPoint> sample;
	fstream file("data.txt", ios::out | ios::in);//ע�ⶨ���λ��,���嵽��������,�ᵼ�����fileָ��ָ���ĵ����ݵ�λ��
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
				double temp;//Ϊʲô�ᵼ�¶���ľ���ȷʵһ����???
				for (j = 0; j < dataDimension; j++)
				{
					if (!file.eof())
					{
						temp = abs(DBSCAN::Generate_Gaussian_Ditribution(temp_mean, temp_sd));
						file << temp;   //ʹ��fstream��������ֱ��ʹ�� �ļ�>>var�Ϳ���,�Զ�����var��Ӧ����������,���ǲ�֪��Ϊʲô��ȷʵһ���־���
						inputData.push_back(temp);
					}
				}
			}
			cout << endl;
			k_means_train_data.push_back(inputData);
			ClusterPoint tempPoint(inputData, dataDimension);
			sample.push_back(tempPoint);  //����
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

