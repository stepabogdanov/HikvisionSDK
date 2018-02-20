#if !defined(AFX_DLGFORTIFY_H__1EAEF6A8_2990_46E5_A399_ED62C8FBA465__INCLUDED_)
#define AFX_DLGFORTIFY_H__1EAEF6A8_2990_46E5_A399_ED62C8FBA465__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgFortify.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgFortify dialog

class CDlgFortify : public CDialog
{
// Construction
public:
	CDlgFortify(CWnd* pParent = NULL);   // standard constructor
	void LoadTreeImage();
	void CreateTree();
	CImageList m_TreeImage;
	BOOL m_bFortify;
	
	// select/ not select all the devices in the area
	void CheckAllDevState(HTREEITEM hRoot, BOOL bCheck, int uFlag);

	// add/delete device in broadcast group
	BOOL AddDVR(HTREEITEM hDevice, int iDeviceIndex , BOOL bCheck);
// Dialog Data
	//{{AFX_DATA(CDlgFortify)
	enum { IDD = IDD_DLG_FORTIFY };
	CTreeCtrl	m_treeAll;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgFortify)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgFortify)
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnFortify();
	afx_msg void OnClickTreeall(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBtnExit();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGFORTIFY_H__1EAEF6A8_2990_46E5_A399_ED62C8FBA465__INCLUDED_)
