/**********************************************************
FileName:    DlgUpgrade.cpp
Description: update dialogbox     
Date:        2008/05/17
Note: 		<Global>struct, macro refer to GeneralDef.h, global variants and API refer to ClientDemo.cpp   
Modification History:      
    <version> <time>         <desc>
    <1.0    > <2008/05/17>       <created>
***********************************************************/

#include "stdafx.h"
#include "ClientDemo.h"
#include "DlgUpgrade.h"
#include ".\dlgupgrade.h"


// CDlgUpgrade dialog
/*********************************************************
  Function:	CDlgUpgrade
  Desc:		Constructor
  Input:	
  Output:	
  Return:	
**********************************************************/
IMPLEMENT_DYNAMIC(CDlgUpgrade, CDialog)
CDlgUpgrade::CDlgUpgrade(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgUpgrade::IDD, pParent)
	, m_csUpgradeFile(_T(""))
	, m_csUpgradeStat(_T(""))
	, m_lUpgradeHandle(0)
	, m_lServerID(-1)
	, m_lpUpgradeTimer(NULL)
	, m_bUpgrade(FALSE)
{
}

/*********************************************************
  Function:	~CDlgUpgrade
  Desc:		destructor
  Input:	
  Output:	
  Return:	
**********************************************************/
CDlgUpgrade::~CDlgUpgrade()
{
}

/*********************************************************
Function:	DoDataExchange
Desc:		the map between control and variable
Input:	
Output:	
Return:	
**********************************************************/
void CDlgUpgrade::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgUpgrade)
	DDX_Control(pDX, IDC_PROGRESS_STEP, m_progressSub);
	DDX_Control(pDX, IDC_COMBO_CHAN, m_comboChan);
	DDX_Control(pDX, IDC_COMBO_UPGRADE_TYPE, m_comboUpgradeType);
	DDX_Control(pDX, IDC_COMBO_ENVIRONMENT, m_comboEnvironment);
	DDX_Control(pDX, IDC_PROGRESS_UPGRADE, m_progressUpgrade);
	DDX_Text(pDX, IDC_EDIT_UPGRADE_FILE, m_csUpgradeFile);
	DDX_Text(pDX, IDC_STATIC_UPGRADE, m_csUpgradeStat);
	DDX_Text(pDX, IDC_STATIC_STEP, m_csUpgradeStep);
	//}}AFX_DATA_MAP
	
}


/*********************************************************
Function:	BEGIN_MESSAGE_MAP
Desc:		the map between control and function
Input:	
Output:	
Return:	
**********************************************************/
BEGIN_MESSAGE_MAP(CDlgUpgrade, CDialog)
	//{{AFX_MSG_MAP(CDlgUpgrade)	
	ON_BN_CLICKED(IDC_BTN_BROWSE_FILE, OnBnClickedBtnBrowseFile)
	ON_BN_CLICKED(IDC_BTN_UPGRADE, OnBnClickedBtnUpgrade)
	ON_BN_CLICKED(IDC_BTN_UPGRADE_EXIT, OnBnClickedBtnUpgradeExit)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BTN_SET_ENVIRO, OnBtnSetEnviro)
	ON_CBN_SELCHANGE(IDC_COMBO_UPGRADE_TYPE, OnSelchangeComboUpgradeType)
	//}}AFX_MSG_MAP
	
END_MESSAGE_MAP()


