// MatPlayBack.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "MatPlayBack.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMatPlayBack dialog
#define GETSTATE_TIMER WM_USER+1

CMatPlayBack::CMatPlayBack(CWnd* pParent /*=NULL*/)
	: CDialog(CMatPlayBack::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMatPlayBack)
	m_PlayBackName = _T("");
	m_PlayBackIP = _T("172.7.160.2");
	m_PlayBackPass = _T("12345");
	m_PlayBackChan = 1;
	m_PlayBackPort = 8000;
	m_PlayBackUser = _T("admin");
	m_PlayStatus = _T("");
	//}}AFX_DATA_INIT
	m_hPlayEnableIcon =			AfxGetApp()->LoadIcon(IDI_PLAY_ENABLE);
	m_hPlayDisableIcon =		AfxGetApp()->LoadIcon(IDI_PLAY_DISABLE);
	m_hPauseEnableIcon =		AfxGetApp()->LoadIcon(IDI_PAUSE_ENABLE);
	m_hPauseDisableIcon =		AfxGetApp()->LoadIcon(IDI_PAUSE_DISABLE);
	m_hStopEnableIcon =			AfxGetApp()->LoadIcon(IDI_STOP_ENABLE);
	m_hStopDisableIcon =		AfxGetApp()->LoadIcon(IDI_STOP_DISABLE);
	m_hSoundStartIcon=			AfxGetApp()->LoadIcon(IDI_SOUND_ENABLE);
	m_hSoundStopIcon=			AfxGetApp()->LoadIcon(IDI_SOUND_DISABLE);
	m_hFastDisableIcon =		AfxGetApp()->LoadIcon(IDI_FASTFORWARD_DISABLE);
	m_hSlowDisableIcon=			AfxGetApp()->LoadIcon(IDI_FASTBACKWARD_DISABLE);
	m_hFastEnableIcon =			AfxGetApp()->LoadIcon(IDI_FASTFORWARD_ENABLE);
	m_hSlowEnableIcon =			AfxGetApp()->LoadIcon(IDI_FASTBACKWARD_ENABLE);
	m_hStepEnableIcon=			AfxGetApp()->LoadIcon(IDI_STEP_ENABLE);
	m_hStepDisableIcon =		AfxGetApp()->LoadIcon(IDI_STEP_DISABLE);

	m_bSound = FALSE;
	m_bPlay = FALSE;
	m_bPause = FALSE;

//	memset(&m_struState, 0, sizeof(m_struState));
}


void CMatPlayBack::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMatPlayBack)
	DDX_Control(pDX, IDC_COMBODECCHAN, m_DecChanCombo);
	DDX_Control(pDX, IDC_PROGRESS_SLIDER, m_ctlProgress);
	DDX_Control(pDX, IDC_DATETIMEPICKER4, m_StopTime);
	DDX_Control(pDX, IDC_DATETIMEPICKER3, m_StopDate);
	DDX_Control(pDX, IDC_DATETIMEPICKER2, m_StartTime);
	DDX_Control(pDX, IDC_DATETIMEPICKER1, m_StartDate);
	DDX_Text(pDX, IDC_EDITBACKNAME, m_PlayBackName);
	DDX_Text(pDX, IDC_EDITIP, m_PlayBackIP);
	DDX_Text(pDX, IDC_EDITPASSWD, m_PlayBackPass);
	DDX_Text(pDX, IDC_EDITCHAN, m_PlayBackChan);
	DDX_Text(pDX, IDC_EDITPORT, m_PlayBackPort);
	DDX_Text(pDX, IDC_EDITUSER, m_PlayBackUser);
	DDX_Text(pDX, IDC_PLAYSTATUS, m_PlayStatus);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMatPlayBack, CDialog)
	//{{AFX_MSG_MAP(CMatPlayBack)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_FAST, OnFast)
	ON_BN_CLICKED(IDC_PLAY_FILE, OnPlayFile)
	ON_BN_CLICKED(IDC_SLOW, OnSlow)
	ON_BN_CLICKED(IDC_SOUND, OnSound)
	ON_BN_CLICKED(IDC_STEP, OnStep)
	ON_BN_CLICKED(IDC_STOP, OnStop)
	ON_WM_HSCROLL()
	ON_BN_CLICKED(IDC_RADIONAME, OnRadioname)
	ON_BN_CLICKED(IDC_RADIOTIME, OnRadiotime)
	ON_BN_CLICKED(IDC_SETUP, OnSetup)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_PROGRESS_SLIDER, OnReleasedcaptureProgressSlider)
	ON_BN_CLICKED(IDC_STOPSOUND, OnStopsound)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMatPlayBack message handlers

