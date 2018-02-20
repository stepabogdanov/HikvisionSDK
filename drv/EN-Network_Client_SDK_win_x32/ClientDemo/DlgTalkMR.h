// DlgTalkMR.h : header file
//

#if !defined(AFX_DLGTALKMR_H__7A5D50DD_8FF3_485D_AA16_E864261314DC__INCLUDED_)
#define AFX_DLGTALKMR_H__7A5D50DD_8FF3_485D_AA16_E864261314DC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CDlgTalkMRdialog

#include "ClientDemo.h"
#include "soundin.h"
#include "wavesound.h"

#define AUDENCSIZE			1280
#define AUDDECSIZE			80
#define G711_AUDDECSIZE		160

#define G726_AUDENCSIZE     640
#define G726_AUDDECSIZE		80 

#define BITS_PER_SAMPLE		16
#define CHANNEL				1
#define SAMPLES_PER_SECOND	16000

#define BIT_RATE_16000		16000
#define AUDIOBUF			(80*40L)

class CDlgTalkMR : public CDialog
{
// Construction
public:
	CDlgTalkMR(CWnd* pParent = NULL);	// standard constructor

	BOOL SendDataToDVR(char *buf, DWORD dwSize);	
	BOOL PutIntoBuf(char *buf, int dwSize);
	BOOL CopyAudioData(PBYTE lpTemp, DWORD dwReadLength);
	void InputAudioData(void);
	BOOL CreateWaveFile(char* sFileName);
	int m_iDeviceIndex;
	static UINT PlayAudioThread(LPVOID pParam);
	BOOL m_bWaveDeal;
	void CreateTree(void);

	CImageList m_TreeImage;
	
	// select/ do not select all the devices 
	void CheckAllDevState(HTREEITEM hRoot, BOOL bCheck, int uFlag);

	void CheckAllAudioState(HTREEITEM hDev, BOOL bCheck, int uFlag);
	void LoadTreeImage(void);
	BOOL StartMR(int iDeviceIndex, int iAudioIndex, BOOL bCheck);

// Dialog Data
	//{{AFX_DATA(CDlgTalkMR)
	enum { IDD = IDD_DLG_TALK_MR };
	CTreeCtrl	m_treeBroadCast;
	CComboBox	m_combVoice;
	CButton	m_btTalk;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgTalkMR)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	WAVEFORMATEX m_struWaveFormat;	
	CWaveSound	m_SoundOut;
	CSoundIn	m_SoundIn;
	BOOL m_bOpenWavOut;
	BOOL m_bOpenWavIn;

	HMMIO		m_hFile;
	MMCKINFO	m_MMCKInfoData;
	MMCKINFO	m_MMCKInfoParent;
	MMCKINFO	m_MMCKInfoChild;
	
	LPBYTE  m_pRenderBuf;		//buffer
	int     m_rIndexRV;			//data that has already been read
	int     m_ReceiveIndexRV;		//received data for m_pRenderBuf
	int     m_nBufNo;			
	BOOL	m_bOpenPlayThread;
	
	void* m_pDecoder;//g722 decoder
	void* m_pEncoder;//g722 encoder
	void* m_pG726Enc;//g726±àÂë¾ä±ú
	void* m_pG726EncM;//g726±àÂëÄ£¿é¾ä±ú
	BOOL m_bReset;//g726Ê×Ö¡ÖØÖÃ
	
	DWORD m_dwBufSize;
	DWORD m_dwBufNum;

	BYTE m_byG711DecBuf[G711_AUDDECSIZE*2];
	BYTE m_byDecBuf[AUDENCSIZE];
	BYTE m_byEncBuf[AUDDECSIZE];
	BYTE m_byEncBuf711[G711_AUDDECSIZE];
	UINT16 m_wG711AudioTemp[AUDENCSIZE/2];
	
	HANDLE m_hExitEvent;
	HANDLE m_hHaveRDataRV;

	// Generated message map functions
	//{{AFX_MSG(CDlgTalkMR)
	virtual BOOL OnInitDialog();
	afx_msg void OnButtalk();
	afx_msg void OnBtnExit();
	afx_msg void OnClickTreeDev(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBtnRefresh();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	void AudioBufDownScale(short const*in, short* out, int inbufLen) const;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGTALKMR_H__7A5D50DD_8FF3_485D_AA16_E864261314DC__INCLUDED_)
