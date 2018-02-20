// DlgVcaBehaviorCfg.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgVcaBehaviorCfg.h"
#include "DlgVcaDrawMode.h"
#include "DlgVcaLF.h"
#include "DlgVcaParamkey.h"
#include "DlgVcaDevAbility.h"
#include "DlgVcaRuleCfg.h"
#include "DlgPUStream.h"
#include "DlgVcaBehaviorCalibrate.h"
#include "DlgvcaMaskRegion.h"
#include "DlgVcaEnterRegion.h"
#include "DlgSizeFilter.h"
#include "DlgVcaFaceDetect.h"
#include "DlgVcaWorkStatus.h"
#include "DlgVcaFaceSnapCfg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgVcaBehaviorCfg dialog


CDlgVcaBehaviorCfg::CDlgVcaBehaviorCfg(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgVcaBehaviorCfg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgVcaBehaviorCfg)
	m_bVcaActive = FALSE;
	//}}AFX_DATA_INIT
    m_lServerID = -1;
    m_iStartChannel = -1;
    m_iDevIndex = -1;
    m_iChannelNum = -1;
    m_iVcaChannel = -1;
	m_iCurChannel = -1;
    memset(&m_struVcaCtrlCfg, 0, sizeof(m_struVcaCtrlCfg));
}


void CDlgVcaBehaviorCfg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgVcaBehaviorCfg)
	DDX_Control(pDX, IDC_COMBO_VCA_TYPE, m_comboVcaType);
	DDX_Control(pDX, IDC_COMBO_STREAM, m_comboStream);
	DDX_Control(pDX, IDC_COMBO_ATM_MODE2, m_comboAtmMode);
	DDX_Control(pDX, IDC_COMBO_VCA_CHAN, m_comboVcaChan);
	DDX_Check(pDX, IDC_CHECK_VCA_ACTIVE, m_bVcaActive);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgVcaBehaviorCfg, CDialog)
	//{{AFX_MSG_MAP(CDlgVcaBehaviorCfg)
	ON_CBN_SELCHANGE(IDC_COMBO_VCA_CHAN, OnSelchangeComboVcaChan)
	ON_BN_CLICKED(ID_BTN_SET_VCA_CTRL, OnBtnSetVcaCtrl)
	ON_BN_CLICKED(IDC_BTN_VCA_RESTART, OnBtnVcaRestart)
	ON_BN_CLICKED(IDC_BTN_MASK_REGION, OnBtnMaskRegion)
	ON_BN_CLICKED(IDC_BTN_ENTER_REGION2, OnBtnEnterRegion2)
	ON_BN_CLICKED(IDC_BTN_VCA_DRAW_MODE, OnBtnVcaDrawMode)
	ON_BN_CLICKED(IDC_BTN_LF_CFG, OnBtnLfCfg)
	ON_BN_CLICKED(IDC_BTN_VCA_BEHAVIOR_KEY, OnBtnVcaBehaviorKey)
	ON_BN_CLICKED(IDC_BTN_DEVABILITY, OnBtnDevability)
	ON_BN_CLICKED(IDC_BTN_SET_RULECFG, OnBtnSetRulecfg)
	ON_BN_CLICKED(IDC_BTN_PU_STREAM, OnBtnPuStream)
	ON_BN_CLICKED(IDC_BTN_BEHAVIOR_CALIBRATE, OnBtnBehaviorCalibrate)
	ON_BN_CLICKED(IDC_BTN_SIZE_FILTER, OnBtnSizeFilter)
	ON_BN_CLICKED(IDC_BTN_FACE_DETECT, OnBtnFaceDetect)
	ON_BN_CLICKED(IDC_BTN_VCA_WORK_STATUS, OnBtnVcaWorkStatus)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgVcaBehaviorCfg message handlers

BOOL CDlgVcaBehaviorCfg::OnInitDialog() 
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

void CDlgVcaBehaviorCfg::InitWnd()
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

void CDlgVcaBehaviorCfg::InitComboVcaType()
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

void CDlgVcaBehaviorCfg::OnSelchangeComboVcaChan() 
{
    m_iVcaChannel = m_comboVcaChan.GetItemData(m_comboVcaChan.GetCurSel());
    SetVcaCtrlToWnd(m_struVcaCtrlCfg.struCtrlInfo[m_iVcaChannel-1]);
    UpdateData(FALSE);
}


