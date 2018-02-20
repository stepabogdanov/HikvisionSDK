/**********************************************************
FileName:    DlgRemoteIPAccess.cpp
Description:       
Date:        2008/06/03
Note: 		<Global>struct, macro refer to GeneralDef.h, global variants and API refer to ClientDemo.cpp   
Modification History:      
    <version> <time>         <desc>
    <1.0    > <2008/06/03>       <created>
***********************************************************/

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgRemoteIPAccess.h"
#include "DlgQuickAddIpc.h"
#include "DlgCuntomProtocal.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/*********************************************************
  Function:	GetDeviceAddress, eg:GetDeviceAddress(&struIPParaCfg.struDevInfo[])
  Desc:		get the useful device address
  Input:	the device information
  Output:	void
  Return:	the device address point
**********************************************************/
char *GetDeviceAddress(LPNET_DVR_IPDEVINFO_V31 lpDeviceInfo)
{
	if (lpDeviceInfo == NULL)
	{
		return NULL;
	}

	return (char *)(lpDeviceInfo->struIP.sIpV4);


// 	if (strlen((char *)(lpDeviceInfo->byDomain)) != 0)
// 	{//If the domain is not blank string, show domain which is useful on device.
// 		return (char *)(lpDeviceInfo->byDomain);
// 	}
// 	else
// 	{
// 		return (char *)(lpDeviceInfo->struIP.sIpV4);
// 	}
}

/*********************************************************
  Function:	SetDeviceAddress
  Desc:		Set Device Address to NET_DVR_IPDEVINFO_V31
  Input:	void
  Output:	void
  Return:	void
**********************************************************/
void SetDeviceAddress(LPNET_DVR_IPDEVINFO_V31 lpDevInfo, char *lpAddress)
{
	if (lpDevInfo != NULL && lpAddress != NULL)
	{
		if (CheckIPStr(lpAddress))
		{
			memcpy(lpDevInfo->struIP.sIpV4, lpAddress, 16);
		}
		else
		{
			memcpy(lpDevInfo->byDomain, lpAddress, MAX_DOMAIN_NAME);
		}	
	}
}

/////////////////////////////////////////////////////////////////////////////
// CDlgRemoteIPAccess dialog
/*********************************************************
  Function:	CDlgRemoteIPAccess
  Desc:		Constructor
  Input:	pParent, parent window pointer
  Output:	none
  Return:	none
**********************************************************/
CDlgRemoteIPAccess::CDlgRemoteIPAccess(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgRemoteIPAccess::IDD, pParent)
{
	m_dwDevIndex = 0;
	m_iCurSel = 0;
	m_iCurChanNO = 0;
	m_iCurChanIndex = 0;
	m_bCurEnable = FALSE;
	m_bAnalogChange = FALSE;
	memset(&m_struIPParaCfgV40, 0, sizeof(m_struIPParaCfgV40));
	//{{AFX_DATA_INIT(CDlgRemoteIPAccess)
	m_csDevIP = _T("172.7.39.1");
	m_uDevPort = 8000;
	m_csDevPwd = _T("12345");
	m_ceDevUserName = _T("admin");
	m_iIPDevChan = 1;
	m_bStreamUrlEnable = FALSE;
	m_csStreamServerUrl = _T("");
	m_iDeviceIdUrl = 0;
	m_iChannelNumUrl = 0;
	//}}AFX_DATA_INIT
}

CDlgRemoteIPAccess::~CDlgRemoteIPAccess()
{
	delete m_pDlgIPAccessDDNS;
	delete m_pDlgIPAccessIPServer;
	delete m_pDlgIPAccessStreamServer;
	delete m_pDlgIPAccessCfgEasyDDNS;
};

/*********************************************************
  Function:	DoDataExchange
  Desc:		the map between control and variable
  Input:	pDX, CDataExchange,pass the data exchange object to the window CWnd::DoDataExchange
  Output:	none
  Return:	none
**********************************************************/
void CDlgRemoteIPAccess::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgRemoteIPAccess)
	DDX_Control(pDX, IDC_COMBO_TRANS_PROTOCALTYPE_URL, m_comboTransProtTypeUrl);
	DDX_Control(pDX, IDC_COMBO_CHANNEL_GROUP_NO, m_comboChannelGroupNO);
	DDX_Control(pDX, IDC_COMBO_STREAM_TYPE, m_comboStreamType);
	DDX_Control(pDX, IDC_COMBO_PROTYPE, m_comboProType);
	DDX_Control(pDX, IDC_LIST_IP_CHAN, m_listIPChan);
	DDX_Text(pDX, IDC_DEVICE_IP, m_csDevIP);
	DDX_Text(pDX, IDC_DEVICE_PORT, m_uDevPort);
	DDX_Text(pDX, IDC_DEVICE_PSW, m_csDevPwd);
	DDX_Text(pDX, IDC_DEVICE_USERNAME, m_ceDevUserName);
	DDX_Text(pDX, IDC_EDIT_CHAN, m_iIPDevChan);
	DDX_Check(pDX, IDC_CHECK_URL_ENABLE, m_bStreamUrlEnable);
	DDX_Text(pDX, IDC_EDIT_STREAM_SERVER_URL, m_csStreamServerUrl);
	DDX_Text(pDX, IDC_EDIT_DEVICEID_URL, m_iDeviceIdUrl);
	DDX_Text(pDX, IDC_EDIT_CHANNELNUM_URL, m_iChannelNumUrl);
	//}}AFX_DATA_MAP
}

