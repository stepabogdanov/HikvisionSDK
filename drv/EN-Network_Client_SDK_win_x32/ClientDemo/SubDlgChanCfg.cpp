/**********************************************************
FileName:    SubDlgChanCfg.cpp
Description: Channel Configuration      
Date:        2008/05/17
Note: 		<Global>struct, macro refer to GeneralDef.h, global variants and API refer to ClientDemo.cpp  
Modification History:      
    <version> <time>         <desc>
    <1.0    > <2008/05/17>       <created>
***********************************************************/
#include "stdafx.h"
#include "ClientDemo.h"
#include "SubDlgChanCfg.h"
#include "DlgRemoteRecordSchedule.h"
#include "DlgRemoteHideArea.h"
#include "DlgRemoteMotionDetect.h"
#include "DlgRemoteHideAlarm.h"
#include "DlgRemoteVideoInLost.h"
#include "DlgRemoteShowString.h"
#include ".\subdlgchancfg.h"
#include "DlgJpegCaptureCfg.h"
#include "DlgDiskQuota.h"
#include "DlgRemoteVideoInput.h"
#include "DlgAccessCameraCfg.h"
#include "DialogRecordTimeSpan.h"
#include "DlgVideoOut.h"
#include "DlgWD1Enable.h"
#include "DlgNetraRecordPackage.h"

LPNET_DVR_MOTION_V30 g_lpMotionDetect = NULL;
LPNET_DVR_HIDEALARM_V30 g_lpHideAlarm = NULL;
LPNET_DVR_VILOST_V30 g_lpVILost = NULL;
// CSubDlgChanCfg dialog

/*********************************************************
  Function:	CSubDlgChanCfg
  Desc:		Constructor
  Input:	
  Output:	
  Return:	
**********************************************************/
IMPLEMENT_DYNAMIC(CSubDlgChanCfg, CDialog)
CSubDlgChanCfg::CSubDlgChanCfg(CWnd* pParent /*=NULL*/)
	: CDialog(CSubDlgChanCfg::IDD, pParent)
	, m_csChanName(_T(""))
	, m_iBitRate(0)
	, m_iFrameIInterval(0)
	, m_bCheckRecord(FALSE)
	, m_bCheckHideArea(FALSE)
	, m_bCheckMotion(FALSE)
	, m_bCheckHideAlarm(FALSE)
	, m_bCheckVILost(FALSE)
	, m_bCheckOsd(FALSE)
	, m_iOsdX(0)
	, m_iOsdY(0)
	, m_bChkDispWeek(FALSE)
	, m_bCheckChanName(FALSE)
	, m_iChanNameX(0)
	, m_iChanNameY(0)
	, m_iDeviceIndex(-1)
	, m_lLoginID(-1)
	, m_iCompressionTypeSel(NORM_HIGH_STREAM_COMPRESSION)
	, m_iCurChanIndex(-1)
	, m_iChanShowNum(0)
	, m_iCopyChanIndex(0)
	, m_iChanCount(0)
	, m_lStartChannel(0)
	, m_dwAlarmOutNum(0)
	, m_dwDurationTime(0)
{
	int i = 0; 
	for (i=0; i<MAX_CHANNUM_V30*2; i++)
	{
		m_bSetChannelPara[i] = FALSE;
		m_bGetChannelPara[i] = FALSE;
		m_bRemoteRecord[i] = FALSE;
		memset(&m_struMSCompressionCfg[i], 0, 4*sizeof(NET_DVR_MULTI_STREAM_COMPRESSIONCFG));
		memset(&m_struPicCfg[i], 0, sizeof(NET_DVR_PICCFG_V30));
		memset(&m_struCompressionCfg[i], 0, sizeof(NET_DVR_COMPRESSIONCFG_V30));
		memset(&m_struRemoteRecCfg[i], 0, sizeof(NET_DVR_RECORD_V30));
		memset(&m_struAudioIn[i], 0, sizeof(NET_DVR_AUDIO_INPUT_PARAM));
		memset(&m_struCabac[i], 0, sizeof(NET_DVR_STREAM_CABAC));
		memset(&m_struPOEAdapterType[i], 0, sizeof(NET_DVR_POE_CHANNEL_ADD_MODE));

	}
	for (i=0; i<4; i++)
	{
		memset(&m_struMSCond[i], 0, sizeof(NET_DVR_MULTI_STREAM_COMPRESSIONCFG_COND));
	}
    m_pCompresscfgAbility = new NET_DVR_COMPRESSIONCFG_ABILITY;
}

/*********************************************************
  Function:	~CSubDlgChanCfg
  Desc:		destructor
  Input:	
  Output:	
  Return:	
**********************************************************/
CSubDlgChanCfg::~CSubDlgChanCfg()
{
    delete m_pCompresscfgAbility;
}

/*********************************************************
Function:	DoDataExchange
Desc:		the map between control and variable
Input:	
Output:	
Return:	
**********************************************************/
void CSubDlgChanCfg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSubDlgChanCfg)
	DDX_Control(pDX, IDC_COMBO_POE_ADAPTER_TYPE, m_cmbPoeAdapterType);
	DDX_Control(pDX, IDC_COMBO_AUDIOIN_TYPE, m_comboAudioInType);
	DDX_Control(pDX, IDC_COMBO_VIDEO_ENC_COMPLEXITY, m_comboVideoEncComplexity);
	DDX_Control(pDX, IDC_COMBO_OSD_FONT, m_cmbOsdFont);
	DDX_Control(pDX, IDC_COMBO_HOUR_TYPE, m_comboHourType);
	DDX_Control(pDX, IDC_COMBO_VIDEO_TYPE, m_comboVideoType);
	DDX_Control(pDX, IDC_COMBO_AUDIO_TYPE, m_comboAudioType);
	DDX_Control(pDX, IDC_COMBO_COMPRESSION_TYPE, m_comboCompressionType);
	DDX_Check(pDX, IDC_CHK_HIDE_ALARM, m_bCheckHideAlarm);
	DDX_Check(pDX, IDC_CHK_VILOST, m_bCheckVILost);
	DDX_Check(pDX, IDC_CHK_MOTION, m_bCheckMotion);
	DDX_Control(pDX, IDC_EDIT_REC_DELAY, m_comboRecDelay);
	DDX_Control(pDX, IDC_EDIT_PRERECORD_TIME, m_comboPreRecordTime);
	DDX_Check(pDX, IDC_CHK_HIDE_AREA, m_bCheckHideArea);
	DDX_Control(pDX, IDC_COMBO_CHAN, m_comboChanNum);
	DDX_Text(pDX, IDC_EDIT_CHANNEL_NAME, m_csChanName);
	DDX_Control(pDX, IDC_COMBO_IMAGE_QUALITY, m_comboImageQuality);
	DDX_Control(pDX, IDC_COMBO_STREAM_TYPE, m_comboStreamType);
	DDX_Control(pDX, IDC_COMBO_RESOLUTION, m_comboResolution);
	DDX_Control(pDX, IDC_COMBO_BIT_RATE_TYPE, m_comboBitRateType);
	DDX_Control(pDX, IDC_COMBO_FRAME_RATE, m_comboFrameRate);
	DDX_Control(pDX, IDC_COMBO_MAX_BIT_RATE, m_comboBitRate);
	DDX_Text(pDX, IDC_EDIT_BIT_RATE, m_iBitRate);
	DDX_Text(pDX, IDC_EDIT_FRAME_I_INTERVAL, m_iFrameIInterval);
	DDX_Control(pDX, IDC_COMBO_FRAME_BP_INTERVAL, m_comboFrameBPInterval);
	DDX_Check(pDX, IDC_CHK_RECORD, m_bCheckRecord);
	DDX_Check(pDX, IDC_CHK_OSD, m_bCheckOsd);
	DDX_Text(pDX, IDC_EDIT_OSD_X, m_iOsdX);
	DDX_Text(pDX, IDC_EDIT_OSD_Y, m_iOsdY);
	DDX_Check(pDX, IDC_CHK_DISPLAY_WEEK, m_bChkDispWeek);
	DDX_Control(pDX, IDC_COMBO_OSD_ATTRIB, m_comboOsdAttrib);
	DDX_Control(pDX, IDC_COMBO_OSD_TYPE, m_comboOsdType);
	DDX_Check(pDX, IDC_CHK_CHAN_NAME, m_bCheckChanName);
	DDX_Text(pDX, IDC_EDIT_CHAN_NAME_X, m_iChanNameX);
	DDX_Text(pDX, IDC_EDIT_CHAN_NAME_Y, m_iChanNameY);
	DDX_Control(pDX, IDC_COMBO_COPY_CHAN, m_comboCopyChan);
	DDX_Text(pDX, IDC_EDIT_DURATION_TIME, m_dwDurationTime);
	DDX_Check(pDX, IDC_CHK_REDUNDANCY_REC, m_bChkRedundancyRec);
	DDX_Check(pDX, IDC_CHK_AUDIO_REC, m_bChkAudioRec);
	DDX_Check(pDX, IDC_CHK_EVENT_COMPRESS, m_bEventCompress);
	DDX_Check(pDX, IDC_CHECK_CABAC, m_bCabacCheck);
	DDX_Text(pDX, IDC_EDIT_VOLUME, m_byVolume);
	//}}AFX_DATA_MAP
}

/*********************************************************
Function:	BEGIN_MESSAGE_MAP
Desc:		the map between control and function
Input:	
Output:	
Return:	
**********************************************************/
BEGIN_MESSAGE_MAP(CSubDlgChanCfg, CDialog)
	//{{AFX_MSG_MAP(CSubDlgChanCfg)	
	ON_CBN_SELCHANGE(IDC_COMBO_MAX_BIT_RATE, OnCbnSelchangeComboMaxBitRate)
	ON_CBN_SELCHANGE(IDC_COMBO_COMPRESSION_TYPE, OnCbnSelchangeComboCompressionType)
	ON_BN_CLICKED(IDC_BTN_CMP_OK, OnBnClickedBtnCmpOk)
	ON_BN_CLICKED(IDC_BTN_REMOTE_RECORD_SETUP, OnBnClickedBtnRemoteRecordSetup)
	ON_BN_CLICKED(IDC_BTN_HIDE_SETUP, OnBnClickedBtnHideSetup)
	ON_BN_CLICKED(IDC_BTN_MOTION_SETUP, OnBnClickedBtnMotionSetup)
	ON_BN_CLICKED(IDC_BTN_HIDE_ALARM_SETUP, OnBnClickedBtnHideAlarmSetup)
	ON_BN_CLICKED(IDC_BTN_VILOST_SETUP, OnBnClickedBtnVilostSetup)
	ON_BN_CLICKED(IDC_BTN_STRING, OnBnClickedBtnString)
	ON_BN_CLICKED(IDC_BTN_CHAN_COPY, OnBnClickedBtnChanCopy)
	ON_BN_CLICKED(ID_BTN_CHAN_CFG_OK, OnBnClickedBtnChanCfgOk)
	ON_BN_CLICKED(ID_BTN_CHAN_CFG_EXIT, OnBnClickedBtnChanCfgExit)
	ON_BN_CLICKED(IDC_CHK_RECORD, OnBnClickedChkRecord)
	ON_BN_CLICKED(IDC_CHK_HIDE_AREA, OnBnClickedChkHideArea)
	ON_BN_CLICKED(IDC_CHK_OSD, OnBnClickedChkOsd)
	ON_BN_CLICKED(IDC_CHK_CHAN_NAME, OnBnClickedChkChanNamePos)
	ON_CBN_SELCHANGE(IDC_COMBO_CHAN, OnCbnSelchangeComboChan)
	ON_CBN_SELCHANGE(IDC_COMBO_COPY_CHAN, OnCbnSelchangeComboCopyChan)
	ON_BN_CLICKED(IDC_CHK_MOTION, OnBnClickedChkMotion)
	ON_BN_CLICKED(IDC_CHK_HIDE_ALARM, OnBnClickedChkHideAlarm)
	ON_BN_CLICKED(IDC_CHK_VILOST, OnBnClickedChkVilost)
	ON_CBN_SELCHANGE(IDC_COMBO_FRAME_RATE, OnCbnSelchangeComboFrameRate)
	ON_BN_CLICKED(IDC_BTN_JPEG_CAPTURE, OnBtnJpegCapture)
	ON_BN_CLICKED(IDC_BTN_DISK_QUOTA, OnBtnDiskQuota)
	ON_BN_CLICKED(IDC_BUTTON_LIMIT_FRAME_UPDATE, OnButtonLimitFrameUpdate)
	ON_BN_CLICKED(IDC_BUTTON_VIDEO_IN_EFFECT, OnButtonVideoInEffect)
	ON_BN_CLICKED(IDC_BUTTON_CONFIG_CAMERA_TYPE, OnButtonConfigCameraType)
	ON_BN_CLICKED(IDC_BUTTON_INQUIRY_TIME_SPAN, OnButtonInquiryTimeSpan)
	ON_BN_CLICKED(IDC_BUTTON_UPDATE_INDEX, OnButtonUpdateIndex)
	ON_BN_CLICKED(IDC_BTN_VIDEO_OUTPUT, OnBtnVideoOutput)
	ON_BN_CLICKED(IDC_BTN_WD_ENABLE, OnBtnWdEnable)
	ON_BN_CLICKED(IDC_BTN_VEDIOPACKAGE, OnBtnVediopackage)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// CSubDlgChanCfg message handlers

