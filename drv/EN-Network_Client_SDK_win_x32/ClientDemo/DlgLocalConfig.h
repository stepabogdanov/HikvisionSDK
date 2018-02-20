#pragma once
#include "afxwin.h"
#include "time.h"
#include "afxdtctl.h"


// CDlgLocalConfig dialog

class CDlgLocalConfig : public CDialog
{
	DECLARE_DYNAMIC(CDlgLocalConfig)

public:
	CDlgLocalConfig(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgLocalConfig();

// Dialog Data

public:	
	//{{AFX_DATA(CDlgLocalConfig)
	enum { IDD = IDD_DLG_LOCAL_CONFIG };
	CComboBox	m_AllAddressCtrl;
	CComboBox	m_comboSDKLog;
	CComboBox	m_comboBFrame;
	CComboBox	m_comboSoundMode;
	CButton m_chkCyclePlay;
	CButton m_chkUseCard;
	int m_iCycleTime;
	CButton m_chkAutoRecord;
	CButton m_chkCycleRecord;
	CComboBox m_comboRecFirstDisk;
	CComboBox m_comboRecLastDisk;
	int m_iFileInterval;
	CString m_csDownLoadPath;
	CString m_csPicSnatchPath;
	CString m_csLogPath;
	CButton m_chkSysTime;
	CTime m_ctimeCheckDeviceTime;
	BOOL m_bCyclePlay;
	BOOL m_bAutoRecord;
	BOOL m_bCycleRecord;
	BOOL m_bUseCard;
	BOOL m_bChkDeviceTime;
	CDateTimeCtrl m_ctCheckTime;
	CComboBox m_comboVideoFormat;
	BOOL	m_bChkNoDecode;
	BOOL	m_bBlock;
	int		m_iTimeOut;
	CString	m_strSdklog;
	BOOL	m_bWriteSdkLog;
	BOOL	m_bReconnect;
	int		m_iListenPort;
	//}}AFX_DATA

	LONG m_lListenHandle;



	//{{AFX_VIRTUAL(CDlgLocalConfig)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
protected:
	// Generated message map functions
	//{{AFX_MSG(CDlgLocalConfig)
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedBtnSelectDownLoadPath();
	afx_msg void OnBnClickedLocalOk();
	afx_msg void OnBnClickedChkCyclePlay();
	afx_msg void OnBnClickedChkAutoRecord();
	afx_msg void OnBnClickedBtnSetTime();
	afx_msg void OnBnClickedBtnSelectPicPath();
	afx_msg void OnBnClickedBtnSelectLogPath();
	afx_msg void OnBnClickedChkSystime();
	afx_msg void OnBnClickedChkUseCard();
	afx_msg void OnSelchangeComboSoundMode();
	afx_msg void OnButtonStartListen();
	afx_msg void OnButtonStopListen();
	afx_msg void OnButtonRefrush();
	afx_msg void OnBtnSelectSdklogPath();
	afx_msg void OnBtnBindIp();
	//}}AFX_MSG
	
	DECLARE_MESSAGE_MAP()
		
public:
	
	CString GetDirectoryPath();
	
};
