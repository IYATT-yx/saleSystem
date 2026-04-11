
// saleSystemDoc.cpp: CsaleSystemDoc 类的实现
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "saleSystem.h"
#endif

#include "saleSystemDoc.h"

#include <propkey.h>

#include "StoreManager.hpp"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CsaleSystemDoc

IMPLEMENT_DYNCREATE(CsaleSystemDoc, CDocument)

BEGIN_MESSAGE_MAP(CsaleSystemDoc, CDocument)
END_MESSAGE_MAP()


// CsaleSystemDoc 构造/析构

CsaleSystemDoc::CsaleSystemDoc() noexcept
{
	// TODO: 在此添加一次性构造代码

}

CsaleSystemDoc::~CsaleSystemDoc()
{
}

BOOL CsaleSystemDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 在此添加重新初始化代码
	// (SDI 文档将重用该文档)
	CString projectName;
	projectName.LoadStringW(ID_STRING_PROJECTNAME); // 导入字符串资源
	SetTitle(projectName); // 设置窗口标题

	//CString path = L"saleSystem.sqlite3";
	//StoreManager::connect(path);
	//CString name, pw;
	//name = "admin";
	//pw = "abcder";
	//StoreManager::writePassword(name, pw);
	//pw = "";
	//StoreManager::readLogin(name, pw);
	//name = name + " " + pw;
	//AfxMessageBox(name.GetString(), MB_OK | MB_ICONINFORMATION);

	return TRUE;
}




// CsaleSystemDoc 序列化

void CsaleSystemDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 在此添加存储代码
	}
	else
	{
		// TODO: 在此添加加载代码
	}
}

#ifdef SHARED_HANDLERS

// 缩略图的支持
void CsaleSystemDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// 修改此代码以绘制文档数据
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// 搜索处理程序的支持
void CsaleSystemDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// 从文档数据设置搜索内容。
	// 内容部分应由“;”分隔

	// 例如:     strSearchContent = _T("point;rectangle;circle;ole object;")；
	SetSearchContent(strSearchContent);
}

void CsaleSystemDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = nullptr;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != nullptr)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CsaleSystemDoc 诊断

#ifdef _DEBUG
void CsaleSystemDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CsaleSystemDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CsaleSystemDoc 命令
