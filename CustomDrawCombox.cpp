// CustomDrawCombox.cpp : 实现文件
//

#include "stdafx.h"
#include "CustomDrawCombox.h"


// CCustomDrawCombox

IMPLEMENT_DYNAMIC(CCustomDrawCombox, CComboBox)

CCustomDrawCombox::CCustomDrawCombox()
{
	COMBOBOXINFO si;
	::GetComboBoxInfo(this->GetSafeHwnd(),&si);
	int iiii=0;
}

CCustomDrawCombox::~CCustomDrawCombox()
{
}


BEGIN_MESSAGE_MAP(CCustomDrawCombox, CComboBox)
	ON_WM_PAINT()
END_MESSAGE_MAP()



// CCustomDrawCombox 消息处理程序


void CCustomDrawCombox::PreSubclassWindow()
{
	
	ModifyStyle(0,BS_OWNERDRAW);
	CComboBox::PreSubclassWindow();
}
void CCustomDrawCombox::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	CString strDrawText;
	if(!lpDrawItemStruct->itemID!=-1)
	{
		GetLBText(lpDrawItemStruct->itemID,strDrawText);
	}
	else
	{
		strDrawText = "请选择";
	}
	TEXTMETRIC TextMetr;
	CDC* pDC = CDC::FromHandle(lpDrawItemStruct->hDC);
	if(pDC)
	{
		pDC->GetTextMetrics(&TextMetr);
		CRect rcClient;
		GetClientRect(&rcClient);

		if((lpDrawItemStruct->itemState & ODS_SELECTED)&&
			(lpDrawItemStruct->itemAction&(ODA_DRAWENTIRE|ODA_SELECT)))
		{
			pDC->FillSolidRect(&lpDrawItemStruct->rcItem,RGB(101,160,251));
			pDC->SetBkColor(::GetSysColor(COLOR_HIGHLIGHT));
			pDC->SetTextColor(RGB(255,255,255));
			pDC->TextOut(lpDrawItemStruct->rcItem.left,lpDrawItemStruct->rcItem.top,strDrawText);
		}
		else if (lpDrawItemStruct->itemAction&(ODA_SELECT|ODA_DRAWENTIRE))
		{
			pDC->FillSolidRect(&lpDrawItemStruct->rcItem,RGB(255,255,255));
			pDC->SetBkColor(::GetSysColor(COLOR_WINDOW));
			pDC->SetTextColor(::GetSysColor(COLOR_WINDOWTEXT));
			pDC->TextOut(lpDrawItemStruct->rcItem.left,lpDrawItemStruct->rcItem.top,strDrawText);
		}
		ReleaseDC(pDC);
	}

}
void CCustomDrawCombox::MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct)
{
	lpMeasureItemStruct->itemHeight = 40;
}
int CCustomDrawCombox::CompareItem(LPCOMPAREITEMSTRUCT lpCompareItemStruct)
{
	return 1;
}
void CCustomDrawCombox::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	OnNcPaint(&dc);
}
void CCustomDrawCombox::OnNcPaint(CDC* pDC)
{
	//绘制客户区
	CDC dMemDC;
	dMemDC.CreateCompatibleDC(pDC);
	dMemDC.SetMapMode(pDC->GetMapMode());

	//画动作
	CBitmap mNewBmp;
	CRect rc;
	GetClientRect(&rc);

	mNewBmp.CreateCompatibleBitmap(pDC, rc.right - rc.left, rc.bottom - rc.top);
	CBitmap* pOldBmp = dMemDC.SelectObject(&mNewBmp);
	CPen pen(PS_SOLID,1,RGB(200,200,200));
	CPen *pOldPen = dMemDC.SelectObject(&pen);
	CBrush bkBrush;
	bkBrush.CreateSolidBrush(RGB(255,255,255));
	dMemDC.SelectObject(&bkBrush);
	CPoint pt(10,10);
	dMemDC.Rectangle(rc);//画整个客户区域

	CRect rcEnd(rc);//按钮区域
	rcEnd.left = rc.right - 20;
	//画右边的三角形按钮
	CBrush bkBrushRect;
	bkBrushRect.CreateSolidBrush(RGB(21,123,237));
	dMemDC.SelectObject(&bkBrushRect);
	dMemDC.Rectangle(rcEnd);
	//画三角形
	CRgn rgn;
	CPoint ptAngle[3];
	int angleSideWidth = 8;//三角形边长
	//第一个点的坐标
	ptAngle[0].x = rcEnd.left+rcEnd.Width()/2-angleSideWidth/2;
	ptAngle[0].y = rcEnd.top+rcEnd.Height()/2-2;
	//第二个点的坐标
	ptAngle[1].x = ptAngle[0].x + angleSideWidth;
	ptAngle[1].y = ptAngle[0].y;
	//第三个点的坐标
	ptAngle[2].x = rcEnd.left+rcEnd.Width()/2;
	ptAngle[2].y = ptAngle[0].y + 5;
	CBrush brushAngle;
	rgn.CreatePolygonRgn(ptAngle, 3, ALTERNATE); //创建区域  
	brushAngle.CreateSolidBrush( RGB(255,255,255) ); //创建画刷
	dMemDC.FillRgn( &rgn, &brushAngle ); //填充区域
	//dMemDC.DrawFrameControl( &rcEnd,DFC_SCROLL,DFCS_SCROLLDOWN|DFCS_FLAT|DFCS_MONO );
	pDC->BitBlt(rc.left, rc.top, rc.right - rc.left, rc.bottom - rc.top, &dMemDC,
		rc.left ,rc.top, SRCCOPY);
	//恢复
	dMemDC.SelectObject(pOldBmp);
	dMemDC.SelectObject(pOldPen);
	pOldPen->DeleteObject();
	pOldBmp->DeleteObject();
	dMemDC.DeleteDC();
	bkBrush.DeleteObject();
	bkBrushRect.DeleteObject();
	brushAngle.DeleteObject();
}