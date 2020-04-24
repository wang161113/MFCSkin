// CustomerStatic.cpp : 实现文件
//

#include "stdafx.h"
#include "CustomerStatic.h"


// CCustomerStatic

IMPLEMENT_DYNAMIC(CCustomerDrawStatic, CStatic)

CCustomerDrawStatic::CCustomerDrawStatic()
{
	m_txtColor = RGB(0,0,0);
	m_bkColor = RGB(255,255,255);
	m_bChangeCursor = FALSE;
	m_bTransparent = TRUE;
	m_bkBrush.CreateSolidBrush(m_bkColor);
}

CCustomerDrawStatic::~CCustomerDrawStatic()
{
}


BEGIN_MESSAGE_MAP(CCustomerDrawStatic, CStatic)
	ON_WM_CTLCOLOR_REFLECT()
	ON_WM_MOUSEMOVE(WM_MOUSEMOVE,CCustomerDrawStatic::OnMouseMove)
END_MESSAGE_MAP()



// CCustomerStatic 消息处理程序

HBRUSH CCustomerDrawStatic::CtlColor(CDC* pDC, UINT nCtlColor) 
{
	if(m_bTransparent)
	{
		pDC->SetBkMode(TRANSPARENT);   
		pDC->SetTextColor(m_txtColor);   
		return (HBRUSH)GetStockObject(HOLLOW_BRUSH);
	}
	else
	{
		pDC->SetBkColor(m_bkColor);
		pDC->SetTextColor(m_txtColor);
		return m_bkBrush;
	}
}
void CCustomerDrawStatic::SetTextColor(COLORREF color)
{
	m_txtColor = color;
	Invalidate(TRUE);
}
void CCustomerDrawStatic::SetBkTransparent(BOOL bTrans)
{
	m_bTransparent = bTrans;
}
void CCustomerDrawStatic::SetBkColor(COLORREF color)
{
	m_bkColor = color;
	if(m_bkBrush.GetSafeHandle())
	{
		m_bkBrush.DeleteObject();
		m_bkBrush.CreateSolidBrush(color);
	}
	Invalidate(TRUE);
}
void CCustomerDrawStatic::OnMouseMove(UINT nFlags, CPoint point)
{
	if(m_bChangeCursor){
		HCURSOR hcur = ::LoadCursor(NULL,IDC_HAND);
		::SetCursor(hcur);
	}
}
void CCustomerDrawStatic::SetNeedChangeCur(BOOL bChange)
{
	m_bChangeCursor = bChange;
}
