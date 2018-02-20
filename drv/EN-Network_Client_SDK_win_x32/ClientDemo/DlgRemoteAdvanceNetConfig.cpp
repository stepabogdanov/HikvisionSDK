/**********************************************************
FileName:    DlgRemoteAdvanceNetConfig.cpp
Description: Advanced Network Config     
Date:        2008/05/29
Note: 		<global>struct, pleasse refer to GeneralDef.h for macro definition,  and ClientDemo.cpp for API and global variants   
Modification History:      
    <version> <time>         <desc>
    <1.0    > <2008/05/29>       <created>
***********************************************************/

#include "stdafx.h"
#include "ClientDemo.h"
#include "DlgRemoteAdvanceNetConfig.h"
#include "DlgRemoteEmailAddReceiver.h"
#include ".\dlgremoteadvancenetconfig.h"
#include "DlgSnmpCfg.h"

// CDlgRemoteAdvanceNetConfig dialog
extern BOOL CheckEmailAddress(CString csEmailAddr);
CDlgRemoteAdvanceNetConfig *g_pRemoteAdvaceNetConfig = NULL;

/*********************************************************
Function:	CDlgRemoteAdvanceNetConfig
Desc:		Constructor
Input:	
Output:	
Return:	
**********************************************************/
IMPLEMENT_DYNAMIC(CDlgRemoteAdvanceNetConfig, CDialog)
CDlgRemoteAdvanceNetConfig::CDlgRemoteAdvanceNetConfig(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgRemoteAdvanceNetConfig::IDD, pParent)
	, m_csSenderName(_T(""))
	, m_csSenderAddr(_T(""))
	, m_csAccountPwd(_T(""))
	, m_csAccountPwdConfirm(_T(""))
	, m_csAccount(_T(""))
	, m_bChkAuthen(FALSE)
	, m_bChkAttach(FALSE)
	, m_csDnsIP(_T(""))
	, m_bChkNtp(FALSE)
	, m_csNtpAddr(_T(""))
	, m_iNtpInterval(0)
	, m_iNTPInterHour(0)
	, m_iNTPInterMin(0)
	, m_bChkDdns(FALSE)
	, m_csDDNSAddr(_T(""))
	, m_csDDNSUserName(_T(""))
	, m_csDDNSPwd(_T(""))
	, m_csDDNSPwdConfirm(_T(""))
	, m_bChkEnablePPPoE(FALSE)
	, m_csPPPoEUserName(_T(""))
	, m_csPPPoEPwd(_T(""))
	, m_csPPPoEIP(_T(""))
	, m_csSmtpSvrAddr(_T(""))
	, m_csPop3SvrAddr(_T(""))
	, m_uDDNSPort(0)
	, m_iDeviceIndex(0)
	, m_uNtpPort(0)
	, m_wSmtpPort(0)
    , m_lEmailTestHandle(-1)
{
	memset(&m_struNTPPara, 0, sizeof(NET_DVR_NTPPARA));
	memset(&m_struDDNSPara, 0, sizeof(NET_DVR_DDNSPARA));
	memset(&m_struEmailCfg, 0, sizeof(NET_DVR_EMAILCFG_V30));
}

/*********************************************************
Function:	~CDlgRemoteAdvanceNetConfig
Desc:		destructor
Input:	
Output:	
Return:	
**********************************************************/
CDlgRemoteAdvanceNetConfig::~CDlgRemoteAdvanceNetConfig()
{
}

