// EventDate.h: CEventDate �N���X�̃C���^�[�t�F�C�X
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_EVENTDATE_H__B4AC4B3F_01F7_4D86_B879_C6D6F2801611__INCLUDED_)
#define AFX_EVENTDATE_H__B4AC4B3F_01F7_4D86_B879_C6D6F2801611__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/**
 * @brif �C�x���g�f�[�^ �`�����N�w�b�_
 */
typedef struct tagEVENTDATA{
	char szKey[5];	//������
	int nSize;		//�f�[�^�T�C�Y
}EVENTDATA, *PEVENTDATA;

/**
 * �C�x���g�f�[�^��ʗ񋓌^
 */
typedef enum eSCTYPE{
	SC_NORMAL = 0,	//�ʏ�f�[�^
	SC_TODO,		//TODO
	SC_FIX_YEAR,	//����f�[�^(�N��)
	SC_FIX_MONTH1,	//����f�[�^(����1�F���w��)
	SC_FIX_MONTH2,	//����f�[�^(����2�F��N�j���w��)
	SC_FIX_WEEK,	//����f�[�^(�T)
};

/**
 * @brif �x���������񋓌^
 */
typedef enum ePLAN_HOLYDAY{
	HO_NONE = 0,	//�������Ȃ�
	HO_PREV,		//�O�̓�
	HO_NEXT,		//���̓�
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
	CString			m_strName;			//�X�P�W���[���̊T�v
	CString			m_strDetail;		//�X�P�W���[���ڍ�
	COleDateTime	m_objDate;			//���t
	COleDateTime	m_objPlan[2];		//�\��(�J�n�ƏI��)
	COleDateTime	m_objProgress[2];	//�i��(�J�n�ƏI��)
	double			m_dProcessPar;		//�i����
	CString			m_strEventID;		//ID
	eSCTYPE			m_eType;
	int				m_nFixMonth;		//����f�[�^�p
	int				m_nFixDay;			//����f�[�^�p

	int				m_nSpan;			//��n
	int				m_nWeekDays;		//���`��

	BOOL			m_arrWeekDays[7];	//���`��

	BOOL			m_bHolyday;			//�x�����ǂ���
	ePLAN_HOLYDAY	m_ePlanHolyday;		//�\�肪�x���ɂȂ����ꍇ

	CString			m_strCategory;		//�J�e�S��

	int				m_nState;			//�X�e�[�^�X

	BOOL			m_bModify;			//�ύX�L��/����
};

#endif // !defined(AFX_EVENTDATE_H__B4AC4B3F_01F7_4D86_B879_C6D6F2801611__INCLUDED_)
