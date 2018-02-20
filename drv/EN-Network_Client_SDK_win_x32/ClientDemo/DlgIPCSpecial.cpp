// DlgIPCSpecial.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgIPCSpecial.h"
#include "DlgIPAddrFilterCfg.h"
#include "DlgUploadLogo.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgIPCSpecial dialog

CDlgIPCSpecial::CDlgIPCSpecial(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgIPCSpecial::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgIPCSpecial)
	m_dwDeadPixelX = 0;
	m_dwDeadPixelY = 0;
	m_dwDelayTime = 0;
	m_byWirelessIndex = 0;
	m_bChkMonitorAlarm = FALSE;
	m_bChkAudioAlarm = FALSE;
	m_bChkReportCenter = FALSE;
	m_bChkInvokeAlarmOut = FALSE;
	m_bChkInvokeJpegCapture = FALSE;
	m_bChkPicFtp = FALSE;
	m_bChkHanleAlarm = FALSE;
	m_bChkRecordEn = FALSE;
	m_csAlarmName = _T("");
	m_bChkWirelessLight = FALSE;
	m_bChkWpsEn = FALSE;
	m_csAPPin = _T("");
	m_csDevPin = _T("");
	m_csWpsEssid = _T("");
	m_dwPTZFishEyeChannelNum = 0;
	m_dwFEChannelNum = 0;
	m_dwCruiseChannelNum = 0;
	m_iPresetNum = 0;
	m_iPtzCruiseNum = 0;
	m_iPresetGroupNum = 0;
	m_iPreCruiseGroupNum = 0;
	m_iPresetChannel = 0;
	m_iPresetGetGroupNum = 0;
	m_iPreCruiseChannel = 0;
	m_iPreGetCruiseGroupNum = 0;
	m_byWirelessID = 0;
	//}}AFX_DATA_INIT
	m_lServerID = -1;
    m_iDevIndex = -1;
	m_lChannel = -1;
	m_lPlayHandle = -1;
	m_iPtzPresetNum = 0;
	dwChoosePtzindexNum = 0;
	memset(&m_rcWnd, 0, sizeof(m_rcWnd));
	memset(&m_bAlarmOut[0], 0, sizeof(BOOL)*MAX_ALARMOUT_V30);
	memset(&m_struAuxAlarm, 0, sizeof(m_struAuxAlarm));
	memset(&m_struPoint,0,sizeof(m_struPoint));
}


void CDlgIPCSpecial::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgIPCSpecial)
	DDX_Control(pDX, IDC_COMBO_MOTION_TRACK_GET, m_comboMotionTrackGet);
	DDX_Control(pDX, IDC_COMBO_MOTION_TRACK_SET, m_comboMotionTrackSet);
	DDX_Control(pDX, IDC_LIST_PRECRUISE_INFO, m_listGetPreCruiseiInfo);
	DDX_Control(pDX, IDC_LIST_PRESET_INFO2, m_listGetPresetInfo);
	DDX_Control(pDX, IDC_COMBO_CURISE_PRESET, m_comboCurisePreset);
	DDX_Control(pDX, IDC_COMBO_CRUISE_TIME2, m_comboCuriseTime);
	DDX_Control(pDX, IDC_COMBO_CRUISE_SPEED2, m_comboCruiseSpeed);
	DDX_Control(pDX, IDC_COMBO_CRUISE_POINT, m_comboCruisePoint);
	DDX_Control(pDX, IDC_COMBO_CRUISE_ROUTE, m_comboCruiseRoute);
	DDX_Control(pDX, IDC_COMBO_FE_PRESET_NUM, m_comboPresetNum);
	DDX_Control(pDX, IDC_COMBO_FISH_EYE_START_STOP, m_comboFishEyeStartStop);
	DDX_Control(pDX, IDC_COMBO_FISH_EYE_SPEED_CONTROL, m_comboFishEyeSpeedControl);
	DDX_Control(pDX, IDC_COMBO_FISH_EYE_MOUNT_TYPE, m_comboFishEyeMountType);
	DDX_Control(pDX, IDC_COMBO_FISH_EYE_DISPLAY_MODE, m_comboFishEyeDisplayMode);
	DDX_Control(pDX, IDC_COMBO_FISH_EYE_CONNECT_MODE, m_comboFishEyeConnectMode);
	DDX_Control(pDX, IDC_COMBO_WPS_CONNECT_TYPE, m_comboWpsConType);
	DDX_Control(pDX, IDC_COMBO_WIRELESS_ALARM_ID, m_comboWirelessId);
	DDX_Control(pDX, IDC_COMBO_AUXALARM_TYPE, m_comboAuxAlarmType);
	DDX_Control(pDX, IDC_COMBO_AUX_ALARM_ID, m_comboAuxAlarmId);
	DDX_Control(pDX, IDC_TREE_ALARM_OUT, m_treeAlarmOut);
	DDX_Control(pDX, IDC_COMBO_COMMAND, m_comboCmd);
	DDX_Text(pDX, IDC_EDIT_DEADPIXEL_X, m_dwDeadPixelX);
	DDX_Text(pDX, IDC_EDIT_DEADPIXEL_Y, m_dwDeadPixelY);
	DDX_Text(pDX, IDC_EDIT_DELAY_TIME, m_dwDelayTime);
	DDX_Text(pDX, IDC_EDIT_WIRELESS_INDEX, m_byWirelessIndex);
	DDX_Check(pDX, IDC_CHK_MONITOR_ALARM, m_bChkMonitorAlarm);
	DDX_Check(pDX, IDC_CHK_AUDIO_ALARM, m_bChkAudioAlarm);
	DDX_Check(pDX, IDC_CHK_REPORT_CENTER, m_bChkReportCenter);
	DDX_Check(pDX, IDC_CHK_INVOKE_ALARM_OUT, m_bChkInvokeAlarmOut);
	DDX_Check(pDX, IDC_CHK_INVOKE_JPEG_CAPTURE, m_bChkInvokeJpegCapture);
	DDX_Check(pDX, IDC_CHK_PIC_FTP, m_bChkPicFtp);
	DDX_Check(pDX, IDC_CHK_HANLE_ALARM, m_bChkHanleAlarm);
	DDX_Check(pDX, IDC_CHK_RECORD_EN, m_bChkRecordEn);
	DDX_Text(pDX, IDC_EDIT_ALARM_NAME, m_csAlarmName);
	DDX_Check(pDX, IDC_CHK_WIRELESS_LIGHT, m_bChkWirelessLight);
	DDX_Check(pDX, IDC_CHK_WPS_EN, m_bChkWpsEn);
	DDX_Text(pDX, IDC_EDIT_AP_PIN, m_csAPPin);
	DDX_Text(pDX, IDC_EDIT_DEV_PIN, m_csDevPin);
	DDX_Text(pDX, IDC_EDIT_WPS_ESSID, m_csWpsEssid);
	DDX_Text(pDX, IDC_EDIT_PTZ_FISH_Eye_CHANNEL_NUM, m_dwPTZFishEyeChannelNum);
	DDX_Text(pDX, IDC_EDIT_PRESET_NUM, m_iPresetNum);
	DDX_Text(pDX, IDC_EDIT_PTZCRUISE_NUM, m_iPtzCruiseNum);
	DDX_Text(pDX, IDC_EDIT_PRESET_GROUPNUM, m_iPresetGroupNum);
	DDX_Text(pDX, IDC_EDIT_PRECRUISE_GROUPNUM, m_iPreCruiseGroupNum);
	DDX_Text(pDX, IDC_EDIT_PRESET_CHANNEL, m_iPresetChannel);
	DDX_Text(pDX, IDC_EDIT_PREGET_GROUPNUM, m_iPresetGetGroupNum);
	DDX_Text(pDX, IDC_EDIT_PRCRUISE_CHANNEL, m_iPreCruiseChannel);
	DDX_Text(pDX, IDC_EDIT_PRECRUISEGET_GROUPNUM, m_iPreGetCruiseGroupNum);
	DDX_Text(pDX, IDC_EDIT_WIRELESS_ID, m_byWirelessID);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgIPCSpecial, CDialog)
	//{{AFX_MSG_MAP(CDlgIPCSpecial)
	ON_BN_CLICKED(IDC_BTN_SHUTTER_COMP, OnBtnShutterComp)
	ON_BN_CLICKED(IDC_BTN_SET, OnBtnSet)
	ON_BN_CLICKED(IDC_BTN_IPC_ONEPUSH_FOCUS, OnBtnIpcOnepushFocus)
	ON_BN_CLICKED(IDC_BTN_IPC_RESET_LENS, OnBtnIpcResetLens)
	ON_BN_CLICKED(IDC_BTN_REMOTECONTROL_ALARM, OnBtnRemotecontrolAlarm)
	ON_BN_CLICKED(IDC_BTN_REMOTECONTROL_DISALARM, OnBtnRemotecontrolDisalarm)
	ON_BN_CLICKED(IDC_BTN_REMOTECONTROL_STUDY, OnBtnRemotecontrolStudy)
	ON_BN_CLICKED(IDC_BTN_WIRELESS_STUDY, OnBtnWirelessStudy)
	ON_BN_CLICKED(IDC_BTN_GET_AUXALARM, OnBtnGetAuxalarm)
	ON_BN_CLICKED(IDC_BTN_SET_AUXALARM, OnBtnSetAuxalarm)
	ON_NOTIFY(NM_CLICK, IDC_TREE_ALARM_OUT, OnClickTreeAlarmOut)
	ON_BN_CLICKED(IDC_BTN_SAVE_AUX_ALARM, OnBtnSaveAuxAlarm)
	ON_CBN_SELCHANGE(IDC_COMBO_AUX_ALARM_ID, OnSelchangeComboAuxAlarmId)
	ON_CBN_SELCHANGE(IDC_COMBO_AUXALARM_TYPE, OnSelchangeComboAuxalarmType)
	ON_CBN_SELCHANGE(IDC_COMBO_WIRELESS_ALARM_ID, OnSelchangeComboWirelessAlarmId)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_CHK_WPS_EN, OnChkWpsEn)
	ON_BN_CLICKED(IDC_BTN_REFRESH, OnBtnRefresh)
	ON_BN_CLICKED(IDC_BTN_WPS_CONNECT, OnBtnWpsConnect)
	ON_BN_CLICKED(IDC_BTN_UPDATE_PIN, OnBtnUpdatePin)
	ON_BN_CLICKED(IDC_BTN_GET_DEV_PIN, OnBtnGetDevPin)
	ON_BN_CLICKED(IDC_BTN_FISH_EYE_SET, OnBtnFishEyeSet)
	ON_BN_CLICKED(IDC_BTN_FISH_EYE_GET, OnBtnFishEyeGet)
	ON_BN_CLICKED(IDC_BTN_FE_PTZ_SET, OnBtnFePtzSet)
	ON_BN_CLICKED(IDC_BTN_PTZ_UP, OnBtnPtzUp)
	ON_BN_CLICKED(IDC_BTN_PTZ_LEFT, OnBtnPtzLeft)
	ON_BN_CLICKED(IDC_BTN_PTZ_RIGHT, OnBtnPtzRight)
	ON_BN_CLICKED(IDC_BTN_PTZ_DOWN, OnBtnPtzDown)
	ON_BN_CLICKED(IDC_BTN_PTZ_BIG, OnBtnPtzBig)
	ON_BN_CLICKED(IDC_BTN_PTZ_NARROW, OnBtnPtzNarrow)
	ON_BN_CLICKED(IDC_BTN_PTZ_AUTO, OnBtnPtzAuto)
	ON_BN_CLICKED(IDC_BTN_PTZ_CIRCLE, OnBtnPtzCircle)
	ON_BN_CLICKED(IDC_BTN_FE_PTZ_CLEAN, OnBtnFePtzClean)
	ON_BN_CLICKED(IDC_BTN_FE_PTZ_TURN, OnBtnFePtzTurn)
	ON_BN_CLICKED(IDC_BTN_FE_CRUISE_SET, OnBtnFeCruiseSet)
	ON_BN_CLICKED(IDC_BTN_FE_CRUISE_DEL, OnBtnFeCruiseDel)
	ON_BN_CLICKED(IDC_BTN_FE_CRUISE_RUN, OnBtnFeCruiseRun)
	ON_BN_CLICKED(IDC_BTN_FE_CRUISE_STOP, OnBtnFeCruiseStop)
	ON_BN_CLICKED(IDC_BTN_GET_PRESET_NUM, OnBtnGetPresetNum)
	ON_BN_CLICKED(IDC_BTN_GET_PTZCRUISE_NUM, OnBtnGetPtzcruiseNum)
	ON_BN_CLICKED(IDC_BTN_GETPRESET_INFO, OnBtnGetpresetInfo)
	ON_BN_CLICKED(IDC_BTN_GETCRUISE_INFO, OnBtnGetcruiseInfo)
	ON_BN_CLICKED(IDC_BTN_MOTION_TRACK_SET, OnBtnMotionTrackSet)
	ON_BN_CLICKED(IDC_BTN_MOTION_TRACK_GET, OnBtnMotionTrackGet)
	ON_BN_CLICKED(IDC_BTN_UP_PRESET, OnBtnUpPreset)
	ON_BN_CLICKED(IDC_BTN_DELSEQ, OnBtnDelseq)
	ON_BN_CLICKED(IDC_BTN_IPADDR_FILTER, OnBtnIpaddrFilter)
	ON_BN_CLICKED(IDC_BTN_UPLOAD_LOGO, OnBtnUploadLogo)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgIPCSpecial message handlers
