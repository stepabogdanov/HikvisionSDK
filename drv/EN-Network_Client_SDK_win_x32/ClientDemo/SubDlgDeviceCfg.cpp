/**********************************************************
FileName:    SubDlgDeviceCfg.cpp
Description: device info configuration    
Date:        2008/05/17
Note: 		<Global>struct, macro refer to GeneralDef.h, global variants and API refer to ClientDemo.cpp   
Modification History:      
    <version> <time>         <desc>
    <1.0    > <2008/05/17>       <created>
***********************************************************/


#include "stdafx.h"
#include "ClientDemo.h"
#include "SubDlgDeviceCfg.h"
#include ".\subdlgdevicecfg.h"
#include "MatDecDnsCfg.h"
#include "DlgRemoteNetNFS.h"
#include "DlgRemoteAdvanceNetConfig.h"
#include "DlgRemoteZone.h"
#include "DlgRtspConfig.h"
#include "DlgDeviceAudioTalkCode.h"
#include "DlgWifi.h"
#include "DlgCcdParam.h"
#include "DialogMultiNetCard.h"
#include "DlgJpegFTP.h"
#include "DlgNetworkBonding.h"
#include "DlgNetworkFlowTest.h"
#include "DlgUpnpCfg.h"	
#include "DlgAES.h"
#include "DlgESataMiniSasUsage.h"
#include "DlgAutoReboot.h"
#include "DlgEthernetIpv6Cfg.h"

// CSubDlgDeviceCfg dialog
/*********************************************************
  Function:	CSubDlgDeviceCfg
  Desc:		Constructor
  Input:	
  Output:	
  Return:	
**********************************************************/
IMPLEMENT_DYNAMIC(CSubDlgDeviceCfg, CDialog)
CSubDlgDeviceCfg::CSubDlgDeviceCfg(CWnd* pParent /*=NULL*/)
	: CDialog(CSubDlgDeviceCfg::IDD, pParent)
	, m_csDeviceName(_T(""))
	, m_iHdNum(0)
	, m_iYKQID(0)
	, m_csIPResolver(_T(""))
	, m_csDeviceIP(_T(""))
	, m_csMultiIP(_T(""))
	, m_iMainPort(0)
	, m_csGatewayIP(_T(""))
	, m_csIPMask(_T(""))
	, m_csDeviceSerialNo(_T(""))
	, m_csSoftwareVersion(_T(""))
	, m_csHardwareVersion(_T(""))
	, m_csPanelVersion(_T(""))
	, m_csDspVersion(_T(""))
	, m_iAlarmInNum(0)
	, m_iAlarmOutNum(0)
	, m_iChanNum(0)
	, m_csMacAddr(_T(""))
	, m_csRemoteManageHost1IP(_T(""))
	, m_iHttpPort(0)
	, m_iRemoteManageHost1Port(0)
	, m_bDeviceCfgSet(FALSE)
	, m_bNetCfgSet(FALSE)
	, m_iDeviceIndex(-1)//CheckInitParam, iut is required that m_iDeviceIndex is initialed as -1
	, m_lLoginID(-1)
	, m_iChanCount(0)
	, m_lStartChannel(0)
	, m_dwUseZoom(0)
	, m_bSupScale(FALSE)
	, m_csAlarmHostIP(_T(""))
	, m_iAlarmHostPort(0)
	, m_iResolverPort(0)
	, m_csDNSIP1(_T("0.0.0.0"))
	, m_csDNSIP2(_T("0.0.0.0"))
	, m_wMTU(1500)
	, m_iAuxoManagePort(0)
	, m_bChkDhcp(FALSE)
	, m_csDevTypeName(_T(""))
{
	memset(&m_struDeviceCfg, 0, sizeof(m_struDeviceCfg));
	memset(&m_struNetCfg, 0, sizeof(m_struNetCfg));
	memset(&m_struMenuOutputMode, 0, sizeof(m_struMenuOutputMode));
}

/*********************************************************
  Function:	~CSubDlgDeviceCfg
  Desc:		destructor
  Input:	
  Output:	
  Return:	
**********************************************************/
CSubDlgDeviceCfg::~CSubDlgDeviceCfg()
{
}

