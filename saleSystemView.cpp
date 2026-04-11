
// saleSystemView.cpp: CsaleSystemView 类的实现
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "saleSystem.h"
#endif

#include "saleSystemDoc.h"
#include "saleSystemView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CsaleSystemView

IMPLEMENT_DYNCREATE(CsaleSystemView, CView)

BEGIN_MESSAGE_MAP(CsaleSystemView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CsaleSystemView 构造/析构

CsaleSystemView::CsaleSystemView() noexcept
{
	// TODO: 在此处添加构造代码

}

CsaleSystemView::~CsaleSystemView()
{
}

BOOL CsaleSystemView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CsaleSystemView 绘图

void CsaleSystemView::OnDraw(CDC* /*pDC*/)
{
	CsaleSystemDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
}


// CsaleSystemView 打印

BOOL CsaleSystemView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CsaleSystemView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CsaleSystemView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}


// CsaleSystemView 诊断

#ifdef _DEBUG
void CsaleSystemView::AssertValid() const
{
	CView::AssertValid();
}

void CsaleSystemView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CsaleSystemDoc* CsaleSystemView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CsaleSystemDoc)));
	return (CsaleSystemDoc*)m_pDocument;
}
#endif //_DEBUG


// CsaleSystemView 消息处理程序
