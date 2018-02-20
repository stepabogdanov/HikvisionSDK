/**********************************************************
FileName:    SubDlgAlarmCfg.cpp
Description: alarm configuration     
Date:        2008/05/17
Note: 		<Global>struct, macro refer to GeneralDef.h, global variants and API refer to ClientDemo.cpp  
Modification History:      
    <version> <time>         <desc>
    <1.0    > <2008/05/17>       <created>
***********************************************************/

#include "stdafx.h"
#include "ClientDemo.h"
#include "SubDlgAlarmCfg.h"
#include "DlgRemoteAlarmInHandle.h"
#include "DlgRemoteAlarmInPtzInvoke.h"
#include ".\subdlgalarmcfg.h"


// CSubDlgAlarmCfg dialog

/*********************************************************
  Function:	CSubDlgAlarmCfg
  Desc:		Constructor
  Input:	
  Output:	
  Return:	
**********************************************************/
IMPLEMENT_DYNAMIC(CSubDlgAlarmCfg, CDialog)
CSubDlgAlarmCfg::CSubDlgAlarmCfg(CWnd* pParent /*=NULL*/)
	: CDialog(CSubDlgAlarmCfg::IDD, pParent)
	, m_csAlarmInName(_T(""))
	, m_bChkAlarmInHandle(FALSE)
	, m_iHour11(0)
	, m_iMin11(0)
	, m_iHour12(0)
	, m_iMin12(0)
	, m_iHour21(0)
	, m_iMin21(0)
	, m_iHour22(0)
	, m_iMin22(0)
	, m_iHour31(0)
	, m_iMin31(0)
	, m_iHour32(0)
	, m_iMin32(0)
	, m_iHour41(0)
	, m_iMin41(0)
	, m_iHour42(0)
	, m_iMin42(0)
	, m_iHour51(0)
	, m_iMin51(0)
	, m_iHour52(0)
	, m_iMin52(0)
	, m_iHour61(0)
	, m_iMin61(0)
	, m_iHour62(0)
	, m_iMin62(0)
	, m_iHour71(0)
	, m_iMin71(0)
	, m_iHour72(0)
	, m_iMin72(0)
	, m_iHour81(0)
	, m_iMin81(0)
	, m_iHour82(0)
	, m_iMin82(0)
	, m_iDeviceIndex(-1)
	, m_lLoginID(-1)
	, m_dwAlarmInNum(0)
	, m_dwAlarmOutNum(0)
	, m_iChanCount(0)
	, m_iAnalogChannel(0)
	, m_lStartChannel(0)
	, m_iDStartChannel(0)
	, m_iAlarmInIndex(-1)
	, m_iCopyAlarmIn(0)
	, m_iCopyAlarmOut(-1)
	, m_nCopyOutTime(0)
	, m_iAlarmOutIndex(-1)
	, m_csAlarmInIP(_T(""))
	, m_csAlarmOutIP(_T(""))
	, m_csAlarmInChan(_T("0"))
	, m_csAlarmOutChan(_T("0"))
	, m_iState(0)
	, m_bSupportMultiGroupAlarm(FALSE)
	, m_iIPAlarmInGroupNO(0)
	, m_iIPAlarmOutGroupNO(0)
{
    memset(&m_struAlarmOutHolidayHandle, 0, sizeof(m_struAlarmOutHolidayHandle));
}

/*********************************************************
  Function:	~CSubDlgAlarmCfg
  Desc:		destructor
  Input:	
  Output:	
  Return:	
**********************************************************/
CSubDlgAlarmCfg::~CSubDlgAlarmCfg()
{
}

/*********************************************************
Function:	DoDataExchange
Desc:		the map between control and variable
Input:	
Output:	
Return:	
**********************************************************/
void CSubDlgAlarmCfg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSubDlgAlarmCfg)
	DDX_Control(pDX, IDC_COMBO_ALARMOUT_GROUP_NO, m_comboAlarmOutGroupNO);
	DDX_Control(pDX, IDC_COMBO_ALARMIN_GROUP_NO, m_comboAlarmInGroupNO);
	DDX_Control(pDX, IDC_COMBO_ALARM_IN, m_comboAlarmIn);
	DDX_Control(pDX, IDC_COMBO_ALARM_IN_TYPE, m_comboAlarmInType);
	DDX_Text(pDX, IDC_EDIT_ALARM_IN_NAME, m_csAlarmInName);
	DDX_Check(pDX, IDC_CHK_ALARM_IN_HANDLE, m_bChkAlarmInHandle);
	DDX_Control(pDX, IDC_COMBO_COPY_ALARM_IN, m_comboCopyAlarmIn);
	DDX_Control(pDX, IDC_COMBO_ALARM_OUT, m_comboAlarmOut);
	DDX_Control(pDX, IDC_COMBO_OUT_DELAY, m_comboAlarmOutDelay);
	DDX_Control(pDX, IDC_COMBO_ALARM_OUT_WEEKDAY, m_comboWeekday);
	DDX_Control(pDX, IDC_COMBO_ALARM_OUT_COPY_DAY, m_comboCopyDay);
	DDX_Text(pDX, IDC_EDIT_HOUR11, m_iHour11);
	DDX_Text(pDX, IDC_EDIT_MIN11, m_iMin11);
	DDX_Text(pDX, IDC_EDIT_HOUR12, m_iHour12);
	DDX_Text(pDX, IDC_EDIT_MIN12, m_iMin12);
	DDX_Text(pDX, IDC_EDIT_HOUR21, m_iHour21);
	DDX_Text(pDX, IDC_EDIT_MIN21, m_iMin21);
	DDX_Text(pDX, IDC_EDIT_HOUR22, m_iHour22);
	DDX_Text(pDX, IDC_EDIT_MIN22, m_iMin22);
	DDX_Text(pDX, IDC_EDIT_HOUR31, m_iHour31);
	DDX_Text(pDX, IDC_EDIT_MIN31, m_iMin31);
	DDX_Text(pDX, IDC_EDIT_HOUR32, m_iHour32);
	DDX_Text(pDX, IDC_EDIT_MIN32, m_iMin32);
	DDX_Text(pDX, IDC_EDIT_HOUR41, m_iHour41);
	DDX_Text(pDX, IDC_EDIT_MIN41, m_iMin41);
	DDX_Text(pDX, IDC_EDIT_HOUR42, m_iHour42);
	DDX_Text(pDX, IDC_EDIT_MIN42, m_iMin42);
	DDX_Text(pDX, IDC_EDIT_HOUR51, m_iHour51);
	DDX_Text(pDX, IDC_EDIT_MIN51, m_iMin51);
	DDX_Text(pDX, IDC_EDIT_HOUR52, m_iHour52);
	DDX_Text(pDX, IDC_EDIT_MIN52, m_iMin52);
	DDX_Text(pDX, IDC_EDIT_HOUR61, m_iHour61);
	DDX_Text(pDX, IDC_EDIT_MIN61, m_iMin61);
	DDX_Text(pDX, IDC_EDIT_HOUR62, m_iHour62);
	DDX_Text(pDX, IDC_EDIT_MIN62, m_iMin62);
	DDX_Text(pDX, IDC_EDIT_HOUR71, m_iHour71);
	DDX_Text(pDX, IDC_EDIT_MIN71, m_iMin71);
	DDX_Text(pDX, IDC_EDIT_HOUR72, m_iHour72);
	DDX_Text(pDX, IDC_EDIT_MIN72, m_iMin72);
	DDX_Text(pDX, IDC_EDIT_HOUR81, m_iHour81);
	DDX_Text(pDX, IDC_EDIT_MIN81, m_iMin81);
	DDX_Text(pDX, IDC_EDIT_HOUR82, m_iHour82);
	DDX_Text(pDX, IDC_EDIT_MIN82, m_iMin82);
	DDX_Control(pDX, IDC_COMBO_COPY_ALARM_OUT, m_comboCopyAlarmOut);
	DDX_Text(pDX, IDC_EDIT_ALARMIN_IP, m_csAlarmInIP);
	DDX_Text(pDX, IDC_EDIT_ALARMIN_CHAN, m_csAlarmInChan);
	DDX_Text(pDX, IDC_EDIT_ALARMOUT_CHAN, m_csAlarmOutChan);
	DDX_Text(pDX, IDC_EDIT_ALARMOUT_IP, m_csAlarmOutIP);
	DDX_Text(pDX, IDC_EDIT_ALARMOUT_NAME, m_csAlarmOutName);
	DDX_Text(pDX, IDC_EDIT_STATE, m_iState);
	DDX_Text(pDX, IDC_EDIT_VCA_CHANNEL, m_iVcaChannel);
	//}}AFX_DATA_MAP
	
}


/*********************************************************
Function:	BEGIN_MESSAGE_MAP
Desc:		the map between control and function
Input:	
Output:	
Return:	
**********************************************************/
BEGIN_MESSAGE_MAP(CSubDlgAlarmCfg, CDialog)
	//{{AFX_MSG_MAP(CSubDlgAlarmCfg)	
	ON_CBN_SELCHANGE(IDC_COMBO_ALARM_IN, OnCbnSelchangeComboAlarmIn)
	ON_BN_CLICKED(IDC_CHK_ALARM_IN_HANDLE, OnBnClickedChkAlarmInHandle)
	ON_BN_CLICKED(IDC_BTN_ALARM_OUT_DAY_OK, OnBnClickedBtnAlarmOutDayOk)
	ON_CBN_SELCHANGE(IDC_COMBO_ALARM_OUT_WEEKDAY, OnCbnSelchangeComboAlarmOutWeekday)
	ON_CBN_SELCHANGE(IDC_COMBO_ALARM_OUT, OnCbnSelchangeComboAlarmOut)
	ON_BN_CLICKED(IDC_BTN_ALARM_OUT_DAY_COPY, OnBnClickedBtnAlarmOutDayCopy)
	ON_BN_CLICKED(IDC_BTN_ALARM_OUT_COPY, OnBnClickedBtnAlarmOutCopy)
	ON_BN_CLICKED(IDC_BTN_ALARM_IN_OK, OnBnClickedBtnAlarmInOk)
	ON_BN_CLICKED(IDC_BTN_ALARM_OUT_OK, OnBnClickedBtnAlarmOutOk)
	ON_BN_CLICKED(IDC_BTN_ALARM_IN_HANDLE, OnBnClickedBtnAlarmInHandle)
	ON_BN_CLICKED(IDC_BTN_ALARM_IN_PTZ, OnBnClickedBtnAlarmInPtz)
	ON_BN_CLICKED(IDC_BTN_ALARM_IN_COPY, OnBnClickedBtnAlarmInCopy)
	ON_BN_CLICKED(IDC_BTN_SET_STATE, OnBtnSetState)
	ON_CBN_SELCHANGE(IDC_COMBO_ALARMIN_GROUP_NO, OnSelchangeComboAlarminGroupNo)
	ON_CBN_SELCHANGE(IDC_COMBO_ALARMOUT_GROUP_NO, OnSelchangeComboAlarmoutGroupNo)
	//}}AFX_MSG_MAP
	