/*********************************************************
Function:	OnInitDialog
Desc:		Initialize the dialog
Input:	
Output:	
Return:	
**********************************************************/
BOOL CSubDlgChanCfg::OnInitDialog()
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
Desc:		Check and update init paramerters
Input:	
Output:	
Return:	TRUE,device parameters correct, init device;FALSE,do not init
**********************************************************/
BOOL CSubDlgChanCfg::CheckInitParam()
{
	UpdateData(TRUE);
	int iDeviceIndex = g_pMainDlg->GetCurDeviceIndex();

	if (iDeviceIndex == -1)
	{
		return FALSE;
	}
	
// 	if (g_pMainDlg->IsCurDevMatDec(iDeviceIndex))
// 	{
// 		return FALSE;
// 	}

	if (m_iDeviceIndex == iDeviceIndex && m_iCurChanIndex != -1)
	{
		return TRUE;
	}
	else
	{
		m_iDeviceIndex = iDeviceIndex;
		m_lLoginID = g_struDeviceInfo[m_iDeviceIndex].lLoginID;
		m_lStartChannel = g_struDeviceInfo[m_iDeviceIndex].iStartChan;
		m_iChanCount = g_struDeviceInfo[m_iDeviceIndex].iDeviceChanNum;
		m_dwAlarmOutNum = g_struDeviceInfo[m_iDeviceIndex].iAlarmOutNum;
	}


	m_bCheckHideAlarm = FALSE;
	m_bCheckVILost = FALSE;
	m_bCheckMotion = FALSE;

	m_bCheckHideArea = FALSE;
	m_csChanName = _T("");

	m_iBitRate = 0;
	m_iFrameIInterval = 0;
	m_comboRecDelay.SetCurSel(-1);
	m_comboPreRecordTime.SetCurSel(-1);
	m_comboChanNum.SetCurSel(-1);
	m_comboImageQuality.SetCurSel(-1);
	m_comboStreamType.SetCurSel(-1);
	m_comboResolution.SetCurSel(-1);
	m_comboBitRateType.SetCurSel(-1);
	m_comboFrameRate.SetCurSel(-1);
	m_comboBitRate.SetCurSel(-1);
	m_comboFrameBPInterval.SetCurSel(-1);

	m_comboOsdAttrib.SetCurSel(-1);
	m_comboOsdType.SetCurSel(-1);
	m_comboHourType.SetCurSel(-1);
	m_bCheckRecord = FALSE;
	m_bCheckOsd = FALSE;
	m_iOsdX = 0;
	m_iOsdY = 0;
	m_bChkDispWeek = FALSE;
	m_bCheckChanName = FALSE;
	m_iChanNameX = 0;
	m_iChanNameY = 0;
	m_iCompressionTypeSel = 0;
	m_comboCopyChan.ResetContent();
	m_comboChanNum.ResetContent();

	if (m_lLoginID < 0)
	{
		return FALSE;
	}

	DWORD dwReturned = 0;
	int i=0;
	CString sTemp;
	DWORD dwChanShow = 0;//display channel number
	DWORD iCopyIndex = 0;
	char szLan[128] = {0};
	m_iCopyChanIndex = -1;
	
    //GetStreamTypeAbility();


	g_struDeviceInfo[iDeviceIndex].struChanInfo[i];
	
	//2008-9-6 12:54	
	m_comboCompressionType.SetCurSel(0);
	g_StringLanType(szLan, "ȫ��ͨ��", "All Channels");
	m_comboCopyChan.AddString(szLan);
	for (i=0; i < MAX_CHANNUM_V30*2; i++)
	{
		STRU_CHANNEL_INFO *pChannelInfo = &(g_struDeviceInfo[iDeviceIndex].struChanInfo[i]);
		if (pChannelInfo->iChanIndex < 0)
		{
			break;
		}

		dwChanShow = pChannelInfo->iChannelNO;


		m_bSetChannelPara[i] = FALSE;
		m_bGetChannelPara[i] = FALSE;
		m_bRemoteRecord[i] = FALSE;
		if (pChannelInfo->iChanType  == DEMO_CHANNEL_TYPE_ANALOG)
		{
			sTemp.Format(ANALOG_C_FORMAT, dwChanShow);
		}
		else if (pChannelInfo->iChanType  == DEMO_CHANNEL_TYPE_IP)
		{
			sTemp.Format(DIGITAL_C_FORMAT, dwChanShow - g_struDeviceInfo[iDeviceIndex].struIPParaCfgV40.dwStartDChan + 1);
		}
		else
		{
			sTemp.Format("NO_Type%d", dwChanShow);
		}
		m_comboChanNum.AddString(sTemp);

		DWORD dwStatus[4] = {0};

		if (g_struDeviceInfo[m_iDeviceIndex].struChanInfo[i].bEnable)
		{
// 			memset(&m_struCompressionCfg[i], 0, sizeof(m_struCompressionCfg[i]));
// 			if (!NET_DVR_GetDVRConfig(m_lLoginID, NET_DVR_GET_COMPRESSCFG_V30, dwChanShow, &m_struCompressionCfg[i], sizeof(NET_DVR_COMPRESSIONCFG_V30), &dwReturned))
// 			{
// 				g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "chan[%d] NET_DVR_GET_COMPRESSCFG_V30", dwChanShow);
// 				//return FALSE;
// 			}
// 			else
// 			{
// 				g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_COMPRESSCFG_V30 chan[%d]", dwChanShow);	
// 			}
	

			memset(&m_struMSCompressionCfg[i][0], 0, 4*sizeof(NET_DVR_MULTI_STREAM_COMPRESSIONCFG));

			for(int j=0; j<4; j++)
			{			
				m_struMSCond[j].dwSize = sizeof(NET_DVR_MULTI_STREAM_COMPRESSIONCFG_COND);
				m_struMSCond[j].struStreamInfo.dwChannel = dwChanShow;
				m_struMSCond[j].dwStreamType = j; 

			}



			if (!NET_DVR_GetDeviceConfig(m_lLoginID, NET_DVR_GET_MULTI_STREAM_COMPRESSIONCFG, 4,\
				&m_struMSCond[0], 4*sizeof(NET_DVR_MULTI_STREAM_COMPRESSIONCFG_COND), &dwStatus[0], &m_struMSCompressionCfg[i][0], 4*sizeof(NET_DVR_MULTI_STREAM_COMPRESSIONCFG)))
			{
				g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "chan[%d] NET_DVR_GET_MULTI_STREAM_COMPRESSIONCFG", dwChanShow);
			}
			else
			{
				g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_MULTI_STREAM_COMPRESSIONCFG chan[%d]", dwChanShow);	
			}
			
			memset(&m_struPicCfg[i], 0, sizeof(m_struPicCfg[i]));
			if (!NET_DVR_GetDVRConfig(m_lLoginID, NET_DVR_GET_PICCFG_V30, dwChanShow, &m_struPicCfg[i], sizeof(NET_DVR_PICCFG_V30), &dwReturned))
			{
				g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "chan[%d]:NET_DVR_GET_PICCFG_V30", dwChanShow);
				//return FALSE;
			}
			else
			{
				g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_PICCFG_V30 chan[%d]", dwChanShow);	
			}
			
			memset(&m_struRemoteRecCfg[i], 0, sizeof(m_struRemoteRecCfg[i]));
			if (!NET_DVR_GetDVRConfig(m_lLoginID,NET_DVR_GET_RECORDCFG_V30, dwChanShow, &m_struRemoteRecCfg[i], sizeof(NET_DVR_RECORD_V30), &dwReturned))	
			{
				g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "chan[%d] NET_DVR_GET_RECORDCFG_V30", dwChanShow);	
				//return FALSE;
			}
			else
			{
				g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_RECORDCFG_V30 chan[%d]", dwChanShow);	
			}

			memset(&m_struAudioIn[i], 0, sizeof(m_struAudioIn[i]));
			if (!NET_DVR_GetDVRConfig(m_lLoginID, NET_DVR_GET_AUDIO_INPUT, dwChanShow, &m_struAudioIn[i], sizeof(NET_DVR_AUDIO_INPUT_PARAM), &dwReturned))
			{
				g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "chan[%d] NET_DVR_GET_AUDIO_INPUT", dwChanShow);
				//return FALSE;
			}
			else
			{
				g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_AUDIO_INPUT chan[%d]", dwChanShow);	
			}

			m_comboCopyChan.AddString(sTemp);
			m_comboCopyChan.SetItemData(iCopyIndex, i);	
			iCopyIndex++;//0 map to all channels
			m_bGetChannelPara[i] = TRUE;

			memset(&m_struCabac[i], 0, sizeof(m_struCabac[i]));
			if (!NET_DVR_GetDVRConfig(m_lLoginID, NET_DVR_GET_STREAM_CABAC, dwChanShow, &m_struCabac[i], sizeof(NET_DVR_STREAM_CABAC), &dwReturned))
			{
				g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "chan[%d] NET_DVR_GET_STREAM_CABAC", dwChanShow);
				//return FALSE;
			}
			else
			{
				g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_STREAM_CABAC chan[%d]", dwChanShow);	
			}

			memset(&m_struPOEAdapterType[i], 0, sizeof(m_struPOEAdapterType[i]));
			if (!NET_DVR_GetDVRConfig(m_lLoginID, NET_DVR_GET_POE_CHANNEL_ADD_MODE, dwChanShow, &m_struPOEAdapterType[i], sizeof(NET_DVR_POE_CHANNEL_ADD_MODE), &dwReturned))
			{
				g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "chan[%d] NET_DVR_GET_POE_CHANNEL_ADD_MODE", dwChanShow);
				//return FALSE;
			}
			else
			{
				g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_POE_CHANNEL_ADD_MODE chan[%d]", dwChanShow);	
			}
		}
		else 
		{
			continue;
		}
	}
	g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_CFG");	
	return TRUE;
}
/*********************************************************
Function:	CurCfgUpdate
Desc:		Update device parameters and refreshthecontrols
Input:	
Output:	
Return:	
**********************************************************/
void CSubDlgChanCfg::CurCfgUpdate(int iChanIndex)
{ 
	char cTemp[100] = {0};
	int i = 0;

	if (iChanIndex == -1)
	{//channel index may be -1 and select a node on the device list, the default value is set as the first valid index value
		for (i=0; i<MAX_CHANNUM_V30; i++)
		{
			if (g_struDeviceInfo[m_iDeviceIndex].struChanInfo[i].bEnable)
			{
				break;
			}
		}
		m_iCurChanIndex = i;
	}
	else
	{
		m_iCurChanIndex = iChanIndex;
	}

    // As the zero chan do  noting
    if (m_iCurChanIndex >= ZERO_CHAN_INDEX)
    {
        AfxMessageBox("Not support zero chan in the page");
        return;
    }

	//*** 0<=m_iCurChanIndex<= 64*2***//
	DEMO_CHANNEL_TYPE iChannelType = g_struDeviceInfo[m_iDeviceIndex].struChanInfo[m_iCurChanIndex].iChanType;

    m_lLoginID = g_struDeviceInfo[m_iDeviceIndex].lLoginID;
	if (iChannelType ==  DEMO_CHANNEL_TYPE_ANALOG)
	{
		GetDlgItem(IDC_BTN_STRING)->EnableWindow(TRUE);	
	}
	else
	{
		GetDlgItem(IDC_BTN_STRING)->EnableWindow(TRUE);
	}

	m_comboChanNum.SetCurSel(m_iCurChanIndex);
	m_comboCopyChan.SetCurSel(0);
	m_iChanShowNum = g_struDeviceInfo[m_iDeviceIndex].struChanInfo[m_iCurChanIndex].iChannelNO;

	//compression parameters
    if (GetCompressCfgAbility(m_iChanShowNum))
    {
        GetStreamTypeAbility();
        m_comboCompressionType.SetCurSel(0);
        GetResolutionAbility();
        GetBitrateAbility();
        GetBitrateTypeAbility();
        GetFrameAbility();
    }
    else
    {
        AfxMessageBox("Get compression ability failed");
    }

    UpdateCompressionInfo();
	
	//recording paramerters
	m_bCheckRecord = m_struRemoteRecCfg[m_iCurChanIndex].dwRecord;
	GetDlgItem(IDC_BTN_REMOTE_RECORD_SETUP)->EnableWindow(m_bCheckRecord);
	m_comboRecDelay.SetCurSel(m_struRemoteRecCfg[m_iCurChanIndex].dwRecordTime);
	m_comboPreRecordTime.SetCurSel(m_struRemoteRecCfg[m_iCurChanIndex].dwPreRecordTime);
// 	if (0xffffffff == m_struRemoteRecCfg[m_iCurChanIndex].dwRecorderDuration)
// 	{
// 		GetDlgItem(IDC_EDIT_DURATION_TIME)->EnableWindow(FALSE);
// 	}
// 	else
// 	{
// 		GetDlgItem(IDC_EDIT_DURATION_TIME)->EnableWindow(TRUE);
// 		m_dwDurationTime = m_struRemoteRecCfg[m_iCurChanIndex].dwRecorderDuration;
// 	}
	//¼�񱣴�ʱ��
	m_dwDurationTime = m_struRemoteRecCfg[m_iCurChanIndex].dwRecorderDuration;

	if (0xff == m_struRemoteRecCfg[m_iCurChanIndex].byRedundancyRec)
	{
		GetDlgItem(IDC_CHK_REDUNDANCY_REC)->EnableWindow(FALSE);
	}
	else
	{
		GetDlgItem(IDC_CHK_REDUNDANCY_REC)->EnableWindow(TRUE);
		m_bChkRedundancyRec = m_struRemoteRecCfg[m_iCurChanIndex].byRedundancyRec;
	}

	if (0xff == m_struRemoteRecCfg[m_iCurChanIndex].byAudioRec)
	{
		GetDlgItem(IDC_CHK_AUDIO_REC)->EnableWindow(FALSE);
	}
	else
	{
		GetDlgItem(IDC_CHK_AUDIO_REC)->EnableWindow(TRUE);
		m_bChkAudioRec = m_struRemoteRecCfg[m_iCurChanIndex].byAudioRec;
	}

    //image parameters
	ZeroMemory(cTemp, 100);
	memcpy(cTemp, m_struPicCfg[m_iCurChanIndex].sChanName, NAME_LEN);
	m_csChanName.Format("%s",cTemp);
	m_bCheckHideArea = m_struPicCfg[m_iCurChanIndex].dwEnableHide;
	GetDlgItem(IDC_BTN_HIDE_SETUP)->EnableWindow(m_bCheckHideArea);
	m_bCheckMotion = m_struPicCfg[m_iCurChanIndex].struMotion.byEnableHandleMotion;
	GetDlgItem(IDC_BTN_MOTION_SETUP)->EnableWindow(m_bCheckMotion);
	if (m_struPicCfg[m_iCurChanIndex].struHideAlarm.dwEnableHideAlarm > 0)
	{
		m_bCheckHideAlarm = TRUE;
	}
	else
	{
		m_bCheckHideAlarm = FALSE;
	}
	GetDlgItem(IDC_BTN_HIDE_ALARM_SETUP)->EnableWindow(m_bCheckHideAlarm);

	m_bCheckChanName = m_struPicCfg[m_iCurChanIndex].dwShowChanName;
	EnableChanname(m_bCheckChanName);
	m_iChanNameX = m_struPicCfg[m_iCurChanIndex].wShowNameTopLeftX;
	m_iChanNameY = m_struPicCfg[m_iCurChanIndex].wShowNameTopLeftY;
	m_bCheckOsd = m_struPicCfg[m_iCurChanIndex].dwShowOsd;
	EnableOsd(m_bCheckOsd);
	m_iOsdX = m_struPicCfg[m_iCurChanIndex].wOSDTopLeftX;
	m_iOsdY = m_struPicCfg[m_iCurChanIndex].wOSDTopLeftY;
	m_bChkDispWeek = m_struPicCfg[m_iCurChanIndex].byDispWeek;
	//2011-07-18 osd����ʾʱ����ʾ��ʽĬ��Ϊ��һ��
	if (!m_bCheckOsd && m_struPicCfg[m_iCurChanIndex].byOSDAttrib == 0)
	{
		m_struPicCfg[m_iCurChanIndex].byOSDAttrib = 1;
	}
	m_comboOsdAttrib.SetCurSel(m_struPicCfg[m_iCurChanIndex].byOSDAttrib-1);
	m_comboOsdType.SetCurSel(m_struPicCfg[m_iCurChanIndex].byOSDType);
	m_cmbOsdFont.SetCurSel(m_struPicCfg[m_iCurChanIndex].byFontSize);
	m_comboHourType.SetCurSel(m_struPicCfg[m_iCurChanIndex].byHourOSDType);
	m_bCheckVILost = m_struPicCfg[m_iCurChanIndex].struVILost.byEnableHandleVILost;
	GetDlgItem(IDC_BTN_VILOST_SETUP)->EnableWindow(m_bCheckVILost);
// 	m_bChkAuLost = m_struPicCfg[m_iCurChanIndex].struAULost.byEnableHandleVILost;
// 	GetDlgItem(IDC_BTN_AULOST_SETUP)->EnableWindow(m_bChkAuLost);
	GetDlgItem(ID_BTN_CHAN_CFG_OK)->EnableWindow(TRUE);

	m_comboAudioInType.SetCurSel(m_struAudioIn[m_iCurChanIndex].byAudioInputType);
	m_byVolume = m_struAudioIn[m_iCurChanIndex].byVolume;

	m_bCabacCheck = m_struCabac[m_iCurChanIndex].byCabacEnable;
	m_cmbPoeAdapterType.SetCurSel(m_struPOEAdapterType->byAddMode);
	UpdateData(FALSE);
}

/*********************************************************
  Function:	OnCbnSelchangeComboChan
  Desc:		get channel paramerets and refresh the control
  Input:	
  Output:	
  Return:	
**********************************************************/
void CSubDlgChanCfg::OnCbnSelchangeComboChan()
{
	UpdateData(TRUE);
	int iChanIndex  = m_comboChanNum.GetCurSel();
	CurCfgUpdate(iChanIndex);
}

/*********************************************************
  Function:	OnBnClickedBtnRemoteRecordSetup
  Desc:		remote recording schedule
  Input:	
  Output:	
  Return:	
**********************************************************/
void CSubDlgChanCfg::OnBnClickedBtnRemoteRecordSetup()
{
	CDlgRemoteRecordSchedule dlg;
    dlg.m_lServerID = m_lLoginID;
    dlg.m_lChannel = g_struDeviceInfo[m_iDeviceIndex].struChanInfo[m_iCurChanIndex].iChannelNO;     
    dlg.m_iDevIndex = m_iDeviceIndex;

	dlg.m_struRemoteRecSchedule = &(m_struRemoteRecCfg[m_iCurChanIndex]);
	if (dlg.DoModal() == IDOK)
	{
		m_bSetChannelPara[m_iCurChanIndex] = TRUE;
		g_bMustReboot = g_pMainDlg->IsNeedRebootDevType();
	}
}


/*********************************************************
  Function:	OnBnClickedBtnHideSetup
  Desc:		privacy mask setting
  Input:	
  Output:	
  Return:	
**********************************************************/
void CSubDlgChanCfg::OnBnClickedBtnHideSetup()
{
	CDlgRemoteHideArea dlg;
	int i = 0;

	for (i=0; i<MAX_SHELTERNUM; i++)
	{
		memcpy(&(dlg.m_struShelter[i]), &(m_struPicCfg[m_iCurChanIndex].struShelter[i]),sizeof(NET_DVR_SHELTER));
	}
	dlg.m_iChanShowNum = m_iChanShowNum;
	dlg.m_lLoginID = m_lLoginID;
	if (dlg.DoModal() == IDOK)
	{
		for (i=0; i<MAX_SHELTERNUM; i++)
		{
			memcpy(&(m_struPicCfg[m_iCurChanIndex].struShelter[i]), &(dlg.m_struShelter[i]),sizeof(NET_DVR_SHELTER));
		}
		m_bSetChannelPara[m_iCurChanIndex] = TRUE;
	}
}

/*********************************************************
  Function:	OnBnClickedBtnMotionSetup
  Desc:		motion detect schedule, zone, etc
  Input:	
  Output:	
  Return:	
**********************************************************/
void CSubDlgChanCfg::OnBnClickedBtnMotionSetup()
{
	CDlgRemoteMotionDetect dlgRemoteMotionDetect;

	g_lpMotionDetect = &(m_struPicCfg[m_iCurChanIndex].struMotion);
	dlgRemoteMotionDetect.m_iChanShowNum = m_iChanShowNum;
	dlgRemoteMotionDetect.m_lLoginID = m_lLoginID;
	dlgRemoteMotionDetect.m_dwAlarmOutNum = m_dwAlarmOutNum;
	dlgRemoteMotionDetect.m_iChanCount = m_iChanCount;
	dlgRemoteMotionDetect.m_dwDevIndex = m_iDeviceIndex;
	if (dlgRemoteMotionDetect.DoModal() == IDOK)
	{
		m_bSetChannelPara[m_iCurChanIndex] = TRUE;
	}
}

/*********************************************************
  Function:	OnBnClickedBtnHideAlarmSetup
  Desc:		view tamper settings 
  Input:	
  Output:	
  Return:	
**********************************************************/
void CSubDlgChanCfg::OnBnClickedBtnHideAlarmSetup()
{
	CDlgRemoteHideAlarm dlgRemoteHideAlarm;

	g_lpHideAlarm = &(m_struPicCfg[m_iCurChanIndex].struHideAlarm);
	dlgRemoteHideAlarm.m_iChanShowNum = m_iChanShowNum;
	dlgRemoteHideAlarm.m_lLoginID = m_lLoginID;
	dlgRemoteHideAlarm.m_dwAlarmOutNum = m_dwAlarmOutNum;
	dlgRemoteHideAlarm.m_dwDevIndex = m_iDeviceIndex;
	if (dlgRemoteHideAlarm.DoModal() == IDOK)
	{
		m_bSetChannelPara[m_iCurChanIndex] = TRUE;
	}
}

/*********************************************************
  Function:	OnBnClickedBtnVilostSetup
  Desc:		video loss settings
  Input:	
  Output:	
  Return:	
**********************************************************/
void CSubDlgChanCfg::OnBnClickedBtnVilostSetup()
{
	CDlgRemoteVideoInLost dlgRemoteVideoInLost;

	g_lpVILost = &(m_struPicCfg[m_iCurChanIndex].struVILost);
	dlgRemoteVideoInLost.m_iChanShowNum = m_iChanShowNum;
	dlgRemoteVideoInLost.m_lLoginID = m_lLoginID;
	dlgRemoteVideoInLost.m_dwAlarmOutNum = m_dwAlarmOutNum;
	dlgRemoteVideoInLost.m_dwDevIndex = m_iDeviceIndex;
	if (dlgRemoteVideoInLost.DoModal() == IDOK)
	{
		m_bSetChannelPara[m_iCurChanIndex] = TRUE;
	}
}

/*********************************************************
  Function:	OnBnClickedBtnString	
  Desc:		string overlay settings
  Input:	
  Output:	
  Return:	
**********************************************************/
void CSubDlgChanCfg::OnBnClickedBtnString()
{
	CDlgRemoteShowString dlgRemoteShowString;

	dlgRemoteShowString.m_lLoginID = m_lLoginID;
	dlgRemoteShowString.m_iChanShowNum = m_iChanShowNum;
	dlgRemoteShowString.DoModal();
}

