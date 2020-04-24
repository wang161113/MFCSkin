#pragma once


// CCustomDrawCombox

class CCustomDrawCombox : public CComboBox
{
	DECLARE_DYNAMIC(CCustomDrawCombox)
	afx_msg void OnPaint();

public:
	CCustomDrawCombox();
	virtual ~CCustomDrawCombox();
private:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	virtual void MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct);
	virtual int CompareItem(LPCOMPAREITEMSTRUCT lpCompareItemStruct);
private:
	virtual void PreSubclassWindow();

protected:
	DECLARE_MESSAGE_MAP()
	void OnNcPaint(CDC* pDC);
};


