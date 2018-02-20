#pragma once
#include "afxcmn.h"
#include "afxwin.h"

#include "ClientDemo.h"
#include "DlgRemoteCfg.h"
#include "DlgOutputCtrl.h"
#include "DlgChannelInfo.h"
#include "DlgConfigAll.h"
#include "DlgLocalConfig.h"
#include "DlgPlayBack.h"
#include "DlgHardDiskCfg.h"
#include "DlgRemoteIPAccess.h"
#include "DlgDeviceState.h"

typedef int (_stdcall *SetDisplayStandardProc)(UINT, VideoStandard_t);
typedef int (_stdcall *SetDisplayRegionProc)(UINT, UINT, REGION_PARAM*, UINT);
typedef int (_stdcall *ClearDisplayRegionProc)(UINT, UINT);
typedef int (_stdcall *SetDisplayRegionPositionProc)(UINT, UINT, UINT, UINT);
typedef int (_stdcall *FillDisplayRegionProc)(UINT, UINT, unsigned char);
typedef int (_stdcall *SetEncoderVideoExtOutputProc)(UINT, UINT, BOOL, UINT, UINT, UINT);
typedef int (_stdcall *SetDecoderVideoExtOutputProc)(UINT, UINT, BOOL, UINT, UINT, UINT);
typedef int (_stdcall *SetDecoderVideoOutputProc)(UINT, UINT, BOOL, UINT, UINT, UINT);

void CALLBACK MessageCallback(LONG lCommand, NET_DVR_ALARMER *pAlarmer, char *pAlarmInfo, DWORD dwBufLen, void* pUser);

typedef unsigned int (_stdcall *GetDisplayChannelCountProc)();
// CClientDemoDlg dialog
class CClientDemoDlg : public CDialog
{
	DECLARE_DYNAMIC(CClientDemoDlg)

public:
	CClientDemoDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CClientDemoDlg();
	int m_iSelListType;

// Dialog Data
	enum { IDD = IDD_DLG_CLIENT_DEMO };

