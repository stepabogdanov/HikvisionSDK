; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CProtectionalarmDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "Protectionalarm.h"

ClassCount=4
Class1=CProtectionalarmApp
Class2=CProtectionalarmDlg
Class3=CAboutDlg

ResourceCount=4
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Class4=CDlgAddDevice
Resource3=IDD_PROTECTIONALARM_DIALOG
Resource4=IDD_ALARM_DIALOG

[CLS:CProtectionalarmApp]
Type=0
HeaderFile=Protectionalarm.h
ImplementationFile=Protectionalarm.cpp
Filter=N

[CLS:CProtectionalarmDlg]
Type=0
HeaderFile=ProtectionalarmDlg.h
ImplementationFile=ProtectionalarmDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=CProtectionalarmDlg

[CLS:CAboutDlg]
Type=0
HeaderFile=ProtectionalarmDlg.h
ImplementationFile=ProtectionalarmDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_PROTECTIONALARM_DIALOG]
Type=1
Class=CProtectionalarmDlg
ControlCount=17
Control1=IDOK_ConnectDevice,button,1342242817
Control2=IDC_STATIC_DeviceName,static,1342308352
Control3=IDC_EDIT_DeviceName,edit,1350631552
Control4=IDC_STATIC_DeviceIp,static,1342308352
Control5=IDC_DeviceIP,SysIPAddress32,1342242816
Control6=IDC_STATIC_Port,static,1342308352
Control7=IDC_EDIT_Port,edit,1350631552
Control8=IDC_STATIC_UserName,static,1342308352
Control9=IDC_STATIC_Password,static,1342308352
Control10=IDC_EDIT_UserName,edit,1350631552
Control11=IDC_EDIT_Password,edit,1350631584
Control12=IDC_STATIC_ConnectGop,button,1342177287
Control13=IDC_LIST_ALARM_INFO,SysListView32,1350567937
Control14=IDC_LIST_DEV,SysListView32,1350631426
Control15=IDDEL_ConnectDevice,button,1342242817
Control16=IDC_CLEAN,button,1342242816
Control17=IDC_BUTTON1,button,1342242816

[CLS:CDlgAddDevice]
Type=0
HeaderFile=DlgAddDevice.h
ImplementationFile=DlgAddDevice.cpp
BaseClass=CDialog
Filter=D
LastObject=IDC_RADIOIPV6
VirtualFilter=dWC

[DLG:IDD_ALARM_DIALOG]
Type=1
Class=?
ControlCount=17
Control1=IDOK_ConnectDevice,button,1342242817
Control2=IDC_STATIC_DeviceName,static,1342308352
Control3=IDC_EDIT_DeviceName,edit,1350631552
Control4=IDC_STATIC_DeviceIp,static,1342308352
Control5=IDC_DeviceIP,SysIPAddress32,1342242816
Control6=IDC_STATIC_Port,static,1342308352
Control7=IDC_EDIT_Port,edit,1350631552
Control8=IDC_STATIC_UserName,static,1342308352
Control9=IDC_STATIC_Password,static,1342308352
Control10=IDC_EDIT_UserName,edit,1350631552
Control11=IDC_EDIT_Password,edit,1350631584
Control12=IDC_STATIC_ConnectGop,button,1342177287
Control13=IDC_LIST_ALARM_INFO,SysListView32,1350567937
Control14=IDC_LIST_DEV,SysListView32,1350631426
Control15=IDDEL_ConnectDevice,button,1342242817
Control16=IDC_CLEAN,button,1342242816
Control17=IDC_BUTTON1,button,1342242816

