#if !defined(AFX_DLGPDCRULECFG_H__8DD08E30_0520_45F8_8882_61155DBA3827__INCLUDED_)
#define AFX_DLGPDCRULECFG_H__8DD08E30_0520_45F8_8882_61155DBA3827__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgPdcRuleCfg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgPdcRuleCfg dialog

class CDlgPdcRuleCfg : public CDialog
{
// Construction
public:
	CDlgPdcRuleCfg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgPdcRuleCfg)
	enum { IDD = IDD_DLG_PDC_RULE_CFG };
	CComboBox	m_comboStreamTransType;
	CComboBox	m_comboDvrTransType;
	CIPAddressCtrl	m_ipStream;
	CIPAddressCtrl	m_ipDvr;
	CComboBox	m_comboDvrTransProtocol;
	CComboBox	m_comboVcaType;
	CComboBox	m_comboStream;
	CComboBox	m_comboVcaChan;
	BOOL	m_bEnableRule;
	BOOL	m_bVcaActive;
	int		m_iDvrChannel;
	int		m_iDvrPort;
	CString	m_csPassword;
	int		m_iStreamPort;
	CString	m_csUserName;
	BOOL	m_bStreamValid;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgPdcRuleCfg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgPdcRuleCfg)
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnPdcRulecfg();
	afx_msg void OnRadioDrawPolygon();
	afx_msg void OnRadioDrawDirection();
	afx_msg void OnBtnCalibration();
	afx_msg void OnSelchangeComboVcaChan();
	afx_msg void OnBtnSetVcaCtrl();
	afx_msg void OnBtnSetPuStream();
	afx_msg void OnBtnPdcQuery();
	afx_msg void OnBtnResetCounte();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public: // func

public: // param
    NET_DVR_PDC_RULE_CFG m_struPdcRuleCfg;
    long        m_lServerID; // �û�ID
    int          m_iDevIndex; // �豸����
 //   long        m_lChannel;  // �û�ͨ����
    long        m_lPlayHandle;  // Ԥ�����ز�������ΪֹͣԤ���Ȳ���
    CRect       m_rcWndRect;   //Ԥ�����ڴ�С

    BOOL   m_bMouseMove;
    BOOL   m_bCloseIn;
    
    DWORD  m_dwPosNum;  //
    
    int     m_iDrawType; //��ͼ����
    int     m_iVcaChan;     // ��ǰ����ͨ�� ��ʼĬ��Ϊ0 
    int     m_iChannelNum;   //ͨ������ 
    int     m_iStartChannel;   // ��ʼͨ��

	int     m_iCurChannel;  //����iVMS6200(V2.0),���ո�ͨ������
    NET_VCA_CTRLCFG     m_struVcaCtrl;
    NET_DVR_PU_STREAM_CFG m_struPUStream;
    
public: // func
    long StartRealPlay();  // ��ʼԤ�� 
    BOOL StopRealPlay();  // ֹͣԤ��

    void F_DrawPdcRule(LONG lRealHandle, HDC hDc, DWORD dwUser);
    void F_DrawFrame(long lRealHandle, HDC hDc, DWORD dwUser,  COLORREF color);
    BOOL IsCrossLine(NET_VCA_POLYGON *alarm_region);
    BOOL F_LineCrossDetect(NET_VCA_POINT p1, NET_VCA_POINT p2, NET_VCA_POINT q1, NET_VCA_POINT q2);
    BOOL IsValidArea(NET_VCA_POLYGON *alarm_region);
    BOOL F_IsACrossLine(NET_VCA_POLYGON *alarm_region);
    BOOL F_IsStraightLine(NET_VCA_POLYGON *alarm_region);
    void PDCDrawDirection(HDC hDc, DWORD dwUser);
    void GetPdcRuleWnd();
    void GetCtrlWnd();
    void GetPUStreamWnd();
    void SetPUStreamCfg();

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGPDCRULECFG_H__8DD08E30_0520_45F8_8882_61155DBA3827__INCLUDED_)
