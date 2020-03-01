#pragma once
#include <map>
#include <list>
using namespace std;

struct	News {
	string title;   //文章标题
	map<double, string> mapNews;  //tfidf - keywords
	int id;      //文章编号
	int views;   //浏览量 推荐系统热度系数
};

struct NewsList {  //新闻集表
	list<News> newList;
	string fileName;
public:
	NewsList();
	News& getId(int);
};

extern NewsList globalNews;