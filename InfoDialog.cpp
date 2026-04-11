// InfoDialog.cpp: 实现文件
//

#include "pch.h"
#include "saleSystem.h"
#include "InfoDialog.hpp"

#include "StoreManager.hpp"

// InfoDialog

IMPLEMENT_DYNCREATE(InfoDialog, CFormView)

InfoDialog::InfoDialog()
	: CFormView(DIALOG_INFO)
{

}

InfoDialog::~InfoDialog()
{
}

void InfoDialog::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, infoListControl);
}

BEGIN_MESSAGE_MAP(InfoDialog, CFormView)
END_MESSAGE_MAP()


// InfoDialog 诊断

#ifdef _DEBUG
void InfoDialog::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void InfoDialog::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// InfoDialog 消息处理程序


void InfoDialog::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: 在此添加专用代码和/或调用基类

	// 显示表头
	this->infoListControl.SetExtendedStyle(this->infoListControl.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	CString field[] = { L"商品ID", L"商品名称", L"商品价格", L"库存数量" };
	for (int i = 0; i < sizeof(field) / sizeof(field[0]); ++i)
	{
		this->infoListControl.InsertColumn(i, field[i], LVCFMT_CENTER, 90);
	}

	// 读取商品信息
	productsVector products;
	StoreManager::readProducts(products);

	// 显示数据
	int idx = 0;
	CString tmpStr;
	for (productsVector::iterator product = products.begin(); product != products.end(); ++product)
	{
		tmpStr.Format(L"%d", product->id);
		this->infoListControl.InsertItem(idx, tmpStr);
		this->infoListControl.SetItemText(idx, 1, product->name);
		tmpStr.Format(L"%f", product->price);
		this->infoListControl.SetItemText(idx, 2, tmpStr);
		tmpStr.Format(L"%d", product->stock);
		this->infoListControl.SetItemText(idx, 3, tmpStr);

		++idx;
	}
}
