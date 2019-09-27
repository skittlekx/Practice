#pragma once
#include <afxwin.h>

#define  WM_PAINT_MSE  WM_USER+1

class CTestCtrl :
	public CWnd
{
public:
	CTestCtrl();
	~CTestCtrl();

private:
	bool RegisterWindowClass();

	
public:
	DECLARE_MESSAGE_MAP()
public:

	afx_msg void OnPaint();
	afx_msg LRESULT OnMyDraw(WPARAM, LPARAM/*CDC *pDC*/);
	void Draw(CDC*);
	bool tag_Paint;

	void isPaint();
};

