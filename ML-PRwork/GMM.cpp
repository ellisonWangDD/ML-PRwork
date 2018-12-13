#include "GMM.h"



double GMM::Gaussian_distribution(const double x_data, const double mean,const double standard_deviation)
{
	return 1.0 / (sqrt(2 * PI)*standard_deviation)*exp(-0.5*(x_data - mean)*(x_data - mean) / (standard_deviation*standard_deviation));
}

int GMM::Predict_data(double test_data)
{
	double current_prob;
	double max_prob(1);
	int optimalLabel;
	int i,j,k;
	for (i = 0; i < clusterNum; i++)
	{
		double sum(0);
		for (j = 0; j < clusterNum; j++)
		{
			sum += a_prob[j] * Gaussian_distribution(test_data, means[j], sd[j]);
		}
		current_prob = a_prob[i] * Gaussian_distribution(test_data, means[i], sd[i]) / sum;
		if (max_prob < current_prob)
		{
			max_prob = current_prob;
			optimalLabel = i;
		}
	}
	return optimalLabel;
}

void GMM::Train_data() //�˺�����������BUG,1.��˹�ֲ� ����ֵΪ0(��������xȡֵ��ǡ��);2.ĳ��λ��vector���;3.�������r_ji�±��������
{
	int i,j,k;
	bool ContinueIterationFlag=false;
	double delta_error=1;
	int iteration=0;
	do
	{
		for (i = 0; i < dataNum; i++)  //i ��ʾ��ǰΪ��i����������
		{
			//double sumDown(0);
			for (j = 0; j < clusterNum; j++)  //j��ʾ��ǰ��������������Ϊ��j����
			{
				double sumDown(0);
				for (k = 0; k < clusterNum; k++)  //k��������������,Ϊ�����ĸ
				{
					int temp = Gaussian_distribution(trainData[i], means[k], sd[k]);
					sumDown += a_prob[k] * Gaussian_distribution(trainData[i], means[k], sd[k]);
				}
				cov_r[i][j] = a_prob[i] * Gaussian_distribution(trainData[i], means[j], sd[j]) / sumDown;//�����������,��i�����������ֵ�j����cov[��������][���ִ���]
			}
		}

		for (i = 0; i < clusterNum; i++)
		{
			double sumUp_mean(0), sumDown_mean(0) ;
			double sumUp_sd(0), sumDown_sd(0);
			for (j = 0; j < dataNum; j++)
			{
				sumUp_mean+=cov_r_bkp[j][i] * trainData[j];
				sumDown_mean += cov_r_bkp[j][i];
			}
			means[i] = sumUp_mean / sumDown_mean;
			for (j = 0; j < dataNum; j++)
			{
				sumUp_sd += cov_r_bkp[j][i] * (trainData[j]-means[i])*(trainData[j]-means[i]);
				sumDown_sd += cov_r_bkp[j][i];
			}
			sd[i] = sqrt(sumUp_sd / sumDown_sd);
			a_prob[i] = sumDown_sd / clusterNum;
			
		}
		ContinueIterationFlag = false;
		for (i = 0; i < clusterNum; i++)
		{
			if (means[i] - means_bkp[i] > min_delta_error)
			{
				ContinueIterationFlag = true;
				break;
			}
			means_bkp[i] = means[i];
			sd_bkp[i] = sd[i];
			a_prob_bkp[i] = a_prob[i];
		}
	} while (delta_error > min_delta_error && (iteration++) < max_iteration);  //do-while ���Ҫд�ֺ�;
}

void GMM::Test_data()
{

}


void GMM::Init_GMM(vector<double>& inputData, int _clusterNum, int _max_iteration, double _min_delta_error)
{
	this->trainData = inputData;
	this->clusterNum = _clusterNum;
	this->min_delta_error = _min_delta_error;
	a_prob.resize(clusterNum);
	a_prob_bkp.resize(clusterNum);
	means.resize(clusterNum);
	means_bkp.resize(clusterNum);
	cov_r.resize(clusterNum);
	cov_r_bkp.resize(clusterNum);
	sd.resize(clusterNum);
	sd_bkp.resize(clusterNum);
	dataNum = trainData.size();
	for (int i = 0; i < clusterNum; ++i)
	{
		a_prob_bkp[i]=a_prob[i] = 1.0 / clusterNum;
		cov_r[i].resize(dataNum);
		cov_r_bkp[i].resize(dataNum);
		a_prob[i] = a_prob_bkp[i] = 1.0 / (double)clusterNum;//����ʹ�ñ�׼��̬�ֲ�,x����Ļ����¸��ʽ��̫С��
		//init means
		means[i] = means_bkp[i] = 255.0*i / (clusterNum);
		//init sigma
		sd[i] = sd_bkp[i] = 50;
	}
}

GMM::GMM()
{
	
}

GMM::~GMM()
{
}
