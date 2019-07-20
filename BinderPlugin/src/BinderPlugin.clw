; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CBinderWnd
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "binderplugin.h"
LastPage=0

ClassCount=3
Class1=CBinderPluginApp
Class2=CBinderWnd

ResourceCount=5
Resource1=IDD_CONF_DLG
Resource2=IDR_POPUP
Resource3=IDD_INP_BINDER_NAME_DLG
Resource4=IDR_TOOLBAR
Class3=CInpBinderNameDlg
Resource5=IDR_ACCELERATOR1

[CLS:CBinderPluginApp]
Type=0
BaseClass=CWinApp
HeaderFile=BinderPlugin.h
ImplementationFile=BinderPlugin.cpp
LastObject=CBinderPluginApp

[CLS:CBinderWnd]
Type=0
BaseClass=CWnd
HeaderFile=BinderWnd.h
ImplementationFile=BinderWnd.cpp
Filter=W
VirtualFilter=WC
LastObject=IDM_FILEDEL

[TB:IDR_TOOLBAR]
Type=1
Class=?
Command1=IDM_ADDBINDER
Command2=IDM_ADDFILE
Command3=IDM_FILEDEL
CommandCount=3

[MNU:IDR_POPUP]
Type=1
Class=?
Command1=IDM_ADDBINDER
Command2=IDM_ADDFILE
Command3=IDM_FILEDEL
CommandCount=3

[ACL:IDR_ACCELERATOR1]
Type=1
Class=?
Command1=IDM_CLIPCOPY
Command2=IDM_FILEDEL
Command3=IDM_ADDFILE
Command4=IDM_ADDBINDER
CommandCount=4

[DLG:IDD_INP_BINDER_NAME_DLG]
Type=1
Class=CInpBinderNameDlg
ControlCount=4
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_BINDER_NAME,edit,1350631552
Control4=IDC_STATIC,static,1342308864

[DLG:IDD_CONF_DLG]
Type=1
Class=?
ControlCount=4
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_SECURE_HTML,button,1342242819
Control4=IDC_STATIC,static,1342308352

[CLS:CInpBinderNameDlg]
Type=0
HeaderFile=InpBinderNameDlg.h
ImplementationFile=InpBinderNameDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=CInpBinderNameDlg
VirtualFilter=dWC

