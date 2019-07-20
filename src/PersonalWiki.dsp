# Microsoft Developer Studio Project File - Name="PersonalWiki" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** 編集しないでください **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=PersonalWiki - Win32 Debug
!MESSAGE これは有効なﾒｲｸﾌｧｲﾙではありません。 このﾌﾟﾛｼﾞｪｸﾄをﾋﾞﾙﾄﾞするためには NMAKE を使用してください。
!MESSAGE [ﾒｲｸﾌｧｲﾙのｴｸｽﾎﾟｰﾄ] ｺﾏﾝﾄﾞを使用して実行してください
!MESSAGE 
!MESSAGE NMAKE /f "PersonalWiki.mak".
!MESSAGE 
!MESSAGE NMAKE の実行時に構成を指定できます
!MESSAGE ｺﾏﾝﾄﾞ ﾗｲﾝ上でﾏｸﾛの設定を定義します。例:
!MESSAGE 
!MESSAGE NMAKE /f "PersonalWiki.mak" CFG="PersonalWiki - Win32 Debug"
!MESSAGE 
!MESSAGE 選択可能なﾋﾞﾙﾄﾞ ﾓｰﾄﾞ:
!MESSAGE 
!MESSAGE "PersonalWiki - Win32 Release" ("Win32 (x86) Application" 用)
!MESSAGE "PersonalWiki - Win32 Debug" ("Win32 (x86) Application" 用)
!MESSAGE "PersonalWiki - Win32 ReleaseBuild" ("Win32 (x86) Application" 用)
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "PersonalWiki - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\lib\Release"
# PROP Intermediate_Dir "..\lib\Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "..\..\project_dev_lib\release\include\devlib" /I "..\..\project_dev_lib\release\include\devstaticlib" /I "..\PluginLib\include" /I "..\..\project_dev_lib\release\include\devmfc" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FAcs /Fa"..\brow\Release/" /Yu"stdafx.h" /FD /c
# SUBTRACT CPP /Fr
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x411 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x411 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 devlib.lib devstaticlib.lib devmfc.lib Wininet.lib /nologo /subsystem:windows /map:"..\brow\Release/PersonalWiki3.map" /machine:I386 /out:"..\bin\Release/PersonalWiki3.exe" /libpath:"..\..\project_dev_lib\release\lib\release"
# SUBTRACT LINK32 /verbose /incremental:yes /debug /nodefaultlib
# Begin Special Build Tool
SOURCE="$(InputPath)"
PostBuild_Cmds=copy /Y ..\..\project_dev_lib\release\bin\release\devlib.dll ..\bin\release	copy /Y ..\..\project_dev_lib\release\bin\release\devjava.dll ..\bin\release	copy /Y ..\..\project_dev_lib\release\bin\release\devmfc.dll ..\bin\release	..\..\_common\upx.exe -9 ..\bin\release\PersonalWiki3.exe
# End Special Build Tool

!ELSEIF  "$(CFG)" == "PersonalWiki - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\lib\Debug"
# PROP Intermediate_Dir "..\lib\Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "..\..\project_dev_lib\release\include\devlib" /I "..\..\project_dev_lib\release\include\devstaticlib" /I "..\PluginLib\include" /I "..\..\project_dev_lib\release\include\devmfc" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x411 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x411 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 devlib.lib devstaticlib.lib devmfc.lib Wininet.lib /nologo /subsystem:windows /debug /machine:I386 /out:"..\bin\Debug/PersonalWiki3.exe" /pdbtype:sept /libpath:"..\..\project_dev_lib\release\lib\debug"
# Begin Special Build Tool
SOURCE="$(InputPath)"
PostBuild_Cmds=copy /Y ..\..\project_dev_lib\release\bin\debug\devlib.dll ..\bin\debug	copy /Y ..\..\project_dev_lib\release\bin\debug\devjava.dll ..\bin\debug	copy /Y ..\..\project_dev_lib\release\bin\debug\devmfc.dll ..\bin\debug
# End Special Build Tool

