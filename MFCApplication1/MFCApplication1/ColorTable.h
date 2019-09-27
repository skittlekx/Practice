#pragma once

#include "CDColorTable.h"

// CColorTable

class CColorTable : public CWnd
{
	DECLARE_DYNAMIC(CColorTable)

public:
	CColorTable();
	virtual ~CColorTable();


protected:
	DECLARE_MESSAGE_MAP()
private:
	bool RegisterWindowClass();
protected:
	enum BarOrientation
	{
		Horizontal,
		Vertical
	} m_Orientation;
	int m_iBorderWidth;
	int m_iAnchorSize;
	__int64 m_i64CurrSelect;
	__int64 m_i64PressedNumber;
	CDUtils::CDColorTable colorTable;
	std::vector<CDUtils::CDColorTable::ColorTableAnchor> m_anchors;
private:
	std::vector<POINT> GetAnchorRegion(double pos);
	double PointToPos(CPoint point);
	int DrawBar(CDC * pDC);
	int DrawAnchor(CDC * pDC, const CDUtils::CDColorTable::ColorTableAnchor & anchor, bool selected = false);
public:
	CDUtils::CDColorTable::ColorTableAnchor & GetCurAnchor();
	inline const __int64 GetCurSel() const
	{
		return m_i64CurrSelect;
	}
	void CompileColorTable();
	inline const CDUtils::CDColorTable & GetColorTable() const
	{
		return colorTable;
	}
	inline void SetColorTable(const CDUtils::CDColorTable & colorTable)
	{
		this->colorTable = colorTable;
		m_anchors = colorTable.GetAnchors();
		m_i64CurrSelect = m_anchors.size() - 1;
	}
	void DelAnchor(__int64 num);
	void AddAnchor(double value, COLORREF color);
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
protected:
	int SendNotify(UINT notifyMsg);
	int PostNotify(UINT notifyMsg);
public:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};


