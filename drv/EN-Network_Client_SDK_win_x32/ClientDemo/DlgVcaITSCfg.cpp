// DlgVcaITSCfg.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgVcaITSCfg.h"
#include "DlgVcaDevAbility.h"
#include "DlgVcaLaneCfg.h"
#include "DlgPUStream.h"
#include "DlgRegionList.h"
#include "DlgTPSRuleCfg.h"
#include "DlgVcaAidRuleCfg.h"
#include "DlgVcaITSCalibrate.h"
#include "DlgVcaParamkey.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#include "DlgVcaDrawMode.h"

/////////////////////////////////////////////////////////////////////////////
// CDlgVcaITSCfg dialog


CDlgVcaITSCfg::CDlgVcaITSCfg(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgVcaITSCfg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgVcaITSCfg)
    	m_bVcaActive = FALSE;
	//}}AFX_DATA_INIT
    m_iDevIndex = -1;
    m_lServerID = -1;
    m_iStartChannel = -1;
    m_iChannelnumber = -1;
	m_iCurChannel = -1;
    memset(&m_struVCADrawMode, 0, sizeof(m_struVCADrawMode));
    m_iVcaChannel = -1;
    memset(&m_struVcaCtrlCfg, 0, sizeof(m_struVcaCtrlCfg));

    memset(&m_struMaskRegionList, 0, sizeof(m_struMaskRegionList));
    memset(&m_struReferenceRegionList, 0, sizeof(m_struReferenceRegionList));
    memset(&m_struLaneCfg, 0, sizeof(m_struLaneCfg));
    memset(&m_struAIDRuleCfg, 0, sizeof(m_struAIDRuleCfg));
    memset(&m_struTPSRuleCfg, 0, sizeof(m_struTPSRuleCfg));
    m_dwSceneMode = 0;
}


void CDlgVcaITSCfg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgVcaITSCfg)
	DDX_Control(pDX, IDC_COMBO_SCENE_MODE, m_comboSceneMode);
	DDX_Control(pDX, IDC_COMBO_STREAM, m_comboStream);
	DDX_Control(pDX, IDC_COMBO_VCA_TYPE, m_comboVcaType);
	DDX_Control(pDX, IDC_COMBO_VCA_CHAN, m_comboVcaChan);
	DDX_Check(pDX, IDC_CHECK_VCA_ACTIVE, m_bVcaActive);
	//}}AFX_DATA_MAP

}


BEGIN_MESSAGE_MAP(CDlgVcaITSCfg, CDialog)
	//{{AFX_MSG_MAP(CDlgVcaITSCfg)
	ON_BN_CLICKED(IDC_BTN_VCA_DEV_ABILITY, OnBtnVcaDevAbility)
	ON_BN_CLICKED(ID_BTN_SET_VCA_CTRL, OnBtnSetVcaCtrl)
	ON_CBN_SELCHANGE(IDC_COMBO_VCA_CHAN, OnSelchangeComboVcaChan)
	ON_BN_CLICKED(IDC_BTN_VCA_DRAW_MODE, OnBtnVcaDrawMode)
	ON_BN_CLICKED(IDC_BTN_MASK_REGION, OnBtnMaskRegion)
	ON_BN_CLICKED(IDC_BTN_REFERENCE_REGION, OnBtnReferenceRegion)
	ON_BN_CLICKED(IDC_BTN_LANECFG, OnBtnLanecfg)
	ON_BN_CLICKED(IDC_BTN_AID_RULECFG, OnBtnAidRulecfg)
	ON_BN_CLICKED(IDC_BTN_TPS_RULECFG, OnBtnTpsRulecfg)
	ON_BN_CLICKED(IDC_BTN_PU_STREAM, OnBtnPuStream)
	ON_BN_CLICKED(IDC_BTN_ITS_CALIBRATE, OnBtnItsCalibrate)
	ON_BN_CLICKED(IDC_BTN_SET_SCENE_MODE, OnBtnSetSceneMode)
	ON_BN_CLICKED(IDC_BTN_VCA_PARAM_KEY, OnBtnVcaParamKey)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgVcaITSCfg message handlers

void CDlgVcaITSCfg::OnBtnVcaDevAbility() 
{
	CDlgVcaDevAbility dlg;
    dlg.m_lServerID = m_lServerID;
    dlg.m_iDevIndex = m_iDevIndex;
    dlg.DoModal();
}


