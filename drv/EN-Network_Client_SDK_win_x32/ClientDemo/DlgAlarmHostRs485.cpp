// DlgAlarmHostRs485.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgAlarmHostRs485.h"
#include "DlgAlarmHostTransparent.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgAlarmHostRs485 dialog


CDlgAlarmHostRs485::CDlgAlarmHostRs485(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgAlarmHostRs485::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgAlarmHostRs485)
	m_csName = _T("");
	m_bEnableAirCondition = FALSE;
	m_iTemprature = 0;
	//}}AFX_DATA_INIT
    m_lServerID = -1;
    m_iDevIndex = -1;
    m_lRs485Index = -1;
    m_lDevType = -1;
    memset(&m_struDevAbility, 0, sizeof(m_struDevAbility));
    memset(&m_struRs485Cfg, 0, sizeof(m_struRs485Cfg));
    memset(&m_struDevTypeList, 0, sizeof(m_struDevTypeList));
    memset(&m_struDevProtoList, 0, sizeof(m_struDevProtoList));
}


void CDlgAlarmHostRs485::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgAlarmHostRs485)
	DDX_Control(pDX, IDC_COMBO_AIRCONDITION_RS485_INDEX, m_comboAircondition485Index);
	DDX_Control(pDX, IDC_COMBO_AIRCONDITION_MODE, m_comboAirConditionMode);
	DDX_Control(pDX, IDC_COMBO_WORK_MODE, m_comboWorkMode);
	DDX_Control(pDX, IDC_COMBO_DUPLEX, m_comboDuplex);
	DDX_Control(pDX, IDC_COMBO_485_BAUD, m_comboBaud);
	DDX_Control(pDX, IDC_COMBO_485_CHECK_BIT, m_comboCheckBit);
	DDX_Control(pDX, IDC_COMBO_485_DATA_BIT, m_comboDataBit);
	DDX_Control(pDX, IDC_COMBO_485_STOP_BIT, m_comboStopBit);
	DDX_Control(pDX, IDC_COMBO_DEVICE_PROTO, m_comboDeviceProto);
	DDX_Control(pDX, IDC_COMBO_DEVICE_TYPE, m_comboDeviceType);
	DDX_Control(pDX, IDC_COMBO_FLOW_CONTROL, m_comboFlowControl);
	DDX_Control(pDX, IDC_COMBO_RS485_INDEX, m_comboRs485Index);
	DDX_Text(pDX, IDC_EDIT_NAME, m_csName);
	DDV_MaxChars(pDX, m_csName, 32);
	DDX_Check(pDX, IDC_CHK_EANBLE_AIRCONDITION, m_bEnableAirCondition);
	DDX_Text(pDX, IDC_EDIT_TEMPERATURE, m_iTemprature);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgAlarmHostRs485, CDialog)
	//{{AFX_MSG_MAP(CDlgAlarmHostRs485)
	ON_CBN_SELCHANGE(IDC_COMBO_RS485_INDEX, OnSelchangeComboRs485Index)
	ON_CBN_SELCHANGE(IDC_COMBO_DEVICE_TYPE, OnSelchangeComboDeviceType)
	ON_BN_CLICKED(IDC_BTN_SET_RS485_CFG, OnBtnSetRs485Cfg)
	ON_BN_CLICKED(IDC_BTN_TRANSPARENT, OnBtnTransparent)
	ON_BN_CLICKED(IDC_BTN_SET_AIRCONDITION, OnBtnSetAircondition)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgAlarmHostRs485 message handlers

