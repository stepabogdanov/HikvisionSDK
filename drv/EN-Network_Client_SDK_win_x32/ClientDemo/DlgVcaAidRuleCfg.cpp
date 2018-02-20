// DlgVcaAidRuleCfg.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgVcaAidRuleCfg.h"
#include "DrawFun.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgVcaAidRuleCfg dialog

CDlgVcaAidRuleCfg *g_pDlgVcaAidRule = NULL;

void CALLBACK g_DrawAidRule(LONG lRealHandle, HDC hDc, DWORD dwUser)
{
    g_pDlgVcaAidRule->F_DrawFun(lRealHandle, hDc, dwUser);
}

CDlgVcaAidRuleCfg::CDlgVcaAidRuleCfg(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgVcaAidRuleCfg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgVcaAidRuleCfg)    
	m_iCongestionDuration = 0;
	m_iCongestionLength = 0;
	m_iDebris = 0;
	m_iInverseAngle = 0;
	m_iInverseDistance = 0;
	m_iInverseDuration = 0;
	m_iParking = 0;
	m_iPedestrian = 0;
	m_csRuleName = _T("");
	m_bEnable = FALSE;
	m_bHandleType1 = FALSE;
	m_bHandleType2 = FALSE;
	m_bHandleType3 = FALSE;
	m_bHandleType4 = FALSE;
	m_bHandleType5 = FALSE;
	m_iHour11 = 0;
	m_iHour12 = 0;
	m_iHour21 = 0;
	m_iHour22 = 0;
	m_iMin11 = 0;
	m_iMin12 = 0;
	m_iMin21 = 0;
	m_iMin22 = 0;
	m_bDrawPolygon = FALSE;
	m_bFilterActive = FALSE;
	m_fMaxHeight = 0.0f;
	m_fMaxWidth = 0.0f;
	m_fMinHeight = 0.0f;
	m_fMinWidth = 0.0f;
	m_bSetMaxFilter = FALSE;
	m_bSetMiniFilter = FALSE;
	//}}AFX_DATA_INIT
    m_lServerID = -1;
    m_lChannel = -1;
    m_iDevIndex = -1;
    memset(&m_struAIDRuleCfg, 0, sizeof(m_struAIDRuleCfg));
    memset(&m_struAIDOneRule, 0, sizeof(m_struAIDOneRule));
    memset(&m_struLaneCfg, 0, sizeof(m_struLaneCfg));
    m_iAidRuleIndex = -1;
    m_dwAlarmOutNum = 0;
    m_iChannelnumber = 0;
    memset(&m_rcWnd, 0, sizeof(m_rcWnd));
    memset(m_bCloseIn, 0, sizeof(m_bCloseIn));
    memset(m_bMouseMove, 0, sizeof(m_bMouseMove));
    memset(m_struVcaPolygon, 0, sizeof(m_struVcaPolygon));
    memset(&m_struVcaChanInParam, 0, sizeof(m_struVcaChanInParam));
    memset(&m_struItsAbility, 0, sizeof(m_struItsAbility));
    memset(&m_struItsAbility, 0, sizeof(m_struItsAbility));
    memset(&m_struPuStream, 0, sizeof(m_struPuStream));
    m_lPUServerID = -1;
}


void CDlgVcaAidRuleCfg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgVcaAidRuleCfg)
	DDX_Control(pDX, IDC_COMBO_FILTER_MODE, m_comboFilterMode);
	DDX_Control(pDX, IDC_COMBO_RESOLUTION, m_comboResolution);
	DDX_Control(pDX, IDC_COMBO_PRO_PIC_TYPE, m_comboProPicType);
	DDX_Control(pDX, IDC_COMBO_PIC_QUALITY, m_comboPicQuality);
	DDX_Control(pDX, IDC_LIST_RECORD_CHAN, m_listRecordChan);
	DDX_Control(pDX, IDC_LIST_ALARM_OUT, m_listAlarmOut);
	DDX_Control(pDX, IDC_COMBOWEEKDAY, m_comboWeekday);
	DDX_Control(pDX, IDC_COMBOCOPYTIME, m_comboCopyTime);
	DDX_Control(pDX, IDC_COMBO_AID_RULE_INDEX, m_comboAidRuleIndex);
	DDX_Control(pDX, IDC_LIST_AID_TYPE, m_listAIDType);
	DDX_Text(pDX, IDC_EDIT_CONGESTION_DURATION, m_iCongestionDuration);
	DDX_Text(pDX, IDC_EDIT_CONGESTION_LENGTH, m_iCongestionLength);
	DDX_Text(pDX, IDC_EDIT_DEBRIS, m_iDebris);
	DDX_Text(pDX, IDC_EDIT_INVERSE_ANGLE, m_iInverseAngle);
	DDX_Text(pDX, IDC_EDIT_INVERSE_DISTANCE, m_iInverseDistance);
	DDX_Text(pDX, IDC_EDIT_INVERSE_DURATION, m_iInverseDuration);
	DDX_Text(pDX, IDC_EDIT_PARKING, m_iParking);
	DDX_Text(pDX, IDC_EDIT_PEDESTRIAN, m_iPedestrian);
	DDX_Text(pDX, IDC_EDIT_RULE_NAME, m_csRuleName);
	DDX_Check(pDX, IDC_CHK_ENABLE, m_bEnable);
	DDX_Check(pDX, IDC_CHECKHANDLETYPE1, m_bHandleType1);
	DDX_Check(pDX, IDC_CHECKHANDLETYPE2, m_bHandleType2);
	DDX_Check(pDX, IDC_CHECKHANDLETYPE3, m_bHandleType3);
	DDX_Check(pDX, IDC_CHECKHANDLETYPE4, m_bHandleType4);
	DDX_Check(pDX, IDC_CHECKHANDLETYPE5, m_bHandleType5);
	DDX_Text(pDX, IDC_EDITHOUR11, m_iHour11);
	DDX_Text(pDX, IDC_EDITHOUR12, m_iHour12);
	DDX_Text(pDX, IDC_EDITHOUR21, m_iHour21);
	DDX_Text(pDX, IDC_EDITHOUR22, m_iHour22);
	DDX_Text(pDX, IDC_EDITMIN11, m_iMin11);
	DDX_Text(pDX, IDC_EDITMIN12, m_iMin12);
	DDX_Text(pDX, IDC_EDITMIN21, m_iMin21);
	DDX_Text(pDX, IDC_EDITMIN22, m_iMin22);
	DDX_Check(pDX, IDC_CHK_DRAW_POLYGON, m_bDrawPolygon);
	DDX_Check(pDX, IDC_CHECK_FILTER_ACTIVE, m_bFilterActive);
	DDX_Text(pDX, IDC_EDIT_MAX_HEIGHT, m_fMaxHeight);
	DDX_Text(pDX, IDC_EDIT_MAX_WIDTH, m_fMaxWidth);
	DDX_Text(pDX, IDC_EDIT_MIN_HEIGHT, m_fMinHeight);
	DDX_Text(pDX, IDC_EDIT_MIN_WIDTH, m_fMinWidth);
	DDX_Check(pDX, IDC_CHECK_SET_MAX_FILTER, m_bSetMaxFilter);
	DDX_Check(pDX, IDC_CHECK_SET_MINI_FILTER, m_bSetMiniFilter);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgVcaAidRuleCfg, CDialog)
	//{{AFX_MSG_MAP(CDlgVcaAidRuleCfg)
	ON_BN_CLICKED(IDC_BTN_SET_AID_RULE, OnBtnSetAidRule)
	ON_CBN_SELCHANGE(IDC_COMBO_AID_RULE_INDEX, OnSelchangeComboAidRuleIndex)
	ON_BN_CLICKED(IDC_TIME_OK, OnTimeOk)
	ON_BN_CLICKED(IDC_TIME_COPY, OnTimeCopy)
	ON_CBN_SELCHANGE(IDC_COMBOWEEKDAY, OnSelchangeComboweekday)
	ON_CBN_SELCHANGE(IDC_COMBOCOPYTIME, OnSelchangeCombocopytime)
	ON_BN_CLICKED(IDC_BTN_ONE_RULE_CONFIRM, OnBtnOneRuleConfirm)
	ON_BN_CLICKED(IDC_CHECK_FILTER_ACTIVE, OnCheckFilterActive)
	ON_BN_CLICKED(IDC_CHK_DRAW_POLYGON, OnChkDrawPolygon)
	ON_CBN_SELCHANGE(IDC_COMBO_FILTER_MODE, OnSelchangeComboFilterMode)
	ON_BN_CLICKED(IDC_CHECK_SET_MINI_FILTER, OnCheckSetMiniFilter)
	ON_BN_CLICKED(IDC_CHECK_SET_MAX_FILTER, OnCheckSetMaxFilter)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgVcaAidRuleCfg message handlers