/*********************************************************
Function:	DoDataExchange
Desc:		the map between control and variable
Input:	
Output:	
Return:	
**********************************************************/
void CDlgRemoteAdvanceNetConfig::DoDataExchange(CDataExchange* pDX)
{

	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgRemoteAdvanceNetConfig)
	DDX_Control(pDX, IDC_COMBO_DDNS_TYPE, m_comboDDNSType);
	DDX_Text(pDX, IDC_EDIT_EMAIL_SEND_NAME, m_csSenderName);
	DDX_Text(pDX, IDC_EDIT_EMAIL_SENDER_ADDR, m_csSenderAddr);
	DDX_Text(pDX, IDC_EDIT_EMAIL_PWD, m_csAccountPwd);
	DDX_Text(pDX, IDC_EDIT_EMAIL_PWD_CONFIRM, m_csAccountPwdConfirm);
	DDX_Text(pDX, IDC_EDIT_EMAIL_ACCOUNT, m_csAccount);
	DDX_Check(pDX, IDC_CHK_AUTHEN, m_bChkAuthen);
	DDX_Check(pDX, IDC_CHK_ATTACH, m_bChkAttach);
	DDX_Control(pDX, IDC_COMBO_EMAIL_INTERVAL, m_comboSendInterval);
	DDX_Check(pDX, IDC_CHK_USE_NTP, m_bChkNtp);
	DDX_Text(pDX, IDC_EDIT_NTP_ADDR, m_csNtpAddr);
	DDX_Text(pDX, IDC_EDIT_NTP_INTERVAL, m_iNtpInterval);
	DDX_Text(pDX, IDC_EDIT_NTP_INTERVAL_HOUR, m_iNTPInterHour);
	DDX_Text(pDX, IDC_EDIT_NTP_INTERVAL_MIN, m_iNTPInterMin);
	DDX_Check(pDX, IDC_CHK_DDNS, m_bChkDdns);
	DDX_Text(pDX, IDC_EDIT_DDNS_ADDR, m_csDDNSAddr);
	DDX_Text(pDX, IDC_EDIT_DDNS_USER_NAME, m_csDDNSUserName);
	DDX_Text(pDX, IDC_EDIT_DDNS_PWD, m_csDDNSPwd);
	DDX_Text(pDX, IDC_EDIT_DDNS_PWD_CONFIRM, m_csDDNSPwdConfirm);
	DDX_Control(pDX, IDC_LIST_RECEIVER, m_listEmailReceiver);
	DDX_Text(pDX, IDC_EDIT_PPPOE_NAME, m_csPPPoEUserName);
	DDX_Text(pDX, IDC_EDIT_PPPOE_PWD, m_csPPPoEPwd);
	DDX_Text(pDX, IDC_EDIT_PPPOE_VERI_PWD, m_csPPPoEVeriPwd);
	DDX_Text(pDX, IDC_SUB_PPPOEIP, m_csPPPoEIP);
	DDX_Text(pDX, IDC_EDIT_SMTP_SVR_ADDR, m_csSmtpSvrAddr);
	DDX_Text(pDX, IDC_EDIT_POP3_SVR_ADDR, m_csPop3SvrAddr);
	DDX_Text(pDX, IDC_DDNS_PORT, m_uDDNSPort);
	DDX_Text(pDX, IDC_DEV_DOMAIN, m_csDevDomain);
	DDX_Text(pDX, IDC_EDIT_NTP_PORT, m_uNtpPort);
	DDX_Text(pDX, IDC_EDIT_SMTP_PORT, m_wSmtpPort);
	DDX_Check(pDX, IDC_CHK_ENABLE_PPPOE, m_bChkEnablePPPoE);
	DDX_Check(pDX, IDC_CHK_SSL, m_bEnableSSL);
	//}}AFX_DATA_MAP
}


/*********************************************************
Function:	BEGIN_MESSAGE_MAP
Desc:		the map between control and function
Input:	
Output:	
Return:	
**********************************************************/
BEGIN_MESSAGE_MAP(CDlgRemoteAdvanceNetConfig, CDialog)
	//{{AFX_MSG_MAP(CDlgRemoteAdvanceNetConfig)	
	ON_BN_CLICKED(IDC_CHK_ENABLE_PPPOE, OnBnClickedChkEnablePppoe)
	ON_BN_CLICKED(IDC_BTN_PPPOE_OK, OnBnClickedBtnPppoeOk)
	ON_BN_CLICKED(IDC_BTN_NTP_OK, OnBnClickedBtnNtpOk)
	ON_BN_CLICKED(IDC_BTN_DDNS_OK, OnBnClickedBtnDdnsOk)
	ON_BN_CLICKED(IDC_BTN_EMAILE_OK, OnBnClickedBtnEmaileOk)
	ON_BN_CLICKED(IDC_BTN_ADD_RECEIVER, OnBnClickedBtnAddReceiver)
	ON_BN_CLICKED(IDC_BTN_DEL_RECEIVER, OnBnClickedBtnDelReceiver)
	ON_BN_CLICKED(IDC_CHK_USE_NTP, OnBnClickedChkUseNtp)
	ON_BN_CLICKED(IDC_CHK_DDNS, OnBnClickedChkDdns)
	ON_BN_CLICKED(IDC_BTN_HIGH_NET_CONFIG_OK, OnBnClickedBtnHighNetConfigOk)
	ON_BN_CLICKED(IDC_BTN_EXIT, OnBtnExit)
	ON_CBN_SELCHANGE(IDC_COMBO_DDNS_TYPE, OnSelchangeComboDdnsType)
	ON_BN_CLICKED(IDC_BTN_TEST, OnBtnTest)
	ON_BN_CLICKED(IDC_BTN_SNMP_CFG, OnBtnSnmpCfg)
	//}}AFX_MSG_MAP
	
END_MESSAGE_MAP()