// CDlgUpgrade message handlers
/*********************************************************
Function:	OnInitDialog
Desc:		Initialize the dialog
Input:	
Output:	
Return:	
**********************************************************/
BOOL CDlgUpgrade::OnInitDialog() 
{
	CDialog::OnInitDialog();

	// TODO: Add extra initialization here
	m_csUpgradeFile.Format("c:\\digicap");
	UpdateData(FALSE);
	m_bUpgrade = FALSE;
	m_progressUpgrade.SetRange(0,100);
	m_progressUpgrade.SetPos(0);
	m_progressUpgrade.ShowWindow(SW_HIDE);
	m_comboEnvironment.SetCurSel(0);

    m_comboUpgradeType.ResetContent();
    m_comboUpgradeType.AddString("DVR");
    m_comboUpgradeType.AddString("Adapter");
    m_comboUpgradeType.AddString("Vca lib");
    m_comboUpgradeType.SetCurSel(0);

    m_comboChan.ResetContent();
    char szLan[128] = {0};
    for (int i = 0; i < g_struDeviceInfo[m_iDeviceIndex].iDeviceChanNum; i++)
    {
        sprintf(szLan, "Chan %d", i + 1);
        m_comboChan.AddString(szLan);
    }
     

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

/*********************************************************
  Function:	OnBnClickedBtnBrowseFile
  Desc:		browse update firmware
  Input:	
  Output:	
  Return:	
**********************************************************/
void CDlgUpgrade::OnBnClickedBtnBrowseFile()
{
	static char szFilter[]="All File(*.*)|*.*||";
	CFileDialog dlg(TRUE,"*.*","digicap",OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,
		szFilter);
	if (dlg.DoModal()==IDOK)
	{
		m_csUpgradeFile = dlg.GetPathName();
		UpdateData(FALSE);
	}	
}

/*********************************************************
  Function:	start update
  Input:	
  Output:	
  Return:	
**********************************************************/
void CDlgUpgrade::OnBnClickedBtnUpgrade()
{
	char m_szFileName[MAX_PATH];

	UpdateData(TRUE);
	strcpy(m_szFileName,m_csUpgradeFile);
	CFile cFile;
	char szLan[128] = {0};
	if (!cFile.Open(m_szFileName,NULL))
	{
		g_StringLanType(szLan, "打开文件失败或无此文件", "Open file failed or no this file");
		AfxMessageBox(szLan);
		return;
	}
	DWORD dwFileSize = (DWORD)cFile.GetLength();
	if (dwFileSize == 0)
	{
		g_StringLanType(szLan, "升级文件为空", "Upgrade file is empty");
		AfxMessageBox(szLan);
	}
	cFile.Close();
    
    if (m_comboUpgradeType.GetCurSel() == 0) // DVR upgrade 
    {
	m_lUpgradeHandle = NET_DVR_Upgrade(m_lServerID, m_szFileName);
    }
    else if (m_comboUpgradeType.GetCurSel() == 1) // adapter upgrade
    {
        m_lUpgradeHandle = NET_DVR_AdapterUpgrade(m_lServerID, m_szFileName);
    }
    else if (m_comboUpgradeType.GetCurSel() == 2) // vca lib upgrade
    {
        m_lUpgradeHandle = NET_DVR_VcalibUpgrade(m_lServerID, m_comboChan.GetCurSel() + 1, m_szFileName);
    }
	if (m_lUpgradeHandle < 0)
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_Upgrade");
		g_StringLanType(szLan, "升级失败", "Upgrade failed");
		AfxMessageBox(szLan);
	}
	else
	{
		GetDlgItem(IDC_STATIC_UPGRADE)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_BTN_UPGRADE)->EnableWindow(FALSE);
		GetDlgItem(IDC_BTN_UPGRADE_EXIT)->EnableWindow(FALSE);
		GetDlgItem(IDC_BTN_BROWSE_FILE)->EnableWindow(FALSE);
		m_progressUpgrade.SetPos(0);
		m_progressUpgrade.ShowWindow(SW_SHOW);
		g_StringLanType(szLan, "状态：正在升级服务器，请等待......", "Status: Server is upgrading, please wait......");
		m_csUpgradeStat.Format(szLan);
		m_bUpgrade = TRUE;
		m_lpUpgradeTimer = SetTimer(UPGRADE_TIMER, 500, NULL);
		UpdateData(FALSE);
	}	
}

/*********************************************************
  Function:	OnBnClickedBtnUpgradeExit
  Desc:		exit update
  Input:	
  Output:	
  Return:	
**********************************************************/
void CDlgUpgrade::OnBnClickedBtnUpgradeExit()
{
	if (m_lpUpgradeTimer)
	{
		KillTimer(UPGRADE_TIMER);
	}
	CDialog::OnCancel();
}

