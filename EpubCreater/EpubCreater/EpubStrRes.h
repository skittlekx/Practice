#pragma once

const char* str_mimetype = "application/epub+zip";
const char* str_container = "<?xml version=\"1.0\" encoding=\"UTF-8\"?> \n\
<container version=\"1.0\" xmlns=\"urn:oasis:names:tc:opendocument:xmlns:container\">\n\
    <rootfiles>\n\
        <rootfile full-path=\"OEBPS/content.opf\" media-type=\"application/oebps-package+xml\"/>\n\
    </rootfiles>\n\
</container>";

const char* str_css1 = "\
/*预设文本样式*/                                                                                     \n\
body{                                                                                          \n\
	padding: 0%;                                                                               \n\
	margin-top: 0%;                                                                            \n\
	margin-bottom: 0%;                                                                         \n\
	margin-left: 1%;                                                                           \n\
	margin-right: 1%;                                                                          \n\
	line-height: 130%;                                                                         \n\
	text-align: justify;                                                                       \n\
}                                                                                              \n\
                                                                                               \n\
h4{                                                                                            \n\
	font-size: 1.5em;                                                                          \n\
	text-align: center;                                                                        \n\
	line-height: 1.2em;                                                                        \n\
	text-indent: 0em;                                                                          \n\
	font-weight: bold;                                                                         \n\
	margin-top: 1em;                                                                           \n\
	margin-bottom: 1.5em;                                                                      \n\
}                                                                                              \n\
div{                                                                                           \n\
	margin: 0px;                                                                               \n\
	padding: 0px;                                                                              \n\
	text-align: justify;                                                                       \n\
}                                                                                              \n\
p{                                                                                             \n\
	text-indent: 2em;                                                                          \n\
	display: block;                                                                            \n\
	line-height: 1.3em;                                                                        \n\
	margin-top: 0.4em;                                                                         \n\
	margin-bottom: 0.4em;                                                                      \n\
}                                                                                              \n\
                                                                                               \n\
/*图片相关*/                                                                                       \n\
.illus{                                                                                        \n\
	text-indent: 0em;                                                                          \n\
	text-align: center;                                                                        \n\
}                                                                                              \n\
.cover{                                                                                        \n\
	margin: 0em;                                                                               \n\
	padding: 0em;                                                                              \n\
	text-indent: 0em;                                                                          \n\
	text-align: center;                                                                        \n\
}                                                                                              \n\
.coverborder{                                                                                  \n\
	border-style: none solid none solid;                                                       \n\
	border-color: #000000;                                                                     \n\
	border-width: 1px;                                                                         \n\
}                                                                                              \n\
";
const char* str_css2 ="\
/*预设格式相关样式*/                                                                                   \n\
.right{                                                                                        \n\
	text-indent: 0em;                                                                          \n\
	text-align: right;                                                                         \n\
}                                                                                              \n\
.left{                                                                                         \n\
	text-indent: 0em;                                                                          \n\
	text-align: left;                                                                          \n\
}                                                                                              \n\
.center{                                                                                       \n\
	text-indent: 0em;                                                                          \n\
    text-align: center;                                                                        \n\
}                                                                                              \n\
.zin{                                                                                          \n\
    text-indent: 0em;                                                                          \n\
}                                                                                              \n\
.bold{                                                                                         \n\
    font-weight: bold;                                                                         \n\
}                                                                                              \n\
.stress{                                                                                       \n\
	font-weight: bold;                                                                         \n\
	font-size: 1.1em;                                                                          \n\
	margin-top: 0.3em;                                                                         \n\
	margin-bottom: 0.3em;                                                                      \n\
}                                                                                              \n\
.author{                                                                                       \n\
	font-size: 1.2em;                                                                          \n\
	text-align: right;                                                                         \n\
	font-weight: bold;                                                                         \n\
	font-style: italic;                                                                        \n\
	margin-right: 1em;                                                                         \n\
}                                                                                              \n\
.dash-break{                                                                                   \n\
	word-break: break-all;                                                                     \n\
	word-wrap: break-word;                                                                     \n\
}                                                                                              \n\
.no-d{                                                                                         \n\
	text-decoration: none;                                                                     \n\
}                                                                                              \n\
.bc{                                                                                           \n\
	border-collapse: collapse;                                                                 \n\
}                                                                                              \n\
.dash-break{                                                                                   \n\
	word-break: break-all;                                                                     \n\
	word-wrap: break-word;                                                                     \n\
}                                                                                              \n\
.message{                                                                                      \n\
	text-indent: 0em;                                                                          \n\
	line-height: 1.2em;                                                                        \n\
	margin-top: 0.2em;                                                                         \n\
	margin-bottom: 0.2em;                                                                      \n\
}                                                                                              \n\
.meg{                                                                                          \n\
	font-size: 1.3em;                                                                          \n\
	text-indent: 0em;                                                                          \n\
	font-weight: bold;                                                                         \n\
	margin-top: 0.5em;                                                                         \n\
	margin-bottom: 0.5em;                                                                      \n\
}                                                                                              \n\
                                                                                               \n\
/*文字大小*/                                                                                       \n\
.em05{                                                                                         \n\
    font-size: 0.5em;                                                                          \n\
}                                                                                              \n\
.em06{                                                                                         \n\
    font-size: 0.6em;                                                                          \n\
}                                                                                              \n\
.em07{                                                                                         \n\
    font-size: 0.7em;                                                                          \n\
}                                                                                              \n\
.em08{                                                                                         \n\
    font-size: 0.8em;                                                                          \n\
}                                                                                              \n\
.em09{                                                                                         \n\
    font-size: 0.9em;                                                                          \n\
}                                                                                              \n\
.em10{                                                                                         \n\
    font-size: 1.0em;                                                                          \n\
}                                                                                              \n\
.em11{                                                                                         \n\
    font-size: 1.1em;                                                                          \n\
}                                                                                              \n\
.em12{                                                                                         \n\
    font-size: 1.2em;                                                                          \n\
}                                                                                              \n\
.em13{                                                                                         \n\
    font-size: 1.3em;                                                                          \n\
}                                                                                              \n\
.em14{                                                                                         \n\
    font-size: 1.4em;                                                                          \n\
}                                                                                              \n\
.em15{                                                                                         \n\
    font-size: 1.5em;                                                                          \n\
}                                                                                              \n\
.em16{                                                                                         \n\
    font-size: 1.6em;                                                                          \n\
}                                                                                              \n\
.em17{                                                                                         \n\
    font-size: 1.7em;                                                                          \n\
}                                                                                              \n\
.em18{                                                                                         \n\
    font-size: 1.8em;                                                                          \n\
}                                                                                              \n\
.em18{                                                                                         \n\
    font-size: 1.9em;                                                                          \n\
}                                                                                              \n\
.em20{                                                                                         \n\
    font-size: 2em;                                                                            \n\
}                                                                                              \n\
";
const char* str_css3="\
/*预设目录样式*/                                                                                     \n\
.contents{                                                                                     \n\
	text-indent: 0em;                                                                          \n\
	text-align: center;                                                                        \n\
   	border-bottom: 0.1em dotted #000000;                                                       \n\
    padding: 0.5em 0 0.4em 0;                                                                  \n\
    margin-bottom: 0.7em;                                                                      \n\
    font-weight: bold;                                                                         \n\
}                                                                                              \n\
.mulu{                                                                                         \n\
	text-indent: 0em;                                                                          \n\
	text-align: center;                                                                        \n\
}                                                                                              \n\
.co20{                                                                                         \n\
	color:#000000;                                                                             \n\
}                                                                                              \n\
                                                                                               \n\
/*预设title样式*/                                                                                  \n\
.title-width{                                                                                  \n\
    width: 100%;                                                                               \n\
}                                                                                              \n\
.bb{                                                                                           \n\
    border-bottom: 3px solid #000000;                                                          \n\
}                                                                                              \n\
.blb{                                                                                          \n\
    border-left: 3px solid #000000;                                                            \n\
    border-bottom: 3px solid #000000;                                                          \n\
}                                                                                              \n\
.bl{                                                                                           \n\
    border-left: 3px solid #000000;                                                            \n\
}                                                                                              \n\
.br{                                                                                           \n\
    border-right: 3px solid #000000;                                                           \n\
}                                                                                              \n\
.brt{                                                                                          \n\
    border-right: 3px solid #000000;                                                           \n\
    border-top: 3px solid #000000;                                                             \n\
}                                                                                              \n\
.bt{                                                                                           \n\
    border-top: 3px solid #000000;                                                             \n\
}                                                                                              \n\
                                                                                               \n\
/*图片允许放大*/                                                                                     \n\
/*                                                                                             \n\
html代码：                                                                                        \n\
                                                                                               \n\
<div class=\"duokan - image - single illus\"><img alt=\"图片名\" src=\".. / Images / 图片名.jpg\" /></div>         \n\
*/                                                                                             \n\
                                                                                               \n\
/*预设注释样式                                                                                       \n\
	 by lucifer004提供*/                                                                         \n\
                                                                                               \n\
.sign{                                                                                         \n\
	font-size: 0.8em;                                                                          \n\
	font-weight: bold;                                                                         \n\
	vertical-align: super;                                                                     \n\
}                                                                                              \n\
.note{                                                                                         \n\
	font-size: 0.8em;                                                                          \n\
	text-indent: -1.6em;                                                                       \n\
	margin: 0.5em 2% 1em 2.5em;                                                                \n\
	padding: 0.8em 0.8em 0.8em 1.9em;                                                          \n\
	background-color: #F1D99D;                                                                 \n\
	border: 1px #BC905A solid;                                                                 \n\
	border-radius: 0 10px;                                                                     \n\
	box-shadow: 2px 2px 4px #555555;                                                           \n\
}                                                                                              \n\
                                                                                               \n\
                                                                                               \n\
/*以下填写自定义css样式*/                                                                               \n\
                                                                                               \n\
";

