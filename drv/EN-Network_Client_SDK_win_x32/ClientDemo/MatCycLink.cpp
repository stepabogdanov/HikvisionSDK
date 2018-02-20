// MatCycLink.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "MatCycLink.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMatCycLink dialog


CMatCycLink::CMatCycLink(CWnd* pParent /*=NULL*/)
	: CDialog(CMatCycLink::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMatCycLink)
	m_DVRChannel = 0;
	m_DVRIP = _T("");
	m_DVRPasswd = _T("");
	m_DVRPort = 0;
	m_DVRUser = _T("");
	m_PoolTime = 0;
	m_bCheckConnectChan = FALSE;
	m_bUseStreamMedia = FALSE;
	m_strStreamMediaIp = _T("");
	m_dwStreamMediaPort = 0;
	m_bUseUrl = FALSE;
	m_csUrl = _T("");
	//}}AFX_DATA_INIT
	m_iChanSel = -1;
	for (int i=0; i<32; i++)
	{
		m_CycLink[i] = FALSE;
	}
    memset(&m_struProtoList, 0, sizeof(m_struProtoList));
}


void CMatCycLink::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMatCycLink)
	DDX_Control(pDX, IDC_COMBO_STREAM_MODE, m_comboStreamMode);
	DDX_Control(pDX, IDC_COMBO_FACTYPE, m_FacTypeCtrl);
	DDX_Control(pDX, IDC_COMBOSTREAMMEDIAPRO, m_ComboStreamMediaPro);
	DDX_Control(pDX, IDC_COMBOTRANSTYPE, m_TransModesCombo);
	DDX_Control(pDX, IDC_COMBOTRANSMODE, m_TransProtocolCombo);
	DDX_Control(pDX, IDC_COMBOSWITCH, m_SwitchCombo);
	DDX_Control(pDX, IDC_COMBODECCHAN2, m_DecChanCombo2);
	DDX_Control(pDX, IDC_COMBODECCHAN, m_DecChanCombo);
	DDX_Control(pDX, IDC_COMBOCONCHAN, m_ConnectChanCombo);
	DDX_Text(pDX, IDC_EDITDVRCHAN, m_DVRChannel);
	DDX_Text(pDX, IDC_EDITDVRIP, m_DVRIP);
	DDX_Text(pDX, IDC_EDITDVRPASSWD, m_DVRPasswd);
	DDX_Text(pDX, IDC_EDITDVRPORT, m_DVRPort);
	DDX_Text(pDX, IDC_EDITDVRUSER, m_DVRUser);
	DDX_Text(pDX, IDC_EDITPOOLTIME, m_PoolTime);
	DDX_Check(pDX, IDC_CHECKCONCHAN, m_bCheckConnectChan);
	DDX_Check(pDX, IDC_USESTREAMMEDIA, m_bUseStreamMedia);
	DDX_Text(pDX, IDC_STREAMMEDIAIP, m_strStreamMediaIp);
	DDX_Text(pDX, IDC_STREAMMEDIAPORT, m_dwStreamMediaPort);
	DDX_Check(pDX, IDC_CHK_URL, m_bUseUrl);
	DDX_Text(pDX, IDC_EDIT_URL, m_csUrl);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMatCycLink, CDialog)
	//{{AFX_MSG_MAP(CMatCycLink)
	ON_CBN_SELCHANGE(IDC_COMBODECCHAN, OnSelchangeCombodecchan)
	ON_CBN_SELCHANGE(IDC_COMBOCONCHAN, OnSelchangeComboconchan)
	ON_BN_CLICKED(IDC_SAVEPARA, OnSavepara)
	ON_BN_CLICKED(IDC_SETPARAM, OnSetparam)
	ON_BN_CLICKED(IDC_SINGLEGET, OnSingleget)
	ON_BN_CLICKED(IDC_WHOLEGET, OnWholeget)
	ON_BN_CLICKED(IDC_SINGLESET, OnSingleset)
	ON_BN_CLICKED(IDC_CHECKCONCHAN, OnCheckconchan)
	ON_CBN_SELCHANGE(IDC_COMBODECCHAN2, OnSelchangeCombodecchan2)
	ON_BN_CLICKED(IDC_USESTREAMMEDIA, OnUsestreammedia)
	ON_BN_CLICKED(IDC_CHK_URL, OnChkUrl)
	ON_CBN_SELCHANGE(IDC_COMBO_STREAM_MODE, OnSelchangeComboStreamMode)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMatCycLink message handlers

