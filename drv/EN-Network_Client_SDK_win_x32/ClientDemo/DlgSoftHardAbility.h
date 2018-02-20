#if !defined(AFX_DLGSOFTHARDABILITY_H__6FB2DEEB_5242_4460_ABCE_1573D2CA04F9__INCLUDED_)
#define AFX_DLGSOFTHARDABILITY_H__6FB2DEEB_5242_4460_ABCE_1573D2CA04F9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgSoftHardAbility.h : header file
//
#define MAX_VERSION_LENGTH 8
/////////////////////////////////////////////////////////////////////////////
// CDlgSoftHardAbility dialog
#include "Markup.h"

typedef struct tagSOFTWARE_ABILITY_PARAM
{
    BYTE    byNASSupport;				// �Ƿ�֧��nas�洢���ܣ�1-֧�֣���֧��ʱû�иýڵ�
	BYTE	byNASNum;					// ֧��nas������8����֧��ʱû�иýڵ�
	BYTE	byShowStringNum;			// ֧���ַ������Ӹ���,8
	BYTE	byMotionAlarmSpt;			// �Ƿ�֧���ƶ���ⱨ����1-֧�֣���֧��ʱû�иýڵ�
    BYTE	byVILostAlarmSpt;			// �Ƿ�֧����Ƶ��ʧ������1-֧�֣���֧��ʱû�иýڵ�
	BYTE	byHideAlarmSpt;				// �Ƿ�֧���ڵ�������1-֧�֣���֧��ʱû�иýڵ�
	BYTE	byShelterSpt;				// �Ƿ�֧���ڸǣ�1-֧�֣���֧��ʱû�иýڵ�
	BYTE    byRtspSupport;				// �Ƿ�֧��rtsp���紫�书�ܣ�1-֧�֣���֧��ʱû�иýڵ�
	BYTE	byRtpOverRtspSpt;			// �Ƿ�֧��rtp over rtsp���紫�书�ܣ�1-֧�֣���֧��ʱû�иýڵ�
	BYTE	byRtspOverHttpSpt;			// �Ƿ�֧��http over rtsp���紫�书�ܣ�1-֧�֣���֧��ʱû�иýڵ�
	
    BYTE    byNtpSupport;				// �Ƿ�֧��NTPУʱ- 1-֧�֣���֧��ʱû�иýڵ�
    BYTE    byEptzSupport;				// �Ƿ�֧�ֵ�����̨��1-֧�֣���֧��ʱû�иýڵ�       
    BYTE	byPtzSpt;					// �Ƿ�֧����̨���ƣ�1-֧�֣���֧��ʱû�иýڵ�
	BYTE    byDDNSSupport;				// �Ƿ�֧��DDNS - 1-֧�֣���֧��ʱû�иýڵ�
    BYTE	byDDNSHostType[MAX_VERSION_LENGTH];				// DDNS���������ͣ�0-Hikvision DNS��1-Dyndns��2-PeanutHull(������)��3-NO-IP
	BYTE	bySNMPSpt;					// �Ƿ�֧��SNMP,1-֧�֣���֧��ʱû�иýڵ�
	BYTE    bySNMPVersion[MAX_VERSION_LENGTH];				// SNMPЭ��汾��1:v1,2:v2,3:v3
	BYTE    byUPNPSupport;				// �Ƿ�֧��UPNP- 1-֧�֣���֧��ʱû�иýڵ�
    BYTE	byiSCSISpt;					// �Ƿ�֧��iSCSI��1-֧�֣���֧��ʱû�иýڵ�
	BYTE    byIpv6Support;				// �Ƿ�֧��ipv6- 1-֧�֣���֧��ʱû�иýڵ�
    BYTE    byVcaSupport;				// �Ƿ�֧������- 1-֧�֣���֧��ʱû�иýڵ�
    BYTE	byMulStreamSpt;				// �Ƿ�֧�ָ�������1-֧�֣���֧��ʱû�иýڵ�
	BYTE	bySubStreamSpt;				// �Ƿ�֧����������1-֧�֣���֧��ʱû�иýڵ�
	BYTE	byEmailSpt;					// �Ƿ�֧��Email��1-֧�֣���֧��ʱû�иýڵ�
//	BYTE	bySadpSpt;					// �Ƿ�֧��sadp��0����֧�֣�1��֧�� ����������֧��
	BYTE    bySadpVersion[MAX_VERSION_LENGTH];				// sadp�汾��0��v1.0��1��v2.0����֧��ʱû�иýڵ�
//	BYTE	byZeroChanSpt;				// �Ƿ�֧����ͨ����0����֧�֣�1��֧��
	BYTE	byZeroChanNum;				// ��ͨ�����������1��1-֧�֣���֧��ʱû�иýڵ�
    BYTE	byBackupSpt;				// �Ƿ�֧�ֱ��ݣ�1-֧�֣���֧��ʱû�иýڵ�
	BYTE	bySmartSearchSpt;			// �Ƿ�֧����������¼��1-֧�֣���֧��ʱû�иýڵ�
	BYTE	byATMSpt;					// �Ƿ�֧��ATM���ã�1-֧�֣���֧��ʱû�иýڵ�
	BYTE	byFileLockSpt;				// �Ƿ�֧���ļ�����/������1-֧�֣���֧��ʱû�иýڵ�
//	BYTE	byVoiceTalkSpt;				// �Ƿ�֧�������Խ���1-֧�֣���֧��ʱû�иýڵ�
	BYTE	byBitrateLimitSpt;			// �Ƿ�֧�������������ʶ�̬���ƣ�1-֧�֣���֧��ʱû�иýڵ�
//	BYTE	res;
	int		iMaxLoginNum;				// ֧�����ע��·����512��һ���Ʒ128,��Ƶ�ۺ�ƽ̨32
	int		iMaxPreviewNum;				// ֧�����Ԥ��·����512���ϲ�Ʒ24,�µ�64
	int		iMaxPlayBackNum;			// ֧�����ط�·����512��ǰ��:�ط�/Ԥ���ϼ�24
	int		iMaxChanLinkNum;			// ͨ��֧�������������512���º�˲�Ʒ128,����Ϊ6
	BYTE	byShutDownSpt;				// �Ƿ�֧�ֹػ���1-֧�֣���֧��ʱû�иýڵ�
	BYTE	byFrameFreezeSpt;			// �Ƿ�֧��Ԥ�õ㶳�ᣬ1-֧�֣���֧��ʱû�иýڵ�
	tagSOFTWARE_ABILITY_PARAM()
    {
        byNASSupport = 0;
		byNASNum = 0;
		byShowStringNum = 0;
		byMotionAlarmSpt = 0;
		byVILostAlarmSpt = 0;
		byHideAlarmSpt = 0;
		byShelterSpt = 0;
        byRtspSupport = 0;
		byRtpOverRtspSpt = 0;
		byRtspOverHttpSpt = 0;
        byNtpSupport = 0;
        byEptzSupport = 0;
		byPtzSpt = 0;		
        byDDNSSupport = 0;
		memset(byDDNSHostType,0,sizeof(byDDNSHostType));
	//	byDDNSHostType = 0;
		bySNMPSpt = 0;
		memset(bySNMPVersion,0,sizeof(bySNMPVersion));
	//	bySNMPVersion = 0;
        byUPNPSupport = 0;
		byiSCSISpt = 0;
		byIpv6Support  = 0;
        byVcaSupport = 0;
		byMulStreamSpt = 0;
		bySubStreamSpt = 0;
		byEmailSpt = 0;
	//	bySadpSpt = 0;
		memset(bySadpVersion,0,sizeof(bySadpVersion));
	//	bySadpVersion = 0;
	//	byZeroChanSpt = 0;
		byZeroChanNum = 0;
		byBackupSpt = 0;
		bySmartSearchSpt = 0;
		byATMSpt = 0;
		byFileLockSpt = 0;
	//	byVoiceTalkSpt = 0;
		byBitrateLimitSpt = 0;
		iMaxLoginNum = 0;
		iMaxPreviewNum = 0;
		iMaxPlayBackNum = 0;
		iMaxChanLinkNum = 0;
		byShutDownSpt = 0;
		byFrameFreezeSpt = 0;
    }
}SOFTWARE_ABILITY_PARAM, *LPSOFTWARE_ABILITY_PARAM;


