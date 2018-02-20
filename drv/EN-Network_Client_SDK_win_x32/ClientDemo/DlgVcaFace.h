#if !defined(AFX_DLGVCAFACE_H__ACD58867_89C2_43C7_922A_CE76CF8A6430__INCLUDED_)
#define AFX_DLGVCAFACE_H__ACD58867_89C2_43C7_922A_CE76CF8A6430__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgVcaFace.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgVcaFace dialog

class CDlgVcaFace : public CDialog
{
// Construction
public:
	CDlgVcaFace(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgVcaFace)
	enum { IDD = IDD_DLG_VCA_FACE };
	CComboBox	m_comboAtmMode;
	CComboBox	m_comboStream;
	CComboBox	m_comboVcaType;
	CComboBox	m_comboVcaChan;
	BOOL	m_bVcaActive;
	BOOL	m_bChkSnapEn;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgVcaFace)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgVcaFace)
	afx_msg void OnSelchangeComboVcaChan();
	afx_msg void OnBtnSetVcaCtrl();
	afx_msg void OnBtnPuStream();
	afx_msg void OnBtnDevability();
	afx_msg void OnBtnMaskRegion();
	afx_msg void OnBtnVcaDrawMode();
	afx_msg void OnBtnFacesnap();
	afx_msg void OnBtnFindBackgroundpic();
	afx_msg void OnBtnFdProcimg();
	afx_msg void OnBtnBlacklist();
	afx_msg void OnBtnFindSnapPic();
	afx_msg void OnBtnFacematchLog();
	afx_msg void OnBtnVcaDatabase();
	afx_msg void OnBtnSnapDatabase();
	afx_msg void OnBtnFaceDatabase();
	afx_msg void OnBtnSavePath();
	afx_msg void OnBtnDevAccessCfg();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
    LONG    m_lServerID;
    int     m_iStartChannel;
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

#endif // !defined(AFX_DLGVCAFACE_H__ACD58867_89C2_43C7_922A_CE76CF8A6430__INCLUDED_)
