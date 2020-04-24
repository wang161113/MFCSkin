// CustomDrawEdit.cpp : 实现文件
//

#include "stdafx.h"
#include "CustomDrawEdit.h"


// CCustomDrawEdit

IMPLEMENT_DYNAMIC(CCustomDrawEdit, CEdit)

CCustomDrawEdit::CCustomDrawEdit()
{
	m_bkColor = RGB(241,241,241);
	m_txtColor = RGB(113,113,113);
	m_bDraw = FALSE;
	m_bkBrush.CreateSolidBrush(m_bkColor);
}

CCustomDrawEdit::~CCustomDrawEdit()
{
	m_bkBrush.DeleteObject();
}


BEGIN_MESSAGE_MAP(CCustomDrawEdit, CEdit)
	ON_WM_PAINT()
	ON_WM_NCPAINT()
	ON_WM_CTLCOLOR_REFLECT()
END_MESSAGE_MAP()



// CCustomDrawEdit 消息处理程序
HBRUSH CCustomDrawEdit::CtlColor(CDC* pDC, UINT nCtlColor) 
{
	// TODO: Change any attributes of the DC here

	// TODO: Return a non-NULL brush if the parent's handler should not be called
	// TODO: Return a non-NULL brush if the parent's handler should not be called

	//set text color
	pDC->SetTextColor(m_txtColor);
	//set the text's background color
	pDC->SetBkColor(m_bkColor);
	//return the brush used for background this sets control background
	return m_bkBrush;
}
void CCustomDrawEdit::OnPaint()
{
	CEdit::OnPaint();
}
void CCustomDrawEdit::OnNcPaint()
{
	CEdit::OnNcPaint();
	
}
void CCustomDrawEdit::Draw()
{

}
void CCustomDrawEdit::SetBkColor(COLORREF color)
{
	m_bkColor = color;
	//free brush
	if (m_bkBrush.GetSafeHandle())
		m_bkBrush.DeleteObject();
	//set brush to new color
	m_bkBrush.CreateSolidBrush(color);
	//redraw
	Invalidate(TRUE);
}