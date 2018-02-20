// MatDispChan.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "MatDispChan.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define DISP_TIMER	WM_USER + 1
/////////////////////////////////////////////////////////////////////////////
// CMatDispChan dialog
extern void g_IPToStr(DWORD dip, char outbuf[16]);

CMatDispChan::CMatDispChan(CWnd* pParent /*=NULL*/)
	: CDialog(CMatDispChan::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMatDispChan)
	m_DIIP = _T("");
	m_DIChanNum = 0;
	m_DIUserName = _T("");
	m_DIPwd = _T("");
	m_FileName = _T("");
	m_CopyRate = 0;
	m_strStreamMediaIp = _T("");
	m_dwStreamMediaPort = 0;
	m_bUseStreamMedia = FALSE;
	m_dwPassivePort = 0;
	m_DIPort = 0;
	m_bUseUrl = FALSE;
	m_csUrl = _T("");
	//}}AFX_DATA_INIT
	m_iChanSel = -1;
    memset(&m_struProtoList, 0, sizeof(m_struProtoList));
}


void CMatDispChan::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMatDispChan)
	DDX_Control(pDX, IDC_COMBO_STREAM_MODE, m_comboStreamMode);
	DDX_Control(pDX, IDC_COMBO_FACTYPE, m_FacTypeCtrl);
	DDX_Control(pDX, IDC_COMBOSTREAMTYPE, m_comboStreamType);
	DDX_Control(pDX, IDC_COMBOPASSIVETRANSPROTOL, m_ComboPassiveTransProtol);
	DDX_Control(pDX, IDC_COMBOSTREAMMEDIAPRO, m_ComboStreamMediaPro);
	DDX_Control(pDX, IDC_COMBOGETSTREAMMODE, m_ComboGetStreamMode);
	DDX_Control(pDX, IDC_COMBOISLINK, m_IsLinkCombo);
	DDX_Control(pDX, IDC_CHANCOMBO, m_ChanCombo);
	DDX_Control(pDX, IDC_DATETIMEPICKER4, m_EndTime);
	DDX_Control(pDX, IDC_DATETIMEPICKER3, m_EndDate);
	DDX_Control(pDX, IDC_DATETIMEPICKER2, m_StartTime);
	DDX_Control(pDX, IDC_DATETIMEPICKER1, m_StartDate);
	DDX_Control(pDX, IDC_TRANSMODECOMBO2, m_DIModeCombo);
	DDX_Control(pDX, IDC_PROTOCOLTYPECOMBO2, m_DIProTypeCombo);
	DDX_Control(pDX, IDC_COMBODECSTATE, m_DecStateCombo);
    DDX_Text(pDX, IDC_LINKIP2, m_DIIP);
	DDX_Text(pDX, IDC_LINKCHAN2, m_DIChanNum);
	DDX_Text(pDX, IDC_USERNAME2, m_DIUserName);
	DDX_Text(pDX, IDC_PASSWD2, m_DIPwd);
	DDX_Text(pDX, IDC_FILENAME, m_FileName);
	DDX_Text(pDX, IDC_EDITCOPYRATE, m_CopyRate);
	DDX_Text(pDX, IDC_STREAMMEDIAIP, m_strStreamMediaIp);
	DDX_Text(pDX, IDC_STREAMMEDIAPORT, m_dwStreamMediaPort);
	DDX_Check(pDX, IDC_USESTREAMMEDIA, m_bUseStreamMedia);
	DDX_Text(pDX, IDC_PASSIVEPORT, m_dwPassivePort);
	DDX_Text(pDX, IDC_LINKPORT2, m_DIPort);
	DDV_MinMaxDWord(pDX, m_DIPort, 0, 65535);
	DDX_Check(pDX, IDC_CHK_URL, m_bUseUrl);
	DDX_Text(pDX, IDC_EDIT_URL, m_csUrl);
	//}}AFX_DATA_MAP

}


BEGIN_MESSAGE_MAP(CMatDispChan, CDialog)
	//{{AFX_MSG_MAP(CMatDispChan)
	ON_CBN_SELCHANGE(IDC_CHANCOMBO, OnSelchangeChancombo)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_USESTREAMMEDIA, OnUsestreammedia)
	ON_BN_CLICKED(IDC_CHK_URL, OnChkUrl)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMatDispChan message handlers

