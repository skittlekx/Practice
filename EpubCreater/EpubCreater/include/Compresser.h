#pragma once
#include "Folder.h"
#include "./unzip101e/zip.h"
#include "./unzip101e/unzip.h"
class Compresser
{
public:
	Compresser();
	~Compresser();
	void init(const char*);
	bool ToZip(const char*);
private:
	bool CreateZip();
	bool AddToZip(const char*, const char*, zip_fileinfo,int);
	void GetAllFile(Folder,std::string);
private:
	Folder m_Path;
	zipFile ZipFile;
	std::string ZipName;
//	std::string m_cPath;
};