BOOL CDlgVcaAidRuleCfg::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
    GetDlgItem(IDC_PLAYWND)->GetWindowRect(&m_rcWnd);
    
    CPoint pt(0,0);
    GetCursorPos(&pt);

    if (m_bDrawPolygon)
    {
        PreDrawPolygonMsg(pMsg, pt);
    }
    else if (m_bSetMiniFilter || m_bSetMaxFilter)
    {
        PreDrawSizeFilterMsg(pMsg, pt);
    }
	return CDialog::PreTranslateMessage(pMsg);
}

BOOL CDlgVcaAidRuleCfg::PreDrawSizeFilterMsg(MSG* pMsg, CPoint &pt)
{
    switch (pMsg->message)
    {
    case WM_LBUTTONDOWN:
        if(m_bSetMiniFilter && (GetAsyncKeyState(VK_LCONTROL)<0 || GetAsyncKeyState(VK_RCONTROL)<0))
        {
            if(PtInRect(&m_rcWnd,pt))
            {
                m_struAIDOneRule.struSizeFilter.struMiniRect.fX = (float)(pt.x-m_rcWnd.left)/(float)m_rcWnd.Width();
                m_struAIDOneRule.struSizeFilter.struMiniRect.fY = (float)(pt.y-m_rcWnd.top)/(float)m_rcWnd.Height();
            }
        }//First coordinate of Maximal Rectangle
        else if(m_bSetMaxFilter && (GetAsyncKeyState(VK_LCONTROL)<0 || GetAsyncKeyState(VK_RCONTROL)<0))
        {
            if(PtInRect(&m_rcWnd,pt))
            {
                m_struAIDOneRule.struSizeFilter.struMaxRect.fX = (float)(pt.x-m_rcWnd.left)/(float)m_rcWnd.Width();
                m_struAIDOneRule.struSizeFilter.struMaxRect.fY = (float)(pt.y-m_rcWnd.top)/(float)m_rcWnd.Height();
            }
        }
        break;
    case WM_MOUSEMOVE:
        if(m_bSetMiniFilter && (GetAsyncKeyState(VK_LCONTROL)<0 || GetAsyncKeyState(VK_RCONTROL)<0)) //尺寸过滤器
        {
            if(PtInRect(&m_rcWnd,pt))
            {
                m_struAIDOneRule.struSizeFilter.struMiniRect.fWidth = (float)(pt.x-m_rcWnd.left)/(float)m_rcWnd.Width() - m_struAIDOneRule.struSizeFilter.struMiniRect.fX;
                m_struAIDOneRule.struSizeFilter.struMiniRect.fHeight = (float)(pt.y-m_rcWnd.top)/(float)m_rcWnd.Height() - m_struAIDOneRule.struSizeFilter.struMiniRect.fY;
            }
            
        }
        else if(m_bSetMaxFilter && (GetAsyncKeyState(VK_LCONTROL)<0 || GetAsyncKeyState(VK_RCONTROL)<0)) //尺寸过滤器
        {
            if(PtInRect(&m_rcWnd,pt))
            {	
                m_struAIDOneRule.struSizeFilter.struMaxRect.fWidth = (float)(pt.x-m_rcWnd.left)/(float)m_rcWnd.Width() - m_struAIDOneRule.struSizeFilter.struMaxRect.fX;
                m_struAIDOneRule.struSizeFilter.struMaxRect.fHeight = (float)(pt.y-m_rcWnd.top)/(float)m_rcWnd.Height() - m_struAIDOneRule.struSizeFilter.struMaxRect.fY;
            }
        }
        break;
    }

    return TRUE;
}