/*********************************************************
  Function:	BEGIN_MESSAGE_MAP
  Desc:		the map between control and function
  Input:	first parameter:name of current class; second: name of base class
  Output:	none
  Return:	none
**********************************************************/
BEGIN_MESSAGE_MAP(CDlgRemoteIPAccess, CDialog)
	//{{AFX_MSG_MAP(CDlgRemoteIPAccess)
	ON_BN_CLICKED(IDC_BTN_ADD_IP_CHAN, OnBtnAddIPChan)
	ON_NOTIFY(NM_CLICK, IDC_LIST_IP_CHAN, OnClickListIPChan)
	ON_BN_CLICKED(IDC_BTN_DELETE, OnBtnDelete)
	ON_BN_CLICKED(IDC_BTN_ENABLE, OnBtnEnable)
	ON_BN_CLICKED(IDC_BTN_REFRESH, OnBtnRefresh)
	ON_BN_CLICKED(IDC_BTN_SAVE, OnBtnSave)
	ON_BN_CLICKED(IDC_BTN_QUICK_ADD, OnBtnQuickAdd)
	ON_CBN_SELCHANGE(IDC_COMBO_STREAM_TYPE, OnSelchangeComboStreamType)
	ON_BN_CLICKED(IDC_BTN_STREAM_URL_SET, OnBtnStreamUrlSet)
	ON_CBN_SELCHANGE(IDC_COMBO_CHANNEL_GROUP_NO, OnSelchangeComboChannelGroupNo)
	ON_BN_CLICKED(IDC_BUTTON_UPDATE_PRO_LIST, OnButtonUpdateProList)
	ON_BN_CLICKED(IDC_BUTTON_CUSTOM_PRO, OnButtonCustomPro)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgRemoteIPAccess message handlers
