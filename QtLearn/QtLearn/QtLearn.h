#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_QtLearn.h"

class QtLearn : public QMainWindow
{
	Q_OBJECT

public:
	QtLearn(QWidget *parent = Q_NULLPTR);
	~QtLearn();
	void open();
private:
	Ui::QtLearnClass ui;
	QAction m_Act;
};
