#if !defined(AFX_DLGVCAAIDRULECFG_H__99F338AC_6EA9_4523_B17C_6655F112BB51__INCLUDED_)
#define AFX_DLGVCAAIDRULECFG_H__99F338AC_6EA9_4523_B17C_6655F112BB51__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgVcaAidRuleCfg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgVcaAidRuleCfg dialog

class CDlgVcaAidRuleCfg : public CDialog
{
// Construction
public:
	CDlgVcaAidRuleCfg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgVcaAidRuleCfg)
	enum { IDD = IDD_DLG_VCA_AID_RULECFG };
	CComboBox	m_comboFilterMode;
	CComboBox	m_comboResolution;
	CComboBox	m_comboProPicType;
	CComboBox	m_comboPicQuality;
	CListCtrl	m_listRecordChan;
	CListCtrl	m_listAlarmOut;
	CComboBox	m_comboWeekday;
	CComboBox	m_comboCopyTime;
	CComboBox	m_comboAidRuleIndex;
	CListCtrl	m_listAIDType;
	int		m_iCongestionDuration;
	int		m_iCongestionLength;
	int		m_iDebris;
	int		m_iInverseAngle;
	int		m_iInverseDistance;
	int		m_iInverseDuration;
	int		m_iParking;
	int		m_iPedestrian;
	CString	m_csRuleName;
	BOOL	m_bEnable;
	BOOL	m_bHandleType1;
	BOOL	m_bHandleType2;
	BOOL	m_bHandleType3;
	BOOL	m_bHandleType4;
	BOOL	m_bHandleType5;
	int		m_iHour11;
	int		m_iHour12;
	int		m_iHour21;
	int		m_iHour22;
	int		m_iMin11;
	int		m_iMin12;
	int		m_iMin21;
	int		m_iMin22;
	BOOL	m_bDrawPolygon;
	BOOL	m_bFilterActive;
	float	m_fMaxHeight;
	float	m_fMaxWidth;
	float	m_fMinHeight;
	float	m_fMinWidth;
	BOOL	m_bSetMaxFilter;
	BOOL	m_bSetMiniFilter;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgVcaAidRuleCfg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgVcaAidRuleCfg)
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnSetAidRule();
	afx_msg void OnSelchangeComboAidRuleIndex();
	afx_msg void OnTimeOk();
	afx_msg void OnTimeCopy();
	afx_msg void OnSelchangeComboweekday();
	afx_msg void OnSelchangeCombocopytime();
	afx_msg void OnBtnOneRuleConfirm();
	afx_msg void OnCheckFilterActive();
	afx_msg void OnChkDrawPolygon();
	afx_msg void OnSelchangeComboFilterMode();
	afx_msg void OnCheckSetMiniFilter();
	afx_msg void OnCheckSetMaxFilter();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
    LONG    m_lServerID;
    LONG    m_lChannel;
    int     m_iDevIndex;
    NET_DVR_AID_RULECFG m_struAIDRuleCfg;
    NET_DVR_LANE_CFG m_struLaneCfg;
    
    long m_lPlayHandle;     // preview handle

    NET_DVR_ONE_AID_RULE m_struAIDOneRule;
    int     m_iAidRuleIndex;

    DWORD   m_dwAlarmOutNum;
    int     m_iChannelnumber;

    DWORD   m_dwPosNum; 
    CRect   m_rcWnd;
    BOOL    m_bCloseIn[MAX_AID_RULE];
    BOOL    m_bMouseMove[MAX_AID_RULE];
    BOOL    m_bNeedRedraw[MAX_AID_RULE];
    NET_VCA_POLYGON m_struVcaPolygon[MAX_AID_RULE];
    NET_VCA_CHAN_IN_PARAM m_struVcaChanInParam;
    NET_DVR_ITS_ABILITY m_struItsAbility;

    NET_DVR_PU_STREAM_CFG m_struPuStream;
    LONG m_lPUServerID;
    BOOL SetAIDRuleCfg();
    BOOL GetAIDRuleCfg();
    BOOL GetLaneCfg();
    void InitWnd();
    void SetAidRuleToWnd(NET_DVR_AID_RULECFG const &struAidRule);
    void GetAidRuleFromWnd(NET_DVR_AID_RULECFG &struAidRule);
    void SetOneAidRuleToWnd(NET_DVR_ONE_AID_RULE const &struOneAidRule);
    void GetOneAidRuleFromWnd(NET_DVR_ONE_AID_RULE &struOneAidRule);
    void SetAidParamToWnd(NET_DVR_AID_PARAM const &struAidParam);
    void GetAidParamFromWnd(NET_DVR_AID_PARAM& struAidParam);
    void SetAidTypeToWnd(DWORD dwEventType);
    void GetAidTypeFromWnd(DWORD &dwAidEventType);
    void GetSchedTimeFromWnd(NET_DVR_SCHEDTIME *pSchedTime);
    void SetSchedTimeToWnd(NET_DVR_SCHEDTIME* pSchedTime);
    void SetHandleToWnd(NET_DVR_HANDLEEXCEPTION_V30 const &struHandleException);
    void GetHandleFromWnd(NET_DVR_HANDLEEXCEPTION_V30 &struHandleException);
    void SetSizeFilterToWnd(const NET_VCA_SIZE_FILTER &struSizeFilter);
    void GetSizeFilterFromWnd(NET_VCA_SIZE_FILTER &struSizeFilter);

    void EnableFilterModeWnd(BYTE byMode);
    
    BOOL F_TimeTest();

    LONG    StartPlay();
    BOOL    StopPlay();

    BOOL PreDrawPolygonMsg(MSG* pMsg, CPoint &pt);
    BOOL PreDrawSizeFilterMsg(MSG* pMsg, CPoint &pt);
    void F_DrawFun(long lPlayHandle, HDC hDc, DWORD dwUser);
    void DrawLane(HDC hDc);

    BOOL GetVcaChanAbility();

    BOOL GetPuStreamCfg(NET_DVR_PU_STREAM_CFG &struPUStream);
    BOOL SetPuStreamCfg(NET_DVR_PU_STREAM_CFG &struPUStream);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGVCAAIDRULECFG_H__99F338AC_6EA9_4523_B17C_6655F112BB51__INCLUDED_)
