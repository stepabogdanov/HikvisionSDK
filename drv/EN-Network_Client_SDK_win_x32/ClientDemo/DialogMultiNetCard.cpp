// DialogMultiNetCard.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DialogMultiNetCard.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDialogMultiNetCard dialog


CDialogMultiNetCard::CDialogMultiNetCard(CWnd* pParent /*=NULL*/)
	: CDialog(CDialogMultiNetCard::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDialogMultiNetCard)
	m_csAlarmIp = _T("");
    m_iAlarmPort = 0;
    m_iHttpPort = 0;
    m_csManage1IP = _T("");
    m_iManage2Port = 0;
    m_csManage2IP = _T("");
    m_iManage1Port = 0;
    m_iResolverPort = 0;
    m_csRelolverIP = _T("");
    m_csMultIP = _T("");
    m_bCard2 = FALSE;
    m_bCard1 = FALSE;
    m_bCard1Dhcp = FALSE;
    m_bCard2Dhcp = FALSE;
    m_csCard1DNS1 = _T("");
    m_csCard2DNS1 = _T("");
    m_csCard1DNS2 = _T("");
    m_csCard2DNS2 = _T("");
    m_csCard2GateWay = _T("");
    m_csCard1GateWay = _T("");
    m_csCard1Ip = _T("");
    m_csCard2Ip = _T("");
    m_csCard2Mac = _T("");
    m_csCard1Mac = _T("");
    m_csCard1Mask = _T("");
    m_csCard2Mask = _T("");
    m_wCard2MTU = 0;
    m_wCard1MTU = 0;
    m_bEnablePPPoE = FALSE;
    m_csPPPoEIP = _T("");
    m_csPPPoEPassword = _T("");
    m_csPPPoEUserName = _T("");
	m_iDVRPort = 0;
	m_bCard3Dhcp = FALSE;
	m_bCard4Dhcp = FALSE;
	m_csCard3DNS1 = _T("");
	m_csCard3DNS2 = _T("");
	m_csCard3GateWay = _T("");
	m_csCard3Ip = _T("");
	m_csCard3Mac = _T("");
	m_csCard3Mask = _T("");
	m_wCard3MTU = 0;
	m_csCard4DNS1 = _T("");
	m_csCard4DNS2 = _T("");
	m_csCard4GateWay = _T("");
	m_csCard4Ip = _T("");
	m_csCard4Mac = _T("");
	m_csCard4Mask = _T("");
	m_wCard4MTU = 0;
	//}}AFX_DATA_INIT
	m_bShowIpv6 = FALSE;
}


void CDialogMultiNetCard::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDialogMultiNetCard)
	DDX_Control(pDX, IDC_COMBO_CARD4, m_card4Type);
	DDX_Control(pDX, IDC_COMBO_CARD3, m_card3Type);
	DDX_Control(pDX, IDC_COMBO_ROUTER_CARD, m_routerCard);
    DDX_Control(pDX, IDC_COMBO_CARD2, m_card2Type);
    DDX_Control(pDX, IDC_COMBO_CARD1, m_card1Type);
    DDX_Text(pDX, IDC_EDIT_ALARM_IP, m_csAlarmIp);
    DDX_Text(pDX, IDC_EDIT_ALARM_PORT, m_iAlarmPort);
    DDX_Text(pDX, IDC_EDIT_HTTP_PORT, m_iHttpPort);
    DDX_Text(pDX, IDC_EDIT_MANAGE_1IP, m_csManage1IP);
    DDX_Text(pDX, IDC_EDIT_MANAGE_PORT2, m_iManage2Port);
    DDX_Text(pDX, IDC_EDIT1_MANAGE_IP2, m_csManage2IP);
    DDX_Text(pDX, IDC_EDIT1_MANAGE_PORT1, m_iManage1Port);
    DDX_Text(pDX, IDC_EDIT_RESOLVER_PORT, m_iResolverPort);
    DDX_Text(pDX, IDC_EDIT_RESOLVER_IP, m_csRelolverIP);
    DDX_Text(pDX, IDC_EDIT_MULT_IP, m_csMultIP);
    DDX_Check(pDX, IDC_CHECK_CARD1_DHCP, m_bCard1Dhcp);
    DDX_Check(pDX, IDC_CHECK_CARD2_DHCP, m_bCard2Dhcp);
    DDX_Text(pDX, IDC_EDIT_CARD1_DNS1, m_csCard1DNS1);
    DDX_Text(pDX, IDC_EDIT_CARD2_DNS1, m_csCard2DNS1);
    DDX_Text(pDX, IDC_EDIT_CARD1_DNS2, m_csCard1DNS2);
    DDX_Text(pDX, IDC_EDIT_CARD2_DNS2, m_csCard2DNS2);
    DDX_Text(pDX, IDC_EDIT_CARD2_GATEWAY, m_csCard2GateWay);
    DDX_Text(pDX, IDC_EDIT_CARD1_GATEWAY, m_csCard1GateWay);
    DDX_Text(pDX, IDC_EDIT_CARD1_IP, m_csCard1Ip);
    DDX_Text(pDX, IDC_EDIT_CARD2_IP, m_csCard2Ip);
    DDX_Text(pDX, IDC_EDIT_CARD2_MAC, m_csCard2Mac);
    DDX_Text(pDX, IDC_EDIT_CARD1_MAC, m_csCard1Mac);
    DDX_Text(pDX, IDC_EDIT_CARD1_MASK, m_csCard1Mask);
    DDX_Text(pDX, IDC_EDIT_CARD2_MASK, m_csCard2Mask);
    DDX_Text(pDX, IDC_EDIT_CARD2_MTU, m_wCard2MTU);
    DDX_Text(pDX, IDC_EDIT_CARD1_MTU, m_wCard1MTU);
    DDX_Check(pDX, IDC_ENABLE_PPPOE, m_bEnablePPPoE);
    DDX_Text(pDX, IDC_PPP_IP, m_csPPPoEIP);
    DDX_Text(pDX, IDC_PPP_PASSWORD, m_csPPPoEPassword);
    DDX_Text(pDX, IDC_PPP_USER_NAME, m_csPPPoEUserName);
	DDX_Text(pDX, IDC_EDIT_DVR_TRANS_PORT, m_iDVRPort);
	DDX_Check(pDX, IDC_CHECK_CARD3_DHCP, m_bCard3Dhcp);
	DDX_Check(pDX, IDC_CHECK_CARD4_DHCP, m_bCard4Dhcp);
	DDX_Text(pDX, IDC_EDIT_CARD3_DNS1, m_csCard3DNS1);
	DDX_Text(pDX, IDC_EDIT_CARD3_DNS2, m_csCard3DNS2);
	DDX_Text(pDX, IDC_EDIT_CARD3_GATEWAY, m_csCard3GateWay);
	DDX_Text(pDX, IDC_EDIT_CARD3_IP, m_csCard3Ip);
	DDX_Text(pDX, IDC_EDIT_CARD3_MAC, m_csCard3Mac);
	DDX_Text(pDX, IDC_EDIT_CARD3_MASK, m_csCard3Mask);
	DDX_Text(pDX, IDC_EDIT_CARD3_MTU, m_wCard3MTU);
	DDX_Text(pDX, IDC_EDIT_CARD4_DNS1, m_csCard4DNS1);
	DDX_Text(pDX, IDC_EDIT_CARD4_DNS2, m_csCard4DNS2);
	DDX_Text(pDX, IDC_EDIT_CARD4_GATEWAY, m_csCard4GateWay);
	DDX_Text(pDX, IDC_EDIT_CARD4_IP, m_csCard4Ip);
	DDX_Text(pDX, IDC_EDIT_CARD4_MAC, m_csCard4Mac);
	DDX_Text(pDX, IDC_EDIT_CARD4_MASK, m_csCard4Mask);
	DDX_Text(pDX, IDC_EDIT_CARD4_MTU, m_wCard4MTU);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDialogMultiNetCard, CDialog)
	//{{AFX_MSG_MAP(CDialogMultiNetCard)
	ON_BN_CLICKED(IDC_BUTTON_SET_CARD2, OnButtonSetCard2)
	ON_BN_CLICKED(IDC_BUTTON_SET_CARD1, OnButtonSetCard1)
	ON_BN_CLICKED(IDC_BUTTON_NETCFG, OnButtonNetcfg)
	ON_BN_CLICKED(IDC_BUTTON_UPDATE, OnButtonUpdate)
	ON_BN_CLICKED(IDC_EXIT, OnExit)
	ON_BN_CLICKED(IDC_BUTTON_SET_CARD3, OnButtonSetCard3)
	ON_BN_CLICKED(IDC_BUTTON_SET_CARD4, OnButtonSetCard4)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDialogMultiNetCard message handlers

