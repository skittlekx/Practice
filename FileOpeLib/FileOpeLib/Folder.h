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
	//����ļ����ļ���,�ڱ��ļ�����
	int AddFile(const char*);
	int AddFolder(const char*);
	//�����ļ���
	int CreateFolderAsFullPath(const char*);
	int CreateFolder(const char*);

	//�����ļ�
	int CreateFileAsFullPath(const char*);
	int _CreateFile(const char*);

	//�����ļ����ļ���
	int SearchFile(const char*)const;
	FileOpe& FindFile(int);
	int SearchFolder(const char*)const;
	Folder& FindFolder(int);

	void test();
	bool operator<(const Folder&);//sort�ã���·�����ַ�������
private:
	std::string m_Path;
	std::vector<FileOpe> FileList;
	std::vector<Folder> SubList;
	int fileCount;
	int SubCount;
	int currentFile;
	int currentFolder;
};