void CMatPlayBack::F_InitUI()
{
	// ��ʼ����ť
	CButton *pButton;
	
	pButton = (CButton *)GetDlgItem(IDC_PLAY_FILE);
	pButton->SetIcon(m_hPlayDisableIcon);
	pButton->EnableWindow(FALSE);
	
	pButton = (CButton *)GetDlgItem(IDC_STOP);
	pButton->SetIcon(m_hStopDisableIcon);
	pButton->EnableWindow(FALSE);
	
	pButton = (CButton *)GetDlgItem(IDC_FAST);
	pButton->SetIcon(m_hFastDisableIcon);
	pButton->EnableWindow(FALSE);
	
	pButton = (CButton *)GetDlgItem(IDC_SLOW);
	pButton->SetIcon(m_hSlowDisableIcon);
	pButton->EnableWindow(FALSE);
	
	pButton = (CButton *)GetDlgItem(IDC_STEP);
	pButton->SetIcon(m_hStepDisableIcon);
	pButton->EnableWindow(FALSE);
	
    pButton = (CButton *)GetDlgItem(IDC_SOUND);
    //if(m_bSound)
    pButton->SetIcon(m_hSoundStartIcon);
    //else
    pButton = (CButton *)GetDlgItem(IDC_STOPSOUND);
    pButton->SetIcon(m_hSoundStopIcon);
//	pButton = (CButton *)GetDlgItem(IDC_SOUND);
	//	pButton->SetIcon(m_hSoundStopIcon);
	//	pButton->EnableWindow(FALSE);
	
}

void CMatPlayBack::F_SetStopState()
{
	CButton *pButton;
	
	m_ctlProgress.SetPos(0);
	m_ctlProgress.EnableWindow(FALSE);
	
	pButton = (CButton *)GetDlgItem(IDC_PLAY_FILE);
	pButton->SetIcon(m_hPlayEnableIcon);
	pButton->EnableWindow(TRUE);
	
	pButton = (CButton *)GetDlgItem(IDC_STOP);
	pButton->SetIcon(m_hStopDisableIcon);
	pButton->EnableWindow(FALSE);
	
	pButton = (CButton *)GetDlgItem(IDC_FAST);
	pButton->SetIcon(m_hFastDisableIcon);
	pButton->EnableWindow(FALSE);
	
	pButton = (CButton *)GetDlgItem(IDC_SLOW);
	pButton->SetIcon(m_hSlowDisableIcon);
	pButton->EnableWindow(FALSE);
	
	pButton = (CButton *)GetDlgItem(IDC_STEP);
	pButton->SetIcon(m_hStepDisableIcon);
	pButton->EnableWindow(FALSE);

    pButton = (CButton *)GetDlgItem(IDC_SOUND);
    //if(m_bSound)
    pButton->SetIcon(m_hSoundStartIcon);
    //else
    pButton = (CButton *)GetDlgItem(IDC_STOPSOUND);
    pButton->SetIcon(m_hSoundStopIcon);
	
//	pButton = (CButton *)GetDlgItem(IDC_SOUND);
	//	pButton->SetIcon(m_hSoundStopIcon);
	//	pButton->EnableWindow(FALSE);	
	
}