BOOL CDlgIPCSpecial::OnInitDialog()
{
	CDialog::OnInitDialog();
	OnBtnGetAuxalarm();

	CString strTemp;
	int i;
//	((CComboBox*)GetDlgItem(IDC_COMBO_FE_PRESET_NUM))->ResetContent();//消除现有所有内容
// 	m_comboCurisePreset.ResetContent();
// 	for(i=1;i<=255;i++)
// 	{
// 		strTemp.Format("%d",i);
// 		((CComboBox*)GetDlgItem(IDC_COMBO_FE_PRESET_NUM))->AddString(strTemp);
// 		m_comboCurisePreset.AddString(strTemp);
// 	}

	m_comboPresetNum.ResetContent();
	for(i=1;i<=255;i++)
	{
		strTemp.Format("%d",i);
//		((CComboBox*)GetDlgItem(IDC_COMBO_FE_PRESET_NUM))->AddString(strTemp);
		m_comboPresetNum.AddString(strTemp);
	}

	m_comboCruiseRoute.ResetContent();
	for(i=1;i<=32;i++)
	{
		strTemp.Format("%d",i);
		m_comboCruiseRoute.AddString(strTemp);
	}
 
	m_comboCruisePoint.ResetContent();
	for(i=1;i<=32;i++)
	{
		strTemp.Format("%d",i);
		m_comboCruisePoint.AddString(strTemp);
	}
    
    m_comboCruiseSpeed.ResetContent();
	for(i=1;i<=40;i++)
	{
		strTemp.Format("%d",i);
		m_comboCruiseSpeed.AddString(strTemp);
	}

    m_comboCuriseTime.ResetContent();
	for(i=1;i<=255;i++)
	{
		strTemp.Format("%d",i);
		m_comboCuriseTime.AddString(strTemp);
	}

//	GetDlgItem(IDC_PLAYWND_PTZ)->GetWindowRect(&m_rcWnd);
	char szLan[128] = {0};
	m_listGetPresetInfo.InsertColumn(0, "",LVCFMT_LEFT, 0, -1);
	g_StringLanType(szLan, "预置点序号", "Preset point number");
	m_listGetPresetInfo.InsertColumn(1, szLan, LVCFMT_LEFT, 90);
	g_StringLanType(szLan, "预置点x轴", "preset point x axis");
	m_listGetPresetInfo.InsertColumn(2, szLan, LVCFMT_LEFT, 90);
	g_StringLanType(szLan, "预置点y轴", "preset point y axis");
	m_listGetPresetInfo.InsertColumn(3, szLan, LVCFMT_LEFT, 100);
	m_listGetPresetInfo.SetExtendedStyle(m_listGetPresetInfo.GetExtendedStyle()|LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT|LVS_EX_SUBITEMIMAGES);

	m_listGetPreCruiseiInfo.InsertColumn(0, "",LVCFMT_LEFT, 0, -1);
	g_StringLanType(szLan, "巡航路径序号", "Cruise path serial number");
	m_listGetPreCruiseiInfo.InsertColumn(1, szLan, LVCFMT_LEFT, 50);
	g_StringLanType(szLan, "巡航点号", "Cruise Point");
	m_listGetPreCruiseiInfo.InsertColumn(2, szLan, LVCFMT_LEFT, 50);
	g_StringLanType(szLan, "预置点序号", "Preset Point");
	m_listGetPreCruiseiInfo.InsertColumn(3, szLan, LVCFMT_LEFT, 80);
	g_StringLanType(szLan, "预置点x轴", "Preset Point x axis");
	m_listGetPreCruiseiInfo.InsertColumn(4, szLan, LVCFMT_LEFT, 80);
	g_StringLanType(szLan, "预置点y轴", "Preset Point y axis");
	m_listGetPreCruiseiInfo.InsertColumn(5, szLan, LVCFMT_LEFT, 80);
	g_StringLanType(szLan, "停留时间", "Stop time");
	m_listGetPreCruiseiInfo.InsertColumn(6, szLan, LVCFMT_LEFT, 80);
	g_StringLanType(szLan, "速度", "Speed");
	m_listGetPreCruiseiInfo.InsertColumn(7, szLan, LVCFMT_LEFT, 40);

	m_listGetPreCruiseiInfo.SetExtendedStyle(m_listGetPresetInfo.GetExtendedStyle()|LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT|LVS_EX_SUBITEMIMAGES);

	//预览接口调用
	NET_DVR_CLIENTINFO struPlay;
	struPlay.hPlayWnd 	= GetDlgItem(IDC_PLAYWND_PTZ)->GetSafeHwnd();
	struPlay.lChannel 	= m_lChannel; 
	struPlay.lLinkMode 	= 0;
	struPlay.sMultiCastIP = "";	
	m_lPlayHandle = NET_DVR_RealPlay_V30(m_lServerID, &struPlay, NULL, NULL, TRUE);
	if (m_lPlayHandle)
	{
	   if (m_lPlayHandle < 0)
	   {
		   g_pMainDlg->AddLog(-1, OPERATION_FAIL_T, "NET_DVR_RealPlay_V30");
		   AfxMessageBox("NET_DVR_RealPlay_V30 FAIL");		
	   }
	   else
	   {
		   g_pMainDlg->AddLog(-1, OPERATION_SUCC_T, "NET_DVR_RealPlay_V30");			
	   }
    }	

	//OnBtnMotionTrackGet();
	OnBtnGetPresetNum();
	OnBtnGetPtzcruiseNum();
	m_iPresetNum = 0;
	m_iPresetGroupNum = 0;
	m_dwFEChannelNum = 1;

	m_iPresetGetGroupNum = 1;
	m_iPresetChannel = 1;
	
	m_iPreCruiseChannel = 1;
	m_iPreGetCruiseGroupNum = 1;
	UpdateData(FALSE);
	return TRUE;
}

void CDlgIPCSpecial::OnBtnShutterComp() 
{
	// TODO: Add your control notification handler code here
	if (!NET_DVR_ShutterCompensation(m_lServerID))
	{
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_ShutterCompensation");
		return;
	}
	else
	{
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_ShutterCompensation");
	}
}

void CDlgIPCSpecial::OnBtnSet() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	NET_DVR_CORRECT_DEADPIXEL_PARAM struDeadPixel;
	memset(&struDeadPixel, 0, sizeof(struDeadPixel));
    struDeadPixel.dwCommand = m_comboCmd.GetCurSel();
    struDeadPixel.dwDeadPixelX = m_dwDeadPixelX;
	struDeadPixel.dwDeadPixelY = m_dwDeadPixelY;
	struDeadPixel.dwSize = sizeof(struDeadPixel);
	
	if (!NET_DVR_CorrectDeadPixel(m_lServerID, m_lChannel, &struDeadPixel))
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_CorrectDeadPixel");
		return;
	}
	else
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_CorrectDeadPixel");
	}
}

// void CDlgIPCSpecial::OnBtnFocusOnepush() 
// {
// 	// TODO: Add your control notification handler code here
// 	if (!NET_DVR_FocusOnePush(m_lServerID, m_lChannel))
// 	{
// 		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_FocusOnePush");
// 		return;
// 	}
// 	else
// 	{
// 		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_FocusOnePush");
// 	}
// }

// void CDlgIPCSpecial::OnBtnResetLens() 
// {
// 	// TODO: Add your control notification handler code here
// 	if (!NET_DVR_ResetLens(m_lServerID, m_lChannel))
// 	{
// 		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_ResetLens");
// 		return;
// 	}
// 	else
// 	{
// 		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_ResetLens");
// 	}
// }

void CDlgIPCSpecial::OnBtnIpcOnepushFocus() 
{
	// TODO: Add your control notification handler code here
 	if (!NET_DVR_FocusOnePush(m_lServerID, m_lChannel))
 	{
 		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_FocusOnePush");
 		return;
 	}
 	else
 	{
 		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_FocusOnePush");
 	}
}

void CDlgIPCSpecial::OnBtnIpcResetLens() 
{
	// TODO: Add your control notification handler code here
	if (!NET_DVR_ResetLens(m_lServerID, m_lChannel))
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_ResetLens");
		return;
	}
	else
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_ResetLens");
	}
}

void CDlgIPCSpecial::OnBtnRemotecontrolAlarm() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	NET_DVR_REMOTECONTROL_ALARM_PARAM struInBuf = {0};
	struInBuf.dwSize = sizeof(NET_DVR_REMOTECONTROL_ALARM_PARAM);
	struInBuf.dwChannel = 1;
	struInBuf.wDealyTime = m_dwDelayTime;
	if (!NET_DVR_RemoteControl(m_lServerID, NET_DVR_REMOTECONTROL_ALARM, &struInBuf, sizeof(struInBuf)))
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_RemoteControl NET_DVR_REMOTECONTROL_ALARM");
		return;
	}
	else
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_RemoteControl NET_DVR_REMOTECONTROL_ALARM");
	}
}

void CDlgIPCSpecial::OnBtnRemotecontrolDisalarm() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	NET_DVR_REMOTECONTROL_ALARM_PARAM struInBuf = {0};
	struInBuf.dwSize = sizeof(NET_DVR_REMOTECONTROL_ALARM_PARAM);
	struInBuf.dwChannel = 1;
	struInBuf.wDealyTime = m_dwDelayTime;
	if (!NET_DVR_RemoteControl(m_lServerID, NET_DVR_REMOTECONTROL_DISALARM, &struInBuf, sizeof(struInBuf)))
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_RemoteControl NET_DVR_REMOTECONTROL_DISALARM");
		return;
	}
	else
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_RemoteControl NET_DVR_REMOTECONTROL_DISALARM");
	}
}

void CDlgIPCSpecial::OnBtnRemotecontrolStudy() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	NET_DVR_REMOTECONTROL_STUDY_PARAM struInBuf = {0};
	struInBuf.dwSize = sizeof(NET_DVR_REMOTECONTROL_STUDY_PARAM);
	struInBuf.dwChannel = 1;
	if (!NET_DVR_RemoteControl(m_lServerID, NET_DVR_REMOTECONTROL_STUDY, &struInBuf, sizeof(struInBuf)))
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_RemoteControl NET_DVR_REMOTECONTROL_STUDY");
		return;
	}
	else
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_RemoteControl NET_DVR_REMOTECONTROL_STUDY");
	}
}

void CDlgIPCSpecial::OnBtnWirelessStudy() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	NET_DVR_WIRELESS_ALARM_STUDY_PARAM struInBuf = {0};
	struInBuf.dwSize = sizeof(NET_DVR_WIRELESS_ALARM_STUDY_PARAM);
	struInBuf.dwChannel = 1;
	struInBuf.byIndex = m_byWirelessIndex;
	if (!NET_DVR_RemoteControl(m_lServerID, NET_DVR_WIRELESS_ALARM_STUDY, &struInBuf, sizeof(struInBuf)))
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_RemoteControl NET_DVR_WIRELESS_ALARM_STUDY");
		return;
	}
	else
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_RemoteControl NET_DVR_WIRELESS_ALARM_STUDY");
	}
}

void CDlgIPCSpecial::OnBtnGetAuxalarm() 
{
	// TODO: Add your control notification handler code here
	DWORD dwReturn = 0;
	int i;
    
    if (NET_DVR_GetDVRConfig(m_lServerID, NET_IPC_GET_AUX_ALARMCFG, 1, &m_struAuxAlarm, sizeof(m_struAuxAlarm), &dwReturn))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_IPC_GET_AUX_ALARMCFG");
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_IPC_GET_AUX_ALARMCFG");
//        return;
    }
	m_comboAuxAlarmId.SetCurSel(0);
	m_comboWirelessId.SetCurSel(0);
	m_lWirelessID = 0;
	m_lAuxAlarmID = 0;
	m_comboAuxAlarmType.SetCurSel(m_struAuxAlarm.struAlarm[m_lAuxAlarmID].byAlarmType-1);
	if (m_struAuxAlarm.struAlarm[m_lAuxAlarmID].byAlarmType == IPC_AUXALARM_PIR)
	{
		m_csAlarmName.Format("%s", m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struPIRAlarm.byAlarmName);
		m_bChkHanleAlarm = m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struPIRAlarm.byAlarmHandle;
		for (i=0; i<MAX_ALARMOUT_V30; i++)
		{
			m_bAlarmOut[i] = m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struPIRAlarm.struAlarmHandleType.byRelAlarmOut[i];
		}
		m_bChkRecordEn = m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struPIRAlarm.byRelRecordChan[0];
		m_bChkMonitorAlarm = m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struPIRAlarm.struAlarmHandleType.dwHandleType &0x01;
		m_bChkAudioAlarm = (m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struPIRAlarm.struAlarmHandleType.dwHandleType>>1)&0x01;
		m_bChkReportCenter = (m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struPIRAlarm.struAlarmHandleType.dwHandleType>>2)&0x01;
		m_bChkInvokeAlarmOut = (m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struPIRAlarm.struAlarmHandleType.dwHandleType>>3)&0x01;
		m_bChkInvokeJpegCapture = (m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struPIRAlarm.struAlarmHandleType.dwHandleType>>4)&0x01;
	    m_bChkPicFtp = (m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struPIRAlarm.struAlarmHandleType.dwHandleType>>9)&0x01;
		m_bChkWirelessLight = (m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struPIRAlarm.struAlarmHandleType.dwHandleType>>5)&0x01;
	}
	else if (m_struAuxAlarm.struAlarm[m_lAuxAlarmID].byAlarmType == IPC_AUXALARM_WIRELESS)
	{
		m_csAlarmName.Format("%s", m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struWirelessAlarm.struWirelessAlarm[m_lWirelessID].byAlarmName);
		m_bChkHanleAlarm = m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struWirelessAlarm.struWirelessAlarm[m_lWirelessID].byAlarmHandle;
		m_byWirelessID = m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struWirelessAlarm.struWirelessAlarm[m_lWirelessID].byID;
		for (i=0; i<MAX_ALARMOUT_V30; i++)
		{
			m_bAlarmOut[i] = m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struWirelessAlarm.struWirelessAlarm[m_lWirelessID].struAlarmHandleType.byRelAlarmOut[i];
		}
		m_bChkRecordEn = m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struWirelessAlarm.struWirelessAlarm[m_lWirelessID].byRelRecordChan[0];
		m_bChkMonitorAlarm = m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struWirelessAlarm.struWirelessAlarm[m_lWirelessID].struAlarmHandleType.dwHandleType &0x01;
		m_bChkAudioAlarm = (m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struWirelessAlarm.struWirelessAlarm[m_lWirelessID].struAlarmHandleType.dwHandleType>>1)&0x01;
		m_bChkReportCenter = (m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struWirelessAlarm.struWirelessAlarm[m_lWirelessID].struAlarmHandleType.dwHandleType>>2)&0x01;
		m_bChkInvokeAlarmOut = (m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struWirelessAlarm.struWirelessAlarm[m_lWirelessID].struAlarmHandleType.dwHandleType>>3)&0x01;
		m_bChkInvokeJpegCapture = (m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struWirelessAlarm.struWirelessAlarm[m_lWirelessID].struAlarmHandleType.dwHandleType>>4)&0x01;
		m_bChkPicFtp = (m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struWirelessAlarm.struWirelessAlarm[m_lWirelessID].struAlarmHandleType.dwHandleType>>9)&0x01;
		m_bChkWirelessLight = (m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struWirelessAlarm.struWirelessAlarm[m_lWirelessID].struAlarmHandleType.dwHandleType>>5)&0x01;
	}
	else if (m_struAuxAlarm.struAlarm[m_lAuxAlarmID].byAlarmType == IPC_AUXALARM_CALLHELP)
	{
		m_bChkHanleAlarm = m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struCallHelpAlarm.byAlarmHandle;
		for (i=0; i<MAX_ALARMOUT_V30; i++)
		{
			m_bAlarmOut[i] = m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struCallHelpAlarm.struAlarmHandleType.byRelAlarmOut[i];
		}
		m_bChkRecordEn = m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struCallHelpAlarm.byRelRecordChan[0];
		m_bChkMonitorAlarm = m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struCallHelpAlarm.struAlarmHandleType.dwHandleType &0x01;
		m_bChkAudioAlarm = (m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struCallHelpAlarm.struAlarmHandleType.dwHandleType>>1)&0x01;
		m_bChkReportCenter = (m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struCallHelpAlarm.struAlarmHandleType.dwHandleType>>2)&0x01;
		m_bChkInvokeAlarmOut = (m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struCallHelpAlarm.struAlarmHandleType.dwHandleType>>3)&0x01;
		m_bChkInvokeJpegCapture = (m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struCallHelpAlarm.struAlarmHandleType.dwHandleType>>4)&0x01;
		m_bChkPicFtp = (m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struCallHelpAlarm.struAlarmHandleType.dwHandleType>>9)&0x01;
		m_bChkWirelessLight = (m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struCallHelpAlarm.struAlarmHandleType.dwHandleType>>5)&0x01;
	}

	CreateTree();
	UpdateData(FALSE);
}

