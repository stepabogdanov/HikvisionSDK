// DlgPlayMotion.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgPlayMotion.h"
#include "resource.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
int g_dwPrecision = 16;
CDlgPlayMotion *g_PlayMotion = NULL;
/////////////////////////////////////////////////////////////////////////////
// CDlgPlayMotion dialog
void CALLBACK DrawSearchMotionArea(LONG lRealHandle, HDC hDc, DWORD dwUser)
{
   CRect rect;
    int i = 0,j = 0;
    CPoint point;
    for (i = 0;i<18;i++)
    {
        for (j = 0;j<22;j++)
        {
            if (g_PlayMotion->m_struSmartSearch.byMotionScope[i][j] == 1)
            {
                point.x = j*g_dwPrecision;
                point.y = i*g_dwPrecision;
                rect.left = point.x;
                rect.top = point.y;
                rect.right = point.x + g_dwPrecision;
                rect.bottom = point.y + g_dwPrecision;
                ::DrawEdge(hDc, &rect, BDR_SUNKENOUTER, BF_RECT);
            }
        }
    }
	SetBkMode(hDc,TRANSPARENT);
}


DWORD  GetMotionInfoThread(LPVOID pParam)
{
    CDlgPlayMotion *pPlayMotion = (CDlgPlayMotion*)pParam;

   
    NET_DVR_SMART_SEARCH_RET struSmartSearchRet = {0};
    long nStatus = -1; 
    char szLan[128] = {0};
    
    pPlayMotion->m_listMotionTime.DeleteAllItems();
    int nItemIndex = 0;
    while (1)
    {
        nStatus = NET_DVR_SearchNextInfo(pPlayMotion->m_lSearchHandle, &struSmartSearchRet);
        CString str = "";
    
        if (-1 == nStatus)
        {
            g_StringLanType(szLan, "查找失败", "Fail to search");
            str = szLan;
            break;
        }
        else if (NET_DVR_FILE_SUCCESS == nStatus)
        {
            char chStartTime[128] = {0};
            char chStopTime[128] = {0};
            sprintf(chStartTime, "%04d%02d%02d%02d%02d%02d",struSmartSearchRet.struStartTime.dwYear, 
                struSmartSearchRet.struStartTime.dwMonth, struSmartSearchRet.struStartTime.dwDay,
                struSmartSearchRet.struStartTime.dwHour, struSmartSearchRet.struStartTime.dwMinute, 
                struSmartSearchRet.struStartTime.dwSecond);
            sprintf(chStopTime, "%04d%02d%02d%02d%02d%02d", struSmartSearchRet.struEndTime.dwYear, struSmartSearchRet.struEndTime.dwMonth, 
                struSmartSearchRet.struEndTime.dwDay, struSmartSearchRet.struEndTime.dwHour, struSmartSearchRet.struEndTime.dwMinute, 
                struSmartSearchRet.struEndTime.dwSecond);
            
            char chCount[256]= {0};
            sprintf(chCount, "%d", nItemIndex+1);
            pPlayMotion->m_listMotionTime.InsertItem(nItemIndex, chCount, 0);
            pPlayMotion->m_listMotionTime.SetItemText(nItemIndex, 1,chStartTime);
            pPlayMotion->m_listMotionTime.SetItemText(nItemIndex, 2, chStopTime );
            TRACE("StartTime:Y[%d]M[%d]D[%d]H[%d]M[%d]S[%d]  EndTime:Y[%d]M[%d]D[%d]H[%d]M[%d]S[%d]\n",
                struSmartSearchRet.struStartTime.dwYear, struSmartSearchRet.struStartTime.dwMonth, struSmartSearchRet.struStartTime.dwDay,
                struSmartSearchRet.struStartTime.dwHour, struSmartSearchRet.struStartTime.dwMinute, struSmartSearchRet.struStartTime.dwSecond,
                struSmartSearchRet.struEndTime.dwYear, struSmartSearchRet.struEndTime.dwMonth, struSmartSearchRet.struEndTime.dwDay,
                struSmartSearchRet.struEndTime.dwHour, struSmartSearchRet.struEndTime.dwMinute, struSmartSearchRet.struEndTime.dwSecond
                );
            g_StringLanType(szLan, "获取到文件信息", "Access to file information");
            str = szLan;
            nItemIndex++;
        }
        else if (NET_DVR_ISFINDING == nStatus)
        {
            g_StringLanType(szLan, "正在查找", "searching");
            str = szLan;
        }
        else if (NET_DVR_NOMOREFILE == nStatus)
        {
            g_StringLanType(szLan, "查找时没有更多文件", "search end");
            str = szLan;
            AfxMessageBox(szLan);
            break;
        }
        else if (NET_DVR_FILE_EXCEPTION == nStatus)
        {
            g_StringLanType(szLan, "查找文件时异常", "search exception");
            str = szLan;
            break;
        }
        else if (NET_DVR_FILE_NOFIND == nStatus)
        {
            g_StringLanType(szLan, "没有查找到文件", "search nothing");
            str = szLan;
            AfxMessageBox(szLan);
            break;
        }
        else
        {
            g_StringLanType(szLan, "查找错误", "search error");
            str = szLan;
            break;
        }
        g_PlayMotion->GetDlgItem(IDC_STATIC_MOTION_SEARCH_STATE)->SetWindowText(str);
        
    }
    
    if (!NET_DVR_StopSearch(pPlayMotion->m_lSearchHandle))
    {

    }
    return 1;
}