void CDlgVcaITSCfg::OnBtnSetVcaCtrl() 
{
    
    UpdateData(TRUE);
    int nChanIndex;
    nChanIndex = m_comboVcaChan.GetCurSel()+1;
    
    m_struVcaCtrlCfg.struCtrlInfo[nChanIndex-1].byVCAEnable = (unsigned char)m_bVcaActive;
    m_struVcaCtrlCfg.struCtrlInfo[nChanIndex-1].byVCAType = (unsigned char)m_comboVcaType.GetItemData(m_comboVcaType.GetCurSel());
    m_struVcaCtrlCfg.struCtrlInfo[nChanIndex-1].byStreamWithVCA = (unsigned char)m_comboStream.GetCurSel();
    
    if(!NET_DVR_SetDVRConfig(m_lServerID, NET_DVR_SET_VCA_CTRLCFG, nChanIndex , &m_struVcaCtrlCfg, sizeof(m_struVcaCtrlCfg)))
    {	
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "Fail to set vca ctrl");
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "Succ to set vca ctrl");
    }
}

BOOL CDlgVcaITSCfg::InsertComboVcaType()
{
    m_comboVcaType.ResetContent();
    int index = 0;
    if (g_pMainDlg->m_struVcaDevAbility.byBBaseChanNum > 0)
    {
        char szLan[128] = {0};
        g_StringLanType(szLan, "行为分析基本版", "Behavior of basic");
        m_comboVcaType.InsertString(index, szLan);
        m_comboVcaType.SetItemData(index, 1);
        index++;
    }
    if (g_pMainDlg->m_struVcaDevAbility.byBAdvanceChanNum > 0)
    {
        char szLan[128] = {0};
        g_StringLanType(szLan, "行为分析高级版", "Behavior of advanced");
        m_comboVcaType.InsertString(index, szLan);
        m_comboVcaType.SetItemData(index, 2);
        index++;
    }
    if (g_pMainDlg->m_struVcaDevAbility.byBFullChanNum > 0)
    {
        char szLan[128] = {0};
        g_StringLanType(szLan, "行为分析完整版", "Behavior of full");
        m_comboVcaType.InsertString(index, szLan);
        m_comboVcaType.SetItemData(index, 3);
        index++;
    }
    if (g_pMainDlg->m_struVcaDevAbility.byPlateChanNum > 0)
    {
        char szLan[128] = {0};
        g_StringLanType(szLan, "车牌识别", "Plate Recognition");
        m_comboVcaType.InsertString(index, szLan);
        m_comboVcaType.SetItemData(index, 4);
        index++;
    }
    if (g_pMainDlg->m_struVcaDevAbility.byATMChanNum > 0)
    {
        m_comboVcaType.InsertString(index, "ATM");
        m_comboVcaType.SetItemData(index, 5);
    }
    if (g_pMainDlg->m_struVcaDevAbility.byPDCChanNum > 0)
    {
        m_comboVcaType.InsertString(index, "PDC");
        m_comboVcaType.SetItemData(index, 6);
    }
    if (g_pMainDlg->m_struVcaDevAbility.byITSChanNum > 0)
    {
        m_comboVcaType.InsertString(index, "ITS");
        m_comboVcaType.SetItemData(index, 7);
    }
    return TRUE;
}

void CDlgVcaITSCfg::GetDevVcaChanPara()
{
    UpdateData(FALSE);
    
	memset(&m_struVcaCtrlCfg, 0,sizeof(NET_VCA_CTRLCFG));
    memcpy(&m_struVcaCtrlCfg, &g_pMainDlg->m_struVcaCtrlCfg,sizeof(NET_VCA_CTRLCFG));
    char sbuf[128];
    for (int i = 0; i < g_pMainDlg->m_struVcaDevAbility.byVCAChanNum; i++)
    {
        sprintf(sbuf, "VCA Chan%d", i+1);
        m_comboVcaChan.InsertString(i,sbuf);
    }
	
	switch (g_struDeviceInfo[m_iDevIndex].iDeviceType)
    {
	case IVMS_6200_T:
        m_comboVcaChan.SetCurSel(m_iCurChannel/*+m_iStartChannel*/);
		GetDlgItem(IDC_COMBO_VCA_CHAN)->EnableWindow(FALSE);
		m_iVcaChannel = m_iCurChannel+m_iStartChannel;
		break;
	default:
		m_comboVcaChan.SetCurSel(0);
		GetDlgItem(IDC_COMBO_VCA_CHAN)->EnableWindow(TRUE);
		break;
    }
    
//  m_comboVcaChan.SetCurSel(0);
    InsertComboVcaType(); 
    OnSelchangeComboVcaChan();	
}	// TODO: Add your control notification handler code here

