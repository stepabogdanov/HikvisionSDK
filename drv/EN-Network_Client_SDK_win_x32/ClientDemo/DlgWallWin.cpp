// DlgWallWin.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgWallWin.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgWallWin dialog


CDlgWallWin::CDlgWallWin(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgWallWin::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgWallWin)
	m_bEnable = FALSE;
	m_dwLayer = 0;
	m_wH = 0;
	m_wW = 0;
	m_wX = 0;
	m_wY = 0;
	m_byTransparency = 0;
	m_byWinMode = 0;
	m_bTransparency = FALSE;
	//}}AFX_DATA_INIT
}


void CDlgWallWin::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgWallWin)
	DDX_Control(pDX, IDC_LIST_WINCFG, m_listWinCfg);
	DDX_Check(pDX, IDC_CHK_ENABLE, m_bEnable);
	DDX_Text(pDX, IDC_EDIT_LAYER, m_dwLayer);
	DDX_Text(pDX, IDC_EDIT_WIN_H, m_wH);
	DDX_Text(pDX, IDC_EDIT_WIN_W, m_wW);
	DDX_Text(pDX, IDC_EDIT_X, m_wX);
	DDX_Text(pDX, IDC_EDIT_Y, m_wY);
	DDX_Text(pDX, IDC_EDIT_TRANSPARENCY, m_byTransparency);
	DDV_MinMaxByte(pDX, m_byTransparency, 0, 100);
	DDX_Text(pDX, IDC_EDIT_WINMODE, m_byWinMode);
	DDX_Check(pDX, IDC_CHECK_TRANSPARENCY, m_bTransparency);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgWallWin, CDialog)
	//{{AFX_MSG_MAP(CDlgWallWin)
	ON_NOTIFY(NM_CLICK, IDC_LIST_WINCFG, OnClickListWincfg)
	ON_BN_CLICKED(IDC_BTN_SAVE, OnBtnSave)
	ON_BN_CLICKED(IDC_BTN_SET, OnBtnSet)
	ON_BN_CLICKED(IDC_BTN_GET, OnBtnGet)
	ON_BN_CLICKED(IDC_BTN_EXIT, OnBtnExit)
	ON_BN_CLICKED(IDC_BTN_SET_PRO, OnBtnSetPro)
	ON_BN_CLICKED(IDC_BTN_GET_PRO, OnBtnGetPro)
	ON_BN_CLICKED(IDC_BTN_GET_ALL, OnBtnGetAll)
	ON_BN_CLICKED(IDC_BTN_SET_WALL_CFG, OnBtnSetWallCfg)
	ON_BN_CLICKED(IDC_BTN_GET_WALL_CFG, OnBtnGetWallCfg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgWallWin message handlers

BOOL CDlgWallWin::OnInitDialog() 
{
	CDialog::OnInitDialog();
	CString cs;
	m_iCurSel = -1;
	m_iDeviceIndex = g_pMainDlg->GetCurDeviceIndex();
	m_dwWinCount = 0;
	memset(m_dwStatus, 0, sizeof(m_dwStatus));
	memset(m_struList, 0, sizeof(m_struList));
	memset(m_struSet, 0, sizeof(m_struSet)); 
	memset(m_dwWinNum, 0xff, sizeof(m_dwWinNum));
	memset(m_dwWinNumSet, 0xff, sizeof(m_dwWinNumSet));
	memset(&m_struWallWinParam, 0, sizeof(m_struWallWinParam));
	memset(&m_struWallCfg, 0, sizeof(m_struWallCfg));

	m_listWinCfg.SetExtendedStyle(m_listWinCfg.GetExtendedStyle()|LVS_EX_FULLROWSELECT);
	m_listWinCfg.InsertColumn(0, "窗口号",LVCFMT_LEFT,80,-1);
	m_listWinCfg.InsertColumn(1, "X",LVCFMT_LEFT,80,-1);
    m_listWinCfg.InsertColumn(2, "Y",LVCFMT_LEFT,80,-1);
	m_listWinCfg.InsertColumn(3, "宽",LVCFMT_LEFT,80,-1);
	m_listWinCfg.InsertColumn(4, "高",LVCFMT_LEFT,80,-1);
	m_listWinCfg.InsertColumn(5, "图层号",LVCFMT_LEFT,80,-1);
	m_listWinCfg.InsertColumn(6, "使能",LVCFMT_LEFT,80,-1);

	int i = 0;	
	for (i = 0; i < 16; i++)
	{
		m_dwWinNum[i] = i + 1;
	}
	
	OnBtnGetAll();
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgWallWin::OnClickListWincfg(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	POSITION  iPos = m_listWinCfg.GetFirstSelectedItemPosition();
	if (iPos == NULL)
	{
		return;
 	}
    m_iCurSel = m_listWinCfg.GetNextSelectedItem(iPos);
	m_bEnable = m_struList[m_iCurSel].byEnable;
	m_wX = m_struList[m_iCurSel].struWinPosition.wXCoordinate;
	m_wY = m_struList[m_iCurSel].struWinPosition.wYCoordinate;
	m_wW = m_struList[m_iCurSel].struWinPosition.wWidth;
	m_wH = m_struList[m_iCurSel].struWinPosition.wHeight;
	m_dwLayer = m_struList[m_iCurSel].dwLayerIndex;
    UpdateData(FALSE);
	*pResult = 0;
}

void CDlgWallWin::OnBtnSave() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	CString cs;
    if (m_iCurSel == -1)
    {
		AfxMessageBox("未选中条目");
		return;
    }
	int i = 0;
	for (i = 0; i < m_dwWinCount; i++)
	{
		if (m_dwWinNumSet[i] == m_listWinCfg.GetItemData(m_iCurSel))
		{
			break;
		}
		if (m_dwWinNumSet[i] == 0xffffffff)
		{
			m_dwWinNumSet[i] = m_listWinCfg.GetItemData(m_iCurSel);
			m_dwSetCount++;
			break;
		}
	}
	
	m_struSet[i].dwSize = sizeof(NET_DVR_WALLWINCFG);
	m_struSet[i].byEnable = m_bEnable;
	m_struSet[i].dwWinNum = m_dwWinNumSet[i];
	m_struSet[i].dwLayerIndex = m_dwLayer;
	m_struSet[i].struWinPosition.wXCoordinate = m_wX;
	m_struSet[i].struWinPosition.wYCoordinate = m_wY;
	m_struSet[i].struWinPosition.wWidth = m_wW;
	m_struSet[i].struWinPosition.wHeight = m_wH;
	
	cs.Format("%d", m_struSet[i].struWinPosition.wXCoordinate);
	m_listWinCfg.SetItemText(m_iCurSel, 1, cs);
	cs.Format("%d", m_struSet[i].struWinPosition.wYCoordinate);
	m_listWinCfg.SetItemText(m_iCurSel, 2, cs);
	cs.Format("%d", m_struSet[i].struWinPosition.wWidth);
	m_listWinCfg.SetItemText(m_iCurSel, 3, cs);
	cs.Format("%d", m_struSet[i].struWinPosition.wHeight);
	m_listWinCfg.SetItemText(m_iCurSel, 4, cs);
	cs.Format("%d", m_struSet[i].dwLayerIndex);
	m_listWinCfg.SetItemText(m_iCurSel, 5, cs);
	if (m_struSet[i].byEnable == 0)
	{
		cs.Format("Disable");
	}
	else
	{
		cs.Format("Enable");
	}
	m_listWinCfg.SetItemText(m_iCurSel, 6, cs);

}

void CDlgWallWin::DrawList()
{
	int i = 0;
	CString cs;
    for(i = 0; i < m_dwWinCount; i++)
	{
		
		cs.Format("%d",  m_dwWinNum[i]);
		m_listWinCfg.InsertItem(i, cs, 0);		
		cs.Format("%d", m_struList[i].struWinPosition.wXCoordinate);
		m_listWinCfg.SetItemText(i, 1, cs);
		cs.Format("%d", m_struList[i].struWinPosition.wYCoordinate);
		m_listWinCfg.SetItemText(i, 2, cs);
		cs.Format("%d", m_struList[i].struWinPosition.wWidth);
		m_listWinCfg.SetItemText(i, 3, cs);
		cs.Format("%d", m_struList[i].struWinPosition.wHeight);
		m_listWinCfg.SetItemText(i, 4, cs);
		cs.Format("%d", m_struList[i].dwLayerIndex);
		m_listWinCfg.SetItemText(i, 5, cs);
		if (m_struList[i].byEnable == 0)
		{
			cs.Format("Disable");
		}
		else
		{
			cs.Format("Enable");
		}
		m_listWinCfg.SetItemText(i, 6, cs);
		m_listWinCfg.SetItemData(i, m_dwWinNum[i]);
	}
}

void CDlgWallWin::OnBtnSet() 
{
	// TODO: Add your control notification handler code here
	memset(m_dwStatus, 0, sizeof(m_dwStatus));
	int i = 0;
	int j = 0;
	char cs[128] = {0};
	if (m_dwSetCount == 0)
	{
		if (!NET_DVR_SetDeviceConfig(m_lUserID, NET_DVR_WALLWIN_SET, m_dwWinCount, m_dwWinNum, m_dwWinCount*4, m_dwStatus, m_struList, m_dwWinCount * sizeof(NET_DVR_WALLWINCFG)))
		{
			AfxMessageBox("设置失败");
			g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_WALLWIN_SET");
			return;
		}
		else
		{
			sprintf(cs, "Fail winnum:\n");
			for(i = 0; i < m_dwWinCount; i++)
			{
				if (m_dwStatus[i] > 0)
				{
					sprintf(cs, "%s %d\n", cs, m_dwWinNum[i]);
					j++;
				}
			}
			if (j > 0)
			{
				AfxMessageBox(cs);
			}
			else
			{
				g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_WALLWIN_SET");
			}
		}
	}
	else
	{
		if (!NET_DVR_SetDeviceConfig(m_lUserID, NET_DVR_WALLWIN_SET, m_dwSetCount, m_dwWinNumSet, 4*m_dwSetCount, m_dwStatus, m_struSet, m_dwSetCount*sizeof(NET_DVR_WALLWINCFG)))
		{
			AfxMessageBox("设置失败");
			g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_WALLWIN_SET");
			return;
		}
		else
		{
			sprintf(cs, "Fail winnum:\n");
			for(i = 0; i < m_dwSetCount; i++)
			{
				if (m_dwStatus[i] > 0)
				{
					sprintf(cs, "%s %d\n", cs, m_dwWinNumSet[i]);
					j++;
				}
			}
			if (j > 0)
			{
				AfxMessageBox(cs);				
			}
			else
			{
				g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_WALLWIN_SET");				
			}
			m_dwSetCount = 0;
			memset(m_dwWinNumSet, 0xff, sizeof(m_dwWinNumSet));
			memset(m_struSet, 0, sizeof(m_struSet));
		}
	}
}

void CDlgWallWin::OnBtnGet() 
{
	// TODO: Add your control notification handler code here
	int i,j = 0;
	CString cs;
	memset(m_struList, 0, sizeof(m_struList));
	if (!NET_DVR_GetDeviceConfig(m_lUserID, NET_DVR_WALLWIN_GET, m_dwWinCount, m_dwWinNum, 4*m_dwWinCount, m_dwStatus, m_struList, m_dwWinCount*sizeof(NET_DVR_WALLWINCFG)))
	{
		AfxMessageBox("获取窗口信息失败");
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_WALLWIN_GET");
		//return FALSE;
	}
	cs.Format("Fail winnum:\n");
	for(i = 0; i < m_dwWinCount; i++)
	{
		if (m_dwStatus[i] > 0)
		{
			cs.Format("%s %d\n", cs, m_dwWinNum[i]);
			j++;
		}
	}
    if (j > 0)
    {
		AfxMessageBox(cs);
    }
	m_listWinCfg.DeleteAllItems();
    DrawList();

	m_dwSetCount = 0;
	memset(m_dwWinNumSet, 0xff, sizeof(m_dwWinNumSet));
	memset(m_struSet, 0, sizeof(m_struSet));
	UpdateData(FALSE);
}

void CDlgWallWin::OnBtnExit() 
{
	// TODO: Add your control notification handler code here
	CDialog::OnCancel();
}

void CDlgWallWin::OnBtnSetPro() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	if (m_iCurSel == -1)
	{
		AfxMessageBox("未选中窗口号");
		return;
	}
	m_struWallWinParam.dwSize = sizeof(NET_DVR_WALLWINPARAM);
	m_struWallWinParam.byTransparency = (BYTE)m_bTransparency;
	m_struWallWinParam.byWinMode = m_byWinMode;
	if (!NET_DVR_SetDVRConfig(m_lUserID, NET_DVR_WALLWINPARAM_SET, m_listWinCfg.GetItemData(m_iCurSel), &m_struWallWinParam, sizeof(m_struWallWinParam)))
	{
		AfxMessageBox("设置失败");
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_WALLWINPARAM_SET");
	}
	else
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_WALLWINPARAM_SET");
	}

}

