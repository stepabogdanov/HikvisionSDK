#pragma once
#include "afxwin.h"


// CDlgPTZPreset dialog

class CDlgPTZPreset : public CDialog
{
	DECLARE_DYNAMIC(CDlgPTZPreset)

public:
	CDlgPTZPreset(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgPTZPreset();
	BOOL m_bAuto;
// Dialog Data

public:
	//{{AFX_DATA(CDlgPTZPreset)
	enum { IDD = IDD_DLG_PTZ_PRESET };
	CComboBox m_comboPreset;
	//}}AFX_DATA
	
	//{{AFX_VIRTUAL(CDlgPTZPreset)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
protected:
	// Generated message map functions
	//{{AFX_MSG(CDlgPTZPreset)
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedBtnPresetAdd();
	afx_msg void OnBnClickedBtnPresetDel();
	afx_msg void OnBtnExit();
	afx_msg void OnBtnPtzTran();
	afx_msg void OnBtnDo();
	afx_msg void OnBtnPtzLight();
	afx_msg void OnBtnWiper();
	//}}AFX_MSG
	
	DECLARE_MESSAGE_MAP()
		
public:
	
};