BOOL CMatCycLink::OnInitDialog() 
{
	CDialog::OnInitDialog();
	int i = 0;

	ZeroMemory(&m_MatLoopDec, sizeof(NET_DVR_MATRIX_LOOP_DECINFO_V41));
	// TODO: Add extra initialization here
	DWORD chanNum = 0;
	CString tmp;
	i = 0;
	for (i=0; i<m_iChannelnumber; i++)
	{
		chanNum = i + m_lStartChan;
		tmp.Format("%d", chanNum);
		m_DecChanCombo.AddString(tmp);
        m_DecChanCombo2.AddString(tmp);
	}

    char szLan [128] = {0};
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
    
	if (!NET_DVR_MatrixGetLoopDecChanInfo_V41(m_lServerID, m_lStartChan, &m_MatLoopDec))
	{
		TRACE("\nError: NET_DVR_MatrixGetLoopDecChanInfo[%d] = %d\n", i, NET_DVR_GetLastError());
	}
	else
	{
		TRACE("NET_DVR_MatrixGetLoopDecChanInfo_V41 succ");
    }

	if (!NET_DVR_MatrixGetLoopDecChanEnable(m_lServerID, m_lStartChan, &chanNum))
	{
		TRACE("\nError: NET_DVR_MatrixGetLoopDecChanEnable = %d\n", NET_DVR_GetLastError());
	}
	else
	{
		m_SwitchCombo.SetCurSel(chanNum);
	}
	m_DecChanCombo.SetCurSel(0);
	m_DecChanCombo2.SetCurSel(0);
	m_iChanSel = 0;
	for (i=0; i<MAX_CYCLE_CHAN_V30; i++)
	{
		tmp.Format("%d", i + m_lStartChan);
		m_ConnectChanCombo.AddString(tmp);
	}

	m_ConnectChanCombo.SetCurSel(0);
	m_PoolTime = m_MatLoopDec.dwPoolTime;
	m_bCheckConnectChan = m_MatLoopDec.struchanConInfo[0].byEnable;
	if (m_MatLoopDec.struchanConInfo[0].byEnable)
	{
		if (m_MatLoopDec.struchanConInfo[0].byStreamMode == 1 && m_MatLoopDec.struchanConInfo[0].uDecStreamMode.struDecStreamDev.struStreamMediaSvrCfg.byValid == 1)
		{
			m_bUseStreamMedia = TRUE;
			m_bUseUrl = FALSE;
		}
		else if (m_MatLoopDec.struchanConInfo[0].byStreamMode == 2)
		{
			m_bUseStreamMedia = FALSE;
			m_bUseUrl = TRUE;
		}
		else
		{
			m_bUseStreamMedia = FALSE;
			m_bUseUrl = FALSE;
		}

		m_comboStreamMode.SetCurSel(m_MatLoopDec.struchanConInfo[0].byStreamMode);

		if (!m_bUseUrl)
		{
			m_DVRIP.Format("%s", m_MatLoopDec.struchanConInfo[0].uDecStreamMode.struDecStreamDev.struDevChanInfo.byAddress);
			m_DVRPort = m_MatLoopDec.struchanConInfo[0].uDecStreamMode.struDecStreamDev.struDevChanInfo.wDVRPort;
			m_DVRUser.Format("%s", m_MatLoopDec.struchanConInfo[0].uDecStreamMode.struDecStreamDev.struDevChanInfo.sUserName);
			m_DVRPasswd.Format("%s", m_MatLoopDec.struchanConInfo[0].uDecStreamMode.struDecStreamDev.struDevChanInfo.sPassword);
			m_DVRChannel = m_MatLoopDec.struchanConInfo[0].uDecStreamMode.struDecStreamDev.struDevChanInfo.byChannel;
			m_TransModesCombo.SetCurSel(m_MatLoopDec.struchanConInfo[0].uDecStreamMode.struDecStreamDev.struDevChanInfo.byTransMode);
		    m_TransProtocolCombo.SetCurSel(m_MatLoopDec.struchanConInfo[0].uDecStreamMode.struDecStreamDev.struDevChanInfo.byTransProtocol);
		}		
        //m_FacTypeCtrl.SetCurSel(m_MatLoopDec.struchanConInfo[0].struDevChanInfo.byFactoryType);
        int i = 0;
        for(i = 0; i < m_struProtoList.dwProtoNum; i++)
        {
            if (m_MatLoopDec.struchanConInfo[0].uDecStreamMode.struDecStreamDev.struDevChanInfo.byFactoryType == m_struProtoList.struProto[i].dwType) 
            {
                m_FacTypeCtrl.SetCurSel(i);
                break;
            }
        }
        if (i >= m_struProtoList.dwProtoNum) 
        {
            m_FacTypeCtrl.SetCurSel(-1);
        }
        //m_bUseStreamMedia = m_MatLoopDec.struchanConInfo[0].uDecStreamMode.struDecStreamDev.struStreamMediaSvrCfg.byValid;
        if (m_bUseStreamMedia)
        {
            m_strStreamMediaIp.Format("%s", m_MatLoopDec.struchanConInfo[0].uDecStreamMode.struDecStreamDev.struStreamMediaSvrCfg.byAddress);
            m_dwStreamMediaPort = m_MatLoopDec.struchanConInfo[0].uDecStreamMode.struDecStreamDev.struStreamMediaSvrCfg.wDevPort;
            m_ComboStreamMediaPro.SetCurSel(m_MatLoopDec.struchanConInfo[0].uDecStreamMode.struDecStreamDev.struStreamMediaSvrCfg.byTransmitType);
            GetDlgItem(IDC_STREAMMEDIAIP)->EnableWindow(TRUE);
            GetDlgItem(IDC_STREAMMEDIAPORT)->EnableWindow(TRUE);
            GetDlgItem(IDC_COMBOSTREAMMEDIAPRO)->EnableWindow(TRUE);
        }
        else
        {
            GetDlgItem(IDC_STREAMMEDIAIP)->EnableWindow(FALSE);
            GetDlgItem(IDC_STREAMMEDIAPORT)->EnableWindow(FALSE);
            GetDlgItem(IDC_COMBOSTREAMMEDIAPRO)->EnableWindow(FALSE);
        }
		//m_bUseUrl = m_MatLoopDec.struchanConInfo[0].uDecStreamMode.struUrlInfo.byEnable;
		if (m_bUseUrl)
		{
			GetDlgItem(IDC_EDIT_URL)->EnableWindow(TRUE);
		}
		{
			GetDlgItem(IDC_EDIT_URL)->EnableWindow(FALSE);
		}
		m_csUrl.Format("%s", m_MatLoopDec.struchanConInfo[0].uDecStreamMode.struUrlInfo.strURL);
	}
	else
	{
		m_comboStreamMode.SetCurSel(m_MatLoopDec.struchanConInfo[0].byStreamMode);
		EnableConChan(FALSE);
	}

	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CMatCycLink::EnableConChan(BOOL bEnable)
{
	GetDlgItem(IDC_COMBO_STREAM_MODE)->EnableWindow(bEnable);
	GetDlgItem(IDC_EDITDVRIP)->EnableWindow(bEnable);
	GetDlgItem(IDC_EDITDVRPORT)->EnableWindow(bEnable);
	GetDlgItem(IDC_EDITDVRCHAN)->EnableWindow(bEnable);
	GetDlgItem(IDC_EDITDVRUSER)->EnableWindow(bEnable);
	GetDlgItem(IDC_EDITDVRPASSWD)->EnableWindow(bEnable);
	GetDlgItem(IDC_COMBOTRANSMODE)->EnableWindow(bEnable);
	GetDlgItem(IDC_COMBOTRANSTYPE)->EnableWindow(bEnable);

    GetDlgItem(IDC_USESTREAMMEDIA)->EnableWindow(bEnable);
	GetDlgItem(IDC_COMBO_FACTYPE)->EnableWindow(bEnable);
	//m_bUseStreamMedia = bEnable;
	UpdateData(FALSE);
    OnUsestreammedia();
	OnChkUrl();
}

void CMatCycLink::OnSelchangeCombodecchan() 
{
	// TODO: Add your control notification handler code here
	int sel = m_DecChanCombo.GetCurSel();
	if (sel == m_iChanSel)
	{
		return;
	}
	m_iChanSel = sel;
	if (!NET_DVR_MatrixGetLoopDecChanInfo_V41(m_lServerID, m_iChanSel + m_lStartChan, &m_MatLoopDec))
	{
		g_pMainDlg->AddLog(g_struDeviceInfo[m_lServerID].iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_MatrixGetLoopDecChanInfo_V41");
		TRACE("\nError: NET_DVR_MatrixGetLoopDecChanInfo[%d] = %d\n", m_iChanSel + m_lStartChan, NET_DVR_GetLastError());
    }
	else
	{
		g_pMainDlg->AddLog(g_struDeviceInfo[m_lStartChan].iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_MatrixGetLoopDecChanInfo_V41");
	}

	m_PoolTime = m_MatLoopDec.dwPoolTime;
	m_ConnectChanCombo.SetCurSel(0);
	m_bCheckConnectChan = m_MatLoopDec.struchanConInfo[0].byEnable;
	if (m_MatLoopDec.struchanConInfo[0].byEnable)
	{		
		if (m_MatLoopDec.struchanConInfo[0].byStreamMode == 2)
		{
			m_bUseStreamMedia = FALSE;
			m_bUseUrl = TRUE;
		}
		else if (m_MatLoopDec.struchanConInfo[0].byStreamMode == 1 && m_MatLoopDec.struchanConInfo[0].uDecStreamMode.struDecStreamDev.struStreamMediaSvrCfg.byValid == 1)
		{
			m_bUseStreamMedia = TRUE;
			m_bUseUrl = FALSE;
		}
		else
		{
			m_bUseStreamMedia = FALSE;
			m_bUseUrl = FALSE;
		}
		
		m_comboStreamMode.SetCurSel(m_MatLoopDec.struchanConInfo[0].byStreamMode - 1);
        //m_bUseStreamMedia = m_MatLoopDec.struchanConInfo[sel].uDecStreamMode.struDecStreamDev.struStreamMediaSvrCfg.byValid;
        if (m_bUseStreamMedia)
        {
            m_dwStreamMediaPort = m_MatLoopDec.struchanConInfo[0].uDecStreamMode.struDecStreamDev.struStreamMediaSvrCfg.wDevPort;
            m_strStreamMediaIp.Format("%s", m_MatLoopDec.struchanConInfo[0].uDecStreamMode.struDecStreamDev.struStreamMediaSvrCfg.byAddress);
            m_ComboStreamMediaPro.SetCurSel(m_MatLoopDec.struchanConInfo[0].uDecStreamMode.struDecStreamDev.struStreamMediaSvrCfg.byTransmitType);
        }

		EnableConChan(TRUE);

        int i = 0;
        for(i = 0; i < m_struProtoList.dwProtoNum; i++)
        {
            if (m_MatLoopDec.struchanConInfo[0].uDecStreamMode.struDecStreamDev.struDevChanInfo.byFactoryType == m_struProtoList.struProto[i].dwType) 
            {
                m_FacTypeCtrl.SetCurSel(i);
                break;
            }
        }
        if (i >= m_struProtoList.dwProtoNum) 
        {
            m_FacTypeCtrl.SetCurSel(-1);
        }
		if (!m_bUseUrl)
		{
			m_FacTypeCtrl.SetCurSel(m_MatLoopDec.struchanConInfo[0].uDecStreamMode.struDecStreamDev.struDevChanInfo.byFactoryType);
			
			m_DVRIP.Format("%s", m_MatLoopDec.struchanConInfo[0].uDecStreamMode.struDecStreamDev.struDevChanInfo.byAddress);
			m_DVRPort = m_MatLoopDec.struchanConInfo[0].uDecStreamMode.struDecStreamDev.struDevChanInfo.wDVRPort;
			m_DVRUser.Format("%s", m_MatLoopDec.struchanConInfo[0].uDecStreamMode.struDecStreamDev.struDevChanInfo.sUserName);
			m_DVRPasswd.Format("%s", m_MatLoopDec.struchanConInfo[0].uDecStreamMode.struDecStreamDev.struDevChanInfo.sPassword);
			m_DVRChannel = m_MatLoopDec.struchanConInfo[0].uDecStreamMode.struDecStreamDev.struDevChanInfo.byChannel;
			m_TransModesCombo.SetCurSel(m_MatLoopDec.struchanConInfo[0].uDecStreamMode.struDecStreamDev.struDevChanInfo.byTransMode);
		    m_TransProtocolCombo.SetCurSel(m_MatLoopDec.struchanConInfo[0].uDecStreamMode.struDecStreamDev.struDevChanInfo.byTransProtocol);
		}
        

		//m_bUseUrl = m_MatLoopDec.struchanConInfo[0].uDecStreamMode.struUrlInfo.byEnable;
		if (m_bUseUrl)
		{
			m_csUrl.Format("%s", m_MatLoopDec.struchanConInfo[0].uDecStreamMode.struUrlInfo.strURL);
		}
	}
	else
	{
		m_bUseStreamMedia = FALSE;
		m_bUseUrl = FALSE;
		EnableConChan(FALSE);
	}

	UpdateData(FALSE);
}

void CMatCycLink::OnSelchangeComboconchan() 
{
	// TODO: Add your control notification handler code here
	int sel = m_ConnectChanCombo.GetCurSel();

	m_bCheckConnectChan = m_MatLoopDec.struchanConInfo[sel].byEnable;
	TRACE("\n### m_bCheckConnectChan = 0x%x\n", m_bCheckConnectChan);	
	if (m_MatLoopDec.struchanConInfo[sel].byEnable)
	{

		EnableConChan(TRUE);
		m_comboStreamMode.SetCurSel(m_MatLoopDec.struchanConInfo[sel].byStreamMode);
		m_DVRIP.Format("%s", m_MatLoopDec.struchanConInfo[sel].uDecStreamMode.struDecStreamDev.struDevChanInfo.byAddress);
		m_DVRPort = m_MatLoopDec.struchanConInfo[sel].uDecStreamMode.struDecStreamDev.struDevChanInfo.wDVRPort;
		m_DVRUser.Format("%s", m_MatLoopDec.struchanConInfo[sel].uDecStreamMode.struDecStreamDev.struDevChanInfo.sUserName);
		m_DVRPasswd.Format("%s", m_MatLoopDec.struchanConInfo[sel].uDecStreamMode.struDecStreamDev.struDevChanInfo.sPassword);
		m_DVRChannel = m_MatLoopDec.struchanConInfo[sel].uDecStreamMode.struDecStreamDev.struDevChanInfo.byChannel;
		m_TransModesCombo.SetCurSel(m_MatLoopDec.struchanConInfo[sel].uDecStreamMode.struDecStreamDev.struDevChanInfo.byTransMode);
		m_TransProtocolCombo.SetCurSel(m_MatLoopDec.struchanConInfo[sel].uDecStreamMode.struDecStreamDev.struDevChanInfo.byTransProtocol);
        //m_FacTypeCtrl.SetCurSel(m_MatLoopDec.struchanConInfo[sel].struDevChanInfo.byFactoryType);
        
        int i = 0;
        for(i = 0; i < m_struProtoList.dwProtoNum; i++)
        {
            if (m_MatLoopDec.struchanConInfo[sel].uDecStreamMode.struDecStreamDev.struDevChanInfo.byFactoryType == m_struProtoList.struProto[i].dwType) 
            {
                m_FacTypeCtrl.SetCurSel(i);
                break;
            }
        }
        if (i >= m_struProtoList.dwProtoNum) 
        {
            m_FacTypeCtrl.SetCurSel(-1);
        }

		if (m_MatLoopDec.struchanConInfo[sel].byStreamMode == 1 && m_MatLoopDec.struchanConInfo[sel].uDecStreamMode.struDecStreamDev.struStreamMediaSvrCfg.byValid == 1)
		{
			m_bUseStreamMedia = TRUE;
			m_bUseUrl = FALSE;
		}
		else if (m_MatLoopDec.struchanConInfo[sel].byStreamMode == 2)
		{
			m_bUseStreamMedia = FALSE;
			m_bUseUrl = TRUE;
		}
		else
		{
			m_bUseStreamMedia = FALSE;
			m_bUseUrl = FALSE;
		}
		//m_bUseStreamMedia = m_MatLoopDec.struchanConInfo[sel].uDecStreamMode.struDecStreamDev.struStreamMediaSvrCfg.byValid;
		if (m_bUseStreamMedia)
		{
			m_dwStreamMediaPort = m_MatLoopDec.struchanConInfo[sel].uDecStreamMode.struDecStreamDev.struStreamMediaSvrCfg.wDevPort;
			m_strStreamMediaIp.Format("%s", m_MatLoopDec.struchanConInfo[sel].uDecStreamMode.struDecStreamDev.struStreamMediaSvrCfg.byAddress);
			m_ComboStreamMediaPro.SetCurSel(m_MatLoopDec.struchanConInfo[sel].uDecStreamMode.struDecStreamDev.struStreamMediaSvrCfg.byTransmitType);
		}
		
		//m_bUseUrl = m_MatLoopDec.struchanConInfo[sel].uDecStreamMode.struUrlInfo.byEnable;
		if (m_bUseUrl)
		{
			m_csUrl.Format("%s", m_MatLoopDec.struchanConInfo[sel].uDecStreamMode.struUrlInfo.strURL);
		}
	}
	else
	{
		m_comboStreamMode.SetCurSel(m_MatLoopDec.struchanConInfo[sel].byStreamMode);
		EnableConChan(FALSE);
	}

	

	UpdateData(FALSE);
    OnUsestreammedia();
	OnChkUrl();
}

void CMatCycLink::OnSavepara() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	int sel = m_ConnectChanCombo.GetCurSel();
	ZeroMemory(&m_MatLoopDec.struchanConInfo[sel], sizeof(m_MatLoopDec.struchanConInfo[sel]));	
	m_MatLoopDec.struchanConInfo[sel].byEnable = m_bCheckConnectChan;
	if (m_bCheckConnectChan)
	{
		m_MatLoopDec.struchanConInfo[sel].byStreamMode = m_comboStreamMode.GetCurSel();
		m_MatLoopDec.struchanConInfo[sel].uDecStreamMode.struDecStreamDev.struDevChanInfo.byChannel = m_DVRChannel;
		m_MatLoopDec.struchanConInfo[sel].uDecStreamMode.struDecStreamDev.struDevChanInfo.byTransMode = m_TransModesCombo.GetCurSel();
		m_MatLoopDec.struchanConInfo[sel].uDecStreamMode.struDecStreamDev.struDevChanInfo.byTransProtocol = m_TransProtocolCombo.GetCurSel();
		m_MatLoopDec.struchanConInfo[sel].uDecStreamMode.struDecStreamDev.struDevChanInfo.wDVRPort = m_DVRPort;
		sprintf((char *)m_MatLoopDec.struchanConInfo[sel].uDecStreamMode.struDecStreamDev.struDevChanInfo.byAddress, "%s", m_DVRIP);
		sprintf((char *)m_MatLoopDec.struchanConInfo[sel].uDecStreamMode.struDecStreamDev.struDevChanInfo.sUserName, "%s", m_DVRUser);
		sprintf((char *)m_MatLoopDec.struchanConInfo[sel].uDecStreamMode.struDecStreamDev.struDevChanInfo.sPassword, "%s", m_DVRPasswd);
        char temp[20] = {0};
        m_FacTypeCtrl.GetLBText(m_FacTypeCtrl.GetCurSel(), temp);
        
        for (int i = 0; i < m_struProtoList.dwProtoNum; i++)
        {
            if (strcmp(temp, (const char *)m_struProtoList.struProto[i].byDescribe) == 0)
            {
                m_MatLoopDec.struchanConInfo[sel].uDecStreamMode.struDecStreamDev.struDevChanInfo.byFactoryType = m_struProtoList.struProto[i].dwType;
                break;
            }
        }
        
        //TRACE("m_bUseStreamMedia ==== %d", m_bUseStreamMedia);
        if (m_bUseStreamMedia)
        {
			m_MatLoopDec.struchanConInfo[sel].uDecStreamMode.struDecStreamDev.struStreamMediaSvrCfg.byValid = m_bUseStreamMedia;
            m_MatLoopDec.struchanConInfo[sel].uDecStreamMode.struDecStreamDev.struStreamMediaSvrCfg.wDevPort = m_dwStreamMediaPort;
            m_MatLoopDec.struchanConInfo[sel].uDecStreamMode.struDecStreamDev.struStreamMediaSvrCfg.byTransmitType = m_ComboStreamMediaPro.GetCurSel();
            sprintf((char *)m_MatLoopDec.struchanConInfo[sel].uDecStreamMode.struDecStreamDev.struStreamMediaSvrCfg.byAddress, "%s", m_strStreamMediaIp);
            //TRACE(m_MatLoopDec.struchanConInfo[sel].streamMediaServerCfg.byAddress);
        }		
		
		if (m_bUseUrl)
		{
			m_MatLoopDec.struchanConInfo[sel].uDecStreamMode.struUrlInfo.byEnable = m_bUseUrl;
			sprintf((char *)m_MatLoopDec.struchanConInfo[sel].uDecStreamMode.struUrlInfo.strURL, "%s", m_csUrl);
		}
	}
}

void CMatCycLink::OnSetparam() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	int sel = m_ConnectChanCombo.GetCurSel();
	ZeroMemory(&m_MatLoopDec.struchanConInfo[sel], sizeof(m_MatLoopDec.struchanConInfo[sel]));
	m_MatLoopDec.struchanConInfo[sel].byEnable = m_bCheckConnectChan;
	if (m_bCheckConnectChan)
	{
		m_MatLoopDec.struchanConInfo[sel].byStreamMode = m_comboStreamMode.GetCurSel();
		m_MatLoopDec.struchanConInfo[sel].uDecStreamMode.struDecStreamDev.struDevChanInfo.byChannel = m_DVRChannel;
		m_MatLoopDec.struchanConInfo[sel].uDecStreamMode.struDecStreamDev.struDevChanInfo.byTransMode = m_TransModesCombo.GetCurSel();
		m_MatLoopDec.struchanConInfo[sel].uDecStreamMode.struDecStreamDev.struDevChanInfo.byTransProtocol = m_TransProtocolCombo.GetCurSel();
		m_MatLoopDec.struchanConInfo[sel].uDecStreamMode.struDecStreamDev.struDevChanInfo.wDVRPort = m_DVRPort;
		sprintf((char *)m_MatLoopDec.struchanConInfo[sel].uDecStreamMode.struDecStreamDev.struDevChanInfo.byAddress, "%s", m_DVRIP);
		sprintf((char *)m_MatLoopDec.struchanConInfo[sel].uDecStreamMode.struDecStreamDev.struDevChanInfo.sUserName, "%s", m_DVRUser);
		sprintf((char *)m_MatLoopDec.struchanConInfo[sel].uDecStreamMode.struDecStreamDev.struDevChanInfo.sPassword, "%s", m_DVRPasswd);
        char temp[20] = {0};
        m_FacTypeCtrl.GetLBText(m_FacTypeCtrl.GetCurSel(), temp);
        
        for (int i = 0; i < m_struProtoList.dwProtoNum; i++)
        {
            if (strcmp(temp, (const char *)m_struProtoList.struProto[i].byDescribe) == 0)
            {
                m_MatLoopDec.struchanConInfo[sel].uDecStreamMode.struDecStreamDev.struDevChanInfo.byFactoryType = m_struProtoList.struProto[i].dwType;
                break;
            }
        }
        
        TRACE("m_bUseStreamMedia ==== %d", m_bUseStreamMedia);
        if (m_bUseStreamMedia)
        {
			m_MatLoopDec.struchanConInfo[sel].uDecStreamMode.struDecStreamDev.struStreamMediaSvrCfg.byValid = m_bUseStreamMedia;
            m_MatLoopDec.struchanConInfo[sel].uDecStreamMode.struDecStreamDev.struStreamMediaSvrCfg.wDevPort = m_dwStreamMediaPort;
            m_MatLoopDec.struchanConInfo[sel].uDecStreamMode.struDecStreamDev.struStreamMediaSvrCfg.byTransmitType = m_ComboStreamMediaPro.GetCurSel();
            sprintf((char *)m_MatLoopDec.struchanConInfo[sel].uDecStreamMode.struDecStreamDev.struStreamMediaSvrCfg.byAddress, "%s", m_strStreamMediaIp);
            //TRACE(m_MatLoopDec.struchanConInfo[sel].streamMediaServerCfg.byAddress);
        }		
		
		if (m_bUseUrl)
		{
			m_MatLoopDec.struchanConInfo[sel].uDecStreamMode.struUrlInfo.byEnable = m_bUseUrl;
			sprintf((char *)m_MatLoopDec.struchanConInfo[sel].uDecStreamMode.struUrlInfo.strURL, "%s", m_csUrl);
		}
	}
	m_MatLoopDec.dwPoolTime = m_PoolTime;

	BOOL error = FALSE;

    m_MatLoopDec.dwSize = sizeof(NET_DVR_MATRIX_LOOP_DECINFO_V41);
	//TRACE("sizeof(NET_DVR_MATRIX_LOOP_DECINFO_V30) = %d", sizeof(NET_DVR_MATRIX_LOOP_DECINFO_V30));
    if (!NET_DVR_MatrixSetLoopDecChanInfo_V41(m_lServerID, m_iChanSel + m_lStartChan, &m_MatLoopDec/*[m_iChanSel]*/))
    {
        //TRACE("\nError: NET_DVR_MatrixSetLoopDecChanInfo = %d\n", NET_DVR_GetLastError());
        CString stmp;
        stmp.Format("\nError: NET_DVR_MatrixSetLoopDecChanInfo = %d\n", NET_DVR_GetLastError());
        AfxMessageBox(stmp);
        //TRACE(stmp);
        error = TRUE;
    }
    
    if (!error)
    {
		char szLan[128] = {0};
		g_StringLanType(szLan, "保存成功", "save successfully");
		AfxMessageBox(szLan);
	}
}

void CMatCycLink::OnSingleget() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	int sel = m_DecChanCombo2.GetCurSel();
	DWORD flg = 0;
	if (!NET_DVR_MatrixGetLoopDecChanEnable(m_lServerID, sel+m_lStartChan, &flg))
	{
		TRACE("\nError: NET_DVR_MatrixGetLoopDecChanEnable[%d] = %d\n", sel+m_lStartChan, NET_DVR_GetLastError());
		return;
	}
	if (flg)
	{
		m_CycLink[sel] = TRUE;
	}
	else
	{
		m_CycLink[sel] = FALSE;
	}
	m_SwitchCombo.SetCurSel(m_CycLink[sel]);
	UpdateData(FALSE);
	char szLan[128] = {0};
	g_StringLanType(szLan, "获取成功", "Get successfully");
	AfxMessageBox(szLan);
}

