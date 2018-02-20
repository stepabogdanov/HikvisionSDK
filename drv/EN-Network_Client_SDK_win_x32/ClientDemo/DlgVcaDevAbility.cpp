// DlgVcaDevAbility.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgVcaDevAbility.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgVcaDevAbility dialog

CDlgVcaDevAbility::CDlgVcaDevAbility(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgVcaDevAbility::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgVcaDevAbility)
	m_iAtmChanNum = 0;
	m_iVcaChanNum = 0;
	m_iITSChanNum = 0;
	m_iBBaseChanNum = 0;
	m_iBFullChanNum = 0;
	m_iBAdvanceChanNum = 0;
	m_iPlateChanNum = 0;
	m_iBPrisonChanNum = 0;
	//}}AFX_DATA_INIT
    m_lServerID = -1;
    m_iDevIndex = -1;
    memset(&m_struVcaDevAbility, 0, sizeof(m_struVcaDevAbility));

}


void CDlgVcaDevAbility::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgVcaDevAbility)
	DDX_Text(pDX, IDC_EDIT_ATM_CHAN_NUM, m_iAtmChanNum);
	DDX_Text(pDX, IDC_EDIT_VCA_CHAN_NUM, m_iVcaChanNum);
	DDX_Text(pDX, IDC_EDIT_ITS_CHAN_NUM, m_iITSChanNum);
	DDX_Text(pDX, IDC_EDIT_BBASE_CHAN_NUM, m_iBBaseChanNum);
	DDX_Text(pDX, IDC_EDIT_BFULL_CHAN_NUM, m_iBFullChanNum);
	DDX_Text(pDX, IDC_EDIT_BADVANCE_CHAN_NUM, m_iBAdvanceChanNum);
	DDX_Text(pDX, IDC_EDIT_PLATE_CHAN_NUM, m_iPlateChanNum);
	DDX_Text(pDX, IDC_EDIT_BPRISON_CHAN_NUM, m_iBPrisonChanNum);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgVcaDevAbility, CDialog)
	//{{AFX_MSG_MAP(CDlgVcaDevAbility)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BOOL CDlgVcaDevAbility::GetVcaDevAbility()
{
    BOOL bRet = FALSE;
    if (!NET_DVR_GetDeviceAbility(m_lServerID,  VCA_DEV_ABILITY, NULL, 0, (char*)&m_struVcaDevAbility, sizeof(m_struVcaDevAbility)))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "VCA_DEV_ABILITY");
        bRet = FALSE;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "VCA_DEV_ABILITY");
        bRet = TRUE;
    }
    return bRet;
}


/////////////////////////////////////////////////////////////////////////////
// CDlgVcaDevAbility message handlers


BOOL CDlgVcaDevAbility::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
    GetVcaDevAbility();
	
    m_iVcaChanNum = m_struVcaDevAbility.byVCAChanNum;
    m_iPlateChanNum = m_struVcaDevAbility.byPlateChanNum;
    m_iAtmChanNum = m_struVcaDevAbility.byATMChanNum;
    m_iBBaseChanNum = m_struVcaDevAbility.byBBaseChanNum;
    m_iBAdvanceChanNum = m_struVcaDevAbility.byBAdvanceChanNum;
    m_iBFullChanNum = m_struVcaDevAbility.byBFullChanNum;
    m_iITSChanNum = m_struVcaDevAbility.byITSChanNum;
    m_iBPrisonChanNum = m_struVcaDevAbility.byBPrisonChanNum;

    UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