/*********************************************************
  Function:	OnInitDialog
  Desc:		Initialize the dialog
  Input:	none
  Output:	none
  Return:	none
**********************************************************/
BOOL CDlgRemoteIPAccess::OnInitDialog()
{
	CDialog::OnInitDialog();
	m_listIPChan.SetExtendedStyle(m_listIPChan.GetExtendedStyle()|LVS_EX_FULLROWSELECT);
	char szLan[128] = {0};
	g_StringLanType(szLan, "���", "Serial No.");
	m_listIPChan.InsertColumn(0, szLan,LVCFMT_LEFT,40,-1);
	g_StringLanType(szLan, "ͨ����", "Channel");
	m_listIPChan.InsertColumn(1,szLan,LVCFMT_LEFT,80,-1);

	g_StringLanType(szLan, "�Ƿ�����", "Whether online");
	m_listIPChan.InsertColumn(2, szLan,LVCFMT_LEFT,80,-1);
	g_StringLanType(szLan, "Э��", "Protocol");
	m_listIPChan.InsertColumn(3, szLan,LVCFMT_LEFT,100,-1);

// 	g_StringLanType(szLan, "IP��ַ", "IP Address/Domain");
// 	m_listIPChan.InsertColumn(2, szLan,LVCFMT_LEFT,120,-1);
// 	g_StringLanType(szLan, "�˿ں�", "Port");
// 	m_listIPChan.InsertColumn(3, szLan,LVCFMT_LEFT,80,-1);
// 	g_StringLanType(szLan, "IPͨ����", "IP Channel");
//  	m_listIPChan.InsertColumn(4, szLan,LVCFMT_LEFT,80,-1);

	m_pDlgIPAccessStreamServer = new CDlgIPAccessCfgStreamServer;
	m_pDlgIPAccessStreamServer->Create(IDD_DLG_REMOTE_IP_ACCESS_CFG_STREAM_SERVER,this);
	m_pDlgIPAccessStreamServer->MoveWindow(10, 280, 600, 230);
	
	m_pDlgIPAccessIPServer = new CDlgIPAccessCfgIPServer;
	m_pDlgIPAccessIPServer->Create(IDD_DLG_REMOTE_IP_ACCESS_CFG_IPSERVER,this);
	m_pDlgIPAccessIPServer->MoveWindow(10, 280, 600, 230);
	
	m_pDlgIPAccessDDNS = new CDlgIPAccessCfgDDNS;
	m_pDlgIPAccessDDNS->Create(IDD_DLG_REMOTE_IP_ACCESS_CFG_DDNS,this);
	m_pDlgIPAccessDDNS->MoveWindow(10, 280, 600, 230);

	m_pDlgIPAccessCfgEasyDDNS = new DlgIPAccessCfgEasyDDNS;
	m_pDlgIPAccessCfgEasyDDNS->Create(IDD_DLG_REMOTE_IP_ACCESS_CFG_EASYDDNS,this);
	m_pDlgIPAccessCfgEasyDDNS->MoveWindow(10, 280, 600, 230);

	
	m_comboStreamType.SetCurSel(0);
	ShowInfoByGetStreamType(0);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

/*********************************************************
  Function:	
  Desc:		
  Input:	void
  Output:	void
  Return:	void
**********************************************************/
char* CDlgRemoteIPAccess::ProIndexToStr(int iProType)
{
	switch(iProType)
	{
	case 0:
		
		break;
	default:
		break;
	}
	return m_szProType;	
}

/*********************************************************
  Function:	CheckInitParam
  Desc:		check and initialize the parameters
  Input:	none
  Output:	none
  Return:	none
**********************************************************/
void CDlgRemoteIPAccess::CheckInitParam()
{
	int i = 0;

	//Update channel list: group[0]
	UpdateGroup(0);
	char szLan[128] = {0};	
	m_comboChannelGroupNO.ResetContent();
	for (i = 0; i < (int)m_struIPParaCfgV40.dwGroupNum; i++)
	{
		memset(szLan, 0, 128);
		sprintf(szLan, "%d", i);
		m_comboChannelGroupNO.AddString(szLan);
	}
	m_comboChannelGroupNO.SetCurSel(0);
	return;
}

void CDlgRemoteIPAccess::UpdateGroup(int iGroupNO)
{
	if (iGroupNO < 0)
	{
		return;
	}

	ShowWindow(SW_SHOW);
	int iDev = g_pMainDlg->GetCurDeviceIndex();
	if (iDev == -1 /*|| g_pMainDlg->IsCurDevMatDec(iDev)*/)
	{
		EnableWindow(FALSE);
		return;
	}
	EnableWindow(TRUE);

	m_dwDevIndex = iDev;
	m_dwStartChan = g_struDeviceInfo[m_dwDevIndex].iStartChan;
	m_iSelAccessType = 0;
	
	CString strTemp =_T("");
	CString strChanTmp = _T("");
	int i = 0;
	DWORD dwChanNum = 0;
	int iIndex = 0;
	DWORD dwIPChanIndex = 0;
	DWORD dwID = 0;
	m_iCurChanNO = -1;
	m_iCurSel = -1;
	EnableInfoCtrl(FALSE);
	SetCtrlStat(2);

	char szLan[128] = {0};
	m_listIPChan.DeleteAllItems();

	//Get IPParamCfg_V40
	//.....
	if (g_pMainDlg->DoGetDeviceResoureCfg(m_dwDevIndex, iGroupNO))
	{
		g_pMainDlg->RedrawDeviceNode(m_dwDevIndex);

		OnButtonUpdateProList();

		memset(&m_struIPParaCfgV40, 0, sizeof(m_struIPParaCfgV40));
		memcpy(&m_struIPParaCfgV40, &g_struDeviceInfo[m_dwDevIndex].struIPParaCfgV40, sizeof(m_struIPParaCfgV40));

		int iMaxSimulateChannelNO = m_struIPParaCfgV40.dwAChanNum + g_struDeviceInfo[m_dwDevIndex].iStartChan;
		//***channel list: group[0]****//
		//***64 simulate channel***//
		for (i = 0; i < MAX_CHANNUM_V30; i++)
		{
			dwChanNum = i + g_struDeviceInfo[m_dwDevIndex].iStartChan + MAX_CHANNUM_V30 * iGroupNO;
			if ((dwChanNum + 1) > iMaxSimulateChannelNO)
			{
				break;
			}

			strTemp.Format("%02d", iIndex+1);
			m_listIPChan.InsertItem(iIndex, strTemp, 0);
			strTemp.Format(ANALOG_C_FORMAT, dwChanNum);
			m_listIPChan.SetItemText(iIndex, 1, strTemp);
			if (m_struIPParaCfgV40.byAnalogChanEnable[i])
			{
				g_StringLanType(szLan, "����", "Enable");
				m_listIPChan.SetItemText(i, 2, szLan);
				m_listIPChan.SetItemData(iIndex, ANALOG_CHAN_ENABLE*1000+i);
			}
			else
			{
				g_StringLanType(szLan, "������", "Disabled");
				m_listIPChan.SetItemText(i, 2, szLan);
				m_listIPChan.SetItemData(iIndex, ANALOG_CHAN_DISABLE*1000+i);
			}
			iIndex++;
		}

		//***64 IP channel***//
		int iMaxIPChannelNO = m_struIPParaCfgV40.dwStartDChan + m_struIPParaCfgV40.dwDChanNum;
		for (i = 0; i < MAX_CHANNUM_V30; i++)
		{
			dwChanNum = i + m_struIPParaCfgV40.dwStartDChan + MAX_CHANNUM_V30 * iGroupNO;
			if ((dwChanNum + 1) > iMaxIPChannelNO)
			{
				break;
			}
            
			strTemp.Format("%02d", iIndex+1);
			m_listIPChan.InsertItem(iIndex, strTemp, 0);

			strTemp.Format(IP_CAMERA_NAME, dwChanNum - m_struIPParaCfgV40.dwStartDChan + 1);
			m_listIPChan.SetItemText(iIndex, 1, strTemp);
			ShowIsEnableOrOnlineInList(iIndex, 2, i);
		
			//4.the type of getting stream
			memset(szLan, 0, 128);
			sprintf(szLan, "%d", m_struIPParaCfgV40.struStreamMode[i].byGetStreamType);
			m_listIPChan.SetItemText(iIndex, 3, szLan);

			iIndex++;		
        }	

		GetDlgItem(IDC_BTN_SAVE)->EnableWindow(TRUE);
		EnableWindow(TRUE);
	}
	else
	{
		GetDlgItem(IDC_BTN_SAVE)->EnableWindow(FALSE);
		if (NET_DVR_GetLastError() == NET_DVR_NOSUPPORT)
		{
			EnableWindow(FALSE);
		}
	}
}

/*********************************************************
  Function:	OnBtnDelete
  Desc:		delete the ip carema
  Input:	none
  Output:	none
  Return:	none
**********************************************************/
void CDlgRemoteIPAccess::OnBtnDelete() 
{
	char szLan[128] = {0};
	int iGroupNO = m_comboChannelGroupNO.GetCurSel();

	int iIPChanIndex = m_iCurChanNO - m_struIPParaCfgV40.dwStartDChan - iGroupNO * MAX_CHANNUM_V30;//Current ip channel array index
	if (iIPChanIndex < 0 && iIPChanIndex >= MAX_CHANNUM_V30)
	{
		g_pMainDlg->AddLog(m_dwDevIndex, OPERATION_FAIL_T, "chanindex[%d] err ip Channel", m_iCurChanNO);
		return;
	}

	m_struIPParaCfgV40.struStreamMode[iIPChanIndex].byGetStreamType = 0; //direct connect device.
	//clear ip channel info
	memset(&(m_struIPParaCfgV40.struStreamMode[iIPChanIndex].uGetStream.struChanInfo), 0, sizeof(NET_DVR_IPCHANINFO));
    //set device infomation
	memset(&(m_struIPParaCfgV40.struIPDevInfo[iIPChanIndex]), 0, sizeof(NET_DVR_IPDEVINFO_V31));

	g_StringLanType(szLan, "������", "Disable");
	m_listIPChan.SetItemText(m_iCurSel, 2, szLan);
	m_listIPChan.SetItemData(m_iCurSel, IP_CHAN_ENABLE*1000+m_iCurChanNO);
	
	SetCtrlStat(IP_CHAN_DISABLE);
}

/*********************************************************
  Function:	OnBtnAddIPChan
  Desc:		add the ip camera
  Input:	none
  Output:	none
  Return:	none
**********************************************************/
void CDlgRemoteIPAccess::OnBtnAddIPChan() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	int i = 0;
	int j = 0;
	CString csTmp;
	BOOL bExistDev = FALSE;
	char szLan[128] = {0};
	int iGroupNO = m_comboChannelGroupNO.GetCurSel();
	int iIPChanIndex =  0; //Array index in v40.

	iIPChanIndex = m_iCurChanNO - m_struIPParaCfgV40.dwStartDChan - iGroupNO * MAX_CHANNUM_V30;

	//check params
	if (iIPChanIndex < 0)
	{
		g_pMainDlg->AddLog(m_dwDevIndex, OPERATION_FAIL_T, "chan [%d] not ip Channel", m_iCurChanNO);
		return;
	}
	if (m_iCurSel < 0)
	{		
		g_StringLanType(szLan, "��ѡ���б��е�ͨ��", "Please choose the channel in the list");
		AfxMessageBox(szLan);
		return;
	}
	if (m_iIPDevChan == 0 || memcmp(m_csDevIP.GetBuffer(0), "0.0.0.0", m_csDevIP.GetLength()) == 0)
	{
		g_StringLanType(szLan, "��������", "Parameter error");
		AfxMessageBox(szLan);
		return;
	}	
	
	m_struIPParaCfgV40.struStreamMode[iIPChanIndex].byGetStreamType = 0; //direct connect device.
	//clear device info
	memset(&(m_struIPParaCfgV40.struStreamMode[iIPChanIndex].uGetStream.struChanInfo), 0, sizeof(NET_DVR_IPCHANINFO));
	
	//set device id
	m_struIPParaCfgV40.struStreamMode[iIPChanIndex].uGetStream.struChanInfo.byEnable = FALSE; //Is online?
	m_struIPParaCfgV40.struStreamMode[iIPChanIndex].uGetStream.struChanInfo.byChannel = (BYTE)m_iIPDevChan;
	int iDevID = iIPChanIndex + iGroupNO * MAX_CHANNUM_V30 + 1;
	m_struIPParaCfgV40.struStreamMode[iIPChanIndex].uGetStream.struChanInfo.byIPID = iDevID % 256;
	m_struIPParaCfgV40.struStreamMode[iIPChanIndex].uGetStream.struChanInfo.byIPIDHigh = iDevID /256;

    //set device infomation
	SetDeviceAddress(&(m_struIPParaCfgV40.struIPDevInfo[iIPChanIndex]), m_csDevIP.GetBuffer(0));
	m_struIPParaCfgV40.struIPDevInfo[iIPChanIndex].byProType = (BYTE)m_comboProType.GetItemData(m_comboProType.GetCurSel());
	m_struIPParaCfgV40.struIPDevInfo[iIPChanIndex].byEnable = TRUE;
	memcpy(m_struIPParaCfgV40.struIPDevInfo[iIPChanIndex].sUserName, m_ceDevUserName.GetBuffer(0), NAME_LEN);
	memcpy(m_struIPParaCfgV40.struIPDevInfo[iIPChanIndex].sPassword, m_csDevPwd.GetBuffer(0), PASSWD_LEN);
	m_struIPParaCfgV40.struIPDevInfo[iIPChanIndex].wDVRPort = (WORD)m_uDevPort;

	g_StringLanType(szLan, "����", "Enable");
	m_listIPChan.SetItemText(m_iCurSel, 2, szLan);

	m_listIPChan.SetItemData(m_iCurSel, IP_CHAN_ENABLE*1000 + m_iCurChanNO);
	SetCtrlStat(IP_CHAN_ENABLE);	
}