void CDlgIPCSpecial::OnBtnSetAuxalarm() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	if (NET_DVR_SetDVRConfig(m_lServerID, NET_IPC_SET_AUX_ALARMCFG, 1, &m_struAuxAlarm, sizeof(m_struAuxAlarm)))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_IPC_SET_AUX_ALARMCFG");
        return;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_IPC_SET_AUX_ALARMCFG");
        return;
    }
}

/*********************************************************
Function:	CreateTree
Desc:		Create alarm output-video channel connection
Input:	
Output:	
Return:	
**********************************************************/
void CDlgIPCSpecial::CreateTree(void)
{
	//m_treeAlarmOut.DeleteAllItems();
	g_CreateAlarmOutTree(m_treeAlarmOut, m_iDevIndex, m_bAlarmOut);
}

void CDlgIPCSpecial::OnClickTreeAlarmOut(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	CPoint pt(0,0);
	CRect rc(0,0,0,0);
	GetCursorPos(&pt);
	GetDlgItem(IDC_TREE_ALARM_OUT)->GetWindowRect(&rc);
	ScreenToClient(&rc);
	ScreenToClient(&pt);
	pt.x = pt.x - rc.left;
	pt.y = pt.y - rc.top;
	
	UINT uFlag = 0;
	HTREEITEM hSelect = m_treeAlarmOut.HitTest(pt, &uFlag);
	
	if (NULL == hSelect) 
	{
		return;
	}
	m_treeAlarmOut.SelectItem(hSelect);
	DWORD dwIndex = m_treeAlarmOut.GetItemData(hSelect)%1000;
	BOOL bCheck = m_treeAlarmOut.GetCheck(hSelect);
	m_bAlarmOut[dwIndex] = !bCheck;
	
	if (uFlag != LVHT_TOLEFT)
	{
		m_treeAlarmOut.SetCheck(hSelect, !bCheck);
	}
	else
	{
		m_treeAlarmOut.SetCheck(hSelect, bCheck);
	}
	*pResult = 0;
}

void CDlgIPCSpecial::OnBtnSaveAuxAlarm() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	int i;
	m_lAuxAlarmID = m_comboAuxAlarmId.GetCurSel();
	m_lWirelessID = m_comboWirelessId.GetCurSel();
	m_struAuxAlarm.struAlarm[m_lAuxAlarmID].byAlarmType = m_comboAuxAlarmType.GetCurSel()+1;
	if (m_comboAuxAlarmType.GetCurSel()+1 == IPC_AUXALARM_PIR)
	{
		memcpy(m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struPIRAlarm.byAlarmName, m_csAlarmName,NAME_LEN);
		m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struPIRAlarm.byAlarmHandle = m_bChkHanleAlarm;
		for (i=0; i<MAX_ALARMOUT_V30; i++)
		{
			m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struPIRAlarm.struAlarmHandleType.byRelAlarmOut[i] = (BYTE)m_bAlarmOut[i];
		}
		m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struPIRAlarm.byRelRecordChan[0] = m_bChkRecordEn;
		m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struPIRAlarm.struAlarmHandleType.dwHandleType = 0;
		m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struPIRAlarm.struAlarmHandleType.dwHandleType |= (m_bChkMonitorAlarm << 0);
		m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struPIRAlarm.struAlarmHandleType.dwHandleType |= (m_bChkAudioAlarm << 1);
		m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struPIRAlarm.struAlarmHandleType.dwHandleType |= (m_bChkReportCenter << 2);
		m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struPIRAlarm.struAlarmHandleType.dwHandleType |= (m_bChkInvokeAlarmOut << 3);
		m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struPIRAlarm.struAlarmHandleType.dwHandleType |= (m_bChkInvokeJpegCapture << 4);
		m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struPIRAlarm.struAlarmHandleType.dwHandleType |= (m_bChkWirelessLight << 5);
	    m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struPIRAlarm.struAlarmHandleType.dwHandleType |= (m_bChkPicFtp << 9);
	}
	else if (m_comboAuxAlarmType.GetCurSel()+1 == IPC_AUXALARM_WIRELESS)
	{
		memcpy(m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struWirelessAlarm.struWirelessAlarm[m_lWirelessID].byAlarmName, m_csAlarmName,NAME_LEN);
		m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struWirelessAlarm.struWirelessAlarm[m_lWirelessID].byAlarmHandle = m_bChkHanleAlarm;
		m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struWirelessAlarm.struWirelessAlarm[m_lWirelessID].byID = m_byWirelessID;
		for (i=0; i<MAX_ALARMOUT_V30; i++)
		{
			m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struPIRAlarm.struAlarmHandleType.byRelAlarmOut[i] = (BYTE)m_bAlarmOut[i];
		}
		m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struWirelessAlarm.struWirelessAlarm[m_lWirelessID].byRelRecordChan[0] = m_bChkRecordEn;
		m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struWirelessAlarm.struWirelessAlarm[m_lWirelessID].struAlarmHandleType.dwHandleType = 0;
		m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struWirelessAlarm.struWirelessAlarm[m_lWirelessID].struAlarmHandleType.dwHandleType |= (m_bChkMonitorAlarm << 0);
		m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struWirelessAlarm.struWirelessAlarm[m_lWirelessID].struAlarmHandleType.dwHandleType |= (m_bChkAudioAlarm << 1);
		m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struWirelessAlarm.struWirelessAlarm[m_lWirelessID].struAlarmHandleType.dwHandleType |= (m_bChkReportCenter << 2);
		m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struWirelessAlarm.struWirelessAlarm[m_lWirelessID].struAlarmHandleType.dwHandleType |= (m_bChkInvokeAlarmOut << 3);
		m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struWirelessAlarm.struWirelessAlarm[m_lWirelessID].struAlarmHandleType.dwHandleType |= (m_bChkInvokeJpegCapture << 4);
		m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struWirelessAlarm.struWirelessAlarm[m_lWirelessID].struAlarmHandleType.dwHandleType |= (m_bChkWirelessLight << 5);
		m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struWirelessAlarm.struWirelessAlarm[m_lWirelessID].struAlarmHandleType.dwHandleType |= (m_bChkPicFtp << 9);
	}
	else if (m_comboAuxAlarmType.GetCurSel()+1 == IPC_AUXALARM_CALLHELP)
	{
		m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struCallHelpAlarm.byAlarmHandle = m_bChkHanleAlarm;
		for (i=0; i<MAX_ALARMOUT_V30; i++)
		{
			m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struCallHelpAlarm.struAlarmHandleType.byRelAlarmOut[i] = (BYTE)m_bAlarmOut[i];
		}
		m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struCallHelpAlarm.byRelRecordChan[0] = m_bChkRecordEn;
		m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struCallHelpAlarm.struAlarmHandleType.dwHandleType = 0;
		m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struCallHelpAlarm.struAlarmHandleType.dwHandleType |= (m_bChkMonitorAlarm << 0);
		m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struCallHelpAlarm.struAlarmHandleType.dwHandleType |= (m_bChkAudioAlarm << 1);
		m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struCallHelpAlarm.struAlarmHandleType.dwHandleType |= (m_bChkReportCenter << 2);
		m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struCallHelpAlarm.struAlarmHandleType.dwHandleType |= (m_bChkInvokeAlarmOut << 3);
		m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struCallHelpAlarm.struAlarmHandleType.dwHandleType |= (m_bChkInvokeJpegCapture << 4);
		m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struCallHelpAlarm.struAlarmHandleType.dwHandleType |= (m_bChkWirelessLight << 5);
		m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struCallHelpAlarm.struAlarmHandleType.dwHandleType |= (m_bChkPicFtp << 9);
	}
}

void CDlgIPCSpecial::OnSelchangeComboAuxAlarmId() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	int i;
	m_lAuxAlarmID = m_comboAuxAlarmId.GetCurSel();
	m_lWirelessID = m_comboWirelessId.GetCurSel();

	m_comboAuxAlarmType.SetCurSel(m_struAuxAlarm.struAlarm[m_lAuxAlarmID].byAlarmType-1);
	if (m_struAuxAlarm.struAlarm[m_lAuxAlarmID].byAlarmType == IPC_AUXALARM_PIR)
	{
		m_csAlarmName.Format("%s", m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struPIRAlarm.byAlarmName);
		m_bChkHanleAlarm = m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struPIRAlarm.byAlarmHandle;
		for (i=0; i<MAX_ALARMOUT_V30; i++)
		{
			m_bAlarmOut[i] = m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struPIRAlarm.struAlarmHandleType.byRelAlarmOut[i];
		}
		m_bChkRecordEn = m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struPIRAlarm.byRelRecordChan[0];
		m_bChkMonitorAlarm = m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struPIRAlarm.struAlarmHandleType.dwHandleType &0x01;
		m_bChkAudioAlarm = (m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struPIRAlarm.struAlarmHandleType.dwHandleType>>1)&0x01;
		m_bChkReportCenter = (m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struPIRAlarm.struAlarmHandleType.dwHandleType>>2)&0x01;
		m_bChkInvokeAlarmOut = (m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struPIRAlarm.struAlarmHandleType.dwHandleType>>3)&0x01;
		m_bChkInvokeJpegCapture = (m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struPIRAlarm.struAlarmHandleType.dwHandleType>>4)&0x01;
		m_bChkPicFtp = (m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struPIRAlarm.struAlarmHandleType.dwHandleType>>9)&0x01;
		m_bChkWirelessLight = (m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struPIRAlarm.struAlarmHandleType.dwHandleType>>5)&0x01;
	}
	else if (m_struAuxAlarm.struAlarm[m_lAuxAlarmID].byAlarmType == IPC_AUXALARM_WIRELESS)
	{
		m_csAlarmName.Format("%s", m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struWirelessAlarm.struWirelessAlarm[m_lWirelessID].byAlarmName);
		m_bChkHanleAlarm = m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struWirelessAlarm.struWirelessAlarm[m_lWirelessID].byAlarmHandle;
		m_byWirelessID = m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struWirelessAlarm.struWirelessAlarm[m_lWirelessID].byID;
		for (i=0; i<MAX_ALARMOUT_V30; i++)
		{
			m_bAlarmOut[i] = m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struWirelessAlarm.struWirelessAlarm[m_lWirelessID].struAlarmHandleType.byRelAlarmOut[i];
		}
		m_bChkRecordEn = m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struWirelessAlarm.struWirelessAlarm[m_lWirelessID].byRelRecordChan[0];
		m_bChkMonitorAlarm = m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struWirelessAlarm.struWirelessAlarm[m_lWirelessID].struAlarmHandleType.dwHandleType &0x01;
		m_bChkAudioAlarm = (m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struWirelessAlarm.struWirelessAlarm[m_lWirelessID].struAlarmHandleType.dwHandleType>>1)&0x01;
		m_bChkReportCenter = (m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struWirelessAlarm.struWirelessAlarm[m_lWirelessID].struAlarmHandleType.dwHandleType>>2)&0x01;
		m_bChkInvokeAlarmOut = (m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struWirelessAlarm.struWirelessAlarm[m_lWirelessID].struAlarmHandleType.dwHandleType>>3)&0x01;
		m_bChkInvokeJpegCapture = (m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struWirelessAlarm.struWirelessAlarm[m_lWirelessID].struAlarmHandleType.dwHandleType>>4)&0x01;
		m_bChkPicFtp = (m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struWirelessAlarm.struWirelessAlarm[m_lWirelessID].struAlarmHandleType.dwHandleType>>9)&0x01;
		m_bChkWirelessLight = (m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struWirelessAlarm.struWirelessAlarm[m_lWirelessID].struAlarmHandleType.dwHandleType>>5)&0x01;
	}
	else if (m_struAuxAlarm.struAlarm[m_lAuxAlarmID].byAlarmType == IPC_AUXALARM_CALLHELP)
	{
		m_bChkHanleAlarm = m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struCallHelpAlarm.byAlarmHandle;
		for (i=0; i<MAX_ALARMOUT_V30; i++)
		{
			m_bAlarmOut[i] = m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struCallHelpAlarm.struAlarmHandleType.byRelAlarmOut[i];
		}
		m_bChkRecordEn = m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struCallHelpAlarm.byRelRecordChan[0];
		m_bChkMonitorAlarm = m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struCallHelpAlarm.struAlarmHandleType.dwHandleType &0x01;
		m_bChkAudioAlarm = (m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struCallHelpAlarm.struAlarmHandleType.dwHandleType>>1)&0x01;
		m_bChkReportCenter = (m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struCallHelpAlarm.struAlarmHandleType.dwHandleType>>2)&0x01;
		m_bChkInvokeAlarmOut = (m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struCallHelpAlarm.struAlarmHandleType.dwHandleType>>3)&0x01;
		m_bChkInvokeJpegCapture = (m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struCallHelpAlarm.struAlarmHandleType.dwHandleType>>4)&0x01;
		m_bChkPicFtp = (m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struCallHelpAlarm.struAlarmHandleType.dwHandleType>>9)&0x01;
		m_bChkWirelessLight = (m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struCallHelpAlarm.struAlarmHandleType.dwHandleType>>5)&0x01;
	}
	CreateTree();
	UpdateData(FALSE);
}

