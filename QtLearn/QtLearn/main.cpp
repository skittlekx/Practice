#include "QtLearn.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	QtLearn w;
	w.show();
	return a.exec();
}
