/**********************************************************
FileName:    DlgLocalConfig.cpp
Description: local configuration     
Date:        2008/05/17
Note: 		 <global>struct, refer to GeneralDef.h, global variants and functions refer to ClientDemo.cpp   
Modification History:      
    <version> <time>         <desc>
    <1.0    > <2008/05/17>       <created>
***********************************************************/


#include "stdafx.h"
#include "ClientDemo.h"
#include "DlgLocalConfig.h"
#include ".\dlglocalconfig.h"
#include "DlgLocalRecordSchedule.h"
#include ".\clientdemodlg.h"


// CDlgLocalConfig dialog
/*********************************************************
  Function:	CDlgLocalConfig
  Desc:		Constructor
  Input:	
  Output:	
  Return:	
**********************************************************/
IMPLEMENT_DYNAMIC(CDlgLocalConfig, CDialog)
CDlgLocalConfig::CDlgLocalConfig(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgLocalConfig::IDD, pParent)
	, m_iCycleTime(5)
	, m_iFileInterval(1)
	, m_csDownLoadPath(_T(""))
	, m_csPicSnatchPath(_T(""))
	, m_csLogPath(_T(""))
	, m_ctimeCheckDeviceTime(0)
	, m_bCyclePlay(FALSE)
	, m_bAutoRecord(FALSE)
	, m_bCycleRecord(FALSE)
	, m_bUseCard(FALSE)
	, m_bChkDeviceTime(FALSE)
	, m_iListenPort(7200)
	, m_lListenHandle(-1)
    , m_bWriteSdkLog(FALSE)
{
    m_strSdklog = "c:\\sdklog\\";
}
/*********************************************************
  Function:	~CDlgLocalConfig
  Desc:		destructor
  Input:	
  Output:	
  Return:	
**********************************************************/
CDlgLocalConfig::~CDlgLocalConfig()
{
}

/*********************************************************
Function:	DoDataExchange
Desc:		the map between control and variable
Input:	
Output:	
Return:	
**********************************************************/
void CDlgLocalConfig::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgLocalConfig)
	DDX_Control(pDX, IDC_COMBO_IPADDRESS, m_AllAddressCtrl);
	DDX_Control(pDX, IDC_COMBO_SDK_LOG, m_comboSDKLog);
	DDX_Control(pDX, IDC_COMBO_B_FRAME, m_comboBFrame);
	DDX_Control(pDX, IDC_COMBO_SOUND_MODE, m_comboSoundMode);
	DDX_Control(pDX, IDC_CHK_CYCLE_PLAY, m_chkCyclePlay);
	DDX_Control(pDX, IDC_CHK_USE_CARD, m_chkUseCard);
	DDX_Text(pDX, IDC_EDIT_CYCLE_TIME, m_iCycleTime);
	DDX_Control(pDX, IDC_CHK_AUTO_RECORD, m_chkAutoRecord);
	DDX_Control(pDX, IDC_CHK_CYCLE_RECORD, m_chkCycleRecord);
	DDX_Control(pDX, IDC_COMBO_FIRST_DISK, m_comboRecFirstDisk);
	DDX_Control(pDX, IDC_COMBO_LAST_DISK, m_comboRecLastDisk);
	DDX_Text(pDX, IDC_EDIT_FILE_INTERVAL, m_iFileInterval);
	DDX_Text(pDX, IDC_EDIT_DOWNLOAD_PATH, m_csDownLoadPath);
	DDX_Text(pDX, IDC_EDIT_PIC_PATH, m_csPicSnatchPath);
	DDX_Text(pDX, IDC_EDIT_LOG_PATH, m_csLogPath);
	DDX_Control(pDX, IDC_CHK_SYSTIME, m_chkSysTime);
	DDX_DateTimeCtrl(pDX, IDC_DATETIME_PICKER, m_ctimeCheckDeviceTime);
	DDX_Check(pDX, IDC_CHK_CYCLE_PLAY, m_bCyclePlay);
	DDX_Check(pDX, IDC_CHK_AUTO_RECORD, m_bAutoRecord);
	DDX_Check(pDX, IDC_CHK_CYCLE_RECORD, m_bCycleRecord);
	DDX_Check(pDX, IDC_CHK_USE_CARD, m_bUseCard);
	DDX_Check(pDX, IDC_CHK_SYSTIME, m_bChkDeviceTime);
	DDX_Control(pDX, IDC_DATETIME_PICKER, m_ctCheckTime);
	DDX_Control(pDX, IDC_COMBO_VIDEO_FORMAT, m_comboVideoFormat);
	DDX_Check(pDX, IDC_CHK_NO_DECODE, m_bChkNoDecode);
	DDX_Check(pDX, IDC_CHK_PREVIEW_BLOCK, m_bBlock);
	DDX_Text(pDX, IDC_EDIT_RECV_TIMEOUT, m_iTimeOut);
	DDV_MinMaxInt(pDX, m_iTimeOut, 1, 120000);
	DDX_Text(pDX, IDC_EDIT_SDKLOG, m_strSdklog);
	DDX_Check(pDX, IDC_CHECK_CYCLEWRITE, m_bWriteSdkLog);
	DDX_Check(pDX, IDC_CHECK_RECONNECT, m_bReconnect);
	DDX_Text(pDX, IDC_EDIT_LISETN_PORT, m_iListenPort);
	//}}AFX_DATA_MAP

}

