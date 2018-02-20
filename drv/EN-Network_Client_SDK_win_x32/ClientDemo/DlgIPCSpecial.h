#if !defined(AFX_DLGIPCSPECIAL_H__25057DA2_3A6C_420B_8613_1113541AA449__INCLUDED_)
#define AFX_DLGIPCSPECIAL_H__25057DA2_3A6C_420B_8613_1113541AA449__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgIPCSpecial.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgIPCSpecial dialog

class CDlgIPCSpecial : public CDialog
{
// Construction
public:
	CDlgIPCSpecial(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgIPCSpecial();

// Dialog Data
	//{{AFX_DATA(CDlgIPCSpecial)
	enum { IDD = IDD_DLG_IPC_SPECIAL };
	CComboBox	m_comboPtzPreset;
	CComboBox	m_comboMotionTrackGet;
	CComboBox	m_comboMotionTrackSet;
	CListCtrl	m_listGetPreCruiseiInfo;
	CListCtrl	m_listGetPresetInfo;
	CListCtrl	m_listPresetInfo;
	CComboBox	m_comboCurisePreset;
	CComboBox	m_comboCuriseTime;
	CComboBox	m_comboCruiseSpeed;
	CComboBox	m_comboCruisePoint;
	CComboBox	m_comboCruiseRoute;
	CComboBox	m_comboFECuriseCmd;
	CComboBox	m_comboPresetNum;
	CComboBox	m_comboFECCmd;
	CComboBox	m_comboFishEyeStartStop;
	CComboBox	m_comboFishEyeControlCommand;
	CComboBox	m_comboFishEyeSpeedControl;
	CComboBox	m_comboFishEyeMountType;
	CComboBox	m_comboFishEyeDisplayMode;
	CComboBox	m_comboFishEyeConnectMode;
	CComboBox	m_comboWpsConType;
	CComboBox	m_comboWirelessId;
	CComboBox	m_comboAuxAlarmType;
	CComboBox	m_comboAuxAlarmId;
	CTreeCtrl	m_treeAlarmOut;
	CComboBox	m_comboCmd;
	DWORD	m_dwDeadPixelX;
	DWORD	m_dwDeadPixelY;
	DWORD	m_dwDelayTime;
	BYTE	m_byWirelessIndex;
	BOOL	m_bChkMonitorAlarm;
	BOOL	m_bChkAudioAlarm;
	BOOL	m_bChkReportCenter;
	BOOL	m_bChkInvokeAlarmOut;
	BOOL	m_bChkInvokeJpegCapture;
	BOOL	m_bChkPicFtp;
	BOOL	m_bChkHanleAlarm;
	BOOL	m_bChkRecordEn;
	CString	m_csAlarmName;
	BOOL	m_bChkWirelessLight;
	BOOL	m_bChkWpsEn;
	CString	m_csAPPin;
	CString	m_csDevPin;
	CString	m_csWpsEssid;
	DWORD	m_dwPTZFishEyeChannelNum;
	DWORD	m_dwPtzFishEyeX;
	DWORD	m_dwPtzFishEyeY;
	DWORD	m_dwFEChannelNum;
	DWORD	m_dwCruiseChannelNum;
	int		m_iPresetNum;
	int		m_iPtzCruiseNum;
	int		m_iPresetGroupNum;
	int		m_iPreCruiseGroupNum;
	int		m_iPresetChannel;
	int		m_iPresetGetGroupNum;
	int		m_iPreCruiseChannel;
	int		m_iPreGetCruiseGroupNum;
	BYTE	m_byWirelessID;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgIPCSpecial)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgIPCSpecial)
	afx_msg void OnBtnShutterComp();
	afx_msg void OnBtnSet();
	afx_msg void OnBtnIpcOnepushFocus();
	afx_msg void OnBtnIpcResetLens();
	afx_msg void OnBtnRemotecontrolAlarm();
	afx_msg void OnBtnRemotecontrolDisalarm();
	afx_msg void OnBtnRemotecontrolStudy();
	afx_msg void OnBtnWirelessStudy();
	afx_msg void OnBtnGetAuxalarm();
	afx_msg void OnBtnSetAuxalarm();
	afx_msg void OnClickTreeAlarmOut(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBtnSaveAuxAlarm();
	afx_msg void OnSelchangeComboAuxAlarmId();
	afx_msg void OnSelchangeComboAuxalarmType();
	afx_msg void OnSelchangeComboWirelessAlarmId();
	afx_msg void OnPaint();
	afx_msg void OnChkWpsEn();
	afx_msg void OnBtnRefresh();
	afx_msg void OnBtnWpsConnect();
	afx_msg void OnBtnUpdatePin();
	afx_msg void OnBtnGetDevPin();
	afx_msg void OnBtnFishEyeSet();
	afx_msg void OnBtnFishEyeGet();
	afx_msg void OnBtnFishEyePtzSet();
	afx_msg void OnBtnFePtzSet();
	afx_msg void OnBtnPtzUp();
	afx_msg void OnBtnPtzLeft();
	afx_msg void OnBtnPtzRight();
	afx_msg void OnBtnPtzDown();
	afx_msg void OnBtnPtzBig();
	afx_msg void OnBtnPtzNarrow();
	afx_msg void OnBtnPtzAuto();
	afx_msg void OnBtnPtzCircle();
	afx_msg void OnBtnFePtzClean();
	afx_msg void OnBtnFePtzTurn();
	afx_msg void OnBtnFeCruiseSet();
	afx_msg void OnBtnFeCruiseDel();
	afx_msg void OnBtnFeCruiseRun();
	afx_msg void OnBtnFeCruiseStop();
	afx_msg void OnBtnGetPresetNum();
	afx_msg void OnBtnGetPtzcruiseNum();
	afx_msg void OnBtnGetpresetInfo();
	afx_msg void OnBtnGetcruiseInfo();
	afx_msg void OnBtnMotionTrackSet();
	afx_msg void OnBtnMotionTrackGet();
	afx_msg void OnBtnUpPreset();
	afx_msg void OnBtnDelseq();
	afx_msg void OnBtnIpaddrFilter();
	afx_msg void OnBtnUploadLogo();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	LONG    m_lServerID;
    int     m_iDevIndex;
	LONG    m_lChannel;
	LONG m_lAuxAlarmID;
	LONG m_lWirelessID;
	LONG m_lPlayHandle;
	DWORD dwChoosePtzindexNum;
	BOOL m_bAlarmOut[MAX_ALARMOUT_V30];
	NET_IPC_AUX_ALARMCFG m_struAuxAlarm;
	void CreateTree();
	
	int m_iPtzPresetNum;

	CRect m_rcWnd; 
	NET_VCA_POINT m_struPoint;

	NET_DVR_PRESETCFG m_struPreSetCfg[128];
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGIPCSPECIAL_H__25057DA2_3A6C_420B_8613_1113541AA449__INCLUDED_)