BOOL CDialogMultiNetCard::OnInitDialog() 
{
	CDialog::OnInitDialog();
	char szLan[128] = {0};

    memset(&m_struNetCfg, 0, sizeof(NET_DVR_NETCFG_MULTI));
    DWORD dwReturned = 0;
    m_iDeviceIndex = g_pMainDlg->GetCurDeviceIndex();
    m_lLoginID = g_struDeviceInfo[m_iDeviceIndex].lLoginID;
    if (!NET_DVR_GetDVRConfig(m_lLoginID, NET_DVR_GET_NETCFG_MULTI, 0, &m_struNetCfg, sizeof(NET_DVR_NETCFG_MULTI), &dwReturned))
    {
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_NETCFG_MULTI");
		g_StringLanType(szLan, "��ȡ�������������ʧ��", "Get multi network card para failed!");
		AfxMessageBox(szLan);
		return FALSE;
    }
	else
	{
		switch(m_struNetCfg.byNetworkCardNum)
		{
		case 1:
			GetDlgItem(IDC_BUTTON_SET_CARD2)->EnableWindow(FALSE);
			GetDlgItem(IDC_BUTTON_SET_CARD3)->EnableWindow(FALSE);
			GetDlgItem(IDC_BUTTON_SET_CARD4)->EnableWindow(FALSE);
		case 2:
			GetDlgItem(IDC_BUTTON_SET_CARD3)->EnableWindow(FALSE);
			GetDlgItem(IDC_BUTTON_SET_CARD4)->EnableWindow(FALSE);
		case 3:
			GetDlgItem(IDC_BUTTON_SET_CARD4)->EnableWindow(FALSE);
		}
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_NETCFG_MULTI");
	}
	m_bShowIpv6 = ValidIPv6((BYTE*)g_struDeviceInfo[m_iDeviceIndex].chDeviceIP);
	//2011-7-19,��ʹ��ipv6��ַ��½���豸��������ʾ��ipv6��ַ
    m_routerCard.SetCurSel(m_struNetCfg.byDefaultRoute);
	(m_bShowIpv6 && ValidIPv6(m_struNetCfg.struManageHost1IpAddr.byIPv6)) ? 	
	m_csManage1IP = m_struNetCfg.struManageHost1IpAddr.byIPv6:
	m_csManage1IP = m_struNetCfg.struManageHost1IpAddr.sIpV4;
	(m_bShowIpv6 && ValidIPv6(m_struNetCfg.struManageHost2IpAddr.byIPv6)) ? 	
	m_csManage2IP = m_struNetCfg.struManageHost2IpAddr.byIPv6:
	m_csManage2IP = m_struNetCfg.struManageHost2IpAddr.sIpV4; 
	(m_bShowIpv6 && ValidIPv6(m_struNetCfg.struAlarmHostIpAddr.byIPv6)) ? 	
	m_csAlarmIp = m_struNetCfg.struAlarmHostIpAddr.byIPv6:
	m_csAlarmIp = m_struNetCfg.struAlarmHostIpAddr.sIpV4;  
	(m_bShowIpv6 && ValidIPv6(m_struNetCfg.struMulticastIpAddr.byIPv6)) ? 	
	m_csMultIP = m_struNetCfg.struMulticastIpAddr.byIPv6:
	m_csMultIP = m_struNetCfg.struMulticastIpAddr.sIpV4;

    m_iManage1Port = m_struNetCfg.wManageHost1Port;
    m_iManage2Port = m_struNetCfg.wManageHost2Port;    
    m_iAlarmPort = m_struNetCfg.wAlarmHostIpPort;
    char cTemp[200] = {0};
    memcpy(cTemp, m_struNetCfg.byIpResolver, MAX_DOMAIN_NAME);
    m_csRelolverIP = cTemp;
    m_iResolverPort = m_struNetCfg.wIpResolverPort;
	m_iDVRPort = m_struNetCfg.wDvrPort;
    m_iHttpPort = m_struNetCfg.wHttpPortNo;   
    
	//Network Card 1
   	(m_bShowIpv6 && ValidIPv6(m_struNetCfg.struEtherNet[0].struDVRIP.byIPv6)) ? 
	m_csCard1Ip = m_struNetCfg.struEtherNet[0].struDVRIP.byIPv6 : 
	m_csCard1Ip = m_struNetCfg.struEtherNet[0].struDVRIP.sIpV4;
	(m_bShowIpv6 &&	ValidIPv6(m_struNetCfg.struEtherNet[0].struDVRIPMask.byIPv6)) ? 
	m_csCard1Mask = m_struNetCfg.struEtherNet[0].struDVRIPMask.byIPv6 : 
	m_csCard1Mask = m_struNetCfg.struEtherNet[0].struDVRIPMask.sIpV4;
	(m_bShowIpv6 &&	ValidIPv6(m_struNetCfg.struEtherNet[0].struGatewayIpAddr.byIPv6)) ? 
	m_csCard1GateWay = m_struNetCfg.struEtherNet[0].struGatewayIpAddr.byIPv6 : 
	m_csCard1GateWay = m_struNetCfg.struEtherNet[0].struGatewayIpAddr.sIpV4;
	(m_bShowIpv6 &&	ValidIPv6(m_struNetCfg.struEtherNet[0].struDnsServer1IpAddr.byIPv6)) ? 
	m_csCard1DNS1 = m_struNetCfg.struEtherNet[0].struDnsServer1IpAddr.byIPv6 : 
	m_csCard1DNS1 = m_struNetCfg.struEtherNet[0].struDnsServer1IpAddr.sIpV4;
	(m_bShowIpv6 &&	ValidIPv6(m_struNetCfg.struEtherNet[0].struDnsServer2IpAddr.byIPv6)) ? 
	m_csCard1DNS2 = m_struNetCfg.struEtherNet[0].struDnsServer2IpAddr.byIPv6 : 
	m_csCard1DNS2 = m_struNetCfg.struEtherNet[0].struDnsServer2IpAddr.sIpV4;

    m_wCard1MTU = m_struNetCfg.struEtherNet[0].wMTU;
    m_bCard1Dhcp = m_struNetCfg.struEtherNet[0].byUseDhcp;
    m_csCard1Mac.Format("%02x:%02x:%02x:%02x:%02x:%02x", m_struNetCfg.struEtherNet[0].byMACAddr[0],m_struNetCfg.struEtherNet[0].byMACAddr[1],m_struNetCfg.struEtherNet[0].byMACAddr[2],m_struNetCfg.struEtherNet[0].byMACAddr[3],m_struNetCfg.struEtherNet[0].byMACAddr[4],m_struNetCfg.struEtherNet[0].byMACAddr[5]);
    m_card1Type.SetCurSel(m_struNetCfg.struEtherNet[0].dwNetInterface -1);
   
	//Network Card 2
	(m_bShowIpv6 && ValidIPv6(m_struNetCfg.struEtherNet[1].struDVRIP.byIPv6)) ? 
	m_csCard2Ip = m_struNetCfg.struEtherNet[1].struDVRIP.byIPv6 : 
	m_csCard2Ip = m_struNetCfg.struEtherNet[1].struDVRIP.sIpV4;
	(m_bShowIpv6 &&	ValidIPv6(m_struNetCfg.struEtherNet[1].struDVRIPMask.byIPv6)) ? 
	m_csCard2Mask = m_struNetCfg.struEtherNet[1].struDVRIPMask.byIPv6 : 
	m_csCard2Mask = m_struNetCfg.struEtherNet[1].struDVRIPMask.sIpV4;
	(m_bShowIpv6 &&	ValidIPv6(m_struNetCfg.struEtherNet[1].struGatewayIpAddr.byIPv6)) ? 
	m_csCard2GateWay = m_struNetCfg.struEtherNet[1].struGatewayIpAddr.byIPv6 : 
	m_csCard2GateWay = m_struNetCfg.struEtherNet[1].struGatewayIpAddr.sIpV4;
	(m_bShowIpv6 &&	ValidIPv6(m_struNetCfg.struEtherNet[1].struDnsServer1IpAddr.byIPv6)) ? 
	m_csCard2DNS1 = m_struNetCfg.struEtherNet[1].struDnsServer1IpAddr.byIPv6 : 
	m_csCard2DNS1 = m_struNetCfg.struEtherNet[1].struDnsServer1IpAddr.sIpV4;
	(m_bShowIpv6 &&	ValidIPv6(m_struNetCfg.struEtherNet[1].struDnsServer2IpAddr.byIPv6)) ? 
	m_csCard2DNS2 = m_struNetCfg.struEtherNet[1].struDnsServer2IpAddr.byIPv6 : 
	m_csCard2DNS2 = m_struNetCfg.struEtherNet[1].struDnsServer2IpAddr.sIpV4;

    m_wCard2MTU = m_struNetCfg.struEtherNet[1].wMTU;
    m_bCard2Dhcp = m_struNetCfg.struEtherNet[1].byUseDhcp;
    m_csCard2Mac.Format("%02x:%02x:%02x:%02x:%02x:%02x", m_struNetCfg.struEtherNet[1].byMACAddr[0],m_struNetCfg.struEtherNet[1].byMACAddr[1],m_struNetCfg.struEtherNet[1].byMACAddr[2],m_struNetCfg.struEtherNet[1].byMACAddr[3],m_struNetCfg.struEtherNet[1].byMACAddr[4],m_struNetCfg.struEtherNet[1].byMACAddr[5]);
    m_card2Type.SetCurSel(m_struNetCfg.struEtherNet[1].dwNetInterface -1);

	//Network Card 3
    (m_bShowIpv6 && ValidIPv6(m_struNetCfg.struEtherNet[2].struDVRIP.byIPv6)) ? 
	m_csCard3Ip = m_struNetCfg.struEtherNet[2].struDVRIP.byIPv6 : 
	m_csCard3Ip = m_struNetCfg.struEtherNet[2].struDVRIP.sIpV4;
	(m_bShowIpv6 &&	ValidIPv6(m_struNetCfg.struEtherNet[2].struDVRIPMask.byIPv6)) ? 
	m_csCard3Mask = m_struNetCfg.struEtherNet[2].struDVRIPMask.byIPv6 : 
	m_csCard3Mask = m_struNetCfg.struEtherNet[2].struDVRIPMask.sIpV4;
	(m_bShowIpv6 &&	ValidIPv6(m_struNetCfg.struEtherNet[2].struGatewayIpAddr.byIPv6)) ? 
	m_csCard3GateWay = m_struNetCfg.struEtherNet[2].struGatewayIpAddr.byIPv6 : 
	m_csCard3GateWay = m_struNetCfg.struEtherNet[2].struGatewayIpAddr.sIpV4;
	(m_bShowIpv6 &&	ValidIPv6(m_struNetCfg.struEtherNet[2].struDnsServer1IpAddr.byIPv6)) ? 
	m_csCard3DNS1 = m_struNetCfg.struEtherNet[2].struDnsServer1IpAddr.byIPv6 : 
	m_csCard3DNS1 = m_struNetCfg.struEtherNet[2].struDnsServer1IpAddr.sIpV4;
	(m_bShowIpv6 &&	ValidIPv6(m_struNetCfg.struEtherNet[2].struDnsServer2IpAddr.byIPv6)) ? 
	m_csCard3DNS2 = m_struNetCfg.struEtherNet[2].struDnsServer2IpAddr.byIPv6 : 
	m_csCard3DNS2 = m_struNetCfg.struEtherNet[2].struDnsServer2IpAddr.sIpV4;

    m_wCard3MTU = m_struNetCfg.struEtherNet[2].wMTU;
    m_bCard3Dhcp = m_struNetCfg.struEtherNet[2].byUseDhcp;
    m_csCard3Mac.Format("%02x:%02x:%02x:%02x:%02x:%02x", m_struNetCfg.struEtherNet[2].byMACAddr[0],m_struNetCfg.struEtherNet[2].byMACAddr[1],m_struNetCfg.struEtherNet[2].byMACAddr[2],m_struNetCfg.struEtherNet[2].byMACAddr[3],m_struNetCfg.struEtherNet[2].byMACAddr[4],m_struNetCfg.struEtherNet[2].byMACAddr[5]);
    m_card3Type.SetCurSel(m_struNetCfg.struEtherNet[2].dwNetInterface -1);

	//Network Card 4
	(m_bShowIpv6 && ValidIPv6(m_struNetCfg.struEtherNet[3].struDVRIP.byIPv6)) ? 
	m_csCard4Ip = m_struNetCfg.struEtherNet[3].struDVRIP.byIPv6 : 
	m_csCard4Ip = m_struNetCfg.struEtherNet[3].struDVRIP.sIpV4;
	(m_bShowIpv6 &&	ValidIPv6(m_struNetCfg.struEtherNet[3].struDVRIPMask.byIPv6)) ? 
	m_csCard4Mask = m_struNetCfg.struEtherNet[3].struDVRIPMask.byIPv6 : 
	m_csCard4Mask = m_struNetCfg.struEtherNet[3].struDVRIPMask.sIpV4;
	(m_bShowIpv6 &&	ValidIPv6(m_struNetCfg.struEtherNet[3].struGatewayIpAddr.byIPv6)) ? 
	m_csCard4GateWay = m_struNetCfg.struEtherNet[3].struGatewayIpAddr.byIPv6 : 
	m_csCard4GateWay = m_struNetCfg.struEtherNet[3].struGatewayIpAddr.sIpV4;
	(m_bShowIpv6 &&	ValidIPv6(m_struNetCfg.struEtherNet[3].struDnsServer1IpAddr.byIPv6)) ? 
	m_csCard4DNS1 = m_struNetCfg.struEtherNet[3].struDnsServer1IpAddr.byIPv6 : 
	m_csCard4DNS1 = m_struNetCfg.struEtherNet[3].struDnsServer1IpAddr.sIpV4;
	(m_bShowIpv6 &&	ValidIPv6(m_struNetCfg.struEtherNet[3].struDnsServer2IpAddr.byIPv6)) ? 
	m_csCard4DNS2 = m_struNetCfg.struEtherNet[3].struDnsServer2IpAddr.byIPv6 : 
	m_csCard4DNS2 = m_struNetCfg.struEtherNet[3].struDnsServer2IpAddr.sIpV4;

    m_wCard4MTU = m_struNetCfg.struEtherNet[3].wMTU;
    m_bCard4Dhcp = m_struNetCfg.struEtherNet[3].byUseDhcp;
    m_csCard4Mac.Format("%02x:%02x:%02x:%02x:%02x:%02x", m_struNetCfg.struEtherNet[3].byMACAddr[0],m_struNetCfg.struEtherNet[3].byMACAddr[1],m_struNetCfg.struEtherNet[3].byMACAddr[2],m_struNetCfg.struEtherNet[3].byMACAddr[3],m_struNetCfg.struEtherNet[3].byMACAddr[4],m_struNetCfg.struEtherNet[3].byMACAddr[5]);
    m_card4Type.SetCurSel(m_struNetCfg.struEtherNet[3].dwNetInterface -1);
  
	//PPPoE
	if (m_struNetCfg.struPPPoE.dwPPPOE == 1)
    {
		m_bEnablePPPoE = TRUE;
    }
    else
    {
		m_bEnablePPPoE = FALSE;
    }
	char csPPPoeName[NAME_LEN+1] = {0};
	memcpy(csPPPoeName, m_struNetCfg.struPPPoE.sPPPoEUser, NAME_LEN);
    m_csPPPoEUserName.Format("%s", csPPPoeName);
    m_csPPPoEPassword.Format("%s",  m_struNetCfg.struPPPoE.sPPPoEPassword);
    if (m_bShowIpv6 && ValidIPv6(m_struNetCfg.struPPPoE.struPPPoEIP.byIPv6))
	{
		m_csPPPoEIP.Format("%s",  m_struNetCfg.struPPPoE.struPPPoEIP.byIPv6);
	}
	else
	{
		m_csPPPoEIP.Format("%s",  m_struNetCfg.struPPPoE.struPPPoEIP.sIpV4);
	}
    
    UpdateData(FALSE);
    return TRUE;  
}