/*********************************************************
  Function:	OnBnClickedBtnChanCopy
  Desc:		copy channel configuration
  Input:	
  Output:	
  Return:	
**********************************************************/
void CSubDlgChanCfg::OnBnClickedBtnChanCopy()
{
	UpdateData(TRUE);
	int i = 0, j = 0, k = 0;
	m_iCopyChanIndex = m_comboCopyChan.GetItemData(m_comboCopyChan.GetCurSel()) - 1;
// 	if (m_iCopyChanIndex == m_iCurChanIndex)
// 	{
// 		return;
// 	}

	if (m_iCopyChanIndex == -1)
	{
		for (i=0; i<MAX_CHANNUM_V30; i++)
		{
			if (i == m_iCurChanIndex|| !g_struDeviceInfo[m_iDeviceIndex].struChanInfo[i].bEnable)//ȥ��û�л�ȡ�豸ͨ��������ͨ�����ȴ��ڹر�״̬��ͨ��
			{
				continue;// || !m_bGetChannelPara[i] 
			}
			//copy comrpession parameters
				//main stream
			CheckRebootParam( &(m_struMSCompressionCfg[i][NORM_HIGH_STREAM_COMPRESSION].struStreamPara.byStreamType),\
				m_struMSCompressionCfg[m_iCurChanIndex][NORM_HIGH_STREAM_COMPRESSION].struStreamPara.byStreamType, FALSE);				 
			m_struMSCompressionCfg[i][NORM_HIGH_STREAM_COMPRESSION].struStreamPara.byPicQuality = m_struMSCompressionCfg[m_iCurChanIndex][NORM_HIGH_STREAM_COMPRESSION].struStreamPara.byPicQuality;
			m_struMSCompressionCfg[i][NORM_HIGH_STREAM_COMPRESSION].struStreamPara.dwVideoBitrate = m_struMSCompressionCfg[m_iCurChanIndex][NORM_HIGH_STREAM_COMPRESSION].struStreamPara.dwVideoBitrate;
			CheckRebootParam( &(m_struMSCompressionCfg[i][NORM_HIGH_STREAM_COMPRESSION].struStreamPara.byResolution),\
				m_struMSCompressionCfg[m_iCurChanIndex][NORM_HIGH_STREAM_COMPRESSION].struStreamPara.byResolution, TRUE);
			m_struMSCompressionCfg[i][NORM_HIGH_STREAM_COMPRESSION].struStreamPara.dwVideoFrameRate = m_struMSCompressionCfg[m_iCurChanIndex][NORM_HIGH_STREAM_COMPRESSION].struStreamPara.dwVideoFrameRate;
			m_struMSCompressionCfg[i][NORM_HIGH_STREAM_COMPRESSION].struStreamPara.byBitrateType = m_struMSCompressionCfg[m_iCurChanIndex][NORM_HIGH_STREAM_COMPRESSION].struStreamPara.byBitrateType;
			m_struMSCompressionCfg[i][NORM_HIGH_STREAM_COMPRESSION].struStreamPara.byIntervalBPFrame = m_struMSCompressionCfg[m_iCurChanIndex][NORM_HIGH_STREAM_COMPRESSION].struStreamPara.byIntervalBPFrame;	
			m_struMSCompressionCfg[i][NORM_HIGH_STREAM_COMPRESSION].struStreamPara.wIntervalFrameI = m_struMSCompressionCfg[m_iCurChanIndex][NORM_HIGH_STREAM_COMPRESSION].struStreamPara.wIntervalFrameI;
			m_struMSCompressionCfg[i][NORM_HIGH_STREAM_COMPRESSION].struStreamPara.byVideoEncType = m_struMSCompressionCfg[m_iCurChanIndex][NORM_HIGH_STREAM_COMPRESSION].struStreamPara.byVideoEncType;	
			m_struMSCompressionCfg[i][NORM_HIGH_STREAM_COMPRESSION].struStreamPara.byAudioEncType = m_struMSCompressionCfg[m_iCurChanIndex][NORM_HIGH_STREAM_COMPRESSION].struStreamPara.byAudioEncType;
			m_struMSCompressionCfg[i][NORM_HIGH_STREAM_COMPRESSION].struStreamPara.byVideoEncComplexity = m_struMSCompressionCfg[m_iCurChanIndex][NORM_HIGH_STREAM_COMPRESSION].struStreamPara.byVideoEncComplexity;
			
			//sub stream
			m_struMSCompressionCfg[i][SUB_STREAM_COMPRESSION].struStreamPara.byStreamType = m_struMSCompressionCfg[m_iCurChanIndex][SUB_STREAM_COMPRESSION].struStreamPara.byStreamType;
			m_struMSCompressionCfg[i][SUB_STREAM_COMPRESSION].struStreamPara.byPicQuality = m_struMSCompressionCfg[m_iCurChanIndex][SUB_STREAM_COMPRESSION].struStreamPara.byPicQuality;
			m_struMSCompressionCfg[i][SUB_STREAM_COMPRESSION].struStreamPara.dwVideoBitrate = m_struMSCompressionCfg[m_iCurChanIndex][SUB_STREAM_COMPRESSION].struStreamPara.dwVideoBitrate;
			m_struMSCompressionCfg[i][SUB_STREAM_COMPRESSION].struStreamPara.byResolution = m_struMSCompressionCfg[m_iCurChanIndex][SUB_STREAM_COMPRESSION].struStreamPara.byResolution;
			m_struMSCompressionCfg[i][SUB_STREAM_COMPRESSION].struStreamPara.dwVideoFrameRate= m_struMSCompressionCfg[m_iCurChanIndex][SUB_STREAM_COMPRESSION].struStreamPara.dwVideoFrameRate;
			m_struMSCompressionCfg[i][SUB_STREAM_COMPRESSION].struStreamPara.byBitrateType = m_struMSCompressionCfg[m_iCurChanIndex][SUB_STREAM_COMPRESSION].struStreamPara.byBitrateType;
			m_struMSCompressionCfg[i][SUB_STREAM_COMPRESSION].struStreamPara.byIntervalBPFrame = m_struMSCompressionCfg[m_iCurChanIndex][SUB_STREAM_COMPRESSION].struStreamPara.byIntervalBPFrame;	
			m_struMSCompressionCfg[i][SUB_STREAM_COMPRESSION].struStreamPara.wIntervalFrameI = m_struMSCompressionCfg[m_iCurChanIndex][SUB_STREAM_COMPRESSION].struStreamPara.wIntervalFrameI;
			m_struMSCompressionCfg[i][SUB_STREAM_COMPRESSION].struStreamPara.byVideoEncType = m_struMSCompressionCfg[m_iCurChanIndex][SUB_STREAM_COMPRESSION].struStreamPara.byVideoEncType;	
			m_struMSCompressionCfg[i][SUB_STREAM_COMPRESSION].struStreamPara.byAudioEncType = m_struMSCompressionCfg[m_iCurChanIndex][SUB_STREAM_COMPRESSION].struStreamPara.byAudioEncType;
			m_struMSCompressionCfg[i][SUB_STREAM_COMPRESSION].struStreamPara.byVideoEncComplexity = m_struMSCompressionCfg[m_iCurChanIndex][SUB_STREAM_COMPRESSION].struStreamPara.byVideoEncComplexity;
			
			//event
			m_struMSCompressionCfg[i][EVENT_INVOKE_COMPRESSION].struStreamPara.byStreamType = m_struMSCompressionCfg[m_iCurChanIndex][EVENT_INVOKE_COMPRESSION].struStreamPara.byStreamType;
			m_struMSCompressionCfg[i][EVENT_INVOKE_COMPRESSION].struStreamPara.byPicQuality = m_struMSCompressionCfg[m_iCurChanIndex][EVENT_INVOKE_COMPRESSION].struStreamPara.byPicQuality;
			m_struMSCompressionCfg[i][EVENT_INVOKE_COMPRESSION].struStreamPara.dwVideoBitrate = m_struMSCompressionCfg[m_iCurChanIndex][EVENT_INVOKE_COMPRESSION].struStreamPara.dwVideoBitrate;
			m_struMSCompressionCfg[i][EVENT_INVOKE_COMPRESSION].struStreamPara.byResolution = m_struMSCompressionCfg[m_iCurChanIndex][EVENT_INVOKE_COMPRESSION].struStreamPara.byResolution;
			m_struMSCompressionCfg[i][EVENT_INVOKE_COMPRESSION].struStreamPara.dwVideoFrameRate = m_struMSCompressionCfg[m_iCurChanIndex][EVENT_INVOKE_COMPRESSION].struStreamPara.dwVideoFrameRate;
			m_struMSCompressionCfg[i][EVENT_INVOKE_COMPRESSION].struStreamPara.byBitrateType = m_struMSCompressionCfg[m_iCurChanIndex][EVENT_INVOKE_COMPRESSION].struStreamPara.byBitrateType;
			m_struMSCompressionCfg[i][EVENT_INVOKE_COMPRESSION].struStreamPara.byIntervalBPFrame = m_struMSCompressionCfg[m_iCurChanIndex][EVENT_INVOKE_COMPRESSION].struStreamPara.byIntervalBPFrame;	
			m_struMSCompressionCfg[i][EVENT_INVOKE_COMPRESSION].struStreamPara.wIntervalFrameI = m_struMSCompressionCfg[m_iCurChanIndex][EVENT_INVOKE_COMPRESSION].struStreamPara.wIntervalFrameI;
			m_struMSCompressionCfg[i][EVENT_INVOKE_COMPRESSION].struStreamPara.byVideoEncType = m_struMSCompressionCfg[m_iCurChanIndex][EVENT_INVOKE_COMPRESSION].struStreamPara.byVideoEncType;	
			m_struMSCompressionCfg[i][EVENT_INVOKE_COMPRESSION].struStreamPara.byAudioEncType = m_struMSCompressionCfg[m_iCurChanIndex][EVENT_INVOKE_COMPRESSION].struStreamPara.byAudioEncType;
			m_struMSCompressionCfg[i][EVENT_INVOKE_COMPRESSION].struStreamPara.byVideoEncComplexity = m_struMSCompressionCfg[m_iCurChanIndex][EVENT_INVOKE_COMPRESSION].struStreamPara.byVideoEncComplexity;
	
// 			m_struCompressionCfg[i].struNormLowRecordPara.byStreamType = m_struCompressionCfg[m_iCurChanIndex].struNormLowRecordPara.byStreamType;
// 			m_struCompressionCfg[i].struNormLowRecordPara.byPicQuality = m_struCompressionCfg[m_iCurChanIndex].struNormLowRecordPara.byPicQuality;
// 			m_struCompressionCfg[i].struNormLowRecordPara.dwVideoBitrate = m_struCompressionCfg[m_iCurChanIndex].struNormLowRecordPara.dwVideoBitrate;
// 			m_struCompressionCfg[i].struNormLowRecordPara.byResolution = m_struCompressionCfg[m_iCurChanIndex].struNormLowRecordPara.byResolution;
// 			m_struCompressionCfg[i].struNormLowRecordPara.dwVideoFrameRate = m_struCompressionCfg[m_iCurChanIndex].struNormLowRecordPara.dwVideoFrameRate;
// 			m_struCompressionCfg[i].struNormLowRecordPara.byBitrateType = m_struCompressionCfg[m_iCurChanIndex].struNormLowRecordPara.byBitrateType;
// 			m_struCompressionCfg[i].struNormLowRecordPara.byIntervalBPFrame = m_struCompressionCfg[m_iCurChanIndex].struNormLowRecordPara.byIntervalBPFrame;	
// 			m_struCompressionCfg[i].struNormLowRecordPara.wIntervalFrameI = m_struCompressionCfg[m_iCurChanIndex].struNormLowRecordPara.wIntervalFrameI;

			//recording paramerters
			m_struRemoteRecCfg[i].dwRecord = m_struRemoteRecCfg[m_iCurChanIndex].dwRecord;
			m_struRemoteRecCfg[i].dwRecordTime = m_struRemoteRecCfg[m_iCurChanIndex].dwRecordTime;
			m_struRemoteRecCfg[i].dwPreRecordTime = m_struRemoteRecCfg[m_iCurChanIndex].dwPreRecordTime;
			m_struRemoteRecCfg[i].dwRecorderDuration = m_struRemoteRecCfg[m_iCurChanIndex].dwRecorderDuration;
			//copy time schedule
			for (k=0; k<MAX_DAYS; k++)
			{
				memcpy(&(m_struRemoteRecCfg[i].struRecAllDay[k]), &(m_struRemoteRecCfg[m_iCurChanIndex].struRecAllDay[k]), sizeof(NET_DVR_RECORDDAY));
				for (j=0; j<MAX_TIMESEGMENT_V30; j++)
				{
					memcpy(&m_struRemoteRecCfg[i].struRecordSched[k][j],&m_struRemoteRecCfg[m_iCurChanIndex].struRecordSched[k][j],sizeof(NET_DVR_RECORDSCHED));				
				}
			}

			//image parameters
			m_struPicCfg[i].dwEnableHide = m_bCheckHideArea;
			m_struPicCfg[i].struMotion.byEnableHandleMotion = (BYTE)m_bCheckMotion;			
			if (!m_bCheckHideAlarm)
			{
				m_struPicCfg[i].struHideAlarm.dwEnableHideAlarm = m_bCheckHideAlarm;
			}
			m_struPicCfg[i].dwShowChanName = m_bCheckChanName;
			m_struPicCfg[i].wShowNameTopLeftX = (WORD)m_iChanNameX;
			m_struPicCfg[i].wShowNameTopLeftY = (WORD)m_iChanNameY;
			m_struPicCfg[i].dwShowOsd = m_bCheckOsd;
			m_struPicCfg[i].wOSDTopLeftX = (WORD)m_iOsdX;
			m_struPicCfg[i].wOSDTopLeftY = (WORD)m_iOsdY;
			m_struPicCfg[i].byDispWeek = (BYTE)m_bChkDispWeek;
			m_struPicCfg[i].byOSDAttrib = (BYTE)(m_comboOsdAttrib.GetCurSel()+1);
			m_struPicCfg[i].byOSDType = (BYTE)m_comboOsdType.GetCurSel();
			m_struPicCfg[i].byFontSize = (BYTE)(m_cmbOsdFont.GetCurSel());
			m_struPicCfg[i].byHourOSDType = (BYTE)m_comboHourType.GetCurSel();
			m_struPicCfg[i].struVILost.byEnableHandleVILost = (BYTE)m_bCheckVILost;
//			m_struPicCfg[i].struAULost.byEnableHandleVILost = m_bChkAuLost;
				//copy image parameters
//			memcpy(&(m_struPicCfg[i].struViColor), &(m_struPicCfg[m_iCurChanIndex].struViColor), sizeof(NET_DVR_VICOLOR));
			m_struAudioIn[i].byAudioInputType = (BYTE)(m_comboAudioInType.GetCurSel());
			m_struAudioIn[i].byVolume = m_byVolume;
			m_bSetChannelPara[i] = TRUE;
		}		
	}
	else
	{//main stream
		CheckRebootParam( &(m_struCompressionCfg[m_iCopyChanIndex].struNormHighRecordPara.byStreamType),\
			m_struMSCompressionCfg[m_iCurChanIndex][NORM_HIGH_STREAM_COMPRESSION].struStreamPara.byStreamType, FALSE);
		CheckRebootParam( &(m_struMSCompressionCfg[m_iCopyChanIndex][NORM_HIGH_STREAM_COMPRESSION].struStreamPara.byStreamType),\
			m_struMSCompressionCfg[m_iCurChanIndex][NORM_HIGH_STREAM_COMPRESSION].struStreamPara.byStreamType, FALSE);				 
		m_struMSCompressionCfg[m_iCopyChanIndex][NORM_HIGH_STREAM_COMPRESSION].struStreamPara.byPicQuality = m_struMSCompressionCfg[m_iCurChanIndex][NORM_HIGH_STREAM_COMPRESSION].struStreamPara.byPicQuality;
		m_struMSCompressionCfg[m_iCopyChanIndex][NORM_HIGH_STREAM_COMPRESSION].struStreamPara.dwVideoBitrate = m_struMSCompressionCfg[m_iCurChanIndex][NORM_HIGH_STREAM_COMPRESSION].struStreamPara.dwVideoBitrate;
		CheckRebootParam( &(m_struMSCompressionCfg[m_iCopyChanIndex][NORM_HIGH_STREAM_COMPRESSION].struStreamPara.byResolution),\
			m_struMSCompressionCfg[m_iCurChanIndex][NORM_HIGH_STREAM_COMPRESSION].struStreamPara.byResolution, TRUE);
		m_struMSCompressionCfg[m_iCopyChanIndex][NORM_HIGH_STREAM_COMPRESSION].struStreamPara.dwVideoFrameRate = m_struMSCompressionCfg[m_iCurChanIndex][NORM_HIGH_STREAM_COMPRESSION].struStreamPara.dwVideoFrameRate;
		m_struMSCompressionCfg[m_iCopyChanIndex][NORM_HIGH_STREAM_COMPRESSION].struStreamPara.byBitrateType = m_struMSCompressionCfg[m_iCurChanIndex][NORM_HIGH_STREAM_COMPRESSION].struStreamPara.byBitrateType;
		m_struMSCompressionCfg[m_iCopyChanIndex][NORM_HIGH_STREAM_COMPRESSION].struStreamPara.byIntervalBPFrame = m_struMSCompressionCfg[m_iCurChanIndex][NORM_HIGH_STREAM_COMPRESSION].struStreamPara.byIntervalBPFrame;	
		m_struMSCompressionCfg[m_iCopyChanIndex][NORM_HIGH_STREAM_COMPRESSION].struStreamPara.wIntervalFrameI = m_struMSCompressionCfg[m_iCurChanIndex][NORM_HIGH_STREAM_COMPRESSION].struStreamPara.wIntervalFrameI;
		m_struMSCompressionCfg[m_iCopyChanIndex][NORM_HIGH_STREAM_COMPRESSION].struStreamPara.byVideoEncType = m_struMSCompressionCfg[m_iCurChanIndex][NORM_HIGH_STREAM_COMPRESSION].struStreamPara.byVideoEncType;	
		m_struMSCompressionCfg[m_iCopyChanIndex][NORM_HIGH_STREAM_COMPRESSION].struStreamPara.byAudioEncType = m_struMSCompressionCfg[m_iCurChanIndex][NORM_HIGH_STREAM_COMPRESSION].struStreamPara.byAudioEncType;
		m_struMSCompressionCfg[m_iCopyChanIndex][NORM_HIGH_STREAM_COMPRESSION].struStreamPara.byVideoEncComplexity = m_struMSCompressionCfg[m_iCurChanIndex][NORM_HIGH_STREAM_COMPRESSION].struStreamPara.byVideoEncComplexity;
		
		//sub stream
		m_struMSCompressionCfg[m_iCopyChanIndex][SUB_STREAM_COMPRESSION].struStreamPara.byStreamType = m_struMSCompressionCfg[m_iCurChanIndex][SUB_STREAM_COMPRESSION].struStreamPara.byStreamType;
		m_struMSCompressionCfg[m_iCopyChanIndex][SUB_STREAM_COMPRESSION].struStreamPara.byPicQuality = m_struMSCompressionCfg[m_iCurChanIndex][SUB_STREAM_COMPRESSION].struStreamPara.byPicQuality;
		m_struMSCompressionCfg[m_iCopyChanIndex][SUB_STREAM_COMPRESSION].struStreamPara.dwVideoBitrate = m_struMSCompressionCfg[m_iCurChanIndex][SUB_STREAM_COMPRESSION].struStreamPara.dwVideoBitrate;
		m_struMSCompressionCfg[m_iCopyChanIndex][SUB_STREAM_COMPRESSION].struStreamPara.byResolution = m_struMSCompressionCfg[m_iCurChanIndex][SUB_STREAM_COMPRESSION].struStreamPara.byResolution;
		m_struMSCompressionCfg[m_iCopyChanIndex][SUB_STREAM_COMPRESSION].struStreamPara.dwVideoFrameRate= m_struMSCompressionCfg[m_iCurChanIndex][SUB_STREAM_COMPRESSION].struStreamPara.dwVideoFrameRate;
		m_struMSCompressionCfg[m_iCopyChanIndex][SUB_STREAM_COMPRESSION].struStreamPara.byBitrateType = m_struMSCompressionCfg[m_iCurChanIndex][SUB_STREAM_COMPRESSION].struStreamPara.byBitrateType;
		m_struMSCompressionCfg[m_iCopyChanIndex][SUB_STREAM_COMPRESSION].struStreamPara.byIntervalBPFrame = m_struMSCompressionCfg[m_iCurChanIndex][SUB_STREAM_COMPRESSION].struStreamPara.byIntervalBPFrame;	
		m_struMSCompressionCfg[m_iCopyChanIndex][SUB_STREAM_COMPRESSION].struStreamPara.wIntervalFrameI = m_struMSCompressionCfg[m_iCurChanIndex][SUB_STREAM_COMPRESSION].struStreamPara.wIntervalFrameI;
		m_struMSCompressionCfg[m_iCopyChanIndex][SUB_STREAM_COMPRESSION].struStreamPara.byVideoEncType = m_struMSCompressionCfg[m_iCurChanIndex][SUB_STREAM_COMPRESSION].struStreamPara.byVideoEncType;	
		m_struMSCompressionCfg[m_iCopyChanIndex][SUB_STREAM_COMPRESSION].struStreamPara.byAudioEncType = m_struMSCompressionCfg[m_iCurChanIndex][SUB_STREAM_COMPRESSION].struStreamPara.byAudioEncType;
		m_struMSCompressionCfg[m_iCopyChanIndex][SUB_STREAM_COMPRESSION].struStreamPara.byVideoEncComplexity = m_struMSCompressionCfg[m_iCurChanIndex][SUB_STREAM_COMPRESSION].struStreamPara.byVideoEncComplexity;
		
		//event
		m_struMSCompressionCfg[m_iCopyChanIndex][EVENT_INVOKE_COMPRESSION].struStreamPara.byStreamType = m_struMSCompressionCfg[m_iCurChanIndex][EVENT_INVOKE_COMPRESSION].struStreamPara.byStreamType;
		m_struMSCompressionCfg[m_iCopyChanIndex][EVENT_INVOKE_COMPRESSION].struStreamPara.byPicQuality = m_struMSCompressionCfg[m_iCurChanIndex][EVENT_INVOKE_COMPRESSION].struStreamPara.byPicQuality;
		m_struMSCompressionCfg[m_iCopyChanIndex][EVENT_INVOKE_COMPRESSION].struStreamPara.dwVideoBitrate = m_struMSCompressionCfg[m_iCurChanIndex][EVENT_INVOKE_COMPRESSION].struStreamPara.dwVideoBitrate;
		m_struMSCompressionCfg[m_iCopyChanIndex][EVENT_INVOKE_COMPRESSION].struStreamPara.byResolution = m_struMSCompressionCfg[m_iCurChanIndex][EVENT_INVOKE_COMPRESSION].struStreamPara.byResolution;
		m_struMSCompressionCfg[m_iCopyChanIndex][EVENT_INVOKE_COMPRESSION].struStreamPara.dwVideoFrameRate = m_struMSCompressionCfg[m_iCurChanIndex][EVENT_INVOKE_COMPRESSION].struStreamPara.dwVideoFrameRate;
		m_struMSCompressionCfg[m_iCopyChanIndex][EVENT_INVOKE_COMPRESSION].struStreamPara.byBitrateType = m_struMSCompressionCfg[m_iCurChanIndex][EVENT_INVOKE_COMPRESSION].struStreamPara.byBitrateType;
		m_struMSCompressionCfg[m_iCopyChanIndex][EVENT_INVOKE_COMPRESSION].struStreamPara.byIntervalBPFrame = m_struMSCompressionCfg[m_iCurChanIndex][EVENT_INVOKE_COMPRESSION].struStreamPara.byIntervalBPFrame;	
		m_struMSCompressionCfg[m_iCopyChanIndex][EVENT_INVOKE_COMPRESSION].struStreamPara.wIntervalFrameI = m_struMSCompressionCfg[m_iCurChanIndex][EVENT_INVOKE_COMPRESSION].struStreamPara.wIntervalFrameI;
		m_struMSCompressionCfg[m_iCopyChanIndex][EVENT_INVOKE_COMPRESSION].struStreamPara.byVideoEncType = m_struMSCompressionCfg[m_iCurChanIndex][EVENT_INVOKE_COMPRESSION].struStreamPara.byVideoEncType;	
		m_struMSCompressionCfg[m_iCopyChanIndex][EVENT_INVOKE_COMPRESSION].struStreamPara.byAudioEncType = m_struMSCompressionCfg[m_iCurChanIndex][EVENT_INVOKE_COMPRESSION].struStreamPara.byAudioEncType;
		m_struMSCompressionCfg[m_iCopyChanIndex][EVENT_INVOKE_COMPRESSION].struStreamPara.byVideoEncComplexity = m_struMSCompressionCfg[m_iCurChanIndex][EVENT_INVOKE_COMPRESSION].struStreamPara.byVideoEncComplexity;
		
		//remote record parameters
		m_struRemoteRecCfg[m_iCopyChanIndex].dwRecord = m_bCheckRecord;
		m_struRemoteRecCfg[m_iCopyChanIndex].dwRecordTime = m_comboRecDelay.GetCurSel();
		m_struRemoteRecCfg[m_iCopyChanIndex].dwPreRecordTime = m_comboPreRecordTime.GetCurSel();
		m_struRemoteRecCfg[m_iCopyChanIndex].dwRecorderDuration = m_dwDurationTime;
		for (k=0; k<MAX_DAYS; k++)
		{
			memcpy(&(m_struRemoteRecCfg[m_iCopyChanIndex].struRecAllDay[k]), &(m_struRemoteRecCfg[m_iCurChanIndex].struRecAllDay[k]), sizeof(NET_DVR_RECORDDAY));
			for (j=0; j<MAX_TIMESEGMENT_V30; j++)
			{
				memcpy(&m_struRemoteRecCfg[m_iCopyChanIndex].struRecordSched[k][j],&m_struRemoteRecCfg[m_iCurChanIndex].struRecordSched[k][j],sizeof(NET_DVR_RECORDSCHED));				
			}
		}
		
		m_struPicCfg[m_iCopyChanIndex].dwEnableHide = m_bCheckHideArea;
		m_struPicCfg[m_iCopyChanIndex].struMotion.byEnableHandleMotion = (BYTE)m_bCheckMotion;
		if (!m_bCheckHideAlarm)
		{
			m_struPicCfg[m_iCopyChanIndex].struHideAlarm.dwEnableHideAlarm = m_bCheckHideAlarm;
		}
		m_struPicCfg[m_iCopyChanIndex].dwShowChanName = m_bCheckChanName;
		m_struPicCfg[m_iCopyChanIndex].wShowNameTopLeftX = (WORD)m_iChanNameX;
		m_struPicCfg[m_iCopyChanIndex].wShowNameTopLeftY = (WORD)m_iChanNameY;
		m_struPicCfg[m_iCopyChanIndex].dwShowOsd = m_bCheckOsd;
		m_struPicCfg[m_iCopyChanIndex].wOSDTopLeftX = (WORD)m_iOsdX;
		m_struPicCfg[m_iCopyChanIndex].wOSDTopLeftY = (WORD)m_iOsdY;
		m_struPicCfg[m_iCopyChanIndex].byDispWeek = (BYTE)m_bChkDispWeek;
		m_struPicCfg[m_iCopyChanIndex].byOSDAttrib = (BYTE)(m_comboOsdAttrib.GetCurSel()+1);
		m_struPicCfg[m_iCopyChanIndex].byOSDType = (BYTE)m_comboOsdType.GetCurSel();
		m_struPicCfg[m_iCopyChanIndex].byFontSize = (BYTE)(m_cmbOsdFont.GetCurSel());
		m_struPicCfg[m_iCopyChanIndex].struVILost.byEnableHandleVILost = (BYTE)m_bCheckVILost;
		m_struAudioIn[m_iCopyChanIndex].byAudioInputType = (BYTE)(m_comboAudioInType.GetCurSel());
		m_bSetChannelPara[m_iCopyChanIndex] = TRUE;
	}
}