const char* str_xhtmlHead = "\
<?xml version=\"1.0\" encoding=\"utf-8\"?>\n\
<!DOCTYPE html PUBLIC \"-//W3C//DTD XHTML 1.1//EN\"\n\
  \"http://www.w3.org/TR/xhtml11/DTD/xhtml11.dtd\">\n\
\n\
<html xmlns=\"http://www.w3.org/1999/xhtml\" xml:lang=\"zh-CN\" xmlns:epub=\"http://www.idpf.org/2007/ops\" xmlns:xml=\"http://www.w3.org/XML/1998/namespace\">\n\
<head>\n\
";

/*<script src=\"../Misc/notereplace.js\" type=\"text/javascript\"></script>\n\*/
const char* str_xhtmlLink = "\
    <link href=\"../Styles/style.css\" rel=\"stylesheet\" type=\"text/css\"/>\n\
</head>\n\
<body>\n\
    <div>\n\
";
const char* str_xhtmltail = "\
    </div>\n\
</body>\n\
</html>\n\
";
#define _strTitle(X) "    <title> "+X+" </title>"
#define _strH(X) "        <h4> "+X+" </h4>"
#define _strP(X) "        <p> "+X+" </p>"


const char* str_contHead = "\
<?xml version=\"1.0\" encoding=\"utf-8\" standalone=\"yes\"?>\n\
<package xmlns = \"http://www.idpf.org/2007/opf\" unique-identifier = \"BookId\" version = \"2.0\">";
const char* str_contTail = "</package>";

