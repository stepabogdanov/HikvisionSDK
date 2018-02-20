// DlgSafetyCabin.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgSafetyCabin.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgSafetyCabin dialog


CDlgSafetyCabin::CDlgSafetyCabin(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgSafetyCabin::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgSafetyCabin)
	m_wCurtainDelay = 0;
	m_wCurtainResponse = 0;
	m_byDevUseTimeOut = 0;
	m_bySensitivity = 0;
	//}}AFX_DATA_INIT
}


void CDlgSafetyCabin::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgSafetyCabin)
	DDX_Control(pDX, IDC_COMBO_WORK_MODE, m_comboWorkMode);
	DDX_Control(pDX, IDC_COMBO_SENSOR_TYPE, m_comboSensorType);
	DDX_Text(pDX, IDC_EDIT_CURTAIN_DELAY, m_wCurtainDelay);
	DDX_Text(pDX, IDC_EDIT_CURTAIN_RESPONSE, m_wCurtainResponse);
	DDV_MinMaxInt(pDX, m_wCurtainResponse, 0, 300);
	DDX_Text(pDX, IDC_EDIT_DEVUSE_TIMEOUT, m_byDevUseTimeOut);
	DDV_MinMaxByte(pDX, m_byDevUseTimeOut, 0, 30);
	DDX_Text(pDX, IDC_EDIT_SENSITIVITY, m_bySensitivity);
	DDV_MinMaxByte(pDX, m_bySensitivity, 0, 100);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgSafetyCabin, CDialog)
	//{{AFX_MSG_MAP(CDlgSafetyCabin)
	ON_BN_CLICKED(IDC_BTN_SET, OnBtnSet)
	ON_BN_CLICKED(IDC_BTN_GET, OnBtnGet)
	ON_BN_CLICKED(IDC_BTN_EXIT, OnBtnExit)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgSafetyCabin message handlers

BOOL CDlgSafetyCabin::OnInitDialog() 
{
	CDialog::OnInitDialog();
	m_iDeviceIndex = g_pMainDlg->GetCurDeviceIndex();
	char szLan[128] = {0};
	// TODO: Add extra initialization here
	if (!NET_DVR_GetDeviceAbility(m_lUserID, ALARMHOST_ABILITY, NULL, 0, (char*)&m_struAblity, sizeof(m_struAblity)))
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "ALARMHOST_ABILITY");
		g_StringLanType(szLan, "��ȡ������ʧ��", "Get ability fail");
	}
	else
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "ALARMHOST_ABILITY");
	}


	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgSafetyCabin::OnBtnSet() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	char szLan[128] = {0};
	m_struWorkMode.dwSize = sizeof(NET_DVR_SAFETYCABIN_WORK_MODE);
	m_struWorkMode.byWorkMode = m_comboWorkMode.GetCurSel();

	m_struPersonSignalCfg.dwSize = sizeof(NET_DVR_SAFETYCABIN_PERSON_SIGNAL_CFG);
	m_struPersonSignalCfg.bySensorType = m_comboSensorType.GetCurSel();
	m_struPersonSignalCfg.bySensitivity = m_bySensitivity;
	m_struPersonSignalCfg.byDevUseTimeout = m_byDevUseTimeOut;
	m_struPersonSignalCfg.wCurtainDelayTime = m_wCurtainDelay;
	m_struPersonSignalCfg.wCurtainResponseTime = m_wCurtainResponse;

	if (!NET_DVR_SetDVRConfig(m_lUserID, NET_DVR_SET_SAFETYCABIN_WORK_MODE, 0, &m_struWorkMode, sizeof(m_struWorkMode)))
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_SAFETYCABIN_WORK_MODE");
		g_StringLanType(szLan, "���÷����չ���ģʽʧ��", "Set safety cabin work mode fail");
		AfxMessageBox(szLan);
	}
	else
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_SAFETYCABIN_WORK_MODE");
	}

	if (!NET_DVR_SetDVRConfig(m_lUserID, NET_DVR_SET_SAFETYCABIN_PERSON_SIGNAL_CFG, 0, &m_struPersonSignalCfg, sizeof(m_struPersonSignalCfg)))
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_SAFETYCABIN_PERSON_SIGNAL_CFG");
		g_StringLanType(szLan, "�������ź�̽�����ʧ��", "Set person signal config fail");
		AfxMessageBox(szLan);
	}
	else
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_SAFETYCABIN_PERSON_SIGNAL_CFG");
	}
}

void CDlgSafetyCabin::OnBtnGet() 
{
	// TODO: Add your control notification handler code here
	char szLan[128] = {0};
	DWORD dwReturned = 0;
	if (!NET_DVR_GetDVRConfig(m_lUserID, NET_DVR_GET_SAFETYCABIN_WORK_MODE, 0, &m_struWorkMode, sizeof(m_struWorkMode), &dwReturned))
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_SAFETYCABIN_WORK_MODE");
		g_StringLanType(szLan, "��ȡ�����չ���ģʽʧ��", "Get safety cabin work mode fail");
		AfxMessageBox(szLan);
		return;
	}
	else
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_SAFETYCABIN_WORK_MODE");
	}
	
	if (!NET_DVR_GetDVRConfig(m_lUserID, NET_DVR_GET_SAFETYCABIN_PERSON_SIGNAL_CFG, 0, &m_struPersonSignalCfg, sizeof(m_struPersonSignalCfg), &dwReturned))
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_SAFETYCABIN_PERSON_SIGNAL_CFG");
		g_StringLanType(szLan, "��ȡ���ź�̽�����ʧ��", "Get person signal config fail");
		AfxMessageBox(szLan);
		return;
	}
	else
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_SAFETYCABIN_PERSON_SIGNAL_CFG");
	}

	m_comboWorkMode.SetCurSel(m_struWorkMode.byWorkMode);

	m_comboSensorType.SetCurSel(m_struPersonSignalCfg.bySensorType);
	m_bySensitivity = m_struPersonSignalCfg.bySensitivity;
	m_byDevUseTimeOut = m_struPersonSignalCfg.byDevUseTimeout;
	m_wCurtainDelay = m_struPersonSignalCfg.wCurtainDelayTime;
	m_wCurtainResponse = m_struPersonSignalCfg.wCurtainResponseTime;

	UpdateData(FALSE);
}

void CDlgSafetyCabin::OnBtnExit() 
{
	// TODO: Add your control notification handler code here
	CDialog::OnCancel();
}