/*********************************************************
Function:	DoDataExchange
Desc:		the map between control and variable
Input:	
Output:	
Return:	
**********************************************************/
void CSubDlgDeviceCfg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSubDlgDeviceCfg)
	DDX_Control(pDX, IDC_SUB_COMBO_IPV6_MODE, m_comboIPv6Mode);
	DDX_Control(pDX, IDC_COMBO_MENU_OUTPUT_MODE, m_cmbMenuOutputMode);
	DDX_Control(pDX, IDC_COMBO_STORAGE_MODE, m_comboStorageMode);
	DDX_Control(pDX, IDC_COMBO_IPC_PLUG, m_comboPlug);
	DDX_Control(pDX, IDC_COMBO_ESATA, m_comboEsata);
	DDX_Control(pDX, IDC_COMBO_DEV_SUPPORT, m_comboDevSupport);
	DDX_Control(pDX, IDC_COMBO_SUB_PROTOCOL, m_comboSubProtocol);
	DDX_Control(pDX, IDC_COMBO_MAIN_PROTOCOL, m_comboMainProtocol);
	DDX_Control(pDX, IDC_SUB_COMBO_MINOR_ZOOM, m_comboMinor);
	DDX_Text(pDX, IDC_SUB_EDIT_DEVICE_NAME, m_csDeviceName);
	DDX_Text(pDX, IDC_SUB_EDIT_HD_NUM, m_iHdNum);
	DDX_Text(pDX, IDC_SUB_EDIT_YKQID, m_iYKQID);
	DDX_Text(pDX, IDC_SUB_EDIT_RESOLVER_IP, m_csIPResolver);
	DDX_Text(pDX, IDC_SUB_EDIT_DEVIP, m_csDeviceIP);
	DDX_Text(pDX, IDC_SUB_EDIT_MULTIIP, m_csMultiIP);
	DDX_Text(pDX, IDC_SUB_EDIT_PORT, m_iMainPort);
	DDX_Text(pDX, IDC_SUB_EDIT_GATEWAY, m_csGatewayIP);
	DDX_Text(pDX, IDC_SUB_EDIT_IPMASK, m_csIPMask);
	DDX_Control(pDX, IDC_SUB_COMBO_NET_FACE, m_comboNetFace);
	DDX_Control(pDX, IDC_SUB_COMBO_USE_ZOOM, m_comboUseZoom);
	DDX_Text(pDX, IDC_SUB_EDIT_SERIAL, m_csDeviceSerialNo);
	DDX_Text(pDX, IDC_SUB_SOFTWARE_VERSION, m_csSoftwareVersion);
	DDX_Text(pDX, IDC_SUB_HARDWARE_VERSION, m_csHardwareVersion);
	DDX_Text(pDX, IDC_SUB_DSP_VERSION, m_csDspVersion);
	DDX_Text(pDX, IDC_SUB_ALARM_IN_NUM, m_iAlarmInNum);
	DDX_Text(pDX, IDC_SUB_ALARM_OUT_NUM, m_iAlarmOutNum);
	DDX_Text(pDX, IDC_SUB_EDIT_CHAN_NUM, m_iChanNum);
	DDX_Control(pDX, IDC_SUB_CYCLE_RECORD, m_comboCycleRec);
	DDX_Text(pDX, IDC_SUB_EDIT_MACIP, m_csMacAddr);
	DDX_Text(pDX, IDC_SUB_MANAGE_HOST1IP, m_csRemoteManageHost1IP);
	DDX_Text(pDX, IDC_AUXO_MANAGE_HOSTIP, m_csAuxoManageHostIP);
	DDX_Text(pDX, IDC_AUXO_MANAGE_HOSTPORT, m_iAuxoManagePort);
	DDX_Check(pDX, IDC_CHK_DHCP, m_bChkDhcp);
	DDX_Text(pDX, IDC_SUB_QMB_VERSION, m_csPanelVersion);
	DDX_Text(pDX, IDC_EDIT_ZEROCHAN_NUM, m_iZeroChanNum);
	DDX_Text(pDX, IDC_SUB_EDIT_DEV_TYPE_NAME, m_csDevTypeName);
	DDX_Text(pDX, IDC_SUB_EDIT_HTTP_PORT, m_iHttpPort);
	DDX_Text(pDX, IDC_SUB_MANAGE_HOST1PORT, m_iRemoteManageHost1Port);
	DDX_Text(pDX, IDC_SUB_ALARM_HOSTIP, m_csAlarmHostIP);
	DDX_Text(pDX, IDC_SUB_ALARM_HOST_PORT, m_iAlarmHostPort);
	DDX_Text(pDX, IDC_SUB_RESOLVER_PORT, m_iResolverPort);
	DDX_Text(pDX, IDC_SUB_EDIT_DNS_IP1, m_csDNSIP1);
	DDX_Text(pDX, IDC_SUB_DNS_IP2, m_csDNSIP2);
	DDX_Text(pDX, IDC_SUB_MTU, m_wMTU);
	//}}AFX_DATA_MAP
}


/*********************************************************
Function:	BEGIN_MESSAGE_MAP
Desc:		the map between control and function
Input:	
Output:	
Return:	
**********************************************************/
BEGIN_MESSAGE_MAP(CSubDlgDeviceCfg, CDialog)
	//{{AFX_MSG_MAP(CSubDlgDeviceCfg)	
	ON_BN_CLICKED(IDC_BTN_REMOTE_NET_OK, OnBnClickedBtnRemoteNetOk)
	ON_BN_CLICKED(IDC_BTN_MAT_DEC_DNS, OnBnClickedBtnMatDecDns)
	ON_BN_CLICKED(IDC_BTN_ADVANCE_NET_SETUP, OnBnClickedBtnAdvanceNetSetup)
	ON_BN_CLICKED(IDC_BTN_REMOTE_NET_NFS, OnBnClickedBtnRemoteNetNfs)
	ON_BN_CLICKED(IDC_BTN_ZONE, OnBtnZone)
	ON_BN_CLICKED(IDC_BTN_RTSP, OnBtnRtsp)
	ON_BN_CLICKED(IDC_CHK_DHCP, OnChkDhcp)
	ON_BN_CLICKED(IDC_BTN_AUDIOTALKCODET_CONFIG, OnBtnAudiotalkcodetConfig)
	ON_BN_CLICKED(IDC_BTN_WIFI_CONFIG, OnBtnWifiConfig)
	ON_BN_CLICKED(IDC_BTN_CCDCONFIG, OnBtnCCDConfig)
	ON_BN_CLICKED(IDC_BUTTON_MULT_NETCARD, OnButtonMultNetcard)
	ON_BN_CLICKED(IDC_BUTTON_JPEG_FTP, OnButtonJpegFtp)
	ON_BN_CLICKED(IDC_BTN_NETWORK_FLOWTEST, OnBtnNetworkFlowtest)
	ON_BN_CLICKED(IDC_BTN_BONDING_CFG, OnBtnBondingCfg)
	ON_BN_CLICKED(IDC_BUTTON_UPNP, OnButtonUpnp)
	ON_BN_CLICKED(IDC_BUTTON_AES, OnButtonAes)
	ON_BN_CLICKED(IDC_BUTTON_ESATA_MINISAS_USAGE, OnButtonEsataMinisasUsage)
	ON_BN_CLICKED(IDC_BTN_AUTO_REBOOT, OnBtnAutoReboot)
	ON_BN_CLICKED(IDC_BTN_GET_ETHERNET_IPV6_CFG, OnBtnGetEthernetIpv6Cfg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// CSubDlgDeviceCfg message handlers
/*********************************************************
Function:	OnInitDialog
Desc:		Initialize the dialog
Input:	
Output:	
Return:	
**********************************************************/
BOOL CSubDlgDeviceCfg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	CRect rc(0, 0, 0, 0);
	GetParent()->GetClientRect(&rc);
	((CTabCtrl*)GetParent())->AdjustRect(FALSE, &rc);
	MoveWindow(&rc);

	return TRUE;
}

