// MatDynamicTest.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "MatDynamicTest.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMatDynamicTest dialog


CMatDynamicTest::CMatDynamicTest(CWnd* pParent /*=NULL*/)
	: CDialog(CMatDynamicTest::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMatDynamicTest)
	m_RemoteIP = _T("172.7.103.253");
	m_RemoteSurveillace = 1;
	m_RemoteUser = _T("admin");
	m_RemotePass = _T("12345");
	m_strStreamMediaIp = _T("172.7.162.100");
	m_dwStreamMediaPort = 8888;
	m_bUseStreamMedia = FALSE;
	m_RemotePort = 0;
	m_csUrl = _T("");
	m_bUseUrl = FALSE;
	//}}AFX_DATA_INIT
    memset(&m_struProtoList, 0, sizeof(m_struProtoList));
}


void CMatDynamicTest::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMatDynamicTest)
	DDX_Control(pDX, IDC_COMBO_FACTYPE, m_FacTypeCtrl);
	DDX_Control(pDX, IDC_COMBOSTREAMMEDIAPRO, m_ComboStreamMediaPro);
	DDX_Control(pDX, IDC_COMBODECCHANNUM, m_DecChanCombo);
	DDX_Control(pDX, IDC_COMBOTRANSMODE, m_TransModeCombo);
	DDX_Control(pDX, IDC_COMBOPROTOCOL, m_TransProtocolCombo);
	DDX_Text(pDX, IDC_EDITREMOTEIP, m_RemoteIP);
	DDX_Text(pDX, IDC_EDITREMOTESURVE, m_RemoteSurveillace);
	DDX_Text(pDX, IDC_EDITREMOTENAME, m_RemoteUser);
	DDX_Text(pDX, IDC_EDITREMOTEPASS, m_RemotePass);
	DDX_Text(pDX, IDC_STREAMMEDIAIP, m_strStreamMediaIp);
	DDX_Text(pDX, IDC_STREAMMEDIAPORT, m_dwStreamMediaPort);
	DDX_Check(pDX, IDC_USESTREAMMEDIA, m_bUseStreamMedia);
	DDX_Text(pDX, IDC_EDITREMOTEPORT, m_RemotePort);
	DDV_MinMaxDWord(pDX, m_RemotePort, 0, 65535);
	DDX_Text(pDX, IDC_EDIT_URL, m_csUrl);
	DDX_Check(pDX, IDC_CHK_URL, m_bUseUrl);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMatDynamicTest, CDialog)
	//{{AFX_MSG_MAP(CMatDynamicTest)
	ON_BN_CLICKED(IDC_STARTDYNAMIC, OnStartdynamic)
	ON_BN_CLICKED(IDC_STOPDYNAMIC, OnStopdynamic)
	ON_BN_CLICKED(IDC_USESTREAMMEDIA, OnUsestreammedia)
	ON_BN_CLICKED(IDC_CHK_URL, OnChkUrl)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMatDynamicTest message handlers

void CMatDynamicTest::OnStartdynamic() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	
	NET_DVR_PU_STREAM_CFG_V41 dt;
	ZeroMemory(&dt, sizeof(dt));
	dt.dwSize = sizeof(NET_DVR_PU_STREAM_CFG_V41);
	dt.byStreamMode = 1;
	dt.uDecStreamMode.struDecStreamDev.struDevChanInfo.byChannel = (BYTE)m_RemoteSurveillace;
	dt.uDecStreamMode.struDecStreamDev.struDevChanInfo.byTransMode = m_TransModeCombo.GetCurSel();
	dt.uDecStreamMode.struDecStreamDev.struDevChanInfo.byTransProtocol = m_TransProtocolCombo.GetCurSel();
	sprintf((char *)dt.uDecStreamMode.struDecStreamDev.struDevChanInfo.sPassword, "%s", m_RemotePass);
	sprintf((char *)dt.uDecStreamMode.struDecStreamDev.struDevChanInfo.sUserName, "%s", m_RemoteUser);
	sprintf((char *)dt.uDecStreamMode.struDecStreamDev.struDevChanInfo.byAddress, "%s", m_RemoteIP);
	dt.uDecStreamMode.struDecStreamDev.struDevChanInfo.wDVRPort = m_RemotePort;
	
    char temp[20] = {0};
    m_FacTypeCtrl.GetLBText(m_FacTypeCtrl.GetCurSel(), temp);
    
    for (int i = 0; i < m_struProtoList.dwProtoNum; i++)
    {
        if (strcmp(temp, (const char *)m_struProtoList.struProto[i].byDescribe) == 0)
        {
            dt.uDecStreamMode.struDecStreamDev.struDevChanInfo.byFactoryType = m_struProtoList.struProto[i].dwType;
            break;
        }
    }
    

    
    if (m_bUseStreamMedia)
    {
		dt.uDecStreamMode.struDecStreamDev.struStreamMediaSvrCfg.byValid = 1;
        dt.uDecStreamMode.struDecStreamDev.struStreamMediaSvrCfg.wDevPort = m_dwStreamMediaPort;
        dt.uDecStreamMode.struDecStreamDev.struStreamMediaSvrCfg.byTransmitType = m_ComboStreamMediaPro.GetCurSel();
        sprintf((char *)dt.uDecStreamMode.struDecStreamDev.struStreamMediaSvrCfg.byAddress, "%s", m_strStreamMediaIp);		
    }
		
	if (m_bUseUrl)
	{
		dt.uDecStreamMode.struUrlInfo.byEnable = 1;
		sprintf((char *)dt.uDecStreamMode.struUrlInfo.strURL, "%s", m_csUrl);
		dt.byStreamMode = 2;
	}

	if (!NET_DVR_MatrixStartDynamic_V41(m_lServerID, m_DecChanCombo.GetCurSel()+m_lStartChan, &dt))
	{
		CString tmp;
		tmp.Format("Error: NET_DVR_MatrixStartDynamic = %d\n", NET_DVR_GetLastError());
		AfxMessageBox(tmp);
		return;
	}

	MessageBox("Start successfully!");
}

