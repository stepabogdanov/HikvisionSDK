#if !defined(AFX_DLGVCADEVABILITY_H__5E4EB178_F2FF_4913_9FC3_191235B91123__INCLUDED_)
#define AFX_DLGVCADEVABILITY_H__5E4EB178_F2FF_4913_9FC3_191235B91123__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgVcaDevAbility.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgVcaDevAbility dialog

class CDlgVcaDevAbility : public CDialog
{
// Construction
public:
	CDlgVcaDevAbility(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgVcaDevAbility)
	enum { IDD = IDD_DLG_VCA_DEV_ABILITY };
	int		m_iAtmChanNum;
	int		m_iVcaChanNum;
	int		m_iITSChanNum;
	int		m_iBBaseChanNum;
	int		m_iBFullChanNum;
	int		m_iBAdvanceChanNum;
	int		m_iPlateChanNum;
	int		m_iBPrisonChanNum;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgVcaDevAbility)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgVcaDevAbility)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
    LONG m_lServerID;
    int  m_iDevIndex;
    NET_VCA_DEV_ABILITY m_struVcaDevAbility;
    BOOL GetVcaDevAbility();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGVCADEVABILITY_H__5E4EB178_F2FF_4913_9FC3_191235B91123__INCLUDED_)
