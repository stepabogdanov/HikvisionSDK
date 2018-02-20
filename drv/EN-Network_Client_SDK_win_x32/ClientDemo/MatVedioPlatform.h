#if !defined(AFX_MATVEDIOPLATFORM_H__9AB835CF_15C7_4CF1_BB2F_D62B3C014285__INCLUDED_)
#define AFX_MATVEDIOPLATFORM_H__9AB835CF_15C7_4CF1_BB2F_D62B3C014285__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MatVedioPlatform.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMatVedioPlatform dialog

class CMatVedioPlatform : public CDialog
{
// Construction
public:
	CMatVedioPlatform(CWnd* pParent = NULL);   // standard constructor

    LONG m_lServerID;
    NET_DVR_ALLSUBSYSTEMINFO m_AllSubSystemInfo;
	NET_DVR_NATASSOCIATECFG m_struNatAssociateCfg;
	NET_DVR_VIDEOPLATFORMALARMCFG m_struAlarmTemperatureCfg;

// Dialog Data
	//{{AFX_DATA(CMatVedioPlatform)
	enum { IDD = IDD_DLG_MATVEDIOPLATPORM };
	CComboBox	m_AlarmTypeCtrl;
	CComboBox	m_UseNatCtrl;
	CComboBox	m_SubSystemTypeCtrl;
	CComboBox	m_SubSystemCtrl;
	CComboBox	m_LoginTypeCtrl;
	CString	m_strDnsIp;
	CString	m_strDomainName;
	int		m_iSubSystemChan;
	CString	m_strSubSystemIp;
	CString	m_strSubSystemPsw;
	DWORD	m_dwSubSystemPort;
	CString	m_strSubSystemUser;
	CString	m_strSerial;
	CString	m_strMaskIp;
	CString	m_strGateWayIp;
	CString	m_strNat1IP;
	CString	m_strNat2Ip;
	CString	m_strNat1Gateway;
	CString	m_strNat1Mask;
	CString	m_strNat2Gateway;
	CString	m_strNat2Mask;
	BOOL	m_bAudioAlarm;
	BOOL	m_bJpegCapture;
	BOOL	m_bMonitorAlarm;
	BOOL	m_bReportCenter;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMatVedioPlatform)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CMatVedioPlatform)
	virtual void OnCancel();
	afx_msg void OnSetvedioplatform();
	afx_msg void OnSavepara();
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeCombologintype();
	afx_msg void OnSelchangeCombosubsystemnum();
	afx_msg void OnBtnGet();
	afx_msg void OnBtnSet();
	afx_msg void OnBtnGettempalarm();
	afx_msg void OnBtnSettempalarm();
	afx_msg void OnButtonTemp();
	afx_msg void OnButtonPull();
	afx_msg void OnSelchangeComboAlarmtype();
	afx_msg void OnButtonSure();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MATVEDIOPLATFORM_H__9AB835CF_15C7_4CF1_BB2F_D62B3C014285__INCLUDED_)
