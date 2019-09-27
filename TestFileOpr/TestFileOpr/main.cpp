#include "FileOpe.h"
#include "Folder.h"
#include <Windows.h>
#include <iostream>
#include <string>
#include <codecvt>
#include "CChineseCode.h"
using namespace std;
typedef unsigned long  uLong;
typedef unsigned int   uInt;
typedef struct tm_zip_s
{
	uInt tm_sec;            /* seconds after the minute - [0,59] */
	uInt tm_min;            /* minutes after the hour - [0,59] */
	uInt tm_hour;           /* hours since midnight - [0,23] */
	uInt tm_mday;           /* day of the month - [1,31] */
	uInt tm_mon;            /* months since January - [0,11] */
	uInt tm_year;           /* years - [1980..2044] */
} tm_zip;
string UTF8ToGB(const char* str)
{
	string result;
	WCHAR *strSrc;
	LPSTR szRes;

	//获得临时变量的大小
	int i = MultiByteToWideChar(CP_UTF8, 0, str, -1, NULL, 0);
	strSrc = new WCHAR[i + 1];
	MultiByteToWideChar(CP_UTF8, 0, str, -1, strSrc, i);

	//获得临时变量的大小
	i = WideCharToMultiByte(CP_ACP, 0, strSrc, -1, NULL, 0, NULL, NULL);
	szRes = new CHAR[i + 1];
	WideCharToMultiByte(CP_ACP, 0, strSrc, -1, szRes, i, NULL, NULL);

	result = szRes;
	delete[]strSrc;
	delete[]szRes;

	return result;
}
string filter(const char* str)
{
	string res = str;
	unsigned char chr = *str;
	int k = 0;
	for (int i = 0; str[i] != 0; i++) {
		chr = *(str + i);
		if (chr == 63) {
			res.replace(i-(k++), 1, "");
		}
	}
	return res;
}
void print(const char* str)
{
	unsigned char chr = *str;
	unsigned char _str[256];
	int k = 0;
	for (unsigned int i = 0; str[i] != '\0'; i++) {
		chr = *(str + i);
		unsigned int a = chr;
		if (a > 127) {
			i++;
			chr = *(str + i);
			unsigned int b = chr;
			cout << a << " " << b << endl;
		}
		else {
			cout << a << endl;
		}
		
		/*if (a != 63 && b!=63) {
			_str[k++] = (unsigned char)a;
			_str[k++] = (unsigned char)b;
		}*/
		/*if (a != 63) {
			_str[k++] = (unsigned char)a;
		}
		if (b != 63) {
			_str[k++] = (unsigned char)b;
		}*/
	}
	//cout << filter(str) << endl;
	/*for (int i = 0; _str[i] != '\0'; i+=2)
	{
		cout << (int)_str[i] << ' ' << (int)_str[i + 1] << endl;
	}*/
}