typedef struct tagHARDWARE_ABILITY_PARAM
{
    BYTE    byAlarmInPortNum;   // �����������
    BYTE    byAlarmOutPortNum;  // �����������
    BYTE    byRs232Num;         // RS232����
    BYTE    byRs485Num;         // RS485����    
    BYTE    byNetworkPortNum;   // ���ڸ���
    BYTE    byUsbNum;           // USB����
    BYTE    bySDNum;            // SD������
	BYTE	byHardDiskNum;		// Ӳ�̸���
    BYTE    byVideoInNum;       // VideoInNum    
    BYTE    byVideoOutNum;      // VideoOutNum
    BYTE    byAudioInNum;       // AIN����
    BYTE    byAudioOutNum;      // AOUT����
	BYTE	byAudioTalkNum;		// �����Խ�ͨ��������2
    BYTE    bySDSupport;        // �Ƿ�֧��SD��    
    BYTE    byWifiSupport;      // �Ƿ�֧��WiFi- 1��֧��,��֧��ʱû�иýڵ�
    BYTE    byPOESupport;       // �Ƿ�֧��POE- 1��֧��,��֧��ʱû�иýڵ�
    BYTE    byIRSSupport;       // �Ƿ�֧�ֺ��� - 1��֧��,��֧��ʱû�иýڵ�
    BYTE    byVideoSupport;     // �Ƿ�֧�ֱ������- 1: ֧��,��֧��ʱû�иýڵ�
    BYTE	byAnalogChannelNum; // ֧��ģ��ͨ��������255
	BYTE	byIPChannelNum;		// ֧������ͨ��������255
	BYTE	byMulNetworkCardSpt;// �Ƿ�֧�ֶ�������1��֧��,��֧��ʱû�иýڵ�
	BYTE	byNetworkCardNum;	// ֧�ֶ�����������4
	BYTE	byVGANum;			// ֧��VGA������255
	BYTE	byHDMINum;			// ֧��HDMI������255
	BYTE	byCVBSNum;			// ֧��CVBS������255
	BYTE	byAuxoutNum;		// ֧�ָ��ڸ�����255
//	BYTE	byRaidSpt;			// �Ƿ�֧��raid��1��֧��,��֧��ʱû�иýڵ�
	int  	iRaidType;			// 0:Ӳraid,1:��raid,�����֧��raid������������Ĭ����-1��ʾ,����������û�иýڵ�
    BYTE    byResetSupport;     // �Ƿ�֧�ָֻ��������� 1��֧��,��֧��ʱû�иýڵ�
    BYTE    byRes1[3];          // �����ֽ�   
	DWORD	dwHardwareVersion;  // ���汾
    DWORD   dwFlashSize;        // Flash��С
    DWORD   dwRamSize;          // Ram ��С
    char    chUsbVersion[MAX_VERSION_LENGTH];   // USB �汾
    tagHARDWARE_ABILITY_PARAM()
    {
        byAlarmInPortNum = 0;
        byAlarmOutPortNum = 0;
        byRs232Num = 0;
        byRs485Num = 0;
        
        byNetworkPortNum = 0;
        byUsbNum = 0;
        bySDNum = 0;
		byHardDiskNum = 0;
        byVideoInNum = 0;
        
        byVideoOutNum = 0;
        byAudioInNum = 0;
        byAudioOutNum = 0;
		byAudioTalkNum = 0;
        bySDSupport = 0;
        
        byWifiSupport = 0;
        byPOESupport = 0;
        byIRSSupport = 0;
        byVideoSupport = 0;
		byAnalogChannelNum = 0;
        byIPChannelNum = 0;
		byMulNetworkCardSpt = 0;
		byNetworkCardNum = 0;
		byVGANum = 0;
		byHDMINum = 0;
		byCVBSNum = 0;
		byAuxoutNum = 0;
//	    byRaidSpt = 0;	
		iRaidType = -1;
        byResetSupport = 0;
        memset(byRes1, 0, sizeof(byRes1));
        dwHardwareVersion = 0;
        dwFlashSize = 0;
        dwRamSize = 0;
        memset(chUsbVersion, 0, sizeof(chUsbVersion));
    }
}HARDWARE_ABILITY_PARAM, *LPHARDWARE_ABILITY_PARAM;