/*********************************************************
  Function:	OnBnClickedBtnChanCfgOk
  Desc:		Confirm current channel configuration
  Input:	
  Output:	
  Return:	
**********************************************************/
void CSubDlgChanCfg::OnBnClickedBtnChanCfgOk()
{
	SaveLastCompressTypePara();
	
	UpdateData(TRUE);	
	OnBnClickedBtnCmpOk();
	//record paramerters
	m_struRemoteRecCfg[m_iCurChanIndex].dwRecord = m_bCheckRecord;
	m_struRemoteRecCfg[m_iCurChanIndex].dwRecordTime = m_comboRecDelay.GetCurSel();
	m_struRemoteRecCfg[m_iCurChanIndex].dwPreRecordTime = m_comboPreRecordTime.GetCurSel();
	m_struRemoteRecCfg[m_iCurChanIndex].dwRecorderDuration = m_dwDurationTime;
	m_struRemoteRecCfg[m_iCurChanIndex].byRedundancyRec = (BYTE)m_bChkRedundancyRec;
	m_struRemoteRecCfg[m_iCurChanIndex].byAudioRec = (BYTE)m_bChkAudioRec;
	//channel image paramerters
	memcpy(m_struPicCfg[m_iCurChanIndex].sChanName,m_csChanName,NAME_LEN);
	m_struPicCfg[m_iCurChanIndex].dwEnableHide = m_bCheckHideArea;
	m_struPicCfg[m_iCurChanIndex].struMotion.byEnableHandleMotion = (BYTE)m_bCheckMotion;
	
	//delete this condition judgement
	if (!m_bCheckHideAlarm)
	{
		m_struPicCfg[m_iCurChanIndex].struHideAlarm.dwEnableHideAlarm = m_bCheckHideAlarm;
	}

	m_struPicCfg[m_iCurChanIndex].dwShowChanName = m_bCheckChanName;
	m_struPicCfg[m_iCurChanIndex].wShowNameTopLeftX = (WORD)m_iChanNameX;
	m_struPicCfg[m_iCurChanIndex].wShowNameTopLeftY = (WORD)m_iChanNameY;
	m_struPicCfg[m_iCurChanIndex].dwShowOsd = m_bCheckOsd;
	m_struPicCfg[m_iCurChanIndex].wOSDTopLeftX = (WORD)m_iOsdX;
	m_struPicCfg[m_iCurChanIndex].wOSDTopLeftY = (WORD)m_iOsdY;
	m_struPicCfg[m_iCurChanIndex].byDispWeek = (BYTE)m_bChkDispWeek;
	m_struPicCfg[m_iCurChanIndex].byOSDAttrib = (BYTE)(m_comboOsdAttrib.GetCurSel()+1);
	m_struPicCfg[m_iCurChanIndex].byOSDType = (BYTE)(m_comboOsdType.GetCurSel());
	m_struPicCfg[m_iCurChanIndex].byFontSize = (BYTE)(m_cmbOsdFont.GetCurSel());
	m_struPicCfg[m_iCurChanIndex].byHourOSDType = (BYTE)m_comboHourType.GetCurSel();
	m_struPicCfg[m_iCurChanIndex].struVILost.byEnableHandleVILost = (BYTE)m_bCheckVILost;	
//	m_struPicCfg[m_iCurChanIndex].struAULost.byEnableHandleVILost = m_bChkAuLost;
	
	m_bSetChannelPara[m_iCurChanIndex] = TRUE;
	GetDlgItem(IDC_BTN_CHAN_COPY)->EnableWindow(TRUE);

	m_struCabac[m_iCurChanIndex].dwSize = sizeof(NET_DVR_STREAM_CABAC);
	m_struCabac[m_iCurChanIndex].byCabacEnable = m_bCabacCheck;

	m_struPOEAdapterType[m_iCurChanIndex].dwSize = sizeof(NET_DVR_POE_CHANNEL_ADD_MODE);
	m_struPOEAdapterType[m_iCurChanIndex].byAddMode = (BYTE)m_cmbPoeAdapterType.GetCurSel();

}

/*********************************************************
Function:	CfgSetup
Desc:		Set image paramerters
Input:	
Output:	
Return:	TRUE,setting succeeds;FALSE,settings fails;
**********************************************************/
BOOL CSubDlgChanCfg::CfgSetup()
{
	CString sTemp;
	int i = 0;
	int iChanShow = 0;//display channel number
	char szLan[128] = {0};
	DWORD dwStatus[4] = {0};
	//the confirm button on channel setting is only valid for the selected channel, users need to copy the settings to other channels
	for (i = 0; i < MAX_CHANNUM_V30*2; i++)
	{
		STRU_CHANNEL_INFO *pChannelInfo = &(g_struDeviceInfo[m_iDeviceIndex].struChanInfo[i]);
		iChanShow = pChannelInfo->iChannelNO;
		if (m_bSetChannelPara[i] && g_struDeviceInfo[m_iDeviceIndex].struChanInfo[i].bEnable)
		{
			// 			if (!NET_DVR_SetDVRConfig(m_lLoginID,NET_DVR_SET_COMPRESSCFG_V30, iChanShow,&(m_struCompressionCfg[i]), sizeof(NET_DVR_COMPRESSIONCFG_V30)))
			// 			{
			// 				g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_COMPRESSCFG_V30 %s", g_struDeviceInfo[m_iDeviceIndex].struChanInfo[i].chChanName);
			// 				g_StringLanType(szLan, "��������ʧ��", "Save failed");
			// 				AfxMessageBox(szLan);
			// 				//return FALSE;
			// 			}
			// 			else
			// 			{
			// 				g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_COMPRESSCFG_V30  %s", g_struDeviceInfo[m_iDeviceIndex].struChanInfo[i].chChanName);	
			// 			}
			
			for(int j=0; j<4; j++)
			{			
				m_struMSCond[j].dwSize = sizeof(NET_DVR_MULTI_STREAM_COMPRESSIONCFG_COND);
				m_struMSCond[j].struStreamInfo.dwChannel = iChanShow;
				m_struMSCond[j].dwStreamType = j; 
				m_struMSCompressionCfg[i][j].dwSize = sizeof(NET_DVR_MULTI_STREAM_COMPRESSIONCFG);				
				
			}
			
			if (!NET_DVR_SetDeviceConfig(m_lLoginID, NET_DVR_SET_MULTI_STREAM_COMPRESSIONCFG, 4,
				&m_struMSCond, 4*sizeof(NET_DVR_MULTI_STREAM_COMPRESSIONCFG_COND), &dwStatus, &m_struMSCompressionCfg[i], 4*sizeof(NET_DVR_MULTI_STREAM_COMPRESSIONCFG)))	
			{
				g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_MULTI_STREAM_COMPRESSIONCFG,  %s", g_struDeviceInfo[m_iDeviceIndex].struChanInfo[i].chChanName);
				g_StringLanType(szLan, "��������ʧ��", "Save failed");
				AfxMessageBox(szLan);
				//return FALSE;
			}
			else
			{
				g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_MULTI_STREAM_COMPRESSIONCFG %s", g_struDeviceInfo[m_iDeviceIndex].struChanInfo[i].chChanName);
			}
			
			
			if (!NET_DVR_SetDVRConfig(m_lLoginID,NET_DVR_SET_RECORDCFG_V30, iChanShow,&(m_struRemoteRecCfg[i]), sizeof(NET_DVR_RECORD_V30)))	
			{
				g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_RECORDCFG_V30 %s", g_struDeviceInfo[m_iDeviceIndex].struChanInfo[i].chChanName);
				g_StringLanType(szLan, "��������ʧ��", "Save failed");
				AfxMessageBox(szLan);
				//return FALSE;
			}
			else
			{
				g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_RECORDCFG_V30 %s", g_struDeviceInfo[m_iDeviceIndex].struChanInfo[i].chChanName);
			}
			
			if (!NET_DVR_SetDVRConfig(m_lLoginID, NET_DVR_SET_PICCFG_V30, iChanShow, &(m_struPicCfg[i]), sizeof(NET_DVR_PICCFG_V30)))
			{
				g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "chan[%d]: NET_DVR_SET_PICCFG_V30", iChanShow);
				g_StringLanType(szLan, "��������ʧ��", "Save failed");
				AfxMessageBox(szLan);
				//return FALSE;
			}
			else
			{
				g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_PICCFG_V30 %s", g_struDeviceInfo[m_iDeviceIndex].struChanInfo[i].chChanName);
			}
			
			if (!NET_DVR_SetDVRConfig(m_lLoginID,NET_DVR_SET_AUDIO_INPUT, iChanShow,&(m_struAudioIn[i]), sizeof(NET_DVR_AUDIO_INPUT_PARAM)))
			{
				g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_AUDIO_INPUT %s", g_struDeviceInfo[m_iDeviceIndex].struChanInfo[i].chChanName);
			}
			else
			{
				g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_AUDIO_INPUT  %s", g_struDeviceInfo[m_iDeviceIndex].struChanInfo[i].chChanName);	
			}
			
			if (!NET_DVR_SetDVRConfig(m_lLoginID,NET_DVR_SET_STREAM_CABAC, iChanShow, &(m_struCabac[i]), sizeof(NET_DVR_STREAM_CABAC)))
			{
				g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_STREAM_CABAC %s", g_struDeviceInfo[m_iDeviceIndex].struChanInfo[i].chChanName);
			}
			else
			{
				g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_STREAM_CABAC  %s", g_struDeviceInfo[m_iDeviceIndex].struChanInfo[i].chChanName);	
			}
			
			if (!NET_DVR_SetDVRConfig(m_lLoginID,NET_DVR_SET_POE_CHANNEL_ADD_MODE, iChanShow, &(m_struPOEAdapterType[i]), sizeof(NET_DVR_POE_CHANNEL_ADD_MODE)))
			{
				g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_POE_CHANNEL_ADD_MODE %s", g_struDeviceInfo[m_iDeviceIndex].struChanInfo[i].chChanName);
			}
			else
			{
				g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_POE_CHANNEL_ADD_MODE  %s", g_struDeviceInfo[m_iDeviceIndex].struChanInfo[i].chChanName);	
			}
			
			m_bSetChannelPara[i] = FALSE;
		}
	}
	g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "chan parameter set successfully!"); 
	return TRUE;
	
}

