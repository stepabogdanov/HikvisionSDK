// DlgXmlAbility.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgXmlAbility.h"
#include "DlgSoftHardAbility.h"
#include "DlgEncodeAbility.h"
#include "DlgNetworkAbility.h"
#include "DlgIPCFrontAbility.h"
#include "DlgCurrentEncodeAbility.h"
#include "DlgDynChanAbility.h"
#include "DlgXmlItcAbility.h"
#include "XmlUserAbility.h"
#include "DlgXmlJpegCapAbility.h"
#include "DlgXmlNetAppAbility.h"
#include "DlgXmlVideoPic.h"
#include "DlgXmlSerialAbility.h"
#include "DlgXmlAlarmAbility.h"
#include "DlgXmlDecoderAbility.h"
#include "DlgXmlRaidAbility.h"
#include "DlgXmlWallAblity.h"
#include "DlgChanInputAbility.h"
#include "DlgRecordAbility.h"
#include "DlgRemoteControlAbility.h"
#include "DlgXmlEventAbility.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgXmlAbility dialog

CDlgXmlAbility::CDlgXmlAbility(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgXmlAbility::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgXmlAbility)
	m_dwVideoChan = 0;
	//}}AFX_DATA_INIT
    m_lServerID = -1;
    m_iDevIndex = -1;
}


void CDlgXmlAbility::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgXmlAbility)
	DDX_Text(pDX, IDC_EDIT_ENCODE_VIDEO_CHAN, m_dwVideoChan);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgXmlAbility, CDialog)
	//{{AFX_MSG_MAP(CDlgXmlAbility)
	ON_BN_CLICKED(IDC_BTN_SOFTHARD_ABILITY, OnBtnSofthardAbility)
	ON_BN_CLICKED(IDC_BTN_ENCODE_ABILITY, OnBtnEncodeAbility)
	ON_BN_CLICKED(IDC_BTN_NETWORK, OnBtnNetwork)
	ON_BN_CLICKED(IDC_BTN_IPC_FRONT_ABILITY, OnBtnIpcFrontAbility)
	ON_BN_CLICKED(IDC_BTN_DYNCHAN_ABILITY, OnBtnDynchanAbility)
	ON_BN_CLICKED(IDC_BTN_ITC_ITS_ABILITY, OnBtnItcItsAbility)
	ON_BN_CLICKED(IDC_BTN_USER_ABILITY, OnBtnUserAbility)
	ON_BN_CLICKED(IDC_BTN_JPEG_CAP_ABILITY, OnBtnJpegCapAbility)
	ON_BN_CLICKED(IDC_BTN_NETAPP_ABILITY, OnBtnNetappAbility)
	ON_BN_CLICKED(IDC_BTN_VIDEO_PIC_ABILITY, OnBtnVideoPicAbility)
	ON_BN_CLICKED(IDC_BTN_SERIAL_ABILITY, OnBtnSerialAbility)
	ON_BN_CLICKED(IDC_BTN_ALARM_ABILITY, OnBtnAlarmAbility)
	ON_BN_CLICKED(IDC_BTN_DECODER_ABILITY, OnBtnDecoderAbility)
	ON_BN_CLICKED(IDC_BTN_RAID_ABILITY, OnBtnRaidAbility)
	ON_BN_CLICKED(IDC_BTN_WALL_ABILITY, OnBtnWallAbility)
	ON_BN_CLICKED(IDC_BTN_CHAN_INPUT_ABILITY, OnBtnChanInputAbility)
	ON_BN_CLICKED(IDC_BTN_RECORD_ABILITY, OnBtnRecordAbility)
	ON_BN_CLICKED(IDC_BTN_REMOTE_CONTROL_ABILITY, OnBtnRemoteControlAbility)
	ON_BN_CLICKED(IDC_BTN_EVENT_ABILITY, OnBtnEventAbility)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgXmlAbility message handlers

void CDlgXmlAbility::OnBtnSofthardAbility() 
{
    CDlgSoftHardAbility dlg;
    dlg.m_lServerID = m_lServerID;
    dlg.m_iDevIndex = m_iDevIndex;
    dlg.DoModal();
}