// CDlgRemoteAdvanceNetConfig message handlers
/*********************************************************
Function:	OnInitDialog
Desc:		Initialize the dialog
Input:	
Output:	
Return:	
**********************************************************/
BOOL CDlgRemoteAdvanceNetConfig::OnInitDialog()
{
	CDialog::OnInitDialog();
	CString sTemp;
	DWORD dwReturned;
	CString csToName;
	CString csToAddr;
	unsigned int i = 0;
	char csPPPoeName[NAME_LEN+1] = {0};
	char csPPPoEPwd[PASSWD_LEN+1] = {0};

    g_pRemoteAdvaceNetConfig = this;

	m_bChkEnablePPPoE = m_pPPPoECfg->dwPPPOE;
	EnablePPPOEItem(m_bChkEnablePPPoE);
	if (m_bChkEnablePPPoE)
	{
		memcpy(csPPPoeName, m_pPPPoECfg->sPPPoEUser, NAME_LEN);
		m_csPPPoEUserName.Format("%s", csPPPoeName);
		memcpy(csPPPoEPwd, m_pPPPoECfg->sPPPoEPassword, PASSWD_LEN);
		m_csPPPoEPwd.Format("%s", csPPPoEPwd);
		m_csPPPoEVeriPwd.Format("%s",csPPPoEPwd);
		m_csPPPoEIP.Format("%s", m_pPPPoECfg->struPPPoEIP.sIpV4);
	}

	memset(&m_struNTPPara, 0, sizeof(NET_DVR_NTPPARA));
	if (!NET_DVR_GetDVRConfig(m_lServerID, NET_DVR_GET_NTPCFG, 0, &m_struNTPPara, sizeof(NET_DVR_NTPPARA), &dwReturned))
	{
		GetDlgItem(IDC_CHK_USE_NTP)->EnableWindow(FALSE);
		GetDlgItem(IDC_BTN_NTP_OK)->EnableWindow(FALSE);
		EnableNTPItem(FALSE);
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_NTPCFG");	
		m_bNTPGet = FALSE;
	}
	else
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_NTPCFG");
		m_bChkNtp = m_struNTPPara.byEnableNTP;
		EnableNTPItem(m_bChkNtp);
		if (m_bChkNtp)
		{
			m_csNtpAddr.Format("%s", m_struNTPPara.sNTPServer);
			m_iNtpInterval = m_struNTPPara.wInterval;
			m_iNTPInterHour = m_struNTPPara.cTimeDifferenceH;
			m_iNTPInterMin = m_struNTPPara.cTimeDifferenceM;
			m_uNtpPort = m_struNTPPara.wNtpPort;
		}
		m_bNTPGet = TRUE;
	}
	memset(&m_struDDNSPara, 0, sizeof(NET_DVR_GET_DDNSCFG_V30));
	if (!NET_DVR_GetDVRConfig(m_lServerID, NET_DVR_GET_DDNSCFG_V30, 0, &m_struDDNSPara, sizeof(NET_DVR_DDNSPARA_V30), &dwReturned))
	{
		GetDlgItem(IDC_CHK_DDNS)->EnableWindow(FALSE);
		GetDlgItem(IDC_BTN_DDNS_OK)->EnableWindow(FALSE);	
		m_bChkDdns = FALSE;
		m_uDDNSPort = 0;
		SwitchDDNSCtrlStat(-1);
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_DDNSCFG_V30");
		m_bDDNSGet = FALSE;
	}
	else
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_DDNSCFG_V30");
		GetDlgItem(IDC_CHK_DDNS)->EnableWindow(TRUE);
		GetDlgItem(IDC_BTN_DDNS_OK)->EnableWindow(TRUE);
		m_bChkDdns = m_struDDNSPara.byEnableDDNS;
		m_comboDDNSType.ResetContent();
		m_comboDDNSType.AddString("IPServer");
		m_comboDDNSType.AddString("DynDNS");
		m_comboDDNSType.AddString("PeanutHull");
		m_comboDDNSType.AddString("NO-IP");
		m_comboDDNSType.AddString("hkDDNS");
		m_comboDDNSType.SetCurSel(m_struDDNSPara.byHostIndex);
		SwitchDDNSCtrlStat(m_struDDNSPara.byHostIndex);
		m_bDDNSGet = TRUE;
	}

	memset(&m_struEmailCfg, 0, sizeof(NET_DVR_EMAILCFG_V30));
	if (!NET_DVR_GetDVRConfig(m_lServerID, NET_DVR_GET_EMAILCFG_V30, 0, &m_struEmailCfg, sizeof(NET_DVR_EMAILCFG_V30), &dwReturned))
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_EMAILCFG_V30");
		GetDlgItem(IDC_LIST_RECEIVER)->EnableWindow(FALSE);
		GetDlgItem(IDC_COMBO_EMAIL_INTERVAL)->EnableWindow(FALSE);
		GetDlgItem(IDC_CHK_ATTACH)->EnableWindow(FALSE);
		GetDlgItem(IDC_CHK_AUTHEN)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_EMAIL_ACCOUNT)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_EMAIL_PWD_CONFIRM)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_EMAIL_PWD)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_EMAIL_SENDER_ADDR)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_EMAIL_SEND_NAME)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_EMAIL_SENDER_ADDR)->EnableWindow(FALSE);
		GetDlgItem(IDC_BTN_ADD_RECEIVER)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_POP3_SVR_ADDR)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_SMTP_SVR_ADDR)->EnableWindow(FALSE);
		GetDlgItem(IDC_BTN_DEL_RECEIVER)->EnableWindow(FALSE);
		GetDlgItem(IDC_BTN_EMAILE_OK)->EnableWindow(FALSE);
		m_bEmailGet = FALSE;
	}
	else
	{
		char szLan[128] = {0};
		char szName[33] = {0};
		char szRecPswd[49] = {0};
		char szAddress[49] = {0};
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_EMAILCFG_V30");
		m_comboSendInterval.SetCurSel(m_struEmailCfg.byMailInterval);
		m_listEmailReceiver.SetExtendedStyle(m_listEmailReceiver.GetExtendedStyle() | LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
		g_StringLanType(szLan, "���շ�����", "Receiver Name");
		m_listEmailReceiver.InsertColumn(0, szLan, LVCFMT_LEFT, 90, -1);
		g_StringLanType(szLan, "���շ�Email��ַ", "Recevier Email address");
		m_listEmailReceiver.InsertColumn(1, szLan, LVCFMT_LEFT, 200, -1);
		memcpy(szName, m_struEmailCfg.struSender.sName, 32);
		m_csSenderName.Format("%s", szName);
		memcpy(szAddress,m_struEmailCfg.struSender.sAddress,48);
		m_csSenderAddr.Format("%s", szAddress);
		memset(szName, 0, 33);
		memcpy(szName,m_struEmailCfg.sAccount,32);
		m_csAccount.Format("%s", szName);
		if (!m_csAccount.IsEmpty())
		{
			memset(szName,0,33);
			memcpy(szName, m_struEmailCfg.sPassword,32);
			m_csAccountPwd.Format("%s", szName);
			m_csAccountPwdConfirm = m_csAccountPwd;
		}

		for (i = 0; i < 3; i++)
		{
			memset(szName,0,33);
			memcpy(szName, m_struEmailCfg.struReceiver[i].sName,32);
			memset(szAddress,0,49);
			memcpy(szAddress,m_struEmailCfg.struReceiver[i].sAddress,48);
			csToName.Format("%s", szName);
			csToAddr.Format("%s", szAddress);
			if (!csToName.IsEmpty())
			{
				int iIndex = m_listEmailReceiver.InsertItem(m_listEmailReceiver.GetItemCount(), csToName);
				m_listEmailReceiver.SetItemText(iIndex, 1, csToAddr);
			}
		}

		m_bChkAuthen = m_struEmailCfg.bySmtpServerVerify;
		if (m_bChkAuthen != TRUE)
		{
			m_bChkAuthen = FALSE;
		}
		m_bChkAttach = m_struEmailCfg.byAttachment;
		if (m_bChkAttach != TRUE)
		{
			m_bChkAttach = FALSE;
		}
		//m_comboSendInterval.SetCurSel(m_struEmailCfg.byMailinterval);
		memset(szAddress,0,49);
		memcpy(szAddress, m_struEmailCfg.sSmtpServer,48);
		m_csSmtpSvrAddr.Format("%s",szAddress);
		//m_csPop3SvrAddr.Format("%s", m_struEmailCfg.sPop3Server);
		m_bEnableSSL = (BOOL)m_struEmailCfg.byEnableSSL;
		m_wSmtpPort = m_struEmailCfg.wSmtpPort;
		m_bEmailGet = TRUE;
	}

	UpdateData(FALSE);
	return TRUE;  
}

