#pragma once



// InfoDialog 窗体视图

class InfoDialog : public CFormView
{
	DECLARE_DYNCREATE(InfoDialog)

protected:
	InfoDialog();           // 动态创建所使用的受保护的构造函数
	virtual ~InfoDialog();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = DIALOG_INFO };
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
	CListCtrl infoListControl;
public:
	virtual void OnInitialUpdate();
};