void CDlgIPCSpecial::OnSelchangeComboAuxalarmType() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	char sAlarmName[33] = {0};
	int i;
	m_lAuxAlarmID = m_comboAuxAlarmId.GetCurSel();
	m_lWirelessID = m_comboWirelessId.GetCurSel();
	
	if (m_struAuxAlarm.struAlarm[m_lAuxAlarmID].byAlarmType == m_comboAuxAlarmType.GetCurSel()+1)
	{
		if (m_struAuxAlarm.struAlarm[m_lAuxAlarmID].byAlarmType == IPC_AUXALARM_PIR)
		{
			m_csAlarmName.Format("%s", m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struPIRAlarm.byAlarmName);
			m_bChkHanleAlarm = m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struPIRAlarm.byAlarmHandle;
			for (i=0; i<MAX_ALARMOUT_V30; i++)
			{
				m_bAlarmOut[i] = m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struPIRAlarm.struAlarmHandleType.byRelAlarmOut[i];
			}
			m_bChkRecordEn = m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struPIRAlarm.byRelRecordChan[0];
			m_bChkMonitorAlarm = m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struPIRAlarm.struAlarmHandleType.dwHandleType &0x01;
			m_bChkAudioAlarm = (m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struPIRAlarm.struAlarmHandleType.dwHandleType>>1)&0x01;
			m_bChkReportCenter = (m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struPIRAlarm.struAlarmHandleType.dwHandleType>>2)&0x01;
			m_bChkInvokeAlarmOut = (m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struPIRAlarm.struAlarmHandleType.dwHandleType>>3)&0x01;
			m_bChkInvokeJpegCapture = (m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struPIRAlarm.struAlarmHandleType.dwHandleType>>4)&0x01;
			m_bChkPicFtp = (m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struPIRAlarm.struAlarmHandleType.dwHandleType>>9)&0x01;
			m_bChkWirelessLight = (m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struPIRAlarm.struAlarmHandleType.dwHandleType>>5)&0x01;
		}
		else if (m_struAuxAlarm.struAlarm[m_lAuxAlarmID].byAlarmType == IPC_AUXALARM_WIRELESS)
		{
			m_csAlarmName.Format("%s", m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struWirelessAlarm.struWirelessAlarm[m_lWirelessID].byAlarmName);
			m_bChkHanleAlarm = m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struWirelessAlarm.struWirelessAlarm[m_lWirelessID].byAlarmHandle;
			m_byWirelessID = m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struWirelessAlarm.struWirelessAlarm[m_lWirelessID].byID;
			for (i=0; i<MAX_ALARMOUT_V30; i++)
			{
				m_bAlarmOut[i] = m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struWirelessAlarm.struWirelessAlarm[m_lWirelessID].struAlarmHandleType.byRelAlarmOut[i];
			}
			m_bChkRecordEn = m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struWirelessAlarm.struWirelessAlarm[m_lWirelessID].byRelRecordChan[0];
			m_bChkMonitorAlarm = m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struWirelessAlarm.struWirelessAlarm[m_lWirelessID].struAlarmHandleType.dwHandleType &0x01;
			m_bChkAudioAlarm = (m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struWirelessAlarm.struWirelessAlarm[m_lWirelessID].struAlarmHandleType.dwHandleType>>1)&0x01;
			m_bChkReportCenter = (m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struWirelessAlarm.struWirelessAlarm[m_lWirelessID].struAlarmHandleType.dwHandleType>>2)&0x01;
			m_bChkInvokeAlarmOut = (m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struWirelessAlarm.struWirelessAlarm[m_lWirelessID].struAlarmHandleType.dwHandleType>>3)&0x01;
			m_bChkInvokeJpegCapture = (m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struWirelessAlarm.struWirelessAlarm[m_lWirelessID].struAlarmHandleType.dwHandleType>>4)&0x01;
			m_bChkPicFtp = (m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struWirelessAlarm.struWirelessAlarm[m_lWirelessID].struAlarmHandleType.dwHandleType>>9)&0x01;
			m_bChkWirelessLight = (m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struWirelessAlarm.struWirelessAlarm[m_lWirelessID].struAlarmHandleType.dwHandleType>>5)&0x01;
		}
		else if (m_struAuxAlarm.struAlarm[m_lAuxAlarmID].byAlarmType == IPC_AUXALARM_CALLHELP)
		{
			m_bChkHanleAlarm = m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struCallHelpAlarm.byAlarmHandle;
			for (i=0; i<MAX_ALARMOUT_V30; i++)
			{
				m_bAlarmOut[i] = m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struCallHelpAlarm.struAlarmHandleType.byRelAlarmOut[i];
			}
			m_bChkRecordEn = m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struCallHelpAlarm.byRelRecordChan[0];
			m_bChkMonitorAlarm = m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struCallHelpAlarm.struAlarmHandleType.dwHandleType &0x01;
			m_bChkAudioAlarm = (m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struCallHelpAlarm.struAlarmHandleType.dwHandleType>>1)&0x01;
			m_bChkReportCenter = (m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struCallHelpAlarm.struAlarmHandleType.dwHandleType>>2)&0x01;
			m_bChkInvokeAlarmOut = (m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struCallHelpAlarm.struAlarmHandleType.dwHandleType>>3)&0x01;
			m_bChkInvokeJpegCapture = (m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struCallHelpAlarm.struAlarmHandleType.dwHandleType>>4)&0x01;
			m_bChkPicFtp = (m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struCallHelpAlarm.struAlarmHandleType.dwHandleType>>9)&0x01;
			m_bChkWirelessLight = (m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struCallHelpAlarm.struAlarmHandleType.dwHandleType>>5)&0x01;
		}
	}
	else
	{
		m_comboWirelessId.SetCurSel(0);
		
		m_csAlarmName.Format("%s", sAlarmName);
		m_bChkHanleAlarm = 0;
		for (i=0; i<MAX_ALARMOUT_V30; i++)
		{
			m_bAlarmOut[i] = 0;
		}
		m_bChkRecordEn = 0;
		m_bChkMonitorAlarm = 0;
		m_bChkAudioAlarm = 0;
		m_bChkReportCenter = 0;
		m_bChkInvokeAlarmOut = 0;
		m_bChkInvokeJpegCapture = 0;
		m_bChkPicFtp = 0;
		m_bChkWirelessLight = 0;
	}
	CreateTree();
	UpdateData(FALSE);
}

void CDlgIPCSpecial::OnSelchangeComboWirelessAlarmId() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	int i;
	m_lAuxAlarmID = m_comboAuxAlarmId.GetCurSel();
	m_lWirelessID = m_comboWirelessId.GetCurSel();
	
	m_comboAuxAlarmType.SetCurSel(m_struAuxAlarm.struAlarm[m_lAuxAlarmID].byAlarmType-1);
	if (m_struAuxAlarm.struAlarm[m_lAuxAlarmID].byAlarmType == IPC_AUXALARM_PIR)
	{
		m_csAlarmName.Format("%s", m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struPIRAlarm.byAlarmName);
		m_bChkHanleAlarm = m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struPIRAlarm.byAlarmHandle;
		for (i=0; i<MAX_ALARMOUT_V30; i++)
		{
			m_bAlarmOut[i] = m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struPIRAlarm.struAlarmHandleType.byRelAlarmOut[i];
		}
		m_bChkRecordEn = m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struPIRAlarm.byRelRecordChan[0];
		m_bChkMonitorAlarm = m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struPIRAlarm.struAlarmHandleType.dwHandleType &0x01;
		m_bChkAudioAlarm = (m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struPIRAlarm.struAlarmHandleType.dwHandleType>>1)&0x01;
		m_bChkReportCenter = (m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struPIRAlarm.struAlarmHandleType.dwHandleType>>2)&0x01;
		m_bChkInvokeAlarmOut = (m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struPIRAlarm.struAlarmHandleType.dwHandleType>>3)&0x01;
		m_bChkInvokeJpegCapture = (m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struPIRAlarm.struAlarmHandleType.dwHandleType>>4)&0x01;
		m_bChkPicFtp = (m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struPIRAlarm.struAlarmHandleType.dwHandleType>>9)&0x01;
		m_bChkWirelessLight = (m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struPIRAlarm.struAlarmHandleType.dwHandleType>>5)&0x01;
	}
	else if (m_struAuxAlarm.struAlarm[m_lAuxAlarmID].byAlarmType == IPC_AUXALARM_WIRELESS)
	{
		m_csAlarmName.Format("%s", m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struWirelessAlarm.struWirelessAlarm[m_lWirelessID].byAlarmName);
		m_bChkHanleAlarm = m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struWirelessAlarm.struWirelessAlarm[m_lWirelessID].byAlarmHandle;
		m_byWirelessID = m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struWirelessAlarm.struWirelessAlarm[m_lWirelessID].byID;
		for (i=0; i<MAX_ALARMOUT_V30; i++)
		{
			m_bAlarmOut[i] = m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struWirelessAlarm.struWirelessAlarm[m_lWirelessID].struAlarmHandleType.byRelAlarmOut[i];
		}
		m_bChkRecordEn = m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struWirelessAlarm.struWirelessAlarm[m_lWirelessID].byRelRecordChan[0];
		m_bChkMonitorAlarm = m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struWirelessAlarm.struWirelessAlarm[m_lWirelessID].struAlarmHandleType.dwHandleType &0x01;
		m_bChkAudioAlarm = (m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struWirelessAlarm.struWirelessAlarm[m_lWirelessID].struAlarmHandleType.dwHandleType>>1)&0x01;
		m_bChkReportCenter = (m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struWirelessAlarm.struWirelessAlarm[m_lWirelessID].struAlarmHandleType.dwHandleType>>2)&0x01;
		m_bChkInvokeAlarmOut = (m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struWirelessAlarm.struWirelessAlarm[m_lWirelessID].struAlarmHandleType.dwHandleType>>3)&0x01;
		m_bChkInvokeJpegCapture = (m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struWirelessAlarm.struWirelessAlarm[m_lWirelessID].struAlarmHandleType.dwHandleType>>4)&0x01;
		m_bChkPicFtp = (m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struWirelessAlarm.struWirelessAlarm[m_lWirelessID].struAlarmHandleType.dwHandleType>>9)&0x01;
		m_bChkWirelessLight = (m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struWirelessAlarm.struWirelessAlarm[m_lWirelessID].struAlarmHandleType.dwHandleType>>5)&0x01;
	}
	else if (m_struAuxAlarm.struAlarm[m_lAuxAlarmID].byAlarmType == IPC_AUXALARM_CALLHELP)
	{
		m_bChkHanleAlarm = m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struCallHelpAlarm.byAlarmHandle;
		for (i=0; i<MAX_ALARMOUT_V30; i++)
		{
			m_bAlarmOut[i] = m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struCallHelpAlarm.struAlarmHandleType.byRelAlarmOut[i];
		}
		m_bChkRecordEn = m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struCallHelpAlarm.byRelRecordChan[0];
		m_bChkMonitorAlarm = m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struCallHelpAlarm.struAlarmHandleType.dwHandleType &0x01;
		m_bChkAudioAlarm = (m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struCallHelpAlarm.struAlarmHandleType.dwHandleType>>1)&0x01;
		m_bChkReportCenter = (m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struCallHelpAlarm.struAlarmHandleType.dwHandleType>>2)&0x01;
		m_bChkInvokeAlarmOut = (m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struCallHelpAlarm.struAlarmHandleType.dwHandleType>>3)&0x01;
		m_bChkInvokeJpegCapture = (m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struCallHelpAlarm.struAlarmHandleType.dwHandleType>>4)&0x01;
		m_bChkPicFtp = (m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struCallHelpAlarm.struAlarmHandleType.dwHandleType>>9)&0x01;
		m_bChkWirelessLight = (m_struAuxAlarm.struAlarm[m_lAuxAlarmID].uAlarm.struCallHelpAlarm.struAlarmHandleType.dwHandleType>>5)&0x01;
	}
	CreateTree();
	UpdateData(FALSE);
}

void CDlgIPCSpecial::OnPaint() 
{
	CreateTree();
	CDialog::OnPaint();
}

void CDlgIPCSpecial::OnChkWpsEn() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	NET_DVR_WPS_PARAM struWps = {0};
	struWps.dwSize = sizeof(struWps);
	struWps.byEnableWps = m_bChkWpsEn;

	char szLan[128] = {0};

	if (!NET_DVR_SetDVRConfig(m_lServerID, NET_DVR_SET_WPSCFG, 1, &struWps, sizeof(struWps)))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_SET_WPSCFG fail");
        AfxMessageBox("Fail to set PU stream config");
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_SET_WPSCFG Succ");
    }
}

void CDlgIPCSpecial::OnBtnRefresh() 
{
	// TODO: Add your control notification handler code here
	DWORD dwReturn;

	char szLan[128] = {0};
	NET_DVR_WPS_PARAM struWps = {0};
    if (!NET_DVR_GetDVRConfig(m_lServerID, NET_DVR_GET_WPSCFG, 1, &struWps, sizeof(struWps), &dwReturn))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_WPSCFG Fail");
        g_StringLanType(szLan, "获取WPS配置失败", "Fail to get WPS config");
        AfxMessageBox(szLan);
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_WPSCFG Success");
    }

	m_bChkWpsEn = struWps.byEnableWps;
	UpdateData(FALSE);
}

void CDlgIPCSpecial::OnBtnWpsConnect() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	char szTmp[33] = {0};
	NET_DVR_WPS_CONNECT_PARAM struWps = {0};
	struWps.dwSize = sizeof(struWps);
	struWps.byConnectType = m_comboWpsConType.GetCurSel();
    memcpy(struWps.byPIN, m_csAPPin, m_csAPPin.GetLength());
	memcpy(struWps.byEssid, m_csWpsEssid, m_csWpsEssid.GetLength());
	if (!NET_DVR_RemoteControl(m_lServerID, NET_DVR_WPS_CONNECT, &struWps, sizeof(struWps)))
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_RemoteControl NET_DVR_WPS_CONNECT");
		return;
	}
	else
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_RemoteControl NET_DVR_WPS_CONNECT");
	}
}

void CDlgIPCSpecial::OnBtnUpdatePin() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	if (!NET_DVR_RemoteControl(m_lServerID, NET_DVR_UPDATE_PIN, NULL, 0))
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_RemoteControl NET_DVR_UPDATE_PIN");
		return;
	}
	else
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_RemoteControl NET_DVR_UPDATE_PIN");
	}
}

void CDlgIPCSpecial::OnBtnGetDevPin() 
{
	// TODO: Add your control notification handler code here
	DWORD dwReturn;
	
	char szLan[128] = {0};
	NET_DVR_PIN_PARAM struPin = {0};
    if (!NET_DVR_GetDVRConfig(m_lServerID, NET_DVR_GET_DEVICE_PIN, 1, &struPin, sizeof(struPin), &dwReturn))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_DEVICE_PIN Fail");
        g_StringLanType(szLan, "获取设备PIN码失败", "Fail to get device PIN");
        AfxMessageBox(szLan);
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_DEVICE_PIN Success");
    }
	
	char szTmp[9] = {0};
	memcpy(szTmp, struPin.byPIN, 8);
	m_csDevPin.Format("%s", szTmp);
	UpdateData(FALSE);
}

void CDlgIPCSpecial::OnBtnFishEyeSet() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	NET_DVR_PREVIEW_DISPLAYCFG struFishEye;
	memset(&struFishEye, 0, sizeof(struFishEye));
	struFishEye.dwSize =  sizeof(struFishEye);
	struFishEye.byMountType = m_comboFishEyeMountType.GetCurSel();
	struFishEye.byDisplayMode = m_comboFishEyeDisplayMode.GetCurSel();
	struFishEye.byCorrectMode = m_comboFishEyeConnectMode.GetCurSel();

	if (NET_DVR_SetDVRConfig(m_lServerID, NET_DVR_SET_PREVIEW_DISPLAYCFG, 1, &struFishEye, sizeof(struFishEye)))
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_SET_PREVIEW_DISPLAYCFG");
		return;
	}
	else
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_SET_PREVIEW_DISPLAYCFG");
		return;
	}
}

void CDlgIPCSpecial::OnBtnFishEyeGet() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	DWORD dwReturn;
	
	char szLan[128] = {0};
	NET_DVR_PREVIEW_DISPLAYCFG struFishEye = {0};
    if (!NET_DVR_GetDVRConfig(m_lServerID,  NET_DVR_GET_PREVIEW_DISPLAYCFG, 1, &struFishEye, sizeof(struFishEye), &dwReturn))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, " NET_DVR_GET_PREVIEW_DISPLAYCFG Fail");
        g_StringLanType(szLan, "获取预览显示模式参数配置(鱼眼) 失败", "Fail to get WPS config");
        AfxMessageBox(szLan);
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, " NET_DVR_GET_PREVIEW_DISPLAYCFG Success");
    }
	
	m_comboFishEyeConnectMode.SetCurSel(struFishEye.byCorrectMode);
	m_comboFishEyeDisplayMode.SetCurSel(struFishEye.byDisplayMode);
	m_comboFishEyeMountType.SetCurSel(struFishEye.byMountType);
	UpdateData(FALSE);
}

