#include <iostream>
#include "EpubCreater.h"
using namespace std;
void toEpub()
{
	const char* ResPath = "C:\\Users\\skittle\\Downloads\\233";
	const char* AimPath = "C:\\Users\\skittle\\Downloads\\fan";
	Folder Res;
	Res.init(ResPath);
	METADATA md;
	{
		md.author = "跳舞";
		md.ID = "123456";
		md.creator = "skx";
		md.date = "2019-9-9";
		md.language = "zh-CN";
	}
	//单本
	EpubCreater book;
	string tName = "猎国";
	md.title = tName;
	cout << tName << "  Create.......";
	book.init(tName.c_str(), AimPath);
	book.AddFromTxtsFolder(Res.getPath().c_str());

	book.SetMetaData(md);
	book.WriteToEpub();
	cout << "Done!" << endl;
	//多本
	/*for (Folder i = Res.getFirstFolder(); !Res.isEndFolder(); Res.getNextFolder(i))
	{
		
		EpubCreater book;
		string tName = i.getPathName();
		md.title = tName;
		cout << tName << "  Create.......";
		book.init(tName.c_str(), AimPath);
		book.AddFromTxtsFolder(i.getPath().c_str());
		
		book.SetMetaData(md);
		book.WriteToEpub();
		cout << "Done!" << endl;
	}*/

}
int main()
{
	toEpub();
	
	//system("pause");
}