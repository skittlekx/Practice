#pragma once
#include <string>
#include <Windows.h>
using namespace std;
class CChineseCode
{
public:
	static void UTF_8ToUnicode(wchar_t* pOut, const char *pText);  // 把UTF-8转换成Unicode
	static void UnicodeToUTF_8(char* pOut, const wchar_t* pText);  //Unicode 转换成UTF-8
	static void UnicodeToGB2312(char* pOut, const wchar_t uData);  // 把Unicode 转换成 GB2312 
	static void Gb2312ToUnicode(wchar_t* pOut, const char *gbBuffer);// GB2312 转换成　Unicode
	static void GB2312ToUTF_8(string& pOut, const char *pText, int pLen);//GB2312 转为 UTF-8
	static void UTF_8ToGB2312(string &pOut, const char *pText, int pLen);//UTF-8 转为 GB2312
};


