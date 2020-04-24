// CustomDrawHeaderCtrl.cpp : 实现文件
//

#include "stdafx.h"
#include "CustomDrawHeaderCtrl.h"


// CCustomDrawHeaderCtrl

IMPLEMENT_DYNAMIC(CCustomDrawHeaderCtrl, CHeaderCtrl)

CCustomDrawHeaderCtrl::CCustomDrawHeaderCtrl()
{
	m_headerBkColor = SKinColors::light_gray2;
	m_headerTxtColor = RGB(0,0,0);
}

CCustomDrawHeaderCtrl::~CCustomDrawHeaderCtrl()
{
}


BEGIN_MESSAGE_MAP(CCustomDrawHeaderCtrl, CHeaderCtrl)
	ON_WM_PAINT()
	ON_MESSAGE(HDM_LAYOUT, OnLayout) 
END_MESSAGE_MAP()



// CCustomDrawHeaderCtrl 消息处理程序

void CCustomDrawHeaderCtrl::OnPaint()
{
	CPaintDC dc(this);
	int nItems = GetItemCount();
	CRect rcClient;
	GetClientRect(&rcClient);
	//循环绘制每一项
	for (int i=0;i<nItems;i++)
	{
		CRect itemRect;//每一项得区域
		GetItemRect(i,&itemRect);
		dc.FillSolidRect(itemRect,m_headerBkColor);
		//画文字
		dc.SetBkMode(TRANSPARENT);  
		CFont nFont ,* nOldFont;   
		//dc.SetTextColor(RGB(250,50,50));   
		dc.SetTextColor(m_headerTxtColor);  
		nFont.CreateFont(12,0,0,0,700,FALSE,FALSE,0,0,0,0,0,0,_TEXT("宋体"));//创建字体   
		nOldFont = dc.SelectObject(&nFont);
		TEXTMETRIC metric;  
		dc.GetTextMetrics(&metric);  
		int ofst = 0;  
		ofst = itemRect.Height() - metric.tmHeight;  
		itemRect.OffsetRect(0,ofst/2); 

		HD_ITEM hdi;
		::ZeroMemory(&hdi, sizeof(hdi));
		TCHAR lpBuffer[256];
		hdi.pszText = lpBuffer;
		hdi.mask = HDI_TEXT;
		hdi.cchTextMax = sizeof(lpBuffer);
	
		this->GetItem(i,&hdi);
		CString strText = hdi.pszText;
		dc.DrawText(strText,&itemRect,DT_CENTER);  
		dc.SelectObject(nOldFont);   
		nFont.DeleteObject(); //释放字体

		//画剩余没有标题得部分
		//画头部剩余部分(没有标题的那部分)  
		CRect rtRect;  
		CRect clientRect;  
		GetItemRect(nItems - 1,rtRect);  
		GetClientRect(clientRect); //当前(CHeaderCtrl)控件的大小  
		rtRect.left = rtRect.right+1;  
		rtRect.right = clientRect.right;   
		CRect nRect(rtRect);
		dc.FillSolidRect(rtRect,m_headerBkColor);
	}
}
LRESULT CCustomDrawHeaderCtrl::OnLayout( WPARAM wParam, LPARAM lParam )  
{  
	LRESULT lResult = CHeaderCtrl::DefWindowProc(HDM_LAYOUT, 0, lParam);   
	HD_LAYOUT &hdl = *( HD_LAYOUT * ) lParam;   
	RECT *prc = hdl.prc;   
	WINDOWPOS *pwpos = hdl.pwpos;   
	//表头高度为原来1.5倍，如果要动态修改表头高度的话，将1.5设成一个全局变量   
	int nHeight = (int)(pwpos->cy * 1.8);  
	pwpos->cy = nHeight;   
	prc->top = nHeight;   
	return lResult;
}