/*********************************************************
  Function:	OnClickListIPChan
  Desc:		choose the channel item in the list, and update the channel
  Input:	pNMHDR, Contains the click information
  Output:	pResult, result after handle notification	
  Return:	none
**********************************************************/
void CDlgRemoteIPAccess::OnClickListIPChan(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
//	LPNMHEADER phdr = reinterpret_cast<LPNMHEADER>(pNMHDR);
 	POSITION  iPos = m_listIPChan.GetFirstSelectedItemPosition();
 	if (iPos == NULL)
 	{
 		return;
 	}
 	m_iCurSel = m_listIPChan.GetNextSelectedItem(iPos);
	int iData = m_listIPChan.GetItemData(m_iCurSel);

	int iGroupNO = m_comboChannelGroupNO.GetCurSel();

	m_iCurChanNO = iData%1000 + iGroupNO * 64;

	m_iCurChanIndex = m_iCurChanNO - m_struIPParaCfgV40.dwStartDChan - iGroupNO * MAX_CHANNUM_V30; 

	SetCtrlStat(iData/1000);
	UpdateData(FALSE);
	*pResult = 0;
}

/*********************************************************
  Function:	EnableInfoCtrl
  Desc:		enable the control status of the ip device
  Input:	bEnable, TRUE/FALSE; 
  Output:	none
  Return:	none
**********************************************************/
void CDlgRemoteIPAccess::EnableInfoCtrl(BOOL bEnable)
{
	GetDlgItem(IDC_DEVICE_IP)->EnableWindow(bEnable);
	GetDlgItem(IDC_DEVICE_PORT)->EnableWindow(bEnable);
	GetDlgItem(IDC_DEVICE_PSW)->EnableWindow(bEnable);
	GetDlgItem(IDC_DEVICE_USERNAME)->EnableWindow(bEnable);
	GetDlgItem(IDC_EDIT_CHAN)->EnableWindow(bEnable);
	GetDlgItem(IDC_BUTTON_UPDATE_PRO_LIST)->EnableWindow(bEnable);
	GetDlgItem(IDC_BUTTON_CUSTOM_PRO)->EnableWindow(bEnable);
}

