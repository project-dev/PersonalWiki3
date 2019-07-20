// EventDate.h: CEventDate クラスのインターフェイス
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_EVENTDATE_H__B4AC4B3F_01F7_4D86_B879_C6D6F2801611__INCLUDED_)
#define AFX_EVENTDATE_H__B4AC4B3F_01F7_4D86_B879_C6D6F2801611__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/**
 * @brif イベントデータ チャンクヘッダ
 */
typedef struct tagEVENTDATA{
	char szKey[5];	//文字列
	int nSize;		//データサイズ
}EVENTDATA, *PEVENTDATA;

/**
 * イベントデータ種別列挙型
 */
typedef enum eSCTYPE{
	SC_NORMAL = 0,	//通常データ
	SC_TODO,		//TODO
	SC_FIX_YEAR,	//定期データ(年間)
	SC_FIX_MONTH1,	//定期データ(月間1：日指定)
	SC_FIX_MONTH2,	//定期データ(月間2：第N曜日指定)
	SC_FIX_WEEK,	//定期データ(週)
};

/**
 * @brif 休日時処理列挙型
 */
typedef enum ePLAN_HOLYDAY{
	HO_NONE = 0,	//何もしない
	HO_PREV,		//前の日
	HO_NEXT,		//次の日
};

class CEventDate {
public:
	LPCTSTR GetStateString();
	int GetState();
	void SetState(int nState);
	BOOL IsHolyDay(int nYear, int nMonth, int nDay);
	BOOL ChkShiftPlan(int &nYear, int &nMonth, int &nDay);
	void SetModify(BOOL bModify);
	BOOL IsModify();
	eSCTYPE GetType();
	BOOL IsToDay();
	CEventDate();
	virtual ~CEventDate();
	BOOL Create(LPCTSTR pszName, LPCTSTR pszDetail, COleDateTime *pDate, eSCTYPE eType = SC_NORMAL);

	BOOL LoadEvent(LPCTSTR pszFile, BOOL bToDo = FALSE);
	BOOL SaveEvent(LPCTSTR pszFile, BOOL bToDo = FALSE);
	BOOL DeleteEvent(LPCTSTR pszFile);

	void SetName(LPCTSTR pszName);
	void SetDetail(LPCTSTR pszDetail);
	void SetDate(COleDateTime *pDate);
	void SetPlan(COleDateTime *pStart, COleDateTime *pEnd);
	void SetProgress(COleDateTime *pStart, COleDateTime *pEnd);
	void SetProcess(double dPar);
	void SetMonthDay(int nMonth, int nDay);
	void SetCategory(LPCTSTR pszCategory);
	void SetWeekDay(int nWeekDay);
	void SetSpan(int nSpan);
	void SetWeekDay(int nDays, BOOL bUse);
	void SetHoliday(BOOL bHoliday);
	void SetOption(ePLAN_HOLYDAY eOption);

	LPCTSTR GetName();
	LPCTSTR GetDetail();
	void GetDate(COleDateTime *pDate);
	void GetPlan(COleDateTime *pStart, COleDateTime *pEnd);
	void GetProgress(COleDateTime *pStart, COleDateTime *pEnd);
	void GetMonthDay(int &nMonth, int &nDay);
	LPCTSTR GetCategory();
	double GetProcess();
	int GetWeekDay();
	int GetSpan();
	BOOL GetWeekDay(int nDays);
	BOOL GetHoliday();
	ePLAN_HOLYDAY GetOption();

	void SetEventID(LPCTSTR pszID);
	LPCTSTR GetEventID();
	CEventDate& operator =(CEventDate&);
	BOOL operator !=(CEventDate&);
	BOOL operator ==(CEventDate&);
protected:
	CString			m_strName;			//スケジュールの概要
	CString			m_strDetail;		//スケジュール詳細
	COleDateTime	m_objDate;			//日付
	COleDateTime	m_objPlan[2];		//予定(開始と終了)
	COleDateTime	m_objProgress[2];	//進捗(開始と終了)
	double			m_dProcessPar;		//進捗率
	CString			m_strEventID;		//ID
	eSCTYPE			m_eType;
	int				m_nFixMonth;		//定期データ用
	int				m_nFixDay;			//定期データ用

	int				m_nSpan;			//第n
	int				m_nWeekDays;		//日～月

	BOOL			m_arrWeekDays[7];	//日～月

	BOOL			m_bHolyday;			//休日かどうか
	ePLAN_HOLYDAY	m_ePlanHolyday;		//予定が休日になった場合

	CString			m_strCategory;		//カテゴリ

	int				m_nState;			//ステータス

	BOOL			m_bModify;			//変更有り/無し
};

#endif // !defined(AFX_EVENTDATE_H__B4AC4B3F_01F7_4D86_B879_C6D6F2801611__INCLUDED_)
