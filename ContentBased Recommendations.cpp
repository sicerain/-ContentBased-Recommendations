// ContentBased Recommendations.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <map>
#include <string>
#include <Windows.h>
using namespace std;

int main()

{

	map<int, string> mapStudent;

	mapStudent[1] = "student_one";

	mapStudent[1] = "student_two";

	mapStudent[2] = "student_three";

	map<int, string>::iterator iter;

	for (iter = mapStudent.begin(); iter != mapStudent.end(); iter++)

		cout << iter->first << ' ' << iter->second << endl;

	system("pause");
}