/*********************************************************
Function:	OnBnClickedBtnAddReceiver
Desc:		add email receiver info
Input:	
Output:	
Return:	
**********************************************************/
void CDlgRemoteAdvanceNetConfig::OnBnClickedBtnAddReceiver()
{
	char szLan[128] = {0};
	if (m_listEmailReceiver.GetItemCount() >= 3)
	{
		g_StringLanType(szLan, "Ŀǰֻ֧��3�����ն�!", "Now only suppert 3 receviers!");
		AfxMessageBox(szLan);
		return;
	}
	CDlgRemoteEmailAddReceiver dlgEmail;
	if (IDOK == dlgEmail.DoModal())
	{
		int iIndex = m_listEmailReceiver.InsertItem(m_listEmailReceiver.GetItemCount(), dlgEmail.m_csReceiverName);
		m_listEmailReceiver.SetItemText(iIndex, 1, dlgEmail.m_csReceiverAddr);
	}
}

/*********************************************************
Function:	OnBnClickedBtnDelReceiver
Desc:		delete email receiver info
Input:	
Output:	
Return:	
**********************************************************/
void CDlgRemoteAdvanceNetConfig::OnBnClickedBtnDelReceiver()
{
	POSITION iPos = m_listEmailReceiver.GetFirstSelectedItemPosition();
	int iIndex = m_listEmailReceiver.GetNextSelectedItem(iPos);
	if (iIndex < 0)
	{
		return;
	}
	m_listEmailReceiver.DeleteItem(iIndex);
}

/*********************************************************
Function:	OnBnClickedChkUseNtp
Desc:		update Ntp control status
Input:	
Output:	
Return:	
**********************************************************/
void CDlgRemoteAdvanceNetConfig::OnBnClickedChkUseNtp()
{
	UpdateData(TRUE);
	EnableNTPItem(m_bChkNtp);
}

/*********************************************************
Function:	OnBnClickedChkDdns
Desc:		update ddns control status
Input:	
Output:	
Return:	
**********************************************************/
void CDlgRemoteAdvanceNetConfig::OnBnClickedChkDdns()
{
	UpdateData(TRUE);
	SwitchDDNSCtrlStat(m_comboDDNSType.GetCurSel());
	UpdateData(FALSE);
}

