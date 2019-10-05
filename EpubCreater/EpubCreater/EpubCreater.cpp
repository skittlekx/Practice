#include "EpubCreater.h"
#include "EpubStrRes.h"
#include "CChineseCode.h"
#include <string>
using namespace std;

EpubCreater::EpubCreater()
{
	isContent = false;
	isNcx = false;
}


EpubCreater::~EpubCreater()
{
}

void EpubCreater::init(const char* name, const char* path)
{
	m_Name.assign(name);
	string str(path);
	if (!Folder::IsExitPath(path))
	{
		Folder::CreateFolderAsFullPath(path);
	}
	m_Path.assign(str);
	str.append("\\").append(name);
	m_EpubPath.init(str.c_str());
	CreatBaseFile();
}

bool EpubCreater::AddFromLayeredTxts(const char* res) {
	Folder Res;
	if (!Folder::IsExitPath(res))
	{
		return false;
	}
	Res.init(res);
	if (Res.getFolderCount() == 0 && Res.getFileCount() == 0)
		return false;
	int k = 0;
	for (auto j = Res.getFirstFolder(); !Res.isEndFolder(); Res.getNextFolder(j))
	{
		int itag = 0;
		for (auto i = j.getFirstFile(); !j.isEndFile(); j.getNextFile(i),++itag)
		{
			string str = i.getName();
			string path = i.getPath();
			string name = path + str;
			string nName;
			//string spinetext = str.substr(0, str.length() - 4);
			char num[10];
			sprintf_s(num, "%04d", k++);
			nName.assign("Section").append(num).append(".xhtml");
			string spinetext = _Txt2xHtml(name.c_str());
			if (itag == 0) {
				spinetext.insert(spinetext.begin(), 5, '*');
			}
			m_Spine.push_back(spinetext);
			string xhtmlname = str.substr(0, str.find_last_of(".")).append(".xhtml");
			m_O_Text._CreateFile(nName.c_str());
			FileOpe tt = m_O_Text.FindFile(m_O_Text.SearchFile((m_O_Text.getPath() + "\\" + nName).c_str()));
			tt.CopyFrom((path + xhtmlname).c_str());
			FileOpe _tt((path + xhtmlname).c_str());
			_tt.Delete();
		}
	}
	return true;
}

bool EpubCreater::AddFromTxtsFolder(const char* res)
{
	Folder Res;
	if (!Folder::IsExitPath(res))
	{
		return false;
	}
	Res.init(res);
	if (Res.getFileCount() == 0)
		return false;
	int k = 0;
	for (FileOpe i = Res.getFirstFile(); !Res.isEndFile(); Res.getNextFile(i))
	{
		string str = i.getName();
		string path = i.getPath();
		string name = path + str;
		string nName;
		//string spinetext = str.substr(0, str.length() - 4);
		char num[10];
		sprintf_s(num, "%04d", k++);
		nName.assign("Section").append(num).append(".xhtml");
		string spinetext = _Txt2xHtml(name.c_str());
		m_Spine.push_back(spinetext);
		string xhtmlname = str.substr(0, str.find_last_of(".")).append(".xhtml");
		m_O_Text._CreateFile(nName.c_str());
		FileOpe tt = m_O_Text.FindFile(m_O_Text.SearchFile((m_O_Text.getPath() + "\\" + nName).c_str()));
		tt.CopyFrom((path + xhtmlname).c_str());
		FileOpe _tt((path + xhtmlname).c_str());
		_tt.Delete();
	}
	return true;
}

