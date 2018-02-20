#if !defined(AFX_DLGVCABEHAVIORCFG_H__4EBD75E1_AFF5_4308_974D_FFC38019252E__INCLUDED_)
#define AFX_DLGVCABEHAVIORCFG_H__4EBD75E1_AFF5_4308_974D_FFC38019252E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgVcaBehaviorCfg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgVcaBehaviorCfg dialog

class CDlgVcaBehaviorCfg : public CDialog
{
// Construction
public:
	CDlgVcaBehaviorCfg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgVcaBehaviorCfg)
	enum { IDD = IDD_DLG_VCA_BEHAVIORCFG };
	CComboBox	m_comboVcaType;
	CComboBox	m_comboStream;
	CComboBox	m_comboAtmMode;
	CComboBox	m_comboVcaChan;
	BOOL	m_bVcaActive;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgVcaBehaviorCfg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgVcaBehaviorCfg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeComboVcaChan();
	afx_msg void OnBtnSetVcaCtrl();
	afx_msg void OnBtnVcaRestart();
	afx_msg void OnBtnMaskRegion();
	afx_msg void OnBtnEnterRegion2();
	afx_msg void OnBtnVcaDrawMode();
	afx_msg void OnBtnLfCfg();
	afx_msg void OnBtnVcaBehaviorKey();
	afx_msg void OnBtnDevability();
	afx_msg void OnBtnSetRulecfg();
	afx_msg void OnBtnPuStream();
	afx_msg void OnBtnBehaviorCalibrate();
	afx_msg void OnBtnSizeFilter();
	afx_msg void OnBtnFaceDetect();
	afx_msg void OnBtnVcaWorkStatus();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
    LONG    m_lServerID;
    int     m_iStartChannel ;
    int     m_iDevIndex;
    int     m_iChannelNum;
    int     m_iVcaChannel;
	int     m_iCurChannel;  //兼容iVMS6200(V2.0),按照各通道能力
    NET_VCA_CTRLCFG m_struVcaCtrlCfg;
private:
    void InitWnd();
    void InitComboVcaType();
    BOOL SetVcaCtrlToWnd(NET_VCA_CTRLINFO const &struVcaCtrlInfo);
    BOOL GetVcaCtrlFromWnd(NET_VCA_CTRLINFO &struVcaCtrlInfo);
    BOOL SetVcaCtrlCfg();
    BOOL GetVcaCtrlCfg();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGVCABEHAVIORCFG_H__4EBD75E1_AFF5_4308_974D_FFC38019252E__INCLUDED_)
