// DlgJpegCaptureCfg.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgJpegCaptureCfg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgJpegCaptureCfg dialog

CDlgJpegCaptureCfg::CDlgJpegCaptureCfg(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgJpegCaptureCfg::IDD, pParent)
	, m_bCheckAllDay(FALSE)
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
	, m_pCompresscfgAbility(NULL)
{
	//{{AFX_DATA_INIT(CDlgJpegCaptureCfg)
	m_dwIntervalEvent = 0;
	m_dwIntrvalTime = 0;
	m_bEnableCapture = FALSE;
	m_dwPicSaveDays = 0;
	m_csIP = _T("");
	m_dwPort = 0;
	m_csPassword = _T("");
	m_csUserName = _T("");
	m_csIP2 = _T("");
	m_dwPort2 = 0;
	m_csPassword2 = _T("");
	m_csUserName2 = _T("");
	m_byEventCapTimes = 0;
	m_bChkAnony = FALSE;
	m_csMainFirstUserDir = _T("");
	m_csMainSecordUserDir = _T("");
	m_bChkAnony2 = FALSE;
	m_csSubSecordUserDir = _T("");
	m_csSubFirstUserDir = _T("");
	m_csIPv6 = _T("");
	m_csIP2v6 = _T("");
	//}}AFX_DATA_INIT
    m_lUserID = -1;
    m_lChannelNum = -1;
	m_iChanShowNO = -1;
    m_lChannel = -1;
	m_iChanCount = 0;
	m_dwDevIndex = 0;
    memset(&m_struJpegCapture, 0, sizeof(m_struJpegCapture));
    memset(&m_struCaptureSched, 0, sizeof(m_struCaptureSched));
	memset(&m_strFtpCfg, 0, sizeof(m_strFtpCfg));
	m_pCompresscfgAbility = new NET_DVR_COMPRESSIONCFG_ABILITY;
	memset(m_pCompresscfgAbility, 0, sizeof(NET_DVR_COMPRESSIONCFG_ABILITY));
}

void CDlgJpegCaptureCfg::GetResolutionAbility()
{
    for (int nAbilityCount = 0; nAbilityCount < m_pCompresscfgAbility->dwAbilityNum; nAbilityCount++)
    {
        if (MAIN_RESOLUTION_ABILITY == m_pCompresscfgAbility->struAbilityNode[nAbilityCount].dwAbilityType)
        {
            m_comboTimePicResolution.ResetContent();
			m_comboEventPicResolution.ResetContent();
            for (int i = 0; i < m_pCompresscfgAbility->struAbilityNode[nAbilityCount].dwNodeNum; i++)
            {
				m_comboTimePicResolution.AddString((char*)m_pCompresscfgAbility->struAbilityNode[nAbilityCount].struDescNode[i].byDescribe);
                m_comboTimePicResolution.SetItemData(i, m_pCompresscfgAbility->struAbilityNode[nAbilityCount].struDescNode[i].iValue);

                m_comboEventPicResolution.AddString((char*)m_pCompresscfgAbility->struAbilityNode[nAbilityCount].struDescNode[i].byDescribe);
                m_comboEventPicResolution.SetItemData(i, m_pCompresscfgAbility->struAbilityNode[nAbilityCount].struDescNode[i].iValue);
            }
        }
    }
}

void CDlgJpegCaptureCfg::SetTimeResolutionCurSel(DWORD dwData)
{
    for (int i = 0; i < m_comboTimePicResolution.GetCount(); i++)
    {
        if (m_comboTimePicResolution.GetItemData(i) == dwData)
        {
            m_comboTimePicResolution.SetCurSel(i);
            return;
        }
    }
}

void CDlgJpegCaptureCfg::SetEventResolutionCurSel(DWORD dwData)
{
    for (int i = 0; i < m_comboEventPicResolution.GetCount(); i++)
    {
        if (m_comboEventPicResolution.GetItemData(i) == dwData)
        {
            m_comboEventPicResolution.SetCurSel(i);
            return;
        }
    }
}

BOOL CDlgJpegCaptureCfg::GetCompressCfgAbility(DWORD dwIPChanIndex)
{
    if (!NET_DVR_GetDeviceAbility(m_lUserID, PIC_CAPTURE_ABILITY, (char*)&dwIPChanIndex, sizeof(dwIPChanIndex), (char*)m_pCompresscfgAbility, sizeof(NET_DVR_COMPRESSIONCFG_ABILITY)))
    {
        g_pMainDlg->AddLog(m_dwDevIndex, OPERATION_FAIL_T, "PIC_CAPTURE_ABILITY");
        return FALSE;    
    }
    else
    {
        g_pMainDlg->AddLog(m_dwDevIndex, OPERATION_SUCC_T, "PIC_CAPTURE_ABILITY");
        return TRUE;
    }
}

/*********************************************************
Function:	TimeTest
Desc:		check time settings
Input:	
Output:	
Return:	TRUE,correct schedule;FALSE,incorrect schedule;
**********************************************************/
BOOL CDlgJpegCaptureCfg::TimeTest()
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
		g_StringLanType(szLan, "Сʱ��Χ��0 -- 24֮��", "Hour between 0 - 24 ");
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
		g_StringLanType(szLan, "���ӷ�Χ��0 -- 60֮��", "Minute between 0 - 60 ");
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
			g_StringLanType(szLan, "����ʱ�䲻�ܳ���24:00", "Fortify time can not be more than 24:00");
			AfxMessageBox(szLan);
			return FALSE;
		}
		if (wStartTime[i] > wStopTime[i])
		{
			g_StringLanType(szLan, "������ʼʱ�䲻�ܴ���ֹͣʱ��", "Fortify start time can not be larger than the record to stop time");
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
				g_StringLanType(szLan, "ʱ��β����ظ�", "time can not be repeated");
				AfxMessageBox(szLan);
				return FALSE;
			}
		}
	}
	return TRUE;
}

void CDlgJpegCaptureCfg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgJpegCaptureCfg)
	DDX_Control(pDX, IDC_COMBO_PROTOCALTYPE2, m_comboProtocalType2);
	DDX_Control(pDX, IDC_COMBO_SERVERTYPE2, m_comboServerType2);
	DDX_Control(pDX, IDC_COMBO_SERVERTYPE, m_comboServerType);
	DDX_Control(pDX, IDC_COMBO_PROTOCALTYPE, m_comboProtocalType);
	DDX_Control(pDX, IDC_COMBOUSEFTPUP2, m_UseFTPUpCtrl2);
	DDX_Control(pDX, IDC_COMBO_SUB_SECORD_DIRMODE, m_comboSubSecordDirModeCtrl);
	DDX_Control(pDX, IDC_COMBO_SUB_FIRST_DIRMODE, m_comboSubFirstDirModeCtr);
	DDX_Control(pDX, IDC_COMBO_SUB_DIR_LEVEL, m_DirLevelCtrl2);
	
	DDX_Control(pDX, IDC_COMBO_DIR_LEVEL, m_DirLevelCtrl);
	DDX_Control(pDX, IDC_COMBOUSEFTPUP, m_UseFTPUpCtrl);
	DDX_Control(pDX, IDC_COMBO_FIRST_DIRMODE, m_comboMainFirstDirModeCtr);
	DDX_Control(pDX, IDC_TREE_EVENT, m_treeEvent);
	DDX_Control(pDX, IDC_TREE_ALARMIN, m_treeAlarmin);
	DDX_Control(pDX, IDC_COMBO_ALARM_IN, m_comboAlarmIn);
	DDX_Control(pDX, IDC_COMBO_OTHER_EVENT, m_comboEvent);
	DDX_Control(pDX, IDC_COMBO_TIME_PIC_RESOLUTION, m_comboTimePicResolution);
	DDX_Control(pDX, IDC_COMBO_TIME_PIC_QUALITY, m_comboTimePicQuality);
	DDX_Control(pDX, IDC_COMBO_EVENT_PIC_RESOLUTION, m_comboEventPicResolution);
	DDX_Control(pDX, IDC_COMBO_EVENT_PIC_QUALITY, m_comboEventPicQuality);
	DDX_Text(pDX, IDC_EDIT_CAPTURE_INTERVAL_EVENT, m_dwIntervalEvent);
	DDX_Text(pDX, IDC_EDIT_CAPTURE_INTERVAL_TIME, m_dwIntrvalTime);
	DDX_Control(pDX, IDC_COMBO_WEEK_DAY, m_comboWeekday);
	DDX_Check(pDX, IDC_CHK_ALL_DAY, m_bCheckAllDay);
	DDX_Control(pDX, IDC_COMBO_ALL_DAY_TYPE, m_comboAllDayType);
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
	DDX_Control(pDX, IDC_COMBO_TIME_REC_TYPE1, m_comboTimeRecType1);
	DDX_Control(pDX, IDC_COMBO_TIME_REC_TYPE2, m_comboTimeRecType2);
	DDX_Control(pDX, IDC_COMBO_TIME_REC_TYPE3, m_comboTimeRecType3);
	DDX_Control(pDX, IDC_COMBO_TIME_REC_TYPE4, m_comboTimeRecType4);
	DDX_Control(pDX, IDC_COMBO_COPY_WEEKDAY, m_comboCopyWeekday);
	DDX_Control(pDX, IDC_COMBO_TIME_REC_TYPE5, m_comboTimeRecType5);
	DDX_Control(pDX, IDC_COMBO_TIME_REC_TYPE6, m_comboTimeRecType6);
	DDX_Control(pDX, IDC_COMBO_TIME_REC_TYPE7, m_comboTimeRecType7);
	DDX_Control(pDX, IDC_COMBO_TIME_REC_TYPE8, m_comboTimeRecType8);
	DDX_Check(pDX, IDC_CHK_ENABLE_CAPTURE, m_bEnableCapture);
	DDX_Text(pDX, IDC_EDIT_PICTURE_SAVE_DAYS, m_dwPicSaveDays);
	DDX_Control(pDX, IDC_COMBO_CAPTURE_INTERVAL_EVENT, m_comboIntervalEvent);
	DDX_Control(pDX, IDC_COMBO_CAPTURE_INTERVAL_TIME, m_comboIntervalTime);
	DDX_Control(pDX, IDC_COMBO_SECORD_DIRMODE, m_comboMainSecordDirModeCtrl);
	DDX_Text(pDX, IDC_EDIT_IP, m_csIP);
	DDX_Text(pDX, IDC_EDIT_PORT, m_dwPort);
	DDX_Text(pDX, IDC_EDIT_PSWD, m_csPassword);
	DDX_Text(pDX, IDC_EDIT_USER, m_csUserName);
	DDX_Text(pDX, IDC_EDIT_IP2, m_csIP2);
	DDX_Text(pDX, IDC_EDIT_PORT2, m_dwPort2);
	DDX_Text(pDX, IDC_EDIT_PSWD2, m_csPassword2);
	DDX_Text(pDX, IDC_EDIT_USER2, m_csUserName2);
	DDX_Text(pDX, IDC_EDIT_EVENT_CAPTIMES, m_byEventCapTimes);
	DDX_Check(pDX, IDC_CHK_ANONY_ENABLE, m_bChkAnony);
	DDX_Text(pDX, IDC_EDIT_FIRST_USERDIR, m_csMainFirstUserDir);
	DDX_Text(pDX, IDC_EDIT_SECOND_USERDIR, m_csMainSecordUserDir);
	DDX_Check(pDX, IDC_CHK_ANONY_ENABLE_2, m_bChkAnony2);
	DDX_Text(pDX, IDC_EDIT_SUB_SECOND_USERDIR, m_csSubSecordUserDir);
	DDX_Text(pDX, IDC_EDIT_SUB_FIRST_USERDIR, m_csSubFirstUserDir);
	DDX_Text(pDX, IDC_EDIT_IPV6_FIRST, m_csIPv6);
	DDX_Text(pDX, IDC_EDIT_IP2V6, m_csIP2v6);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgJpegCaptureCfg, CDialog)
	//{{AFX_MSG_MAP(CDlgJpegCaptureCfg)
	ON_BN_CLICKED(IDC_BUTTON_UPDATE, OnButtonUpdate)
	ON_CBN_SELCHANGE(IDC_COMBO_ALARM_IN, OnSelchangeComboAlarmIn)
	ON_CBN_SELCHANGE(IDC_COMBO_OTHER_EVENT, OnSelchangeComboOtherEvent)
	ON_NOTIFY(NM_CLICK, IDC_TREE_ALARMIN, OnClickTreeAlarmin)
	ON_NOTIFY(NM_CLICK, IDC_TREE_EVENT, OnClickTreeEvent)
	ON_BN_CLICKED(IDC_BTN_SET_JPEG_CAPTURE, OnBtnSetJpegCapture)
	ON_BN_CLICKED(IDC_BUTTON_EXIT, OnButtonExit)
	ON_BN_CLICKED(IDC_CAPTURE_DAY_OK, OnCaptureDayOk)
	ON_CBN_SELCHANGE(IDC_COMBO_WEEKDAY, OnSelchangeComboWeekday)
	ON_BN_CLICKED(IDC_BUTTON_UPDATE_SCHED, OnButtonUpdateSched)
	ON_BN_CLICKED(IDC_BTN_SET_JPEG_CAPTURE_SCHED, OnBtnSetJpegCaptureSched)
	ON_BN_CLICKED(IDC_BUTTON_UPDATE_FTP, OnButtonUpdateFtp)
	ON_CBN_SELCHANGE(IDC_COMBO_DIR_LEVEL, OnSelchangeComboDirLevel)
	ON_CBN_SELCHANGE(IDC_COMBO_SUB_DIR_LEVEL, OnSelchangeComboSubDirLevel)
	ON_CBN_SELCHANGE(IDC_COMBO_FIRST_DIRMODE, OnSelchangeComboDirModeOne)
	ON_CBN_SELCHANGE(IDC_COMBO_SECORD_DIRMODE, OnSelchangeComboDirModeTwo)
	ON_CBN_SELCHANGE(IDC_COMBO_SUB_FIRST_DIRMODE, OnSelchangeSubComboDirModeOne)
	ON_CBN_SELCHANGE(IDC_COMBO_SUB_SECORD_DIRMODE, OnSelchangeSubComboDirModeTwo)	
	ON_BN_CLICKED(IDC_BTN_SET_FTP, OnBtnSetFtp)
	ON_BN_CLICKED(IDC_BTN_DAY_COPY, OnBtnDayCopy)
	ON_BN_CLICKED(IDC_CHK_ALL_DAY, OnChkAllDay)
	ON_BN_CLICKED(IDC_BUTTON_ALARMIN_ALL, OnButtonAlarminAll)
	ON_BN_CLICKED(IDC_BUTTON_ALARMIN_CLEAN, OnButtonAlarminClean)
	ON_BN_CLICKED(IDC_BUTTON_EVENT_ALL, OnButtonEventAll)
	ON_BN_CLICKED(IDC_BUTTON_EVENT_CLEAN, OnButtonEventClean)
	ON_BN_CLICKED(IDC_BUTTON_UPDATE_FTP2, OnButtonUpdateFtp2)
	ON_BN_CLICKED(IDC_BTN_SET_FTP2, OnBtnSetFtp2)
	ON_CBN_EDITCHANGE(IDC_COMBO_SERVERTYPE2, OnEditchangeComboServertype2)
	ON_CBN_EDITCHANGE(IDC_COMBO_SERVERTYPE, OnEditchangeComboServertype)
	ON_CBN_SELCHANGE(IDC_COMBO_SERVERTYPE, OnSelchangeComboServertype)
	ON_CBN_SELCHANGE(IDC_COMBO_SERVERTYPE2, OnSelchangeComboServertype2)

	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