void CMatPlayBack::F_SetPlayState() 
{
	m_ctlProgress.EnableWindow(TRUE);

	CButton *pButton;
	
	pButton = (CButton *)GetDlgItem(IDC_PLAY_FILE);
	pButton->SetIcon(m_hPauseEnableIcon);
	pButton->EnableWindow(TRUE);
	
	pButton = (CButton *)GetDlgItem(IDC_STOP);
	pButton->SetIcon(m_hStopEnableIcon);
	pButton->EnableWindow(TRUE);
	
	pButton = (CButton *)GetDlgItem(IDC_FAST);
	pButton->SetIcon(m_hFastEnableIcon);
	pButton->EnableWindow(TRUE);
	
	pButton = (CButton *)GetDlgItem(IDC_SLOW);
	pButton->SetIcon(m_hSlowEnableIcon);
	pButton->EnableWindow(TRUE);
	
	pButton = (CButton *)GetDlgItem(IDC_SOUND);
	//if(m_bSound)
    pButton->SetIcon(m_hSoundStartIcon);
	//else
    pButton = (CButton *)GetDlgItem(IDC_STOPSOUND);
		pButton->SetIcon(m_hSoundStopIcon);
	pButton->EnableWindow(TRUE);
	
	pButton = (CButton *)GetDlgItem(IDC_STEP);
	pButton->SetIcon(m_hStepEnableIcon);
	pButton->EnableWindow(TRUE);
}

void CMatPlayBack::F_SetPauseState()
{
	CButton *pButton;	
	pButton = (CButton *)GetDlgItem(IDC_PLAY_FILE);
	pButton->SetIcon(m_hPlayEnableIcon);
	pButton->EnableWindow(TRUE);
}

void CMatPlayBack::EnableControl(BOOL bEnable)
{
	GetDlgItem(IDC_EDITBACKNAME)->EnableWindow(bEnable);
	GetDlgItem(IDC_DATETIMEPICKER1)->EnableWindow(!bEnable);
	GetDlgItem(IDC_DATETIMEPICKER2)->EnableWindow(!bEnable);
	GetDlgItem(IDC_DATETIMEPICKER3)->EnableWindow(!bEnable);
	GetDlgItem(IDC_DATETIMEPICKER4)->EnableWindow(!bEnable);
}