BOOL CDlgVcaAidRuleCfg::PreDrawPolygonMsg(MSG* pMsg, CPoint &pt)
{
    int i=0;
    BOOL bOneLine = TRUE,bXOneLine = TRUE,bYOneLine = TRUE;

    switch (pMsg->message)
    {
    case WM_LBUTTONDOWN:
        if ((GetAsyncKeyState(VK_LCONTROL)<0 || GetAsyncKeyState(VK_RCONTROL)<0) && 
            PtInRect(&m_rcWnd,pt))
        {

                if(m_bNeedRedraw[m_iAidRuleIndex])
                {			
                    if(m_bCloseIn[m_iAidRuleIndex])
                    {
                        m_dwPosNum = 0;
                        m_struVcaPolygon[m_iAidRuleIndex].dwPointNum = m_dwPosNum;		
                    }
                    if(m_dwPosNum>9)
                    {
                        char szLan[128] = {0};
                        g_StringLanType(szLan,"多边形顶点不能超过10个!","Apexes of polygon should less than 10");
                        AfxMessageBox(szLan);
                        return TRUE;
                    }
                    if((float)(pt.x-m_rcWnd.left)/(float)m_rcWnd.Width() <= m_struVcaPolygon[m_iAidRuleIndex].struPos[m_dwPosNum-1].fX+0.01 && (float)(pt.x-m_rcWnd.left)/(float)m_rcWnd.Width() >= m_struVcaPolygon[m_iAidRuleIndex].struPos[m_dwPosNum-1].fX-0.01\
                        && (float)(pt.y-m_rcWnd.top)/(float)m_rcWnd.Height() <= m_struVcaPolygon[m_iAidRuleIndex].struPos[m_dwPosNum-1].fY+0.01 && (float)(pt.y-m_rcWnd.top)/(float)m_rcWnd.Height() >= m_struVcaPolygon[m_iAidRuleIndex].struPos[m_dwPosNum-1].fY-0.01)
                    {
                        char szLan[128] = {0};
                        g_StringLanType(szLan, "不能连续在同一点上画区域", "Can't draw region on the point used");
                        AfxMessageBox(szLan);
                        return TRUE;
                    }
                    m_bCloseIn[m_iAidRuleIndex] = FALSE;
                    m_bMouseMove[m_iAidRuleIndex] = FALSE;
                    m_struVcaPolygon[m_iAidRuleIndex].struPos[m_dwPosNum].fX = (float)(pt.x-m_rcWnd.left)/(float)m_rcWnd.Width();
                    m_struVcaPolygon[m_iAidRuleIndex].struPos[m_dwPosNum].fY = (float)(pt.y-m_rcWnd.top)/(float)m_rcWnd.Height();
                    m_dwPosNum++;
                    m_struVcaPolygon[m_iAidRuleIndex].dwPointNum = m_dwPosNum;	
                    
            }
            
        }
        break;
    case WM_MOUSEMOVE:
        if ((GetAsyncKeyState(VK_LCONTROL)<0 || GetAsyncKeyState(VK_RCONTROL)<0) && 
            PtInRect(&m_rcWnd,pt))
        {
                if(PtInRect(&m_rcWnd,pt))
                {
                    if(m_dwPosNum > 9)
                    {
                        return TRUE;
                    }
                    if( m_bNeedRedraw[m_iAidRuleIndex] && !m_bCloseIn[m_iAidRuleIndex])
                    {
                        m_bMouseMove[m_iAidRuleIndex] = TRUE;
                        m_struVcaPolygon[m_iAidRuleIndex].struPos[m_dwPosNum].fX = (float)(pt.x-m_rcWnd.left)/(float)m_rcWnd.Width();
                        m_struVcaPolygon[m_iAidRuleIndex].struPos[m_dwPosNum].fY = (float)(pt.y-m_rcWnd.top)/(float)m_rcWnd.Height();
                        m_struVcaPolygon[m_iAidRuleIndex].dwPointNum = m_dwPosNum+1;				
                    }
                }
        }

        break;
    case WM_RBUTTONDOWN:
        if((GetAsyncKeyState(VK_LCONTROL)<0 || GetAsyncKeyState(VK_RCONTROL)<0) 
            && PtInRect(&m_rcWnd,pt))
        {
                if(m_dwPosNum > 9)
                {
                    return TRUE;
                }
                for(i=0; i<m_dwPosNum; i++)
                {
                    if(m_struVcaPolygon[m_iAidRuleIndex].struPos[i].fX != m_struVcaPolygon[m_iAidRuleIndex].struPos[i+1].fX)
                    {
                        bXOneLine = FALSE;
                        break;
                    }
                }
                for(i=0; i<m_dwPosNum; i++)
                {
                    if(m_struVcaPolygon[m_iAidRuleIndex].struPos[i].fY != m_struVcaPolygon[m_iAidRuleIndex].struPos[i+1].fY)
                    {
                        bYOneLine = FALSE;
                        break;
                    }
                }
                bOneLine = bXOneLine||bYOneLine;
                if(bOneLine)
                {
                    char szlan[128] = {0};
                    g_StringLanType(szlan, "所画点成一线，无法构成区域!","The points is on a line and can't create a rectangle!");
                    AfxMessageBox(szlan);
                    return TRUE;
                }
                if( m_bNeedRedraw[m_iAidRuleIndex] && !m_bCloseIn[m_iAidRuleIndex])
                {
                    if(m_bMouseMove[m_iAidRuleIndex])
                    {
                        m_bMouseMove[m_iAidRuleIndex] = FALSE;
                        m_struVcaPolygon[m_iAidRuleIndex].dwPointNum--;
                        m_struVcaPolygon[m_iAidRuleIndex].struPos[m_struVcaPolygon[m_iAidRuleIndex].dwPointNum].fX = 0;
                        m_struVcaPolygon[m_iAidRuleIndex].struPos[m_struVcaPolygon[m_iAidRuleIndex].dwPointNum].fY = 0;
                    }
                    m_bCloseIn[m_iAidRuleIndex] = TRUE;
                }
		}
        break;
    }
    return TRUE;
}

BOOL CDlgVcaAidRuleCfg::OnInitDialog() 
{
	CDialog::OnInitDialog();
    g_pDlgVcaAidRule = this;
    GetVcaChanAbility();

	InitWnd();


    if (!GetAIDRuleCfg())
    {
        AfxMessageBox("Fail to get AID rule config");
        return FALSE;
    }
    
    GetLaneCfg();
    for (int i = 0; i < MAX_AID_RULE; i++)
    {
        memcpy(&m_struVcaPolygon[i], &m_struAIDRuleCfg.struOneAIDRule[i].struPolygon, sizeof(m_struVcaPolygon[i]));
    }

    StartPlay();

    m_comboAidRuleIndex.SetCurSel(0);
    OnSelchangeComboAidRuleIndex();
    
    SetAidRuleToWnd(m_struAIDRuleCfg);

    UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


BOOL CDlgVcaAidRuleCfg::GetVcaChanAbility()
{
    BOOL bRet = FALSE; 
    DWORD dwSceneMode = 0;
    if (!NET_DVR_GetSceneMode(m_lServerID, m_lChannel, &dwSceneMode))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "VCA_CHAN_ABILITY");
        return FALSE;
    }
    m_struVcaChanInParam.byMode = (BYTE)dwSceneMode;
    m_struVcaChanInParam.byVCAType = VCA_ITS;
    
    if (!NET_DVR_GetDeviceAbility(m_lServerID, VCA_CHAN_ABILITY, (char*)&m_struVcaChanInParam,\
        sizeof(m_struVcaChanInParam), (char*)&m_struItsAbility, sizeof(m_struItsAbility)))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "VCA_CHAN_ABILITY");
        bRet = FALSE;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "VCA_CHAN_ABILITY");
        bRet = TRUE;
    }
    
    return bRet;
}

