#pragma once
#include <list>
#include <string>
#include "news.h"

using namespace std;
/*
����ת���ӿڣ�api��
ʵ�ֹؼ������±�ŵĵ�����������������ݵ��ı����ݣ�
���������ٻز��Ժܺõ����������������Ƽ������ʡ�
*/
struct NewsInformation {
	int id;    //���±��
	int tfidf; //�ؼ���TFIDF
};
struct NewsIDList {
	string keyword;  //���ű�ؼ���
	list<NewsInformation> newsIDList;  //�ĵ���ű�
};
struct Inverted {
	list<NewsIDList> invertedList;  // �����
	void update(News&);     //���µ��ű�
	NewsIDList getNewsIDList(string);  //��ȡ�ĵ���ű�
};
extern Inverted invertedLists;