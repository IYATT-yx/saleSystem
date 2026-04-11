// AddDialog.cpp: 实现文件
//

#include "pch.h"
#include "saleSystem.h"
#include "AddDialog.hpp"

#include "StoreManager.hpp"


// AddDialog

IMPLEMENT_DYNCREATE(AddDialog, CFormView)

AddDialog::AddDialog()
	: CFormView(DIALOG_ADD)
	, stockPriceEditValue(0)
	, stockNumEditValue(0)
	, newProductEditValue(_T(""))
	, newPriceEditValue(0)
	, newNumEditValue(0)
{

}

AddDialog::~AddDialog()
{
}

void AddDialog::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT2, stockPriceEditValue);
	DDX_Text(pDX, IDC_EDIT3, stockNumEditValue);
	DDX_Text(pDX, IDC_EDIT4, newProductEditValue);
	DDX_Text(pDX, IDC_EDIT5, newPriceEditValue);
	DDX_Text(pDX, IDC_EDIT6, newNumEditValue);
	DDX_Control(pDX, IDC_COMBO2, stockProductComboBoxControl);
}

BEGIN_MESSAGE_MAP(AddDialog, CFormView)
	ON_CBN_SELCHANGE(IDC_COMBO2, &AddDialog::OnCbnSelchangeCombo2)
	ON_BN_CLICKED(IDC_BUTTON3, &AddDialog::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &AddDialog::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &AddDialog::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON6, &AddDialog::OnBnClickedButton6)
END_MESSAGE_MAP()


// AddDialog 诊断

#ifdef _DEBUG
void AddDialog::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void AddDialog::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// AddDialog 消息处理程序

void AddDialog::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: 在此添加专用代码和/或调用基类

	productsVector products;
	StoreManager::readProducts(products);
	for (productsVector::iterator product = products.begin(); product != products.end(); ++product)
	{
		this->stockProductComboBoxControl.AddString(product->name);
	}
	this->stockProductComboBoxControl.SetCurSel(0);

	this->OnCbnSelchangeCombo2();
}

void AddDialog::OnCbnSelchangeCombo2()
{
	// TODO: 在此添加控件通知处理程序代码

	int curIdx = this->stockProductComboBoxControl.GetCurSel();
	CString curText;
	this->stockProductComboBoxControl.GetLBText(curIdx, curText);

	productsVector products;
	StoreManager::readProducts(products);
	for (productsVector::iterator product = products.begin(); product != products.end(); ++product)
	{
		if (curText == product->name)
		{
			this->stockPriceEditValue = product->price;
			this->stockNumEditValue = 0;
			UpdateData(FALSE);
			break;
		}
	}
}

void AddDialog::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码

	UpdateData(TRUE);

	if (this->stockNumEditValue <= 0 || this->stockPriceEditValue <= 0)
	{
		MessageBox(L"数量必须大于 0，或价格不能低于 0");
		return;
	}

	int curIdx = this->stockProductComboBoxControl.GetCurSel();
	CString curText;
	this->stockProductComboBoxControl.GetLBText(curIdx, curText);

	productsVector products;
	StoreManager::readProducts(products);
	for (productsVector::iterator product = products.begin(); product != products.end(); ++product)
	{
		if (curText == product->name)
		{
			product->stock += this->stockNumEditValue;
			CString msg;
			productsVector tmpProduct = { *product };
			StoreManager::modifyProducts(tmpProduct);
			msg.Format(L"增加库存：%d，库存总量：%d", this->stockNumEditValue, product->stock);
			MessageBox(msg.GetString());
			break;
		}
	}

	this->stockNumEditValue = 0;
	UpdateData(FALSE);
}

void AddDialog::OnBnClickedButton4()
{
	// TODO: 在此添加控件通知处理程序代码
	this->stockNumEditValue = 0;
	UpdateData(FALSE);
}

void AddDialog::OnBnClickedButton5()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);

	if (this->newNumEditValue <= 0 || this->newPriceEditValue <= 0 || this->newProductEditValue.IsEmpty())
	{
		MessageBox(L"输入信息有误");
		return;
	}

	productStruct product;
	product.name = this->newProductEditValue;
	product.price = this->newPriceEditValue;
	product.stock = this->newNumEditValue;
	productsVector tmpProduct = { product };
	StoreManager::writeProducts(tmpProduct);

	this->newProductEditValue.Empty();
	this->newPriceEditValue = 0;
	this->newNumEditValue = 0;
	UpdateData(FALSE);

	this->OnInitialUpdate();

	CString msg;
	msg.Format(L"添加商品：%s，单价：%f，数量：%d", product.name.GetString(), product.price, product.stock);
	MessageBox(msg.GetString());
}

void AddDialog::OnBnClickedButton6()
{
	// TODO: 在此添加控件通知处理程序代码
	this->newProductEditValue.Empty();
	this->newPriceEditValue = 0;
	this->newNumEditValue = 0;
	UpdateData(FALSE);
}