/*********************************************************
  Function:	SetCtrlStat
  Desc:		change the button status as the type(analog or digital) of the channel
  Input:	iStat, the status of the channels
  Output:	none
  Return:	none
**********************************************************/
void CDlgRemoteIPAccess::SetCtrlStat(int iStat)
{
	DWORD dwID = 0;
	char szLan[128] = {0};
	int i = 0;
	switch(iStat)
	{
	case ANALOG_CHAN_DISABLE://analog disable
		GetDlgItem(IDC_BTN_ADD_IP_CHAN)->EnableWindow(FALSE);
		GetDlgItem(IDC_BTN_DELET)->EnableWindow(FALSE);
		GetDlgItem(IDC_BTN_ENABLE)->EnableWindow(TRUE);
		g_StringLanType(szLan, "����", "Enable");	
		GetDlgItem(IDC_BTN_ENABLE)->SetWindowText(szLan);
		EnableInfoCtrl(FALSE);
		m_bCurEnable = FALSE;
		SetChannelInfobyStreamType(TRUE);
		break;
	case ANALOG_CHAN_ENABLE://analog enable channel
		GetDlgItem(IDC_BTN_ADD_IP_CHAN)->EnableWindow(FALSE);
		GetDlgItem(IDC_BTN_DELET)->EnableWindow(FALSE);
		GetDlgItem(IDC_BTN_ENABLE)->EnableWindow(TRUE);
		g_StringLanType(szLan, "����", "Disable");	
		GetDlgItem(IDC_BTN_ENABLE)->SetWindowText(szLan);
		EnableInfoCtrl(FALSE);
		m_bCurEnable = TRUE;
		SetChannelInfobyStreamType(TRUE);
		break;
	case IP_CHAN_DISABLE://digital disable channel
		GetDlgItem(IDC_BTN_ADD_IP_CHAN)->EnableWindow(TRUE);
		g_StringLanType(szLan, "���", "Add");
		GetDlgItem(IDC_BTN_ADD_IP_CHAN)->SetWindowText(szLan);
		GetDlgItem(IDC_BTN_DELET)->EnableWindow(FALSE);
		GetDlgItem(IDC_BTN_ENABLE)->EnableWindow(FALSE);
		//GetDlgItem(IDC_BTN_MOD)->EnableWindow(FALSE);
		EnableInfoCtrl(TRUE);
		m_bCurEnable = FALSE;
		SetChannelInfobyStreamType(FALSE);
		break;
	case IP_CHAN_ENABLE://digital enable
		GetDlgItem(IDC_BTN_ADD_IP_CHAN)->EnableWindow(TRUE);
		g_StringLanType(szLan, "�޸�", "Modify");
		GetDlgItem(IDC_BTN_ADD_IP_CHAN)->SetWindowText(szLan);
		GetDlgItem(IDC_BTN_DELET)->EnableWindow(TRUE);
		GetDlgItem(IDC_BTN_ENABLE)->EnableWindow(FALSE);
		
		//GetDlgItem(IDC_BTN_MOD)->EnableWindow(TRUE);
		EnableInfoCtrl(TRUE);
		m_bCurEnable = TRUE;
		SetChannelInfobyStreamType(FALSE);
		break;
	default:
	    break;
	}

	//Set info by the type of getting stream.
	

	UpdateData(FALSE);
}

/*********************************************************
  Function:	OnBtnEnable
  Desc:		enable the analog channel or not
  Input:	none
  Output:	none
  Return:	none
**********************************************************/
void CDlgRemoteIPAccess::OnBtnEnable() 
{
	char szLan[128] = {0};
	if (m_bCurEnable)
	{
		g_StringLanType(szLan, "����", "Disable");
		m_listIPChan.SetItemText(m_iCurSel, 2, szLan);
		m_listIPChan.SetItemData(m_iCurSel, ANALOG_CHAN_DISABLE*1000+m_iCurChanNO);
		m_struIPParaCfgV40.byAnalogChanEnable[m_iCurChanNO] = FALSE;
		SetCtrlStat(0);
	}
	else
	{
		g_StringLanType(szLan, "����", "Enable");
		m_listIPChan.SetItemText(m_iCurSel, 2, szLan);
		m_listIPChan.SetItemData(m_iCurSel, ANALOG_CHAN_ENABLE*1000+m_iCurChanNO);
		m_struIPParaCfgV40.byAnalogChanEnable[m_iCurChanNO] = TRUE;
		SetCtrlStat(1);	
	}
	m_bAnalogChange = TRUE;
}

/*********************************************************
  Function:	OnBtnRefresh
  Desc:		get the ip configure again and refresh the local information
  Input:	none
  Output:	none
  Return:	none
**********************************************************/
void CDlgRemoteIPAccess::OnBtnRefresh() 
{
	// TODO: Add your control notification handler code here
	CheckInitParam();
}

/*********************************************************
  Function:	OnBtnSave
  Desc:		save the ip access configure
  Input:	none
  Output:	none
  Return:	none
**********************************************************/
void CDlgRemoteIPAccess::OnBtnSave() 
{
	char szLan[128] = {0};
	if (memcmp(g_struDeviceInfo[m_dwDevIndex].struIPParaCfgV40.byAnalogChanEnable, m_struIPParaCfgV40.byAnalogChanEnable, MAX_ANALOG_CHANNUM) != 0)
	{
		g_StringLanType(szLan, "�޸�ģ��ͨ��ʹ��״̬,�豸���Զ�����!",\
			"Modify the status of Analog channel, the device will automatically restart");
		if (IDOK != MessageBox(szLan,"Warning",IDOK))
		{
			return;
		}
	}
	memcpy(&g_struDeviceInfo[m_dwDevIndex].struIPParaCfgV40, &m_struIPParaCfgV40, sizeof(m_struIPParaCfgV40));
	if (g_pMainDlg->DoSetIPAccessCfg(m_dwDevIndex))
	{
		g_StringLanType(szLan, "IPC�������óɹ�!��ˢ��!", "IPC configuration settings successfully! Please refresh!");
		AfxMessageBox(szLan);
	}
	else
	{
		g_StringLanType(szLan, "IPC��������ʧ��!", "IPC configuration settings failed!");
		AfxMessageBox(szLan);
	}
}

