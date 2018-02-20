#if !defined(AFX_MATDISPCHAN_H__B12A9342_F03D_4BC7_B3B3_060224F63241__INCLUDED_)
#define AFX_MATDISPCHAN_H__B12A9342_F03D_4BC7_B3B3_060224F63241__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MatDispChan.h : header file
//
#include "vector"
#include "afxwin.h"

using namespace std;

/////////////////////////////////////////////////////////////////////////////
// CMatDispChan dialog

class CMatDispChan : public CDialog
{
// Construction
public:
	CMatDispChan(CWnd* pParent = NULL);   // standard constructor
    void EnableStreamMedia(BOOL bUseStreamMedia);

	int m_lServerID;
	int m_lStartChan;
	int m_iChannelnumber;

    NET_DVR_IPC_PROTO_LIST m_struProtoList;
// Dialog Data
	//{{AFX_DATA(CMatDispChan)
	enum { IDD = IDD_DLG_MATDISPCHAN };
	CComboBox	m_comboStreamMode;
	CComboBox	m_FacTypeCtrl;
	CComboBox	m_comboStreamType;
	CComboBox	m_ComboPassiveTransProtol;
	CComboBox	m_ComboStreamMediaPro;
	CComboBox	m_ComboGetStreamMode;
	CComboBox	m_IsLinkCombo;
	CComboBox	m_ChanCombo;
	CDateTimeCtrl	m_EndTime;
	CDateTimeCtrl	m_EndDate;
	CDateTimeCtrl	m_StartTime;
	CDateTimeCtrl	m_StartDate;
	CComboBox	m_DIModeCombo;
	CComboBox	m_DIProTypeCombo;
	CComboBox m_DecStateCombo;
	CString	m_DIIP;
	BYTE	m_DIChanNum;
	CString	m_DIUserName;
	CString	m_DIPwd;
	CString	m_FileName;
	DWORD	m_CopyRate;
	CString	m_strStreamMediaIp;
	DWORD	m_dwStreamMediaPort;
	BOOL	m_bUseStreamMedia;
	DWORD	m_dwPassivePort;
	DWORD	m_DIPort;
	BOOL	m_bUseUrl;
	CString	m_csUrl;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMatDispChan)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CMatDispChan)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeChancombo();
	afx_msg void OnTimer(UINT nIDEvent);
	virtual void OnCancel();
	afx_msg void OnUsestreammedia();
	afx_msg void OnChkUrl();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

protected:	
	BOOL GetChanStatus(DWORD DispChanNum,int index);
	void ShowChanInfo(int index);

private:
	NET_DVR_MATRIX_DEC_CHAN_STATUS m_DecChanStatus[2 * MAX_CHANNUM];
	NET_DVR_MATRIX_DEC_CHAN_INFO_V41 m_DecChanInfo[2 * MAX_CHANNUM];

	int m_iChanSel;
	vector<BOOL> m_vGetStatus;
	vector<BOOL> m_vbGetInfo;

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MATDISPCHAN_H__B12A9342_F03D_4BC7_B3B3_060224F63241__INCLUDED_)