void CDialogMultiNetCard::OnButtonSetCard2() 
{
	UpdateData(TRUE);
    (m_bShowIpv6 && ValidIPv6((unsigned char*)m_csCard2Ip.GetBuffer(m_csCard2Ip.GetLength()))) ?
	memcpy(m_struNetCfg.struEtherNet[1].struDVRIP.byIPv6, m_csCard2Ip,128):
	memcpy(m_struNetCfg.struEtherNet[1].struDVRIP.sIpV4, m_csCard2Ip,16);
	m_csCard2Ip.ReleaseBuffer();
	(m_bShowIpv6 && ValidIPv6((unsigned char*)m_csCard2Mask.GetBuffer(m_csCard2Mask.GetLength()))) ?
	memcpy(m_struNetCfg.struEtherNet[1].struDVRIPMask.byIPv6, m_csCard2Mask,128):
	memcpy(m_struNetCfg.struEtherNet[1].struDVRIPMask.sIpV4, m_csCard2Mask,16);
	m_csCard2Mask.ReleaseBuffer();
	(m_bShowIpv6 && ValidIPv6((unsigned char*)m_csCard2GateWay.GetBuffer(m_csCard2GateWay.GetLength()))) ?
	memcpy(m_struNetCfg.struEtherNet[1].struGatewayIpAddr.byIPv6, m_csCard2GateWay,128):
	memcpy(m_struNetCfg.struEtherNet[1].struGatewayIpAddr.sIpV4, m_csCard2GateWay,16);
	m_csCard2GateWay.ReleaseBuffer();
	(m_bShowIpv6 && ValidIPv6((unsigned char*)m_csCard2DNS1.GetBuffer(m_csCard2DNS1.GetLength()))) ?
	memcpy(m_struNetCfg.struEtherNet[1].struDnsServer1IpAddr.byIPv6, m_csCard2DNS1,128):
	memcpy(m_struNetCfg.struEtherNet[1].struDnsServer1IpAddr.sIpV4, m_csCard2DNS1,16);
	m_csCard2DNS1.ReleaseBuffer();
	(m_bShowIpv6 && ValidIPv6((unsigned char*)m_csCard2DNS2.GetBuffer(m_csCard2DNS2.GetLength()))) ?
	memcpy(m_struNetCfg.struEtherNet[1].struDnsServer2IpAddr.byIPv6, m_csCard2DNS2,128):
	memcpy(m_struNetCfg.struEtherNet[1].struDnsServer2IpAddr.sIpV4, m_csCard2DNS2,16);
	m_csCard2DNS2.ReleaseBuffer();
    
    m_struNetCfg.struEtherNet[1].wMTU = (WORD)m_wCard2MTU;
    if (m_bCard2Dhcp)
    {
        m_struNetCfg.struEtherNet[1].byUseDhcp = 1;
    }
    else
    {
        m_struNetCfg.struEtherNet[1].byUseDhcp = 0;
    }
    m_struNetCfg.struEtherNet[1].dwNetInterface = m_card2Type.GetCurSel()+1;
}

