#pragma once


// CDlgUpgrade dialog
//update operation
class CDlgUpgrade : public CDialog
{
	DECLARE_DYNAMIC(CDlgUpgrade)

public:
	CDlgUpgrade(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgUpgrade();

// Dialog Data

public:
	//{{AFX_DATA(CDlgUpgrade)
	enum { IDD = IDD_DLG_UPGRADE };
	CProgressCtrl	m_progressSub;
	CComboBox	m_comboChan;
	CComboBox	m_comboUpgradeType;
	CComboBox	m_comboEnvironment;
	CProgressCtrl	m_progressUpgrade;
	CString m_csUpgradeFile;
	CString m_csUpgradeStat;
	CString	m_csUpgradeStep;
	//}}AFX_DATA
	
	//{{AFX_VIRTUAL(CDlgUpgrade)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
protected:
	// Generated message map functions
	//{{AFX_MSG(CDlgUpgrade)
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedBtnBrowseFile();
	afx_msg void OnBnClickedBtnUpgrade();
	afx_msg void OnBnClickedBtnUpgradeExit();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnBtnSetEnviro();
	afx_msg void OnSelchangeComboUpgradeType();
	//}}AFX_MSG
	
	DECLARE_MESSAGE_MAP()
		
public:
	LONG m_lUpgradeHandle;
	
	LONG	m_lServerID;
	UINT	m_lpUpgradeTimer;
	BOOL	m_bUpgrade;
	int		m_iDeviceIndex;
};