END_MESSAGE_MAP()


// CSubDlgAlarmCfg message handlers
/*********************************************************
Function:	OnInitDialog
Desc:		Initialize the dialog
Input:	
Output:	
Return:	
**********************************************************/
BOOL CSubDlgAlarmCfg::OnInitDialog()
{
	CDialog::OnInitDialog();

	CRect rc(0, 0, 0, 0);
	GetParent()->GetClientRect(&rc);
	((CTabCtrl*)GetParent())->AdjustRect(FALSE, &rc);
	MoveWindow(&rc);

  
	return TRUE;
}

/*********************************************************
Function:	CheckInitParam
Desc:		check and update device parameters
Input:	
Output:	
Return:		TRUE,device paramerter correct;FALSE,do not initialize
**********************************************************/
BOOL CSubDlgAlarmCfg::CheckInitParam(BOOL bInit, int iInGroupNO, int iOutGroupNO)
{
	if (bInit)
	{
		iInGroupNO  = 0;
		iOutGroupNO = 0;
	}
	m_iIPAlarmInGroupNO = iInGroupNO;
	m_iIPAlarmOutGroupNO = iOutGroupNO;

	CString sTemp;
	int i = 0;
	DWORD dwReturned = 0;
	int iAlarmInSel = 0;
	int iAlarmOutSel = 0;
	char szLan[128] = {0};
	int iDeviceIndex = g_pMainDlg->GetCurDeviceIndex();
	memset(&m_struIPAlarmInCfg, 0, sizeof(NET_DVR_IPALARMINCFG));
	memset(&m_struIPAlarmOutCfg, 0, sizeof(NET_DVR_IPALARMOUTCFG));
	if (iDeviceIndex == -1)
	{
		return FALSE;
	}

	if (m_iDeviceIndex == iDeviceIndex)
	{
		return TRUE;
	}
	else
	{
		m_iDeviceIndex = iDeviceIndex;
		m_lLoginID = g_struDeviceInfo[m_iDeviceIndex].lLoginID;
		m_lStartChannel = g_struDeviceInfo[m_iDeviceIndex].iStartChan;
		m_iChanCount = g_struDeviceInfo[m_iDeviceIndex].iDeviceChanNum;
		m_iAnalogChannel = g_struDeviceInfo[m_iDeviceIndex].iAnalogChanNum;
		m_iDStartChannel = g_struDeviceInfo[m_iDeviceIndex].struIPParaCfgV40.dwStartDChan;
		m_dwAlarmInNum = g_struDeviceInfo[m_iDeviceIndex].iAlarmInNum;
		m_dwAlarmOutNum = g_struDeviceInfo[m_iDeviceIndex].iAlarmOutNum;
	}

	m_csAlarmInName = _T("");
	m_bChkAlarmInHandle = FALSE;
	m_iHour11 = 0;
	m_iMin11 = 0;
	m_iHour12 = 0;
	m_iMin12 = 0;
	m_iHour21 = 0;
	m_iMin21 = 0;
	m_iHour22 = 0;
	m_iMin22 = 0;
	m_iHour31 = 0;
	m_iMin31 = 0;
	m_iHour32 = 0;
	m_iMin32 = 0;
	m_iHour41 = 0;
	m_iMin41 = 0;
	m_iHour42 = 0;
	m_iMin42 = 0;
	m_iHour51 = 0;
	m_iMin51 = 0;
	m_iHour52 = 0;
	m_iMin52 = 0;
	m_iHour61 = 0;
	m_iMin61 = 0;
	m_iHour62 = 0;
	m_iMin62 = 0;
	m_iHour71 = 0;
	m_iMin71 = 0;
	m_iHour72 = 0;
	m_iMin72 = 0;
	m_iHour81 = 0;
	m_iMin81 = 0;
	m_iHour82 = 0;
	m_iMin82 = 0;

	m_iAlarmInIndex = 0;
	m_iCopyAlarmIn = -1;
	m_iAlarmOutIndex = 0;
	m_iCopyAlarmOut = -1;
	m_nCopyOutTime = -1;
	m_comboWeekday.SetCurSel(-1);
	m_comboCopyDay.SetCurSel(-1);
	m_comboAlarmInType.SetCurSel(-1);
	m_comboAlarmOutDelay.SetCurSel(-1);
	m_comboAlarmIn.ResetContent();
	m_comboCopyAlarmIn.ResetContent();
	m_comboAlarmOut.ResetContent();
	m_comboCopyAlarmOut.ResetContent();

	if (m_lLoginID < 0)
	{
		return FALSE;
	}

	sTemp.Format(_T("All AlarmIn"));
	m_comboCopyAlarmIn.AddString(sTemp);
	m_comboCopyAlarmIn.SetItemData(0, -1);
	if (g_struDeviceInfo[m_iDeviceIndex].iIPChanNum > 0)// == DS90XX_HF_S
	{
		//Get the Group number of alarm in and alarm out.
		if (bInit)
		{
			GetAlarmInOutGroupNum();
		}

		if (g_pMainDlg->DoGetIPAlarmInCfg(m_iDeviceIndex, m_bSupportMultiGroupAlarm, m_iIPAlarmInGroupNO))
		{
			memcpy(&m_struIPAlarmInCfg, &g_struDeviceInfo[m_iDeviceIndex].struAlarmInCfg, sizeof(NET_DVR_IPALARMINCFG));
		}

		if (g_pMainDlg->DoGetIPAlarmOutCfg(m_iDeviceIndex, m_bSupportMultiGroupAlarm, m_iIPAlarmOutGroupNO))
		{
			memcpy(&m_struIPAlarmOutCfg, &g_struDeviceInfo[m_iDeviceIndex].struAlarmOutCfg, sizeof(NET_DVR_IPALARMOUTCFG));
		}
		
	}

	for (i=0; i<MAX_ALARMIN_V30; i++)//m_dwAlarmInNum
	{	
		m_bGetAlarmIn[i] = FALSE;
		m_bSetAlarmIn[i] = FALSE;
		int iIPAlarmIndex = 0;

		if (i<(int)m_dwAlarmInNum || (i>=MAX_ANALOG_ALARMIN && m_struIPAlarmInCfg.struIPAlarmInInfo[i-MAX_ANALOG_ALARMIN].byIPID > 0))
		{

			if (i >= MAX_ANALOG_ALARMIN)
			{
				iIPAlarmIndex = i + MAX_IP_ALARMIN*m_iIPAlarmInGroupNO;
			}
			else
			{
				iIPAlarmIndex = i;
			}

			//此处代码用于验证测试部提的用老接口设置后出现中文乱码的情况
// 			NET_DVR_ALARMINCFG struAlaraming = {0};
// 			if (!NET_DVR_GetDVRConfig(m_lLoginID, NET_DVR_GET_ALARMINCFG, iIPAlarmIndex, &struAlaraming, sizeof(NET_DVR_ALARMINCFG), &dwReturned))
// 			{
// 				m_bGetAlarmIn[i] = FALSE;
// 				g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_ALARMINCFG_V30 chanindex[%d]", iIPAlarmIndex);	
// 				g_StringLanType(szLan, "获取报警输入参数失败", "Alarm input parameters to get the failure");
// 				AfxMessageBox(szLan);
// 				return FALSE;
// 			}
// 
//             memcpy(m_struAlarmInCfg[i].sAlarmInName, struAlaraming.sAlarmInName ,NAME_LEN);
// 			m_struAlarmInCfg[i].byChannel = struAlaraming.byChannel;
// 			m_struAlarmInCfg[i].byAlarmType = struAlaraming.byAlarmType;
// 			memcpy(m_struAlarmInCfg[i].byCruiseNo,struAlaraming.byCruiseNo,MAX_CHANNUM);
// 			memcpy(m_struAlarmInCfg[i].byRelRecordChan,struAlaraming.byRelRecordChan,MAX_CHANNUM);
// 			memcpy(m_struAlarmInCfg[i].byPresetNo,struAlaraming.byPresetNo,MAX_CHANNUM);
// 			memcpy(m_struAlarmInCfg[i].byEnablePreset,struAlaraming.byEnablePreset,MAX_CHANNUM);
// 			memcpy(m_struAlarmInCfg[i].byEnableCruise,struAlaraming.byEnableCruise,MAX_CHANNUM);
// 			memcpy(m_struAlarmInCfg[i].byPTZTrack,struAlaraming.byPTZTrack,MAX_CHANNUM);
// 			memcpy(m_struAlarmInCfg[i].byEnablePtzTrack,struAlaraming.byEnablePtzTrack,MAX_CHANNUM);
			if (!NET_DVR_GetDVRConfig(m_lLoginID, NET_DVR_GET_ALARMINCFG_V30, iIPAlarmIndex, &m_struAlarmInCfg[i], sizeof(NET_DVR_ALARMINCFG_V30), &dwReturned))
			{
				m_bGetAlarmIn[i] = FALSE;
				g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_ALARMINCFG_V30 chanindex[%d]", iIPAlarmIndex);	
				g_StringLanType(szLan, "获取报警输入参数失败", "Alarm input parameters to get the failure");
				AfxMessageBox(szLan);
				return FALSE;
			}
			if (i<(int)m_dwAlarmInNum)
			{			
				sTemp.Format(ALARM_IN_NAME, (1+i));
			}
			else
			{
				sTemp.Format(IP_ALARM_IN_NAME, (1 + iIPAlarmIndex-MAX_ANALOG_ALARMIN));
			}	

			m_bGetAlarmIn[i] = TRUE;
			m_comboAlarmIn.AddString(sTemp);
			m_comboAlarmIn.SetItemData(iAlarmInSel, iIPAlarmIndex);
			
			m_comboCopyAlarmIn.AddString(sTemp);
			m_comboCopyAlarmIn.SetItemData(iAlarmInSel+1, iIPAlarmIndex);
			iAlarmInSel++;
		}
	}
	m_comboCopyAlarmIn.SetCurSel(0);		
	m_comboAlarmIn.SetCurSel(0);
	m_iAlarmInIndex = m_comboAlarmIn.GetItemData(0);
	m_iCopyAlarmIn = m_comboAlarmIn.GetItemData(0);

	sTemp.Format(_T("All AlarmOut"));
	m_comboCopyAlarmOut.AddString(sTemp);
	m_comboCopyAlarmOut.SetItemData(0, -1);
	for (i=0; i<MAX_ALARMOUT_V30; i++)//m_dwAlarmOutNum for test
	{	
		m_bGetAlarmOut[i] = FALSE;
		m_bSetAlarmOut[i] = FALSE;
		int iIPAlarmIndex = 0;

		if (i<(int)m_dwAlarmOutNum || (i>=MAX_ANALOG_ALARMOUT && m_struIPAlarmOutCfg.struIPAlarmOutInfo[i-MAX_ANALOG_ALARMOUT].byIPID > 0))
		{
			if (i >= MAX_ANALOG_ALARMIN)
			{
				iIPAlarmIndex = i + MAX_IP_ALARMIN*m_iIPAlarmOutGroupNO;
			}
			else
			{
				iIPAlarmIndex = i;
			}

			if (!NET_DVR_GetDVRConfig(m_lLoginID, NET_DVR_GET_ALARMOUTCFG_V30, i, &m_struAlarmOutCfg[i], sizeof(NET_DVR_ALARMOUTCFG_V30), &dwReturned))
			{
				m_bGetAlarmOut[i] = FALSE;
				g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_ALARMOUTCFG_V30 index[%d]", i);		
				g_StringLanType(szLan, "获取报警输出参数失败", "Alarm output parameters to get the failure");
				AfxMessageBox(szLan);
				return FALSE;
			}
			if (i<(int)m_dwAlarmOutNum)
			{			
				sTemp.Format(ALARM_OUT_FORMAT, 1 + iIPAlarmIndex);
			}
			else if (i>=MAX_ANALOG_ALARMOUT)
			{
				sTemp.Format(IP_ALARM_OUT_NAME, 1 + iIPAlarmIndex - MAX_ANALOG_ALARMOUT);
			}

			m_bGetAlarmOut[i] = TRUE;
			m_comboAlarmOut.AddString(sTemp);	
			m_comboAlarmOut.SetItemData(iAlarmOutSel, iIPAlarmIndex);
			
			m_comboCopyAlarmOut.AddString(sTemp);
			m_comboCopyAlarmOut.SetItemData(iAlarmOutSel+1, iIPAlarmIndex);
			iAlarmOutSel++;
		}
	}
	m_comboCopyAlarmOut.SetCurSel(0);		
	m_comboAlarmOut.SetCurSel(0);
	m_iAlarmOutIndex = m_comboAlarmOut.GetItemData(0);
	OnCbnSelchangeComboAlarmIn();
	OnCbnSelchangeComboAlarmOut();
	return TRUE;
}