typedef struct tagNEEDREBOOT_PARAM
{
	BYTE	byImportCfgFileReboot;		// ���������ļ��Ƿ��Զ�������1����Ҫ����������Ҫ����ʱû�иýڵ�
	BYTE	byRS232workModeReboot;		// ����232����ģʽ�����Ƿ���Ҫ������1����Ҫ����������Ҫ����ʱû�иýڵ�
	BYTE	byNetPortReboot;			// ���紫��˿ڸ����Ƿ���Ҫ������1����Ҫ����������Ҫ����ʱû�иýڵ�
	BYTE	byDhcpEnableReboot;			// DHCP����״̬�����Ƿ���Ҫ������1����Ҫ����������Ҫ����ʱû�иýڵ�
	BYTE	byHttpPortReboot;			// http�˿ڸ����Ƿ���Ҫ������1����Ҫ����������Ҫ����ʱû�иýڵ�
	BYTE	byPPPoEReboot;				// pppoe���������Ƿ���Ҫ������1����Ҫ����������Ҫ����ʱû�иýڵ�
	BYTE	byHDParamReboot;			// Ӳ�̲��������Ƿ���Ҫ������1����Ҫ����������Ҫ����ʱû�иýڵ�
	BYTE	byRecordTimeReboot;			// ¼��ƻ���ʱ������Ƿ���Ҫ������1����Ҫ����������Ҫ����ʱû�иýڵ�
	BYTE	byVideoEncodeTypeReboot;	// ѹ����������Ƶ�������͸����Ƿ���Ҫ������1����Ҫ����������Ҫ����ʱû�иýڵ�
	BYTE	byAudioEncodeTypeReboot;	// ѹ����������Ƶ�������͸����Ƿ���Ҫ������1����Ҫ����������Ҫ����ʱû�иýڵ�
	BYTE	byStandardTypeReboot;		// ֻ�����͸����Ƿ���Ҫ������1����Ҫ����������Ҫ����ʱû�иýڵ�
	tagNEEDREBOOT_PARAM()
	{
		byImportCfgFileReboot = 0;		
		byRS232workModeReboot = 0;		
		byNetPortReboot = 0;			
		byDhcpEnableReboot = 0;			
		byHttpPortReboot = 0;			
		byPPPoEReboot = 0;				
		byHDParamReboot = 0;			
		byRecordTimeReboot = 0;			
		byVideoEncodeTypeReboot = 0;	
		byAudioEncodeTypeReboot = 0;	
		byStandardTypeReboot = 0;	
	}
}NEEDREBOOT_PARAM,*LPNEEDREBOOT_PARAM;
typedef struct tagSOFTHARDWARE_ABILITY_PARAM
{
    SOFTWARE_ABILITY_PARAM struSoftAbilityParam;
    HARDWARE_ABILITY_PARAM struHardAbilityParam;
	NEEDREBOOT_PARAM struNeedRebootParam;
}SOFTHARDWARE_ABILITY_PARAM, *LPSOFTHARDWARE_ABILITY_PARAM;

