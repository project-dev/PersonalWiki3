# Microsoft Developer Studio Project File - Name="BinderPlugin" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** 編集しないでください **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=BinderPlugin - Win32 Debug
!MESSAGE これは有効なﾒｲｸﾌｧｲﾙではありません。 このﾌﾟﾛｼﾞｪｸﾄをﾋﾞﾙﾄﾞするためには NMAKE を使用してください。
!MESSAGE [ﾒｲｸﾌｧｲﾙのｴｸｽﾎﾟｰﾄ] ｺﾏﾝﾄﾞを使用して実行してください
!MESSAGE 
!MESSAGE NMAKE /f "BinderPlugin.mak".
!MESSAGE 
!MESSAGE NMAKE の実行時に構成を指定できます
!MESSAGE ｺﾏﾝﾄﾞ ﾗｲﾝ上でﾏｸﾛの設定を定義します。例:
!MESSAGE 
!MESSAGE NMAKE /f "BinderPlugin.mak" CFG="BinderPlugin - Win32 Debug"
!MESSAGE 
!MESSAGE 選択可能なﾋﾞﾙﾄﾞ ﾓｰﾄﾞ:
!MESSAGE 
!MESSAGE "BinderPlugin - Win32 Release" ("Win32 (x86) Dynamic-Link Library" 用)
!MESSAGE "BinderPlugin - Win32 Debug" ("Win32 (x86) Dynamic-Link Library" 用)
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "BinderPlugin - Win32 Release"

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
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "..\..\PluginLib\Include" /I "..\..\..\project_dev_lib\release\include\devlib" /I "..\..\..\project_dev_lib\release\include\devstaticlib" /I "..\..\..\_common\bregexp" /I "..\..\..\project_dev_lib\release\include\devmfc" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_USRDLL" /FAcs /Fa"..\brow\Release/" /Yu"stdafx.h" /FD /c
# SUBTRACT CPP /Fr
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x411 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x411 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 PluginLib.lib devlib.lib devstaticlib.lib BREGEXP.LIB Wininet.lib devmfc.lib /nologo /subsystem:windows /dll /pdb:"..\lib\ReleaseBinderPlugin.pdb" /map:"..\brow\Release/BinderPlugin.map" /machine:I386 /out:"..\..\bin\Release\plugins\BinderPlugin.pwp" /libpath:"..\..\PluginLib\lib\release" /libpath:"..\..\..\project_dev_lib\release\lib\release" /libpath:"..\..\..\_common\bregexp"
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "BinderPlugin - Win32 Debug"

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
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "..\..\PluginLib\Include" /I "..\..\..\project_dev_lib\release\include\devlib" /I "..\..\..\project_dev_lib\release\include\devstaticlib" /I "..\..\..\_common\bregexp" /I "..\..\..\project_dev_lib\release\include\devmfc" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_USRDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x411 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x411 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 PluginLib.lib devlib.lib devstaticlib.lib BREGEXP.LIB Wininet.lib devmfc.lib /nologo /subsystem:windows /dll /debug /machine:I386 /out:"..\..\bin\Debug\plugins\BinderPlugin.pwp" /pdbtype:sept /libpath:"..\..\PluginLib\lib\Debug" /libpath:"..\..\..\project_dev_lib\release\lib\debug" /libpath:"..\..\..\_common\bregexp"

!ENDIF 

# Begin Target

# Name "BinderPlugin - Win32 Release"
# Name "BinderPlugin - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\Binder.cpp
# End Source File
# Begin Source File

SOURCE=.\BinderDropTarget.cpp
# End Source File
# Begin Source File

SOURCE=.\BinderPlugin.cpp
# End Source File
# Begin Source File

SOURCE=.\BinderPlugin.def
# End Source File
# Begin Source File

SOURCE=.\BinderPlugin.rc
# End Source File
# Begin Source File

SOURCE=.\BinderWnd.cpp
# End Source File
# Begin Source File

SOURCE=.\BregExpRap.cpp
# End Source File
# Begin Source File

SOURCE=.\InpBinderNameDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\Binder.h
# End Source File
# Begin Source File

SOURCE=.\BinderDropTarget.h
# End Source File
# Begin Source File

SOURCE=.\BinderPlugin.h
# End Source File
# Begin Source File

SOURCE=.\BinderWnd.h
# End Source File
# Begin Source File

SOURCE=.\BregExpRap.h
# End Source File
# Begin Source File

SOURCE=.\InpBinderNameDlg.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\BinderPlugin.rc2
# End Source File
# Begin Source File

SOURCE=.\res\bitmap1.bmp
# End Source File
# Begin Source File

SOURCE=.\toolbar1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\ToolBar256.bmp
# End Source File
# Begin Source File

SOURCE=.\res\treeicon.bmp
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