/*********************************************************
Function:	OnBnClickedBtnHighNetConfigOk
Desc:		set advanced network configuration
Input:	
Output:	
Return:	
**********************************************************/
void CDlgRemoteAdvanceNetConfig::OnBnClickedBtnHighNetConfigOk()
{
	UpdateData(TRUE);

	CString sTemp;
	BOOL error = FALSE;
	char szLan[128] = {0};
	if (m_bNTPGet)
	{
		if (!NET_DVR_SetDVRConfig(m_lServerID, NET_DVR_SET_NTPCFG, 0, &m_struNTPPara, sizeof(NET_DVR_NTPPARA)))
		{
			g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_NTPCFG"); 
			g_StringLanType(szLan, "NTP��������ʧ��!", "NTP configure error!");
			AfxMessageBox(szLan);		
			error = TRUE;
		}
		else
		{
			g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_NTPCFG");
		}
	}

	if (m_bDDNSGet)
	{
		if (!NET_DVR_SetDVRConfig(m_lServerID, NET_DVR_SET_DDNSCFG_V30, 0, &m_struDDNSPara, sizeof(NET_DVR_DDNSPARA_V30)))
		{
			g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_DDNSCFG_V30"); 
			g_StringLanType(szLan, "DDNS��������ʧ��!", "DDNS configure save error!");
			AfxMessageBox(szLan);	
			error = TRUE;
		}
		else
		{
			g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_DDNSCFG_V30"); 
		}
	}

	if (m_bEmailGet)
	{
		if (!NET_DVR_SetDVRConfig(m_lServerID, NET_DVR_SET_EMAILCFG_V30, 0, &m_struEmailCfg, sizeof(NET_DVR_EMAILCFG_V30)))
		{
			g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_EMAILCFG_V30"); 
			g_StringLanType(szLan, "Email��������ʧ��!", "Email configure save error!");
			AfxMessageBox(szLan);	
			error = TRUE;
		}
		else
		{
			g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_EMAILCFG_V30");
		}
	}

	if (!error)
	{
		g_StringLanType(szLan, "��������ɹ�!", "save successfully!");
		AfxMessageBox(szLan);
	}
}

/*********************************************************
Function:	EnableNTPItem
Desc:		enable ntp
Input:	
Output:	
Return:		TRUE,enable;FALSE,disable
**********************************************************/
void CDlgRemoteAdvanceNetConfig::EnableNTPItem(BOOL bEnable)
{
	GetDlgItem(IDC_EDIT_NTP_ADDR)->EnableWindow(bEnable);
	GetDlgItem(IDC_EDIT_NTP_INTERVAL)->EnableWindow(bEnable);
	GetDlgItem(IDC_EDIT_NTP_INTERVAL_HOUR)->EnableWindow(bEnable);
	GetDlgItem(IDC_EDIT_NTP_INTERVAL_MIN)->EnableWindow(bEnable);
	GetDlgItem(IDC_EDIT_NTP_PORT)->EnableWindow(bEnable);
	UpdateData(FALSE);
}

/*********************************************************
  Function:	OnBnClickedChkEnablePppoe
  Desc:		enable/disable pppoe
  Input:	
  Output:	
  Return:	
**********************************************************/
void CDlgRemoteAdvanceNetConfig::OnBnClickedChkEnablePppoe()
{
	UpdateData(TRUE);
	EnablePPPOEItem(m_bChkEnablePPPoE);
}

/*********************************************************
Function:	EnablePPPOEItem
Desc:		pppoe status
Input:	
Output:	
Return:	
**********************************************************/
void CDlgRemoteAdvanceNetConfig::EnablePPPOEItem(BOOL bFlag)
{
	GetDlgItem(IDC_EDIT_PPPOE_NAME)->EnableWindow(bFlag);
	GetDlgItem(IDC_EDIT_PPPOE_PWD)->EnableWindow(bFlag);
	UpdateData(FALSE);
}

/*********************************************************
  Function:	OnBnClickedBtnPppoeOk
  Desc:		get PPPoe status
  Input:	
  Output:	
  Return:	
**********************************************************/
void CDlgRemoteAdvanceNetConfig::OnBnClickedBtnPppoeOk()
{
	UpdateData(TRUE);
	char szLan[128] = {0};
	if(m_csPPPoEPwd != m_csPPPoEVeriPwd)
	{
		g_StringLanType(szLan, "������ȷ�����벻һ��!", "Password and Confirm Password inconsistent!");
		AfxMessageBox(szLan);
		return;
	}
	m_pPPPoECfg->dwPPPOE = m_bChkEnablePPPoE;
	if (m_bChkEnablePPPoE)
	{
		memcpy(m_pPPPoECfg->sPPPoEUser, m_csPPPoEUserName, NAME_LEN);
		memcpy(m_pPPPoECfg->sPPPoEPassword, m_csPPPoEPwd, PASSWD_LEN);
		memcpy(m_pPPPoECfg->struPPPoEIP.sIpV4, m_csPPPoEIP, 16);
	}
	//should set pppoe by netcfg_v30
	g_pMainDlg->m_dlgRemoteCfg->m_subDlgDeviceCfg.m_bNetCfgSet = TRUE;
	g_pMainDlg->m_dlgRemoteCfg->m_subDlgDeviceCfg.CfgSetup();
}

/*********************************************************
Function:	OnBnClickedBtnNtpOk
Desc:		get ntp status
Input:	
Output:	
Return:	
**********************************************************/
void CDlgRemoteAdvanceNetConfig::OnBnClickedBtnNtpOk()
{
	UpdateData(TRUE);
	char szLan[128] = {0};
	if (m_iNTPInterHour < -12 || m_iNTPInterHour > 13 || m_iNTPInterMin < 0 || m_iNTPInterMin >59)
	{
		g_StringLanType(szLan, "ʱ����������!", "Time Zone Error!");
		AfxMessageBox(szLan);
		return;
	}

	m_struNTPPara.byEnableNTP = (BYTE)m_bChkNtp;
	if (m_bChkNtp)
	{
		memcpy(m_struNTPPara.sNTPServer, m_csNtpAddr, MAX_DOMAIN_NAME);
		m_struNTPPara.wInterval = m_iNtpInterval;
		m_struNTPPara.cTimeDifferenceH = (char)m_iNTPInterHour;
		m_struNTPPara.cTimeDifferenceM = (char)m_iNTPInterMin;
		m_struNTPPara.wNtpPort = (WORD)m_uNtpPort;
	}
}

