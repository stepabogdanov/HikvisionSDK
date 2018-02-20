#if !defined(AFX_MATPLAYBACK_H__AF25D63B_05A9_46E9_BD80_111DE2102B43__INCLUDED_)
#define AFX_MATPLAYBACK_H__AF25D63B_05A9_46E9_BD80_111DE2102B43__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MatPlayBack.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMatPlayBack dialog

class CMatPlayBack : public CDialog
{
// Construction
public:
	CMatPlayBack(CWnd* pParent = NULL);   // standard constructor

	LONG m_lServerID;
	int m_iChannelNumber;
	LONG m_lStartChan;
// Dialog Data
	//{{AFX_DATA(CMatPlayBack)
	enum { IDD = IDD_DLG_MATPLAYBACK };
	CComboBox	m_DecChanCombo;
	CSliderCtrl	m_ctlProgress;
	CDateTimeCtrl	m_StopTime;
	CDateTimeCtrl	m_StopDate;
	CDateTimeCtrl	m_StartTime;
	CDateTimeCtrl	m_StartDate;
	CString	m_PlayBackName;
	CString	m_PlayBackIP;
	CString	m_PlayBackPass;
	int		m_PlayBackChan;
	short	m_PlayBackPort;
	CString	m_PlayBackUser;
	CString	m_PlayStatus;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMatPlayBack)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CMatPlayBack)
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnFast();
	afx_msg void OnPlayFile();
	afx_msg void OnSlow();
	afx_msg void OnSound();
	afx_msg void OnStep();
	afx_msg void OnStop();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnRadioname();
	afx_msg void OnRadiotime();
	afx_msg void OnSetup();
	virtual void OnCancel();
	afx_msg void OnReleasedcaptureProgressSlider(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnStopsound();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

protected:
	void F_InitUI();
	void F_SetStopState();
	void F_SetPlayState();
	void F_SetPauseState();

	void EnableControl(BOOL bEnable);
private:
	HICON m_hSoundStartIcon;
	HICON m_hSoundStopIcon;
	
	HICON m_hPlayEnableIcon;
	HICON m_hPlayDisableIcon;
	
	HICON m_hPauseEnableIcon;
	HICON m_hPauseDisableIcon;
	
	HICON m_hStopEnableIcon;
	HICON m_hStopDisableIcon;
	
	HICON m_hFastDisableIcon;
	HICON m_hFastEnableIcon;
	
	HICON m_hStepEnableIcon;
	HICON m_hStepDisableIcon;

	HICON m_hSlowDisableIcon;
	HICON m_hSlowEnableIcon;

	BOOL m_bSound;
	BOOL m_bPlay;
	BOOL m_bPause;

	NET_DVR_MATRIX_DEC_REMOTE_PLAY_STATUS m_struState;
	NET_DVR_MATRIX_DEC_REMOTE_PLAY m_struPlay;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MATPLAYBACK_H__AF25D63B_05A9_46E9_BD80_111DE2102B43__INCLUDED_)
