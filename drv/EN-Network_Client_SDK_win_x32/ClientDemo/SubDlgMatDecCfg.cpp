/**********************************************************
FileName:    SubDlgMatDecCfg.cpp
Description:       
Date:        2008/06/02
Note: 		<Global>struct, macro refer to GeneralDef.h, global variants and API refer to ClientDemo.cpp      
Modification History:      
    <version> <time>         <desc>
    <1.0    > <2008/06/02>       <created>
***********************************************************/

#include "stdafx.h"
#include "clientdemo.h"
#include "SubDlgMatDecCFG.h"
// #include "MatCenter.h"
// #include "MatColumn.h"
// #include "MatRow.h"
// #include "MatManuLink.h"
#include "MatTrans.h"
#include "MatDispChan.h"
#include "MatDynamicTest.h"
#include "MatCycLink.h"
#include "MatPlayBack.h"
#include "MatDispChanControl.h"
#include "MatPassive.h"
#include "DlgUploadLogo.h"
#include "MatDecoderStatus.h"

#include "MatVedioPlatform.h"
#include "MatCodeSplitter.h"

#include "DlgDecoderAbility.h"
#include "DlgMatDecBigScrSplice.h"
#include "DlgMatDecodeChanJoint.h"

#include "DlgWall.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMatDecCFG dialog

/*********************************************************
  Function:	CSubDlgMatDecCfg
  Desc:		Constructor
  Input:	
  Output:	
  Return:	
**********************************************************/
CMatDecCFG::CMatDecCFG(CWnd* pParent /*=NULL*/)
	: CDialog(CMatDecCFG::IDD, pParent)
	, m_iChannelnumber(0)
	, m_lServerID(-1)
	, m_lStartChan(0)
{
	//{{AFX_DATA_INIT(CMatDecCFG)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	for(int i = 0; i < 32; i++)
	{
		memset(&m_struDecChanCtrl[i], 0, sizeof(m_struDecChanCtrl[i]));
		m_dwDecSwitch[i] = 0;
	}
}

/*********************************************************
Function:	DoDataExchange
Desc:		the map between control and variable
Input:	
Output:	
Return:	
**********************************************************/
void CMatDecCFG::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMatDecCFG)
	DDX_Control(pDX, IDC_COMBODECODEDELAY, m_DecodeDelayCtrl);
	DDX_Control(pDX, IDC_COMBOSCALESTATUS, m_ScaleStatusCtrl);
	DDX_Control(pDX, IDC_COMBODECODECHAN, m_DecodeChanCtrl);
	DDX_Control(pDX, IDC_COMBOSWITCH, m_SwitchCombo);
	DDX_Control(pDX, IDC_COMBODECCHAN, m_DecChanCombo);
	//}}AFX_DATA_MAP
}

