#if !defined(AFX_DLGPLUGINEXPORT_H__550304F9_4C41_4892_BF58_25482F5D67A9__INCLUDED_)
#define AFX_DLGPLUGINEXPORT_H__550304F9_4C41_4892_BF58_25482F5D67A9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgPluginExport.h : ヘッダー ファイル
//

/////////////////////////////////////////////////////////////////////////////
// CDlgPluginExport ダイアログ
#include "AbstractBaseWnd.h"
class CDlgPluginExport : public CDialog, CAbstractBaseWnd{
// コンストラクション
public:
	CDlgPluginExport(CWnd* pParent = NULL);   // 標準のコンストラクタ

// ダイアログ データ
	//{{AFX_DATA(CDlgPluginExport)
	enum { IDD = IDD_DLG_PLUGIN_EXPORT };
	CComboBox	m_objExpCmb;
	CString	m_strWikiPath;
	//}}AFX_DATA

	CStringArray m_arrPluginName;
	CString m_strSelPlugin;

// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CDlgPluginExport)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:

	// 生成されたメッセージ マップ関数
	//{{AFX_MSG(CDlgPluginExport)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_DLGPLUGINEXPORT_H__550304F9_4C41_4892_BF58_25482F5D67A9__INCLUDED_)