/*********************************************************
  Function:	BEGIN_MESSAGE_MAP
  Desc:		map between message and function
  Input:	
  Output:	
  Return:	
**********************************************************/
BEGIN_MESSAGE_MAP(CDlgLocalConfig, CDialog)
	//{{AFX_MSG_MAP(CDlgLocalConfig)	
	ON_BN_CLICKED(IDC_BTN_SELECT_DOWNLOAD_PATH, OnBnClickedBtnSelectDownLoadPath)
	ON_BN_CLICKED(IDC_LOCAL_OK, OnBnClickedLocalOk)
	ON_BN_CLICKED(IDC_CHK_CYCLE_PLAY, OnBnClickedChkCyclePlay)
	ON_BN_CLICKED(IDC_CHK_AUTO_RECORD, OnBnClickedChkAutoRecord)
	ON_BN_CLICKED(IDC_BTN_SET_TIME, OnBnClickedBtnSetTime)
	ON_BN_CLICKED(IDC_BTN_SELECT_PIC_PATH, OnBnClickedBtnSelectPicPath)
	ON_BN_CLICKED(IDC_BTN_SELECT_LOG_PATH, OnBnClickedBtnSelectLogPath)
	ON_BN_CLICKED(IDC_CHK_SYSTIME, OnBnClickedChkSystime)
	ON_BN_CLICKED(IDC_CHK_USE_CARD, OnBnClickedChkUseCard)
	ON_CBN_SELCHANGE(IDC_COMBO_SOUND_MODE, OnSelchangeComboSoundMode)
	ON_BN_CLICKED(IDC_BUTTON_START_LISTEN, OnButtonStartListen)
	ON_BN_CLICKED(IDC_BUTTON_STOP_LISTEN, OnButtonStopListen)
	ON_BN_CLICKED(IDC_BUTTON_REFRUSH, OnButtonRefrush)
	ON_BN_CLICKED(IDC_BTN_SELECT_SDKLOG_PATH, OnBtnSelectSdklogPath)
	ON_BN_CLICKED(IDC_BTN_BIND_IP, OnBtnBindIp)
	//}}AFX_MSG_MAP

END_MESSAGE_MAP()


