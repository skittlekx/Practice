#include "stdafx.h"
#include "CTestCtrl.h"

#define TESTCTRL_CLASSNAME    _T("CTestCtrl")  // Window class name


CTestCtrl::CTestCtrl()
{
	tag_Paint = false;
	RegisterWindowClass();
}


CTestCtrl::~CTestCtrl()
{
}


bool CTestCtrl::RegisterWindowClass()
{
	WNDCLASS wndcls;
	HINSTANCE hInst = AfxGetInstanceHandle();

	if (!(::GetClassInfo(hInst, TESTCTRL_CLASSNAME, &wndcls)))
	{
		memset(&wndcls, 0, sizeof(WNDCLASS));

		wndcls.hInstance = hInst;
		wndcls.lpfnWndProc = ::DefWindowProc;
		wndcls.hCursor = LoadCursor(NULL, IDC_ARROW);
		wndcls.hIcon = 0;
		wndcls.lpszMenuName = NULL;
		wndcls.hbrBackground = ::GetSysColorBrush(COLOR_WINDOW);
		wndcls.style = CS_DBLCLKS;
		wndcls.cbClsExtra = 0;
		wndcls.cbWndExtra = 0;
		wndcls.lpszClassName = TESTCTRL_CLASSNAME;

		if (!RegisterClass(&wndcls))
		{
			//  AfxThrowResourceException();
			return false;
		}
	}

	return true;
}

BEGIN_MESSAGE_MAP(CTestCtrl, CWnd)
	ON_WM_PAINT()
	ON_MESSAGE(WM_PAINT_MSE, OnMyDraw)
END_MESSAGE_MAP()


void CTestCtrl::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 在此处添加消息处理程序代码
					   // 不为绘图消息调用 CWnd::OnPaint()
	
	//if (tag_Paint)
	//{
		Draw(&dc);
	//}
}

LRESULT CTestCtrl::OnMyDraw(WPARAM w, LPARAM l)
{
	
	//AfxMessageBox(_T("ttttttt"));
	tag_Paint = true;
	Invalidate();
	return true;
}
void CTestCtrl::isPaint() 
{
	tag_Paint = true;
	Invalidate();
}
void CTestCtrl::Draw(CDC* pDC) {
	CRect rect;
	GetWindowRect(&rect);
	int wRect = rect.Width();
	int hRect = rect.Height();

	for (int i = 0; i < wRect; i++) {
		for (int j = 0; j < hRect; j++) {
			pDC->SetPixel(i, j, RGB(255, 0, 0));
		}
	}
}