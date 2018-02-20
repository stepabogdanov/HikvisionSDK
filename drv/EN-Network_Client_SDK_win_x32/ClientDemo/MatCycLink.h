#if !defined(AFX_MATCYCLINK_H__C81B5763_F98C_42C4_A5FE_223E644FFB9D__INCLUDED_)
#define AFX_MATCYCLINK_H__C81B5763_F98C_42C4_A5FE_223E644FFB9D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MatCycLink.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMatCycLink dialog

class CMatCycLink : public CDialog
{
// Construction
public:
	CMatCycLink(CWnd* pParent = NULL);   // standard constructor

	LONG m_lServerID;
	int m_iChannelnumber;
	LONG m_lStartChan;

    NET_DVR_IPC_PROTO_LIST m_struProtoList;

// Dialog Data
	//{{AFX_DATA(CMatCycLink)
	enum { IDD = IDD_DLG_MATCYCLINK };
	CComboBox	m_comboStreamMode;
	CComboBox	m_FacTypeCtrl;
	CComboBox	m_ComboStreamMediaPro;
	CComboBox	m_TransModesCombo;
	CComboBox	m_TransProtocolCombo;
	CComboBox	m_SwitchCombo;
	CComboBox	m_DecChanCombo2;
	CComboBox	m_DecChanCombo;
	CComboBox	m_ConnectChanCombo;
	int		m_DVRChannel;
	CString	m_DVRIP;
	CString	m_DVRPasswd;
	short	m_DVRPort;
	CString	m_DVRUser;
	int		m_PoolTime;
	BOOL	m_bCheckConnectChan;
	BOOL	m_bUseStreamMedia;
	CString	m_strStreamMediaIp;
	DWORD	m_dwStreamMediaPort;
	BOOL	m_bUseUrl;
	CString	m_csUrl;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMatCycLink)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	
	NET_DVR_MATRIX_LOOP_DECINFO_V41 m_MatLoopDec;
	int m_iChanSel;
	BOOL m_CycLink[32];

	void EnableConChan(BOOL bEnable);
	// Generated message map functions
	//{{AFX_MSG(CMatCycLink)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeCombodecchan();
	afx_msg void OnSelchangeComboconchan();
	afx_msg void OnSavepara();
	afx_msg void OnSetparam();
	afx_msg void OnSingleget();
	afx_msg void OnWholeget();
	afx_msg void OnSingleset();
	afx_msg void OnCheckconchan();
	afx_msg void OnSelchangeCombodecchan2();
	afx_msg void OnUsestreammedia();
	afx_msg void OnChkUrl();
	afx_msg void OnSelchangeComboStreamMode();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MATCYCLINK_H__C81B5763_F98C_42C4_A5FE_223E644FFB9D__INCLUDED_)
