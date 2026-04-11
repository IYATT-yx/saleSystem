#pragma once
#include "afxcview.h"

// SelectView 视图

class SelectView : public CTreeView
{
	DECLARE_DYNCREATE(SelectView)

protected:
	SelectView();           // 动态创建所使用的受保护的构造函数
	virtual ~SelectView();

public:
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	DECLARE_MESSAGE_MAP()

private:
	CTreeCtrl* treeCtrl;
	CImageList imageList;
public:
	virtual void OnInitialUpdate();
	afx_msg void OnTvnSelchanged(NMHDR* pNMHDR, LRESULT* pResult);
};


