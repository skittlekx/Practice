#include "Folder.h"
#include <io.h>
#include <direct.h>
#include <algorithm>
#include <iostream>
using namespace std;

Folder::Folder()
{
}


Folder::~Folder()
{
}
bool Folder::operator<(const Folder& a)
{
	return this->getPath() < a.getPath();
}
bool Folder::init(const char* path)
{
	if (_access(path, 0) == -1) return false;
	m_Path.assign(path);
	fileCount = 0;
	SubCount = 0;
#ifdef _WIN64
	init64(path);
#else
	init32(path);
#endif
	sort(FileList.begin(), FileList.end());
	sort(SubList.begin(), SubList.end());
	currentFile = -1;
	currentFolder = -1;
	return true;
}

void Folder::init64(const char* path)
{
	//文件句柄
	__int64   hFile = 0;
	//文件信息
	struct __finddata64_t fileinfo;
	string p;
	if ((hFile = _findfirst64(p.assign(path).append("\\*").c_str(), &fileinfo)) != -1)
	{
		do
		{
			//如果是目录,迭代之
			//如果不是,加入列表
			if ((fileinfo.attrib &  _A_SUBDIR))
			{
				if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0)
				{
					Folder temp;
					temp.init(p.assign(path).append("\\").append(fileinfo.name).c_str());
					SubList.push_back(temp);
					SubCount++;
				}
			}
			else
			{
				FileOpe temp(p.assign(path).append("\\").append(fileinfo.name).c_str());
				FileList.push_back(temp);
				fileCount++;
			}
		} while (_findnext64(hFile, &fileinfo) == 0);
		_findclose(hFile);
	}
}
void Folder::init32(const char* path)
{
	//文件句柄
	long   hFile = 0;
	//文件信息
	struct _finddata_t fileinfo;
	string p;
	if ((hFile = _findfirst(p.assign(path).append("\\*").c_str(), &fileinfo)) != -1)
	{
		do
		{
			//如果是目录,迭代之
			//如果不是,加入列表
			if ((fileinfo.attrib &  _A_SUBDIR))
			{
				if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0)
				{
					Folder temp;
					temp.init(p.assign(path).append("\\").append(fileinfo.name).c_str());
					SubList.push_back(temp);
					SubCount++;
				}
			}
			else
			{
				FileOpe temp(p.assign(path).append("\\").append(fileinfo.name).c_str());
				FileList.push_back(temp);
				fileCount++;
			}
		} while (_findnext(hFile, &fileinfo) == 0);
		_findclose(hFile);
	}
}

int Folder::getFileCount()
{
	return fileCount;
}
int Folder::getFolderCount()
{
	return SubCount;
}
FileOpe& Folder::getFirstFile()
{
	currentFile = 1;
	return FileList[currentFile-1];
}

bool Folder::getNextFile(FileOpe& res)
{
	currentFile++;
	if (currentFile <= 0 ||currentFile == fileCount+1)return false;
	
	//currentFile %= fileCount - 1;
	res = FileList[currentFile-1];
	return true;
}

bool Folder::isEndFile()
{
	return currentFile == fileCount+1;
}

Folder& Folder::getFirstFolder()
{
	currentFolder = 1;
	return SubList[currentFolder - 1];
}

bool Folder::getNextFolder(Folder& res)// :getNextFile(FileOpe& res)
{
	currentFolder++;
	if (currentFolder <= 0 || currentFolder == SubCount + 1)return false;

	//currentFile %= fileCount - 1;
	res = SubList[currentFolder - 1];
	return true;
}

bool Folder::isEndFolder()
{
	return currentFolder == SubCount + 1;
}

string Folder::getPath()const
{
	return m_Path;
}
string Folder::getPathName()const
{
	string res;
	res = m_Path.substr(m_Path.find_last_of('\\')+1);
	return res;
}

int Folder::CreateFileAsFullPath(const char* name)
{
	if (_access(name, 0) != -1)
	{
		return SearchFile(name);
	}
	ofstream tem(name);
	if (tem.fail())return -1;
	fileCount++;
	FileOpe tt(name);
	FileList.push_back(tt);
	sort(FileList.begin(), FileList.end());
	tem.close();
	return SearchFile((tt.getPath() + tt.getName()).c_str());
	//return fileCount - 1;
}
int Folder::_CreateFile(const char* name)
{
	string str;
	str.assign(m_Path).append("\\").append(name);
	if (_access(str.c_str(), 0) != -1)
	{
		return SearchFile(str.c_str());
	}
	ofstream tem(str);
	if (tem.fail())return -1;
	fileCount++;
	FileOpe *tt = new FileOpe(str.c_str());
	FileList.push_back(*tt);
	sort(FileList.begin(), FileList.end());
	tem.close();
	return SearchFile((tt->getPath() + tt->getName()).c_str());
}
int Folder::CreateFolder(const char* name)
{
	string str;
	str.assign(m_Path).append("\\").append(name);
	if (_access(str.c_str(), 0) != -1)
	{
		return SearchFolder(str.c_str());
	}
	_mkdir(str.c_str());
	SubCount++;
	Folder tt;
	tt.init(str.c_str());
	SubList.push_back(tt);
	sort(SubList.begin(), SubList.end());
	return SearchFolder(tt.getPath().c_str());
	//return SubCount - 1;
}
int Folder::CreateFolderAsFullPath(const char* name)
{
	if (_access(name, 0) != -1)
	{
		return SearchFolder(name);
	}
	_mkdir(name);
	SubCount++;
	Folder tt;
	tt.init(name);
	SubList.push_back(tt);
	sort(SubList.begin(), SubList.end());
	return SearchFolder(tt.getPath().c_str());
	//return SubCount - 1;
}