/*********************************************************
Function:	OnBnClickedBtnDdnsOk
Desc:		get ddns config
Input:	
Output:	
Return:	
**********************************************************/
void CDlgRemoteAdvanceNetConfig::OnBnClickedBtnDdnsOk()
{
	UpdateData(TRUE);

	m_struDDNSPara.byEnableDDNS = (BYTE)m_bChkDdns;
	m_struDDNSPara.byHostIndex = (BYTE)m_comboDDNSType.GetCurSel();
	if (m_bChkDdns)
	{
		memcpy(m_struDDNSPara.struDDNS[m_struDDNSPara.byHostIndex].sServerName, m_csDDNSAddr, MAX_DOMAIN_NAME);
		m_struDDNSPara.struDDNS[m_struDDNSPara.byHostIndex].wDDNSPort = (WORD)m_uDDNSPort;
		memcpy(m_struDDNSPara.struDDNS[m_struDDNSPara.byHostIndex].sUsername, m_csDDNSUserName, NAME_LEN);
		memcpy(m_struDDNSPara.struDDNS[m_struDDNSPara.byHostIndex].sPassword, m_csDDNSPwd, PASSWD_LEN);
		memcpy(m_struDDNSPara.struDDNS[m_struDDNSPara.byHostIndex].sDomainName, m_csDevDomain, MAX_DOMAIN_NAME);
	}
}