void CDlgVcaAidRuleCfg::InitWnd()
{
    char szLan[128] = {0};
    char sbufCn[128] = {0};
    char sbufEn[128] = {0};
    int i = 0;

    for (i = 0; i < MAX_AID_RULE; i ++)
    {
        m_bNeedRedraw[i] = FALSE;//Redraw polygon
        m_bCloseIn[i] = TRUE;//Polygon is closed or not
    }
    int index = 0;
    m_comboAidRuleIndex.ResetContent();
    m_comboAidRuleIndex.AddString("Rule 1");
    m_comboAidRuleIndex.AddString("Rule 2");
    m_comboAidRuleIndex.AddString("Rule 3");
    m_comboAidRuleIndex.AddString("Rule 4");
    m_comboAidRuleIndex.AddString("Rule 5");
    m_comboAidRuleIndex.AddString("Rule 6");
    m_comboAidRuleIndex.AddString("Rule 7");
    m_comboAidRuleIndex.AddString("Rule 8");

    m_listAIDType.DeleteAllItems();
    m_listAIDType.SetExtendedStyle(LVS_EX_CHECKBOXES);
    index = 0;

    if ((m_struItsAbility.dwAbilityType & ITS_CONGESTION_ABILITY) != 0)
    {
    g_StringLanType(szLan, "拥堵", "Congestion");
    m_listAIDType.InsertItem(index, szLan);
    m_listAIDType.SetItemData(index, CONGESTION);
    index++;
    }

    if ((m_struItsAbility.dwAbilityType & ITS_PARKING_ABILITY) != 0)
    {
    g_StringLanType(szLan, "停车", "Parking");
    m_listAIDType.InsertItem(index, szLan);
    m_listAIDType.SetItemData(index, PARKING);
    index++;
    }

    if ((m_struItsAbility.dwAbilityType & ITS_INVERSE_ABILITY) != 0)
    {
    g_StringLanType(szLan, "逆行", "Inverse");
    m_listAIDType.InsertItem(index, szLan);
    m_listAIDType.SetItemData(index, INVERSE);
    index++;
    }

    if ((m_struItsAbility.dwAbilityType & ITS_PEDESTRIAN_ABILITY) != 0)
    {
    g_StringLanType(szLan, "行人", "Pedestrian");
    m_listAIDType.InsertItem(index, szLan);
    m_listAIDType.SetItemData(index, PEDESTRIAN);
    index++;
    }

    if ((m_struItsAbility.dwAbilityType & ITS_DEBRIS_ABILITY) != 0)
    {
    g_StringLanType(szLan, "抛洒物", "Debris");
    m_listAIDType.InsertItem(index, szLan);
    m_listAIDType.SetItemData(index, DEBRIS);
    index++;
    }

    if ((m_struItsAbility.dwAbilityType & ITS_SMOKE_ABILITY) != 0)
    {
        g_StringLanType(szLan, "烟雾", "Smoke");
        m_listAIDType.InsertItem(index, szLan);
        m_listAIDType.SetItemData(index, SMOKE);
        index++;
    }

    m_dwAlarmOutNum = g_struDeviceInfo[m_iDevIndex].iAlarmOutNum;
    m_listAlarmOut.DeleteAllItems();
    m_listAlarmOut.SetExtendedStyle(LVS_EX_CHECKBOXES);
    for (i = 0; i < m_dwAlarmOutNum; i++)
    {
        sprintf(sbufCn, "输出%d", (i+1));
        sprintf(sbufEn, "Channel%d", (i+1));
        g_StringLanType(szLan, sbufCn, sbufEn);
        m_listAlarmOut.InsertItem(i, szLan);
    }

    m_iChannelnumber = g_struDeviceInfo[m_iDevIndex].iDeviceChanNum;
    m_listRecordChan.SetExtendedStyle(LVS_EX_CHECKBOXES);
    m_listRecordChan.DeleteAllItems();
    for (i = 0; i < m_iChannelnumber; i++)
    {
        sprintf(sbufCn, "通道%d", (i+1));
        sprintf(sbufEn, "Channel%d", (i+1));
        g_StringLanType(szLan, sbufCn, sbufEn);
        m_listRecordChan.InsertItem(i, szLan);
    }


}


BOOL CDlgVcaAidRuleCfg::SetAIDRuleCfg()
{
    BOOL bRet = FALSE;
    if (!NET_DVR_SetDVRConfig(m_lServerID, NET_DVR_SET_AID_RULECFG, m_lChannel, &m_struAIDRuleCfg, sizeof(m_struAIDRuleCfg)))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_SET_AID_RULECFG Chan[%d]", m_lChannel);
        bRet = FALSE;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_SET_AID_RULECFG Chan[%d]", m_lChannel);
        bRet = TRUE;
    }
    return bRet;
}

BOOL CDlgVcaAidRuleCfg::GetAIDRuleCfg()
{
    DWORD dwReturn = 0;
    BOOL bRet = FALSE;
    if (!NET_DVR_GetDVRConfig(m_lServerID, NET_DVR_GET_AID_RULECFG, m_lChannel, &m_struAIDRuleCfg, sizeof(m_struAIDRuleCfg), &dwReturn))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_AID_RULECFG Chan[%d]", m_lChannel);
        bRet = FALSE;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_AID_RULECFG Chan[%d]", m_lChannel);
        bRet = TRUE;
    }
    return bRet;
}

BOOL CDlgVcaAidRuleCfg::GetLaneCfg()
{
    DWORD dwReturn = 0;
    BOOL bRet = FALSE;
    if (!NET_DVR_GetDVRConfig(m_lServerID, NET_DVR_GET_LANECFG, m_lChannel, &m_struLaneCfg, sizeof(m_struLaneCfg), &dwReturn))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_LANECFG Chan[%d]", m_lChannel);
        bRet = FALSE;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_LANECFG Chan[%d]", m_lChannel);
        bRet = TRUE;
    }
    return bRet;
}

