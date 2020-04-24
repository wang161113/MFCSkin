#pragma once
#include "CustomDrawHeaderCtrl.h"
#include <vector>
using namespace std;

// CCustomDrawListCtrl

//±£´æcheckbox×´Ì¬
struct ITEM_CHECK 
{
	int itemID;
	BOOL isChecked;
};
class CCustomDrawListCtrl : public CListCtrl
{
	DECLARE_DYNAMIC(CCustomDrawListCtrl)

public:
	CCustomDrawListCtrl();
	virtual ~CCustomDrawListCtrl();
	void SetRowHeight(int rowHeight);

protected:
	DECLARE_MESSAGE_MAP()
	virtual void PreSubclassWindow();  
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
protected:  
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	void MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct);  
public:
	int InsertColumn(int nCol, LPCTSTR lpszColumnHeading,  
		int nFormat = LVCFMT_LEFT, int nWidth = -1, int nSubItem = -1);
	int InsertItem(int nItem,LPCTSTR lpszItem);
	void DeleteAllItems();
	vector<ITEM_CHECK>& GetItemChecked();
protected:
	CCustomDrawHeaderCtrl m_headerCtrl;
	int m_nRowHeight;
	COLORREF m_txtColor;
	COLORREF m_txtHighLightColor;
	COLORREF m_selectedBorderColor;
	COLORREF m_highLightColColor;
	COLORREF m_highLightColColor2;
	vector<ITEM_CHECK> m_itemVector;
	vector<ITEM_CHECK> m_itemCheckVector;

};


