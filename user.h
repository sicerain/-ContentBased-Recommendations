#pragma once
#include "news.h"

using namespace std;

struct userNews {
	map<double, string>  userFeatureSpace;  //tfidf - keywords �û������ռ� ��֤tfidf����
	double downWeight;  //˥��ϵ�� ��ʱ���˥������С��
	NewsList likeNewsList;   //�ղ�ϲ�������б�
	const double likeWeight; //�ղ������Ƽ�Ȩ��
	NewsList viewNewLisr;    //�����������б�
	const double viewWeight; //�������Ƽ�Ȩ��(��ʱ����أ�
};