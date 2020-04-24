// CustomDrawBtn.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "CustomDrawBtn.h"


// CCustomDrawBtn

IMPLEMENT_DYNAMIC(CCustomDrawBtn, CButton)

CCustomDrawBtn::CCustomDrawBtn()
{
	m_bkColor = RGB(51,126,251);//Ĭ������ɫ��񱳾�
	m_hoverColor = RGB(17,94,188);//Ĭ�ϸ���ɫ
	m_textColor = RGB(255,255,255);//Ĭ��������ɫ
	m_radis = 0;//Բ�Ƿ���
	m_fontSize = 14;//����
	m_bPaintedHighLight = false;
	m_btnText = "";
	m_drawBkColor = m_bkColor;
	m_borderColor = m_bkColor;
}

CCustomDrawBtn::~CCustomDrawBtn()
{
}


BEGIN_MESSAGE_MAP(CCustomDrawBtn, CButton)
	ON_WM_MOUSEMOVE(WM_MOUSEMOVE,CCustomDrawBtn::OnMouseMove)
	ON_WM_TIMER(WM_TIMER,CCustomDrawBtn::OnTimer)
END_MESSAGE_MAP()



// CCustomDrawBtn ��Ϣ�������


void CCustomDrawBtn::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	Redraw(lpDrawItemStruct);
}
void CCustomDrawBtn::SetColorStyle(COLORREF bkColor,COLORREF hoverColor,COLORREF textColor,COLORREF borderColor,int fontSize,int radis)
{
	m_bkColor = bkColor;
	m_hoverColor = hoverColor;
	m_radis = radis;
	m_textColor = textColor;
	m_fontSize = fontSize;
	m_drawBkColor = m_bkColor;
	m_borderColor = borderColor;
	Invalidate();
	
}
void CCustomDrawBtn::SetFontSize(int fontsize)
{
	m_fontSize = fontsize;
}
void CCustomDrawBtn::SetTextColor(COLORREF color)
{
	m_textColor = color;
}
void CCustomDrawBtn::Redraw(LPDRAWITEMSTRUCT lpDrSt)
{
	int roundRadis = m_radis;//Բ�Ƿ���
	GetClientRect(&m_rcDrawClient);
	CDC* pDC = GetDC();
	if(pDC)
	{
		GetWindowText(m_btnText);
		Draw(lpDrSt,pDC,m_rcDrawClient,m_radis,m_drawBkColor,m_btnText);
		ReleaseDC(pDC);
	}
}
void CCustomDrawBtn::Draw(LPDRAWITEMSTRUCT lpDrSt,CDC* pDC,CRect rect,int roundRadis,COLORREF bkColor,CString strText)
{
	if(pDC)
	{
		CRect rect,rectFocus;
		GetClientRect(&rect);
		rectFocus.CopyRect(&rect);
		rectFocus.DeflateRect(4,4,4,4);

		COLORREF textColor = m_textColor;
		COLORREF borderColor = m_borderColor;
		if(lpDrSt->itemState & ODS_DISABLED)
		{
			bkColor = SKinColors::lightgray;
			textColor = SKinColors::dark_gray;
			borderColor = SKinColors::dark_gray;
		}
		//HRGN h_rgn = CreateRoundRectRgn(0,0,rect.right,rect.bottom,roundRadis,roundRadis);
		//SetWindowRgn(h_rgn,TRUE);
		CPen pen(PS_SOLID,1,borderColor);//�߿���ɫ
		CPen* pOldPen = pDC->SelectObject(&pen);
		CFont font;
		font.CreateFont(m_fontSize,0,0,0,700,FALSE,FALSE,FALSE,DEFAULT_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH,"����");
		CFont* pOldFont = pDC->SelectObject(&font);
		// �����ɫ
		CBrush brush;

		brush.CreateSolidBrush(bkColor);
		pDC->SelectObject(&brush);
		pDC->RoundRect(0,0,rect.right,rect.bottom,roundRadis,roundRadis);
		pDC->SelectObject(pOldPen);
		//���ư�ť�ı�
		//����һ��CRect���ڻ����ı� 
		CRect textRect;
		//������������ 
		textRect.CopyRect(&m_rcDrawClient);
		//����ַ����ߴ�
		CString btnCaption = m_btnText;
		CSize sz = pDC->GetTextExtent(btnCaption);
		//�����ı�λ�� ���� 
		textRect.top += (textRect.Height()- sz.cy)/2;
		//�����ı�����͸�� 
		pDC->SetBkMode(TRANSPARENT);
		//�����ı���ɫ
		pDC->SetTextColor(textColor); 
		//�����ı�����
		pDC->DrawText(btnCaption,&textRect,DT_RIGHT|DT_CENTER|DT_BOTTOM);

		if (lpDrSt->itemState & ODS_FOCUS)
		{
			int iPrevBkMode = pDC->GetBkMode();
			pDC->SetBkMode(TRANSPARENT);

			CPen pen(PS_DOT, 0, m_hoverColor);
			CPen *pPrevPen = pDC->SelectObject(&pen);

			CGdiObject *pPrevBrush = pDC->SelectStockObject(NULL_BRUSH);

			BOOL bRet = pDC->Rectangle(&rectFocus);

			pDC->SetBkMode(iPrevBkMode);
			pDC->SelectObject(pPrevPen);
			pDC->SelectObject(pPrevBrush);
		}

		pDC->SelectObject(pOldFont);
		font.DeleteObject();
		pen.DeleteObject();
	}
}
void CCustomDrawBtn::OnMouseMove(UINT nFlags, CPoint point)
{
	CRect rcWindow;
	GetWindowRect(&rcWindow);
	CPoint ptCursor;//�����λ��
	GetCursorPos(&ptCursor);
	if(!m_bPaintedHighLight)
	{
		SetTimer(1,10,NULL);
		m_drawBkColor = m_hoverColor;//�任����ɫ
		InvalidateRect(NULL);
		m_bPaintedHighLight = true;
	}
	CButton::OnMouseMove(nFlags,point);
}
void CCustomDrawBtn::PreSubclassWindow()
{
	
	ModifyStyle(0, BS_OWNERDRAW); // make the button owner drawn
	CButton::PreSubclassWindow();
}
void CCustomDrawBtn::OnTimer(UINT nIDEvent)
{
	CRect rcWindow;
	GetWindowRect(&rcWindow);
	CPoint ptCursor;//�����λ��
	GetCursorPos(&ptCursor);
	if(!rcWindow.PtInRect(ptCursor))//���ڰ�ť��
	{
		CButton::OnTimer(nIDEvent);
		KillTimer(1);
		m_drawBkColor = m_bkColor;//�ָ�����ɫ
		InvalidateRect(NULL);
		m_bPaintedHighLight = false;
		return;
	}
	CButton::OnTimer(nIDEvent);
}