/*********************************************************
  Function:	CurCfgUpdate
  Desc:		update device parameters and updated the controls
  Input:	
  Output:	
  Return:	
**********************************************************/
void CSubDlgAlarmCfg::CurCfgUpdate()
{
	if (!CheckInitParam())
	{
		UpdateData(FALSE);
		EnableWindow(FALSE);
		return;
	}
	EnableWindow(TRUE);

	char cTemp[100];

	if (m_bGetAlarmIn[m_iAlarmInIndex])
	{
		m_comboAlarmInType.SetCurSel(m_struAlarmInCfg[m_iAlarmInIndex].byAlarmType);
		m_bChkAlarmInHandle = m_struAlarmInCfg[m_iAlarmInIndex].byAlarmInHandle;
		ZeroMemory(cTemp, 100);
		memcpy(cTemp, m_struAlarmInCfg[m_iAlarmInIndex].sAlarmInName, NAME_LEN);
		m_csAlarmInName.Format("%s", cTemp);
        m_iVcaChannel = m_struAlarmInCfg[m_iAlarmInIndex].byChannel;
		if (m_bChkAlarmInHandle)
		{
			GetDlgItem(IDC_BTN_ALARM_IN_HANDLE)->EnableWindow(TRUE);
		}
		else
		{
			GetDlgItem(IDC_BTN_ALARM_IN_HANDLE)->EnableWindow(FALSE);
		}
		GetDlgItem(IDC_BTN_ALARM_IN_COPY)->EnableWindow(TRUE);
		GetDlgItem(IDC_BTN_ALARM_IN_OK)->EnableWindow(TRUE);
	}

	if (m_bGetAlarmOut[m_iAlarmOutIndex])
	{
		ZeroMemory(cTemp, 100);
		memcpy(cTemp, m_struAlarmOutCfg[m_iAlarmOutIndex].sAlarmOutName, NAME_LEN);
		m_comboAlarmOutDelay.SetCurSel(m_struAlarmOutCfg[m_iAlarmOutIndex].dwAlarmOutDelay);
		m_csAlarmOutName.Format("%s", cTemp);
		m_comboWeekday.SetCurSel(0);
		m_comboCopyDay.SetCurSel(0);
		m_iHour11 = m_struAlarmOutCfg[m_iAlarmOutIndex].struAlarmOutTime[0][0].byStartHour;
		m_iMin11 = m_struAlarmOutCfg[m_iAlarmOutIndex].struAlarmOutTime[0][0].byStartMin;
		m_iHour12 = m_struAlarmOutCfg[m_iAlarmOutIndex].struAlarmOutTime[0][0].byStopHour;
		m_iMin12 = m_struAlarmOutCfg[m_iAlarmOutIndex].struAlarmOutTime[0][0].byStopMin;
		m_iHour21 = m_struAlarmOutCfg[m_iAlarmOutIndex].struAlarmOutTime[0][1].byStartHour;
		m_iMin21 = m_struAlarmOutCfg[m_iAlarmOutIndex].struAlarmOutTime[0][1].byStartMin;
		m_iHour22 = m_struAlarmOutCfg[m_iAlarmOutIndex].struAlarmOutTime[0][1].byStopHour;
		m_iMin22 = m_struAlarmOutCfg[m_iAlarmOutIndex].struAlarmOutTime[0][1].byStopMin;
		m_iHour31 = m_struAlarmOutCfg[m_iAlarmOutIndex].struAlarmOutTime[0][2].byStartHour;
		m_iMin31 = m_struAlarmOutCfg[m_iAlarmOutIndex].struAlarmOutTime[0][2].byStartMin;
		m_iHour32 = m_struAlarmOutCfg[m_iAlarmOutIndex].struAlarmOutTime[0][2].byStopHour;
		m_iMin32 = m_struAlarmOutCfg[m_iAlarmOutIndex].struAlarmOutTime[0][2].byStopMin;
		m_iHour41 = m_struAlarmOutCfg[m_iAlarmOutIndex].struAlarmOutTime[0][3].byStartHour;
		m_iMin41 = m_struAlarmOutCfg[m_iAlarmOutIndex].struAlarmOutTime[0][3].byStartMin;
		m_iHour42 = m_struAlarmOutCfg[m_iAlarmOutIndex].struAlarmOutTime[0][3].byStopHour;
		m_iMin42 = m_struAlarmOutCfg[m_iAlarmOutIndex].struAlarmOutTime[0][3].byStopMin;
		m_iHour51 = m_struAlarmOutCfg[m_iAlarmOutIndex].struAlarmOutTime[0][4].byStartHour;
		m_iMin51 = m_struAlarmOutCfg[m_iAlarmOutIndex].struAlarmOutTime[0][4].byStartMin;
		m_iHour52 = m_struAlarmOutCfg[m_iAlarmOutIndex].struAlarmOutTime[0][4].byStopHour;
		m_iMin52 = m_struAlarmOutCfg[m_iAlarmOutIndex].struAlarmOutTime[0][4].byStopMin;
		m_iHour61 = m_struAlarmOutCfg[m_iAlarmOutIndex].struAlarmOutTime[0][5].byStartHour;
		m_iMin61 = m_struAlarmOutCfg[m_iAlarmOutIndex].struAlarmOutTime[0][5].byStartMin;
		m_iHour62 = m_struAlarmOutCfg[m_iAlarmOutIndex].struAlarmOutTime[0][5].byStopHour;
		m_iMin62 = m_struAlarmOutCfg[m_iAlarmOutIndex].struAlarmOutTime[0][5].byStopMin;
		m_iHour71 = m_struAlarmOutCfg[m_iAlarmOutIndex].struAlarmOutTime[0][6].byStartHour;
		m_iMin71 = m_struAlarmOutCfg[m_iAlarmOutIndex].struAlarmOutTime[0][6].byStartMin;
		m_iHour72 = m_struAlarmOutCfg[m_iAlarmOutIndex].struAlarmOutTime[0][6].byStopHour;
		m_iMin72 = m_struAlarmOutCfg[m_iAlarmOutIndex].struAlarmOutTime[0][6].byStopMin;
		m_iHour81 = m_struAlarmOutCfg[m_iAlarmOutIndex].struAlarmOutTime[0][7].byStartHour;
		m_iMin81 = m_struAlarmOutCfg[m_iAlarmOutIndex].struAlarmOutTime[0][7].byStartMin;
		m_iHour82 = m_struAlarmOutCfg[m_iAlarmOutIndex].struAlarmOutTime[0][7].byStopHour;
		m_iMin82 = m_struAlarmOutCfg[m_iAlarmOutIndex].struAlarmOutTime[0][7].byStopMin;
		GetDlgItem(IDC_BTN_ALARM_OUT_OK)->EnableWindow(TRUE); 
		GetDlgItem(IDC_BTN_ALARM_OUT_DAY_OK)->EnableWindow(TRUE); 
		GetDlgItem(IDC_BTN_ALARM_OUT_DAY_COPY)->EnableWindow(FALSE);
	}
	UpdateData(FALSE);	
}