BOOL CDlgVcaBehaviorCfg::SetVcaCtrlToWnd(NET_VCA_CTRLINFO const &struVcaCtrlInfo)
{

    for (int i = 0; i < m_comboVcaType.GetCount(); i++)
    {
        if (m_comboVcaType.GetItemData(i) == struVcaCtrlInfo.byVCAType )
        {
            m_comboVcaType.SetCurSel(i);
            break;
        }
    }

    m_comboStream.SetCurSel(struVcaCtrlInfo.byStreamWithVCA);
    m_bVcaActive = struVcaCtrlInfo.byVCAEnable;
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

BOOL CDlgVcaBehaviorCfg::GetVcaCtrlFromWnd(NET_VCA_CTRLINFO &struVcaCtrlInfo)
{
    struVcaCtrlInfo.byVCAEnable = m_bVcaActive;
    struVcaCtrlInfo.byStreamWithVCA = m_comboStream.GetCurSel();
    struVcaCtrlInfo.byVCAType = m_comboVcaType.GetItemData(m_comboVcaType.GetCurSel());
    struVcaCtrlInfo.byMode = m_comboAtmMode.GetCurSel();
    if (VCA_ATM == struVcaCtrlInfo.byVCAType)
    {
        struVcaCtrlInfo.byMode = m_comboAtmMode.GetCurSel();
    }

    return TRUE;
}

BOOL CDlgVcaBehaviorCfg::SetVcaCtrlCfg()
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

BOOL CDlgVcaBehaviorCfg::GetVcaCtrlCfg()
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

void CDlgVcaBehaviorCfg::OnBtnSetVcaCtrl() 
{
    UpdateData(TRUE);
    GetVcaCtrlFromWnd(m_struVcaCtrlCfg.struCtrlInfo[m_iVcaChannel-1]);
     if (!SetVcaCtrlCfg())
    {
        AfxMessageBox("Fail to set vca control");
    }
}

void CDlgVcaBehaviorCfg::OnBtnVcaRestart() 
{
    char szLan[128] = {0};
    if (!NET_VCA_RestartLib(m_lServerID, m_iVcaChannel))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_VCA_RestartLib %d", m_iVcaChannel);
        char sBufCn[128] =  {0};
        char sBufEn[128] = {0};
        sprintf(sBufCn, "智能通道%d智能库重启失败", m_iVcaChannel);
        sprintf(sBufEn, "VcaChannel%d failed to restart VCA library", m_iVcaChannel);
        g_StringLanType(szLan, sBufCn, sBufEn);
        AfxMessageBox(szLan);
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_VCA_RestartLib %d", m_iVcaChannel);
    }	
}

void CDlgVcaBehaviorCfg::OnBtnMaskRegion() 
{
	CDlgVcaMaskRegion dlg;
    dlg.m_lServerID = m_lServerID;
    dlg.m_iChannel = m_iVcaChannel;
    dlg.m_iDevIndex = m_iDevIndex;
    dlg.DoModal();
}

void CDlgVcaBehaviorCfg::OnBtnEnterRegion2() 
{
    CDlgVcaEnterRegion dlg;
    dlg.m_lServerID = m_lServerID;
    dlg.m_iChannel = m_iVcaChannel;
    dlg.m_iDevIndex = m_iDevIndex;
    dlg.DoModal();
}

void CDlgVcaBehaviorCfg::OnBtnVcaDrawMode() 
{
    CDlgVcaDrawMode dlg;
    dlg.m_lChannel = m_iVcaChannel;
    dlg.m_iDevIndex = m_iDevIndex;
    dlg.m_lServerID = m_lServerID;
    dlg.DoModal();
	
}

void CDlgVcaBehaviorCfg::OnBtnLfCfg() 
{
    CDlgVcaLF dlg;
    dlg.m_lServerID = m_lServerID;
    dlg.m_iDevIndex = m_iDevIndex;
    dlg.DoModal();
}

void CDlgVcaBehaviorCfg::OnBtnVcaBehaviorKey() 
{
    CDlgVcaParamkey dlg;
    dlg.m_lServerID = m_lServerID;
    dlg.m_iDevIndex = m_iDevIndex;
    dlg.m_lChannel = m_iVcaChannel;
    dlg.DoModal();
}

void CDlgVcaBehaviorCfg::OnBtnDevability() 
{
    CDlgVcaDevAbility dlg;
    dlg.m_lServerID = m_lServerID;
    dlg.m_iDevIndex = m_iDevIndex;
    dlg.DoModal();
}

void CDlgVcaBehaviorCfg::OnBtnSetRulecfg() 
{
    CDlgVcaRuleCfg dlg;
    dlg.m_lServerID = m_lServerID;
    dlg.m_iVcaChannel = m_iVcaChannel;
    dlg.m_iDevIndex = m_iDevIndex;
       
    dlg.DoModal();
}

void CDlgVcaBehaviorCfg::OnBtnPuStream() 
{
    CDlgPUStream dlg;
    dlg.m_iDevIndex = m_iDevIndex;
    dlg.m_lChannel = m_iVcaChannel;
    dlg.m_lServerID = m_lServerID;
    dlg.DoModal();
}

void CDlgVcaBehaviorCfg::OnBtnBehaviorCalibrate() 
{
    CDlgVcaBehaviorCalibrate dlg;
    dlg.m_lServerID = m_lServerID;
    dlg.m_iDevIndex = m_iDevIndex;
    dlg.m_lChannel = m_iVcaChannel;
    dlg.DoModal();
}

void CDlgVcaBehaviorCfg::OnBtnSizeFilter() 
{
    CDlgSizeFilter dlg;
    dlg.m_lServerID = m_lServerID;
    dlg.m_lChannel = m_iVcaChannel;
    dlg.m_iDevIndex = m_iDevIndex;
    dlg.DoModal();
}   

void CDlgVcaBehaviorCfg::OnBtnFaceDetect() 
{
	// TODO: Add your control notification handler code here
    CDlgVcaFaceDetect dlg;
    dlg.m_lServerID = m_lServerID;
    dlg.m_lChannel = m_iVcaChannel;
    dlg.m_iDevIndex = m_iDevIndex;
	dlg.m_iChannelNum = m_iChannelNum;
    dlg.DoModal();

}

void CDlgVcaBehaviorCfg::OnBtnVcaWorkStatus() 
{
    CDlgVcaWorkStatus dlg;
    dlg.m_lServerID = m_lServerID;
    dlg.m_iDevIndex = m_iDevIndex;
    dlg.m_lChanNum = m_iChannelNum;
    dlg.DoModal();
}