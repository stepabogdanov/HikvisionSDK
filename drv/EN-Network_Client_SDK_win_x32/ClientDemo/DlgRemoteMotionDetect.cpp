/**********************************************************
FileName:    DlgRemoteMotionDetect.cpp
Description: motion detect handling      
Date:        2008/05/17
Note: 		<Global>struct, macro refer to GeneralDef.h, global variants and API refer to ClientDemo.cpp      
Modification History:      
    <version> <time>         <desc>
    <1.0    > <2008/05/17>       <created>
***********************************************************/
#include "stdafx.h"
#include "ClientDemo.h"
#include "DlgRemoteMotionDetect.h"
#include ".\dlgremotemotiondetect.h"

// CDlgRemoteMotionDetect dialog
#define MAX_MOTION_NUM 4
extern LPNET_DVR_MOTION_V30 g_lpMotionDetect;

DWORD	g_iDetectIndex = 0;			//motion detect zone index
RECT g_rectMotionDetectSet[MAX_MOTION_NUM];	//motion detect zone display rectangle
RECT g_rectMotionDetectMouse[MAX_MOTION_NUM];//mouse drawing line 
DWORD g_dwPrecision = 16;// the precision of the 22*11 detect unit under D1(704*576) resolution is 32*32, in the demothepicture is displayed in cif(352*288), and precision/2


/*********************************************************
  Function:	MotionDetectGetCallBack
  Desc:		get motion detect zone
  Input:	
  Output:	
  Return:	
**********************************************************/
void CALLBACK MotionDetectGetCallBack(LONG nPort,HDC hDc,DWORD nUser)
{
	CRect rect;
	int i = 0,j = 0;
	CPoint point;
	for (i = 0;i<64;i++)
	{
		for (j = 0;j<96;j++)
		{
			if (g_lpMotionDetect->byMotionScope[i][j] == 1)
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

/*********************************************************
  Function:	MotionDetectSetCallBack
  Desc:		set motion detect zone
  Input:	
  Output:	
  Return:	
**********************************************************/
void CALLBACK MotionDetectSetCallBack(LONG nPort,HDC hDc,DWORD nUser)
{
	DWORD i = 0;
	for (i=0;i<g_iDetectIndex;i++)
	{
		::DrawEdge(hDc, &g_rectMotionDetectSet[i], BDR_SUNKENOUTER, BF_RECT);
	}
	SetBkMode(hDc,TRANSPARENT);
}

/*********************************************************
  Function:	CDlgRemoteMotionDetect
  Desc:		Constructor
  Input:	
  Output:	
  Return:	
**********************************************************/
IMPLEMENT_DYNAMIC(CDlgRemoteMotionDetect, CDialog)
CDlgRemoteMotionDetect::CDlgRemoteMotionDetect(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgRemoteMotionDetect::IDD, pParent)
	, m_bChkMonitorAlarm(FALSE)
	, m_bChkAudioAlarm(FALSE)
	, m_bChkReportCenter(FALSE)
	, m_bChkInvokeAlarmOut(FALSE)
	, m_bChkInvokeJpegCapture(FALSE)
	, m_bChkEmapAlarmOut(FALSE)
	, m_bChkPicFtp(FALSE)
	, m_bChkAlarmOut1(FALSE)
	, m_bChkAlarmOut2(FALSE)
	, m_bChkAlarmOut3(FALSE)
	, m_bChkAlarmOut4(FALSE)
	, m_bChkAlarmOut5(FALSE)
	, m_bChkAlarmOut6(FALSE)
	, m_bChkAlarmOut7(FALSE)
	, m_bChkAlarmOut8(FALSE)
	, m_bChkAlarmOut9(FALSE)
	, m_bChkAlarmOut10(FALSE)
	, m_bChkAlarmOut11(FALSE)
	, m_bChkAlarmOut12(FALSE)
	, m_bChkAlarmOut13(FALSE)
	, m_bChkAlarmOut14(FALSE)
	, m_bChkAlarmOut15(FALSE)
	, m_bChkAlarmOut16(FALSE)
	, m_bChkAlarmOut17(FALSE)
	, m_bChkAlarmOut18(FALSE)
	, m_bChkAlarmOut19(FALSE)
	, m_bChkAlarmOut20(FALSE)
	, m_bChkAlarmOut21(FALSE)
	, m_bChkAlarmOut22(FALSE)
	, m_bChkAlarmOut23(FALSE)
	, m_bChkAlarmOut24(FALSE)
	, m_bChkAlarmOut25(FALSE)
	, m_bChkAlarmOut26(FALSE)
	, m_bChkAlarmOut27(FALSE)
	, m_bChkAlarmOut28(FALSE)
	, m_bChkAlarmOut29(FALSE)
	, m_bChkAlarmOut30(FALSE)
	, m_bChkAlarmOut31(FALSE)
	, m_bChkAlarmOut32(FALSE)
	, m_iHour11(0)
	, m_iMin11(0)
	, m_iHour12(0)
	, m_iMin12(0)
	, m_iHour21(0)
	, m_iMin21(0)
	, m_iHour22(0)
	, m_iMin22(0)
	, m_iHour31(0)
	, m_iMin31(0)
	, m_iHour32(0)
	, m_iMin32(0)
	, m_iHour41(0)
	, m_iMin41(0)
	, m_iHour42(0)
	, m_iMin42(0)
	, m_iHour51(0)
	, m_iMin51(0)
	, m_iHour52(0)
	, m_iMin52(0)
	, m_iHour61(0)
	, m_iMin61(0)
	, m_iHour62(0)
	, m_iMin62(0)
	, m_iHour71(0)
	, m_iMin71(0)
	, m_iHour72(0)
	, m_iMin72(0)
	, m_iHour81(0)
	, m_iMin81(0)
	, m_iHour82(0)
	, m_iMin82(0)
	, m_bChkMotionShow(FALSE)
	, m_bChkMotionSet(FALSE)
	, m_iChanShowNum(0)
	, m_lLoginID(-1)
	, m_bDrawArea(FALSE)
	, m_lPlayHandle(NULL)
	, m_bSetMotion(FALSE)
	, m_dwAlarmOutNum(0)
	, m_iChanCount(0)
	, m_dwDevIndex(0)
{
	memset(&m_bAlarmOut[0], 0, sizeof(BOOL)*MAX_ALARMOUT_V30);
	memset(&m_bRecordChan[0], 0, sizeof(BOOL)*MAX_CHANNUM_V30);
    memset(&m_struHolidayHandle, 0, sizeof(m_struHolidayHandle));
}

/*********************************************************
  Function:	~CDlgRemoteMotionDetect
  Desc:		destructor
  Input:	
  Output:	
  Return:	
**********************************************************/
CDlgRemoteMotionDetect::~CDlgRemoteMotionDetect()
{
}

/*********************************************************
Function:	DoDataExchange
Desc:		the map between control and variable
Input:	
Output:	
Return:	
**********************************************************/
void CDlgRemoteMotionDetect::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgRemoteMotionDetect)
	DDX_Control(pDX, IDC_TREE_ALARM_OUT, m_treeAlarmOut);
	DDX_Control(pDX, IDC_TREE_CHAN, m_treeChan);
	DDX_Check(pDX, IDC_CHK_MONITOR_ALARM, m_bChkMonitorAlarm);
	DDX_Check(pDX, IDC_CHK_AUDIO_ALARM, m_bChkAudioAlarm);
	DDX_Check(pDX, IDC_CHK_REPORT_CENTER, m_bChkReportCenter);
	DDX_Check(pDX, IDC_CHK_INVOKE_ALARM_OUT, m_bChkInvokeAlarmOut);
	DDX_Check(pDX, IDC_CHK_INVOKE_JPEG_CAPTURE, m_bChkInvokeJpegCapture);
	DDX_Check(pDX, IDC_CHK_ALARMOUT_EMAP, m_bChkEmapAlarmOut);
	DDX_Control(pDX, IDC_COMBO_MOTION_WEEKDAY, m_comboWeekday);
	DDX_Control(pDX, IDC_COMBO_MOTION_DAY_COPY, m_comboDayCopy);
	DDX_Text(pDX, IDC_EDIT_HOUR11, m_iHour11);
	DDX_Text(pDX, IDC_EDIT_MIN11, m_iMin11);
	DDX_Text(pDX, IDC_EDIT_HOUR12, m_iHour12);
	DDX_Text(pDX, IDC_EDIT_MIN12, m_iMin12);
	DDX_Text(pDX, IDC_EDIT_HOUR21, m_iHour21);
	DDX_Text(pDX, IDC_EDIT_MIN21, m_iMin21);
	DDX_Text(pDX, IDC_EDIT_HOUR22, m_iHour22);
	DDX_Text(pDX, IDC_EDIT_MIN22, m_iMin22);
	DDX_Text(pDX, IDC_EDIT_HOUR31, m_iHour31);
	DDX_Text(pDX, IDC_EDIT_MIN31, m_iMin31);
	DDX_Text(pDX, IDC_EDIT_HOUR32, m_iHour32);
	DDX_Text(pDX, IDC_EDIT_MIN32, m_iMin32);
	DDX_Text(pDX, IDC_EDIT_HOUR41, m_iHour41);
	DDX_Text(pDX, IDC_EDIT_MIN41, m_iMin41);
	DDX_Text(pDX, IDC_EDIT_HOUR42, m_iHour42);
	DDX_Text(pDX, IDC_EDIT_MIN42, m_iMin42);
	DDX_Text(pDX, IDC_EDIT_HOUR51, m_iHour51);
	DDX_Text(pDX, IDC_EDIT_MIN51, m_iMin51);
	DDX_Text(pDX, IDC_EDIT_HOUR52, m_iHour52);
	DDX_Text(pDX, IDC_EDIT_MIN52, m_iMin52);
	DDX_Text(pDX, IDC_EDIT_HOUR61, m_iHour61);
	DDX_Text(pDX, IDC_EDIT_MIN61, m_iMin61);
	DDX_Text(pDX, IDC_EDIT_HOUR62, m_iHour62);
	DDX_Text(pDX, IDC_EDIT_MIN62, m_iMin62);
	DDX_Text(pDX, IDC_EDIT_HOUR71, m_iHour71);
	DDX_Text(pDX, IDC_EDIT_MIN71, m_iMin71);
	DDX_Text(pDX, IDC_EDIT_HOUR72, m_iHour72);
	DDX_Text(pDX, IDC_EDIT_MIN72, m_iMin72);
	DDX_Text(pDX, IDC_EDIT_HOUR81, m_iHour81);
	DDX_Text(pDX, IDC_EDIT_MIN81, m_iMin81);
	DDX_Text(pDX, IDC_EDIT_HOUR82, m_iHour82);
	DDX_Text(pDX, IDC_EDIT_MIN82, m_iMin82);
	DDX_Check(pDX, IDC_CHK_MOTION_DETECT_SHOW, m_bChkMotionShow);
	DDX_Check(pDX, IDC_CHK_MOTION_DETECT_SET, m_bChkMotionSet);
	DDX_Control(pDX, IDC_COMBO_MOTION_SENSITIVE, m_comboMotionSensitive);
	DDX_Control(pDX, IDC_PIC_MOTION_DETECT, m_picMotionDetect);
	DDX_Control(pDX, IDC_COMBO_PRECISIOIN, m_comboPrecision);
	DDX_Check(pDX, IDC_CHK_PIC_FTP, m_bChkPicFtp);
	DDX_Check(pDX, IDC_CHK_SHOW_MOTION, m_bChkShowMotion);
	//}}AFX_DATA_MAP
}


/*********************************************************
Function:	BEGIN_MESSAGE_MAP
Desc:		the map between control and function
Input:	
Output:	
Return:	
**********************************************************/
BEGIN_MESSAGE_MAP(CDlgRemoteMotionDetect, CDialog)
	//{{AFX_MSG_MAP(CDlgRemoteMotionDetect)	
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_CHK_INVOKE_ALARM_OUT, OnBnClickedChkInvokeAlarmOut)
	ON_CBN_SELCHANGE(IDC_COMBO_MOTION_WEEKDAY, OnCbnSelchangeComboWeekday)
	ON_BN_CLICKED(IDC_CHK_MOTION_DETECT_SHOW, OnBnClickedChkMotionDetectShow)
	ON_BN_CLICKED(IDC_CHK_MOTION_DETECT_SET, OnBnClickedChkMotionDetectSet)
	ON_BN_CLICKED(IDC_MOTION_DAY_OK, OnBnClickedMotionDayOk)
	ON_BN_CLICKED(IDC_BTN_MOTION_DAY_COPY, OnBnClickedBtnMotionDayCopy)
	ON_BN_CLICKED(ID_BTN_MOTION_OK, OnBnClickedBtnMotionOk)
	ON_BN_CLICKED(ID_BTN_MOTION_EXIT, OnBnClickedBtnMotionExit)
	ON_CBN_SELCHANGE(IDC_COMBO_PRECISIOIN, OnCbnSelchangeComboPrecisioin)
	ON_NOTIFY(NM_CLICK, IDC_TREE_CHAN, OnClickTreeChan)
	ON_NOTIFY(NM_CLICK, IDC_TREE_ALARM_OUT, OnClickTreeAlarmOut)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


