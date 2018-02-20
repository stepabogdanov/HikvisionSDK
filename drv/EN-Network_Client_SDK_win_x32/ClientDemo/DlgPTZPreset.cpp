/**********************************************************
FileName:    DlgPTZPreset.cpp
Description: PTZ preset     
Date:        2008/06/28
Note: 		 <global>struct, refer to GeneralDef.h, global variants and functions refer to ClientDemo.cpp  
Modification History:      
    <version> <time>         <desc>
    <1.0    > <2008/06/28>       <created>
***********************************************************/

#include "stdafx.h"
#include "ClientDemo.h"
#include "DlgPTZPreset.h"
#include ".\dlgptzpreset.h"

extern BOOL PTZPresetAll(LONG lRealHandle, int iDevIndex, int iChanIndex, DWORD dwPTZCommand, DWORD dwPresetIndex, char *szCmdString);
// CDlgPTZPreset dialog
/*********************************************************
  Function:	CDlgPTZPreset
  Desc:		constructor
  Input:	
  Output:	
  Return:	
**********************************************************/
IMPLEMENT_DYNAMIC(CDlgPTZPreset, CDialog)
CDlgPTZPreset::CDlgPTZPreset(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgPTZPreset::IDD, pParent)
	, m_bAuto(FALSE)
{
}

/*********************************************************
  Function:	~CDlgPTZPreset
  Desc:		destructor
  Input:	
  Output:	
  Return:	
**********************************************************/
CDlgPTZPreset::~CDlgPTZPreset()
{
}

/*********************************************************
Function:	DoDataExchange
Desc:		the map between control and variable
Input:	
Output:	
Return:	
**********************************************************/
void CDlgPTZPreset::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgPTZPreset)
	DDX_Control(pDX, IDC_COMBO_PRESET_SETUP, m_comboPreset);
        //}}AFX_DATA_MAP

}

/*********************************************************
Function:	BEGIN_MESSAGE_MAP
Desc:		the map between control and function
Input:	
Output:	
Return:	
**********************************************************/
BEGIN_MESSAGE_MAP(CDlgPTZPreset, CDialog)
	//{{AFX_MSG_MAP(CDlgPTZPreset)	
	ON_BN_CLICKED(IDC_BTN_PRESET_ADD, OnBnClickedBtnPresetAdd)
	ON_BN_CLICKED(IDC_BTN_PRESET_DEL, OnBnClickedBtnPresetDel)
	ON_BN_CLICKED(IDC_BTN_EXIT, OnBtnExit)
	ON_BN_CLICKED(IDC_BTN_PTZ_TRAN, OnBtnPtzTran)
	ON_BN_CLICKED(IDC_BTN_DO, OnBtnDo)
	ON_BN_CLICKED(IDC_BTN_PTZ_LIGHT, OnBtnPtzLight)
	ON_BN_CLICKED(IDC_BTN_WIPER, OnBtnWiper)
	//}}AFX_MSG_MAP

END_MESSAGE_MAP()