/*********************************************************
  Function:	OnBnClickedBtnChanCfgExit
  Desc:		cancel current channel settings
  Input:	
  Output:	
  Return:	
**********************************************************/
void CSubDlgChanCfg::OnBnClickedBtnChanCfgExit()
{
	for (int i=0; i<m_iChanCount; i++)
	{
		m_bSetChannelPara[i] = FALSE;
	}
}

/*********************************************************
  Function:	OnBnClickedChkRecord
  Desc:		set remote record schedule or not
  Input:	
  Output:	
  Return:	
**********************************************************/
void CSubDlgChanCfg::OnBnClickedChkRecord()
{
	UpdateData(TRUE);
	if (m_bCheckRecord)
	{
		GetDlgItem(IDC_BTN_REMOTE_RECORD_SETUP)->EnableWindow(TRUE);
	}
	else
	{
		GetDlgItem(IDC_BTN_REMOTE_RECORD_SETUP)->EnableWindow(FALSE);
	}
}

/*********************************************************
  Function:	OnBnClickedChkHideArea
  Desc:		set privacy mask or not
  Input:	
  Output:	
  Return:	
**********************************************************/
void CSubDlgChanCfg::OnBnClickedChkHideArea()
{
	UpdateData(TRUE);
	if (m_bCheckHideArea)
	{
		GetDlgItem(IDC_BTN_HIDE_SETUP)->EnableWindow(TRUE);
	}
	else
	{
		GetDlgItem(IDC_BTN_HIDE_SETUP)->EnableWindow(FALSE);
	}
}

/*********************************************************
  Function:	OnBnClickedChkOsd
  Desc:		set osd or not
  Input:	
  Output:	
  Return:	
**********************************************************/
void CSubDlgChanCfg::OnBnClickedChkOsd()
{
	UpdateData(TRUE);
	EnableOsd(m_bCheckOsd);
	UpdateData(FALSE);
}

/*********************************************************
  Function:	EnableOsd
  Desc:		 status of osd parameters in the control
  Input:	bEnable,TRUE,enable;FALSE,disable;
  Output:	
  Return:	
**********************************************************/
void CSubDlgChanCfg::EnableOsd(BOOL bEnable) 
{
	GetDlgItem(IDC_EDIT_OSD_X)->EnableWindow(bEnable);
	GetDlgItem(IDC_EDIT_OSD_Y)->EnableWindow(bEnable);
	GetDlgItem(IDC_COMBO_OSD_ATTRIB)->EnableWindow(bEnable);
	GetDlgItem(IDC_COMBO_OSD_TYPE)->EnableWindow(bEnable);
	GetDlgItem(IDC_CHK_DISPLAY_WEEK)->EnableWindow(bEnable);
}

/*********************************************************
  Function:	OnBnClickedChkChanNamePos
  Desc:		set channel name position or not
  Input:	
  Output:	
  Return:	
**********************************************************/
void CSubDlgChanCfg::OnBnClickedChkChanNamePos()
{
	UpdateData(TRUE);
	EnableChanname(m_bCheckChanName);
	UpdateData(FALSE);
}

/*********************************************************
Function:	EnableChanname
Desc:		channel name position parameters status on the control
Input:	bEnable,TRUE,enable;FALSE,disable;
Output:	
Return:	
**********************************************************/
void CSubDlgChanCfg::EnableChanname(BOOL bEnable) 
{
	GetDlgItem(IDC_EDIT_CHAN_NAME_X)->EnableWindow(bEnable);
	GetDlgItem(IDC_EDIT_CHAN_NAME_Y)->EnableWindow(bEnable);
}

/*********************************************************
  Function:	OnCbnSelchangeComboCopyChan
  Desc:		select the channel number to be copied to
  Input:	
  Output:	
  Return:	
**********************************************************/
void CSubDlgChanCfg::OnCbnSelchangeComboCopyChan()
{
	UpdateData(TRUE);
	DWORD dwSel = m_comboCopyChan.GetCurSel();
	CString csChan = _T("");
	if (dwSel == 0)
	{
		m_iCopyChanIndex =  - 1;
	}
	else
	{
		m_comboCopyChan.SetItemData(1, 1);
		dwSel = m_comboCopyChan.GetItemData(1);
		m_comboCopyChan.GetDlgItemText(dwSel, csChan);
		m_iCopyChanIndex = atoi(csChan.GetBuffer(0));
	}	
}

/*********************************************************
  Function:	OnBnClickedChkMotion
  Desc:		setmotion detect or not
  Input:	
  Output:	
  Return:	
**********************************************************/
void CSubDlgChanCfg::OnBnClickedChkMotion()
{
	UpdateData(TRUE);
	GetDlgItem(IDC_BTN_MOTION_SETUP)->EnableWindow(m_bCheckMotion);
}

/*********************************************************
  Function:	OnBnClickedChkHideAlarm
  Desc:		set view tamper detect or not
  Input:	
  Output:	
  Return:	
**********************************************************/
void CSubDlgChanCfg::OnBnClickedChkHideAlarm()
{
	UpdateData(TRUE);
	GetDlgItem(IDC_BTN_HIDE_ALARM_SETUP)->EnableWindow(m_bCheckHideAlarm);
}

/*********************************************************
  Function:	OnBnClickedChkVilost
  Desc:		set video loss detect or not
  Input:	
  Output:	
  Return:	
**********************************************************/
void CSubDlgChanCfg::OnBnClickedChkVilost()
{
	UpdateData(TRUE);
	GetDlgItem(IDC_BTN_VILOST_SETUP)->EnableWindow(m_bCheckVILost);
}


/*********************************************************
  Function:	FrameIIntervalMap
  Desc:		frame interval
  Input:	
  Output:	
  Return:	
**********************************************************/
WORD CSubDlgChanCfg::FrameIIntervalMap(DWORD nSelFrameRate)
{
	WORD nRet = 0;
	switch (nSelFrameRate)
	{
	case 0:
		nRet = 25;
		break;
	case 6:
		nRet = 2;
		break;
	case 7:
		nRet = 4;
		break;
	case 8:
		nRet = 6;
		break;
	case 9:
		nRet = 8;
		break;
	case 10:
		nRet = 10;
		break;
	case 11:
		nRet = 12;
		break;
	case 12:
		nRet = 16;
		break;
	case 13:
		nRet = 20;
		break;
	case 14:
		nRet = 15;
		break;
	case 15:
		nRet = 18;
		break;
	case 16:
		nRet = 22;
		break;
	default:
		nRet = 1;
	}
	nRet *= 4;
	return nRet;
}

/*********************************************************
  Function:	OnCbnSelchangeComboFrameRate
  Desc:		main stream settings
  Input:	
  Output:	
  Return:	
**********************************************************/
void CSubDlgChanCfg::OnCbnSelchangeComboFrameRate()
{
	UpdateData(TRUE);
	WORD nSel = (WORD)m_comboFrameRate.GetCurSel();
	m_iFrameIInterval = FrameIIntervalMap(nSel);	
	UpdateData(FALSE);
}

/*********************************************************
Function:	UpdateCompressionInfo
Desc:		update compression paraemeters and control display
Input:	
Output:	
Return:	
**********************************************************/
void CSubDlgChanCfg::UpdateCompressionInfo()
{
    UpdateData(TRUE);
	GetDlgItem(IDC_CHK_EVENT_COMPRESS)->ShowWindow(SW_HIDE);
    int nCount = 0;
	switch (m_comboCompressionType.GetItemData(m_comboCompressionType.GetCurSel()))
	{
	case NORM_HIGH_STREAM_COMPRESSION:
        GetResolutionAbility();
		GetDlgItem(IDC_COMBO_STREAM_TYPE)->EnableWindow(TRUE);
		GetDlgItem(IDC_COMBO_RESOLUTION)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_FRAME_I_INTERVAL)->EnableWindow(TRUE);
		GetDlgItem(IDC_COMBO_FRAME_BP_INTERVAL)->EnableWindow(TRUE);

		//�������ͣ������� or ������
        SetBitrateTypeCurSel(m_struMSCompressionCfg[m_iCurChanIndex][NORM_HIGH_STREAM_COMPRESSION].struStreamPara.byBitrateType);
       
		//��������
		if ((m_struMSCompressionCfg[m_iCurChanIndex][NORM_HIGH_STREAM_COMPRESSION].struStreamPara.dwVideoBitrate >> 31) & 0x01) // �Զ���
		{
			GetDlgItem(IDC_EDIT_BIT_RATE)->EnableWindow(TRUE);
			m_comboBitRate.SetCurSel(m_comboBitRate.GetCount()-1);		//adjust bit rate settings
			m_iBitRate = (m_struMSCompressionCfg[m_iCurChanIndex][NORM_HIGH_STREAM_COMPRESSION].struStreamPara.dwVideoBitrate & 0x7fffffff)/1024;
		}
		else
		{
            SetBitrateCurSel(m_struMSCompressionCfg[m_iCurChanIndex][NORM_HIGH_STREAM_COMPRESSION].struStreamPara.dwVideoBitrate);
            m_iBitRate = 0;
			GetDlgItem(IDC_EDIT_BIT_RATE)->EnableWindow(FALSE);
		}	

        SetResolutionCurSel(m_struMSCompressionCfg[m_iCurChanIndex][NORM_HIGH_STREAM_COMPRESSION].struStreamPara.byResolution);
        m_comboStreamType.SetCurSel(m_struMSCompressionCfg[m_iCurChanIndex][NORM_HIGH_STREAM_COMPRESSION].struStreamPara.byStreamType);
		m_comboImageQuality.SetCurSel(m_struMSCompressionCfg[m_iCurChanIndex][NORM_HIGH_STREAM_COMPRESSION].struStreamPara.byPicQuality);

		//m_comboBitRateType.SetCurSel(m_struCompressionCfg[m_iCurChanIndex].struNormHighRecordPara.byBitrateType);
        SetFrameCurSel(m_struMSCompressionCfg[m_iCurChanIndex][NORM_HIGH_STREAM_COMPRESSION].struStreamPara.dwVideoFrameRate);
		//m_comboFrameRate.SetCurSel(m_struCompressionCfg[m_iCurChanIndex].struNormHighRecordPara.dwVideoFrameRate);
		m_comboFrameBPInterval.SetCurSel(m_struMSCompressionCfg[m_iCurChanIndex][NORM_HIGH_STREAM_COMPRESSION].struStreamPara.byIntervalBPFrame);	
		m_iFrameIInterval = m_struMSCompressionCfg[m_iCurChanIndex][NORM_HIGH_STREAM_COMPRESSION].struStreamPara.wIntervalFrameI;

//		m_comboVideoType.EnableWindow(FALSE);
//		m_comboAudioType.EnableWindow(FALSE);
		//2011-05-01
		if (m_struMSCompressionCfg[m_iCurChanIndex][NORM_HIGH_STREAM_COMPRESSION].struStreamPara.byVideoEncType == 0xff)
		{
			//not support this parameter, disable the Combo
			m_comboVideoType.EnableWindow(FALSE);
			m_comboVideoType.SetCurSel(0);
		}
// 		else
// 		{
//             m_comboVideoType.SetCurSel(m_struMSCompressionCfg[m_iCurChanIndex][NORM_HIGH_STREAM_COMPRESSION].struStreamPara.byVideoEncType);
// 		}

		else if (m_struMSCompressionCfg[m_iCurChanIndex][NORM_HIGH_STREAM_COMPRESSION].struStreamPara.byVideoEncType > 2)
		{
			m_comboVideoType.SetCurSel(m_struMSCompressionCfg[m_iCurChanIndex][NORM_HIGH_STREAM_COMPRESSION].struStreamPara.byVideoEncType - 4);
		}
		else
		{
            m_comboVideoType.SetCurSel(m_struMSCompressionCfg[m_iCurChanIndex][NORM_HIGH_STREAM_COMPRESSION].struStreamPara.byVideoEncType);
		}

		if (m_struMSCompressionCfg[m_iCurChanIndex][NORM_HIGH_STREAM_COMPRESSION].struStreamPara.byAudioEncType == 0xff)
		{
			//not support this parameter, disable the Combo
			m_comboAudioType.EnableWindow(FALSE);
			m_comboAudioType.SetCurSel(0);
		}
		else
		{
			m_comboAudioType.SetCurSel(m_struMSCompressionCfg[m_iCurChanIndex][NORM_HIGH_STREAM_COMPRESSION].struStreamPara.byAudioEncType);
		}
		m_comboVideoEncComplexity.SetCurSel(m_struMSCompressionCfg[m_iCurChanIndex][NORM_HIGH_STREAM_COMPRESSION].struStreamPara.byVideoEncComplexity);

		break;
	case SUB_STREAM_COMPRESSION:	
        GetSubResolutionAbility();
		GetDlgItem(IDC_COMBO_STREAM_TYPE)->EnableWindow(TRUE);
		GetDlgItem(IDC_COMBO_RESOLUTION)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_FRAME_I_INTERVAL)->EnableWindow(TRUE);
		GetDlgItem(IDC_COMBO_FRAME_BP_INTERVAL)->EnableWindow(TRUE);
		if ((m_struMSCompressionCfg[m_iCurChanIndex][SUB_STREAM_COMPRESSION].struStreamPara.dwVideoBitrate >> 31) & 0x01)
		{
			GetDlgItem(IDC_EDIT_BIT_RATE)->EnableWindow(TRUE);
			m_comboBitRate.SetCurSel(m_comboBitRate.GetCount()-1);		//adjust bit rate settings
			m_iBitRate = (m_struMSCompressionCfg[m_iCurChanIndex][SUB_STREAM_COMPRESSION].struStreamPara.dwVideoBitrate & 0x7fffffff)/1024;
		}
		else
		{
            SetBitrateCurSel(m_struMSCompressionCfg[m_iCurChanIndex][SUB_STREAM_COMPRESSION].struStreamPara.dwVideoBitrate);
            m_iBitRate = 0;
			GetDlgItem(IDC_EDIT_BIT_RATE)->EnableWindow(FALSE);
		}


        SetResolutionCurSel(m_struMSCompressionCfg[m_iCurChanIndex][SUB_STREAM_COMPRESSION].struStreamPara.byResolution);
		m_comboStreamType.SetCurSel(m_struMSCompressionCfg[m_iCurChanIndex][SUB_STREAM_COMPRESSION].struStreamPara.byStreamType);
		m_comboImageQuality.SetCurSel(m_struMSCompressionCfg[m_iCurChanIndex][SUB_STREAM_COMPRESSION].struStreamPara.byPicQuality);
        SetBitrateTypeCurSel(m_struMSCompressionCfg[m_iCurChanIndex][SUB_STREAM_COMPRESSION].struStreamPara.byBitrateType);
		SetFrameCurSel(m_struMSCompressionCfg[m_iCurChanIndex][SUB_STREAM_COMPRESSION].struStreamPara.dwVideoFrameRate);
        //m_comboFrameRate.SetCurSel(m_struCompressionCfg[m_iCurChanIndex].struNetPara.dwVideoFrameRate);	
		m_comboFrameBPInterval.SetCurSel(m_struMSCompressionCfg[m_iCurChanIndex][SUB_STREAM_COMPRESSION].struStreamPara.byIntervalBPFrame);	
		m_iFrameIInterval = m_struMSCompressionCfg[m_iCurChanIndex][SUB_STREAM_COMPRESSION].struStreamPara.wIntervalFrameI;

		if (m_struMSCompressionCfg[m_iCurChanIndex][SUB_STREAM_COMPRESSION].struStreamPara.byVideoEncType > 2)
		{
			m_comboVideoType.SetCurSel(m_struMSCompressionCfg[m_iCurChanIndex][SUB_STREAM_COMPRESSION].struStreamPara.byVideoEncType - 4);
		}
		else
		{
            m_comboVideoType.SetCurSel(m_struMSCompressionCfg[m_iCurChanIndex][SUB_STREAM_COMPRESSION].struStreamPara.byVideoEncType);
		}
		m_comboAudioType.SetCurSel(m_struMSCompressionCfg[m_iCurChanIndex][SUB_STREAM_COMPRESSION].struStreamPara.byAudioEncType);
		m_comboVideoEncComplexity.SetCurSel(m_struMSCompressionCfg[m_iCurChanIndex][SUB_STREAM_COMPRESSION].struStreamPara.byVideoEncComplexity);
		break;
	case EVENT_INVOKE_COMPRESSION:
        GetEventResolutionAbility();
		GetDlgItem(IDC_CHK_EVENT_COMPRESS)->ShowWindow(SW_SHOW);
		if (m_iCurChanIndex < MAX_ANALOG_CHANNUM)
		{
			EnableEventCtrl(TRUE);
		}
		else
		{
			EnableEventCtrl(FALSE);
		}
		
		
		if ((m_struMSCompressionCfg[m_iCurChanIndex][EVENT_INVOKE_COMPRESSION].struStreamPara.dwVideoBitrate >> 31) & 0x01)
		{
			GetDlgItem(IDC_EDIT_BIT_RATE)->EnableWindow(TRUE);
			m_comboBitRate.SetCurSel(m_comboBitRate.GetCount()-1);		//adjust bit rate settings
			m_iBitRate = (m_struMSCompressionCfg[m_iCurChanIndex][EVENT_INVOKE_COMPRESSION].struStreamPara.dwVideoBitrate & 0x7fffffff)/1024;
		}
		else
		{
            SetBitrateCurSel(m_struMSCompressionCfg[m_iCurChanIndex][EVENT_INVOKE_COMPRESSION].struStreamPara.dwVideoBitrate);
            m_iBitRate = 0;
			GetDlgItem(IDC_EDIT_BIT_RATE)->EnableWindow(FALSE);
		}
		// 		dwResoltion = m_struCompressionCfg[m_iCurChanIndex].struEventRecordPara.byResolution;
		// 		if (dwResoltion >=15)
		// 		{
		// 			dwResoltion = dwResoltion - 11;
		// 		}
		// 		m_comboResolution.SetCurSel(dwResoltion);
		if (m_struMSCompressionCfg[m_iCurChanIndex][EVENT_INVOKE_COMPRESSION].struStreamPara.byStreamType & 0x80)
		{
			m_bEventCompress = TRUE;
			m_struMSCompressionCfg[m_iCurChanIndex][EVENT_INVOKE_COMPRESSION].struStreamPara.byStreamType &= 0x7f;
		}
		else
		{
			m_bEventCompress = FALSE;
			m_struMSCompressionCfg[m_iCurChanIndex][EVENT_INVOKE_COMPRESSION].struStreamPara.byStreamType &= 0x0;

		}
        SetResolutionCurSel(m_struMSCompressionCfg[m_iCurChanIndex][EVENT_INVOKE_COMPRESSION].struStreamPara.byResolution);
		m_comboStreamType.SetCurSel(m_struMSCompressionCfg[m_iCurChanIndex][EVENT_INVOKE_COMPRESSION].struStreamPara.byStreamType);
		m_comboImageQuality.SetCurSel(m_struMSCompressionCfg[m_iCurChanIndex][EVENT_INVOKE_COMPRESSION].struStreamPara.byPicQuality);
        SetBitrateTypeCurSel(m_struMSCompressionCfg[m_iCurChanIndex][EVENT_INVOKE_COMPRESSION].struStreamPara.byBitrateType);
        SetFrameCurSel(m_struMSCompressionCfg[m_iCurChanIndex][EVENT_INVOKE_COMPRESSION].struStreamPara.dwVideoFrameRate);

		m_comboFrameBPInterval.SetCurSel(m_struMSCompressionCfg[m_iCurChanIndex][EVENT_INVOKE_COMPRESSION].struStreamPara.byIntervalBPFrame);	
		m_iFrameIInterval = m_struMSCompressionCfg[m_iCurChanIndex][EVENT_INVOKE_COMPRESSION].struStreamPara.wIntervalFrameI;
		//2011-05-01
		if (m_struMSCompressionCfg[m_iCurChanIndex][EVENT_INVOKE_COMPRESSION].struStreamPara.byVideoEncType == 0xff)
		{
			//not support this parameter, disable the Combo
			m_comboVideoType.EnableWindow(FALSE);
			m_comboVideoType.SetCurSel(0);
		}
