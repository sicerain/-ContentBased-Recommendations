#pragma once
#include <list>
#include <string>
#include "news.h"

using namespace std;
/*
倒排转换接口（api）
实现关键词文章编号的倒排引索，面向大数据的文本内容，
倒排引索召回策略很好的提升了文章搜索推荐的速率。
*/
struct NewsInformation {
	int id;    //文章编号
	int tfidf; //关键字TFIDF
};
struct NewsIDList {
	string keyword;  //倒排表关键字
	list<NewsInformation> newsIDList;  //文档编号表
};
struct Inverted {
	list<NewsIDList> invertedList;  // 反向表
	void update(News&);     //更新倒排表
	NewsIDList getNewsIDList(string);  //获取文档编号表
};
extern Inverted invertedLists;