BOOL CMatPlayBack::OnInitDialog() 
{
	CDialog::OnInitDialog();
	// TODO: Add extra initialization here
	F_InitUI();
	
	CString tmp;
	char szLan[128] = {0};
	g_StringLanType(szLan, "ͨ��", "Channel");
	for (int i=0; i<m_iChannelNumber; i++)
	{
		tmp.Format("%s %d",szLan, i+m_lStartChan);
		m_DecChanCombo.AddString(tmp);
	}

	m_DecChanCombo.SetCurSel(0);
	m_ctlProgress.SetRange(0, 100);
	m_ctlProgress.SetPos(0);

	CTime ct = CTime::GetCurrentTime();
	SYSTEMTIME st;
	st.wYear = ct.GetYear();
	st.wMonth = ct.GetMonth();
	st.wDay = ct.GetDay();
	st.wHour = 0;
	st.wMinute = 0;
	st.wSecond = 0;
	m_StartDate.SetTime(&st);
	m_StartTime.SetTime(&st);
	st.wHour = 23;
	st.wMinute = 59;
	st.wSecond = 59;
	m_StopDate.SetTime(&st);
	m_StopTime.SetTime(&st);

	CheckRadioButton(IDC_RADIONAME, IDC_RADIOTIME, IDC_RADIONAME);
	EnableControl(TRUE);

	F_SetStopState();
	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CMatPlayBack::OnTimer(UINT nIDEvent) 
{
	CDialog::OnTimer(nIDEvent);
	NET_DVR_MATRIX_DEC_CHAN_STATUS MDStatus;
	CString tmp;
	// TODO: Add your message handler code here and/or call default
	if (nIDEvent == GETSTATE_TIMER)
	{
		if (m_bPlay)
		{
 			memset(&MDStatus, 0, sizeof(MDStatus));
 			if (!NET_DVR_MatrixGetDecChanStatus(m_lServerID, m_DecChanCombo.GetCurSel()+m_lStartChan, &MDStatus))
 			{
 				tmp.Format("Error: NET_DVR_MatrixGetDecChanStatus = %d", NET_DVR_GetLastError());
 				//AfxMessageBox(tmp);
 			}
 			else
 			{
 				if (MDStatus.dwIsLinked < 3)
 				{
 					OutputDebugString("Please wait, decoding has not started!");
 				}
 				else
 				{
 					UpdateData(TRUE);
 					memset(&m_struState, 0, sizeof(m_struState));
 					if (!NET_DVR_MatrixGetRemotePlayStatus(m_lServerID, m_DecChanCombo.GetCurSel()+m_lStartChan, &m_struState))
 					{
 						tmp.Format("Error: NET_DVR_MatrixGetRemotePlayStatus = %d", NET_DVR_GetLastError());
 						OutputDebugString(tmp);
 					}
 					else
 					{
 						m_PlayStatus.Format("Pos: %u/%u  Time: %u/%u  Frame: %u",
 							m_struState.dwCurMediaFilePosition, m_struState.dwCurMediaFileLen, 
							m_struState.dwCurPlayTime, m_struState.dwCurMediaFileDuration, 
							m_struState.dwCurMediaFIleFrames);
 
 						if (m_struState.dwCurMediaFileDuration > 0)
 						{
 							m_ctlProgress.SetPos((m_struState.dwCurPlayTime * 100) / m_struState.dwCurMediaFileDuration);
 						}
 
  						if (m_struState.dwCurDataType == 21)
 						{
 							m_ctlProgress.SetPos(0);
 							m_bPlay = FALSE;
 							m_bPause = FALSE;
 							F_SetStopState();
							char szLan[128] = {0};
							g_StringLanType(szLan, "�طŽ���", "Playback Failed");
							AfxMessageBox(szLan);
 						}
 					}
 					UpdateData(FALSE);
 				}
 			}	
		}
	}
}	

void CMatPlayBack::OnFast() 
{
	// TODO: Add your control notification handler code here
 	if (!NET_DVR_MatrixSetRemotePlayControl(m_lServerID, m_DecChanCombo.GetCurSel()+m_lStartChan, NET_DVR_PLAYFAST, 2, NULL))
 	{
 		CString tmp;
 		tmp.Format("Error: NET_DVR_MatrixSetRemotePlayControl = %d", NET_DVR_GetLastError());
 		AfxMessageBox(tmp);
 	}
}

void CMatPlayBack::OnPlayFile() 
{
	UpdateData(TRUE);
	// TODO: Add your control notification handler code here

 	if (m_bPause && m_bPlay)
 	{
 		if (!NET_DVR_MatrixSetRemotePlayControl(m_lServerID, m_DecChanCombo.GetCurSel()+m_lStartChan, NET_DVR_PLAYRESTART, 0, NULL))
 		{
 			CString tmp;
 			tmp.Format("Error: NET_DVR_MatrixSetRemotePlayControl = %d", NET_DVR_GetLastError());
 			AfxMessageBox(tmp);
 			return;
 		}
 		m_bPause = FALSE;
 		F_SetPlayState();
 	}
 	else if (m_bPlay)
 	{
 		if (!NET_DVR_MatrixSetRemotePlayControl(m_lServerID, m_DecChanCombo.GetCurSel()+m_lStartChan, NET_DVR_PLAYPAUSE, 0, NULL))
 		{
 			CString tmp;
 			tmp.Format("Error: NET_DVR_MatrixSetRemotePlayControl = %d", NET_DVR_GetLastError());
 			AfxMessageBox(tmp);
 			return;
 		}
 		m_bPause = TRUE;
 		F_SetPauseState();
 	}
 	else
 	{
 		if (!NET_DVR_MatrixSetRemotePlayControl(m_lServerID, m_DecChanCombo.GetCurSel()+m_lStartChan, NET_DVR_PLAYSTART, 0, NULL))
 		{
 			CString tmp;
 			tmp.Format("Error: NET_DVR_MatrixSetRemotePlayControl = %d", NET_DVR_GetLastError());
 			AfxMessageBox(tmp);
 			return;
 		}
 		m_bPlay = TRUE;
 		m_bPause = FALSE;
 		F_SetPlayState();
 		SetTimer(GETSTATE_TIMER, 2000, NULL);
 	}
 
 	UpdateData(FALSE);
}

void CMatPlayBack::OnSlow() 
{
	// TODO: Add your control notification handler code here
 	if (!NET_DVR_MatrixSetRemotePlayControl(m_lServerID, m_DecChanCombo.GetCurSel()+m_lStartChan, NET_DVR_PLAYSLOW, 2, NULL))
 	{
 		CString tmp;
 		tmp.Format("Error: NET_DVR_MatrixSetRemotePlayControl = %d", NET_DVR_GetLastError());
 		AfxMessageBox(tmp);
 	}
}

void CMatPlayBack::OnSound() 
{
    if (!NET_DVR_MatrixSetRemotePlayControl(m_lServerID, m_DecChanCombo.GetCurSel()+m_lStartChan, NET_DVR_PLAYSTARTAUDIO, 0, NULL))
    {
        CString tmp;
        tmp.Format("Error: NET_DVR_MatrixSetRemotePlayControl = %d", NET_DVR_GetLastError());
        AfxMessageBox(tmp);
        return;
    }
}

void CMatPlayBack::OnStep() 
{
	// TODO: Add your control notification handler code here
 	if (!NET_DVR_MatrixSetRemotePlayControl(m_lServerID, m_DecChanCombo.GetCurSel()+m_lStartChan, NET_DVR_PLAYNORMAL, 0, NULL))
 	{
 		CString tmp;
 		tmp.Format("Error: NET_DVR_MatrixSetRemotePlayControl = %d", NET_DVR_GetLastError());
 		AfxMessageBox(tmp);
 	}
}

void CMatPlayBack::OnStop() 
{
	UpdateData(TRUE);
	// TODO: Add your control notification handler code here
 	if (!NET_DVR_MatrixSetRemotePlayControl(m_lServerID, m_DecChanCombo.GetCurSel()+m_lStartChan, NET_DVR_PLAYSTOP, 0, NULL))
 	{
 		CString tmp;
 		tmp.Format("Error: NET_DVR_MatrixSetRemotePlayControl = %d", NET_DVR_GetLastError());
 		AfxMessageBox(tmp);
 		return;
 	}
 	m_PlayStatus.Empty();
 	m_bPlay = FALSE;
 	m_bPause = FALSE;
 	F_SetStopState();
 	KillTimer(GETSTATE_TIMER);
 
 	UpdateData(FALSE);
}

void CMatPlayBack::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
	// TODO: Add your message handler code here and/or call default
	if (GetDlgItem(IDC_PROGRESS_SLIDER) == pScrollBar)
	{
 		
	}
}