void CDlgWallWin::OnBtnGetPro() 
{
	// TODO: Add your control notification handler code here
	if (m_iCurSel == -1)
	{
		AfxMessageBox("未选中窗口号");
		return;
	}
	DWORD dwReturned = 0;
	if (!NET_DVR_GetDVRConfig(m_lUserID, NET_DVR_WALLWINPARAM_GET, m_listWinCfg.GetItemData(m_iCurSel), &m_struWallWinParam, sizeof(m_struWallWinParam), &dwReturned))
	{
		AfxMessageBox("获取失败");
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_WALLWINPARAM_GET");
		return;
	}
	else
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_WALLWINPARAM_GET");
		m_bTransparency = m_struWallWinParam.byTransparency;
		m_byWinMode = m_struWallWinParam.byWinMode;
		UpdateData(FALSE);
	}
}

void CDlgWallWin::OnBtnGetAll() 
{
	// TODO: Add your control notification handler code here
	int i,j = 0;
	CString cs;
	//memset(m_struList, 0, sizeof(m_struList));

    char *pTemp = new char[4 + MAX_WALL_WIN_COUNT *sizeof(NET_DVR_WALLWINCFG)];
	memset(pTemp, 0, 4 + MAX_WALL_WIN_COUNT *sizeof(NET_DVR_WALLWINCFG));
	if (!NET_DVR_GetDeviceConfig(m_lUserID, NET_DVR_WALLWIN_GET, 0xffffffff, NULL, 0, NULL, pTemp, 4 + MAX_WALL_WIN_COUNT * sizeof(NET_DVR_WALLWINCFG)))
	{
		AfxMessageBox("获取窗口信息失败");
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_WALLWIN_GET");
		//return FALSE;
	}
// 	cs.Format("Fail winnum:\n");
// 	for(i = 0; i < 16; i++)
// 	{
// 		if (m_dwStatus[i] > 0)
// 		{
// 			cs.Format("%s %d\n", cs, m_dwWinNum[i]);
// 			j++;
// 		}
// 	}
//     if (j > 0)
//     {
// 		AfxMessageBox(cs);
//     }

	else
	{
		m_dwWinCount = *((DWORD*)pTemp);
		memcpy(m_struList, pTemp + 4, m_dwWinCount * sizeof(NET_DVR_WALLWINCFG));
		for (i = 0; i < m_dwWinCount; i++)
		{
			m_dwWinNum[i] = m_struList[i].dwWinNum;
		}
		m_listWinCfg.DeleteAllItems();
        
		m_dwSetCount = 0;
		memset(m_dwWinNumSet, 0xff, sizeof(m_dwWinNumSet));
	    memset(m_struSet, 0, sizeof(m_struSet));

	}	
	
	delete []pTemp;
	pTemp = NULL;
	DrawList();
	UpdateData(FALSE);
}