BOOL CDlgAlarmHostRs485::OnInitDialog() 
{
	CDialog::OnInitDialog();
    GetDeviceTypeList(m_struDevTypeList);

    InitWnd();
    m_comboAirConditionMode.SetCurSel(0);
    m_comboAircondition485Index.SetCurSel(0);
    m_comboRs485Index.SetCurSel(0);
    OnSelchangeComboRs485Index();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgAlarmHostRs485::InitWnd()
{
    Init485IndexCombo();
    InitDeviceTypeCombo();
    InitBaudCombo();
    InitCheckBitCombo();
    InitDataBitCombo();
    InitStopBitCombo();
    InitFlowControlCombo();
    InitDuplexCombo();
    InitWorkMode();
    InitAir485Combo();
}


void CDlgAlarmHostRs485::Init485IndexCombo()
{
    char szLan[128] = {0};
    m_comboRs485Index.ResetContent();
    for (int i = 0; i < (m_struDevAbility.wLocalRs485Num + m_struDevAbility.wExpandRs485Num); i++)
    {
        sprintf(szLan, "Rs485 %d", i+1);
        m_comboRs485Index.AddString(szLan);
    }
}

void CDlgAlarmHostRs485::InitDeviceTypeCombo()
{
    m_comboDeviceType.ResetContent();
    for (int i = 0; i <m_struDevTypeList.dwTypeNum; i++)
    {
        m_comboDeviceType.InsertString(i, (char*)m_struDevTypeList.struDeviceType[i].byDescribe);
        m_comboDeviceType.SetItemData(i, m_struDevTypeList.struDeviceType[i].dwType);
    }
}

void CDlgAlarmHostRs485::InitDeviceProtoCombo()
{
    m_comboDeviceProto.ResetContent();
    for (int i = 0; i < m_struDevProtoList.dwProtoNum; i++)
    {
        m_comboDeviceProto.InsertString(i, (char*)m_struDevProtoList.struProtoType[i].byDescribe);
        m_comboDeviceProto.SetItemData(i, m_struDevProtoList.struProtoType[i].dwType);
    }
}

void CDlgAlarmHostRs485::InitBaudCombo()
{
    int nIndex = 0;
    m_comboBaud.ResetContent();

    m_comboBaud.InsertString(nIndex, "50");
    m_comboBaud.SetItemData(nIndex, 0);
    nIndex++;
    m_comboBaud.InsertString(nIndex, "75");
    m_comboBaud.SetItemData(nIndex, 1);
    nIndex++;
    m_comboBaud.InsertString(nIndex, "110");
    m_comboBaud.SetItemData(nIndex, 2);
    nIndex++;
    m_comboBaud.InsertString(nIndex, "150");
    m_comboBaud.SetItemData(nIndex, 3);
    nIndex++;
    m_comboBaud.InsertString(nIndex, "300");
    m_comboBaud.SetItemData(nIndex, 4);
    nIndex++;
    m_comboBaud.InsertString(nIndex, "600");
    m_comboBaud.SetItemData(nIndex, 5);
    nIndex++;
    m_comboBaud.InsertString(nIndex, "1200");
    m_comboBaud.SetItemData(nIndex, 6);
    nIndex++;
    m_comboBaud.InsertString(nIndex, "2400");
    m_comboBaud.SetItemData(nIndex, 7);
    nIndex++;
    m_comboBaud.InsertString(nIndex, "4800");
    m_comboBaud.SetItemData(nIndex, 8);
    nIndex++;
    m_comboBaud.InsertString(nIndex, "9600");
    m_comboBaud.SetItemData(nIndex, 9);
    nIndex++;
    m_comboBaud.InsertString(nIndex, "19200");
    m_comboBaud.SetItemData(nIndex, 10);
    nIndex++;
    m_comboBaud.InsertString(nIndex, "38400");
    m_comboBaud.SetItemData(nIndex, 11);
    nIndex++;
    m_comboBaud.InsertString(nIndex, "57600");
    m_comboBaud.SetItemData(nIndex, 12);
    nIndex++;
    m_comboBaud.InsertString(nIndex, "76800");
    m_comboBaud.SetItemData(nIndex, 13);
    nIndex++;
    m_comboBaud.SetItemData(nIndex, 14);
    nIndex++;
}

void CDlgAlarmHostRs485::InitCheckBitCombo()
{
//     BYTE    byParity;               //�Ƿ�У�飺0-��У�飬1-��У�飬2-żУ�� 
    // No parity, 1 - odd parity, 2 - even parity
    int nIndex = 0;
    m_comboCheckBit.ResetContent();
    m_comboCheckBit.InsertString(nIndex, "No parity");
    m_comboCheckBit.SetItemData(nIndex, 0);
    nIndex++;
    m_comboCheckBit.InsertString(nIndex, "odd parity");
    m_comboCheckBit.SetItemData(nIndex, 1);
    nIndex++;
    m_comboCheckBit.InsertString(nIndex, "even parity");
    m_comboCheckBit.SetItemData(nIndex, 2);
    nIndex++;
}

void CDlgAlarmHostRs485::InitDataBitCombo()
{
    //     BYTE    byDataBit;              // �����м�λ��0-5λ��1-6λ��2-7λ��3-8λ 
    int nIndex = 0;
    m_comboDataBit.ResetContent();
    m_comboDataBit.InsertString(nIndex, "5bit");
    m_comboDataBit.SetItemData(nIndex, 0);
    nIndex++;
    m_comboDataBit.InsertString(nIndex, "6bit");
    m_comboDataBit.SetItemData(nIndex, 1);
    nIndex++;
    m_comboDataBit.InsertString(nIndex, "7bit");
    m_comboDataBit.SetItemData(nIndex, 2);
    nIndex++;
    m_comboDataBit.InsertString(nIndex, "8bit");
    m_comboDataBit.SetItemData(nIndex, 3);
    nIndex++;

}

void CDlgAlarmHostRs485::InitStopBitCombo()
{
    int nIndex = 0;
    m_comboStopBit.ResetContent();
    m_comboStopBit.InsertString(nIndex, "1bit");
    m_comboStopBit.SetItemData(nIndex, 0);
    nIndex++;
    m_comboStopBit.InsertString(nIndex, "2bit");
    m_comboStopBit.SetItemData(nIndex, 1);
    nIndex++;
}

void CDlgAlarmHostRs485::InitFlowControlCombo()
{
    int nIndex = 0;
    m_comboFlowControl.ResetContent();
    m_comboFlowControl.InsertString(nIndex, "No");
    m_comboFlowControl.SetItemData(nIndex, 0);
    nIndex++;
    m_comboFlowControl.InsertString(nIndex, "Soft");
    m_comboFlowControl.SetItemData(nIndex, 1);
    nIndex++;    
    m_comboFlowControl.InsertString(nIndex, "Hard");
    m_comboFlowControl.SetItemData(nIndex, 2);
    nIndex++;
}
void CDlgAlarmHostRs485::InitDuplexCombo()
{
    m_comboDuplex.ResetContent();
    m_comboDuplex.AddString("Half duplex");
    m_comboDuplex.AddString("Full duplex");
}

void CDlgAlarmHostRs485::InitWorkMode()
{
	char szLan[128] = {0};
    m_comboWorkMode.ResetContent();
	g_StringLanType(szLan, "����̨","Console");
    m_comboWorkMode.AddString(szLan);
	g_StringLanType(szLan, "͸��ͨ��", "Transparent channel");
    m_comboWorkMode.AddString(szLan);
}

void CDlgAlarmHostRs485::InitAir485Combo()
{
    char szLan[128] = {0};
    m_comboAircondition485Index.ResetContent();
    for (int i = 0; i < (m_struDevAbility.wLocalRs485Num + m_struDevAbility.wExpandRs485Num); i++)
    {
        sprintf(szLan, "Rs485 %d", i+1);
        m_comboAircondition485Index.AddString(szLan);
    }
}

void CDlgAlarmHostRs485::InitAirconditionModeCombo()
{
    char szLan[128] = {0};
    m_comboAirConditionMode.ResetContent();
    g_StringLanType(szLan, "����", "Refrigeration");
    m_comboAirConditionMode.AddString(szLan);
    g_StringLanType(szLan, "����", "Heating");
    m_comboAirConditionMode.AddString(szLan);
    g_StringLanType(szLan, "��ʪ", "Dehumidifier");
    m_comboAirConditionMode.AddString(szLan);
    g_StringLanType(szLan, "�Զ�", "Auto");
    m_comboAirConditionMode.AddString(szLan);
}

BOOL CDlgAlarmHostRs485::GetRs485Cfg(NET_DVR_ALARM_RS485CFG &struRs485Cfg)
{
    DWORD dwReturn = 0;
    if (NET_DVR_GetDVRConfig(m_lServerID, NET_DVR_GET_ALARM_RS485CFG, m_lRs485Index, &struRs485Cfg, sizeof(struRs485Cfg), &dwReturn))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_ALARM_RS485CFG");
        return TRUE;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_ALARM_RS485CFG");
        return FALSE;
    }
}
BOOL CDlgAlarmHostRs485::SetRs485Cfg(NET_DVR_ALARM_RS485CFG &struRs485Cfg)
{
    if (NET_DVR_SetDVRConfig(m_lServerID, NET_DVR_SET_ALARM_RS485CFG, m_lRs485Index, &struRs485Cfg, sizeof(struRs485Cfg)))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVE_SET_ALARM_RS485CFG");
        return TRUE;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVE_SET_ALARM_RS485CFG");
        return FALSE;
    }
}

