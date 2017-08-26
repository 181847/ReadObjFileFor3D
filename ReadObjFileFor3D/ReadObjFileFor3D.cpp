// ReadObjFileFor3D.cpp : �������̨Ӧ�ó������ڵ㡣
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
	//����������ꡣ
	for (auto& vertex : meshData.Vertices)
	{
		out << "���꣺x: " << vertex.Position.x << ", y: " << vertex.Position.y << ", z: " << vertex.Position.z << endl;
		out << "���ߣ�x: " << vertex.Normal.x << ", y: " << vertex.Normal.y << ", z: " << vertex.Normal.z << endl << endl;
	}

	return out;
}

void RunTest()
{
	cout << "���Կ�ʼ" << endl;
	auto result = ObjReader::ReadObjFile("Tank.obj");

	for (auto& geo : *result)
	{
		cout << "�Ѷ�ȡ����" << geo.first << endl;
		cout << "*********************************" << endl
			<< "***************" << endl
			<< *(geo.second)
			<< "***************" << endl
			<< "*********************************" << endl;
	}
	cout << "���Խ���" << endl;
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