///////////////////////////////////////////////////////////////////////////
//CDlgJpegCaptureCfg messagehandlers

BOOL CDlgJpegCaptureCfg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	char szLan[128] = {0};

	//add alarmin chan
	m_comboAlarmIn.ResetContent();    
	m_comboAlarmIn.AddString("AlarmIn1");
	m_comboAlarmIn.SetCurSel(0);

	//add other event type
    m_comboEvent.ResetContent();    
    g_StringLanType(szLan, "�ƶ����", "Motion");
    m_comboEvent.AddString(szLan);
    g_StringLanType(szLan, "��Ƶ�ڵ�", "Hide");
    m_comboEvent.AddString(szLan);
	g_StringLanType(szLan, "��Ƶ��ʧ", "Lost");
    m_comboEvent.AddString(szLan);
	g_StringLanType(szLan, "PIR����", "PIR");
    m_comboEvent.AddString(szLan);
	g_StringLanType(szLan, "���߱���", "Wireless");
    m_comboEvent.AddString(szLan);
	g_StringLanType(szLan, "���ȱ���", "Call help");
    m_comboEvent.AddString(szLan);
	m_comboEvent.SetCurSel(0);

	m_comboTimePicResolution.ResetContent();
    m_comboTimePicResolution.AddString("CIF");
    m_comboTimePicResolution.AddString("QCIF");
    m_comboTimePicResolution.AddString("D1");
	m_comboTimePicResolution.SetCurSel(0);

    m_comboEventPicResolution.ResetContent();
    m_comboEventPicResolution.AddString("CIF");
    m_comboEventPicResolution.AddString("QCIF");
    m_comboEventPicResolution.AddString("D1");
	m_comboEventPicResolution.SetCurSel(0);

	if (GetCompressCfgAbility(m_iChanShowNO))
	{
		GetResolutionAbility();
	}

	m_comboEventPicQuality.ResetContent();
	m_comboTimePicQuality.ResetContent();
	g_StringLanType(szLan, "���", "Best");
	m_comboEventPicQuality.AddString(szLan);    
    m_comboTimePicQuality.AddString(szLan);
	g_StringLanType(szLan, "�Ϻ�", "Better");
    m_comboEventPicQuality.AddString(szLan);
    m_comboTimePicQuality.AddString(szLan);
	g_StringLanType(szLan, "һ��", "Normal");
    m_comboEventPicQuality.AddString(szLan);
    m_comboTimePicQuality.AddString(szLan);
	m_comboEventPicQuality.SetCurSel(0);
	m_comboTimePicQuality.SetCurSel(0);	
	m_comboIntervalEvent.SetCurSel(1);
	m_comboIntervalTime.SetCurSel(1);
	m_comboWeekday.SetCurSel(0);
	m_comboCopyWeekday.SetCurSel(0);

	OnButtonUpdate();
	OnButtonUpdateSched();
	OnButtonUpdateFtp();
	//OnButtonUpdateFtp2();
	return TRUE;
}

/*********************************************************
Function:	EnableControl
Desc:		Dialog control enable
Input:	
Output:	
Return:	
	**********************************************************/
void CDlgJpegCaptureCfg::EnableControl(BOOL bEnable)
{
	GetDlgItem(IDC_EDIT_HOUR11)->EnableWindow(bEnable);
	GetDlgItem(IDC_EDIT_HOUR21)->EnableWindow(bEnable);
	GetDlgItem(IDC_EDIT_HOUR31)->EnableWindow(bEnable);
	GetDlgItem(IDC_EDIT_HOUR41)->EnableWindow(bEnable);
	GetDlgItem(IDC_EDIT_HOUR51)->EnableWindow(bEnable);
	GetDlgItem(IDC_EDIT_HOUR61)->EnableWindow(bEnable);
	GetDlgItem(IDC_EDIT_HOUR71)->EnableWindow(bEnable);
	GetDlgItem(IDC_EDIT_HOUR81)->EnableWindow(bEnable);
	
	GetDlgItem(IDC_EDIT_MIN11)->EnableWindow(bEnable);
	GetDlgItem(IDC_EDIT_MIN21)->EnableWindow(bEnable);
	GetDlgItem(IDC_EDIT_MIN31)->EnableWindow(bEnable);
	GetDlgItem(IDC_EDIT_MIN41)->EnableWindow(bEnable);
	GetDlgItem(IDC_EDIT_MIN51)->EnableWindow(bEnable);
	GetDlgItem(IDC_EDIT_MIN61)->EnableWindow(bEnable);
	GetDlgItem(IDC_EDIT_MIN71)->EnableWindow(bEnable);
	GetDlgItem(IDC_EDIT_MIN81)->EnableWindow(bEnable);
	
	GetDlgItem(IDC_EDIT_HOUR12)->EnableWindow(bEnable);
	GetDlgItem(IDC_EDIT_HOUR22)->EnableWindow(bEnable);
	GetDlgItem(IDC_EDIT_HOUR32)->EnableWindow(bEnable);
	GetDlgItem(IDC_EDIT_HOUR42)->EnableWindow(bEnable);
	GetDlgItem(IDC_EDIT_HOUR52)->EnableWindow(bEnable);
	GetDlgItem(IDC_EDIT_HOUR62)->EnableWindow(bEnable);
	GetDlgItem(IDC_EDIT_HOUR72)->EnableWindow(bEnable);
	GetDlgItem(IDC_EDIT_HOUR82)->EnableWindow(bEnable);
	
	GetDlgItem(IDC_EDIT_MIN12)->EnableWindow(bEnable);
	GetDlgItem(IDC_EDIT_MIN22)->EnableWindow(bEnable);
	GetDlgItem(IDC_EDIT_MIN32)->EnableWindow(bEnable);
	GetDlgItem(IDC_EDIT_MIN42)->EnableWindow(bEnable);
	GetDlgItem(IDC_EDIT_MIN52)->EnableWindow(bEnable);
	GetDlgItem(IDC_EDIT_MIN62)->EnableWindow(bEnable);
	GetDlgItem(IDC_EDIT_MIN72)->EnableWindow(bEnable);
	GetDlgItem(IDC_EDIT_MIN82)->EnableWindow(bEnable);
	
	GetDlgItem(IDC_COMBO_TIME_REC_TYPE1)->EnableWindow(bEnable);
	GetDlgItem(IDC_COMBO_TIME_REC_TYPE2)->EnableWindow(bEnable);
	GetDlgItem(IDC_COMBO_TIME_REC_TYPE3)->EnableWindow(bEnable);
	GetDlgItem(IDC_COMBO_TIME_REC_TYPE4)->EnableWindow(bEnable);
	GetDlgItem(IDC_COMBO_TIME_REC_TYPE5)->EnableWindow(bEnable);
	GetDlgItem(IDC_COMBO_TIME_REC_TYPE6)->EnableWindow(bEnable);
	GetDlgItem(IDC_COMBO_TIME_REC_TYPE7)->EnableWindow(bEnable);
	GetDlgItem(IDC_COMBO_TIME_REC_TYPE8)->EnableWindow(bEnable);
	GetDlgItem(IDC_COMBO_ALL_DAY_TYPE)->EnableWindow(!bEnable);
}

void CDlgJpegCaptureCfg::OnButtonUpdate() 
{
	DWORD dwBytesReturned = 0;
	if(!NET_DVR_GetDVRConfig(m_lUserID, NET_DVR_GET_JPEG_CAPTURE_CFG, m_lChannel, &m_struJpegCapture, sizeof(m_struJpegCapture), &dwBytesReturned))
	{
		g_pMainDlg->AddLog(m_dwDevIndex, OPERATION_FAIL_T, "chan[%d] NET_DVR_GET_JPEG_CAPTURE_CFG", m_lChannel);
	}
	else
	{
		g_pMainDlg->AddLog(m_dwDevIndex, OPERATION_SUCC_T, "chan[%d] NET_DVR_GET_JPEG_CAPTURE_CFG", m_lChannel);
		m_comboTimePicQuality.SetCurSel(m_struJpegCapture.struTimingCapture.struJpegPara.wPicQuality);
		SetTimeResolutionCurSel(m_struJpegCapture.struTimingCapture.struJpegPara.wPicSize);
		SetEventResolutionCurSel(m_struJpegCapture.struEventCapture.struJpegPara.wPicSize);
		m_comboEventPicQuality.SetCurSel(m_struJpegCapture.struEventCapture.struJpegPara.wPicQuality);
	//	m_dwIntrvalTime = m_struJpegCapture.struTimingCapture.dwPicInterval;
	//	m_dwIntervalEvent = m_struJpegCapture.struEventCapture.dwPicInterval;
		m_comboIntervalEvent.SetCurSel(m_struJpegCapture.struEventCapture.dwPicInterval - 1);
		m_comboIntervalTime.SetCurSel(m_struJpegCapture.struTimingCapture.dwPicInterval - 1);
		m_byEventCapTimes = m_struJpegCapture.struEventCapture.byCapTimes;
		OnSelchangeComboAlarmIn();
		OnSelchangeComboOtherEvent();
	}
	UpdateData(FALSE);
}

void CDlgJpegCaptureCfg::OnSelchangeComboAlarmIn() 
{
	int iIndex = m_comboAlarmIn.GetCurSel();
	CreateChanTreeAlarmIn(iIndex);
}

void CDlgJpegCaptureCfg::OnSelchangeComboOtherEvent() 
{
	int iIndex = m_comboEvent.GetCurSel();
	CreateChanTreeEvent(iIndex);
}

void CDlgJpegCaptureCfg::CreateChanTreeAlarmIn(int iIndex, BOOL bSetAll, BOOL bClearAll)
{
	//create channel tree
	m_treeAlarmin.DeleteAllItems();
	CString strTemp =_T("");
	CString strChanTmp = _T("");
	int i = 0;
	HTREEITEM hChanItem = NULL;
	if (m_iChanCount <= 0)
	{
		m_treeAlarmin.EnableWindow(FALSE);
	}
	
	for (i = 0; i < MAX_CHANNUM_V30; i++)
	{
		if ((i < m_iChanCount) && g_struDeviceInfo[m_dwDevIndex].struChanInfo[i].bEnable)
		{
			strTemp.Format(ANALOG_C_FORMAT, i+g_struDeviceInfo[m_dwDevIndex].iStartChan);
			hChanItem =  m_treeAlarmin.InsertItem(strTemp, 0, 0, TVI_ROOT);
			m_treeAlarmin.SetItemData(hChanItem, 0*1000 + i);
			if(bSetAll)
			{
				m_struJpegCapture.struEventCapture.struAlarmInCapture[iIndex].byChan[i/8] |= (0x01<<(i%8));
			}
			if(bClearAll)
			{
				m_struJpegCapture.struEventCapture.struAlarmInCapture[iIndex].byChan[i/8] = 0;
			}
			if(((m_struJpegCapture.struEventCapture.struAlarmInCapture[iIndex].byChan[i/8] >> (i%8)) & 0x01) == 1)
			{
		        m_treeAlarmin.SetCheck(hChanItem, TRUE);
			}
		}
		else if (i >= MAX_ANALOG_CHANNUM && g_struDeviceInfo[m_dwDevIndex].struChanInfo[i].bEnable)
		{
			if(bSetAll)
			{
				m_struJpegCapture.struEventCapture.struAlarmInCapture[iIndex].byChan[i/8] |= (0x01<<(i%8));
			}
			if(bClearAll)
			{
				m_struJpegCapture.struEventCapture.struAlarmInCapture[iIndex].byChan[i/8] = 0;
			}
			strTemp.Format(DIGITAL_C_FORMAT, i+g_struDeviceInfo[m_dwDevIndex].iStartChan-MAX_ANALOG_CHANNUM);
			hChanItem =  m_treeAlarmin.InsertItem(strTemp, 0, 0, TVI_ROOT);
			m_treeAlarmin.SetItemData(hChanItem, 1*1000 + i);
			if(((m_struJpegCapture.struEventCapture.struAlarmInCapture[iIndex].byChan[i/8] >> (i%8)) & 0x01) == 1)
			{
			   m_treeAlarmin.SetCheck(hChanItem, TRUE);
			}
		}
	}
	m_treeAlarmin.SelectItem(hChanItem);
	m_treeAlarmin.Expand(m_treeAlarmin.GetRootItem(),TVE_EXPAND);
}