/*********************************************************
Function:	BEGIN_MESSAGE_MAP
Desc:		the map between control and function
Input:	
Output:	
Return:	
**********************************************************/
BEGIN_MESSAGE_MAP(CMatDecCFG, CDialog)
	//{{AFX_MSG_MAP(CMatDecCFG)
	ON_BN_CLICKED(IDC_BTN_CENTER_SET, OnBtnCenterSet)
	ON_BN_CLICKED(IDC_BUTCOLUMNSET, OnButcolumnset)
	ON_BN_CLICKED(IDC_BUTMANPLAY, OnButmanplay)
	ON_BN_CLICKED(IDC_BUTROWSET, OnButrowset)
	ON_BN_CLICKED(IDC_BTN_DEC_TRANS_SET, OnButtransset)
	ON_BN_CLICKED(IDC_DISPCHANCFG, OnDispchancfg)
	ON_BN_CLICKED(IDC_BUTDYNAMICTEST, OnButdynamictest)
	ON_BN_CLICKED(IDC_BUTCYCLINK, OnButcyclink)
	ON_BN_CLICKED(IDC_BUTTONGET, OnButtonget)
	ON_BN_CLICKED(IDC_BUTTONSET, OnButtonset)
	ON_BN_CLICKED(IDC_BUTREMOTEPLAYBACK, OnButremoteplayback)
	ON_BN_CLICKED(IDC_PASSIVEDECODE, OnPassivedecode)
	ON_BN_CLICKED(IDC_DISPCHAN, OnDispchan)
	ON_BN_CLICKED(IDC_UPLOADLOGO, OnUploadlogo)
	ON_BN_CLICKED(IDC_BUTTON_DECODERSTATUS, OnButtonDecoderstatus)
	ON_BN_CLICKED(IDC_BUTTONGETSCALESTATUS, OnButtongetscalestatus)
	ON_BN_CLICKED(IDC_BUTTONSETSCALESTATUS, OnButtonsetscalestatus)
	ON_CBN_SELCHANGE(IDC_COMBODECCHAN, OnSelchangeCombodecchan)
	ON_CBN_SELCHANGE(IDC_COMBODECODECHAN, OnSelchangeCombodecodechan)
	ON_BN_CLICKED(IDC_BTN_VIDEOCFG, OnBtnVideocfg)
	ON_BN_CLICKED(IDC_BTN_CODESPITTER, OnBtnCodespitter)
	ON_BN_CLICKED(IDC_BTN_BIGSCREENSPLICE, OnBtnBigscreensplice)
	ON_BN_CLICKED(IDC_BTN_DECODERABILITY, OnBtnDecoderability)
	ON_BN_CLICKED(IDC_BTN_WALL, OnBtnWall)
	ON_BN_CLICKED(IDC_BTN_JOINT_CHAN, OnBtnJointChan)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/*********************************************************
  Function:	OnInitDialog
  Desc:		Initialize the dialog
  Input:	
  Output:	
  Return:	
**********************************************************/
BOOL CMatDecCFG::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	CRect rc(0, 0, 0, 0);
	GetParent()->GetClientRect(&rc);
	((CTabCtrl*)GetParent())->AdjustRect(FALSE, &rc);
	MoveWindow(&rc);

	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

/*********************************************************
Function:	CurCfgUpdate
Desc:		
Input:	
Output:	
Return:	
**********************************************************/
void CMatDecCFG::CurCfgUpdate()
{
	int iDeviceIndex = g_pMainDlg->GetCurDeviceIndex();
//  	if (!g_pMainDlg->IsCurDevMatDec(iDeviceIndex))
// 	{
// 		EnableWindow(FALSE);
// 		return;
// 	}
	if (iDeviceIndex == -1)
	{
		EnableWindow(FALSE);
		return;
	}
	else
	{
		m_lServerID = g_struDeviceInfo[iDeviceIndex].lLoginID;
		m_iChannelnumber = g_struDeviceInfo[iDeviceIndex].iDeviceChanNum;
		m_lStartChan = g_struDeviceInfo[iDeviceIndex].iStartChan;
		EnableWindow(TRUE);
	}

    CString tmp;
    int i=0;
    int ChanNo = -1;
    char szLan[128] = {0};
    m_DecChanCombo.ResetContent(); 
	m_DecodeChanCtrl.ResetContent();
    for(i = 0; i < m_iChannelnumber; i++)
    {
        ChanNo = m_lStartChan + i;
        g_StringLanType(szLan, "ͨ��", "Chan");
        tmp.Format("%s %d", szLan, ChanNo);
        m_DecChanCombo.AddString(tmp);
		m_DecodeChanCtrl.AddString(tmp);
        // GetChanStatus(ChanNo, i);
    }
	UpdateData(FALSE);
}

/*********************************************************
  Function:	OnBtnCenterSet
  Desc:		
  Input:	
  Output:	
  Return:	
**********************************************************/
void CMatDecCFG::OnBtnCenterSet() 
{

// 	CMatCenter dlg;
// 	dlg.m_iChannelnumber = m_iChannelnumber;
// 	dlg.m_lServerID = m_lServerID;
// 	dlg.m_lStartChan = m_lStartChan;
// 	dlg.DoModal();
}

