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
private:
	//��ʼ��
	void init();
	//���ļ�
	bool Open();
	//�ر��ļ�
	bool Close();


	std::string fileName;
	std::fstream fio;
	bool openFlag;
};
//bool comp(FileOpe& a, FileOpe& b);