CDlgPlayMotion::CDlgPlayMotion(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgPlayMotion::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgPlayMotion)
	m_ctDateStart = 0;
	m_ctDateStop = 0;
	m_ctTimeStart = 0;
	m_ctTimeStop = 0;
	m_iTime = 0;
	//}}AFX_DATA_INIT
    m_hFindThread = NULL;
    m_lServerID = -1;
    m_lChannel = -1;
    m_iDevIndex = -1;
    memset(&m_struSmartSearch, 0, sizeof(m_struSmartSearch));
    m_lSearchHandle = -1;
    m_lRealPlayHandle = -1;
    m_lPlayBackHandle = -1;
    m_iDrawingIndex = -1;
    memset(m_bMouseMove, 0, sizeof(m_bMouseMove));
    memset(m_struRect, 0, sizeof(m_struRect));
    memset(m_bDrawed, 0, sizeof(m_bDrawed));
    memset(&m_struStartTime, 0, sizeof(m_struStartTime)) ;
    memset(&m_struStopTime, 0, sizeof(m_struStopTime));
    m_iItemSel = -1;
}


void CDlgPlayMotion::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgPlayMotion)
	DDX_Control(pDX, IDC_LIST_MOTION_TIME, m_listMotionTime);
	DDX_Control(pDX, IDC_COMBO_SEARCH_SENSE, m_comboSearchSense);
	DDX_DateTimeCtrl(pDX, IDC_COMBO_REMOTE_DATE_START, m_ctDateStart);
	DDX_DateTimeCtrl(pDX, IDC_COMBO_REMOTE_DATE_STOP, m_ctDateStop);
	DDX_DateTimeCtrl(pDX, IDC_COMBO_REMOTE_TIME_START, m_ctTimeStart);
	DDX_DateTimeCtrl(pDX, IDC_COMBO_REMOTE_TIME_STOP, m_ctTimeStop);
	DDX_Text(pDX, IDC_EDIT_TIME, m_iTime);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgPlayMotion, CDialog)
	//{{AFX_MSG_MAP(CDlgPlayMotion)
	ON_BN_CLICKED(IDC_BTN_MOTION_SEARCH, OnBtnMotionSearch)
	ON_BN_CLICKED(IDC_BTN_PREVIEW, OnBtnPreview)
	ON_NOTIFY(NM_CLICK, IDC_LIST_MOTION_TIME, OnClickListMotionTime)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_MOTION_TIME, OnDblclkListMotionTime)
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgPlayMotion message handlers

