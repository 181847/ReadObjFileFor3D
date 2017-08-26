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

ostream& operator << (ostream& out, GeometryGenerator::MeshData& meshData)
{
	//输出顶点坐标。
	for (auto& vertex : meshData.Vertices)
	{
		out << "坐标：x: " << vertex.Position.x << ", y: " << vertex.Position.y << ", z: " << vertex.Position.z << endl;
		out << "法线：x: " << vertex.Normal.x << ", y: " << vertex.Normal.y << ", z: " << vertex.Normal.z << endl << endl;
	}

	return out;
}

void RunTest()
{
	cout << "测试开始" << endl;
	auto result = ObjReader::ReadObjFile("Tank.obj");

	for (auto& geo : *result)
	{
		cout << "已读取网格：" << geo.first << endl;
		cout << "*********************************" << endl
			<< "***************" << endl
			<< *(geo.second)
			<< "***************" << endl
			<< "*********************************" << endl;
	}
	cout << "测试结束" << endl;
}

int main()
{
	try
	{
		RunTest();
	}
	catch (SimpleException& e)
	{
		cout << e.ToString() << endl;
	}

	//wait for '?'
	while ('?' != getchar());

    return 0;
}

