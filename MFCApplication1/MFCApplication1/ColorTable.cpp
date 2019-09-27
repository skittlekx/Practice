// ColorTable.cpp: 实现文件
//

#include "stdafx.h"
#include "Visualize.h"
#include "ColorTable.h"

#define COLORTABLE_CLASSNAME    _T("ColorTable")  // Window class name

using Anchor = CDUtils::CDColorTable::ColorTableAnchor;

// CColorTable

IMPLEMENT_DYNAMIC(CColorTable, CWnd)

CColorTable::CColorTable()
	: colorTable(
		{
			Anchor(0.0, RGB(191, 255, 255)),
			Anchor(1.0 / 3, RGB(0, 0, 191)),
			Anchor(0.5, RGB(255, 255, 255)),
			Anchor(2.0 / 3, RGB(191, 0, 0)),
			Anchor(1.0, RGB(255, 255, 0))
		}
	)
{
	m_iBorderWidth = 2;
	m_iAnchorSize = 5;
	m_Orientation = Horizontal;
	m_i64PressedNumber = -1;
	m_anchors = colorTable.GetAnchors();
	m_i64CurrSelect = m_anchors.size() - 1;

	RegisterWindowClass();
}

CColorTable::~CColorTable()
{
}


BEGIN_MESSAGE_MAP(CColorTable, CWnd)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()



// CColorTable 消息处理程序




bool CColorTable::RegisterWindowClass()
{
	WNDCLASS wndcls;
	HINSTANCE hInst = AfxGetInstanceHandle();

	if (!(::GetClassInfo(hInst, COLORTABLE_CLASSNAME, &wndcls)))
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
		wndcls.lpszClassName = COLORTABLE_CLASSNAME;

		if (!RegisterClass(&wndcls))
		{
			//  AfxThrowResourceException();
			return false;
		}
	}

	return true;
}


CDUtils::CDColorTable::ColorTableAnchor & CColorTable::GetCurAnchor()
{
	return m_anchors[m_i64CurrSelect];
}

void CColorTable::CompileColorTable()
{
	colorTable.GetRawAnchors() = m_anchors;
	colorTable.Compile();
}

void CColorTable::DelAnchor(__int64 num)
{
	m_anchors.erase(m_anchors.begin() + num);
	if (m_i64CurrSelect >= m_anchors.size())
		m_i64CurrSelect = m_anchors.size() - 1;
	colorTable.GetRawAnchors() = m_anchors;
	colorTable.Compile();
}

void CColorTable::AddAnchor(double value, COLORREF color)
{
	m_anchors.emplace_back(value, color);
	colorTable.GetRawAnchors() = m_anchors;
	colorTable.Compile();
}

void CColorTable::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	
	DrawBar(&dc);
	for (auto & anchor : colorTable.GetAnchors())
		DrawAnchor(&dc, anchor);
	DrawAnchor(&dc, m_anchors[m_i64CurrSelect], true);
					   // 不为绘图消息调用 CWnd::OnPaint()
}


std::vector<POINT> CColorTable::GetAnchorRegion(double pos)
{
	CRect rect;
	GetWindowRect(&rect);
	--rect.right;
	--rect.bottom;

	int wRect;
	int hRect;
	switch (m_Orientation)
	{
	case Horizontal:
		wRect = rect.Width();
		hRect = rect.Height();
		break;
	case Vertical:
		wRect = rect.Height();
		hRect = rect.Width();
		break;
	}

	int barLeftMargin = m_iAnchorSize + m_iBorderWidth;
	int barBottomMargin = 3 * m_iAnchorSize + 3 * m_iBorderWidth + 1;
	int barLength = wRect - 2 * barLeftMargin;
	int barHeight = hRect - barBottomMargin;
	long xOffset = barLeftMargin + barLength * pos;
	long yOffset = barHeight;
	long anchorWidth = 2 * barLeftMargin + 1;

	std::vector<POINT> result;
	switch (m_Orientation)
	{
	case Vertical:
		{
			auto t = xOffset;
			xOffset = yOffset;
			yOffset = wRect - t;
		}
		result.emplace_back(POINT{ xOffset, yOffset });
		result.emplace_back(POINT{ xOffset + m_iAnchorSize + m_iBorderWidth, yOffset - m_iAnchorSize - m_iBorderWidth });
		result.emplace_back(POINT{ result[1].x + anchorWidth, result[1].y });
		result.emplace_back(POINT{ result[2].x, yOffset + m_iAnchorSize + m_iBorderWidth });
		result.emplace_back(POINT{ result[1].x, result[3].y });
		break;
	case Horizontal:
		result.emplace_back(POINT{ xOffset, yOffset });
		result.emplace_back(POINT{ xOffset + m_iAnchorSize + m_iBorderWidth, yOffset + m_iAnchorSize + m_iBorderWidth });
		result.emplace_back(POINT{ result[1].x, result[1].y + anchorWidth });
		result.emplace_back(POINT{ xOffset - m_iAnchorSize - m_iBorderWidth, result[2].y });
		result.emplace_back(POINT{ result[3].x, result[1].y });
		break;
	}
	return result;
}