void CDlgPlayMotion::OnBtnMotionSearch() 
{
    UpdateData(TRUE);
    m_struSmartSearch.struStartTime.dwYear = (WORD)m_ctDateStart.GetYear();
    m_struSmartSearch.struStartTime.dwMonth = (WORD)m_ctDateStart.GetMonth();
    m_struSmartSearch.struStartTime.dwDay = (WORD)m_ctDateStart.GetDay();
    m_struSmartSearch.struStartTime.dwHour = (char)m_ctTimeStart.GetHour();
    m_struSmartSearch.struStartTime.dwMinute = (char)m_ctTimeStart.GetMinute();
    m_struSmartSearch.struStartTime.dwSecond = (char)m_ctTimeStart.GetSecond();
    m_struSmartSearch.struEndTime.dwYear = (WORD)m_ctDateStop.GetYear();
    m_struSmartSearch.struEndTime.dwMonth = (WORD)m_ctDateStop.GetMonth();
    m_struSmartSearch.struEndTime.dwDay = (WORD)m_ctDateStop.GetDay();
    m_struSmartSearch.struEndTime.dwHour = (char)m_ctTimeStop.GetHour();
    m_struSmartSearch.struEndTime.dwMinute = (char)m_ctTimeStop.GetMinute();
    m_struSmartSearch.struEndTime.dwSecond = (char)m_ctTimeStop.GetSecond();


    m_struSmartSearch.byChan = (BYTE)m_lChannel;
    m_struSmartSearch.bySensitivity = m_comboSearchSense.GetCurSel()+1;

    m_lSearchHandle =  NET_DVR_SmartSearch(m_lServerID, &m_struSmartSearch);
    
    if (-1 == m_lSearchHandle)
    {
        MessageBox("Fail to search");
        return;
    }

    
    if (m_hFindThread == NULL)
    {
        m_hFindThread = CreateThread(NULL,0,LPTHREAD_START_ROUTINE(GetMotionInfoThread),this,0,NULL);
    }
    
    if (m_hFindThread != NULL)
    {
        CloseHandle(m_hFindThread);
        m_hFindThread = NULL;
    }
}

