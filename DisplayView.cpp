// DisplayView.cpp: 实现文件
//

#include "pch.h"
#include "saleSystem.h"
#include "DisplayView.hpp"


// DisplayView

IMPLEMENT_DYNCREATE(DisplayView, CFormView)

DisplayView::DisplayView()
	: CFormView(IDD_DisplayView1)
{

}

DisplayView::~DisplayView()
{
}

void DisplayView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(DisplayView, CFormView)
END_MESSAGE_MAP()


// DisplayView 诊断

#ifdef _DEBUG
void DisplayView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void DisplayView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// DisplayView 消息处理程序