int Folder::SearchFile(const char* name)const
{
	/*for (int i = 0; i < FileList.size(); i++)
	{
		if (FileList[i].getPath() + FileList[i].getName() == name)
		{
			return i;
		}
	}*/
	if (fileCount == 0)return -1;
	else if (fileCount == 1)
	{
		if ((FileList[0].getPath() + FileList[0].getName()) != name)
			return -1;
		else return 0;
	}
	for (int a = 0, b = FileList.size() - 1; a <= b;)
	{
		if (a + 1 >= b) 
			if ((FileList[a].getPath() + FileList[a].getName()) == name) return a;
			else if((FileList[b].getPath() + FileList[b].getName()) == name)return b;
			else return -1;

		int c = (a + b) / 2;
		string com = FileList[c].getPath() + FileList[c].getName();
		if (com < name) {
			a = c;
		}
		else if (com > name)
		{
			b = c;
		}
		else
			return c;
	}
}
FileOpe& Folder::FindFile(int ind)
{
	return FileList[ind];
}
int Folder::SearchFolder(const char* path)const
{
	/*for (int i = 0; i < FileList.size(); i++)
	{
		if (SubList[i].getPath() == path)
		{
			return i;
		}
	}*/
	if (SubCount == 0)return -1;
	else if (SubCount == 1)
	{
		if ((SubList[0].getPath() == path))return 0;
		else return -1;
	}
	for (int a = 0, b = SubList.size() - 1; a < b;)
	{
		if (a == b)
			if (SubList[a].getPath() == path) return a;
			else return -1;
		if (a + 1 >= b)
			if (SubList[a].getPath() == path)return a;
			else if (SubList[b].getPath() == path)return b;
			else return -1;

		int c = (a + b) / 2;
		string com = SubList[c].getPath();// +SubList[c].getName();
		if (com < path) {
			a = c;
		}
		else if (com > path)
		{
			b = c;
		}
		else
			return c;
		
	}
}
Folder& Folder::FindFolder(int ind)
{
	return SubList[ind];
}

int Folder::AddFile(const char* name)
{
	string str;
	str.assign(m_Path).append("\\").append(name);
	if (fileCount == 1)
	{
		if ((FileList[0].getPath() + FileList[0].getName()) > name)
		{
			FileOpe tt(str.c_str());
			FileList.insert(FileList.begin(), tt);
			fileCount++;
			return 0;
		}
		else if ((FileList[0].getPath() + FileList[0].getName()) < name)
		{
			FileOpe tt(str.c_str());
			FileList.insert(FileList.begin()+1, tt);
			fileCount++;
			return 1;
		}
		else return 0;
	}
	for (int a = 0, b = FileList.size() - 1; a < b;)
	{
		if (a + 1 >= b)
			if ((FileList[a].getPath() + FileList[a].getName()) == name) return a;
			else if ((FileList[b].getPath() + FileList[b].getName()) == name)return b;
			else {
				FileOpe tt(str.c_str());
				FileList.insert(FileList.begin() + b, tt);
				fileCount++;
				return b;
			}
		int c = (a + b) / 2;
		string com = FileList[c].getPath() + FileList[c].getName();
		if (com < str) {
			a = c;
		}
		else if (com > str)
		{
			b = c;
		}
		else
			return c;
	}
}
int Folder::AddFolder(const char* path)
{
	string str;
	str.assign(m_Path).append("\\").append(path);
	for (int a = 0, b = SubList.size() - 1; a < b;)
	{
		if (a == b)
			if (SubList[a].getPath() == path) return a;
			else {
				Folder tt;
				tt.init(str.c_str());
				SubList.insert(SubList.begin() + b, tt);
				SubCount++;
				return b;
			}
		if (a + 1 >= b)
			if (SubList[a].getPath() == path)return a;
			else if (SubList[b].getPath() == path)return b;
			else {
				Folder tt;
				tt.init(str.c_str());
				SubList.insert(SubList.begin() + b, tt);
				SubCount++;
				return b;
			}

		int c = (a + b) / 2;
		string com = SubList[c].getPath();// +SubList[c].getName();
		if (com < path) {
			a = c;
		}
		else if (com > path)
		{
			b = c;
		}
		else
			return c;

	}
}

void Folder::test()
{
	for(int i=0;i<fileCount;i++)
		std::cout << &FileList[i] << endl;
}