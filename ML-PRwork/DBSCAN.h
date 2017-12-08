#pragma once
#include <vector>
#include <math.h>
#include <ctime>
#include <stdlib.h>
#include <iostream>
#include "ClusterPoint.h"

using namespace std;
class DBSCAN
{
public:
	DBSCAN(vector<ClusterPoint>& _inputData, double _eps, int _min_pts);
	void Generate_Cluster(unsigned long _pointID, int cluster);
	void Clustering_analysis();
	double Get2PointDistance(ClusterPoint x_1,ClusterPoint x_2);
	static double Generate_Gaussian_Ditribution(double mean,double sd);
	//unsigned long Get_clusterID_member(unsigned long _clusterID);
	~DBSCAN();

public:
	vector<unsigned long> keyData;
	vector<ClusterPoint> sampleData;
	int sampleNum;
	int keyDataNum;
	int clusterNum;
	double eps;
	int  min_pts;
};