BOOL CDlgAlarmHostRs485::GetDeviceTypeList(NET_DVR_DEVICE_TYPE_LIST& struDevTypeList)
{
    if (NET_DVR_GetDeviceTypeList(m_lServerID, &struDevTypeList))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GetDeviceTypeList");
        return TRUE;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GetDeviceTypeList");
        return FALSE;
    }
}

BOOL CDlgAlarmHostRs485::GetDeviceProtoList(NET_DVR_DEVICE_PROTO_LIST& struDevProtoList)
{
    if (NET_DVR_GetDeviceProtoList(m_lServerID, m_lDevType, &struDevProtoList))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GetDeviceProtoList");
        return TRUE;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GetDeviceProtoList");
        return FALSE;
    }
}

void CDlgAlarmHostRs485::GetRs485CfgFromWnd(NET_DVR_ALARM_RS485CFG &struRs485Cfg)
{
    strncpy((char*)struRs485Cfg.sDeviceName, m_csName.GetBuffer(0), sizeof(struRs485Cfg.sDeviceName));
    struRs485Cfg.wDeviceType = m_comboDeviceType.GetItemData(m_comboDeviceType.GetCurSel());
    struRs485Cfg.wDeviceProtocol = m_comboDeviceProto.GetItemData(m_comboDeviceProto.GetCurSel());
    struRs485Cfg.dwBaudRate = m_comboBaud.GetItemData(m_comboBaud.GetCurSel());
    struRs485Cfg.byDataBit = m_comboDataBit.GetItemData(m_comboDataBit.GetCurSel());
    struRs485Cfg.byStopBit = m_comboStopBit.GetItemData(m_comboStopBit.GetCurSel());
    struRs485Cfg.byParity = m_comboCheckBit.GetItemData(m_comboCheckBit.GetCurSel());
    struRs485Cfg.byFlowcontrol = m_comboFlowControl.GetItemData(m_comboFlowControl.GetCurSel());
    struRs485Cfg.byDuplex = m_comboDuplex.GetCurSel();
    struRs485Cfg.byWorkMode = m_comboWorkMode.GetCurSel();
}
void CDlgAlarmHostRs485::SetRs485CfgToWnd(NET_DVR_ALARM_RS485CFG &struRs485Cfg)
{
    int nIndex = 0;
    char szLan[40] = {0};
    strncpy(szLan, (char *)struRs485Cfg.sDeviceName, sizeof(struRs485Cfg.sDeviceName));
    m_csName = szLan;
    for (nIndex = 0; nIndex < m_comboDeviceType.GetCount(); nIndex++)
    {
        if (m_comboDeviceType.GetItemData(nIndex) == struRs485Cfg.wDeviceType)
        {
            m_comboDeviceType.SetCurSel(nIndex);
            OnSelchangeComboDeviceType();
            break;
        }
    }
    for (nIndex = 0; nIndex < m_comboDeviceProto.GetCount(); nIndex++)
    {
        if (m_comboDeviceProto.GetItemData(nIndex) == struRs485Cfg.wDeviceProtocol)
        {
            m_comboDeviceProto.SetCurSel(nIndex);
            break;
        }
    }
    m_comboBaud.SetCurSel(struRs485Cfg.dwBaudRate);
    m_comboDataBit.SetCurSel(struRs485Cfg.byDataBit);
    m_comboStopBit.SetCurSel(struRs485Cfg.byStopBit);
    m_comboCheckBit.SetCurSel(struRs485Cfg.byParity);
    m_comboFlowControl.SetCurSel(struRs485Cfg.byFlowcontrol);
    m_comboDuplex.SetCurSel(struRs485Cfg.byDuplex);
    m_comboWorkMode.SetCurSel(struRs485Cfg.byWorkMode);    
}