// 		else
// 		{
//             m_comboVideoType.SetCurSel(m_struMSCompressionCfg[m_iCurChanIndex][EVENT_INVOKE_COMPRESSION].struStreamPara.byVideoEncType);
// 		}
		else if (m_struMSCompressionCfg[m_iCurChanIndex][EVENT_INVOKE_COMPRESSION].struStreamPara.byVideoEncType > 2)
		{
			m_comboVideoType.SetCurSel(m_struMSCompressionCfg[m_iCurChanIndex][EVENT_INVOKE_COMPRESSION].struStreamPara.byVideoEncType - 4);
		}
		else
		{
            m_comboVideoType.SetCurSel(m_struMSCompressionCfg[m_iCurChanIndex][EVENT_INVOKE_COMPRESSION].struStreamPara.byVideoEncType);
		}
		
		if (m_struMSCompressionCfg[m_iCurChanIndex][EVENT_INVOKE_COMPRESSION].struStreamPara.byAudioEncType == 0xff)
		{
			//not support this parameter, disable the Combo
			m_comboAudioType.EnableWindow(FALSE);
			m_comboAudioType.SetCurSel(0);
		}
		else
		{
			m_comboAudioType.SetCurSel(m_struMSCompressionCfg[m_iCurChanIndex][EVENT_INVOKE_COMPRESSION].struStreamPara.byAudioEncType);
		}
		m_comboVideoEncComplexity.SetCurSel(m_struMSCompressionCfg[m_iCurChanIndex][EVENT_INVOKE_COMPRESSION].struStreamPara.byVideoEncComplexity);
		break;
	case THIRD_STREAM_COMPRESSION:
        GetThirdResolutionAbility();
		GetDlgItem(IDC_COMBO_STREAM_TYPE)->EnableWindow(TRUE);
		GetDlgItem(IDC_COMBO_RESOLUTION)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_FRAME_I_INTERVAL)->EnableWindow(TRUE);
		GetDlgItem(IDC_COMBO_FRAME_BP_INTERVAL)->EnableWindow(TRUE);
		if ((m_struMSCompressionCfg[m_iCurChanIndex][THIRD_STREAM_COMPRESSION].struStreamPara.dwVideoBitrate >> 31) & 0x01)
		{
			GetDlgItem(IDC_EDIT_BIT_RATE)->EnableWindow(TRUE);
			m_comboBitRate.SetCurSel(m_comboBitRate.GetCount()-1);		//adjust bit rate settings
			m_iBitRate = (m_struMSCompressionCfg[m_iCurChanIndex][THIRD_STREAM_COMPRESSION].struStreamPara.dwVideoBitrate & 0x7fffffff)/1024;
		}
		else
		{
            SetBitrateCurSel(m_struMSCompressionCfg[m_iCurChanIndex][THIRD_STREAM_COMPRESSION].struStreamPara.dwVideoBitrate);
            m_iBitRate = 0;
			GetDlgItem(IDC_EDIT_BIT_RATE)->EnableWindow(FALSE);
		}
		
		// 		dwResoltion = m_struCompressionCfg[m_iCurChanIndex].struNetPara.byResolution;
		// // 		if (dwResoltion >=16)
		// // 		{
		// // 			dwResoltion = dwResoltion - 11;
		// // 		}
		// 		m_comboResolution.SetCurSel(dwResoltion-1);
        SetResolutionCurSel(m_struMSCompressionCfg[m_iCurChanIndex][THIRD_STREAM_COMPRESSION].struStreamPara.byResolution);
		m_comboStreamType.SetCurSel(m_struMSCompressionCfg[m_iCurChanIndex][THIRD_STREAM_COMPRESSION].struStreamPara.byStreamType);
		m_comboImageQuality.SetCurSel(m_struMSCompressionCfg[m_iCurChanIndex][THIRD_STREAM_COMPRESSION].struStreamPara.byPicQuality);
        SetBitrateTypeCurSel(m_struMSCompressionCfg[m_iCurChanIndex][THIRD_STREAM_COMPRESSION].struStreamPara.byBitrateType);
		SetFrameCurSel(m_struMSCompressionCfg[m_iCurChanIndex][THIRD_STREAM_COMPRESSION].struStreamPara.dwVideoFrameRate);
        //m_comboFrameRate.SetCurSel(m_struCompressionCfg[m_iCurChanIndex].struNetPara.dwVideoFrameRate);	
		m_comboFrameBPInterval.SetCurSel(m_struMSCompressionCfg[m_iCurChanIndex][THIRD_STREAM_COMPRESSION].struStreamPara.byIntervalBPFrame);	
		m_iFrameIInterval = m_struMSCompressionCfg[m_iCurChanIndex][THIRD_STREAM_COMPRESSION].struStreamPara.wIntervalFrameI;
		
		if (m_struMSCompressionCfg[m_iCurChanIndex][THIRD_STREAM_COMPRESSION].struStreamPara.byVideoEncType > 2)
		{
			m_comboVideoType.SetCurSel(m_struMSCompressionCfg[m_iCurChanIndex][THIRD_STREAM_COMPRESSION].struStreamPara.byVideoEncType - 4);
		}
		else
		{
            m_comboVideoType.SetCurSel(m_struMSCompressionCfg[m_iCurChanIndex][THIRD_STREAM_COMPRESSION].struStreamPara.byVideoEncType);
		}
		m_comboAudioType.SetCurSel(m_struMSCompressionCfg[m_iCurChanIndex][THIRD_STREAM_COMPRESSION].struStreamPara.byAudioEncType);
		m_comboVideoEncComplexity.SetCurSel(m_struMSCompressionCfg[m_iCurChanIndex][THIRD_STREAM_COMPRESSION].struStreamPara.byVideoEncComplexity);
		break;
	default:
		break;
	}
	UpdateData(FALSE);
}

/*********************************************************
Function:	OnCbnSelchangeComboCompressionType
Desc:		update compression parameters and control display
Input:	
Output:	
Return:	
**********************************************************/
void CSubDlgChanCfg::OnCbnSelchangeComboCompressionType()
{
//	SaveLastCompressTypePara();
	UpdateData(TRUE);
	int iCmpType = NORM_HIGH_STREAM_COMPRESSION;
	switch(m_comboCompressionType.GetItemData(m_comboCompressionType.GetCurSel()))
	{
	case 0:
		iCmpType = NORM_HIGH_STREAM_COMPRESSION;
		break;
	case 1:
		iCmpType = SUB_STREAM_COMPRESSION;
		break;
	case 2:
		iCmpType = EVENT_INVOKE_COMPRESSION;
		break;
	case 3:
		iCmpType = THIRD_STREAM_COMPRESSION;
	default:
		break;
	}
// 	if (m_iCompressionTypeSel == iCmpType)
// 	{
// 		return;
// 	}
	m_iCompressionTypeSel = iCmpType;
	UpdateCompressionInfo();
	DoUpdateFrame();
	UpdateData(FALSE);
}

/*********************************************************
  Function:	OnBnClickedBtnCmpOk
  Desc:		finish compression paramertes modification
  Input:	
  Output:	
  Return:	
**********************************************************/
void CSubDlgChanCfg::OnBnClickedBtnCmpOk()
{
	UpdateData(TRUE);
	DWORD dwDefBitRate = 0;
	BYTE byEventResolution = 0;

	m_struAudioIn[m_iCurChanIndex].byAudioInputType = m_comboAudioInType.GetCurSel();
	m_struAudioIn[m_iCurChanIndex].byVolume = m_byVolume;
	switch (m_comboCompressionType.GetCurSel())
	{
	case NORM_HIGH_STREAM_COMPRESSION:
		CheckRebootParam( &(m_struMSCompressionCfg[m_iCurChanIndex][NORM_HIGH_STREAM_COMPRESSION].struStreamPara.byStreamType),\
			m_comboStreamType.GetCurSel(), FALSE);

		m_struMSCompressionCfg[m_iCurChanIndex][NORM_HIGH_STREAM_COMPRESSION].struStreamPara.byPicQuality = (BYTE)m_comboImageQuality.GetCurSel();
		if (m_comboBitRate.GetItemData(m_comboBitRate.GetCurSel()) == -1)	//adjust bit rate settings
		{
			dwDefBitRate = m_iBitRate*1024;		
			if (dwDefBitRate < 32*1024)
			{
				dwDefBitRate = 32*1024;
			}
//2010-6-9 ɾ��������������޵�����
// 			if (dwDefBitRate > 8192*1024)
// 			{
// 				dwDefBitRate =  8192*1024;
// 			}
			dwDefBitRate |= 0x80000000;
			m_struMSCompressionCfg[m_iCurChanIndex][NORM_HIGH_STREAM_COMPRESSION].struStreamPara.dwVideoBitrate = dwDefBitRate;
		}
		else
		{
			m_struMSCompressionCfg[m_iCurChanIndex][NORM_HIGH_STREAM_COMPRESSION].struStreamPara.dwVideoBitrate = m_comboBitRate.GetItemData(m_comboBitRate.GetCurSel());
		}
		CheckRebootParam( &(m_struCompressionCfg[m_iCurChanIndex].struNormHighRecordPara.byResolution),\
			m_comboResolution.GetCurSel(), TRUE);
        m_struMSCompressionCfg[m_iCurChanIndex][NORM_HIGH_STREAM_COMPRESSION].struStreamPara.byResolution = m_comboResolution.GetItemData(m_comboResolution.GetCurSel());
		//	m_struCompressionCfg[m_iCurChanIndex].struNormHighRecordPara.byResolution = m_comboResolution.GetCurSel();
		m_struMSCompressionCfg[m_iCurChanIndex][NORM_HIGH_STREAM_COMPRESSION].struStreamPara.dwVideoFrameRate = m_comboFrameRate.GetItemData(m_comboFrameRate.GetCurSel());
		m_struMSCompressionCfg[m_iCurChanIndex][NORM_HIGH_STREAM_COMPRESSION].struStreamPara.byBitrateType = (BYTE)m_comboBitRateType.GetItemData(m_comboBitRateType.GetCurSel());
		m_struMSCompressionCfg[m_iCurChanIndex][NORM_HIGH_STREAM_COMPRESSION].struStreamPara.byIntervalBPFrame = (BYTE)m_comboFrameBPInterval.GetCurSel();
		m_struMSCompressionCfg[m_iCurChanIndex][NORM_HIGH_STREAM_COMPRESSION].struStreamPara.wIntervalFrameI = (WORD)m_iFrameIInterval;
		
		if (m_comboVideoType.GetCurSel() == 3 ||m_comboVideoType.GetCurSel() == 4)
		{
			m_struMSCompressionCfg[m_iCurChanIndex][NORM_HIGH_STREAM_COMPRESSION].struStreamPara.byVideoEncType = (BYTE)m_comboVideoType.GetCurSel() + 4;
		}
		else
		{
            m_struMSCompressionCfg[m_iCurChanIndex][NORM_HIGH_STREAM_COMPRESSION].struStreamPara.byVideoEncType = (BYTE)m_comboVideoType.GetCurSel();
		}
		
		m_struMSCompressionCfg[m_iCurChanIndex][NORM_HIGH_STREAM_COMPRESSION].struStreamPara.byAudioEncType = (BYTE)m_comboAudioType.GetCurSel();		
		m_struMSCompressionCfg[m_iCurChanIndex][NORM_HIGH_STREAM_COMPRESSION].struStreamPara.byVideoEncComplexity = (BYTE)m_comboVideoEncComplexity.GetCurSel();
		break;
	case SUB_STREAM_COMPRESSION:
		m_struMSCompressionCfg[m_iCurChanIndex][SUB_STREAM_COMPRESSION].struStreamPara.byStreamType = (BYTE)m_comboStreamType.GetCurSel();
		m_struMSCompressionCfg[m_iCurChanIndex][SUB_STREAM_COMPRESSION].struStreamPara.byPicQuality = (BYTE)m_comboImageQuality.GetCurSel();
		if (m_comboBitRate.GetItemData(m_comboBitRate.GetCurSel()) == -1)	//adjust bit rate settings
		{
			dwDefBitRate = m_iBitRate*1024;		
			if (dwDefBitRate < 32*1024)
			{
				dwDefBitRate = 32*1024;
			}
//2010-6-9 ɾ��������������޵�����
// 			if (dwDefBitRate > 8192*1024)
// 			{
// 				dwDefBitRate =  8192*1024;
// 			}
			dwDefBitRate |= 0x80000000;
			m_struMSCompressionCfg[m_iCurChanIndex][SUB_STREAM_COMPRESSION].struStreamPara.dwVideoBitrate = dwDefBitRate;
		}
		else
		{
			m_struMSCompressionCfg[m_iCurChanIndex][SUB_STREAM_COMPRESSION].struStreamPara.dwVideoBitrate = m_comboBitRate.GetItemData(m_comboBitRate.GetCurSel());
		}
		
		m_struMSCompressionCfg[m_iCurChanIndex][SUB_STREAM_COMPRESSION].struStreamPara.byResolution = (BYTE)(m_comboResolution.GetItemData(m_comboResolution.GetCurSel()));
		m_struMSCompressionCfg[m_iCurChanIndex][SUB_STREAM_COMPRESSION].struStreamPara.dwVideoFrameRate = m_comboFrameRate.GetItemData(m_comboFrameRate.GetCurSel());
		m_struMSCompressionCfg[m_iCurChanIndex][SUB_STREAM_COMPRESSION].struStreamPara.byBitrateType = (BYTE)m_comboBitRateType.GetItemData(m_comboBitRateType.GetCurSel());
		m_struMSCompressionCfg[m_iCurChanIndex][SUB_STREAM_COMPRESSION].struStreamPara.byIntervalBPFrame = (BYTE)m_comboFrameBPInterval.GetCurSel();
		m_struMSCompressionCfg[m_iCurChanIndex][SUB_STREAM_COMPRESSION].struStreamPara.wIntervalFrameI = (WORD)m_iFrameIInterval;
		if (m_comboVideoType.GetCurSel() == 3 ||m_comboVideoType.GetCurSel() == 4)
		{
			m_struMSCompressionCfg[m_iCurChanIndex][SUB_STREAM_COMPRESSION].struStreamPara.byVideoEncType = (BYTE)m_comboVideoType.GetCurSel() + 4;
		}
		else
		{
            m_struMSCompressionCfg[m_iCurChanIndex][SUB_STREAM_COMPRESSION].struStreamPara.byVideoEncType = (BYTE)m_comboVideoType.GetCurSel();
		}
		
		m_struMSCompressionCfg[m_iCurChanIndex][SUB_STREAM_COMPRESSION].struStreamPara.byAudioEncType = (BYTE)m_comboAudioType.GetCurSel();		
		m_struMSCompressionCfg[m_iCurChanIndex][SUB_STREAM_COMPRESSION].struStreamPara.byVideoEncComplexity = (BYTE)m_comboVideoEncComplexity.GetCurSel();
		break;
	case EVENT_INVOKE_COMPRESSION:
		m_struMSCompressionCfg[m_iCurChanIndex][EVENT_INVOKE_COMPRESSION].struStreamPara.byStreamType = (BYTE)m_comboStreamType.GetCurSel();
		if (m_bEventCompress)
		{
			m_struMSCompressionCfg[m_iCurChanIndex][EVENT_INVOKE_COMPRESSION].struStreamPara.byStreamType |= 0x80;
		}
		m_struMSCompressionCfg[m_iCurChanIndex][EVENT_INVOKE_COMPRESSION].struStreamPara.byPicQuality = (BYTE)m_comboImageQuality.GetCurSel();
		if (m_comboBitRate.GetItemData(m_comboBitRate.GetCurSel()) == -1)	//adjust bit rate settings
		{
			dwDefBitRate = m_iBitRate*1024;		
			if (dwDefBitRate < 32*1024)
			{
				dwDefBitRate = 32*1024;
			}
//2010-6-9 ɾ��������������޵�����
// 			if (dwDefBitRate > 8192*1024)
// 			{
// 				dwDefBitRate =  8192*1024;
// 			}
			dwDefBitRate |= 0x80000000;
			m_struMSCompressionCfg[m_iCurChanIndex][EVENT_INVOKE_COMPRESSION].struStreamPara.dwVideoBitrate = dwDefBitRate;
		}
		else
		{
			m_struMSCompressionCfg[m_iCurChanIndex][EVENT_INVOKE_COMPRESSION].struStreamPara.dwVideoBitrate = m_comboBitRate.GetItemData(m_comboBitRate.GetCurSel());
		}
		
		byEventResolution = (BYTE)m_comboResolution.GetItemData(m_comboResolution.GetCurSel());
		
		m_struMSCompressionCfg[m_iCurChanIndex][EVENT_INVOKE_COMPRESSION].struStreamPara.byResolution = byEventResolution;
		
		m_struMSCompressionCfg[m_iCurChanIndex][EVENT_INVOKE_COMPRESSION].struStreamPara.dwVideoFrameRate = m_comboFrameRate.GetItemData(m_comboFrameRate.GetCurSel());
		m_struMSCompressionCfg[m_iCurChanIndex][EVENT_INVOKE_COMPRESSION].struStreamPara.byBitrateType = (BYTE)m_comboBitRateType.GetItemData(m_comboBitRateType.GetCurSel());
		m_struMSCompressionCfg[m_iCurChanIndex][EVENT_INVOKE_COMPRESSION].struStreamPara.byIntervalBPFrame = (BYTE)m_comboFrameBPInterval.GetCurSel();
		m_struMSCompressionCfg[m_iCurChanIndex][EVENT_INVOKE_COMPRESSION].struStreamPara.wIntervalFrameI = (WORD)m_iFrameIInterval;
	
		//		m_struCompressionCfg[m_iCurChanIndex].struEventRecordPara.byIntervalBPFrame = m_comboFrameBPInterval.GetCurSel();//same with main stream
		//m_struCompressionCfg[m_iCurChanIndex].struEventRecordPara.wIntervalFrameI = m_iFrameIInterval;//same with main stream


		
		if (m_comboVideoType.GetCurSel() == 3 ||m_comboVideoType.GetCurSel() == 4)
		{
			m_struMSCompressionCfg[m_iCurChanIndex][EVENT_INVOKE_COMPRESSION].struStreamPara.byVideoEncType = (BYTE)m_comboVideoType.GetCurSel() + 4;
		}
		else
		{
            m_struMSCompressionCfg[m_iCurChanIndex][EVENT_INVOKE_COMPRESSION].struStreamPara.byVideoEncType = (BYTE)m_comboVideoType.GetCurSel();
		}
		
		m_struMSCompressionCfg[m_iCurChanIndex][EVENT_INVOKE_COMPRESSION].struStreamPara.byAudioEncType = (BYTE)m_comboAudioType.GetCurSel();
		m_struMSCompressionCfg[m_iCurChanIndex][EVENT_INVOKE_COMPRESSION].struStreamPara.byVideoEncComplexity = (BYTE)m_comboVideoEncComplexity.GetCurSel();
		break;
	case THIRD_STREAM_COMPRESSION:
		m_struMSCompressionCfg[m_iCurChanIndex][THIRD_STREAM_COMPRESSION].dwStreamType = THIRD_STREAM_COMPRESSION;
        m_struMSCompressionCfg[m_iCurChanIndex][THIRD_STREAM_COMPRESSION].struStreamPara.byStreamType = (BYTE)m_comboStreamType.GetCurSel();
		m_struMSCompressionCfg[m_iCurChanIndex][THIRD_STREAM_COMPRESSION].struStreamPara.byPicQuality = (BYTE)m_comboImageQuality.GetCurSel();
		if (m_comboBitRate.GetItemData(m_comboBitRate.GetCurSel()) == -1)	//adjust bit rate settings
		{
			dwDefBitRate = m_iBitRate*1024;		
			if (dwDefBitRate < 32*1024)
			{
				dwDefBitRate = 32*1024;
			}
			//2010-6-9 ɾ��������������޵�����
			// 			if (dwDefBitRate > 8192*1024)
			// 			{
			// 				dwDefBitRate =  8192*1024;
			// 			}
			dwDefBitRate |= 0x80000000;
			m_struMSCompressionCfg[m_iCurChanIndex][THIRD_STREAM_COMPRESSION].struStreamPara.dwVideoBitrate = dwDefBitRate;
		}
		else
		{
			m_struMSCompressionCfg[m_iCurChanIndex][THIRD_STREAM_COMPRESSION].struStreamPara.dwVideoBitrate = m_comboBitRate.GetItemData(m_comboBitRate.GetCurSel());
		}
		
		m_struMSCompressionCfg[m_iCurChanIndex][THIRD_STREAM_COMPRESSION].struStreamPara.byResolution = (BYTE)(m_comboResolution.GetItemData(m_comboResolution.GetCurSel()));
		m_struMSCompressionCfg[m_iCurChanIndex][THIRD_STREAM_COMPRESSION].struStreamPara.dwVideoFrameRate = m_comboFrameRate.GetItemData(m_comboFrameRate.GetCurSel());
		m_struMSCompressionCfg[m_iCurChanIndex][THIRD_STREAM_COMPRESSION].struStreamPara.byBitrateType = (BYTE)m_comboBitRateType.GetItemData(m_comboBitRateType.GetCurSel());
		m_struMSCompressionCfg[m_iCurChanIndex][THIRD_STREAM_COMPRESSION].struStreamPara.byIntervalBPFrame = (BYTE)m_comboFrameBPInterval.GetCurSel();
		m_struMSCompressionCfg[m_iCurChanIndex][THIRD_STREAM_COMPRESSION].struStreamPara.wIntervalFrameI = (WORD)m_iFrameIInterval;
		if (m_comboVideoType.GetCurSel() == 3 ||m_comboVideoType.GetCurSel() == 4)
		{
			m_struMSCompressionCfg[m_iCurChanIndex][THIRD_STREAM_COMPRESSION].struStreamPara.byVideoEncType = (BYTE)m_comboVideoType.GetCurSel() + 4;
		}
		else
		{
            m_struMSCompressionCfg[m_iCurChanIndex][THIRD_STREAM_COMPRESSION].struStreamPara.byVideoEncType = (BYTE)m_comboVideoType.GetCurSel();
		}
		
		m_struMSCompressionCfg[m_iCurChanIndex][THIRD_STREAM_COMPRESSION].struStreamPara.byAudioEncType = (BYTE)m_comboAudioType.GetCurSel();		
		m_struMSCompressionCfg[m_iCurChanIndex][THIRD_STREAM_COMPRESSION].struStreamPara.byVideoEncComplexity = (BYTE)m_comboVideoEncComplexity.GetCurSel();
		break;
	default:
		break;
	}
}