void CDialogMultiNetCard::OnButtonSetCard1() 
{
	UpdateData(TRUE);
    (m_bShowIpv6 && ValidIPv6((unsigned char*)m_csCard1Ip.GetBuffer(m_csCard1Ip.GetLength()))) ?
	memcpy(m_struNetCfg.struEtherNet[0].struDVRIP.byIPv6, m_csCard1Ip,128):
	memcpy(m_struNetCfg.struEtherNet[0].struDVRIP.sIpV4, m_csCard1Ip,16);
	m_csCard1Ip.ReleaseBuffer();
	(m_bShowIpv6 && ValidIPv6((unsigned char*)m_csCard1Mask.GetBuffer(m_csCard1Mask.GetLength()))) ?
	memcpy(m_struNetCfg.struEtherNet[0].struDVRIPMask.byIPv6, m_csCard1Mask,128):
	memcpy(m_struNetCfg.struEtherNet[0].struDVRIPMask.sIpV4, m_csCard1Mask,16);
	m_csCard1Mask.ReleaseBuffer();
	(m_bShowIpv6 && ValidIPv6((unsigned char*)m_csCard1GateWay.GetBuffer(m_csCard1GateWay.GetLength()))) ?
	memcpy(m_struNetCfg.struEtherNet[0].struGatewayIpAddr.byIPv6, m_csCard1GateWay,128):
	memcpy(m_struNetCfg.struEtherNet[0].struGatewayIpAddr.sIpV4, m_csCard1GateWay,16);
	m_csCard1GateWay.ReleaseBuffer();
	(m_bShowIpv6 && ValidIPv6((unsigned char*)m_csCard1DNS1.GetBuffer(m_csCard1DNS1.GetLength()))) ?
	memcpy(m_struNetCfg.struEtherNet[0].struDnsServer1IpAddr.byIPv6, m_csCard1DNS1,128):
	memcpy(m_struNetCfg.struEtherNet[0].struDnsServer1IpAddr.sIpV4, m_csCard1DNS1,16);
	m_csCard1DNS1.ReleaseBuffer();
	(m_bShowIpv6 && ValidIPv6((unsigned char*)m_csCard1DNS2.GetBuffer(m_csCard1DNS2.GetLength()))) ?
	memcpy(m_struNetCfg.struEtherNet[0].struDnsServer2IpAddr.byIPv6, m_csCard1DNS2,128):
	memcpy(m_struNetCfg.struEtherNet[0].struDnsServer2IpAddr.sIpV4, m_csCard1DNS2,16);
	m_csCard1DNS2.ReleaseBuffer();
    
    m_struNetCfg.struEtherNet[0].wMTU = (WORD)m_wCard1MTU;
    if (m_bCard1Dhcp)
    {
        m_struNetCfg.struEtherNet[0].byUseDhcp = 1;
    }
    else
    {
        m_struNetCfg.struEtherNet[0].byUseDhcp = 0;
    }    
    m_struNetCfg.struEtherNet[0].dwNetInterface = m_card1Type.GetCurSel()+1;
}

