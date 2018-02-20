// DlgAlarmOutCfg.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgAlarmOutCfg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgAlarmOutCfg dialog


CDlgAlarmOutCfg::CDlgAlarmOutCfg(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgAlarmOutCfg::IDD, pParent)
,m_iSirenDelayTime(0)
,m_iDevIndex(-1)
{
	//{{AFX_DATA_INIT(CDlgAlarmOutCfg)
	m_iDelayTime = 0;
	m_csName = _T("");
	m_csSirenName = _T("");
	m_iSirenDelayTime = 0;
	//}}AFX_DATA_INIT
    memset(&m_struAbility, 0, sizeof(m_struAbility));
    m_lServerID = -1;
    m_iDevIndex = -1;
    memset(&m_struAlarmOutParam, 0, sizeof(m_struAlarmOutParam));
    memset(&m_struSirenParam, 0, sizeof(m_struSirenParam));
}


void CDlgAlarmOutCfg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgAlarmOutCfg)
	DDX_Control(pDX, IDC_LIST_SIREN_ALARM_IN, m_listSirenAlarmIn);
	DDX_Control(pDX, IDC_COMBO_SIREN_INDEX, m_comboSirenIndex);
	DDX_Control(pDX, IDC_LIST_ALARM_IN, m_listAlarmIn);
	DDX_Control(pDX, IDC_COMBO_ALARMOUT_INDEX, m_comboAlarmOutIndex);
	DDX_Text(pDX, IDC_EDIT_DELAY_TIME, m_iDelayTime);
	DDX_Text(pDX, IDC_EDIT_NAME, m_csName);
	DDV_MaxChars(pDX, m_csName, 32);
	DDX_Text(pDX, IDC_EDIT_SIREN_NAME, m_csSirenName);
	DDV_MaxChars(pDX, m_csSirenName, 32);
	DDX_Text(pDX, IDC_EDIT_SIREN_DELAYTIME, m_iSirenDelayTime);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgAlarmOutCfg, CDialog)
	//{{AFX_MSG_MAP(CDlgAlarmOutCfg)
	ON_BN_CLICKED(IDC_BTN_SET_ALARMOUT_PARAM, OnBtnSetAlarmoutParam)
	ON_CBN_SELCHANGE(IDC_COMBO_ALARMOUT_INDEX, OnSelchangeComboAlarmoutIndex)
	ON_BN_CLICKED(IDC_BTN_OPEN_ALARMOUT, OnBtnOpenAlarmout)
	ON_BN_CLICKED(IDC_BTN_CLOSE_ALARMOUT, OnBtnCloseAlarmout)
	ON_BN_CLICKED(IDC_BNT_SET_SIREN_PARAM, OnBntSetSirenParam)
	ON_CBN_SELCHANGE(IDC_COMBO_SIREN_INDEX, OnSelchangeComboSirenIndex)
	ON_BN_CLICKED(IDC_BTN_OPEN_SIREN, OnBtnOpenSiren)
	ON_BN_CLICKED(IDC_BTN_CLOSE_SIREN, OnBtnCloseSiren)
	ON_NOTIFY(NM_RCLICK, IDC_LIST_ALARM_IN, OnRclickListAlarmIn)
	ON_COMMAND(ID_MENU_CANCEL_ALL, OnMenuCancelAll)
	ON_COMMAND(ID_MENU_SELECT_ALL, OnMenuSelectAll)
	ON_BN_CLICKED(IDC_BTN_OPEN_ALARMOUT_ALL, OnBtnOpenAlarmoutAll)
	ON_BN_CLICKED(IDC_BTN_CLOSE_ALARMOUT_ALL, OnBtnCloseAlarmoutAll)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgAlarmOutCfg message handlers

