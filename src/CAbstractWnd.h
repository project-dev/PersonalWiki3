#if !defined(__ABSTRACTWND__)
#define(__ABSTRACTWND__)
class CAbstractWnd{
public:
	LPCTSTR GetBasePath(){
		return m_strBasePath;
	};
	LPCTSTR GetInifilePath(){
		return m_strIniFilePath;
	}
private:
	static CString m_strBasePath;
	static CString m_strIniFilePath;

};
CString CAbstractWnd::m_strBasePath = "";
CString CAbstractWnd::m_strIniFilePath = "";
#endif