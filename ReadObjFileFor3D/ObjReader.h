#pragma once
#include "GeometryGenerator.h"
#include "MyTools.h"
using namespace DirectX; 
using namespace std;


typedef unsigned int UINT;

class ObjReader
{
public:
	ObjReader();
	~ObjReader();

	using uint16 = std::uint16_t;
	using uint32 = std::uint32_t;

	//Obj�ļ��У�������������涨�壬
	//ÿ�����������㣬
	//ÿ�����������������ꡢ��ͼ�����ߵ���Ϣ�����Obj�ļ��е�������
	struct ObjectGeometry
	{
		//��������֡�
		string name;
		//�������ꡣ
		 vector<uint32> LocationList;
		//��ͼ���ꡣ
		vector<uint32> TextureList;
		//���ߡ�
		vector<uint32> NormalList;
	};

public:
	//��ʼ������Ĵ�С�����ڹ����������Vector�ĳ�ʼ��С��
	static UINT initVectorSize;

protected:
	//��ȡָ����Obj�ļ���������ļ��е����е���Obj��ȡΪһ��unorderedMap��
	//ÿһ�����ֶ�Ӧһ����������
	static unique_ptr<unordered_map< 
		string, unique_ptr<vector<GeometryGenerator::MeshData>>>> ReadObjFile(string filePath);

	//��obj�ļ��ж�ȡ�ؼ����ݵ�����vector�С��ȴ������Ĵ���������ر��ļ���
	static void ReadKeyInfo(
		ifstream& openedFile,		//�Ѿ��򿪵�Obj�ļ�������������ϡ�
		vector<XMFLOAT3>& vs,		//�������껺�塣
		vector<XMFLOAT3>& vts,		//��ͼ���껺�塣
		vector<XMFLOAT3>& ns,		//�����������塣
		vector<unique_ptr<ObjectGeometry>>& geos);	//�����������壬�Լ�ÿ�����������

	//��obj�ļ��ж�ȡ�Ĺؼ����ݽ���ת�������MeshData��
	static unique_ptr<unordered_map<
		string, unique_ptr<vector<GeometryGenerator::MeshData>>>> Convert(
			vector<XMFLOAT3>& vs,		//�������껺�塣
			vector<XMFLOAT3>& vts,		//��ͼ���껺�塣
			vector<XMFLOAT3>& ns,		//�����������塣
			vector<unique_ptr<ObjectGeometry>>& geos);	//�����������壬�Լ�ÿ�����������

	//��ָ�����ַ�������ȡ�����������Ϣ��
	static void SaveVertexLocation(string& line, vector<XMFLOAT3>& vs);
	//��ָ�����ַ�������ȡ�������ͼ���ꡣ
	static void SaveTextureLocation(string& line, vector<XMFLOAT3>& vts);
	//��ָ�����ַ�������ȡ����ķ���������
	static void SaveNormal(string& line, vector<XMFLOAT3>& ns);

	//��֪��ǰ�ļ���ȡ��������g��ͷ����ʾһ�������壬��ǰ�е���Ϣ��line��
	//������ļ�����������������ȡ��������������Ϣ��
	//��ǰ�����������Ϣһ����ֹ������ֹ�ļ���ȡ��
	//������ر��ļ���
	static void ReadKeyInfo_For_OneGeometry(ifstream& openedFile, string& line, vector<unique_ptr<ObjectGeometry>>& geos);
};
