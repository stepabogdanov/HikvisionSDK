#pragma once
#include "time.h"
#include "afxwin.h"
#include "afxcmn.h"


// CDlgPlayRemoteTime dialog

class CDlgPlayRemoteTime : public CDialog
{
	DECLARE_DYNAMIC(CDlgPlayRemoteTime)

public:
	CDlgPlayRemoteTime(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgPlayRemoteTime();

// Dialog Data
protected:
	HICON m_hSoundStartIcon;
	HICON m_hSoundStopIcon;

	HICON m_hPlayEnableIcon;
	HICON m_hPlayDisableIcon;

	HICON m_hPauseEnableIcon;
	HICON m_hPauseDisableIcon;

	HICON m_hStopEnableIcon;
	HICON m_hStopDisableIcon;

	HICON m_hGotoHeadDisableIcon;
	HICON m_hGotoHeadEnableIcon;

	HICON m_hGotoTailEnableIcon;
	HICON m_hGotoTailDisableIcon;

	HICON m_hFastDisableIcon;
	HICON m_hFastEnableIcon;

	HICON m_hSlowDisableIcon;
	HICON m_hSlowEnableIcon;

	HICON m_hStepEnableIcon;
	HICON m_hStepDisableIcon;

	HICON m_hStepBackEnableIcon;
	HICON m_hStepBackDisableIcon;

	HICON m_hCaptureIcon;
public:
	//{{AFX_DATA(CDlgPlayRemoteTime)
	enum { IDD = IDD_DLG_PLAY_REMOTE_TIME };
	CSliderCtrl	m_SliderTimeProgress;
	CComboBox	m_comboDiskList;
	CTime m_ctDateStart;
	CTime m_ctTimeStart;
	CTime m_ctDateStop;
	CTime m_ctTimeStop;
	CStatic m_staticWnd;
	CSliderCtrl m_sliderVolume;
	CString	m_csTotalLen;
	CTime	m_ctDateSet;
	CTime	m_ctTimeSet;
	BOOL	m_bBackupPlayer;
	int		m_iDownloadSpeed;
	BOOL	m_bDrawFrame;
	//}}AFX_DATA


	//{{AFX_VIRTUAL(CDlgPlayRemoteTime)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
protected:
	// Generated message map functions
	//{{AFX_MSG(CDlgPlayRemoteTime)
	virtual BOOL OnInitDialog();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnBnClickedBtnTimePlay();
	afx_msg void OnBnClickedBtnTimeStop();
	afx_msg void OnBnClickedBtnTimeSlow();
	afx_msg void OnBnClickedBtnTimeFast();
	afx_msg void OnBnClickedBtnTimePicSnatch();
	afx_msg void OnBnClickedBtnTimeSound();
	afx_msg void OnBnClickedBtnRtDownload();
	afx_msg void OnBnClickedBtnRtPlaySave();	
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnBtnSetTime();
	afx_msg void OnBtnBackup();
	afx_msg void OnSelchangeComboDiskList();
	afx_msg void OnBtnDownloadSpeed();
	afx_msg void OnRadioForward();
	afx_msg void OnRadioReverse();
	//}}AFX_MSG
	
	DECLARE_MESSAGE_MAP()
		
public:
	int m_iChanIndex;
	int m_iDeviceIndex;
	LONG m_lStartChan;
	int m_iChanShowNum;
	LONG m_lLoginID;
	
	HWND m_hPareTabWnd;
	HWND m_hPareDlgWnd;
	LONG m_lPlayHandle;
	BOOL m_bFullScreen;
	CRect m_rcScreen;
	CRect m_rcParent;
	CRect m_rcPareDlg;
	CRect m_rcPareTab;
	CRect m_rcWnd;
	BOOL m_bSound;
	BOOL m_bPause;
	BOOL m_bDown;
	LONG m_lLoadHandle;
	BOOL m_bTimeSave;
	
    NET_DVR_BACKUP_TIME_PARAM m_struBackupTimeParam;
    NET_DVR_DISKABILITY_LIST m_struDiskList;
    HANDLE m_hBackupThread;
    LONG m_lBackupHandle;
    BOOL m_bBackuping;
    void GetDiskList();
    
	void SetParentWnd(HWND *hhWnd, int iParentNum);
	void StopPlay();
	void InitUI();
	void EnableFlashWnd(BOOL bEnable);
	void ShowNormal();
	void ShowFullScreen();
	BOOL IsInWnd(CPoint point);
	void SetPlayState();
	BOOL CheckInitParam();
};
