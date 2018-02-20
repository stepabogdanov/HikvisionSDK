#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// CDlgRemoteAdvanceNetConfig dialog

class CDlgRemoteAdvanceNetConfig : public CDialog
{
	DECLARE_DYNAMIC(CDlgRemoteAdvanceNetConfig)

public:
	CDlgRemoteAdvanceNetConfig(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgRemoteAdvanceNetConfig();

// Dialog Data
	
public:
	//{{AFX_DATA(CDlgRemoteAdvanceNetConfig)
	enum { IDD = IDD_DLG_REMOTE_ADVANCE_NET_CFG };
	CComboBox	m_comboDDNSType;
	CString m_csSenderName;
	CString m_csSenderAddr;
	CString m_csAccountPwd;
	CString m_csAccountPwdConfirm;
	CString m_csAccount;
	BOOL m_bChkAuthen;
	BOOL m_bChkAttach;
	CComboBox m_comboSendInterval;
	CComboBox m_comboServerType;
	BOOL m_bChkNtp;
	CString m_csNtpAddr;
	short m_iNtpInterval;
	short m_iNTPInterHour;
	short m_iNTPInterMin;
	BOOL m_bChkDdns;
	CString m_csDDNSAddr;//domain name
	CString m_csDDNSUserName;
	CString m_csDDNSPwd;
	CString m_csDDNSPwdConfirm;
	CListCtrl m_listEmailReceiver;
	CString m_csPPPoEUserName;
	CString m_csPPPoEPwd;
	CString m_csPPPoEVeriPwd;
	CString m_csPPPoEIP;	
	CString m_csSmtpSvrAddr;
	CString m_csPop3SvrAddr;
	UINT	m_uDDNSPort;
	CString	m_csDevDomain;
	UINT	m_uNtpPort;
	short	m_wSmtpPort;
	BOOL	m_bEnableSSL;
	//}}AFX_DATA
	//{{AFX_VIRTUAL(CDlgRemoteAdvanceNetConfig)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
protected:
	// Generated message map functions
	//{{AFX_MSG(CDlgRemoteAdvanceNetConfig)
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedChkEnablePppoe();
	afx_msg void OnBnClickedBtnPppoeOk();
	afx_msg void OnBnClickedBtnNtpOk();
	afx_msg void OnBnClickedBtnDdnsOk();
	afx_msg void OnBnClickedBtnEmaileOk();	
	afx_msg void OnBnClickedBtnAddReceiver();
	afx_msg void OnBnClickedBtnDelReceiver();
	afx_msg void OnBnClickedChkUseNtp();
	afx_msg void OnBnClickedChkDdns();
	afx_msg void OnBnClickedBtnHighNetConfigOk();
	afx_msg void OnBtnExit();
	afx_msg void OnSelchangeComboDdnsType();
	afx_msg void OnBtnTest();
	afx_msg void OnBtnSnmpCfg();
	//}}AFX_MSG
	
	DECLARE_MESSAGE_MAP()
public:	
	CString m_csDnsIP;
	int m_iDeviceIndex;
	BOOL	m_bEmailGet;
	BOOL	m_bNTPGet;
	BOOL m_bChkEnablePPPoE;
	void EnablePPPOEItem(BOOL bEnable);
	void EnableNTPItem(BOOL bEnable);
	void SwitchDDNSCtrlStat(int iHost);
    void SetEmailTestState(LPCTSTR lpszString);
	LONG	m_lServerID;	
	LPNET_DVR_PPPOECFG m_pPPPoECfg;
	BOOL	m_bPPPoEGet;
	NET_DVR_DDNSPARA_V30 m_struDDNSPara;
	BOOL	m_bDDNSGet;
	NET_DVR_NTPPARA     m_struNTPPara;	
	NET_DVR_EMAILCFG_V30	m_struEmailCfg;
    HANDLE  m_hEmailTestThread;
    long m_lEmailTestHandle;
};
