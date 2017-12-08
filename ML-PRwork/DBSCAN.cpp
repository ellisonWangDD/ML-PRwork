#include "DBSCAN.h"





DBSCAN::DBSCAN(vector<ClusterPoint>& _inputData ,double _eps,int _min_pts )
{
	min_pts = _min_pts;//�뾶����С����
	eps = _eps;//�趨����С����뾶
	sampleData = _inputData;//��ʼ������vector
	sampleNum = sampleData.size();//��ʼ����������
	clusterNum = 0;//��ʼ��������
	for (int i=0;i<sampleNum;i++)
	{
		sampleData[i].pointID = i;//��ÿ��point���б��
	}
}

void DBSCAN::Clustering_analysis()
{
	int i, j, k;
	double tempDistance(1), MaxDistane(0);
	//vector<ClusterPoint> unVisitedCluster=sampleData;
	for (i=0;i<sampleNum;i++)   //����ÿһ����������,dataNum�������ݸ���  �Һ��ĵ�
	{
		int tempCount(0);
		for (j = i+1; j < sampleNum; j++)
		{
			tempDistance=Get2PointDistance(sampleData[i],sampleData[j]);  //û�н����Ż�,Ч�ʵ���,���˷�,����������������
			if (tempDistance <= eps)
			{
				sampleData[i].nearPoint.push_back(sampleData[j].pointID);//����push
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

double DBSCAN::Get2PointDistance(ClusterPoint x_1, ClusterPoint x_2)//�����������
{
	int i, j, k;
	int n = x_1.vector_n;//����õ��ά��(��ʼ����ʱ�����е�ά�ȶ�Ҫһ��) ע��!! �������ĳ�Ա����һ��Ҫ��ʼ��,����ʼ��vector_n�ᵼ�������ѭ���޷�ִ��!
	double sum(0);   //�������sumʱҪע����Ӧ������,��������int�ͻᵼ����ʼ��Ϊ0
	for (i = 0; i < n; i++)
	{
		sum += (x_1.data[i] - x_2.data[i])*(x_1.data[i] - x_2.data[i]);
	}
	return sqrt(sum);
}

double DBSCAN::Generate_Gaussian_Ditribution(double mean,double sd)//����Box-Muller�㷨����һά��˹�ֲ�,��׼��mean,����sd  X~N(mean,(sd)^2)
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

void DBSCAN::Generate_Cluster(unsigned long _pointID,int _clusterID)  //_pointID�ǵ�ǰ���ID����,_clusterID�Ǹõ����ڵĴ�
{
	ClusterPoint &centerPoint=sampleData[_pointID];//����pointID������������ȡ���õ�
	if (centerPoint.isKey==false)//�õ�����ֻ��һ���Ļ�,�򷵻�
		return ;
	int nearPoint_size = centerPoint.nearPoint.size();//ȡ���õ������ֵ���ڼ���
	for (int i = 0; i < nearPoint_size; i++)//�����õ������е�ÿһ����
	{
		ClusterPoint & nearPoint = sampleData[centerPoint.nearPoint[i]];//ȡ���������ڲ��ĵ�
		if (nearPoint.isVisited == false)//�жϸõ�û�б����ʹ�,����������������еĵ�
		{
			//ClusterPoint & nearPoint = sampleData[centerPoint.nearPoint[i]];//ȡ���������ڲ��ĵ�
			nearPoint.isVisited = true;  //��Ƿ��ʹ�
			nearPoint.clusterID = _clusterID;//��¼�õ��IDֵ
			cout << " ID:  " << nearPoint.pointID << "  is  " << _clusterID <<"   cluster  "<< endl;
			if (nearPoint.isKey==true)
				Generate_Cluster(nearPoint.pointID, _clusterID);//�ݹ�ĵ��øþ��ຯ��   
		}
	}

}