/*********************************************************
  Function:	OnBtnQuickAdd
  Desc:		quick add device.
  Input:	none
  Output:	none
  Return:	none
**********************************************************/
void CDlgRemoteIPAccess::OnBtnQuickAdd() 
{
    CDlgQuickAddIpc dlg;
    dlg.m_iDevIndex = m_dwDevIndex;
    dlg.m_lServerID = g_struDeviceInfo[m_dwDevIndex].lLoginID;
    memcpy(&dlg.m_struIpcProtoList, &m_struProtoList, sizeof(m_struProtoList));
    dlg.DoModal();
}

void CDlgRemoteIPAccess::ShowInfoByGetStreamType(int iType)
{
	int iGroupNO = m_comboChannelGroupNO.GetCurSel();
	int iChannelIndex = m_iCurChanNO - m_struIPParaCfgV40.dwStartDChan - iGroupNO * MAX_CHANNUM_V30;

    switch (iType)
    {
    case 0:  //direct  connect device
	    ShowDeviceInfo(TRUE);
        m_pDlgIPAccessDDNS->ShowWindow(SW_HIDE);
		m_pDlgIPAccessIPServer->ShowWindow(SW_HIDE);
		m_pDlgIPAccessStreamServer->ShowWindow(SW_HIDE);
		m_pDlgIPAccessCfgEasyDDNS->ShowWindow(SW_HIDE);
		ShowStreamUrl(FALSE);
     	break;
	 case 1: //Get stream from stream server.
		ShowDeviceInfo(FALSE);
		m_pDlgIPAccessStreamServer->ShowWindow(SW_SHOW);
		m_pDlgIPAccessIPServer->ShowWindow(SW_HIDE);
		m_pDlgIPAccessDDNS->ShowWindow(SW_HIDE);
		m_pDlgIPAccessCfgEasyDDNS->ShowWindow(SW_HIDE);
		ShowStreamUrl(FALSE);
		m_pDlgIPAccessStreamServer->m_iChannelIndex = iChannelIndex;
		break;
	 case 2: //Get stream from IP server.
		ShowDeviceInfo(FALSE);
		m_pDlgIPAccessStreamServer->ShowWindow(SW_HIDE);
		m_pDlgIPAccessIPServer->ShowWindow(SW_SHOW);
		m_pDlgIPAccessDDNS->ShowWindow(SW_HIDE);
		m_pDlgIPAccessCfgEasyDDNS->ShowWindow(SW_HIDE);
		ShowStreamUrl(FALSE);
		break;
	 case 3: //Get stream from IP server and stream server.
		ShowDeviceInfo(FALSE);
		m_pDlgIPAccessStreamServer->ShowWindow(SW_HIDE);
		m_pDlgIPAccessIPServer->ShowWindow(SW_HIDE);
		m_pDlgIPAccessDDNS->ShowWindow(SW_SHOW);
		m_pDlgIPAccessCfgEasyDDNS->ShowWindow(SW_HIDE);
		ShowStreamUrl(FALSE);
		break;
	 case 4: //Get stream from IP server and stream server.
		ShowDeviceInfo(TRUE);//
		m_pDlgIPAccessStreamServer->ShowWindow(SW_HIDE);
		m_pDlgIPAccessIPServer->ShowWindow(SW_HIDE);
		m_pDlgIPAccessDDNS->ShowWindow(SW_HIDE);
		m_pDlgIPAccessCfgEasyDDNS->ShowWindow(SW_HIDE);
		ShowStreamUrl(TRUE);
		break;
	 case 5: //Get stream from EasyDDNS.
		 ShowDeviceInfo(FALSE);
		 m_pDlgIPAccessStreamServer->ShowWindow(SW_HIDE);
		 m_pDlgIPAccessIPServer->ShowWindow(SW_HIDE);
		 m_pDlgIPAccessDDNS->ShowWindow(SW_HIDE);
		 m_pDlgIPAccessCfgEasyDDNS->ShowWindow(SW_SHOW);
		 ShowStreamUrl(FALSE);
		break;
	 default: //same as case 0;
		ShowDeviceInfo(TRUE);
		m_pDlgIPAccessDDNS->ShowWindow(SW_HIDE);
		m_pDlgIPAccessIPServer->ShowWindow(SW_HIDE);
		m_pDlgIPAccessStreamServer->ShowWindow(SW_HIDE);
		m_pDlgIPAccessCfgEasyDDNS->ShowWindow(SW_HIDE);
		ShowStreamUrl(FALSE);
		break;
     }
}

void CDlgRemoteIPAccess::ShowDeviceInfo(BOOL bShow)
{
    //static
	GetDlgItem(IDC_STATIC_DEVICE)->ShowWindow(bShow);
	GetDlgItem(IDC_STATIC_IP)->ShowWindow(bShow);
	GetDlgItem(IDC_STATIC_PORT)->ShowWindow(bShow);
	GetDlgItem(IDC_STATIC_CHANNEL)->ShowWindow(bShow);
	GetDlgItem(IDC_STATIC_USER)->ShowWindow(bShow);
	GetDlgItem(IDC_STATIC_PASS)->ShowWindow(bShow);
	GetDlgItem(IDC_STATIC_DEV_TYPE)->ShowWindow(bShow);

	//edit
	GetDlgItem(IDC_DEVICE_IP)->ShowWindow(bShow);
	GetDlgItem(IDC_DEVICE_PORT)->ShowWindow(bShow);
	GetDlgItem(IDC_EDIT_CHAN)->ShowWindow(bShow);
	GetDlgItem(IDC_DEVICE_USERNAME)->ShowWindow(bShow);
	GetDlgItem(IDC_DEVICE_PSW)->ShowWindow(bShow);
	GetDlgItem(IDC_COMBO_PROTYPE)->ShowWindow(bShow);
	GetDlgItem(IDC_BUTTON_UPDATE_PRO_LIST)->ShowWindow(bShow);
	GetDlgItem(IDC_BUTTON_CUSTOM_PRO)->ShowWindow(bShow);

	//btn
	GetDlgItem(IDC_BTN_ENABLE)->ShowWindow(bShow);
	GetDlgItem(IDC_BTN_ADD_IP_CHAN)->ShowWindow(bShow);
	GetDlgItem(IDC_BTN_DELETE)->ShowWindow(bShow);
}

