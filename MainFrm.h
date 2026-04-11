
// MainFrm.h: CMainFrame 类的接口
//

#pragma once

// 自定义通知消息
constexpr UINT NM_USER = WM_USER + 100;
constexpr UINT NM_SELL = WM_USER + 101;
constexpr UINT NM_INFO = WM_USER + 102;
constexpr UINT NM_ADD = WM_USER + 103;
constexpr UINT NM_DEL = WM_USER + 104;


class CMainFrame : public CFrameWnd
{
	
protected: // 仅从序列化创建
	CMainFrame() noexcept;
	DECLARE_DYNCREATE(CMainFrame)

// 特性
public:

// 操作
public:

// 重写
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// 实现
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // 控件条嵌入成员
	CStatusBar        m_wndStatusBar;

// 生成的消息映射函数
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	DECLARE_MESSAGE_MAP()

private:
	CSplitterWnd splitter;

	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);

protected:
	afx_msg LRESULT onMyChange(WPARAM wParam, LPARAM lParam);
public:
	afx_msg void OnUser();
	afx_msg void OnSell();
	afx_msg void OnInfo();
	afx_msg void OnAdd();
	afx_msg void OnDel();
};


