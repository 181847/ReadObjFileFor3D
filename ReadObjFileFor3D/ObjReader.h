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

	//Obj文件中，单个子网格的面定义，
	//每个面三个顶点，
	//每个顶点包含顶点的坐标、贴图、法线的信息在这个Obj文件中的索引。
	struct ObjectGeometry
	{
		//网格的名字。
		string name;
		//顶点坐标。
		 vector<uint32> LocationList;
		//贴图坐标。
		vector<uint32> TextureList;
		//法线。
		vector<uint32> NormalList;
	};

public:
	//初始化缓冲的大小，用于构建绝大多数Vector的初始大小。
	static UINT initVectorSize;

protected:
	//读取指定的Obj文件，将这个文件中的所有单个Obj读取为一个unorderedMap，
	//每一个名字对应一个物体网格。
	static unique_ptr<unordered_map< 
		string, unique_ptr<vector<GeometryGenerator::MeshData>>>> ReadObjFile(string filePath);

	//从obj文件中读取关键数据到各个vector中。等待后续的处理，不负责关闭文件。
	static void ReadKeyInfo(
		ifstream& openedFile,		//已经打开的Obj文件流，不负责关上。
		vector<XMFLOAT3>& vs,		//顶点坐标缓冲。
		vector<XMFLOAT3>& vts,		//贴图坐标缓冲。
		vector<XMFLOAT3>& ns,		//法线向量缓冲。
		vector<unique_ptr<ObjectGeometry>>& geos);	//单个子网格定义，以及每个面的索引。

	//将obj文件中读取的关键数据进行转化，变成MeshData。
	static unique_ptr<unordered_map<
		string, unique_ptr<vector<GeometryGenerator::MeshData>>>> Convert(
			vector<XMFLOAT3>& vs,		//顶点坐标缓冲。
			vector<XMFLOAT3>& vts,		//贴图坐标缓冲。
			vector<XMFLOAT3>& ns,		//法线向量缓冲。
			vector<unique_ptr<ObjectGeometry>>& geos);	//单个子网格定义，以及每个面的索引。

	//从指定的字符串中提取顶点的坐标信息。
	static void SaveVertexLocation(string& line, vector<XMFLOAT3>& vs);
	//从指定的字符串中提取顶点的贴图坐标。
	static void SaveTextureLocation(string& line, vector<XMFLOAT3>& vts);
	//从指定的字符串中提取顶点的法线向量。
	static void SaveNormal(string& line, vector<XMFLOAT3>& ns);

	//已知当前文件读取的行数是g打头，表示一个几何体，当前行的信息是line，
	//从这个文件接下来的内容中提取这个几何体的面信息，
	//当前几何体的面信息一旦终止，便终止文件读取，
	//不负责关闭文件。
	static void ReadKeyInfo_For_OneGeometry(ifstream& openedFile, string& line, vector<unique_ptr<ObjectGeometry>>& geos);
};