double CColorTable::PointToPos(CPoint point)
{
	CRect rect;
	GetWindowRect(&rect);
	--rect.right;
	--rect.bottom;

	int wRect;
	int hRect;
	switch (m_Orientation)
	{
	case Horizontal:
		wRect = rect.Width();
		hRect = rect.Height();
		break;
	case Vertical:
		wRect = rect.Height();
		hRect = rect.Width();
		break;
	}

	int barLeftMargin = m_iAnchorSize + m_iBorderWidth;
	int barBottomMargin = 3 * m_iAnchorSize + 3 * m_iBorderWidth + 1;
	int barLength = wRect - 2 * barLeftMargin;
	int barHeight = hRect - barBottomMargin;

	switch (m_Orientation)
	{
	case Horizontal:
		return double(point.x - barLeftMargin) / barLength;
	case Vertical:
		return double(wRect - point.y - barLeftMargin) / barLength;
	}

	return 0.0;
}

int CColorTable::DrawBar(CDC * pDC)
{
	CRect rect;
	GetWindowRect(&rect);
	--rect.right;
	--rect.bottom;

	int wRect;
	int hRect;
	switch (m_Orientation)
	{
	case Horizontal:
		wRect = rect.Width();
		hRect = rect.Height();
		break;
	case Vertical:
		wRect = rect.Height();
		hRect = rect.Width();
		break;
	}

	int barLeftMargin = m_iAnchorSize + m_iBorderWidth;
	int barBottomMargin = 3 * m_iAnchorSize + 3 * m_iBorderWidth + 1;
	int barLength = wRect - 2 * barLeftMargin;
	int barHeight = hRect - barBottomMargin;

	switch (m_Orientation)
	{
	case Vertical:
		for (int y = 0; y < barLength; ++y)
			for (int x = 0; x < barHeight; ++x)
			{
				double v = double(barLength - y) / barLength;
				int xpos = x;
				int ypos = barLeftMargin + y;
				if (colorTable.GetAlpha(v) > 254)
					pDC->SetPixel(xpos, ypos, colorTable.GetColor(v));
				else
				{
					if ((xpos / 8) % 2 == (ypos / 8) % 2)
						pDC->SetPixel(xpos, ypos, RGB(191, 191, 191));
					else
						pDC->SetPixel(xpos, ypos, RGB(255, 255, 255));
				}
			}
		break;
	case Horizontal:
		for (int x = 0; x < barLength; ++x)
			for (int y = 0; y < barHeight; ++y)
			{
				double v = double(x) / barLength;
				int xpos = barLeftMargin + x;
				int ypos = y;
				if (colorTable.GetAlpha(v) > 254)
					pDC->SetPixel(xpos, ypos, colorTable.GetColor(v));
				else
				{
					if ((xpos / 8) % 2 == (ypos / 8) % 2)
						pDC->SetPixel(xpos, ypos, RGB(191, 191, 191));
					else
						pDC->SetPixel(xpos, ypos, RGB(255, 255, 255));
				}
			}
		break;
	}

	return 0;
}