/*********************************************************
  Function:	OnButcolumnset
  Desc:		
  Input:	
  Output:	
  Return:	
**********************************************************/
void CMatDecCFG::OnButcolumnset() 
{
// 
// 	CMatColumn dlg;
// 	dlg.m_iChannelnumber = m_iChannelnumber;
// 	dlg.m_lServerID = m_lServerID;
// 	dlg.m_lStartChan = m_lStartChan;	
// 	dlg.DoModal();
}

/*********************************************************
  Function:	OnButmanplay
  Desc:		
  Input:	
  Output:	
  Return:	
**********************************************************/
void CMatDecCFG::OnButmanplay() 
{

// 	CMatManuLink dlg;
// 	dlg.m_iChannelnumber = m_iChannelnumber;
// 	dlg.m_lServerID = m_lServerID;
// 	dlg.m_lStartChan = m_lStartChan;
// 	dlg.DoModal();
}

/*********************************************************
  Function:	OnButrowset
  Desc:		to set mattix row
  Input:	
  Output:	
  Return:	
**********************************************************/
void CMatDecCFG::OnButrowset() 
{

// 	CMatRow dlg;
// 	dlg.m_iChannelnumber = m_iChannelnumber;
// 	dlg.m_lServerID = m_lServerID;
// 	dlg.m_lStartChan = m_lStartChan;	
// 	dlg.DoModal();
}

/*********************************************************
  Function:	OnButtransset
  Desc:		to set the transparent
  Input:	none
  Output:	none
  Return:	none
**********************************************************/
void CMatDecCFG::OnButtransset() 
{

	CMatTrans dlg;
	dlg.m_iChannelnumber = m_iChannelnumber;
	dlg.m_lServerID = m_lServerID;
	dlg.m_lStartChan = m_lStartChan;
	dlg.DoModal();
}

/*********************************************************
  Function:	OnDispchancfg
  Desc:		to setup the configure of the display channel
  Input:	none
  Output:	none
  Return:	none
**********************************************************/
void CMatDecCFG::OnDispchancfg() 
{
	
	CMatDispChan dlg;
	dlg.m_iChannelnumber = m_iChannelnumber;
	dlg.m_lServerID = m_lServerID;
	dlg.m_lStartChan = m_lStartChan;	
	dlg.DoModal();
}

/*********************************************************
  Function:	OnButdynamictest
  Desc:		to set the dynamic configure
  Input:	none
  Output:	none
  Return:	none
**********************************************************/
void CMatDecCFG::OnButdynamictest() 
{
	
	CMatDynamicTest mdt;
	mdt.m_lServerID = m_lServerID;
	mdt.m_lStartChan = m_lStartChan;
	mdt.m_iChannelnumber = m_iChannelnumber;
	mdt.DoModal();
}

/*********************************************************
  Function:	OnButcyclink
  Desc:		to setup cycle link
  Input:	none
  Output:	none
  Return:	none
**********************************************************/
void CMatDecCFG::OnButcyclink() 
{
	
	CMatCycLink mcl;
	mcl.m_lServerID = m_lServerID;
	mcl.m_lStartChan = m_lStartChan;
	mcl.m_iChannelnumber = m_iChannelnumber;
	mcl.DoModal();
}

/*********************************************************
  Function:	OnButtonget
  Desc:		to get the status of the channels
  Input:	none
  Output:	none
  Return:	none
**********************************************************/
void CMatDecCFG::OnButtonget() 
{	
	UpdateData(TRUE);
	
	int sel = m_DecChanCombo.GetCurSel();
	
	CString tmp;
	if (!NET_DVR_MatrixGetDecChanEnable(m_lServerID, sel+m_lStartChan, &m_dwDecSwitch[sel]))
	{
		tmp.Format("Error: NET_DVR_MatrixGetDecChanEnable = %d", NET_DVR_GetLastError());
		AfxMessageBox(tmp);
	}
	else
	{
		m_SwitchCombo.SetCurSel(m_dwDecSwitch[sel]);
	}
	UpdateData(FALSE);
}