/*********************************************************
  Function:	SaveLastCompressTypePara
  Desc:		Save parameter when Compress Type changed
  Input:	
  Output:	
  Return:	
**********************************************************/
void CSubDlgChanCfg::SaveLastCompressTypePara()
{
    UpdateData(TRUE);
	DWORD dwDefBitRate = 0;
	BYTE byEventResolution = 0;
	switch (m_iCompressionTypeSel)
	{
	case NORM_HIGH_STREAM_COMPRESSION:
		CheckRebootParam( &(m_struMSCompressionCfg[m_iCurChanIndex][NORM_HIGH_STREAM_COMPRESSION].struStreamPara.byStreamType),\
			m_comboStreamType.GetCurSel(), FALSE);
		
		m_struMSCompressionCfg[m_iCurChanIndex][NORM_HIGH_STREAM_COMPRESSION].struStreamPara.byPicQuality = (BYTE)m_comboImageQuality.GetCurSel();
		if (m_comboBitRate.GetItemData(m_comboBitRate.GetCurSel()) == -1)	//adjust bit rate settings
		{
			dwDefBitRate = m_iBitRate*1024;		
			if (dwDefBitRate < 32*1024)
			{
				dwDefBitRate = 32*1024;
			}
//2010-6-9 ɾ��������������޵�����
// 			if (dwDefBitRate > 8192*1024)
// 			{
// 				dwDefBitRate =  8192*1024;
// 			}
			dwDefBitRate |= 0x80000000;
			m_struMSCompressionCfg[m_iCurChanIndex][NORM_HIGH_STREAM_COMPRESSION].struStreamPara.dwVideoBitrate = dwDefBitRate;
		}
		else
		{
			m_struMSCompressionCfg[m_iCurChanIndex][NORM_HIGH_STREAM_COMPRESSION].struStreamPara.dwVideoBitrate = m_comboBitRate.GetItemData(m_comboBitRate.GetCurSel());
		}
		CheckRebootParam( &(m_struCompressionCfg[m_iCurChanIndex].struNormHighRecordPara.byResolution),\
			m_comboResolution.GetCurSel(), TRUE);
        m_struMSCompressionCfg[m_iCurChanIndex][NORM_HIGH_STREAM_COMPRESSION].struStreamPara.byResolution = m_comboResolution.GetItemData(m_comboResolution.GetCurSel());
	//	m_struCompressionCfg[m_iCurChanIndex].struNormHighRecordPara.byResolution = m_comboResolution.GetCurSel();
		m_struMSCompressionCfg[m_iCurChanIndex][NORM_HIGH_STREAM_COMPRESSION].struStreamPara.dwVideoFrameRate = m_comboFrameRate.GetItemData(m_comboFrameRate.GetCurSel());
		m_struMSCompressionCfg[m_iCurChanIndex][NORM_HIGH_STREAM_COMPRESSION].struStreamPara.byBitrateType = (BYTE)m_comboBitRateType.GetItemData(m_comboBitRateType.GetCurSel());
		m_struMSCompressionCfg[m_iCurChanIndex][NORM_HIGH_STREAM_COMPRESSION].struStreamPara.byIntervalBPFrame = (BYTE)m_comboFrameBPInterval.GetCurSel();
		m_struMSCompressionCfg[m_iCurChanIndex][NORM_HIGH_STREAM_COMPRESSION].struStreamPara.wIntervalFrameI = (WORD)m_iFrameIInterval;

		if (m_comboVideoType.GetCurSel() == 3 ||m_comboVideoType.GetCurSel() == 4)
		{
			m_struMSCompressionCfg[m_iCurChanIndex][NORM_HIGH_STREAM_COMPRESSION].struStreamPara.byVideoEncType = (BYTE)m_comboVideoType.GetCurSel() + 4;
		}
		else
		{
            m_struMSCompressionCfg[m_iCurChanIndex][NORM_HIGH_STREAM_COMPRESSION].struStreamPara.byVideoEncType = (BYTE)m_comboVideoType.GetCurSel();
		}
		m_struMSCompressionCfg[m_iCurChanIndex][NORM_HIGH_STREAM_COMPRESSION].struStreamPara.byAudioEncType = (BYTE)m_comboAudioType.GetCurSel();		
		m_struMSCompressionCfg[m_iCurChanIndex][NORM_HIGH_STREAM_COMPRESSION].struStreamPara.byVideoEncComplexity = (BYTE)m_comboVideoEncComplexity.GetCurSel();
		break;
	case SUB_STREAM_COMPRESSION:
		m_struMSCompressionCfg[m_iCurChanIndex][SUB_STREAM_COMPRESSION].struStreamPara.byStreamType = (BYTE)m_comboStreamType.GetCurSel();
		m_struMSCompressionCfg[m_iCurChanIndex][SUB_STREAM_COMPRESSION].struStreamPara.byPicQuality = (BYTE)m_comboImageQuality.GetCurSel();
		if (m_comboBitRate.GetItemData(m_comboBitRate.GetCurSel()) == -1)	//adjust bit rate settings
		{
			dwDefBitRate = m_iBitRate*1024;		
			if (dwDefBitRate < 32*1024)
			{
				dwDefBitRate = 32*1024;
			}
//2010-6-9 ɾ��������������޵�����
// 			if (dwDefBitRate > 8192*1024)
// 			{
// 				dwDefBitRate =  8192*1024;
// 			}
			dwDefBitRate |= 0x80000000;
			m_struMSCompressionCfg[m_iCurChanIndex][SUB_STREAM_COMPRESSION].struStreamPara.dwVideoBitrate = dwDefBitRate;
		}
		else
		{
			m_struMSCompressionCfg[m_iCurChanIndex][SUB_STREAM_COMPRESSION].struStreamPara.dwVideoBitrate = m_comboBitRate.GetItemData(m_comboBitRate.GetCurSel());
		}
		
		m_struMSCompressionCfg[m_iCurChanIndex][SUB_STREAM_COMPRESSION].struStreamPara.byResolution = (BYTE)(m_comboResolution.GetItemData(m_comboResolution.GetCurSel()));
		m_struMSCompressionCfg[m_iCurChanIndex][SUB_STREAM_COMPRESSION].struStreamPara.dwVideoFrameRate = m_comboFrameRate.GetItemData(m_comboFrameRate.GetCurSel());
		m_struMSCompressionCfg[m_iCurChanIndex][SUB_STREAM_COMPRESSION].struStreamPara.byBitrateType = (BYTE)m_comboBitRateType.GetItemData(m_comboBitRateType.GetCurSel());
		m_struMSCompressionCfg[m_iCurChanIndex][SUB_STREAM_COMPRESSION].struStreamPara.byIntervalBPFrame = (BYTE)m_comboFrameBPInterval.GetCurSel();
		m_struMSCompressionCfg[m_iCurChanIndex][SUB_STREAM_COMPRESSION].struStreamPara.wIntervalFrameI = (WORD)m_iFrameIInterval;
		if (m_comboVideoType.GetCurSel() == 3||m_comboVideoType.GetCurSel() == 4)
		{
			m_struMSCompressionCfg[m_iCurChanIndex][SUB_STREAM_COMPRESSION].struStreamPara.byVideoEncType = (BYTE)m_comboVideoType.GetCurSel() + 4;
		}
		else
		{
            m_struMSCompressionCfg[m_iCurChanIndex][SUB_STREAM_COMPRESSION].struStreamPara.byVideoEncType = (BYTE)m_comboVideoType.GetCurSel();
		}
		
		m_struMSCompressionCfg[m_iCurChanIndex][SUB_STREAM_COMPRESSION].struStreamPara.byAudioEncType = (BYTE)m_comboAudioType.GetCurSel();		
		m_struMSCompressionCfg[m_iCurChanIndex][SUB_STREAM_COMPRESSION].struStreamPara.byVideoEncComplexity = (BYTE)m_comboVideoEncComplexity.GetCurSel();
		break;
	case EVENT_INVOKE_COMPRESSION:
		m_struMSCompressionCfg[m_iCurChanIndex][EVENT_INVOKE_COMPRESSION].struStreamPara.byStreamType = (BYTE)m_comboStreamType.GetCurSel();
		if (m_bEventCompress)
		{
			m_struMSCompressionCfg[m_iCurChanIndex][EVENT_INVOKE_COMPRESSION].struStreamPara.byStreamType |= 0x80;
		//	m_bEventCompress = FALSE;
		}
		m_struMSCompressionCfg[m_iCurChanIndex][EVENT_INVOKE_COMPRESSION].struStreamPara.byPicQuality = (BYTE)m_comboImageQuality.GetCurSel();
		if (m_comboBitRate.GetItemData(m_comboBitRate.GetCurSel()) == -1)	//adjust bit rate settings
		{
			dwDefBitRate = m_iBitRate*1024;		
			if (dwDefBitRate < 32*1024)
			{
				dwDefBitRate = 32*1024;
			}
//2010-6-9 ɾ��������������޵�����
// 			if (dwDefBitRate > 8192*1024)
// 			{
// 				dwDefBitRate =  8192*1024;
// 			}
			dwDefBitRate |= 0x80000000;
			m_struMSCompressionCfg[m_iCurChanIndex][EVENT_INVOKE_COMPRESSION].struStreamPara.dwVideoBitrate = dwDefBitRate;
		}
		else
		{
			m_struMSCompressionCfg[m_iCurChanIndex][EVENT_INVOKE_COMPRESSION].struStreamPara.dwVideoBitrate = m_comboBitRate.GetItemData(m_comboBitRate.GetCurSel());
		}

		byEventResolution = (BYTE)m_comboResolution.GetItemData(m_comboResolution.GetCurSel());

		m_struMSCompressionCfg[m_iCurChanIndex][EVENT_INVOKE_COMPRESSION].struStreamPara.byResolution = byEventResolution;

		m_struMSCompressionCfg[m_iCurChanIndex][EVENT_INVOKE_COMPRESSION].struStreamPara.dwVideoFrameRate = m_comboFrameRate.GetItemData(m_comboFrameRate.GetCurSel());
		m_struMSCompressionCfg[m_iCurChanIndex][EVENT_INVOKE_COMPRESSION].struStreamPara.byBitrateType = (BYTE)m_comboBitRateType.GetItemData(m_comboBitRateType.GetCurSel());
//		m_struCompressionCfg[m_iCurChanIndex].struEventRecordPara.byIntervalBPFrame = m_comboFrameBPInterval.GetCurSel();//same with main stream
		//m_struCompressionCfg[m_iCurChanIndex].struEventRecordPara.wIntervalFrameI = m_iFrameIInterval;//same with main stream

		if (m_comboVideoType.GetCurSel() == 3||m_comboVideoType.GetCurSel() == 4)
		{
			m_struMSCompressionCfg[m_iCurChanIndex][EVENT_INVOKE_COMPRESSION].struStreamPara.byVideoEncType = (BYTE)m_comboVideoType.GetCurSel() + 4;
		}
		else
		{
            m_struMSCompressionCfg[m_iCurChanIndex][EVENT_INVOKE_COMPRESSION].struStreamPara.byVideoEncType = (BYTE)m_comboVideoType.GetCurSel();
		}
		
		m_struMSCompressionCfg[m_iCurChanIndex][EVENT_INVOKE_COMPRESSION].struStreamPara.byAudioEncType = (BYTE)m_comboAudioType.GetCurSel();
		m_struMSCompressionCfg[m_iCurChanIndex][EVENT_INVOKE_COMPRESSION].struStreamPara.byVideoEncComplexity = (BYTE)m_comboVideoEncComplexity.GetCurSel();
		break;
	case THIRD_STREAM_COMPRESSION:
		m_struMSCompressionCfg[m_iCurChanIndex][THIRD_STREAM_COMPRESSION].dwStreamType = THIRD_STREAM_COMPRESSION;
        m_struMSCompressionCfg[m_iCurChanIndex][THIRD_STREAM_COMPRESSION].struStreamPara.byStreamType = (BYTE)m_comboStreamType.GetCurSel();
		m_struMSCompressionCfg[m_iCurChanIndex][THIRD_STREAM_COMPRESSION].struStreamPara.byPicQuality = (BYTE)m_comboImageQuality.GetCurSel();
		if (m_comboBitRate.GetItemData(m_comboBitRate.GetCurSel()) == -1)	//adjust bit rate settings
		{
			dwDefBitRate = m_iBitRate*1024;		
			if (dwDefBitRate < 32*1024)
			{
				dwDefBitRate = 32*1024;
			}
			//2010-6-9 ɾ��������������޵�����
			// 			if (dwDefBitRate > 8192*1024)
			// 			{
			// 				dwDefBitRate =  8192*1024;
			// 			}
			dwDefBitRate |= 0x80000000;
			m_struMSCompressionCfg[m_iCurChanIndex][THIRD_STREAM_COMPRESSION].struStreamPara.dwVideoBitrate = dwDefBitRate;
		}
		else
		{
			m_struMSCompressionCfg[m_iCurChanIndex][THIRD_STREAM_COMPRESSION].struStreamPara.dwVideoBitrate = m_comboBitRate.GetItemData(m_comboBitRate.GetCurSel());
		}
		
		m_struMSCompressionCfg[m_iCurChanIndex][THIRD_STREAM_COMPRESSION].struStreamPara.byResolution = (BYTE)(m_comboResolution.GetItemData(m_comboResolution.GetCurSel()));
		m_struMSCompressionCfg[m_iCurChanIndex][THIRD_STREAM_COMPRESSION].struStreamPara.dwVideoFrameRate = m_comboFrameRate.GetItemData(m_comboFrameRate.GetCurSel());
		m_struMSCompressionCfg[m_iCurChanIndex][THIRD_STREAM_COMPRESSION].struStreamPara.byBitrateType = (BYTE)m_comboBitRateType.GetItemData(m_comboBitRateType.GetCurSel());
		m_struMSCompressionCfg[m_iCurChanIndex][THIRD_STREAM_COMPRESSION].struStreamPara.byIntervalBPFrame = (BYTE)m_comboFrameBPInterval.GetCurSel();
		m_struMSCompressionCfg[m_iCurChanIndex][THIRD_STREAM_COMPRESSION].struStreamPara.wIntervalFrameI = (WORD)m_iFrameIInterval;
		if (m_comboVideoType.GetCurSel() == 3||m_comboVideoType.GetCurSel() == 4)
		{
			m_struMSCompressionCfg[m_iCurChanIndex][THIRD_STREAM_COMPRESSION].struStreamPara.byVideoEncType = (BYTE)m_comboVideoType.GetCurSel() + 4;
		}
		else
		{
            m_struMSCompressionCfg[m_iCurChanIndex][THIRD_STREAM_COMPRESSION].struStreamPara.byVideoEncType = (BYTE)m_comboVideoType.GetCurSel();
		}
		
		m_struMSCompressionCfg[m_iCurChanIndex][THIRD_STREAM_COMPRESSION].struStreamPara.byAudioEncType = (BYTE)m_comboAudioType.GetCurSel();		
		m_struMSCompressionCfg[m_iCurChanIndex][THIRD_STREAM_COMPRESSION].struStreamPara.byVideoEncComplexity = (BYTE)m_comboVideoEncComplexity.GetCurSel();
		break;
	default:
		break;
	}
}