// CDlgRemoteMotionDetect message handlers
/*********************************************************
Function:	OnInitDialog
Desc:		Initialize the dialog
Input:	
Output:	
Return:	
**********************************************************/
BOOL CDlgRemoteMotionDetect::OnInitDialog() 
{
	CDialog::OnInitDialog();

	NET_DVR_CLIENTINFO struPlayInfo;
	int i = 0;
	m_picMotionDetect.MoveWindow(DETECT_AREA_TOP, DETECT_AREA_TOP, 352, 288);
	if (g_lpMotionDetect->byMotionSensitive == 0xFF)
	{
		m_comboMotionSensitive.SetCurSel(0);
	}
	else
	{
		m_comboMotionSensitive.SetCurSel(g_lpMotionDetect->byMotionSensitive+1);
	}
	m_bChkShowMotion = g_lpMotionDetect->byEnableDisplay;
	g_dwPrecision = 16;//for 352*288
//	m_comboPrecision.SetCurSel(g_lpMotionDetect->byPrecision);

// 	switch (g_lpMotionDetect->byPrecision)
// 	{
// 	case 0://32*32;
// 		g_dwPrecision = 32;
// 		break;
// 	case 1://64*64
// 		g_dwPrecision = 64;
// 		break;
// 	case 2://96*96
// 		g_dwPrecision = 96;
// 		break;
// 	default:
// 		g_dwPrecision = 96;
// 		break;
// 	}

    GetMotionHolidayHandle(m_struHolidayHandle);
    
	struPlayInfo.hPlayWnd = m_picMotionDetect.GetSafeHwnd();
	struPlayInfo.lChannel = m_iChanShowNum;
	struPlayInfo.lLinkMode = PTOPTCPMODE;
	struPlayInfo.sMultiCastIP = "";	

	m_lPlayHandle = NET_DVR_RealPlay(m_lLoginID, &struPlayInfo);	
	if (m_lPlayHandle == -1)
	{
		char szLan[128] = {0};
		g_StringLanType(szLan, "网络连接失败!", "Connect failed!");
		g_pMainDlg->AddLog(g_pMainDlg->m_iCurDeviceIndex, OPERATION_FAIL_T, "NET_DVR_RealPlay");
		AfxMessageBox(szLan);
	}	
	m_bDrawArea = FALSE;
	m_bSetMotion = FALSE;
	m_bChkMonitorAlarm = g_lpMotionDetect->struMotionHandleType.dwHandleType &0x01;
	m_bChkAudioAlarm = (g_lpMotionDetect->struMotionHandleType.dwHandleType>>1)&0x01;
	m_bChkReportCenter = (g_lpMotionDetect->struMotionHandleType.dwHandleType>>2)&0x01;
	m_bChkInvokeAlarmOut = (g_lpMotionDetect->struMotionHandleType.dwHandleType>>3)&0x01;
	m_bChkInvokeJpegCapture = (g_lpMotionDetect->struMotionHandleType.dwHandleType>>4)&0x01;
	m_bChkEmapAlarmOut = (g_lpMotionDetect->struMotionHandleType.dwHandleType>>6)&0x01;
	m_bChkPicFtp = (g_lpMotionDetect->struMotionHandleType.dwHandleType>>9)&0x01;
	m_treeAlarmOut.EnableWindow(m_bChkInvokeAlarmOut);
	for (i=0; i<MAX_ALARMOUT_V30; i++)
	{
		m_bAlarmOut[i] = g_lpMotionDetect->struMotionHandleType.byRelAlarmOut[i];
	}

	for (i=0; i< MAX_CHANNUM_V30; i++)
	{
		m_bRecordChan[i] = g_lpMotionDetect->byRelRecordChan[i];
	}

	m_comboWeekday.SetCurSel(0);
	m_comboDayCopy.SetCurSel(0);
	m_iHour11 = g_lpMotionDetect->struAlarmTime[0][0].byStartHour;
	m_iMin11 = g_lpMotionDetect->struAlarmTime[0][0].byStartMin;
	m_iHour12 = g_lpMotionDetect->struAlarmTime[0][0].byStopHour;
	m_iMin12 = g_lpMotionDetect->struAlarmTime[0][0].byStopMin;
	m_iHour21 = g_lpMotionDetect->struAlarmTime[0][1].byStartHour;
	m_iMin21 = g_lpMotionDetect->struAlarmTime[0][1].byStartMin;
	m_iHour22 = g_lpMotionDetect->struAlarmTime[0][1].byStopHour;
	m_iMin22 = g_lpMotionDetect->struAlarmTime[0][1].byStopMin;
	m_iHour31 = g_lpMotionDetect->struAlarmTime[0][2].byStartHour;
	m_iMin31 = g_lpMotionDetect->struAlarmTime[0][2].byStartMin;
	m_iHour32 = g_lpMotionDetect->struAlarmTime[0][2].byStopHour;
	m_iMin32 = g_lpMotionDetect->struAlarmTime[0][2].byStopMin;
	m_iHour41 = g_lpMotionDetect->struAlarmTime[0][3].byStartHour;
	m_iMin41 = g_lpMotionDetect->struAlarmTime[0][3].byStartMin;
	m_iHour42 = g_lpMotionDetect->struAlarmTime[0][3].byStopHour;
	m_iMin42 = g_lpMotionDetect->struAlarmTime[0][3].byStopMin;
	m_iHour51 = g_lpMotionDetect->struAlarmTime[0][4].byStartHour;
	m_iMin51 = g_lpMotionDetect->struAlarmTime[0][4].byStartMin;
	m_iHour52 = g_lpMotionDetect->struAlarmTime[0][4].byStopHour;
	m_iMin52 = g_lpMotionDetect->struAlarmTime[0][4].byStopMin;
	m_iHour61 = g_lpMotionDetect->struAlarmTime[0][5].byStartHour;
	m_iMin61 = g_lpMotionDetect->struAlarmTime[0][5].byStartMin;
	m_iHour62 = g_lpMotionDetect->struAlarmTime[0][5].byStopHour;
	m_iMin62 = g_lpMotionDetect->struAlarmTime[0][5].byStopMin;
	m_iHour71 = g_lpMotionDetect->struAlarmTime[0][6].byStartHour;
	m_iMin71 = g_lpMotionDetect->struAlarmTime[0][6].byStartMin;
	m_iHour72 = g_lpMotionDetect->struAlarmTime[0][6].byStopHour;
	m_iMin72 = g_lpMotionDetect->struAlarmTime[0][6].byStopMin;
	m_iHour81 = g_lpMotionDetect->struAlarmTime[0][7].byStartHour;
	m_iMin81 = g_lpMotionDetect->struAlarmTime[0][7].byStartMin;
	m_iHour82 = g_lpMotionDetect->struAlarmTime[0][7].byStopHour;
	m_iMin82 = g_lpMotionDetect->struAlarmTime[0][7].byStopMin;
	GetDlgItem(IDC_CHK_MOTION_DETECT_SHOW)->EnableWindow(TRUE);
	GetDlgItem(IDC_CHK_MOTION_DETECT_SET)->EnableWindow(TRUE);
	GetDlgItem(ID_BTN_MOTION_OK)->EnableWindow(TRUE);
	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
}
/*********************************************************
  Function:	OnBnClickedChkInvokeAlarmOut
  Desc:		invoke alarm out
  Input:	
  Output:	
  Return:	
**********************************************************/
void CDlgRemoteMotionDetect::OnBnClickedChkInvokeAlarmOut()
{
	UpdateData(TRUE);
	m_treeAlarmOut.EnableWindow(m_bChkInvokeAlarmOut);
}