/*********************************************************
  Function:	OnTimer
  Desc:		refresh update status timer
  Input:	
  Output:	
  Return:	
**********************************************************/
void CDlgUpgrade::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	char szLan[128] = {0};
	if (nIDEvent == UPGRADE_TIMER)
	{
		if (m_bUpgrade)
		{
			int UpgradeStatic = NET_DVR_GetUpgradeState(m_lUpgradeHandle);
			DWORD dwError = NET_DVR_GetLastError();
			int iPos = NET_DVR_GetUpgradeProgress(m_lUpgradeHandle);
			
			LONG iSubProgress = -1;
			int iStep = NET_DVR_GetUpgradeStep(m_lUpgradeHandle, &iSubProgress);

			if(iStep != -1)
			{
				GetDlgItem(IDC_STATIC_STEP)->ShowWindow(SW_SHOW);
				GetDlgItem(IDC_PROGRESS_STEP)->ShowWindow(SW_SHOW);	
				m_progressSub.SetPos(iSubProgress);
				switch(iStep)
				{
				case STEP_RECV_DATA:
					g_StringLanType(szLan, "正在读取升级文件", "Receving upgrade file");
					m_csUpgradeStep.Format("%s", szLan);
					break;
				case STEP_UPGRADE:
					g_StringLanType(szLan, "正在升级系统", "Upgrading system");
					m_csUpgradeStep.Format("%s", szLan);
					break;
				case STEP_BACKUP:
					g_StringLanType(szLan, "正在备份系统", "Backuping system");
					m_csUpgradeStep.Format("%s", szLan);
					break;
				case STEP_SEARCH:
					g_StringLanType(szLan, "正在搜索升级文件", "Searching  upgrade file");
					m_csUpgradeStep.Format("%s", szLan);
					break;
				default:
					g_StringLanType(szLan, "未知阶段", "Unknow step");
					m_csUpgradeStep.Format("%s:%d", szLan, iStep);
					break;
				}
			}

			g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GetUpgradeProgress= [%d]",iPos);
			if (iPos >0)
			{
				m_progressUpgrade.SetPos(iPos);
			}
			if (UpgradeStatic == 2)
			{
				g_StringLanType(szLan, "状态：正在升级设备，请等待......", "Status: Device is upgrading, please wait......");
				m_csUpgradeStat.Format(szLan);
				UpdateData(FALSE);
			}
			else
			{
				switch (UpgradeStatic)
				{
				case -1:
					g_StringLanType(szLan, "升级失败", "Upgrade failed");
					AfxMessageBox(szLan);			
					break;
				case 1:
					g_StringLanType(szLan, "状态：升级设备成功", "Status:upgrade successfully");
					m_csUpgradeStat.Format(szLan);
					m_progressUpgrade.SetPos(100);
					break;			
				case 3:
					g_StringLanType(szLan, "状态：升级设备失败", "Status:upgrade failed");
					m_csUpgradeStat.Format(szLan);		
					break;
				case 4:
					g_StringLanType(szLan, "状态：从设备接收数据错误, 状态未知", "Status:get data with probrem from device, status unknown");
					m_csUpgradeStat.Format(szLan);					
					break;
				case 5:
					g_StringLanType(szLan, "状态：升级文件语言版本不匹配", "Status:Upgrade file language mismatch");
					m_csUpgradeStat.Format(szLan);				
					break;
				default: 
					break;
				}
				UpdateData(FALSE);
				m_bUpgrade = FALSE;
				GetDlgItem(IDC_BTN_UPGRADE)->EnableWindow(TRUE);
				GetDlgItem(IDC_BTN_UPGRADE_EXIT)->EnableWindow(TRUE);
				GetDlgItem(IDC_BTN_BROWSE_FILE)->EnableWindow(TRUE);
				if (!NET_DVR_CloseUpgradeHandle(m_lUpgradeHandle))
				{
					g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_CloseUpgradeHandle");
				}
				GetDlgItem(IDC_STATIC_STEP)->ShowWindow(SW_HIDE);
				GetDlgItem(IDC_PROGRESS_STEP)->ShowWindow(SW_HIDE);	
				m_lUpgradeHandle = -1;
			}
		}		
	}
	CDialog::OnTimer(nIDEvent);
}

/*********************************************************
  Function:	OnBtnSetEnviro
  Desc:		set the environment of the network
  Input:	none
  Output:	none
  Return:	none
**********************************************************/
void CDlgUpgrade::OnBtnSetEnviro() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	char szLan[128] = {0};

	if (!NET_DVR_SetNetworkEnvironment(m_comboEnvironment.GetCurSel()))
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SetNetworkEnvironment[%d]", m_comboEnvironment.GetCurSel());
		g_StringLanType(szLan, "设置网络环境", "Set up the network environment!");
		AfxMessageBox(szLan);
	}
	else
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SetNetworkEnvironment[%d]", m_comboEnvironment.GetCurSel());
	}
	
}

void CDlgUpgrade::OnSelchangeComboUpgradeType() 
{
    if (m_comboUpgradeType.GetCurSel() == 2)
    {
        GetDlgItem(IDC_STATIC_CHAN)->ShowWindow(SW_SHOW);
        m_comboChan.ShowWindow(SW_SHOW);
    }
    else
    {
        GetDlgItem(IDC_STATIC_CHAN)->ShowWindow(SW_HIDE);
        m_comboChan.ShowWindow(SW_HIDE);
    }
}