void CDlgVcaAidRuleCfg::OnBtnSetAidRule() 
{
    UpdateData(TRUE);
    GetAidRuleFromWnd(m_struAIDRuleCfg);
    if (!SetAIDRuleCfg())
    {
        AfxMessageBox("Fail to set AID rule config");
    }	
    else
    {
        memcpy(&m_struAIDOneRule, &m_struAIDRuleCfg.struOneAIDRule[m_iAidRuleIndex], sizeof(m_struAIDOneRule));
    }
}

void CDlgVcaAidRuleCfg::SetAidRuleToWnd(NET_DVR_AID_RULECFG const &struAidRule)
{
    m_comboProPicType.SetCurSel(struAidRule.byPicProType); //Get actions for alarm
    m_comboResolution.SetCurSel(struAidRule.struPictureParam.wPicSize);//image resolution
	m_comboPicQuality.SetCurSel(struAidRule.struPictureParam.wPicQuality);//image quality
    
    SetOneAidRuleToWnd(struAidRule.struOneAIDRule[m_iAidRuleIndex]);
}

void CDlgVcaAidRuleCfg::GetAidRuleFromWnd(NET_DVR_AID_RULECFG &struAidRule)
{
    struAidRule.byPicProType = m_comboProPicType.GetCurSel(); //Get actions for alarm
    struAidRule.struPictureParam.wPicSize = m_comboResolution.GetCurSel();//image resolution
    struAidRule.struPictureParam.wPicQuality = m_comboPicQuality.GetCurSel();//image quality
    
    GetOneAidRuleFromWnd(struAidRule.struOneAIDRule[m_iAidRuleIndex]);
 
}
void CDlgVcaAidRuleCfg::SetOneAidRuleToWnd(NET_DVR_ONE_AID_RULE const &struOneAidRule)
{
    m_bEnable = struOneAidRule.byEnable;
    m_csRuleName = struOneAidRule.byRuleName;
    SetAidTypeToWnd(struOneAidRule.dwEventType);
    SetAidParamToWnd(struOneAidRule.struAIDParam);
    m_comboWeekday.SetCurSel(0);
//    OnSelchangeComboweekday();
	m_iHour11 = struOneAidRule.struAlarmTime[0][0].byStartHour;
    m_iMin11 = struOneAidRule.struAlarmTime[0][0].byStartMin;
    m_iHour12 = struOneAidRule.struAlarmTime[0][0].byStopHour;
    m_iMin12 = struOneAidRule.struAlarmTime[0][0].byStopMin;
    m_iHour21 = struOneAidRule.struAlarmTime[0][1].byStartHour;
    m_iMin21 = struOneAidRule.struAlarmTime[0][1].byStartMin;
    m_iHour22 = struOneAidRule.struAlarmTime[0][1].byStopHour;
    m_iMin22 = struOneAidRule.struAlarmTime[0][1].byStopMin;
    SetHandleToWnd(struOneAidRule.struHandleType);
    SetSizeFilterToWnd(struOneAidRule.struSizeFilter);

    for (int i = 0; i < m_iChannelnumber; i++ )
    {
        m_listRecordChan.SetCheck(i, FALSE);
        if (struOneAidRule.byRelRecordChan[i])
        {
            m_listRecordChan.SetCheck(i, TRUE);
        }
    }
	UpdateData(FALSE);
}

void CDlgVcaAidRuleCfg::GetOneAidRuleFromWnd(NET_DVR_ONE_AID_RULE &struOneAidRule)
{
    struOneAidRule.byEnable = m_bEnable;
    strncpy((char*)struOneAidRule.byRuleName, m_csRuleName.GetBuffer(0), sizeof(struOneAidRule.byRuleName));
    GetAidTypeFromWnd(struOneAidRule.dwEventType);
    GetAidParamFromWnd(struOneAidRule.struAIDParam);
    int i = m_comboWeekday.GetCurSel();
    GetSchedTimeFromWnd(struOneAidRule.struAlarmTime[i]);
    GetHandleFromWnd(struOneAidRule.struHandleType);
    GetSizeFilterFromWnd(struOneAidRule.struSizeFilter);

    for (i = 0; i < m_iChannelnumber; i++)
    {
        struOneAidRule.byRelRecordChan[i] = (BYTE)m_listRecordChan.GetCheck(i);
    }
    memcpy(&struOneAidRule.struPolygon, &m_struVcaPolygon[m_iAidRuleIndex], sizeof(struOneAidRule.struPolygon));
    
    //     m_bEnable = struOneAidRule.byEnable;
    //     m_csRuleName = struOneAidRule.byRuleName;
    //     SetAidTypeToWnd(struOneAidRule.dwEventType);
    //     SetAidParamToWnd(struOneAidRule.struAIDParam);
    //     m_comboWeekday.SetCurSel(0);
    //     OnSelchangeComboweekday();
    //     SetHandleToWnd(struOneAidRule.struHandleType);
    //     
    //     for (int i = 0; i < m_iChannelnumber; i++ )
    //     {
    //         if (struOneAidRule.byRelRecordChan[i])
    //         {
    //             m_listRecordChan.SetCheck(i);
    //         }
    //     }
}
//void CDlgVcaAidRuleCfg:GetOneAidRuleFromWnd(NET_DVR_On)
void CDlgVcaAidRuleCfg::SetAidParamToWnd(NET_DVR_AID_PARAM const &struAidParam)
{
    m_iParking = struAidParam.wParkingDuration;
    m_iPedestrian = struAidParam.wPedestrianDuration;
    m_iDebris = struAidParam.wDebrisDuration;
    m_iCongestionLength = struAidParam.wCongestionLength;
    m_iCongestionDuration = struAidParam.wCongestionDuration;
    m_iInverseDuration = struAidParam.wInverseDuration;
    m_iInverseDistance = struAidParam.wInverseDistance;
    m_iInverseAngle = struAidParam.wInverseAngleTolerance;
}

void CDlgVcaAidRuleCfg::GetAidParamFromWnd(NET_DVR_AID_PARAM& struAidParam)
{
    struAidParam.wParkingDuration = m_iParking;
    struAidParam.wPedestrianDuration = m_iPedestrian;
    struAidParam.wDebrisDuration = m_iDebris;
    struAidParam.wCongestionLength = m_iCongestionLength;
    struAidParam.wCongestionDuration = m_iCongestionDuration;
    struAidParam.wInverseDuration = m_iInverseDuration;
    struAidParam.wInverseDistance = m_iInverseDistance;
    struAidParam.wInverseAngleTolerance = m_iInverseAngle;
}

void CDlgVcaAidRuleCfg::SetAidTypeToWnd(DWORD dwEventType)
{
    for (int i = 0; i < m_listAIDType.GetItemCount(); i++)
    {
        m_listAIDType.SetCheck(i, FALSE);
        
        if ((m_struAIDOneRule.dwEventType & m_listAIDType.GetItemData(i)) != 0)
        {
            m_listAIDType.SetCheck(i, TRUE);
        }
    }
}

void CDlgVcaAidRuleCfg::GetAidTypeFromWnd(DWORD &dwAidEventType)
{
    dwAidEventType = 0;
    for (int i = 0; i < m_listAIDType.GetItemCount(); i++)
    {
        if (m_listAIDType.GetCheck(i))
        {
            dwAidEventType += m_listAIDType.GetItemData(i);
        }
    }
}

void CDlgVcaAidRuleCfg::SetSchedTimeToWnd(NET_DVR_SCHEDTIME* pSchedTime)
{
    m_iHour11 = pSchedTime[0].byStartHour;
    m_iMin11 = pSchedTime[0].byStartMin;
    m_iHour12 = pSchedTime[0].byStopHour;
    m_iMin12 = pSchedTime[0].byStopMin;
    m_iHour21 = pSchedTime[1].byStartHour;
    m_iMin21 = pSchedTime[1].byStartMin;
    m_iHour22 = pSchedTime[1].byStopHour;
    m_iMin22 = pSchedTime[1].byStopMin;
}

void CDlgVcaAidRuleCfg::GetSchedTimeFromWnd(NET_DVR_SCHEDTIME* pSchedTime)
{
    int i = m_comboWeekday.GetCurSel();	
    pSchedTime[0].byStartHour = (BYTE)m_iHour11;
    pSchedTime[0].byStartMin = (BYTE)m_iMin11;
    pSchedTime[0].byStopHour = (BYTE)m_iHour12;
    pSchedTime[0].byStopMin = (BYTE)m_iMin12;
    pSchedTime[1].byStartHour = (BYTE)m_iHour21;
    pSchedTime[1].byStartMin = (BYTE)m_iMin21;
    pSchedTime[1].byStopHour = (BYTE)m_iHour22;
	pSchedTime[1].byStopMin = (BYTE)m_iMin22;
}

void CDlgVcaAidRuleCfg::SetHandleToWnd(NET_DVR_HANDLEEXCEPTION_V30 const &struHandleException)
{
    m_bHandleType1 = (struHandleException.dwHandleType) &0x01;
    m_bHandleType2 = (struHandleException.dwHandleType>>1)&0x01;
    m_bHandleType3 = (struHandleException.dwHandleType>>2)&0x01;
    m_bHandleType4 = (struHandleException.dwHandleType>>3)&0x01;
    m_bHandleType5 = (struHandleException.dwHandleType>>4)&0x01;
    
    for (int i = 0; i < m_dwAlarmOutNum; i++ )
    {
        if (struHandleException.byRelAlarmOut[i])
        {
            m_listAlarmOut.SetCheck(i);
        }
    }

    m_listAlarmOut.EnableWindow(m_bHandleType4);
	

}

void CDlgVcaAidRuleCfg::GetHandleFromWnd(NET_DVR_HANDLEEXCEPTION_V30 &struHandleException)
{
    struHandleException.dwHandleType = 0;
    struHandleException.dwHandleType |= (m_bHandleType1 << 0);
    struHandleException.dwHandleType |= (m_bHandleType2 << 1);
    struHandleException.dwHandleType |= (m_bHandleType3 << 2);
    struHandleException.dwHandleType |= (m_bHandleType4 << 3);
    struHandleException.dwHandleType |= (m_bHandleType5 << 4);
    
    for (DWORD i = 0; i < m_dwAlarmOutNum; i++)
    {
        struHandleException.byRelAlarmOut[i] = (BYTE)m_listAlarmOut.GetCheck(i);
    }
}

void CDlgVcaAidRuleCfg::SetSizeFilterToWnd(const NET_VCA_SIZE_FILTER &struSizeFilter)
{
    m_bFilterActive = struSizeFilter.byActive;

    m_comboFilterMode.SetCurSel(struSizeFilter.byMode);
    EnableFilterModeWnd(struSizeFilter.byMode);
    m_fMinHeight = struSizeFilter.struMiniRect.fHeight;
    m_fMinWidth = struSizeFilter.struMiniRect.fWidth;
    m_fMaxHeight = struSizeFilter.struMaxRect.fHeight;
    m_fMaxWidth = struSizeFilter.struMaxRect.fWidth;
}

void CDlgVcaAidRuleCfg::EnableFilterModeWnd(BYTE byMode)
{
    BOOL bEnable = FALSE;
    if (IMAGE_PIX_MODE == byMode)
    {
        bEnable = FALSE;
    }
    else if (REAL_WORLD_MODE == byMode)
    {
        bEnable = TRUE;
    }

    GetDlgItem(IDC_EDIT_MIN_WIDTH)->EnableWindow(bEnable);
    GetDlgItem(IDC_EDIT_MIN_HEIGHT)->EnableWindow(bEnable);
    GetDlgItem(IDC_EDIT_MAX_WIDTH)->EnableWindow(bEnable);
    GetDlgItem(IDC_EDIT_MAX_HEIGHT)->EnableWindow(bEnable);
}


void CDlgVcaAidRuleCfg::GetSizeFilterFromWnd(NET_VCA_SIZE_FILTER &struSizeFilter)
{
    struSizeFilter.byActive = m_bFilterActive;
    struSizeFilter.byMode = m_comboFilterMode.GetCurSel();
    if (REAL_WORLD_MODE == struSizeFilter.byMode)
    {
        struSizeFilter.struMiniRect.fHeight = m_fMinHeight;
        struSizeFilter.struMiniRect.fWidth = m_fMinWidth;
        struSizeFilter.struMaxRect.fHeight = m_fMaxHeight;
        struSizeFilter.struMaxRect.fWidth = m_fMaxWidth;
    }
}

void CDlgVcaAidRuleCfg::OnSelchangeComboAidRuleIndex() 
{
	UpdateData(TRUE);
    m_iAidRuleIndex = m_comboAidRuleIndex.GetCurSel();
    m_bNeedRedraw[m_iAidRuleIndex] = TRUE;//Draw polygon
    memcpy(&m_struAIDOneRule, &m_struAIDRuleCfg.struOneAIDRule[m_iAidRuleIndex], sizeof(m_struAIDOneRule));
    SetOneAidRuleToWnd(m_struAIDOneRule);
    UpdateData(FALSE);
    
}