void CDlgJpegCaptureCfg::CreateChanTreeEvent(int iIndex, BOOL bSetAll, BOOL bClearAll)
{
	//create channel tree
	m_treeEvent.DeleteAllItems();
	CString strTemp =_T("");
	CString strChanTmp = _T("");
	int i = 0;
	HTREEITEM hChanItem = NULL;
	if (m_iChanCount <= 0)
	{
		m_treeEvent.EnableWindow(FALSE);
	}
	
	for (i = 0; i < MAX_CHANNUM_V30; i++)
	{
		if ((i < m_iChanCount) && g_struDeviceInfo[m_dwDevIndex].struChanInfo[i].bEnable)
		{
			if(bSetAll)
			{
				m_struJpegCapture.struEventCapture.struRelCaptureChan[iIndex].byChan[i/8] |= (0x01<<(i%8));
			}
			if(bClearAll)
			{
				m_struJpegCapture.struEventCapture.struRelCaptureChan[iIndex].byChan[i/8] = 0;
			}
			strTemp.Format(ANALOG_C_FORMAT, i+g_struDeviceInfo[m_dwDevIndex].iStartChan);
			hChanItem =  m_treeEvent.InsertItem(strTemp, 0, 0, TVI_ROOT);
			m_treeEvent.SetItemData(hChanItem, 0*1000 + i);
			if(((m_struJpegCapture.struEventCapture.struRelCaptureChan[iIndex].byChan[i/8] >> (i%8)) & 0x01) == 1)
			{
				m_treeEvent.SetCheck(hChanItem, TRUE);
			}
		}
		else if (i >= MAX_ANALOG_CHANNUM && g_struDeviceInfo[m_dwDevIndex].struChanInfo[i].bEnable)
		{
			if(bSetAll)
			{
				m_struJpegCapture.struEventCapture.struRelCaptureChan[iIndex].byChan[i/8] |= (0x01<<(i%8));
			}
			if(bClearAll)
			{
				m_struJpegCapture.struEventCapture.struRelCaptureChan[iIndex].byChan[i/8] = 0;
			}
			strTemp.Format(DIGITAL_C_FORMAT, i+g_struDeviceInfo[m_dwDevIndex].iStartChan-MAX_ANALOG_CHANNUM);
			hChanItem =  m_treeEvent.InsertItem(strTemp, 0, 0, TVI_ROOT);
			m_treeEvent.SetItemData(hChanItem, 1*1000 + i);
			if(((m_struJpegCapture.struEventCapture.struRelCaptureChan[iIndex].byChan[i/8] >> (i%8)) & 0x01) == 1)
			{
				m_treeEvent.SetCheck(hChanItem, TRUE);
			}
		}
	}
	m_treeEvent.SelectItem(hChanItem);
	m_treeEvent.Expand(m_treeEvent.GetRootItem(),TVE_EXPAND);
}

void CDlgJpegCaptureCfg::OnClickTreeAlarmin(NMHDR* pNMHDR, LRESULT* pResult) 
{
	UpdateData(TRUE);
	CPoint pt(0,0);
	CRect rc(0,0,0,0);
	GetCursorPos(&pt);
	GetDlgItem(IDC_TREE_ALARMIN)->GetWindowRect(&rc);
	ScreenToClient(&rc);
	ScreenToClient(&pt);
	pt.x = pt.x - rc.left;
	pt.y = pt.y - rc.top;
	
	UINT uFlag = 0;
	HTREEITEM hSelect = m_treeAlarmin.HitTest(pt, &uFlag);
	
	if (NULL == hSelect) 
	{
		return;
	}
	m_treeAlarmin.SelectItem(hSelect);
	DWORD dwIndex = m_treeAlarmin.GetItemData(hSelect)%1000;
	BOOL bCheck = m_treeAlarmin.GetCheck(hSelect);
	m_struJpegCapture.struEventCapture.struAlarmInCapture[0].byChan[dwIndex/8] |=  ((!bCheck)<<(dwIndex%8));
	//switch checkbox status on click
	if (uFlag != LVHT_TOLEFT)
	{
		m_treeAlarmin.SetCheck(hSelect, !bCheck);
	}
	else
	{
		m_treeAlarmin.SetCheck(hSelect, bCheck);
	}
	
	*pResult = 0;
}

void CDlgJpegCaptureCfg::OnClickTreeEvent(NMHDR* pNMHDR, LRESULT* pResult) 
{
	UpdateData(TRUE);
	CPoint pt(0,0);
	CRect rc(0,0,0,0);
	GetCursorPos(&pt);
	GetDlgItem(IDC_TREE_EVENT)->GetWindowRect(&rc);
	ScreenToClient(&rc);
	ScreenToClient(&pt);
	pt.x = pt.x - rc.left;
	pt.y = pt.y - rc.top;
	
	UINT uFlag = 0;
	HTREEITEM hSelect = m_treeAlarmin.HitTest(pt, &uFlag);
	int iEventIndex = m_comboEvent.GetCurSel();

	if (NULL == hSelect) 
	{
		return;
	}
	m_treeEvent.SelectItem(hSelect);
	DWORD dwIndex = m_treeEvent.GetItemData(hSelect)%1000;
	BOOL bCheck = m_treeEvent.GetCheck(hSelect);
	m_struJpegCapture.struEventCapture.struRelCaptureChan[iEventIndex].byChan[dwIndex/8] |=  ((!bCheck)<<(dwIndex%8));
	//switch checkbox status on click
	if (uFlag != LVHT_TOLEFT)
	{
		m_treeEvent.SetCheck(hSelect, !bCheck);
	}
	else
	{
		m_treeEvent.SetCheck(hSelect, bCheck);
	}
	
	*pResult = 0;
}

void CDlgJpegCaptureCfg::OnBtnSetJpegCapture() 
{
	UpdateData(TRUE);

	m_struJpegCapture.struTimingCapture.struJpegPara.wPicSize = m_comboTimePicResolution.GetItemData(m_comboTimePicResolution.GetCurSel());
	m_struJpegCapture.struTimingCapture.struJpegPara.wPicQuality = m_comboTimePicQuality.GetCurSel();
	m_struJpegCapture.struEventCapture.struJpegPara.wPicSize = m_comboEventPicResolution.GetItemData(m_comboEventPicResolution.GetCurSel());
	m_struJpegCapture.struEventCapture.struJpegPara.wPicQuality = m_comboEventPicQuality.GetCurSel();
	//m_struJpegCapture.struTimingCapture.dwPicInterval = m_dwIntrvalTime;
	//m_struJpegCapture.struEventCapture.dwPicInterval = m_dwIntervalEvent;
	m_struJpegCapture.struEventCapture.byCapTimes = m_byEventCapTimes;
    m_struJpegCapture.struTimingCapture.dwPicInterval = m_comboIntervalTime.GetCurSel() + 1;
	m_struJpegCapture.struEventCapture.dwPicInterval = m_comboIntervalEvent.GetCurSel() + 1;	


	if(!NET_DVR_SetDVRConfig(m_lUserID, NET_DVR_SET_JPEG_CAPTURE_CFG, m_lChannel, &m_struJpegCapture, sizeof(m_struJpegCapture)))
	{
		g_pMainDlg->AddLog(m_dwDevIndex, OPERATION_FAIL_T, "chan[%d] NET_DVR_SET_JPEG_CAPTURE_CFG", m_lChannel);
	}
	else
	{
		g_pMainDlg->AddLog(m_dwDevIndex, OPERATION_SUCC_T, "chan[%d] NET_DVR_SET_JPEG_CAPTURE_CFG", m_lChannel);
	}	
}

void CDlgJpegCaptureCfg::OnButtonExit() 
{
	if (m_pCompresscfgAbility != NULL)
	{
		delete m_pCompresscfgAbility;
		m_pCompresscfgAbility = NULL;
	}
	CDialog::OnCancel();
}

void CDlgJpegCaptureCfg::OnCaptureDayOk() 
{
	UpdateData(TRUE);
	if (!TimeTest())
	{
		return;
	}
    
	int iIndex = m_comboWeekday.GetCurSel();

    if (7 == iIndex) // ���� ������ 
    {
        m_struCaptureSched.struCaptureHoliday.byAllDayCapture = (WORD)m_bCheckAllDay;
        if (m_bCheckAllDay)
        {		
            m_struCaptureSched.struCaptureHoliday.byCaptureType = (BYTE)m_comboAllDayType.GetCurSel();
        }
		else
		{
			m_struCaptureSched.struHolidaySched[0].byCaptureType = (BYTE)m_comboTimeRecType1.GetCurSel();
			m_struCaptureSched.struHolidaySched[1].byCaptureType = (BYTE)m_comboTimeRecType2.GetCurSel();
			m_struCaptureSched.struHolidaySched[2].byCaptureType = (BYTE)m_comboTimeRecType3.GetCurSel();
			m_struCaptureSched.struHolidaySched[3].byCaptureType = (BYTE)m_comboTimeRecType4.GetCurSel();	
			m_struCaptureSched.struHolidaySched[4].byCaptureType = (BYTE)m_comboTimeRecType5.GetCurSel();
			m_struCaptureSched.struHolidaySched[5].byCaptureType = (BYTE)m_comboTimeRecType6.GetCurSel();
			m_struCaptureSched.struHolidaySched[6].byCaptureType = (BYTE)m_comboTimeRecType7.GetCurSel();
			m_struCaptureSched.struHolidaySched[7].byCaptureType = (BYTE)m_comboTimeRecType8.GetCurSel();
			
			m_struCaptureSched.struHolidaySched[0].struCaptureTime.byStartHour = (BYTE)m_iHour11;
			m_struCaptureSched.struHolidaySched[0].struCaptureTime.byStopHour = (BYTE)m_iHour12;
			m_struCaptureSched.struHolidaySched[1].struCaptureTime.byStartHour = (BYTE)m_iHour21;
			m_struCaptureSched.struHolidaySched[1].struCaptureTime.byStopHour = (BYTE)m_iHour22;
			m_struCaptureSched.struHolidaySched[2].struCaptureTime.byStartHour = (BYTE)m_iHour31;
			m_struCaptureSched.struHolidaySched[2].struCaptureTime.byStopHour = (BYTE)m_iHour32;
			m_struCaptureSched.struHolidaySched[3].struCaptureTime.byStartHour = (BYTE)m_iHour41;
			m_struCaptureSched.struHolidaySched[3].struCaptureTime.byStopHour = (BYTE)m_iHour42;
			
			m_struCaptureSched.struHolidaySched[0].struCaptureTime.byStartMin = (BYTE)m_iMin11;
			m_struCaptureSched.struHolidaySched[0].struCaptureTime.byStopMin = (BYTE)m_iMin12;
			m_struCaptureSched.struHolidaySched[1].struCaptureTime.byStartMin = (BYTE)m_iMin21;
			m_struCaptureSched.struHolidaySched[1].struCaptureTime.byStopMin = (BYTE)m_iMin22;
			m_struCaptureSched.struHolidaySched[2].struCaptureTime.byStartMin = (BYTE)m_iMin31;
			m_struCaptureSched.struHolidaySched[2].struCaptureTime.byStopMin = (BYTE)m_iMin32;
			m_struCaptureSched.struHolidaySched[3].struCaptureTime.byStartMin = (BYTE)m_iMin41;
			m_struCaptureSched.struHolidaySched[3].struCaptureTime.byStopMin = (BYTE)m_iMin42;
			
			m_struCaptureSched.struHolidaySched[4].struCaptureTime.byStartHour = (BYTE)m_iHour51;
			m_struCaptureSched.struHolidaySched[4].struCaptureTime.byStopHour = (BYTE)m_iHour52;
			m_struCaptureSched.struHolidaySched[5].struCaptureTime.byStartHour = (BYTE)m_iHour61;
			m_struCaptureSched.struHolidaySched[5].struCaptureTime.byStopHour = (BYTE)m_iHour62;
			m_struCaptureSched.struHolidaySched[6].struCaptureTime.byStartHour = (BYTE)m_iHour71;
			m_struCaptureSched.struHolidaySched[6].struCaptureTime.byStopHour = (BYTE)m_iHour72;
			m_struCaptureSched.struHolidaySched[7].struCaptureTime.byStartHour = (BYTE)m_iHour81;
			m_struCaptureSched.struHolidaySched[7].struCaptureTime.byStopHour = (BYTE)m_iHour82;
			
			m_struCaptureSched.struHolidaySched[4].struCaptureTime.byStartMin = (BYTE)m_iMin51;
			m_struCaptureSched.struHolidaySched[4].struCaptureTime.byStopMin = (BYTE)m_iMin52;
			m_struCaptureSched.struHolidaySched[5].struCaptureTime.byStartMin = (BYTE)m_iMin61;
			m_struCaptureSched.struHolidaySched[5].struCaptureTime.byStopMin = (BYTE)m_iMin62;
			m_struCaptureSched.struHolidaySched[6].struCaptureTime.byStartMin = (BYTE)m_iMin71;
			m_struCaptureSched.struHolidaySched[6].struCaptureTime.byStopMin = (BYTE)m_iMin72;
			m_struCaptureSched.struHolidaySched[7].struCaptureTime.byStartMin = (BYTE)m_iMin81;
			m_struCaptureSched.struHolidaySched[7].struCaptureTime.byStopMin = (BYTE)m_iMin82; 
		}
	   
    }
    else
    {
		m_struCaptureSched.struCaptureDay[iIndex].byAllDayCapture = (WORD)m_bCheckAllDay;
        if (m_bCheckAllDay)
        {		
            m_struCaptureSched.struCaptureDay[iIndex].byCaptureType = (BYTE)m_comboAllDayType.GetCurSel();
        }
        m_struCaptureSched.struCaptureSched[iIndex][0].byCaptureType = (BYTE)m_comboTimeRecType1.GetCurSel();
        m_struCaptureSched.struCaptureSched[iIndex][1].byCaptureType = (BYTE)m_comboTimeRecType2.GetCurSel();
        m_struCaptureSched.struCaptureSched[iIndex][2].byCaptureType = (BYTE)m_comboTimeRecType3.GetCurSel();
        m_struCaptureSched.struCaptureSched[iIndex][3].byCaptureType = (BYTE)m_comboTimeRecType4.GetCurSel();	
        m_struCaptureSched.struCaptureSched[iIndex][4].byCaptureType = (BYTE)m_comboTimeRecType5.GetCurSel();
        m_struCaptureSched.struCaptureSched[iIndex][5].byCaptureType = (BYTE)m_comboTimeRecType6.GetCurSel();
        m_struCaptureSched.struCaptureSched[iIndex][6].byCaptureType = (BYTE)m_comboTimeRecType7.GetCurSel();
        m_struCaptureSched.struCaptureSched[iIndex][7].byCaptureType = (BYTE)m_comboTimeRecType8.GetCurSel();
        
        m_struCaptureSched.struCaptureSched[iIndex][0].struCaptureTime.byStartHour = (BYTE)m_iHour11;
        m_struCaptureSched.struCaptureSched[iIndex][0].struCaptureTime.byStopHour = (BYTE)m_iHour12;
        m_struCaptureSched.struCaptureSched[iIndex][1].struCaptureTime.byStartHour = (BYTE)m_iHour21;
        m_struCaptureSched.struCaptureSched[iIndex][1].struCaptureTime.byStopHour = (BYTE)m_iHour22;
        m_struCaptureSched.struCaptureSched[iIndex][2].struCaptureTime.byStartHour = (BYTE)m_iHour31;
        m_struCaptureSched.struCaptureSched[iIndex][2].struCaptureTime.byStopHour = (BYTE)m_iHour32;
        m_struCaptureSched.struCaptureSched[iIndex][3].struCaptureTime.byStartHour = (BYTE)m_iHour41;
        m_struCaptureSched.struCaptureSched[iIndex][3].struCaptureTime.byStopHour = (BYTE)m_iHour42;
        
        m_struCaptureSched.struCaptureSched[iIndex][0].struCaptureTime.byStartMin = (BYTE)m_iMin11;
        m_struCaptureSched.struCaptureSched[iIndex][0].struCaptureTime.byStopMin = (BYTE)m_iMin12;
        m_struCaptureSched.struCaptureSched[iIndex][1].struCaptureTime.byStartMin = (BYTE)m_iMin21;
        m_struCaptureSched.struCaptureSched[iIndex][1].struCaptureTime.byStopMin = (BYTE)m_iMin22;
        m_struCaptureSched.struCaptureSched[iIndex][2].struCaptureTime.byStartMin = (BYTE)m_iMin31;
        m_struCaptureSched.struCaptureSched[iIndex][2].struCaptureTime.byStopMin = (BYTE)m_iMin32;
        m_struCaptureSched.struCaptureSched[iIndex][3].struCaptureTime.byStartMin = (BYTE)m_iMin41;
        m_struCaptureSched.struCaptureSched[iIndex][3].struCaptureTime.byStopMin = (BYTE)m_iMin42;
        
        m_struCaptureSched.struCaptureSched[iIndex][4].struCaptureTime.byStartHour = (BYTE)m_iHour51;
        m_struCaptureSched.struCaptureSched[iIndex][4].struCaptureTime.byStopHour = (BYTE)m_iHour52;
        m_struCaptureSched.struCaptureSched[iIndex][5].struCaptureTime.byStartHour = (BYTE)m_iHour61;
        m_struCaptureSched.struCaptureSched[iIndex][5].struCaptureTime.byStopHour = (BYTE)m_iHour62;
        m_struCaptureSched.struCaptureSched[iIndex][6].struCaptureTime.byStartHour = (BYTE)m_iHour71;
        m_struCaptureSched.struCaptureSched[iIndex][6].struCaptureTime.byStopHour = (BYTE)m_iHour72;
        m_struCaptureSched.struCaptureSched[iIndex][7].struCaptureTime.byStartHour = (BYTE)m_iHour81;
        m_struCaptureSched.struCaptureSched[iIndex][7].struCaptureTime.byStopHour = (BYTE)m_iHour82;
        
        m_struCaptureSched.struCaptureSched[iIndex][4].struCaptureTime.byStartMin = (BYTE)m_iMin51;
        m_struCaptureSched.struCaptureSched[iIndex][4].struCaptureTime.byStopMin = (BYTE)m_iMin52;
        m_struCaptureSched.struCaptureSched[iIndex][5].struCaptureTime.byStartMin = (BYTE)m_iMin61;
        m_struCaptureSched.struCaptureSched[iIndex][5].struCaptureTime.byStopMin = (BYTE)m_iMin62;
        m_struCaptureSched.struCaptureSched[iIndex][6].struCaptureTime.byStartMin = (BYTE)m_iMin71;
        m_struCaptureSched.struCaptureSched[iIndex][6].struCaptureTime.byStopMin = (BYTE)m_iMin72;
        m_struCaptureSched.struCaptureSched[iIndex][7].struCaptureTime.byStartMin = (BYTE)m_iMin81;
        m_struCaptureSched.struCaptureSched[iIndex][7].struCaptureTime.byStopMin = (BYTE)m_iMin82;
    }        
	GetDlgItem(IDC_BTN_DAY_COPY)->EnableWindow(TRUE);
}