void testRename() {
	Folder test;
	//test.init("E:\\PPW");
	test.init("E:\\动漫\\。。\\我的英雄学院\\[dmhy][Boku no hero academia][我的英雄學院][1080P]");
	int k = 0;
	for (FileOpe i = test.getFirstFile(); !test.isEndFile(); test.getNextFile(i))
	{
		string name;
		name.assign(i.getPath().append(i.getName()));
		string ints;
		ints = to_string(k++);
		ints.append(".txt");
		//cout << name << endl;
		if (i.Rename(ints.c_str()))
		{
			cout << name << "----改名成功!!!" << endl;
		}
		else
		{
			cout << name << "----改名失败!!!" << endl;
		}
	}

}
void testFile()
{
	//FileOpe test("E:\\动漫\\。。\\我的英雄学院\\[dmhy][Boku no hero academia][我的英雄學院][1080P]\\[dmhy][Boku no hero academia][01][x264_aac][1080P_MKV]_Track3");
	FileOpe test("E:\\[dmhy][Boku no hero academia][01][x264_aac][1080P_MKV]_Track3.ass");
	//FileOpe test("E:\\test.txt");
	test.Rename("000.txt");
	//test.Delete();
}
void testFolder()
{
	wstring_convert<codecvt_utf8<wchar_t>> conv;
	string mainPath = "C:\\Users\\skittle\\Desktop\\yishijiemigong";
	string tempPath = "C:\\Users\\skittle\\Desktop\\yishijiemigong\\temp\\temp.txt";
	int fail = 0;
	//当前一级、二级文件夹和文件
	int current1FolderInd = 0, current2FolderInd = 0;
	int currentFileInd = 0;
	Folder current1Folder, current2Folder;
	FileOpe currentFile;
	Folder main;// , temp;
	main.init(mainPath.c_str());
	//temp.init(tempPath.c_str());
	ifstream in("C:\\Users\\skittle\\Desktop\\user_out.txt");
	string Ustr;
	ofstream out(tempPath);
	while (getline(in, Ustr))
	{
		//wstring str = conv.from_bytes(Ustr);
		string str;
		CChineseCode::UTF_8ToGB2312(str, (char*)Ustr.c_str(), Ustr.length());
		//CChineseCode::GB2312ToUTF_8(str, (char*)str.c_str(), str.length());
		//string str = Ustr;
		string head30str; 
		string head6str; //'- - - '
		string head4str; //'- - '
		string head2str; //'- '
		string tail30str;
		string tail6str; //'- - - '
		string tail4str; //'- - '
		string tail2str; //'- '
		if (str.length() > 30)
		{
			head30str = str.substr(0, 30);
			tail30str = str.substr(30);
		}
		if (str.length() > 6)
		{
			head6str = str.substr(0, 6);
			tail6str = str.substr(6);
		}
		if (str.length() > 4)
		{
			head4str = str.substr(0, 4);
			tail4str = str.substr(4);
		}
		if (str.length() > 2)
		{
			head2str = str.substr(0, 2);
			tail2str = str.substr(2);
		}
		//if (head30str == " - - - - - - - - - - - - - -")
		if (head30str == "－－－－－－－－－－－－－－－")
		{
			if(tail30str == "BEGIN")
			{

				string tt,aim;
				getline(in, tt);getline(in, tt);
				tt = UTF8ToGB(tt.c_str());
				aim.assign(current2Folder.getPath()).append("\\").append(tt).append(".txt");
				currentFileInd = current2Folder.SearchFile(aim.c_str());
				if (currentFileInd == -1)
				{
					aim.assign(current2Folder.getPath()).append("\\").append(filter(tt.c_str())).append(".txt");
					currentFileInd = current2Folder.SearchFile(aim.c_str());
				}
				if (currentFileInd == -1)
				{
					cout << aim << "  写入失败" << endl;
					return;
				}
				currentFile = current2Folder.FindFile(currentFileInd);
				cout << aim << "正在写入。。。" << endl;
				continue;
			}
			else if (tail30str == "BODY")
			{
				out.open(tempPath);
				out << currentFile.getName().substr(0, currentFile.getName().length()-4) << endl;
				continue;
			}
			else if (tail30str == "END")
			{
				out.close();
				currentFile.CopyFrom(tempPath.c_str());
			}
		}
		else if (head30str == "＝＝＝＝＝＝＝＝＝＝＝＝＝＝＝")
		{
			if (tail30str == "CHECK")
			{
				string tt,aim1,aim2;
				getline(in, tt); getline(in, tt);
				tt = UTF8ToGB(tt.c_str());
				aim1.assign(mainPath).append("\\").append(tt);
				current1FolderInd = main.SearchFolder(aim1.c_str());
				current1Folder = main.FindFolder(current1FolderInd);
				getline(in, tt);
				tt = UTF8ToGB(tt.c_str());
				aim2.assign(current1Folder.getPath()).append("\\").append(tt);
				current2FolderInd = current1Folder.SearchFolder(aim2.c_str());
				if (current2FolderInd == -1)
				{
					aim2.assign(current1Folder.getPath()).append("\\").append(filter(tt.c_str()));
					current2FolderInd = current1Folder.SearchFolder(aim2.c_str());
				}
				if (current2FolderInd == -1)
				{
					cout << aim2 << "路径不存在！" << endl;
					return;
				}
				current2Folder = current1Folder.FindFolder(current2FolderInd);

			}
		}
		if (head6str == "- - - ")
		{
			cout << str << "create...";
			currentFileInd = current2Folder._CreateFile((tail6str + ".txt").c_str());
			if (currentFileInd == -1)
			{
				currentFileInd = current2Folder._CreateFile((filter(tail6str.c_str()) + ".txt").c_str());

			}
			if (currentFileInd == -1)
			{
				cout << "fail!!" << endl;
				fail++; //continue;
				cout << filter(str.c_str()) << endl;
				print(str.c_str()); 
				return;
			}
			cout << "Done!!" << endl;
			currentFile = current2Folder.FindFile(currentFileInd);
		}
		else if (head4str == "- - ")
		{
			cout << str << "create...";
			current2FolderInd = current1Folder.CreateFolder(tail4str.c_str());
			if (current2FolderInd == -1)
			{
				current2FolderInd = current1Folder.CreateFolder(filter(tail4str.c_str()).c_str());
			}
			if (current2FolderInd == -1)
			{
				cout << "fail!!" << endl;
				fail++;
				print(str.c_str()); 
				return;
				//return;
			}
			cout << "Done!!" << endl;
			current2Folder = current1Folder.FindFolder(current2FolderInd);
		}
		else if (head2str == "- ")
		{
			cout << str << "create...";
			current1FolderInd = main.CreateFolder(tail2str.c_str());
			if (current1FolderInd == -1)
			{
				current1FolderInd = main.CreateFolder(filter(tail2str.c_str()).c_str());
			}
			if (current1FolderInd == -1)
			{
				cout << "fail!!" << endl;
				fail++; 
				print(str.c_str());
				return;
			}
			cout << "Done!!" << endl;
			current1Folder = main.FindFolder(current1FolderInd);
		}
		out << str << endl;
	}
	cout << fail << endl;
	out.close();
	in.close();
}


