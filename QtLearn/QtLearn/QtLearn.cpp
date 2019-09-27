#include "QtLearn.h"
#include <qmessagebox.h>


QtLearn::QtLearn(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	//m_Act = new QAction(QIcon(tr(":/image/Image1")), tr("&Open"), this);
	//m_Act->setText(tr("&Open"));
	m_Act.setText(tr("&Open"));
	m_Act.setShortcut(QKeySequence::Open);
	m_Act.setStatusTip(tr("Open Files"));
	connect(&m_Act, &QAction::triggered, this, &QtLearn::open);
	
	QMenu *Menu = menuBar()->addMenu(tr("&File"));
	Menu->addAction(&m_Act);
	
	m_Act.setIcon(QIcon(tr(":/image/Image1")));
	QToolBar *Tt = addToolBar(tr("&File"));
	Tt->addAction(&m_Act);


	statusBar();
}
QtLearn::~QtLearn()
{

}

void QtLearn::open()
{
	QMessageBox::information(this, tr("Information"), tr("Open"));
}