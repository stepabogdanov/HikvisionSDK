#if !defined(AFX_MATDYNAMICTEST_H__7153FB2E_1558_4224_AA30_429CFA570960__INCLUDED_)
#define AFX_MATDYNAMICTEST_H__7153FB2E_1558_4224_AA30_429CFA570960__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MatDynamicTest.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMatDynamicTest dialog

class CMatDynamicTest : public CDialog
{
// Construction
public:
	CMatDynamicTest(CWnd* pParent = NULL);   // standard constructor

	LONG m_lServerID;
	int m_iChannelnumber;
	LONG m_lStartChan;

    NET_DVR_IPC_PROTO_LIST m_struProtoList;

// Dialog Data
	//{{AFX_DATA(CMatDynamicTest)
	enum { IDD = IDD_DLG_MATDYNAMIC };
	CComboBox	m_FacTypeCtrl;
	CComboBox	m_ComboStreamMediaPro;
	CComboBox	m_DecChanCombo;
	CComboBox	m_TransModeCombo;
	CComboBox	m_TransProtocolCombo;
	CString	m_RemoteIP;
	int		m_RemoteSurveillace;
	CString	m_RemoteUser;
	CString	m_RemotePass;
	CString	m_strStreamMediaIp;
	DWORD	m_dwStreamMediaPort;
	BOOL	m_bUseStreamMedia;
	DWORD	m_RemotePort;
	CString	m_csUrl;
	BOOL	m_bUseUrl;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMatDynamicTest)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CMatDynamicTest)
	afx_msg void OnStartdynamic();
	afx_msg void OnStopdynamic();
	virtual BOOL OnInitDialog();
	afx_msg void OnUsestreammedia();
	afx_msg void OnChkUrl();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MATDYNAMICTEST_H__7153FB2E_1558_4224_AA30_429CFA570960__INCLUDED_)