void CDialogMultiNetCard::OnButtonNetcfg() 
{
	UpdateData(TRUE);
	char szLan[128] = {0};
    
    m_struNetCfg.byDefaultRoute = m_routerCard.GetCurSel();
	(m_bShowIpv6 && ValidIPv6((unsigned char*)m_csManage1IP.GetBuffer(m_csManage1IP.GetLength()))) ?
	memcpy(m_struNetCfg.struManageHost1IpAddr.byIPv6, m_csManage1IP, 128) :
	memcpy(m_struNetCfg.struManageHost1IpAddr.sIpV4, m_csManage1IP, 16); 
	m_csManage1IP.ReleaseBuffer();
	(m_bShowIpv6 && ValidIPv6((unsigned char*)m_csManage2IP.GetBuffer(m_csManage2IP.GetLength()))) ?
	memcpy(m_struNetCfg.struManageHost2IpAddr.byIPv6, m_csManage2IP, 128):    
    memcpy(m_struNetCfg.struManageHost2IpAddr.sIpV4, m_csManage2IP, 16);
	m_csManage2IP.ReleaseBuffer();
    m_struNetCfg.wManageHost1Port = (WORD)m_iManage1Port;
    m_struNetCfg.wManageHost2Port = (WORD)m_iManage2Port;
	(m_bShowIpv6 && ValidIPv6((unsigned char*)m_csAlarmIp.GetBuffer(m_csAlarmIp.GetLength()))) ?
	memcpy(m_struNetCfg.struAlarmHostIpAddr.byIPv6, m_csAlarmIp, 128):    
    memcpy(m_struNetCfg.struAlarmHostIpAddr.sIpV4, m_csAlarmIp, 16);
	m_csAlarmIp.ReleaseBuffer();
    m_struNetCfg.wAlarmHostIpPort = (WORD)m_iAlarmPort;
    memcpy(m_struNetCfg.byIpResolver, m_csRelolverIP, MAX_DOMAIN_NAME);
    m_struNetCfg.wIpResolverPort = (WORD)m_iResolverPort;
    m_struNetCfg.wHttpPortNo = (WORD)m_iHttpPort;
    (m_bShowIpv6 && ValidIPv6((unsigned char*)m_csMultIP.GetBuffer(m_csMultIP.GetLength()))) ?
	memcpy(m_struNetCfg.struMulticastIpAddr.byIPv6, m_csMultIP, 128):    
    memcpy(m_struNetCfg.struMulticastIpAddr.sIpV4, m_csMultIP, 16);
	m_csMultIP.ReleaseBuffer();
	
    m_struNetCfg.struPPPoE.dwPPPOE = m_bEnablePPPoE;
    memcpy(m_struNetCfg.struPPPoE.sPPPoEUser, m_csPPPoEUserName, NAME_LEN);
    memcpy(m_struNetCfg.struPPPoE.sPPPoEPassword, m_csPPPoEPassword, PASSWD_LEN);
	(m_bShowIpv6 && ValidIPv6((unsigned char*)m_csPPPoEIP.GetBuffer(m_csPPPoEIP.GetLength()))) ?
	memcpy(m_struNetCfg.struPPPoE.struPPPoEIP.byIPv6, m_csPPPoEIP, 128):    
    memcpy(m_struNetCfg.struPPPoE.struPPPoEIP.sIpV4, m_csPPPoEIP, 16);
	m_csPPPoEIP.ReleaseBuffer();

	m_struNetCfg.wDvrPort = m_iDVRPort;

    if (!NET_DVR_SetDVRConfig(m_lLoginID, NET_DVR_SET_NETCFG_MULTI, 0, &(m_struNetCfg), sizeof(NET_DVR_NETCFG_MULTI)))
    {
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_NETCFG_MULTI");
		g_StringLanType(szLan, "���ö������������ʧ��", "Set multi network card para failed!");
		AfxMessageBox(szLan);
    }
	else
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_NETCFG_MULTI");
		g_StringLanType(szLan, "���ö�������������ɹ�", "Set multi network card para succeed!");
		AfxMessageBox(szLan);
	}
}