int CColorTable::DrawAnchor(CDC * pDC, const CDUtils::CDColorTable::ColorTableAnchor & anchor, bool selected)
{
	CRect rect;
	GetWindowRect(&rect);
	--rect.right;
	--rect.bottom;

	int wRect;
	int hRect;
	switch (m_Orientation)
	{
	case Horizontal:
		wRect = rect.Width();
		hRect = rect.Height();
		break;
	case Vertical:
		wRect = rect.Height();
		hRect = rect.Width();
		break;
	}

	int barLeftMargin = m_iAnchorSize + m_iBorderWidth;
	int barBottomMargin = 3 * m_iAnchorSize + 3 * m_iBorderWidth + 1;
	int barLength = wRect - 2 * barLeftMargin;
	int barHeight = hRect - barBottomMargin;
	long xOffset = barLeftMargin + barLength * anchor.value;
	long yOffset = barHeight;
	long anchorWidth = 2 * barLeftMargin + 1;

	POINT outter[5];
	POINT inner[6];
	switch (m_Orientation)
	{
	case Vertical:
		{
			auto t = xOffset;
			xOffset = yOffset;
			yOffset = wRect - t;
		}
		outter[0] = { xOffset, yOffset };
		outter[1] = { xOffset + m_iAnchorSize + m_iBorderWidth, yOffset - m_iAnchorSize - m_iBorderWidth };
		outter[2] = { outter[1].x + anchorWidth, outter[1].y };
		outter[3] = { outter[2].x, yOffset + m_iAnchorSize + m_iBorderWidth };
		outter[4] = { outter[1].x, outter[3].y };

		if (anchor.alpha > 127)
		{
			inner[0] = { outter[1].x + m_iBorderWidth, outter[1].y + m_iBorderWidth };
			inner[1] = { outter[2].x - m_iBorderWidth, outter[2].y + m_iBorderWidth };
			inner[2] = { outter[3].x - m_iBorderWidth, outter[3].y - m_iBorderWidth };
			inner[3] = { outter[4].x + m_iBorderWidth, outter[4].y - m_iBorderWidth };
		}
		else
		{
			inner[0] = { outter[1].x + m_iBorderWidth, outter[1].y + m_iBorderWidth };
			inner[1] = { inner[0].x + m_iBorderWidth, inner[0].y };
			inner[5] = { inner[0].x, inner[0].y + m_iBorderWidth };
			inner[3] = { outter[3].x - m_iBorderWidth, outter[3].y - m_iBorderWidth };
			inner[2] = { inner[3].x, inner[3].y - m_iBorderWidth };
			inner[4] = { inner[3].x - m_iBorderWidth, inner[3].y };
		}
		break;
	case Horizontal:
		outter[0] = { xOffset, yOffset };
		outter[1] = { xOffset + m_iAnchorSize + m_iBorderWidth, yOffset + m_iAnchorSize + m_iBorderWidth};
		outter[2] = { outter[1].x, outter[1].y + anchorWidth };
		outter[3] = { xOffset - m_iAnchorSize - m_iBorderWidth, outter[2].y };
		outter[4] = { outter[3].x, outter[1].y };

		if (anchor.alpha > 127)
		{
			inner[0] = { outter[1].x - m_iBorderWidth, outter[1].y + m_iBorderWidth };
			inner[1] = { outter[2].x - m_iBorderWidth, outter[2].y - m_iBorderWidth };
			inner[2] = { outter[3].x + m_iBorderWidth, outter[3].y - m_iBorderWidth };
			inner[3] = { outter[4].x + m_iBorderWidth, outter[4].y + m_iBorderWidth };
		}
		else
		{
			inner[0] = { outter[1].x - m_iBorderWidth, outter[1].y + m_iBorderWidth };
			inner[1] = { inner[0].x, inner[0].y + m_iBorderWidth };
			inner[5] = { inner[0].x - m_iBorderWidth, inner[0].y };
			inner[3] = { outter[3].x + m_iBorderWidth, outter[3].y - m_iBorderWidth };
			inner[2] = { inner[3].x + m_iBorderWidth, inner[3].y };
			inner[4] = { inner[3].x, inner[3].y - m_iBorderWidth };
		}
		break;
	}

	CBrush innerBrush(anchor.alpha > 127 ? anchor.color : RGB(255, 0, 0));
	CBrush outterBrush(selected ? RGB(0, 0, 0) : RGB(192, 192, 192));
	CRgn outterRgn;
	outterRgn.CreatePolygonRgn(outter, 5, ALTERNATE);
	pDC->FillRgn(&outterRgn, &outterBrush);
	CRgn innerRgn;
	innerRgn.CreatePolygonRgn(inner, 4, ALTERNATE);
	pDC->FillRgn(&innerRgn, &innerBrush);

	return 0;
}