void CDlgAlarmHostRs485::OnSelchangeComboRs485Index() 
{
    m_lRs485Index = m_comboRs485Index.GetCurSel() + 1;

    if (m_lRs485Index == 1)
    {
        m_comboDuplex.EnableWindow(TRUE);
    }
    else
    {
        m_comboDuplex.EnableWindow(FALSE);
    }
    if (!GetRs485Cfg(m_struRs485Cfg))
    {
        AfxMessageBox("Fail to get rs485 config");
        return;
    }
    
    SetRs485CfgToWnd(m_struRs485Cfg);
    UpdateData(FALSE);
}

void CDlgAlarmHostRs485::OnSelchangeComboDeviceType() 
{
    m_lDevType = m_comboDeviceType.GetItemData(m_comboDeviceType.GetCurSel());
    
    GetDeviceProtoList(m_struDevProtoList);
    InitDeviceProtoCombo();
}

void CDlgAlarmHostRs485::OnBtnSetRs485Cfg() 
{
    UpdateData(TRUE);
    GetRs485CfgFromWnd(m_struRs485Cfg);
    if (SetRs485Cfg(m_struRs485Cfg))
    {
        AfxMessageBox("Succ to set rs485 config");
    }
}

void CDlgAlarmHostRs485::OnBtnTransparent() 
{
	CDlgAlarmHostTransparent dlg;
    dlg.m_lServerID = m_lServerID;
    memcpy(&dlg.m_struDevAbility, &m_struDevAbility, sizeof(m_struDevAbility));
    dlg.m_iDevIndex = m_iDevIndex;
    dlg.DoModal();
}

void CDlgAlarmHostRs485::OnBtnSetAircondition() 
{
	NET_DVR_AIR_CONDITION_PARAM struAirCondition;
    memset(&struAirCondition, 0, sizeof(struAirCondition));

    UpdateData(TRUE);
    struAirCondition.dwSize = sizeof(struAirCondition);
    struAirCondition.byEnable = m_bEnableAirCondition;
    struAirCondition.byMode = m_comboAirConditionMode.GetCurSel();
    struAirCondition.byTemperature = (BYTE)m_iTemprature;

	if (!SetAirCondition(struAirCondition))
	{
        AfxMessageBox("Fail to control aircondition");
	}
}


BOOL CDlgAlarmHostRs485::SetAirCondition(NET_DVR_AIR_CONDITION_PARAM &struAirCondition)
{
    BOOL bRet = FALSE;
    if (NET_DVR_SetAirCondition(m_lServerID, m_comboAircondition485Index.GetCurSel()+1, &struAirCondition))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_SetAirCondition");
        bRet = TRUE;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_SetAirCondition");
        bRet = FALSE;
    }
    return bRet;
}
