#pragma once


// CCustomDrawEdit

class CCustomDrawEdit : public CEdit
{
	DECLARE_DYNAMIC(CCustomDrawEdit)
	afx_msg void OnPaint();
	afx_msg void OnNcPaint();
	afx_msg HBRUSH CtlColor(CDC* pDC, UINT nCtlColor);
	
public:
	CCustomDrawEdit();
	virtual ~CCustomDrawEdit();
	BOOL SubclassDlgItem(UINT nID,CWnd* pParent);
	void SetBkColor(COLORREF color);

protected:
	DECLARE_MESSAGE_MAP()
	void Draw();
private:
	COLORREF m_bkColor;
	COLORREF m_txtColor;
	CBrush   m_bkBrush;
	BOOL     m_bDraw;
	CRect    m_rectNCBottom;
	CRect    m_rectNCTop;
};


