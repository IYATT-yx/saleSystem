
// MainFrm.cpp: CMainFrame 类的实现
//

#include "pch.h"
#include "framework.h"
#include "saleSystem.h"
#include "SelectView.hpp"
#include "DisplayView.hpp"
#include "UserDialog.hpp"
#include "SellDialog.hpp"
#include "InfoDialog.hpp"
#include "AddDialog.hpp"
#include "DelDialog.hpp"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()

	// 响应自定义消息
	ON_MESSAGE(NM_USER, onMyChange)
	ON_MESSAGE(NM_SELL, onMyChange)
	ON_MESSAGE(NM_INFO, onMyChange)
	ON_MESSAGE(NM_ADD, onMyChange)
	ON_MESSAGE(NM_DEL, onMyChange)
	ON_COMMAND(ID_32771, &CMainFrame::OnUser)
	ON_COMMAND(ID_32772, &CMainFrame::OnSell)
	ON_COMMAND(ID_32773, &CMainFrame::OnInfo)
	ON_COMMAND(ID_32774, &CMainFrame::OnAdd)
	ON_COMMAND(ID_32775, &CMainFrame::OnDel)
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // 状态行指示器
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

// CMainFrame 构造/析构

CMainFrame::CMainFrame() noexcept
{
	// TODO: 在此添加成员初始化代码
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("未能创建状态栏\n");
		return -1;      // 未能创建
	}
	m_wndStatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT));

	// 加载图标
	HICON winIcon = AfxGetApp()->LoadIconW(IDI_ICON_WIN);
	// 设置小图标
	SetIcon(winIcon, FALSE);

	// 设置位置(0,0)和窗口大小（800×600)
	MoveWindow(0, 0, 800, 600);
	// 居中显示
	CenterWindow();

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return TRUE;
}

// CMainFrame 诊断

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}
#endif //_DEBUG


// CMainFrame 消息处理程序


BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext)
{
	// TODO: 在此添加专用代码和/或调用基类

	//return CFrameWnd::OnCreateClient(lpcs, pContext);

	// 拆分为 1 行 2 列
	this->splitter.CreateStatic(this, 1, 2);

	// 创建左侧视图
	this->splitter.CreateView(0, 0, RUNTIME_CLASS(SelectView), CSize(200, 500), pContext);

	// 创建右侧视图
	this->splitter.CreateView(0, 1, RUNTIME_CLASS(DisplayView), CSize(600, 500), pContext);

	return TRUE;
}

afx_msg LRESULT CMainFrame::onMyChange(WPARAM wParam, LPARAM lParam)
{
	CCreateContext context;
	this->splitter.DeleteView(0, 1);
	switch (wParam)
	{
		case NM_USER:
		{
			context.m_pNewViewClass = RUNTIME_CLASS(UserDialog);
			this->splitter.CreateView(0, 1, RUNTIME_CLASS(UserDialog), CSize(600, 500), &context);
			((UserDialog*)this->splitter.GetPane(0, 1))->OnInitialUpdate();
			break;
		}
		case NM_SELL:
		{
			context.m_pNewViewClass = RUNTIME_CLASS(SellDialog);
			this->splitter.CreateView(0, 1, RUNTIME_CLASS(SellDialog), CSize(600, 500), &context);
			((SellDialog*)this->splitter.GetPane(0, 1))->OnInitialUpdate();
			break;
		}
		case NM_INFO:
		{
			context.m_pNewViewClass = RUNTIME_CLASS(InfoDialog);
			this->splitter.CreateView(0, 1, RUNTIME_CLASS(InfoDialog), CSize(600, 500), &context);
			((InfoDialog*)this->splitter.GetPane(0, 1))->OnInitialUpdate();
			break;
		}
		case NM_ADD:
		{
			context.m_pNewViewClass = RUNTIME_CLASS(AddDialog);
			this->splitter.CreateView(0, 1, RUNTIME_CLASS(AddDialog), CSize(600, 500), &context);
			((AddDialog*)this->splitter.GetPane(0, 1))->OnInitialUpdate();
			break;
		}
		case NM_DEL:
		{
			context.m_pNewViewClass = RUNTIME_CLASS(DelDialog);
			this->splitter.CreateView(0, 1, RUNTIME_CLASS(DelDialog), CSize(600, 500), &context);
			((DelDialog*)this->splitter.GetPane(0, 1))->OnInitialUpdate();
			break;
		}

	}
	this->splitter.RecalcLayout();
	this->splitter.SetActivePane(0, 1);
	context.m_pLastView = (CFormView*)this->splitter.GetPane(0, 1);
	context.m_pCurrentFrame = this;

	return 0;
}
void CMainFrame::OnUser()
{
	// TODO: 在此添加命令处理程序代码
	::PostMessage(AfxGetMainWnd()->GetSafeHwnd(), NM_USER, NM_USER, 0);
}

void CMainFrame::OnSell()
{
	// TODO: 在此添加命令处理程序代码
	::PostMessage(AfxGetMainWnd()->GetSafeHwnd(), NM_SELL, NM_SELL, 0);
}

void CMainFrame::OnInfo()
{
	// TODO: 在此添加命令处理程序代码
	::PostMessage(AfxGetMainWnd()->GetSafeHwnd(), NM_INFO, NM_INFO, 0);
}

void CMainFrame::OnAdd()
{
	// TODO: 在此添加命令处理程序代码
	::PostMessage(AfxGetMainWnd()->GetSafeHwnd(), NM_ADD, NM_ADD, 0);
}

void CMainFrame::OnDel()
{
	// TODO: 在此添加命令处理程序代码
	::PostMessage(AfxGetMainWnd()->GetSafeHwnd(), NM_DEL, NM_DEL, 0);
}