inline BOOL CSubDlgDeviceCfg::ValidIPv6(BYTE *ip)
{
	if (strlen((char *)ip) >= 2 && strchr((char *)ip, ':') != NULL)
	{
		return TRUE;
	}
	return FALSE;
}

/*********************************************************
Function:	CheckInitParam
Desc:		detect device parameters and update parameter display on the dialog box
Input:	
Output:	
Return:	TRUE,correct parameter, update paramerter display; FALSE, do not initial
**********************************************************/
BOOL CSubDlgDeviceCfg::CheckInitParam()
{
	int iDeviceIndex = g_pMainDlg->GetCurDeviceIndex();
	DWORD dwReturned = 0;
	CString sTemp;
	char szLan[128] = {0};

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
		//update parameter display on the control
		m_iDeviceIndex = iDeviceIndex;
		m_lLoginID = g_struDeviceInfo[m_iDeviceIndex].lLoginID;
		m_lStartChannel = g_struDeviceInfo[m_iDeviceIndex].iStartChan;
		m_iChanCount = g_struDeviceInfo[m_iDeviceIndex].iDeviceChanNum;
	}

	m_csDeviceName = _T("");
	m_iHdNum = 0;
	m_iYKQID = 0;
	m_csIPResolver = _T("");
	m_csDeviceIP = _T("");
	m_csMultiIP = _T("");
	m_iMainPort = 0;
	m_csGatewayIP = _T("");
	m_csIPMask = _T("");
	m_csDeviceSerialNo = _T("");
	m_csSoftwareVersion = _T("");
	m_csHardwareVersion = _T("");
	m_csPanelVersion = _T("");
	m_csDspVersion = _T("");
	m_iAlarmInNum = 0;
	m_iAlarmOutNum = 0;
	m_iChanNum = 0;
	m_csMacAddr = _T("");
	m_csRemoteManageHost1IP = _T("");
	m_iRemoteManageHost1Port = 0;

	m_csAuxoManageHostIP = _T("");
	m_iAuxoManagePort = 0;
	m_iHttpPort = 0;
	m_csDevTypeName = _T("");

	m_comboUseZoom.SetCurSel(-1);

	if (m_lLoginID < 0)
	{
		return FALSE;
	}

// 	if ((g_pMainDlg->IsCurDevMatDec(iDeviceIndex)))
// 	{
// 		GetDlgItem(IDC_BTN_ADVANCE_NET_SETUP)->ShowWindow(SW_SHOW);
// 		GetDlgItem(IDC_BTN_ZONE)->ShowWindow(SW_HIDE);
// 		GetDlgItem(IDC_BTN_REMOTE_NET_NFS)->ShowWindow(SW_HIDE);
// 		GetDlgItem(IDC_BTN_MAT_DEC_DNS)->ShowWindow(SW_SHOW);
// 	}
// 	else
	{
		GetDlgItem(IDC_BTN_ADVANCE_NET_SETUP)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_BTN_ZONE)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_BTN_REMOTE_NET_NFS)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_BTN_MAT_DEC_DNS)->ShowWindow(SW_HIDE);
	}

	m_bSetDeviceCfg = FALSE;
	memset(&m_struDeviceCfg, 0, sizeof(m_struDeviceCfg));
	memset(&m_struNetCfg, 0, sizeof(NET_DVR_NETCFG_V30));
	m_dwUseZoom = 0;
	if (!NET_DVR_GetDVRConfig(m_lLoginID, NET_DVR_GET_DEVICECFG_V40, 0, &m_struDeviceCfg, sizeof(m_struDeviceCfg), &dwReturned))
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_DEVICECFG_V40");
		g_StringLanType(szLan, "获取设备参数失败", "Get Device Configure failed");
		AfxMessageBox(szLan);
	//	return FALSE;
	}
	else
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_DEVICECFG_V40");
	}

	if (!NET_DVR_GetDVRConfig(m_lLoginID, NET_DVR_GET_NETCFG_V30, 0,&m_struNetCfg, sizeof(NET_DVR_NETCFG_V30), &dwReturned))
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_NETCFG_V30");
		g_StringLanType(szLan, "获取网络参数失败", "Get Network Configure failed");
		AfxMessageBox(szLan);
	}
	else
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_NETCFG_V30");
	}

	if (!NET_DVR_GetScaleCFG_V30(m_lLoginID, &m_struScale))
	{
		m_bSupScale = FALSE;
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GetScaleCFG_V30");
	}
	else
	{
		m_bSupScale = TRUE;	
	}

	if (!NET_DVR_GetDVRConfig(m_lLoginID, NET_DVR_GET_MEMU_OUTPUT_MODE, 0,&m_struMenuOutputMode, sizeof(NET_DVR_MENU_OUTPUT_MODE), &dwReturned))
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_MEMU_OUTPUT_MODE");
	}
	else
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_MEMU_OUTPUT_MODE");
		m_cmbMenuOutputMode.SetCurSel(m_struMenuOutputMode.byMenuOutputMode);
	}

	UpdateData(FALSE);
	return TRUE;
}

