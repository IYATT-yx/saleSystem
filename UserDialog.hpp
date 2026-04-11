#pragma once



// UserDialog 窗体视图

class UserDialog : public CFormView
{
	DECLARE_DYNCREATE(UserDialog)

protected:
	UserDialog();           // 动态创建所使用的受保护的构造函数
	virtual ~UserDialog();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = DIALOG_USER };
#endif
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
private:
	CEdit positionEditControl;
	CEdit usernameEditControl;
	CEdit newPasswordEditControl;
	CEdit confirmPasswordEditControl;
public:
	virtual void OnInitialUpdate();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
};


