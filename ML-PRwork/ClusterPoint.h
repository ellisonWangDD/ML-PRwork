#pragma once
#include <vector>

using namespace std;
class ClusterPoint
{
public:
	ClusterPoint(vector<double> &_inputData,int _dataDimension);
	void GetPointValue();
	~ClusterPoint();
public:

	unsigned long pointID;
	bool isKey;
	bool isVisited;
	vector<double> data;
	vector<unsigned long> nearPoint;
    int clusterID;
	int vector_n;

};