void CColorTable::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	__int64 counter = colorTable.GetAnchors().size();
	for (auto it = colorTable.GetAnchors().crbegin(); it != colorTable.GetAnchors().crend(); ++it)
	{
		--counter;
		CRgn rgn;
		auto pts = GetAnchorRegion(it->value);
		rgn.CreatePolygonRgn(&pts[0], pts.size(), ALTERNATE);
		if (rgn.PtInRegion(point))
		{
			m_i64PressedNumber = counter;
			m_anchors = colorTable.GetAnchors();
			m_i64CurrSelect = m_i64PressedNumber;
			SendNotify(NTF_COLORTABLE_CLICK_ANCHOR);
			Invalidate();
			return;
		}
	}
	m_i64PressedNumber = -1;

	CWnd::OnLButtonDown(nFlags, point);
}


void CColorTable::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (m_i64PressedNumber >= 0)
		m_i64PressedNumber = -1;

	CWnd::OnLButtonUp(nFlags, point);
}


void CColorTable::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (m_i64PressedNumber >= 0)
	{
		double pos = PointToPos(point);
		pos = pos >= 0.0 ? pos <= 1.0 ? pos : 1.0 : 0.0;
		m_anchors[m_i64PressedNumber].value = pos;
		colorTable.GetRawAnchors() = m_anchors;
		colorTable.Compile();
		Invalidate();
	}

	CWnd::OnMouseMove(nFlags, point);
}


int CColorTable::SendNotify(UINT notifyMsg)
{
	NMHDR nmh;
	nmh.code = notifyMsg;    // Message type defined by control.
	nmh.idFrom = GetDlgCtrlID();
	nmh.hwndFrom = m_hWnd;
	GetParent()->SendMessage(
		WM_NOTIFY,
		nmh.idFrom,
		(LPARAM)&nmh);
	return 0;
}

int CColorTable::PostNotify(UINT notifyMsg)
{
	NMHDR nmh;
	nmh.code = notifyMsg;    // Message type defined by control.
	nmh.idFrom = GetDlgCtrlID();
	nmh.hwndFrom = m_hWnd;
	GetParent()->PostMessage(
		WM_NOTIFY,
		nmh.idFrom,
		(LPARAM)&nmh);
	return 0;
}


BOOL CColorTable::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CRect rect;
	GetWindowRect(&rect);
	--rect.right;
	--rect.bottom;

	int wRect;
	int hRect;
	switch (m_Orientation)
	{
	case Horizontal:
		wRect = rect.Width();
		hRect = rect.Height();
		break;
	case Vertical:
		wRect = rect.Height();
		hRect = rect.Width();
		break;
	}

	int barLeftMargin = m_iAnchorSize + m_iBorderWidth;
	int barBottomMargin = 3 * m_iAnchorSize + 3 * m_iBorderWidth + 1;
	int barLength = wRect - 2 * barLeftMargin;
	int barHeight = hRect - barBottomMargin;
	
	CRect anchorArea;
	switch (m_Orientation)
	{
	case Horizontal:
		anchorArea.SetRect(0, barHeight, wRect, hRect);
		break;
	case Vertical:
		anchorArea.SetRect(barHeight, 0, hRect, wRect);
		break;
	}

	CBrush bsh(GetSysColor(COLOR_3DFACE));
	pDC->FillRect(anchorArea, &bsh);

	//return CWnd::OnEraseBkgnd(pDC);
	return TRUE;
}