/*********************************************************
  Function:	OnCbnSelchangeComboAlarmIn
  Desc:		update selected alarm parameters
  Input:	
  Output:	
  Return:	
**********************************************************/
void CSubDlgAlarmCfg::OnCbnSelchangeComboAlarmIn()
{
	char szLan[128] = {0};
	char cTemp[100] = {0};
	DWORD dwID = 0;
	m_iAlarmInIndex = m_comboAlarmIn.GetItemData(m_comboAlarmIn.GetCurSel());
	ZeroMemory(cTemp, 100);
	memcpy(cTemp, m_struAlarmInCfg[m_iAlarmInIndex].sAlarmInName, NAME_LEN);
	m_csAlarmInName.Format("%s", cTemp);
    m_iVcaChannel = m_struAlarmInCfg[m_iAlarmInIndex].byChannel;
	m_comboAlarmInType.SetCurSel(m_struAlarmInCfg[m_iAlarmInIndex].byAlarmType);
	m_bChkAlarmInHandle = m_struAlarmInCfg[m_iAlarmInIndex].byAlarmInHandle;
	if (m_iAlarmInIndex >= 0 && m_iAlarmInIndex < MAX_ANALOG_ALARMIN)
	{
		g_StringLanType(szLan, "本地", "Local");
		m_csAlarmInIP.Format(szLan);
		m_csAlarmInChan.Format("0");
	}
	else if (m_iAlarmInIndex >= MAX_ANALOG_ALARMIN && m_iAlarmInIndex < MAX_ALARMOUT_V30)
	{
		dwID = g_struDeviceInfo[m_iDeviceIndex].struAlarmInCfg.struIPAlarmInInfo[m_iAlarmInIndex-MAX_ANALOG_ALARMIN].byIPID;
		if (dwID <= 0)
		{
			g_StringLanType(szLan, "不在线", "Offline");
			m_csAlarmInIP.Format(szLan);
			m_csAlarmInChan.Format("0");
		}
		else
		{
			m_csAlarmInIP.Format("%s", g_struDeviceInfo[m_iDeviceIndex].struIPParaCfgV40.struIPDevInfo[dwID-1].struIP.sIpV4);
			m_csAlarmInChan.Format("%d", m_struIPAlarmInCfg.struIPAlarmInInfo[m_iAlarmInIndex-MAX_ANALOG_ALARMIN].byAlarmIn);
		}
		
	}
	else
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "Err m_iAlarmInIndex %d", m_iAlarmInIndex);
	}
	
	if (m_bChkAlarmInHandle)
	{
		GetDlgItem(IDC_BTN_ALARM_IN_HANDLE)->EnableWindow(TRUE);
	}
	else
	{
		GetDlgItem(IDC_BTN_ALARM_IN_HANDLE)->EnableWindow(FALSE);
	}
	UpdateData(FALSE);
}

/*********************************************************
  Function:	OnBnClickedBtnAlarmInHandle
  Desc:		Set selected alarm input parameters
  Input:	
  Output:	
  Return:	
**********************************************************/
void CSubDlgAlarmCfg::OnBnClickedBtnAlarmInHandle()
{
	CDlgRemoteAlarmInHandle dlg;
	dlg.m_lpAlarmIn = &m_struAlarmInCfg[m_iAlarmInIndex];
	dlg.m_iChanCount = m_iChanCount;
	dlg.m_iAnaChanCount = m_iAnalogChannel;
	dlg.m_iDStartChannel = m_iDStartChannel;
	dlg.m_dwDevIndex = m_iDeviceIndex;
	dlg.m_lStartChannel = m_lStartChannel;
	dlg.m_dwAlarmOutNum = m_dwAlarmOutNum;
	dlg.m_dwAlarmInNum = m_dwAlarmInNum;
    dlg.m_lAlarmInIndex = m_iAlarmInIndex;
    dlg.m_lServerID = m_lLoginID;
	if (dlg.DoModal()==IDOK)
	{
		m_bSetAlarmIn[m_iAlarmInIndex] = TRUE;
		g_bMustReboot = TRUE;
	}
}

/*********************************************************
  Function:	OnBnClickedBtnAlarmInPtz
  Desc:		external PTZ config on alarm
  Input:	
  Output:	
  Return:	
**********************************************************/
void CSubDlgAlarmCfg::OnBnClickedBtnAlarmInPtz()
{
	CDlgRemoteAlarmInPtzInvoke dlg;
	dlg.m_lpAlarmIn = &m_struAlarmInCfg[m_iAlarmInIndex];
	dlg.m_iChanCount = m_iChanCount;
	dlg.m_iAnalogChanNum = m_iAnalogChannel;
	dlg.m_lStartChannel = m_lStartChannel;
	dlg.m_iDStartChannel = m_iDStartChannel;
	dlg.m_iDeviceIndex = m_iDeviceIndex;
	if (dlg.DoModal()==IDOK)
	{
		m_bSetAlarmIn[m_iAlarmInIndex] = TRUE;
	}
}

/*********************************************************
  Function:	OnBnClickedBtnAlarmInCopy
  Desc:		copy alarm config to certain channel
  Input:	
  Output:	
  Return:	
**********************************************************/
void CSubDlgAlarmCfg::OnBnClickedBtnAlarmInCopy()
{
	UpdateData(TRUE);
	int i;
	m_iCopyAlarmIn = m_comboCopyAlarmIn.GetItemData(m_comboCopyAlarmIn.GetCurSel());
	m_struAlarmInCfg[m_iAlarmInIndex].byAlarmInHandle = (BYTE)m_bChkAlarmInHandle;
	m_struAlarmInCfg[m_iAlarmInIndex].byAlarmType = (BYTE)m_comboAlarmInType.GetCurSel();
	memcpy(m_struAlarmInCfg[m_iAlarmInIndex].sAlarmInName, m_csAlarmInName, NAME_LEN);
    m_struAlarmInCfg[m_iAlarmInIndex].byChannel = (BYTE)m_iVcaChannel;

	if (m_iCopyAlarmIn == -1)
	{
		for (i=0; i<MAX_ALARMIN_V30; i++)
		{
			if ( i < MAX_ANALOG_ALARMIN && i >= (int)m_dwAlarmInNum )
			{
				continue;
			}
			if ( i>=MAX_ANALOG_ALARMIN )
			{//IP alarm channel not exist
				if (g_struDeviceInfo[m_iDeviceIndex].struAlarmInCfg.struIPAlarmInInfo[i-MAX_ANALOG_ALARMIN].byIPID == 0)
				{
					continue;
				}
			}
			if (m_iAlarmInIndex == i)
			{
				continue;	
			}
			memcpy(&(m_struAlarmInCfg[i]), &(m_struAlarmInCfg[m_iAlarmInIndex]), sizeof(NET_DVR_ALARMINCFG_V30));
			m_bSetAlarmIn[i] = TRUE;
		}
	}
	else
	{	
		memcpy(&(m_struAlarmInCfg[m_iCopyAlarmIn]), &(m_struAlarmInCfg[m_iAlarmInIndex]), sizeof(NET_DVR_ALARMINCFG_V30));
		m_bSetAlarmIn[m_iCopyAlarmIn] = TRUE;
	}
	
}

/*********************************************************
  Function:	OnBnClickedBtnAlarmInOk
  Desc:		finish current alarm configuration
  Input:	
  Output:	
  Return:	
**********************************************************/
void CSubDlgAlarmCfg::OnBnClickedBtnAlarmInOk()
{
	UpdateData(TRUE);

	m_struAlarmInCfg[m_iAlarmInIndex].byAlarmInHandle = (BYTE)m_bChkAlarmInHandle;
	m_struAlarmInCfg[m_iAlarmInIndex].byAlarmType = (BYTE)m_comboAlarmInType.GetCurSel();
	memcpy(m_struAlarmInCfg[m_iAlarmInIndex].sAlarmInName, m_csAlarmInName, NAME_LEN);
    m_struAlarmInCfg[m_iAlarmInIndex].byChannel = (BYTE)m_iVcaChannel;
	m_bSetAlarmIn[m_iAlarmInIndex] = TRUE;
}

/*********************************************************
  Function:	OnBnClickedChkAlarmInHandle
  Desc:		enable/disable alarm handling
  Input:	
  Output:	
  Return:	
**********************************************************/
void CSubDlgAlarmCfg::OnBnClickedChkAlarmInHandle()
{
	UpdateData(TRUE);
	m_struAlarmInCfg[m_iAlarmInIndex].byAlarmInHandle = (BYTE)m_bChkAlarmInHandle;
	if (m_bChkAlarmInHandle)
	{
		GetDlgItem(IDC_BTN_ALARM_IN_HANDLE)->EnableWindow(TRUE);		
	}
	else
	{
		GetDlgItem(IDC_BTN_ALARM_IN_HANDLE)->EnableWindow(FALSE);
	}
}

