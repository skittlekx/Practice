#include "FileOpe.h"
#include <io.h>
#include <codecvt>
#include <Windows.h>
#include <vector>
#include <iostream>
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

bool FileOpe::Open(unsigned int mode)
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
	fio.open(fileName,mode);
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
	if(openFlag = Open(ios::out|ios::trunc))fio << inFile.rdbuf();
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


wstring FileOpe::stringToUTF8(const string & str)
{
	int nwLen = ::MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, NULL, 0);

	wchar_t * pwBuf = new wchar_t[nwLen + 1];//一定要加1，不然会出现尾巴 
	ZeroMemory(pwBuf, nwLen * 2 + 2);

	::MultiByteToWideChar(CP_ACP, 0, str.c_str(), str.length(), pwBuf, nwLen);

	wstring retStr(pwBuf);

	delete[]pwBuf;

	pwBuf = NULL;

	return retStr;
}

void FileOpe::SaveAsUtf8(const char* name)
{
	string sName(name);
	int _a = sName.find_last_of(".");
	string nName = sName.substr(0, _a).append("_utf8").append(sName.substr(_a));
	ifstream in(name);
	wofstream out(nName);
	out.imbue(locale("zh-CN.UTF-8"));
	string str;
	while (getline(in, str))
	{
		/*wstring_convert<codecvt_utf8<wchar_t>> conv;
		wstring ss = */
		//wstring ss = Ansi2WChar(str.c_str(), str.size());//conv.from_bytes(str);
		//wstring ss = L"1.233";
		//wstring ss = stringToUTF8(str);
		/*std::locale loc = std::locale::global(std::locale(".936", std::locale::ctype));
		setlocale(LC_ALL, "Chinese-simplified");*/
		
		wstring ss = stringToUTF8(str);
		//wcout << ss <<endl;
		out << ss << endl;
	}
	in.close();
	out.close();
	FileOpe tt(sName.c_str()),t1(nName.c_str());
	tt.CopyFrom(nName.c_str());
	t1.Rename(sName.c_str());
}

bool FileOpe::IsUtf8(const char* str)
{
	unsigned int nBytes = 0;//UFT8可用1-6个字节编码,ASCII用一个字节
	unsigned char chr = *str;
	bool bAllAscii = true;
	for (unsigned int i = 0; str[i] != '\0'; ++i) {
		chr = *(str + i);
		//判断是否ASCII编码,如果不是,说明有可能是UTF8,ASCII用7位编码,最高位标记为0,0xxxxxxx
		if (nBytes == 0 && (chr & 0x80) != 0) {
			bAllAscii = false;
		}
		if (nBytes == 0) {
			//如果不是ASCII码,应该是多字节符,计算字节数
			if (chr >= 0x80) {
				if (chr >= 0xFC && chr <= 0xFD) {
					nBytes = 6;
				}
				else if (chr >= 0xF8) {
					nBytes = 5;
				}
				else if (chr >= 0xF0) {
					nBytes = 4;
				}
				else if (chr >= 0xE0) {
					nBytes = 3;
				}
				else if (chr >= 0xC0) {
					nBytes = 2;
				}
				else {
					return false;
				}
				nBytes--;
			}
		}
		else {
			//多字节符的非首字节,应为 10xxxxxx
			if ((chr & 0xC0) != 0x80) {
				return false;
			}
			//减到为零为止
			nBytes--;
		}
	}
	//违返UTF8编码规则
	if (nBytes != 0) {
		return false;
	}
	if (bAllAscii) { //如果全部都是ASCII, 也是UTF8
		return true;
	}
	return true;
}