string EpubCreater::_Txt2xHtml(const char* sfile)//, const char* nfile)
{
	string title_return;
	string str(sfile);
	str = str.substr(0, str.find_last_of(".")).append(".xhtml");
	ifstream in(sfile);
	ofstream out(str,ios::out|ios::trunc);

	if (in.fail()) {
		//cout << "--in--fail------" << endl;
		return NULL;// false;
	}
	if (in.fail()) {
	//	cout << "--out--fail------" << endl;
		return NULL;// false;
	}
	string Temp, Current;
	getline(in, Temp);
	if (FileOpe::IsUtf8(Temp.c_str()))
	{
		CChineseCode::UTF_8ToGB2312(Current, Temp.c_str(), Temp.length());
	}
	else
	{
		Current.assign(Temp);
	}
	out << str_xhtmlHead;
	string ss;
	//ss.assign("    <title>").append(Current).append("</title>");
	ss.assign(_strTitle(Current));
	title_return = Current;
	out << ss <<endl;
	out << str_xhtmlLink;
	//ss.assign("        <h4>").append(Current).append("</h4>");
	ss.assign(_strH(Current));
	out << ss << endl << endl;

	while (!in.eof()) {
		getline(in, Temp);
		if (FileOpe::IsUtf8(Temp.c_str()))
		{
			CChineseCode::UTF_8ToGB2312(Current, Temp.c_str(), Temp.length());
		}
		else
		{
			Current.assign(Temp);
		}
		//out << "        <p> " << Current << " </p>" << endl << endl;
		if (Current == "")Current.assign("<br/>");
		ss.assign(_strP(Current));
		out << ss << endl << endl;
	}
	out << str_xhtmltail;
	in.close();
	out.close();
	FileOpe::SaveAsUtf8(str.c_str());
	return title_return;
}
void EpubCreater::CreatBaseFile()
{
	m_EpubPath._CreateFile("mimetype");
	m_EpubPath.CreateFolder("META-INF");
	m_EpubPath.CreateFolder("OEBPS");
	//创建 mimetype
	string name = m_EpubPath.getPath();
	name.append("\\mimetype");
	ofstream out(name);
	if (out.fail())return;
	out << str_mimetype;
	out.close();

	//创建子文件夹
	m_META = m_EpubPath.FindFolder(m_EpubPath.SearchFolder((m_EpubPath.getPath() + "\\" + "META-INF").c_str()));
	m_OEBPS = m_EpubPath.FindFolder(m_EpubPath.SearchFolder((m_EpubPath.getPath() + "\\" + "OEBPS").c_str()));

	//创建container.xml
	m_META._CreateFile("container.xml");
	name.assign(m_META.getPath()).append("\\container.xml");
	out.open(name);
	if (out.fail())return;
	out << str_container;
	out.close();
	//创建资源文件夹
	m_OEBPS.CreateFolder("Styles");
	m_OEBPS.CreateFolder("Images");
	m_OEBPS.CreateFolder("Text");
	m_O_Styles = m_OEBPS.FindFolder(m_OEBPS.SearchFolder((m_OEBPS.getPath() + "\\" + "Styles").c_str()));
	m_O_Images = m_OEBPS.FindFolder(m_OEBPS.SearchFolder((m_OEBPS.getPath() + "\\" + "Images").c_str()));
	m_O_Text = m_OEBPS.FindFolder(m_OEBPS.SearchFolder((m_OEBPS.getPath() + "\\" + "Text").c_str()));
	m_O_Styles._CreateFile("style.css");
	name.assign(m_O_Styles.getPath() + "\\style.css");
	out.open(name);
	if (out.fail())return;
	out << str_css1 << str_css2 << str_css3;
	out.close();
}
void EpubCreater::WriteToEpub()
{
	if(!isContent)CreateContent();
	if(!isNcx)CreateNcx();
	string zipname(m_Path);
	zipname.append("\\").append(m_Name);// .append(".zip");
	Compresser com;
	com.init(m_EpubPath.getPath().c_str());
	com.ToZip((zipname+".epub").c_str());
	//FileOpe tt((zipname + ".zip").c_str());
	//tt.Rename((m_Name + ".epub").c_str());
}

