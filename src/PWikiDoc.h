// PWikiDoc.h : CPWikiDoc クラスの宣言およびインターフェイスの定義をします。
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_PWIKIDOC_H__407042E7_81C9_4D26_9416_17EFF4B1673F__INCLUDED_)
#define AFX_PWIKIDOC_H__407042E7_81C9_4D26_9416_17EFF4B1673F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "TodoData.h"
#include "ScDateData.h"
#include "AbstractBaseWnd.h"
#include "FixedData.h"

class CPWikiDoc : public CDocument, CAbstractBaseWnd{
protected: // シリアライズ機能のみから作成します。
	CPWikiDoc();
	DECLARE_DYNCREATE(CPWikiDoc)

// アトリビュート
public:
	CTodoData m_objToDoData;
	CScDateData m_objScDateData;
	CFixedData m_objFixedData;

// オペレーション
public:

//オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CPWikiDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	virtual void OnCloseDocument();
	//}}AFX_VIRTUAL

// インプリメンテーション
public:
	BOOL CreateWikiDir(LPCTSTR pszWikiPage, LPCTSTR pszBasePath, CString &strWikiPage, CString &strWikiDir, CString &strWikiAttDir);
	int GetDayOfWeekNum(int nDay);
	int GetWeek(int nYear, int nMonth, int nDay);
	CEventDate* FindDate(int nYear, int nMonth, int nDay);
	void FindFixedDate(int nYear, int nMonth, int nDay, CString &strDetail, BOOL& bHoliday);
	void FindToDoDate(int nYear, int nMonth, int nDay, CString &strDetail, BOOL bGetDetail = FALSE);
	void FindSpecialDay(int nYear, int nMonth, int nDay, CString &strDetail);
	virtual ~CPWikiDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	CStringArray m_arrCategory;

protected:

// 生成されたメッセージ マップ関数
protected:
	//{{AFX_MSG(CPWikiDoc)
		// メモ - ClassWizard はこの位置にメンバ関数を追加または削除します。
		//        この位置に生成されるコードを編集しないでください。
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_PWIKIDOC_H__407042E7_81C9_4D26_9416_17EFF4B1673F__INCLUDED_)
