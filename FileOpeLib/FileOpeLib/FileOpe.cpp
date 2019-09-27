#include "stdafx.h"
#include "FileOpe.h"
#include <io.h>
using namespace std;


FileOpe::FileOpe()
{
	init();
}

FileOpe::FileOpe(const char* name)
{
	init();
	//openFlag = Open(name);
	fileName = name;
	/*if (!isExist())
	{
		fileName.assign("");
	}*/
}

FileOpe::FileOpe(const FileOpe& tt)
{
	init();
	fileName = tt.getPath() + tt.getName();
}
FileOpe& FileOpe::operator=(const FileOpe& tt)
{
	init();
	fileName = tt.getPath() + tt.getName();
	return *this;
}
bool FileOpe::operator<(const FileOpe& a)
{
	return this->getName() < a.getName();
}
FileOpe::~FileOpe()
{
	Close();
	init();
}

void FileOpe::init()
{
	openFlag = false;
	fileName.clear();
	fio.clear();
	fileName = "";
}

bool FileOpe::Open()
{
	//fileName = name;
	if (!isExist())
	{
		return false;
	}
	if (openFlag)
	{
		return openFlag;
	}
	fio.open(fileName);
	openFlag = !fio.fail();
	return openFlag;
}

bool FileOpe::Close()
{
	if (!fio.is_open())
	{
		return true;
	}
	fio.close();
	//init();
	openFlag = fio.is_open();
	return !openFlag;
}

bool FileOpe::Rename(const char* newName)
{
	if (getName() == newName)// != 0)
	{
		return false;
	}
	if (!openFlag) openFlag = Open();
	string path = getPath() + newName;

	ofstream newFile(path);
	/*string temp;
	while (getline(fio, temp))
	{
		newFile << temp << endl;
	}*/
	newFile << fio.rdbuf();
	newFile.close();
	Delete();
	fileName = path;
	Close();
	return true;
}

bool FileOpe::Delete()
{
	if (isOpen())Close();
	if (!isExist())return false;
	if (remove(fileName.c_str()))return false;
	else return true;
}

bool FileOpe::MoveTo(const char* newPath, bool isDelete)
{
	bool res = true;
	if (!openFlag)
	{
		openFlag = Open();
	}
	string str = newPath;
	str += '\\' + getName();
	ofstream newFile(str);
	if (newFile.fail()) return false;
	/*string temp;
	while (getline(fio,temp))
	{
		newFile << temp << endl;
	}*/
	newFile << fio.rdbuf();
	newFile.close();
	if (isDelete) res = Delete();

	init();
	fileName = str;
	Close();
	return res;
}

bool FileOpe::CopyFrom(const char* sourceFile)
{
	ifstream inFile(sourceFile);
	if (inFile.fail())return false;
	if (fileName.empty())return false;
	Close();
	if(openFlag = Open())fio << inFile.rdbuf();
	else return false;
	/*string temp;
	while (getline(inFile, temp))
	{
		fio << temp << endl;
	}*/
	
	inFile.close();
	return true;
}

bool FileOpe::isOpen()
{
	if (fileName.empty() || !fio.is_open())
	{
		return false;
	}
	return fio.is_open();
}

bool FileOpe::isExist()
{
	if (_access(fileName.c_str(), 0) == -1) return false;
	else return true;

}
string FileOpe::getName()const
{
	int a = fileName.find_last_of('\\');
	if (a == -1) return string();
	basic_string <char> res = fileName.substr(a+1);
	return res;
}
string FileOpe::getPath()const
{
	int a = fileName.find_last_of('\\');
	if (a == -1) return string();
	basic_string <char> res = fileName.substr(0, a+1);
	return res;
}
string FileOpe::getExtension()const
{
	int a = fileName.find_last_of('.');
	if (a == -1) return string();
	basic_string <char> res = fileName.substr(a+1);
	return res;
}
