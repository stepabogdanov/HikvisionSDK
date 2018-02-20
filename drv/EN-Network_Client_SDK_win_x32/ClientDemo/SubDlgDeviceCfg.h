#pragma once
#include "afxwin.h"


// CSubDlgDeviceCfg dialog

class CSubDlgDeviceCfg : public CDialog
{
	DECLARE_DYNAMIC(CSubDlgDeviceCfg)

public:
	CSubDlgDeviceCfg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CSubDlgDeviceCfg();

// Dialog Data
public:
	//{{AFX_DATA(CSubDlgDeviceCfg)
	enum { IDD = IDD_SUB_DLG_DEVICE_CFG };
	CComboBox	m_comboIPv6Mode;
	CComboBox	m_cmbMenuOutputMode;
	CComboBox	m_comboStorageMode;
	CComboBox	m_comboPlug;
	CComboBox	m_comboEsata;
	CComboBox	m_comboDevSupport;
	CComboBox	m_comboSubProtocol;
	CComboBox	m_comboMainProtocol;
	CComboBox	m_comboMinor;
	CString m_csDeviceName;
	int m_iHdNum;
	int m_iYKQID;
	CString m_csIPResolver;
	CString m_csDeviceIP;
	CString m_csMultiIP;
	int m_iMainPort;
	CString m_csGatewayIP;
	CString m_csIPMask;
	CComboBox m_comboNetFace;
	CComboBox m_comboUseZoom;
	CString m_csDeviceSerialNo;
	CString m_csSoftwareVersion;
	CString m_csHardwareVersion;
	CString m_csDspVersion;
	int m_iAlarmInNum;
	int m_iAlarmOutNum;
	int m_iChanNum;
	CComboBox m_comboCycleRec;
	CString m_csMacAddr;
	CString m_csRemoteManageHost1IP;
	CString	m_csAuxoManageHostIP;
	UINT	m_iAuxoManagePort;
	BOOL	m_bChkDhcp;
	CString	m_csPanelVersion;
	int		m_iZeroChanNum;
	CString	m_csDevTypeName;
	//}}AFX_DATA
	
	//{{AFX_VIRTUAL(CSubDlgDeviceCfg)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
protected:
	// Generated message map functions
	//{{AFX_MSG(CSubDlgDeviceCfg)
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedBtnRemoteNetOk();
	afx_msg void OnBnClickedBtnHighNetCfg();
	afx_msg void OnBnClickedBtnJpegFtp();
	afx_msg void OnBnClickedBtnMatDecDns();
	afx_msg void OnBnClickedBtnAdvanceNetSetup();
	afx_msg void OnBnClickedBtnRemoteNetNfs();
	afx_msg void OnBtnZone();
	afx_msg void OnBtnRtsp();
	afx_msg void OnChkDhcp();
	afx_msg void OnBtnAudiotalkcodetConfig();
	afx_msg void OnBtnWifiConfig();
	afx_msg void OnBtnCCDConfig();
	afx_msg void OnButtonMultNetcard();
	afx_msg void OnButtonJpegFtp();
	afx_msg void OnBtnNetworkFlowtest();
	afx_msg void OnBtnBondingCfg();
	afx_msg void OnButtonUpnp();
	afx_msg void OnButtonAes();
	afx_msg void OnButtonEsataMinisasUsage();
	afx_msg void OnBtnAutoReboot();
	afx_msg void OnBtnGetEthernetIpv6Cfg();
	//}}AFX_MSG
	
	DECLARE_MESSAGE_MAP()
		
public:
	BOOL CfgSetup();
	BOOL CheckInitParam();
	void CurCfgUpdate();
	void EnableDhcp();
	inline BOOL ValidIPv6(BYTE *ip);
	
	DWORD m_dwUseZoom;
	NET_DVR_SCALECFG m_struScale;
	int	m_iChanCount;//preview channel number
	LONG	m_lStartChannel;	
	NET_DVR_DEVICECFG_V40 m_struDeviceCfg;
	NET_DVR_NETCFG_V30 m_struNetCfg;
	NET_DVR_MENU_OUTPUT_MODE m_struMenuOutputMode;
	BOOL	m_bSetDeviceCfg;
	BOOL	m_bSupScale;
	int		m_iSelType;
	int m_iTypeNum;
	
	int m_iHttpPort;
	int m_iRemoteManageHost1Port;
	BOOL m_bDeviceCfgSet;
	BOOL m_bNetCfgSet;
	
	int m_iDeviceIndex;
	LONG m_lLoginID;
	
	//afx_msg void OnBnClickedBtnRemoteDeviceOk();
	
	CString m_csAlarmHostIP;
	int m_iAlarmHostPort;
	int m_iResolverPort;
	CString m_csDNSIP1;
	CString m_csDNSIP2;
	short m_wMTU;
};