void CDlgVcaITSCfg::OnSelchangeComboVcaChan() 
{
    m_iVcaChannel = m_comboVcaChan.GetCurSel()+1;
    SetComboVcaType();
    m_bVcaActive = m_struVcaCtrlCfg.struCtrlInfo[m_iVcaChannel-1].byVCAEnable;
//    EnableVcaWindow(m_bVcaActive);
    m_comboStream.SetCurSel(m_struVcaCtrlCfg.struCtrlInfo[m_iVcaChannel-1].byStreamWithVCA);
    UpdateData(FALSE);
}

void CDlgVcaITSCfg::SetComboVcaType()
{
    int nIndex = m_comboVcaType.GetCount();
    for (int i = 0; i < nIndex; i++)
    {
        if (m_comboVcaType.GetItemData(i) == m_struVcaCtrlCfg.struCtrlInfo[m_iVcaChannel-1].byVCAType )
        {
            m_comboVcaType.SetCurSel(i);
            return;
        }
        
    }
}

BOOL CDlgVcaITSCfg::OnInitDialog() 
{
	CDialog::OnInitDialog();
    InitWnd();
	
	
	GetDevVcaChanPara();
    
    GetSceneMode();
    SetSceneModeToWnd();
    UpdateData(FALSE);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgVcaITSCfg::InitWnd()
{
    char szLan[128] = {0};
    m_comboSceneMode.ResetContent();
    g_StringLanType(szLan, "普通高速公路", "Freeway");
    m_comboSceneMode.AddString(szLan);
    
    g_StringLanType(szLan, "高速隧道场景", "Tunnel");
    m_comboSceneMode.AddString(szLan);

    g_StringLanType(szLan, "高速桥梁场景", "Bridge");
    m_comboSceneMode.AddString(szLan);
}

BOOL CDlgVcaITSCfg::GetSceneMode()
{
    if (!NET_DVR_GetSceneMode(m_lServerID, m_iVcaChannel, &m_dwSceneMode))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GetSceneMode Chan[%d]", m_iVcaChannel);
        return FALSE;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GetSceneMode Chan[%d]", m_iVcaChannel);
        return TRUE;
    }
}

BOOL CDlgVcaITSCfg::SetSceneMode()
{
    if (!NET_DVR_SetSceneMode(m_lServerID, m_iVcaChannel, m_dwSceneMode))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_SetSceneMode Chan[%d]", m_iVcaChannel);
        return FALSE;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_SetSceneMode Chan[%d]", m_iVcaChannel);
        return TRUE;
    }
}

void CDlgVcaITSCfg::SetSceneModeToWnd()
{
    m_comboSceneMode.SetCurSel(m_dwSceneMode);
}
void CDlgVcaITSCfg::GetSceneModeFromWnd()
{
    m_dwSceneMode = m_comboSceneMode.GetCurSel();
}
void CDlgVcaITSCfg::OnBtnVcaDrawMode() 
{
    CDlgVcaDrawMode dlg;
    dlg.m_lChannel = m_iVcaChannel;
    dlg.m_iDevIndex = m_iDevIndex;
    dlg.m_lServerID = m_lServerID;
    dlg.DoModal();
}

void CDlgVcaITSCfg::OnBtnMaskRegion() 
{
    CDlgRegionList dlg;
    dlg.m_dwRegionType = MASK_REGION;
    dlg.m_lServerID = m_lServerID;
    dlg.m_lChannel = m_iVcaChannel;
    dlg.m_iDevIndex = m_iDevIndex;
    dlg.DoModal();
}

void CDlgVcaITSCfg::OnBtnReferenceRegion() 
{
    CDlgRegionList dlg;
    dlg.m_dwRegionType = REFERENCE_REGION;
    dlg.m_lServerID = m_lServerID;
    dlg.m_lChannel = m_iVcaChannel;
    dlg.m_iDevIndex = m_iDevIndex;
    dlg.DoModal();
}