class CDlgSoftHardAbility : public CDialog
{
// Construction
public:
	CDlgSoftHardAbility(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgSoftHardAbility)
	enum { IDD = IDD_DLG_SOFTHARD_ABILITY };
	CListBox	m_lstSnmpVersion;
	CListBox	m_lstSadpVersion;
	CListBox	m_lstDdnsType;
	BOOL	m_bDDNS;
	BOOL	m_bEptz;
	BOOL	m_bIpv6;
	BOOL	m_bNas;
	BOOL	m_bNtp;
	BOOL	m_bRtsp;
	BOOL	m_bUpnp;
	BOOL	m_bVca;
	BOOL	m_bSupportIRS;
	BOOL	m_bSupportPOE;
	BOOL	m_bSupportReset;
	BOOL	m_bSuportSD;
	BOOL	m_bSupportVideo;
	BOOL	m_bSupportWifi;
	int		m_iAlarmOutNum;
	int		m_iAlarmInNum;
	int		m_iAudioInNum;
	int		m_iAudioOutNum;
	UINT	m_dwFlashSize;
	int		m_iNetworkPortNum;
	UINT	m_dwRamSize;
	int		m_iRs232Num;
	int		m_iRs485Num;
	int		m_iSDNum;
	int		m_iUsbNum;
	CString	m_csUsbVersion;
	int		m_iVideoInNum;
	int		m_iVideoOutNum;
	BYTE	m_byNasNum;
	BYTE	m_byShowStringNum;
	BOOL	m_bATM;
	BOOL	m_bAudioEncodeTypeReboot;
	BOOL	m_bBackup;
	BOOL	m_bBitrateLimit;
	BOOL	m_bDHCPReboot;
	BOOL	m_bEmailSPT;
	BOOL	m_bFileLockSPT;
	BOOL	m_bHDParamReboot;
	BOOL	m_bHideAlarmSPT;
	BOOL	m_bHttpOverRtspSPT;
	BOOL	m_bHttpPortReboot;
	BOOL	m_bImportCFGFileReboot;
	BOOL	m_bISCSISpt;
	BOOL	m_bMotionDetectAlarmSPT;
	BOOL	m_bMulStreamSPT;
	BOOL	m_bNetPortReboot;
	BOOL	m_bPtzSPT;
	BOOL	m_bRecordTimeReboot;
	BOOL	m_bRS232Reboot;
	BOOL	m_bRtpoverRtsp;
	BOOL	m_bShutDown;
	BOOL	m_bSmartSearch;
	BOOL	m_bSNMP;
	BOOL	m_bStandardTypeReboot;
	BOOL	m_bSubStreamSPT;
	BOOL	m_bVideoEncodeTypeReboot;
	BOOL	m_bVILostAlarmSPT;
	CString	m_csDDNSType;
	int		m_iMaxChanLinkNum;
	int		m_iMaxLoginNum;
	int		m_iMaxPlayBackNum;
	int		m_iMaxPreviewNum;
	CString	m_csSadpVersion;
	CString	m_csSNMPVersion;
	BYTE	m_byZeroChanNum;
	BOOL	m_bPPPoeReboot;
	BOOL	m_bMulNetworkCard;
	BOOL	m_bSupportRaid;
	BYTE	m_byAnalogChanNum;
	BYTE	m_byAudioTalkNum;
	BYTE	m_byAuxoutNum;
	BYTE	m_byHardDiskNum;
	DWORD	m_dwHardwareVersion;
	BYTE	m_byIPChanNum;
	BYTE	m_byNetworkCardNum;
	BYTE	m_byVGANum;
	BOOL	m_bShelterSPT;
	int		m_iRaidType;
	BYTE	m_byHDMINum;
	BYTE	m_byCVBSNum;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgSoftHardAbility)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgSoftHardAbility)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
    LONG    m_lServerID;
    int     m_iDevIndex;
    char    *m_pRecvBuf;
    char    *m_pSendBuf;

    SOFTHARDWARE_ABILITY_PARAM m_struAbilityParam;
public:
    BOOL    GetSoftHardAbility();
    BOOL    ParseSoftHardAbilityXml(char *pBuf, DWORD dwBufSize);
    BOOL    WirteBufToFile(char *pBuf, DWORD dwBufSize);
    BOOL    SetSoftHardAbilityToWnd(SOFTHARDWARE_ABILITY_PARAM struSoftHardAbility);
    BOOL    SetSoftAbilityToWnd(SOFTWARE_ABILITY_PARAM struSoftwareAbility);
	BOOL	SetNeedRebootToWnd(NEEDREBOOT_PARAM struNeedReboot);
    BOOL    SetHardAbilityToWnd(HARDWARE_ABILITY_PARAM struHardwareAbility);
	void	ParseStrIndex(CString strIndex, byte* array, int iArrayLength);
	void	SetRangeToWnd(CListBox* pList, BYTE* pArray, int iArrayLength);
//SOFTHARDWARE_ABILITY_PARAM g_struSofgHardAbilityParam;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGSOFTHARDABILITY_H__6FB2DEEB_5242_4460_ABCE_1573D2CA04F9__INCLUDED_)
