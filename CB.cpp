#include "stdafx.h"
#include <iostream>
#include <list>
#include "news.h"
#include "user.h"
#include "Invert conversion.h"
#include <math.h>

int CB(NewsList&, userNews& user) {
	map<double, string>::iterator iter;   //�û������ռ������
	map<double, int> recommendMap;        //�Ƽ��� �Ƽ�ϵ�� ���±��
	list<NewsIDList> newsIDListIterList;                    //���ű�ŵ�������
	//��ȡ�Ƽ����·�Χ��
	for (iter = user.userFeatureSpace.begin(); iter != user.userFeatureSpace.end(); iter++) {
		/*invertedListΪ���ű� ���û����������õ���������С�Ƽ����·�Χ�ӿ��Ƽ���������
		  �Ƽ����·�Χ��newsIDListItorListȡ��
		*/
		newsIDListIterList.push_back(invertedLists.getNewsIDList(iter->second));  //��ȡ���ŵ�����
	}
	list<NewsIDList>::iterator recommendIter; //�Ƽ�������
	//�����Ƽ����ű�ű�
	for (recommendIter = newsIDListIterList.begin(); recommendIter != newsIDListIterList.end(); iter++) {
		NewsIDList p;
		p = *recommendIter;
		list<NewsInformation>::iterator x;  //�����ĵ���ű�
		for (x = p.newsIDList.begin(); x != p.newsIDList.end(); x++) {
			NewsInformation t = *x;
			News& localNew = globalNews.getId(t.id);
			double recommendScore = 1;   //�Ƽ�ϵ��
			/*CB�㷨*/
			map<double, string>::iterator userIter;   //�û������ռ������
			map<double, string>::iterator itemIter;   //�ĵ�����������
			list<News>::iterator viewitemListIter;   //�ĵ�����������
			list<News>::iterator likeitemListIter;   //�ĵ�����������
			map<double, string>::iterator viewitemIter;   //�ĵ�����������
			map<double, string>::iterator likeitemIter;   //�ĵ�����������
			for (itemIter = localNew.mapNews.begin(); itemIter != localNew.mapNews.end();itemIter++) {
				/*�û������Ƽ����㣨������Ȥ˥�����⣩*/
				for (userIter = user.userFeatureSpace.begin(); userIter != user.userFeatureSpace.end(); iter++) {
					if (itemIter->second == userIter->second) {
						recommendScore = recommendScore * log(itemIter->first) / log(10) * log(userIter->first) / log(10) * user.downWeight;
						//lg(itemtfidf)*lg(userKeyWordtfidf)*˥��ϵ��
					}
				}
				/*�������ı������Ƽ�����*/
				for (viewitemListIter = user.viewNewLisr.newList.begin(); viewitemListIter != user.viewNewLisr.newList.end(); viewitemListIter++) {
					News toomany = *viewitemListIter;
					for (viewitemIter = toomany.mapNews.begin(); viewitemIter != toomany.mapNews.end();viewitemIter++) {
						if (itemIter->second == viewitemIter->second) {
							recommendScore = recommendScore * log(itemIter->first) / log(10) * log(viewitemIter->first) / log(10) * user.viewWeight;
							//lg(itemtfidf)*lg(viewWordtfidf)*viewWeight
						}
					}
				}
				/*ϲ���ı������Ƽ�����*/
				for (likeitemListIter = user.viewNewLisr.newList.begin(); likeitemListIter != user.viewNewLisr.newList.end(); viewitemListIter++) {
					News toomany = *likeitemListIter;
					for (likeitemIter = toomany.mapNews.begin(); likeitemIter != toomany.mapNews.end();likeitemIter++) {
						if (itemIter->second == likeitemIter->second) {
							recommendScore = recommendScore * log(itemIter->first) / log(10) * log(likeitemIter->first) / log(10) * user.viewWeight;
							//lg(itemtfidf)*lg(likeWordtfidf)*likeWeight
						}
					}
				}
				/*�����ȶ�Ȩ��*/
				recommendScore = recommendScore * log(localNew.views) / log(10);
				//������ĵ����Ƽ�ϵ�������Ƽ�
				recommendMap.insert(pair<double, int>(recommendScore, localNew.id));
			}
			
		}
	}
	return 0;
}