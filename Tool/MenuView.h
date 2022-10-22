#pragma once
#include "TabDlg.h"

// CMenuView view

class CMenuView : public CView
{
	DECLARE_DYNCREATE(CMenuView)

protected:
	CMenuView();           // protected constructor used by dynamic creation
	virtual ~CMenuView();

public:
	CTabDlg m_TabDlg;

public:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
};


