#include "K_Means.h"



void K_Means::Init_K_Means(vector<vector<double>>& inputData, int _clusterNum)
{
	clusterNum = _clusterNum;
	trainData = inputData;
	dataNum = inputData.size();
	if (trainData.size() == 0||trainData[0].size()==0)
	{
		cout << "INPUT DATA ERROR" << endl;
		system("pause");
	}
	vector_n = trainData[0].size();
}

void K_Means::Train_data()   //此函数可能有严重bug
{
	int i, j, k;
	bool ContinueFlag=false;
	srand(time(NULL));//系统时间 随机数种子发生器
	for (i = 0; i < clusterNum; i++)
	{
		mean_vector_bkp[i]=mean_vector[i]=trainData[(int)rand() % dataNum];//随机选取 cluster数目个样本作为初始均值向量
	}
	do 
	{
		for (i = 0; i < dataNum; i++)
		{
			double min_distance(100);
			int min_distance_cluster(0);
			for (j = 0; j < clusterNum; j++)
			{
				double sum(0);
				for (k = 0; k < vector_n; k++)
				{
					sum += (trainData[i][k] - mean_vector[j][k])*(trainData[i][k] - mean_vector[j][k]);
				}
				if (sum < min_distance)
				{
					min_distance = sum;
					min_distance_cluster = j;
				}
			}
			cluster[j].push_back(trainData[j]);  //将距离最近的样本数据push到j类
		}

		for (k = 0; k < clusterNum; k++)
		{
			int cluster_size = cluster[k].size();  //计算每个簇C内有多少个样本
			for (i = 0; i < vector_n; i++)
			{
				double sum(0);
				for (j = 0; j < clusterNum; j++)
				{
					sum += mean_vector[j][i];
				}
				mean_vector[k][i] = sum / (double)cluster_size;//计算每个簇内的均值向量
			}
			if (mean_vector[k] != mean_vector_bkp[k])
			{
				ContinueFlag = true;
				mean_vector_bkp[k] = mean_vector[k];
			}
		}
		ContinueFlag = false;
	} while (ContinueFlag==true);
}

void K_Means::Print_cluster()
{
	int i, j, k;
	int size;
	//int dimension=vector_n;
	for (i=0;i<clusterNum;i++)
	{
		cout << "The" << i << "Cluster:";
		size = cluster[i].size();
		for (j = 0; j < size; j++)
		{
			cout << '(';
			for (k = 0; k < vector_n; k++)
			{
				cout << cluster[i][j][k] << ' ';
			}
			cout << ')';
		}
		cout << endl;
	}
}

K_Means::K_Means()
{
	

}


K_Means::~K_Means()
{
}