void CDlgIPCSpecial::OnBtnFishEyePtzSet() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
    NET_DVR_REMOTECONTROL_PTZ_PARAM struRemoControl;
	struRemoControl.dwSize = sizeof(struRemoControl);
	struRemoControl.dwChannel = m_dwPTZFishEyeChannelNum;
	struRemoControl.dwPTZCommand = m_comboFishEyeControlCommand.GetItemData(m_comboFishEyeControlCommand.GetCurSel());
	struRemoControl.dwSpeed = m_comboFishEyeSpeedControl.GetCurSel();
	struRemoControl.dwStop = m_comboFishEyeStartStop.GetCurSel();
	struRemoControl.struVcaPoint.fX = m_struPoint.fX;
	struRemoControl.struVcaPoint.fY = m_struPoint.fY;

	if (!NET_DVR_RemoteControl(m_lServerID, NET_DVR_REMOTECONTROL_PTZ, &struRemoControl, sizeof(struRemoControl)))
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_RemoteControl NET_DVR_REMOTECONTROL_PTZ");
		return;
	}
	else
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_RemoteControl NET_DVR_REMOTECONTROL_PTZ");
	}
}

void CDlgIPCSpecial::OnBtnFePtzSet() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	char szLan[128] = {0};
	NET_DVR_PRESET_POINT_PARAM struRresetPoint = {0};
	struRresetPoint.dwSize = sizeof(struRresetPoint);
	struRresetPoint.dwChannel = m_dwFEChannelNum;
	struRresetPoint.dwPresetIndex = m_comboPresetNum.GetCurSel();
	struRresetPoint.dwPTZPresetCmd = SET_PRESET;
	struRresetPoint.struVcaPoint.fX = m_struPoint.fX;
	struRresetPoint.struVcaPoint.fY = m_struPoint.fY;

// 	dwChoosePtzindexNum = m_comboPresetNum.GetCurSel();
//     m_comboCurisePreset.
	if (!NET_DVR_RemoteControl(m_lServerID, NET_DVR_REMOTECONTROL_PRESETPOINT, &struRresetPoint, sizeof(struRresetPoint)))
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_RemoteControl NET_DVR_REMOTECONTROL_PRESETPOINT");
		g_StringLanType(szLan, "预置点设置失败!", "Preset settings fail");
        AfxMessageBox(szLan);
		return;
	}
	else
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_RemoteControl NET_DVR_REMOTECONTROL_PRESETPOINT");
		AfxMessageBox("预置点设置成功!");
	}

	OnBtnGetPresetNum();
}

void CDlgIPCSpecial::OnBtnPtzUp() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	NET_DVR_REMOTECONTROL_PTZ_PARAM struRemoControl = {0};
	struRemoControl.dwSize = sizeof(struRemoControl);
	struRemoControl.dwChannel = m_dwPTZFishEyeChannelNum;
	struRemoControl.dwPTZCommand = TILT_UP;
	struRemoControl.dwSpeed = m_comboFishEyeSpeedControl.GetCurSel();
	struRemoControl.dwStop = m_comboFishEyeStartStop.GetCurSel();
	struRemoControl.struVcaPoint.fX = m_struPoint.fX;
	struRemoControl.struVcaPoint.fY = m_struPoint.fY;
	if (!NET_DVR_RemoteControl(m_lServerID, NET_DVR_REMOTECONTROL_PTZ, &struRemoControl, sizeof(struRemoControl)))
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_RemoteControl NET_DVR_REMOTECONTROL_PTZ TILT_UP");
		return;
	}
	else
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_RemoteControl NET_DVR_REMOTECONTROL_PTZ TILT_UP");
	}
}

void CDlgIPCSpecial::OnBtnPtzLeft() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	NET_DVR_REMOTECONTROL_PTZ_PARAM struRemoControl = {0};
	struRemoControl.dwSize = sizeof(struRemoControl);
	struRemoControl.dwChannel = m_dwPTZFishEyeChannelNum;
	struRemoControl.dwPTZCommand = PAN_LEFT;
	struRemoControl.dwSpeed = m_comboFishEyeSpeedControl.GetCurSel();
	struRemoControl.dwStop = m_comboFishEyeStartStop.GetCurSel();
	struRemoControl.struVcaPoint.fX = m_struPoint.fX;
	struRemoControl.struVcaPoint.fY = m_struPoint.fY;
	if (!NET_DVR_RemoteControl(m_lServerID, NET_DVR_REMOTECONTROL_PTZ, &struRemoControl, sizeof(struRemoControl)))
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_RemoteControl NET_DVR_REMOTECONTROL_PTZ PAN_LEFT");
		return;
	}
	else
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_RemoteControl NET_DVR_REMOTECONTROL_PTZ PAN_LEFT");
	}	
}

void CDlgIPCSpecial::OnBtnPtzRight() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	NET_DVR_REMOTECONTROL_PTZ_PARAM struRemoControl = {0};
	struRemoControl.dwSize = sizeof(struRemoControl);
	struRemoControl.dwChannel = m_dwPTZFishEyeChannelNum;
	struRemoControl.dwPTZCommand = PAN_RIGHT;
	struRemoControl.dwSpeed = m_comboFishEyeSpeedControl.GetCurSel();
	struRemoControl.dwStop = m_comboFishEyeStartStop.GetCurSel();
	struRemoControl.struVcaPoint.fX = m_struPoint.fX;
	struRemoControl.struVcaPoint.fY = m_struPoint.fY;
	if (!NET_DVR_RemoteControl(m_lServerID, NET_DVR_REMOTECONTROL_PTZ, &struRemoControl, sizeof(struRemoControl)))
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_RemoteControl NET_DVR_REMOTECONTROL_PTZ PAN_RIGHT");
		return;
	}
	else
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_RemoteControl NET_DVR_REMOTECONTROL_PTZ PAN_RIGHT");
	}
}

void CDlgIPCSpecial::OnBtnPtzDown() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	NET_DVR_REMOTECONTROL_PTZ_PARAM struRemoControl = {0};
	struRemoControl.dwSize = sizeof(struRemoControl);
	struRemoControl.dwChannel = m_dwPTZFishEyeChannelNum;
	struRemoControl.dwPTZCommand = TILT_DOWN;
	struRemoControl.dwSpeed = m_comboFishEyeSpeedControl.GetCurSel();
	struRemoControl.dwStop = m_comboFishEyeStartStop.GetCurSel();
	struRemoControl.struVcaPoint.fX = m_struPoint.fX;
	struRemoControl.struVcaPoint.fY = m_struPoint.fY;
	if (!NET_DVR_RemoteControl(m_lServerID, NET_DVR_REMOTECONTROL_PTZ, &struRemoControl, sizeof(struRemoControl)))
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_RemoteControl NET_DVR_REMOTECONTROL_PTZ TILT_DOWN");
		return;
	}
	else
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_RemoteControl NET_DVR_REMOTECONTROL_PTZ TILT_DOWN");
	}
}

void CDlgIPCSpecial::OnBtnPtzBig() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	NET_DVR_REMOTECONTROL_PTZ_PARAM struRemoControl = {0};
	struRemoControl.dwSize = sizeof(struRemoControl);
	struRemoControl.dwChannel = m_dwPTZFishEyeChannelNum;
	struRemoControl.dwPTZCommand = ZOOM_IN;
	struRemoControl.dwSpeed = m_comboFishEyeSpeedControl.GetCurSel();
	struRemoControl.dwStop = m_comboFishEyeStartStop.GetCurSel();
	struRemoControl.struVcaPoint.fX = m_struPoint.fX;
	struRemoControl.struVcaPoint.fY = m_struPoint.fY;
	if (!NET_DVR_RemoteControl(m_lServerID, NET_DVR_REMOTECONTROL_PTZ, &struRemoControl, sizeof(struRemoControl)))
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_RemoteControl NET_DVR_REMOTECONTROL_PTZ ZOOM_IN");
		return;
	}
	else
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_RemoteControl NET_DVR_REMOTECONTROL_PTZ ZOOM_IN");
	}
}

void CDlgIPCSpecial::OnBtnPtzNarrow() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	NET_DVR_REMOTECONTROL_PTZ_PARAM struRemoControl = {0};
	struRemoControl.dwSize = sizeof(struRemoControl);
	struRemoControl.dwChannel = m_dwPTZFishEyeChannelNum;
	struRemoControl.dwPTZCommand = ZOOM_OUT;
	struRemoControl.dwSpeed = m_comboFishEyeSpeedControl.GetCurSel();
	struRemoControl.dwStop = m_comboFishEyeStartStop.GetCurSel();
	struRemoControl.struVcaPoint.fX = m_struPoint.fX;
	struRemoControl.struVcaPoint.fY = m_struPoint.fY;
	if (!NET_DVR_RemoteControl(m_lServerID, NET_DVR_REMOTECONTROL_PTZ, &struRemoControl, sizeof(struRemoControl)))
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_RemoteControl NET_DVR_REMOTECONTROL_PTZ ZOOM_OUT");
		return;
	}
	else
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_RemoteControl NET_DVR_REMOTECONTROL_PTZ ZOOM_OUT");
	}
}

void CDlgIPCSpecial::OnBtnPtzAuto() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	NET_DVR_REMOTECONTROL_PTZ_PARAM struRemoControl= {0};
	struRemoControl.dwSize = sizeof(struRemoControl);
	struRemoControl.dwChannel = m_dwPTZFishEyeChannelNum;
	struRemoControl.dwPTZCommand = PAN_AUTO;
	struRemoControl.dwSpeed = m_comboFishEyeSpeedControl.GetCurSel();
	struRemoControl.dwStop = m_comboFishEyeStartStop.GetCurSel();
	struRemoControl.struVcaPoint.fX = m_struPoint.fX;
	struRemoControl.struVcaPoint.fY = m_struPoint.fY;
	if (!NET_DVR_RemoteControl(m_lServerID, NET_DVR_REMOTECONTROL_PTZ, &struRemoControl, sizeof(struRemoControl)))
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_RemoteControl NET_DVR_REMOTECONTROL_PTZ PAN_AUTO");
		return;
	}
	else
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_RemoteControl NET_DVR_REMOTECONTROL_PTZ PAN_AUTO");
	}
}

void CDlgIPCSpecial::OnBtnPtzCircle() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	NET_DVR_REMOTECONTROL_PTZ_PARAM struRemoControl={0};
	struRemoControl.dwSize = sizeof(struRemoControl);
	struRemoControl.dwChannel = m_dwPTZFishEyeChannelNum;
	struRemoControl.dwPTZCommand = PAN_CIRCLE;
	struRemoControl.dwSpeed = m_comboFishEyeSpeedControl.GetCurSel();
	struRemoControl.dwStop = m_comboFishEyeStartStop.GetCurSel();
	struRemoControl.struVcaPoint.fX = m_struPoint.fX;
	struRemoControl.struVcaPoint.fY = m_struPoint.fY;
	if (!NET_DVR_RemoteControl(m_lServerID, NET_DVR_REMOTECONTROL_PTZ, &struRemoControl, sizeof(struRemoControl)))
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_RemoteControl NET_DVR_REMOTECONTROL_PTZ PAN_CIRCLE");
		return;
	}
	else
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_RemoteControl NET_DVR_REMOTECONTROL_PTZ PAN_CIRCLE");
	}
}

void CDlgIPCSpecial::OnBtnFePtzClean() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	char szLan[128] = {0};
	NET_DVR_PRESET_POINT_PARAM struRresetPoint = {0};
	struRresetPoint.dwSize = sizeof(struRresetPoint);
	struRresetPoint.dwChannel = m_dwFEChannelNum;
	struRresetPoint.dwPresetIndex = m_comboPresetNum.GetCurSel();
	struRresetPoint.dwPTZPresetCmd = CLE_PRESET;
	struRresetPoint.struVcaPoint.fX = m_struPoint.fX;
	struRresetPoint.struVcaPoint.fY = m_struPoint.fY;
	if (!NET_DVR_RemoteControl(m_lServerID, NET_DVR_REMOTECONTROL_PRESETPOINT, &struRresetPoint, sizeof(struRresetPoint)))
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_RemoteControl NET_DVR_REMOTECONTROL_PRESETPOINT");
		return;
	}
	else
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_RemoteControl NET_DVR_REMOTECONTROL_PRESETPOINT");
		g_StringLanType(szLan, "清除成功!", "Clear success");
        AfxMessageBox(szLan);
	}	
	OnBtnGetPresetNum();
}

void CDlgIPCSpecial::OnBtnFePtzTurn() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	NET_DVR_PRESET_POINT_PARAM struRresetPoint= {0};
	struRresetPoint.dwSize = sizeof(struRresetPoint);
	struRresetPoint.dwChannel = m_dwFEChannelNum;
	struRresetPoint.dwPresetIndex = m_comboPresetNum.GetCurSel();
	struRresetPoint.dwPTZPresetCmd = GOTO_PRESET;
	struRresetPoint.struVcaPoint.fX = m_struPoint.fX;
	struRresetPoint.struVcaPoint.fY = m_struPoint.fY;
	if (!NET_DVR_RemoteControl(m_lServerID, NET_DVR_REMOTECONTROL_PRESETPOINT, &struRresetPoint, sizeof(struRresetPoint)))
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_RemoteControl NET_DVR_REMOTECONTROL_PRESETPOINT");
		return;
	}
	else
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_RemoteControl NET_DVR_REMOTECONTROL_PRESETPOINT");
	}	
}

void CDlgIPCSpecial::OnBtnFeCruiseSet() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	char szLan[128] = {0};
	NET_DVR_PTZ_CRUISE_PARAM struPTZCruise= {0};
	struPTZCruise.dwSize = sizeof(struPTZCruise);
	struPTZCruise.dwChannel = 1;
	struPTZCruise.dwPTZCruiseCmd = FILL_PRE_SEQ;
	struPTZCruise.struVcaPoint.fX = m_struPoint.fX;
	struPTZCruise.struVcaPoint.fY = m_struPoint.fY;
	struPTZCruise.wCruisePoint = m_comboCruisePoint.GetCurSel();//巡航点
    struPTZCruise.wCruiseRoute = m_comboCruiseRoute.GetCurSel();//巡航路径
	struPTZCruise.wInput = m_comboCurisePreset.GetItemData(m_comboCurisePreset.GetCurSel());


	if (!NET_DVR_RemoteControl(m_lServerID, NET_DVR_REMOTECONTROL_CRUISE, &struPTZCruise, sizeof(struPTZCruise)))
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_RemoteControl NET_DVR_REMOTECONTROL_CRUISE FILL_PRE_SEQ");
        g_StringLanType(szLan, "巡航路径设置失败!", "The cruise path set failed!");
        AfxMessageBox(szLan);
		return;
	}
	else
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_RemoteControl NET_DVR_REMOTECONTROL_CRUISE FILL_PRE_SEQ");

        struPTZCruise.wInput = m_comboCuriseTime.GetCurSel() + 1;
		struPTZCruise.dwPTZCruiseCmd = SET_SEQ_DWELL;
		if (NET_DVR_RemoteControl(m_lServerID, NET_DVR_REMOTECONTROL_CRUISE, &struPTZCruise, sizeof(struPTZCruise)))
		{
            g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_RemoteControl NET_DVR_REMOTECONTROL_CRUISE SET_SEQ_DWELL");

			struPTZCruise.wInput = m_comboCruiseSpeed.GetCurSel() + 1;
		    struPTZCruise.dwPTZCruiseCmd = SET_SEQ_SPEED;
			if (NET_DVR_RemoteControl(m_lServerID, NET_DVR_REMOTECONTROL_CRUISE, &struPTZCruise, sizeof(struPTZCruise)))
			{
				g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_RemoteControl NET_DVR_REMOTECONTROL_CRUISE SET_SEQ_SPEED");
				g_StringLanType(szLan, "巡航路径设置成功!", "The cruise path set successed!");
				AfxMessageBox(szLan);
			}
		}
	}
	OnBtnGetPtzcruiseNum();
	UpdateData(FALSE);
}