void CDlgVcaAidRuleCfg::OnTimeOk() 
{
    UpdateData(TRUE);
    if (!F_TimeTest())
    {
        return;
    }
    int	i = m_comboWeekday.GetCurSel();	
    GetSchedTimeFromWnd(m_struAIDOneRule.struAlarmTime[i]);	
}

BOOL CDlgVcaAidRuleCfg::F_TimeTest()
{
    int i, j;
    WORD wStartTime[4], wStopTime[4];
    
    UpdateData(TRUE);
    if( (m_iHour11 < 0) || (m_iHour11 > 24) || (m_iHour12 < 0) || (m_iHour12 > 24) ||	\
        (m_iHour21 < 0) || (m_iHour21 > 24) || (m_iHour22 < 0) || (m_iHour22 > 24) )
    {
        AfxMessageBox("Hours range 0 - 24 !");
        return FALSE;
    }
    if( (m_iMin11 < 0) || (m_iMin11 > 60) || (m_iMin12 < 0) || (m_iMin12 > 60) ||	\
        (m_iMin21 < 0) || (m_iMin21 > 60) || (m_iMin22 < 0) || (m_iMin22 > 60) )
    {
        AfxMessageBox("Minute range 0 - 60!");
        return FALSE;
    }
    wStartTime[0] = (WORD)(m_iHour11 * 100 + m_iMin11);
    wStartTime[1] = (WORD)(m_iHour21 * 100 + m_iMin21);
    wStopTime[0] = (WORD)(m_iHour12 * 100 + m_iMin12);
    wStopTime[1] = (WORD)(m_iHour22 * 100 + m_iMin22);
    for(i = 0; i < MAX_TIMESEGMENT_2; i++)
    {
        if( (wStartTime[i] > 2400) || (wStopTime[i] > 2400) )
        {
            char szLan[128] = {0};
            g_StringLanType(szLan, "布防时间不能超过24:00", "Fortify time can not be more than 24:00");
            AfxMessageBox(szLan);
            return FALSE;
        }
        if(wStartTime[i] > wStopTime[i])
        {
            char szLan[128] = {0};
            g_StringLanType(szLan, "布防起始时间不能大于停止时间", "Fortify start time can not be larger than the record to stop time");
            AfxMessageBox(szLan);
            return FALSE;
        }
        for(j = 0; j < MAX_TIMESEGMENT_2; j++)
        {
            if (i == j)
                continue;
            if( (wStartTime[i] > wStartTime[j]) && (wStartTime[i] < wStopTime[j]) ||	\
                (wStopTime[i] > wStartTime[j]) && (wStopTime[i] < wStopTime[j]) )
            {
                char szLan[128] = {0};
                g_StringLanType(szLan, "布防时间段不能重复!","Fortify time period can not be repeated!");
                AfxMessageBox(szLan);
                return FALSE;
            }
        }
    }
    return TRUE;
}

void CDlgVcaAidRuleCfg::OnTimeCopy() 
{
    UpdateData(TRUE);
    int j,k;
    int i = m_comboWeekday.GetCurSel();
    int m_nCopyTime = m_comboCopyTime.GetCurSel() - 1;
    
    if(m_nCopyTime == -1)
    {
        for(j=0; j<MAX_DAYS; j++)
        {
            if(j == i)
                continue;
            for(k=0; k<MAX_TIMESEGMENT_2; k++)
            {
                memcpy(&(m_struAIDOneRule.struAlarmTime[j][k]), &(m_struAIDOneRule.struAlarmTime[i][k]), sizeof(NET_DVR_SCHEDTIME));
            }
        }
    }
    else
    {
        for(k=0; k<MAX_TIMESEGMENT_2; k++)
        {
            memcpy(&(m_struAIDOneRule.struAlarmTime[m_nCopyTime][k]), &(m_struAIDOneRule.struAlarmTime[i][k]), sizeof(NET_DVR_SCHEDTIME));
        }
    }
}

void CDlgVcaAidRuleCfg::OnSelchangeComboweekday() 
{
	UpdateData(TRUE);
	int i = m_comboWeekday.GetCurSel();
    SetSchedTimeToWnd(m_struAIDOneRule.struAlarmTime[i]);
	UpdateData(FALSE);
}

void CDlgVcaAidRuleCfg::OnSelchangeCombocopytime() 
{
	
}

void CDlgVcaAidRuleCfg::OnBtnOneRuleConfirm() 
{
    UpdateData(TRUE);
    GetOneAidRuleFromWnd(m_struAIDOneRule);
    memcpy(&m_struAIDRuleCfg.struOneAIDRule[m_iAidRuleIndex], &m_struAIDOneRule, sizeof(m_struAIDOneRule));
}

LONG CDlgVcaAidRuleCfg::StartPlay()
{
    GetPuStreamCfg(m_struPuStream);

    NET_DVR_DEVICEINFO_V30 struDeviceInfo = {0};
    
    m_lPUServerID = NET_DVR_Login_V30(m_struPuStream.struDevChanInfo.struIP.sIpV4, m_struPuStream.struDevChanInfo.wDVRPort,
        (char*)m_struPuStream.struDevChanInfo.sUserName, (char*)m_struPuStream.struDevChanInfo.sPassword, &struDeviceInfo);
    if (m_lPUServerID < 0)
    {
        AfxMessageBox("Fail to login front device");
        return m_lPUServerID;
    }
    
    NET_DVR_CLIENTINFO struPlay;
    struPlay.hPlayWnd 	= GetDlgItem(IDC_PLAYWND)->GetSafeHwnd();
    struPlay.lChannel 	= m_struPuStream.struDevChanInfo.byChannel; 
    struPlay.lLinkMode 	= 0;
    struPlay.sMultiCastIP = "";	

    m_lPlayHandle = NET_DVR_RealPlay_V30(m_lPUServerID, &struPlay, NULL, NULL, TRUE); 
    
    BOOL bRet = FALSE;
    if (m_lPlayHandle < 0)
    {
        g_pMainDlg->AddLog(-1, OPERATION_FAIL_T, "NET_DVR_RealPlay_V30");
        AfxMessageBox("NET_DVR_RealPlay_V30 FAIL");		
    }
    else
    {
        g_pMainDlg->AddLog(-1, OPERATION_SUCC_T, "NET_DVR_RealPlay_V30");
        bRet = NET_DVR_RigisterDrawFun(m_lPlayHandle, g_DrawAidRule, 0);//DC Draw callback
    }
    return m_lPlayHandle;
}