// CDlgLocalConfig message handlers
/*********************************************************
Function:	OnInitDialog
Desc:		Initialize the dialog
Input:	
Output:	
Return:	
**********************************************************/
BOOL CDlgLocalConfig::OnInitDialog()
{
	CDialog::OnInitDialog();
	int i = 0;
	m_comboSoundMode.SetCurSel(g_bShareSound);
	m_bCyclePlay = g_struLocalParam.bCyclePlay;
	if (m_bCyclePlay)
	{
		GetDlgItem(IDC_EDIT_CYCLE_TIME)->EnableWindow(TRUE);
	}
	else
	{
		GetDlgItem(IDC_EDIT_CYCLE_TIME)->EnableWindow(FALSE);
	}

	m_iCycleTime = g_struLocalParam.iCycleTime;
	m_bUseCard = g_struLocalParam.bUseCard;
	m_bChkNoDecode = g_struLocalParam.bNoDecode;
	m_bBlock = g_struLocalParam.bPreviewBlock;
	m_comboVideoFormat.SetCurSel(g_struLocalParam.bNTSC);//
	m_comboBFrame.SetCurSel(g_struLocalParam.dwBFrameNum);

	if (m_bUseCard)
	{
		GetDlgItem(IDC_COMBO_VIDEO_FORMAT)->EnableWindow(TRUE);
	}
	else
	{
		GetDlgItem(IDC_COMBO_VIDEO_FORMAT)->EnableWindow(FALSE);
	}

	CString csHardDriver;
	for (i = 0; i < (int)(g_pMainDlg->m_iDriverNum); i++)
	{
		csHardDriver.Format("%c%s", g_pMainDlg->m_cHardDriver[i], ":\\");
		m_comboRecFirstDisk.AddString(csHardDriver);
		m_comboRecLastDisk.AddString(csHardDriver);
	}
	m_comboRecFirstDisk.SetCurSel(g_struLocalParam.iStartRecordDriver);
	m_comboRecLastDisk.SetCurSel(g_struLocalParam.iEndRecordDriver);

	m_iFileInterval = g_struLocalParam.iRecordFileInterval;
	m_bCycleRecord = g_struLocalParam.bCycleRecord;
	m_bAutoRecord = g_struLocalParam.bAutoRecord;

	if (m_bAutoRecord)
	{
		GetDlgItem(IDC_BTN_SET_TIME)->EnableWindow(TRUE);
	}
	else
	{
		GetDlgItem(IDC_BTN_SET_TIME)->EnableWindow(FALSE);
	}

	m_csDownLoadPath.Format("%s",g_struLocalParam.chDownLoadPath);
	m_csPicSnatchPath.Format("%s",g_struLocalParam.chPictureSavePath);
	m_csLogPath.Format("%s",g_struLocalParam.chRemoteCfgSavePath);
	m_bChkDeviceTime = g_struLocalParam.bAutoCheckDeviceTime;
	CTime ctTime(2008, 7, 17, g_struLocalParam.lCheckDeviceTime/10000, (g_struLocalParam.lCheckDeviceTime%10000)/100, g_struLocalParam.lCheckDeviceTime%100);
	m_ctimeCheckDeviceTime = ctTime;
	m_comboSDKLog.SetCurSel(g_struLocalParam.nLogLevel);
	m_iTimeOut = g_struLocalParam.nTimeout;
	if (m_bChkDeviceTime)
	{
		GetDlgItem(IDC_DATETIME_PICKER)->EnableWindow(TRUE);
	}
	else
	{
		GetDlgItem(IDC_DATETIME_PICKER)->EnableWindow(FALSE);
	}

    char sAllIp[16][16] = {0};
    DWORD dwIpNum = 0;
    BOOL bBind = FALSE;
    if (!NET_DVR_GetLocalIP(sAllIp, &dwIpNum, &bBind))
    {
        MessageBox(NET_DVR_GetErrorMsg());
        return FALSE;
    }
    
    for (i = 0; i < dwIpNum; i++)
    {
        m_AllAddressCtrl.AddString(sAllIp[i]);
    }
    m_AllAddressCtrl.SetCurSel(0);

    m_bWriteSdkLog = g_struLocalParam.bCycleWriteLog;
    m_bReconnect = g_struLocalParam.bReconnect;
	UpdateData(FALSE);
	return TRUE;
}