void CDlgJpegCaptureCfg::OnSelchangeComboWeekday() 
{
	int iIndex = m_comboWeekday.GetCurSel();	
	if (iIndex == 7) // ����¼��ƻ� 
	{
		m_bCheckAllDay = m_struCaptureSched.struCaptureHoliday.byAllDayCapture;
        m_comboAllDayType.SetCurSel(m_struCaptureSched.struCaptureHoliday.byCaptureType);

        m_comboTimeRecType1.SetCurSel(m_struCaptureSched.struHolidaySched[0].byCaptureType);
        m_comboTimeRecType2.SetCurSel(m_struCaptureSched.struHolidaySched[1].byCaptureType);
        m_comboTimeRecType3.SetCurSel(m_struCaptureSched.struHolidaySched[2].byCaptureType);
        m_comboTimeRecType4.SetCurSel(m_struCaptureSched.struHolidaySched[3].byCaptureType);
		m_comboTimeRecType5.SetCurSel(m_struCaptureSched.struHolidaySched[4].byCaptureType);
        m_comboTimeRecType6.SetCurSel(m_struCaptureSched.struHolidaySched[5].byCaptureType);
        m_comboTimeRecType7.SetCurSel(m_struCaptureSched.struHolidaySched[6].byCaptureType);
        m_comboTimeRecType8.SetCurSel(m_struCaptureSched.struHolidaySched[7].byCaptureType);
        m_iHour11 = m_struCaptureSched.struHolidaySched[0].struCaptureTime.byStartHour;
        m_iHour12 = m_struCaptureSched.struHolidaySched[0].struCaptureTime.byStopHour;
        m_iHour21 = m_struCaptureSched.struHolidaySched[1].struCaptureTime.byStartHour;
        m_iHour22 = m_struCaptureSched.struHolidaySched[1].struCaptureTime.byStopHour;
        m_iHour31 = m_struCaptureSched.struHolidaySched[2].struCaptureTime.byStartHour;
        m_iHour32 = m_struCaptureSched.struHolidaySched[2].struCaptureTime.byStopHour;
        m_iHour41 = m_struCaptureSched.struHolidaySched[3].struCaptureTime.byStartHour;
        m_iHour42 = m_struCaptureSched.struHolidaySched[3].struCaptureTime.byStopHour;
        m_iMin11 = m_struCaptureSched.struHolidaySched[0].struCaptureTime.byStartMin;
        m_iMin12 = m_struCaptureSched.struHolidaySched[0].struCaptureTime.byStopMin;
        m_iMin21 = m_struCaptureSched.struHolidaySched[1].struCaptureTime.byStartMin;
        m_iMin22 = m_struCaptureSched.struHolidaySched[1].struCaptureTime.byStopMin;
        m_iMin31 = m_struCaptureSched.struHolidaySched[2].struCaptureTime.byStartMin;
        m_iMin32 = m_struCaptureSched.struHolidaySched[2].struCaptureTime.byStopMin;
        m_iMin41 = m_struCaptureSched.struHolidaySched[3].struCaptureTime.byStartMin;
        m_iMin42 = m_struCaptureSched.struHolidaySched[3].struCaptureTime.byStopMin;
		m_iHour51 = m_struCaptureSched.struHolidaySched[4].struCaptureTime.byStartHour;
        m_iHour52 = m_struCaptureSched.struHolidaySched[4].struCaptureTime.byStopHour;
        m_iHour61 = m_struCaptureSched.struHolidaySched[5].struCaptureTime.byStartHour;
        m_iHour62 = m_struCaptureSched.struHolidaySched[5].struCaptureTime.byStopHour;
        m_iHour71 = m_struCaptureSched.struHolidaySched[6].struCaptureTime.byStartHour;
        m_iHour72 = m_struCaptureSched.struHolidaySched[6].struCaptureTime.byStopHour;
        m_iHour81 = m_struCaptureSched.struHolidaySched[7].struCaptureTime.byStartHour;
        m_iHour82 = m_struCaptureSched.struHolidaySched[7].struCaptureTime.byStopHour;
        m_iMin51 = m_struCaptureSched.struHolidaySched[4].struCaptureTime.byStartMin;
        m_iMin52 = m_struCaptureSched.struHolidaySched[4].struCaptureTime.byStopMin;
        m_iMin61 = m_struCaptureSched.struHolidaySched[5].struCaptureTime.byStartMin;
        m_iMin62 = m_struCaptureSched.struHolidaySched[5].struCaptureTime.byStopMin;
        m_iMin71 = m_struCaptureSched.struHolidaySched[6].struCaptureTime.byStartMin;
        m_iMin72 = m_struCaptureSched.struHolidaySched[6].struCaptureTime.byStopMin;
        m_iMin81 = m_struCaptureSched.struHolidaySched[7].struCaptureTime.byStartMin;
        m_iMin82 = m_struCaptureSched.struHolidaySched[7].struCaptureTime.byStopMin;	
	}
    else
    {
		m_bCheckAllDay = m_struCaptureSched.struCaptureDay[iIndex].byAllDayCapture;
        m_comboAllDayType.SetCurSel(m_struCaptureSched.struCaptureDay[iIndex].byCaptureType);

        m_comboTimeRecType1.SetCurSel(m_struCaptureSched.struCaptureSched[iIndex][0].byCaptureType);
        m_comboTimeRecType2.SetCurSel(m_struCaptureSched.struCaptureSched[iIndex][1].byCaptureType);
        m_comboTimeRecType3.SetCurSel(m_struCaptureSched.struCaptureSched[iIndex][2].byCaptureType);
        m_comboTimeRecType4.SetCurSel(m_struCaptureSched.struCaptureSched[iIndex][3].byCaptureType);
		m_comboTimeRecType5.SetCurSel(m_struCaptureSched.struCaptureSched[iIndex][4].byCaptureType);
        m_comboTimeRecType6.SetCurSel(m_struCaptureSched.struCaptureSched[iIndex][5].byCaptureType);
        m_comboTimeRecType7.SetCurSel(m_struCaptureSched.struCaptureSched[iIndex][6].byCaptureType);
        m_comboTimeRecType8.SetCurSel(m_struCaptureSched.struCaptureSched[iIndex][7].byCaptureType);
        
		m_iHour11 = m_struCaptureSched.struCaptureSched[iIndex][0].struCaptureTime.byStartHour;
        m_iHour12 = m_struCaptureSched.struCaptureSched[iIndex][0].struCaptureTime.byStopHour;
        m_iHour21 = m_struCaptureSched.struCaptureSched[iIndex][1].struCaptureTime.byStartHour;
        m_iHour22 = m_struCaptureSched.struCaptureSched[iIndex][1].struCaptureTime.byStopHour;
        m_iHour31 = m_struCaptureSched.struCaptureSched[iIndex][2].struCaptureTime.byStartHour;
        m_iHour32 = m_struCaptureSched.struCaptureSched[iIndex][2].struCaptureTime.byStopHour;
        m_iHour41 = m_struCaptureSched.struCaptureSched[iIndex][3].struCaptureTime.byStartHour;
        m_iHour42 = m_struCaptureSched.struCaptureSched[iIndex][3].struCaptureTime.byStopHour;
        m_iMin11 = m_struCaptureSched.struCaptureSched[iIndex][0].struCaptureTime.byStartMin;
        m_iMin12 = m_struCaptureSched.struCaptureSched[iIndex][0].struCaptureTime.byStopMin;
        m_iMin21 = m_struCaptureSched.struCaptureSched[iIndex][1].struCaptureTime.byStartMin;
        m_iMin22 = m_struCaptureSched.struCaptureSched[iIndex][1].struCaptureTime.byStopMin;
        m_iMin31 = m_struCaptureSched.struCaptureSched[iIndex][2].struCaptureTime.byStartMin;
        m_iMin32 = m_struCaptureSched.struCaptureSched[iIndex][2].struCaptureTime.byStopMin;
        m_iMin41 = m_struCaptureSched.struCaptureSched[iIndex][3].struCaptureTime.byStartMin;
        m_iMin42 = m_struCaptureSched.struCaptureSched[iIndex][3].struCaptureTime.byStopMin;
		m_iHour51 = m_struCaptureSched.struCaptureSched[iIndex][4].struCaptureTime.byStartHour;
        m_iHour52 = m_struCaptureSched.struCaptureSched[iIndex][4].struCaptureTime.byStopHour;
        m_iHour61 = m_struCaptureSched.struCaptureSched[iIndex][5].struCaptureTime.byStartHour;
        m_iHour62 = m_struCaptureSched.struCaptureSched[iIndex][5].struCaptureTime.byStopHour;
        m_iHour71 = m_struCaptureSched.struCaptureSched[iIndex][6].struCaptureTime.byStartHour;
        m_iHour72 = m_struCaptureSched.struCaptureSched[iIndex][6].struCaptureTime.byStopHour;
        m_iHour81 = m_struCaptureSched.struCaptureSched[iIndex][7].struCaptureTime.byStartHour;
        m_iHour82 = m_struCaptureSched.struCaptureSched[iIndex][7].struCaptureTime.byStopHour;
        m_iMin51 = m_struCaptureSched.struCaptureSched[iIndex][4].struCaptureTime.byStartMin;
        m_iMin52 = m_struCaptureSched.struCaptureSched[iIndex][4].struCaptureTime.byStopMin;
        m_iMin61 = m_struCaptureSched.struCaptureSched[iIndex][5].struCaptureTime.byStartMin;
        m_iMin62 = m_struCaptureSched.struCaptureSched[iIndex][5].struCaptureTime.byStopMin;
        m_iMin71 = m_struCaptureSched.struCaptureSched[iIndex][6].struCaptureTime.byStartMin;
        m_iMin72 = m_struCaptureSched.struCaptureSched[iIndex][6].struCaptureTime.byStopMin;
        m_iMin81 = m_struCaptureSched.struCaptureSched[iIndex][7].struCaptureTime.byStartMin;
        m_iMin82 = m_struCaptureSched.struCaptureSched[iIndex][7].struCaptureTime.byStopMin;
    }
	EnableControl(!m_bCheckAllDay);
	GetDlgItem(IDC_BTN_DAY_COPY)->EnableWindow(FALSE);
	UpdateData(FALSE);
}

