// ReadObjFileFor3D.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "ObjReader.h"
#include <iostream>
using namespace std;

ostream& operator << (ostream& out, vector<string>& strings)
{
	for (string& s : strings)
	{
		out << s.c_str() << endl;
	}
	return out;
}

int main()
{
	string s("f 1/1/1  2/2/2 3/3/3 ");
	vector<string> subStrings;
	SplitString(s, subStrings, " ");


	for (size_t i = 0; i < subStrings.size(); ++i)
	{
		vector<string> subNumbers;
		SplitString(subStrings[i], subNumbers, "/");
		cout << subNumbers.size() << endl << subNumbers << endl;
	}


	//wait for '?'
	while ('?' != getchar());

    return 0;
}

