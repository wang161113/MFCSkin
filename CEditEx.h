#pragma once
#include "CustomDrawEdit.h"

// CCEditEx

class CCEditEx : public CStatic
{
	DECLARE_DYNAMIC(CCEditEx)

public:
	CCEditEx();
	virtual ~CCEditEx();
	CCustomDrawEdit& GetMyEdit();
	void setTipText(CString tip);
	void setPwdMode(BOOL bPwdMode);
	void SetWindowText(CString strText);
	void GetWindowText(CString& strText);
	void SetBkColor(COLORREF color);
	void SetBorderColor(COLORREF color);
	void SetDisable(BOOL isDisable);

protected:
	DECLARE_MESSAGE_MAP()
	virtual void PreSubclassWindow();
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	void DrawBorder(CDC* dc, CRect &rc);
	void OnNcPaint();
	void OnPaint();
protected:
	CCustomDrawEdit m_edit;
	int		m_radian;
	int		m_padding;
	COLORREF m_normal_in_color;
	COLORREF m_normal_out_color;
	COLORREF m_bkColor;
	COLORREF m_text_color;
	CBrush   m_bkBrush;
	CString  m_strTip;
	BOOL     m_bPwdInput;
	CString  m_strText;
	BOOL     m_bDisable;

};