BOOL CDlgAlarmOutCfg::OnInitDialog() 
{
    CDialog::OnInitDialog();
    
    InitWnd();

    m_comboAlarmOutIndex.SetCurSel(0);
    OnSelchangeComboAlarmoutIndex();
    
    if (m_struAbility.wSirenNum > 0)
    {
        m_comboSirenIndex.SetCurSel(0);
        OnSelchangeComboSirenIndex();
    }
	SetAlarmOutParamToWnd(m_struAlarmOutParam);
    return TRUE;  // return TRUE unless you set the focus to a control
    // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgAlarmOutCfg::InitWnd()
{
    InitAlarmOutIndex();
    InitAlarmInList();
	//InitEventTriggerList();
    InitSirenAlarmInList();
    InitSirenIndexCombo();
}


void CDlgAlarmOutCfg::InitAlarmOutIndex()
{
    char szLan[128] = {0};
    
    for (int i = 0; i < (m_struAbility.wLocalAlarmOutNum + m_struAbility.wExpandAlarmOutNum); i++)
    {
        sprintf(szLan, "Alarm out %d", i + 1);
        m_comboAlarmOutIndex.AddString(szLan);
    }
}


void CDlgAlarmOutCfg::InitAlarmInList()
{
    char szLan[128] = {0};
    
    m_listAlarmIn.SetExtendedStyle(LVS_EX_CHECKBOXES);
    for (int i = 0; i < (m_struAbility.wLocalAlarmInNum + m_struAbility.wExpandAlarmInNum); i++)
    {
        sprintf(szLan, "Alarm In %d", (i+1));
        m_listAlarmIn.InsertItem(i, szLan);
    }

}

void CDlgAlarmOutCfg::InitSirenIndexCombo()
{
    char szLan[128] = {0};
    for (int i = 0; i <m_struAbility.wSirenNum; i++)
    {
        sprintf(szLan, "Siren %d", (i+1));
        m_comboSirenIndex.AddString(szLan);
    }
}

void CDlgAlarmOutCfg::InitSirenAlarmInList()
{
    char szLan[128] = {0};
    
    m_listSirenAlarmIn.SetExtendedStyle(LVS_EX_CHECKBOXES);
    for (int i = 0; i < (m_struAbility.wLocalAlarmInNum + m_struAbility.wExpandAlarmInNum); i++)
    {
        sprintf(szLan, "Alarm In %d", (i+1));
        m_listSirenAlarmIn.InsertItem(i, szLan);
    }
}


BOOL CDlgAlarmOutCfg::GetAlarmOutParam(NET_DVR_ALARMOUT_PARAM& struAlarmOutParam, LONG lAlarmOutPort)
{
    BOOL bRet = FALSE;
    DWORD dwReturn = 0;
    if (NET_DVR_GetDVRConfig(m_lServerID, NET_DVR_GET_ALARMOUT_PARAM, lAlarmOutPort, &struAlarmOutParam, sizeof(struAlarmOutParam), &dwReturn))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_ALARMOUT_PARAM");
        bRet = TRUE;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_ALARMOUT_PARAM");
        bRet = FALSE;
    }

    return bRet;
}

BOOL CDlgAlarmOutCfg::SetAlarmOutParam(NET_DVR_ALARMOUT_PARAM& struAlarmOutParam, LONG lAlarmOutPort)
{
    BOOL bRet = FALSE;

    if (NET_DVR_SetDVRConfig(m_lServerID, NET_DVR_SET_ALARMOUT_PARAM, lAlarmOutPort, &struAlarmOutParam, sizeof(struAlarmOutParam)))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_SET_ALARMOUT_PARAM");
        bRet = TRUE;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_SET_ALARMOUT_PARAM");
        bRet = FALSE;
    }
    return bRet;
}

BOOL CDlgAlarmOutCfg::SetAlarmOut(LONG lAlarmOutPort, LONG lAlarmOutStatic)
{
    BOOL bRet = FALSE;
    
    if (NET_DVR_SetAlarmHostOut(m_lServerID, lAlarmOutPort, lAlarmOutStatic))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_SetAlarmHostOut");
        bRet = TRUE;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_SetAlarmHostOut");
        bRet = FALSE;
    }
    return bRet;
}

BOOL CDlgAlarmOutCfg::GetSirenParam(NET_DVR_SIREN_PARAM& struSirenParam)
{
	UpdateData(TRUE);
    BOOL bRet = FALSE;
    DWORD dwRetrun = 0;
    LONG lSirenIndex = m_comboSirenIndex.GetCurSel() + 1;
    if (NET_DVR_GetDVRConfig(m_lServerID, NET_DVR_GET_SIREN_PARAM, lSirenIndex, &struSirenParam, sizeof(struSirenParam), &dwRetrun))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_SIREN_PARAM");
        bRet = TRUE;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_SIREN_PARAM");
        bRet = FALSE;
    }
    return bRet;
}

