// DlgCcdParam1.cpp : implementation file
/**********************************************************
FileName:    DlgCcdParam.cpp
Description: CCD Parameter Config    
Date:        2009/11/11
Note: 		 <global>struct, refer to GeneralDef.h, global variants and functions refer to ClientDemo.cpp   
Modification History:      
    <version> <time>         <desc>
    <1.0    > <2008/06/10>       <created>
***********************************************************/

#include "stdafx.h"
#include "ClientDemo.h"
#include "DlgCcdParam.h"
#include "DlgInfrareCfg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgCcdParam dialog

/*********************************************************
  Function:	CDlgCcdParam
  Desc:		Constructor
  Input:	pParent, parent window pointer
  Output:	none
  Return:	none
**********************************************************/
CDlgCcdParam::CDlgCcdParam(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgCcdParam::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgCcdParam)
	m_iBrightness = 0;
	m_iContrast = 0;
	m_iGain = 0;
	m_iSaturation = 0;
	m_iSharpness = 0;
	m_iExposureUserSet = 0;
	m_iVedioExposure = 0;
	m_iUserGain = 0;
	m_byNormalLevel = 0;
	m_bySpectralLevel = 0;
	m_byTemporalLevel = 0;
	m_byAutoCompInter = 0;
	m_bChkFogremoveEn = FALSE;
	m_bChkLightInhibitEn = FALSE;
	m_bChkIlluminationEn = FALSE;
	m_bChkSmartIREn = FALSE;
	m_byBGain = 0;
	m_byRGain = 0;
	m_byEndTimeHour = 0;
	m_byEndTimeMin = 0;
	m_byEndTimeSec = 0;
	m_iDeviceIndex = -1;
	m_dwBackLightX1 = 0;
	m_dwBackLightX2 = 0;
	m_dwBackLightY1 = 0;
	m_dwBackLightY2 = 0;
	m_byBeginTimeHour = 0;
	m_byBeginTimeMin = 0;
	m_byBeginTimeSec = 0;
	//}}AFX_DATA_INIT
	memset(&m_struDehaze, 0, sizeof(m_struDehaze));
}