/*********************************************************
  Function:	SwitchDDNSCtrlStat
  Desc:		change the control status about ddns
  Input:	iHost, the ddns type
  Output:	none
  Return:	none
**********************************************************/
void CDlgRemoteAdvanceNetConfig::SwitchDDNSCtrlStat(int iHost)
{	
	char csUserName[NAME_LEN+1] = {0};
	if (m_bChkDdns)
	{
		switch(iHost)
		{
		case 0://private
			GetDlgItem(IDC_EDIT_DDNS_ADDR)->EnableWindow(TRUE);
			GetDlgItem(IDC_DDNS_PORT)->EnableWindow(TRUE);
			GetDlgItem(IDC_EDIT_DDNS_USER_NAME)->EnableWindow(FALSE);
			GetDlgItem(IDC_EDIT_DDNS_PWD)->EnableWindow(FALSE);
			GetDlgItem(IDC_EDIT_DDNS_PWD_CONFIRM)->EnableWindow(FALSE);
			GetDlgItem(IDC_DEV_DOMAIN)->EnableWindow(TRUE);
			m_csDDNSAddr.Format("%s", m_struDDNSPara.struDDNS[iHost].sServerName);
			m_csDDNSUserName.Format("");
			m_csDDNSPwd.Format("");
			m_csDDNSPwdConfirm.Format("");
			//
			m_uDDNSPort = m_struDDNSPara.struDDNS[iHost].wDDNSPort;
			//m_uDDNSPort = 7070;
			//m_csDevDomain.Format("");
			m_csDevDomain = m_struDDNSPara.struDDNS[iHost].sDomainName;
			break;
		case 1://DynDNS
			GetDlgItem(IDC_EDIT_DDNS_ADDR)->EnableWindow(TRUE);
			GetDlgItem(IDC_DDNS_PORT)->EnableWindow(TRUE);
			GetDlgItem(IDC_EDIT_DDNS_USER_NAME)->EnableWindow(TRUE);
			GetDlgItem(IDC_EDIT_DDNS_PWD)->EnableWindow(TRUE);
			GetDlgItem(IDC_EDIT_DDNS_PWD_CONFIRM)->EnableWindow(TRUE);
			GetDlgItem(IDC_DEV_DOMAIN)->EnableWindow(TRUE);
			m_csDDNSAddr.Format("%s", m_struDDNSPara.struDDNS[iHost].sServerName);
			memcpy(csUserName, m_struDDNSPara.struDDNS[iHost].sUsername, NAME_LEN);
			m_csDDNSUserName.Format("%s", csUserName);
			m_csDDNSPwd.Format("%s", m_struDDNSPara.struDDNS[iHost].sPassword);
			m_csDDNSPwdConfirm = m_csDDNSPwd;
			m_uDDNSPort = m_struDDNSPara.struDDNS[iHost].wDDNSPort;
			m_csDevDomain = m_struDDNSPara.struDDNS[iHost].sDomainName;
			break;
		case 2://PeanutHull
			GetDlgItem(IDC_EDIT_DDNS_ADDR)->EnableWindow(FALSE);
			GetDlgItem(IDC_DDNS_PORT)->EnableWindow(FALSE);
			GetDlgItem(IDC_EDIT_DDNS_USER_NAME)->EnableWindow(TRUE);
			GetDlgItem(IDC_EDIT_DDNS_PWD)->EnableWindow(TRUE);
			GetDlgItem(IDC_EDIT_DDNS_PWD_CONFIRM)->EnableWindow(TRUE);
			GetDlgItem(IDC_DEV_DOMAIN)->EnableWindow(FALSE);
			m_csDDNSAddr.Format("%s", m_struDDNSPara.struDDNS[iHost].sServerName);
			memcpy(csUserName, m_struDDNSPara.struDDNS[iHost].sUsername, NAME_LEN);
			m_csDDNSUserName.Format("%s", csUserName);
			m_csDDNSPwd.Format("%s", m_struDDNSPara.struDDNS[iHost].sPassword);
			m_csDDNSPwdConfirm = m_csDDNSPwd;
			m_csDevDomain = m_struDDNSPara.struDDNS[iHost].sDomainName;
			m_uDDNSPort = 0;//
			m_csDevDomain.Format("");
			break;
		case 3://NO-IP
			GetDlgItem(IDC_EDIT_DDNS_ADDR)->EnableWindow(FALSE);
			GetDlgItem(IDC_DDNS_PORT)->EnableWindow(FALSE);
			GetDlgItem(IDC_EDIT_DDNS_USER_NAME)->EnableWindow(TRUE);
			GetDlgItem(IDC_EDIT_DDNS_PWD)->EnableWindow(TRUE);
			GetDlgItem(IDC_EDIT_DDNS_PWD_CONFIRM)->EnableWindow(TRUE);
			GetDlgItem(IDC_DEV_DOMAIN)->EnableWindow(TRUE);
			m_csDDNSAddr.Format("%s", m_struDDNSPara.struDDNS[iHost].sServerName);
			memcpy(csUserName, m_struDDNSPara.struDDNS[iHost].sUsername, NAME_LEN);
			m_csDDNSUserName.Format("%s", csUserName);
			m_csDDNSPwd.Format("%s", m_struDDNSPara.struDDNS[iHost].sPassword);
			m_csDDNSPwdConfirm = m_csDDNSPwd;
			m_uDDNSPort = 0;//m_struDDNSPara.struDDNS[m_struDDNSPara.byHostIndex].wDDNSPort
			m_csDevDomain = m_struDDNSPara.struDDNS[iHost].sDomainName;
			break;
        case 4://EDDNS
            GetDlgItem(IDC_EDIT_DDNS_ADDR)->EnableWindow(TRUE);
            GetDlgItem(IDC_DDNS_PORT)->EnableWindow(TRUE);
            GetDlgItem(IDC_EDIT_DDNS_USER_NAME)->EnableWindow(FALSE);
            GetDlgItem(IDC_EDIT_DDNS_PWD)->EnableWindow(FALSE);
            GetDlgItem(IDC_EDIT_DDNS_PWD_CONFIRM)->EnableWindow(FALSE);
            GetDlgItem(IDC_DEV_DOMAIN)->EnableWindow(TRUE);
            m_csDDNSAddr.Format("%s", m_struDDNSPara.struDDNS[iHost].sServerName);
			memcpy(csUserName, m_struDDNSPara.struDDNS[iHost].sUsername, NAME_LEN);
            m_csDDNSUserName.Format("%s", csUserName);
            m_csDDNSPwd.Format("%s", m_struDDNSPara.struDDNS[iHost].sPassword);
            m_csDDNSPwdConfirm = m_csDDNSPwd;
            m_uDDNSPort = m_struDDNSPara.struDDNS[iHost].wDDNSPort;
            m_csDevDomain = m_struDDNSPara.struDDNS[iHost].sDomainName;
			break;
		default:
			break;
		}
		GetDlgItem(IDC_COMBO_DDNS_TYPE)->EnableWindow(TRUE);
	}
	else
	{
		GetDlgItem(IDC_COMBO_DDNS_TYPE)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_DDNS_ADDR)->EnableWindow(FALSE);
		GetDlgItem(IDC_DDNS_PORT)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_DDNS_USER_NAME)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_DDNS_PWD)->EnableWindow(FALSE);
		GetDlgItem(IDC_EDIT_DDNS_PWD_CONFIRM)->EnableWindow(FALSE);
		GetDlgItem(IDC_DEV_DOMAIN)->EnableWindow(FALSE);
	}
}