void EpubCreater::CreateContent()//, MANIFEST manifest, SPINE spine)
{
	isContent = true;
	m_OEBPS._CreateFile((m_OEBPS.getPath()+"\\content.opf").c_str());
	
	//更新文件夹结构
	m_EpubPath.init(m_EpubPath.getPath().c_str());
	m_META = m_EpubPath.FindFolder(m_EpubPath.SearchFolder((m_EpubPath.getPath() + "\\" + "META-INF").c_str()));
	m_OEBPS = m_EpubPath.FindFolder(m_EpubPath.SearchFolder((m_EpubPath.getPath() + "\\" + "OEBPS").c_str()));
	m_O_Styles = m_OEBPS.FindFolder(m_OEBPS.SearchFolder((m_OEBPS.getPath() + "\\" + "Styles").c_str()));
	m_O_Images = m_OEBPS.FindFolder(m_OEBPS.SearchFolder((m_OEBPS.getPath() + "\\" + "Images").c_str()));
	m_O_Text = m_OEBPS.FindFolder(m_OEBPS.SearchFolder((m_OEBPS.getPath() + "\\" + "Text").c_str()));


	string name = m_OEBPS.getPath() + "\\content.opf";
	wofstream out(name);
	out.imbue(locale("zh-CN.UTF-8"));
	out << FileOpe::stringToUTF8(string(str_contHead)) << endl;
	out << FileOpe::stringToUTF8(AddMetaData()) << FileOpe::stringToUTF8(AddManifest())
		<< FileOpe::stringToUTF8(AddSpine()) << FileOpe::stringToUTF8(AddGuid());
	out << FileOpe::stringToUTF8(string(str_contTail)) << endl;
	out.close();
}
void EpubCreater::CreateNcx()
{
	isNcx = true;
	m_OEBPS._CreateFile((m_OEBPS.getPath() + "\\toc.ncx").c_str());

	//更新文件夹结构
	m_EpubPath.init(m_EpubPath.getPath().c_str());
	m_OEBPS = m_EpubPath.FindFolder(m_EpubPath.SearchFolder((m_EpubPath.getPath() + "\\" + "OEBPS").c_str()));


	string name = m_OEBPS.getPath() + "\\toc.ncx";
	wofstream out(name);
	out.imbue(locale("zh-CN.UTF-8"));
	out << FileOpe::stringToUTF8(string(str_ncxHead)) << endl;

	out << FileOpe::stringToUTF8(AddNcxHead()) << FileOpe::stringToUTF8(AddNcxTitle())
		<< FileOpe::stringToUTF8(AddNcxMap());// << FileOpe::stringToUTF8(AddGuid());

	out << FileOpe::stringToUTF8(string(str_ncxTail)) << endl;
	out.close();
}
void EpubCreater::SetMetaData(METADATA md)
{
	m_md = md;
}
string EpubCreater::AddMetaData()
{
	string result;
	result.assign(str_MetaHead);
	result.append("\n").append(_str_Meta_Title(m_md.title));
	result.append("\n").append(_str_Meta_ID(m_md.ID));
	result.append("\n").append(_str_Meta_Auther(m_md.author));
	result.append("\n").append(_str_Meta_Date(m_md.date));
	result.append("\n").append(_str_Meta_Langu(m_md.language));
	result.append("\n").append(_str_Meta_Creater(m_md.creator));
	result.append("\n").append(str_MetaTail).append("\n");
	return result;
}
string EpubCreater::AddManifest()
{
	string result;
	result.assign(str_maniHead);
	MANIFEST a1, a2;
	{
		a1.id.assign("ncx");
		a1.herf.assign("toc.ncx");
		a1.MetaDataType.assign("application/x-dtbncx+xml");
	}
	{
		a2.id.assign("style.css");
		a2.herf.assign("Styles/style.css");
		a2.MetaDataType.assign("text/css");
	}
	result.append("\n").append(_str_Mani(a1.id, a1.herf, a1.MetaDataType));
	result.append("\n").append(_str_Mani(a2.id, a2.herf, a2.MetaDataType));
	if (m_O_Images.getFileCount() != 0)
	{
		MANIFEST a3;
		for (FileOpe i = m_O_Images.getFirstFile(); !m_O_Images.isEndFile(); m_O_Images.getNextFile(i))
		{
			string str = i.getName();
			string ss = i.getExtension();
			a3.id.assign("x").append(str);
			a3.herf.assign("Images/").append(str);
			a3.MetaDataType.assign("image/").append(ss.substr(1));
			result.append("\n").append(_str_Mani(a3.id, a3.herf, a3.MetaDataType));
		}
	}
	if (m_O_Text.getFileCount() != 0)
	{
		MANIFEST a3;
		a3.MetaDataType.assign("application/xhtml+xml");
		for (FileOpe i = m_O_Text.getFirstFile(); !m_O_Text.isEndFile(); m_O_Text.getNextFile(i))
		{
			string str = i.getName();
			string ss = i.getExtension();
			a3.id.assign(str);// .append(str);
			a3.herf.assign("Text/").append(str);
			//a3.MetaDataType.assign("image/").append(ss.substr(1));
			result.append("\n").append(_str_Mani(a3.id, a3.herf, a3.MetaDataType));
		}
	}
	result.append("\n").append(str_maniTail).append("\n");
	return result;
}
string EpubCreater::AddSpine()
{
	string result;
	result.assign(str_SpineHead);
	if (m_O_Text.getFileCount() != 0)
	{
		for (FileOpe i = m_O_Text.getFirstFile(); !m_O_Text.isEndFile(); m_O_Text.getNextFile(i))
		{
			string str = i.getName();

			result.append("\n").append(_str_Spine(str));
		}
	}

	result.append("\n").append(str_SpineTail).append("\n");
	return result;
}
string EpubCreater::AddGuid()
{
	string result;
	result.assign(str_Guid).append("\n");

	//result.append("\n").append(str_MetaTail).append("\n");
	return result;
}

