#pragma once


// CCustomDrawBtn
//自绘圆角矩形按钮
class CCustomDrawBtn : public CButton
{
	DECLARE_DYNAMIC(CCustomDrawBtn)

public:
	CCustomDrawBtn();
	virtual ~CCustomDrawBtn();
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	virtual void PreSubclassWindow();
	void SetColorStyle(COLORREF bkColor,COLORREF hoverColor,COLORREF textColor,COLORREF borderColor,int fontSize,int radis);
	void SetFontSize(int fontsize);
	void SetTextColor(COLORREF color);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT nIDEvent);

protected:
	DECLARE_MESSAGE_MAP()
	void Draw(LPDRAWITEMSTRUCT lpDrSt,CDC* pDC,CRect rect,int roundRadis,COLORREF bkColor,CString strText);
	void Redraw(LPDRAWITEMSTRUCT lpDrSt);
private:
	CRect m_rcDrawClient;//绘制区域
	COLORREF m_bkColor;//默认背景颜色
	COLORREF m_hoverColor;//鼠标移动上去的颜色
	COLORREF m_textColor;//文字颜色
	COLORREF m_borderColor;//边框颜色
	COLORREF m_drawBkColor;
	int      m_fontSize;//字体大小
	int      m_radis;//圆角幅度>0,=0 无圆角
	BOOL     m_bPaintedHighLight;//是否已经画了高亮色
	CString  m_btnText;
};