void CDlgRemoteIPAccess::ShowStreamUrl(BOOL bShow)
{
	GetDlgItem(IDC_STATIC_STREAM_SERVER_URL)->ShowWindow(bShow);
	GetDlgItem(IDC_EDIT_STREAM_SERVER_URL)->ShowWindow(bShow);
	GetDlgItem(IDC_CHECK_URL_ENABLE)->ShowWindow(bShow);
	GetDlgItem(IDC_BTN_STREAM_URL_SET)->ShowWindow(bShow);
	GetDlgItem(IDC_STATIC_URLCFG)->ShowWindow(bShow);
	GetDlgItem(IDC_COMBO_TRANS_PROTOCALTYPE_URL)->ShowWindow(bShow);
	GetDlgItem(IDC_EDIT_CHANNELNUM_URL)->ShowWindow(bShow);
	GetDlgItem(IDC_EDIT_DEVICEID_URL)->ShowWindow(bShow);
	GetDlgItem(IDC_STATIC_TRANSPORTPROTOCAL_TYPE_URL)->ShowWindow(bShow);
	GetDlgItem(IDC_STATIC_DVEICEID_URL)->ShowWindow(bShow);
	GetDlgItem(IDC_STATIC_CHANNEL_NUM_URL)->ShowWindow(bShow);
}

//Set channel information by the type of getting stream.
void CDlgRemoteIPAccess::SetChannelInfobyStreamType(BOOL bAnalog)
{
	if (m_iCurChanNO < 0)
	{
		return;
	}

	if (bAnalog)
	{
		ShowInfoByGetStreamType(0);
		m_comboStreamType.EnableWindow(FALSE);
		return;
	}

	m_comboStreamType.EnableWindow(TRUE);
	int iGroupNO = m_comboChannelGroupNO.GetCurSel();
	int iIPChanIndex =  0; //Array index in v40.
	iIPChanIndex = m_iCurChanNO - m_struIPParaCfgV40.dwStartDChan - iGroupNO * MAX_CHANNUM_V30;
	if (iIPChanIndex < 0)
	{
		g_pMainDlg->AddLog(-1, OPERATION_FAIL_T, "(iIPChanIndex = %d)<0", iIPChanIndex);
		return;
	}

	int iStreamType  = m_struIPParaCfgV40.struStreamMode[iIPChanIndex].byGetStreamType;
	ShowInfoByGetStreamType(iStreamType);

	//the combo of Stream type.
	m_comboStreamType.SetCurSel(iStreamType);

	//set information
	switch(iStreamType)
	{
	case 0: //direct get stream from the device
		if (iIPChanIndex >= 0)
		{
			int dwID = m_struIPParaCfgV40.struStreamMode[iIPChanIndex].uGetStream.struChanInfo.byIPID + \
				256 * m_struIPParaCfgV40.struStreamMode[iIPChanIndex].uGetStream.struChanInfo.byIPIDHigh;
			if (dwID > 0 && dwID <= MAX_IP_DEVICE_V40)
			{
				if (m_struProtoList.dwProtoNum < IPC_PROTOCOL_NUM)
				{
					for (int i = 0; i<m_struProtoList.dwProtoNum; i++)
					{
						if (m_struIPParaCfgV40.struIPDevInfo[dwID-1].byProType == m_struProtoList.struProto[i].dwType)
						{
							m_comboProType.SetCurSel(i); //protocol	
							break;
						}
					}
				}

				m_csDevIP.Format("%s", GetDeviceAddress(&(m_struIPParaCfgV40.struIPDevInfo[dwID-1]))); //IP
				m_uDevPort = m_struIPParaCfgV40.struIPDevInfo[dwID-1].wDVRPort;
				m_iIPDevChan = m_struIPParaCfgV40.struStreamMode[iIPChanIndex].uGetStream.struChanInfo.byChannel;
			}
		}
		break;
	case 1: //Get stream from stream server.  
        m_pDlgIPAccessStreamServer->UpdateParams();
		break;
	case 2: //Get stream from IP server.
    	m_pDlgIPAccessIPServer->UpdateParams();
		break;
	case 3: //Get stream from IP server and stream server.
	    m_pDlgIPAccessDDNS->UpdateParams();
	    break;
	case 4: //Get stream from stream server by url.
		m_csStreamServerUrl.Format("%s", m_struIPParaCfgV40.struStreamMode[iIPChanIndex].uGetStream.struStreamUrl.strURL);
		m_bStreamUrlEnable = m_struIPParaCfgV40.struStreamMode[iIPChanIndex].uGetStream.struStreamUrl.byEnable; 
		break;
	case 5: //Get stream from EasyDDNS.
		m_pDlgIPAccessCfgEasyDDNS->UpdateParams();
	    break;
	default: 
	    break;
	}
	UpdateData(FALSE);
}

