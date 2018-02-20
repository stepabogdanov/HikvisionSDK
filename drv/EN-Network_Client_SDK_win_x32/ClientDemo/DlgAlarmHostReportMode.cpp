// DlgAlarmHostReportMode.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgAlarmHostReportMode.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgAlarmHostReportMode dialog


CDlgAlarmHostReportMode::CDlgAlarmHostReportMode(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgAlarmHostReportMode::IDD, pParent)
	, m_iDeviceIndex(-1)
	, m_lUserID(-1)
	, m_pStruReportCenter(NULL)
	, m_iCenterNum(-1)
	, m_iChanNum(-1)
{
	//{{AFX_DATA_INIT(CDlgAlarmHostReportMode)
	m_bValid = FALSE;
	m_bCheckSend1 = FALSE;
	m_bCheckSend2 = FALSE;
	m_bCheckSend3 = FALSE;
	m_bCheckSend4 = FALSE;
	m_bCheckSend5 = FALSE;
	m_bCheckSend6 = FALSE;
	//}}AFX_DATA_INIT
	m_pStruReportCenter = new NET_DVR_ALARMHOST_REPORTCENTER_CFG[MAX_CENTERGROUP_NUM];
}

CDlgAlarmHostReportMode::~CDlgAlarmHostReportMode()
{
	delete[] m_pStruReportCenter;
	m_pStruReportCenter = NULL;
}

void CDlgAlarmHostReportMode::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgAlarmHostReportMode)
	DDX_Control(pDX, IDC_COMBO_CENTER, m_cmCenter);
	DDX_Control(pDX, IDC_COMBO_DATATYPE, m_cmDataType);
	DDX_Check(pDX, IDC_CHECK_VALID, m_bValid);
	DDX_Check(pDX, IDC_CHECK_SEND1, m_bCheckSend1);
	DDX_Check(pDX, IDC_CHECK_SEND2, m_bCheckSend2);
	DDX_Check(pDX, IDC_CHECK_SEND3, m_bCheckSend3);
	DDX_Check(pDX, IDC_CHECK_SEND4, m_bCheckSend4);
	DDX_Check(pDX, IDC_CHECK_SEND5, m_bCheckSend5);
	DDX_Check(pDX, IDC_CHECK_SEND6, m_bCheckSend6);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgAlarmHostReportMode, CDialog)
	//{{AFX_MSG_MAP(CDlgAlarmHostReportMode)
	ON_CBN_SELCHANGE(IDC_COMBO_CENTER, OnSelchangeComboCenter)
	ON_BN_CLICKED(IDC_BTN_SURE, OnBtnSure)
	ON_BN_CLICKED(IDC_BTN_GET, OnBtnGet)
	ON_BN_CLICKED(IDC_BTN_SET, OnBtnSet)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgAlarmHostReportMode message handlers

BOOL CDlgAlarmHostReportMode::OnInitDialog() 
{
	CDialog::OnInitDialog();
	InitComboBox();
	CString csStr;
	// TODO: Add extra initialization here
	m_iDeviceIndex = g_pMainDlg->GetCurDeviceIndex();
	m_lUserID = g_struDeviceInfo[m_iDeviceIndex].lLoginID;
	NET_DVR_ALARMHOST_ABILITY struAbility = {0};
	struAbility.dwSize = sizeof(NET_DVR_ALARMHOST_ABILITY);
	if(!NET_DVR_GetDeviceAbility(m_lUserID, ALARMHOST_ABILITY, NULL, 0, (char*)&struAbility, sizeof(NET_DVR_ALARMHOST_ABILITY)))
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GetDeviceAbility FAILED");
		m_iCenterNum = 0;
	}
	else
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GetDeviceAbility SUCC");
		m_iCenterNum = struAbility.byCenterGroupNum;
	}
	int i=0;
	m_cmCenter.ResetContent();
	for (i=0; i<m_iCenterNum; i++)
	{
		g_StringLanType(szLan, "中心", "Center");
		csStr.Format("%s%d", szLan, i+1);
		m_cmCenter.AddString(csStr);
	}

	//初始化通道
	m_iChanNum = m_iCenterNum * 4;
	for (i=0; i<m_iChanNum; i++)
	{
		g_StringLanType(szLan, "关", "Close");
		csStr.Format(szLan);
		((CComboBox*)GetDlgItem(g_struMode[i]))->AddString(csStr);
		csStr.Format("T1");
		((CComboBox*)GetDlgItem(g_struMode[i]))->AddString(csStr);
		csStr.Format("T2");
		((CComboBox*)GetDlgItem(g_struMode[i]))->AddString(csStr);
		csStr.Format("N1");
		((CComboBox*)GetDlgItem(g_struMode[i]))->AddString(csStr);
		csStr.Format("N2");
		((CComboBox*)GetDlgItem(g_struMode[i]))->AddString(csStr);
		csStr.Format("G1");
		((CComboBox*)GetDlgItem(g_struMode[i]))->AddString(csStr);
		csStr.Format("G2");
		((CComboBox*)GetDlgItem(g_struMode[i]))->AddString(csStr);
	}
	for (i=0; i<m_iChanNum; i++)
	{
		((CComboBox*)GetDlgItem(g_struMode[i]))->SetCurSel(0);
	}
	UpdateData(FALSE);
	OnBtnGet();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE

}

void CDlgAlarmHostReportMode::InitComboBox()
{
	char szLan[128] = {0};
	m_cmDataType.ResetContent();
	g_StringLanType(szLan, "报警数据", "ALARM DATA");
	m_cmDataType.AddString(szLan);
	g_StringLanType(szLan, "非报警数据", "NORAML DATA");
	m_cmDataType.AddString(szLan);
	g_StringLanType(szLan, "所有数据", "ALL DATA");
	m_cmDataType.AddString(szLan);
	UpdateData(FALSE);
} 

