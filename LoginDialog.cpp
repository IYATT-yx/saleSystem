// LoginDialog.cpp: 实现文件
//

#include "pch.h"
#include "saleSystem.h"
#include "afxdialogex.h"
#include "LoginDialog.hpp"

#include "StoreManager.hpp"


// LoginDialog 对话框

IMPLEMENT_DYNAMIC(LoginDialog, CDialogEx)

LoginDialog::LoginDialog(CWnd* pParent /*=nullptr*/)
	: CDialogEx(DIALOG_LOGIN, pParent)
{

}

LoginDialog::~LoginDialog()
{
}

void LoginDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, usernameEditControl);
	DDX_Control(pDX, IDC_EDIT2, passwordEditControl);
}


BEGIN_MESSAGE_MAP(LoginDialog, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &LoginDialog::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &LoginDialog::OnBnClickedButton2)
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// LoginDialog 消息处理程序
#include "StoreManager.hpp"


BOOL LoginDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	CString databasePath;
	databasePath.LoadStringW(DATABASE_PATH);
	StoreManager::connect(databasePath);	

	//productStruct product;
	//product.name = "桌子";
	//product.price = 1000.5;
	//product.stock = 50;
	//productsVector products;
	//products.push_back(product);
	//StoreManager::modifyProducts(products);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void LoginDialog::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码

	// 读取用户输入的用户名和密码
	CString inputUsername, inputPassword;
	this->usernameEditControl.GetWindowTextW(inputUsername);
	this->passwordEditControl.GetWindowTextW(inputPassword);

	// 读取数据库中的用户名和密码
	CString username, password;
	StoreManager::readLogin(username, password);

	// 判断用户名和密码
	if (inputUsername == username)
	{
		if (inputPassword != password)
		{
			MessageBox(L"密码错误");
			this->usernameEditControl.SetWindowTextW(L"");
			this->passwordEditControl.SetWindowTextW(L"");
		}
		else
		{
			MessageBox(L"登录成功");
			CDialogEx::OnOK();
		}
	}
	else
	{
		MessageBox(L"用户名不存在");
		this->usernameEditControl.SetWindowTextW(L"");
		this->passwordEditControl.SetWindowTextW(L"");
	}
}
#include <stdexcept>

void LoginDialog::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}


void LoginDialog::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类

	//CDialogEx::OnOK();
	this->OnBnClickedButton1();
}
