#pragma once



// DisplayView 窗体视图

class DisplayView : public CFormView
{
	DECLARE_DYNCREATE(DisplayView)

protected:
	DisplayView();           // 动态创建所使用的受保护的构造函数
	virtual ~DisplayView();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DisplayView1 };
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
};


