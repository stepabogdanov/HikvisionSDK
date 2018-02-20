// DlgVcaChanCtrlCfg.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgVcaChanCtrlCfg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgVcaChanCtrlCfg dialog


CDlgVcaChanCtrlCfg::CDlgVcaChanCtrlCfg(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgVcaChanCtrlCfg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgVcaChanCtrlCfg)
	m_bChkStreamWithVca = FALSE;
	m_bChkEnable = FALSE;
	//}}AFX_DATA_INIT
}


void CDlgVcaChanCtrlCfg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgVcaChanCtrlCfg)
	DDX_Control(pDX, IDC_COMBO_ATM_MODE, m_comboAtmMode);
	DDX_Control(pDX, IDC_COMBO_CHAN_VCATYPE, m_comboChanVcaType);
	DDX_Control(pDX, IDC_COMBO_CHANNEL, m_comboChan);
	DDX_Check(pDX, IDC_CHK_STREAM_WITH_VCA, m_bChkStreamWithVca);
	DDX_Check(pDX, IDC_CHK_ENABLE, m_bChkEnable);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgVcaChanCtrlCfg, CDialog)
	//{{AFX_MSG_MAP(CDlgVcaChanCtrlCfg)
	ON_BN_CLICKED(IDC_BTN_SURE, OnBtnSure)
	ON_BN_CLICKED(IDC_BTN_GET, OnBtnGet)
	ON_BN_CLICKED(IDC_BTN_SET, OnBtnSet)
	ON_CBN_SELCHANGE(IDC_COMBO_CHANNEL, OnSelchangeComboChannel)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgVcaChanCtrlCfg message handlers
BOOL CDlgVcaChanCtrlCfg::OnInitDialog()
{
	CDialog::OnInitDialog();
	char szLan[128] = {0};
    
	m_comboChan.ResetContent();
    for (int i = 0; i < m_iChannelNum; i++)
    {
        sprintf(szLan, "Chan%d", i+1);
        m_comboChan.InsertString(i,szLan);
        m_comboChan.SetItemData(i, i+1);
    }
	
	memset(&m_struVcaDevAbility, 0, sizeof(NET_VCA_DEV_ABILITY));
	if(!NET_DVR_GetDeviceAbility(g_struDeviceInfo[m_iDevIndex].lLoginID,  VCA_DEV_ABILITY, NULL, 0, (char*)&m_struVcaDevAbility, sizeof(NET_VCA_DEV_ABILITY)))
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "VCA_DEV_ABILITY");
		g_StringLanType(szLan, "设备不支持", "Device does not support");
		AfxMessageBox(szLan);
		return FALSE;
	}
	else 
	{
		g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "VCA_DEV_ABILITY");
    }
	
	m_comboChanVcaType.ResetContent();
    int index = 0;
    if (m_struVcaDevAbility.byBBaseChanNum > 0)
    {
        char szLan[128] = {0};
        g_StringLanType(szLan, "行为分析基本版", "Behavior of basic");
        m_comboChanVcaType.InsertString(index, szLan);
        m_comboChanVcaType.SetItemData(index, VCA_BEHAVIOR_BASE);
        index++;
    }
    if (m_struVcaDevAbility.byBAdvanceChanNum > 0)
    {
        char szLan[128] = {0};
        g_StringLanType(szLan, "行为分析高级版", "Behavior of advanced");
        m_comboChanVcaType.InsertString(index, szLan);
        m_comboChanVcaType.SetItemData(index, VCA_BEHAVIOR_ADVANCE);
        index++;
    }
    if (m_struVcaDevAbility.byBFullChanNum > 0)
    {
        char szLan[128] = {0};
        g_StringLanType(szLan, "行为分析完整版", "Behavior of full");
        m_comboChanVcaType.InsertString(index, szLan);
        m_comboChanVcaType.SetItemData(index, VCA_BEHAVIOR_FULL);
        index++;
    }
    if (m_struVcaDevAbility.byPlateChanNum> 0)
    {
        m_comboChanVcaType.InsertString(index, "Plate Recognition");
        m_comboChanVcaType.SetItemData(index, VCA_PLATE);
        index++;
    }
    if (m_struVcaDevAbility.byATMChanNum > 0)
    {
        m_comboChanVcaType.InsertString(index, "ATM");
        m_comboChanVcaType.SetItemData(index, VCA_ATM);
        index++;
    }
	if (m_struVcaDevAbility.byPDCChanNum > 0)
    {
        m_comboChanVcaType.InsertString(index, "PDC");
        m_comboChanVcaType.SetItemData(index, VCA_PDC);
        index++;
    }
    if (m_struVcaDevAbility.byITSChanNum > 0)
    {
        m_comboChanVcaType.InsertString(index, "ITS");
        m_comboChanVcaType.SetItemData(index, VCA_ITS);
        index++;
    }
    
    if (m_struVcaDevAbility.byBPrisonChanNum > 0)
    {
        m_comboChanVcaType.InsertString(index, "Behavior of prison");
        m_comboChanVcaType.SetItemData(index, VCA_BEHAVIOR_PRISON);
        index++;
    }	

	if (g_pMainDlg->m_struVcaDevAbility.byFSnapChanNum > 0)
	{
        m_comboChanVcaType.InsertString(index, "Face Snap");
        m_comboChanVcaType.SetItemData(index, VCA_FACE_SNAP);
        index++;
	}
	
	if (g_pMainDlg->m_struVcaDevAbility.byFSnapRecogChanNum > 0)
	{
        m_comboChanVcaType.InsertString(index, "Face Snap and Recognition");
        m_comboChanVcaType.SetItemData(index, VCA_FACE_SNAPRECOG);
        index++;
	}
	
	if (g_pMainDlg->m_struVcaDevAbility.byFRetrievalChanNum > 0)
	{
        m_comboChanVcaType.InsertString(index, "Face Retrieval");
        m_comboChanVcaType.SetItemData(index, VCA_FACE_RETRIEVAL);
        index++;
	}
	
	if (g_pMainDlg->m_struVcaDevAbility.byFRecogChanNum > 0)
	{
        m_comboChanVcaType.InsertString(index, "Face Recognize");
        m_comboChanVcaType.SetItemData(index, VCA_FACE_RECOG);
        index++;
	}

	if (g_pMainDlg->m_struVcaDevAbility.byBPPerimeterChanNum > 0)
	{
        m_comboChanVcaType.InsertString(index, "Prison perimeter");
        m_comboChanVcaType.SetItemData(index, VCA_BEHAVIOR_PRISON_PERIMETER);
        index++;
	}
	
	if (g_pMainDlg->m_struVcaDevAbility.byTPSChanNum > 0)
	{
        m_comboChanVcaType.InsertString(index, "TPS");
        m_comboChanVcaType.SetItemData(index, VCA_TPS);
        index++;
	}
	
	if (!GetVcaCtrlCfg())
    {
        AfxMessageBox("Fail to get vca ctrl");
		CDialog::OnCancel();
        return FALSE;
    }
    
    
    m_comboChan.SetCurSel(0);
	OnSelchangeComboChannel();
	
	return TRUE;
}

