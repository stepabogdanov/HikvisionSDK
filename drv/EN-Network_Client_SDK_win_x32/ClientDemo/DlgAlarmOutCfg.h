#if !defined(AFX_DLGALARMOUTCFG_H__7E69A958_4D64_4ECC_92CF_D0E162AE317B__INCLUDED_)
#define AFX_DLGALARMOUTCFG_H__7E69A958_4D64_4ECC_92CF_D0E162AE317B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgAlarmOutCfg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgAlarmOutCfg dialog

class CDlgAlarmOutCfg : public CDialog
{
// Construction
public:
	CDlgAlarmOutCfg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgAlarmOutCfg)
	enum { IDD = IDD_DLG_ALARMOUT_CFG };
	CListCtrl	m_listSirenAlarmIn;
	CComboBox	m_comboSirenIndex;
	CListCtrl	m_listAlarmIn;
	CComboBox	m_comboAlarmOutIndex;
	int		m_iDelayTime;
	CString	m_csName;
	CString	m_csSirenName;
	int		m_iSirenDelayTime;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgAlarmOutCfg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgAlarmOutCfg)
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnSetAlarmoutParam();
	afx_msg void OnSelchangeComboAlarmoutIndex();
	afx_msg void OnBtnOpenAlarmout();
	afx_msg void OnBtnCloseAlarmout();
	afx_msg void OnBntSetSirenParam();
	afx_msg void OnSelchangeComboSirenIndex();
	afx_msg void OnBtnOpenSiren();
	afx_msg void OnBtnCloseSiren();
	afx_msg void OnRclickListAlarmIn(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnMenuCancelAll();
	afx_msg void OnMenuSelectAll();
	afx_msg void OnBtnOpenAlarmoutAll();
	afx_msg void OnBtnCloseAlarmoutAll();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public: // mem
    NET_DVR_ALARMHOST_ABILITY m_struAbility;
    LONG    m_lServerID;
    int     m_iDevIndex;
	int		m_iCurSirenIndex;
    
    NET_DVR_ALARMOUT_PARAM m_struAlarmOutParam;
    NET_DVR_SIREN_PARAM m_struSirenParam;
public: // fun
    void InitWnd();
    void InitAlarmOutIndex();
    void InitAlarmInList();
    void InitSirenIndexCombo();
    void InitSirenAlarmInList();
    
    BOOL GetAlarmOutParam(NET_DVR_ALARMOUT_PARAM& struAlarmOutParam, LONG lAlarmOutPort);
    BOOL SetAlarmOutParam(NET_DVR_ALARMOUT_PARAM& struAlarmOutParam, LONG lAlarmOutPort);
    BOOL SetAlarmOut(LONG lAlarmOutPort, LONG lAlarmOutStatic);
    BOOL GetSirenParam(NET_DVR_SIREN_PARAM& struSirenParam);
    BOOL SetSirenParam(NET_DVR_SIREN_PARAM& struSirenParam);
    BOOL SirenControl(LONG lSirenStatic);

    void GetAlarmOutParamFromWnd(NET_DVR_ALARMOUT_PARAM &struAlarmOutParam);
    void SetAlarmOutParamToWnd(NET_DVR_ALARMOUT_PARAM &struAlarmOutParam);
    void GetAssociateAlarmInParamFromWnd(BYTE *byAlarmIn, DWORD dwSize);
    void SetAssociateAlarmInParamToWnd(BYTE *byAlarmIn, DWORD dwSize);
    
    void GetSirenParamFromWnd(NET_DVR_SIREN_PARAM &struSirenParam);
    void SetSirenParamToWnd(NET_DVR_SIREN_PARAM &struSirenParam);

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGALARMOUTCFG_H__7E69A958_4D64_4ECC_92CF_D0E162AE317B__INCLUDED_)