string EpubCreater::AddNcxHead()
{
	string idstr = _str_Ncx_MetaId(m_md.ID);
	string result = _str_Ncx_Head(idstr);
	return result.append("\n");
}
string EpubCreater::AddNcxTitle()
{
	string result = _str_Ncx_TitleText(m_md.title);
	return result.append("\n");
}
string EpubCreater::AddNcxMap()
{
	string result(str_ncxmapHead);
	if (m_O_Text.getFileCount() != 0)
	{
		string num,laynum,laystr,navstr,textstr,srcstr,tailstr;
		int k = 0;
		int layercount = 0;
		for (FileOpe i = m_O_Text.getFirstFile(); !m_O_Text.isEndFile(); m_O_Text.getNextFile(i),++k)
		{
			num = to_string(k);
			string str = i.getName();
			srcstr.assign("Text/").append(str);
			if (m_Spine[k].find("*****") != -1) {
				m_Spine[k].replace(0, 5, "");
				char _num[10];
				sprintf_s(_num, "%04d", layercount);
				laynum.assign("volume").append(_num);
				if (layercount++ != 0) {
					result.append("\n").append(str_Ncx_Layer_Tail);
				}
				laystr.assign(_str_Ncx_Layer_Head(laynum, num, m_Spine[k],srcstr));
				result.append("\n").append(laystr);
			}
			else {
				navstr.assign(_str_Ncx_navHead(num));
				textstr.assign(_str_Ncx_Text(m_Spine[k]));
				tailstr.assign(_str_Ncx_navTail(srcstr));
				result.append("\n").append(navstr);
				result.append("\n").append(textstr);
				result.append("\n").append(tailstr);
			}
		}
		if (layercount != 0) {
			result.append("\n").append(str_Ncx_Layer_Tail);
		}
	}
	result.append("\n").append(str_ncxmapTail).append("\n");
	return result;
}