/*********************************************************
  Function:	OnCbnSelchangeComboWeekday
  Desc:		update time changing
  Input:	
  Output:	
  Return:	
**********************************************************/
void CDlgRemoteMotionDetect::OnCbnSelchangeComboWeekday()
{
	UpdateData(TRUE);
	int	i = m_comboWeekday.GetCurSel();	

    if (i == 7)     // 7代表假日 需要单独获取
    {
        m_iHour11 = m_struHolidayHandle.struAlarmTime[0].byStartHour;
        m_iMin11 = m_struHolidayHandle.struAlarmTime[0].byStartMin;
        m_iHour12 = m_struHolidayHandle.struAlarmTime[0].byStopHour;
        m_iMin12 = m_struHolidayHandle.struAlarmTime[0].byStopMin;
        m_iHour21 = m_struHolidayHandle.struAlarmTime[1].byStartHour;
        m_iMin21 = m_struHolidayHandle.struAlarmTime[1].byStartMin;
        m_iHour22 = m_struHolidayHandle.struAlarmTime[1].byStopHour;
        m_iMin22 = m_struHolidayHandle.struAlarmTime[1].byStopMin;
        m_iHour31 = m_struHolidayHandle.struAlarmTime[2].byStartHour;
        m_iMin31 = m_struHolidayHandle.struAlarmTime[2].byStartMin;
        m_iHour32 = m_struHolidayHandle.struAlarmTime[2].byStopHour;
        m_iMin32 = m_struHolidayHandle.struAlarmTime[2].byStopMin;
        m_iHour41 = m_struHolidayHandle.struAlarmTime[3].byStartHour;
        m_iMin41 = m_struHolidayHandle.struAlarmTime[3].byStartMin;
        m_iHour42 = m_struHolidayHandle.struAlarmTime[3].byStopHour;
        m_iMin42 = m_struHolidayHandle.struAlarmTime[3].byStopMin;
        m_iHour51 = m_struHolidayHandle.struAlarmTime[4].byStartHour;
        m_iMin51 = m_struHolidayHandle.struAlarmTime[4].byStartMin;
        m_iHour52 = m_struHolidayHandle.struAlarmTime[4].byStopHour;
        m_iMin52 = m_struHolidayHandle.struAlarmTime[4].byStopMin;
        m_iHour61 = m_struHolidayHandle.struAlarmTime[5].byStartHour;
        m_iMin61 = m_struHolidayHandle.struAlarmTime[5].byStartMin;
        m_iHour62 = m_struHolidayHandle.struAlarmTime[5].byStopHour;
        m_iMin62 = m_struHolidayHandle.struAlarmTime[5].byStopMin;
        m_iHour71 = m_struHolidayHandle.struAlarmTime[6].byStartHour;
        m_iMin71 = m_struHolidayHandle.struAlarmTime[6].byStartMin;
        m_iHour72 = m_struHolidayHandle.struAlarmTime[6].byStopHour;
        m_iMin72 = m_struHolidayHandle.struAlarmTime[6].byStopMin;
        m_iHour81 = m_struHolidayHandle.struAlarmTime[7].byStartHour;
        m_iMin81 = m_struHolidayHandle.struAlarmTime[7].byStartMin;
        m_iHour82 = m_struHolidayHandle.struAlarmTime[7].byStopHour;
        m_iMin82 = m_struHolidayHandle.struAlarmTime[7].byStopMin;
    }
    else
    {
        m_iHour11 = g_lpMotionDetect->struAlarmTime[i][0].byStartHour;
        m_iMin11 = g_lpMotionDetect->struAlarmTime[i][0].byStartMin;
        m_iHour12 = g_lpMotionDetect->struAlarmTime[i][0].byStopHour;
        m_iMin12 = g_lpMotionDetect->struAlarmTime[i][0].byStopMin;
        m_iHour21 = g_lpMotionDetect->struAlarmTime[i][1].byStartHour;
        m_iMin21 = g_lpMotionDetect->struAlarmTime[i][1].byStartMin;
        m_iHour22 = g_lpMotionDetect->struAlarmTime[i][1].byStopHour;
        m_iMin22 = g_lpMotionDetect->struAlarmTime[i][1].byStopMin;
        m_iHour31 = g_lpMotionDetect->struAlarmTime[i][2].byStartHour;
        m_iMin31 = g_lpMotionDetect->struAlarmTime[i][2].byStartMin;
        m_iHour32 = g_lpMotionDetect->struAlarmTime[i][2].byStopHour;
        m_iMin32 = g_lpMotionDetect->struAlarmTime[i][2].byStopMin;
        m_iHour41 = g_lpMotionDetect->struAlarmTime[i][3].byStartHour;
        m_iMin41 = g_lpMotionDetect->struAlarmTime[i][3].byStartMin;
        m_iHour42 = g_lpMotionDetect->struAlarmTime[i][3].byStopHour;
        m_iMin42 = g_lpMotionDetect->struAlarmTime[i][3].byStopMin;
        m_iHour51 = g_lpMotionDetect->struAlarmTime[i][4].byStartHour;
        m_iMin51 = g_lpMotionDetect->struAlarmTime[i][4].byStartMin;
        m_iHour52 = g_lpMotionDetect->struAlarmTime[i][4].byStopHour;
        m_iMin52 = g_lpMotionDetect->struAlarmTime[i][4].byStopMin;
        m_iHour61 = g_lpMotionDetect->struAlarmTime[i][5].byStartHour;
        m_iMin61 = g_lpMotionDetect->struAlarmTime[i][5].byStartMin;
        m_iHour62 = g_lpMotionDetect->struAlarmTime[i][5].byStopHour;
        m_iMin62 = g_lpMotionDetect->struAlarmTime[i][5].byStopMin;
        m_iHour71 = g_lpMotionDetect->struAlarmTime[i][6].byStartHour;
        m_iMin71 = g_lpMotionDetect->struAlarmTime[i][6].byStartMin;
        m_iHour72 = g_lpMotionDetect->struAlarmTime[i][6].byStopHour;
        m_iMin72 = g_lpMotionDetect->struAlarmTime[i][6].byStopMin;
        m_iHour81 = g_lpMotionDetect->struAlarmTime[i][7].byStartHour;
        m_iMin81 = g_lpMotionDetect->struAlarmTime[i][7].byStartMin;
        m_iHour82 = g_lpMotionDetect->struAlarmTime[i][7].byStopHour;
        m_iMin82 = g_lpMotionDetect->struAlarmTime[i][7].byStopMin;
    }
	UpdateData(FALSE);
}