void CDlgJpegCaptureCfg::OnButtonUpdateSched() 
{
 	DWORD dwBytesReturned = 0;
	if(!NET_DVR_GetDVRConfig(m_lUserID, NET_DVR_GET_SCHED_CAPTURECFG, m_lChannel, &m_struCaptureSched, sizeof(m_struCaptureSched), &dwBytesReturned))
	{
		g_pMainDlg->AddLog(m_dwDevIndex, OPERATION_FAIL_T, "chan[%d] NET_DVR_GET_SCHED_CAPTURECFG", m_lChannel);
	}
	else
	{
		g_pMainDlg->AddLog(m_dwDevIndex, OPERATION_SUCC_T, "chan[%d] NET_DVR_GET_SCHED_CAPTURECFG", m_lChannel);
			
		m_bEnableCapture = m_struCaptureSched.byEnable;
		m_dwPicSaveDays = m_struCaptureSched.dwRecorderDuration;

		OnSelchangeComboWeekday();
	}

	UpdateData(FALSE);
}

void CDlgJpegCaptureCfg::OnBtnSetJpegCaptureSched() 
{
	OnCaptureDayOk();
	m_struCaptureSched.byEnable = m_bEnableCapture;
	m_struCaptureSched.dwRecorderDuration = m_dwPicSaveDays;

	if(!NET_DVR_SetDVRConfig(m_lUserID, NET_DVR_SET_SCHED_CAPTURECFG, m_lChannel, &m_struCaptureSched, sizeof(m_struCaptureSched)))
	{
		g_pMainDlg->AddLog(m_dwDevIndex, OPERATION_FAIL_T, "chan[%d] NET_DVR_SET_SCHED_CAPTURECFG", m_lChannel);
	}
	else
	{
		g_pMainDlg->AddLog(m_dwDevIndex, OPERATION_SUCC_T, "chan[%d] NET_DVR_SET_SCHED_CAPTURECFG", m_lChannel);
	}
}

void CDlgJpegCaptureCfg::OnButtonUpdateFtp() 
{
	DWORD dwBytesReturned = 0;
	char szLan[1024] = {0};

	memset(m_struFtpCfgV40,0,sizeof(m_struFtpCfgV40));
	NET_DVR_FTP_TYPE struTempFtpType[2] = {0};
	struTempFtpType[0].byType = 0;
	struTempFtpType[1].byType = 1;
	DWORD dwStatus[2] = {0}; 

	if (!NET_DVR_GetDeviceConfig(m_lUserID, NET_DVR_GET_FTPCFG_V40,2,&struTempFtpType,sizeof(struTempFtpType),&dwStatus,&m_struFtpCfgV40, sizeof(m_struFtpCfgV40)))
	{
		g_pMainDlg->AddLog(m_dwDevIndex, OPERATION_FAIL_T, "chan[%d] NET_DVR_GET_FTPCFG_V40", m_lChannel);
		
		sprintf(szLan,"%d",NET_DVR_GetLastError());
		AfxMessageBox(szLan);
	}
	else
	{
		g_pMainDlg->AddLog(m_dwDevIndex, OPERATION_SUCC_T, "chan[%d] NET_DVR_GET_FTPCFG_V40", m_lChannel);
		SetFtpV40Info();
		//���ñ���		
	}
	
	
}

void CDlgJpegCaptureCfg::OnSelchangeComboDirLevel() 
{
	UpdateData(TRUE);
	SetMainFtpSelDirShow(FALSE);
	SetMainFtpSelSecondDirShow(FALSE);
	int temp;
	temp = m_DirLevelCtrl.GetCurSel();
	switch (temp)
	{
	case 0:	
		m_comboMainFirstDirModeCtr.EnableWindow(FALSE);
        m_comboMainSecordDirModeCtrl.EnableWindow(FALSE);		
		break;
	case 1:
		m_comboMainFirstDirModeCtr.EnableWindow(TRUE); 
		m_comboMainSecordDirModeCtrl.EnableWindow(FALSE);
		break;
	case 2:
		m_comboMainFirstDirModeCtr.EnableWindow(TRUE);
		m_comboMainSecordDirModeCtrl.EnableWindow(TRUE);
		break;
	default:	
		break;
	}
	
	UpdateData(FALSE);
}

void CDlgJpegCaptureCfg::OnSelchangeComboDirModeOne()
{
   	UpdateData(TRUE);
	int temp;
	temp = m_comboMainFirstDirModeCtr.GetCurSel();
	switch (temp)
	{
	case 3:
		SetMainFtpSelDirShow(TRUE);
		break;
	default:
		SetMainFtpSelDirShow(FALSE);
		//SetMainFtpSelSecondDirShow(FALSE);
		break;
	}
	
	UpdateData(FALSE);
}
void CDlgJpegCaptureCfg::OnSelchangeComboDirModeTwo()
{
	UpdateData(TRUE);
	int temp;
	temp = m_comboMainSecordDirModeCtrl.GetCurSel();
	
	switch(temp)
	{
	case 2:
		SetMainFtpSelSecondDirShow(TRUE);
		break;
	default:
		SetMainFtpSelSecondDirShow(FALSE);
		break;
	}
	UpdateData(FALSE);		
	
	
}	
void CDlgJpegCaptureCfg::OnSelchangeSubComboDirModeOne()
{
	UpdateData(TRUE);
	int temp;
	temp = m_comboSubFirstDirModeCtr.GetCurSel();
	
	switch(temp)
	{
	case 3:
		SetSubFtpSelDirShow(TRUE);
		break;
	default:
		SetSubFtpSelDirShow(FALSE);
	//	SetSubFtpSelSecondDirShow(FALSE);
		break;
	}
	UpdateData(FALSE);	
	
}
void CDlgJpegCaptureCfg::OnSelchangeSubComboDirModeTwo()
{
	UpdateData(TRUE);
	int temp;
	temp = m_comboSubSecordDirModeCtrl.GetCurSel();
	
	switch(temp)
	{
	case 2:
		SetSubFtpSelSecondDirShow(TRUE);
		break;
	default:
		SetSubFtpSelSecondDirShow(FALSE);
		break;
	}
	UpdateData(FALSE);
}

void CDlgJpegCaptureCfg::OnBtnSetFtp() 
{
	UpdateData(TRUE);
	CString sTemp;
	char szLan[128] = {0};
	//��ȡ������Ϣ
	GetFtpV40Info();    
	NET_DVR_FTP_TYPE struTempFtpType[2] = {0};	
	
	memset(struTempFtpType, 0, 2*sizeof(NET_DVR_FTP_TYPE));
	struTempFtpType[0].byType = 0;
	struTempFtpType[1].byType = 1;
	
	DWORD dwStatus[2] = {0}; 
	if (!NET_DVR_SetDeviceConfig(m_lUserID,NET_DVR_SET_FTPCFG_V40,2,&struTempFtpType,2*sizeof(NET_DVR_FTP_TYPE),&dwStatus,&m_struFtpCfgV40,sizeof(m_struFtpCfgV40)))
	{
		g_pMainDlg->AddLog(m_dwDevIndex, OPERATION_FAIL_T, "chan[%d] NET_DVR_SET_FTPCFG_V40", m_lChannel);
		sprintf(szLan,"%d",NET_DVR_GetLastError());
		AfxMessageBox(szLan);
	}
	else
	{
		g_pMainDlg->AddLog(m_dwDevIndex, OPERATION_SUCC_T, "chan[%d] NET_DVR_SET_FTPCFG_V40", m_lChannel);	
	}
}

