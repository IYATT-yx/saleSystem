// DelDialog.cpp: 实现文件
//

#include "pch.h"
#include "saleSystem.h"
#include "DelDialog.hpp"

#include "StoreManager.hpp"


// DelDialog

IMPLEMENT_DYNCREATE(DelDialog, CFormView)

DelDialog::DelDialog()
	: CFormView(DIALOG_DEL)
	, priceEditValue(0)
	, numEditValue(0)
{

}

DelDialog::~DelDialog()
{
}

void DelDialog::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, productComboBoxControl);
	DDX_Text(pDX, IDC_EDIT1, priceEditValue);
	DDX_Text(pDX, IDC_EDIT2, numEditValue);
}

BEGIN_MESSAGE_MAP(DelDialog, CFormView)
	ON_CBN_SELCHANGE(IDC_COMBO1, &DelDialog::OnCbnSelchangeCombo1)
	ON_BN_CLICKED(IDOK, &DelDialog::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &DelDialog::OnBnClickedCancel)
END_MESSAGE_MAP()


// DelDialog 诊断

#ifdef _DEBUG
void DelDialog::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void DelDialog::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// DelDialog 消息处理程序

void DelDialog::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: 在此添加专用代码和/或调用基类

	productsVector products;
	StoreManager::readProducts(products);

	for (productsVector::iterator product = products.begin(); product != products.end(); ++product)
	{
		this->productComboBoxControl.AddString(product->name);
	}
	this->productComboBoxControl.SetCurSel(0);

	this->OnCbnSelchangeCombo1();
}

void DelDialog::OnCbnSelchangeCombo1()
{
	// TODO: 在此添加控件通知处理程序代码

	int curIdx = this->productComboBoxControl.GetCurSel();
	CString curText;
	this->productComboBoxControl.GetLBText(curIdx, curText);

	productsVector products;
	StoreManager::readProducts(products);
	for (productsVector::iterator product = products.begin(); product != products.end(); ++product)
	{
		if (curText == product->name)
		{
			this->priceEditValue = product->price;
			this->numEditValue = 0;
			UpdateData(FALSE);
			break;
		}
	}
}

void DelDialog::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码

	UpdateData(TRUE);

	if (this->numEditValue <= 0)
	{
		MessageBox(L"数量必须大于 0");
		return;
	}

	int curIdx = this->productComboBoxControl.GetCurSel();
	CString curText;
	this->productComboBoxControl.GetLBText(curIdx, curText);

	productsVector products;
	StoreManager::readProducts(products);
	for (productsVector::iterator product = products.begin(); product != products.end(); ++product)
	{
		if (curText == product->name)
		{
			product->stock -= this->numEditValue;
			productsVector tmpProduct = { *product };
			StoreManager::modifyProducts(tmpProduct);
			CString msg;
			msg.Format(L"删除商品：%s, 单价：%f，数量：%d", product->name.GetString(), product->price, this->numEditValue);
			MessageBox(msg.GetString());
			break;
		}
	}

	this->numEditValue = 0;
	UpdateData(FALSE);
}

void DelDialog::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	this->numEditValue = 0;
	UpdateData(FALSE);
}