const char* str_MetaHead = "\
  <metadata xmlns:dc=\"http://purl.org/dc/elements/1.1/\" xmlns:opf=\"http://www.idpf.org/2007/opf\">";

const char* str_MetaTail = "  </metadata>";

const char* str_maniHead = "  <manifest>";
const char* str_maniTail = "  </manifest>";

const char* str_SpineHead = "  <spine toc=\"ncx\">";
const char* str_SpineTail = "  </spine>";

const char* str_Guid = "\
  <guide>\n\
    <reference type=\"cover\" title=\"封面\" href=\"Text/cover.xhtml\" />\n\
  </guide>";

#define _str_Meta_Title(X) "    <dc:title>"+X+"</dc:title>"
#define _str_Meta_ID(X) "    <dc:identifier id=\"bookid\">urn:uuid:"+X+"</dc:identifier>"
#define _str_Meta_Langu(X) "    <dc:language>"+X+"</dc:language>"
#define _str_Meta_Date(X) "    <dc:date opf:event=\"modification\">"+X+"</dc:date>"
#define _str_Meta_Auther(X) "    <dc:creator opf:file-as=\"1\" opf:role=\"aut\">"+X+"</dc:creator>"
#define _str_Meta_Creater(X) "    <dc:creator>ePub制作者："+X+"</dc:creator>"
#define _str_Mani(ID,HREF,TYPE) "    <item id=\""+ID+"\" href=\""+HREF+"\" media-type=\""+TYPE+"\"/>"
#define _str_Spine(X) "    <itemref idref=\""+X+"\"/>"

#define _str_Ncx_MetaId(X) "    <meta name=\"dtb:uid\" content=\"urn:uuid:"+X+"\"/>"
#define _str_Ncx_TitleText(X) "\
  <docTitle>\n\
    <text>" + X + "</text>\n\
  </docTitle>"
#define _str_Ncx_Layer_Head(X,Y,Z,W) "<navPoint id=\""+X+"\" playOrder=\""+Y+"\">\n\
  <navLabel>\n\
    <text>" + Z + "</text>\n\
  </navLabel>\n\
  <content src = \"" + W + "\"/>"
const char* str_Ncx_Layer_Tail = "</navPoint>";
#define _str_Ncx_Text(X) "        <text>" + X + "</text>"
#define _str_Ncx_Head(X) "  <head>\n" +X+"\n\
    <meta name=\"dtb:depth\" content=\"1\"/>\n\
    <meta name=\"dtb:totalPageCount\" content=\"0\"/>\n\
    <meta name=\"dtb:maxPageNumber\" content=\"0\"/>\n\
  </head>"
#define _str_Ncx_navHead(X) "\
    <navPoint id=\"navPoint-"+X+"\" playOrder=\""+X+"\">\n\
      <navLabel>"
#define _str_Ncx_navTail(X) "\
      </navLabel>\n\
	  <content src = \""+X+"\"/>\n\
    </navPoint>"
const char* str_ncxHead = "\
<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>              \n\
<!DOCTYPE ncx PUBLIC \"-//NISO//DTD ncx 2005-1//EN\"                   \n\
 \"http://www.daisy.org/z3986/2005/ncx-2005-1.dtd\">                   \n\
<ncx xmlns=\"http://www.daisy.org/z3986/2005/ncx/\" version=\"2005-1\">";

const char* str_ncxTail = "</ncx>";
const char* str_ncxmapHead = "  <navMap>";
const char* str_ncxmapTail = "  </navMap>";