/*********************************************************
Function:	CurCfgUpdate
Desc:		update parameter and refresh control display
Input:	
Output:	
Return:	
**********************************************************/
void CSubDlgDeviceCfg::CurCfgUpdate()
{
	if (!CheckInitParam())
	{
		UpdateData(FALSE);
		EnableWindow(FALSE);
		return;
	}
	EnableWindow(TRUE);
	
	char cTemp[200] = {0};
	if (m_bSupScale)
	{		
		GetDlgItem(IDC_STATICSCALE)->ShowWindow(SW_SHOW);
		m_comboUseZoom.ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC_MAJOR)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_STATIC_MINOR)->ShowWindow(SW_SHOW);
		m_comboMinor.ShowWindow(SW_SHOW);
		m_comboUseZoom.SetCurSel(m_struScale.dwMajorScale);	
		m_comboMinor.SetCurSel(m_struScale.dwMinorScale);	
	}
	else
	{
		GetDlgItem(IDC_STATICSCALE)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_MAJOR)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_STATIC_MINOR)->ShowWindow(SW_HIDE);
		m_comboUseZoom.ShowWindow(SW_HIDE);
		m_comboMinor.ShowWindow(SW_HIDE);
	}

    //2010-01-16
    char szLan[128] = {0};
    m_comboDevSupport.ResetContent();
    if (m_struDeviceCfg.bySupport & 0x01 == 1)
    {
        g_StringLanType(szLan, "支持移动侦测搜索", "Motion Search");
        m_comboDevSupport.AddString(szLan);
    }

    if (((m_struDeviceCfg.bySupport >> 1) & 0x01) == 1)
    {
        g_StringLanType(szLan, "支持备份", "Backup");
        m_comboDevSupport.AddString(szLan);
    }

    if (((m_struDeviceCfg.bySupport >> 2) & 0x01) == 1)
    {
        g_StringLanType(szLan, "支持压缩能力", "Compression Ability");
        m_comboDevSupport.AddString(szLan);
    }

    if (((m_struDeviceCfg.bySupport >> 4) & 0x01) == 1)
    {
        g_StringLanType(szLan, "远程SADP", "Remote SADP");
        m_comboDevSupport.AddString(szLan);
    }

    if (((m_struDeviceCfg.bySupport >> 5) & 0x01) == 1)
    {
        g_StringLanType(szLan, "Raid", "Raid");
        m_comboDevSupport.AddString(szLan);
    }

    if ((m_struDeviceCfg.bySupport >> 6 & 0x01) == 1)
    {
        m_comboDevSupport.AddString("IPSAN Search");
    }

	if ((m_struDeviceCfg.bySupport >> 7 & 0x01) == 1)
	{
		m_comboDevSupport.AddString("RTP Over RTSP");
    }

	if (m_struDeviceCfg.bySupport1 & 0x01 == 1)
    {
        m_comboDevSupport.AddString("SNMP V30");
    }

    if (((m_struDeviceCfg.bySupport >> 1) & 0x01) == 1)
    {
        g_StringLanType(szLan, "区分回放和下载", "distinguish playback from download");
        m_comboDevSupport.AddString(szLan);
    }

	m_comboEsata.ResetContent();
	g_StringLanType(szLan, "备份", "Backup");
	m_comboEsata.AddString(szLan);
	g_StringLanType(szLan, "录像", "Record");
	m_comboEsata.AddString(szLan);

    m_comboSubProtocol.SetCurSel(g_struDeviceInfo[m_iDeviceIndex].bySubProto);
    m_comboMainProtocol.SetCurSel(g_struDeviceInfo[m_iDeviceIndex].byMainProto);
	m_comboPlug.SetCurSel(m_struDeviceCfg.byIPCPlug);
	m_comboEsata.SetCurSel(m_struDeviceCfg.byEsataUseage);
    m_iZeroChanNum = m_struDeviceCfg.byZeroChanNum;

	m_comboCycleRec.SetCurSel(m_struDeviceCfg.dwRecycleRecord);
	ZeroMemory(cTemp, 200);
	memcpy(cTemp, m_struDeviceCfg.sDVRName, NAME_LEN);
	m_csDeviceName.Format("%s", cTemp);
	m_iYKQID = m_struDeviceCfg.dwDVRID;
	ZeroMemory(cTemp, 200);
	memcpy(cTemp, m_struDeviceCfg.sSerialNumber, SERIALNO_LEN);
	m_csDeviceSerialNo.Format("%s", cTemp);
	memcpy(cTemp,m_struDeviceCfg.byDevTypeName,sizeof(m_struDeviceCfg.byDevTypeName));
	m_csDevTypeName.Format("%s",cTemp);

	if (((m_struDeviceCfg.dwSoftwareVersion>>24)&0xFF) > 0)
	{
		m_csSoftwareVersion.Format("V%d.%d.%d build %02d%02d%02d",\
			(m_struDeviceCfg.dwSoftwareVersion>>24)&0xFF, (m_struDeviceCfg.dwSoftwareVersion>>16)&0xFF, m_struDeviceCfg.dwSoftwareVersion&0xFFFF, (m_struDeviceCfg.dwSoftwareBuildDate>>16)&0xFFFF, (m_struDeviceCfg.dwSoftwareBuildDate>>8)&0xFF,m_struDeviceCfg.dwSoftwareBuildDate&0xFF);
	}
	else
	{
		m_csSoftwareVersion.Format("V%d.%d build %02d%02d%02d",\
			(m_struDeviceCfg.dwSoftwareVersion>>16)&0xFFFF, m_struDeviceCfg.dwSoftwareVersion&0xFFFF, (m_struDeviceCfg.dwSoftwareBuildDate>>16)&0xFFFF, (m_struDeviceCfg.dwSoftwareBuildDate>>8)&0xFF,m_struDeviceCfg.dwSoftwareBuildDate&0xFF);
	}
	m_csDspVersion.Format("V%d.%d build %02d%02d%02d", (m_struDeviceCfg.dwDSPSoftwareVersion>>16)&0xFFFF, m_struDeviceCfg.dwDSPSoftwareVersion&0xFFFF, (m_struDeviceCfg.dwDSPSoftwareBuildDate>>16)&0xFFFF-2000, (m_struDeviceCfg.dwDSPSoftwareBuildDate>>8)&0xFF,m_struDeviceCfg.dwDSPSoftwareBuildDate&0xFF);	
	m_csHardwareVersion.Format("0x%x", m_struDeviceCfg.dwHardwareVersion);
	m_csPanelVersion.Format("V%d", m_struDeviceCfg.dwPanelVersion);

	m_iAlarmInNum = m_struDeviceCfg.byAlarmInPortNum;
	m_iAlarmOutNum = m_struDeviceCfg.byAlarmOutPortNum;
	m_iChanNum = m_struDeviceCfg.byChanNum;	
    m_comboStorageMode.SetCurSel(m_struDeviceCfg.byStorageMode);
