// CustomDrawGroupBox.cpp : 实现文件
//

#include "stdafx.h"
#include "CustomDrawGroupBox.h"


// CCustomDrawGroupBox

IMPLEMENT_DYNAMIC(CCustomDrawGroupBox, CButton)

CCustomDrawGroupBox::CCustomDrawGroupBox()
{
	m_bkColor = RGB(255,255,255);
	m_borderColor = RGB(255,255,255);
}

CCustomDrawGroupBox::~CCustomDrawGroupBox()
{
}


BEGIN_MESSAGE_MAP(CCustomDrawGroupBox, CButton)
	ON_WM_PAINT()
END_MESSAGE_MAP()



// CCustomDrawGroupBox 消息处理程序
void CCustomDrawGroupBox::OnPaint()
{
	CPaintDC dc(this);
	CRect rcClient;
	GetClientRect(&rcClient);
	if(dc)
	{
		CBrush bkBrush;
		CPen   borderPen(PS_SOLID,1,m_borderColor);
		CPoint pt(10,10);
		bkBrush.CreateSolidBrush(m_bkColor);
		CBrush* pOldBrush = dc.SelectObject(&bkBrush);
		CPen*   pOldPen = dc.SelectObject(&borderPen);
		dc.RoundRect(&rcClient,pt);
		dc.SelectObject(pOldBrush);
		dc.SelectObject(pOldPen);
		dc.SetBkMode(TRANSPARENT);
	}
}
void CCustomDrawGroupBox::PreSubclassWindow()
{

	CButton::PreSubclassWindow();
	//modified the style to avoid text overlap when press tab 
	ModifyStyle(0, BS_ICON);
}
void CCustomDrawGroupBox::SetBkColor(COLORREF color)
{
	m_bkColor = color;
}