void CDlgWallWin::OnBtnSetWallCfg() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	char szLan[128] = {0};
	m_struWallCfg.dwSize = sizeof(NET_DVR_WALL_CFG);
	m_struWallCfg.byTransparency = m_byTransparency;
	
	if (!NET_DVR_SetDVRConfig(m_lUserID, NET_DVR_SET_WALL_CFG, 0, &m_struWallCfg, sizeof(NET_DVR_WALL_CFG)))
	{
		g_StringLanType(szLan, "设置失败", "Set fail");
		AfxMessageBox(szLan);
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_WALL_CFG");
	}
	else
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_SET_WALL_CFG");
	}
}

void CDlgWallWin::OnBtnGetWallCfg() 
{
	// TODO: Add your control notification handler code here
	char szLan[128] = {0};
	DWORD dwReturned = 0;
	
	if (!NET_DVR_GetDVRConfig(m_lUserID, NET_DVR_GET_WALL_CFG, 0, &m_struWallCfg, sizeof(NET_DVR_WALL_CFG), &dwReturned))
	{
		g_StringLanType(szLan, "获取失败", "Get fail");
		AfxMessageBox(szLan);
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_WALL_CFG");
	}
	else
	{
		m_byTransparency = m_struWallCfg.byTransparency;
		UpdateData(FALSE);
	}
}