// 	for (int i=0; i<m_iTypeNum; i++)
// 	{
// 		if (m_comboDeviceType.GetItemData(i) == m_struDeviceCfg.byDVRType)
// 		{
// 			m_iSelType = i;
// 			break;
// 		}
// 	}
	/*m_comboDeviceType.SetCurSel(m_iSelType);*/
    m_csDevTypeName = m_struDeviceCfg.byDevTypeName;
	if (m_struNetCfg.byUseDhcp == 0xff)
	{
		GetDlgItem(IDC_CHK_DHCP)->EnableWindow(FALSE);
	}
	else
	{
		GetDlgItem(IDC_CHK_DHCP)->EnableWindow(TRUE);
		m_bChkDhcp = m_struNetCfg.byUseDhcp;
		EnableDhcp();
	}

	m_csIPResolver = m_struNetCfg.byIpResolver;
	//2011-7-19,对使用ipv6登陆的设备，优先显示其ipv6地址
	BOOL bShowIpv6 = ValidIPv6((BYTE*)g_struDeviceInfo[m_iDeviceIndex].chDeviceIP);
	if (bShowIpv6 && ValidIPv6(m_struNetCfg.struGatewayIpAddr.byIPv6))
	{
		m_csGatewayIP.Format("%s", m_struNetCfg.struGatewayIpAddr.byIPv6);
	}
	else
	{
		m_csGatewayIP.Format("%s", m_struNetCfg.struGatewayIpAddr.sIpV4);
	}
	if (bShowIpv6 && ValidIPv6(m_struNetCfg.struEtherNet[0].struDVRIP.byIPv6))
	{
		m_csDeviceIP.Format("%s", m_struNetCfg.struEtherNet[0].struDVRIP.byIPv6);
	}
	else
	{
		m_csDeviceIP.Format("%s", m_struNetCfg.struEtherNet[0].struDVRIP.sIpV4);
	}
	if (bShowIpv6 && ValidIPv6(m_struNetCfg.struEtherNet[0].struDVRIPMask.byIPv6))
	{
		m_csIPMask.Format("%s", m_struNetCfg.struEtherNet[0].struDVRIPMask.byIPv6);
	}
	else
	{
		m_csIPMask.Format("%s", m_struNetCfg.struEtherNet[0].struDVRIPMask.sIpV4);
	}
	m_csMacAddr.Format("%02x:%02x:%02x:%02x:%02x:%02x", m_struNetCfg.struEtherNet[0].byMACAddr[0],m_struNetCfg.struEtherNet[0].byMACAddr[1],m_struNetCfg.struEtherNet[0].byMACAddr[2],m_struNetCfg.struEtherNet[0].byMACAddr[3],m_struNetCfg.struEtherNet[0].byMACAddr[4],m_struNetCfg.struEtherNet[0].byMACAddr[5]);
	if (bShowIpv6 && ValidIPv6(m_struNetCfg.struMulticastIpAddr.byIPv6))
	{
		m_csMultiIP.Format("%s", m_struNetCfg.struMulticastIpAddr.byIPv6);
	}
	else
	{
		m_csMultiIP.Format("%s", m_struNetCfg.struMulticastIpAddr.sIpV4);
	}
	if (bShowIpv6 && ValidIPv6(m_struNetCfg.struDnsServer1IpAddr.byIPv6))
	{
		m_csDNSIP1.Format("%s", m_struNetCfg.struDnsServer1IpAddr.byIPv6);
	}
	else
	{
		m_csDNSIP1.Format("%s", m_struNetCfg.struDnsServer1IpAddr.sIpV4);
	}
	if (bShowIpv6 && ValidIPv6(m_struNetCfg.struDnsServer2IpAddr.byIPv6))
	{
		m_csDNSIP2.Format("%s", m_struNetCfg.struDnsServer2IpAddr.byIPv6);
	}
	else
	{
		m_csDNSIP2.Format("%s", m_struNetCfg.struDnsServer2IpAddr.sIpV4);
	}
	m_wMTU = m_struNetCfg.struEtherNet[0].wMTU;
	m_iMainPort = m_struNetCfg.struEtherNet[0].wDVRPort;
	m_iHdNum = m_struDeviceCfg.byDiskNum;
// 	m_csRemoteManageHost1IP = m_struNetCfg.struManageHost1IpAddr.sIpV4;
// 	m_iRemoteManageHost1Port = m_struNetCfg.wManageHost1Port;
// 	m_csAuxoManageHostIP = m_struNetCfg.struManageHost2IpAddr.sIpV4;
// 	m_iAuxoManagePort = m_struNetCfg.wManageHost2Port;
	if (bShowIpv6 && ValidIPv6(m_struNetCfg.struAlarmHostIpAddr.byIPv6))
	{
		m_csAlarmHostIP.Format("%s", m_struNetCfg.struAlarmHostIpAddr.byIPv6);
	}
	else
	{
		m_csAlarmHostIP.Format("%s", m_struNetCfg.struAlarmHostIpAddr.sIpV4);
	}
	m_iAlarmHostPort = m_struNetCfg.wAlarmHostIpPort;
	ZeroMemory(cTemp, 200);
	memcpy(cTemp, m_struNetCfg.byIpResolver, MAX_DOMAIN_NAME);
	m_csIPResolver = cTemp;

	m_comboNetFace.SetCurSel(m_struNetCfg.struEtherNet[0].dwNetInterface-1);
	m_iHttpPort = m_struNetCfg.wHttpPortNo;
	m_comboIPv6Mode.SetCurSel(m_struNetCfg.byIPv6Mode);


	UpdateData(FALSE);
}