void CDlgIPCSpecial::OnBtnFeCruiseDel() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	char szLan[128] = {0};
	NET_DVR_PTZ_CRUISE_PARAM struPTZCruise= {0};
	struPTZCruise.dwSize = sizeof(struPTZCruise);
	struPTZCruise.dwChannel = 1;
	struPTZCruise.dwPTZCruiseCmd = CLE_PRE_SEQ;
	struPTZCruise.struVcaPoint.fX = m_struPoint.fX;
	struPTZCruise.struVcaPoint.fY = m_struPoint.fY;
	struPTZCruise.wCruisePoint = m_comboCruisePoint.GetCurSel();//巡航点
    struPTZCruise.wCruiseRoute = m_comboCruiseRoute.GetCurSel();//巡航路径
	struPTZCruise.wInput = m_comboCurisePreset.GetCurSel();

	if (!NET_DVR_RemoteControl(m_lServerID, NET_DVR_REMOTECONTROL_CRUISE, &struPTZCruise, sizeof(struPTZCruise)))
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_RemoteControl NET_DVR_REMOTECONTROL_CRUISE CLE_PRE_SEQ");
		return;
	}
	else
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_RemoteControl NET_DVR_REMOTECONTROL_CRUISE CLE_PRE_SEQ");
		g_StringLanType(szLan, "删除巡航点成功!", "The cruise path del failed!");
        AfxMessageBox(szLan);
	}
}

void CDlgIPCSpecial::OnBtnFeCruiseRun() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	NET_DVR_PTZ_CRUISE_PARAM struPTZCruise={0};
	struPTZCruise.dwSize = sizeof(struPTZCruise);
	struPTZCruise.dwChannel = m_dwFEChannelNum;
	struPTZCruise.dwPTZCruiseCmd = RUN_SEQ;
	struPTZCruise.struVcaPoint.fX = m_struPoint.fX;
	struPTZCruise.struVcaPoint.fY = m_struPoint.fY;
	struPTZCruise.wCruisePoint = m_comboCruisePoint.GetCurSel();//巡航点
    struPTZCruise.wCruiseRoute = m_comboCruiseRoute.GetCurSel();//巡航路径
	struPTZCruise.wInput = m_comboCurisePreset.GetCurSel();

	if (!NET_DVR_RemoteControl(m_lServerID, NET_DVR_REMOTECONTROL_CRUISE, &struPTZCruise, sizeof(struPTZCruise)))
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_RemoteControl NET_DVR_REMOTECONTROL_CRUISE RUN_SEQ");
		return;
	}
	else
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_RemoteControl NET_DVR_REMOTECONTROL_CRUISE RUN_SEQ");
	}
}

void CDlgIPCSpecial::OnBtnFeCruiseStop() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	NET_DVR_PTZ_CRUISE_PARAM struPTZCruise = {0};
	struPTZCruise.dwSize = sizeof(struPTZCruise);
	struPTZCruise.dwChannel = m_dwFEChannelNum;
	struPTZCruise.dwPTZCruiseCmd = STOP_SEQ;
	struPTZCruise.struVcaPoint.fX = m_struPoint.fX;
	struPTZCruise.struVcaPoint.fY = m_struPoint.fY;
	struPTZCruise.wCruisePoint = m_comboCruisePoint.GetCurSel();//巡航点
    struPTZCruise.wCruiseRoute = m_comboCruiseRoute.GetCurSel();//巡航路径
	struPTZCruise.wInput = m_comboCurisePreset.GetCurSel();
	
	if (!NET_DVR_RemoteControl(m_lServerID, NET_DVR_REMOTECONTROL_CRUISE, &struPTZCruise, sizeof(struPTZCruise)))
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_RemoteControl NET_DVR_REMOTECONTROL_CRUISE STOP_SEQ");
		return;
	}
	else
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_RemoteControl NET_DVR_REMOTECONTROL_CRUISE STOP_SEQ");
	}
}

/*************************************************
函数名:    	~CDlgIPCSpecial
函数描述:	析构函数
输入参数:   
无
输出参数: 无  			
返回值:		
无
*************************************************/
CDlgIPCSpecial::~CDlgIPCSpecial()
{
	if (m_lPlayHandle >= 0)
	{
		NET_DVR_RigisterDrawFun(m_lPlayHandle,NULL, 0);
		NET_DVR_StopRealPlay(m_lPlayHandle);
		m_lPlayHandle = -1;
	}
}


BOOL CDlgIPCSpecial::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	CPoint pt(0,0);
    GetDlgItem(IDC_PLAYWND_PTZ)->GetWindowRect(&m_rcWnd);
    GetCursorPos(&pt);
	ScreenToClient(&m_rcWnd);
	ScreenToClient(&pt);
    CString strTemp = _T("");
    DWORD i=0;
    BOOL bOneLine = TRUE,bXOneLine = TRUE,bYOneLine = TRUE;
    
    switch(pMsg->message)  // Message of Draw
    {
    case WM_LBUTTONDOWN:
        if( (GetAsyncKeyState(VK_LCONTROL)<0 || GetAsyncKeyState(VK_RCONTROL)<0))//Press CTRL to draw
        {
			if(PtInRect(&m_rcWnd,pt))
			{
				m_struPoint.fX = (float)(pt.x-m_rcWnd.left)/(float)m_rcWnd.Width();
				m_struPoint.fY = (float)(pt.y-m_rcWnd.top)/(float)m_rcWnd.Height();
			}
		}
		break;
	default:
		break;
	}
	return CDialog::PreTranslateMessage(pMsg);
}

void CDlgIPCSpecial::OnBtnGetPresetNum() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	DWORD dwReturn;
	char szLan[128] = {0};
	NET_DVR_PRESET_INFO strPrsetinfo = {0};
	if (!NET_DVR_GetDVRConfig(m_lServerID,  NET_DVR_GET_PRESET_NUM, 1, &strPrsetinfo, sizeof(strPrsetinfo), &dwReturn))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, " NET_DVR_GET_PRESET_NUM Fail");
        g_StringLanType(szLan, "获取预置点个数失败", "Fail to get Preset Num");
        AfxMessageBox(szLan);
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, " NET_DVR_GET_PRESET_NUM Success");
    }
	m_iPresetNum = strPrsetinfo.dwPresetNum;
	m_iPresetGroupNum = strPrsetinfo.dwGroupNum;

	m_iPtzPresetNum = strPrsetinfo.dwPresetNum;

	UpdateData(FALSE);	
}

void CDlgIPCSpecial::OnBtnGetPtzcruiseNum() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	DWORD dwReturn;
	char szLan[128] = {0};
	NET_DVR_PTZCRUISE_INFO strPtzCruiseinfo = {0};
	if (!NET_DVR_GetDVRConfig(m_lServerID,  NET_DVR_GET_PTZCRUISE_NUM, 1, &strPtzCruiseinfo, sizeof(strPtzCruiseinfo), &dwReturn))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, " NET_DVR_GET_PTZCRUISE_NUM Fail");
        g_StringLanType(szLan, "获取巡航路径个数失败", "Fail to get PTZCRUISE Num");
        AfxMessageBox(szLan);
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, " NET_DVR_GET_PTZCRUISE_NUM Success");
    }
	m_iPtzCruiseNum = strPtzCruiseinfo.dwPtzCruiseNum;
	m_iPreCruiseGroupNum = strPtzCruiseinfo.dwGroupNum;
	
	UpdateData(FALSE);
}

void CDlgIPCSpecial::OnBtnGetpresetInfo() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	DWORD dwReturn = 0;
	char szLan[128] = {0};
	char szTemp[256] = {0};
	int i = 0;
	DWORD dwStatus = 0;
	CString   strTextPresetIndex; 
	CString   strTextPresetfx; 
	CString   strTextPresetfy; 
	BOOL bRet = FALSE;

	LPNET_DVR_PRESET_COND pstrPresetCond = NULL;
//	LPNET_DVR_PRESET_COND pstrPresetCondTemp = NULL;

	LPNET_DVR_PRESET_COND pstrPresetCondSecond = NULL;
//	LPNET_DVR_PRESET_COND pstrPresetCondSecondTemp = NULL;

	LPNET_DVR_PRESETCFG pPresetcfg = NULL;
	LPNET_DVR_PRESETCFG pPresetcfgTemp = NULL;
	LPNET_DVR_PRESETCFG pPresetSecondcfg = NULL;
    
	if (1 == m_iPresetGetGroupNum)
	{
// 		pstrPresetCond = new NET_DVR_PRESET_COND[m_iPtzPresetNum];
// 		if (NULL == pstrPresetCond)
// 		{
// 			g_StringLanType(szLan,"申请内存失败","new memory failed");
// 			AfxMessageBox(szLan);
// 			return;
// 		}
// 		memset(pstrPresetCond, 0, m_iPtzPresetNum*sizeof(NET_DVR_PRESET_COND));
// 
// 		pstrPresetCond->dwChannel = m_iPresetChannel;
// 		pstrPresetCond->dwSize = sizeof(NET_DVR_PRESET_COND);
// 		pstrPresetCond->dwGroupNO = m_iPresetGetGroupNum;

		NET_DVR_PRESET_COND strPresetCond = {0};
		strPresetCond.dwSize = sizeof(NET_DVR_PRESET_COND);
		strPresetCond.dwChannel = m_iPresetChannel;
		strPresetCond.dwGroupNO = m_iPresetGetGroupNum;
 
		if (0 == m_iPtzPresetNum)
		{
			m_listGetPresetInfo.DeleteAllItems();
			g_StringLanType(szLan, "没有预置点可以获取!", "No preset points can get");
			AfxMessageBox(szLan);
		}
		pPresetcfg = new NET_DVR_PRESETCFG[m_iPtzPresetNum];
		if (NULL == pPresetcfg)
		{
			g_StringLanType(szLan,"申请内存失败","new memory failed");
			AfxMessageBox(szLan);
			return;
		}
		memset(pPresetcfg, 0, m_iPtzPresetNum*sizeof(NET_DVR_PRESETCFG));
		//pPresetcfgTemp = pPresetcfg;
		DWORD *pStatus = new DWORD[m_iPtzPresetNum];
		memset(pStatus, 0, sizeof(DWORD)*m_iPtzPresetNum);

		bRet = NET_DVR_GetDeviceConfig(m_lServerID, NET_DVR_GET_PRESETCFG, m_iPtzPresetNum, &strPresetCond, sizeof(NET_DVR_PRESET_COND), pStatus, pPresetcfg, m_iPtzPresetNum*sizeof(NET_DVR_PRESETCFG));
		if (bRet && (NULL == pStatus))
		{
			g_StringLanType(szLan, "获取预置点信息失败", "Get video preset info configuration failed");
			sprintf(szTemp, "%s %s", szLan, NET_DVR_GetErrorMsg());
			AfxMessageBox(szTemp);
//			delete [] pstrPresetCond;s
			delete [] pStatus;
			delete [] pPresetcfg;

			return ;
		}
		pPresetcfgTemp = pPresetcfg;
		if (TRUE == bRet)
		{
			m_listGetPresetInfo.DeleteAllItems();	
			for(i = 0; i < m_iPtzPresetNum; i++)
			{
// 				if (pPresetcfg->dwPresetIndex != 0)
// 				{
				    
					m_listGetPresetInfo.InsertItem(i, "", -1);	
					strTextPresetIndex.Format("%d", (pPresetcfgTemp->dwPresetIndex + 1));
					strTextPresetfx.Format("%f", pPresetcfgTemp->struVcaPoint.fX);
					strTextPresetfy.Format("%f", pPresetcfgTemp->struVcaPoint.fY);
					
					m_listGetPresetInfo.SetItemText(i, 1, strTextPresetIndex);
					m_listGetPresetInfo.SetItemText(i, 2, strTextPresetfx);
					m_listGetPresetInfo.SetItemText(i, 3, strTextPresetfy);				
/*				}*/
				//pPresetcfg = pPresetcfg + sizeof(NET_DVR_PRESETCFG);
					pPresetcfgTemp++;
			}
//			delete [] pstrPresetCond;
			delete [] pStatus;
			delete [] pPresetcfg;
		}

	}

	if (2 == m_iPresetGetGroupNum)
	{
		int m_ipresetgrp = 0;
		if (m_iPtzPresetNum <= 64)
		{
			m_ipresetgrp = 0;
		} 
		else
		{
			m_ipresetgrp = m_iPtzPresetNum - 64;
		}
		
// 		pstrPresetCond = new NET_DVR_PRESET_COND[64];
// 		if (NULL == pstrPresetCond)
// 		{
// 			g_StringLanType(szLan,"申请内存失败","new memory failed");
// 			AfxMessageBox(szLan);
// 			return;
// 		}
// 		memset(pstrPresetCond, 0, 64*sizeof(NET_DVR_PRESET_COND));
// 
// 		pstrPresetCond->dwChannel = m_iPresetChannel;
// 		pstrPresetCond->dwSize = sizeof(NET_DVR_PRESET_COND);
// 		pstrPresetCond->dwGroupNO = m_iPresetGetGroupNum;

		NET_DVR_PRESET_COND strPresetCond = {0};
		strPresetCond.dwSize = sizeof(NET_DVR_PRESET_COND);
		strPresetCond.dwChannel = m_iPresetChannel;
		strPresetCond.dwGroupNO = m_iPresetGetGroupNum;

		pPresetcfg = new NET_DVR_PRESETCFG[64];
		if (NULL == pPresetcfg)
		{
			g_StringLanType(szLan,"申请内存失败","new memory failed");
			AfxMessageBox(szLan);
			return;
		}
		memset(pPresetcfg, 0, 64*sizeof(NET_DVR_PRESETCFG));
		pPresetcfgTemp = pPresetcfg;
		
		DWORD *pStatus = new DWORD[64];
		memset(pStatus, 0, sizeof(DWORD)*64);
		
		bRet = NET_DVR_GetDeviceConfig(m_lServerID, NET_DVR_GET_PRESETCFG, 64, &strPresetCond, sizeof(NET_DVR_PRESETCFG), pStatus, pPresetcfg, 64*sizeof(NET_DVR_PRESETCFG));
		if (bRet && (NULL == pStatus))
		{
			g_StringLanType(szLan, "获取预置点信息失败", "Get video preset info configuration failed");
			sprintf(szTemp, "%s %s", szLan, NET_DVR_GetErrorMsg());
			AfxMessageBox(szTemp);			
//			delete [] pstrPresetCond;
			delete [] pPresetcfg;
			delete [] pStatus;
			return;
		}
		
		if (TRUE == bRet)
		{
//			m_listGetPresetInfo.InsertItem(0, "", -1);
			for(i = 0; i < 64; i++)
			{
// 				if (pPresetcfg->dwPresetIndex != 0)
// 				{
					m_listGetPresetInfo.InsertItem(i, "", -1);
					strTextPresetIndex.Format("%d", (pPresetcfgTemp->dwPresetIndex + 1));
					strTextPresetfx.Format("%d", pPresetcfg->struVcaPoint.fX);
					strTextPresetfy.Format("%d", pPresetcfg->struVcaPoint.fY);
					
					m_listGetPresetInfo.SetItemText(i, 1, strTextPresetIndex);
					m_listGetPresetInfo.SetItemText(i, 2, strTextPresetfx);
					m_listGetPresetInfo.SetItemText(i, 3, strTextPresetfy);	
					pPresetcfgTemp ++;
/*				}*/
			}
//			delete [] pstrPresetCond;
			delete [] pPresetcfg;
			delete [] pStatus;
		}

		if (0 != m_ipresetgrp)
		{
// 			pstrPresetCondSecond = new NET_DVR_PRESET_COND[m_ipresetgrp];
// 			if (NULL == pstrPresetCondSecond)
// 			{
// 				g_StringLanType(szLan,"申请内存失败","new memory failed");
// 				AfxMessageBox(szLan);
// 				return;
// 			}
// 			memset(pstrPresetCondSecond, 0, m_ipresetgrp*sizeof(NET_DVR_PRESET_COND));
// 			
// 			pstrPresetCondSecond->dwChannel = m_iPresetChannel;
// 			pstrPresetCondSecond->dwSize = sizeof(NET_DVR_PRESET_COND);
// 			pstrPresetCondSecond->dwGroupNO = m_iPresetGetGroupNum;
			
			pPresetSecondcfg = new NET_DVR_PRESETCFG[m_ipresetgrp];
			if (NULL == pPresetSecondcfg)
			{
				g_StringLanType(szLan,"申请内存失败","new memory failed");
				AfxMessageBox(szLan);
				return;
			}
			memset(pPresetSecondcfg, 0, m_ipresetgrp*sizeof(NET_DVR_PRESETCFG));
			pPresetcfgTemp = pPresetcfg;	
			
			DWORD *pStatusSecond = new DWORD[m_ipresetgrp];
			memset(pStatusSecond, 0, sizeof(DWORD)*m_ipresetgrp);
			
			bRet = NET_DVR_GetDeviceConfig(m_lServerID, NET_DVR_GET_PRESETCFG, m_ipresetgrp, &strPresetCond, sizeof(NET_DVR_PRESETCFG), pStatusSecond,\
				pPresetSecondcfg, m_ipresetgrp*sizeof(NET_DVR_PRESETCFG)); 
			if (bRet/* && (NULL == pStatusSecond)*/)
			{
				g_StringLanType(szLan, "获取预置点信息失败", "Get video preset info configuration failed");
				sprintf(szTemp, "%s %s", szLan, NET_DVR_GetErrorMsg());
				AfxMessageBox(szTemp);

//				delete [] pstrPresetCondSecond;
				delete [] pPresetSecondcfg;
				delete [] pStatusSecond;
				return;
			}
			
			if (TRUE == bRet)
			{
				for(i = 0; i < m_ipresetgrp; i++)
				{
// 					if (pPresetcfg->dwPresetIndex != 0)
// 					{
						m_listGetPresetInfo.InsertItem(i, "", -1);
						strTextPresetIndex.Format("%d", (pPresetcfgTemp->dwPresetIndex + 1));
						strTextPresetfx.Format("%d", pPresetSecondcfg->struVcaPoint.fX);
						strTextPresetfy.Format("%d", pPresetSecondcfg->struVcaPoint.fY);
						
						m_listGetPresetInfo.SetItemText(i, 1, strTextPresetIndex);
						m_listGetPresetInfo.SetItemText(i, 2, strTextPresetfx);
						m_listGetPresetInfo.SetItemText(i, 3, strTextPresetfy);				
/*					}*/
				}
//				delete [] pstrPresetCondSecond;
				delete [] pPresetSecondcfg;
				delete [] pStatusSecond;
			}
		}
	}
	UpdateData(FALSE);
}

