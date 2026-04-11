// SellDialog.cpp: 实现文件
//

#include "pch.h"
#include "saleSystem.h"
#include "SellDialog.hpp"

#include "StoreManager.hpp"


// SellDialog

IMPLEMENT_DYNCREATE(SellDialog, CFormView)

SellDialog::SellDialog()
	: CFormView(DIALOG_SELL)
	, priceEditValue(0)
	, numEditValue(0)
{

}

SellDialog::~SellDialog()
{
}

void SellDialog::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, productNameComboBoxControl);
	DDX_Text(pDX, IDC_EDIT1, priceEditValue);
	DDX_Text(pDX, IDC_EDIT2, numEditValue);
	DDX_Control(pDX, IDC_EDIT3, sellEditControl);
}

BEGIN_MESSAGE_MAP(SellDialog, CFormView)
	ON_CBN_SELCHANGE(IDC_COMBO1, &SellDialog::OnCbnSelchangeCombo1)
	ON_BN_CLICKED(IDOK, &SellDialog::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &SellDialog::OnBnClickedCancel)
END_MESSAGE_MAP()


// SellDialog 诊断

#ifdef _DEBUG
void SellDialog::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void SellDialog::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// SellDialog 消息处理程序

void SellDialog::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: 在此添加专用代码和/或调用基类

	productsVector products;
	StoreManager::readProducts(products);

	for (productStruct product : products)
	{
		this->productNameComboBoxControl.AddString(product.name);
	}
	this->productNameComboBoxControl.SetCurSel(0);

	this->OnCbnSelchangeCombo1();
}



void SellDialog::OnCbnSelchangeCombo1()
{
	// TODO: 在此添加控件通知处理程序代码

	// 获取当前选中项的索引
	int curIdx = this->productNameComboBoxControl.GetCurSel();

	// 获取当前选中项的文本
	CString curText;
	this->productNameComboBoxControl.GetLBText(curIdx, curText);

	productsVector products;
	StoreManager::readProducts(products);

	for (productStruct product : products)
	{
		if (curText == product.name)
		{
			this->priceEditValue = product.price;
			this->numEditValue = 0;
			UpdateData(FALSE);
			break;
		}
	}
}

void SellDialog::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);

	if (this->numEditValue == 0)
	{
		MessageBox(L"购买数量不能为 0");
		return;
	}

	int curIdx = this->productNameComboBoxControl.GetCurSel();
	CString curText;
	this->productNameComboBoxControl.GetLBText(curIdx, curText);

	productsVector products;
	StoreManager::readProducts(products);
	for (productsVector::iterator product = products.begin(); product != products.end(); ++product)
	{
		if (curText == product->name)
		{
			if (this->numEditValue > product->stock)
			{
				CString msg;
				msg.Format(L"购买数量超出库存，当前库存数量：%d，请减小购买数量后再试", product->stock);
				MessageBox(msg.GetString());
				return;
			}
			product->stock = product->stock - this->numEditValue;
			productsVector modifyProduct = { *product };
			StoreManager::modifyProducts(modifyProduct);
			CString sellMsg;
			sellMsg.Format(L"商品：%s\r\n单价：%f\r\n数量：%d\r\n总价：%f\r\n剩余库存：%d", product->name.GetString(), product->price, this->numEditValue, product->price * this->numEditValue, product->stock);
			this->sellEditControl.SetWindowTextW(sellMsg.GetString());
			break;
		}
	}
}

void SellDialog::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	this->sellEditControl.SetWindowTextW(L"");
	this->numEditValue = 0;
	UpdateData(FALSE);
}
