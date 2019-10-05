// emmm.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#include "pch.h"
#include <iostream>
#include <windows.h>
#include <direct.h>
#include <fstream>
#include <string>
#include <vector>
#include <stdarg.h>
using namespace std;

/**
 * 功能：格式化字符串
 * 参数：
 *  @pszFmt，格式描述
 *  @...，不定参数
 * 返回值：格式化的结果字符串
 */
string format(const char *pszFmt, ...)
{
	string str;
	va_list args;
	va_start(args, pszFmt);
	{
		int nLength = _vscprintf(pszFmt, args);
		nLength += 1;  //上面返回的长度是包含\0，这里加上
		std::vector<char> vectorChars(nLength);
		_vsnprintf(vectorChars.data(), nLength, pszFmt, args);
		str.assign(vectorChars.data());
	}
	va_end(args);
	return str;
}

bool dirExists(const std::string& dirName_in)
{
	DWORD ftyp = GetFileAttributesA(dirName_in.c_str());
	if (ftyp == INVALID_FILE_ATTRIBUTES)
		return false;  //something is wrong with your path!  

	if (ftyp & FILE_ATTRIBUTE_DIRECTORY)
		return true;   // this is a directory!  

	return false;    // this is not a directory!  
}
void cut()
{
	string path = "..\\..\\..\\ff.txt";
	string root = "..\\..\\..\\233\\";
	string target = root;
	const string tag = "";
	string txtIndex = format("%04d.txt", 0);
	string file = target + txtIndex;
	ifstream fin(path);
	ofstream fout(file);
	if (fin.fail())
	{
		return;
	}
	if (fout.fail())
	{
		return;
	}
	string buff;
	int index = 0;
	int k = 0;
	while (!fin.eof())
	{
		getline(fin, buff);
		if (buff.compare(tag) == 0)
		{
			fout.close();
			txtIndex = format("%04d.txt", ++index);
			file = target + txtIndex;
			fout.open(file);
			getline(fin, buff);
			//while (buff.length() == 0)
			//{
			//	getline(fin, buff);
			//	fout << buff << endl;
			//}
			//string buff2;
			//getline(fin, buff2);
			//while (buff2.length() == 0)
			//{
			//	fout << buff << endl;
			//	getline(fin, buff2);
			//}
			//if (buff2.compare(tag) == 0)
			//{
			//	string temp = root + "%02d" + buff + "\\";
			//	temp = format(temp.c_str(), k++);
			//	if (!dirExists(temp))
			//	{
			//		//CreateDirectory(LPCWSTR(temp.c_str()), NULL);
			//		_mkdir(temp.c_str());
			//		target = temp;
			//	}
			//	continue;
			//}
			//fout << buff << endl;
			continue;
		}
		fout << buff << endl;
	}
}

int main()
{
   // std::cout << "Hello World!\n"; 
	cut();
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门提示: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
