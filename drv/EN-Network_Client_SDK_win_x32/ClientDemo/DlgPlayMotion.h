#if !defined(AFX_DLGPLAYMOTION_H__F1C33271_6554_417D_A0FA_57D824B56848__INCLUDED_)
#define AFX_DLGPLAYMOTION_H__F1C33271_6554_417D_A0FA_57D824B56848__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgPlayMotion.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgPlayMotion dialog
#define MOTION_NUM 4
class CDlgPlayMotion : public CDialog
{
// Construction
public:
	CDlgPlayMotion(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgPlayMotion)
	enum { IDD = IDD_DLG_PLAY_MOTION };
	CListCtrl	m_listMotionTime;
	CComboBox	m_comboSearchSense;
	CTime	m_ctDateStart;
	CTime	m_ctDateStop;
	CTime	m_ctTimeStart;
	CTime	m_ctTimeStop;
	int		m_iTime;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgPlayMotion)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgPlayMotion)
	afx_msg void OnBtnMotionSearch();
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnPreview();
	afx_msg void OnClickListMotionTime(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDblclkListMotionTime(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
    LONG    m_lChannel;
    LONG    m_lServerID;
    int     m_iDevIndex;
    NET_DVR_SMART_SEARCH_PARAM m_struSmartSearch; 
    LONG    m_lSearchHandle;
    NET_VCA_RECT m_struRect[MOTION_NUM];
    LONG    m_lRealPlayHandle;
    BOOL    m_bMouseMove[MOTION_NUM];
    BOOL    m_bDrawed[MOTION_NUM];
    HANDLE m_hFindThread;
    int     m_iDrawingIndex;
    int     m_iPreviewState;    
    LONG    m_lPlayBackHandle;
    NET_DVR_TIME m_struStartTime;
    NET_DVR_TIME m_struStopTime;
    int  m_iItemSel;
public:
    long StartPlay();

    BOOL StopPlay();
    void SetParentWnd(HWND *hhWnd, int iParentNum);
    BOOL CheckInitParam();
    void BtnRemoteFileStop();
    void BtnRemotFilePlay();
    void PlayBack();
    void StopPlayBack();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGPLAYMOTION_H__F1C33271_6554_417D_A0FA_57D824B56848__INCLUDED_)