void CDialogMultiNetCard::OnButtonUpdate() 
{
	char szLan[128] = {0};

	memset(&m_struNetCfg, 0, sizeof(NET_DVR_NETCFG_MULTI));
    DWORD dwReturned = 0;
    m_iDeviceIndex = g_pMainDlg->GetCurDeviceIndex();
    m_lLoginID = g_struDeviceInfo[m_iDeviceIndex].lLoginID;
	if (!NET_DVR_GetDVRConfig(m_lLoginID, NET_DVR_GET_NETCFG_MULTI, 0, &m_struNetCfg, sizeof(NET_DVR_NETCFG_MULTI), &dwReturned))
    {
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_NETCFG_MULTI");
		g_StringLanType(szLan, "��ȡ�������������ʧ��", "Get multi network card para failed!");
		AfxMessageBox(szLan);
	}
	else
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_NETCFG_MULTI");
	}

    m_routerCard.SetCurSel(m_struNetCfg.byDefaultRoute);
	(m_bShowIpv6 && ValidIPv6(m_struNetCfg.struManageHost1IpAddr.byIPv6)) ? 	
	m_csManage1IP = m_struNetCfg.struManageHost1IpAddr.byIPv6:
	m_csManage1IP = m_struNetCfg.struManageHost1IpAddr.sIpV4;
	(m_bShowIpv6 && ValidIPv6(m_struNetCfg.struManageHost2IpAddr.byIPv6)) ? 	
	m_csManage2IP = m_struNetCfg.struManageHost2IpAddr.byIPv6:
	m_csManage2IP = m_struNetCfg.struManageHost2IpAddr.sIpV4; 
	(m_bShowIpv6 && ValidIPv6(m_struNetCfg.struAlarmHostIpAddr.byIPv6)) ? 	
	m_csAlarmIp = m_struNetCfg.struAlarmHostIpAddr.byIPv6:
	m_csAlarmIp = m_struNetCfg.struAlarmHostIpAddr.sIpV4;  
	(m_bShowIpv6 && ValidIPv6(m_struNetCfg.struMulticastIpAddr.byIPv6)) ? 	
	m_csMultIP = m_struNetCfg.struMulticastIpAddr.byIPv6:
	m_csMultIP = m_struNetCfg.struMulticastIpAddr.sIpV4;

    m_iManage1Port = m_struNetCfg.wManageHost1Port;
    m_iManage2Port = m_struNetCfg.wManageHost2Port;
	m_iDVRPort = m_struNetCfg.wDvrPort;    
    m_iAlarmPort = m_struNetCfg.wAlarmHostIpPort;
    char cTemp[200] = {0};
    memcpy(cTemp, m_struNetCfg.byIpResolver, MAX_DOMAIN_NAME);
    m_csRelolverIP = cTemp;
    m_iResolverPort = m_struNetCfg.wIpResolverPort;
    m_iHttpPort = m_struNetCfg.wHttpPortNo;   
   
	//Network Card 1
    (m_bShowIpv6 && ValidIPv6(m_struNetCfg.struEtherNet[0].struDVRIP.byIPv6)) ? 
	m_csCard1Ip = m_struNetCfg.struEtherNet[0].struDVRIP.byIPv6 : 
	m_csCard1Ip = m_struNetCfg.struEtherNet[0].struDVRIP.sIpV4;
	(m_bShowIpv6 &&	ValidIPv6(m_struNetCfg.struEtherNet[0].struDVRIPMask.byIPv6)) ? 
	m_csCard1Mask = m_struNetCfg.struEtherNet[0].struDVRIPMask.byIPv6 : 
	m_csCard1Mask = m_struNetCfg.struEtherNet[0].struDVRIPMask.sIpV4;
	(m_bShowIpv6 &&	ValidIPv6(m_struNetCfg.struEtherNet[0].struGatewayIpAddr.byIPv6)) ? 
	m_csCard1GateWay = m_struNetCfg.struEtherNet[0].struGatewayIpAddr.byIPv6 : 
	m_csCard1GateWay = m_struNetCfg.struEtherNet[0].struGatewayIpAddr.sIpV4;
	(m_bShowIpv6 &&	ValidIPv6(m_struNetCfg.struEtherNet[0].struDnsServer1IpAddr.byIPv6)) ? 
	m_csCard1DNS1 = m_struNetCfg.struEtherNet[0].struDnsServer1IpAddr.byIPv6 : 
	m_csCard1DNS1 = m_struNetCfg.struEtherNet[0].struDnsServer1IpAddr.sIpV4;
	(m_bShowIpv6 &&	ValidIPv6(m_struNetCfg.struEtherNet[0].struDnsServer2IpAddr.byIPv6)) ? 
	m_csCard1DNS2 = m_struNetCfg.struEtherNet[0].struDnsServer2IpAddr.byIPv6 : 
	m_csCard1DNS2 = m_struNetCfg.struEtherNet[0].struDnsServer2IpAddr.sIpV4;	

    m_wCard1MTU = m_struNetCfg.struEtherNet[0].wMTU;
    m_bCard1Dhcp = m_struNetCfg.struEtherNet[0].byUseDhcp;
    m_csCard1Mac.Format("%02x:%02x:%02x:%02x:%02x:%02x", m_struNetCfg.struEtherNet[0].byMACAddr[0],m_struNetCfg.struEtherNet[0].byMACAddr[1],m_struNetCfg.struEtherNet[0].byMACAddr[2],m_struNetCfg.struEtherNet[0].byMACAddr[3],m_struNetCfg.struEtherNet[0].byMACAddr[4],m_struNetCfg.struEtherNet[0].byMACAddr[5]);
    m_card1Type.SetCurSel(m_struNetCfg.struEtherNet[0].dwNetInterface -1);
    
	//Network Card 2
   	(m_bShowIpv6 && ValidIPv6(m_struNetCfg.struEtherNet[1].struDVRIP.byIPv6)) ? 
	m_csCard2Ip = m_struNetCfg.struEtherNet[1].struDVRIP.byIPv6 : 
	m_csCard2Ip = m_struNetCfg.struEtherNet[1].struDVRIP.sIpV4;
	(m_bShowIpv6 &&	ValidIPv6(m_struNetCfg.struEtherNet[1].struDVRIPMask.byIPv6)) ? 
	m_csCard2Mask = m_struNetCfg.struEtherNet[1].struDVRIPMask.byIPv6 : 
	m_csCard2Mask = m_struNetCfg.struEtherNet[1].struDVRIPMask.sIpV4;
	(m_bShowIpv6 &&	ValidIPv6(m_struNetCfg.struEtherNet[1].struGatewayIpAddr.byIPv6)) ? 
	m_csCard2GateWay = m_struNetCfg.struEtherNet[1].struGatewayIpAddr.byIPv6 : 
	m_csCard2GateWay = m_struNetCfg.struEtherNet[1].struGatewayIpAddr.sIpV4;
	(m_bShowIpv6 &&	ValidIPv6(m_struNetCfg.struEtherNet[1].struDnsServer1IpAddr.byIPv6)) ? 
	m_csCard2DNS1 = m_struNetCfg.struEtherNet[1].struDnsServer1IpAddr.byIPv6 : 
	m_csCard2DNS1 = m_struNetCfg.struEtherNet[1].struDnsServer1IpAddr.sIpV4;
	(m_bShowIpv6 &&	ValidIPv6(m_struNetCfg.struEtherNet[1].struDnsServer2IpAddr.byIPv6)) ? 
	m_csCard2DNS2 = m_struNetCfg.struEtherNet[1].struDnsServer2IpAddr.byIPv6 : 
	m_csCard2DNS2 = m_struNetCfg.struEtherNet[1].struDnsServer2IpAddr.sIpV4;

    m_wCard2MTU = m_struNetCfg.struEtherNet[1].wMTU;
    m_bCard2Dhcp = m_struNetCfg.struEtherNet[1].byUseDhcp;
    m_csCard2Mac.Format("%02x:%02x:%02x:%02x:%02x:%02x", m_struNetCfg.struEtherNet[1].byMACAddr[0],m_struNetCfg.struEtherNet[1].byMACAddr[1],m_struNetCfg.struEtherNet[1].byMACAddr[2],m_struNetCfg.struEtherNet[1].byMACAddr[3],m_struNetCfg.struEtherNet[1].byMACAddr[4],m_struNetCfg.struEtherNet[1].byMACAddr[5]);
    m_card2Type.SetCurSel(m_struNetCfg.struEtherNet[1].dwNetInterface -1);

	//Network Card 3
	(m_bShowIpv6 && ValidIPv6(m_struNetCfg.struEtherNet[2].struDVRIP.byIPv6)) ? 
	m_csCard3Ip = m_struNetCfg.struEtherNet[2].struDVRIP.byIPv6 : 
	m_csCard3Ip = m_struNetCfg.struEtherNet[2].struDVRIP.sIpV4;
	(m_bShowIpv6 &&	ValidIPv6(m_struNetCfg.struEtherNet[2].struDVRIPMask.byIPv6)) ? 
	m_csCard3Mask = m_struNetCfg.struEtherNet[2].struDVRIPMask.byIPv6 : 
	m_csCard3Mask = m_struNetCfg.struEtherNet[2].struDVRIPMask.sIpV4;
	(m_bShowIpv6 &&	ValidIPv6(m_struNetCfg.struEtherNet[2].struGatewayIpAddr.byIPv6)) ? 
	m_csCard3GateWay = m_struNetCfg.struEtherNet[2].struGatewayIpAddr.byIPv6 : 
	m_csCard3GateWay = m_struNetCfg.struEtherNet[2].struGatewayIpAddr.sIpV4;
	(m_bShowIpv6 &&	ValidIPv6(m_struNetCfg.struEtherNet[2].struDnsServer1IpAddr.byIPv6)) ? 
	m_csCard3DNS1 = m_struNetCfg.struEtherNet[2].struDnsServer1IpAddr.byIPv6 : 
	m_csCard3DNS1 = m_struNetCfg.struEtherNet[2].struDnsServer1IpAddr.sIpV4;
	(m_bShowIpv6 &&	ValidIPv6(m_struNetCfg.struEtherNet[2].struDnsServer2IpAddr.byIPv6)) ? 
	m_csCard3DNS2 = m_struNetCfg.struEtherNet[2].struDnsServer2IpAddr.byIPv6 : 
	m_csCard3DNS2 = m_struNetCfg.struEtherNet[2].struDnsServer2IpAddr.sIpV4;

    m_wCard3MTU = m_struNetCfg.struEtherNet[2].wMTU;
    m_bCard3Dhcp = m_struNetCfg.struEtherNet[2].byUseDhcp;
    m_csCard3Mac.Format("%02x:%02x:%02x:%02x:%02x:%02x", m_struNetCfg.struEtherNet[2].byMACAddr[0],m_struNetCfg.struEtherNet[2].byMACAddr[1],m_struNetCfg.struEtherNet[2].byMACAddr[2],m_struNetCfg.struEtherNet[2].byMACAddr[3],m_struNetCfg.struEtherNet[2].byMACAddr[4],m_struNetCfg.struEtherNet[2].byMACAddr[5]);
    m_card3Type.SetCurSel(m_struNetCfg.struEtherNet[2].dwNetInterface -1);
  
	//Network Card 4
   	(m_bShowIpv6 && ValidIPv6(m_struNetCfg.struEtherNet[3].struDVRIP.byIPv6)) ? 
	m_csCard4Ip = m_struNetCfg.struEtherNet[3].struDVRIP.byIPv6 : 
	m_csCard4Ip = m_struNetCfg.struEtherNet[3].struDVRIP.sIpV4;
	(m_bShowIpv6 &&	ValidIPv6(m_struNetCfg.struEtherNet[3].struDVRIPMask.byIPv6)) ? 
	m_csCard4Mask = m_struNetCfg.struEtherNet[3].struDVRIPMask.byIPv6 : 
	m_csCard4Mask = m_struNetCfg.struEtherNet[3].struDVRIPMask.sIpV4;
	(m_bShowIpv6 &&	ValidIPv6(m_struNetCfg.struEtherNet[3].struGatewayIpAddr.byIPv6)) ? 
	m_csCard4GateWay = m_struNetCfg.struEtherNet[3].struGatewayIpAddr.byIPv6 : 
	m_csCard4GateWay = m_struNetCfg.struEtherNet[3].struGatewayIpAddr.sIpV4;
	(m_bShowIpv6 &&	ValidIPv6(m_struNetCfg.struEtherNet[3].struDnsServer1IpAddr.byIPv6)) ? 
	m_csCard4DNS1 = m_struNetCfg.struEtherNet[3].struDnsServer1IpAddr.byIPv6 : 
	m_csCard4DNS1 = m_struNetCfg.struEtherNet[3].struDnsServer1IpAddr.sIpV4;
	(m_bShowIpv6 &&	ValidIPv6(m_struNetCfg.struEtherNet[3].struDnsServer2IpAddr.byIPv6)) ? 
	m_csCard4DNS2 = m_struNetCfg.struEtherNet[3].struDnsServer2IpAddr.byIPv6 : 
	m_csCard4DNS2 = m_struNetCfg.struEtherNet[3].struDnsServer2IpAddr.sIpV4;

    m_wCard4MTU = m_struNetCfg.struEtherNet[3].wMTU;
    m_bCard4Dhcp = m_struNetCfg.struEtherNet[3].byUseDhcp;
    m_csCard4Mac.Format("%02x:%02x:%02x:%02x:%02x:%02x", m_struNetCfg.struEtherNet[3].byMACAddr[0],m_struNetCfg.struEtherNet[3].byMACAddr[1],m_struNetCfg.struEtherNet[3].byMACAddr[2],m_struNetCfg.struEtherNet[3].byMACAddr[3],m_struNetCfg.struEtherNet[3].byMACAddr[4],m_struNetCfg.struEtherNet[3].byMACAddr[5]);
    m_card4Type.SetCurSel(m_struNetCfg.struEtherNet[3].dwNetInterface -1);

	//PPPoe
	if (m_struNetCfg.struPPPoE.dwPPPOE == 1)
    {
		m_bEnablePPPoE = TRUE;
    }
    else
    {
		m_bEnablePPPoE = FALSE;
    }
    m_csPPPoEUserName.Format("%s", m_struNetCfg.struPPPoE.sPPPoEUser);
    m_csPPPoEPassword.Format("%s",  m_struNetCfg.struPPPoE.sPPPoEPassword);
    if (m_bShowIpv6 && ValidIPv6(m_struNetCfg.struPPPoE.struPPPoEIP.byIPv6))
	{
		m_csPPPoEIP.Format("%s",  m_struNetCfg.struPPPoE.struPPPoEIP.byIPv6);
	} 
	else
	{
		m_csPPPoEIP.Format("%s",  m_struNetCfg.struPPPoE.struPPPoEIP.sIpV4);
	}    
    
    UpdateData(FALSE);
}