void CMatCycLink::OnWholeget() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	
	int sel = m_DecChanCombo2.GetCurSel();
	DWORD flg = 0;
	if (!NET_DVR_MatrixGetLoopDecEnable(m_lServerID, &flg))
	{
		TRACE("\nError: NET_DVR_MatrixGetLoopDecEnable = %d\n", NET_DVR_GetLastError());
		return;
	}
	TRACE("\n### 0x%x\n", flg);
	for (int i=0; i<m_iChannelnumber; i++)
	{
		if (flg&0x1)
		{
			m_CycLink[i] = TRUE;
		}
		else
		{
			m_CycLink[i] = FALSE;
		}
		flg = flg>>1;
		TRACE("\n### %d\n", m_CycLink[i]);
	}
	m_SwitchCombo.SetCurSel(m_CycLink[sel]);
	UpdateData(FALSE);
	char szLan[128] = {0};
	g_StringLanType(szLan, "获取成功", "Get successfully");
	AfxMessageBox(szLan);
}

void CMatCycLink::OnSingleset() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	int sel = m_DecChanCombo2.GetCurSel();
	BOOL flg = FALSE;
	if (m_SwitchCombo.GetCurSel())
	{
		flg = TRUE;
	}
	if (!NET_DVR_MatrixSetLoopDecChanEnable(m_lServerID, sel+m_lStartChan, flg))
	{
		TRACE("\nError: NET_DVR_MatrixSetLoopDecChanEnable[%d] = %d\n", sel+m_lStartChan, NET_DVR_GetLastError());
		return;
	}
	MessageBox("Set successfully!");
}

