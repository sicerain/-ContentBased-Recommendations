#pragma once
#include <map>
#include <list>
using namespace std;

struct	News {
	string title;   //���±���
	map<double, string> mapNews;  //tfidf - keywords
	int id;      //���±��
	int views;   //����� �Ƽ�ϵͳ�ȶ�ϵ��
};

struct NewsList {  //���ż���
	list<News> newList;
	string fileName;
public:
	NewsList();
	News& getId(int);
};

extern NewsList globalNews;