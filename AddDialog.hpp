#pragma once



// AddDialog 窗体视图

class AddDialog : public CFormView
{
	DECLARE_DYNCREATE(AddDialog)

protected:
	AddDialog();           // 动态创建所使用的受保护的构造函数
	virtual ~AddDialog();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = DIALOG_ADD };
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
	double stockPriceEditValue;
	int stockNumEditValue;
	CString newProductEditValue;
	double newPriceEditValue;
	int newNumEditValue;
	CComboBox stockProductComboBoxControl;
public:
	virtual void OnInitialUpdate();
	afx_msg void OnCbnSelchangeCombo2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton6();
};