void CDlgIPCSpecial::OnBtnGetcruiseInfo() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	DWORD dwReturn = 0;
	char szLan[128] = {0};
	char szTemp[256] = {0};
	int i = 0;
	int j = 0;
	CString   strTextPtzCruiseIndex;
	CString   strTextPtzCruisepoint;
	CString   strTextPresetIndex; 
	CString   strTextPresetfx; 
	CString   strTextPresetfy; 
	CString   strTextDwell;		
	CString   strTextSpeed;

	BOOL bRet = FALSE;
	LPNET_DVR_PTZCRUISECFG pPtzCuisePointCfg = NULL;
	LPNET_DVR_PTZCRUISECFG pPtzCuisePointCfgSecond =  NULL;

	LPNET_DVR_PTZCRUISECFG pPtzCuisePointCfgTemp = NULL;

	NET_DVR_PTZCRUISE_COND strPtzCruiseCond = {0};                        //只发送一个控制结构体
	strPtzCruiseCond.dwChannel = 1 /*m_iPreCruiseChannel*/;
	strPtzCruiseCond.dwGroupNO = m_iPreGetCruiseGroupNum;
	strPtzCruiseCond.dwSize = sizeof(strPtzCruiseCond);

	if (0 == m_iPtzCruiseNum)
	{
		m_listGetPreCruiseiInfo.DeleteAllItems();
        g_StringLanType(szLan, "没有巡航路径可以获取!", "No cruise path can get!");
        AfxMessageBox(szLan);
	}

	pPtzCuisePointCfg = new NET_DVR_PTZCRUISECFG[m_iPtzCruiseNum];  //分配接受内存(返回为多个结构体)
	if (NULL == pPtzCuisePointCfg)
	{
		g_StringLanType(szLan,"申请内存失败","new memory failed");
		AfxMessageBox(szLan);
		return;
	}
	memset(pPtzCuisePointCfg, 0, m_iPtzCruiseNum*sizeof(NET_DVR_PTZCRUISECFG));

	DWORD *pStatus = new DWORD[m_iPtzCruiseNum];
	memset(pStatus, 0, m_iPtzCruiseNum*sizeof(DWORD));

	if (1 == m_iPreGetCruiseGroupNum)
	{
		bRet = NET_DVR_GetDeviceConfig(m_lServerID, NET_DVR_GET_PTZCRUISECFG, m_iPtzCruiseNum, &strPtzCruiseCond, sizeof(NET_DVR_PTZCRUISE_COND), pStatus, pPtzCuisePointCfg, m_iPtzCruiseNum*sizeof(NET_DVR_PTZCRUISECFG));
		if (bRet && (NULL == pStatus))
		{
			g_StringLanType(szLan, "获取巡航路径信息失败", "Get Video PtzCruise Info Configuration failed");
			sprintf(szTemp, "%s %s", szLan, NET_DVR_GetErrorMsg());
			AfxMessageBox(szTemp);
			delete [] pPtzCuisePointCfg;
			delete [] pStatus;
			return;
		}
		pPtzCuisePointCfgTemp = pPtzCuisePointCfg;
		if (TRUE == bRet)
		{
			m_listGetPreCruiseiInfo.DeleteAllItems();
			for(j = 0; j < m_iPtzCruiseNum; j++)
			{
				for (i = 0;i < 32;i++)
				{
					if (pPtzCuisePointCfgTemp->struCruisePoint[i].dwPresetIndex != 255)
					{
						m_listGetPreCruiseiInfo.InsertItem(i, "", -1);
						strTextPtzCruiseIndex.Format("%d", (pPtzCuisePointCfgTemp->dwCruiseRoute + 1));
						strTextPtzCruisepoint.Format("%d", i + 1);
						strTextPresetIndex.Format("%d",(pPtzCuisePointCfgTemp->struCruisePoint[i].dwPresetIndex + 1));
						strTextPresetfx.Format("%f", pPtzCuisePointCfgTemp->struCruisePoint[i].struVcaPoint.fX);
						strTextPresetfy.Format("%f", pPtzCuisePointCfgTemp->struCruisePoint[i].struVcaPoint.fY);
						strTextDwell.Format("%d", pPtzCuisePointCfgTemp->struCruisePoint[i].byDwell);
						strTextSpeed.Format("%d", pPtzCuisePointCfgTemp->struCruisePoint[i].bySpeed);

						m_listGetPreCruiseiInfo.SetItemText(i, 1, strTextPtzCruiseIndex);
						m_listGetPreCruiseiInfo.SetItemText(i, 2, strTextPtzCruisepoint);
						m_listGetPreCruiseiInfo.SetItemText(i, 3, strTextPresetIndex);
						m_listGetPreCruiseiInfo.SetItemText(i, 4, strTextPresetfx);
						m_listGetPreCruiseiInfo.SetItemText(i, 5, strTextPresetfy);
						m_listGetPreCruiseiInfo.SetItemText(i, 6, strTextDwell);
						m_listGetPreCruiseiInfo.SetItemText(i, 7, strTextSpeed);						
					}
				}
				pPtzCuisePointCfgTemp++;
			}
			delete [] pPtzCuisePointCfg;
			delete [] pStatus;
		
		}		
	}
	
	if (2 == m_iPreGetCruiseGroupNum)
	{
		int m_iPtzCruisegrp = 0;
		if (m_iPtzCruiseNum <= 32)
		{
			m_iPtzCruisegrp = 0;
		}
		else
		{
			m_iPtzCruisegrp = m_iPtzCruiseNum - 32;
		}

		pPtzCuisePointCfg = new NET_DVR_PTZCRUISECFG[32];  //分配接受内存(返回为多个结构体)
		if (NULL == pPtzCuisePointCfg)
		{
			g_StringLanType(szLan,"申请内存失败","new memory failed");
			AfxMessageBox(szLan);
			return;
		}
		memset(pPtzCuisePointCfg, 0, 32*sizeof(NET_DVR_PTZCRUISECFG));
		
		DWORD *pStatus = new DWORD[32];
		memset(pStatus, 0, 32*sizeof(DWORD));

		bRet = NET_DVR_GetDeviceConfig(m_lServerID, NET_DVR_GET_PTZCRUISECFG, 32, &strPtzCruiseCond, sizeof(strPtzCruiseCond), \
			pStatus, pPtzCuisePointCfg, 32*sizeof(NET_DVR_PTZCRUISECFG));

		if (bRet && (0 == pStatus))
		{
			g_StringLanType(szLan, "获取巡航路径信息失败", "Get video ptzcruise info configuration failed");
			sprintf(szTemp, "%s %s", szLan, NET_DVR_GetErrorMsg());
			AfxMessageBox(szTemp);
			delete [] pPtzCuisePointCfg;
			delete [] pStatus;
		}
		pPtzCuisePointCfgTemp = pPtzCuisePointCfg;
		if (TRUE == bRet)
		{
			for(i = 1; i <= 32; i++)
			{
				for (i = 0;i < 32;i++)
				{
					if (pPtzCuisePointCfgTemp->struCruisePoint[i].dwPresetIndex != 255)
					{
						m_listGetPreCruiseiInfo.InsertItem(0, "", -1);
						strTextPtzCruiseIndex.Format("%d", (pPtzCuisePointCfgTemp->dwCruiseRoute + 1));
						strTextPtzCruisepoint.Format("%d", i);
						strTextPresetIndex.Format("%d",(pPtzCuisePointCfgTemp->struCruisePoint[i].dwPresetIndex + 1));
						strTextPresetfx.Format("%f", pPtzCuisePointCfgTemp->struCruisePoint[i].struVcaPoint.fX);
						strTextPresetfy.Format("%f", pPtzCuisePointCfgTemp->struCruisePoint[i].struVcaPoint.fY);
						strTextDwell.Format("%d", pPtzCuisePointCfgTemp->struCruisePoint[i].byDwell);
						strTextSpeed.Format("%d", pPtzCuisePointCfgTemp->struCruisePoint[i].bySpeed);

						m_listGetPreCruiseiInfo.SetItemText(i, 1, strTextPtzCruiseIndex);
						m_listGetPreCruiseiInfo.SetItemText(i, 2, strTextPtzCruisepoint);
						m_listGetPreCruiseiInfo.SetItemText(i, 3, strTextPresetIndex);
						m_listGetPreCruiseiInfo.SetItemText(i, 4, strTextPresetfx);
						m_listGetPreCruiseiInfo.SetItemText(i, 5, strTextPresetfy);
						m_listGetPreCruiseiInfo.SetItemText(i, 6, strTextDwell);
						m_listGetPreCruiseiInfo.SetItemText(i, 7, strTextSpeed);						
					}
				}
				pPtzCuisePointCfgTemp++;
			}
			delete [] pPtzCuisePointCfg;
			delete [] pStatus;
		}
		
		if (0 != m_iPtzCruisegrp)
		{
			pPtzCuisePointCfgSecond = new NET_DVR_PTZCRUISECFG[m_iPtzCruisegrp];  //分配接受内存(返回为多个结构体)
			if (NULL == pPtzCuisePointCfgSecond)
			{
				g_StringLanType(szLan,"申请内存失败","new memory failed");
				AfxMessageBox(szLan);
				return;
			}
			memset(pPtzCuisePointCfgSecond, 0, m_iPtzCruisegrp*sizeof(NET_DVR_PTZCRUISECFG));
			
			DWORD *pStatus = new DWORD[m_iPtzCruisegrp];
			memset(pStatus, 0, m_iPtzCruisegrp*sizeof(DWORD));

			bRet = NET_DVR_GetDeviceConfig(m_lServerID, NET_DVR_GET_PTZCRUISECFG, m_iPtzCruisegrp, &strPtzCruiseCond, sizeof(strPtzCruiseCond), 
				pStatus, pPtzCuisePointCfgSecond, m_iPtzCruisegrp*sizeof(NET_DVR_PTZCRUISECFG));
			if (bRet && (NULL == pStatus))
			{
				g_StringLanType(szLan, "获取巡航路径信息失败", "Get video ptzcruise info configuration failed");
				sprintf(szTemp, "%s %s", szLan, NET_DVR_GetErrorMsg());
				AfxMessageBox(szTemp);
				delete [] pPtzCuisePointCfgSecond;
				delete [] pStatus;
				return;
			}
			
			if (TRUE == bRet)
			{
				for(i = 0; i < m_iPtzCruisegrp; i++)
				{
				for (i = 0;i < 32;i++)
				{
					if (pPtzCuisePointCfgTemp->struCruisePoint[i].dwPresetIndex != 255)
					{
						m_listGetPreCruiseiInfo.InsertItem(0, "", -1);
						strTextPtzCruiseIndex.Format("%d", (pPtzCuisePointCfgTemp->dwCruiseRoute + 1));
						strTextPtzCruisepoint.Format("%d", i);
						strTextPresetIndex.Format("%d",(pPtzCuisePointCfgTemp->struCruisePoint[i].dwPresetIndex + 1));
						strTextPresetfx.Format("%f", pPtzCuisePointCfgTemp->struCruisePoint[i].struVcaPoint.fX);
						strTextPresetfy.Format("%f", pPtzCuisePointCfgTemp->struCruisePoint[i].struVcaPoint.fY);
						strTextDwell.Format("%d", pPtzCuisePointCfgTemp->struCruisePoint[i].byDwell);
						strTextSpeed.Format("%d", pPtzCuisePointCfgTemp->struCruisePoint[i].bySpeed);

						m_listGetPreCruiseiInfo.SetItemText(i, 1, strTextPtzCruiseIndex);
						m_listGetPreCruiseiInfo.SetItemText(i, 2, strTextPtzCruisepoint);
						m_listGetPreCruiseiInfo.SetItemText(i, 3, strTextPresetIndex);
						m_listGetPreCruiseiInfo.SetItemText(i, 4, strTextPresetfx);
						m_listGetPreCruiseiInfo.SetItemText(i, 5, strTextPresetfy);
						m_listGetPreCruiseiInfo.SetItemText(i, 6, strTextDwell);
						m_listGetPreCruiseiInfo.SetItemText(i, 7, strTextSpeed);						
					}
				}
				pPtzCuisePointCfgTemp++;
				}
				delete [] pPtzCuisePointCfgSecond;
				delete [] pStatus;
			}
		}
	}
	UpdateData(FALSE);
}