void CDialogMultiNetCard::OnExit() 
{
	CDialog::OnCancel();	
}

void CDialogMultiNetCard::OnButtonSetCard3() 
{
	UpdateData(TRUE);
    (m_bShowIpv6 && ValidIPv6((unsigned char*)m_csCard3Ip.GetBuffer(m_csCard3Ip.GetLength()))) ?
	memcpy(m_struNetCfg.struEtherNet[2].struDVRIP.byIPv6, m_csCard3Ip,128):
	memcpy(m_struNetCfg.struEtherNet[2].struDVRIP.sIpV4, m_csCard3Ip,16);
	m_csCard3Ip.ReleaseBuffer();
	(m_bShowIpv6 && ValidIPv6((unsigned char*)m_csCard3Mask.GetBuffer(m_csCard3Mask.GetLength()))) ?
	memcpy(m_struNetCfg.struEtherNet[2].struDVRIPMask.byIPv6, m_csCard3Mask,128):
	memcpy(m_struNetCfg.struEtherNet[2].struDVRIPMask.sIpV4, m_csCard3Mask,16);
	m_csCard3Mask.ReleaseBuffer();
	(m_bShowIpv6 && ValidIPv6((unsigned char*)m_csCard3GateWay.GetBuffer(m_csCard3GateWay.GetLength()))) ?
	memcpy(m_struNetCfg.struEtherNet[2].struGatewayIpAddr.byIPv6, m_csCard3GateWay,128):
	memcpy(m_struNetCfg.struEtherNet[2].struGatewayIpAddr.sIpV4, m_csCard3GateWay,16);
	m_csCard3GateWay.ReleaseBuffer();
	(m_bShowIpv6 && ValidIPv6((unsigned char*)m_csCard3DNS1.GetBuffer(m_csCard3DNS1.GetLength()))) ?
	memcpy(m_struNetCfg.struEtherNet[2].struDnsServer1IpAddr.byIPv6, m_csCard3DNS1,128):
	memcpy(m_struNetCfg.struEtherNet[2].struDnsServer1IpAddr.sIpV4, m_csCard3DNS1,16);
	m_csCard3DNS1.ReleaseBuffer();
	(m_bShowIpv6 && ValidIPv6((unsigned char*)m_csCard3DNS2.GetBuffer(m_csCard3DNS2.GetLength()))) ?
	memcpy(m_struNetCfg.struEtherNet[2].struDnsServer2IpAddr.byIPv6, m_csCard3DNS2,128):
	memcpy(m_struNetCfg.struEtherNet[2].struDnsServer2IpAddr.sIpV4, m_csCard3DNS2,16);
	m_csCard3DNS2.ReleaseBuffer();
    
    m_struNetCfg.struEtherNet[2].wMTU = (WORD)m_wCard3MTU;
    if (m_bCard3Dhcp)
    {
        m_struNetCfg.struEtherNet[2].byUseDhcp = 1;
    }
    else
    {
        m_struNetCfg.struEtherNet[2].byUseDhcp = 0;
    }
    m_struNetCfg.struEtherNet[2].dwNetInterface = m_card1Type.GetCurSel()+1;
}

