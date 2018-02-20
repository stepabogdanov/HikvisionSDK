// DlgVcaFace.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgVcaFace.h"
#include "DlgPUStream.h"
#include "DlgVcaDevAbility.h"
#include "DlgvcaMaskRegion.h"
#include "DlgVcaDrawMode.h"
#include "DlgSizeFilter.h"
#include "DlgVcaFaceSnapCfg.h"
#include "DlgVcaFindBackgroundPic.h"
#include "DlgVcaSingleProcImg.h"
#include "DlgVcaBlackList.h"
#include "DlgVcaFindSnapData.h"
#include "DlgVcaFaceMatchLogSearch.h"
#include "DlgVcaDataBase.h"
#include "DlgVcaSnapDatabase.h"
#include "DlgVcaFaceDataBase.h"
#include "DlgVcaSavePathConfig.h"
#include "DlgVcaDevAccessCfg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgVcaFace dialog


CDlgVcaFace::CDlgVcaFace(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgVcaFace::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgVcaFace)
	m_bVcaActive = FALSE;
	m_bChkSnapEn = FALSE;
	//}}AFX_DATA_INIT
}


void CDlgVcaFace::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgVcaFace)
	DDX_Control(pDX, IDC_COMBO_ATM_MODE, m_comboAtmMode);
	DDX_Control(pDX, IDC_COMBO_STREAM, m_comboStream);
	DDX_Control(pDX, IDC_COMBO_VCA_TYPE, m_comboVcaType);
	DDX_Control(pDX, IDC_COMBO_VCA_CHAN, m_comboVcaChan);
	DDX_Check(pDX, IDC_CHECK_VCA_ACTIVE, m_bVcaActive);
	DDX_Check(pDX, IDC_CHK_SNAP_ENABLE, m_bChkSnapEn);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgVcaFace, CDialog)
	//{{AFX_MSG_MAP(CDlgVcaFace)
	ON_CBN_SELCHANGE(IDC_COMBO_VCA_CHAN, OnSelchangeComboVcaChan)
	ON_BN_CLICKED(ID_BTN_SET_VCA_CTRL, OnBtnSetVcaCtrl)
	ON_BN_CLICKED(IDC_BTN_PU_STREAM, OnBtnPuStream)
	ON_BN_CLICKED(IDC_BTN_DEVABILITY, OnBtnDevability)
	ON_BN_CLICKED(IDC_BTN_MASK_REGION, OnBtnMaskRegion)
	ON_BN_CLICKED(IDC_BTN_VCA_DRAW_MODE, OnBtnVcaDrawMode)
	ON_BN_CLICKED(IDC_BTN_FACESNAP, OnBtnFacesnap)
	ON_BN_CLICKED(IDC_BTN_FIND_BACKGROUNDPIC, OnBtnFindBackgroundpic)
	ON_BN_CLICKED(IDC_BTN_FD_PROCIMG, OnBtnFdProcimg)
	ON_BN_CLICKED(IDC_BTN_BLACKLIST, OnBtnBlacklist)
	ON_BN_CLICKED(IDC_BTN_FIND_SNAP_PIC, OnBtnFindSnapPic)
	ON_BN_CLICKED(IDC_BTN_FACEMATCH_LOG, OnBtnFacematchLog)
	ON_BN_CLICKED(IDC_BTN_VCA_DATABASE, OnBtnVcaDatabase)
	ON_BN_CLICKED(IDC_BTN_SNAP_DATABASE, OnBtnSnapDatabase)
	ON_BN_CLICKED(IDC_BTN_FACE_DATABASE, OnBtnFaceDatabase)
	ON_BN_CLICKED(IDC_BTN_SAVE_PATH, OnBtnSavePath)
	ON_BN_CLICKED(IDC_BTN_DEV_ACCESS_CFG, OnBtnDevAccessCfg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgVcaFace message handlers
BOOL CDlgVcaFace::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
    InitWnd();
    
    if (!GetVcaCtrlCfg())
    {
        AfxMessageBox("Fail to get vca ctrl");
		CDialog::OnCancel();
        return FALSE;
    }
	
	m_comboVcaChan.SetCurSel(0);
    OnSelchangeComboVcaChan();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgVcaFace::InitWnd()
{
    char  szLan[128] = {0};
    char szLanCn[128] = {0};
    char szLanEn[128] = {0};
    m_comboVcaChan.ResetContent();
    for (int i = 0; i < m_iChannelNum; i++)
    {
        sprintf(szLan, "Chan%d", i+1);
        m_comboVcaChan.InsertString(i,szLan);
        m_comboVcaChan.SetItemData(i, i +1 );
    }
	
    InitComboVcaType();
	
}

void CDlgVcaFace::InitComboVcaType()
{
    m_comboVcaType.ResetContent();
    int index = 0;
    if (g_pMainDlg->m_struVcaDevAbility.byBBaseChanNum > 0)
    {
        char szLan[128] = {0};
        g_StringLanType(szLan, "行为分析基本版", "Behavior of basic");
        m_comboVcaType.InsertString(index, szLan);
        m_comboVcaType.SetItemData(index, VCA_BEHAVIOR_BASE);
        index++;
    }
    if (g_pMainDlg->m_struVcaDevAbility.byBAdvanceChanNum > 0)
    {
        char szLan[128] = {0};
        g_StringLanType(szLan, "行为分析高级版", "Behavior of advanced");
        m_comboVcaType.InsertString(index, szLan);
        m_comboVcaType.SetItemData(index, VCA_BEHAVIOR_ADVANCE);
        index++;
    }
    if (g_pMainDlg->m_struVcaDevAbility.byBFullChanNum > 0)
    {
        char szLan[128] = {0};
        g_StringLanType(szLan, "行为分析完整版", "Behavior of full");
        m_comboVcaType.InsertString(index, szLan);
        m_comboVcaType.SetItemData(index, VCA_BEHAVIOR_FULL);
        index++;
    }
    if (g_pMainDlg->m_struVcaDevAbility.byPlateChanNum> 0)
    {
        m_comboVcaType.InsertString(index, "Plate Recognition");
        m_comboVcaType.SetItemData(index, VCA_PLATE);
        index++;
    }
    if (g_pMainDlg->m_struVcaDevAbility.byATMChanNum > 0)
    {
        m_comboVcaType.InsertString(index, "ATM");
        m_comboVcaType.SetItemData(index, VCA_ATM);
        index++;
    }
    if (g_pMainDlg->m_struVcaDevAbility.byITSChanNum > 0)
    {
        m_comboVcaType.InsertString(index, "ITS");
        m_comboVcaType.SetItemData(index, VCA_ITS);
        index++;
    }
    
    if (g_pMainDlg->m_struVcaDevAbility.byBPrisonChanNum > 0)
    {
        m_comboVcaType.InsertString(index, "Behavior of prison");
        m_comboVcaType.SetItemData(index, VCA_BEHAVIOR_PRISON);
        index++;
    }
	
	if (g_pMainDlg->m_struVcaDevAbility.byFSnapChanNum > 0)
	{
        m_comboVcaType.InsertString(index, "Face Snap");
        m_comboVcaType.SetItemData(index, VCA_FACE_SNAP);
        index++;
	}
	
	if (g_pMainDlg->m_struVcaDevAbility.byFSnapRecogChanNum > 0)
	{
        m_comboVcaType.InsertString(index, "Face Snap and Recognition");
        m_comboVcaType.SetItemData(index, VCA_FACE_SNAPRECOG);
        index++;
	}
	
	if (g_pMainDlg->m_struVcaDevAbility.byFRetrievalChanNum > 0)
	{
        m_comboVcaType.InsertString(index, "Face Retrieval");
        m_comboVcaType.SetItemData(index, VCA_FACE_RETRIEVAL);
        index++;
	}

	if (g_pMainDlg->m_struVcaDevAbility.byFRecogChanNum > 0)
	{
        m_comboVcaType.InsertString(index, "Face Recognize");
        m_comboVcaType.SetItemData(index, VCA_FACE_RECOG);
        index++;
	}

	if (g_pMainDlg->m_struVcaDevAbility.byBPPerimeterChanNum > 0)
	{
        m_comboVcaType.InsertString(index, "Prison perimeter");
        m_comboVcaType.SetItemData(index, VCA_BEHAVIOR_PRISON_PERIMETER);
        index++;
	}
	
	if (g_pMainDlg->m_struVcaDevAbility.byTPSChanNum > 0)
	{
        m_comboVcaType.InsertString(index, "TPS");
        m_comboVcaType.SetItemData(index, VCA_TPS);
        index++;
	}
}

void CDlgVcaFace::OnSelchangeComboVcaChan() 
{
	// TODO: Add your control notification handler code here
	m_iVcaChannel = m_comboVcaChan.GetItemData(m_comboVcaChan.GetCurSel());
    SetVcaCtrlToWnd(m_struVcaCtrlCfg.struCtrlInfo[m_iVcaChannel-1]);
    UpdateData(FALSE);
}

BOOL CDlgVcaFace::SetVcaCtrlToWnd(NET_VCA_CTRLINFO const &struVcaCtrlInfo)
{
	
    for (int i = 0; i < m_comboVcaType.GetCount(); i++)
    {
        if (m_comboVcaType.GetItemData(i) == struVcaCtrlInfo.byVCAType)
        {
            m_comboVcaType.SetCurSel(i);
            break;
        }
    }
	
    m_comboStream.SetCurSel(struVcaCtrlInfo.byStreamWithVCA);
    m_bVcaActive = struVcaCtrlInfo.byVCAEnable;
    m_comboAtmMode.SetCurSel(struVcaCtrlInfo.byMode);
	m_bChkSnapEn = struVcaCtrlInfo.byControlType&0x1;
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

BOOL CDlgVcaFace::GetVcaCtrlFromWnd(NET_VCA_CTRLINFO &struVcaCtrlInfo)
{
    struVcaCtrlInfo.byVCAEnable = m_bVcaActive;
    struVcaCtrlInfo.byStreamWithVCA = m_comboStream.GetCurSel();
    struVcaCtrlInfo.byVCAType = m_comboVcaType.GetItemData(m_comboVcaType.GetCurSel());
    struVcaCtrlInfo.byMode = m_comboAtmMode.GetCurSel();
    if (VCA_ATM == struVcaCtrlInfo.byVCAType)
    {
        struVcaCtrlInfo.byMode = m_comboAtmMode.GetCurSel();
    }
	struVcaCtrlInfo.byControlType = m_bChkSnapEn;
	
    return TRUE;
}

BOOL CDlgVcaFace::SetVcaCtrlCfg()
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

BOOL CDlgVcaFace::GetVcaCtrlCfg()
{
    BOOL bRet = FALSE;
    DWORD dwReturn = 0;
    if(!NET_DVR_GetDVRConfig(m_lServerID, NET_DVR_GET_VCA_CTRLCFG, m_iVcaChannel, &m_struVcaCtrlCfg, sizeof(m_struVcaCtrlCfg), &dwReturn))
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


void CDlgVcaFace::OnBtnSetVcaCtrl() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
    GetVcaCtrlFromWnd(m_struVcaCtrlCfg.struCtrlInfo[m_iVcaChannel-1]);
	if (!SetVcaCtrlCfg())
    {
        AfxMessageBox("Fail to set vca control");
    }
}

void CDlgVcaFace::OnBtnPuStream() 
{
	// TODO: Add your control notification handler code here
	CDlgPUStream dlg;
    dlg.m_iDevIndex = m_iDevIndex;
    dlg.m_lChannel = m_iVcaChannel;
    dlg.m_lServerID = m_lServerID;
    dlg.DoModal();
}

void CDlgVcaFace::OnBtnDevability() 
{
	// TODO: Add your control notification handler code here
	CDlgVcaDevAbility dlg;
    dlg.m_lServerID = m_lServerID;
    dlg.m_iDevIndex = m_iDevIndex;
    dlg.DoModal();
}

void CDlgVcaFace::OnBtnMaskRegion() 
{
	// TODO: Add your control notification handler code here
	CDlgVcaMaskRegion dlg;
    dlg.m_lServerID = m_lServerID;
    dlg.m_iChannel = m_iVcaChannel;
    dlg.m_iDevIndex = m_iDevIndex;
    dlg.DoModal();
}

void CDlgVcaFace::OnBtnVcaDrawMode() 
{
	// TODO: Add your control notification handler code here
	CDlgVcaDrawMode dlg;
    dlg.m_lChannel = m_iVcaChannel;
    dlg.m_iDevIndex = m_iDevIndex;
    dlg.m_lServerID = m_lServerID;
    dlg.DoModal();
}

void CDlgVcaFace::OnBtnFacesnap() 
{
	// TODO: Add your control notification handler code here
	CDlgVcaFaceSnapCfg dlg;
    dlg.m_lServerID = m_lServerID;
    dlg.m_lChannel = m_iVcaChannel;
    dlg.m_iDevIndex = m_iDevIndex;
    dlg.DoModal();
}

void CDlgVcaFace::OnBtnFindBackgroundpic() 
{
	// TODO: Add your control notification handler code here
	CDlgVcaFindBackgroundPic dlg;
    dlg.m_lServerID = m_lServerID;
    dlg.m_iDevIndex = m_iDevIndex;
    dlg.DoModal();
}

void CDlgVcaFace::OnBtnFdProcimg() 
{
	// TODO: Add your control notification handler code here
	CDlgVcaSingleProcImg dlg;
    dlg.m_lServerID = m_lServerID;
	dlg.m_lChannel = m_iVcaChannel;
    dlg.m_iDevIndex = m_iDevIndex;
    dlg.DoModal();
}

void CDlgVcaFace::OnBtnBlacklist() 
{
	// TODO: Add your control notification handler code here
	CDlgVcaBlackList dlg;
    dlg.m_lServerID = m_lServerID;
	dlg.m_lChannel = m_iVcaChannel;
    dlg.m_iDevIndex = m_iDevIndex;
    dlg.DoModal();
}

void CDlgVcaFace::OnBtnFindSnapPic() 
{
	// TODO: Add your control notification handler code here
	CDlgVcaFindSnapData dlg;
    dlg.m_lServerID = m_lServerID;
	dlg.m_lChannel = m_iVcaChannel;
    dlg.m_iDevIndex = m_iDevIndex;
    dlg.DoModal();
}

void CDlgVcaFace::OnBtnFacematchLog() 
{
	// TODO: Add your control notification handler code here
	CDlgVcaFaceMatchLogSearch dlg;
    dlg.m_lServerID = m_lServerID;
	dlg.m_lChannel = m_iVcaChannel;
    dlg.m_iDevIndex = m_iDevIndex;
    dlg.DoModal();
}

void CDlgVcaFace::OnBtnVcaDatabase() 
{
	// TODO: Add your control notification handler code here
	CDlgVcaDataBase dlg;
	dlg.m_lServerID = m_lServerID;
	dlg.m_iDevIndex = m_iDevIndex;
	dlg.DoModal();
}

void CDlgVcaFace::OnBtnSnapDatabase() 
{
	// TODO: Add your control notification handler code here
	CDlgVcaSnapDatabase dlg;
	dlg.m_lServerID = m_lServerID;
	dlg.m_iDevIndex = m_iDevIndex;
	dlg.DoModal();
}

void CDlgVcaFace::OnBtnFaceDatabase() 
{
	// TODO: Add your control notification handler code here
	CDlgVcaFaceDataBase dlg;
	dlg.m_lServerID = m_lServerID;
    dlg.m_iDevIndex = m_iDevIndex;
	dlg.DoModal();
}

void CDlgVcaFace::OnBtnSavePath() 
{
	// TODO: Add your control notification handler code here
	CDlgVcaSavePathConfig dlg;
    dlg.m_lServerID = m_lServerID;
	dlg.m_lChannel = m_iVcaChannel;
	dlg.m_iDevIndex = m_iDevIndex;
	dlg.DoModal();
}

void CDlgVcaFace::OnBtnDevAccessCfg() 
{
	// TODO: Add your control notification handler code here
	CDlgVcaDevAccessCfg dlg;
    dlg.m_lServerID = m_lServerID;
	dlg.m_lChannel = m_iVcaChannel;
	dlg.m_iDevIndex = m_iDevIndex;
	dlg.DoModal();
}