/*********************************************************
  Function:	GetDirectoryPath
  Desc:		get directory pathe
  Input:	
  Output:	
  Return:	
**********************************************************/
CString CDlgLocalConfig::GetDirectoryPath()
{
	LPITEMIDLIST pidlRoot=NULL;
	SHGetSpecialFolderLocation(m_hWnd,CSIDL_DRIVES,&pidlRoot);
	BROWSEINFO bi;   //the input parameters needed
	CString strDisplayName;  
	bi.hwndOwner=GetSafeHwnd();   //get handle value of parent window 
	bi.pidlRoot=pidlRoot;   
	bi.pszDisplayName=strDisplayName.GetBuffer(MAX_PATH+1);   //get buffer pointer
	char szLan[32] = {0};
	g_StringLanType(szLan, "文件夹", "Directory");
	bi.lpszTitle=szLan;   //set title
	bi.ulFlags=BIF_RETURNONLYFSDIRS;   //set flag
	bi.lpfn=NULL;
	bi.lParam=0;
	bi.iImage=0;   //The above parameters are not related to the settings, better set up,
	LPITEMIDLIST lpIDList= SHBrowseForFolder(&bi);	//open dialog
	strDisplayName.ReleaseBuffer();   //correspond to GetBuffer()
	char pPath[MAX_PATH];
	CString Str;
	if (lpIDList)
	{
		SHGetPathFromIDList (lpIDList, pPath);
		Str=pPath;
	}
	return Str;
}

/*********************************************************
  Function:	OnBnClickedLocalOk
  Desc:		finish local configuration
  Input:	
  Output:	
  Return:	
**********************************************************/
void CDlgLocalConfig::OnBnClickedLocalOk()
{
	int i = 0, j = 0;
	char szLan[32] = {0};
	UpdateData(TRUE);
	if ((m_iFileInterval < 1) || (m_iFileInterval > 60))
	{
		g_StringLanType(szLan, "非法的文件打包时间!", "Illegal file packing time");
		AfxMessageBox(szLan);
		return;
	}
	if ((m_csDownLoadPath == "") || (m_csPicSnatchPath == "") || (m_csLogPath == ""))
	{
		g_StringLanType(szLan, "请选择文件保存路径!", "Please select the file path");
		AfxMessageBox(szLan);
		return;
	}


	i = m_comboRecFirstDisk.GetCurSel();
	j = m_comboRecLastDisk.GetCurSel();
	if (i > j)
	{
		g_StringLanType(szLan, "起始驱动器和终止驱动器不匹配!", "First drive and last drive is mismatch");
		AfxMessageBox(szLan);
		return;
	}

	if (m_iCycleTime < 5)
	{
		m_iCycleTime = 5;
	}
	g_struLocalParam.bCyclePlay = m_bCyclePlay;
	g_struLocalParam.iCycleTime = m_iCycleTime;
	if (g_struLocalParam.bUseCard != m_bUseCard)
	{
		if (!g_struLocalParam.bUseCard)
		{
			g_bCardInit = FALSE;
		}
		else
		{
			g_bCardInit = TRUE;
		}
	}
	g_struLocalParam.bUseCard = m_bUseCard;
	g_struLocalParam.bNTSC = m_comboVideoFormat.GetCurSel();

	g_struLocalParam.bAutoRecord = m_bAutoRecord;
	g_struLocalParam.bCycleRecord = m_bCycleRecord;
	g_struLocalParam.iRecordFileInterval = m_iFileInterval;

	g_struLocalParam.iStartRecordDriver = i;
	g_struLocalParam.iEndRecordDriver = j;
	g_struLocalParam.bNoDecode = m_bChkNoDecode;
	g_struLocalParam.bPreviewBlock = m_bBlock;
	g_struLocalParam.dwBFrameNum = m_comboBFrame.GetCurSel();

	sprintf(g_struLocalParam.chDownLoadPath, "%s", m_csDownLoadPath.GetBuffer(0));
	sprintf(g_struLocalParam.chPictureSavePath, "%s", m_csPicSnatchPath.GetBuffer(0));
	sprintf(g_struLocalParam.chRemoteCfgSavePath, "%s", m_csLogPath.GetBuffer(0));
	g_struLocalParam.bAutoCheckDeviceTime = m_bChkDeviceTime;
	g_struLocalParam.lCheckDeviceTime = m_ctimeCheckDeviceTime.GetHour()*10000 + m_ctimeCheckDeviceTime.GetMinute()*100 + m_ctimeCheckDeviceTime.GetSecond();
	g_struLocalParam.nLogLevel = m_comboSDKLog.GetCurSel();
    g_struLocalParam.bCycleWriteLog = m_bWriteSdkLog;

    g_struLocalParam.bReconnect = m_bReconnect;
    NET_DVR_SetReconnect(0, g_struLocalParam.bReconnect);
    char sLogPath[256] = {0};
    strncpy(sLogPath, m_strSdklog, 256);
	NET_DVR_SetLogToFile(g_struLocalParam.nLogLevel, sLogPath);
	g_struLocalParam.nTimeout = m_iTimeOut;
	NET_DVR_SetRecvTimeOut(m_iTimeOut);
	//NET_DVR_SetLogPrint(TRUE);
	//NET_DVR_SetLogPrintAction(g_struLocalParam.nLogLevel, 1, 0, 0, 0);
	//initial operation after conform
	WriteLocalConfig();
}