/*********************************************************
  Function:	OnCbnSelchangeComboAlarmOut
  Desc:		update alarm output channel parametersand update the control
  Input:	
  Output:	
  Return:	
**********************************************************/
void CSubDlgAlarmCfg::OnCbnSelchangeComboAlarmOut()
{
	UpdateData(TRUE);
	char szLan[128] = {0};
	char szTemp[100] = {0};
	DWORD dwID = 0;
	m_iAlarmOutIndex = m_comboAlarmOut.GetItemData(m_comboAlarmOut.GetCurSel());

	if (m_iAlarmOutIndex >= 0 && m_iAlarmOutIndex < MAX_ANALOG_ALARMOUT)
	{
		g_StringLanType(szLan, "本地", "Local");
		m_csAlarmOutIP.Format(szLan);
		m_csAlarmOutChan.Format("0");
	}
	else
	{
		dwID = g_struDeviceInfo[m_iDeviceIndex].struAlarmOutCfg.struIPAlarmOutInfo[m_iAlarmOutIndex-MAX_ANALOG_ALARMOUT].byIPID;
		if (dwID <= 0)
		{
			g_StringLanType(szLan, "不在线", "Offline");
			m_csAlarmOutIP.Format(szLan);
			m_csAlarmOutChan.Format("0");
		}
		else
		{
			m_csAlarmOutIP.Format("%s", g_struDeviceInfo[m_iDeviceIndex].struIPParaCfgV40.struIPDevInfo[dwID-1].struIP.sIpV4);
			m_csAlarmOutChan.Format("%d", m_struIPAlarmOutCfg.struIPAlarmOutInfo[m_iAlarmOutIndex-MAX_ANALOG_ALARMOUT].byAlarmOut);
		}
	}
	
	memcpy(szTemp, m_struAlarmOutCfg[m_iAlarmOutIndex].sAlarmOutName, NAME_LEN);
	m_csAlarmOutName.Format("%s", szTemp);
	m_comboAlarmOutDelay.SetCurSel(m_struAlarmOutCfg[m_iAlarmOutIndex].dwAlarmOutDelay);
	m_comboWeekday.SetCurSel(0);
	m_comboCopyDay.SetCurSel(0);

	m_iHour11 = m_struAlarmOutCfg[m_iAlarmOutIndex].struAlarmOutTime[0][0].byStartHour;
	m_iMin11 = m_struAlarmOutCfg[m_iAlarmOutIndex].struAlarmOutTime[0][0].byStartMin;
	m_iHour12 = m_struAlarmOutCfg[m_iAlarmOutIndex].struAlarmOutTime[0][0].byStopHour;
	m_iMin12 = m_struAlarmOutCfg[m_iAlarmOutIndex].struAlarmOutTime[0][0].byStopMin;
	m_iHour21 = m_struAlarmOutCfg[m_iAlarmOutIndex].struAlarmOutTime[0][1].byStartHour;
	m_iMin21 = m_struAlarmOutCfg[m_iAlarmOutIndex].struAlarmOutTime[0][1].byStartMin;
	m_iHour22 = m_struAlarmOutCfg[m_iAlarmOutIndex].struAlarmOutTime[0][1].byStopHour;
	m_iMin22 = m_struAlarmOutCfg[m_iAlarmOutIndex].struAlarmOutTime[0][1].byStopMin;
	m_iHour31 = m_struAlarmOutCfg[m_iAlarmOutIndex].struAlarmOutTime[0][2].byStartHour;
	m_iMin31 = m_struAlarmOutCfg[m_iAlarmOutIndex].struAlarmOutTime[0][2].byStartMin;
	m_iHour32 = m_struAlarmOutCfg[m_iAlarmOutIndex].struAlarmOutTime[0][2].byStopHour;
	m_iMin32 = m_struAlarmOutCfg[m_iAlarmOutIndex].struAlarmOutTime[0][2].byStopMin;
	m_iHour41 = m_struAlarmOutCfg[m_iAlarmOutIndex].struAlarmOutTime[0][3].byStartHour;
	m_iMin41 = m_struAlarmOutCfg[m_iAlarmOutIndex].struAlarmOutTime[0][3].byStartMin;
	m_iHour42 = m_struAlarmOutCfg[m_iAlarmOutIndex].struAlarmOutTime[0][3].byStopHour;
	m_iMin42 = m_struAlarmOutCfg[m_iAlarmOutIndex].struAlarmOutTime[0][3].byStopMin;
	m_iHour51 = m_struAlarmOutCfg[m_iAlarmOutIndex].struAlarmOutTime[0][4].byStartHour;
	m_iMin51 = m_struAlarmOutCfg[m_iAlarmOutIndex].struAlarmOutTime[0][4].byStartMin;
	m_iHour52 = m_struAlarmOutCfg[m_iAlarmOutIndex].struAlarmOutTime[0][4].byStopHour;
	m_iMin52 = m_struAlarmOutCfg[m_iAlarmOutIndex].struAlarmOutTime[0][4].byStopMin;
	m_iHour61 = m_struAlarmOutCfg[m_iAlarmOutIndex].struAlarmOutTime[0][5].byStartHour;
	m_iMin61 = m_struAlarmOutCfg[m_iAlarmOutIndex].struAlarmOutTime[0][5].byStartMin;
	m_iHour62 = m_struAlarmOutCfg[m_iAlarmOutIndex].struAlarmOutTime[0][5].byStopHour;
	m_iMin62 = m_struAlarmOutCfg[m_iAlarmOutIndex].struAlarmOutTime[0][5].byStopMin;
	m_iHour71 = m_struAlarmOutCfg[m_iAlarmOutIndex].struAlarmOutTime[0][6].byStartHour;
	m_iMin71 = m_struAlarmOutCfg[m_iAlarmOutIndex].struAlarmOutTime[0][6].byStartMin;
	m_iHour72 = m_struAlarmOutCfg[m_iAlarmOutIndex].struAlarmOutTime[0][6].byStopHour;
	m_iMin72 = m_struAlarmOutCfg[m_iAlarmOutIndex].struAlarmOutTime[0][6].byStopMin;
	m_iHour81 = m_struAlarmOutCfg[m_iAlarmOutIndex].struAlarmOutTime[0][7].byStartHour;
	m_iMin81 = m_struAlarmOutCfg[m_iAlarmOutIndex].struAlarmOutTime[0][7].byStartMin;
	m_iHour82 = m_struAlarmOutCfg[m_iAlarmOutIndex].struAlarmOutTime[0][7].byStopHour;
	m_iMin82 = m_struAlarmOutCfg[m_iAlarmOutIndex].struAlarmOutTime[0][7].byStopMin;

	UpdateData(FALSE);
}

/*********************************************************
Function:	OnBnClickedBtnAlarmOutOk
Desc:		finish alarm output settings
Input:	
Output:	
Return:	
**********************************************************/
void CSubDlgAlarmCfg::OnBnClickedBtnAlarmOutOk()
{
	UpdateData(TRUE);
	OnBnClickedBtnAlarmOutDayOk();
	memcpy(m_struAlarmOutCfg[m_iAlarmOutIndex].sAlarmOutName, m_csAlarmOutName, NAME_LEN);
	m_struAlarmOutCfg[m_iAlarmOutIndex].dwAlarmOutDelay = m_comboAlarmOutDelay.GetCurSel();
	GetDlgItem(IDC_BTN_ALARM_OUT_COPY)->EnableWindow(TRUE);
	m_bSetAlarmOut[m_iAlarmOutIndex] = TRUE;
	g_bMustReboot = TRUE;
}