/*********************************************************
Function:	OnBnClickedBtnEmaileOk
Desc:		get email configuration
Input:	
Output:	
Return:	
**********************************************************/
void CDlgRemoteAdvanceNetConfig::OnBnClickedBtnEmaileOk()
{
	UpdateData(TRUE);
	int i = 0;
	char szLan[128] = {0};
	if (!m_csSenderAddr.IsEmpty() && !CheckEmailAddress(m_csSenderAddr))
	{
		g_StringLanType(szLan, "Email��ַ����", "Email Address error");
		AfxMessageBox(szLan);
		return;
	}
	if (m_csAccountPwd != m_csAccountPwdConfirm)
	{
		g_StringLanType(szLan, "Email�ʻ����벻ƥ��", "Email account password does not match");
		AfxMessageBox(szLan);
		return;
	}
	if (m_bChkDdns &&m_csDDNSPwd != m_csDDNSPwdConfirm)
	{
		g_StringLanType(szLan, "DDNS�ʻ����벻ƥ��", "DDNS account password does not match");
		AfxMessageBox(szLan);
		return;
	}

	if (!m_csAccountPwd.IsEmpty() && m_csAccount.IsEmpty())
	{
		g_StringLanType(szLan, "Email�ʻ�������Ϊ��", "Email account name should not be empty");
		AfxMessageBox(szLan);
		return;
	}


	ZeroMemory(&m_struEmailCfg, sizeof(m_struEmailCfg));
	m_struEmailCfg.dwSize = sizeof(m_struEmailCfg);
	sprintf((char *)(m_struEmailCfg.sAccount), "%s", m_csAccount);
	sprintf((char *)(m_struEmailCfg.sPassword), "%s", m_csAccountPwd);
	sprintf((char *)(m_struEmailCfg.struSender.sName), "%s", m_csSenderName);
	sprintf((char *)(m_struEmailCfg.struSender.sAddress), "%s", m_csSenderAddr);
	for (i = 0;i<m_listEmailReceiver.GetItemCount(); i++)
	{
		sprintf((char *)(m_struEmailCfg.struReceiver[i].sName), "%s", m_listEmailReceiver.GetItemText(i,0));
		sprintf((char *)(m_struEmailCfg.struReceiver[i].sAddress), "%s", m_listEmailReceiver.GetItemText(i,1));
	}

	sprintf((char *)(m_struEmailCfg.sSmtpServer), "%s", m_csSmtpSvrAddr);
	sprintf((char *)(m_struEmailCfg.sPop3Server), "%s", m_csPop3SvrAddr);
	m_struEmailCfg.byAttachment = (BYTE)m_bChkAttach;
	m_struEmailCfg.bySmtpServerVerify = (BYTE)m_bChkAuthen;
	m_struEmailCfg.byMailInterval = (BYTE)m_comboSendInterval.GetCurSel();
	m_struEmailCfg.byEnableSSL = (BYTE)m_bEnableSSL;
	m_struEmailCfg.wSmtpPort = m_wSmtpPort;
}

/*********************************************************
  Function: OnBtnExit	
  Desc:		exit the advance net configure
  Input:	none
  Output:	none
  Return:	none
**********************************************************/
void CDlgRemoteAdvanceNetConfig::OnBtnExit() 
{
	// TODO: Add your control notification handler code here
	CDialog::OnCancel();
}

/*********************************************************
  Function:	OnSelchangeComboDdnsType
  Desc:		select the ddns type
  Input:	void
  Output:	void
  Return:	void
**********************************************************/
void CDlgRemoteAdvanceNetConfig::OnSelchangeComboDdnsType() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	SwitchDDNSCtrlStat(m_comboDDNSType.GetCurSel());
	UpdateData(FALSE);
}

UINT GetEmailTestStatus(LPVOID pParam)
{
    CDlgRemoteAdvanceNetConfig *pEmailTest = (CDlgRemoteAdvanceNetConfig*)pParam;

    BOOL bKeepLoop = TRUE;
    DWORD dwState = 0;
    while (bKeepLoop)
    {

       if (!NET_DVR_GetEmailTestProgress(pEmailTest->m_lEmailTestHandle, &dwState))
       {
            AfxMessageBox(" ��ȡ�ʼ�����״̬ʧ��");
            bKeepLoop = FALSE;
       }
       if (PROCESS_SUCCESS == dwState)
       {
           pEmailTest->SetEmailTestState("�ʼ����Գɹ�");
           bKeepLoop = FALSE;
       }
       else if (PROCESS_FAILED == dwState)
       {
           pEmailTest->SetEmailTestState("�ʼ�����ʧ��");
           bKeepLoop = FALSE;
       }
       else if (PROCESS_EXCEPTION == dwState)
       {
           pEmailTest->SetEmailTestState("�ʼ����������쳣");
           bKeepLoop = FALSE;
       }
       else if (PROCESSING == dwState)
       {
           pEmailTest->SetEmailTestState("�ʼ�������");
       }
       Sleep(1000);
    }
    
    NET_DVR_StopEmailTest(pEmailTest->m_lEmailTestHandle);;
    return 0;
}

void CDlgRemoteAdvanceNetConfig::SetEmailTestState(LPCTSTR lpszString)
{
    GetDlgItem(IDC_STATIC_EMAILTEST)->SetWindowText(lpszString);
}
/*********************************************************
  Function:	OnBtnTest
  Desc:		test email configure is ok or not
  Input:	void
  Output:	void
  Return:	void
**********************************************************/
void CDlgRemoteAdvanceNetConfig::OnBtnTest() 
{
    m_lEmailTestHandle =  NET_DVR_StartEmailTest(m_lServerID);
    if (-1 == m_lEmailTestHandle)
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_StartEmailTest");
        MessageBox("�ʼ�����ʧ��");
    }
    
    m_hEmailTestThread = CreateThread(NULL,0, LPTHREAD_START_ROUTINE(GetEmailTestStatus),this,0,NULL);		
    if (m_hEmailTestThread != NULL)
    {
        CloseHandle(m_hEmailTestThread);
        m_hEmailTestThread = NULL;
    }

}

void CDlgRemoteAdvanceNetConfig::OnBtnSnmpCfg() 
{
    CDlgSnmpCfg dlg;
   	dlg.m_lServerID = m_lServerID;
    dlg.m_iDevIndex = m_iDeviceIndex;
    dlg.DoModal();
}
