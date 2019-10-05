#include <iostream>
#include "EpubCreater.h"
using namespace std;
void toEpub()
{
	const char* ResPath = "..\\..\\..\\233";
	const char* AimPath = "..\\..\\..\\fan";
	Folder Res;
	Res.init(ResPath);
	METADATA md;
	{
		md.author = "烽火戏诸侯";
		md.ID = "123456";
		md.creator = "skx";
		md.date = "2019-9-9";
		md.language = "zh-CN";
	}
	//单本
	EpubCreater book;
	string tName = "雪中悍刀行";
	md.title = tName;
	cout << tName << "  Create.......";
	book.init(tName.c_str(), AimPath);
	book.AddFromLayeredTxts(Res.getPath().c_str());

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