void CDlgVcaITSCfg::OnBtnLanecfg() 
{
    CDlgVcaLaneCfg dlg;
    dlg.m_lServerID = m_lServerID;
    dlg.m_iDevIndex = m_iDevIndex;
    dlg.m_lChannel = m_iVcaChannel;
    dlg.DoModal();
}
void CDlgVcaITSCfg::OnBtnAidRulecfg() 
{
    CDlgVcaAidRuleCfg dlg;
    dlg.m_lServerID = m_lServerID;
    dlg.m_iDevIndex = m_iDevIndex;
    dlg.m_lChannel = m_iVcaChannel;
    dlg.DoModal();
}

void CDlgVcaITSCfg::OnBtnTpsRulecfg() 
{
    CDlgTPSRuleCfg dlg;
    dlg.m_iDevIndex = m_iDevIndex;
    dlg.m_lServerID = m_lServerID;
    dlg.m_lChannel = m_iVcaChannel;
    dlg.DoModal();
}

// #define NET_DVR_SET_AID_RULECFG         404         // 设置交通事件规则参数
// #define NET_DVR_GET_AID_RULECFG         405         // 获取交通事件规则参数
// 
// #define NET_DVR_SET_TPS_RULECFG         406         // 设置交通统计规则参数
// #define NET_DVR_GET_TPS_RULECFG         407         // 获取交通统计规则参数
BOOL CDlgVcaITSCfg::SetAIDRuleCfg()
{
    BOOL bRet = FALSE;
    if (!NET_DVR_SetDVRConfig(m_lServerID, NET_DVR_SET_AID_RULECFG, m_iVcaChannel, &m_struAIDRuleCfg, sizeof(m_struAIDRuleCfg)))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_SET_AID_RULECFG Chan[%d]", m_iVcaChannel);
        bRet = FALSE;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_SET_AID_RULECFG Chan[%d]", m_iVcaChannel);
        bRet = TRUE;
    }
    return bRet;
}

BOOL CDlgVcaITSCfg::GetAIDRuleCfg()
{
    DWORD dwReturn = 0;
    BOOL bRet = FALSE;
    if (!NET_DVR_GetDVRConfig(m_lServerID, NET_DVR_GET_AID_RULECFG, m_iVcaChannel, &m_struAIDRuleCfg, sizeof(m_struAIDRuleCfg), &dwReturn))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_AID_RULECFG Chan[%d]", m_iVcaChannel);
        bRet = FALSE;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_AID_RULECFG Chan[%d]", m_iVcaChannel);
        bRet = TRUE;
    }
    return bRet;
}

BOOL CDlgVcaITSCfg::SetTPSRuleCfg()
{
    BOOL bRet = FALSE;
    if (!NET_DVR_SetDVRConfig(m_lServerID, NET_DVR_SET_TPS_RULECFG, m_iVcaChannel, &m_struTPSRuleCfg, sizeof(m_struTPSRuleCfg)))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_SET_TPS_RULECFG Chan[%d]", m_iVcaChannel);
        bRet = FALSE;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_SET_TPS_RULECFG Chan[%d]", m_iVcaChannel);
        bRet = TRUE;
    }
    return bRet;
}

BOOL CDlgVcaITSCfg::GetTPSRuleCfg()
{
    DWORD dwReturn = 0;
    BOOL bRet = FALSE;
    if (!NET_DVR_GetDVRConfig(m_lServerID, NET_DVR_GET_TPS_RULECFG, m_iVcaChannel, &m_struTPSRuleCfg, sizeof(m_struTPSRuleCfg), &dwReturn))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_TPS_RULECFG Chan[%d]", m_iVcaChannel);
        bRet = FALSE;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_TPS_RULECFG Chan[%d]", m_iVcaChannel);
        bRet = TRUE;
    }
    return bRet;
}


BOOL CDlgVcaITSCfg::SetLaneCfg()
{
    BOOL bRet = FALSE;
    if (!NET_DVR_SetDVRConfig(m_lServerID, NET_DVR_SET_LANECFG, m_iVcaChannel, &m_struLaneCfg, sizeof(m_struLaneCfg)))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_SET_LANECFG Chan[%d]", m_iVcaChannel);
        bRet = FALSE;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_SET_LANECFG Chan[%d]", m_iVcaChannel);
        bRet = TRUE;
    }
    return bRet;
}