uLong filetime(const char* f, tm_zip* tmzip, uLong* dt)
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
int main() {
	/*tm_zip tmz;
	uLong dt;
	const char* chr = "C:\\Users\\skittle\\Desktop\\233\\233";
	filetime(chr, &tmz, &dt);*/
	/*testRename();*/
	
	testFolder();

	//Folder tt;
	//tt.init("C:\\Users\\skittle\\Desktop\\233\\233");
	//Folder F;
	//F.init("C:\\Users\\skittle\\Desktop\\yishijiemigong\\temp");
	//F.CreateFolder("test");
	//F.FindFolder(0)._CreateFile("test.txt");
	//F.FindFolder(0)._CreateFile("test1.txt");
	//F.FindFolder(0)._CreateFile("test3.txt");
	//F.FindFolder(0).test();
	//cout << "----------------" << endl;
	//for (FileOpe i = F.FindFolder(0).getFirstFile(); !F.FindFolder(0).isEndFile(); F.FindFolder(0).getNextFile(i)) {
	//	//i.CopyFrom("C:\\Users\\skittle\\Desktop\\user_out.txt");
	//	cout << &i << endl;
	//	i.CopyFrom("C:\\Users\\skittle\\Desktop\\yishijiemigong\\temp\\temp.txt");
	//}
	


	/*FileOpe test("C:\\Users\\skittle\\Desktop\\yishijiemigong\\temp\\temp1.txt");
	test.CopyFrom("C:\\Users\\skittle\\Desktop\\yishijiemigong\\temp\\temp.txt");*/
	system("pause");
	return 0;
}