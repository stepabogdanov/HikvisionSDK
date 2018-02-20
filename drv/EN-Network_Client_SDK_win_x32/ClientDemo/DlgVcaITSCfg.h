#if !defined(AFX_DLGVCAITSCFG_H__FBF48ECE_C485_475E_B949_C74BEDEE105B__INCLUDED_)
#define AFX_DLGVCAITSCFG_H__FBF48ECE_C485_475E_B949_C74BEDEE105B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgVcaITSCfg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgVcaITSCfg dialog

class CDlgVcaITSCfg : public CDialog
{
// Construction
public:
	CDlgVcaITSCfg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgVcaITSCfg)
	enum { IDD = IDD_DLG_VCA_ITS_CFG };
	CComboBox	m_comboSceneMode;
	CComboBox	m_comboStream;
	CComboBox	m_comboVcaType;
	CComboBox	m_comboVcaChan;
	BOOL	m_bVcaActive;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgVcaITSCfg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgVcaITSCfg)
	afx_msg void OnBtnVcaDevAbility();
	afx_msg void OnBtnSetVcaCtrl();
	afx_msg void OnSelchangeComboVcaChan();
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnVcaDrawMode();
	afx_msg void OnBtnMaskRegion();
	afx_msg void OnBtnReferenceRegion();
	afx_msg void OnBtnLanecfg();
	afx_msg void OnBtnAidRulecfg();
	afx_msg void OnBtnTpsRulecfg();
	afx_msg void OnBtnPuStream();
	afx_msg void OnBtnItsCalibrate();
	afx_msg void OnBtnSetSceneMode();
	afx_msg void OnBtnVcaParamKey();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
    int     m_iDevIndex;
    LONG    m_lServerID;
    int     m_iStartChannel;
    int     m_iChannelnumber;
    NET_VCA_DRAW_MODE m_struVCADrawMode;
    int     m_iVcaChannel;
	int     m_iCurChannel;  //兼容iVMS6200(V2.0),按照各通道能力
    NET_VCA_CTRLCFG m_struVcaCtrlCfg;
public:
    BOOL InsertComboVcaType();
    void GetDevVcaChanPara();
    void SetComboVcaType();

    NET_DVR_REGION_LIST m_struMaskRegionList;
    NET_DVR_REGION_LIST m_struReferenceRegionList;
    NET_DVR_LANE_CFG    m_struLaneCfg;
    NET_DVR_AID_RULECFG m_struAIDRuleCfg;
    NET_DVR_TPS_RULECFG m_struTPSRuleCfg;
    DWORD m_dwSceneMode;    

    BOOL SetTPSRuleCfg();
    BOOL GetTPSRuleCfg();
    BOOL SetAIDRuleCfg();
    BOOL GetAIDRuleCfg();
    BOOL SetLaneCfg();
    BOOL GetLaneCfg();
    BOOL SetMaskRegion();
    BOOL GetMaskRegion();
    BOOL SetReferenceRegion();
    BOOL GetReferenceRegion();

    BOOL GetSceneMode();
    BOOL SetSceneMode();
    
    void InitWnd();
    void SetSceneModeToWnd();
    void GetSceneModeFromWnd();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGVCAITSCFG_H__FBF48ECE_C485_475E_B949_C74BEDEE105B__INCLUDED_)