void CMatDynamicTest::OnStopdynamic() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	if (!NET_DVR_MatrixStopDynamic(m_lServerID, m_DecChanCombo.GetCurSel() + m_lStartChan))
	{
		TRACE("\nError: NET_DVR_MatrixStopDynamic = %d\n", NET_DVR_GetLastError());
        CString str;
        str.Format("Error Code : %d", NET_DVR_GetLastError());
        AfxMessageBox(str);
		return;
	}
	char szLan[128] = {0};
	g_StringLanType(szLan, "成功停止", "Stop successfully");
	AfxMessageBox(szLan);
}

BOOL CMatDynamicTest::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	CString tmp;
	char szLan[128] = {0};
	g_StringLanType(szLan, "通道", "Channel");
	for (int i=0; i<m_iChannelnumber;i++)
	{
		tmp.Format("%s%d", szLan, i + m_lStartChan);
		m_DecChanCombo.AddString(tmp);
	}

    if (NET_DVR_GetIPCProtoList(m_lServerID, &m_struProtoList))
    {
        for (int i = 0; i < (int)m_struProtoList.dwProtoNum; i++)
        {
            memset(szLan, 0, DESC_LEN);
            memcpy(szLan, m_struProtoList.struProto[i].byDescribe, DESC_LEN);
            m_FacTypeCtrl.AddString(szLan);
		}
        m_FacTypeCtrl.SetCurSel(0);
    } 
	else
	{
		MessageBox(NET_DVR_GetErrorMsg());
	}

	m_DecChanCombo.SetCurSel(0);
	m_TransProtocolCombo.SetCurSel(0);
	m_TransModeCombo.SetCurSel(0);
    m_bUseStreamMedia = 0;
	UpdateData(FALSE);
    OnUsestreammedia();
	OnChkUrl();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CMatDynamicTest::OnUsestreammedia() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
    if (m_bUseStreamMedia)
    {
        GetDlgItem(IDC_STREAMMEDIAIP)->EnableWindow(TRUE);
        GetDlgItem(IDC_STREAMMEDIAPORT)->EnableWindow(TRUE);
        GetDlgItem(IDC_COMBOSTREAMMEDIAPRO)->EnableWindow(TRUE);
		m_bUseUrl = FALSE;
		UpdateData(FALSE);
		OnChkUrl();
    }
    else
    {
        GetDlgItem(IDC_STREAMMEDIAIP)->EnableWindow(FALSE);
        GetDlgItem(IDC_STREAMMEDIAPORT)->EnableWindow(FALSE);
        GetDlgItem(IDC_COMBOSTREAMMEDIAPRO)->EnableWindow(FALSE);
    }	
    UpdateData(FALSE);	
}

void CMatDynamicTest::OnChkUrl() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	if (m_bUseUrl)
	{
		GetDlgItem(IDC_EDIT_URL)->EnableWindow(TRUE);
		m_bUseStreamMedia = FALSE;
		UpdateData(FALSE);
		OnUsestreammedia();
	}
	else
	{
		GetDlgItem(IDC_EDIT_URL)->EnableWindow(FALSE);
	}
	UpdateData(FALSE);	
}
