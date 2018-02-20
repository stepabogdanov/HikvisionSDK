; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CVoiceDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "Voice.h"

ClassCount=5
Class1=CVoiceApp
Class2=CVoiceDlg
Class3=CAboutDlg

ResourceCount=5
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Resource3=IDD_VOICE_DIALOG
Class4=CVoiceTalk
Resource4=IDD_DIALOG_VOICE_TALK
Class5=CTalkMR
Resource5=IDD_DIALOG_TALK_MR

[CLS:CVoiceApp]
Type=0
HeaderFile=Voice.h
ImplementationFile=Voice.cpp
Filter=N
BaseClass=CWinApp
VirtualFilter=AC

[CLS:CVoiceDlg]
Type=0
HeaderFile=VoiceDlg.h
ImplementationFile=VoiceDlg.cpp
Filter=D
LastObject=IDC_BUTTON_LOGIN
BaseClass=CDialog
VirtualFilter=dWC

[CLS:CAboutDlg]
Type=0
HeaderFile=VoiceDlg.h
ImplementationFile=VoiceDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_VOICE_DIALOG]
Type=1
Class=CVoiceDlg
ControlCount=10
Control1=IDC_TAB_VOICE,SysTabControl32,1342178304
Control2=IDC_IPADDRESS_DEV,SysIPAddress32,1342242816
Control3=IDC_EDIT_PORT,edit,1350631552
Control4=IDC_EDIT_USER,edit,1350631552
Control5=IDC_EDIT_PWD,edit,1350631584
Control6=IDC_BUTTON_LOGIN,button,1342242816
Control7=IDC_STATIC,static,1342308352
Control8=IDC_STATIC,static,1342308352
Control9=IDC_STATIC,static,1342308352
Control10=IDC_STATIC,static,1342308352

[DLG:IDD_DIALOG_VOICE_TALK]
Type=1
Class=CVoiceTalk
ControlCount=8
Control1=IDC_STATIC,static,1342308352
Control2=IDC_RADIO_AUDIO1,button,1342308361
Control3=IDC_RADIO_AUDIO2,button,1342177289
Control4=IDC_STATIC,static,1342308352
Control5=IDC_RADIO_DATA_PCM,button,1342308361
Control6=IDC_RADIO_DATA_G722,button,1207959561
Control7=IDC_BUTTON_TALK,button,1342242816
Control8=IDC_BUTTON_RECORD,button,1342242816

[CLS:CVoiceTalk]
Type=0
HeaderFile=VoiceTalk.h
ImplementationFile=VoiceTalk.cpp
BaseClass=CDialog
Filter=D
LastObject=CVoiceTalk
VirtualFilter=dWC

[DLG:IDD_DIALOG_TALK_MR]
Type=1
Class=CTalkMR
ControlCount=2
Control1=IDC_TREE_VOICE_CHAN,SysTreeView32,1350631715
Control2=IDC_BUTTON_TALK_MR,button,1342242816

[CLS:CTalkMR]
Type=0
HeaderFile=TalkMR.h
ImplementationFile=TalkMR.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC

