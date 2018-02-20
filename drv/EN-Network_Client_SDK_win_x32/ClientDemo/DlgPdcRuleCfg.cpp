// DlgPdcRuleCfg.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgPdcRuleCfg.h"
#include <math.h>
#include "DlgPdcCalibration.h"
#include "DlgPDCSearch.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
CDlgPdcRuleCfg *g_pDlgPdcRuleCfg;
/////////////////////////////////////////////////////////////////////////////
// CDlgPdcRuleCfg dialog
void CALLBACK DrawPDCShow(LONG lRealHandle, HDC hDc, DWORD dwUser)
{
    SetBkMode(hDc, TRANSPARENT);
    SetTextColor(hDc, RGB(255, 255, 255));
    
    if (g_pDlgPdcRuleCfg != NULL)
    {
        g_pDlgPdcRuleCfg->F_DrawPdcRule(lRealHandle, hDc, dwUser);
    }
    
}

CDlgPdcRuleCfg::CDlgPdcRuleCfg(CWnd* pParent /*=NULL*/)
: CDialog(CDlgPdcRuleCfg::IDD, pParent)
{
    //{{AFX_DATA_INIT(CDlgPdcRuleCfg)
	m_bEnableRule = FALSE;
	m_bVcaActive = FALSE;
	m_iDvrChannel = 0;
	m_iDvrPort = 0;
	m_csPassword = _T("");
	m_iStreamPort = 0;
	m_csUserName = _T("");
	m_bStreamValid = FALSE;
	//}}AFX_DATA_INIT
    memset(&m_struPdcRuleCfg, 0, sizeof(m_struPdcRuleCfg));
    m_lServerID = -1; 
    m_iDevIndex = -1; 
    m_lPlayHandle = -1; 
    memset(&m_rcWndRect, 0, sizeof(m_rcWndRect));   
    m_bMouseMove = FALSE;
    m_bCloseIn =   FALSE;
    
    m_dwPosNum = 0;  
    m_iDrawType = -1;
    m_iVcaChan = 0;     
    m_iChannelNum = 0;   
    m_iStartChannel = -1;   
	m_iCurChannel = -1;
    memset(&m_struVcaCtrl, 0, sizeof(m_struVcaCtrl));
    memset(&m_struPUStream, 0, sizeof(m_struPUStream));
}


void CDlgPdcRuleCfg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CDlgPdcRuleCfg)
	DDX_Control(pDX, IDC_COMBO_STREAM_TRANSTYPE, m_comboStreamTransType);
	DDX_Control(pDX, IDC_COMBO_DVR_TRANS_TYPE, m_comboDvrTransType);
	DDX_Control(pDX, IDC_IPADDRESS_STREAM, m_ipStream);
	DDX_Control(pDX, IDC_IPADDRESS_DVR, m_ipDvr);
	DDX_Control(pDX, IDC_COMBO_DVR_TRANS_PROTOCOL2, m_comboDvrTransProtocol);
	DDX_Control(pDX, IDC_COMBO_VCA_TYPE, m_comboVcaType);
	DDX_Control(pDX, IDC_COMBO_STREAM, m_comboStream);
	DDX_Control(pDX, IDC_COMBO_VCA_CHAN, m_comboVcaChan);
	DDX_Check(pDX, IDC_CHK_RULE, m_bEnableRule);
	DDX_Check(pDX, IDC_CHECK_VCA_ACTIVE, m_bVcaActive);
	DDX_Text(pDX, IDC_EDIT_DVR_CHANNEL2, m_iDvrChannel);
	DDX_Text(pDX, IDC_EDIT_DVR_PORT2, m_iDvrPort);
	DDX_Text(pDX, IDC_EDIT_PASSWORD2, m_csPassword);
	DDX_Text(pDX, IDC_EDIT_STREAM_PORT, m_iStreamPort);
	DDX_Text(pDX, IDC_EDIT_USER_NAME, m_csUserName);
	DDX_Check(pDX, IDC_CHECK_STREAM_VALID2, m_bStreamValid);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgPdcRuleCfg, CDialog)
    //{{AFX_MSG_MAP(CDlgPdcRuleCfg)
    ON_BN_CLICKED(IDC_BTN_PDC_RULECFG, OnBtnPdcRulecfg)
    ON_BN_CLICKED(IDC_RADIO_DRAW_POLYGON, OnRadioDrawPolygon)
    ON_BN_CLICKED(IDC_RADIO_DRAW_DIRECTION, OnRadioDrawDirection)
    ON_BN_CLICKED(IDC_BTN_CALIBRATION, OnBtnCalibration)
    ON_CBN_SELCHANGE(IDC_COMBO_VCA_CHAN, OnSelchangeComboVcaChan)
    ON_BN_CLICKED(ID_BTN_SET_VCA_CTRL, OnBtnSetVcaCtrl)
    ON_BN_CLICKED(IDC_BTN_SET_PU_STREAM, OnBtnSetPuStream)
    ON_BN_CLICKED(IDC_BTN_PDC_QUERY, OnBtnPdcQuery)
	ON_BN_CLICKED(IDC_BTN_RESET_COUNTE, OnBtnResetCounte)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgPdcRuleCfg message handlers

BOOL CDlgPdcRuleCfg::OnInitDialog() 
{
    CDialog::OnInitDialog();
    
    // TODO: Add extra initialization here
    g_pDlgPdcRuleCfg = this;
    GetDlgItem(IDC_PLAYWND)->GetWindowRect(&m_rcWndRect);
    m_bCloseIn = TRUE;

    m_iVcaChan = m_iStartChannel + 0;
	char sbuf[128];
    m_comboVcaChan.ResetContent();
	for (int i = 0; i < m_iChannelNum; i++)
    {
        sprintf(sbuf, "VCA Chan%d", i+m_iStartChannel);
        m_comboVcaChan.InsertString(i,sbuf);
    }
//	m_comboVcaChan.SetCurSel(m_iVcaChan - m_iStartChannel);

	switch (g_struDeviceInfo[m_iDevIndex].iDeviceType)
    {
	case IVMS_6200_C:
        m_comboVcaChan.SetCurSel(m_iCurChannel/*+m_iStartChannel*/);
		GetDlgItem(IDC_COMBO_VCA_CHAN)->EnableWindow(FALSE);
		m_iVcaChan = m_iCurChannel+m_iStartChannel;
		break;
	default:
		m_comboVcaChan.SetCurSel(m_iVcaChan - m_iStartChannel);
		GetDlgItem(IDC_COMBO_VCA_CHAN)->EnableWindow(TRUE);
		break;
    }

    GetPdcRuleWnd();
    GetCtrlWnd();
    GetPUStreamWnd();
   UpdateData(FALSE);

    return TRUE;  // return TRUE unless you set the focus to a control
    // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgPdcRuleCfg::GetCtrlWnd() 
{
    m_bVcaActive = m_struVcaCtrl.struCtrlInfo[m_iVcaChan-1].byVCAEnable;
    m_comboVcaType.SetCurSel(0);
	m_comboStream.SetCurSel(m_struVcaCtrl.struCtrlInfo[m_iVcaChan-1].byStreamWithVCA);

}
void CDlgPdcRuleCfg::GetPdcRuleWnd()
{
    char szLan[128] = {0};
    DWORD dwReturn;
    if (!NET_DVR_GetDVRConfig(m_lServerID, NET_DVR_GET_PDC_RULECFG, m_iVcaChan, &m_struPdcRuleCfg, sizeof(m_struPdcRuleCfg), &dwReturn))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_PDC_RULECFG Fail");
        g_StringLanType(szLan, "��ȡPDC����ʧ��", "Fail to get PDC rule config");
        AfxMessageBox(szLan);
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_PDC_RULECFG Success");
    }
    if (m_lPlayHandle >= 0)
    {
        StopRealPlay();
    }
    StartRealPlay();
    
    m_bEnableRule = m_struPdcRuleCfg.byEnable;
    
    
    UpdateData(FALSE);

}
void CDlgPdcRuleCfg::GetPUStreamWnd()
{
 
    DWORD dwReturn = 0;
    char szLan[128] = {0};
    if (!NET_DVR_GetDVRConfig(m_lServerID, NET_DVR_GET_PU_STREAMCFG, m_iVcaChan, &m_struPUStream, sizeof(m_struPUStream), &dwReturn))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_PU_STREAMCFG fail");
        g_StringLanType(szLan, "��ȡǰ��ȡ���豸��Ϣʧ��", "Fail to get PU stream config");
        AfxMessageBox(szLan);
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_PU_STREAMCFG Succ");
    }
        //Channel info
        DWORD ipDvr = CStringTodwIP(m_struPUStream.struDevChanInfo.struIP.sIpV4);
        m_ipDvr.SetAddress(ipDvr);
        m_iDvrPort = m_struPUStream.struDevChanInfo.wDVRPort;
        m_iDvrChannel = m_struPUStream.struDevChanInfo.byChannel;
        m_comboDvrTransType.SetCurSel(m_struPUStream.struDevChanInfo.byTransMode);
        m_comboDvrTransProtocol.SetCurSel(m_struPUStream.struDevChanInfo.byTransProtocol);
        m_csUserName = m_struPUStream.struDevChanInfo.sUserName;
        m_csPassword = m_struPUStream.struDevChanInfo.sPassword;
        
        //Stream server config
        m_bStreamValid = m_struPUStream.struStreamMediaSvrCfg.byValid;
       // EnableStream(m_bStreamValid);
        DWORD ipStream = CStringTodwIP(m_struPUStream.struStreamMediaSvrCfg.struDevIP.sIpV4);
        m_ipStream.SetAddress(ipStream);
        m_iStreamPort = m_struPUStream.struStreamMediaSvrCfg.wDevPort;
        m_comboStreamTransType.SetCurSel(m_struPUStream.struStreamMediaSvrCfg.byTransmitType);

}
BOOL CDlgPdcRuleCfg::PreTranslateMessage(MSG* pMsg) 
{
    // TODO: Add your specialized code here and/or call the base class
    CPoint pt(0,0);
    CRect  rcWnd(0,0,0,0);
    GetDlgItem(IDC_PLAYWND)->GetWindowRect(&rcWnd);
    GetCursorPos(&pt);
    CString strTemp = _T("");
    DWORD i=0;
    BOOL bOneLine = TRUE,bXOneLine = TRUE,bYOneLine = TRUE;
    
    switch(pMsg->message) 
    {
    case WM_LBUTTONDOWN:
        if((m_iDrawType == 1 || m_iDrawType == 2)&& (GetAsyncKeyState(VK_LCONTROL)<0 || GetAsyncKeyState(VK_RCONTROL)<0))//��CTRL�� ��ͼ
        {
            if (m_iDrawType == 1)// Draw repolygon
            {
                if(PtInRect(&rcWnd,pt))
                {	
                        if(m_bCloseIn)
                        {
                            m_dwPosNum = 0;
                            m_struPdcRuleCfg.struPolygon.dwPointNum = m_dwPosNum;		
                        }
                        if(m_dwPosNum>9)
                        {
                            char szLan[128] = {0};
                            g_StringLanType(szLan,"����ͳ�ƹ���Ϊ4����","Polygon vertex can not be over 4!");
                            AfxMessageBox(szLan);
                            return TRUE;
                        }
                        if((float)(pt.x-rcWnd.left)/(float)rcWnd.Width() <= m_struPdcRuleCfg.struPolygon.struPos[m_dwPosNum-1].fX+0.01 && (float)(pt.x-rcWnd.left)/(float)rcWnd.Width() >= m_struPdcRuleCfg.struPolygon.struPos[m_dwPosNum-1].fX-0.01\
                            && (float)(pt.y-rcWnd.top)/(float)rcWnd.Height() <= m_struPdcRuleCfg.struPolygon.struPos[m_dwPosNum-1].fY+0.01 && (float)(pt.y-rcWnd.top)/(float)rcWnd.Height() >= m_struPdcRuleCfg.struPolygon.struPos[m_dwPosNum-1].fY-0.01)
                        {
                            char szLan[128] = {0};
                            g_StringLanType(szLan, "����������ͬһ���ϻ�����", "Region can not be painted in the same point");
                            AfxMessageBox(szLan);
                            return TRUE;
                        }
                        m_bCloseIn = FALSE;
                        m_bMouseMove = FALSE;
                        m_struPdcRuleCfg.struPolygon.struPos[m_dwPosNum].fX = (float)(pt.x-rcWnd.left)/(float)rcWnd.Width();
                        m_struPdcRuleCfg.struPolygon.struPos[m_dwPosNum].fY = (float)(pt.y-rcWnd.top)/(float)rcWnd.Height();
                        m_dwPosNum++;
                        m_struPdcRuleCfg.struPolygon.dwPointNum = m_dwPosNum;			
                }
                
            }
            else if (m_iDrawType == 2)
            {
                if(PtInRect(&rcWnd,pt))
                {		
                    if(!m_bMouseMove)
                    {
                        m_struPdcRuleCfg.struEnterDirection.struStartPoint.fX = (float)(pt.x-rcWnd.left)/(float)rcWnd.Width();
                        m_struPdcRuleCfg.struEnterDirection.struStartPoint.fY = (float)(pt.y-rcWnd.top)/(float)rcWnd.Height();		
                        m_struPdcRuleCfg.struEnterDirection.struEndPoint.fX = (float)(pt.x-rcWnd.left)/(float)rcWnd.Width();
                        m_struPdcRuleCfg.struEnterDirection.struEndPoint.fY = (float)(pt.y-rcWnd.top)/(float)rcWnd.Height();			
                        m_bMouseMove = TRUE;
                    }
                    else
                    {
                        if ((float)(pt.x-rcWnd.left)/(float)rcWnd.Width() <= m_struPdcRuleCfg.struEnterDirection.struStartPoint.fX+0.01 && (float)(pt.x-rcWnd.left)/(float)rcWnd.Width() >= m_struPdcRuleCfg.struEnterDirection.struStartPoint.fX-0.01\
                            && (float)(pt.y-rcWnd.top)/(float)rcWnd.Height() <= m_struPdcRuleCfg.struEnterDirection.struStartPoint.fY+0.01 && (float)(pt.y-rcWnd.top)/(float)rcWnd.Height() >= m_struPdcRuleCfg.struEnterDirection.struStartPoint.fY-0.01)
                        {
                            char szLan[128] = {0};
                            g_StringLanType(szLan, "����������ͬһ���ϻ�����", "Region can not be painted in the same point");
                            AfxMessageBox(szLan);
                            return TRUE;
                        }
                        m_struPdcRuleCfg.struEnterDirection.struEndPoint.fX = (float)(pt.x-rcWnd.left)/(float)rcWnd.Width();
                        m_struPdcRuleCfg.struEnterDirection.struEndPoint.fY = (float)(pt.y-rcWnd.top)/(float)rcWnd.Height();			
                        m_bMouseMove = FALSE;
                    }
				}
            }
            break;
        }
    case WM_MOUSEMOVE:
        if((m_iDrawType == 1 || m_iDrawType == 2)&&(GetAsyncKeyState(VK_LCONTROL)<0 || GetAsyncKeyState(VK_RCONTROL)<0))
        {
            if (m_iDrawType == 1)
            {
                if(PtInRect(&rcWnd,pt))
                {
                    if(m_dwPosNum > 9)
                    {
                        return TRUE;
                    }
                    if( !m_bCloseIn)
                    {
                        m_bMouseMove = TRUE;
                        m_struPdcRuleCfg.struPolygon.struPos[m_dwPosNum].fX = (float)(pt.x-rcWnd.left)/(float)rcWnd.Width();
                        m_struPdcRuleCfg.struPolygon.struPos[m_dwPosNum].fY = (float)(pt.y-rcWnd.top)/(float)rcWnd.Height();
                        m_struPdcRuleCfg.struPolygon.dwPointNum = m_dwPosNum+1;				
                    }
                }
            }
            else if (m_iDrawType == 2)
            {
                if(PtInRect(&rcWnd,pt))
                {
                    if(m_bMouseMove)
                    {
                        m_struPdcRuleCfg.struEnterDirection.struEndPoint.fX = (float)(pt.x-rcWnd.left)/(float)rcWnd.Width();
                        m_struPdcRuleCfg.struEnterDirection.struEndPoint.fY = (float)(pt.y-rcWnd.top)/(float)rcWnd.Height();			
                    }
                }

            }
        }
        break;
    case WM_LBUTTONUP:
        if((m_iDrawType == 1 )&&(GetAsyncKeyState(VK_LCONTROL)<0 || GetAsyncKeyState(VK_RCONTROL)<0))
        {
            m_bMouseMove = FALSE;
        }
        break;

    case WM_RBUTTONDOWN:
        if(m_iDrawType == 1 && (GetAsyncKeyState(VK_LCONTROL)<0 || GetAsyncKeyState(VK_RCONTROL)<0))
        {
            if(PtInRect(&rcWnd,pt))
            {
                if(m_dwPosNum > 9)
                {
                    return TRUE;
                }
                for(i=0; i<m_dwPosNum; i++)
                {
                    if(m_struPdcRuleCfg.struPolygon.struPos[i].fX != m_struPdcRuleCfg.struPolygon.struPos[i+1].fX)
                    {
                        bXOneLine = FALSE;
                        break;
                    }
                }
                for(i=0; i<m_dwPosNum; i++)
                {
                    if(m_struPdcRuleCfg.struPolygon.struPos[i].fY != m_struPdcRuleCfg.struPolygon.struPos[i+1].fY)
                    {
                        bYOneLine = FALSE;
                        break;
                    }
                }
                bOneLine = bXOneLine||bYOneLine;
                if(bOneLine)
                {
                    char szlan[128] = {0};
                    g_StringLanType(szlan, "�������һ�ߣ��޷���������!","Can not constitute a regional");
                    AfxMessageBox(szlan);
                    return TRUE;
                }
                if( !m_bCloseIn)
                {
                    if(m_bMouseMove)
                    {
                        m_bMouseMove = FALSE;
                        m_struPdcRuleCfg.struPolygon.dwPointNum--;
                        m_struPdcRuleCfg.struPolygon.struPos[m_struPdcRuleCfg.struPolygon.dwPointNum].fX = 0;
                        m_struPdcRuleCfg.struPolygon.struPos[m_struPdcRuleCfg.struPolygon.dwPointNum].fY = 0;
                    }
                    m_bCloseIn = TRUE;
                }
            }
        }
        else if(m_iDrawType == 1)
        {
            if(PtInRect(&rcWnd,pt))
            {
                if(m_dwPosNum == 0)
                {
                    return TRUE;
                }
                if( !m_bCloseIn)
                {
                    m_struPdcRuleCfg.struPolygon.dwPointNum--;
                    m_dwPosNum--;
                    m_struPdcRuleCfg.struPolygon.struPos[m_struPdcRuleCfg.struPolygon.dwPointNum].fX = 0;
                    m_struPdcRuleCfg.struPolygon.struPos[m_struPdcRuleCfg.struPolygon.dwPointNum].fY = 0;
                }
                else if( m_bCloseIn)
                {
                    m_struPdcRuleCfg.struPolygon.dwPointNum = 0;
                    m_dwPosNum = 0;
                    m_bCloseIn = FALSE;
                }
            }
        }
        break;
    default:
        break;
    }
    return CDialog::PreTranslateMessage(pMsg);
}