!ELSEIF  "$(CFG)" == "PersonalWiki - Win32 ReleaseBuild"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "PersonalWiki___Win32_ReleaseBuild"
# PROP BASE Intermediate_Dir "PersonalWiki___Win32_ReleaseBuild"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\lib\ReleaseBuild"
# PROP Intermediate_Dir "..\lib\ReleaseBuild"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /I "..\..\project_dev_lib\release\include\devlib" /I "..\..\project_dev_lib\release\include\devstaticlib" /I "..\PluginLib\include" /I "..\..\project_dev_lib\release\include\devmfc" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "..\..\project_dev_lib\release\include\devlib" /I "..\..\project_dev_lib\release\include\devstaticlib" /I "..\PluginLib\include" /I "..\..\project_dev_lib\release\include\devmfc" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x411 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x411 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 devlib.lib devstaticlib.lib devmfc.lib /nologo /subsystem:windows /machine:I386 /out:"..\bin\Release/PersonalWiki.exe" /libpath:"..\..\project_dev_lib\release\lib\release"
# ADD LINK32 devlib.lib devstaticlib.lib devmfc.lib /nologo /subsystem:windows /machine:I386 /out:"..\Release/PersonalWiki.exe" /libpath:"..\..\project_dev_lib\release\lib\release"
# Begin Special Build Tool
SOURCE="$(InputPath)"
PostBuild_Cmds=copy /Y ..\..\project_dev_lib\release\bin\release\devlib.dll ..\release	copy /Y ..\..\project_dev_lib\release\bin\release\devjava.dll ..\release	copy /Y ..\..\project_dev_lib\release\bin\release\devmfc.dll ..\release	..\..\_common\upx.exe -9 ..\release\PersonalWiki.exe
# End Special Build Tool

!ENDIF 

# Begin Target

# Name "PersonalWiki - Win32 Release"
# Name "PersonalWiki - Win32 Debug"
# Name "PersonalWiki - Win32 ReleaseBuild"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\AbstractBaseWnd.cpp
# End Source File
# Begin Source File

SOURCE=.\AbstractWikiWnd.cpp
# End Source File
# Begin Source File

SOURCE=.\AnalisysWiki.cpp
# End Source File
# Begin Source File

SOURCE=.\AppSetPage1.cpp
# End Source File
# Begin Source File

SOURCE=.\AppSetPage2.cpp
# End Source File
# Begin Source File

SOURCE=.\AppSetPage3.cpp
# End Source File
# Begin Source File

SOURCE=.\AppSetPage4.cpp
# End Source File
# Begin Source File

SOURCE=.\AppSetPage5.cpp
# End Source File
# Begin Source File

SOURCE=.\AppSetPage6.cpp
# End Source File
# Begin Source File

SOURCE=.\AppSetPage7.cpp
# End Source File
# Begin Source File

SOURCE=.\AppSetPage8.cpp
# End Source File
# Begin Source File

SOURCE=.\AppSetPage9.cpp
# End Source File
# Begin Source File

SOURCE=.\CalenderWnd.cpp
# End Source File
# Begin Source File

SOURCE=.\CalView.cpp
# End Source File
# Begin Source File

SOURCE=.\ChartWnd.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgAppSet.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgDateInp.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgFixData.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgFixDataPage1.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgFixDataPage2.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgFixDataPage3.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgFixDataPage4.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgImpUrlInp.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgInfo.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgInpWikiPage.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgPluginExport.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgPwInp.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgToDay.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgToDoInp.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgWikiInp.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgWikiProp.cpp
# End Source File
# Begin Source File

SOURCE=.\EvDatBase.cpp
# End Source File
# Begin Source File

SOURCE=.\EventDate.cpp
# End Source File
# Begin Source File

SOURCE=.\FindWnd.cpp
# End Source File
# Begin Source File

SOURCE=.\FixedData.cpp
# End Source File
# Begin Source File

SOURCE=.\FixHtmlView.cpp
# End Source File
# Begin Source File

SOURCE=.\InfoTabView.cpp
# End Source File
# Begin Source File

SOURCE=.\InfoView.cpp
# End Source File
# Begin Source File

SOURCE=.\MainFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\MimeType.cpp
# End Source File
# Begin Source File

SOURCE=.\PersonalWiki.cpp
# End Source File
# Begin Source File

SOURCE=.\PersonalWiki.rc
# End Source File
# Begin Source File

SOURCE=.\PreviewHtmlView.cpp
# End Source File
# Begin Source File

SOURCE=.\PWikiDoc.cpp
# End Source File
# Begin Source File

SOURCE=.\PWikiIniFile.cpp
# End Source File
# Begin Source File

SOURCE=.\PWikiPlgList.cpp
# End Source File
# Begin Source File

SOURCE=.\PWikiPlugin.cpp
# End Source File
# Begin Source File

SOURCE=.\PWikiPluginException.cpp
# End Source File
# Begin Source File

SOURCE=.\PWikiView.cpp
# End Source File
# Begin Source File

SOURCE=.\ScDateData.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\TodoData.cpp
# End Source File
# Begin Source File

SOURCE=.\ToDoView.cpp
# End Source File
# Begin Source File

SOURCE=.\WikiEditWnd.cpp
# End Source File
# Begin Source File

SOURCE=.\WikiWnd.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\AbstractBaseWnd.h
# End Source File
# Begin Source File

SOURCE=.\AbstractWikiWnd.h
# End Source File
# Begin Source File

SOURCE=.\AnalisysWiki.h
# End Source File
# Begin Source File

SOURCE=.\AppSetPage1.h
# End Source File
# Begin Source File

SOURCE=.\AppSetPage2.h
# End Source File
# Begin Source File