void CMatPlayBack::OnRadioname() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	CheckRadioButton(IDC_RADIONAME, IDC_RADIOTIME, IDC_RADIONAME);
	EnableControl(TRUE);

	UpdateData(FALSE);
}

void CMatPlayBack::OnRadiotime() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	
	CheckRadioButton(IDC_RADIONAME, IDC_RADIOTIME, IDC_RADIOTIME);
	EnableControl(FALSE);
	
	UpdateData(FALSE);
}

void CMatPlayBack::OnSetup() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

 	memset(&m_struPlay, 0, sizeof(m_struPlay));
 	m_struPlay.dwSize = sizeof(m_struPlay);
 
 	sprintf(m_struPlay.sDVRIP, "%s", m_PlayBackIP);
 	m_struPlay.wDVRPort = m_PlayBackPort;
 	m_struPlay.byChannel = m_PlayBackChan;
 	sprintf((char *)m_struPlay.sUserName, "%s", m_PlayBackUser);
 	sprintf((char *)m_struPlay.sPassword, "%s", m_PlayBackPass);
 
 	if (GetCheckedRadioButton(IDC_RADIONAME, IDC_RADIOTIME) == IDC_RADIOTIME)
 	{
 		SYSTEMTIME st;
 		m_StartDate.GetTime(&st);
 		m_struPlay.StartTime.dwYear = st.wYear;
 		m_struPlay.StartTime.dwMonth = st.wMonth;
 		m_struPlay.StartTime.dwDay = st.wDay;
 		m_StartTime.GetTime(&st);
 		m_struPlay.StartTime.dwHour = st.wHour;
 		m_struPlay.StartTime.dwMinute = st.wMinute;
 		m_struPlay.StartTime.dwSecond = st.wSecond;
 
 		m_StopDate.GetTime(&st);
 		m_struPlay.StopTime.dwYear = st.wYear;
 		m_struPlay.StopTime.dwMonth = st.wMonth;
 		m_struPlay.StopTime.dwDay = st.wDay;
 		m_StopTime.GetTime(&st);
 		m_struPlay.StopTime.dwHour = st.wHour;
 		m_struPlay.StopTime.dwMinute = st.wMinute;
 		m_struPlay.StopTime.dwSecond = st.wSecond;
 
 		m_struPlay.dwPlayMode = 1;
 	}
 	else
 	{
 		sprintf(m_struPlay.sFileName, "%s", m_PlayBackName);
 		m_struPlay.dwPlayMode = 0;
 	}
 
 	if (!NET_DVR_MatrixSetRemotePlay(m_lServerID, m_DecChanCombo.GetCurSel()+m_lStartChan, &m_struPlay))
 	{
 		CString tmp;
 		tmp.Format("Error: NET_DVR_MatrixSetRemotePlay = %d", NET_DVR_GetLastError());
 		AfxMessageBox(tmp);
 		return;
 	}

	KillTimer(GETSTATE_TIMER);
	char szLan[128] = {0};
	g_StringLanType(szLan, "���óɹ�", "Set Successfully");
	AfxMessageBox(szLan);
}

