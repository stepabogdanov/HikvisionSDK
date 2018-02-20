#pragma once
#include "afxwin.h"
#include "time.h"
#include "afxcmn.h"


// CDlgPlayRemoteFile dialog

class CDlgPlayRemoteFile : public CDialog
{
	DECLARE_DYNAMIC(CDlgPlayRemoteFile)

public:
	CDlgPlayRemoteFile(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgPlayRemoteFile();

// Dialog Data
	
public:
	//{{AFX_DATA(CDlgPlayRemoteFile)
	enum { IDD = IDD_DLG_PLAY_REMOTE_FILE };
	CComboBox	m_comboDiskList;
	CComboBox	m_comboAttr;
	CString m_csCardNum;
	BOOL m_bChkCardNum;
	CComboBox m_comboFileType;
	CTime m_ctDateStart;
	CTime m_ctTimeStart;
	CTime m_ctDateStop;
	CTime m_ctTimeStop;
	CListCtrl m_listRemoteFile;
	CStatic m_staticPlayWnd;
	CSliderCtrl m_sliderPlayProgress;
	CSliderCtrl m_sliderVolume;
	CProgressCtrl m_progressDownload;
	CString m_csDownloadStat;
	int		m_iOffset;
	int		m_iSpeed;
	CString	m_csFileLen;
	CString	m_csName;
	CTime	m_ctDateSet;
	CTime	m_ctTimeSet;
	BOOL	m_bBackupPlayer;
	BOOL	m_bContinue;
	CString	m_csAddLabelName;
	BOOL	m_bDrawFrame;
	//}}AFX_DATA


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


	//{{AFX_VIRTUAL(CDlgPlayRemoteFile)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
protected:
	// Generated message map functions
	//{{AFX_MSG(CDlgPlayRemoteFile)
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedBtnRemoteSearchList();
	afx_msg void OnBnClickedBtnFileDownload();
	afx_msg void OnNMDblclkListRemoteFile(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedBtnRemoteFilePlay();
	afx_msg void OnBnClickedBtnRemoteFileStop();
	afx_msg void OnBnClickedBtnRemoteFileStopSave();
	afx_msg void OnBnClickedBtnRemoteFileGotoBeginning();
	afx_msg void OnBnClickedBtnRemoteFileSlow();
	afx_msg void OnBnClickedBtnRemoteFileSnatchPic();
	afx_msg void OnBnClickedBtnRemoteFileStep();
	afx_msg void OnBnClickedBtnRemoteFileSound();
	afx_msg void OnBnClickedBtnRemoteFileFast();
	afx_msg void OnBnClickedBtnRemoteFileSave();	
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnChkCardNum();
	afx_msg void OnClickListRemoteFile(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBtnLock();
	afx_msg void OnBtnTimeLock();
	afx_msg void OnBtnTimeUnlock();
	afx_msg void OnDestroy();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnCustomdrawSliderRemoteFileProgress(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnReleasedcaptureSliderRemoteFileProgress(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnReleasedcaptureSliderRemoteFileVolume(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBtnSetTime();
	afx_msg void OnBtnBackup();
	afx_msg void OnSelchangeComboDiskList();
	afx_msg void OnBtnInsertRecordLabel();
	afx_msg void OnRadioForward();
	afx_msg void OnRadioReverse();
	//}}AFX_MSG
	
	DECLARE_MESSAGE_MAP()
		
public:
	
	int m_iDeviceIndex;
	LONG m_lLoginID;
	BOOL CheckInitParam();
	void SetParentWnd(HWND *hhWnd, int iParentNum);
	DWORD m_dwCurFileLen;
	LONG m_lDeviceType;
	BOOL m_bDownloading;
	BOOL m_bSearching;
	int m_nPlayHandle;
	BOOL m_bSound;
	BOOL m_bPause;
	BOOL m_bGetMaxTime;
	BOOL m_bFullScreen;
	HWND m_hPlayWnd;
	HWND m_hPareTabWnd;
	HWND m_hPareDlgWnd;
	CRect m_rcScreen;
	CRect m_rcWnd;
	CRect m_rcPareDlg;
	CRect m_rcPareTab;
	CRect m_rcParent;
	LONG  m_lDownloadHandle;
	HANDLE m_hFileThread;
	int m_iFileNum;

	NET_DVR_FILECOND_V40 m_struFileCond;
	int m_iItemSel;//selected file index
	int m_iFileAttr;
	int m_iChanShowNum;
	int m_iFileType;
	LONG m_lFileHandle;
	DWORD m_nFileTime;
	DWORD m_nTotalFrames;
	int m_nTotalSecond;
	int m_nTotalMinute;
	int m_nTotalHour;
	LONG m_lStartChan;
	char m_szFileName[200];
	char m_szCurFileName[200];
	char m_szDownLoadFileName[256];
	BOOL m_bSaveFile;
	BOOL m_bSetFrame;
	int m_iChanNum;
	int m_iChanIndex;

	LONG m_lPort;
	BOOL m_bChangeSpeed;
	BOOL m_bQuit;

    NET_DVR_BACKUP_NAME_PARAM m_struBackupParam;
    NET_DVR_FINDDATA_V30 m_struFindData;
	NET_DVR_DISKABILITY_LIST m_struDiskList;
    HANDLE m_hBackupThread;
    LONG m_lBackupHandle;
    BOOL m_bBackuping;
	void ExitPlayBack();
	void InitUI();
	void SetStopState();
	void PlayBack();
	void SetPlayState();
	void SetPauseState();
	void StopPlay();
	void PlayBackShowNormal();
	void EnableFlashWnd(BOOL bEnable);
	void PlayBackFullScreen();
	BOOL IsInWnd(CPoint point);

    void GetDiskList();
    DWORD ProcessFileSize(CString csFileSize);
    BOOL InsertRecordLabel(NET_DVR_RECORD_LABEL* lpRecordLabel, NET_DVR_LABEL_IDENTIFY *lpLableIdentify);


};