	enum {PREVIEW_WND = 0, CONFIG_ALL_WND, PLAY_BACK_WND};
	//{{AFX_VIRTUAL(CClientDemoDlg)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	//}}AFX_VIRTUAL
public:
	//{{AFX_MSG(CClientDemoDlg)
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnMove(int x, int y); 
	afx_msg void OnNMClickTreeDeviceList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMRclickTreeDeviceList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMDblclkTreeDeviceList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnCbnSelchangeComboWndNum();	
	afx_msg void OnBnClickedBtnConfig();
	afx_msg void OnBnClickedBtnRecord();
	afx_msg void OnCbnSelchangeComboNetdelay();
	afx_msg void OnBnClickedBtnPlayback();
	afx_msg void OnBnClickedBtnManage();
	afx_msg void OnBnClickedBtnLogClear();
	afx_msg void OnBnClickedBtnLogSave();
	afx_msg void OnBnClickedBtnMakeIframe();
	afx_msg void OnBnClickedBtnLogConfig();
	afx_msg void OnNMClickListAllLog(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedBtnPreview();
	afx_msg void OnBnClickedBtnExit();
	afx_msg void OnBnClickedBtnPlay();
	afx_msg void OnBnClickedBtnPictureSnatch();
	afx_msg void OnBnClickedBtnElse();
	afx_msg void OnDblclkListAllLog(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnColumnclickListAllLog(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnColumnclickListAlarmInfo(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBtnTest();
	afx_msg void OnRadioLocalLog();
	afx_msg void OnRadioAlarmInfo();
	afx_msg void OnBtnVca();
	afx_msg void OnMenuAtmFrameFormat();
	afx_msg void OnMenuInquestDvr();
	afx_msg void OnMenuRaidConfig();
	afx_msg void OnMenuVcaVersion();
	afx_msg void OnManuCodespitter();
	afx_msg void OnManuAbility();
	afx_msg void OnMenuSensorCfg();
	afx_msg void OnMenuAlarmhostCfg();
	afx_msg void OnMenuIscsiCfg();
	afx_msg void OnMenuAlarmLogSearch();
	afx_msg void OnMenuPtzScope();
	afx_msg void OnMenuAlarmCamcfg();
	afx_msg void OnMenuSensorAddPreview();
	afx_msg void OnMenuHolidayCfg();
	afx_msg void OnMenuEncodeJoint();
	afx_msg void OnMenuIpcSpecial();
	afx_msg void OnMenuNvrCfg();
	afx_msg void OnMenuVcaChanCtrl();
	afx_msg void OnMenuAudioUpdown();
	afx_msg void OnMenuItsConfig();
	afx_msg void OnButton1();
	afx_msg void OnMenu67DVSCfg();
	afx_msg void OnMenuCertInfo(); 
	afx_msg void OnMenuNetra();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	
// main interface:
	//1.device list;
	//2.preview area;
	//3.operation on single device:parameter configuration
		//remote update/format/reboot
	//4.preview/playback/config
// 5.remote config/playback,hardware decoding, etc
// 6.create as domodle mode with 3 & 4
	//playback

	COleDateTime m_curTime;
	LONG m_pAutoRecTimer;
	LONG m_pChkDevTimer;
	LONG m_pCyclePlayTimer;
	LONG m_pFreeSpaceTimer;
	LONG m_pFileIntervalTimer;
	LONG m_pSysTimer;
	CRITICAL_SECTION m_struLock;
// 	CStdioFile m_fLog;
// 	CStdioFile m_fAlarm;
	FILE * m_fLog;
	FILE * m_fAlarm;
	LONG m_lListenHandle;
////////////////////////////////
//0.operation on main interface
	BOOL RegisterPlayer(BOOL bRegister);
	BOOL IsPlaying(void);
	void CreateNewLogFile(BOOL bCreate);
	void ArrangeOutputs(int iNumber);
	void OnSelchangeComboListType();
	LONG m_iCardChanCount;//decoder card DSP number
	BOOL InitDecodeCard();
	BOOL InitHardDriver();
	void InitGlobalSysInfo();
	void InitMainWin();
	void GetVersionInfor();
	void InitChildWindow(void);
	void DoTestElseFunction();
	BOOL DoSetIPAccessCfg(int iDeviceIndex);
	void RedrawDeviceNode(int iDeviceIndex);
	void RefreshIPDevLocalCfg(int iDeviceIndex);
	BOOL DoGetIPAlarmInCfg(int iDeviceIndex, BOOL bSupportMultiGroup = FALSE, int GroupNO = 0);
	BOOL DoGetIPAlarmOutCfg(int iDeviceIndex, BOOL bSupportMultiGroup = FALSE, int GroupNO = 0);
	void ListRestore();
	void PictureSnatchInSide();//reserve function 
	static void* DoLoginEx(void *lpParam);
	HICON m_hIcon;

	char m_cHardDriver[26];//HD driver name
	int m_iDriverNum;//HD driver number
	int m_iCurRecDriver;//current recording HD drive
	BOOL m_iMainType;	//main interface type
	int m_iCurWndNum;	//screen split mode 1, 4, 9, 16, 25, 36
	int m_iCurWndIndex; //current selected split window index, start from 0

	int m_iTreeWidth;   //device list displaywidth on main interface
	int  m_iRightWidth;    //preview config dialog box size or video control
	int  m_iFunBtnHeight;	//height of main function button area
	int  m_iListLogHeight;	//height of log

	NET_DVR_VIDEOPLATFORM_ALRAMINFO m_struVideoPlatform;
	

	void AddLog(int iDeviceIndex, int iLogType, const char* format, ...);
/////////////////////
//1.device list
	void CreateTree(void);
	HTREEITEM GetAfterItem(HTREEITEM hRoot);
	HTREEITEM GetDeviceItem(HTREEITEM hRoot, int iDeviceIndex);// find relative node according to device index number
	void DeleteItem(int iItemNo, int iType);// delete node info
	void ModifyChanNameInListTree(int iDeviceIndex, int iChanIndex);// modify channel name
	void SetItemImage(HTREEITEM hChanItem,PCHANNEL_INFO pChanInfo);// modify node icon
	BOOL DoLogout(int iDeviceIndex, HTREEITEM hDeviceItem);
	BOOL DoLogin(int iDeviceIndex, HTREEITEM hDeviceItem);
	BOOL DoGetDeviceResoureCfg(int iDeviceIndex, int iGroupNO = 0);
	void DblAllTree();

	void OnMenuDeviceAdd();
	void OnMenuDeviceDelete();
	void OnMenuLogout();
	void OnMenuDeviceInfo();
	void OnMenuChannelInfo();


	// init device list
	void LoadTreeImage(void);
	LRESULT OnWMProcAlarm(WPARAM wParam, LPARAM lParam);
	LRESULT OnWMAddLog(WPARAM wParam, LPARAM lParam);
	LRESULT ChangeChannelItemImage(WPARAM wParam, LPARAM lParam);
	LRESULT ChangeDeviceItemImage(WPARAM wParam, LPARAM lParam);

	int GetCurChanIndex();
	int GetCurChanIndexInTree();
	int GetCurDeviceIndex();

	HTREEITEM GetChanItem(int iDeviceIndex, int iChanIndex);
	HTREEITEM GetDeviceItem(int iDeviceIndex);
	void DblPlayChan(int iDeviceIndex, int iChanIndex,HTREEITEM hChanItem);
	void PlayZeroChan(int iDeviceIndex, int iChanIndex,HTREEITEM hChanItem);
	BOOL StopPlayedChan(int iDeviceIndex, int iChanIndex);
	BOOL m_bDrag;// enable drag	
	int  m_iDragType;// select channel/ device or group on dragging. 
	int m_iDragChanIndex;// dragging channel index
	int m_iDragParentIndex;// dragging device/group Index

	int m_iCurDeviceIndex;
	int m_iCurChanIndex;// channel index of selected node
	HTREEITEM m_hCurDeviceItem;
	HTREEITEM m_hCurChanItem;
///////////////
//2.preview
	// 0.
	//init preview window
	void InitPreviewRect();
	//management of preview dialog box(output),button,static, etc. only display on mainDlg
	void PriviewWinManage();
	void PreviewReferShow(BOOL bShow);
	void FullScreen(BOOL bFullScreen);
	
	// get the node of preview channel
	HTREEITEM GetPlayChanInfo(int iPlayChan, CHANNEL_INFO &pChanInfo);
	CRect m_rectPreviewBG;//preview background
	CRect m_rectRightArea;//preview background

	// 1.main operation
	void DblPlayDevice(int iDeviceIndex, int iStartOutputIndex);
	void StartPlayAll();
	void StopPlayAll();
	void CyclePause();
	void PlayFrontPage();
	void PlayNextPage();
	void CyclePlayAllDevicesLogined();
	void ChangePlayBtnState(void);
		
// 	BYTE m_byStreamHead[MAX_PREVIEWS][40];//save file header on stream callback
// 
// 	BOOL m_bHeadRev[MAX_PREVIEWS];//judge whether fileheader had been saved on stream callback
//////////////////
// 	3.configuration buttons
	void InitConfigAllRefer();
	void ConfigAllHide();

	CDlgConfigAll *m_dlgConfigAll;

	//1.remote config

	CDlgRemoteCfg *m_dlgRemoteCfg;
	CDlgLocalConfig *m_dlgLocalCfg;
	CDlgRemoteIPAccess *m_dlgIPAccess;
	CDlgHardDiskCfg *m_dlgHDConfig;

	CDlgOutputCtrl *m_dlgOutputCtrl;

	//manage
	void OnMenuUpgrade();
	void OnMenuReboot();
	void OnMenuHDFormat();
	void OnMenuPoweroff();

	void OnMenuFortify();
	void OnMenuVoiceTalk();
	void OnMenuJPEGSnatchConfig();
	void OnMenuBroadCast();

	void OnMenuRemoteKey();
	void OnMenuCheckTime();
	void OnMenuDVRRecordStart();
	void OnMenuWorkState();
	void OnMenuLogSearch();

	void OnMenuPreviewSetup();
	void OnMenuMatDecDNSSetup();
	void OnMenuAuxVideoOutSetup();
	void OnMenuSerialTrans();
	void OnMenuDefaultConfig();
	void OnMenuConfigFlash();
	void OnMenuTalkMR();

	void ProcAlarm(WPARAM wParam, LPARAM lParam);
	void ProcAlarmV30(WPARAM wParam, LPARAM lParam);
	void ProcIPCfgAlarm(WPARAM wParam, LPARAM lParam);
	void ProcIPCfgAlarmV31(WPARAM wParam, LPARAM lParam);
    void ProcIPCCfgAlarmV40(WPARAM wParam,LPARAM lParam);
	void ProcRuleAlarm(WPARAM wParam, LPARAM lParam);
    void ProcPdcAlarm(WPARAM wParam, LPARAM lParam);
    void ProcAidAlarm(WPARAM wParam, LPARAM lParam);
    void ProcTpsAlarm(WPARAM wParam, LPARAM lParam);
    void ProcAlarmHostAlarm(WPARAM wParam, LPARAM lParam);
    void ProcSensorAlarm(WPARAM wParam, LPARAM lParam);
    void ProcFaceDetectAlarm(WPARAM wParam, LPARAM lParam);
    void ProcRuleInfoUpload(WPARAM wParam, LPARAM lParam);
    void ProcSensorValueUpload(WPARAM wParam, LPARAM lParam);
    void ProcSwitchAlarm(WPARAM wParam, LPARAM lParam);
    void ProcAlarmHostException(WPARAM wParam, LPARAM lParam);
	void ProcDeviceAlarm(WPARAM wParam, LPARAM lParam);

	void ProcFaceSnapAlarm(WPARAM wParam, LPARAM lParam);
	void ProcFaceSnapMatchAlarm(WPARAM wParam, LPARAM lParam);

	void ProcAlarmHostSatetyCabinState(WPARAM wParam, LPARAM lParam);
	void ProcAlarmHostAlarmoutStatus(WPARAM wParam, LPARAM lParam);

	void ProcAuxAlarm(WPARAM wParam, LPARAM lParam);
	void ProcITSPlateAlarm(WPARAM wParam, LPARAM lParam);
	void ProcITSRoadException(WPARAM wParam, LPARAM lParam);
	void ProcAlarmHostCIDAlarm(WPARAM wParam, LPARAM lParam);
    
	//4.playback
	CDlgPlayBack *m_dlgPlayBack;
	void InitPlayBackRefer();
	void ManualClearAlarm(int iDeviceIndex, int iChanIndex);
	//record
	BOOL IsCurDevMatDec(int iDeviceIndex);
	BOOL IsNeedRebootDevType(void);
	
	BOOL MakeRecDir();
	BOOL IsDiskFull();
	void DeleteClientRecordFile();

	WINDOWPLACEMENT m_struOldWndpl;
	BOOL m_bListLogEnlarge;
	BOOL m_bListAlarmEnlarge;
	void EnlargeList(CListCtrl &list, BOOL &bEnlarge);
	NET_VCA_DEV_ABILITY m_struVcaDevAbility;
	NET_VCA_CTRLCFG m_struVcaCtrlCfg;

    NET_DVR_SENSOR_ALARM m_struSensorAlarm[16]; 
	//{{AFX_DATA(CClientDemoDlg)
	CButton m_btnPlay;
	CButton m_btnRecord;
	CImageList m_imageTreeList;
	CTreeCtrl m_treeDeviceList;
	CComboBox m_comboWinNum;
	CComboBox m_comboNetDelayBufNum;
	CListCtrl m_listAllLog;
	CListCtrl m_listAlarmInfo;
	//}}AFX_DATA
};