void CDlgVcaChanCtrlCfg::OnBtnSure() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
    GetVcaCtrlFromWnd(m_struVcaCtrlCfg.struCtrlInfo[m_iVcaChannel-1]);
}

void CDlgVcaChanCtrlCfg::OnBtnGet() 
{
	// TODO: Add your control notification handler code here
	GetVcaCtrlCfg();
}

void CDlgVcaChanCtrlCfg::OnBtnSet() 
{
	// TODO: Add your control notification handler code here
	SetVcaCtrlCfg();
}


BOOL CDlgVcaChanCtrlCfg::SetVcaCtrlToWnd(NET_VCA_CTRLINFO const &struVcaCtrlInfo)
{
	
    for (int i = 0; i < m_comboChanVcaType.GetCount(); i++)
    {
        if (m_comboChanVcaType.GetItemData(i) == struVcaCtrlInfo.byVCAType)
        {
            m_comboChanVcaType.SetCurSel(i);
            break;
        }
    }
	
    m_bChkStreamWithVca = struVcaCtrlInfo.byStreamWithVCA;
    m_bChkEnable = struVcaCtrlInfo.byVCAEnable;
    m_comboAtmMode.SetCurSel(struVcaCtrlInfo.byMode);
    if (struVcaCtrlInfo.byVCAType == VCA_ATM)
    {
        GetDlgItem(IDC_STATIC_ATM_MODE)->ShowWindow(SW_SHOW);
        m_comboAtmMode.ShowWindow(SW_SHOW);
        m_comboAtmMode.SetCurSel(struVcaCtrlInfo.byMode);
    }
    else
    {
        GetDlgItem(IDC_STATIC_ATM_MODE)->ShowWindow(SW_HIDE);
        m_comboAtmMode.ShowWindow(SW_HIDE);
    }
    return TRUE;
}

BOOL CDlgVcaChanCtrlCfg::GetVcaCtrlFromWnd(NET_VCA_CTRLINFO &struVcaCtrlInfo)
{
    struVcaCtrlInfo.byVCAEnable = m_bChkEnable;
    struVcaCtrlInfo.byStreamWithVCA = m_bChkStreamWithVca;
    struVcaCtrlInfo.byVCAType = m_comboChanVcaType.GetItemData(m_comboChanVcaType.GetCurSel());
    struVcaCtrlInfo.byMode = m_comboAtmMode.GetCurSel();
    if (VCA_ATM == struVcaCtrlInfo.byVCAType)
    {
        struVcaCtrlInfo.byMode = m_comboAtmMode.GetCurSel();
    }
	
    return TRUE;
}

BOOL CDlgVcaChanCtrlCfg::SetVcaCtrlCfg()
{
    BOOL bRet = FALSE;
    if(!NET_DVR_SetDVRConfig(m_lServerID, NET_DVR_SET_VCA_CTRLCFG, m_iVcaChannel, &m_struVcaCtrlCfg, sizeof(m_struVcaCtrlCfg)))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_SET_VCA_CTRLCFG");            
        bRet = FALSE;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_SET_VCA_CTRLCFG");            
        bRet = TRUE;
    }
    return bRet;
}

BOOL CDlgVcaChanCtrlCfg::GetVcaCtrlCfg()
{
    BOOL bRet = FALSE;
    DWORD dwReturn = 0;
    if(!NET_DVR_GetDVRConfig(m_lServerID, NET_DVR_GET_VCA_CTRLCFG, m_iVcaChannel, &m_struVcaCtrlCfg, sizeof(m_struVcaCtrlCfg), &dwReturn))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_VCA_CTRLCFG");            
        bRet = FALSE;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_VCA_CTRLCFG");            
        bRet = TRUE;
    }
    return bRet;
}

void CDlgVcaChanCtrlCfg::OnSelchangeComboChannel() 
{
	// TODO: Add your control notification handler code here
	m_iVcaChannel = m_comboChan.GetItemData(m_comboChan.GetCurSel());
    SetVcaCtrlToWnd(m_struVcaCtrlCfg.struCtrlInfo[m_iVcaChannel-1]);
    UpdateData(FALSE);
}