void CDlgPdcRuleCfg::OnBtnPdcRulecfg() 
{
    // TODO: Add your control notification handler code here
    UpdateData(TRUE);
    m_struPdcRuleCfg.byEnable = m_bEnableRule;
    char szLan[128] = {0};
    if (!NET_DVR_SetDVRConfig(m_lServerID, NET_DVR_SET_PDC_RULECFG, m_iVcaChan, &m_struPdcRuleCfg, sizeof(m_struPdcRuleCfg)))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_SET_PDC_RULECFG");
        g_StringLanType(szLan, "����PDC����ʧ��", "Fail to set PDC rule config");
        AfxMessageBox(szLan);
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_SET_PDC_RULECFG");
    }
}

void CDlgPdcRuleCfg::PostNcDestroy() 
{
    // TODO: Add your specialized code here and/or call the base class
    StopRealPlay();
    CDialog::PostNcDestroy();
}

long CDlgPdcRuleCfg::StartRealPlay()
{
    NET_DVR_CLIENTINFO struClientInfo;
    memset(&struClientInfo, 0, sizeof(NET_DVR_CLIENTINFO));
    struClientInfo.lChannel = m_iVcaChan;
    struClientInfo.hPlayWnd = GetDlgItem(IDC_PLAYWND)->GetSafeHwnd();
    m_lPlayHandle = NET_DVR_RealPlay_V30(m_lServerID, &struClientInfo, NULL, NULL, TRUE); 
    if (m_lPlayHandle == -1) 
    {
        AfxMessageBox("Fail to Preview");
        return m_lPlayHandle;
    }
    else
    {
        if (!NET_DVR_RigisterDrawFun(m_lPlayHandle, DrawPDCShow, 0)) 
        {
            g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_RigisterDrawFun Fail");
            AfxMessageBox("Fail to set DrawFun callback");
        }
        
    }
    return m_lPlayHandle;
}

BOOL CDlgPdcRuleCfg::StopRealPlay()
{
    BOOL bRet;
    if (m_lPlayHandle >= 0)
    {
        bRet = NET_DVR_StopRealPlay(m_lPlayHandle);
        if (!bRet)
        {
            AfxMessageBox("Fail to stop preview");
        }
    }
    return bRet;
}

void CDlgPdcRuleCfg::F_DrawPdcRule(LONG lRealHandle, HDC hDc, DWORD dwUser)
{
    F_DrawFrame(lRealHandle, hDc, dwUser,  RGB(255, 255, 0));
    PDCDrawDirection(hDc, dwUser);
}

/*********************************************************
Function:	F_DrawFrame
Desc:	
Input:	lPlayHandle, ���Ŵ��ڵĲ��ž��
hDc : ���Ŵ��ڵ��豸���������
dwUser: �û����ݣ��������ֶ�·Ԥ��ʱ�����øûص�����
DWORD dwRuleID ��ǰ����ID
COLORREF color ������ɫ
Output:	
Return:	 void
**********************************************************/
/*********************************************************
  Function:	F_DrawFrame
  Desc:		Draw frame
  Input:	lRealHandle, player port;
            hDc,handle;
			dwUser, user data;
			color
  Output:	
  Return:	
**********************************************************/
void CDlgPdcRuleCfg::F_DrawFrame(long lRealHandle, HDC hDc, DWORD dwUser,  COLORREF color)
{
    
    using namespace Gdiplus;
    Graphics graphics(hDc);
    SolidBrush  brush(Color(50, 0, 0, 0));
    brush.SetColor(Color(50, GetRValue(color), GetGValue(color), GetBValue(color)));
    
    POINT point[VCA_MAX_POLYGON_POINT_NUM] = {0};
    
    CPen DrawPen;
    unsigned int i;
    
    DrawPen.CreatePen(PS_SOLID, 1, color);
    SetTextColor(hDc,color);
    
    HGDIOBJ pOldPen = SelectObject(hDc, DrawPen);
    MoveToEx(hDc, (int)(m_struPdcRuleCfg.struPolygon.struPos[0].fX*m_rcWndRect.Width()), \
        (int)(m_struPdcRuleCfg.struPolygon.struPos[0].fY*m_rcWndRect.Height()), NULL);
    
    for(i=1; i<m_struPdcRuleCfg.struPolygon.dwPointNum; i++)
    {
        
        LineTo(hDc, (int)(m_struPdcRuleCfg.struPolygon.struPos[i].fX*m_rcWndRect.Width()),\
            (int)(m_struPdcRuleCfg.struPolygon.struPos[i].fY*m_rcWndRect.Height()));
        //if cross, redraw
        if(i>=MIN_PNT_NUM && !m_bMouseMove && IsCrossLine(&m_struPdcRuleCfg.struPolygon))
        {
            char szLan[128] = {0};
            g_StringLanType(szLan,"����β����ڵı����ཻ�������,����������!","Polygon edges are not adjacent is intersect");
            AfxMessageBox(szLan);
            m_dwPosNum--;
            m_struPdcRuleCfg.struPolygon.dwPointNum--;
            break;
        }

    }
    
    for (i=0; i<(int)m_struPdcRuleCfg.struPolygon.dwPointNum ; i++)
    {
        if (i == VCA_MAX_POLYGON_POINT_NUM)
        {
            break;
        }
        
        point[i].x = (int)(m_struPdcRuleCfg.struPolygon.struPos[i].fX*m_rcWndRect.Width());
        point[i].y = (int)(m_struPdcRuleCfg.struPolygon.struPos[i].fY*m_rcWndRect.Height());
    }
    
    if(VCA_MAX_POLYGON_POINT_NUM == i && !m_bMouseMove)
    {
        if (IsValidArea(&m_struPdcRuleCfg.struPolygon))
        {
            graphics.FillPolygon(&brush, (Point *)point, m_struPdcRuleCfg.struPolygon.dwPointNum);
            
            LineTo(hDc, (int)(m_struPdcRuleCfg.struPolygon.struPos[0].fX*m_rcWndRect.Width()), (int)(m_struPdcRuleCfg.struPolygon.struPos[0].fY*m_rcWndRect.Height()));	
            m_bCloseIn = TRUE;
        }else
        {
            m_bCloseIn = FALSE;
            m_struPdcRuleCfg.struPolygon.dwPointNum--;
            m_dwPosNum--;
        }
    }
    else if(m_struPdcRuleCfg.struPolygon.dwPointNum>2 && m_bCloseIn)
    {
        if (IsValidArea(&m_struPdcRuleCfg.struPolygon))
        {
            graphics.FillPolygon(&brush, (Point *)point, m_struPdcRuleCfg.struPolygon.dwPointNum);
            
            LineTo(hDc, (int)(m_struPdcRuleCfg.struPolygon.struPos[0].fX*m_rcWndRect.Width()),(int)(m_struPdcRuleCfg.struPolygon.struPos[0].fY*m_rcWndRect.Height()));
        }else
        {
            m_bCloseIn = FALSE;
        }
    }
    
    SelectObject(hDc, pOldPen);
    DeleteObject(DrawPen);
}

BOOL CDlgPdcRuleCfg::IsCrossLine(NET_VCA_POLYGON *alarm_region)
{
    if(alarm_region == NULL)
    {
        return FALSE;
    }
    unsigned int i, j;
    DWORD nPointTotal = 0;
    NET_VCA_POINT *pPointArray = NULL;
    NET_VCA_POINT *pPntArr = NULL;
    BOOL    bCrossLine;
    
    pPointArray = alarm_region->struPos;
    nPointTotal = alarm_region->dwPointNum;
    bCrossLine  = FALSE;
    
    if (nPointTotal >= 3)
    {
        bCrossLine = FALSE;
    }
    else
    {
        pPntArr = new NET_VCA_POINT[nPointTotal];
        if (pPntArr == NULL)
        {
            char szLan[128] = {0};
            g_StringLanType(szLan, "�ڴ����ʧ��!","Memory allocation failure!");
            AfxMessageBox(szLan);
            exit(EXIT_FAILURE);
        }
        
        for (i = 0; i < nPointTotal; i++)
        {
            pPntArr[i] = pPointArray[i];
        }
        
        for(i = 0; i < nPointTotal - 3; i++)
        {
            for (j = i + 2; j < nPointTotal-1; j++)
            {
                
                if (F_LineCrossDetect(pPntArr[i], pPntArr[i + 1], pPntArr[j], pPntArr[j + 1]))
                {
                    bCrossLine = TRUE;
                }			
            }
        }
        if (pPntArr != NULL)
        {
            delete [] pPntArr;
        }
    }
    return bCrossLine;
}

