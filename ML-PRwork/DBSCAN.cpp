#include "DBSCAN.h"





DBSCAN::DBSCAN(vector<ClusterPoint>& _inputData ,double _eps,int _min_pts )
{
	min_pts = _min_pts;//半径内最小点数
	eps = _eps;//设定的最小距离半径
	sampleData = _inputData;//初始化样本vector
	sampleNum = sampleData.size();//初始化样本数量
	clusterNum = 0;//初始化簇数量
	for (int i=0;i<sampleNum;i++)
	{
		sampleData[i].pointID = i;//对每个point进行编号
	}
}

void DBSCAN::Clustering_analysis()
{
	int i, j, k;
	double tempDistance(1), MaxDistane(0);
	//vector<ClusterPoint> unVisitedCluster=sampleData;
	for (i=0;i<sampleNum;i++)   //便利每一个样本数据,dataNum样本数据个数  找核心点
	{
		int tempCount(0);
		for (j = i+1; j < sampleNum; j++)
		{
			tempDistance=Get2PointDistance(sampleData[i],sampleData[j]);  //没有进行优化,效率低下,有浪费,可以用两点距离矩阵
			if (tempDistance <= eps)
			{
				sampleData[i].nearPoint.push_back(sampleData[j].pointID);//互相push
				sampleData[j].nearPoint.push_back(sampleData[i].pointID);
			}
		}
		cout << " the "<<i<<"  near point: ";
		for (j = 0;j<sampleData[i].nearPoint.size();j++)
			cout << "  " <<sampleData[i].nearPoint[j]<<" ";
		cout << endl;
		tempCount = sampleData[i].nearPoint.size();
		if (tempCount >= min_pts)
		{
			//keyData.push_back(sampleData[i].pointID);
			sampleData[i].isKey = true;
			cout << "sample " << sampleData[i].pointID << " is keyData" << endl;
		}
		cout << endl << endl;
	}
	int clusterID(0);
	for (int i = 0; i < sampleData.size(); i++)
	{
		ClusterPoint &point = sampleData[i];
		if (point.isKey && !point.isVisited)
		{
			point.clusterID = clusterID;
			//cout << "key point : " << point.pointID << " is " << clusterID << "  cluter " << endl;
			point.isVisited = true;
			//point.isKey = true;
			Generate_Cluster(point.pointID,clusterID);
			clusterID++;
		}
	}
	cout << "Total clusterNum is :" << clusterID  << endl;
}

double DBSCAN::Get2PointDistance(ClusterPoint x_1, ClusterPoint x_2)//返回两点距离
{
	int i, j, k;
	int n = x_1.vector_n;//计算该点的维度(初始化的时候所有点维度都要一致) 注意!! 定义的类的成员变量一定要初始化,不初始化vector_n会导致下面的循环无法执行!
	double sum(0);   //声明求和sum时要注意相应的类型,如果定义成int型会导致其始终为0
	for (i = 0; i < n; i++)
	{
		sum += (x_1.data[i] - x_2.data[i])*(x_1.data[i] - x_2.data[i]);
	}
	return sqrt(sum);
}

double DBSCAN::Generate_Gaussian_Ditribution(double mean,double sd)//利用Box-Muller算法生成一维高斯分布,标准差mean,方差sd  X~N(mean,(sd)^2)
{
	static double V1, V2, S;
	static int phase = 0;
	double X;
	if (phase == 0) {
		do {
			double U1 = (double)rand() / RAND_MAX;
			double U2 = (double)rand() / RAND_MAX;

			V1 = 2 * U1 - 1;
			V2 = 2 * U2 - 1;
			S = V1 * V1 + V2 * V2;
		} while (S >= 1 || S == 0);

		X = V1 * sqrt(-2 * log(S) / S);
	}
	else
		X = V2 * sqrt(-2 * log(S) / S);
	phase = 1 - phase;
	return (X*sd+mean);
}

//unsigned long DBSCAN::Get_clusterID_member(unsigned long _clusterID)
//{
//	int i(0), j(0), k(0);
//	
//	for (i = 0; i < sampleData.size(); i++)
//	{
//		if (sampleData[i].clusterID)
//	}
//	return 0;
//}

DBSCAN::~DBSCAN()
{
}

void DBSCAN::Generate_Cluster(unsigned long _pointID,int _clusterID)  //_pointID是当前点的ID索引,_clusterID是该点属于的簇
{
	ClusterPoint &centerPoint=sampleData[_pointID];//根据pointID索引从样本集取出该点
	if (centerPoint.isKey==false)//该点邻域只有一个的话,则返回
		return ;
	int nearPoint_size = centerPoint.nearPoint.size();//取出该点邻域的值用于计算
	for (int i = 0; i < nearPoint_size; i++)//遍历该点邻域中的每一个点
	{
		ClusterPoint & nearPoint = sampleData[centerPoint.nearPoint[i]];//取出该邻域内部的点
		if (nearPoint.isVisited == false)//判断该点没有被访问过,则遍历该邻域内所有的点
		{
			//ClusterPoint & nearPoint = sampleData[centerPoint.nearPoint[i]];//取出该邻域内部的点
			nearPoint.isVisited = true;  //标记访问过
			nearPoint.clusterID = _clusterID;//记录该点的ID值
			cout << " ID:  " << nearPoint.pointID << "  is  " << _clusterID <<"   cluster  "<< endl;
			if (nearPoint.isKey==true)
				Generate_Cluster(nearPoint.pointID, _clusterID);//递归的调用该聚类函数   
		}
	}

}
