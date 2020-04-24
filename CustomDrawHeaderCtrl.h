#pragma once


// CCustomDrawHeaderCtrl

class CCustomDrawHeaderCtrl : public CHeaderCtrl
{
	DECLARE_DYNAMIC(CCustomDrawHeaderCtrl)

public:
	CCustomDrawHeaderCtrl();
	virtual ~CCustomDrawHeaderCtrl();

protected:
	DECLARE_MESSAGE_MAP()
	afx_msg void OnPaint();
	LRESULT OnLayout( WPARAM wParam, LPARAM lParam ); 
private:
	COLORREF m_headerBkColor;
	COLORREF m_headerTxtColor;
};