BOOL CMatDispChan::OnInitDialog()
{
	CDialog::OnInitDialog();

	CString tmp;
	int i=0;
	int ChanNo = -1;
	char szLan[128] = {0};
	m_vGetStatus.resize(m_iChannelnumber);
	m_vbGetInfo.resize(m_iChannelnumber);
	TRACE("\nm_iChannelnumber = %d\n", m_iChannelnumber);
	
    g_StringLanType(szLan, "主动", "Active");
    m_ComboGetStreamMode.InsertString(0,szLan);
    g_StringLanType(szLan, "被动", "Passive");    
    m_ComboGetStreamMode.InsertString(1,szLan);
	
	for(i=0; i<m_iChannelnumber; i++)
	{
		ChanNo = m_lStartChan+i;
		g_StringLanType(szLan, "通道", "Chan");
		tmp.Format("%s %d", szLan, ChanNo);
		m_ChanCombo.AddString(tmp);
	
		GetChanStatus(ChanNo, i);
	}

	for (i=0; i<m_iChannelnumber; ++i)
	{
		if (m_vbGetInfo[i])
		{
			ShowChanInfo(i);
			if (m_vGetStatus[i])
			{
				m_IsLinkCombo.SetCurSel(m_DecChanStatus[i].dwIsLinked);
				TRACE("m_DecChanStatus[i].dwIsLinked = %d\n", m_DecChanStatus[i].dwIsLinked);
				m_CopyRate = m_DecChanStatus[i].dwStreamCpRate;
			}
			else
			{
				g_pMainDlg->AddLog(-1, OPERATION_FAIL_T, "Get Chan%d Status ERR ", i+m_lStartChan);
				AfxMessageBox(tmp);
			}
			break;
		}
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

    m_ChanCombo.SetCurSel(0);
	UpdateData(FALSE);

    OnUsestreammedia();
	OnChkUrl();
	SetTimer(DISP_TIMER, 3000, NULL);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CMatDispChan::GetChanStatus(DWORD DecChanNum, int index)
{
	CString tmp;

	ZeroMemory(&m_DecChanStatus[index], sizeof(m_DecChanStatus[index]));
	m_DecChanStatus->dwSize = sizeof(m_DecChanStatus[index]);
	if (!NET_DVR_MatrixGetDecChanStatus(m_lServerID, DecChanNum, &m_DecChanStatus[index]))
	{
		g_pMainDlg->AddLog(-1, OPERATION_FAIL_T, "NET_DVR_MatrixGetDecChanStatus");	
        //MessageBox("NET_DVR_MatrixGetDecChanStatus failed");
		m_vGetStatus[index] = FALSE;
	}
	else
	{
       //  MessageBox("NET_DVR_MatrixGetDecChanStatus succ");
		m_vGetStatus[index] = TRUE;
	}

	ZeroMemory(&m_DecChanInfo[index], sizeof(m_DecChanInfo[index]));
	m_DecChanInfo[index].dwSize = sizeof(m_DecChanInfo[index]);
	if (!NET_DVR_MatrixGetDecChanInfo_V41(m_lServerID, DecChanNum, &m_DecChanInfo[index]))
	{
		g_pMainDlg->AddLog(-1, OPERATION_FAIL_T, "NET_DVR_MatrixGetDecChanInfo");
        //TRACE("获取NET_DVR_MatrixGetDecChanInfo_V41 错误:%d", NET_DVR_GetLastError());
		m_vbGetInfo[index] = FALSE;
	}
	else
	{
		g_pMainDlg->AddLog(-1, OPERATION_SUCC_T, "NET_DVR_MatrixGetDecChanInfo");
        //TRACE("NET_DVR_MatrixGetDecChanInfo_V41 成功");
		m_vbGetInfo[index] = TRUE;
	}

	return TRUE;
}

void CMatDispChan::ShowChanInfo(int index)
{
	if(index < 0 || index > m_iChannelnumber-1)
	{
		return;
	}

	UpdateData(TRUE);
	CString tmp;
	if(!m_vbGetInfo[index])
	{
		g_pMainDlg->AddLog(-1, OPERATION_FAIL_T, "m_vbGetInfo false %d Err!", index + m_lStartChan);
	}
	else
	{
		if (m_DecChanInfo[index].byStreamMode == 1 && m_DecChanInfo[index].uDecStreamMode.struDecStreamDev.struStreamMediaSvrCfg.byValid == 1)
		{
			m_bUseStreamMedia = TRUE;
			m_bUseUrl = FALSE;
		}
		else if (m_DecChanInfo[index].byStreamMode == 2)
		{
			m_bUseStreamMedia = FALSE;
			m_bUseUrl = TRUE;
		}
		else
		{
			m_bUseStreamMedia = FALSE;
			m_bUseUrl = FALSE;
		}

		m_comboStreamMode.SetCurSel(m_DecChanInfo[index].byStreamMode);

		if (!m_bUseUrl)
		{
			m_ChanCombo.SetCurSel(index);
			m_DecStateCombo.SetCurSel(m_DecChanInfo[index].dwPlayMode);			
			//Dec info...
			m_DIIP.Format("%s", m_DecChanInfo[index].uDecStreamMode.struDecStreamDev.struDevChanInfo.byAddress);
			m_DIPort = m_DecChanInfo[index].uDecStreamMode.struDecStreamDev.struDevChanInfo.wDVRPort;
			m_DIChanNum = m_DecChanInfo[index].uDecStreamMode.struDecStreamDev.struDevChanInfo.byChannel;
			m_DIUserName.Format("%s", m_DecChanInfo[index].uDecStreamMode.struDecStreamDev.struDevChanInfo.sUserName);
			m_DIPwd.Format("%s", m_DecChanInfo[index].uDecStreamMode.struDecStreamDev.struDevChanInfo.sPassword);
			m_DIProTypeCombo.SetCurSel(m_DecChanInfo[index].uDecStreamMode.struDecStreamDev.struDevChanInfo.byTransProtocol);
			m_DIModeCombo.SetCurSel(m_DecChanInfo[index].uDecStreamMode.struDecStreamDev.struDevChanInfo.byTransMode);
			
			int i = 0;
			for(i = 0; i < m_struProtoList.dwProtoNum; i++)
			{
				if (m_DecChanInfo[index].uDecStreamMode.struDecStreamDev.struDevChanInfo.byFactoryType == m_struProtoList.struProto[i].dwType) 
				{
					m_FacTypeCtrl.SetCurSel(i);
					break;
				}
			}
			if (i >= m_struProtoList.dwProtoNum) 
			{
				m_FacTypeCtrl.SetCurSel(-1);
			}
			//m_FacTypeCtrl.SetCurSel(m_DecChanInfo[index].struDevChanInfo.byFactoryType);
			
			m_ComboGetStreamMode.SetCurSel(m_DecChanInfo[index].dwGetStreamMode - 1);
			
			
			//m_bUseStreamMedia = m_DecChanInfo[index].uDecStreamMode.struDecStreamDev.struStreamMediaSvrCfg.byValid;
			if (m_bUseStreamMedia)
			{
				m_strStreamMediaIp.Format("%s", m_DecChanInfo[index].uDecStreamMode.struDecStreamDev.struStreamMediaSvrCfg.byAddress);
				m_dwStreamMediaPort = m_DecChanInfo[index].uDecStreamMode.struDecStreamDev.struStreamMediaSvrCfg.wDevPort;
				m_ComboStreamMediaPro.SetCurSel(m_DecChanInfo[index].uDecStreamMode.struDecStreamDev.struStreamMediaSvrCfg.byTransmitType);
			}

		}		
		//m_bUseUrl = m_DecChanInfo[index].uDecStreamMode.struUrlInfo.byEnable;
		if (m_bUseUrl)
		{
			m_csUrl.Format("%s", m_DecChanInfo[index].uDecStreamMode.struUrlInfo.strURL);
		}

		if (m_DecChanInfo[index].dwPlayMode == 2)
		{
			SYSTEMTIME sysTime;
			ZeroMemory(&sysTime, sizeof(sysTime));
			sysTime.wYear = (WORD)m_DecChanInfo[index].StartTime.dwYear;
			sysTime.wMonth = (WORD)m_DecChanInfo[index].StartTime.dwMonth;
			sysTime.wDay = (WORD)m_DecChanInfo[index].StartTime.dwDay;
			sysTime.wHour = (WORD)m_DecChanInfo[index].StartTime.dwHour;
			sysTime.wMinute = (WORD)m_DecChanInfo[index].StartTime.dwMinute;
			sysTime.wSecond = (WORD)m_DecChanInfo[index].StartTime.dwSecond;
			m_StartDate.SetTime(&sysTime);
			m_StartTime.SetTime(&sysTime);
			ZeroMemory(&sysTime, sizeof(sysTime));
			sysTime.wYear = (WORD)m_DecChanInfo[index].StopTime.dwYear;
			sysTime.wMonth = (WORD)m_DecChanInfo[index].StopTime.dwMonth;
			sysTime.wDay = (WORD)m_DecChanInfo[index].StopTime.dwDay;
			sysTime.wHour = (WORD)m_DecChanInfo[index].StopTime.dwHour;
			sysTime.wMinute = (WORD)m_DecChanInfo[index].StopTime.dwMinute;
			sysTime.wSecond = (WORD)m_DecChanInfo[index].StopTime.dwSecond;
			m_EndDate.SetTime(&sysTime);
			m_EndTime.SetTime(&sysTime);

			m_FileName.Empty();
		}
		else if (m_DecChanInfo[index].dwPlayMode == 3)
		{
			m_FileName.Format("%s", m_DecChanInfo[index].sFileName);
			
			CTime now = CTime::GetCurrentTime();
			m_StartDate.SetTime(&now);
			m_StartTime.SetTime(&now);
			m_EndDate.SetTime(&now);
			m_EndTime.SetTime(&now);
		}
		else
		{
			CTime now = CTime::GetCurrentTime();
			m_StartDate.SetTime(&now);
			m_StartTime.SetTime(&now);
			m_EndDate.SetTime(&now);
			m_EndTime.SetTime(&now);
			m_FileName.Empty();
		}
        TRACE("lll ----- m_DecChanInfo[index].struPassiveMode.wTransProtol = %d", m_DecChanInfo[index].struPassiveMode.wTransProtol);
        m_ComboPassiveTransProtol.SetCurSel(m_DecChanInfo[index].struPassiveMode.wTransProtol);
        m_dwPassivePort = m_DecChanInfo[index].struPassiveMode.wPassivePort;
        m_comboStreamType.SetCurSel(m_DecChanInfo[index].struPassiveMode.byStreamType - 1);
	}
	UpdateData(FALSE);
}

void CMatDispChan::OnSelchangeChancombo() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	int sel = m_ChanCombo.GetCurSel();
	
	ShowChanInfo(sel);
	if (!m_vGetStatus[sel])
	{
		g_pMainDlg->AddLog(-1, OPERATION_FAIL_T, "GetChanStatus %d Err!", sel + m_lStartChan);
	}
	else
	{
		m_IsLinkCombo.SetCurSel(m_DecChanStatus[sel].dwIsLinked);
		m_CopyRate = m_DecChanStatus[sel].dwStreamCpRate;
	}
	
	UpdateData(FALSE);
    OnUsestreammedia();
	OnChkUrl();
}

void CMatDispChan::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	if (nIDEvent == DISP_TIMER)
	{
		UpdateData(TRUE);
		int sel = m_ChanCombo.GetCurSel();

		GetChanStatus(sel+m_lStartChan, sel);

		ShowChanInfo(sel);

		UpdateData(TRUE);
		if (!m_vGetStatus[sel])
		{
			g_pMainDlg->AddLog(-1, OPERATION_FAIL_T, "GetChanStatus %d Err!", sel + m_lStartChan);
		}
		else
		{
			m_IsLinkCombo.SetCurSel(m_DecChanStatus[sel].dwIsLinked);
			TRACE("m_DecChanStatus[i].dwIsLinked = %d\n", m_DecChanStatus[sel].dwIsLinked);
			m_CopyRate = m_DecChanStatus[sel].dwStreamCpRate;
		}

		UpdateData(FALSE);
        OnUsestreammedia();
		OnChkUrl();
	}

	CDialog::OnTimer(nIDEvent);
}

void CMatDispChan::OnCancel() 
{
	// TODO: Add extra cleanup here
	KillTimer(DISP_TIMER);

	CDialog::OnCancel();
}

void CMatDispChan::OnUsestreammedia() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
    EnableStreamMedia(m_bUseStreamMedia);
}
void CMatDispChan::EnableStreamMedia(BOOL bUseStreamMedia)
{
    GetDlgItem(IDC_STREAMMEDIAIP)->EnableWindow(bUseStreamMedia);
    GetDlgItem(IDC_STREAMMEDIAPORT)->EnableWindow(bUseStreamMedia);
    GetDlgItem(IDC_COMBOSTREAMMEDIAPRO)->EnableWindow(bUseStreamMedia);

	if (bUseStreamMedia)
	{
		m_bUseUrl = FALSE;
		UpdateData(FALSE);
		OnChkUrl();
	}
    UpdateData(FALSE);
}

void CMatDispChan::OnChkUrl() 
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
		GetDlgItem(IDC_EDIT_URL)->EnableWindow(TRUE);
	}
	UpdateData(FALSE);	
}
