#pragma once
#include <fstream>
#include <string>
class FileOpe
{
public:
	FileOpe();
	FileOpe(const char* name);
	FileOpe(const FileOpe& tt);
	~FileOpe();
	FileOpe& operator=(const FileOpe& tt);
	//改名，不改变储存路径
	bool Rename(const char* newName);
	//将文件移动向指定路径，默认删除当前文件
	bool MoveTo(const char* newPath,bool isDelete = true);
	//删除文件
	bool Delete();

	//从指定文件处拷贝文件
	bool CopyFrom(const char* sourceFile);
	
	//是否打开
	bool isOpen();
	//文件是否存在
	bool isExist();
	//返回文件名
	std::string getName() const;
	//返回文件路径
	std::string getPath() const;
	//返回文件扩展名
	std::string getExtension() const;

	bool operator<(const FileOpe&);// , const FileOpe& b);
private:
	//初始化
	void init();
	//打开文件
	bool Open();
	//关闭文件
	bool Close();


	std::string fileName;
	std::fstream fio;
	bool openFlag;
};
//bool comp(FileOpe& a, FileOpe& b);
