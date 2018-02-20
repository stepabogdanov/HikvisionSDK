// ClientDemo.h : main header file for the CLIENTDEMO application
//
/**********************************************************
FileName:    ClientDemo.h
Description: this function will export global structs, defines, variables, and functions that will be used, most of documents should include this head file
Date:        2008/03/27
Note: 		<golbal>struct,define refer to GeneralDef.h, variables and functions refer to ClientDemo.cpp   
Modification History:      
    <version> <time>         <desc>
    <1.0    > <2008/03/27>       <created>
***********************************************************/

#if !defined(AFX_CLIENTDEMO_H__BFFEA4FD_9DA7_4869_B509_9D4ED18FA5F1__INCLUDED_)
#define AFX_CLIENTDEMO_H__BFFEA4FD_9DA7_4869_B509_9D4ED18FA5F1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

//include general struct and Macro;then only need to include ClientDemo.h at start of other files;

#include "GeneralDef.h"
#include "ClientDemoDlg.h"
#include "DlgOutput.h"
#include "DlgRemoteCfg.h"
#include "DlgOutputCtrl.h"
#include "gdiplus/GdiPlus.h"
#include "DlgSensorCfg.h"

//provide global variables to other dlg classes, using 'extern' to avoid redefinition
extern LOCAL_FACE_PICTURE_INFO g_struFacePic[MAX_HUMAN_PICTURE_NUM];
extern LOCAL_FACE_MODEL_INFO g_struFaceModel[MAX_HUMAN_PICTURE_NUM];
extern LOCAL_SENSOR_ADD_PREVIEW g_struSensorAddPreview[MAX_ALARMHOST_ALARMIN_NUM];
extern STRU_DEVICE_INFO g_struDeviceInfo[MAX_DEVICES];
extern LOCAL_PARAM g_struLocalParam;
extern BOOL g_bCapPic[MAX_OUTPUTS];
extern BOOL g_bLocalCapPic;
extern BOOL g_bInSide;
extern BOOL g_bStandardCB;

//2009-7-22
extern DWORD g_dwStreamTransType;
//2009-7-22 end

extern CDlgOutput g_dlgOutput[MAX_OUTPUTS];
extern char g_sSecretKey[17];
extern HBRUSH	g_hPlayHardBgBrush;//Brush of preview window background, different color in hardware decode from software decode 
extern HBRUSH	g_hPlaySoftBgBrush;//Brush of preview window background, different color in hardware decode from software decode 
extern BOOL g_bShareSound;

//all play parameters, select g_struLocalParam.bCycle to turn to next page automatically in circulation by order,not by schedule
extern PLAY_INFO g_struPlayAllInfo[MAX_PREVIEWS];
extern BOOL g_bPlayAllDevice;			//check if all the devices are playing
extern WORD g_nSurveillanceTotalNum;	//surveillance points for preview(camera number)
extern int g_iNextSurveillanceIndex;//the  serial NO. of last surveillance point in all play or circulative play
extern int g_pCycleTimer;			//the index of cycle timer

extern int g_nNetDelay;
extern char g_szWorkDir[MAX_PATH];
extern BOOL g_bCardInit;

extern CClientDemoDlg *g_pMainDlg;
extern CDlgSensorCfg *g_pDlgSensor;

extern CRect g_rcWindow;				//area of entire dialog
extern DWORD g_dwOldDeviceNum;	//display card num
extern int	g_iCurScreenWidth;    //width of current screen
extern int	g_iCurScreenHeight;   //height of current screen

extern LONG	g_lVoiceHandle;	//handle of voice talk

extern BOOL g_bMustReboot;
extern int g_bExitDemo;

