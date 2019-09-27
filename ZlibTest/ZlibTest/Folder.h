#pragma once
#include <vector>
#include "FileOpe.h"
class Folder
{
public:
	Folder();
	~Folder();
	bool init(const char* path);
	void init64(const char*);
	void init32(const char*);
	int getFileCount();
	int getFolderCount();
	FileOpe& getFirstFile();
	bool getNextFile(FileOpe&);
	Folder& getFirstFolder();
	bool getNextFolder(Folder&);
	bool isEndFile();
	bool isEndFolder();
	std::string getPath()const;
	std::string getPathName()const;
	//添加文件或文件夹,在本文件夹内
	int AddFile(const char*);
	int AddFolder(const char*);
	//创建文件夹
	int CreateFolderAsFullPath(const char*);
	int CreateFolder(const char*);

	//创建文件
	int CreateFileAsFullPath(const char*);
	int _CreateFile(const char*);

	//查找文件或文件夹
	int SearchFile(const char*)const;
	FileOpe& FindFile(int);
	int SearchFolder(const char*)const;
	Folder& FindFolder(int);

	void test();
	bool operator<(const Folder&);//sort用，按路径名字符串排序
private:
	std::string m_Path;
	std::vector<FileOpe> FileList;
	std::vector<Folder> SubList;
	int fileCount;
	int SubCount;
	int currentFile;
	int currentFolder;
};