#if !defined(__PWIKI_PLUGIN__)
#define __PWIKI_PLUGIN__

#define _NO_RELEASE_

#define MAX_PLUGINNAME 128
#define MAX_INFO 1024
typedef enum ePLGTYPE{
	eTypeWikiFormat = 0,	//書式拡張
	eTypeTabExtend,			//タブ機能拡張
	eTypeExportExtend,		//エクスポート拡張
	eTypeInfoExtend,		//情報バー拡張
	eTypeEnd = 30,
};

typedef struct tagPWIKIPLUGIN{
	int nPlgVersion[3];				//プラグインバージョン
	char szName[MAX_PLUGINNAME];	//プラグイン名
	char szInfo[MAX_INFO];			//プラグイン情報
	BOOL arrType[eTypeEnd];			//プラグインタイプ
}PWIKIPLUGIN, *PPWIKIPLUGIN;

/**
 * @brif プラグインSDKバージョン取得
 */
static const char* GetPluginSDKVersion();

/**
 * @brif プラグイン情報取得
 */
typedef BOOL (WINAPI *PGetPluginInfoFunc)(PPWIKIPLUGIN pInfo);

/**
 * @brif プラグイン設定ダイアログ表示
 */
typedef BOOL (WINAPI *PShowSetupDlgFunc)();

/**
 * @brif プラグインを利用するかどうかを取得
 */
typedef BOOL (WINAPI *PGetUseFunc)();
/**
 * @brif プラグインを利用するかどうかを設定
 */
typedef void (WINAPI *PSetUseFunc)(BOOL bUse);

/**
 * @brif プラグイン終了関数
 */
typedef BOOL (WINAPI *PExitPluginFunc)();

/////////////////////////////////////
////////// eTypeWikiFormat //////////
/////////////////////////////////////
#if !defined(_NO_RELEASE_)
/**
 * @brif 書式数
 */
typedef int (WINAPI *PGetFormatNumFunc)();

/**
 * @brif 書式取得
 */
typedef BOOL (WINAPI *PGetFormatFunc)(int nIndex, char* pszFormat, BOOL bInline);

/**
 * @brif 解析 pszRetTextがNULLの場合、必要な文字数を返すこと
 */
typedef int (WINAPI *PAnalisysFunc)(char* pszFromText, char* pszRetText);

/**
 * @brif アクション。
 */
typedef BOOL (WINAPI *PCallActionFunc)(char* pszCmd, char* pszParam);
#endif

/////////////////////////////////////
////////// eTypeTabExtend  //////////
/////////////////////////////////////
/**
 * @brif タブに追加するウィンドウのハンドル
 */
typedef HWND (WINAPI *PGetTabWndFunc)(HWND hParent);


/////////////////////////////////////
//////////eTypeExportExtend//////////
/////////////////////////////////////

enum eExportDataType{
	EXP_WIKITEXT = 0,		//Wikiドキュメントを読み込んだ際の文字列
	EXP_WIKIFILE = 1,	//Wikiドキュメントのパス
	EXP_HTMLFILE = 2,	//HTMLのパス
};

typedef eExportDataType (WINAPI *PReqDataTypeFunc)();

/**
 * @brif エクスポート
 * @param pszWikiText eExportDataTypeにより情報が変わる
 */
typedef BOOL (WINAPI *PExportFunc)(char* pszWikiBuff);

/////////////////////////////////////
////////// eTypeInfoExtend //////////
/////////////////////////////////////
#if !defined(_NO_RELEASE_)
/**
 * @brif 情報バーへ表示する文字列の長さ取得
 */
typedef int (WINAPI *PGetInfoTextLenFunc)();

/**
 * @brif 情報バーへ表示する文字列取得
 */
typedef BOOL (WINAPI *PGetInfoTextFunc)(char* pszText, int nLen);

#endif

/////////////////////////////////////
/////////// デバッグ機能  ///////////
/////////////////////////////////////
/**
 * @brif ログ出力フラグ設定
 * @param bLogState ログ出力を行うかどうか
 * @param bAppLogState アプリケーションログを出力するかどうか
 * @param bExceptLogState 例外ログを出力するかどうか
 * @param bFatalLogState 致命的エラーログを出力するかどうか
 */
typedef void (WINAPI *PSetLogFlagFunc)(BOOL bLogState, BOOL bAppLogState, BOOL bExceptLogState, BOOL bFatalLogState);
#endif
