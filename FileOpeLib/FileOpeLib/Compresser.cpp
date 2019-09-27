#include "stdafx.h"
#include <time.h>
#include <io.h>
#include <windows.h>
#include "Compresser.h"

using namespace std;
//typedef unsigned long uLong;
#ifdef _WIN64
uLong filetime(const char* f, tm_zip* tmzip, uLong* dt)
{
	int ret = 0;
	{
		//FILETIME ftLocal;
		struct tm ft;
		//�ļ����
		__int64   hFile = 0;
		//�ļ���Ϣ
		struct __finddata64_t fileinfo;

		if ((hFile = _findfirst64(f, &fileinfo)) != -1)
		{
			_localtime64_s(&ft, &fileinfo.time_write);
			tmzip->tm_hour = ft.tm_hour;
			tmzip->tm_mday = ft.tm_mday;
			tmzip->tm_min = ft.tm_min;
			tmzip->tm_mon = ft.tm_mon;
			tmzip->tm_sec = ft.tm_sec;
			tmzip->tm_year = ft.tm_year-80;
			//dt = fileinfo.time_write;
			/*FileTimeToLocalFileTime(&(fileinfo.time_write), &ftLocal);
			FileTimeToDosDateTime(&ftLocal, ((LPWORD)dt) + 1, ((LPWORD)dt) + 0);*/
			_findclose(hFile);
			ret = 1;
		}
	}
	return ret;
}
#else
uLong filetime(const char* f,tm_zip* tmzip,uLong* dt)
{
	int ret = 0;
	{
		FILETIME ftLocal;
		HANDLE hFind;
		WIN32_FIND_DATA  ff32;

		hFind = FindFirstFile(f, &ff32);
		if (hFind != INVALID_HANDLE_VALUE)
		{
			FileTimeToLocalFileTime(&(ff32.ftLastWriteTime), &ftLocal);
			FileTimeToDosDateTime(&ftLocal, ((LPWORD)dt) + 1, ((LPWORD)dt) + 0);
			FindClose(hFind);
			ret = 1;
		}
	}
	return ret;
}
#endif

Compresser::Compresser()
{
	//m_cPath.assign("");
}


Compresser::~Compresser()
{
}

void Compresser::init(const char* path)
{
	m_Path.init(path);
	//return CreateZip();
}
bool Compresser::ToZip(const char* name)
{
	//m_Path.init(path);
	ZipName = name;
	return CreateZip();
}
bool Compresser::CreateZip() 
{
	ZipFile = zipOpen(ZipName.c_str(), APPEND_STATUS_CREATE); //����zip�ļ�
	if (ZipFile == NULL)
	{
		return false;
	}
	GetAllFile(m_Path,"");
	//CollectFilesInDirToZip(newZipFile, dirName, _T(""));
	zipClose(ZipFile, NULL); //�ر�zip�ļ�
	return true;
}
bool Compresser::AddToZip(const char* newName,const char* srcName, zip_fileinfo zi,int flag)
{
	string newFile = newName;
	string srcFile = srcName;
	int CompreLevel = flag; 
	FILE* srcfp = NULL;

	if (srcFile == "")
	{
		newFile.append("/");
	}
	if (CompreLevel != Z_NO_COMPRESSION  //0 
		&& CompreLevel != Z_BEST_SPEED   //1
		&& CompreLevel != Z_BEST_COMPRESSION //9
		)
	{
		CompreLevel = Z_DEFAULT_COMPRESSION; //-1
	}
	//��zip�ļ��д������ļ�
	zipOpenNewFileInZip(ZipFile, newFile.c_str(), &zi
		, NULL, 0, NULL, 0, NULL
		, CompreLevel == 0 ? 0 : Z_DEFLATED, 
		CompreLevel);

	if (srcFile != "")
	{
		//��Դ�ļ�
		srcfp = fopen(srcFile.c_str(), "rb");
		if (srcfp == NULL)
		{
			zipCloseFileInZip(ZipFile); //�ر�zip�ļ�
			return false;
		}

		//����Դ�ļ���д��zip�ļ�
		char buf[100 * 1024]; //buffer
		int numBytes = 0;
		while (!feof(srcfp))
		{
			numBytes = fread(buf, 1, sizeof(buf), srcfp);
			zipWriteInFileInZip(ZipFile, buf, numBytes);
			if (ferror(srcfp))
				break;
		}

		//�ر�Դ�ļ�
		fclose(srcfp);
	}

	//�ر�zip�ļ�
	zipCloseFileInZip(ZipFile);
}
void Compresser::GetAllFile(Folder root,string m_cPath)
{
	if (!m_cPath.empty())m_cPath.append("/");
	//��ʼ��д��zip���ļ���Ϣ
	zip_fileinfo zi;
	zi.tmz_date.tm_sec = zi.tmz_date.tm_min = zi.tmz_date.tm_hour =
		zi.tmz_date.tm_mday = zi.tmz_date.tm_mon = zi.tmz_date.tm_year = 0;
	zi.dosDate = 0;
	zi.internal_fa = 0;
	zi.external_fa = 0;
	if (root.getFileCount() != 0)
	{
		for (FileOpe i = root.getFirstFile(); !root.isEndFile(); root.getNextFile(i))
		{
			int flag = 9;
			if (i.getName() == "mimetype")flag = 0;
			filetime((i.getPath() + i.getName()).c_str(), &zi.tmz_date, &zi.dosDate);
			AddToZip((m_cPath + i.getName()).c_str(), (i.getPath() + i.getName()).c_str(), zi, flag);
		}
	}
	//�ݹ��ȡ�ļ���
	if (root.getFolderCount() != 0)
	{
		for (Folder i = root.getFirstFolder(); !root.isEndFolder(); root.getNextFolder(i))
		{
			string str;
			str.assign(m_cPath).append(i.getPathName());
			filetime(i.getPath().c_str(), &zi.tmz_date, &zi.dosDate);
			AddToZip(str.c_str(), "",zi,0);//����Ŀ¼�ṹ
			GetAllFile(i,str); //�ݹ�
		}
	}
	
}