/*********************************************************
  Function:	DoDataExchange
  Desc:		the map between control and variable
  Input:	pDX, CDataExchange,pass the data exchange object to the window CWnd::DoDataExchange
  Output:	none
  Return:	none
**********************************************************/
void CDlgCcdParam::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgCcdParam)
	DDX_Control(pDX, IDC_COMBO_LOCALOUTPUTCATE, m_comboLocalOutPutGate);
	DDX_Control(pDX, IDC_COMBO_DAYNIGHT_FILTER_TYPE, m_comboDayNightType);
	DDX_Control(pDX, IDC_COMBO_ALARM_TRIG_STATE, m_comboAlarmTrigMode);
	DDX_Control(pDX, IDC_COMBO_BACKLIGHT_MODE, m_comboBackLightMode);
	DDX_Control(pDX, IDC_COMBO_WHITEBALANCE_MODE, m_comboWhiteBalanceMode);
	DDX_Control(pDX, IDC_COMBO_LIGHT_INHIBIT_LEVEL, m_comboLightInhibitLevel);
	DDX_Control(pDX, IDC_COMBO_GRAY_LEVEL, m_comboGrayLevel);
	DDX_Control(pDX, IDC_COMBO_DIGITAL_ZOOM, m_comboDigitalZoom);
	DDX_Control(pDX, IDC_COMBO_PALETTE_MODE, m_comboPaletteMode);
	DDX_Control(pDX, IDC_COMBO_FOCUS_SPEED, m_comboFocusSpeed);
	DDX_Control(pDX, IDC_COMBO_FILTER_SWITCH, m_comboFilterSwitch);
	DDX_Control(pDX, IDC_COMBO_ENHANCE_MODE, m_comboEnhanceMode);
	DDX_Control(pDX, IDC_COMBO_DIMMERMODE, m_comboDimmerMode);
	DDX_Control(pDX, IDC_COMBO_INOUT_DOOR_MODE, m_comboInOutMode);
	DDX_Control(pDX, IDC_COMBO_NOISEMOVEMODE, m_comboNoiseMoveMode);
	DDX_Control(pDX, IDC_COMBO_IRISMODE, m_ctrlIrisMode);
	DDX_Text(pDX, IDC_EDIT_BRIGHTNESS, m_iBrightness);
	DDX_Text(pDX, IDC_EDIT_CONTRAST, m_iContrast);
	DDX_Text(pDX, IDC_EDIT_GAIN, m_iGain);
	DDX_Text(pDX, IDC_EDIT_SATURATION, m_iSaturation);
	DDX_Text(pDX, IDC_EDIT_SHARPNESS, m_iSharpness);
	DDX_Text(pDX, IDC_EDIT_EXPOSUREUSERSET, m_iExposureUserSet);
	DDX_Text(pDX, IDC_EDIT_VEDIOEXPOSURE, m_iVedioExposure);
	DDX_Text(pDX, IDC_EDIT_USERGAIN, m_iUserGain);
	DDX_Text(pDX, IDC_EDIT_NORMAILEVEL, m_byNormalLevel);
	DDX_Text(pDX, IDC_EDIT_SPECTRALLEVEL, m_bySpectralLevel);
	DDX_Text(pDX, IDC_EDIT_TEMPORALLEVEL, m_byTemporalLevel);
	DDX_Text(pDX, IDC_EDIT_AUTO_COMP_INTERVAL, m_byAutoCompInter);
	DDX_Check(pDX, IDC_CHK_FOGREMOVE_EN, m_bChkFogremoveEn);
	DDX_Check(pDX, IDC_CHK_LIGHT_INHIBIT_EN, m_bChkLightInhibitEn);
	DDX_Check(pDX, IDC_CHK_ILLUMINATION_EN, m_bChkIlluminationEn);
	DDX_Check(pDX, IDC_CHK_SMARTIR_ENABLE, m_bChkSmartIREn);
	DDX_Text(pDX, IDC_EDIT_B_GAIN, m_byBGain);
	DDX_Text(pDX, IDC_EDIT_R_GAIN, m_byRGain);
	DDX_Text(pDX, IDC_EDIT_END_TIME_HOUR1, m_byEndTimeHour);
	DDX_Text(pDX, IDC_EDIT_END_TIME_MIN, m_byEndTimeMin);
	DDX_Text(pDX, IDC_EDIT_END_TIME_SEC, m_byEndTimeSec);
	DDX_Text(pDX, IDC_EDIT_BACKLIGHT_X1, m_dwBackLightX1);
	DDX_Text(pDX, IDC_EDIT_BACKLIGHT_X2, m_dwBackLightX2);
	DDX_Text(pDX, IDC_EDIT_BACKLIGHT_Y1, m_dwBackLightY1);
	DDX_Text(pDX, IDC_EDIT_BACKLIGHT_Y2, m_dwBackLightY2);
	DDX_Text(pDX, IDC_EDIT_BEGIN_TIME_HOUR, m_byBeginTimeHour);
	DDX_Text(pDX, IDC_EDIT_BEGIN_TIME_MIN, m_byBeginTimeMin);
	DDX_Text(pDX, IDC_EDIT_BEGIN_TIME_SEC, m_byBeginTimeSec);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgCcdParam, CDialog)
	//{{AFX_MSG_MAP(CDlgCcdParam)
	ON_BN_CLICKED(IDC_BTN_GET, OnBtnGet)
	ON_BN_CLICKED(IDC_BTN_SET, OnBtnSet)
	ON_BN_CLICKED(IDC_BTN_EXIT, OnBtnExit)
	ON_BN_CLICKED(IDC_BTN_INFRARE_CFG, OnBtnInfrareCfg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgCcdParam message handlers
/*********************************************************
  Function:	OnBtnGet
  Desc:		CCD parameter get
  Input:	
  Output:	
  Return:	
**********************************************************/
void CDlgCcdParam::OnBtnGet() 
{
    DWORD dwReturn = 0;
    memset(&m_CcdParam, 0, sizeof(m_CcdParam));
    m_CcdParam.dwSize = sizeof(m_CcdParam);
    TRACE("ccdparamstruct size = %d", sizeof(m_CcdParam));
    if (!NET_DVR_GetDVRConfig(g_struDeviceInfo[m_iDeviceIndex].lLoginID, NET_DVR_GET_CCDPARAMCFG, -1, &m_CcdParam, sizeof(m_CcdParam), &dwReturn))
    {
		g_pMainDlg->AddLog(g_struDeviceInfo[m_iDeviceIndex].lLoginID, OPERATION_FAIL_T, "NET_DVR_GET_CCDPARAMCFG");
    }
	else
	{
        g_pMainDlg->AddLog(g_struDeviceInfo[m_iDeviceIndex].lLoginID, OPERATION_SUCC_T, "NET_DVR_GET_CCDPARAMCFG");
	}
	m_comboLocalOutPutGate.SetCurSel(m_CcdParam.byLocalOutputGate);

    m_iBrightness = m_CcdParam.struVideoEffect.byBrightnessLevel;
    m_iExposureUserSet = m_CcdParam.struExposure.dwVideoExposureSet;
    m_iVedioExposure = m_CcdParam.struExposure.dwVideoExposureSet;
    m_iContrast = m_CcdParam.struVideoEffect.byContrastLevel;
    m_iGain = m_CcdParam.struGain.byGainLevel;
	m_iUserGain = m_CcdParam.struGain.byGainUserSet;
    m_iSaturation = m_CcdParam.struVideoEffect.bySaturationLevel;
    m_iSharpness = m_CcdParam.struVideoEffect.bySharpnessLevel;
	m_bChkSmartIREn = m_CcdParam.struVideoEffect.byEnableFunc&0x01;
	m_bChkIlluminationEn = (m_CcdParam.struVideoEffect.byEnableFunc>>1)&0x01;
	m_bChkLightInhibitEn = (m_CcdParam.struVideoEffect.byEnableFunc>>2)&0x01;
	m_comboLightInhibitLevel.SetCurSel(m_CcdParam.struVideoEffect.byLightInhibitLevel-1);
	m_comboGrayLevel.SetCurSel(m_CcdParam.struVideoEffect.byGrayLevel);
	m_ctrlIrisMode.SetCurSel(m_CcdParam.byIrisMode);

	m_comboWhiteBalanceMode.SetCurSel(m_CcdParam.struWhiteBalance.byWhiteBalanceMode);
	m_byBGain = m_CcdParam.struWhiteBalance.byWhiteBalanceModeBGain;
	m_byRGain = m_CcdParam.struWhiteBalance.byWhiteBalanceModeRGain;

	m_comboNoiseMoveMode.SetCurSel(m_CcdParam.struNoiseRemove.byDigitalNoiseRemoveEnable);
	m_byNormalLevel = m_CcdParam.struNoiseRemove.byDigitalNoiseRemoveLevel;
	m_bySpectralLevel = m_CcdParam.struNoiseRemove.bySpectralLevel;
	m_byTemporalLevel = m_CcdParam.struNoiseRemove.byTemporalLevel;

	m_comboDigitalZoom.SetCurSel(m_CcdParam.byDigitalZoom);
	m_comboDimmerMode.SetCurSel(m_CcdParam.byDimmerMode);
	m_comboEnhanceMode.SetCurSel(m_CcdParam.byEnhancedMode);
	m_comboPaletteMode.SetCurSel(m_CcdParam.byPaletteMode);
	m_comboFilterSwitch.SetCurSel(m_CcdParam.byFilterSwitch);
	m_comboFocusSpeed.SetCurSel(m_CcdParam.byFocusSpeed);
	m_byAutoCompInter = m_CcdParam.byAutoCompensationInterval;

	m_comboInOutMode.SetCurSel(m_CcdParam.bySceneMode);
	
	m_comboDayNightType.SetCurSel(m_CcdParam.struDayNight.byDayNightFilterType);
	m_byBeginTimeHour = m_CcdParam.struDayNight.byBeginTime;
	m_byBeginTimeMin = m_CcdParam.struDayNight.byBeginTimeMin;
	m_byBeginTimeSec = m_CcdParam.struDayNight.byBeginTimeSec;
	m_byEndTimeHour = m_CcdParam.struDayNight.byEndTime;
	m_byEndTimeMin = m_CcdParam.struDayNight.byEndTimeMin;
	m_byEndTimeSec = m_CcdParam.struDayNight.byEndTimeSec;
	m_comboAlarmTrigMode.SetCurSel(m_CcdParam.struDayNight.byAlarmTrigState);

	m_comboBackLightMode.SetCurSel(m_CcdParam.struBackLight.byBacklightMode);
	m_dwBackLightX1 = m_CcdParam.struBackLight.dwPositionX1;
	m_dwBackLightX2 = m_CcdParam.struBackLight.dwPositionX2;
	m_dwBackLightY1 = m_CcdParam.struBackLight.dwPositionY1;
	m_dwBackLightY2 = m_CcdParam.struBackLight.dwPositionY2;

	if (!NET_DVR_GetDVRConfig(g_struDeviceInfo[m_iDeviceIndex].lLoginID, NET_DVR_GET_CAMERA_DEHAZE_CFG, 1, &m_struDehaze, sizeof(m_struDehaze), &dwReturn))
    {
		g_pMainDlg->AddLog(g_struDeviceInfo[m_iDeviceIndex].lLoginID, OPERATION_FAIL_T, "NET_DVR_GET_CAMERA_DEHAZE_CFG");
    }
	else
	{
        g_pMainDlg->AddLog(g_struDeviceInfo[m_iDeviceIndex].lLoginID, OPERATION_SUCC_T, "NET_DVR_GET_CAMERA_DEHAZE_CFG");
	}
	m_bChkFogremoveEn = m_struDehaze.byDehazeMode;
 
    UpdateData(FALSE);
}

/*********************************************************
  Function:	OnBtnSet
  Desc:		CCD parameter set
  Input:	
  Output:	
  Return:	
**********************************************************/
void CDlgCcdParam::OnBtnSet() 
{
    UpdateData(TRUE);
	if((m_iBrightness < 0) || (m_iBrightness >100) || (m_iContrast < 0) || (m_iContrast >100) ||  \
		(m_iSaturation < 0) || (m_iSaturation >100) || (m_iSharpness < 0) || (m_iSharpness >100) ||  \
		(m_iGain < 0) || (m_iGain >100) || (m_iUserGain < 0) || (m_iUserGain > 100))
	{
		return;
	}
    m_CcdParam.struVideoEffect.byBrightnessLevel = m_iBrightness;
    m_CcdParam.struVideoEffect.byContrastLevel = m_iContrast;
    m_CcdParam.struVideoEffect.bySaturationLevel = m_iSaturation;
    m_CcdParam.struVideoEffect.bySharpnessLevel = m_iSharpness;
	m_CcdParam.struVideoEffect.byEnableFunc = 0;
	m_CcdParam.struVideoEffect.byEnableFunc |= m_bChkSmartIREn;
	m_CcdParam.struVideoEffect.byEnableFunc |= (m_bChkIlluminationEn<<1);
	m_CcdParam.struVideoEffect.byEnableFunc |= (m_bChkLightInhibitEn<<2);
	m_CcdParam.struVideoEffect.byLightInhibitLevel = m_comboLightInhibitLevel.GetCurSel()+1;
	m_CcdParam.struVideoEffect.byGrayLevel = m_comboGrayLevel.GetCurSel();

    m_CcdParam.struExposure.dwExposureUserSet = m_iExposureUserSet;
    m_CcdParam.struExposure.dwVideoExposureSet = m_iVedioExposure;
    m_CcdParam.struGain.byGainLevel = m_iGain;
	m_CcdParam.struGain.byGainUserSet = m_iUserGain;
	m_CcdParam.byIrisMode = m_ctrlIrisMode.GetCurSel();
    m_CcdParam.dwSize = sizeof(m_CcdParam);

	m_CcdParam.struWhiteBalance.byWhiteBalanceMode = m_comboWhiteBalanceMode.GetCurSel();
	m_CcdParam.struWhiteBalance.byWhiteBalanceModeBGain = m_byBGain;
	m_CcdParam.struWhiteBalance.byWhiteBalanceModeRGain = m_byRGain;

	m_CcdParam.struNoiseRemove.byDigitalNoiseRemoveEnable = m_comboNoiseMoveMode.GetCurSel();
	m_CcdParam.struNoiseRemove.byDigitalNoiseRemoveLevel = m_byNormalLevel;
	m_CcdParam.struNoiseRemove.bySpectralLevel = m_bySpectralLevel;
	m_CcdParam.struNoiseRemove.byTemporalLevel = m_byTemporalLevel;

	m_CcdParam.byDigitalZoom = m_comboDigitalZoom.GetCurSel();
	m_CcdParam.byDimmerMode = m_comboDimmerMode.GetCurSel();
	m_CcdParam.byEnhancedMode = m_comboEnhanceMode.GetCurSel();
	m_CcdParam.byPaletteMode = m_comboPaletteMode.GetCurSel();
	m_CcdParam.byFilterSwitch = m_comboFilterSwitch.GetCurSel();
	m_CcdParam.byAutoCompensationInterval = m_byAutoCompInter;
	m_CcdParam.byFocusSpeed = m_comboFocusSpeed.GetCurSel();

	m_CcdParam.bySceneMode = m_comboInOutMode.GetCurSel();
	m_CcdParam.byLocalOutputGate = m_comboLocalOutPutGate.GetCurSel();
	m_CcdParam.struDayNight.byDayNightFilterType = m_comboDayNightType.GetCurSel();
	m_CcdParam.struDayNight.byBeginTime = m_byBeginTimeHour;
	m_CcdParam.struDayNight.byBeginTimeMin = m_byBeginTimeMin;
	m_CcdParam.struDayNight.byBeginTimeSec = m_byBeginTimeSec;
	m_CcdParam.struDayNight.byEndTime = m_byEndTimeHour;
	m_CcdParam.struDayNight.byEndTimeMin = m_byEndTimeMin;
	m_CcdParam.struDayNight.byEndTimeSec = m_byEndTimeSec;
	m_CcdParam.struDayNight.byAlarmTrigState = m_comboAlarmTrigMode.GetCurSel();

	m_CcdParam.struBackLight.byBacklightMode = m_comboBackLightMode.GetCurSel();
	m_CcdParam.struBackLight.dwPositionX1 = m_dwBackLightX1;
	m_CcdParam.struBackLight.dwPositionX2 = m_dwBackLightX2;
	m_CcdParam.struBackLight.dwPositionY1 = m_dwBackLightY1;
	m_CcdParam.struBackLight.dwPositionY2 = m_dwBackLightY2;

    if (!NET_DVR_SetDVRConfig(g_struDeviceInfo[m_iDeviceIndex].lLoginID, NET_DVR_SET_CCDPARAMCFG, -1, &m_CcdParam, sizeof(m_CcdParam)))
    {
		g_pMainDlg->AddLog(g_struDeviceInfo[m_iDeviceIndex].lLoginID, OPERATION_FAIL_T, "NET_DVR_SET_CCDPARAMCFG");
        return;
    }
	else
	{
		g_pMainDlg->AddLog(g_struDeviceInfo[m_iDeviceIndex].lLoginID, OPERATION_SUCC_T, "NET_DVR_SET_CCDPARAMCFG");
	}

	m_struDehaze.byDehazeMode = m_bChkFogremoveEn;
	if (!NET_DVR_SetDVRConfig(g_struDeviceInfo[m_iDeviceIndex].lLoginID, NET_DVR_SET_CAMERA_DEHAZE_CFG, 1, &m_struDehaze, sizeof(m_struDehaze)))
    {
		g_pMainDlg->AddLog(g_struDeviceInfo[m_iDeviceIndex].lLoginID, OPERATION_FAIL_T, "NET_DVR_SET_CAMERA_DEHAZE_CFG");
        return;
    }
	else
	{
		g_pMainDlg->AddLog(g_struDeviceInfo[m_iDeviceIndex].lLoginID, OPERATION_SUCC_T, "NET_DVR_SET_CAMERA_DEHAZE_CFG");
	}
}

/*********************************************************
  Function:	OnBtnExit
  Desc:		Exit fun
  Input:	
  Output:	
  Return:	
**********************************************************/
void CDlgCcdParam::OnBtnExit() 
{
    CDialog::OnCancel();	
}

/*********************************************************
  Function:	OnInitDialog
  Desc:		Initialize the dialog
  Input:	
  Output:	
  Return:	
**********************************************************/
BOOL CDlgCcdParam::OnInitDialog() 
{
	CDialog::OnInitDialog();
	char szLan[128] = {0};
	m_comboLocalOutPutGate.ResetContent();
	g_StringLanType(szLan, "本地输出关闭", "Local output off");
	m_comboLocalOutPutGate.InsertString(0, szLan);
    m_comboLocalOutPutGate.SetItemData(0, 0);
	
	g_StringLanType(szLan, "本地输出打开", "Local output on");
	m_comboLocalOutPutGate.InsertString(1, szLan);
    m_comboLocalOutPutGate.SetItemData(1, 1);

	g_StringLanType(szLan, "缩放输出", "Scaling output");
	m_comboLocalOutPutGate.InsertString(2, szLan);
    m_comboLocalOutPutGate.SetItemData(2, 11);

	g_StringLanType(szLan, "裁剪输出", "Cutting output");
	m_comboLocalOutPutGate.InsertString(3, szLan);
    m_comboLocalOutPutGate.SetItemData(3, 12);

	OnBtnGet();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgCcdParam::OnBtnInfrareCfg() 
{
	// TODO: Add your control notification handler code here
	CDlgInfrareCfg dlg;
	dlg.m_iDevIndex = m_iDeviceIndex;
	dlg.DoModal();
}
