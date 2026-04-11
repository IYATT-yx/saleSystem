// SelectView.cpp: 实现文件
//
#include "pch.h"
#include "saleSystem.h"
#include "SelectView.hpp"
#include "MainFrm.h"

// SelectView

IMPLEMENT_DYNCREATE(SelectView, CTreeView)

SelectView::SelectView()
{

}

SelectView::~SelectView()
{
}

BEGIN_MESSAGE_MAP(SelectView, CTreeView)
	ON_NOTIFY_REFLECT(TVN_SELCHANGED, &SelectView::OnTvnSelchanged)
END_MESSAGE_MAP()


// SelectView 诊断

#ifdef _DEBUG
void SelectView::AssertValid() const
{
	CTreeView::AssertValid();
}

#ifndef _WIN32_WCE
void SelectView::Dump(CDumpContext& dc) const
{
	CTreeView::Dump(dc);
}
#endif
#endif //_DEBUG


// SelectView 消息处理程序

void SelectView::OnInitialUpdate()
{
	CTreeView::OnInitialUpdate();

	// TODO: 在此添加专用代码和/或调用基类

	// 加载图标
	HICON icon = AfxGetApp()->LoadIconW(IDI_ICON_RE);

	// 创建图片列表
	this->imageList.Create(30, 30, ILC_COLOR32, 1, 1);

	// 添加图标
	this->imageList.Add(icon);

	// 获取树控件
	this->treeCtrl = &GetTreeCtrl();

	// 树控件设置图片列表
	this->treeCtrl->SetImageList(&this->imageList, TVSIL_NORMAL);

	// 树控件设置节点
	//  节点文本，图像索引，处于选中状态时的图片索引，父节点，插入位置
	this->treeCtrl->InsertItem(L"个人信息", 0, 0, TVI_ROOT, TVI_LAST);
	this->treeCtrl->InsertItem(L"销售管理", 0, 0, TVI_ROOT, TVI_LAST);
	this->treeCtrl->InsertItem(L"库存信息", 0, 0, TVI_ROOT, TVI_LAST);
	this->treeCtrl->InsertItem(L"库存添加", 0, 0, TVI_ROOT, TVI_LAST);
	this->treeCtrl->InsertItem(L"库存删除", 0, 0, TVI_ROOT, TVI_LAST);
}

void SelectView::OnTvnSelchanged(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;

	// 获取选中的项目
	HTREEITEM item = this->treeCtrl->GetSelectedItem();

	// 获取选中项文本内容
	CString selectedText = this->treeCtrl->GetItemText(item);

	if (selectedText == L"个人信息")
	{
		// 将消息放入消息队列
		::PostMessage(
			AfxGetMainWnd()->GetSafeHwnd(), // 框架窗口对象指针
			NM_USER, // 发送自定义消息
			NM_USER, // 消息的附加参数
			0 // 消息的附加参数，这里不使用
		);
	}
	else if (selectedText == L"销售管理")
	{
		::PostMessage(AfxGetMainWnd()->GetSafeHwnd(), NM_SELL, NM_SELL, 0);
	}
	else if (selectedText == L"库存信息")
	{
		::PostMessage(AfxGetMainWnd()->GetSafeHwnd(), NM_INFO, NM_INFO, 0);
	}
	else if (selectedText == L"库存添加")
	{
		::PostMessage(AfxGetMainWnd()->GetSafeHwnd(), NM_ADD, NM_ADD, 0);
	}
	else if (selectedText == L"库存删除")
	{
		::PostMessage(AfxGetMainWnd()->GetSafeHwnd(), NM_DEL, NM_DEL, 0);
	}
}