BOOL CDlgPdcRuleCfg::F_LineCrossDetect(NET_VCA_POINT p1, NET_VCA_POINT p2, NET_VCA_POINT q1, NET_VCA_POINT q2)
{
    NET_VCA_POINT p1_q1, q2_q1, p2_q1, q1_p1, p2_p1, q2_p1;    
    float z1, z2, z3, z4;
    BOOL  line_cross = FALSE;
    
    // p1 - q1;
    p1_q1.fX = p1.fX - q1.fX;
    p1_q1.fY = p1.fY - q1.fY;
    
    // q2 - q1;
    q2_q1.fX = q2.fX - q1.fX;
    q2_q1.fY = q2.fY - q1.fY;
    
    // p2 - q1;
    p2_q1.fX = p2.fX - q1.fX;
    p2_q1.fY = p2.fY - q1.fY;
    
    // ���1 (p1 - q1) �� (q2 - q1)��
    z1 = p1_q1.fX * q2_q1.fY - q2_q1.fX * p1_q1.fY; 
    
    // ���2 (q2 - q1) �� (p2 - q1)��
    z2 = q2_q1.fX * p2_q1.fY - p2_q1.fX * q2_q1.fY;
    
    // q1 - p1;
    q1_p1.fX = q1.fX - p1.fX;
    q1_p1.fY = q1.fY - p1.fY;
    
    // p2 - p1;
    p2_p1.fX = p2.fX - p1.fX;
    p2_p1.fY = p2.fY - p1.fY;
    
    // q2 - p1;
    q2_p1.fX = q2.fX - p1.fX;
    q2_p1.fY = q2.fY - p1.fY;
    
    // ���3 (q1 - p1) �� (p2 - p1)��
    z3 = q1_p1.fX * p2_p1.fY - p2_p1.fX * q1_p1.fY;
    
    // ���4 (p2 - p1) �� (q2 - p1);
    z4 = p2_p1.fX * q2_p1.fY - q2_p1.fX * p2_p1.fY;
    
    if( ((z1 >= 0.0f && z2 >= 0.0f) || (z1 < 0.0f && z2 < 0.0f)) && 
        ((z3 >= 0.0f && z4 >= 0.0f) || (z3 < 0.0f && z4 < 0.0f)))
    {
        line_cross = TRUE;	
    }else
    {
        line_cross = FALSE;
    }
    
    return line_cross;
}

BOOL CDlgPdcRuleCfg::IsValidArea(NET_VCA_POLYGON *alarm_region)
{
    if(alarm_region == NULL)
    {
        return FALSE;
    }

    if (F_IsStraightLine(alarm_region))
    {
        char szLan[128] = {0};
        g_StringLanType(szLan, "���е���ͬһֱ���ϣ�������ɶ����!",\
            "All points have been in the same line, not able to form the polygon");
        MessageBox(szLan);
        return FALSE;
    }
   
    if (F_IsACrossLine(alarm_region))
    {
        char szLan[128] = {0};
        g_StringLanType(szLan,"�յ���������������е�ֱ���ཻ�����������Ч�Ķ����!", \
            "There are straight-line intersection, can not be composed of an effective polygon");
        MessageBox(szLan);
        return FALSE;
    }
    return TRUE;
}

BOOL CDlgPdcRuleCfg::F_IsACrossLine(NET_VCA_POLYGON *alarm_region) // 
{
    if(alarm_region == NULL)
    {
        return FALSE;
    }
    unsigned int i;
    DWORD	 nPointTotal;
    NET_VCA_POINT *pPointArray;
    NET_VCA_POINT *pPntArr;
    BOOL    bCrossLine;
    
    pPointArray = alarm_region->struPos;
    nPointTotal = alarm_region->dwPointNum;
    bCrossLine  = FALSE;
    
    if (nPointTotal == VCA_MAX_POLYGON_POINT_NUM)
    {
        bCrossLine = FALSE;
    }
    else
    {
        pPntArr = new NET_VCA_POINT[nPointTotal];
        if (pPntArr == NULL)
        {
            char szLan[128] = {0};
            g_StringLanType(szLan, "�ڴ����ʧ��!","Memory allocation failure!");
            AfxMessageBox(szLan);
            exit(EXIT_FAILURE);
        }
        
        for (i = 0; i < nPointTotal; i++)
        {
            pPntArr[i] = pPointArray[i];
        }
        //      pPntArr[nPointTotal] = pPointArray[0];
        
        for(i = 0; i < nPointTotal - 1; i++)
        {
            
            if (F_LineCrossDetect(pPntArr[0], pPntArr[nPointTotal - 1], pPntArr[i], pPntArr[i + 1]))
            {
                bCrossLine = TRUE;
            }			
        } 
        delete [] pPntArr;
    }
    return bCrossLine;
}