/*********************************************************
  Function:	OnBnClickedChkMotionDetectShow
  Desc:		display selected motion detection zone
  Input:	
  Output:	
  Return:	
**********************************************************/
void CDlgRemoteMotionDetect::OnBnClickedChkMotionDetectShow()
{
	if (m_lPlayHandle < 0)
	{
		return;
	}
	UpdateData(TRUE);
	if (m_bChkMotionSet)
	{
		m_bChkMotionSet = FALSE;
		m_bDrawArea = FALSE;
		UpdateData(FALSE);
	}
	if (m_bChkMotionShow)
	{
		NET_DVR_RigisterDrawFun(m_lPlayHandle,NULL, 0);
		Sleep(200);
		NET_DVR_RigisterDrawFun(m_lPlayHandle,MotionDetectGetCallBack, 0);
	}
	else
	{
		NET_DVR_RigisterDrawFun(m_lPlayHandle,NULL, 0);
	}	
}

/*********************************************************
Function:	OnBnClickedChkMotionDetectSet
Desc:		display selected motion detection zone selection
Input:	
Output:	
Return:	
**********************************************************/
void CDlgRemoteMotionDetect::OnBnClickedChkMotionDetectSet()
{
	//Set motion detect zone
	if (m_lPlayHandle < 0)
	{
		return;
	}
	UpdateData(TRUE);
	if (m_bChkMotionShow)
	{
		m_bChkMotionShow = FALSE;
		UpdateData(FALSE);
	}
	if (m_bChkMotionSet)
	{
		NET_DVR_RigisterDrawFun(m_lPlayHandle,NULL,0);
		g_iDetectIndex = 0;
		m_bDrawArea = TRUE;
		m_bSetMotion = TRUE;
	}
	else
	{
		m_bDrawArea = FALSE;
		NET_DVR_RigisterDrawFun(m_lPlayHandle,NULL,0);
	}
}

/*********************************************************
  Function:	OnLButtonDown
  Desc:		left click detection
  Input:	nFlags,function key status;point,mouse status
  Output:	
  Return:	
**********************************************************/
void CDlgRemoteMotionDetect::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	if (m_bDrawArea)
	{
		if (MK_CONTROL&nFlags)
		{
			NET_DVR_RigisterDrawFun(m_lPlayHandle, MotionDetectSetCallBack, 0);
			if (g_iDetectIndex >=MAX_MOTION_NUM)
			{
				g_iDetectIndex = 0;
			}
			point.x -= DETECT_AREA_TOP;
			point.y -= DETECT_AREA_TOP;
			g_rectMotionDetectMouse[g_iDetectIndex].left=point.x/g_dwPrecision*g_dwPrecision;
			g_rectMotionDetectMouse[g_iDetectIndex].top=point.y/g_dwPrecision*g_dwPrecision;
			g_rectMotionDetectMouse[g_iDetectIndex].right=g_rectMotionDetectMouse[g_iDetectIndex].left;
			g_rectMotionDetectMouse[g_iDetectIndex].bottom=g_rectMotionDetectMouse[g_iDetectIndex].top;
			POINT tPoint=point;
			g_rectMotionDetectSet[g_iDetectIndex].left=tPoint.x/g_dwPrecision*g_dwPrecision;
			g_rectMotionDetectSet[g_iDetectIndex].top=tPoint.y/g_dwPrecision*g_dwPrecision;
			//
			g_rectMotionDetectSet[g_iDetectIndex].right=tPoint.x/g_dwPrecision*g_dwPrecision+1;
			g_rectMotionDetectSet[g_iDetectIndex].bottom=tPoint.y/g_dwPrecision*g_dwPrecision+1;
			g_iDetectIndex ++;
		}
	}	
	CDialog::OnLButtonDown(nFlags, point);
}

/*********************************************************
  Function:	OnMouseMove
  Desc:		set motion detect zone
  Input:	nFlags,function key status;point,mouse status
  Output:	
  Return:	
**********************************************************/
void CDlgRemoteMotionDetect::OnMouseMove(UINT nFlags, CPoint point) 
{
	if (m_bDrawArea)
	{
		if (MK_CONTROL&nFlags&&MK_LBUTTON&nFlags)
		{
			point.x -= DETECT_AREA_TOP;
			point.y -= DETECT_AREA_TOP; 
			g_rectMotionDetectMouse[g_iDetectIndex-1].right=point.x/g_dwPrecision*g_dwPrecision;
			g_rectMotionDetectMouse[g_iDetectIndex-1].bottom=point.y/g_dwPrecision*g_dwPrecision;
			POINT tPoint=point;
			g_rectMotionDetectSet[g_iDetectIndex-1].right=tPoint.x/g_dwPrecision*g_dwPrecision;
			g_rectMotionDetectSet[g_iDetectIndex-1].bottom=tPoint.y/g_dwPrecision*g_dwPrecision;
		}
	}	
	CDialog::OnMouseMove(nFlags, point);
}

/*********************************************************
Function:	OnBnClickedBtnAlarmInTimeOk
Desc:		finish and update time schedule settings
Input:	
Output:	
Return:	
**********************************************************/
void CDlgRemoteMotionDetect::OnBnClickedMotionDayOk()
{
	UpdateData(TRUE);
	if (!TimeTest())
	{
		return;
	}
	int	i = m_comboWeekday.GetCurSel();	

    if (i == 7)
    {
        m_struHolidayHandle.struAlarmTime[0].byStartHour = (BYTE)m_iHour11;
        m_struHolidayHandle.struAlarmTime[0].byStartMin = (BYTE)m_iMin11;
        m_struHolidayHandle.struAlarmTime[0].byStopHour = (BYTE)m_iHour12;
        m_struHolidayHandle.struAlarmTime[0].byStopMin = (BYTE)m_iMin12;
        m_struHolidayHandle.struAlarmTime[1].byStartHour = (BYTE)m_iHour21;
        m_struHolidayHandle.struAlarmTime[1].byStartMin = (BYTE)m_iMin21;
        m_struHolidayHandle.struAlarmTime[1].byStopHour = (BYTE)m_iHour22;
        m_struHolidayHandle.struAlarmTime[1].byStopMin = (BYTE)m_iMin22;
        m_struHolidayHandle.struAlarmTime[2].byStartHour = (BYTE)m_iHour31;
        m_struHolidayHandle.struAlarmTime[2].byStartMin = (BYTE)m_iMin31;
        m_struHolidayHandle.struAlarmTime[2].byStopHour = (BYTE)m_iHour32;
        m_struHolidayHandle.struAlarmTime[2].byStopMin = (BYTE)m_iMin32;
        m_struHolidayHandle.struAlarmTime[3].byStartHour = (BYTE)m_iHour41;
        m_struHolidayHandle.struAlarmTime[3].byStartMin = (BYTE)m_iMin41;
        m_struHolidayHandle.struAlarmTime[3].byStopHour = (BYTE)m_iHour42;
        m_struHolidayHandle.struAlarmTime[3].byStopMin = (BYTE)m_iMin42;
        
        m_struHolidayHandle.struAlarmTime[4].byStartHour = (BYTE)m_iHour51;
        m_struHolidayHandle.struAlarmTime[4].byStartMin = (BYTE)m_iMin51;
        m_struHolidayHandle.struAlarmTime[4].byStopHour = (BYTE)m_iHour52;
        m_struHolidayHandle.struAlarmTime[4].byStopMin = (BYTE)m_iMin52;
        m_struHolidayHandle.struAlarmTime[5].byStartHour = (BYTE)m_iHour61;
        m_struHolidayHandle.struAlarmTime[5].byStartMin = (BYTE)m_iMin61;
        m_struHolidayHandle.struAlarmTime[5].byStopHour = (BYTE)m_iHour62;
        m_struHolidayHandle.struAlarmTime[5].byStopMin = (BYTE)m_iMin62;
        m_struHolidayHandle.struAlarmTime[6].byStartHour = (BYTE)m_iHour71;
        m_struHolidayHandle.struAlarmTime[6].byStartMin = (BYTE)m_iMin71;
        m_struHolidayHandle.struAlarmTime[6].byStopHour = (BYTE)m_iHour72;
        m_struHolidayHandle.struAlarmTime[6].byStopMin = (BYTE)m_iMin72;
        m_struHolidayHandle.struAlarmTime[7].byStartHour = (BYTE)m_iHour81;
        m_struHolidayHandle.struAlarmTime[7].byStartMin = (BYTE)m_iMin81;
        m_struHolidayHandle.struAlarmTime[7].byStopHour = (BYTE)m_iHour82;
	    m_struHolidayHandle.struAlarmTime[7].byStopMin = (BYTE)m_iMin82;
        if (!SetMotionHolidayHandle(m_struHolidayHandle))
        {
            AfxMessageBox("Fail to set motion holiday handle");
        }
    }
    else
    {
        g_lpMotionDetect->struAlarmTime[i][0].byStartHour = (BYTE)m_iHour11;
        g_lpMotionDetect->struAlarmTime[i][0].byStartMin = (BYTE)m_iMin11;
        g_lpMotionDetect->struAlarmTime[i][0].byStopHour = (BYTE)m_iHour12;
        g_lpMotionDetect->struAlarmTime[i][0].byStopMin = (BYTE)m_iMin12;
        g_lpMotionDetect->struAlarmTime[i][1].byStartHour = (BYTE)m_iHour21;
        g_lpMotionDetect->struAlarmTime[i][1].byStartMin = (BYTE)m_iMin21;
        g_lpMotionDetect->struAlarmTime[i][1].byStopHour = (BYTE)m_iHour22;
        g_lpMotionDetect->struAlarmTime[i][1].byStopMin = (BYTE)m_iMin22;
        g_lpMotionDetect->struAlarmTime[i][2].byStartHour = (BYTE)m_iHour31;
        g_lpMotionDetect->struAlarmTime[i][2].byStartMin = (BYTE)m_iMin31;
        g_lpMotionDetect->struAlarmTime[i][2].byStopHour = (BYTE)m_iHour32;
        g_lpMotionDetect->struAlarmTime[i][2].byStopMin = (BYTE)m_iMin32;
        g_lpMotionDetect->struAlarmTime[i][3].byStartHour = (BYTE)m_iHour41;
        g_lpMotionDetect->struAlarmTime[i][3].byStartMin = (BYTE)m_iMin41;
        g_lpMotionDetect->struAlarmTime[i][3].byStopHour = (BYTE)m_iHour42;
        g_lpMotionDetect->struAlarmTime[i][3].byStopMin = (BYTE)m_iMin42;
        
        g_lpMotionDetect->struAlarmTime[i][4].byStartHour = (BYTE)m_iHour51;
        g_lpMotionDetect->struAlarmTime[i][4].byStartMin = (BYTE)m_iMin51;
        g_lpMotionDetect->struAlarmTime[i][4].byStopHour = (BYTE)m_iHour52;
        g_lpMotionDetect->struAlarmTime[i][4].byStopMin = (BYTE)m_iMin52;
        g_lpMotionDetect->struAlarmTime[i][5].byStartHour = (BYTE)m_iHour61;
        g_lpMotionDetect->struAlarmTime[i][5].byStartMin = (BYTE)m_iMin61;
        g_lpMotionDetect->struAlarmTime[i][5].byStopHour = (BYTE)m_iHour62;
        g_lpMotionDetect->struAlarmTime[i][5].byStopMin = (BYTE)m_iMin62;
        g_lpMotionDetect->struAlarmTime[i][6].byStartHour = (BYTE)m_iHour71;
        g_lpMotionDetect->struAlarmTime[i][6].byStartMin = (BYTE)m_iMin71;
        g_lpMotionDetect->struAlarmTime[i][6].byStopHour = (BYTE)m_iHour72;
        g_lpMotionDetect->struAlarmTime[i][6].byStopMin = (BYTE)m_iMin72;
        g_lpMotionDetect->struAlarmTime[i][7].byStartHour = (BYTE)m_iHour81;
        g_lpMotionDetect->struAlarmTime[i][7].byStartMin = (BYTE)m_iMin81;
        g_lpMotionDetect->struAlarmTime[i][7].byStopHour = (BYTE)m_iHour82;
        g_lpMotionDetect->struAlarmTime[i][7].byStopMin = (BYTE)m_iMin82;
    }
	GetDlgItem(IDC_BTN_MOTION_DAY_COPY)->EnableWindow(TRUE);

}