BOOL CDlgAlarmOutCfg::SetSirenParam(NET_DVR_SIREN_PARAM& struSirenParam)
{
    BOOL bRet = FALSE;
    LONG lSirenIndex = m_comboSirenIndex.GetCurSel() + 1;
    if (NET_DVR_SetDVRConfig(m_lServerID, NET_DVR_SET_SIREN_PARAM, lSirenIndex, &struSirenParam, sizeof(struSirenParam)))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_SET_SIREN_PARAM");
        bRet = TRUE;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_SET_SIREN_PARAM");
        bRet = FALSE;
    }
    return bRet;
}

BOOL CDlgAlarmOutCfg::SirenControl(LONG lSirenStatic)
{
    BOOL bRet = FALSE;
    LONG lSirenIndex = m_comboSirenIndex.GetCurSel() + 1;

    if (NET_DVR_AlarmHostAssistantControl(m_lServerID, 4, lSirenIndex, lSirenStatic))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_AlarmHostAssistantControl [%d]", lSirenStatic);
        bRet = TRUE;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_AlarmHostAssistantControl [%d]", lSirenStatic);
        bRet = FALSE;
    }
    return bRet;
}

void CDlgAlarmOutCfg::GetAlarmOutParamFromWnd(NET_DVR_ALARMOUT_PARAM &struAlarmOutParam)
{
    strncpy((char*)struAlarmOutParam.byName, m_csName.GetBuffer(0), sizeof(struAlarmOutParam.byName));
    struAlarmOutParam.wDelay = m_iDelayTime;
    GetAssociateAlarmInParamFromWnd(struAlarmOutParam.byAssociateAlarmIn, ARRAY_SIZE(struAlarmOutParam.byAssociateAlarmIn));
//	GetAlarmoutEventTriggerFromWnd(&struAlarmOutParam.dwEventTriggerAlarmOn, &struAlarmOutParam.dwEventTriggerAlarmOff);
}


void CDlgAlarmOutCfg::SetAlarmOutParamToWnd(NET_DVR_ALARMOUT_PARAM &struAlarmOutParam)
{
    char szLan[40] = {0};
    strncpy(szLan, (char*)struAlarmOutParam.byName, sizeof(struAlarmOutParam.byName));
    m_csName = szLan;
    m_iDelayTime = struAlarmOutParam.wDelay;
    SetAssociateAlarmInParamToWnd(struAlarmOutParam.byAssociateAlarmIn, ARRAY_SIZE(struAlarmOutParam.byAssociateAlarmIn));
}

void CDlgAlarmOutCfg::GetAssociateAlarmInParamFromWnd(BYTE *byAlarmIn, DWORD dwSize)
{
    for (int i = 0; i < m_listAlarmIn.GetItemCount(); i++)
    {
        if (TRUE == m_listAlarmIn.GetCheck(i))
        {
            byAlarmIn[i] = 1;
        }
        else
        {
            byAlarmIn[i] = 0;
        }
    }
}
void CDlgAlarmOutCfg::SetAssociateAlarmInParamToWnd(BYTE *byAlarmIn, DWORD dwSize)
{
    for (int i = 0; i < m_listAlarmIn.GetItemCount(); i++ )
    {
        if (1==  byAlarmIn[i])
        {
            m_listAlarmIn.SetCheck(i, TRUE);
        }
        else
        {
            m_listAlarmIn.SetCheck(i, FALSE);
        }
    }

}

void CDlgAlarmOutCfg::OnBtnSetAlarmoutParam() 
{
    UpdateData(TRUE);
	GetAlarmOutParamFromWnd(m_struAlarmOutParam);
    SetAlarmOutParam(m_struAlarmOutParam, m_comboAlarmOutIndex.GetCurSel());
}

void CDlgAlarmOutCfg::OnSelchangeComboAlarmoutIndex() 
{
    GetAlarmOutParam(m_struAlarmOutParam, m_comboAlarmOutIndex.GetCurSel());
    SetAlarmOutParamToWnd(m_struAlarmOutParam);
    UpdateData(FALSE);
}

void CDlgAlarmOutCfg::OnBtnOpenAlarmout() 
{
    if (!SetAlarmOut(m_comboAlarmOutIndex.GetCurSel(), 1 ))
    {
        AfxMessageBox("Fail to set alarm out");
    }
    	
}

