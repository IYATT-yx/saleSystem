// UserDialog.cpp: 实现文件
//

#include "pch.h"
#include "saleSystem.h"
#include "UserDialog.hpp"

#include "StoreManager.hpp"


// UserDialog

IMPLEMENT_DYNCREATE(UserDialog, CFormView)

UserDialog::UserDialog()
	: CFormView(DIALOG_USER)
{

}

UserDialog::~UserDialog()
{
}

void UserDialog::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, positionEditControl);
	DDX_Control(pDX, IDC_EDIT3, usernameEditControl);
	DDX_Control(pDX, IDC_EDIT2, newPasswordEditControl);
	DDX_Control(pDX, IDC_EDIT4, confirmPasswordEditControl);
}

BEGIN_MESSAGE_MAP(UserDialog, CFormView)
	ON_BN_CLICKED(IDOK, &UserDialog::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &UserDialog::OnBnClickedCancel)
END_MESSAGE_MAP()


// UserDialog 诊断

#ifdef _DEBUG
void UserDialog::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void UserDialog::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// UserDialog 消息处理程序

void UserDialog::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: 在此添加专用代码和/或调用基类

	this->positionEditControl.SetWindowTextW(L"销售员");
}

void UserDialog::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码

	if (this->usernameEditControl.GetWindowTextLengthW() == 0)
	{
		MessageBox(L"输入用户名不能为空");
		return;
	}

	if (this->newPasswordEditControl.GetWindowTextLengthW() == 0 || this->confirmPasswordEditControl.GetWindowTextLengthW() == 0)
	{
		MessageBox(L"输入密码不能为空");
		return;
	}

	CString newPassword, confirmPassword;
	this->newPasswordEditControl.GetWindowTextW(newPassword);
	this->confirmPasswordEditControl.GetWindowTextW(confirmPassword);

	if (newPassword != confirmPassword)
	{
		MessageBox(L"输入密码和确定密码不同");
		return;
	}

	CString oldPassword, username, inputUsername;
	StoreManager::readLogin(username, oldPassword);
	this->usernameEditControl.GetWindowTextW(inputUsername);

	if (inputUsername != username)
	{
		MessageBox(L"用户名错误");
		return;
	}

	if (newPassword == oldPassword)
	{
		MessageBox(L"新密码和原密码相同");
		return;
	}

	if (StoreManager::writePassword(inputUsername, newPassword))
	{
		MessageBox(L"修改密码成功");
	}
	else
	{
		MessageBox(L"修改密码失败");
	}
}

void UserDialog::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码

	this->usernameEditControl.SetWindowTextW(L"");
	this->newPasswordEditControl.SetWindowTextW(L"");
	this->confirmPasswordEditControl.SetWindowTextW(L"");
}

