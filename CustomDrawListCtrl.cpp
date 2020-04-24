// CustomDrawListCtrl.cpp : 实现文件
//

#include "stdafx.h"
#include "CustomDrawListCtrl.h"


// CCustomDrawListCtrl

IMPLEMENT_DYNAMIC(CCustomDrawListCtrl, CListCtrl)

CCustomDrawListCtrl::CCustomDrawListCtrl()
{
	m_nRowHeight = 120;
	m_txtColor = SKinColors::black;
	m_txtHighLightColor = SKinColors::blue;
	m_selectedBorderColor = SKinColors::blue;
	m_highLightColColor = SKinColors::green;
	m_highLightColColor2 = SKinColors::red;

}

CCustomDrawListCtrl::~CCustomDrawListCtrl()
{
}


BEGIN_MESSAGE_MAP(CCustomDrawListCtrl, CListCtrl)
	ON_WM_MEASUREITEM_REFLECT()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()



// CCustomDrawListCtrl 消息处理程序
void CCustomDrawListCtrl::PreSubclassWindow()
{
	ModifyStyle(0,LVS_OWNERDRAWFIXED);
	SetExtendedStyle(LVS_EX_CHECKBOXES);
	CListCtrl::PreSubclassWindow();
	CHeaderCtrl* pHeader = GetHeaderCtrl();
	if (pHeader)
	{
		m_headerCtrl.SubclassWindow(pHeader->GetSafeHwnd());
	}
}
void CCustomDrawListCtrl::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	TCHAR lpBuffer[256];
	LV_ITEM lvi;
	lvi.mask = LVIF_TEXT | LVIF_PARAM ;
	lvi.iItem = lpDrawItemStruct->itemID ; 
	lvi.iSubItem = 0;
	lvi.pszText = lpBuffer ;
	lvi.cchTextMax = sizeof(lpBuffer);
	VERIFY(GetItem(&lvi));
	LV_COLUMN lvc, lvcprev ;
	::ZeroMemory(&lvc, sizeof(lvc));
	::ZeroMemory(&lvcprev, sizeof(lvcprev));
	lvc.mask = LVCF_WIDTH | LVCF_FMT;
	lvcprev.mask = LVCF_WIDTH | LVCF_FMT;
	CDC* pDC;
	pDC = CDC::FromHandle(lpDrawItemStruct->hDC);
	CRect rtClient;
	GetClientRect(&rtClient);
	CRect checkBoxRect;
	checkBoxRect.CopyRect(&lpDrawItemStruct->rcItem);


	

	//高亮选中的行
	if(lpDrawItemStruct->itemState & ODS_SELECTED)
	{
		CBrush rowBrush;
		rowBrush.CreateSolidBrush(m_selectedBorderColor);
		CRect rcRow;
		rcRow.CopyRect(&lpDrawItemStruct->rcItem);
		pDC->FrameRect(rcRow,&rowBrush);
	}
	//画出每一个单元格，包括颜色和文字
	for ( int nCol=0; GetColumn(nCol, &lvc); nCol++)
	{
		if ( nCol > 0 ) 
		{
			GetColumn(nCol-1, &lvcprev) ;
			lpDrawItemStruct->rcItem.left += lvcprev.cx ;
			lpDrawItemStruct->rcItem.right += lpDrawItemStruct->rcItem.left; 
		}
		CRect rcItem;   
		if (!GetSubItemRect(lpDrawItemStruct->itemID,nCol,LVIR_LABEL,rcItem))//获取单元格区域   
			continue;   
		::ZeroMemory(&lvi, sizeof(lvi));
		lvi.iItem = lpDrawItemStruct->itemID;
		lvi.mask = LVIF_TEXT | LVIF_PARAM;
		lvi.iSubItem = nCol;
		lvi.pszText = lpBuffer;
		lvi.cchTextMax = sizeof(lpBuffer);
		VERIFY(GetItem(&lvi));//获取单元格的内容信息
		CRect rcTemp;
		rcTemp = rcItem;
		if (nCol==0)
		{
			rcTemp.left -=2;
		}
		if ( (lpDrawItemStruct->itemState & ODS_SELECTED))
		{
			//这里面可以重绘每个单元格的选中风格,目前只改变其颜色
			pDC->SetTextColor(m_txtHighLightColor) ;
		}
		else
		{
			COLORREF color;
			color = GetBkColor();
			pDC->FillSolidRect(rcTemp,color);
			pDC->SetTextColor(m_txtColor);
			int colCount = m_headerCtrl.GetItemCount();
			CString str1 = lpBuffer;
			CString str2 = "正常";
			if((nCol == colCount-1) && str1.Compare(str2) == 0){//改变最后一列内容的颜色
				pDC->SetTextColor(m_highLightColColor);
			}
			else if ((nCol == colCount-1) && str1.Compare(str2) != 0)
			{
				pDC->SetTextColor(m_highLightColColor2);
			}
		}
		pDC->SelectObject(GetStockObject(DEFAULT_GUI_FONT));
		TEXTMETRIC metric;
		pDC->GetTextMetrics(&metric);
		int ofst;
		ofst = rcItem.Height() - metric.tmHeight;
		rcItem.OffsetRect(0,ofst/2);

		CFont nFont ,* nOldFont; 
		nFont.CreateFont(14,0,0,0,0,FALSE,FALSE,0,0,0,0,0,0,_TEXT("Arial"));//创建字体 
		nOldFont = pDC->SelectObject(&nFont);
		DrawText(lpDrawItemStruct->hDC, lpBuffer, strlen(lpBuffer), 
			&rcItem, DT_CENTER);

		pDC->SelectStockObject(SYSTEM_FONT) ;
	}
	//画checkbox
	int nSize = GetSystemMetrics(SM_CYMENU);
	checkBoxRect.top = checkBoxRect.top+3;
	checkBoxRect.left = checkBoxRect.left + 5;
	checkBoxRect.right = checkBoxRect.left + 12,
		checkBoxRect.bottom = checkBoxRect.top + 12;

	//lpDrawItemStruct->itemState = lpDrawItemStruct->itemState|ODS_CHECKED;
	if (!m_itemVector.empty())
	{
		if (m_itemVector[lpDrawItemStruct->itemID].isChecked)
		{
			pDC->DrawFrameControl(checkBoxRect,
				DFC_BUTTON, 
				DFCS_BUTTONCHECK|DFCS_CHECKED);
		}
		else
		{
			pDC->DrawFrameControl(checkBoxRect,
				DFC_BUTTON, 
				DFCS_BUTTONCHECK);
		}
	}
	
	
}
void CCustomDrawListCtrl::MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct)
{
	if (m_nRowHeight>0)
	{
		lpMeasureItemStruct->itemHeight = m_nRowHeight;
	}
}
void CCustomDrawListCtrl::SetRowHeight(int rowHeight)
{
	m_nRowHeight = rowHeight;
	CRect rcWin;
	GetWindowRect(&rcWin);
	WINDOWPOS wp;
	wp.hwnd = m_hWnd;
	wp.cx = rcWin.Width();
	wp.cy = rcWin.Height();
	wp.flags = SWP_NOACTIVATE | SWP_NOMOVE | SWP_NOOWNERZORDER | SWP_NOZORDER;
	SendMessage(WM_WINDOWPOSCHANGED, 0, (LPARAM)&wp);
}
int CCustomDrawListCtrl::InsertColumn(int nCol, LPCTSTR lpszColumnHeading, int nFormat /* = LVCFMT_LEFT */, int nWidth /* = -1 */, int nSubItem /* = -1 */)
{
	return CListCtrl::InsertColumn(nCol,lpszColumnHeading,nFormat,nWidth,nSubItem);
}
void CCustomDrawListCtrl::OnLButtonDown(UINT nFlags, CPoint point)
{
	if (m_itemVector.empty())
	{
		return;
	}
	UINT uFlags = 0;
	int nHitItem =this->HitTest(point, &uFlags);

	// we need additional checking in owner-draw mode
	// because we only get LVHT_ONITEM
	BOOL bHit = FALSE;
	if (uFlags == LVHT_ONITEM && (GetStyle() & LVS_OWNERDRAWFIXED))
	{
		CRect rect;
		this->GetItemRect(nHitItem,&rect,0);
		CRect checkboxRect;
		checkboxRect.CopyRect(&rect);
		checkboxRect.right = checkboxRect.left+20;
		if (checkboxRect.PtInRect(point))
		{
			m_itemVector[nHitItem].isChecked = !m_itemVector[nHitItem].isChecked;
		}
	}
	else if (uFlags & LVHT_ONITEMSTATEICON)
		bHit = TRUE;
	CListCtrl::OnLButtonDown(nFlags,point);
}
int CCustomDrawListCtrl::InsertItem(int nItem,LPCTSTR lpszItem)
{
	CListCtrl::InsertItem(nItem,lpszItem);

	ITEM_CHECK newItem;
	newItem.itemID=nItem;
	newItem.isChecked=FALSE;
	m_itemVector.push_back(newItem);
	return nItem;
}
void CCustomDrawListCtrl::DeleteAllItems()
{
	CListCtrl::DeleteAllItems();
	m_itemVector.clear();
}
vector<ITEM_CHECK>& CCustomDrawListCtrl::GetItemChecked()
{
	m_itemCheckVector.clear();
	for (int i=0;i<m_itemVector.size();i++)
	{
		if (m_itemVector[i].isChecked)
		{
			m_itemCheckVector.push_back(m_itemVector[i]);
		}
	}
	return m_itemCheckVector;
}