/*********************************************************
  Function:	OnButtonset
  Desc:		to set the status of the channels
  Input:	none
  Output:	none
  Return:	none
**********************************************************/
void CMatDecCFG::OnButtonset() 
{	
	UpdateData(TRUE);
	
	CString tmp;
	if (!NET_DVR_MatrixSetDecChanEnable(m_lServerID, m_DecChanCombo.GetCurSel() + m_lStartChan, m_SwitchCombo.GetCurSel()))
	{
		tmp.Format("Error: NET_DVR_MatrixSetDecChanEnable = %d", NET_DVR_GetLastError());
		AfxMessageBox(tmp);
		return;
	}
	char szLan[128] = {0};
	g_StringLanType(szLan, "���óɹ�", "Set successfully");
	AfxMessageBox(szLan);
}

/*********************************************************
  Function:	OnButremoteplayback
  Desc:		to play back remotely
  Input:	none
  Output:	none
  Return:	none
**********************************************************/
void CMatDecCFG::OnButremoteplayback() 
{
	
	CMatPlayBack pl;
	pl.m_lServerID = m_lServerID;
	pl.m_iChannelNumber = m_iChannelnumber;
	pl.m_lStartChan = m_lStartChan;
	pl.DoModal();
}

void CMatDecCFG::OnPassivedecode() 
{
	// TODO: Add your control notification handler code here
    CMatPassive pl;
    pl.m_lServerID = m_lServerID;
    pl.m_iChannelNumber = m_iChannelnumber;
    pl.m_lStartChan = m_lStartChan;
    pl.DoModal();
}

void CMatDecCFG::OnDispchan() 
{
	// TODO: Add your control notification handler code here
    CMatDispChanControl pl;
    pl.m_lServerID = m_lServerID;
    pl.DoModal();
}

void CMatDecCFG::OnUploadlogo() 
{
	// TODO: Add your control notification handler code here
	CDlgUploadLogo dlg;
    dlg.m_lServerID = m_lServerID;
    dlg.DoModal();
}

void CMatDecCFG::OnButtonDecoderstatus() 
{
	// TODO: Add your control notification handler code here
	CMatDecoderStatus dlg;
    //CDlgMatDeviceInfo dlg;
    dlg.m_lServerID = m_lServerID;
    dlg.DoModal();
}

void CMatDecCFG::OnButtongetscalestatus() 
{
	UpdateData(TRUE);
	
	int sel = m_DecodeChanCtrl.GetCurSel();	
	CString tmp;
	//NET_DVR_MATRIX_DECCHAN_CONTROL struDecChanCtrl = {0};
	m_struDecChanCtrl[sel].dwSize = sizeof(m_struDecChanCtrl[sel]);
	if (!NET_DVR_MatrixGetDecChanCfg(m_lServerID, sel + m_lStartChan, &m_struDecChanCtrl[sel]))
	{
		tmp.Format("Error: NET_DVR_MatrixGetDecChanCfg = %d", NET_DVR_GetLastError());
		AfxMessageBox(tmp);
	}
	else
	{
		m_ScaleStatusCtrl.SetCurSel(m_struDecChanCtrl[sel].byDecChanScaleStatus);
        if (m_struDecChanCtrl[sel].byDecodeDelay == 0xff)
        {
            m_DecodeDelayCtrl.SetCurSel(6);
        }
        else
        {
            m_DecodeDelayCtrl.SetCurSel(m_struDecChanCtrl[sel].byDecodeDelay);
        }
		
	}
	UpdateData(FALSE);
}

