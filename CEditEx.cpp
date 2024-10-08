// CEditEx.cpp : 实现文件
//

#include "stdafx.h"
#include "CEditEx.h"


// CCEditEx

IMPLEMENT_DYNAMIC(CCEditEx, CStatic)

CCEditEx::CCEditEx()
{
	m_normal_in_color = RGB(241,241,241);
	m_normal_out_color = RGB(241,241,241);
	m_bkColor = m_normal_in_color;
	m_text_color = RGB(0,0,0);
	m_radian = 10;
	m_padding = 20;
	m_bkBrush.CreateSolidBrush(m_normal_in_color);
	m_strTip = "";
	m_bPwdInput = FALSE;
	m_bDisable = FALSE;
}

CCEditEx::~CCEditEx()
{
}


BEGIN_MESSAGE_MAP(CCEditEx, CStatic)
	ON_WM_NCPAINT()
	ON_WM_ERASEBKGND()
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()



// CCEditEx 消息处理程序


void CCEditEx::PreSubclassWindow()
{

	DWORD dwStyle = GetStyle();
	SetWindowLong(GetSafeHwnd(), GWL_STYLE, dwStyle | SS_OWNERDRAW | SS_NOTIFY);
	CStatic::PreSubclassWindow();
}

void CCEditEx::OnNcPaint()
{
	CStatic::OnNcPaint();
}
void CCEditEx::OnPaint()
{
	CStatic::OnPaint();
}

void CCEditEx::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{

	CRect rc;
	rc = lpDrawItemStruct->rcItem;

	CDC dc;
	dc.Attach(lpDrawItemStruct->hDC);
	dc.SelectObject(&m_bkBrush);
	DrawBorder(&dc,rc);

	rc.DeflateRect(m_padding, m_padding);

	if (m_edit.GetSafeHwnd() && !m_bDisable) 
	{
		m_edit.ShowWindow(SW_SHOW);
		m_edit.SetBkColor(m_bkColor);
		m_edit.SetWindowText(m_strText);
	}
	else if(m_edit.GetSafeHwnd() && m_bDisable)
	{
		m_edit.EnableWindow(FALSE);
		m_edit.SetBkColor(m_bkColor);
		m_edit.SetWindowText(m_strText);
	}
    else 
	{

		GetClientRect(&rc);
		rc.DeflateRect(10,10);
		m_edit.Create(WS_CHILD | WS_VISIBLE | ES_LEFT | ES_AUTOHSCROLL, rc, this, 1);
		m_edit.SetFont(GetFont());
			//m_edit.SetCueBanner("123");
		if(m_bPwdInput){
			m_edit.SetPasswordChar('*');
		}
		m_edit.SetWindowText(m_strText);
		m_edit.SetBkColor(m_bkColor);
		m_edit.ShowWindow(SW_SHOW);
		if(m_bDisable)
		{
			m_edit.EnableWindow(FALSE);
		}

	}
	ReleaseDC(&dc);
}
void CCEditEx::DrawBorder(CDC* dc,CRect &rc) {
	CPen inpen(PS_SOLID, 1, m_normal_out_color);
	CPen outpen(PS_SOLID, 1, m_normal_in_color);
	CPen * oldPen = dc->SelectObject(&inpen);
	dc->RoundRect(rc, CPoint(m_radian, m_radian));
	rc.InflateRect(-1, -1);
	dc->SelectObject(&outpen);
	dc->RoundRect(rc, CPoint(m_radian, m_radian));
	dc->SelectObject(oldPen);
	oldPen->Detach();
	oldPen = NULL;
}
void CCEditEx::setTipText(CString tip)
{
	m_strTip = tip;
	InvalidateRect(NULL);
}
void CCEditEx::SetBkColor(COLORREF color)
{
	m_bkColor = color;
	m_bkBrush.DeleteObject();
	m_bkBrush.CreateSolidBrush(color);
	if(m_edit.GetSafeHwnd())
	{
		m_edit.SetBkColor(color);
	}
	Invalidate(TRUE);
}
void CCEditEx::SetBorderColor(COLORREF color)
{

}
void CCEditEx::setPwdMode(BOOL bPwdMode)
{
	m_bPwdInput = bPwdMode;
}
void CCEditEx::SetWindowText(CString strText)
{
	m_strText = strText;
	Invalidate(TRUE);
}
void CCEditEx::GetWindowText(CString& strText)
{
	m_edit.GetWindowText(strText);
}
BOOL CCEditEx::OnEraseBkgnd(CDC* pDC)
{
	return TRUE;
}
CCustomDrawEdit& CCEditEx::GetMyEdit()
{
	return m_edit;
}
void CCEditEx::SetDisable(BOOL isDisable)
{
	m_bDisable = isDisable;
	Invalidate(TRUE);
}


HBRUSH CCEditEx::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CStatic::OnCtlColor(pDC, pWnd, nCtlColor);
	return hbr;
}