SOURCE=.\AppSetPage3.h
# End Source File
# Begin Source File

SOURCE=.\AppSetPage4.h
# End Source File
# Begin Source File

SOURCE=.\AppSetPage5.h
# End Source File
# Begin Source File

SOURCE=.\AppSetPage6.h
# End Source File
# Begin Source File

SOURCE=.\AppSetPage7.h
# End Source File
# Begin Source File

SOURCE=.\AppSetPage8.h
# End Source File
# Begin Source File

SOURCE=.\AppSetPage9.h
# End Source File
# Begin Source File

SOURCE=.\CalenderWnd.h
# End Source File
# Begin Source File

SOURCE=.\CalView.h
# End Source File
# Begin Source File

SOURCE=.\ChartWnd.h
# End Source File
# Begin Source File

SOURCE=.\DlgAppSet.h
# End Source File
# Begin Source File

SOURCE=.\DlgDateInp.h
# End Source File
# Begin Source File

SOURCE=.\DlgFixData.h
# End Source File
# Begin Source File

SOURCE=.\DlgFixDataPage1.h
# End Source File
# Begin Source File

SOURCE=.\DlgFixDataPage2.h
# End Source File
# Begin Source File

SOURCE=.\DlgFixDataPage3.h
# End Source File
# Begin Source File

SOURCE=.\DlgFixDataPage4.h
# End Source File
# Begin Source File

SOURCE=.\DlgImpUrlInp.h
# End Source File
# Begin Source File

SOURCE=.\DlgInfo.h
# End Source File
# Begin Source File

SOURCE=.\DlgInpWikiPage.h
# End Source File
# Begin Source File

SOURCE=.\DlgPluginExport.h
# End Source File
# Begin Source File

SOURCE=.\DlgPwInp.h
# End Source File
# Begin Source File

SOURCE=.\DlgToDay.h
# End Source File
# Begin Source File

SOURCE=.\DlgToDoInp.h
# End Source File
# Begin Source File

SOURCE=.\DlgWikiInp.h
# End Source File
# Begin Source File

SOURCE=.\DlgWikiProp.h
# End Source File
# Begin Source File

SOURCE=.\EvDatBase.h
# End Source File
# Begin Source File

SOURCE=.\EventDate.h
# End Source File
# Begin Source File

SOURCE=.\FindWnd.h
# End Source File
# Begin Source File

SOURCE=.\FixedData.h
# End Source File
# Begin Source File

SOURCE=.\FixHtmlView.h
# End Source File
# Begin Source File

SOURCE=.\InfoTabView.h
# End Source File
# Begin Source File

SOURCE=.\InfoView.h
# End Source File
# Begin Source File

SOURCE=.\MainFrm.h
# End Source File
# Begin Source File

SOURCE=.\MimeType.h
# End Source File
# Begin Source File

SOURCE=.\PersonalWiki.h
# End Source File
# Begin Source File

SOURCE=.\PreviewHtmlView.h
# End Source File
# Begin Source File

SOURCE=.\PWikiDoc.h
# End Source File
# Begin Source File

SOURCE=.\PWikiIniFile.h
# End Source File
# Begin Source File

SOURCE=.\PWikiPlgList.h
# End Source File
# Begin Source File

SOURCE=..\Plugin\include\PWikiPlugin.h
# End Source File
# Begin Source File

SOURCE=.\PWikiPlugin.h
# End Source File
# Begin Source File

SOURCE=.\PWikiPluginException.h
# End Source File
# Begin Source File

SOURCE=.\PWikiView.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\ScDateData.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\TodoData.h
# End Source File
# Begin Source File

SOURCE=.\ToDoView.h
# End Source File
# Begin Source File

SOURCE=.\WikiEditWnd.h
# End Source File
# Begin Source File

SOURCE=.\WikiWnd.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\bitmap1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00001.bmp
# End Source File
# Begin Source File

SOURCE=.\res\DlgWikiInp.bmp
# End Source File
# Begin Source File

SOURCE=.\res\DlgWikiInp256.bmp
# End Source File
# Begin Source File

SOURCE=.\res\icon2.ico
# End Source File
# Begin Source File

SOURCE=.\res\MainToolBar.bmp
# End Source File
# Begin Source File

SOURCE=.\res\PersonalWiki.ico
# End Source File
# Begin Source File

SOURCE=.\res\PersonalWiki.rc2
# End Source File
# Begin Source File

SOURCE=.\res\PWikiDoc.ico
# End Source File
# Begin Source File

SOURCE=.\res\ToDoState.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Toolbar.bmp
# End Source File
# Begin Source File

SOURCE=.\res\toolbar1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\WikiMenu.bmp
# End Source File
# Begin Source File

SOURCE=.\res\WikiMenu256.bmp
# End Source File
# Begin Source File

SOURCE=.\res\WikiTree.bmp
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