void CMatDecCFG::OnButtonsetscalestatus() 
{	
	UpdateData(TRUE);
	
	CString tmp;
	//NET_DVR_MATRIX_DECCHAN_CONTROL struDecChanCtrl = {0};
	m_struDecChanCtrl[m_DecodeChanCtrl.GetCurSel()].dwSize = sizeof(m_struDecChanCtrl[m_DecodeChanCtrl.GetCurSel()]);
	m_struDecChanCtrl[m_DecodeChanCtrl.GetCurSel()].byDecChanScaleStatus = m_ScaleStatusCtrl.GetCurSel();

    if (m_DecodeDelayCtrl.GetCurSel() < 6)
    {
        m_struDecChanCtrl[m_DecodeChanCtrl.GetCurSel()].byDecodeDelay = m_DecodeDelayCtrl.GetCurSel();
    }
    else
    {
        m_struDecChanCtrl[m_DecodeChanCtrl.GetCurSel()].byDecodeDelay = 0xff;
    }
	if (!NET_DVR_MatrixSetDecChanCfg(m_lServerID, m_DecodeChanCtrl.GetCurSel() + m_lStartChan, &m_struDecChanCtrl[m_DecodeChanCtrl.GetCurSel()]))
	{
		tmp.Format("Error: NET_DVR_MatrixSetDecChanCfg = %d", NET_DVR_GetLastError());
		AfxMessageBox(tmp);
		return;
	}
	char szLan[128] = {0};
	g_StringLanType(szLan, "���óɹ�", "Set successfully");
	AfxMessageBox(szLan);
}

void CMatDecCFG::OnSelchangeCombodecchan() 
{
	UpdateData(TRUE);
	
	int sel = m_DecChanCombo.GetCurSel();
	
	CString tmp;
	if (!NET_DVR_MatrixGetDecChanEnable(m_lServerID, sel+m_lStartChan, &m_dwDecSwitch[sel]))
	{
		tmp.Format("Error: NET_DVR_MatrixGetDecChanEnable = %d", NET_DVR_GetLastError());
		AfxMessageBox(tmp);
	}
	else
	{
		m_SwitchCombo.SetCurSel(m_dwDecSwitch[sel]);
	}
	UpdateData(FALSE);	
}

void CMatDecCFG::OnSelchangeCombodecodechan() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	
	int sel = m_DecodeChanCtrl.GetCurSel();	
	CString tmp;
	m_struDecChanCtrl[sel].dwSize = sizeof(m_struDecChanCtrl[sel]);
	if (!NET_DVR_MatrixGetDecChanCfg(m_lServerID, sel + m_lStartChan, &m_struDecChanCtrl[sel]))
	{
		tmp.Format("Error: NET_DVR_MatrixGetDecChanCfg = %d", NET_DVR_GetLastError());
		AfxMessageBox(tmp);
	}
	else
	{
        if (m_struDecChanCtrl[sel].byDecodeDelay == 0xff)
        {
            m_DecodeDelayCtrl.SetCurSel(6);
        }
        else
        {
            m_DecodeDelayCtrl.SetCurSel(m_struDecChanCtrl[sel].byDecodeDelay);
        }
		m_ScaleStatusCtrl.SetCurSel(m_struDecChanCtrl[sel].byDecChanScaleStatus);
	}
	UpdateData(FALSE);
}

void CMatDecCFG::OnBtnVideocfg() 
{
	// TODO: Add your control notification handler code here
	CMatVedioPlatform dlg;
    dlg.m_lServerID = m_lServerID;
    dlg.DoModal();
}

void CMatDecCFG::OnBtnCodespitter() 
{
	// TODO: Add your control notification handler code here
	CMatCodeSplitter dlg;
    dlg.m_lServerID = m_lServerID;
    dlg.DoModal();
}

void CMatDecCFG::OnBtnBigscreensplice() 
{
	// TODO: Add your control notification handler code here
	CDlgMatDecBigScrSplice dlg;
 	dlg.DoModal();
}

void CMatDecCFG::OnBtnDecoderability() 
{
	// TODO: Add your control notification handler code here
	CDlgDecoderAbility dlg;
	dlg.DoModal();
}

void CMatDecCFG::OnBtnWall() 
{
	// TODO: Add your control notification handler code here
	CDlgWall dlg;
	dlg.m_lServerID = m_lServerID;
	dlg.DoModal();
}

void CMatDecCFG::OnBtnJointChan() 
{
	// TODO: Add your control notification handler code here
	CDlgMatDecodeChanJoint dlg;
	dlg.DoModal();
}
