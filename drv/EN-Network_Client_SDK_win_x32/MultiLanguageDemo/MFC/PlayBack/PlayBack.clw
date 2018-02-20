; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CPlayRemoteFile
LastTemplate=CPropertyPage
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "PlayBack.h"

ClassCount=8
Class1=CPlayBackApp
Class2=CPlayBackDlg
Class3=CAboutDlg

ResourceCount=5
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Resource3=IDD_PLAYBACK_DIALOG
Resource4=IDD_PAGE_REMOTE
Class4=CPlayRemoteFile
Class5=CPlayLocalFile
Class6=CPlaybackSheet
Class7=CAddDevice
Class8=CPlayTimeFile
Resource5=IDD_PAGE_TIME

[CLS:CPlayBackApp]
Type=0
HeaderFile=PlayBack.h
ImplementationFile=PlayBack.cpp
Filter=N
BaseClass=CWinApp
VirtualFilter=AC
LastObject=CPlayBackApp

[CLS:CPlayBackDlg]
Type=0
HeaderFile=PlayBackDlg.h
ImplementationFile=PlayBackDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=IDC_TREE_CHAN

[CLS:CAboutDlg]
Type=0
HeaderFile=PlayBackDlg.h
ImplementationFile=PlayBackDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_PLAYBACK_DIALOG]
Type=1
Class=CPlayBackDlg
ControlCount=11
Control1=IDC_TAB_PLAYBACK,SysTabControl32,1342178304
Control2=IDC_IPADDRESS_DEV,SysIPAddress32,1342242816
Control3=IDC_EDIT_PORT,edit,1350631552
Control4=IDC_EDIT_USER,edit,1350631552
Control5=IDC_EDIT_PWD,edit,1350631584
Control6=IDC_BUTTON_LOGIN,button,1342242816
Control7=IDC_STATIC,static,1342308352
Control8=IDC_STATIC,static,1342308352
Control9=IDC_STATIC,static,1342308352
Control10=IDC_STATIC,static,1342308352
Control11=IDC_TREE_CHAN,SysTreeView32,1350631459

[DLG:IDD_PAGE_REMOTE]
Type=1
Class=CPlayRemoteFile
ControlCount=30
Control1=IDC_STATIC,static,1342308352
Control2=IDC_COMBO_TYPE,combobox,1344339971
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC,static,1342308352
Control5=IDC_DATE_START,SysDateTimePick32,1342242848
Control6=IDC_DATE_END,SysDateTimePick32,1342242848
Control7=IDC_TIME_START,SysDateTimePick32,1342242857
Control8=IDC_TIME_END,SysDateTimePick32,1342242857
Control9=IDC_FILE_LIST,SysListView32,1350631433
Control10=IDC_STATIC,static,1342308352
Control11=IDC_COMBO_FILE_PROPERTY,combobox,1344339971
Control12=IDC_STATIC_PLAY,static,1342312448
Control13=IDC_BUTTON_SEARCH,button,1342242816
Control14=IDC_BUTTON_UNLOCK,button,1208025088
Control15=IDC_BUTTON_DOWNLOAD,button,1342242816
Control16=IDC_PROGRESS_DOWNLOAD,msctls_progress32,1350565889
Control17=IDC_BUTTON_REMOTE_PLAY,button,1342242880
Control18=IDC_SLIDER_PLAY,msctls_trackbar32,1342242840
Control19=IDC_STATIC_SEARCH,static,1342308352
Control20=IDC_BUTTON_REMOTE_STOP,button,1342242880
Control21=IDC_BUTTON_REMOTE_SLOW,button,1342242880
Control22=IDC_BUTTON_REMOTE_FAST,button,1342242880
Control23=IDC_BUTTON_REMOTE_BACK,button,1342242880
Control24=IDC_BUTTON_REMOTE_STEP,button,1342242880
Control25=IDC_STATIC_FRAME,static,1342308352
Control26=IDC_BUTTON_REMOTE_PIC,button,1342242880
Control27=IDC_BUTTON_REMOTE_SOUND,button,1342242880
Control28=IDC_SLIDER_VOLUME,msctls_trackbar32,1342242840
Control29=IDC_BUTTON_REMOTE_SAVE,button,1342242816
Control30=IDC_BUTTON_REMOTE_STOP_SAVE,button,1342242816

[CLS:CPlayRemoteFile]
Type=0
HeaderFile=PlayRemoteFile.h
ImplementationFile=PlayRemoteFile.cpp
BaseClass=CPropertyPage
Filter=D
LastObject=IDC_FILE_LIST
VirtualFilter=idWC

[CLS:CPlayLocalFile]
Type=0
HeaderFile=PlayLocalFile.h
ImplementationFile=PlayLocalFile.cpp
BaseClass=CPropertyPage
Filter=D
VirtualFilter=idWC
LastObject=IDC_SLIDER_PLAY_LOCAL

[CLS:CPlaybackSheet]
Type=0
HeaderFile=PlaybackSheet.h
ImplementationFile=PlaybackSheet.cpp
BaseClass=CPropertySheet
Filter=W

[CLS:CAddDevice]
Type=0
HeaderFile=AddDevice.h
ImplementationFile=AddDevice.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC

[DLG:IDD_PAGE_TIME]
Type=1
Class=CPlayTimeFile
ControlCount=15
Control1=IDC_STATIC,button,1342177287
Control2=IDC_STATIC,static,1342308352
Control3=IDC_STATIC,static,1342308352
Control4=IDC_DATE_START_TIME,SysDateTimePick32,1342242848
Control5=IDC_DATE_END_TIME,SysDateTimePick32,1342242848
Control6=IDC_TIME_START_TIME,SysDateTimePick32,1342242857
Control7=IDC_TIME_END_TIME,SysDateTimePick32,1342242857
Control8=IDC_STATIC_PLAY_WND_TIME,static,1342312448
Control9=IDC_STATIC,button,1342177287
Control10=IDC_BUTTON_DOWNLOAD,button,1342242816
Control11=IDC_BUTTON_SAVE,button,1342242816
Control12=IDC_BUTTON_PLAY_BYTIME,button,1342242880
Control13=IDC_BUTTON_STOP_BYTIME,button,1342242880
Control14=IDC_BUTTON_FAST_BYTIME,button,1342242880
Control15=IDC_BUTTON_SLOW_BYTIME,button,1342242880

[CLS:CPlayTimeFile]
Type=0
HeaderFile=PlayTimeFile.h
ImplementationFile=PlayTimeFile.cpp
BaseClass=CPropertyPage
Filter=D
LastObject=IDC_BUTTON_DOWNLOAD
VirtualFilter=idWC