void CMatCycLink::OnCheckconchan() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	EnableConChan(m_bCheckConnectChan);
}

void CMatCycLink::OnSelchangeCombodecchan2() 
{
	// TODO: Add your control notification handler code here
	int sel = m_DecChanCombo2.GetCurSel();
	
	m_SwitchCombo.SetCurSel(m_CycLink[sel]);
	UpdateData(FALSE);
}

void CMatCycLink::OnUsestreammedia() 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE);
	
//	int sel = m_ConnectChanCombo.GetCurSel();
	//	m_bCheckConnectChan = m_MatLoopDec.struchanConInfo[sel].dwEnable;
	//	if (m_bCheckConnectChan) 
	//	{
	//		m_bUseStreamMedia = m_MatLoopDec.struchanConInfo[sel].streamMediaServerCfg.byValid;
	//	}
	
	//
	/*
	if (m_bUseStreamMedia)
	{*/
    
	GetDlgItem(IDC_STREAMMEDIAIP)->EnableWindow(m_bUseStreamMedia);
	GetDlgItem(IDC_STREAMMEDIAPORT)->EnableWindow(m_bUseStreamMedia);
	GetDlgItem(IDC_COMBOSTREAMMEDIAPRO)->EnableWindow(m_bUseStreamMedia);
	if (m_bUseStreamMedia)
	{
		m_bUseUrl = FALSE;
		UpdateData(FALSE);
		OnChkUrl();
	}
	//m_bUseUrl = !m_bUseStreamMedia;
	/*
        }
        else
        {
            GetDlgItem(IDC_STREAMMEDIAIP)->EnableWindow(FALSE);
            GetDlgItem(IDC_STREAMMEDIAPORT)->EnableWindow(FALSE);
            GetDlgItem(IDC_COMBOSTREAMMEDIAPRO)->EnableWindow(FALSE);
        }*/
    
    UpdateData(FALSE);
}

void CMatCycLink::OnChkUrl() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	GetDlgItem(IDC_EDIT_URL)->EnableWindow(m_bUseUrl);
	if (m_bUseUrl)
	{
		m_bUseStreamMedia = FALSE;
		UpdateData(FALSE);
		OnUsestreammedia();
	}	
	UpdateData(FALSE);
}

void CMatCycLink::OnSelchangeComboStreamMode() 
{
	// TODO: Add your control notification handler code here
	int iSel = m_comboStreamMode.GetCurSel();
	if (iSel == -1)
	{
		return;
	}
	else if (iSel == 0 || iSel == 1)
	{
		m_bUseStreamMedia = FALSE;
		m_bUseUrl = FALSE;
	}
	else if (iSel == 2)
	{
		m_bUseStreamMedia = FALSE;
		m_bUseUrl = TRUE;
	}
	UpdateData(FALSE);
	OnUsestreammedia();
	OnChkUrl();
}
