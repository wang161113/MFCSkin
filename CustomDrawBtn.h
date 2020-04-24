#pragma once


// CCustomDrawBtn
//�Ի�Բ�Ǿ��ΰ�ť
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
	CRect m_rcDrawClient;//��������
	COLORREF m_bkColor;//Ĭ�ϱ�����ɫ
	COLORREF m_hoverColor;//����ƶ���ȥ����ɫ
	COLORREF m_textColor;//������ɫ
	COLORREF m_borderColor;//�߿���ɫ
	COLORREF m_drawBkColor;
	int      m_fontSize;//�����С
	int      m_radis;//Բ�Ƿ���>0,=0 ��Բ��
	BOOL     m_bPaintedHighLight;//�Ƿ��Ѿ����˸���ɫ
	CString  m_btnText;
};