BOOL CDlgPdcRuleCfg::F_IsStraightLine(NET_VCA_POLYGON *alarm_region)  
{
    if(alarm_region == NULL)
    {
        return FALSE;
    }
    unsigned int i = 0;
    BOOL         bStraightLine;
    float        fSlope;
    float        fDistance;
    float        fCoefficient;
    float        fOffset;
    DWORD		 nPointTotal;
    NET_VCA_POINT *pPointArray;
    int          nXOffset;
    int          nYOffset;
    
    pPointArray = alarm_region->struPos;
    nPointTotal = alarm_region->dwPointNum;
    
    nXOffset = (int)(pPointArray[0].fX - pPointArray[1].fX);
    nYOffset = (int)(pPointArray[0].fY - pPointArray[1].fY);
    bStraightLine = TRUE;
    
    if (0 == nXOffset)
    {
        for (i = 2; i < nPointTotal; i++)
        {
            if (pPointArray[0].fX != pPointArray[i].fX)
            {
                bStraightLine = FALSE;
                break;
            }
        }
    }
    
    if (0 == nYOffset)
    {
        for (i = 2; i < nPointTotal; i++)
        {
            if (pPointArray[0].fY != pPointArray[i].fY)
            {
                bStraightLine = FALSE;
                break;
            }                 
        }
    }
    
    if ((0 != nXOffset) && (0 != nYOffset))
    {
        fSlope  = 1.0f * nYOffset / nXOffset;
        
        fOffset = pPointArray[0].fY - fSlope * pPointArray[1].fX;
        
        fCoefficient = (float)sqrt(1.0 + fSlope * fSlope);
        
        for (i = 2; i < nPointTotal; i ++)
        {
            fDistance = (float)fabs(fSlope * pPointArray[i].fX - pPointArray[i].fY + fOffset)/fCoefficient;
            
            if ((fDistance - 0.0f) > 0.000001f)
            {
                bStraightLine = FALSE;
                break;
            }
        }		
    }
    
    return bStraightLine;	
}

void CDlgPdcRuleCfg::PDCDrawDirection(HDC hDc, DWORD dwUser)
{
    CPen cpDrawPen;
    
    int x1 = (int)(m_struPdcRuleCfg.struEnterDirection.struStartPoint.fX*m_rcWndRect.Width());
    int y1 = (int)(m_struPdcRuleCfg.struEnterDirection.struStartPoint.fY*m_rcWndRect.Height());
    
    int x2 = (int)(m_struPdcRuleCfg.struEnterDirection.struEndPoint.fX*m_rcWndRect.Width());
    int y2 = (int)(m_struPdcRuleCfg.struEnterDirection.struEndPoint.fY*m_rcWndRect.Height());
    
    if ((x1 == x2) && (y1 == y2))
    {
        return;
    }
    
    using namespace Gdiplus;
    Graphics graphics(hDc);
    
    Color color(80, 0, 0, 0);
    
    Pen pen(color, 7);
    
    pen.SetStartCap(LineCapFlat);
    
    Point pt1 = Point(0, -1);
    Point pt2 = Point(2, -1);
    Point pt3 = Point(0, 4);
    Point pt4 = Point(-2, -1);
    GraphicsPath fillPath;
    fillPath.AddLine(pt1, pt2);
    fillPath.AddLine(pt2, pt3);
    fillPath.AddLine(pt3, pt4);
    CustomLineCap custCap(&fillPath, NULL);
    pen.SetCustomEndCap(&custCap);
    cpDrawPen.CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
    color.SetValue(color.MakeARGB(100, 0, 255, 255));
    SetTextColor(hDc,RGB(225, 225, 225));
    
    int k = 0;
    
    if(x2 != x1)
        k = (y2 - y1) / (x2 - x1);
    
    pen.SetColor(color);
    
    if(k < 0)
        graphics.DrawLine(&pen, x1-2, y1-1, x2-2, y2-1);
    else
        graphics.DrawLine(&pen, x1+2, y1-1, x2+2, y2-1);
    
    HGDIOBJ cpOldPen = SelectObject(hDc, cpDrawPen);
    
    cpDrawPen.DeleteObject();
    SelectObject(hDc, cpOldPen);
    
    graphics.ReleaseHDC(hDc);
}

void CDlgPdcRuleCfg::OnRadioDrawPolygon() 
{
    // TODO: Add your control notification handler code here
    m_iDrawType = 1; 
    
}

void CDlgPdcRuleCfg::OnRadioDrawDirection() 
{
    // TODO: Add your control notification handler code here
	m_iDrawType = 2; 
}

void CDlgPdcRuleCfg::OnBtnCalibration() 
{
	// TODO: Add your control notification handler code here
    CDlgPdcCalibration dlg;
    dlg.m_lServerID = m_lServerID;
    dlg.m_iDevIndex = m_iDevIndex;
    dlg.m_lChannel =    m_iVcaChan;
    dlg.m_lPlayHandle = m_lPlayHandle;
    dlg.DoModal();
}