/*********************************************************
  Function:	OnBnClickedChkCyclePlay
  Desc:		whether cycle play response function
  Input:	
  Output:	
  Return:	
**********************************************************/
void CDlgLocalConfig::OnBnClickedChkCyclePlay()
{
	if (m_chkCyclePlay.GetCheck() == 1)
	{
		GetDlgItem(IDC_EDIT_CYCLE_TIME)->EnableWindow(TRUE);
	}
	else
	{
		GetDlgItem(IDC_EDIT_CYCLE_TIME)->EnableWindow(FALSE);
	}
}

/*********************************************************
  Function:	OnBnClickedChkAutoRecord
  Desc:		whether auto record response function
  Input:	
  Output:	
  Return:	
**********************************************************/
void CDlgLocalConfig::OnBnClickedChkAutoRecord()
{
	if (m_chkAutoRecord.GetCheck() == 1)
	{
		GetDlgItem(IDC_BTN_SET_TIME)->EnableWindow(TRUE);
		g_pMainDlg->IsDiskFull();
	}
	else
	{
		GetDlgItem(IDC_BTN_SET_TIME)->EnableWindow(FALSE);
	}
}

/*********************************************************
  Function:	OnBnClickedBtnSetTime
  Desc:		set auto record time
  Input:	
  Output:	
  Return:	
**********************************************************/
void CDlgLocalConfig::OnBnClickedBtnSetTime()
{
	CDlgLocalRecordSchedule	dlgLocalRecordSchedule;
	dlgLocalRecordSchedule.DoModal();
}

/*********************************************************
  Function:	OnBnClickedBtnSelectDownLoadPath
  Desc:		choose download path response function
  Input:	
  Output:	
  Return:	
**********************************************************/
void CDlgLocalConfig::OnBnClickedBtnSelectDownLoadPath()
{
	CString csPath = GetDirectoryPath();
	if (csPath != "")
	{
		m_csDownLoadPath = csPath;
		UpdateData(FALSE);
	}
}

/*********************************************************
  Function:	OnBnClickedBtnSelectPicPath
  Desc:		choose pic save path response function
  Input:	
  Output:	
  Return:	
**********************************************************/
void CDlgLocalConfig::OnBnClickedBtnSelectPicPath()
{
	CString csPath = GetDirectoryPath();
	if (csPath != "")
	{
		m_csPicSnatchPath = csPath;
		UpdateData(FALSE);
	}
}

/*********************************************************
  Function:	OnBnClickedBtnSelectLogPath
  Desc:		choose log file save path
  Input:	
  Output:	
  Return:	
**********************************************************/
void CDlgLocalConfig::OnBnClickedBtnSelectLogPath()
{
	CString csPath = GetDirectoryPath();
	if (csPath != "")
	{
		m_csLogPath = csPath;
		UpdateData(FALSE);
	}
}

/*********************************************************
  Function:	OnBnClickedChkSystime
  Desc:		whether check system time
  Input:	
  Output:	
  Return:	
**********************************************************/
void CDlgLocalConfig::OnBnClickedChkSystime()
{
	UpdateData(TRUE);
	if (m_bChkDeviceTime)
	{
		GetDlgItem(IDC_DATETIME_PICKER)->EnableWindow(TRUE);
	}
	else
	{
		GetDlgItem(IDC_DATETIME_PICKER)->EnableWindow(FALSE);
	}
}

