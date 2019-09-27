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
	//���������ı䴢��·��
	bool Rename(const char* newName);
	//���ļ��ƶ���ָ��·����Ĭ��ɾ����ǰ�ļ�
	bool MoveTo(const char* newPath,bool isDelete = true);
	//ɾ���ļ�
	bool Delete();

	//��ָ���ļ��������ļ�
	bool CopyFrom(const char* sourceFile);
	
	//�Ƿ��
	bool isOpen();
	//�ļ��Ƿ����
	bool isExist();
	//�����ļ���
	std::string getName() const;
	//�����ļ�·��
	std::string getPath() const;
	//�����ļ���չ��
	std::string getExtension() const;

	bool operator<(const FileOpe&);// , const FileOpe& b);
	static void SaveAsUtf8(const char* name);
	static std::wstring stringToUTF8(const std::string & str);
	static bool IsUtf8(const char* str);
private:
	//��ʼ��
	void init();
	//���ļ�
	bool Open(unsigned int mode = std::ios::in | std::ios::out);
	//�ر��ļ�
	bool Close();


	std::string fileName;
	std::fstream fio;
	bool openFlag;
};
//bool comp(FileOpe& a, FileOpe& b);