void CDlgIPCSpecial::OnBtnMotionTrackSet() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	NET_DVR_MOTION_TRACK_CFG strMotionTtackCfg = {0};
	memset(&strMotionTtackCfg, 0, sizeof(strMotionTtackCfg));
	strMotionTtackCfg.dwSize = sizeof(strMotionTtackCfg);
	strMotionTtackCfg.byEnableTrack = m_comboMotionTrackSet.GetCurSel();


//	if (NET_DVR_RemoteControl(m_lServerID, NET_DVR_SET_MOTION_TRACK_CFG, &strMotionTtackCfg, sizeof(strMotionTtackCfg)))
	if (NET_DVR_SetDVRConfig(m_lServerID, NET_DVR_SET_MOTION_TRACK_CFG, 1, &strMotionTtackCfg, sizeof(strMotionTtackCfg)))
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_SET_MOTION_TRACK_CFG");
		return;
	}
	else
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_SET_MOTION_TRACK_CFG");
		return;
	}
	UpdateData(FALSE);
}

void CDlgIPCSpecial::OnBtnMotionTrackGet() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	DWORD dwReturn;
	char szLan[128] = {0};
	NET_DVR_MOTION_TRACK_CFG strMotionTtackCfg = {0};
	if (!NET_DVR_GetDVRConfig(m_lServerID,  NET_DVR_GET_MOTION_TRACK_CFG, 1, &strMotionTtackCfg, sizeof(strMotionTtackCfg), &dwReturn))

//	if (!NET_DVR_RemoteControl(m_lServerID, NET_DVR_GET_MOTION_TRACK_CFG, &strMotionTtackCfg, sizeof(strMotionTtackCfg)))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, " NET_DVR_GET_MOTION_TRACK_CFG Fail");
        g_StringLanType(szLan, "获取跟踪模式状态失败", "Fail to get motion track");
        AfxMessageBox(szLan);
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, " NET_DVR_GET_MOTION_TRACK_CFG Success");
    }
	m_comboMotionTrackGet.SetCurSel(strMotionTtackCfg.byEnableTrack);
	
	UpdateData(FALSE);
	
}

void CDlgIPCSpecial::OnBtnUpPreset() 
{
	// TODO: Add your control notification handler code here

	DWORD dwReturn = 0;
	char szLan[128] = {0};
	char szTemp[256] = {0};
	int i = 0;
	int m_iGroupNum = 0;
	DWORD dwStatus = 0;
	CString   strTemp;
	CString   strTextPresetIndex; 
	CString   strTextPresetfx; 
	CString   strTextPresetfy; 
	BOOL bRet = FALSE;

	LPNET_DVR_PRESET_COND pstrPresetCond = NULL;
	//	LPNET_DVR_PRESET_COND pstrPresetCondTemp = NULL;
	
	LPNET_DVR_PRESET_COND pstrPresetCondSecond = NULL;
	//	LPNET_DVR_PRESET_COND pstrPresetCondSecondTemp = NULL;
	
	LPNET_DVR_PRESETCFG pPresetcfg = NULL;
	LPNET_DVR_PRESETCFG pPresetcfgTemp = NULL;
	LPNET_DVR_PRESETCFG pPresetSecondcfg = NULL;

	if (m_iPtzCruiseNum <= 64)
	{
		m_iGroupNum = 1;
	}
	else
	{
		m_iGroupNum = 2;
	}

	NET_DVR_PRESET_COND strPresetCond = {0};
	strPresetCond.dwSize = sizeof(NET_DVR_PRESET_COND);
	strPresetCond.dwChannel = m_iPresetChannel;
	strPresetCond.dwGroupNO = m_iGroupNum;
	

// 		pPresetcfg = new NET_DVR_PRESETCFG[m_iPtzPresetNum];
// 		if (NULL == pPresetcfg)
// 		{
// 			g_StringLanType(szLan,"申请内存失败","new memory failed");
// 			AfxMessageBox(szLan);
// 			return;
// 		}
// 		memset(pPresetcfg, 0, m_iPtzPresetNum*sizeof(NET_DVR_PRESETCFG));
// 		DWORD *pStatus = new DWORD[m_iPtzPresetNum];
// 		memset(pStatus, 0, sizeof(DWORD)*m_iPtzPresetNum);
// 		
// 		bRet = NET_DVR_GetDeviceConfig(m_lServerID, NET_DVR_GET_PRESETCFG, m_iPtzPresetNum, &strPresetCond, sizeof(NET_DVR_PRESET_COND), pStatus, pPresetcfg, m_iPtzPresetNum*sizeof(NET_DVR_PRESETCFG));
// 		if (bRet && (NULL == pStatus))
// 		{
// 			g_StringLanType(szLan, "获取预置点信息失败", "Get video preset info configuration failed");
// 			sprintf(szTemp, "%s %s", szLan, NET_DVR_GetErrorMsg());
// 			AfxMessageBox(szTemp);
// 			delete [] pStatus;
// 			delete [] pPresetcfg;
// 			
// 			return ;
// 		}
// 		pPresetcfgTemp = pPresetcfg;
// 		if (TRUE == bRet)
// 		{
// 			m_comboCurisePreset.ResetContent();
// 			for(i = 0; i < m_iPtzPresetNum; i++)
// 			{
// 				
// 				strTemp.Format("%d", (pPresetcfgTemp->dwPresetIndex + 1));
// 				m_comboCurisePreset.AddString(strTemp);
// 				
// 				pPresetcfgTemp++;
// 			}			
// 			delete [] pStatus;
// 			delete [] pPresetcfg;
// 		}
	
    if (0 == m_iPtzPresetNum)
    {
        g_StringLanType(szLan, "没有预置点可以获取!", "No preset points can get");
        AfxMessageBox(szLan);
		m_comboCurisePreset.ResetContent();
    } 
    else
    {
			if (1 == m_iPresetGetGroupNum)
	{
		NET_DVR_PRESET_COND strPresetCond = {0};
		strPresetCond.dwSize = sizeof(NET_DVR_PRESET_COND);
		strPresetCond.dwChannel = m_iPresetChannel;
		strPresetCond.dwGroupNO = m_iPresetGetGroupNum;

		pPresetcfg = new NET_DVR_PRESETCFG[m_iPtzPresetNum];
		if (NULL == pPresetcfg)
		{
			g_StringLanType(szLan,"申请内存失败","new memory failed");
			AfxMessageBox(szLan);
			return;
		}
		memset(pPresetcfg, 0, m_iPtzPresetNum*sizeof(NET_DVR_PRESETCFG));
		DWORD *pStatus = new DWORD[m_iPtzPresetNum];
		memset(pStatus, 0, sizeof(DWORD)*m_iPtzPresetNum);

		//bRet = NET_DVR_GetDeviceConfig(m_lServerID, NET_DVR_GET_PRESETCFG, m_iPtzPresetNum, &strPresetCond, sizeof(NET_DVR_PRESET_COND), pStatus, pPresetcfg, m_iPtzPresetNum*sizeof(NET_DVR_PRESETCFG));
		bRet = NET_DVR_GetDeviceConfig(m_lServerID, NET_DVR_GET_PRESETCFG, m_iPtzPresetNum, &strPresetCond, sizeof(NET_DVR_PRESET_COND), pStatus, pPresetcfg, m_iPtzPresetNum*sizeof(NET_DVR_PRESETCFG));
		if (!bRet)
		{
			g_StringLanType(szLan, "获取预置点信息失败", "Get video preset info configuration failed");
			sprintf(szTemp, "%s %s", szLan, NET_DVR_GetErrorMsg());
			AfxMessageBox(szTemp);
			delete [] pStatus;
			delete [] pPresetcfg;

			return ;
		}
		pPresetcfgTemp = pPresetcfg;
		if (TRUE == bRet)
		{	
			m_comboCurisePreset.ResetContent();
			for(i = 0; i < m_iPtzPresetNum; i++)
			{
				strTemp.Format("%d", (pPresetcfgTemp->dwPresetIndex + 1));
				m_comboCurisePreset.AddString(strTemp);
				m_comboCurisePreset.SetItemData(i, pPresetcfgTemp->dwPresetIndex);
				pPresetcfgTemp++;
			}
			delete [] pStatus;
			delete [] pPresetcfg;
		}
	}

	if (2 == m_iPresetGetGroupNum)
	{
		int m_ipresetgrp = 0;
		if (m_iPtzPresetNum <= 64)
		{
			m_ipresetgrp = 0;
		} 
		else
		{
			m_ipresetgrp = m_iPtzPresetNum - 64;
		}
		
		NET_DVR_PRESET_COND strPresetCond = {0};
		strPresetCond.dwSize = sizeof(NET_DVR_PRESET_COND);
		strPresetCond.dwChannel = m_iPresetChannel;
		strPresetCond.dwGroupNO = m_iPresetGetGroupNum;

		pPresetcfg = new NET_DVR_PRESETCFG[64];
		if (NULL == pPresetcfg)
		{
			g_StringLanType(szLan,"申请内存失败","new memory failed");
			AfxMessageBox(szLan);
			return;
		}
		memset(pPresetcfg, 0, 64*sizeof(NET_DVR_PRESETCFG));
		pPresetcfgTemp = pPresetcfg;
		
		DWORD *pStatus = new DWORD[64];
		memset(pStatus, 0, sizeof(DWORD)*64);
		
		bRet = NET_DVR_GetDeviceConfig(m_lServerID, NET_DVR_GET_PRESETCFG, 64, &strPresetCond, sizeof(NET_DVR_PRESETCFG), pStatus, pPresetcfg, 64*sizeof(NET_DVR_PRESETCFG));
		if (!bRet)
		{
			g_StringLanType(szLan, "获取预置点信息失败", "Get video preset info configuration failed");
			sprintf(szTemp, "%s %s", szLan, NET_DVR_GetErrorMsg());
			AfxMessageBox(szTemp);			
			delete [] pPresetcfg;
			delete [] pStatus;
			return;
		}
		
		if (TRUE == bRet)
		{
			for(i = 0; i < 64; i++)
			{
				strTemp.Format("%d", (pPresetcfgTemp->dwPresetIndex + 1));
				m_comboCurisePreset.AddString(strTemp);
				
				pPresetcfgTemp++;
			}
			delete [] pPresetcfg;
			delete [] pStatus;
		}

		if (0 != m_ipresetgrp)
		{			
			pPresetSecondcfg = new NET_DVR_PRESETCFG[m_ipresetgrp];
			if (NULL == pPresetSecondcfg)
			{
				g_StringLanType(szLan,"申请内存失败","new memory failed");
				AfxMessageBox(szLan);
				return;
			}
			memset(pPresetSecondcfg, 0, m_ipresetgrp*sizeof(NET_DVR_PRESETCFG));
			pPresetcfgTemp = pPresetcfg;	
			
			DWORD *pStatusSecond = new DWORD[m_ipresetgrp];
			memset(pStatusSecond, 0, sizeof(DWORD)*m_ipresetgrp);
			
			bRet = NET_DVR_GetDeviceConfig(m_lServerID, NET_DVR_GET_PRESETCFG, m_ipresetgrp, &strPresetCond, sizeof(NET_DVR_PRESETCFG), pStatusSecond,\
				pPresetSecondcfg, m_ipresetgrp*sizeof(NET_DVR_PRESETCFG)); 
			if (!bRet)
			{
				g_StringLanType(szLan, "获取预置点信息失败", "Get video preset info configuration failed");
				sprintf(szTemp, "%s %s", szLan, NET_DVR_GetErrorMsg());
				AfxMessageBox(szTemp);
				delete [] pPresetSecondcfg;
				delete [] pStatusSecond;
				return;
			}
			
			if (TRUE == bRet)
			{
				for(i = 0; i < m_ipresetgrp; i++)
				{
					strTemp.Format("%d", (pPresetcfgTemp->dwPresetIndex + 1));
					m_comboCurisePreset.AddString(strTemp);
					
					pPresetcfgTemp++;				
				}
				delete [] pPresetSecondcfg;
				delete [] pStatusSecond;
			}
		}
	}
    }

}



void CDlgIPCSpecial::OnBtnDelseq() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	char szLan[128] = {0};
	char szTemp[256] = {0};	
	
	NET_DVR_PTZ_CRUISE_PARAM struPTZCruise= {0};
	struPTZCruise.dwSize = sizeof(struPTZCruise);
	struPTZCruise.dwChannel = 1;
	struPTZCruise.dwPTZCruiseCmd = DEL_SEQ;
	struPTZCruise.struVcaPoint.fX = m_struPoint.fX;
	struPTZCruise.struVcaPoint.fY = m_struPoint.fY;
	struPTZCruise.wCruisePoint = m_comboCruisePoint.GetCurSel();//巡航点
    struPTZCruise.wCruiseRoute = m_comboCruiseRoute.GetCurSel();//巡航路径
	struPTZCruise.wInput = m_comboCurisePreset.GetCurSel();
	
	if (!NET_DVR_RemoteControl(m_lServerID, NET_DVR_REMOTECONTROL_CRUISE, &struPTZCruise, sizeof(struPTZCruise)))
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, " NET_DVR_REMOTECONTROL_CRUISE DEL_SEQ Fail");
		g_StringLanType(szLan, "删除巡航路径失败!", "Fail to del cruise!");
		sprintf(szTemp, "%s %s", szLan, NET_DVR_GetErrorMsg());
        AfxMessageBox(szTemp);
		return;
	}
	else
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, " NET_DVR_REMOTECONTROL_CRUISE DEL_SEQ Fail");
		AfxMessageBox("删除巡航路径成功!");
	}
	OnBtnGetPtzcruiseNum();
	UpdateData(FALSE);
}

void CDlgIPCSpecial::OnBtnIpaddrFilter() 
{
	// TODO: Add your control notification handler code here
	CDlgIPAddrFilterCfg dlg;
	dlg.m_lServerID = m_lServerID;
	dlg.DoModal();
}

void CDlgIPCSpecial::OnBtnUploadLogo() 
{
	// TODO: Add your control notification handler code here
	CDlgUploadLogo dlg;
	dlg.m_iDevIndex = m_iDevIndex;
	dlg.m_lServerID = m_lServerID;
	dlg.DoModal();
}