BOOL CDlgVcaAidRuleCfg::StopPlay()
{
    if (m_lPlayHandle >= 0)
    {
        NET_DVR_StopRealPlay(m_lPlayHandle);
        m_lPlayHandle = -1;
    }
    
    if (m_lPUServerID >= 0)
    {
        NET_DVR_Logout_V30(m_lPUServerID);
        m_lPUServerID = -1;
    }
    return TRUE;
}


void CDlgVcaAidRuleCfg::PostNcDestroy() 
{
    StopPlay();
    g_pDlgVcaAidRule = NULL;
    
	CDialog::PostNcDestroy();
}

void CDlgVcaAidRuleCfg::F_DrawFun(long lPlayHandle, HDC hDc, DWORD dwUser)
{
    
    DRAW_POLYGON_PARAM struDrawPolygon;
    memset(&struDrawPolygon, 0, sizeof(struDrawPolygon));
    struDrawPolygon.color = RGB(255, 255, 0);
    memcpy(&struDrawPolygon.rcWnd, &m_rcWnd, sizeof(struDrawPolygon.rcWnd));
    memcpy(&struDrawPolygon.struVcaPolygon, &m_struVcaPolygon[m_iAidRuleIndex], sizeof(struDrawPolygon.struVcaPolygon));
    struDrawPolygon.bCloseIn = m_bCloseIn[m_iAidRuleIndex];
    struDrawPolygon.bMouseMove = m_bMouseMove[m_iAidRuleIndex];
    strncpy(struDrawPolygon.chName, (char*)m_struAIDRuleCfg.struOneAIDRule[m_iAidRuleIndex].byRuleName, sizeof(struDrawPolygon.chName));
    CDrawFun::DrawVcaPolygon(hDc, &struDrawPolygon);
    
    if (m_bFilterActive)
    {
        DRAW_RECT_PARAM struDrawRect;
        memset(&struDrawRect, 0, sizeof(struDrawRect));
        struDrawRect.color = RGB(0, 255, 125);
        memcpy(&struDrawRect.rcWnd, &m_rcWnd, sizeof(struDrawRect.rcWnd));
        memcpy(&struDrawRect.struVcaRect, &m_struAIDOneRule.struSizeFilter.struMaxRect, sizeof(struDrawRect.struVcaRect));
        CDrawFun::DrawVcaRect(hDc, &struDrawRect);

        memset(&struDrawRect, 0, sizeof(struDrawRect));
        struDrawRect.color = RGB(0, 255, 125);
        memcpy(&struDrawRect.rcWnd, &m_rcWnd, sizeof(struDrawRect.rcWnd));
        memcpy(&struDrawRect.struVcaRect, &m_struAIDOneRule.struSizeFilter.struMiniRect, sizeof(struDrawRect.struVcaRect));
        CDrawFun::DrawVcaRect(hDc, &struDrawRect);

    }

    DrawLane(hDc);
}

void CDlgVcaAidRuleCfg::DrawLane(HDC hDc)
{
    DRAW_POLYGON_PARAM struPolygonParam;
    memset(&struPolygonParam, 0, sizeof(struPolygonParam));
    
    DRAW_DIRECTION_PARAM struDirectionParam;
    memset(&struPolygonParam, 0, sizeof(struPolygonParam));
    
    for (int i = 0; i < MAX_LANE_NUM; i++)
    {
        struPolygonParam.color = RGB(255,255,0);
        struDirectionParam.color = RGB(255,255,0);

        struPolygonParam.bCloseIn = TRUE;
        struPolygonParam.bMouseMove = FALSE;
        memcpy(&struPolygonParam.rcWnd, &m_rcWnd, sizeof(m_rcWnd));
        memcpy(&struPolygonParam.struVcaPolygon, &m_struLaneCfg.struLane[i].struPolygon, sizeof(struPolygonParam.struVcaPolygon));
        strncpy(struPolygonParam.chName, (char*)m_struLaneCfg.struLane[i].byLaneName, sizeof(struPolygonParam.chName));
        CDrawFun::DrawVcaPolygon(hDc, &struPolygonParam);

        memcpy(&struDirectionParam.rcWnd, &m_rcWnd, sizeof(struDirectionParam.rcWnd));
        memcpy(&struDirectionParam.struDirection, &m_struLaneCfg.struLane[i].struFlowDirection, sizeof(struDirectionParam.struDirection));
        CDrawFun::DrawDirection(hDc, &struDirectionParam);
    }
}

void CDlgVcaAidRuleCfg::OnCheckFilterActive() 
{
    UpdateData(TRUE);
    GetDlgItem(IDC_CHECK_SET_MAX_FILTER)->EnableWindow(m_bFilterActive);
    GetDlgItem(IDC_CHECK_SET_MINI_FILTER)->EnableWindow(m_bFilterActive);
}

void CDlgVcaAidRuleCfg::OnChkDrawPolygon() 
{
    UpdateData(TRUE);	
}

void CDlgVcaAidRuleCfg::OnSelchangeComboFilterMode() 
{
    BYTE byMode = m_comboFilterMode.GetCurSel();
    EnableFilterModeWnd(byMode);
    UpdateData(FALSE);
}

void CDlgVcaAidRuleCfg::OnCheckSetMiniFilter() 
{
	// TODO: Add your control notification handler code here
    UpdateData(TRUE);
    if (m_bSetMiniFilter)
    {
        m_bSetMaxFilter = FALSE;
        m_bDrawPolygon = FALSE;
        UpdateData(FALSE);
	}
}

void CDlgVcaAidRuleCfg::OnCheckSetMaxFilter() 
{
    UpdateData(TRUE);
    if (m_bSetMaxFilter)
    {
        m_bSetMiniFilter = FALSE;
        m_bDrawPolygon = FALSE;
        UpdateData(FALSE);
	}
}

BOOL CDlgVcaAidRuleCfg::GetPuStreamCfg(NET_DVR_PU_STREAM_CFG &struPUStream)
{
    DWORD dwReturn = 0;
    if (NET_DVR_GetDVRConfig(m_lServerID, NET_DVR_GET_PU_STREAMCFG,m_lChannel, &struPUStream, sizeof(struPUStream), &dwReturn))
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_PU_STREAMCFG");
        return TRUE;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_PU_STREAMCFG");
        return FALSE;
    }
}

