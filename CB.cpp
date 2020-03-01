#include "stdafx.h"
#include <iostream>
#include <list>
#include "news.h"
#include "user.h"
#include "Invert conversion.h"
#include <math.h>

int CB(NewsList&, userNews& user) {
	map<double, string>::iterator iter;   //用户特征空间迭代器
	map<double, int> recommendMap;        //推荐表 推荐系数 文章编号
	list<NewsIDList> newsIDListIterList;                    //新闻编号迭代器表
	//获取推荐文章范围：
	for (iter = user.userFeatureSpace.begin(); iter != user.userFeatureSpace.end(); iter++) {
		/*invertedList为倒排表 从用户特征中利用倒排引索缩小推荐文章范围加快推荐文章速率
		  推荐文章范围从newsIDListItorList取得
		*/
		newsIDListIterList.push_back(invertedLists.getNewsIDList(iter->second));  //获取新闻迭代器
	}
	list<NewsIDList>::iterator recommendIter; //推荐迭代器
	//遍历推荐新闻编号表
	for (recommendIter = newsIDListIterList.begin(); recommendIter != newsIDListIterList.end(); iter++) {
		NewsIDList p;
		p = *recommendIter;
		list<NewsInformation>::iterator x;  //遍历文档编号表
		for (x = p.newsIDList.begin(); x != p.newsIDList.end(); x++) {
			NewsInformation t = *x;
			News& localNew = globalNews.getId(t.id);
			double recommendScore = 1;   //推荐系数
			/*CB算法*/
			map<double, string>::iterator userIter;   //用户特征空间迭代器
			map<double, string>::iterator itemIter;   //文档特征迭代器
			list<News>::iterator viewitemListIter;   //文档特征迭代器
			list<News>::iterator likeitemListIter;   //文档特征迭代器
			map<double, string>::iterator viewitemIter;   //文档特征迭代器
			map<double, string>::iterator likeitemIter;   //文档特征迭代器
			for (itemIter = localNew.mapNews.begin(); itemIter != localNew.mapNews.end();itemIter++) {
				/*用户特征推荐计算（考虑兴趣衰减问题）*/
				for (userIter = user.userFeatureSpace.begin(); userIter != user.userFeatureSpace.end(); iter++) {
					if (itemIter->second == userIter->second) {
						recommendScore = recommendScore * log(itemIter->first) / log(10) * log(userIter->first) / log(10) * user.downWeight;
						//lg(itemtfidf)*lg(userKeyWordtfidf)*衰减系数
					}
				}
				/*最近浏览文本特征推荐计算*/
				for (viewitemListIter = user.viewNewLisr.newList.begin(); viewitemListIter != user.viewNewLisr.newList.end(); viewitemListIter++) {
					News toomany = *viewitemListIter;
					for (viewitemIter = toomany.mapNews.begin(); viewitemIter != toomany.mapNews.end();viewitemIter++) {
						if (itemIter->second == viewitemIter->second) {
							recommendScore = recommendScore * log(itemIter->first) / log(10) * log(viewitemIter->first) / log(10) * user.viewWeight;
							//lg(itemtfidf)*lg(viewWordtfidf)*viewWeight
						}
					}
				}
				/*喜欢文本特征推荐计算*/
				for (likeitemListIter = user.viewNewLisr.newList.begin(); likeitemListIter != user.viewNewLisr.newList.end(); viewitemListIter++) {
					News toomany = *likeitemListIter;
					for (likeitemIter = toomany.mapNews.begin(); likeitemIter != toomany.mapNews.end();likeitemIter++) {
						if (itemIter->second == likeitemIter->second) {
							recommendScore = recommendScore * log(itemIter->first) / log(10) * log(likeitemIter->first) / log(10) * user.viewWeight;
							//lg(itemtfidf)*lg(likeWordtfidf)*likeWeight
						}
					}
				}
				/*配以热度权重*/
				recommendScore = recommendScore * log(localNew.views) / log(10);
				//插入该文档的推荐系数加以推荐
				recommendMap.insert(pair<double, int>(recommendScore, localNew.id));
			}
			
		}
	}
	return 0;
}