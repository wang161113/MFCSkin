#pragma once


// CCustomDrawGroupBox

class CCustomDrawGroupBox : public CButton
{
	DECLARE_DYNAMIC(CCustomDrawGroupBox)

public:
	CCustomDrawGroupBox();
	virtual ~CCustomDrawGroupBox();
	void SetBkColor(COLORREF color);

protected:
	DECLARE_MESSAGE_MAP()
	virtual void PreSubclassWindow();
	afx_msg void OnPaint();
private:
	COLORREF m_bkColor;
	COLORREF m_borderColor;
};