void CDlgJpegCaptureCfg::OnBtnDayCopy() 
{
	UpdateData(TRUE);
	int iIndex = m_comboCopyWeekday.GetCurSel() - 1;
	if (!TimeTest())
	{
		return;
	}

	if (iIndex != -1)
	{
        if (iIndex == 7) // ����
        {
            m_struCaptureSched.struCaptureHoliday.byAllDayCapture = m_bCheckAllDay;
            m_struCaptureSched.struCaptureHoliday.byCaptureType = (BYTE)m_comboAllDayType.GetCurSel();		
            m_struCaptureSched.struHolidaySched[0].byCaptureType = (BYTE)m_comboTimeRecType1.GetCurSel();
            m_struCaptureSched.struHolidaySched[1].byCaptureType = (BYTE)m_comboTimeRecType2.GetCurSel();
            m_struCaptureSched.struHolidaySched[2].byCaptureType = (BYTE)m_comboTimeRecType3.GetCurSel();
            m_struCaptureSched.struHolidaySched[3].byCaptureType = (BYTE)m_comboTimeRecType4.GetCurSel();	
            m_struCaptureSched.struHolidaySched[4].byCaptureType = (BYTE)m_comboTimeRecType5.GetCurSel();	
            m_struCaptureSched.struHolidaySched[5].byCaptureType = (BYTE)m_comboTimeRecType6.GetCurSel();	
			m_struCaptureSched.struHolidaySched[6].byCaptureType = (BYTE)m_comboTimeRecType7.GetCurSel();	
			m_struCaptureSched.struHolidaySched[7].byCaptureType = (BYTE)m_comboTimeRecType8.GetCurSel();	
			
            m_struCaptureSched.struHolidaySched[0].struCaptureTime.byStartHour = (BYTE)m_iHour11;
            m_struCaptureSched.struHolidaySched[0].struCaptureTime.byStopHour = (BYTE)m_iHour12;
            m_struCaptureSched.struHolidaySched[1].struCaptureTime.byStartHour = (BYTE)m_iHour21;
            m_struCaptureSched.struHolidaySched[1].struCaptureTime.byStopHour = (BYTE)m_iHour22;
            m_struCaptureSched.struHolidaySched[2].struCaptureTime.byStartHour = (BYTE)m_iHour31;
            m_struCaptureSched.struHolidaySched[2].struCaptureTime.byStopHour = (BYTE)m_iHour32;
            m_struCaptureSched.struHolidaySched[3].struCaptureTime.byStartHour = (BYTE)m_iHour41;
            m_struCaptureSched.struHolidaySched[3].struCaptureTime.byStopHour = (BYTE)m_iHour42;
			m_struCaptureSched.struHolidaySched[4].struCaptureTime.byStartHour = (BYTE)m_iHour51;
            m_struCaptureSched.struHolidaySched[4].struCaptureTime.byStopHour = (BYTE)m_iHour52;
            m_struCaptureSched.struHolidaySched[5].struCaptureTime.byStartHour = (BYTE)m_iHour61;
            m_struCaptureSched.struHolidaySched[5].struCaptureTime.byStopHour = (BYTE)m_iHour62;
            m_struCaptureSched.struHolidaySched[6].struCaptureTime.byStartHour = (BYTE)m_iHour71;
            m_struCaptureSched.struHolidaySched[6].struCaptureTime.byStopHour = (BYTE)m_iHour72;
            m_struCaptureSched.struHolidaySched[7].struCaptureTime.byStartHour = (BYTE)m_iHour81;
            m_struCaptureSched.struHolidaySched[7].struCaptureTime.byStopHour = (BYTE)m_iHour82;
            
            m_struCaptureSched.struHolidaySched[0].struCaptureTime.byStartMin = (BYTE)m_iMin11;
            m_struCaptureSched.struHolidaySched[0].struCaptureTime.byStopMin = (BYTE)m_iMin12;
            m_struCaptureSched.struHolidaySched[1].struCaptureTime.byStartMin = (BYTE)m_iMin21;
            m_struCaptureSched.struHolidaySched[1].struCaptureTime.byStopMin = (BYTE)m_iMin22;
            m_struCaptureSched.struHolidaySched[2].struCaptureTime.byStartMin = (BYTE)m_iMin31;
            m_struCaptureSched.struHolidaySched[2].struCaptureTime.byStopMin = (BYTE)m_iMin32;
            m_struCaptureSched.struHolidaySched[3].struCaptureTime.byStartMin = (BYTE)m_iMin41;
            m_struCaptureSched.struHolidaySched[3].struCaptureTime.byStopMin = (BYTE)m_iMin42;
			m_struCaptureSched.struHolidaySched[4].struCaptureTime.byStartMin = (BYTE)m_iMin51;
            m_struCaptureSched.struHolidaySched[4].struCaptureTime.byStopMin = (BYTE)m_iMin52;
            m_struCaptureSched.struHolidaySched[5].struCaptureTime.byStartMin = (BYTE)m_iMin61;
            m_struCaptureSched.struHolidaySched[5].struCaptureTime.byStopMin = (BYTE)m_iMin62;
            m_struCaptureSched.struHolidaySched[6].struCaptureTime.byStartMin = (BYTE)m_iMin71;
            m_struCaptureSched.struHolidaySched[6].struCaptureTime.byStopMin = (BYTE)m_iMin72;
            m_struCaptureSched.struHolidaySched[7].struCaptureTime.byStartMin = (BYTE)m_iMin81;
            m_struCaptureSched.struHolidaySched[7].struCaptureTime.byStopMin = (BYTE)m_iMin82;
        }
        else
        {
            m_struCaptureSched.struCaptureDay[iIndex].byAllDayCapture = m_bCheckAllDay;
            m_struCaptureSched.struCaptureDay[iIndex].byCaptureType = (BYTE)m_comboAllDayType.GetCurSel();		
            m_struCaptureSched.struCaptureSched[iIndex][0].byCaptureType = (BYTE)m_comboTimeRecType1.GetCurSel();
            m_struCaptureSched.struCaptureSched[iIndex][1].byCaptureType = (BYTE)m_comboTimeRecType2.GetCurSel();
            m_struCaptureSched.struCaptureSched[iIndex][2].byCaptureType = (BYTE)m_comboTimeRecType3.GetCurSel();
            m_struCaptureSched.struCaptureSched[iIndex][3].byCaptureType = (BYTE)m_comboTimeRecType4.GetCurSel();	
            m_struCaptureSched.struCaptureSched[iIndex][4].byCaptureType = (BYTE)m_comboTimeRecType5.GetCurSel();
            m_struCaptureSched.struCaptureSched[iIndex][5].byCaptureType = (BYTE)m_comboTimeRecType6.GetCurSel();
            m_struCaptureSched.struCaptureSched[iIndex][6].byCaptureType = (BYTE)m_comboTimeRecType7.GetCurSel();
            m_struCaptureSched.struCaptureSched[iIndex][7].byCaptureType = (BYTE)m_comboTimeRecType8.GetCurSel();	

            m_struCaptureSched.struCaptureSched[iIndex][0].struCaptureTime.byStartHour = (BYTE)m_iHour11;
            m_struCaptureSched.struCaptureSched[iIndex][0].struCaptureTime.byStopHour = (BYTE)m_iHour12;
            m_struCaptureSched.struCaptureSched[iIndex][1].struCaptureTime.byStartHour = (BYTE)m_iHour21;
            m_struCaptureSched.struCaptureSched[iIndex][1].struCaptureTime.byStopHour = (BYTE)m_iHour22;
            m_struCaptureSched.struCaptureSched[iIndex][2].struCaptureTime.byStartHour = (BYTE)m_iHour31;
            m_struCaptureSched.struCaptureSched[iIndex][2].struCaptureTime.byStopHour = (BYTE)m_iHour32;
            m_struCaptureSched.struCaptureSched[iIndex][3].struCaptureTime.byStartHour = (BYTE)m_iHour41;
            m_struCaptureSched.struCaptureSched[iIndex][3].struCaptureTime.byStopHour = (BYTE)m_iHour42;
			m_struCaptureSched.struCaptureSched[iIndex][4].struCaptureTime.byStartHour = (BYTE)m_iHour51;
            m_struCaptureSched.struCaptureSched[iIndex][4].struCaptureTime.byStopHour = (BYTE)m_iHour52;
            m_struCaptureSched.struCaptureSched[iIndex][5].struCaptureTime.byStartHour = (BYTE)m_iHour61;
            m_struCaptureSched.struCaptureSched[iIndex][5].struCaptureTime.byStopHour = (BYTE)m_iHour62;
            m_struCaptureSched.struCaptureSched[iIndex][6].struCaptureTime.byStartHour = (BYTE)m_iHour71;
            m_struCaptureSched.struCaptureSched[iIndex][6].struCaptureTime.byStopHour = (BYTE)m_iHour72;
            m_struCaptureSched.struCaptureSched[iIndex][7].struCaptureTime.byStartHour = (BYTE)m_iHour81;
            m_struCaptureSched.struCaptureSched[iIndex][7].struCaptureTime.byStopHour = (BYTE)m_iHour82;
            
            m_struCaptureSched.struCaptureSched[iIndex][0].struCaptureTime.byStartMin = (BYTE)m_iMin11;
            m_struCaptureSched.struCaptureSched[iIndex][0].struCaptureTime.byStopMin = (BYTE)m_iMin12;
            m_struCaptureSched.struCaptureSched[iIndex][1].struCaptureTime.byStartMin = (BYTE)m_iMin21;
            m_struCaptureSched.struCaptureSched[iIndex][1].struCaptureTime.byStopMin = (BYTE)m_iMin22;
            m_struCaptureSched.struCaptureSched[iIndex][2].struCaptureTime.byStartMin = (BYTE)m_iMin31;
            m_struCaptureSched.struCaptureSched[iIndex][2].struCaptureTime.byStopMin = (BYTE)m_iMin32;
            m_struCaptureSched.struCaptureSched[iIndex][3].struCaptureTime.byStartMin = (BYTE)m_iMin41;
            m_struCaptureSched.struCaptureSched[iIndex][3].struCaptureTime.byStopMin = (BYTE)m_iMin42;
			m_struCaptureSched.struCaptureSched[iIndex][4].struCaptureTime.byStartMin = (BYTE)m_iMin51;
            m_struCaptureSched.struCaptureSched[iIndex][4].struCaptureTime.byStopMin = (BYTE)m_iMin52;
            m_struCaptureSched.struCaptureSched[iIndex][5].struCaptureTime.byStartMin = (BYTE)m_iMin61;
            m_struCaptureSched.struCaptureSched[iIndex][5].struCaptureTime.byStopMin = (BYTE)m_iMin62;
            m_struCaptureSched.struCaptureSched[iIndex][6].struCaptureTime.byStartMin = (BYTE)m_iMin71;
            m_struCaptureSched.struCaptureSched[iIndex][6].struCaptureTime.byStopMin = (BYTE)m_iMin72;
            m_struCaptureSched.struCaptureSched[iIndex][7].struCaptureTime.byStartMin = (BYTE)m_iMin81;
            m_struCaptureSched.struCaptureSched[iIndex][7].struCaptureTime.byStopMin = (BYTE)m_iMin82;
        }
	}
	else
	{
		for (int i = 0;i < MAX_DAYS;i++)
		{	
			m_struCaptureSched.struCaptureDay[i].byAllDayCapture = m_bCheckAllDay;
			m_struCaptureSched.struCaptureDay[i].byCaptureType = (BYTE)m_comboAllDayType.GetCurSel();	

			m_struCaptureSched.struCaptureSched[i][0].byCaptureType = (BYTE)m_comboTimeRecType1.GetCurSel();
			m_struCaptureSched.struCaptureSched[i][1].byCaptureType = (BYTE)m_comboTimeRecType2.GetCurSel();
			m_struCaptureSched.struCaptureSched[i][2].byCaptureType = (BYTE)m_comboTimeRecType3.GetCurSel();
			m_struCaptureSched.struCaptureSched[i][3].byCaptureType = (BYTE)m_comboTimeRecType4.GetCurSel();	
			m_struCaptureSched.struCaptureSched[i][4].byCaptureType = (BYTE)m_comboTimeRecType5.GetCurSel();
			m_struCaptureSched.struCaptureSched[i][5].byCaptureType = (BYTE)m_comboTimeRecType6.GetCurSel();
			m_struCaptureSched.struCaptureSched[i][6].byCaptureType = (BYTE)m_comboTimeRecType7.GetCurSel();
			m_struCaptureSched.struCaptureSched[i][7].byCaptureType = (BYTE)m_comboTimeRecType8.GetCurSel();	

			m_struCaptureSched.struCaptureSched[i][0].struCaptureTime.byStartHour = (BYTE)m_iHour11;
			m_struCaptureSched.struCaptureSched[i][0].struCaptureTime.byStopHour = (BYTE)m_iHour12;
			m_struCaptureSched.struCaptureSched[i][1].struCaptureTime.byStartHour = (BYTE)m_iHour21;
			m_struCaptureSched.struCaptureSched[i][1].struCaptureTime.byStopHour = (BYTE)m_iHour22;
			m_struCaptureSched.struCaptureSched[i][2].struCaptureTime.byStartHour = (BYTE)m_iHour31;
			m_struCaptureSched.struCaptureSched[i][2].struCaptureTime.byStopHour = (BYTE)m_iHour32;
			m_struCaptureSched.struCaptureSched[i][3].struCaptureTime.byStartHour = (BYTE)m_iHour41;
			m_struCaptureSched.struCaptureSched[i][3].struCaptureTime.byStopHour = (BYTE)m_iHour42;
			m_struCaptureSched.struCaptureSched[i][4].struCaptureTime.byStartHour = (BYTE)m_iHour51;
			m_struCaptureSched.struCaptureSched[i][4].struCaptureTime.byStopHour = (BYTE)m_iHour52;
			m_struCaptureSched.struCaptureSched[i][5].struCaptureTime.byStartHour = (BYTE)m_iHour61;
			m_struCaptureSched.struCaptureSched[i][5].struCaptureTime.byStopHour = (BYTE)m_iHour62;
			m_struCaptureSched.struCaptureSched[i][6].struCaptureTime.byStartHour = (BYTE)m_iHour71;
			m_struCaptureSched.struCaptureSched[i][6].struCaptureTime.byStopHour = (BYTE)m_iHour72;
			m_struCaptureSched.struCaptureSched[i][7].struCaptureTime.byStartHour = (BYTE)m_iHour81;
			m_struCaptureSched.struCaptureSched[i][7].struCaptureTime.byStopHour = (BYTE)m_iHour82;

			m_struCaptureSched.struCaptureSched[i][0].struCaptureTime.byStartMin = (BYTE)m_iMin11;
			m_struCaptureSched.struCaptureSched[i][0].struCaptureTime.byStopMin = (BYTE)m_iMin12;
			m_struCaptureSched.struCaptureSched[i][1].struCaptureTime.byStartMin = (BYTE)m_iMin21;
			m_struCaptureSched.struCaptureSched[i][1].struCaptureTime.byStopMin = (BYTE)m_iMin22;
			m_struCaptureSched.struCaptureSched[i][2].struCaptureTime.byStartMin = (BYTE)m_iMin31;
			m_struCaptureSched.struCaptureSched[i][2].struCaptureTime.byStopMin = (BYTE)m_iMin32;
			m_struCaptureSched.struCaptureSched[i][3].struCaptureTime.byStartMin = (BYTE)m_iMin41;
			m_struCaptureSched.struCaptureSched[i][3].struCaptureTime.byStopMin = (BYTE)m_iMin42;
			m_struCaptureSched.struCaptureSched[i][4].struCaptureTime.byStartMin = (BYTE)m_iMin51;
			m_struCaptureSched.struCaptureSched[i][4].struCaptureTime.byStopMin = (BYTE)m_iMin52;
			m_struCaptureSched.struCaptureSched[i][5].struCaptureTime.byStartMin = (BYTE)m_iMin61;
			m_struCaptureSched.struCaptureSched[i][5].struCaptureTime.byStopMin = (BYTE)m_iMin62;
			m_struCaptureSched.struCaptureSched[i][6].struCaptureTime.byStartMin = (BYTE)m_iMin71;
			m_struCaptureSched.struCaptureSched[i][6].struCaptureTime.byStopMin = (BYTE)m_iMin72;
			m_struCaptureSched.struCaptureSched[i][7].struCaptureTime.byStartMin = (BYTE)m_iMin81;
			m_struCaptureSched.struCaptureSched[i][7].struCaptureTime.byStopMin = (BYTE)m_iMin82;
		}
	}	
}

void CDlgJpegCaptureCfg::OnChkAllDay() 
{
	UpdateData(TRUE);
	EnableControl(!m_bCheckAllDay);
}

void CDlgJpegCaptureCfg::OnButtonAlarminAll() 
{
	int iIndex = m_comboAlarmIn.GetCurSel();
	
	CreateChanTreeAlarmIn(iIndex, TRUE, FALSE);
}

void CDlgJpegCaptureCfg::OnButtonAlarminClean() 
{
	int iIndex = m_comboAlarmIn.GetCurSel();
	
	CreateChanTreeAlarmIn(iIndex, FALSE, TRUE);
}

void CDlgJpegCaptureCfg::OnButtonEventAll() 
{
	int iIndex = m_comboEvent.GetCurSel();
	
	CreateChanTreeEvent(iIndex, TRUE, FALSE);
}

void CDlgJpegCaptureCfg::OnButtonEventClean() 
{
	int iIndex = m_comboEvent.GetCurSel();
	
	CreateChanTreeEvent(iIndex, FALSE, TRUE);	
}

