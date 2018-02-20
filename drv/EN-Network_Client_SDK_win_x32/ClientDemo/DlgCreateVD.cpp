// DlgCreateVD.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgCreateVD.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgCreateVD dialog


CDlgCreateVD::CDlgCreateVD(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgCreateVD::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgCreateVD)
	m_csVDName = _T("");
	m_csArrayName = _T("");
	m_nVDCapacity = 0;
	//}}AFX_DATA_INIT
    m_lServerID = -1;
    m_iDevIndex = -1;
    memset(&m_struArraySpaceAlloc, 0, sizeof(m_struArraySpaceAlloc));
    memset(&m_struArrayInfo, 0, sizeof(m_struArrayInfo));
}


void CDlgCreateVD::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgCreateVD)
	DDX_Control(pDX, IDC_COMBO_INIT_TYPE, m_comboInitType);
	DDX_Control(pDX, IDC_COMBO_VD_SLOT, m_comboVDSlot);
	DDX_Text(pDX, IDC_EDIT_VD_NAME, m_csVDName);
	DDX_Text(pDX, IDC_STATIC_ARRAY_NAME, m_csArrayName);
	DDX_Text(pDX, IDC_EDIT_VD_CAPACITY, m_nVDCapacity);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgCreateVD, CDialog)
	//{{AFX_MSG_MAP(CDlgCreateVD)
	ON_BN_CLICKED(IDC_BTN_CRATE_ARRAY, OnBtnCrateArray)
	ON_CBN_SELCHANGE(IDC_COMBO_VD_SLOT, OnSelchangeComboVdSlot)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgCreateVD message handlers

void CDlgCreateVD::OnBtnCrateArray() 
{
    UpdateData(TRUE);

    strncpy((char*)m_struOpeateVD.byName, m_csVDName.GetBuffer(0), sizeof(m_struOpeateVD.byName));
	CString strSlotNum;
	m_comboVDSlot.GetWindowText(strSlotNum);
    m_struOpeateVD.bySlot = atoi(strSlotNum);
    m_struOpeateVD.wArrayID = m_struArrayInfo.wArrayID;
    unsigned __int64 dwCapacity =  ((unsigned __int64)m_nVDCapacity) * 1024 *1024;

    m_struOpeateVD.dwLCapacity = *((DWORD*)&dwCapacity);
    m_struOpeateVD.dwHCapacity = *((DWORD*)((char*)&dwCapacity + 4));
    m_struOpeateVD.byInitType = m_comboInitType.GetCurSel();
    if (!CreateVD())
    {
        AfxMessageBox("Fail to create VD");
    }
    else
    {
        if (!GetArraySpaceAlloc(m_struArrayInfo.wArrayID))
        {
            MessageBox("Fail to GetArraySpaceAlloc");
            return;
        }
        
        InitWnd();
    }
    
}

BOOL CDlgCreateVD::GetArraySpaceAlloc(DWORD dwArraySlot)
{
    
    if (!NET_DVR_GetArraySpaceAlloc(m_lServerID, dwArraySlot, &m_struArraySpaceAlloc))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GetArraySpaceAlloc");
        return FALSE;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GetArraySpaceAlloc");
        return TRUE;
    }
}

BOOL CDlgCreateVD::CreateVD()
{
    if (!NET_DVR_CreateVD(m_lServerID, &m_struOpeateVD))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_CreateVD");
        return FALSE;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_CreateVD");
        return TRUE;
    }
}

BOOL CDlgCreateVD::OnInitDialog() 
{
	CDialog::OnInitDialog();

    m_csArrayName = m_struArrayInfo.byArrayName;
    UpdateData(FALSE);

    if (!GetArraySpaceAlloc(m_struArrayInfo.wArrayID))
    {
        MessageBox("Fail to GetArraySpaceAlloc");
        return FALSE;
    }

    InitWnd();

    m_comboVDSlot.SetCurSel(0);
    OnSelchangeComboVdSlot();
    
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgCreateVD::InitWnd()
{
    char szLan[128] = {0};
    m_comboVDSlot.ResetContent();
    for (int i = 0; i < m_struArraySpaceAlloc.byVDSlotCount; i++)
    {
        sprintf(szLan, "%d", m_struArraySpaceAlloc.struVDSlots[i].wVDSlot);
        m_comboVDSlot.AddString(szLan);
    }

    m_comboInitType.ResetContent();
    g_StringLanType(szLan, "快速初始化", "Quick Format");
    m_comboInitType.AddString(szLan);
    g_StringLanType(szLan, "前台完全初始化", "Front full format");
    m_comboInitType.AddString(szLan); 
    g_StringLanType(szLan, "后台完全初始化", "Back full format");
    m_comboInitType.AddString(szLan);
    m_comboInitType.SetCurSel(0);

}

void CDlgCreateVD::OnSelchangeComboVdSlot() 
{
    char szLan[128] = {0};
    int nSlotIndex = m_comboVDSlot.GetCurSel();

    unsigned __int64 dwCapacity = 0;
    	
    *((DWORD*)&dwCapacity) = m_struArraySpaceAlloc.struVDSlots[nSlotIndex].dwLVDSlotSize;
    *((DWORD*)((char*)&dwCapacity + 4))  = m_struArraySpaceAlloc.struVDSlots[nSlotIndex].dwHVDSlotSize;
    dwCapacity >>= 20;

    if (m_struArraySpaceAlloc.struVDSlots[nSlotIndex].byAlloc)
    {
        sprintf(szLan, "have Alloced: VD = %d spcace = %I64u Gb", m_struArraySpaceAlloc.struVDSlots[nSlotIndex].wVDSlot,
            dwCapacity);
    }
    else
    {
        sprintf(szLan, "haven't Alloced: spcace = %I64u Gb", dwCapacity);
    }
    GetDlgItem(IDC_STATIC_SLOT_INFO)->SetWindowText(szLan);
}