void CMatPlayBack::OnCancel() 
{
	// TODO: Add extra cleanup here
	if (m_bPlay)
	{
		OnStop();
	}

	CDialog::OnCancel();
}

void CMatPlayBack::OnReleasedcaptureProgressSlider(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	if (m_bPlay && m_struPlay.dwPlayMode == 0)
	{
		int pos = m_ctlProgress.GetPos();
		if (!NET_DVR_MatrixSetRemotePlayControl(m_lServerID, m_DecChanCombo.GetCurSel()+m_lStartChan, NET_DVR_PLAYSETPOS, pos, NULL))
		{
			CString tmp;
			tmp.Format("Error: NET_DVR_MatrixSetRemotePlayControl = %d", NET_DVR_GetLastError());
			AfxMessageBox(tmp);
		}
 	}
	
	*pResult = 0;
}

void CMatPlayBack::OnStopsound() 
{
    // TODO: Add your control notification handler code here
    UpdateData(TRUE);
	if (!NET_DVR_MatrixSetRemotePlayControl(m_lServerID, m_DecChanCombo.GetCurSel()+m_lStartChan, NET_DVR_PLAYSTOPAUDIO, 0, NULL))
    {
        CString tmp;
        tmp.Format("Error: NET_DVR_MatrixSetRemotePlayControl = %d", NET_DVR_GetLastError());
        AfxMessageBox(tmp);
        return;
    }
}