void CDlgPdcRuleCfg::OnSelchangeComboVcaChan() 
{
	// TODO: Add your control notification handler code here
	m_iVcaChan = m_comboVcaChan.GetCurSel() + m_iStartChannel;
   GetPdcRuleWnd();
   GetCtrlWnd();
   GetPUStreamWnd();
   UpdateData(FALSE);
}

void CDlgPdcRuleCfg::OnBtnSetVcaCtrl() 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE);
    char szLan[128] = {0};
    char szCn[128] = {0};
    char szEn[128] = {0};
    m_struVcaCtrl.struCtrlInfo[m_iVcaChan-m_iStartChannel].byVCAEnable = (unsigned char)m_bVcaActive;
    m_struVcaCtrl.struCtrlInfo[m_iVcaChan-m_iStartChannel].byVCAType = 6;  // Ŀǰֻ��6  �ò�����øĶ�����Ϊ��̬���Ӻ�֮ǰ��������Ϊ����һ��
	m_struVcaCtrl.struCtrlInfo[m_iVcaChan-m_iStartChannel].byStreamWithVCA = (unsigned char)m_comboStream.GetCurSel();
    if(!NET_DVR_SetDVRConfig(m_lServerID, NET_DVR_SET_VCA_CTRLCFG, 0 , &m_struVcaCtrl, sizeof(NET_VCA_CTRLCFG)))
    {	
        sprintf(szCn, "��������ͨ��%dʧ��", m_iVcaChan);
        sprintf(szEn, "Fail to set vca channel%d", m_iVcaChan);
        g_StringLanType(szLan, szCn, szEn);
        AfxMessageBox(szLan);
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_SET_VCA_CTRLCFG");
    }
    else
    {
        sprintf(szCn, "��������ͨ��%d�ɹ�", m_iVcaChan);
        sprintf(szCn, "Succ to set vca channel%d", m_iVcaChan);
        g_StringLanType(szLan, szCn, szEn);
        AfxMessageBox(szLan);
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_SET_VCA_CTRLCFG");
    }
}

void CDlgPdcRuleCfg::OnBtnSetPuStream() 
{
	// TODO: Add your control notification handler code here
    SetPUStreamCfg();
}

void CDlgPdcRuleCfg::SetPUStreamCfg()
{
    UpdateData(TRUE);
   
    DWORD ipDvr = 0;
    m_ipDvr.GetAddress(ipDvr);
    CString csTemp;
    csTemp = IPToStr(ipDvr);
    sprintf(m_struPUStream.struDevChanInfo.struIP.sIpV4, "%s", csTemp.GetBuffer(0));
    
    m_struPUStream.struDevChanInfo.wDVRPort = (WORD)m_iDvrPort;
    m_struPUStream.struDevChanInfo.byChannel = (BYTE)m_iDvrChannel;
    m_struPUStream.struDevChanInfo.byTransProtocol = (BYTE)m_comboDvrTransProtocol.GetCurSel();
    m_struPUStream.struDevChanInfo.byTransMode = (BYTE)m_comboDvrTransType.GetCurSel();
    memset(m_struPUStream.struDevChanInfo.sUserName, 0, NAME_LEN*sizeof(BYTE));
    strncpy((char*)m_struPUStream.struDevChanInfo.sUserName, (char*)m_csUserName.GetBuffer(0), NAME_LEN-1);
    memset(m_struPUStream.struDevChanInfo.sPassword, 0, PASSWD_LEN*sizeof(BYTE));
    strncpy((char*)m_struPUStream.struDevChanInfo.sPassword, (char*)m_csPassword.GetBuffer(0), PASSWD_LEN-1);
    
    m_struPUStream.struStreamMediaSvrCfg.byValid = m_bStreamValid;
    
    DWORD ipStream = 0;
    m_ipStream.GetAddress(ipStream);
    csTemp = IPToStr(ipStream);
    sprintf(m_struPUStream.struStreamMediaSvrCfg.struDevIP.sIpV4, "%s", csTemp.GetBuffer(0));
    
    m_struPUStream.struStreamMediaSvrCfg.wDevPort = (WORD)m_iStreamPort;
    m_struPUStream.struStreamMediaSvrCfg.byTransmitType = m_comboStreamTransType.GetCurSel();
    

    if (!NET_DVR_SetDVRConfig(m_lServerID, NET_DVR_SET_PU_STREAMCFG, m_iVcaChan, &m_struPUStream, sizeof(m_struPUStream)))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_SET_PU_STREAMCFG fail");
        AfxMessageBox("Fail to set PU stream config");
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_SET_PU_STREAMCFG Succ");
    }

}

void CDlgPdcRuleCfg::OnBtnPdcQuery() 
{
	// TODO: Add your control notification handler code here
    CDlgPDCSearch dlg;
    dlg.m_lServerID = m_lServerID;
    dlg.m_lChannel = m_iVcaChan;
    dlg.m_iDevIndex = m_iDevIndex;
    dlg.DoModal();

}

void CDlgPdcRuleCfg::OnBtnResetCounte() 
{
	// TODO: Add your control notification handler code here
	if (!NET_DVR_ResetCounter(m_lServerID, m_iVcaChan))
	{
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_ResetCounter");
        AfxMessageBox("Fail to reset counter");
	} 
	else
	{
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_ResetCounter");
	}
}