/**********************************************************
FileName:    DlgChannelInfo.cpp
Description: channel info    
Date:        2008/05/17
Note: 		 <global>struct, refer to GeneralDef.h, global variants and functions refer to ClientDemo.cpp 
Modification History:      
    <version> <time>         <desc>
    <1.0    > <2008/05/17>       <created>
***********************************************************/


#include "stdafx.h"
#include "ClientDemo.h"
#include "DlgChannelInfo.h"
#include ".\dlgchannelinfo.h"


// CDlgChannelInfo dialog
/*********************************************************
  Function:	CDlgChannelInfo
  Desc:		Constructor
  Input:	
  Output:	
  Return:	
**********************************************************/
IMPLEMENT_DYNAMIC(CDlgChannelInfo, CDialog)
CDlgChannelInfo::CDlgChannelInfo(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgChannelInfo::IDD, pParent)
	, m_csChanName(_T(""))
	, m_iChanNo(0)
	, m_csLocalNodeName(_T(""))
	, m_csDeviceIP(_T(""))
	, m_bChanged(FALSE)
	, m_pChanInfo(NULL)
{
}

/*********************************************************
  Function:	~CDlgChannelInfo
  Desc:		destructor
  Input:	
  Output:	
  Return:	
**********************************************************/
CDlgChannelInfo::~CDlgChannelInfo()
{
	if (m_pChanInfo != NULL)
	{
		m_pChanInfo = NULL;
	}
}

/*********************************************************
  Function:	DoDataExchange
  Desc:		map between control and data
  Input:	
  Output:	
  Return:	
**********************************************************/
void CDlgChannelInfo::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgChannelInfo)
	DDX_Control(pDX, IDC_COMBO_PREVIEW_TYPE, m_cmPreviewMode);
	DDX_Text(pDX, IDC_CHANNAME, m_csChanName);
	DDX_Text(pDX, IDC_CHANNO, m_iChanNo);
	DDX_Text(pDX, IDC_CHANINFO_DEV_NAME, m_csLocalNodeName);
	DDX_Text(pDX, IDC_CHAN_DEVICE_IP, m_csDeviceIP);
	DDX_Control(pDX, IDC_COMBO_PROTOCOL, m_comboProtocol);
	DDX_Control(pDX, IDC_COMBO_TRANSPORT_TYPE, m_comboTransportType);
	//}}AFX_DATA_MAP
	
}

/*********************************************************
  Function:	BEGIN_MESSAGE_MAP
  Desc:		message map list
  Input:	
  Output:	
  Return:	
**********************************************************/
BEGIN_MESSAGE_MAP(CDlgChannelInfo, CDialog)
//{{AFX_MSG_MAP(CDlgChannelInfo)
ON_BN_CLICKED(ID_OK, OnBnClickedOk)
ON_BN_CLICKED(ID_CANCEL, OnBnClickedCancel)
ON_UPDATE_COMMAND_UI(ID_MENU_CHANNEL_INFO, OnUpdateMenuChannelInfo)
//}}AFX_MSG_MAP
END_MESSAGE_MAP()



// CDlgChannelInfo message handlers
/*********************************************************
  Function:	OnInitDialog
  Desc:		initialize channel info dialog
  Input:	
  Output:	
  Return:	
**********************************************************/
BOOL CDlgChannelInfo::OnInitDialog() 
{
	CDialog::OnInitDialog();
	if (m_pChanInfo == NULL)
	{
		return FALSE;
	}
	m_iChanNo = m_pChanInfo->iChanIndex +1;
	m_csChanName.Format("%s",m_pChanInfo->chChanName);
	m_csLocalNodeName.Format("%s",g_struDeviceInfo[m_pChanInfo->iDeviceIndex].chLocalNodeName);
	m_csDeviceIP.Format("%s",g_struDeviceInfo[m_pChanInfo->iDeviceIndex].chDeviceIP);
// 	m_comboProtocol.SetCurSel(m_pChanInfo->dwProtocol& 0x7fffffff);
// //	m_comboProtocol.SetCurSel( ( (m_pChanInfo->dwProtocol& 0x7fffffff) >= 7) ? ((m_pChanInfo->dwProtocol& 0x7fffffff)-3) : (m_pChanInfo->dwProtocol& 0x7fffffff));
// 	m_comboTransportType.SetCurSel((m_pChanInfo->dwProtocol>>31) & 0x01);

	m_comboProtocol.SetCurSel(m_pChanInfo->dwLinkMode);
	m_comboTransportType.SetCurSel(m_pChanInfo->dwStreamType);
	m_cmPreviewMode.SetCurSel(m_pChanInfo->dwPreviewMode);
	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

/*********************************************************
  Function:	OnBnClickedOk
  Desc:		modify channel info
  Input:	
  Output:	
  Return:	
**********************************************************/
void CDlgChannelInfo::OnBnClickedOk()
{
	UpdateData(TRUE);
	for (int i = 0; i < MAX_CHANNUM_V30; i++)
	{
		if (i == m_pChanInfo->iChanIndex)
		{
			continue;
		}

		if (0 == strcmp(g_struDeviceInfo[m_pChanInfo->iDeviceIndex].struChanInfo[i].chChanName,m_csChanName))
		{
			char szLan[1024] = {0};
			g_StringLanType(szLan, "��ͨ�������Ѵ���!", "this channel name is existed!");
			AfxMessageBox(szLan);
			return;
		}
	}

	DWORD dwTemp = m_comboProtocol.GetCurSel();
// 	if(dwTemp >= 4)
// 	{
// 		dwTemp += 3;
// 	}

	dwTemp |=(m_comboTransportType.GetCurSel()<< 31);

	if (strcmp(m_pChanInfo->chChanName,m_csChanName) != 0 || m_pChanInfo->dwProtocol != dwTemp || m_pChanInfo->dwProtocol!=m_cmPreviewMode.GetCurSel())
	{
		m_bChanged = TRUE;
	}

	sprintf(m_pChanInfo->chChanName,"%s",m_csChanName.GetBuffer(0));
	m_pChanInfo->dwProtocol = dwTemp;
	m_pChanInfo->dwPreviewMode = m_cmPreviewMode.GetCurSel();
	g_struDeviceInfo[m_pChanInfo->iDeviceIndex].struChanInfo[m_pChanInfo->iChanIndex].dwStreamType = m_comboTransportType.GetCurSel();
    g_struDeviceInfo[m_pChanInfo->iDeviceIndex].struChanInfo[m_pChanInfo->iChanIndex].dwLinkMode = m_comboProtocol.GetCurSel();

	OnOK();
}

/*********************************************************
  Function:	OnBnClickedCancel
  Desc:	    cancel channel info
  Input:	
  Output:	
  Return:	
**********************************************************/
void CDlgChannelInfo::OnBnClickedCancel()
{
	OnCancel();
}

void CDlgChannelInfo::OnUpdateMenuChannelInfo(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}