BOOL CDlgPlayMotion::OnInitDialog() 
{
	CDialog::OnInitDialog();

    for (int i =0 ; i < MOTION_NUM; i++)
    {
        m_bMouseMove[i] = FALSE;
        m_bDrawed[i] = FALSE;
    }

    CRect rc(0, 0, 0, 0);
    GetParent()->GetClientRect(&rc);
    ((CTabCtrl*)GetParent())->AdjustRect(FALSE, &rc);
    MoveWindow(&rc);

    CRect rcMotion(0, 0, 0, 0);
    GetDlgItem(IDC_PIC_MOTION_DETECT)->GetWindowRect(&rcMotion);
    ScreenToClient(&rcMotion);
    rcMotion.right = rcMotion.left + 16*22;
    rcMotion.bottom = rcMotion.top + 16*18;
    GetDlgItem(IDC_PIC_MOTION_DETECT)->MoveWindow(rcMotion);

    CTime timeCur = CTime::GetCurrentTime();
    CTime timeStart(timeCur.GetYear(),timeCur.GetMonth(),timeCur.GetDay(),0,0,0);
    CTime timeStop(timeCur.GetYear(),timeCur.GetMonth(),timeCur.GetDay(),23,59,59);
    m_ctDateStart = timeStart;
    m_ctTimeStart = timeStart;
    m_ctDateStop = timeStop;
    m_ctTimeStop = timeStop;

    m_comboSearchSense.SetCurSel(1); 

    int nIndex = 0;
    m_listMotionTime.SetExtendedStyle(m_listMotionTime.GetExtendedStyle() | LVS_EX_FULLROWSELECT);
    char szLan[128] = {0};
    g_StringLanType(szLan, "序号","Index");
    m_listMotionTime.InsertColumn(nIndex, szLan,LVCFMT_LEFT, 50, -1);
    nIndex++;
    g_StringLanType(szLan, "开始时间", "Start time");
    m_listMotionTime.InsertColumn(nIndex, szLan, LVCFMT_LEFT, 120, -1);
    nIndex++;
    g_StringLanType(szLan, "结束时间", "Stop Time");
    m_listMotionTime.InsertColumn(nIndex, szLan, LVCFMT_LEFT, 120, -1);
    nIndex++;

	int iChanIndex = g_pMainDlg->GetCurChanIndex();
    m_lChannel = g_struDeviceInfo[m_iDevIndex].struChanInfo[iChanIndex].iChannelNO;

    UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

long CDlgPlayMotion::StartPlay()
{
    NET_DVR_CLIENTINFO struClientInfo = {0};

    struClientInfo.hPlayWnd = GetDlgItem(IDC_PIC_MOTION_DETECT)->GetSafeHwnd();
    struClientInfo.lChannel = m_lChannel;
    struClientInfo.lLinkMode = 0;
    struClientInfo.sMultiCastIP = "";
    
    m_lRealPlayHandle = NET_DVR_RealPlay_V30(m_lServerID, &struClientInfo, NULL, NULL, TRUE);
    if (-1 == m_lRealPlayHandle)
    {
        AfxMessageBox("Fail to preview");
    }
    else
    {
        g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_RealPlay");
    }
     return m_lRealPlayHandle;
}

BOOL CDlgPlayMotion::StopPlay()
{
    BOOL bRet = TRUE;
    if (m_lRealPlayHandle >= 0)
    {
        bRet = NET_DVR_StopRealPlay(m_lRealPlayHandle);
        m_lRealPlayHandle = -1;

    }   
    return bRet;
}

void CDlgPlayMotion::PostNcDestroy() 
{
	// TODO: Add your specialized code here and/or call the base class
	StopPlay();
	CDialog::PostNcDestroy();
}

BOOL CDlgPlayMotion::PreTranslateMessage(MSG* pMsg) 
{
    CPoint pt(0,0);
    CRect  rcWnd(0,0,0,0);
    GetDlgItem(IDC_PIC_MOTION_DETECT)->GetWindowRect(&rcWnd);

	GetCursorPos(&pt);

    switch (pMsg->message)
    {
    case WM_LBUTTONDOWN:
        if (PtInRect(&rcWnd, pt) && (GetAsyncKeyState(VK_LCONTROL)<0 || GetAsyncKeyState(VK_RCONTROL)<0))
        {
            for (int nMotionIndex = 0; nMotionIndex < MOTION_NUM; nMotionIndex++)
            {
                if (m_bDrawed[nMotionIndex] == FALSE)
                {
                    //Get the Drawing Rect Index
                    m_iDrawingIndex = nMotionIndex;  
                    m_struRect[m_iDrawingIndex].fX = (float)(pt.x-rcWnd.left)/(float)rcWnd.Width();
                    m_struRect[m_iDrawingIndex].fY = (float)(pt.y-rcWnd.top)/(float)rcWnd.Height();
                    m_bMouseMove[m_iDrawingIndex] = TRUE;
                    TRACE("m_struRect.fX =%f m_struRect.fY =%f\n", m_struRect[m_iDrawingIndex].fX,m_struRect[m_iDrawingIndex].fY);
                    break;
                }
            }
        }
        break;
    case WM_LBUTTONUP:
        if (PtInRect(&rcWnd, pt) && (GetAsyncKeyState(VK_LCONTROL)<0 || GetAsyncKeyState(VK_RCONTROL)<0))
        {
            m_bMouseMove[m_iDrawingIndex] = FALSE;
            m_bDrawed[m_iDrawingIndex] = TRUE;
            break;
        }
        break;
    case WM_MOUSEMOVE:
        if (PtInRect(&rcWnd, pt)  && m_bMouseMove[m_iDrawingIndex] && (GetAsyncKeyState(VK_LCONTROL)<0 || GetAsyncKeyState(VK_RCONTROL)<0))
        {   
            m_struRect[m_iDrawingIndex].fWidth = (float)(pt.x-rcWnd.left)/(float)rcWnd.Width() -  m_struRect[m_iDrawingIndex].fX;
            m_struRect[m_iDrawingIndex].fHeight = (float)(pt.y-rcWnd.top)/(float)rcWnd.Height() -  m_struRect[m_iDrawingIndex].fY;
            
            
            TRACE("WM_MOUSEMOVE  MotionIndex[%d] fWidth[%f] fHeight[%f]\n", m_iDrawingIndex, m_struRect[m_iDrawingIndex].fWidth, m_struRect[m_iDrawingIndex].fHeight);
            
            for(int i = int(m_struRect[m_iDrawingIndex].fX * 22); i <= int((m_struRect[m_iDrawingIndex].fX +m_struRect[m_iDrawingIndex].fWidth)*22); i++)
            {
                for (int j = int(m_struRect[m_iDrawingIndex].fY*18); j <= int((m_struRect[m_iDrawingIndex].fY + m_struRect[m_iDrawingIndex].fHeight)*18); j++)
                {
                    m_struSmartSearch.byMotionScope[j][i] = 1;
                }
            }
            break;
        }
        break;
    case WM_RBUTTONDOWN:
        if (PtInRect(&rcWnd, pt) && (GetAsyncKeyState(VK_LCONTROL)<0 || GetAsyncKeyState(VK_RCONTROL)<0))
        {
            memset(&m_struRect, 0, sizeof(m_struRect));
            memset(m_struSmartSearch.byMotionScope, 0, sizeof(m_struSmartSearch.byMotionScope));
            for (int i = 0; i < MOTION_NUM; i++)
            {
                m_bDrawed[i] = FALSE;
                m_bMouseMove[i] = FALSE;
            }
        }
    }
	return CDialog::PreTranslateMessage(pMsg);
}

void CDlgPlayMotion::SetParentWnd(HWND *hhWnd, int iParentNum)
{

}

BOOL CDlgPlayMotion::CheckInitParam()
{
    g_PlayMotion = this;

    m_iDevIndex = g_pMainDlg->GetCurDeviceIndex();
    
    m_lServerID = g_struDeviceInfo[m_iDevIndex].lLoginID;
	int iChanIndex = g_pMainDlg->GetCurChanIndex();
    m_lChannel = g_struDeviceInfo[m_iDevIndex].struChanInfo[iChanIndex].iChannelNO;

    return TRUE;
}

void CDlgPlayMotion::OnBtnPreview() 
{
    if (m_lRealPlayHandle >= 0)
    {
        StopPlay();
        Invalidate();
    }
    else
    {
        StartPlay();
        if (m_lRealPlayHandle >= 0)
        {
            NET_DVR_RigisterDrawFun(m_lRealPlayHandle, DrawSearchMotionArea, 0);
        }
    }
}


void CDlgPlayMotion::OnClickListMotionTime(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
    POSITION  iPos = m_listMotionTime.GetFirstSelectedItemPosition();
    if (iPos == NULL)
    {
        return;
    }
    char szTime[32] = {0};
    char szTmp[8] = {0};
    int iOffset = 0;
    m_iItemSel = m_listMotionTime.GetNextSelectedItem(iPos);
    sprintf(szTime, "%s", m_listMotionTime.GetItemText(m_iItemSel, 1));
    memcpy(szTmp, szTime, 4);
    m_struStartTime.dwYear = atoi(szTmp);
    
    iOffset+=4;
    memset(szTmp, 0, 8);
    memcpy(szTmp, szTime+iOffset, 2);	
    m_struStartTime.dwMonth = atoi(szTmp);
    
    iOffset+=2;memset(szTmp, 0, 8);
    memcpy(szTmp, szTime+iOffset, 2);
    m_struStartTime.dwDay = atoi(szTmp);
    
    iOffset+=2;memset(szTmp, 0, 8);
    memcpy(szTmp, szTime+iOffset, 2);
    m_struStartTime.dwHour = atoi(szTmp);
    
    iOffset+=2;memset(szTmp, 0, 8);
    memcpy(szTmp, szTime+iOffset, 2);
    m_struStartTime.dwMinute = atoi(szTmp);
    
    iOffset+=2;memset(szTmp, 0, 8);
    memcpy(szTmp, szTime+iOffset, 2);
    m_struStartTime.dwSecond = atoi(szTmp);
    
    memset(szTime, 0, 32);
    sprintf(szTime, "%s", m_listMotionTime.GetItemText(m_iItemSel, 2));//stop time
    iOffset=0;memset(szTmp, 0, 8);
    memcpy(szTmp, szTime+iOffset, 4);
    m_struStopTime.dwYear = atoi(szTmp);
    
    iOffset+=4;memset(szTmp, 0, 8);
    memcpy(szTmp, szTime+iOffset, 2);
    m_struStopTime.dwMonth = atoi(szTmp);
    
    iOffset+=2;memset(szTmp, 0, 8);
    memcpy(szTmp, szTime+iOffset, 2);
    m_struStopTime.dwDay = atoi(szTmp);
    
    iOffset+=2;memset(szTmp, 0, 8);
    memcpy(szTmp, szTime+iOffset, 2);
    m_struStopTime.dwHour = atoi(szTmp);
    
    iOffset+=2;memset(szTmp, 0, 8);
    memcpy(szTmp, szTime+iOffset, 2);
    m_struStopTime.dwMinute = atoi(szTmp);
    
    iOffset+=2;memset(szTmp, 0, 8);
    memcpy(szTmp, szTime+iOffset, 2);
    m_struStopTime.dwSecond = atoi(szTmp);
	UpdateData(FALSE);
	*pResult = 0;
}

void CDlgPlayMotion::OnDblclkListMotionTime(NMHDR* pNMHDR, LRESULT* pResult) 
{
	BtnRemoteFileStop();
    BtnRemotFilePlay();

	*pResult = 0;
}

void CDlgPlayMotion::BtnRemoteFileStop()
{

}

void CDlgPlayMotion::BtnRemotFilePlay()
{
    StopPlay();
    if (m_lPlayBackHandle == -1)
    {
        PlayBack();
    }
}

extern BOOL ConvertTime(time_t *lpInBuf, LPNET_DVR_TIME pOutBuf, BOOL bInToOut);

void CDlgPlayMotion::PlayBack()
 {
    UpdateData(TRUE);
    
    int m_nVerifyret = -1;
    CString csFileName;
    int iFileSelPos = 0;
    HWND hPlayWnd=GetDlgItem(IDC_PIC_MOTION_DETECT)->GetSafeHwnd();
    POSITION  posItem = m_listMotionTime.GetFirstSelectedItemPosition();
    NET_DVR_TIME struStartTime,struStopTime;
    char szLan[128] = {0};
    
    //	remoteplay_info.srcfilename=m_szFileName;
    if (m_lPlayBackHandle >= 0)
    {
        if (NET_DVR_StopPlayBack(m_lPlayBackHandle))
        {
            g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_StopPlayBack");
        }
        m_lPlayBackHandle = -1;
        Sleep(400);
    }
    if (m_lPlayBackHandle == -1)
    {
        time_t tmp;
        m_iTime = 5;
        ConvertTime(&tmp, &m_struStartTime, FALSE);
        tmp -= m_iTime;
        ConvertTime(&tmp, &m_struStartTime, TRUE);
        ConvertTime(&tmp, &m_struStopTime, FALSE);
        tmp += m_iTime;
        ConvertTime(&tmp, &m_struStopTime, TRUE);
        memcpy(&struStartTime, &m_struStartTime, sizeof(NET_DVR_TIME));
        memcpy(&struStopTime, &m_struStopTime, sizeof(NET_DVR_TIME));	
        
        
        m_lPlayBackHandle = NET_DVR_PlayBackByTime(m_lServerID, m_lChannel, &struStartTime, &struStopTime, hPlayWnd);//NULL
        
        if (m_lPlayBackHandle== -1)
        {
            g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_PlayBackByTime ChanNum[%d]", m_lChannel);
            g_StringLanType(szLan, "远程回放失败", "Fail to play back remote");
            AfxMessageBox(szLan);
            return;
        }
        NET_DVR_GetPlayBackPlayerIndex(m_lPlayBackHandle);

        NET_DVR_PlayBackControl(m_lPlayBackHandle, NET_DVR_PLAYSTART, 0, NULL);

#if 1

        if (NET_DVR_PlayBackControl(m_lPlayBackHandle, NET_DVR_PLAYSTARTAUDIO, 0, NULL))
        {
//            m_bSound=TRUE;
            NET_DVR_PlayBackControl(m_lPlayBackHandle, NET_DVR_PLAYAUDIOVOLUME, (0xffff)/2, NULL);
  //          m_sliderVolume.SetPos(50);
//            ((CButton *)GetDlgItem(IDC_BTN_EVENT_FILE_SOUND))->SetIcon(m_hSoundStartIcon);
        }
        else
        {
//             m_bSound=FALSE;
//             ((CButton *)GetDlgItem(IDC_BTN_EVENT_FILE_SOUND))->SetIcon(m_hSoundStopIcon);
        }
#endif
        //SetPlayState();
        SetTimer(PLAYBYTIME_TIMER, 3000, NULL);
    }
    else
    {
//         if (m_bPause)
//         {
//             if (NET_DVR_PlayBackControl(m_lPlayBackHandle, NET_DVR_PLAYRESTART, 0, NULL))
//             {
//                 g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_PLAYRESTART");
//                 m_bPause=FALSE;
//                 SetPlayState();
//             }
//         }
//         else
//         {
//             if (NET_DVR_PlayBackControl(m_lPlayBackHandle, NET_DVR_PLAYPAUSE, 0, NULL))
//             {
//                 g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_PLAYPAUSE");
//                 m_bPause=TRUE;
//                 CButton *pButton;	
//                 pButton = (CButton *)GetDlgItem(IDC_BTN_EVENT_FILE_PLAY);
//                 pButton->SetIcon(m_hPlayEnableIcon);
//                 pButton->EnableWindow(TRUE);
//             }
//         }
    }
}




void CDlgPlayMotion::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
    DWORD nPos;
    char szLan[128] = {0};
    //	NET_DVR_TIME struOsdTime;
    if (nIDEvent == PLAYBYTIME_TIMER)
    {
        if (m_lPlayBackHandle >= 0)
        {
            if (NET_DVR_PlayBackControl(m_lPlayBackHandle, NET_DVR_PLAYGETPOS, 0, &nPos))
            {
                g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_PLAYGETPOS pos[%d]", nPos);
            }
            else
            {
                g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_PLAYGETPOS");
            }
            
            if (nPos > 100)
            {
                StopPlayBack();
                g_StringLanType(szLan, "由于网络原因或DVR忙,回放异常终止!", " Due to network reasons or DVR is busy, playback abnormal termination");
                AfxMessageBox(szLan);
            }
            if (nPos == 100)
            {				
                StopPlayBack();
                g_StringLanType(szLan, "按时间回放结束", "playback by time over");
                AfxMessageBox(szLan);
            }		
        }
        
    }

	CDialog::OnTimer(nIDEvent);
}

void CDlgPlayMotion::StopPlayBack()
{
    if (m_lPlayBackHandle >= 0)
    {
        if (!NET_DVR_StopPlayBack(m_lPlayBackHandle))
        {
            g_pMainDlg->AddLog(m_iDevIndex, OPERATION_FAIL_T, "NET_DVR_StopPlayBack");
        }
        else
        {
            g_pMainDlg->AddLog(m_iDevIndex, OPERATION_SUCC_T, "NET_DVR_StopPlayBack");
        
        }
        m_lPlayBackHandle = -1;
        //KillTimer(REMOTE_PLAY_STATE_TIMER);
        UpdateData(FALSE);
        Invalidate(TRUE);
    }
//     m_bPause = FALSE;
//     m_bSetFrame = FALSE;
//     
// 	SetStopState();
}
