#pragma once
#include "Folder.h"
#include "FileOpe.h"
#include "Compresser.h"
struct METADATA
{
	std::string title;
	std::string ID;
	std::string author;
	std::string creator;
	std::string date;
	std::string language;
	METADATA& operator=(const METADATA& a)
	{
		title.assign(a.title);
		ID.assign(a.ID);
		author.assign(a.author);
		creator.assign(a.creator);
		date.assign(a.date);
		language.assign(a.language);
		return *this;
	}
};
struct MANIFEST
{
	std::string id;
	std::string herf;
	std::string MetaDataType;
};

class EpubCreater
{
public:
	EpubCreater();
	~EpubCreater();
	void init(const char* name,const char* path);
	bool AddFromTxtsFolder(const char*);

	bool AddFromLayeredTxts(const char*);

	void CreateContent();// , MANIFEST, SPINE);
	void CreateNcx();
	void CreatBaseFile();
	void WriteToEpub();
	void SetMetaData(METADATA);

private:
	std::string AddMetaData();
	std::string AddManifest();//MANIFEST);
	std::string AddSpine();// SPINE);
	std::string AddGuid();

	std::string AddNcxHead();
	std::string AddNcxTitle();
	std::string AddNcxMap();
public:
	static std::string _Txt2xHtml(const char* sfile);// , const char* nfile);
private:
	bool isContent;
	bool isNcx;
	std::string m_Name;
	std::string m_Path;
	Folder m_EpubPath;
	Folder m_META;
	Folder m_OEBPS;
	Folder m_O_Styles;
	Folder m_O_Text;
	Folder m_O_Images;
	METADATA m_md;
	std::vector<std::string> m_Spine;//ÕÂ½ÚË³Ðò
};