/*********************************************************
  Function:	OnCbnSelchangeComboAlarmOutWeekday
  Desc:		set alarm Output time schedule
  Input:	
  Output:	
  Return:	
**********************************************************/
void CSubDlgAlarmCfg::OnCbnSelchangeComboAlarmOutWeekday()
{
	UpdateData(TRUE);
	int i = m_comboWeekday.GetCurSel();
    if (i == 7)
    {
        GetAlarmOutHolidayHandle(m_struAlarmOutHolidayHandle);

        m_iHour11 = m_struAlarmOutHolidayHandle.struAlarmTime[0].byStartHour;
        m_iMin11 = m_struAlarmOutHolidayHandle.struAlarmTime[0].byStartMin;
        m_iHour12 = m_struAlarmOutHolidayHandle.struAlarmTime[0].byStopHour;
        m_iMin12 = m_struAlarmOutHolidayHandle.struAlarmTime[0].byStopMin;
        m_iHour21 = m_struAlarmOutHolidayHandle.struAlarmTime[1].byStartHour;
        m_iMin21 = m_struAlarmOutHolidayHandle.struAlarmTime[1].byStartMin;
        m_iHour22 = m_struAlarmOutHolidayHandle.struAlarmTime[1].byStopHour;
        m_iMin22 = m_struAlarmOutHolidayHandle.struAlarmTime[1].byStopMin;
        m_iHour31 = m_struAlarmOutHolidayHandle.struAlarmTime[2].byStartHour;
        m_iMin31 = m_struAlarmOutHolidayHandle.struAlarmTime[2].byStartMin;
        m_iHour32 = m_struAlarmOutHolidayHandle.struAlarmTime[2].byStopHour;
        m_iMin32 = m_struAlarmOutHolidayHandle.struAlarmTime[2].byStopMin;
        m_iHour41 = m_struAlarmOutHolidayHandle.struAlarmTime[3].byStartHour;
        m_iMin41 = m_struAlarmOutHolidayHandle.struAlarmTime[3].byStartMin;
        m_iHour42 = m_struAlarmOutHolidayHandle.struAlarmTime[3].byStopHour;
        m_iMin42 = m_struAlarmOutHolidayHandle.struAlarmTime[3].byStopMin;
        m_iHour51 = m_struAlarmOutHolidayHandle.struAlarmTime[4].byStartHour;
        m_iMin51 = m_struAlarmOutHolidayHandle.struAlarmTime[4].byStartMin;
        m_iHour52 = m_struAlarmOutHolidayHandle.struAlarmTime[4].byStopHour;
        m_iMin52 = m_struAlarmOutHolidayHandle.struAlarmTime[4].byStopMin;
        m_iHour61 = m_struAlarmOutHolidayHandle.struAlarmTime[5].byStartHour;
        m_iMin61 = m_struAlarmOutHolidayHandle.struAlarmTime[5].byStartMin;
        m_iHour62 = m_struAlarmOutHolidayHandle.struAlarmTime[5].byStopHour;
        m_iMin62 = m_struAlarmOutHolidayHandle.struAlarmTime[5].byStopMin;
        m_iHour71 = m_struAlarmOutHolidayHandle.struAlarmTime[6].byStartHour;
        m_iMin71 = m_struAlarmOutHolidayHandle.struAlarmTime[6].byStartMin;
        m_iHour72 = m_struAlarmOutHolidayHandle.struAlarmTime[6].byStopHour;
        m_iMin72 = m_struAlarmOutHolidayHandle.struAlarmTime[6].byStopMin;
        m_iHour81 = m_struAlarmOutHolidayHandle.struAlarmTime[7].byStartHour;
        m_iMin81 = m_struAlarmOutHolidayHandle.struAlarmTime[7].byStartMin;
        m_iHour82 = m_struAlarmOutHolidayHandle.struAlarmTime[7].byStopHour;
        m_iMin82 = m_struAlarmOutHolidayHandle.struAlarmTime[7].byStopMin;
    }
    else
    {
        m_iHour11 = m_struAlarmOutCfg[m_iAlarmOutIndex].struAlarmOutTime[i][0].byStartHour;
        m_iMin11 = m_struAlarmOutCfg[m_iAlarmOutIndex].struAlarmOutTime[i][0].byStartMin;
        m_iHour12 = m_struAlarmOutCfg[m_iAlarmOutIndex].struAlarmOutTime[i][0].byStopHour;
        m_iMin12 = m_struAlarmOutCfg[m_iAlarmOutIndex].struAlarmOutTime[i][0].byStopMin;
        m_iHour21 = m_struAlarmOutCfg[m_iAlarmOutIndex].struAlarmOutTime[i][1].byStartHour;
        m_iMin21 = m_struAlarmOutCfg[m_iAlarmOutIndex].struAlarmOutTime[i][1].byStartMin;
        m_iHour22 = m_struAlarmOutCfg[m_iAlarmOutIndex].struAlarmOutTime[i][1].byStopHour;
        m_iMin22 = m_struAlarmOutCfg[m_iAlarmOutIndex].struAlarmOutTime[i][1].byStopMin;
        m_iHour31 = m_struAlarmOutCfg[m_iAlarmOutIndex].struAlarmOutTime[i][2].byStartHour;
        m_iMin31 = m_struAlarmOutCfg[m_iAlarmOutIndex].struAlarmOutTime[i][2].byStartMin;
        m_iHour32 = m_struAlarmOutCfg[m_iAlarmOutIndex].struAlarmOutTime[i][2].byStopHour;
        m_iMin32 = m_struAlarmOutCfg[m_iAlarmOutIndex].struAlarmOutTime[i][2].byStopMin;
        m_iHour41 = m_struAlarmOutCfg[m_iAlarmOutIndex].struAlarmOutTime[i][3].byStartHour;
        m_iMin41 = m_struAlarmOutCfg[m_iAlarmOutIndex].struAlarmOutTime[i][3].byStartMin;
        m_iHour42 = m_struAlarmOutCfg[m_iAlarmOutIndex].struAlarmOutTime[i][3].byStopHour;
        m_iMin42 = m_struAlarmOutCfg[m_iAlarmOutIndex].struAlarmOutTime[i][3].byStopMin;
        m_iHour51 = m_struAlarmOutCfg[m_iAlarmOutIndex].struAlarmOutTime[i][4].byStartHour;
        m_iMin51 = m_struAlarmOutCfg[m_iAlarmOutIndex].struAlarmOutTime[i][4].byStartMin;
        m_iHour52 = m_struAlarmOutCfg[m_iAlarmOutIndex].struAlarmOutTime[i][4].byStopHour;
        m_iMin52 = m_struAlarmOutCfg[m_iAlarmOutIndex].struAlarmOutTime[i][4].byStopMin;
        m_iHour61 = m_struAlarmOutCfg[m_iAlarmOutIndex].struAlarmOutTime[i][5].byStartHour;
        m_iMin61 = m_struAlarmOutCfg[m_iAlarmOutIndex].struAlarmOutTime[i][5].byStartMin;
        m_iHour62 = m_struAlarmOutCfg[m_iAlarmOutIndex].struAlarmOutTime[i][5].byStopHour;
        m_iMin62 = m_struAlarmOutCfg[m_iAlarmOutIndex].struAlarmOutTime[i][5].byStopMin;
        m_iHour71 = m_struAlarmOutCfg[m_iAlarmOutIndex].struAlarmOutTime[i][6].byStartHour;
        m_iMin71 = m_struAlarmOutCfg[m_iAlarmOutIndex].struAlarmOutTime[i][6].byStartMin;
        m_iHour72 = m_struAlarmOutCfg[m_iAlarmOutIndex].struAlarmOutTime[i][6].byStopHour;
        m_iMin72 = m_struAlarmOutCfg[m_iAlarmOutIndex].struAlarmOutTime[i][6].byStopMin;
        m_iHour81 = m_struAlarmOutCfg[m_iAlarmOutIndex].struAlarmOutTime[i][7].byStartHour;
        m_iMin81 = m_struAlarmOutCfg[m_iAlarmOutIndex].struAlarmOutTime[i][7].byStartMin;
        m_iHour82 = m_struAlarmOutCfg[m_iAlarmOutIndex].struAlarmOutTime[i][7].byStopHour;
        m_iMin82 = m_struAlarmOutCfg[m_iAlarmOutIndex].struAlarmOutTime[i][7].byStopMin;
    }

	UpdateData(FALSE);
}

/*********************************************************
Function:	OnBnClickedBtnAlarmOutDayOk
Desc:		check and update time schedule settings
Input:	
Output:	
Return:	
**********************************************************/
void CSubDlgAlarmCfg::OnBnClickedBtnAlarmOutDayOk()
{
	UpdateData(TRUE);
	if (!TimeTest())
	{
		return;
	}

	int i = m_comboWeekday.GetCurSel();	
    if (7 == i)
    {
        m_struAlarmOutHolidayHandle.struAlarmTime[0].byStartHour = (BYTE)m_iHour11;
        m_struAlarmOutHolidayHandle.struAlarmTime[0].byStartMin = (BYTE)m_iMin11;
        m_struAlarmOutHolidayHandle.struAlarmTime[0].byStopHour = (BYTE)m_iHour12;
        m_struAlarmOutHolidayHandle.struAlarmTime[0].byStopMin = (BYTE)m_iMin12;
        m_struAlarmOutHolidayHandle.struAlarmTime[1].byStartHour = (BYTE)m_iHour21;
        m_struAlarmOutHolidayHandle.struAlarmTime[1].byStartMin = (BYTE)m_iMin21;
        m_struAlarmOutHolidayHandle.struAlarmTime[1].byStopHour = (BYTE)m_iHour22;
        m_struAlarmOutHolidayHandle.struAlarmTime[1].byStopMin = (BYTE)m_iMin22;
        m_struAlarmOutHolidayHandle.struAlarmTime[2].byStartHour = (BYTE)m_iHour31;
        m_struAlarmOutHolidayHandle.struAlarmTime[2].byStartMin = (BYTE)m_iMin31;
        m_struAlarmOutHolidayHandle.struAlarmTime[2].byStopHour = (BYTE)m_iHour32;
        m_struAlarmOutHolidayHandle.struAlarmTime[2].byStopMin = (BYTE)m_iMin32;
        m_struAlarmOutHolidayHandle.struAlarmTime[3].byStartHour = (BYTE)m_iHour41;
        m_struAlarmOutHolidayHandle.struAlarmTime[3].byStartMin = (BYTE)m_iMin41;
        m_struAlarmOutHolidayHandle.struAlarmTime[3].byStopHour = (BYTE)m_iHour42;
        m_struAlarmOutHolidayHandle.struAlarmTime[3].byStopMin = (BYTE)m_iMin42;	
        
        m_struAlarmOutHolidayHandle.struAlarmTime[4].byStartHour = (BYTE)m_iHour51;
        m_struAlarmOutHolidayHandle.struAlarmTime[4].byStartMin = (BYTE)m_iMin51;
        m_struAlarmOutHolidayHandle.struAlarmTime[4].byStopHour = (BYTE)m_iHour52;
        m_struAlarmOutHolidayHandle.struAlarmTime[4].byStopMin = (BYTE)m_iMin52;
        m_struAlarmOutHolidayHandle.struAlarmTime[5].byStartHour = (BYTE)m_iHour61;
        m_struAlarmOutHolidayHandle.struAlarmTime[5].byStartMin = (BYTE)m_iMin61;
        m_struAlarmOutHolidayHandle.struAlarmTime[5].byStopHour = (BYTE)m_iHour62;
        m_struAlarmOutHolidayHandle.struAlarmTime[5].byStopMin = (BYTE)m_iMin62;
        m_struAlarmOutHolidayHandle.struAlarmTime[6].byStartHour = (BYTE)m_iHour71;
        m_struAlarmOutHolidayHandle.struAlarmTime[6].byStartMin = (BYTE)m_iMin71;
        m_struAlarmOutHolidayHandle.struAlarmTime[6].byStopHour = (BYTE)m_iHour72;
        m_struAlarmOutHolidayHandle.struAlarmTime[6].byStopMin = (BYTE)m_iMin72;
        m_struAlarmOutHolidayHandle.struAlarmTime[7].byStartHour = (BYTE)m_iHour81;
        m_struAlarmOutHolidayHandle.struAlarmTime[7].byStartMin = (BYTE)m_iMin81;
        m_struAlarmOutHolidayHandle.struAlarmTime[7].byStopHour = (BYTE)m_iHour82;
        m_struAlarmOutHolidayHandle.struAlarmTime[7].byStopMin = (BYTE)m_iMin82;

        if (!SetAlarmOutHolidayHandle(m_struAlarmOutHolidayHandle))
        {
            AfxMessageBox("Fail to set holiday handle");
        }
    }
    else
    {
        m_struAlarmOutCfg[m_iAlarmOutIndex].struAlarmOutTime[i][0].byStartHour = (BYTE)m_iHour11;
        m_struAlarmOutCfg[m_iAlarmOutIndex].struAlarmOutTime[i][0].byStartMin = (BYTE)m_iMin11;
        m_struAlarmOutCfg[m_iAlarmOutIndex].struAlarmOutTime[i][0].byStopHour = (BYTE)m_iHour12;
        m_struAlarmOutCfg[m_iAlarmOutIndex].struAlarmOutTime[i][0].byStopMin = (BYTE)m_iMin12;
        m_struAlarmOutCfg[m_iAlarmOutIndex].struAlarmOutTime[i][1].byStartHour = (BYTE)m_iHour21;
        m_struAlarmOutCfg[m_iAlarmOutIndex].struAlarmOutTime[i][1].byStartMin = (BYTE)m_iMin21;
        m_struAlarmOutCfg[m_iAlarmOutIndex].struAlarmOutTime[i][1].byStopHour = (BYTE)m_iHour22;
        m_struAlarmOutCfg[m_iAlarmOutIndex].struAlarmOutTime[i][1].byStopMin = (BYTE)m_iMin22;
        m_struAlarmOutCfg[m_iAlarmOutIndex].struAlarmOutTime[i][2].byStartHour = (BYTE)m_iHour31;
        m_struAlarmOutCfg[m_iAlarmOutIndex].struAlarmOutTime[i][2].byStartMin = (BYTE)m_iMin31;
        m_struAlarmOutCfg[m_iAlarmOutIndex].struAlarmOutTime[i][2].byStopHour = (BYTE)m_iHour32;
        m_struAlarmOutCfg[m_iAlarmOutIndex].struAlarmOutTime[i][2].byStopMin = (BYTE)m_iMin32;
        m_struAlarmOutCfg[m_iAlarmOutIndex].struAlarmOutTime[i][3].byStartHour = (BYTE)m_iHour41;
        m_struAlarmOutCfg[m_iAlarmOutIndex].struAlarmOutTime[i][3].byStartMin = (BYTE)m_iMin41;
        m_struAlarmOutCfg[m_iAlarmOutIndex].struAlarmOutTime[i][3].byStopHour = (BYTE)m_iHour42;
        m_struAlarmOutCfg[m_iAlarmOutIndex].struAlarmOutTime[i][3].byStopMin = (BYTE)m_iMin42;	
        
        m_struAlarmOutCfg[m_iAlarmOutIndex].struAlarmOutTime[i][4].byStartHour = (BYTE)m_iHour51;
        m_struAlarmOutCfg[m_iAlarmOutIndex].struAlarmOutTime[i][4].byStartMin = (BYTE)m_iMin51;
        m_struAlarmOutCfg[m_iAlarmOutIndex].struAlarmOutTime[i][4].byStopHour = (BYTE)m_iHour52;
        m_struAlarmOutCfg[m_iAlarmOutIndex].struAlarmOutTime[i][4].byStopMin = (BYTE)m_iMin52;
        m_struAlarmOutCfg[m_iAlarmOutIndex].struAlarmOutTime[i][5].byStartHour = (BYTE)m_iHour61;
        m_struAlarmOutCfg[m_iAlarmOutIndex].struAlarmOutTime[i][5].byStartMin = (BYTE)m_iMin61;
        m_struAlarmOutCfg[m_iAlarmOutIndex].struAlarmOutTime[i][5].byStopHour = (BYTE)m_iHour62;
        m_struAlarmOutCfg[m_iAlarmOutIndex].struAlarmOutTime[i][5].byStopMin = (BYTE)m_iMin62;
        m_struAlarmOutCfg[m_iAlarmOutIndex].struAlarmOutTime[i][6].byStartHour = (BYTE)m_iHour71;
        m_struAlarmOutCfg[m_iAlarmOutIndex].struAlarmOutTime[i][6].byStartMin = (BYTE)m_iMin71;
        m_struAlarmOutCfg[m_iAlarmOutIndex].struAlarmOutTime[i][6].byStopHour = (BYTE)m_iHour72;
        m_struAlarmOutCfg[m_iAlarmOutIndex].struAlarmOutTime[i][6].byStopMin = (BYTE)m_iMin72;
        m_struAlarmOutCfg[m_iAlarmOutIndex].struAlarmOutTime[i][7].byStartHour = (BYTE)m_iHour81;
        m_struAlarmOutCfg[m_iAlarmOutIndex].struAlarmOutTime[i][7].byStartMin = (BYTE)m_iMin81;
        m_struAlarmOutCfg[m_iAlarmOutIndex].struAlarmOutTime[i][7].byStopHour = (BYTE)m_iHour82;
        m_struAlarmOutCfg[m_iAlarmOutIndex].struAlarmOutTime[i][7].byStopMin = (BYTE)m_iMin82;
        GetDlgItem(IDC_BTN_ALARM_OUT_DAY_COPY)->EnableWindow(TRUE);
    }
}

