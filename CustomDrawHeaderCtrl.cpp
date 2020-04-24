// CustomDrawHeaderCtrl.cpp : ʵ���ļ�
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



// CCustomDrawHeaderCtrl ��Ϣ�������

void CCustomDrawHeaderCtrl::OnPaint()
{
	CPaintDC dc(this);
	int nItems = GetItemCount();
	CRect rcClient;
	GetClientRect(&rcClient);
	//ѭ������ÿһ��
	for (int i=0;i<nItems;i++)
	{
		CRect itemRect;//ÿһ�������
		GetItemRect(i,&itemRect);
		dc.FillSolidRect(itemRect,m_headerBkColor);
		//������
		dc.SetBkMode(TRANSPARENT);  
		CFont nFont ,* nOldFont;   
		//dc.SetTextColor(RGB(250,50,50));   
		dc.SetTextColor(m_headerTxtColor);  
		nFont.CreateFont(12,0,0,0,700,FALSE,FALSE,0,0,0,0,0,0,_TEXT("����"));//��������   
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
		nFont.DeleteObject(); //�ͷ�����

		//��ʣ��û�б���ò���
		//��ͷ��ʣ�ಿ��(û�б�����ǲ���)  
		CRect rtRect;  
		CRect clientRect;  
		GetItemRect(nItems - 1,rtRect);  
		GetClientRect(clientRect); //��ǰ(CHeaderCtrl)�ؼ��Ĵ�С  
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
	//��ͷ�߶�Ϊԭ��1.5�������Ҫ��̬�޸ı�ͷ�߶ȵĻ�����1.5���һ��ȫ�ֱ���   
	int nHeight = (int)(pwpos->cy * 1.8);  
	pwpos->cy = nHeight;   
	prc->top = nHeight;   
	return lResult;
}
