#include "ClusterPoint.h"





ClusterPoint::ClusterPoint(vector<double> &_inputData,int _dataDimension)
{
	data = _inputData;
	isVisited = false;
	isKey = false;
	clusterID = -1;//-1��ʾû�ж�����й��������
	vector_n = _dataDimension;
}

ClusterPoint::~ClusterPoint()
{
}