/*********************************************************
  Function:	OnBnClickedBtnMotionDayCopy
  Desc:		copy current schedule
  Input:	
  Output:	
  Return:	
**********************************************************/
void CDlgRemoteMotionDetect::OnBnClickedBtnMotionDayCopy()
{
	UpdateData(TRUE);
	int j,k;
	int i = m_comboWeekday.GetCurSel();
	int m_nCopyTime = m_comboDayCopy.GetCurSel() - 1;

	if (m_nCopyTime == -1)
	{
		for (j=0; j<MAX_DAYS; j++)
		{
			if (j == i)
			{
				continue;
			}
			for (k=0; k<MAX_TIMESEGMENT_V30; k++)
			{
				memcpy(&(g_lpMotionDetect->struAlarmTime[j][k]), &(g_lpMotionDetect->struAlarmTime[i][k]), sizeof(NET_DVR_SCHEDTIME));
			}
		}
	}
    if (m_nCopyTime == 7) // 假日情况
    {
        for (k = 0; k < MAX_TIMESEGMENT_V30; k++)
        {
            memcpy(&m_struHolidayHandle.struAlarmTime[k], &(g_lpMotionDetect->struAlarmTime[i][k]), sizeof(NET_DVR_SCHEDTIME));
        }
        if (!SetMotionHolidayHandle(m_struHolidayHandle))
        {
            AfxMessageBox("Fail to set motion holiday handle");
        }
    }
	else
	{
		for (k=0; k<MAX_TIMESEGMENT_V30; k++)
		{
			memcpy(&(g_lpMotionDetect->struAlarmTime[m_nCopyTime][k]), &(g_lpMotionDetect->struAlarmTime[i][k]), sizeof(NET_DVR_SCHEDTIME));
		}
	}
}

/*********************************************************
  Function:	OnBnClickedBtnMotionOk
  Desc:		finish and update motion detect zone sttings
  Input:	
  Output:	
  Return:	
**********************************************************/
void CDlgRemoteMotionDetect::OnBnClickedBtnMotionOk()
{
	UpdateData(TRUE);
	unsigned int i = 0,j = 0,k = 0;
	if (!TimeTest())
	{
		return;
	}
	i = m_comboWeekday.GetCurSel();	
	g_lpMotionDetect->struAlarmTime[i][0].byStartHour = (BYTE)m_iHour11;
	g_lpMotionDetect->struAlarmTime[i][0].byStartMin = (BYTE)m_iMin11;
	g_lpMotionDetect->struAlarmTime[i][0].byStopHour = (BYTE)m_iHour12;
	g_lpMotionDetect->struAlarmTime[i][0].byStopMin = (BYTE)m_iMin12;
	g_lpMotionDetect->struAlarmTime[i][1].byStartHour = (BYTE)m_iHour21;
	g_lpMotionDetect->struAlarmTime[i][1].byStartMin = (BYTE)m_iMin21;
	g_lpMotionDetect->struAlarmTime[i][1].byStopHour = (BYTE)m_iHour22;
	g_lpMotionDetect->struAlarmTime[i][1].byStopMin = (BYTE)m_iMin22;
	g_lpMotionDetect->struAlarmTime[i][2].byStartHour = (BYTE)m_iHour31;
	g_lpMotionDetect->struAlarmTime[i][2].byStartMin = (BYTE)m_iMin31;
	g_lpMotionDetect->struAlarmTime[i][2].byStopHour = (BYTE)m_iHour32;
	g_lpMotionDetect->struAlarmTime[i][2].byStopMin = (BYTE)m_iMin32;
	g_lpMotionDetect->struAlarmTime[i][3].byStartHour = (BYTE)m_iHour41;
	g_lpMotionDetect->struAlarmTime[i][3].byStartMin = (BYTE)m_iMin41;
	g_lpMotionDetect->struAlarmTime[i][3].byStopHour = (BYTE)m_iHour42;
	g_lpMotionDetect->struAlarmTime[i][3].byStopMin = (BYTE)m_iMin42;

	g_lpMotionDetect->struAlarmTime[i][4].byStartHour = (BYTE)m_iHour51;
	g_lpMotionDetect->struAlarmTime[i][4].byStartMin = (BYTE)m_iMin51;
	g_lpMotionDetect->struAlarmTime[i][4].byStopHour = (BYTE)m_iHour52;
	g_lpMotionDetect->struAlarmTime[i][4].byStopMin = (BYTE)m_iMin52;
	g_lpMotionDetect->struAlarmTime[i][5].byStartHour = (BYTE)m_iHour61;
	g_lpMotionDetect->struAlarmTime[i][5].byStartMin = (BYTE)m_iMin61;
	g_lpMotionDetect->struAlarmTime[i][5].byStopHour = (BYTE)m_iHour62;
	g_lpMotionDetect->struAlarmTime[i][5].byStopMin = (BYTE)m_iMin62;
	g_lpMotionDetect->struAlarmTime[i][6].byStartHour = (BYTE)m_iHour71;
	g_lpMotionDetect->struAlarmTime[i][6].byStartMin = (BYTE)m_iMin71;
	g_lpMotionDetect->struAlarmTime[i][6].byStopHour = (BYTE)m_iHour72;
	g_lpMotionDetect->struAlarmTime[i][6].byStopMin = (BYTE)m_iMin72;
	g_lpMotionDetect->struAlarmTime[i][7].byStartHour = (BYTE)m_iHour81;
	g_lpMotionDetect->struAlarmTime[i][7].byStartMin = (BYTE)m_iMin81;
	g_lpMotionDetect->struAlarmTime[i][7].byStopHour = (BYTE)m_iHour82;
	g_lpMotionDetect->struAlarmTime[i][7].byStopMin = (BYTE)m_iMin82;
	if (m_bSetMotion)
	{
		//clear
		for (i = 0; i < 64; i++)
		{
			for (j = 0; j < 96; j++)
			{
				g_lpMotionDetect->byMotionScope[i][j] = 0;
			}
		}
		//save zone settings on the device
		for (k = 0; k < g_iDetectIndex; k++)
		{
			if (g_rectMotionDetectMouse[k].top <= g_rectMotionDetectMouse[k].bottom)
			{
				if (g_rectMotionDetectMouse[k].left <= g_rectMotionDetectMouse[k].right)
				{//draw from top-left to bottom-right
					for (i = g_rectMotionDetectMouse[k].top/g_dwPrecision;i<64 && i<g_rectMotionDetectMouse[k].bottom/g_dwPrecision; i++)
					{
						for (j = g_rectMotionDetectMouse[k].left/g_dwPrecision; j < g_rectMotionDetectMouse[k].right/g_dwPrecision; j++)
						{
							g_lpMotionDetect->byMotionScope[i][j] = 1;
						}
					}
				}
				else
				{//draw from top-right to bottom-left
					for (i = g_rectMotionDetectMouse[k].top/g_dwPrecision; i<64 && i < g_rectMotionDetectMouse[k].bottom/g_dwPrecision; i++)
					{
						for (j = g_rectMotionDetectMouse[k].right/g_dwPrecision; j < g_rectMotionDetectMouse[k].left/g_dwPrecision; j++)
						{
							g_lpMotionDetect->byMotionScope[i][j] = 1;
						}
					}
				}
			}
			else
			{
				if (g_rectMotionDetectMouse[k].left <= g_rectMotionDetectMouse[k].right)
				{//draw from bottom-left to top-right
					for (i = g_rectMotionDetectMouse[k].bottom/g_dwPrecision; i < g_rectMotionDetectMouse[k].top/g_dwPrecision; i++)
					{
						for (j = g_rectMotionDetectMouse[k].left/g_dwPrecision; j < g_rectMotionDetectMouse[k].right/g_dwPrecision; j++)
						{
							g_lpMotionDetect->byMotionScope[i][j] = 1;						
						}
					}
				}
				else
				{//draw from bottom-right to top-left
					for (i = g_rectMotionDetectMouse[k].bottom/g_dwPrecision; i < g_rectMotionDetectMouse[k].top/g_dwPrecision; i++)
					{
						for (j = g_rectMotionDetectMouse[k].right/g_dwPrecision; j < g_rectMotionDetectMouse[k].left/g_dwPrecision; j++)
						{
							g_lpMotionDetect->byMotionScope[i][j] = 1;						
						}
					}
				}
			}
		}
	}

//	g_iDetectIndex = 0;
	if (m_comboMotionSensitive.GetCurSel() == 0)
	{
		g_lpMotionDetect->byMotionSensitive = 0xFF;
	}
	else
	{
		g_lpMotionDetect->byMotionSensitive = (BYTE)(m_comboMotionSensitive.GetCurSel()-1);
	}	
	g_lpMotionDetect->byEnableDisplay = m_bChkShowMotion;

	g_lpMotionDetect->struMotionHandleType.dwHandleType = 0;
	g_lpMotionDetect->struMotionHandleType.dwHandleType |= (m_bChkMonitorAlarm << 0);
	g_lpMotionDetect->struMotionHandleType.dwHandleType |= (m_bChkAudioAlarm << 1);
	g_lpMotionDetect->struMotionHandleType.dwHandleType |= (m_bChkReportCenter << 2);
	g_lpMotionDetect->struMotionHandleType.dwHandleType |= (m_bChkInvokeAlarmOut << 3);
	g_lpMotionDetect->struMotionHandleType.dwHandleType |= (m_bChkInvokeJpegCapture << 4);
	g_lpMotionDetect->struMotionHandleType.dwHandleType |= (m_bChkEmapAlarmOut<<6);
	g_lpMotionDetect->struMotionHandleType.dwHandleType |= (m_bChkPicFtp << 9);
	
	for (i=0; i<MAX_ALARMOUT_V30; i++)
	{
		g_lpMotionDetect->struMotionHandleType.byRelAlarmOut[i] = (BYTE)m_bAlarmOut[i];
	}

	for (i=0; i< MAX_CHANNUM_V30; i++)
	{
		g_lpMotionDetect->byRelRecordChan[i] = (BYTE)m_bRecordChan[i];
	}
	//CDialog::OnOK();
}