/*********************************************************
  Function:	CfgSetup
  Desc:		users need to click device info box and click "OK" on the network configurtaion area
  Input:	
  Output:	
  Return:	TRUE,setting succeed;FALSE, setting failed;
**********************************************************/
BOOL CSubDlgDeviceCfg::CfgSetup()
{
	CString sTemp;
	BOOL bRet = TRUE;
	char szLan[128] = {0};
	
	if (m_bSupScale)
	{
		m_struScale.dwMajorScale = m_comboUseZoom.GetCurSel();
		m_struScale.dwMinorScale = m_comboMinor.GetCurSel();
		if (!NET_DVR_SetScaleCFG_V30(m_lLoginID, &m_struScale))
		{
			g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SetScaleCFG_V30");
			bRet = FALSE;
			//AfxMessageBox("enable scale failed!");		
		}
		else
		{
			g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SetScaleCFG_V30");
		}
	}

	if (m_bDeviceCfgSet)
	{
		if (!NET_DVR_SetDVRConfig(m_lLoginID, NET_DVR_SET_DEVICECFG_V40, 0,&(m_struDeviceCfg), sizeof(m_struDeviceCfg)))
		{
			g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_DEVICECFG_V40");
			//AfxMessageBox("save device info failed!");
			bRet = FALSE;
		}
		else
		{
			g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_DEVICECFG_V40");
		}
	}

	if (m_bNetCfgSet)
	{
		if (!NET_DVR_SetDVRConfig(m_lLoginID, NET_DVR_SET_NETCFG_V30, 0, &(m_struNetCfg), sizeof(NET_DVR_NETCFG_V30)))
		{
			g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_NETCFG_V30");
			g_StringLanType(szLan, "网络参数保存失败", "Save Network configuration failed");
			AfxMessageBox(szLan);
			bRet = FALSE;
		}
		else
		{
			g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_NETCFG_V30");
		}
		//setting succeed, save device configurtaion

		if (!g_ValidIPv6((BYTE *)(g_struDeviceInfo[m_iDeviceIndex].chDeviceIP)))
		{
			sprintf(g_struDeviceInfo[m_iDeviceIndex].chDeviceMultiIP,"%s", m_struNetCfg.struMulticastIpAddr.sIpV4);
		} 
		else
		{
			sprintf(g_struDeviceInfo[m_iDeviceIndex].chDeviceMultiIP,"%s", m_struNetCfg.struMulticastIpAddr.byIPv6);
		}
	}

	if (!NET_DVR_SetDVRConfig(m_lLoginID, NET_DVR_SET_MEMU_OUTPUT_MODE, 0, &(m_struMenuOutputMode), sizeof(NET_DVR_MENU_OUTPUT_MODE)))
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_MEMU_OUTPUT_MODE");
		bRet = FALSE;
	}
	else
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_MEMU_OUTPUT_MODE");
	}
	
	return bRet;
}

