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
		md.author = "���Ϸ���";
		md.ID = "123456";
		md.creator = "skx";
		md.date = "2019-9-9";
		md.language = "zh-CN";
	}
	//����
	EpubCreater book;
	string tName = "ѩ�к�����";
	md.title = tName;
	cout << tName << "  Create.......";
	book.init(tName.c_str(), AimPath);
	book.AddFromLayeredTxts(Res.getPath().c_str());

	book.SetMetaData(md);
	book.WriteToEpub();
	cout << "Done!" << endl;
	//�౾
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