/*********************************************************
  Function:	OnBnClickedBtnMotionExit
  Desc:		cancel motion detect zone settings
  Input:	
  Output:	
  Return:	
**********************************************************/
void CDlgRemoteMotionDetect::OnBnClickedBtnMotionExit()
{
	if (m_lPlayHandle >= 0)
	{
		NET_DVR_RigisterDrawFun(m_lPlayHandle,NULL, 0);
		NET_DVR_StopRealPlay(m_lPlayHandle);
		m_lPlayHandle = -1;
	}
	CDialog::OnOK();
}

/*********************************************************
  Function:	TimeTest
  Desc:		time detection
  Input:	
  Output:	
  Return:	
**********************************************************/
BOOL CDlgRemoteMotionDetect::TimeTest()
{
	int i = 0;
	int j = 0;
	WORD wStartTime[MAX_TIMESEGMENT_V30], wStopTime[MAX_TIMESEGMENT_V30];
	char szLan[128] = {0};
	UpdateData(TRUE);
	if ((m_iHour11 < 0) || (m_iHour11 > 24) || (m_iHour12 < 0) || (m_iHour12 > 24) ||	\
		(m_iHour21 < 0) || (m_iHour21 > 24) || (m_iHour22 < 0) || (m_iHour22 > 24) ||	\
		(m_iHour31 < 0) || (m_iHour31 > 24) || (m_iHour32 < 0) || (m_iHour32 > 24) ||	\
		(m_iHour41 < 0) || (m_iHour41 > 24) || (m_iHour42 < 0) || (m_iHour42 > 24) ||   \
		(m_iHour51 < 0) || (m_iHour51 > 24) || (m_iHour52 < 0) || (m_iHour52 > 24) ||	\
		(m_iHour61 < 0) || (m_iHour61 > 24) || (m_iHour62 < 0) || (m_iHour62 > 24) ||	\
		(m_iHour71 < 0) || (m_iHour71 > 24) || (m_iHour72 < 0) || (m_iHour72 > 24) ||	\
		(m_iHour81 < 0) || (m_iHour81 > 24) || (m_iHour82 < 0) || (m_iHour82 > 24))
	{
		g_StringLanType(szLan, "小时范围在0 -- 24之间", "Hour between 0 - 24 ");
		AfxMessageBox(szLan);
		return FALSE;
	}
	if ((m_iMin11 < 0) || (m_iMin11 > 60) || (m_iMin12 < 0) || (m_iMin12 > 60) ||	\
		(m_iMin21 < 0) || (m_iMin21 > 60) || (m_iMin22 < 0) || (m_iMin22 > 60) ||	\
		(m_iMin31 < 0) || (m_iMin31 > 60) || (m_iMin32 < 0) || (m_iMin32 > 60) ||	\
		(m_iMin41 < 0) || (m_iMin41 > 60) || (m_iMin42 < 0) || (m_iMin42 > 60) ||   \
		(m_iMin51 < 0) || (m_iMin51 > 60) || (m_iMin52 < 0) || (m_iMin52 > 60) ||	\
		(m_iMin61 < 0) || (m_iMin61 > 60) || (m_iMin62 < 0) || (m_iMin62 > 60) ||	\
		(m_iMin71 < 0) || (m_iMin71 > 60) || (m_iMin72 < 0) || (m_iMin72 > 60) ||	\
		(m_iMin81 < 0) || (m_iMin81 > 60) || (m_iMin82 < 0) || (m_iMin82 > 60))
	{
		g_StringLanType(szLan, "分钟范围在0 -- 60之间", "Minute between 0 - 60 ");
		AfxMessageBox(szLan);
		return FALSE;
	}
	wStartTime[0] = (WORD)(m_iHour11 * 100 + m_iMin11);
	wStartTime[1] = (WORD)(m_iHour21 * 100 + m_iMin21);
	wStartTime[2] = (WORD)(m_iHour31 * 100 + m_iMin31);
	wStartTime[3] = (WORD)(m_iHour41 * 100 + m_iMin41);
	wStopTime[0] = (WORD)(m_iHour12 * 100 + m_iMin12);
	wStopTime[1] = (WORD)(m_iHour22 * 100 + m_iMin22);
	wStopTime[2] = (WORD)(m_iHour32 * 100 + m_iMin32);
	wStopTime[3] = (WORD)(m_iHour42 * 100 + m_iMin42);
	wStartTime[4] = (WORD)(m_iHour51 * 100 + m_iMin51);
	wStartTime[5] = (WORD)(m_iHour61 * 100 + m_iMin61);
	wStartTime[6] = (WORD)(m_iHour71 * 100 + m_iMin71);
	wStartTime[7] = (WORD)(m_iHour81 * 100 + m_iMin81);
	wStopTime[4] = (WORD)(m_iHour52 * 100 + m_iMin52);
	wStopTime[5] = (WORD)(m_iHour62 * 100 + m_iMin62);
	wStopTime[6] = (WORD)(m_iHour72 * 100 + m_iMin72);
	wStopTime[7] = (WORD)(m_iHour82 * 100 + m_iMin82);
	for (i = 0; i < MAX_TIMESEGMENT_V30; i++)
	{
		if ((wStartTime[i] > 2400) || (wStopTime[i] > 2400))
		{
			g_StringLanType(szLan, "布防时间不能超过24:00", "Fortify time can not be more than 24:00");
			AfxMessageBox(szLan);
			return FALSE;
		}
		if (wStartTime[i] > wStopTime[i])
		{
			g_StringLanType(szLan, "布防起始时间不能大于停止时间", "Fortify start time can not be larger than the record to stop time");
			AfxMessageBox(szLan);
			return FALSE;
		}
		for (j = 0; j < MAX_TIMESEGMENT_V30; j++)
		{
			if (i == j)
			{
				continue;
			}
			if ((wStartTime[i] > wStartTime[j]) && (wStartTime[i] < wStopTime[j]) ||	\
				(wStopTime[i] > wStartTime[j]) && (wStopTime[i] < wStopTime[j]))
			{
				g_StringLanType(szLan, "时间段不能重复", "time can not be repeated");
				AfxMessageBox(szLan);
				return FALSE;
			}
		}
	}
	return TRUE;
}


