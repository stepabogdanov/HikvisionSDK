#if !defined(AFX_DLGXMLABILITY_H__F0CAF785_5075_4086_8F1E_F4D6C4F3C16D__INCLUDED_)
#define AFX_DLGXMLABILITY_H__F0CAF785_5075_4086_8F1E_F4D6C4F3C16D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgXmlAbility.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgXmlAbility dialog
#include "Markup.h"

class CDlgXmlAbility : public CDialog
{
// Construction
public:
	CDlgXmlAbility(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgXmlAbility)
	enum { IDD = IDD_DLG_XML_ABILITY };
	DWORD	m_dwVideoChan;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgXmlAbility)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgXmlAbility)
	afx_msg void OnBtnSofthardAbility();
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnEncodeAbility();
	afx_msg void OnBtnNetwork();
	afx_msg void OnBtnIpcFrontAbility();
	afx_msg void OnBtnDynchanAbility();
	afx_msg void OnBtnItcItsAbility();
	afx_msg void OnBtnUserAbility();
	afx_msg void OnBtnJpegCapAbility();
	afx_msg void OnBtnNetappAbility();
	afx_msg void OnBtnVideoPicAbility();
	afx_msg void OnBtnSerialAbility();
	afx_msg void OnBtnAlarmAbility();
	afx_msg void OnBtnDecoderAbility();
	afx_msg void OnBtnRaidAbility();
	afx_msg void OnBtnWallAbility();
	afx_msg void OnBtnChanInputAbility();
	afx_msg void OnBtnRecordAbility();
	afx_msg void OnBtnRemoteControlAbility();
	afx_msg void OnBtnEventAbility();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public: // mem
    LONG    m_lServerID;
    int     m_iDevIndex;
//     char    *m_pRecvBuf;
//     char    *m_pSendBuf;
public: // fun
    BOOL    GetEncodeAbility();    
    BOOL    GetCurrentEncodeAbility();

//     BOOL    ParseEncodeAbility(char *pBuf, DWORD dwBufSize);
//     BOOL    ParaseAudioVideoXml(CMarkup &struMarkup);
//     BOOL    ParaseAudioCompressXml(CMarkup &struMarkup);
//     BOOL    ParaseAudioEncodeTypeXml(CMarkup &struMarkup);
//     BOOL    ParaseVoiceTalkEncodeTypeXml(CMarkup &struMarkup);
//     BOOL    ParaseVideoCompressXml(CMarkup &struMarkup);
//     BOOL    ParaseMainChanXml(CMarkup &struMarkup);
//     BOOL    ParaseSubChanXml(CMarkup &struMarkup);

    void    PraseStrIndex(CString strIndex, int* array, int iArrayLength);
    BOOL    WirteBufToFile(char *pBuf, DWORD dwBufSize);

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGXMLABILITY_H__F0CAF785_5075_4086_8F1E_F4D6C4F3C16D__INCLUDED_)