/*********************************************************
  Function:	OnBnClickedBtnRemoteNetOk
  Desc:		Confirm network parameter settings
  Input:	
  Output:	
  Return:	
**********************************************************/
void CSubDlgDeviceCfg::OnBnClickedBtnRemoteNetOk()
{
	UpdateData(TRUE);
	char szLan[128] = {0};

	if (m_iMainPort <= 0)
	{
		g_StringLanType(szLan, "非法的设备端口号", "Illegal device port number");
		AfxMessageBox(szLan);
		return;
	}

	if (/*(m_csDeviceIP == "0.0.0.0") ||*/ (m_csDeviceIP == "") || (!CheckIPStr(m_csDeviceIP) && 
		!ValidIPv6((BYTE*)m_csDeviceIP.GetBuffer(m_csDeviceIP.GetLength()))))
	{
		g_StringLanType(szLan, "非法的设备IP地址", "Illegal device ip address");
		AfxMessageBox(szLan);
		return;
	}

	if (!CheckIPStr(m_csIPMask) && !ValidIPv6((BYTE*)m_csIPMask.GetBuffer(m_csIPMask.GetLength())))
	{
		g_StringLanType(szLan, "非法的掩码地址", "Illegal device MAC address");
		AfxMessageBox(szLan);
		return;
	}

	if (m_comboNetFace.GetCurSel() == 5)//1000M full
	{	
		g_StringLanType(szLan, "请确认为1000M网络，否则无法再登陆设备", "Please this is 1000M network, or can not login device again");
		if (IDOK!=MessageBox(szLan, "Waring",IDOK))
		{
			return;
		}
	}

	if (!CheckIPStr(m_csMultiIP) && !ValidIPv6((BYTE*)m_csMultiIP.GetBuffer(m_csMultiIP.GetLength())))
	{
		g_StringLanType(szLan, "非法的多播IP地址", "Illegal Multicast address");
		AfxMessageBox(szLan);
		return;
	}
	
	if (!CheckIPStr(m_csGatewayIP) && !ValidIPv6((BYTE*)m_csGatewayIP.GetBuffer(m_csGatewayIP.GetLength())))
	{
		g_StringLanType(szLan, "非法的网关IP地址", "Illegal Gateway ip address");
		AfxMessageBox(szLan);
		return;
	}

	if (!CheckIPStr(m_csRemoteManageHost1IP) && !ValidIPv6((BYTE*)m_csRemoteManageHost1IP.GetBuffer(m_csRemoteManageHost1IP.GetLength())))
	{
		g_StringLanType(szLan, "非法的管理主机IP地址", "Illegal Manage host ip address");
		AfxMessageBox(szLan);
		return; 
	}

//Save device configuration
    //2010-01-16
//     m_struDeviceCfg.bySubProto = m_comboSubProtocol.GetCurSel();
//     m_struDeviceCfg.byMainProto = m_comboMainProtocol.GetCurSel();
    m_struDeviceCfg.byIPCPlug = m_comboPlug.GetCurSel();
    m_struDeviceCfg.byEsataUseage = m_comboEsata.GetCurSel(); 
	m_struDeviceCfg.byZeroChanNum = m_iZeroChanNum;
    m_struDeviceCfg.byStorageMode = m_comboStorageMode.GetCurSel();

	m_struDeviceCfg.dwDVRID = m_iYKQID;
	memcpy(m_struDeviceCfg.sDVRName, m_csDeviceName, NAME_LEN);	
	m_struDeviceCfg.dwRecycleRecord = m_comboCycleRec.GetCurSel();
	if (m_bSupScale)
	{
		m_dwUseZoom = m_comboUseZoom.GetCurSel();	
	}
	m_bDeviceCfgSet = TRUE;

//Save network configuration
	m_struNetCfg.byUseDhcp = (BYTE)m_bChkDhcp;
	if (m_csDeviceIP.Find(':') != -1)
	{
		strncpy((char *)m_struNetCfg.struEtherNet[0].struDVRIP.byIPv6, m_csDeviceIP, 128);
	}
	else
	{
		strncpy(m_struNetCfg.struEtherNet[0].struDVRIP.sIpV4, m_csDeviceIP, 16);
	}
	if (m_csIPMask.Find(':') != -1)
	{
		strncpy((char *)m_struNetCfg.struEtherNet[0].struDVRIPMask.byIPv6, m_csIPMask, 128);
	}
	else
	{
		strncpy(m_struNetCfg.struEtherNet[0].struDVRIPMask.sIpV4, m_csIPMask, 16);
	}
	memcpy(m_struNetCfg.byIpResolver, m_csIPResolver, MAX_DOMAIN_NAME);
	//m_struNetCfg.wIpResolverPort = m_iResolverPort;
	if (m_csMultiIP.Find(':') != -1)
	{
		strncpy((char *)m_struNetCfg.struMulticastIpAddr.byIPv6, m_csMultiIP, 128);
	}
	else
	{
		strncpy(m_struNetCfg.struMulticastIpAddr.sIpV4, m_csMultiIP, 16);
	}
	if (m_csGatewayIP.Find(':') != -1)
	{
		strncpy((char *)m_struNetCfg.struGatewayIpAddr.byIPv6, m_csGatewayIP, 128);
	}
	else
	{
		strncpy(m_struNetCfg.struGatewayIpAddr.sIpV4, m_csGatewayIP, 16);
	}
	m_struNetCfg.struEtherNet[0].wDVRPort = (WORD)m_iMainPort;
	m_struNetCfg.struEtherNet[0].wMTU = m_wMTU;
	if (m_csDNSIP1.Find(':') != -1)
	{
		strncpy((char *)m_struNetCfg.struDnsServer1IpAddr.byIPv6, m_csDNSIP1, 128);
	}
	else
	{
		strncpy(m_struNetCfg.struDnsServer1IpAddr.sIpV4, m_csDNSIP1, 16);
	}
	if (m_csDNSIP2.Find(':') != -1)
	{
		strncpy((char *)m_struNetCfg.struDnsServer2IpAddr.byIPv6, m_csDNSIP2, 128);
	}
	else
	{
		strncpy(m_struNetCfg.struDnsServer2IpAddr.sIpV4, m_csDNSIP2, 16);
	}
// 	memcpy(m_struNetCfg.struManageHost1IpAddr.sIpV4, m_csRemoteManageHost1IP,16);
// 	m_struNetCfg.wManageHost1Port = m_iRemoteManageHost1Port;
// 	memcpy(m_struNetCfg.struManageHost2IpAddr.sIpV4, m_csAuxoManageHostIP,16);
// 	m_struNetCfg.wManageHost2Port = m_iAuxoManagePort;

	if (m_csAlarmHostIP.Find(':') != -1)
	{
		strncpy((char *)m_struNetCfg.struAlarmHostIpAddr.byIPv6, m_csAlarmHostIP, 128);
	}
	else
	{
		strncpy(m_struNetCfg.struAlarmHostIpAddr.sIpV4, m_csAlarmHostIP, 16);
	}
	m_struNetCfg.wAlarmHostIpPort = (WORD)m_iAlarmHostPort;

	m_struNetCfg.struEtherNet[0].dwNetInterface = m_comboNetFace.GetCurSel()+1;
	m_struNetCfg.byIPv6Mode = m_comboIPv6Mode.GetCurSel();
	m_struNetCfg.wHttpPortNo = (WORD)m_iHttpPort;
	//m_struDeviceCfg.byLockFrontPanel.GetCurSel();
	m_bNetCfgSet = TRUE;
	g_bMustReboot = g_pMainDlg->IsNeedRebootDevType();
}

/*********************************************************
  Function:	OnBnClickedBtnMatDecDns
  Desc:		Multi-channel decoder DNS settings
  Input:	
  Output:	
  Return:	
**********************************************************/
void CSubDlgDeviceCfg::OnBnClickedBtnMatDecDns()
{
	CDlgRemoteMatDecDnsCfg dlg;

	dlg.m_lLoginID = m_lLoginID;
	dlg.DoModal();
}

/*********************************************************
  Function:	OnBnClickedBtnRemoteNetNfs
  Desc:		NFS configurtaion
  Input:	
  Output:	
  Return:	
**********************************************************/
void CSubDlgDeviceCfg::OnBnClickedBtnRemoteNetNfs()
{
	CDlgRemoteNetNFS dlg;
	dlg.m_lServerID = m_lLoginID;
    dlg.m_iDevIndex = m_iDeviceIndex;  
	dlg.DoModal();
}