void CDlgRemoteMotionDetect::OnCbnSelchangeComboPrecisioin()
{
	UpdateData(TRUE);
	m_iSelPrecision = m_comboPrecision.GetCurSel();
	switch(m_iSelPrecision)
	{
	case 0://16*16;
		g_dwPrecision = 16/2;
		break;
	case 1://32*32
		g_dwPrecision = 32/2;
		break;
	case 2://64*64
		g_dwPrecision = 64/2;
		break;
	default:
		g_dwPrecision = 32/2;
		break;
	}
}

void CDlgRemoteMotionDetect::OnPaint() 
{	
	CreateTree();
	CDialog::OnPaint();
}


/*********************************************************
  Function:	CreateTree
  Desc:		Create alarm output-video channel connection
  Input:	
  Output:	
  Return:	
**********************************************************/
void CDlgRemoteMotionDetect::CreateTree(void)
{
	//m_treeAlarmOut.DeleteAllItems();
	g_CreateAlarmOutTree(m_treeAlarmOut, m_dwDevIndex, m_bAlarmOut);
	m_treeChan.DeleteAllItems();
	CString strTemp =_T("");
	CString strChanTmp = _T("");
	int i = 0;
 	HTREEITEM hChanItem = NULL;
// 	for (i = 0; i < MAX_ALARMOUT_V30; i++)
// 	{
// 		if ((i < m_dwAlarmOutNum) || (i >= MAX_ANALOG_ALARMOUT && i < (MAX_ANALOG_ALARMOUT + 32) && g_struDeviceInfo[m_dwDevIndex].bIPRet))
// 		{
// 			strTemp.Format(ALARM_OUT_FORMAT, i+1);
// 			hChanItem =  m_treeAlarmOut.InsertItem(strTemp, TVI_ROOT);
// 			m_treeAlarmOut.SetItemData(hChanItem, 1*1000 + i);
// 			TRACE(strTemp);
// 			if (m_bAlarmOut[i])
// 			{
// 			BOOL bRet = m_treeAlarmOut.SetCheck(hChanItem, TRUE);
// 			}
// 		}
// 	}
// 	m_treeAlarmOut.Expand(m_treeAlarmOut.GetRootItem(),TVE_EXPAND);

	for (i = 0; i < MAX_CHANNUM_V30; i++)
	{
		if (g_struDeviceInfo[m_dwDevIndex].struChanInfo[i].bEnable)
		{
			if (i < m_iChanCount)
			{
				strTemp.Format(ANALOG_C_FORMAT, i+g_struDeviceInfo[m_dwDevIndex].iStartChan);
				hChanItem =  m_treeChan.InsertItem(strTemp, TVI_ROOT);
				m_treeChan.SetItemData(hChanItem, 1*1000 + i);	
				if (g_lpMotionDetect->byRelRecordChan[i])
				{
					m_treeChan.SetCheck(hChanItem, TRUE);
				}
			}
			else if (i >= MAX_ANALOG_CHANNUM)
			{
				strTemp.Format(DIGITAL_C_FORMAT, i+g_struDeviceInfo[m_dwDevIndex].iStartChan-MAX_ANALOG_CHANNUM);
				hChanItem =  m_treeChan.InsertItem(strTemp, TVI_ROOT);
				m_treeChan.SetItemData(hChanItem, 2*1000 + i);	
				if (m_bRecordChan[i])
				{
					m_treeChan.SetCheck(hChanItem, TRUE);
				}
			}
		}
	}
	m_treeChan.Expand(m_treeChan.GetRootItem(),TVE_EXPAND);	
	UpdateData(FALSE);
}


void CDlgRemoteMotionDetect::OnClickTreeChan(NMHDR* pNMHDR, LRESULT* pResult) 
{
	UpdateData(TRUE);
	CPoint pt(0,0);
	CRect rc(0,0,0,0);
	GetCursorPos(&pt);
	GetDlgItem(IDC_TREE_CHAN)->GetWindowRect(&rc);
	ScreenToClient(&rc);
	ScreenToClient(&pt);
	pt.x = pt.x - rc.left;
	pt.y = pt.y - rc.top;

	UINT uFlag = 0;
	HTREEITEM hSelect = m_treeChan.HitTest(pt, &uFlag);

	if (NULL == hSelect) 
	{
		return;
	}
	m_treeChan.SelectItem(hSelect);
	DWORD dwIndex = m_treeChan.GetItemData(hSelect)%1000;
	BOOL bCheck = m_treeChan.GetCheck(hSelect);
	m_bRecordChan[dwIndex] = !bCheck;
	//
	if (uFlag != LVHT_TOLEFT)
	{
		m_treeChan.SetCheck(hSelect, !bCheck);
	}
	else
	{
		m_treeChan.SetCheck(hSelect, bCheck);
	}

	*pResult = 0;
}

void CDlgRemoteMotionDetect::OnClickTreeAlarmOut(NMHDR* pNMHDR, LRESULT* pResult) 
{
	UpdateData(TRUE);
	CPoint pt(0,0);
	CRect rc(0,0,0,0);
	GetCursorPos(&pt);
	GetDlgItem(IDC_TREE_ALARM_OUT)->GetWindowRect(&rc);
	ScreenToClient(&rc);
	ScreenToClient(&pt);
	pt.x = pt.x - rc.left;
	pt.y = pt.y - rc.top;

	UINT uFlag = 0;
	HTREEITEM hSelect = m_treeAlarmOut.HitTest(pt, &uFlag);

	if (NULL == hSelect) 
	{
		return;
	}
	m_treeAlarmOut.SelectItem(hSelect);
	DWORD dwIndex = m_treeAlarmOut.GetItemData(hSelect)%1000;
	BOOL bCheck = m_treeAlarmOut.GetCheck(hSelect);
	m_bAlarmOut[dwIndex] = !bCheck;
	
		if (uFlag != LVHT_TOLEFT)
	{
		m_treeAlarmOut.SetCheck(hSelect, !bCheck);
	}
	else
	{
		m_treeAlarmOut.SetCheck(hSelect, bCheck);
	}

	*pResult = 0;
}

BOOL CDlgRemoteMotionDetect::GetMotionHolidayHandle(NET_DVR_HOLIDAY_HANDLE &struHolidayHandle)
{
    DWORD dwReturn = 0;
    
    if (NET_DVR_GetDVRConfig(m_lLoginID, NET_DVR_GET_MOTION_HOLIDAY_HANDLE, m_iChanShowNum, &struHolidayHandle, sizeof(struHolidayHandle), &dwReturn))
    {
        g_pMainDlg->AddLog(m_dwDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_MOTION_HOLIDAY_HANDLE");
        return TRUE;
    }
    else
    {
        g_pMainDlg->AddLog(m_dwDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_MOTION_HOLIDAY_HANDLE");
        return FALSE;
    }
}

BOOL CDlgRemoteMotionDetect::SetMotionHolidayHandle(NET_DVR_HOLIDAY_HANDLE &struHolidayHandle)
{
    if (NET_DVR_SetDVRConfig(m_lLoginID, NET_DVR_SET_MOTION_HOLIDAY_HANDLE, m_iChanShowNum, &struHolidayHandle, sizeof(struHolidayHandle)))
    {
        g_pMainDlg->AddLog(m_dwDevIndex, OPERATION_SUCC_T, "NET_DVR_SET_MOTION_HOLIDAY_HANDLE");
        return TRUE;
    }
    else
    {
        g_pMainDlg->AddLog(m_dwDevIndex, OPERATION_FAIL_T, "NET_DVR_SET_MOTION_HOLIDAY_HANDLE");
        return FALSE;
    }
}
