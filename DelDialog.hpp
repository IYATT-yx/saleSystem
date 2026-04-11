#pragma once



// DelDialog 窗体视图

class DelDialog : public CFormView
{
	DECLARE_DYNCREATE(DelDialog)

protected:
	DelDialog();           // 动态创建所使用的受保护的构造函数
	virtual ~DelDialog();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = DIALOG_DEL };
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
	CComboBox productComboBoxControl;
	double priceEditValue;
	int numEditValue;
public:
	virtual void OnInitialUpdate();
	afx_msg void OnCbnSelchangeCombo1();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
};


