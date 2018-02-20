#if !defined(AFX_JPEGPICDOWNLOAD_H__8D8921D7_5CD2_40D5_A33E_5AC96980E365__INCLUDED_)
#define AFX_JPEGPICDOWNLOAD_H__8D8921D7_5CD2_40D5_A33E_5AC96980E365__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// JPEGPicDownload.h : header file
//
/////////////////////////////////////////////////////////////////////////////
// CJPEGPicDownload dialog

class CJPEGPicDownload : public CDialog
{
// Construction
public:
	CJPEGPicDownload(CWnd* pParent = NULL);   // standard constructor

	BOOL m_bDown;
	BOOL m_bSearchDown;
	BOOL m_bBackuping;
	HANDLE m_hBackupThread;

	int m_iChannel;
	HWND m_hPareTabWnd;
	HWND m_hPareDlgWnd;
	LONG  m_lFileHandle;
	HANDLE m_hFileThread;
	HANDLE m_hGetThread;
	int iFileType;
	int m_iFileNum;
	int iSelServer;
	LONG m_lStartChan;
	LONG m_lServerID;
	LONG m_lServerType;
	BOOL m_bFindFile;
	char filenamedownload[256];
    int m_iDeviceIndex;

	POSITION  pos;
	int nSelPics;
	int nDownPics;
    NET_DVR_FIND_PICTURE_PARAM m_struFindPictureParam;
    NET_DVR_DISKABILITY_LIST  m_struDiskList;

    LONG    m_lBackupHandle;
    NET_DVR_FIND_PICTURE *m_pFindPicture;

public:
    
	void F_Close();
    BOOL CheckInitParam();
    void SetParentWnd(HWND *hhWnd, int iParentNum);
    void GetFindPictureParamFromWnd(NET_DVR_FIND_PICTURE_PARAM &struPictureParam);
    BOOL GetBackupPictureParamFromWnd_FILE(NET_DVR_BACKUP_PICTURE_PARAM &struBackPicturParam);
    BOOL GetDiskList(NET_DVR_DISKABILITY_LIST &struDiskList);
	DWORD ProcessFileSize(CString csFileSize);
    
        /*NET_DVR_FIND_PICTURE_PARAM*/
	

// Dialog Data
	//{{AFX_DATA(CJPEGPicDownload)
	enum { IDD = IDD_SUBDLG_PICTURE };
	CComboBox	m_comboBackupType;
	CComboBox	m_comboDiskList;
	CStatic	m_ShowJpegCtrl;
	CProgressCtrl	m_downProgress;
	CListCtrl	m_PicList;
	CComboBox	m_PicTypeCtrl;
	CComboBox	m_ChannelCtrl;
	CString	m_sCardNum;
	BOOL	m_bChkCard;
	CTime	m_ctDateStart;
	CTime	m_ctDateStop;
	CTime	m_ctTimeStart;
	CTime	m_ctTimeStop;
	BOOL	m_bContinue;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CJPEGPicDownload)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CJPEGPicDownload)
	virtual void OnOK();
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	afx_msg void OnSearchlist();
	afx_msg void OnDownload();
	afx_msg void OnCheckcard();
	afx_msg void OnClickRemotepiclist(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDestroy();
	afx_msg void OnBtnBackup();
	afx_msg void OnSelchangeComboDiskList();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_JPEGPICDOWNLOAD_H__8D8921D7_5CD2_40D5_A33E_5AC96980E365__INCLUDED_)
