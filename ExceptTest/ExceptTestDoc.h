// ExceptTestDoc.h : CExceptTestDoc クラスの宣言およびインターフェイスの定義をします。
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_EXCEPTTESTDOC_H__98DB2075_ED8B_4886_A325_23DD8BA61143__INCLUDED_)
#define AFX_EXCEPTTESTDOC_H__98DB2075_ED8B_4886_A325_23DD8BA61143__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CExceptTestDoc : public CDocument
{
protected: // シリアライズ機能のみから作成します。
	CExceptTestDoc();
	DECLARE_DYNCREATE(CExceptTestDoc)

// アトリビュート
public:

// オペレーション
public:

//オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CExceptTestDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// インプリメンテーション
public:
	virtual ~CExceptTestDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成されたメッセージ マップ関数
protected:
	//{{AFX_MSG(CExceptTestDoc)
		// メモ - ClassWizard はこの位置にメンバ関数を追加または削除します。
		//        この位置に生成されるコードを編集しないでください。
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_EXCEPTTESTDOC_H__98DB2075_ED8B_4886_A325_23DD8BA61143__INCLUDED_)