/*********************************************************
  Function:	OnBnClickedBtnAlarmOutDayCopy
  Desc:		copyselected schedule settings
  Input:	
  Output:	
  Return:	
**********************************************************/
void CSubDlgAlarmCfg::OnBnClickedBtnAlarmOutDayCopy()
{
	UpdateData(TRUE);
	int j,k = 0;
	int i = m_comboWeekday.GetCurSel();
	int m_nCopyTime = m_comboCopyDay.GetCurSel() - 1;
	m_iCopyAlarmOut = m_comboCopyAlarmOut.GetItemData(m_comboCopyAlarmOut.GetCurSel());	

	m_iAlarmOutIndex = m_comboAlarmOut.GetItemData(m_comboAlarmOut.GetCurSel());
	if (m_nCopyTime == -1)
	{
		for (j=0; j<MAX_DAYS; j++)
		{
			if (j == i)
			{
				continue;
			}
			for (k=0; k<MAX_TIMESEGMENT_V30; k++)
			{
				memcpy(&(m_struAlarmOutCfg[m_iAlarmOutIndex].struAlarmOutTime[j][k]), &(m_struAlarmOutCfg[m_iAlarmOutIndex].struAlarmOutTime[i][k]), sizeof(NET_DVR_SCHEDTIME));
			}
		}
	}
    else if (7 == m_nCopyTime)
    {
        for (k=0; k<MAX_TIMESEGMENT_V30; k++)
        {
            memcpy(&(m_struAlarmOutHolidayHandle.struAlarmTime[k]), &(m_struAlarmOutCfg[m_iAlarmOutIndex].struAlarmOutTime[i][k]), sizeof(NET_DVR_SCHEDTIME));
        }
    }
	else
	{
		for (k=0; k<MAX_TIMESEGMENT_V30; k++)
		{
			memcpy(&(m_struAlarmOutCfg[m_iAlarmOutIndex].struAlarmOutTime[m_nCopyTime][k]), &(m_struAlarmOutCfg[m_iAlarmOutIndex].struAlarmOutTime[i][k]), sizeof(NET_DVR_SCHEDTIME));
		}
	}
}

/*********************************************************
  Function:	OnBnClickedBtnAlarmOutCopy
  Desc:		copy selected alarm out settings
  Input:	
  Output:	
  Return:	
**********************************************************/
void CSubDlgAlarmCfg::OnBnClickedBtnAlarmOutCopy()
{
	UpdateData(TRUE);
//	CString sTemp;
	m_struAlarmOutCfg[m_iAlarmOutIndex].dwAlarmOutDelay = m_comboAlarmOutDelay.GetCurSel();
	//m_comboAlarmOut.GetLBText(m_iAlarmOutIndex, sTemp);
	memcpy(m_struAlarmOutCfg[m_iAlarmOutIndex].sAlarmOutName, m_csAlarmOutName, NAME_LEN);

	int i;
	m_iCopyAlarmOut = m_comboCopyAlarmOut.GetItemData(m_comboCopyAlarmOut.GetCurSel());	

	if (m_iCopyAlarmOut == -1)
	{
		for (i=0; i<(int)MAX_ALARMOUT_V30; i++)
		{
			
			if ( i < MAX_ANALOG_ALARMOUT && i >= (int)m_dwAlarmOutNum )
			{
				continue;
			}
			if ( i>=MAX_ANALOG_ALARMOUT )
			{//Alarm channel not exist
				if (g_struDeviceInfo[m_iDeviceIndex].struAlarmOutCfg.struIPAlarmOutInfo[i-MAX_ANALOG_ALARMOUT].byIPID == 0)
				{
					continue;
				}
			}
			if (m_iAlarmOutIndex == i) 
			{
				continue;		
			}
			memcpy(&(m_struAlarmOutCfg[i]), &(m_struAlarmOutCfg[m_iAlarmOutIndex]), sizeof(NET_DVR_ALARMOUTCFG_V30));
			m_bSetAlarmOut[i] = TRUE;
			g_bMustReboot = TRUE;
		}
	}
	else
	{	
		memcpy(&(m_struAlarmOutCfg[m_iCopyAlarmOut]), &(m_struAlarmOutCfg[m_iAlarmOutIndex]), sizeof(NET_DVR_ALARMOUTCFG_V30));
		m_bSetAlarmOut[m_iCopyAlarmOut] = TRUE;
		g_bMustReboot = TRUE;
	}	
}