void CDialogMultiNetCard::OnButtonSetCard4() 
{
	UpdateData(TRUE);
	(m_bShowIpv6 && ValidIPv6((unsigned char*)m_csCard4Ip.GetBuffer(m_csCard4Ip.GetLength()))) ?
	memcpy(m_struNetCfg.struEtherNet[3].struDVRIP.byIPv6, m_csCard4Ip,128):
	memcpy(m_struNetCfg.struEtherNet[3].struDVRIP.sIpV4, m_csCard4Ip,16);
	m_csCard4Ip.ReleaseBuffer();
	(m_bShowIpv6 && ValidIPv6((unsigned char*)m_csCard4Mask.GetBuffer(m_csCard4Mask.GetLength()))) ?
	memcpy(m_struNetCfg.struEtherNet[3].struDVRIPMask.byIPv6, m_csCard4Mask,128):
	memcpy(m_struNetCfg.struEtherNet[3].struDVRIPMask.sIpV4, m_csCard4Mask,16);
	m_csCard4Mask.ReleaseBuffer();
	(m_bShowIpv6 && ValidIPv6((unsigned char*)m_csCard4GateWay.GetBuffer(m_csCard4GateWay.GetLength()))) ?
	memcpy(m_struNetCfg.struEtherNet[3].struGatewayIpAddr.byIPv6, m_csCard4GateWay,128):
	memcpy(m_struNetCfg.struEtherNet[3].struGatewayIpAddr.sIpV4, m_csCard4GateWay,16);
	m_csCard4GateWay.ReleaseBuffer();
	(m_bShowIpv6 && ValidIPv6((unsigned char*)m_csCard4DNS1.GetBuffer(m_csCard4DNS1.GetLength()))) ?
	memcpy(m_struNetCfg.struEtherNet[3].struDnsServer1IpAddr.byIPv6, m_csCard4DNS1,128):
	memcpy(m_struNetCfg.struEtherNet[3].struDnsServer1IpAddr.sIpV4, m_csCard4DNS1,16);
	m_csCard4DNS1.ReleaseBuffer();
	(m_bShowIpv6 && ValidIPv6((unsigned char*)m_csCard4DNS2.GetBuffer(m_csCard4DNS2.GetLength()))) ?
	memcpy(m_struNetCfg.struEtherNet[3].struDnsServer2IpAddr.byIPv6, m_csCard4DNS2,128):
	memcpy(m_struNetCfg.struEtherNet[3].struDnsServer2IpAddr.sIpV4, m_csCard4DNS2,16);
	m_csCard4DNS2.ReleaseBuffer();
    
    m_struNetCfg.struEtherNet[3].wMTU = (WORD)m_wCard4MTU;
    if (m_bCard4Dhcp)
    {
        m_struNetCfg.struEtherNet[3].byUseDhcp = 1;
    }
    else
    {
        m_struNetCfg.struEtherNet[3].byUseDhcp = 0;
    }
    m_struNetCfg.struEtherNet[3].dwNetInterface = m_card4Type.GetCurSel()+1;
}

inline BOOL CDialogMultiNetCard::ValidIPv6(BYTE *ip)
{
	if (strlen((char *)ip) > 2 && strchr((char *)ip, ':') != NULL)
	{
		return TRUE;
	}
	return FALSE;
}