// CDlgPTZPreset message handlers
/*********************************************************
Function:	OnInitDialog
Desc:		Initialize the dialog
Input:	
Output:	
Return:	
**********************************************************/
BOOL CDlgPTZPreset::OnInitDialog()
{
	CDialog::OnInitDialog();

	int i=0;
	char szNum[8] = {0};
	for (i=0; i<MAX_PRESET_V30+2; i++)//0 and 257 just for test
	{
		sprintf(szNum, "%d", i);
		m_comboPreset.AddString(szNum);
	}
	m_comboPreset.SetCurSel(1);
	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

/*********************************************************
  Function:	OnBnClickedBtnPresetAdd
  Desc:		add presets
  Input:	
  Output:	
  Return:	
**********************************************************/
void CDlgPTZPreset::OnBnClickedBtnPresetAdd()
{
	UpdateData(TRUE);
	int iWndIndex = g_pMainDlg->m_iCurWndIndex;
	int iPreset = m_comboPreset.GetCurSel();
	int iDevIndex=g_pMainDlg->GetCurDeviceIndex();
	int iChanIndex = g_pMainDlg->GetCurChanIndex();
	PTZPresetAll(g_dlgOutput[iWndIndex].m_lPlayHandle, iDevIndex, iChanIndex, SET_PRESET, iPreset, "SET_PRESET");
}

/*********************************************************
  Function:	OnBnClickedBtnPresetDel
  Desc:		delete presets
  Input:	
  Output:	
  Return:	
**********************************************************/
void CDlgPTZPreset::OnBnClickedBtnPresetDel()
{
	UpdateData(TRUE);
	int iWndIndex = g_pMainDlg->m_iCurWndIndex;
	int iPreset = m_comboPreset.GetCurSel();
	int iDevIndex=g_pMainDlg->GetCurDeviceIndex();
	int iChanIndex = g_pMainDlg->GetCurChanIndex();
	PTZPresetAll(g_dlgOutput[iWndIndex].m_lPlayHandle, iDevIndex, iChanIndex, CLE_PRESET, iPreset, "CLE_PRESET");
}

/*********************************************************
  Function:	OnBtnExit
  Desc:		exit the dialog
  Input:	none
  Output:	none
  Return:	none
**********************************************************/
void CDlgPTZPreset::OnBtnExit() 
{
	// TODO: Add your control notification handler code here
	CDialog::OnCancel();
}

void CDlgPTZPreset::OnBtnPtzTran() 
{
	// TODO: Add your control notification handler code here
	char  sCodeBuf[128] = {0};
    sCodeBuf[0] = (char)0xa0;

    sCodeBuf[1] = (char)0x00;

    sCodeBuf[2] = (char)0x00;

    sCodeBuf[3] = (char)0x07;

    sCodeBuf[4] = (char)0x00;

    sCodeBuf[5] = (char)0x63;

    sCodeBuf[6] = (char)0xaf;

    sCodeBuf[7] = (char)0x6b;
	if (g_dlgOutput[g_pMainDlg->m_iCurWndIndex].m_lPlayHandle >= 0)
	{
		if (!NET_DVR_TransPTZ_EX(g_dlgOutput[g_pMainDlg->m_iCurWndIndex].m_lPlayHandle, sCodeBuf, 8))
		{
			g_dlgOutput[g_pMainDlg->m_iCurWndIndex].AddLog(OPERATION_FAIL_T, "NET_DVR_TransPTZ_EX");
		}
	}

}

extern BOOL PTZControlAll(LONG lRealHandle, int iDevIndex, int iChanIndex, DWORD dwPTZCommand,DWORD dwStop, char *szCmdString);
void CDlgPTZPreset::OnBtnDo() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	int iDevIndex=g_pMainDlg->GetCurDeviceIndex();
	int iChanIndex = g_pMainDlg->GetCurChanIndex();

	PTZControlAll(g_dlgOutput[g_pMainDlg->m_iCurWndIndex].m_lPlayHandle, iDevIndex, iChanIndex, PAN_AUTO, 0, "PAN_AUTO");
}

void CDlgPTZPreset::OnBtnPtzLight() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	int iDevIndex=g_pMainDlg->GetCurDeviceIndex();
	int iChanIndex = g_pMainDlg->GetCurChanIndex();

	for (int i = 0; i<100; i++)
	{
		if (i%2 == 0)
		{
			PTZControlAll(g_dlgOutput[g_pMainDlg->m_iCurWndIndex].m_lPlayHandle, iDevIndex, iChanIndex, LIGHT_PWRON, 0, "LIGHT_PWRON");	
		}
		else
		{
			PTZControlAll(g_dlgOutput[g_pMainDlg->m_iCurWndIndex].m_lPlayHandle, iDevIndex+1, iChanIndex, LIGHT_PWRON, 0, "LIGHT_PWRON");	
		}
		
	}
}

void CDlgPTZPreset::OnBtnWiper() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	int iDevIndex=g_pMainDlg->GetCurDeviceIndex();
	int iChanIndex = g_pMainDlg->GetCurChanIndex();

	PTZControlAll(g_dlgOutput[g_pMainDlg->m_iCurWndIndex].m_lPlayHandle, iDevIndex, iChanIndex, WIPER_PWRON, 0, "WIPER_PWRON");	
	Sleep(2000);
	PTZControlAll(g_dlgOutput[g_pMainDlg->m_iCurWndIndex].m_lPlayHandle, iDevIndex, iChanIndex, WIPER_PWRON, 1, "WIPER_PWRON");
	
}