/*********************************************************
  Function:	CheckRebootParam
  Desc:		detect parameter modification and judge if reboot is needed
  Input:	iCurVal,current value;iModVal,modified value;bJudge,judge device type or not��FALSE:need reboot for all the devices;
  Output:	
  Return:	
**********************************************************/
void CSubDlgChanCfg::CheckRebootParam(BYTE *byCurVal, int iModVal, BOOL bJudge)
{
	if ((*byCurVal) != iModVal)
	{
		*byCurVal = (BYTE)iModVal;
		if (!bJudge && g_pMainDlg->IsNeedRebootDevType())
		{
			g_bMustReboot = TRUE;
		}
		else
		{
			g_bMustReboot = FALSE;
		}
	}
}

/*********************************************************
  Function:	OnCbnSelchangeComboMaxBitRate
  Desc:		select user-defined bit rate
  Input:	
  Output:	
  Return:	
**********************************************************/
void CSubDlgChanCfg::OnCbnSelchangeComboMaxBitRate()
{
	UpdateData(TRUE);
//2010-6-9 ��Ҫ����������ȡ����ĸ���
	if (m_comboBitRate.GetCurSel() == m_comboBitRate.GetCount() - 1/*22*/)	//self-define bitrate
	{
		GetDlgItem(IDC_EDIT_BIT_RATE)->EnableWindow(TRUE);
	}
	else
	{
		GetDlgItem(IDC_EDIT_BIT_RATE)->EnableWindow(FALSE);
	}
}

/*********************************************************
  Function:	EnableEventCtrl
  Desc:		enable  control or not, when the compression is event type
  Input:	bEnable, TRUE/FALSE
  Output:	none
  Return:	none
**********************************************************/
void CSubDlgChanCfg::EnableEventCtrl(BOOL bEnable)
{
	GetDlgItem(IDC_COMBO_STREAM_TYPE)->EnableWindow(bEnable);
	GetDlgItem(IDC_COMBO_RESOLUTION)->EnableWindow(bEnable);
	GetDlgItem(IDC_EDIT_FRAME_I_INTERVAL)->EnableWindow(bEnable);
	GetDlgItem(IDC_COMBO_FRAME_BP_INTERVAL)->EnableWindow(bEnable);
}
    
void CSubDlgChanCfg::GetResolutionAbility()
{
    for (int nAbilityCount = 0; nAbilityCount < m_pCompresscfgAbility->dwAbilityNum; nAbilityCount++)
    {
        if (MAIN_RESOLUTION_ABILITY == m_pCompresscfgAbility->struAbilityNode[nAbilityCount].dwAbilityType)
        {
            m_comboResolution.ResetContent();
            for (int i = 0; i < m_pCompresscfgAbility->struAbilityNode[nAbilityCount].dwNodeNum; i++)
            {
                m_comboResolution.AddString((char*)m_pCompresscfgAbility->struAbilityNode[nAbilityCount].struDescNode[i].byDescribe);
                m_comboResolution.SetItemData(i, m_pCompresscfgAbility->struAbilityNode[nAbilityCount].struDescNode[i].iValue);
            }
        }
    }
}

void CSubDlgChanCfg::GetSubResolutionAbility()
{
    for (int nAbilityCount = 0; nAbilityCount < m_pCompresscfgAbility->dwAbilityNum; nAbilityCount++)
    {
        if (SUB_RESOLUTION_ABILITY == m_pCompresscfgAbility->struAbilityNode[nAbilityCount].dwAbilityType)
        {
            m_comboResolution.ResetContent();
            for (int i = 0; i < m_pCompresscfgAbility->struAbilityNode[nAbilityCount].dwNodeNum; i++)
            {
                m_comboResolution.AddString((char*)m_pCompresscfgAbility->struAbilityNode[nAbilityCount].struDescNode[i].byDescribe);
                m_comboResolution.SetItemData(i, m_pCompresscfgAbility->struAbilityNode[nAbilityCount].struDescNode[i].iValue);
            }
        }
    }
}

void CSubDlgChanCfg::GetEventResolutionAbility()
{
    for (int nAbilityCount = 0; nAbilityCount < m_pCompresscfgAbility->dwAbilityNum; nAbilityCount++)
    {
        if (EVENT_RESOLUTION_ABILITY == m_pCompresscfgAbility->struAbilityNode[nAbilityCount].dwAbilityType)
        {
            m_comboResolution.ResetContent();
            for (int i = 0; i < m_pCompresscfgAbility->struAbilityNode[nAbilityCount].dwNodeNum; i++)
            {
                m_comboResolution.AddString((char*)m_pCompresscfgAbility->struAbilityNode[nAbilityCount].struDescNode[i].byDescribe);
                m_comboResolution.SetItemData(i, m_pCompresscfgAbility->struAbilityNode[nAbilityCount].struDescNode[i].iValue);
            }
        }
    }
}


void CSubDlgChanCfg::GetThirdResolutionAbility()
{
    for (int nAbilityCount = 0; nAbilityCount < m_pCompresscfgAbility->dwAbilityNum; nAbilityCount++)
    {
        if (THIRD_RESOLUTION_ABILITY == m_pCompresscfgAbility->struAbilityNode[nAbilityCount].dwAbilityType)
        {
            m_comboResolution.ResetContent();
            for (int i = 0; i < m_pCompresscfgAbility->struAbilityNode[nAbilityCount].dwNodeNum; i++)
            {
                m_comboResolution.AddString((char*)m_pCompresscfgAbility->struAbilityNode[nAbilityCount].struDescNode[i].byDescribe);
                m_comboResolution.SetItemData(i, m_pCompresscfgAbility->struAbilityNode[nAbilityCount].struDescNode[i].iValue);
            }
        }
    }
}

void CSubDlgChanCfg::GetBitrateTypeAbility()
{
    for (int nAbilityCount = 0; nAbilityCount < m_pCompresscfgAbility->dwAbilityNum; nAbilityCount++)
    {
        if (BITRATE_TYPE_ABILITY == m_pCompresscfgAbility->struAbilityNode[nAbilityCount].dwAbilityType)
        {
            m_comboBitRateType.ResetContent();
            for (int i = 0; i < m_pCompresscfgAbility->struAbilityNode[nAbilityCount].dwNodeNum; i++)
            {
                m_comboBitRateType.AddString((char*)m_pCompresscfgAbility->struAbilityNode[nAbilityCount].struDescNode[i].byDescribe);
                m_comboBitRateType.SetItemData(i, m_pCompresscfgAbility->struAbilityNode[nAbilityCount].struDescNode[i].iValue);
            }
        }
    }
}

void CSubDlgChanCfg::GetBitrateAbility()
{
    for (int nAbilityCount = 0; nAbilityCount < m_pCompresscfgAbility->dwAbilityNum; nAbilityCount++)
    {
        if (BITRATE_ABILITY == m_pCompresscfgAbility->struAbilityNode[nAbilityCount].dwAbilityType)
        {
            m_comboBitRate.ResetContent();
            for (int i = 0; i < m_pCompresscfgAbility->struAbilityNode[nAbilityCount].dwNodeNum; i++)
            {
                m_comboBitRate.AddString((char*)m_pCompresscfgAbility->struAbilityNode[nAbilityCount].struDescNode[i].byDescribe);
                m_comboBitRate.SetItemData(i, m_pCompresscfgAbility->struAbilityNode[nAbilityCount].struDescNode[i].iValue);
            }
        }
    }
}

void CSubDlgChanCfg::GetFrameAbility()
{
    for (int nAbilityCount = 0; nAbilityCount < m_pCompresscfgAbility->dwAbilityNum; nAbilityCount++)
    {
        if (FRAME_ABILITY == m_pCompresscfgAbility->struAbilityNode[nAbilityCount].dwAbilityType)
        {
            m_comboFrameRate.ResetContent();
            for (int i = 0; i < m_pCompresscfgAbility->struAbilityNode[nAbilityCount].dwNodeNum; i++)
            {
                m_comboFrameRate.AddString((char*)m_pCompresscfgAbility->struAbilityNode[nAbilityCount].struDescNode[i].byDescribe);
                m_comboFrameRate.SetItemData(i, m_pCompresscfgAbility->struAbilityNode[nAbilityCount].struDescNode[i].iValue);
            }
        }
    }
}

BOOL CSubDlgChanCfg::GetCompressCfgAbility(DWORD dwIPChanIndex)
{
    if (!NET_DVR_GetDeviceAbility(m_lLoginID, COMPRESSIONCFG_ABILITY, (char*)&dwIPChanIndex, sizeof(dwIPChanIndex), (char*)m_pCompresscfgAbility, sizeof(NET_DVR_COMPRESSIONCFG_ABILITY)))
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "COMPRESSIONCFG_ABILITY");
        return FALSE;    
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "COMPRESSIONCFG_ABILITY");
        return TRUE;
    }
}

void CSubDlgChanCfg::GetStreamTypeAbility()
{
    for (int nAbilityCount = 0; nAbilityCount < m_pCompresscfgAbility->dwAbilityNum; nAbilityCount++)
    {
        if (COMPRESSION_STREAM_ABILITY == m_pCompresscfgAbility->struAbilityNode[nAbilityCount].dwAbilityType)
        {
            m_comboCompressionType.ResetContent();
            for (int i = 0; i < m_pCompresscfgAbility->struAbilityNode[nAbilityCount].dwNodeNum; i++)
            {
                m_comboCompressionType.AddString((char*)m_pCompresscfgAbility->struAbilityNode[nAbilityCount].struDescNode[i].byDescribe);
                m_comboCompressionType.SetItemData(i, m_pCompresscfgAbility->struAbilityNode[nAbilityCount].struDescNode[i].iValue);
            }
        }
    }
}


void CSubDlgChanCfg::SetResolutionCurSel(DWORD dwData)
{
    for (int i = 0; i < m_comboResolution.GetCount(); i++)
    {
        if (m_comboResolution.GetItemData(i) == dwData)
        {
            m_comboResolution.SetCurSel(i);
            return;
        }
    }
}

void CSubDlgChanCfg::SetBitrateCurSel(DWORD dwData)
{
    for (int i = 0; i < m_comboBitRate.GetCount(); i++)
    {
        if (m_comboBitRate.GetItemData(i) == dwData)
        {
            m_comboBitRate.SetCurSel(i);
            return;
        }
    }
}

void CSubDlgChanCfg::SetBitrateTypeCurSel(DWORD dwData)
{
    for (int i = 0; i < m_comboBitRateType.GetCount(); i++)
    {
        if (m_comboBitRateType.GetItemData(i) == dwData)
        {
            m_comboBitRateType.SetCurSel(i);
            return;
        }
    }
}

BOOL CSubDlgChanCfg::SetFrameCurSel(DWORD dwData)
{
    for (int i = 0; i < m_comboFrameRate.GetCount(); i++)
    {
        if (m_comboFrameRate.GetItemData(i) == dwData)
        {
            m_comboFrameRate.SetCurSel(i);
            return TRUE;
        }
    }
	return FALSE;
}

void CSubDlgChanCfg::SetStreamTypeCurSel(DWORD dwData)
{
    for (int i = 0; i < m_comboCompressionType.GetCount(); i++)
    {
        if (m_comboCompressionType.GetItemData(i) == dwData)
        {
            m_comboCompressionType.SetCurSel(i);
            return;
        }
    }
}

void CSubDlgChanCfg::OnBtnJpegCapture() 
{
	CDlgJpegCaptureCfg dlg;
    dlg.m_lUserID = m_lLoginID;
    dlg.m_lChannelNum = m_iChanCount;
	dlg.m_iChanShowNO = m_iChanShowNum;
    dlg.m_lChannel = m_iChanShowNum;
	dlg.m_iChanCount = m_iChanCount;
	dlg.m_dwDevIndex = m_iDeviceIndex;
    
    dlg.DoModal();
}

void CSubDlgChanCfg::OnBtnDiskQuota() 
{
    CDlgDiskQuota dlg;
    dlg.m_lServerID = m_lLoginID;
    dlg.m_iDevIndex = m_iDeviceIndex;
    dlg.m_lChannelNum = m_iChanCount;
    dlg. m_lChannel = m_iChanShowNum;
    dlg.DoModal();
}

void CSubDlgChanCfg::DoUpdateFrame()
{
	char szLan[128] = {0};
	BOOL bGetFirstFrame = FALSE;
	int iFirstFrame = 0;
	NET_DVR_COMPRESSION_LIMIT struCompressionLimit = {0};
	struCompressionLimit.dwSize = sizeof(struCompressionLimit);
	struCompressionLimit.dwChannel = m_iChanShowNum;
	struCompressionLimit.byCompressType = m_comboCompressionType.GetCurSel() + 1;
	if (struCompressionLimit.byCompressType == 3)
	{
		//����������������ѹ����������
		return;
	}
	//Only if the channel is IPC, COMPRESSION_LIMIT is usable.
	if (m_iChanShowNum > MAX_ANALOG_CHANNUM)
	{
		return;
	}

	memcpy(&(struCompressionLimit.struCurrentCfg), &(m_struCompressionCfg[m_iCurChanIndex]), sizeof(NET_DVR_COMPRESSIONCFG_V30));
	NET_DVR_COMPRESSIONCFG_ABILITY struCompresscfgAbility = {0};
	if(!NET_DVR_GetDeviceAbility(m_lLoginID, COMPRESSION_LIMIT, (char*)&struCompressionLimit, sizeof(struCompressionLimit), (char*)(&struCompresscfgAbility), sizeof(struCompresscfgAbility)))
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "COMPRESSION_LIMIT");
	}
	else
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "COMPRESSION_LIMIT");
		
		//update the framerate ability
		
		for (int nAbilityCount = 0; nAbilityCount < struCompresscfgAbility.dwAbilityNum; nAbilityCount++)
		{
			if (FRAME_ABILITY == struCompresscfgAbility.struAbilityNode[nAbilityCount].dwAbilityType)
			{
				m_comboFrameRate.ResetContent();
				for (int i = 0; i < struCompresscfgAbility.struAbilityNode[nAbilityCount].dwNodeNum; i++)
				{
					if (!bGetFirstFrame)
					{
						bGetFirstFrame = TRUE;
						iFirstFrame = struCompresscfgAbility.struAbilityNode[nAbilityCount].struDescNode[i].iValue;
					}
					m_comboFrameRate.AddString((char*)struCompresscfgAbility.struAbilityNode[nAbilityCount].struDescNode[i].byDescribe);
					m_comboFrameRate.SetItemData(i, struCompresscfgAbility.struAbilityNode[nAbilityCount].struDescNode[i].iValue);
				}
			}
		}
		SetFrameCurSel(iFirstFrame);
	}	
	UpdateData(FALSE);
}

void CSubDlgChanCfg::OnButtonLimitFrameUpdate() 
{
	OnBnClickedBtnCmpOk();
	DoUpdateFrame();
}

void CSubDlgChanCfg::OnButtonVideoInEffect() 
{
	CDlgRemoteVideoInput dlg;
    dlg.m_lUserID = m_lLoginID;
    dlg.m_dwDevIndex = m_iDeviceIndex;
    dlg. m_lChannel = m_iChanShowNum;
    dlg.DoModal();
}

void CSubDlgChanCfg::OnButtonConfigCameraType() 
{
	// TODO: Add your control notification handler code here
	CDlgAccessCameraCfg dlg;
    dlg.m_lUserID = m_lLoginID;
    dlg.m_dwDevIndex = m_iDeviceIndex;
    dlg.m_lChannel = m_iChanShowNum;
    dlg.DoModal();
}

void CSubDlgChanCfg::OnButtonInquiryTimeSpan() 
{
	CDialogRecordTimeSpan dlg;
    dlg.m_lServerID = m_lLoginID;
    dlg.m_iDevIndex = m_iDeviceIndex;
    dlg. m_lChannel = m_iChanShowNum;
    dlg.DoModal();	
}

void CSubDlgChanCfg::OnButtonUpdateIndex() 
{
	if(NET_DVR_UpdateRecordIndex(m_lLoginID, m_iChanShowNum))
	{
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_UpdateRecordIndex");
		AfxMessageBox("NET_DVR_UpdateRecordIndex succeed");
	}
	else
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_UpdateRecordIndex");
		CString cs;
		cs.Format("NET_DVR_UpdateRecordIndex failed!Error[%d]", NET_DVR_GetLastError());
		AfxMessageBox(cs);
	}	
}

void CSubDlgChanCfg::OnBtnVideoOutput() 
{
	// TODO: Add your control notification handler code here
	CDlgVideoOut dlg;
	dlg.DoModal();
}
void CSubDlgChanCfg::OnBtnWdEnable() 
{
	// TODO: Add your control notification handler code here
	
	CDlgWD1Enable dlg;
	dlg.m_lServerID = m_lLoginID;
    dlg.m_iDevIndex = m_iDeviceIndex;
    dlg. m_lChannel = m_iChanShowNum;
    dlg.DoModal();
	
}

void CSubDlgChanCfg::OnBtnVeidopackage() 
{
	// TODO: Add your control notification handler code here
	CDlgNetraRecordPackage  dlg ;
	dlg.m_lLoginID = m_lLoginID;
	dlg.m_lChannel = m_iChanShowNum;
	dlg.m_iDevIndex = m_iDeviceIndex ;
	dlg.DoModal();

	
}

void CSubDlgChanCfg::OnBtnVediopackage() 
{
	// TODO: Add your control notification handler code here
	CDlgNetraRecordPackage  dlg ;
	dlg.m_lLoginID = m_lLoginID;
	dlg.m_lChannel = m_iChanShowNum;
	dlg.m_iDevIndex = m_iDeviceIndex ;
	dlg.DoModal();

}