//Is enable or online?
void CDlgRemoteIPAccess::ShowIsEnableOrOnlineInList(int iRowIndex, int iColumnIndex, int iArrayIndex)
{
	char szLan[128] = {0};
	BOOL bEnable = FALSE;

	//3.whether enable?
	switch (m_struIPParaCfgV40.struStreamMode[iArrayIndex].byGetStreamType)
	{
	case 0: //direct device
		bEnable = m_struIPParaCfgV40.struStreamMode[iArrayIndex].uGetStream.struChanInfo.byIPID;
		break;
	case 1:
		bEnable = m_struIPParaCfgV40.struStreamMode[iArrayIndex].uGetStream.struPUStream.struStreamMediaSvrCfg.byValid;
		break;
	case 2:
		bEnable = m_struIPParaCfgV40.struStreamMode[iArrayIndex].uGetStream.struIPServerStream.byEnable;
		break;
	case 3:
		bEnable = m_struIPParaCfgV40.struStreamMode[iArrayIndex].uGetStream.struDDNSStream.byEnable;
		break;
	case 4:
		bEnable = m_struIPParaCfgV40.struStreamMode[iArrayIndex].uGetStream.struStreamUrl.byEnable;
		break;
	default:
		break;
	}

	if (bEnable)
	{
		m_listIPChan.SetItemData(iRowIndex, IP_CHAN_ENABLE*1000+iArrayIndex + m_struIPParaCfgV40.dwStartDChan);
	} 
	else
	{
		m_listIPChan.SetItemData(iRowIndex, IP_CHAN_DISABLE*1000+iArrayIndex + m_struIPParaCfgV40.dwStartDChan);
	}

	if (0 == m_struIPParaCfgV40.struStreamMode[iArrayIndex].byGetStreamType && bEnable)
	{
		if (m_struIPParaCfgV40.struStreamMode[iArrayIndex].uGetStream.struChanInfo.byEnable)
		{
			g_StringLanType(szLan, "����", "online");
		}
		else
		{
			g_StringLanType(szLan, "����", "offline");
		}
	}
	else
	{
		GetIsEnableString(bEnable, szLan);
	}

	m_listIPChan.SetItemText(iRowIndex, iColumnIndex, szLan);	
}

void CDlgRemoteIPAccess::GetIsEnableString(BOOL bEnable, char *pStrEnable)
{
	if (bEnable)
	{
		g_StringLanType(pStrEnable, "����", "Enable");
	}
	else
	{
		g_StringLanType(pStrEnable, "������", "Disable");
	}
}

void CDlgRemoteIPAccess::SetChannelEnable(BOOL bEnable)
{
	char szLan[128] = {0};

	if (bEnable)
	{
		g_StringLanType(szLan, "����", "Enable");
	}
	else
	{
		g_StringLanType(szLan, "������", "Disable");
	}

	
	m_listIPChan.SetItemText(m_iCurSel, 2, szLan);
}


void CDlgRemoteIPAccess::OnSelchangeComboStreamType() 
{
	// TODO: Add your control notification handler code here
	
	ShowInfoByGetStreamType(m_comboStreamType.GetCurSel());
	
}

void CDlgRemoteIPAccess::OnBtnStreamUrlSet() 
{
	if (m_iCurChanIndex < 0 || m_iCurChanIndex >= MAX_CHANNUM_V30)
	{
		return;
	}

	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	m_struIPParaCfgV40.struStreamMode[m_iCurChanIndex].byGetStreamType = NET_SDK_STREAM_MEDIA_URL;
	strncpy((char *)(m_struIPParaCfgV40.struStreamMode[m_iCurChanIndex].uGetStream.struStreamUrl.strURL), m_csStreamServerUrl.GetBuffer(0),\
		sizeof(m_struIPParaCfgV40.struStreamMode[m_iCurChanIndex].uGetStream.struStreamUrl.strURL));
	m_struIPParaCfgV40.struStreamMode[m_iCurChanIndex].uGetStream.struStreamUrl.byEnable = m_bStreamUrlEnable;
	m_struIPParaCfgV40.struStreamMode[m_iCurChanIndex].uGetStream.struStreamUrl.byTransPortocol = m_comboTransProtTypeUrl.GetCurSel();
    m_struIPParaCfgV40.struStreamMode[m_iCurChanIndex].uGetStream.struStreamUrl.wIPID = m_iDeviceIdUrl + m_comboChannelGroupNO.GetCurSel()*64 + 1;
	m_struIPParaCfgV40.struStreamMode[m_iCurChanIndex].uGetStream.struStreamUrl.byChannel = m_iChannelNumUrl;

	SetChannelEnable(TRUE);
}

void CDlgRemoteIPAccess::OnSelchangeComboChannelGroupNo() 
{
	// TODO: Add your control notification handler code here
	int iCurrentGroup = m_comboChannelGroupNO.GetCurSel();

	UpdateGroup(iCurrentGroup);
}

void CDlgRemoteIPAccess::OnButtonUpdateProList() 
{
	int i = 0;
	char szLan[1024] = {0};

	m_comboProType.ResetContent();
	if (NET_DVR_GetIPCProtoList(g_struDeviceInfo[m_dwDevIndex].lLoginID, &m_struProtoList))
	{
		for (i = 0; i < (int)m_struProtoList.dwProtoNum; i++)
		{
			memset(szLan, 0, DESC_LEN);
			memcpy(szLan, m_struProtoList.struProto[i].byDescribe, DESC_LEN);
			m_comboProType.AddString(szLan);	
			m_comboProType.SetItemData(i, m_struProtoList.struProto[i].dwType);
		}
		m_comboProType.SetCurSel(0);
	}  
	else
	{
		//default	
		m_comboProType.AddString("0");
		m_comboProType.SetItemData(0, 0);
		g_pMainDlg->AddLog(m_dwDevIndex, OPERATION_FAIL_T, "NET_DVR_GetIPCProtoList");
		GetDlgItem(IDC_COMBO_PROTYPE)->EnableWindow(TRUE);
	}
	
	m_comboProType.SetCurSel(0);
}

void CDlgRemoteIPAccess::OnButtonCustomPro() 
{
	CDlgCuntomProtocal	dlg;
	dlg.m_lUserID = g_struDeviceInfo[m_dwDevIndex].lLoginID;
	dlg.m_dwDevIndex = m_dwDevIndex;
	dlg.DoModal();
}
