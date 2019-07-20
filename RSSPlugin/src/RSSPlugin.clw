; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CSepBtn
LastTemplate=CButton
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "rssplugin.h"
LastPage=0

ClassCount=5
Class1=CRSSPluginApp
Class2=CRssWnd

ResourceCount=2
Class3=CSetDlg
Resource1=IDD_SET_DLG
Class4=CRSSList
Class5=CSepBtn
Resource2=IDR_RSSMENU

[CLS:CRSSPluginApp]
Type=0
BaseClass=CWinApp
HeaderFile=RSSPlugin.h
ImplementationFile=RSSPlugin.cpp
LastObject=CRSSPluginApp
Filter=N
VirtualFilter=AC

[CLS:CRssWnd]
Type=0
BaseClass=CWnd
HeaderFile=RssWnd.h
ImplementationFile=RssWnd.cpp
LastObject=CRssWnd
Filter=W
VirtualFilter=WC

[DLG:IDD_SET_DLG]
Type=1
Class=CSetDlg
ControlCount=18
Control1=IDC_STATIC,button,1342177287
Control2=IDC_RSSLIST,SysListView32,1350664205
Control3=IDC_STATIC,static,1342308864
Control4=IDC_ED_NAME,edit,1350631552
Control5=IDC_STATIC,static,1342308864
Control6=IDC_ED_URL,edit,1350631552
Control7=IDC_STATIC,static,1342308864
Control8=IDC_ED_ID,edit,1350631552
Control9=IDC_STATIC,static,1342308864
Control10=IDC_ED_PASS,edit,1350631584
Control11=IDC_BTN_ADD,button,1342242816
Control12=IDC_BTN_APPLY,button,1342242816
Control13=IDC_BTN_DEL,button,1342242816
Control14=IDC_CHK_CHECK,button,1342242819
Control15=IDC_ED_SPAN,edit,1350631552
Control16=IDC_STATIC,static,1342308864
Control17=IDOK,button,1342242817
Control18=IDCANCEL,button,1342242816

[CLS:CSetDlg]
Type=0
HeaderFile=SetDlg.h
ImplementationFile=SetDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=IDC_ED_SPAN
VirtualFilter=dWC

[MNU:IDR_RSSMENU]
Type=1
Class=?
Command1=IDM_READRSS
CommandCount=1

[CLS:CRSSList]
Type=0
HeaderFile=RSSList.h
ImplementationFile=RSSList.cpp
BaseClass=CListCtrl
Filter=W
VirtualFilter=FWC

[CLS:CSepBtn]
Type=0
HeaderFile=SepBtn.h
ImplementationFile=SepBtn.cpp
BaseClass=CButton
Filter=W
VirtualFilter=BWC

