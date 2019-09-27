#include "zlib.h"
#include "zconf.h"
#include "unzip101e/unzip.h"
#include "unzip101e/zip.h"
#include <iostream>
#include "Compresser.h"
using namespace std;

//#pragma comment(lib,"zlibstat.lib")

int main()
{
	Compresser co;
	co.init("C:\\Users\\skittle\\Desktop\\233\\233");
	co.ToZip("C:\\Users\\skittle\\Desktop\\233\\233.zip");
	//system("pause");
	return 0;
}