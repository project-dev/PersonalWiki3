#if !defined(__PWIKI_PLUGIN__)
#define __PWIKI_PLUGIN__

#define _NO_RELEASE_

#define MAX_PLUGINNAME 128
#define MAX_INFO 1024
typedef enum ePLGTYPE{
	eTypeWikiFormat = 0,	//�����g��
	eTypeTabExtend,			//�^�u�@�\�g��
	eTypeExportExtend,		//�G�N�X�|�[�g�g��
	eTypeInfoExtend,		//���o�[�g��
	eTypeEnd = 30,
};

typedef struct tagPWIKIPLUGIN{
	int nPlgVersion[3];				//�v���O�C���o�[�W����
	char szName[MAX_PLUGINNAME];	//�v���O�C����
	char szInfo[MAX_INFO];			//�v���O�C�����
	BOOL arrType[eTypeEnd];			//�v���O�C���^�C�v
}PWIKIPLUGIN, *PPWIKIPLUGIN;

/**
 * @brif �v���O�C��SDK�o�[�W�����擾
 */
static const char* GetPluginSDKVersion();

/**
 * @brif �v���O�C�����擾
 */
typedef BOOL (WINAPI *PGetPluginInfoFunc)(PPWIKIPLUGIN pInfo);

/**
 * @brif �v���O�C���ݒ�_�C�A���O�\��
 */
typedef BOOL (WINAPI *PShowSetupDlgFunc)();

/**
 * @brif �v���O�C���𗘗p���邩�ǂ������擾
 */
typedef BOOL (WINAPI *PGetUseFunc)();
/**
 * @brif �v���O�C���𗘗p���邩�ǂ�����ݒ�
 */
typedef void (WINAPI *PSetUseFunc)(BOOL bUse);

/**
 * @brif �v���O�C���I���֐�
 */
typedef BOOL (WINAPI *PExitPluginFunc)();

/////////////////////////////////////
////////// eTypeWikiFormat //////////
/////////////////////////////////////
#if !defined(_NO_RELEASE_)
/**
 * @brif ������
 */
typedef int (WINAPI *PGetFormatNumFunc)();

/**
 * @brif �����擾
 */
typedef BOOL (WINAPI *PGetFormatFunc)(int nIndex, char* pszFormat, BOOL bInline);

/**
 * @brif ��� pszRetText��NULL�̏ꍇ�A�K�v�ȕ�������Ԃ�����
 */
typedef int (WINAPI *PAnalisysFunc)(char* pszFromText, char* pszRetText);

/**
 * @brif �A�N�V�����B
 */
typedef BOOL (WINAPI *PCallActionFunc)(char* pszCmd, char* pszParam);
#endif

/////////////////////////////////////
////////// eTypeTabExtend  //////////
/////////////////////////////////////
/**
 * @brif �^�u�ɒǉ�����E�B���h�E�̃n���h��
 */
typedef HWND (WINAPI *PGetTabWndFunc)(HWND hParent);


/////////////////////////////////////
//////////eTypeExportExtend//////////
/////////////////////////////////////

enum eExportDataType{
	EXP_WIKITEXT = 0,		//Wiki�h�L�������g��ǂݍ��񂾍ۂ̕�����
	EXP_WIKIFILE = 1,	//Wiki�h�L�������g�̃p�X
	EXP_HTMLFILE = 2,	//HTML�̃p�X
};

typedef eExportDataType (WINAPI *PReqDataTypeFunc)();

/**
 * @brif �G�N�X�|�[�g
 * @param pszWikiText eExportDataType�ɂ���񂪕ς��
 */
typedef BOOL (WINAPI *PExportFunc)(char* pszWikiBuff);

/////////////////////////////////////
////////// eTypeInfoExtend //////////
/////////////////////////////////////
#if !defined(_NO_RELEASE_)
/**
 * @brif ���o�[�֕\�����镶����̒����擾
 */
typedef int (WINAPI *PGetInfoTextLenFunc)();

/**
 * @brif ���o�[�֕\�����镶����擾
 */
typedef BOOL (WINAPI *PGetInfoTextFunc)(char* pszText, int nLen);

#endif

/////////////////////////////////////
/////////// �f�o�b�O�@�\  ///////////
/////////////////////////////////////
/**
 * @brif ���O�o�̓t���O�ݒ�
 * @param bLogState ���O�o�͂��s�����ǂ���
 * @param bAppLogState �A�v���P�[�V�������O���o�͂��邩�ǂ���
 * @param bExceptLogState ��O���O���o�͂��邩�ǂ���
 * @param bFatalLogState �v���I�G���[���O���o�͂��邩�ǂ���
 */
typedef void (WINAPI *PSetLogFlagFunc)(BOOL bLogState, BOOL bAppLogState, BOOL bExceptLogState, BOOL bFatalLogState);
#endif