void CDlgAlarmOutCfg::OnBtnCloseAlarmout() 
{
    if (!SetAlarmOut(m_comboAlarmOutIndex.GetCurSel(), 0))
    {
        AfxMessageBox("Succ to set alarm out");
    }	
}

void CDlgAlarmOutCfg::OnBntSetSirenParam() 
{
	UpdateData(TRUE);
    GetSirenParamFromWnd(m_struSirenParam);
    SetSirenParam(m_struSirenParam);
}

void CDlgAlarmOutCfg::OnSelchangeComboSirenIndex() 
{
   	GetSirenParam(m_struSirenParam);
    SetSirenParamToWnd(m_struSirenParam);
    UpdateData(FALSE);
}

void CDlgAlarmOutCfg::GetSirenParamFromWnd(NET_DVR_SIREN_PARAM &struSirenParam)
{
    struSirenParam.wDelay = m_iSirenDelayTime;
    strncpy((char*)struSirenParam.byName, m_csSirenName.GetBuffer(0), sizeof(struSirenParam.byName));
    for (int i = 0; i < m_listSirenAlarmIn.GetItemCount(); i++)
    {
        if (TRUE == m_listSirenAlarmIn.GetCheck(i))
        {
            struSirenParam.byAssociateAlarmIn[i] = 1;
        }
        else
        {
            struSirenParam.byAssociateAlarmIn[i] = 0;
        }
    }
	//GetSirenEventTriggerFromWnd(&struSirenParam.dwEventTriggerAlarmOn, &struSirenParam.dwEventTriggerAlarmOff);
}   

void CDlgAlarmOutCfg::SetSirenParamToWnd(NET_DVR_SIREN_PARAM &struSirenParam)
{
    m_iSirenDelayTime = struSirenParam.wDelay;
    char szLan[40] = {0};
    strncpy(szLan, (char *)struSirenParam.byName, sizeof(struSirenParam.byName));
    m_csSirenName = szLan;
    for (int i = 0; i < m_listSirenAlarmIn.GetItemCount(); i++ )
    {
        if (1==  struSirenParam.byAssociateAlarmIn[i])
        {
            m_listSirenAlarmIn.SetCheck(i, TRUE);
        }
        else
        {
            m_listSirenAlarmIn.SetCheck(i, FALSE);
        }
    }
	UpdateData(FALSE);

}

void CDlgAlarmOutCfg::OnBtnOpenSiren() 
{
    if (!SirenControl(1))
    {
        AfxMessageBox("Fail to set open siren");
    }
}

void CDlgAlarmOutCfg::OnBtnCloseSiren() 
{
    if (!SirenControl(0))
    {
        AfxMessageBox("Fail to set close siren"); 
    }
}

void CDlgAlarmOutCfg::OnRclickListAlarmIn(NMHDR* pNMHDR, LRESULT* pResult) 
{
    CMenu pMenu;
    
    if (!pMenu.LoadMenu(IDR_MENU_SELECT_MODE))
    {
        return;
    }
    CPoint point;
    GetCursorPos(&point);
    pMenu.GetSubMenu(0)->TrackPopupMenu(TPM_LEFTALIGN, point.x, point.y, this);
    *pResult = 0;
}

void CDlgAlarmOutCfg::OnMenuCancelAll() 
{
    for (int i = 0; i < m_listAlarmIn.GetItemCount(); i++)
    {
        m_listAlarmIn.SetCheck(i, FALSE);
    }
}

void CDlgAlarmOutCfg::OnMenuSelectAll() 
{
    for (int i = 0; i < m_listAlarmIn.GetItemCount(); i++)
    {
        m_listAlarmIn.SetCheck(i, TRUE);
    }
}

void CDlgAlarmOutCfg::OnBtnOpenAlarmoutAll() 
{
//    for (int i = 1; i <= m_comboAlarmOutIndex.GetCount(); i++)
    {
        SetAlarmOut(0xffffffff, 1);
    }
}

void CDlgAlarmOutCfg::OnBtnCloseAlarmoutAll() 
{
//    for (int i = 1; i <= m_comboAlarmOutIndex.GetCount(); i++)
    {
        SetAlarmOut(0xffffffff, 0);
    }	
}
