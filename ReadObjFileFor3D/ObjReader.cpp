#include "ObjReader.h"

//��ʼ�����С��
UINT ObjReader::initVectorSize = 100;

ObjReader::ObjReader()
{
}


ObjReader::~ObjReader()
{
}

unique_ptr<unordered_map<
	string, unique_ptr<vector<GeometryGenerator::MeshData>>>> ObjReader::ReadObjFile(string filePath)
{
	ifstream fileStream(filePath);
	if ( ! fileStream.is_open())
	{
		string outputString;
		outputString = "��ȡ�ļ�ʧ�ܣ������ļ���" + filePath;
		throw SimpleException(outputString.c_str(), __FILE__, __LINE__);
	}

	//�������ꡣ
	vector<XMFLOAT3> vertextLocations	= vector<XMFLOAT3>(initVectorSize);
	//������ͼ���ꡣ
	vector<XMFLOAT3> textureLocations	= vector<XMFLOAT3>(initVectorSize);
	//���㷨�ߣ���Ϊһ���������ߵĶ���ȶ�������Ҫ�࣬���������vector�����һЩ�ռ䡣
	vector<XMFLOAT3> normals			= vector<XMFLOAT3>(initVectorSize * 7);
	//��������Ķ��壬���������������������������������
	vector<unique_ptr<ObjectGeometry>> Geometrys = vector<unique_ptr<ObjectGeometry>>();

	//��ȡ�ؼ����ݣ���Ϊobj�ļ��е�������ȫ�ֵģ�������������ȡ��֮����ת����
	ReadKeyInfo(
		fileStream,					//Ŀ���ļ���
		vertextLocations,		//���ж������궨��
		textureLocations,		//��ͼ���궨�塣
		normals,				//���߷����塣
		Geometrys);			//���м�����Ķ��塣

	//�ر��ļ���
	fileStream.close();
	
	//�������ж�ȡ�����ݣ�ת��ΪMeshData������ÿһ��������������ŵ�һ��MeshData�С�
	return Convert(				//Ŀ���ļ���
		vertextLocations,		//���ж������궨��
		textureLocations,		//��ͼ���궨�塣
		normals,				//���߷����塣
		Geometrys);			//���м�����Ķ��塣
}

void ObjReader::ReadKeyInfo(ifstream & openedFile, vector<XMFLOAT3>& vs, 
	vector<XMFLOAT3>& vts, vector<XMFLOAT3>& ns, vector<unique_ptr<ObjectGeometry>>& geos)
{
	string lineBuffer;
	
	//�����ļ�ĩβ��
	while (!openedFile.eof())
	{
		//��ȡһ�С�
		getline(openedFile, lineBuffer);

		//�鿴��һ���ַ���
		switch (lineBuffer[0])
		{
			//�������ꡢ��ͼ�����ߡ�
		case 'v':
			//��һ�����ڶ����ַ���
			switch (lineBuffer[1])
			{
				//��������
			case ' ':
				//�洢�������ꡣ
				SaveVertexLocation(lineBuffer, vs);
				break;

				//��ͼ����
			case 't':
				SaveTextureLocation(lineBuffer, vts);
				break;

				//��������
			case 'n':
				SaveNormal(lineBuffer, ns);
				break;

			default:
				break;
			}
			break;

			//���������塣
		case 'g':
			//��ȡһ�������������Ϣ��
			ReadKeyInfo_For_OneGeometry(openedFile, lineBuffer, geos);
			break;

		default:
			break;
		}
	}
}

void ObjReader::SaveVertexLocation(string & line, vector<XMFLOAT3>& vs)
{
	vector<string> subStrings(5);
	//�Կո�ָ��ַ�����ע���ʾ�������һ�����ƣ���v  -3.2065 1.9203 -7.3193��
	//����v�����������ո����ʹ�÷ָ�������ַ�����һ���յģ�ע��������
	SplitString(line, subStrings, " ");

	vs.push_back(
		XMFLOAT3( 
				strtof(subStrings[2].c_str(), nullptr), 
				strtof(subStrings[3].c_str(), nullptr), 
				strtof(subStrings[4].c_str(), nullptr) 
			)
		);
}

void ObjReader::SaveTextureLocation(string & line, vector<XMFLOAT3>& vts)
{
	vector<string> subStrings(5);
	//�Կո�ָ��ַ�����ע���ʾ�������һ�����ƣ���vt -3.2065 1.9203 -7.3193����
	SplitString(line, subStrings, " ");

	vts.push_back(
		XMFLOAT3(
			strtof(subStrings[1].c_str(), nullptr),
			strtof(subStrings[2].c_str(), nullptr),
			strtof(subStrings[3].c_str(), nullptr)
		)
	);
}

void ObjReader::SaveNormal(string & line, vector<XMFLOAT3>& ns)
{
	vector<string> subStrings(5);
	//�Կո�ָ��ַ�����ע���ʾ�������һ�����ƣ���vn -3.2065 1.9203 -7.3193����
	SplitString(line, subStrings, " ");

	ns.push_back(
		XMFLOAT3(
			strtof(subStrings[1].c_str(), nullptr),
			strtof(subStrings[2].c_str(), nullptr),
			strtof(subStrings[3].c_str(), nullptr)
		)
	);
}

void ObjReader::ReadKeyInfo_For_OneGeometry(ifstream & openedFile, string & line, vector<unique_ptr<ObjectGeometry>>& geos)
{
}

