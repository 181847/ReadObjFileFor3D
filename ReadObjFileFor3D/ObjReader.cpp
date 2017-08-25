#include "ObjReader.h"

//初始缓冲大小。
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
		outputString = "读取文件失败，请检查文件：" + filePath;
		throw SimpleException(outputString.c_str(), __FILE__, __LINE__);
	}

	//顶点坐标。
	vector<XMFLOAT3> vertextLocations	= vector<XMFLOAT3>(initVectorSize);
	//顶点贴图坐标。
	vector<XMFLOAT3> textureLocations	= vector<XMFLOAT3>(initVectorSize);
	//顶点法线，因为一般来讲法线的定义比顶点坐标要多，所以这里的vector多分配一些空间。
	vector<XMFLOAT3> normals			= vector<XMFLOAT3>(initVectorSize * 7);
	//单个物体的定义，这里面包括这个物体所有三角面的索引。
	vector<unique_ptr<ObjectGeometry>> Geometrys = vector<unique_ptr<ObjectGeometry>>();

	//读取关键数据，因为obj文件中的数据是全局的，所以先整个读取，之后再转换。
	ReadKeyInfo(
		fileStream,					//目标文件流
		vertextLocations,		//所有顶点坐标定义
		textureLocations,		//贴图坐标定义。
		normals,				//法线方向定义。
		Geometrys);			//所有几何体的定义。

	//关闭文件。
	fileStream.close();
	
	//整理所有读取的数据，转换为MeshData，并且每一个单独的子网格放到一个MeshData中。
	return Convert(				//目标文件流
		vertextLocations,		//所有顶点坐标定义
		textureLocations,		//贴图坐标定义。
		normals,				//法线方向定义。
		Geometrys);			//所有几何体的定义。
}

void ObjReader::ReadKeyInfo(ifstream & openedFile, vector<XMFLOAT3>& vs, 
	vector<XMFLOAT3>& vts, vector<XMFLOAT3>& ns, vector<unique_ptr<ObjectGeometry>>& geos)
{
	string lineBuffer;
	
	//读到文件末尾。
	while (!openedFile.eof())
	{
		//读取一行。
		getline(openedFile, lineBuffer);

		//查看第一个字符。
		switch (lineBuffer[0])
		{
			//顶点坐标、贴图、法线。
		case 'v':
			//进一步检查第二个字符。
			switch (lineBuffer[1])
			{
				//顶点坐标
			case ' ':
				//存储顶点坐标。
				SaveVertexLocation(lineBuffer, vs);
				break;

				//贴图坐标
			case 't':
				SaveTextureLocation(lineBuffer, vts);
				break;

				//法线向量
			case 'n':
				SaveNormal(lineBuffer, ns);
				break;

			default:
				break;
			}
			break;

			//单个几何体。
		case 'g':
			//读取一个几何体的面信息。
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
	//以空格分割字符串，注意表示顶点的这一行类似：“v  -3.2065 1.9203 -7.3193”
	//其中v后面有两个空格，这会使得分割出来的字符串有一个空的，注意跳过。
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
	//以空格分割字符串，注意表示顶点的这一行类似：“vt -3.2065 1.9203 -7.3193”。
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
	//以空格分割字符串，注意表示顶点的这一行类似：“vn -3.2065 1.9203 -7.3193”。
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