void CDlgAlarmHostReportMode::OnSelchangeComboCenter() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	DWORD dwCenterIndex = m_cmCenter.GetCurSel();
	if (dwCenterIndex > m_iCenterNum)
	{
		dwCenterIndex = 0;
	}
	EnableCheckWindow(dwCenterIndex);
	NET_DVR_ALARMHOST_REPORTCENTER_CFG struReportMode = {0};
	memcpy(&struReportMode, &m_pStruReportCenter[dwCenterIndex], sizeof(struReportMode));
	m_cmDataType.SetCurSel(struReportMode.byDataType - 1);
	m_bValid = struReportMode.byValid;
	m_bCheckSend1 = struReportMode.byDealFailCenter[0];
	m_bCheckSend2 = struReportMode.byDealFailCenter[1];
	m_bCheckSend3 = struReportMode.byDealFailCenter[2];
	m_bCheckSend4 = struReportMode.byDealFailCenter[3];
	m_bCheckSend5 = struReportMode.byDealFailCenter[4];
	m_bCheckSend6 = struReportMode.byDealFailCenter[5];
	UpdateData(FALSE);
}

void CDlgAlarmHostReportMode::EnableCheckWindow(DWORD dwCenterIndex) 
{
	int i = 0;
	for (i=0; i<m_iCenterNum; i++)
	{
		GetDlgItem(g_struCheckSend[i])->EnableWindow(TRUE);
	}
	GetDlgItem(g_struCheckSend[dwCenterIndex])->EnableWindow(FALSE);
}

void CDlgAlarmHostReportMode::OnBtnSure() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	DWORD dwCenterIndex = m_cmCenter.GetCurSel();
	NET_DVR_ALARMHOST_REPORTCENTER_CFG struReportMode = {0};
	struReportMode.dwSize = sizeof(struReportMode);
	struReportMode.byDataType = m_cmDataType.GetCurSel() + 1;
	struReportMode.byValid = m_bValid;
	struReportMode.byDealFailCenter[0] = m_bCheckSend1;
	struReportMode.byDealFailCenter[1] = m_bCheckSend2;
	struReportMode.byDealFailCenter[2] = m_bCheckSend3;
	struReportMode.byDealFailCenter[3] = m_bCheckSend4;
	struReportMode.byDealFailCenter[4] = m_bCheckSend5;
	struReportMode.byDealFailCenter[5] = m_bCheckSend6;
	memcpy(&m_pStruReportCenter[dwCenterIndex], &struReportMode, sizeof(struReportMode));
}

void CDlgAlarmHostReportMode::OnBtnGet() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	DWORD dwBufLen = m_iCenterNum * sizeof(NET_DVR_ALARMHOST_REPORTCENTER_CFG);
	if (!NET_DVR_AlarmHostGetReportMode(m_lUserID, m_pStruReportCenter, dwBufLen))
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_AlarmHostGetReportMode FAILED");
		g_StringLanType(szLan, "获取上传方式失败", "NET_DVR_AlarmHostGetReportMode FAILED");
		MessageBox(szLan);
	}
	else
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_AlarmHostGetReportMode SUCC");
	}
	SetReportMode();
	m_cmCenter.SetCurSel(0);
	UpdateData(FALSE);
	OnSelchangeComboCenter();
}

void CDlgAlarmHostReportMode::SetReportMode()
{
	int iCenterIndex = 0;
	int iStartIndex = 0;
	int i = 0;
	int iReportMode = 0;//1-T1 2-T2
	for (iCenterIndex=0; iCenterIndex<m_iCenterNum; iCenterIndex++)
	{
		iStartIndex = 4*iCenterIndex;
		for (i = 0; i<MAX_REPORTCHAN_NUM; i++)
		{
			iReportMode = m_pStruReportCenter[iCenterIndex].byChanAlarmMode[i];
			//1-6为有效值，其他值都归为0（关）
			if (iReportMode>=1 && iReportMode<=6)
			{
				((CComboBox*)GetDlgItem(g_struMode[i+iStartIndex]))->SetCurSel(iReportMode);
			}
			else
			{
				((CComboBox*)GetDlgItem(g_struMode[i+iStartIndex]))->SetCurSel(0);
			}
		}
	}
	UpdateData(FALSE);
}
void CDlgAlarmHostReportMode::OnBtnSet() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	OnBtnSure();
	int iCenterIndex = 0;
	int iStartIndex = 0;
	int i = 0;
	int iReportMode = 0;//1-T1 2-T2
	for (iCenterIndex=0; iCenterIndex<m_iCenterNum; iCenterIndex++)
	{
		iStartIndex = 4*iCenterIndex;
		for (i = 0; i<4; i++)
		{
			iReportMode = ((CComboBox*)GetDlgItem(g_struMode[i+iStartIndex]))->GetCurSel();
			//1-6为有效值，其他值都归为0（关）
			if (iReportMode>=1 && iReportMode<=6)
			{
				m_pStruReportCenter[iCenterIndex].byChanAlarmMode[i] = iReportMode;
			}
			else
			{
				m_pStruReportCenter[iCenterIndex].byChanAlarmMode[i] = 0;
			}
		}
	}
 	if (!NET_DVR_AlarmHostSetReportMode(m_lUserID, m_iCenterNum, m_pStruReportCenter, m_iCenterNum*sizeof(NET_DVR_ALARMHOST_REPORTCENTER_CFG)))
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_AlarmHostSetReportMode FAILED");
		g_StringLanType(szLan, "设置上传方式失败", "NET_DVR_AlarmHostSetReportMode FAILED");
		MessageBox(szLan);
	}
	else
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_AlarmHostSetReportMode SUCC");
	}
}