/*********************************************************
  Function:	OnBnClickedBtnAdvanceNetSetup
  Desc:		ADvanced network settings
  Input:	
  Output:	
  Return:	
**********************************************************/
void CSubDlgDeviceCfg::OnBnClickedBtnAdvanceNetSetup()
{
	CDlgRemoteAdvanceNetConfig dlg;
	dlg.m_pPPPoECfg = &m_struNetCfg.struPPPoE;
	dlg.m_lServerID = m_lLoginID;
	dlg.m_iDeviceIndex = m_iDeviceIndex;
	dlg.DoModal();
}

/*********************************************************
  Function:	OnBtnZone
  Desc:		to configure the zone and dst
  Input:	none
  Output:	none
  Return:	none
**********************************************************/
void CSubDlgDeviceCfg::OnBtnZone() 
{
	// TODO: Add your control notification handler code here
	CDlgRemoteZone dlg;
	dlg.m_iDeviceIndex = m_iDeviceIndex;
	dlg.DoModal();
}

void CSubDlgDeviceCfg::OnBtnRtsp() 
{
	// TODO: Add your control notification handler code here
	CDlgRtspConfig dlg;
	dlg.m_iDeviceIndex = m_iDeviceIndex;
	dlg.DoModal();
}

void CSubDlgDeviceCfg::OnChkDhcp() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	EnableDhcp();
}

void CSubDlgDeviceCfg::EnableDhcp()
{
	GetDlgItem(IDC_SUB_EDIT_DEVIP)->EnableWindow(!m_bChkDhcp);
	GetDlgItem(IDC_SUB_EDIT_IPMASK)->EnableWindow(!m_bChkDhcp);
	GetDlgItem(IDC_SUB_EDIT_GATEWAY)->EnableWindow(!m_bChkDhcp);
	GetDlgItem(IDC_SUB_EDIT_DNS_IP1)->EnableWindow(!m_bChkDhcp);
	GetDlgItem(IDC_SUB_DNS_IP2)->EnableWindow(!m_bChkDhcp);
}

void CSubDlgDeviceCfg::OnBtnAudiotalkcodetConfig() 
{
	// TODO: Add your control notification handler code here
	CDlgDeviceAudioTalkCode dlg;
	dlg.m_iDeviceIndex = m_iDeviceIndex;
	dlg.DoModal();
}

void CSubDlgDeviceCfg::OnBtnWifiConfig() 
{
	// TODO: Add your control notification handler code here
	CDlgWifi dlg;
	dlg.m_iDeviceIndex = m_iDeviceIndex;
	dlg.DoModal();
}

void CSubDlgDeviceCfg::OnBtnCCDConfig()
{
    CDlgCcdParam dlg;
	dlg.m_iDeviceIndex = m_iDeviceIndex;
	dlg.DoModal();
}

void CSubDlgDeviceCfg::OnButtonMultNetcard() 
{
  CDialogMultiNetCard dlg;
  dlg.DoModal();
}

void CSubDlgDeviceCfg::OnButtonJpegFtp() 
{
	CJpegFTP dlg;
	dlg.m_lServerID = m_lLoginID;
	DWORD m_dwDeviceIndex = g_pMainDlg->GetCurDeviceIndex();
	dlg.m_lStartChannel = g_struDeviceInfo[m_dwDeviceIndex].iStartChan;
	dlg.DoModal();
}

void CSubDlgDeviceCfg::OnBtnNetworkFlowtest() 
{
   	CDlgNetworkFlowTest dlg;
    
    dlg.m_lServerID = m_lLoginID;
    dlg.m_iDevIndex = g_pMainDlg->GetCurDeviceIndex();

    dlg.DoModal();
}

void CSubDlgDeviceCfg::OnBtnBondingCfg() 
{
	CDlgNetworkBonding dlg;
    dlg.m_lServerID = m_lLoginID;
    dlg.m_iDevIndex = g_pMainDlg->GetCurDeviceIndex();
    dlg.m_dwNetworkNum = 4;     // 网卡数目 todo!!!
    dlg.DoModal();
}

void CSubDlgDeviceCfg::OnButtonUpnp() 
{
	CDlgUpnpCfg dlg;
	dlg.m_lUserID = m_lLoginID;
    dlg.m_dwDeviceIndex = g_pMainDlg->GetCurDeviceIndex();
    dlg.DoModal();
}

void CSubDlgDeviceCfg::OnButtonAes() 
{
	CDlgAES dlg;
	dlg.m_lUSerID = m_lLoginID;
    dlg.m_dwDeviceIndex = g_pMainDlg->GetCurDeviceIndex();
    dlg.DoModal();	
}

void CSubDlgDeviceCfg::OnButtonEsataMinisasUsage() 
{
	// TODO: Add your control notification handler code here
	CDlgESataMiniSasUsage dlg;
	dlg.m_lUserID = m_lLoginID;
    dlg.m_dwDevIndex = g_pMainDlg->GetCurDeviceIndex();
    dlg.DoModal();	
}

void CSubDlgDeviceCfg::OnBtnAutoReboot() 
{
	// TODO: Add your control notification handler code here
	CDlgAutoReboot dlg;
	dlg.m_lUserID = m_lLoginID;
	dlg.m_iDeviceIndex = g_pMainDlg->GetCurDeviceIndex();
	dlg.DoModal();
}

void CSubDlgDeviceCfg::OnBtnGetEthernetIpv6Cfg() 
{
	// TODO: Add your control notification handler code here
	CDlgEthernetIpv6Cfg dlg;
	dlg.m_lUserID = m_lLoginID;
	dlg.m_iDeviceIndex = g_pMainDlg->GetCurDeviceIndex();
	dlg.DoModal();
}