void CDlgJpegCaptureCfg::OnButtonUpdateFtp2() 
{
	// TODO: Add your control notification handler code here
	DWORD dwBytesReturned = 0;
	if (!NET_DVR_GetDVRConfig(m_lUserID, NET_DVR_GET_FTPCFG_SECOND, 0,&m_strFtpCfg2, sizeof(NET_DVR_FTPCFG), &dwBytesReturned))
	{
		g_pMainDlg->AddLog(m_dwDevIndex, OPERATION_FAIL_T, "chan[%d] NET_DVR_GET_FTPCFG_SECOND", m_lChannel);
	}
	else
	{
		g_pMainDlg->AddLog(m_dwDevIndex, OPERATION_SUCC_T, "chan[%d] NET_DVR_GET_FTPCFG_SECOND", m_lChannel);
		m_DirLevelCtrl2.SetCurSel(m_strFtpCfg2.dwDirLevel);
        int temp;
        temp = m_DirLevelCtrl2.GetCurSel();
        switch (temp)
        {
        case 0:	
			m_comboSubFirstDirModeCtr.EnableWindow(FALSE);
            m_comboSubSecordDirModeCtrl.EnableWindow(FALSE);
            break;
        case 1:
            m_comboSubFirstDirModeCtr.EnableWindow(TRUE); 
            if (m_strFtpCfg2.wTopDirMode == 0x1)
            {
                m_comboSubFirstDirModeCtr.SetCurSel(0);
            }
            if (m_strFtpCfg2.wTopDirMode == 0x2)
            {
				m_comboSubFirstDirModeCtr.SetCurSel(1);
            }
            if (m_strFtpCfg2.wTopDirMode == 0x3)
            {
                m_comboSubFirstDirModeCtr.SetCurSel(2);
            }
			if (m_strFtpCfg2.wTopDirMode == 0x6)
			{
				m_comboSubFirstDirModeCtr.SetCurSel(3);
			}
            m_comboSubSecordDirModeCtrl.EnableWindow(FALSE);
            break;
        case 2:
            m_comboSubFirstDirModeCtr.EnableWindow(TRUE);
            m_comboSubSecordDirModeCtrl.EnableWindow(TRUE);
            if (m_strFtpCfg2.wTopDirMode == 0x1)
            {
                m_comboSubFirstDirModeCtr.SetCurSel(0);
            }
            if (m_strFtpCfg2.wTopDirMode == 0x2)
            {
                m_comboSubFirstDirModeCtr.SetCurSel(1);
            }
            if (m_strFtpCfg2.wTopDirMode == 0x3)
            {
                m_comboSubFirstDirModeCtr.SetCurSel(2);
            }
            if (m_strFtpCfg2.wSubDirMode == 0x1 )
            {
                m_comboSubSecordDirModeCtrl.SetCurSel(0);
            }
            if (m_strFtpCfg2.wSubDirMode == 0x2 )
            {
                m_comboSubSecordDirModeCtrl.SetCurSel(1);
            }
            break;
        default:	
            break;
        }
		
		m_UseFTPUpCtrl2.SetCurSel(m_strFtpCfg2.dwEnableFTP);	
		m_dwPort2 = m_strFtpCfg2.dwFTPPort;
		m_csPassword2 = m_strFtpCfg2.sPassword;
		m_csUserName2 = m_strFtpCfg2.sUserName;
		m_csIP2 = m_strFtpCfg2.sFTPIP;
	}
	
	UpdateData(FALSE);
}

void CDlgJpegCaptureCfg::OnBtnSetFtp2() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	CString sTemp;
	char szLan[128] = {0};
	
	//FTP����	
	int temp, tmp1, tmp2;
    temp = m_DirLevelCtrl2.GetCurSel();
    switch (temp)
    {
    case 0:
        m_strFtpCfg2.dwDirLevel = 0;
        break;
    case 1:
        m_strFtpCfg2.dwDirLevel = 1;

		tmp1 = m_comboSubFirstDirModeCtr.GetCurSel();
        if (tmp1 == 0)
        {
            m_strFtpCfg2.wTopDirMode = 0x1;
        }
        if (tmp1 == 1)
        {
            m_strFtpCfg2.wTopDirMode = 0x2;
        }
        if (tmp1 == 2)
        {
            m_strFtpCfg2.wTopDirMode = 0x3;
        }
		if (tmp1 == 3)
		{
			m_strFtpCfg2.wTopDirMode = 0x6;

		}
        break;
    case 2:
        m_strFtpCfg2.dwDirLevel = 2;
        tmp1 = m_comboSubFirstDirModeCtr.GetCurSel();
        if (tmp1 == 0)
        {
            m_strFtpCfg2.wTopDirMode = 0x1;
        }
        if (tmp1 == 1)
        {
            m_strFtpCfg2.wTopDirMode = 0x2;
        }
        if (tmp1 == 2)
        {
            m_strFtpCfg2.wTopDirMode = 0x3;
        }
		tmp2 = m_comboSubSecordDirModeCtrl.GetCurSel();
        if (tmp2 == 0)
        {
            m_strFtpCfg2.wSubDirMode = 0x1;
        }
        if (tmp2 == 1)
        {
            m_strFtpCfg2.wSubDirMode = 0x2;
        }
    default:
        break;
    }
	
	m_strFtpCfg2.dwEnableFTP = m_UseFTPUpCtrl2.GetCurSel();
	
	m_strFtpCfg2.dwFTPPort = m_dwPort2;
	sprintf((char*)m_strFtpCfg2.sPassword, m_csPassword2, PASSWD_LEN);
	sprintf((char*)m_strFtpCfg2.sUserName, m_csUserName2, NAME_LEN);
	sprintf((char*)m_strFtpCfg2.sFTPIP, m_csIP2, 16);
	
	if (!NET_DVR_SetDVRConfig(m_lUserID, NET_DVR_SET_FTPCFG_SECOND, 0, &m_strFtpCfg2, sizeof(NET_DVR_FTPCFG)))
	{
		g_pMainDlg->AddLog(m_dwDevIndex, OPERATION_FAIL_T, "chan[%d] NET_DVR_SET_FTPCFG_SECOND", m_lChannel);
	}
	else
	{
		g_pMainDlg->AddLog(m_dwDevIndex, OPERATION_SUCC_T, "chan[%d] NET_DVR_SET_FTPCFG_SECOND", m_lChannel);	
	}
}

void CDlgJpegCaptureCfg::SetFtpV40Info()
{
	int temp;
	
	//�Ƚ��Զ���Ŀ¼��Ϣ����
	SetMainFtpSelDirShow(FALSE);
	SetMainFtpSelSecondDirShow(FALSE);
	SetSubFtpSelDirShow(FALSE);
	SetSubFtpSelSecondDirShow(FALSE);
	m_DirLevelCtrl.SetCurSel(m_struFtpCfgV40[0].byDirLevel);
	temp = m_DirLevelCtrl.GetCurSel();
	switch (temp)
	{
	case 0:	
		m_comboMainFirstDirModeCtr.EnableWindow(FALSE);
		m_comboMainSecordDirModeCtrl.EnableWindow(FALSE);
		break;
	case 1:
		m_comboMainFirstDirModeCtr.EnableWindow(TRUE); 
		if (m_struFtpCfgV40[0].byTopDirMode == 0x1)
		{
			m_comboMainFirstDirModeCtr.SetCurSel(0);
		}
		if (m_struFtpCfgV40[0].byTopDirMode == 0x2)
		{
			m_comboMainFirstDirModeCtr.SetCurSel(1);
		}
		if (m_struFtpCfgV40[0].byTopDirMode == 0x3)
		{
			m_comboMainFirstDirModeCtr.SetCurSel(2);
		}
		if (m_struFtpCfgV40[0].byTopDirMode == 0x6)
		{
			m_comboMainFirstDirModeCtr.SetCurSel(3);
			SetMainFtpSelDirShow(TRUE);
		}
		m_comboMainSecordDirModeCtrl.EnableWindow(FALSE);
		break;
	case 2:
		m_comboMainFirstDirModeCtr.EnableWindow(TRUE);
		m_comboMainSecordDirModeCtrl.EnableWindow(TRUE);
		if (m_struFtpCfgV40[0].byTopDirMode == 0x1)
		{
			m_comboMainFirstDirModeCtr.SetCurSel(0);
		}
		if (m_struFtpCfgV40[0].byTopDirMode == 0x2)
		{
			m_comboMainFirstDirModeCtr.SetCurSel(1);
		}
		if (m_struFtpCfgV40[0].byTopDirMode == 0x3)
		{
			m_comboMainFirstDirModeCtr.SetCurSel(2);
		}

		if (m_struFtpCfgV40[0].byTopDirMode == 0x6)
		{
			m_comboMainFirstDirModeCtr.SetCurSel(3);
			SetMainFtpSelDirShow(TRUE);
		}
		

		if (m_struFtpCfgV40[0].bySubDirMode == 0x1 )
		{
			m_comboMainSecordDirModeCtrl.SetCurSel(0);
		}
		if (m_struFtpCfgV40[0].bySubDirMode == 0x2 )
		{
			m_comboMainSecordDirModeCtrl.SetCurSel(1);
		}
		if (m_struFtpCfgV40[0].bySubDirMode == 0x5)
		{
			m_comboMainSecordDirModeCtrl.SetCurSel(2);
			SetMainFtpSelSecondDirShow(TRUE);			
		}
		break;
	default:	
		break;
	}
	m_UseFTPUpCtrl.SetCurSel(m_struFtpCfgV40[0].byEnableFTP);	
	m_dwPort = m_struFtpCfgV40[0].wFTPPort;
	char cUserTemp[NAME_LEN+1] = {0};
	memcpy(cUserTemp, m_struFtpCfgV40[0].szUserName, NAME_LEN);
	m_csUserName = cUserTemp;
	char cPawdTemp[PASSWD_LEN+1] = {0};
	memcpy(cPawdTemp, m_struFtpCfgV40[0].szPassWORD, PASSWD_LEN);
	
	m_csPassword = cPawdTemp;
	m_comboProtocalType.SetCurSel(m_struFtpCfgV40[0].byProtocolType);
	m_comboServerType.SetCurSel(m_struFtpCfgV40[0].byAddresType);
	
	if (m_struFtpCfgV40[0].byAddresType)
	{
		m_csIP = m_struFtpCfgV40[0].unionServer.struDomain.szDomain;
		GetDlgItem(IDC_STATIC_V4)->SetWindowText("������");
		GetDlgItem(IDC_STATIC_V6)->ShowWindow(FALSE);
		GetDlgItem(IDC_EDIT_IPV6_FIRST)->ShowWindow(FALSE);
	}
	else
	{
		GetDlgItem(IDC_STATIC_V4)->SetWindowText("IPv4/6��ַ:");
		GetDlgItem(IDC_STATIC_V6)->ShowWindow(FALSE);
		GetDlgItem(IDC_EDIT_IPV6_FIRST)->ShowWindow(FALSE);
		if (inet_addr(m_struFtpCfgV40[0].unionServer.struAddrIP.struIp.sIpV4) == 0)
		{
			m_csIP = m_struFtpCfgV40[0].unionServer.struAddrIP.struIp.byIPv6;
		}
		else
		{
			m_csIP = m_struFtpCfgV40[0].unionServer.struAddrIP.struIp.sIpV4;
		}
		
		
	}
	m_csMainFirstUserDir = m_struFtpCfgV40[0].szTopCustomDir;
	m_csMainSecordUserDir = m_struFtpCfgV40[0].szSubCustomDir;
	m_bChkAnony = m_struFtpCfgV40[0].byEnableAnony;


	//���ñ�����Ϣ
	m_DirLevelCtrl2.SetCurSel(m_struFtpCfgV40[1].byDirLevel);
	temp = m_DirLevelCtrl2.GetCurSel();
	switch (temp)
	{
	case 0:	
		m_comboSubFirstDirModeCtr.EnableWindow(FALSE);
		m_comboSubSecordDirModeCtrl.EnableWindow(FALSE);
		break;
	case 1:
		m_comboSubFirstDirModeCtr.EnableWindow(TRUE); 
		if (m_struFtpCfgV40[1].byTopDirMode == 0x1)
		{
			m_comboSubFirstDirModeCtr.SetCurSel(0);
		}
		if (m_struFtpCfgV40[1].byTopDirMode == 0x2)
		{
			m_comboSubFirstDirModeCtr.SetCurSel(1);
		}
		if (m_struFtpCfgV40[1].byTopDirMode == 0x3)
		{
			m_comboSubFirstDirModeCtr.SetCurSel(2);
		}
		if (m_struFtpCfgV40[1].byTopDirMode == 0x6)
		{
			m_comboSubFirstDirModeCtr.SetCurSel(3);
			SetSubFtpSelDirShow(TRUE);
		}
		m_comboSubSecordDirModeCtrl.EnableWindow(FALSE);
		break;
	case 2:
		m_comboSubFirstDirModeCtr.EnableWindow(TRUE);
		m_comboSubSecordDirModeCtrl.EnableWindow(TRUE);
		if (m_struFtpCfgV40[1].byTopDirMode == 0x1)
		{
			m_comboSubFirstDirModeCtr.SetCurSel(0);
		}
		if (m_struFtpCfgV40[1].byTopDirMode == 0x2)
		{
			m_comboSubFirstDirModeCtr.SetCurSel(1);
		}
		if (m_struFtpCfgV40[1].byTopDirMode == 0x3)
		{
			m_comboSubFirstDirModeCtr.SetCurSel(2);
		}

		if (m_struFtpCfgV40[1].byTopDirMode == 0x6 )
		{
			m_comboSubFirstDirModeCtr.SetCurSel(3);
			SetSubFtpSelDirShow(TRUE);
		}
		if (m_struFtpCfgV40[1].bySubDirMode == 0x1 )
		{
			m_comboSubSecordDirModeCtrl.SetCurSel(0);
		}
		if (m_struFtpCfgV40[1].bySubDirMode == 0x2 )
		{
			m_comboSubSecordDirModeCtrl.SetCurSel(1);
		}
		if (m_struFtpCfgV40[1].bySubDirMode == 0x5 )
		{
			m_comboSubSecordDirModeCtrl.SetCurSel(2);
			SetSubFtpSelSecondDirShow(TRUE);
		}
		break;
	default:	
		break;
	}
	m_UseFTPUpCtrl2.SetCurSel(m_struFtpCfgV40[1].byEnableFTP);	
	m_dwPort2 = m_struFtpCfgV40[1].wFTPPort;
	 
	memcpy(cUserTemp, m_struFtpCfgV40[1].szUserName, NAME_LEN);
	m_csUserName2 = cUserTemp;
 
	memcpy(cPawdTemp, m_struFtpCfgV40[1].szPassWORD, PASSWD_LEN);
	
	m_csPassword2 = cPawdTemp;
	m_comboProtocalType2.SetCurSel(m_struFtpCfgV40[1].byProtocolType);
	m_comboServerType2.SetCurSel(m_struFtpCfgV40[1].byAddresType);
	
	if (m_struFtpCfgV40[1].byAddresType)
	{
		m_csIP2v6 = m_struFtpCfgV40[1].unionServer.struDomain.szDomain;

		GetDlgItem(IDC_STATIC2_V4)->SetWindowText("����:");
		GetDlgItem(IDC_STATIC2_V6)->ShowWindow(FALSE);
		GetDlgItem(IDC_EDIT_IP2)->ShowWindow(FALSE);
	}
	else
	{
		GetDlgItem(IDC_STATIC2_V4)->SetWindowText("IPv4/6��ַ:");
		GetDlgItem(IDC_STATIC2_V6)->ShowWindow(FALSE);
		GetDlgItem(IDC_EDIT_IP2)->ShowWindow(FALSE);
		if (inet_addr(m_struFtpCfgV40[1].unionServer.struAddrIP.struIp.sIpV4)!= 0)
		{
			m_csIP2v6 = m_struFtpCfgV40[1].unionServer.struAddrIP.struIp.sIpV4;
		}
		else
		{
			m_csIP2v6  =  m_struFtpCfgV40[1].unionServer.struAddrIP.struIp.byIPv6;
			//GetDlgItem(IDC_EDIT_IP2)->SetWindowText(m_csIP2);
		}
	}
	m_csSubFirstUserDir = m_struFtpCfgV40[1].szTopCustomDir;
	m_csSubSecordUserDir = m_struFtpCfgV40[1].szSubCustomDir;
	m_bChkAnony2 = m_struFtpCfgV40[1].byEnableAnony;
	UpdateData(FALSE);
	//UpdateWindow();
}

