#pragma once
#include "news.h"

using namespace std;

struct userNews {
	map<double, string>  userFeatureSpace;  //tfidf - keywords 用户特征空间 保证tfidf有序
	double downWeight;  //衰减系数 随时间而衰减（减小）
	NewsList likeNewsList;   //收藏喜欢新闻列表
	const double likeWeight; //收藏文章推荐权重
	NewsList viewNewLisr;    //最近浏览新闻列表
	const double viewWeight; //最近浏览推荐权重(与时间相关）
};