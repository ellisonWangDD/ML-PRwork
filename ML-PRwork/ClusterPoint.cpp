#include "ClusterPoint.h"





ClusterPoint::ClusterPoint(vector<double> &_inputData,int _dataDimension)
{
	data = _inputData;
	isVisited = false;
	isKey = false;
	clusterID = -1;//-1表示没有对其进行过聚类操作
	vector_n = _dataDimension;
}

ClusterPoint::~ClusterPoint()
{
}
