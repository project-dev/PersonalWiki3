// AnalisysWiki.h: CAnalisysWiki �N���X�̃C���^�[�t�F�C�X
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ANALISYSWIKI_H__FF8C67E8_E253_4A85_84AB_53A243734C63__INCLUDED_)
#define AFX_ANALISYSWIKI_H__FF8C67E8_E253_4A85_84AB_53A243734C63__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include <AfxTempl.h>
#include "MimeType.h"

/**
 * @brif ��͏��\����
 */
typedef struct tagANAINFO{
	BOOL	bUseRetFormat;				//@brif ���s�������g�p����
	char	pszBasePath[MAX_PATH];		//@brif �f�[�^�̊i�[����Ă���x�[�X�p�X
	char	pszBaseWikiPath[MAX_PATH];	//@brif ��͂���y�[�W�̃p�X
	BOOL	bUseTBLink;					//@brif
	BOOL	bShowAttach;				//@brif �Y�t�t�@�C���ꗗ��\��
	BOOL	bUseShowConvTime;			//@brif �ϊ����Ԃ�\��
	char	pszAppendPath[MAX_PATH];	//@brif Wiki�p�X�ɕt������p�X
}ANAINFO, *PANAINFO;

typedef struct tagMIMETYPE{
	char szExt[8];
	char szType[128];
	BOOL bImg;
}MIMETYPE, *PMIMETYPE;

class CMimeType;

class CAnalisysWiki{
public:

	void SetMimeType(CMimeType *pMime);
	static void AbstractToFullWikiPath(CString &strWikiPath, CString &strBasePath);
	static void FullToAbstractPath(LPCTSTR pszFromPath, LPCTSTR pszToPath, CString& strAbstractPath);
	static void GetAttachFiles(LPCTSTR pszWikiPath, LPCTSTR pszBasePath, CStringArray &arrAttach);
	void GetInlinePlugin(CString &strLine, LPCTSTR pszWikiPathBase, LPCTSTR pszImgPath, BOOL bPlainText);
	void GetOutlinePlugin(CString &strDetail2, CString &strHtml, CStringArray &arrContents, LPCTSTR pszWikiPathBase, LPCTSTR pszImgPath, BOOL bPlainText);
	void AnalisysRef(CString &strHtml, LPCTSTR pszURL, CStringArray *parrPrm, LPCTSTR pszWikiPathBase, LPCTSTR pszImgPath, BOOL bPlainText);
	void GetTableText(CString &strLine, CStringArray &arrTable, BOOL bPlainText);
	void LinkAna(CString &strLine, LPCTSTR pszWikiPathBase, BOOL bPlainText);
	void IncludeAna(CString &strLine, LPCTSTR pszWikiPage, BOOL bPlainText);
	void ContentsAna(CString &strLine, CStringArray &arrContents, BOOL bPlainText);
	void GetLiText(CString &strLiText, CStringArray &arrStockLI, BOOL bPlainText);
	CAnalisysWiki();
	virtual ~CAnalisysWiki();
	void SetAnaSetting(PANAINFO pAnaInfo);

	BOOL Analisys(LPCTSTR pszText, CString &strHtml, LPCTSTR pszWikiPathBase, BOOL bPlainText, BOOL bExport = FALSE, BOOL bInclude = FALSE);
	static void GetHtmlHead(CString &strHtml, LPCTSTR pszCSSPath, LPCTSTR pszTitle);
	void CreateHTML(CString &strHtml, LPCTSTR pszCSSPath, LPCTSTR pszTitle, LPCTSTR pszBody);
	static void CreateHTML2(CString &strHtml, LPCTSTR pszCSSPath, LPCTSTR pszTitle, LPCTSTR pszBody);

	void CheckURLValue(CString &strValue);
	void ReplaceHTMLText(LPCTSTR pszFrom, CString &strEnd);
	static void SplitString(LPCTSTR pszText, LPCTSTR pszSplit, CStringArray &arrResult);

public:

private:
	void GetHtmlHeadLocal(CString &strHtml, LPCTSTR pszCSSPath, LPCTSTR pszTitle);

private:
	ANAINFO m_objAnaInfo;
	CMimeType m_objMime;
	BOOL	m_bExport;
	CString m_strWikiRealPath;

};

#endif // !defined(AFX_ANALISYSWIKI_H__FF8C67E8_E253_4A85_84AB_53A243734C63__INCLUDED_)