BOOL CDlgVcaITSCfg::GetLaneCfg()
{
    DWORD dwReturn = 0;
    BOOL bRet = FALSE;
    if (!NET_DVR_GetDVRConfig(m_lServerID, NET_DVR_GET_LANECFG, m_iVcaChannel, &m_struLaneCfg, sizeof(m_struLaneCfg), &dwReturn))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_LANECFG Chan[%d]", m_iVcaChannel);
        bRet = FALSE;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_LANECFG Chan[%d]", m_iVcaChannel);
        bRet = TRUE;
    }
    return bRet;
}

BOOL CDlgVcaITSCfg::SetMaskRegion()
{
    BOOL bRet = FALSE;
    if (!NET_DVR_SetDVRConfig(m_lServerID, NET_DVR_SET_TRAFFIC_MASK_REGION, m_iVcaChannel, &m_struMaskRegionList, sizeof(m_struMaskRegionList)))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_SET_TRAFFIC_MASK_REGION Chan[%d]", m_iVcaChannel);
        bRet = FALSE;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_SET_TRAFFIC_MASK_REGION Chan[%d]", m_iVcaChannel);
        bRet = TRUE;
    }
    return bRet;
}

BOOL CDlgVcaITSCfg::GetMaskRegion()
{
    DWORD dwReturn = 0;
    BOOL bRet = FALSE;
    if (!NET_DVR_GetDVRConfig(m_lServerID, NET_DVR_GET_TRAFFIC_MASK_REGION, m_iVcaChannel, &m_struMaskRegionList, sizeof(m_struMaskRegionList), &dwReturn))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_TRAFFIC_MASK_REGION Chan[%d]", m_iVcaChannel);
        bRet = FALSE;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_TRAFFIC_MASK_REGION Chan[%d]", m_iVcaChannel);
        bRet = TRUE;
    }
    return bRet;
}
BOOL CDlgVcaITSCfg::SetReferenceRegion()
{
    BOOL bRet = FALSE;
    if (!NET_DVR_SetDVRConfig(m_lServerID, NET_DVR_SET_REFERENCE_REGION, m_iVcaChannel, &m_struReferenceRegionList, sizeof(m_struReferenceRegionList)))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_SET_REFERENCE_REGION Chan[%d]", m_iVcaChannel);
        bRet = FALSE;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_SET_REFERENCE_REGION Chan[%d]", m_iVcaChannel);
        bRet = TRUE;
    }
    return bRet;
}
BOOL CDlgVcaITSCfg::GetReferenceRegion()
{
    DWORD dwReturn = 0;
    BOOL bRet = FALSE;
    if (!NET_DVR_GetDVRConfig(m_lServerID, NET_DVR_GET_REFERENCE_REGION, m_iVcaChannel, &m_struReferenceRegionList, sizeof(m_struReferenceRegionList), &dwReturn))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_REFERENCE_REGION Chan[%d]", m_iVcaChannel);
        bRet = FALSE;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_REFERENCE_REGION Chan[%d]", m_iVcaChannel);
        bRet = TRUE;
    }
    return bRet;
}



void CDlgVcaITSCfg::OnBtnPuStream() 
{
    CDlgPUStream dlg;
    dlg.m_iDevIndex = m_iDevIndex;
    dlg.m_lChannel = m_iVcaChannel;
    dlg.m_lServerID = m_lServerID;
    dlg.DoModal();
}

void CDlgVcaITSCfg::OnBtnItsCalibrate() 
{
    CDlgVcaITSCalibrate dlg;
    dlg.m_iDevIndex = m_iDevIndex;
    dlg.m_lChannel = m_iVcaChannel;
    dlg.m_lServerID = m_lServerID;
    dlg.DoModal();

}

void CDlgVcaITSCfg::OnBtnSetSceneMode() 
{
    GetSceneModeFromWnd();
    if (SetSceneMode())
    {
        AfxMessageBox("Succ set scene mode") ;       
    }
    else
    {
        AfxMessageBox("Fail to set scene mode");
    }
}

void CDlgVcaITSCfg::OnBtnVcaParamKey() 
{
    CDlgVcaParamkey dlg;
    dlg.m_lServerID = m_lServerID;
    dlg.m_iDevIndex = m_iDevIndex;
    dlg.m_lChannel = m_iVcaChannel;
    dlg.DoModal();
}