/*********************************************************
  Function:	OnBnClickedChkUseCard
  Desc:		use card to decode the stream and enable the control or not
  Input:	none
  Output:	none
  Return:	none
**********************************************************/
void CDlgLocalConfig::OnBnClickedChkUseCard()
{
	UpdateData(TRUE);
	GetDlgItem(IDC_COMBO_VIDEO_FORMAT)->EnableWindow(m_bUseCard);
}

void CDlgLocalConfig::OnSelchangeComboSoundMode() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	g_bShareSound = m_comboSoundMode.GetCurSel();
	if (!g_bShareSound)
	{
		NET_DVR_SetAudioMode(MONOPOLIZE_MODE);
		g_bShareSound = FALSE;
		g_pMainDlg->AddLog(-1, OPERATION_SUCC_T, "MONOPOLIZE_MODE");
	}
	else
	{
		NET_DVR_SetAudioMode(SHARE_MODE);
		g_pMainDlg->AddLog(-1, OPERATION_SUCC_T, "SHARE_MODE");
		g_bShareSound = TRUE;
	}	
}

// void CDlgLocalConfig::OnChkDefaultIp() 
// {
// 	UpdateData(TRUE);
// 	GetDlgItem(IDC_EDIT_LISTEN_IP)->ShowWindow(!m_bDefaultListenIP);
// }

void CDlgLocalConfig::OnButtonStartListen() 
{
	UpdateData(TRUE);

    char sIP[64] = {0};
    int sel = m_AllAddressCtrl.GetLBText(m_AllAddressCtrl.GetCurSel(), sIP);

    if(m_lListenHandle == -1)
    {
        m_lListenHandle = NET_DVR_StartListen_V30(sIP, m_iListenPort, MessageCallback, NULL);
        if(m_lListenHandle < 0)
		{
			m_lListenHandle = -1;
	    	g_pMainDlg->AddLog(-1, OPERATION_FAIL_T, "NET_DVR_StartListen_V30");
		}
		else
		{
	    	g_pMainDlg->AddLog(-1, OPERATION_SUCC_T, "NET_DVR_StartListen_V30");
		}
	}
}

void CDlgLocalConfig::OnButtonStopListen() 
{
	if(m_lListenHandle == -1)
	{
		return;
	}

	if(!NET_DVR_StopListen_V30(m_lListenHandle))
	{
	    g_pMainDlg->AddLog(-1, OPERATION_FAIL_T, "NET_DVR_StopListen_V30");
	}
	else
	{
	    g_pMainDlg->AddLog(-1, OPERATION_SUCC_T, "NET_DVR_StopListen_V30");
		m_lListenHandle = -1;	
	}
}

void CDlgLocalConfig::OnButtonRefrush() 
{
	// TODO: Add your control notification handler code here
    m_AllAddressCtrl.ResetContent();
    char sAllIp[16][16] = {0};
    DWORD dwIpNum = 0;
    BOOL bBind = FALSE;
    if (!NET_DVR_GetLocalIP(sAllIp, &dwIpNum, &bBind))
    {
        MessageBox(NET_DVR_GetErrorMsg());
        return;
    }
    
    for (int i = 0; i < dwIpNum; i++)
    {
        m_AllAddressCtrl.AddString(sAllIp[i]);
    }
    m_AllAddressCtrl.SetCurSel(0);
    UpdateData(FALSE);
}

void CDlgLocalConfig::OnBtnSelectSdklogPath() 
{
	// TODO: Add your control notification handler code here
    CString csPath = GetDirectoryPath();
    if (csPath != "")
    {
        m_strSdklog = csPath;
        UpdateData(FALSE);
	}
}

void CDlgLocalConfig::OnBtnBindIp() 
{
	// TODO: Add your control notification handler code here
	if (NET_DVR_SetValidIP(m_AllAddressCtrl.GetCurSel(), true))
	{
		g_pMainDlg->AddLog(-1, OPERATION_SUCC_T, "NET_DVR_SetValidIP");
	}
	else
	{
		g_pMainDlg->AddLog(-1, OPERATION_FAIL_T, "NET_DVR_SetValidIP");
	}	
}