void CDlgJpegCaptureCfg::GetFtpV40Info()
{
	//FTP����
	int temp, tmp1, tmp2;
    temp = m_DirLevelCtrl.GetCurSel();
	memset(&m_struFtpCfgV40,0,sizeof(m_struFtpCfgV40));
	m_struFtpCfgV40[0].struStruceHead.wLength = sizeof(m_struFtpCfgV40[0]);
    switch (temp)
    {
    case 0:
		m_struFtpCfgV40[0].byDirLevel = 0;
        break;
    case 1:
		m_struFtpCfgV40[0].byDirLevel = 1;
		tmp1 = m_comboMainFirstDirModeCtr.GetCurSel();
        if (tmp1 == 0)
        {
			m_struFtpCfgV40[0].byTopDirMode = 0x1;
        }
        if (tmp1 == 1)
        {
			m_struFtpCfgV40[0].byTopDirMode = 0x2;
        }
        if (tmp1 == 2)
        {
			m_struFtpCfgV40[0].byTopDirMode = 0x3;
        }
		
		if (tmp1 == 3)
		{
			m_struFtpCfgV40[0].byTopDirMode = 0x6;
		}
        break;
    case 2:
		m_struFtpCfgV40[0].byDirLevel = 2;
        tmp1 = m_comboMainFirstDirModeCtr.GetCurSel();
        if (tmp1 == 0)
        {
			m_struFtpCfgV40[0].byTopDirMode = 0x1;
        }
        if (tmp1 == 1)
        {
			m_struFtpCfgV40[0].byTopDirMode = 0x2;
        }
        if (tmp1 == 2)
        {
			m_struFtpCfgV40[0].byTopDirMode = 0x3;
        }

		if (tmp1 == 3)
		{
			m_struFtpCfgV40[0].byTopDirMode = 0x6;
		}

		tmp2 = m_comboMainSecordDirModeCtrl.GetCurSel();
        if (tmp2 == 0)
        {
			m_struFtpCfgV40[0].bySubDirMode = 0x1;
        }
        if (tmp2 == 1)
        {
			m_struFtpCfgV40[0].bySubDirMode = 0x2;
        }

		if (tmp2 == 2)
		{
			m_struFtpCfgV40[0].bySubDirMode = 0x5;
		}
    default:
        break;
    }
	
    m_struFtpCfgV40[0].byAddresType = m_comboServerType.GetCurSel();
	m_struFtpCfgV40[0].byProtocolType = m_comboProtocalType.GetCurSel();
	sprintf((char*)m_struFtpCfgV40[0].szTopCustomDir, m_csMainFirstUserDir, 64);
	sprintf((char*)m_struFtpCfgV40[0].szSubCustomDir, m_csMainSecordUserDir, 64);
	
	
	m_struFtpCfgV40[0].byEnableFTP = m_UseFTPUpCtrl.GetCurSel();
	m_struFtpCfgV40[0].byEnableAnony = m_bChkAnony;
	
	m_struFtpCfgV40[0].wFTPPort = (WORD)m_dwPort;
	sprintf((char*)m_struFtpCfgV40[0].szPassWORD,m_csPassword,PASSWD_LEN);
	sprintf((char*)m_struFtpCfgV40[0].szUserName,m_csUserName,NAME_LEN);
	if (m_comboServerType.GetCurSel())
	{
		sprintf((char*)m_struFtpCfgV40[0].unionServer.struDomain.szDomain, m_csIP, 64);
	}
	else
	{
		if (m_csIP.Find(":") == -1)
		{
			sprintf((char*)(&m_struFtpCfgV40[0])->unionServer.struAddrIP.struIp.sIpV4,m_csIP,16);
		}
		else
		{
			sprintf((char*)m_struFtpCfgV40[0].unionServer.struAddrIP.struIp.byIPv6,m_csIP,128);
		}
		
		
	}
	m_struFtpCfgV40[0].byType = 0;
	
	
	//FTP����
	
    temp = m_DirLevelCtrl2.GetCurSel();
	m_struFtpCfgV40[1].struStruceHead.wLength = sizeof(m_struFtpCfgV40[0]);
    switch (temp)
    {
    case 0:
		m_struFtpCfgV40[1].byDirLevel = 0;
        break;
    case 1:
	    m_struFtpCfgV40[1].byDirLevel = 1;
		tmp1 = m_comboSubFirstDirModeCtr.GetCurSel();
        if (tmp1 == 0)
        {
			m_struFtpCfgV40[1].byTopDirMode = 0x1;
        }
        if (tmp1 == 1)
        {
			m_struFtpCfgV40[1].byTopDirMode = 0x2;
        }
        if (tmp1 == 2)
        {
			m_struFtpCfgV40[1].byTopDirMode = 0x3;
        }

		if (tmp1 == 3)
        {
			m_struFtpCfgV40[1].byTopDirMode = 0x6;
        }
		break;
    case 2:
		m_struFtpCfgV40[01].byDirLevel = 2;
        tmp1 = m_comboSubFirstDirModeCtr.GetCurSel();
        if (tmp1 == 0)
        {
			m_struFtpCfgV40[1].byTopDirMode = 0x1;
        }
        if (tmp1 == 1)
        {
			m_struFtpCfgV40[1].byTopDirMode = 0x2;
        }
        if (tmp1 == 2)
        {
			m_struFtpCfgV40[1].byTopDirMode = 0x3;
        }

		if (tmp1 == 3)
        {
			m_struFtpCfgV40[1].byTopDirMode = 0x6;
        }

		tmp2 = m_comboSubSecordDirModeCtrl.GetCurSel();
        if (tmp2 == 0)
        {
			m_struFtpCfgV40[1].bySubDirMode = 0x1;
        }
        if (tmp2 == 1)
        {
			m_struFtpCfgV40[1].bySubDirMode = 0x2;
        }

		if (tmp2 == 2)
        {
			m_struFtpCfgV40[1].bySubDirMode = 0x5;
        }
    default:
        break;
    }
	
    m_struFtpCfgV40[1].byAddresType = m_comboServerType2.GetCurSel();
	m_struFtpCfgV40[1].byProtocolType = m_comboProtocalType2.GetCurSel();
	sprintf((char*)m_struFtpCfgV40[1].szTopCustomDir, m_csSubFirstUserDir, 64);
	sprintf((char*)m_struFtpCfgV40[1].szSubCustomDir, m_csSubSecordUserDir, 64);
	
	
	m_struFtpCfgV40[1].byEnableFTP = m_UseFTPUpCtrl2.GetCurSel();
	
	m_struFtpCfgV40[1].wFTPPort = (WORD)m_dwPort2;
	sprintf((char*)m_struFtpCfgV40[1].szPassWORD,m_csPassword2,PASSWD_LEN);
	sprintf((char*)m_struFtpCfgV40[1].szUserName,m_csUserName2,NAME_LEN);
	m_struFtpCfgV40[0].byEnableAnony = m_bChkAnony2;
	if (m_comboServerType2.GetCurSel())
	{
		sprintf((char*)m_struFtpCfgV40[1].unionServer.struDomain.szDomain, m_csIP2v6, 64);
	}
	else
	{
		sprintf((char*)m_struFtpCfgV40[1].unionServer.struAddrIP.struIp.byIPv6,m_csIP2v6,128);
		sprintf((char*)(&m_struFtpCfgV40[1])->unionServer.struAddrIP.struIp.sIpV4,m_csIP2,16);
 		if (m_csIP2v6.Find(":") == -1)
		{
			sprintf((char*)(&m_struFtpCfgV40[1])->unionServer.struAddrIP.struIp.sIpV4,m_csIP2v6,16);
		}
		else
		{
			sprintf((char*)m_struFtpCfgV40[1].unionServer.struAddrIP.struIp.byIPv6,m_csIP2v6,128);
		}
	}
	m_struFtpCfgV40[1].byType = 1;
}

void CDlgJpegCaptureCfg::OnEditchangeComboServertype2() 
{
	// TODO: Add your control notification handler code here
	
}

void CDlgJpegCaptureCfg::OnEditchangeComboServertype() 
{
	// TODO: Add your control notification handler code here
	if (m_comboServerType.GetCurSel())
	{
		GetDlgItem(IDC_EDIT_IPV6_FIRST)->ShowWindow(TRUE);
		GetDlgItem(IDC_STATIC_V6)->ShowWindow(TRUE);
		GetDlgItem(IDC_STATIC_V4)->SetWindowText("IPv4��ַ:");
		UpdateWindow();
	}
	else
	{
		GetDlgItem(IDC_EDIT_IPV6_FIRST)->ShowWindow(FALSE);
		GetDlgItem(IDC_STATIC_V6)->ShowWindow(FALSE);
		GetDlgItem(IDC_STATIC_V4)->SetWindowText("����:");
		UpdateWindow();
	}
}

void CDlgJpegCaptureCfg::OnSelchangeComboServertype() 
{
	// TODO: Add your control notification handler code here
	if (m_comboServerType.GetCurSel())
	{
		GetDlgItem(IDC_EDIT_IPV6_FIRST)->ShowWindow(FALSE);
		GetDlgItem(IDC_STATIC_V6)->ShowWindow(FALSE);
		GetDlgItem(IDC_STATIC_V4)->SetWindowText("����:");
		UpdateWindow();
	}
	else
	{
		GetDlgItem(IDC_EDIT_IPV6_FIRST)->ShowWindow(FALSE);
		GetDlgItem(IDC_STATIC_V6)->ShowWindow(FALSE);
		GetDlgItem(IDC_STATIC_V4)->SetWindowText("IPv4/6��ַ:");
		UpdateWindow();
	}
}

void CDlgJpegCaptureCfg::OnSelchangeComboServertype2() 
{
	// TODO: Add your control notification handler code here
	if (m_comboServerType2.GetCurSel())
	{
		GetDlgItem(IDC_EDIT_IP2)->ShowWindow(FALSE);
		GetDlgItem(IDC_STATIC2_V6)->ShowWindow(FALSE);
		GetDlgItem(IDC_STATIC2_V4)->SetWindowText("����:");
	}
	else
	{
		GetDlgItem(IDC_EDIT_IP2)->ShowWindow(FALSE);
		GetDlgItem(IDC_STATIC2_V6)->ShowWindow(FALSE);
		GetDlgItem(IDC_STATIC2_V4)->SetWindowText("IPv4/6��ַ:");
	}
}

void CDlgJpegCaptureCfg::SetMainFtpSelDirShow(BOOL bShow )
{
  	// TODO: Add your control notification handler code here
	GetDlgItem(IDC_STATIC_SELF_FIR_DIR)->ShowWindow(bShow);
	GetDlgItem(IDC_EDIT_FIRST_USERDIR)->ShowWindow(bShow);
}

void CDlgJpegCaptureCfg::SetMainFtpSelSecondDirShow(BOOL bShow )
{
	// TODO: Add your control notification handler code here
	GetDlgItem(IDC_STATIC_SELF_SEC_DIR)->ShowWindow(bShow);
	GetDlgItem(IDC_EDIT_SECOND_USERDIR)->ShowWindow(bShow);
}

void CDlgJpegCaptureCfg::SetSubFtpSelDirShow(BOOL bShow )
{
	// TODO: Add your control notification handler code here
	GetDlgItem(IDC_STATIC_SELF_FIR_DIR_SUB)->ShowWindow(bShow);
	GetDlgItem(IDC_EDIT_SUB_FIRST_USERDIR)->ShowWindow(bShow);
}

void CDlgJpegCaptureCfg::SetSubFtpSelSecondDirShow(BOOL bShow )
{
	// TODO: Add your control notification handler code here
	GetDlgItem(IDC_STATIC_SELF_SEC_DIR_SUB)->ShowWindow(bShow);
	GetDlgItem(IDC_EDIT_SUB_SECOND_USERDIR)->ShowWindow(bShow);
}

void CDlgJpegCaptureCfg::OnSelchangeComboSubDirLevel() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	SetSubFtpSelDirShow(FALSE);
	SetSubFtpSelSecondDirShow(FALSE);
	int temp;
	temp = m_DirLevelCtrl2.GetCurSel();
	switch (temp)
	{
	case 0:	
		m_comboSubFirstDirModeCtr.EnableWindow(FALSE);
        m_comboSubSecordDirModeCtrl.EnableWindow(FALSE);		
		break;
	case 1:
		m_comboSubFirstDirModeCtr.EnableWindow(TRUE); 
		m_comboSubSecordDirModeCtrl.EnableWindow(FALSE);
		break;
	case 2:
		m_comboSubFirstDirModeCtr.EnableWindow(TRUE);
		m_comboSubSecordDirModeCtrl.EnableWindow(TRUE);
		break;
	default:	
		break;
	}
	
	UpdateData(FALSE);
	
}