/*********************************************************
Function:	TimeTest
Desc:		cgeck time schedule
Input:	
Output:	
Return:	TRUE,correct schedule;FALSE,incorrect schedule;
**********************************************************/
BOOL CSubDlgAlarmCfg::TimeTest()
{
	int i = 0;
	int j = 0;
	WORD wStartTime[MAX_TIMESEGMENT_V30], wStopTime[MAX_TIMESEGMENT_V30];
	char szLan[128] = {0};
	UpdateData(TRUE);
	if ((m_iHour11 < 0) || (m_iHour11 > 24) || (m_iHour12 < 0) || (m_iHour12 > 24) ||	\
		(m_iHour21 < 0) || (m_iHour21 > 24) || (m_iHour22 < 0) || (m_iHour22 > 24) ||	\
		(m_iHour31 < 0) || (m_iHour31 > 24) || (m_iHour32 < 0) || (m_iHour32 > 24) ||	\
		(m_iHour41 < 0) || (m_iHour41 > 24) || (m_iHour42 < 0) || (m_iHour42 > 24) ||   \
		(m_iHour51 < 0) || (m_iHour51 > 24) || (m_iHour52 < 0) || (m_iHour52 > 24) ||	\
		(m_iHour61 < 0) || (m_iHour61 > 24) || (m_iHour62 < 0) || (m_iHour62 > 24) ||	\
		(m_iHour71 < 0) || (m_iHour71 > 24) || (m_iHour72 < 0) || (m_iHour72 > 24) ||	\
		(m_iHour81 < 0) || (m_iHour81 > 24) || (m_iHour82 < 0) || (m_iHour82 > 24))
	{
		g_StringLanType(szLan, "小时范围在0 -- 24之间", "Hour between 0 - 24 ");
		AfxMessageBox(szLan);
		return FALSE;
	}
	if ((m_iMin11 < 0) || (m_iMin11 > 60) || (m_iMin12 < 0) || (m_iMin12 > 60) ||	\
		(m_iMin21 < 0) || (m_iMin21 > 60) || (m_iMin22 < 0) || (m_iMin22 > 60) ||	\
		(m_iMin31 < 0) || (m_iMin31 > 60) || (m_iMin32 < 0) || (m_iMin32 > 60) ||	\
		(m_iMin41 < 0) || (m_iMin41 > 60) || (m_iMin42 < 0) || (m_iMin42 > 60) ||   \
		(m_iMin51 < 0) || (m_iMin51 > 60) || (m_iMin52 < 0) || (m_iMin52 > 60) ||	\
		(m_iMin61 < 0) || (m_iMin61 > 60) || (m_iMin62 < 0) || (m_iMin62 > 60) ||	\
		(m_iMin71 < 0) || (m_iMin71 > 60) || (m_iMin72 < 0) || (m_iMin72 > 60) ||	\
		(m_iMin81 < 0) || (m_iMin81 > 60) || (m_iMin82 < 0) || (m_iMin82 > 60))
	{
		g_StringLanType(szLan, "分钟范围在0 -- 60之间", "Minute between 0 - 60 ");
		AfxMessageBox(szLan);
		return FALSE;
	}
	wStartTime[0] = (WORD)(m_iHour11 * 100 + m_iMin11);
	wStartTime[1] = (WORD)(m_iHour21 * 100 + m_iMin21);
	wStartTime[2] = (WORD)(m_iHour31 * 100 + m_iMin31);
	wStartTime[3] = (WORD)(m_iHour41 * 100 + m_iMin41);
	wStopTime[0] = (WORD)(m_iHour12 * 100 + m_iMin12);
	wStopTime[1] = (WORD)(m_iHour22 * 100 + m_iMin22);
	wStopTime[2] = (WORD)(m_iHour32 * 100 + m_iMin32);
	wStopTime[3] = (WORD)(m_iHour42 * 100 + m_iMin42);
	wStartTime[4] = (WORD)(m_iHour51 * 100 + m_iMin51);
	wStartTime[5] = (WORD)(m_iHour61 * 100 + m_iMin61);
	wStartTime[6] = (WORD)(m_iHour71 * 100 + m_iMin71);
	wStartTime[7] = (WORD)(m_iHour81 * 100 + m_iMin81);
	wStopTime[4] = (WORD)(m_iHour52 * 100 + m_iMin52);
	wStopTime[5] = (WORD)(m_iHour62 * 100 + m_iMin62);
	wStopTime[6] = (WORD)(m_iHour72 * 100 + m_iMin72);
	wStopTime[7] = (WORD)(m_iHour82 * 100 + m_iMin82);
	for (i = 0; i < MAX_TIMESEGMENT_V30; i++)
	{
		if ((wStartTime[i] > 2400) || (wStopTime[i] > 2400))
		{
			g_StringLanType(szLan, "布防时间不能超过24:00", "Fortify time can not be more than 24:00");
			AfxMessageBox(szLan);
			return FALSE;
		}
		if (wStartTime[i] > wStopTime[i])
		{
			g_StringLanType(szLan, "布防起始时间不能大于停止时间", "Fortify start time can not be larger than the record to stop time");
			AfxMessageBox(szLan);
			return FALSE;
		}
		for (j = 0; j < MAX_TIMESEGMENT_V30; j++)
		{
			if (i == j)
			{
				continue;
			}
			if ((wStartTime[i] > wStartTime[j]) && (wStartTime[i] < wStopTime[j]) ||	\
				(wStopTime[i] > wStartTime[j]) && (wStopTime[i] < wStopTime[j]))
			{
				g_StringLanType(szLan, "时间段不能重复", "time can not be repeated");
				AfxMessageBox(szLan);
				return FALSE;
			}
		}
	}
	return TRUE;
}

/*********************************************************
  Function:	CfgSetup
  Desc:		Set alarm configuration
  Input:	
  Output:	
  Return:	TRUE,settng succeed;FALSE,setting failed;
**********************************************************/
BOOL CSubDlgAlarmCfg::CfgSetup()
{
	CString sTemp;
	int i = 0;
	char szLan[128] = {0};
	for (i=0; i<(int)MAX_ALARMIN_V30; i++)//m_dwAlarmInNum
	{
		if (m_bSetAlarmIn[i])
		{
			if (!NET_DVR_SetDVRConfig(m_lLoginID, NET_DVR_SET_ALARMINCFG_V30, i, &(m_struAlarmInCfg[i]), sizeof(NET_DVR_ALARMINCFG_V30)))
			{
				g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_ALARMINCFG_V30 alarmin index[%d]", i); 	
				g_StringLanType(szLan, "参数保存失败", "parameter save failed");
				AfxMessageBox(szLan);	
				return FALSE;	
			}
			else
			{
				g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_ALARMINCFG_V30 alarmin index[%d]", i); 
			}
			m_bSetAlarmIn[i] = FALSE;
		}
	}
	for (i=0; i<(int)MAX_ALARMOUT_V30; i++)//m_dwAlarmOutNum
	{
		if (m_bSetAlarmOut[i])
		{
			if (!NET_DVR_SetDVRConfig(m_lLoginID, NET_DVR_SET_ALARMOUTCFG_V30, i, &(m_struAlarmOutCfg[i]), sizeof(NET_DVR_ALARMOUTCFG_V30)))
			{
				g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_ALARMOUTCFG_V30 alarmout index[%d]", i); 
				g_StringLanType(szLan, "参数保存失败", "parameter save failed");
				AfxMessageBox(szLan);	
				return FALSE;	
			}
			else
			{
				g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_ALARMOUTCFG_V30 alarmout index[%d]", i); 
			}
			m_bSetAlarmOut[i] = FALSE;
		}

	}
	g_bMustReboot = g_pMainDlg->IsNeedRebootDevType();
	return TRUE;	
}

/*********************************************************
Function:	GetAlarmInOutGroupNum
Desc:		GetAlarmInOutGroupNum 
Input:	
Output:	
Return:	TRUE: succeed; FALSE: failed;
**********************************************************/
BOOL CSubDlgAlarmCfg::GetAlarmInOutGroupNum()
{
	BOOL bRet = false;
	DWORD dwReturned = 0;
	CString sTemp;
	
	memset(&m_struIPAlarmInOutNum, 0, sizeof(m_struIPAlarmInOutNum));
	m_struIPAlarmInOutNum.dwSize = sizeof(m_struIPAlarmInOutNum);
	
	bRet = NET_DVR_GetDVRConfig(g_struDeviceInfo[m_iDeviceIndex].lLoginID, NET_DVR_GET_IP_ALARM_GROUP_NUM, 0, &m_struIPAlarmInOutNum, sizeof(m_struIPAlarmInOutNum), &dwReturned);
	if (bRet)
	{
		//only the newest device: nvr(after 2011-9-300);
		m_bSupportMultiGroupAlarm = true;
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_IP_ALARM_GROUP_NUM");
	} 
	else
	{
		m_bSupportMultiGroupAlarm = false;
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_IP_ALARM_GROUP_NUM");
	}
	
	int i = 0;
	m_comboAlarmInGroupNO.ResetContent();
	for (i = 0; i <= m_struIPAlarmInOutNum.dwIPAlarmInGroup; i++)
	{
		sTemp.Format("%d", i);
		m_comboAlarmInGroupNO.AddString(sTemp);
	}
	
	m_comboAlarmOutGroupNO.ResetContent();
	for (i = 0; i <= m_struIPAlarmInOutNum.dwIPAlarmOutGroup; i++)
	{
		sTemp.Format("%d", i);
		m_comboAlarmOutGroupNO.AddString(sTemp);
	}
	
	m_comboAlarmInGroupNO.SetCurSel(0);
	m_comboAlarmOutGroupNO.SetCurSel(0);
	
	return bRet;
}

/*********************************************************
Function:	OnBtnSetState
Desc:		set state 
Input:	
Output:	
Return:	none
**********************************************************/
void CSubDlgAlarmCfg::OnBtnSetState() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	if (NET_DVR_SetAlarmOut(g_struDeviceInfo[m_iDeviceIndex].lLoginID, m_iAlarmOutIndex, m_iState))
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SetAlarmOut out%d[%d]", m_iAlarmOutIndex, m_iState);
	}
}

/*********************************************************
Function:	GetAlarmOutHolidayHandle
Desc:		Get the holiday of alarm in. 
Input:	
Output:	
Return:	none
**********************************************************/
BOOL CSubDlgAlarmCfg::GetAlarmOutHolidayHandle(NET_DVR_HOLIDAY_HANDLE &struHolidayHandle)
{
    DWORD dwReturn = 0;
    if (NET_DVR_GetDVRConfig(m_lLoginID, NET_DVR_GET_ALARMOUT_HOLIDAY_HANDLE, m_iAlarmOutIndex, &struHolidayHandle,sizeof(struHolidayHandle), &dwReturn))
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_ALARMOUT_HOLIDAY_HANDLE");
        return TRUE;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_ALARMOUT_HOLIDAY_HANDLE");
        return FALSE;
    }
}

/*********************************************************
Function:	GetAlarmOutHolidayHandle
Desc:		Set the holiday of alarm out. 
Input:	
Output:	
Return:	none
**********************************************************/
BOOL CSubDlgAlarmCfg::SetAlarmOutHolidayHandle(NET_DVR_HOLIDAY_HANDLE &struHolidayHandle)
{
    DWORD dwReturn = 0;
    if (NET_DVR_SetDVRConfig(m_lLoginID, NET_DVR_SET_ALARMOUT_HOLIDAY_HANDLE, m_iAlarmOutIndex, &struHolidayHandle,sizeof(struHolidayHandle)))
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_ALARMOUT_HOLIDAY_HANDLE");
        return TRUE;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_ALARMOUT_HOLIDAY_HANDLE");
        return FALSE;
    }
}

/*********************************************************
Function:	GetAlarmOutHolidayHandle
Desc:		Select the group NO of alarm in. 
Input:	
Output:	
Return:	none
**********************************************************/
void CSubDlgAlarmCfg::OnSelchangeComboAlarminGroupNo() 
{
	// TODO: Add your control notification handler code here
	m_iIPAlarmInGroupNO = m_comboAlarmInGroupNO.GetCurSel();
	CheckInitParam(false, m_iIPAlarmInGroupNO, m_iIPAlarmOutGroupNO);
}

/*********************************************************
Function:	GetAlarmOutHolidayHandle
Desc:		Select the group NO of alarm out. 
Input:	
Output:	
Return:	none
**********************************************************/
void CSubDlgAlarmCfg::OnSelchangeComboAlarmoutGroupNo() 
{
	// TODO: Add your control notification handler code here
	m_iIPAlarmOutGroupNO = m_comboAlarmOutGroupNO.GetCurSel();
	CheckInitParam(false, m_iIPAlarmInGroupNO, m_iIPAlarmOutGroupNO);
}