BOOL CDlgXmlAbility::OnInitDialog() 
{
	CDialog::OnInitDialog();

//     m_pRecvBuf = new char[XML_RECV_BUF]; // 128k数据接收XML缓冲区
//     m_pSendBuf = new char[XML_SEND_BUF]; // 128k发送xml缓冲区
    
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void CDlgXmlAbility::OnBtnEncodeAbility() 
{
//     GetEncodeAbility();	
//     ParseEncodeAbility(m_pRecvBuf, strlen(m_pRecvBuf));
	UpdateData(TRUE);
    CDlgEncodeAbility dlg;
    dlg.m_lServerID = m_lServerID;
    dlg.m_iDevIndex = m_iDevIndex;
	dlg.m_dwVideoChan = m_dwVideoChan;
    dlg.DoModal();
}



void CDlgXmlAbility::OnBtnNetwork() 
{
    CDlgNetworkAbility dlg;
    dlg.m_lServerID = m_lServerID;
    dlg.m_iDevIndex = m_iDevIndex;
    dlg.DoModal();
}


void CDlgXmlAbility::OnBtnIpcFrontAbility() 
{
    CDlgIPCFrontAbility dlg;
    dlg.m_lServerID = m_lServerID;
    dlg.m_iDevIndex = m_iDevIndex;
    dlg.DoModal();
}

void CDlgXmlAbility::OnBtnDynchanAbility() 
{
	// TODO: Add your control notification handler code here
	CDlgDynChanAbility dlg;
    dlg.m_lServerID = m_lServerID;
    dlg.m_iDevIndex = m_iDevIndex;
    dlg.DoModal();
}

void CDlgXmlAbility::OnBtnItcItsAbility() 
{
	// TODO: Add your control notification handler code here
	CDlgXmlItcAbility dlg;
    dlg.m_lServerID = m_lServerID;
    dlg.m_iDevIndex = m_iDevIndex;
    dlg.DoModal();
}

void CDlgXmlAbility::OnBtnUserAbility() 
{
	// TODO: Add your control notification handler code here
	CXmlUserAbility dlg;
    dlg.m_lServerID = m_lServerID;
    dlg.m_iDevIndex = m_iDevIndex;
    dlg.DoModal();
}

void CDlgXmlAbility::OnBtnJpegCapAbility() 
{
	// TODO: Add your control notification handler code here
	CDlgXmlJpegCapAbility dlg;
    dlg.m_lServerID = m_lServerID;
    dlg.m_iDevIndex = m_iDevIndex;
    dlg.DoModal();
}

void CDlgXmlAbility::OnBtnNetappAbility() 
{
	// TODO: Add your control notification handler code here
	CDlgXmlNetAppAbility dlg;
    dlg.m_lServerID = m_lServerID;
    dlg.m_iDevIndex = m_iDevIndex;
    dlg.DoModal();
}

void CDlgXmlAbility::OnBtnVideoPicAbility() 
{
	// TODO: Add your control notification handler code here
	CDlgXmlVideoPic dlg;
    dlg.m_lServerID = m_lServerID;
    dlg.m_iDevIndex = m_iDevIndex;
    dlg.DoModal();
}

void CDlgXmlAbility::OnBtnSerialAbility() 
{
	// TODO: Add your control notification handler code here
	CDlgXmlSerialAbility dlg;
    dlg.m_lServerID = m_lServerID;
    dlg.m_iDevIndex = m_iDevIndex;
    dlg.DoModal();
}

void CDlgXmlAbility::OnBtnAlarmAbility() 
{
	// TODO: Add your control notification handler code here
	CDlgXmlAlarmAbility dlg;
    dlg.m_lServerID = m_lServerID;
    dlg.m_iDevIndex = m_iDevIndex;
    dlg.DoModal();
}

void CDlgXmlAbility::OnBtnDecoderAbility() 
{
	// TODO: Add your control notification handler code here
	CDlgXmlDecoderAbility dlg;
    dlg.m_lServerID = m_lServerID;
    dlg.m_iDevIndex = m_iDevIndex;
    dlg.DoModal();
}

void CDlgXmlAbility::OnBtnRaidAbility() 
{
	// TODO: Add your control notification handler code here
	CDlgXmlRaidAbility dlg;
    dlg.m_lServerID = m_lServerID;
    dlg.m_iDevIndex = m_iDevIndex;
    dlg.DoModal();
}

void CDlgXmlAbility::OnBtnWallAbility() 
{
	// TODO: Add your control notification handler code here
	CDlgXmlWallAblity dlg;
	dlg.m_lServerID = m_lServerID;
	dlg.DoModal();
}

void CDlgXmlAbility::OnBtnChanInputAbility() 
{
	// TODO: Add your control notification handler code here
	CDlgChanInputAbility dlg;
    dlg.m_lServerID = m_lServerID;
    dlg.m_iDevIndex = m_iDevIndex;
    dlg.DoModal();
}

void CDlgXmlAbility::OnBtnRecordAbility() 
{
	// TODO: Add your control notification handler code here
	CDlgRecordAbility dlg;
    dlg.m_lServerID = m_lServerID;
    dlg.m_iDevIndex = m_iDevIndex;
    dlg.DoModal();
}

void CDlgXmlAbility::OnBtnRemoteControlAbility() 
{
	// TODO: Add your control notification handler code here
	CDlgRemoteControlAbility dlg;
    dlg.m_lServerID = m_lServerID;
    dlg.m_iDevIndex = m_iDevIndex;
    dlg.DoModal();
}

void CDlgXmlAbility::OnBtnEventAbility() 
{
	// TODO: Add your control notification handler code here
	CDlgXmlEventAbility dlg;
    dlg.m_lServerID = m_lServerID;
    dlg.m_iDevIndex = m_iDevIndex;
    dlg.DoModal();
}