extern void g_ReadDeviceConfig();
extern void g_SaveDeviceConfig();
extern void WriteLocalConfig();
extern void ReadLocalConfig();
extern void GetCurrentPath(char *path);
extern DWORD CStringTodwIP(CString strIP);
extern void g_CreateLocalDir();
extern CString IPToStr(DWORD dwIP);
extern BOOL CheckIPStr(CString ip);
extern void g_CreateAlarmOutTree(CTreeCtrl &m_treeAlarmOut, int iDeviceIndex, BOOL *bAlarmOut);
extern void g_StringLanType(char *szDstLan, char *szLanCn, char *szLanEn);
extern char *gg_StringLanType(char *szLanCn, char *szLanEn, const char* format, ...);
NET_DVR_API BOOL __stdcall NET_DVR_RealPlayPause(LONG lRealHandle);
NET_DVR_API BOOL __stdcall NET_DVR_RealPlayRestart(LONG lRealHandle, HWND hPlayWnd);
extern void g_ReadLocalReadSensorAdd();
extern void g_SaveLocalReadSensorAdd();

//Is ipv6?
BOOL g_ValidIPv6(BYTE *ip);

//Get Osd time macro
#define GET_YEAR(_time_)      (((_time_)>>26) + 2000) 
#define GET_MONTH(_time_)     (((_time_)>>22) & 15)
#define GET_DAY(_time_)       (((_time_)>>17) & 31)
#define GET_HOUR(_time_)      (((_time_)>>12) & 31) 
#define GET_MINUTE(_time_)    (((_time_)>>6)  & 63)
#define GET_SECOND(_time_)    (((_time_)>>0)  & 63)
/////////////////////////////////////////////////////////////////////////////
// CClientDemoApp:
// See ClientDemo.cpp for the implementation of this class
//
#define MINOR_FONT      0
#define NORMAL_FONT     1
#define MAJOR_FONT      2

typedef enum _REMOTE_FILE_TYPE_
{
    FILE_TIMING = 0, //��ʱ¼��
	FILE_MOTION_DETECT = 1, //�ƶ����¼��
	FILE_ALARMIN = 2, //��������¼��
	FILE_MOTION_OR_ALARMIN = 3, //����|�ƶ����
	FILE_MOTION_AND_ALARMIN = 4, //����&�ƶ����
	FILE_COMMAND = 5, //�����¼��
	FILE_MANUAL = 6, //�ֶ�¼��
	FILE_VCA = 7, //����¼��
	FILE_PIR_ALARM = 10, //PIR����¼��
	FILE_WIRELESS_ALARM = 11, //���߱���¼��
	FILE_CALLHELP_ALARM = 12, //���ȱ���
	FILE_PIR_WIRELESS_CALLHELP = 13,  //�ƶ�|��������|PIR|���߱���|���ȱ���
	FILE_INTELLIGENT_TRANSPORT = 14, //���ܽ�ͨ�¼�����
	FILE_ALL = 0xff //ȫ��
}REMOTE_FILE_TYPE;

typedef enum _REMOTE_FILE_CARD_TYPE_
{
    FILE_CARD_TIMING = 0, //��ʱ¼��
	FILE_CARD_MOTION_DETECT = 1, //�ƶ����¼��
	FILE_CARD_CLOSETO = 2, //�ӽ�����¼��
	FILE_CARD_BANKNOTE = 3, //��������¼��
	FILE_CARD_FEEDING = 4, //��������¼��
	FILE_CARD_COMMAND = 5, //�����¼��
	FILE_CARD_MANUAL = 6, //�ֶ�¼��
	FILE_CARD_VIBRATION = 7, //�𶯱���¼��
	FILE_CARD_ENVIRON = 8, //��������¼��
	FILE_CARD_VCA = 9, //����¼��
	FILE_CARD_PIR_ALARM = 10, //PIR����¼��
	FILE_CARD_WIRELESS_ALARM = 11, //���߱���¼��
	FILE_CARD_CALLHELP_ALARM = 12, //���ȱ���
	FILE_CARD_PIR_WIRELESS_CALLHELP = 13,  //�ƶ�|��������|PIR|���߱���|���ȱ���
	FILE_CARD_INTELLIGENT_TRANSPORT = 14, //���ܽ�ͨ�¼�����
	FILE_CARD_ALL = 0xff //ȫ��
}REMOTE_FILE_CARD_TYPE;

class CClientDemoApp : public CWinApp
{
public:
	CClientDemoApp();

    ULONG_PTR m_gdiplusToken;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CClientDemoApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CClientDemoApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CLIENTDEMO_H__BFFEA4FD_9DA7_4869_B509_9D4ED18FA5F1__INCLUDED_)
