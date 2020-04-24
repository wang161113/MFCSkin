#pragma once


// CCustomerStatic

class CCustomerDrawStatic : public CStatic
{
	DECLARE_DYNAMIC(CCustomerDrawStatic)
	afx_msg HBRUSH CtlColor(CDC* pDC, UINT nCtlColor);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);

public:
	CCustomerDrawStatic();
	virtual ~CCustomerDrawStatic();
	void SetTextColor(COLORREF color);
	void SetBkColor(COLORREF color);
	void SetNeedChangeCur(BOOL bChange);
	void SetBkTransparent(BOOL bTrans);

protected:
	DECLARE_MESSAGE_MAP()
private:
	COLORREF m_txtColor;
	COLORREF m_bkColor;
	CBrush   m_bkBrush;
	BOOL     m_bChangeCursor;
	BOOL     m_bTransparent;//±³¾°ÊÇ·ñÍ¸Ã÷

};


