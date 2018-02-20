/**********************************************************
FileName:    DlgTalkMR.cpp
Description: voice media redirect      
Date:        2008/12/18
Note: 		the global Macro definition and structure is in "GeneralDef.h", global variable and function is in "ClientDemo.cpp"
Modification History:      
    <version> <time>         <desc>
    <1.0    > <2008/12/18>       <created>
***********************************************************/

#include "stdafx.h"
#include "DlgTalkMR.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


//#define  RECORD

CDlgTalkMR* g_pDlgTalkMR = NULL;

/*********************************************************
  Function:	fVoiceDataCallBack
  Desc:		call back the audio data from device/从回调中得到设备的音频数据
  Input:	lVoiceComHandle,handle of voice communication;pRecvDataBuffer, buffer for voice data; dwBufSize, voice data length; pUser, User data;
  Output:	none
  Return:	none
**********************************************************/
void CALLBACK fVoiceDataCallBack(LONG lVoiceComHandle, char *pRecvDataBuffer, DWORD dwBufSize, BYTE byAudioFlag, void* pUser)
{
	switch(byAudioFlag)
	{
	case 0:
		TRACE("local audio data\n");
		break;
	case 1:
		g_pDlgTalkMR->PutIntoBuf(pRecvDataBuffer, (int)dwBufSize);
		TRACE("Input data size[%d]\n", dwBufSize);
		break;
	case 2:
		TRACE("audio sending and recving thread exit\n");
		break;
	default:
		break;
	}	
}

/*********************************************************
  Function:	DataFromSoundIn
  Desc:		get local audio data and send to device
  Input:	buffer, local voice data buffer; dwSize, data length; dwOwner, owner data;
  Output:	none
  Return:	none
**********************************************************/
void CALLBACK DataFromSoundIn(char* buffer, DWORD dwSize, DWORD dwOwner)
{
	ASSERT(dwOwner);
	CDlgTalkMR* p = (CDlgTalkMR*) dwOwner;
	p->SendDataToDVR(buffer, dwSize);
}


/////////////////////////////////////////////////////////////////////////////
/*********************************************************
  Function:	CDlgTalkMR
  Desc:		Constructor
  Input:	pParent, parent window pointer
  Output:	none
  Return:	none
**********************************************************/
CDlgTalkMR::CDlgTalkMR(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgTalkMR::IDD, pParent)
{
	m_bWaveDeal = FALSE;
	m_iDeviceIndex = -1;
	//{{AFX_DATA_INIT(CDlgTalkMR)
	//}}AFX_DATA_INIT
	
	m_hFile = NULL;
	m_hExitEvent = NULL;
	m_hHaveRDataRV = NULL;
	
	m_pDecoder = NULL;
	m_pEncoder = NULL;

	m_pG726Enc = NULL;
	m_pG726EncM = NULL;
	m_bReset = TRUE;

	m_bOpenWavOut = FALSE;
	m_bOpenWavIn = FALSE;

	m_dwBufSize = AUDENCSIZE;
	m_dwBufNum = 6;
	//init WAVEFORMATEX
	m_struWaveFormat.cbSize =			sizeof(WAVEFORMATEX);
	m_struWaveFormat.nBlockAlign =		CHANNEL * BITS_PER_SAMPLE / 8;
	m_struWaveFormat.nChannels =		CHANNEL;
	m_struWaveFormat.nSamplesPerSec =	SAMPLES_PER_SECOND;
	m_struWaveFormat.wBitsPerSample =	BITS_PER_SAMPLE;
	m_struWaveFormat.nAvgBytesPerSec =	SAMPLES_PER_SECOND * m_struWaveFormat.nBlockAlign;
	m_struWaveFormat.wFormatTag =		WAVE_FORMAT_PCM;

	m_pRenderBuf = NULL;
	m_nBufNo = 0;
	m_rIndexRV = 0;
	m_ReceiveIndexRV = 0;
	
	m_bOpenPlayThread = FALSE;

	memset(m_wG711AudioTemp,0,AUDENCSIZE);
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDlgTalkMR::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgTalkMR)
	DDX_Control(pDX, IDC_TREE_DEV, m_treeBroadCast);
	DDX_Control(pDX, IDC_BUTTALK, m_btTalk);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDlgTalkMR, CDialog)
	//{{AFX_MSG_MAP(CDlgTalkMR)
	ON_BN_CLICKED(IDC_BUTTALK, OnButtalk)
	ON_BN_CLICKED(IDC_BTN_EXIT, OnBtnExit)
	ON_NOTIFY(NM_CLICK, IDC_TREE_DEV, OnClickTreeDev)
	ON_BN_CLICKED(IDC_BTN_REFRESH, OnBtnRefresh)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
/*********************************************************
  Function:	OnInitDialog
  Desc:		Initialize the dialog
  Input:	none
  Output:	none
  Return:	none
**********************************************************/
BOOL CDlgTalkMR::OnInitDialog()
{
	CDialog::OnInitDialog();
	// TODO: Add extra initialization here
	
#ifdef RECORD 
	CreateWaveFile("record.wav");
#endif
	g_pDlgTalkMR = this;
	GetDlgItem(IDC_BUTTALK)->EnableWindow(TRUE);

	m_hExitEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
	m_hHaveRDataRV = CreateEvent(NULL, TRUE, FALSE, NULL);
	
	//audio buffer
	m_pRenderBuf = (PBYTE)::VirtualAlloc(NULL, 160*40L, MEM_RESERVE|MEM_COMMIT, PAGE_READWRITE);

	//decoder
	m_pDecoder = NET_DVR_InitG722Decoder(BIT_RATE_16000);
	//encoder
	m_pEncoder = NET_DVR_InitG722Encoder();

	//g726
	m_pG726Enc = NET_DVR_InitG726Encoder(&m_pG726EncM);
	LoadTreeImage();
	CreateTree();
	GetDlgItem(IDC_TREE_DEV)->EnableWindow(TRUE);
	return TRUE;  // return TRUE  unless you set the focus to a control
}

/*********************************************************
  Function:	CreateWaveFile
  Desc:		create the file to save wave data
  Input:	sFileName, point to file name;
  Output:	none
  Return:	none
**********************************************************/
BOOL CDlgTalkMR::CreateWaveFile(char* sFileName)
{
	// check if file is already open
	if (m_hFile) 
	{
		return FALSE;	
	}
	
	// open file
	m_hFile = ::mmioOpen(sFileName,NULL, MMIO_CREATE|MMIO_WRITE|MMIO_EXCLUSIVE | MMIO_ALLOCBUF);
	if(m_hFile == NULL) 
	{
		return FALSE;
	}
	
	ZeroMemory(&m_MMCKInfoParent, sizeof(MMCKINFO));
	m_MMCKInfoParent.fccType = mmioFOURCC('W','A','V','E');
	
	MMRESULT mmResult = ::mmioCreateChunk( m_hFile,&m_MMCKInfoParent, MMIO_CREATERIFF);
	
	ZeroMemory(&m_MMCKInfoChild, sizeof(MMCKINFO));
	m_MMCKInfoChild.ckid = mmioFOURCC('f','m','t',' ');
	m_MMCKInfoChild.cksize = sizeof(WAVEFORMATEX) + m_struWaveFormat.cbSize;
	mmResult = ::mmioCreateChunk(m_hFile, &m_MMCKInfoChild, 0);
	mmResult = ::mmioWrite(m_hFile, (char*)&m_struWaveFormat, sizeof(WAVEFORMATEX) + m_struWaveFormat.cbSize); 
	mmResult = ::mmioAscend(m_hFile, &m_MMCKInfoChild, 0);
	m_MMCKInfoChild.ckid = mmioFOURCC('d', 'a', 't', 'a');
	mmResult = ::mmioCreateChunk(m_hFile, &m_MMCKInfoChild, 0);
	
	return TRUE;
}

/*********************************************************
  Function:	OnButtalk
  Desc:		begin get client audio data and send to device/获取本地数据并发送给设备
  Input:	none
  Output:	none
  Return:	none
**********************************************************/
void CDlgTalkMR::OnButtalk() 
{
	if (!m_bWaveDeal)
	{
		m_bReset = TRUE;
		//open wavout
		if (m_SoundOut.OpenSound(m_struWaveFormat, m_dwBufNum, m_dwBufSize, CALLBACK_FUNCTION, 0))
		{	
			g_pMainDlg->AddLog(-1, OPERATION_SUCC_T, "open wavout");
			if (m_SoundOut.PlaySound())
			{
				g_pMainDlg->AddLog(-1, OPERATION_SUCC_T, "play wavout");
				m_bOpenWavOut = TRUE;
				//m_SoundOut.SetVolume(0x7fff7fff);
			}
		}
		else
		{
			g_pMainDlg->AddLog(-1, OPERATION_FAIL_T, "play wavout");
		}
		
		//open wavin
		m_SoundIn.SetSoundInDataCB(DataFromSoundIn, (DWORD)this);
		if (m_SoundIn.Start(&m_struWaveFormat, m_dwBufNum, m_dwBufSize))
		{
			g_pMainDlg->AddLog(-1, OPERATION_SUCC_T, "open wave in");
			m_bOpenWavIn = TRUE;
		}
		else
		{
			g_pMainDlg->AddLog(-1, OPERATION_FAIL_T, "open wave in");
		}
		GetDlgItem(IDC_TREE_DEV)->EnableWindow(TRUE);
		m_btTalk.SetWindowText("Stop Talk MR");
	}
	else
	{
		if (m_hExitEvent)
		{
			SetEvent(m_hExitEvent);
		}
		
		//close wavout
		if (m_bOpenWavOut)
		{
			m_SoundOut.CloseSound();
			m_bOpenWavOut = FALSE;
			g_pMainDlg->AddLog(-1, OPERATION_SUCC_T, "close wave out");
		}

		//close wavin
		if (m_bOpenWavIn)
		{
			m_SoundIn.Stop();
			m_bOpenWavIn = FALSE;
			g_pMainDlg->AddLog(-1, OPERATION_SUCC_T, "close wave in");

#ifdef RECORD
			if(m_hFile)
			{
				::mmioAscend(m_hFile, &m_MMCKInfoChild, 0);
				::mmioAscend(m_hFile, &m_MMCKInfoParent, 0);
				::mmioClose(m_hFile, 0);
				m_hFile = NULL;
			}
#endif
		}

		m_btTalk.SetWindowText("Start Talk MR");
	}	
	m_bWaveDeal = !m_bWaveDeal;
}

/*********************************************************
  Function:	SendDataToDVR
  Desc:		send client audio data to device
  Input:	buf, the audio data buffer;
			dwSize, data length;
  Output:	none
  Return:	TRUE/FALSE
**********************************************************/
BOOL CDlgTalkMR::SendDataToDVR(char *buf, DWORD dwSize)
{
	if (!m_bWaveDeal)
	{
		return FALSE;
	}

	BYTE G711EncBuf[G711_AUDDECSIZE*2] = {0};
	BYTE G711EncBufA[G711_AUDDECSIZE*2] = {0};
	BYTE G726EncBuf[G726_AUDDECSIZE] = {0};
	UINT16 wVoiceBuf[G711_AUDDECSIZE*2] = {0};
	memcpy(m_wG711AudioTemp,buf,AUDENCSIZE);
	AudioBufDownScale((short *)m_wG711AudioTemp, (short *)wVoiceBuf, AUDENCSIZE / 2);
	UINT16 wVoiceBuf1[G711_AUDDECSIZE] = {0};
	UINT16 wVoiceBuf2[G711_AUDDECSIZE] = {0};
	memcpy(wVoiceBuf1,wVoiceBuf,G711_AUDDECSIZE*2);
	memcpy(wVoiceBuf2,wVoiceBuf+G711_AUDDECSIZE,G711_AUDDECSIZE*2);
	NET_DVR_EncodeG711Frame(0,(BYTE*)wVoiceBuf1,G711EncBuf);
	NET_DVR_EncodeG711Frame(0,(BYTE*)wVoiceBuf2,G711EncBuf+G711_AUDDECSIZE);
	NET_DVR_EncodeG711Frame(1,(BYTE*)wVoiceBuf1,G711EncBufA);
	NET_DVR_EncodeG711Frame(1,(BYTE*)wVoiceBuf2,G711EncBufA+G711_AUDDECSIZE);

	if (NULL != m_pG726EncM)
	{
		NET_DVR_EncodeG726Frame(m_pG726EncM, (BYTE*)wVoiceBuf, G726EncBuf, m_bReset);
		m_bReset = 0;
	}
	int i = 0, j=0;;
//	char *pBuf = buf;
//	for (i=0; i<(int)dwSize/2; i++)
//	{
//		*((short *)pBuf) = (short)(*((short *)pBuf) / 2);
//		pBuf += sizeof(short);
//	}
	
#ifdef RECORD 
	if (mmioWrite(m_hFile, buf, dwSize) != dwSize)
	{
		TRACE("mmioWrite failed\n");
	}
#endif

	//encode 
	if (NULL != m_pEncoder)
	{
		NET_DVR_EncodeG722Frame(m_pEncoder, (BYTE*)buf, m_byEncBuf);
		//TRACE("NET_DVR_EncodeG722Frame failed\n");
		//return FALSE;
	}

	//send to dvr
	for (i=0; i<MAX_DEVICES; i++)
	{
		if (g_struDeviceInfo[i].lLoginID >= 0)
		{
			for (j=0; j<g_struDeviceInfo[i].iAudioNum; j++)
			{
				if (g_struDeviceInfo[i].lVoiceCom[j]>=0)
				{
					if (g_struDeviceInfo[i].iAudioEncType == AUDIOTALKTYPE_G722)
					{
						if (!NET_DVR_VoiceComSendData(g_struDeviceInfo[i].lVoiceCom[j], (char*)m_byEncBuf, AUDDECSIZE))
						{
							g_pMainDlg->AddLog(i, OPERATION_FAIL_T, "NET_DVR_VoiceComSendData audioindex[%d]", j);
						}
					}
					else if(g_struDeviceInfo[i].iAudioEncType == AUDIOTALKTYPE_G711_MU)
					{
						if (!NET_DVR_VoiceComSendData(g_struDeviceInfo[i].lVoiceCom[j], (char*)G711EncBuf, G711_AUDDECSIZE))
						{
							g_pMainDlg->AddLog(i, OPERATION_FAIL_T, "NET_DVR_VoiceComSendData audioindex[%d]", j);
						}
						if (!NET_DVR_VoiceComSendData(g_struDeviceInfo[i].lVoiceCom[j], (char*)G711EncBuf+G711_AUDDECSIZE, G711_AUDDECSIZE))
						{
							g_pMainDlg->AddLog(i, OPERATION_FAIL_T, "NET_DVR_VoiceComSendData audioindex[%d]", j);
						}
					}
					else if (g_struDeviceInfo[i].iAudioEncType == AUDIOTALKTYPE_G711_A)
					{
						if (!NET_DVR_VoiceComSendData(g_struDeviceInfo[i].lVoiceCom[j], (char*)G711EncBufA, G711_AUDDECSIZE))
						{
							g_pMainDlg->AddLog(i, OPERATION_FAIL_T, "NET_DVR_VoiceComSendData audioindex[%d]", j);
						}
						if (!NET_DVR_VoiceComSendData(g_struDeviceInfo[i].lVoiceCom[j], (char*)G711EncBufA+G711_AUDDECSIZE, G711_AUDDECSIZE))
						{
							g_pMainDlg->AddLog(i, OPERATION_FAIL_T, "NET_DVR_VoiceComSendData audioindex[%d]", j);
						}
					}
					else if (g_struDeviceInfo[i].iAudioEncType == AUDIOTALKTYPE_G726)
					{
						if (!NET_DVR_VoiceComSendData(g_struDeviceInfo[i].lVoiceCom[j], (char*)G726EncBuf, G726_AUDDECSIZE))
						{
							g_pMainDlg->AddLog(i, OPERATION_FAIL_T, "NET_DVR_VoiceComSendData audioindex[%d]", j);
						}
					}
				//	else
				//	{
					//	g_struDeviceInfo[i].lVoiceCom[j] = -1;
					//	g_pMainDlg->AddLog(i, OPERATION_SUCC_T, "NET_DVR_VoiceComSendData audioindex[%d]", j);
				//	}					
				}
			}
		}
	}
	
	return TRUE;
}


/*********************************************************
  Function:	PutIntoBuf
  Desc:		input the device audio data to buffer for decoding better/对收到的音频数据做缓冲处理
  Input:	lpTemp, voice data buffer;
			Bytes, voice data lenght;
  Output:	none
  Return:	none
**********************************************************/
BOOL CDlgTalkMR::PutIntoBuf(char *lpTemp, int Bytes)
{
	int nTemp = 0;
	int nPacketStart = 0;
	if ((m_ReceiveIndexRV + Bytes) <= AUDIOBUF)
	{
		if (!m_bOpenPlayThread)
		{
			memcpy(m_pRenderBuf+m_ReceiveIndexRV, lpTemp, Bytes);
			m_ReceiveIndexRV += Bytes;
			m_ReceiveIndexRV = m_ReceiveIndexRV % AUDIOBUF;
		}
		else
		{
			if (((m_ReceiveIndexRV + Bytes) >= m_rIndexRV)  
				&& (m_ReceiveIndexRV < m_rIndexRV))
			{   //buffer1 overflow
				TRACE("buffer1 overflow.");
				::SetEvent(m_hHaveRDataRV);
				nPacketStart = (m_rIndexRV - AUDDECSIZE + m_ReceiveIndexRV % AUDDECSIZE);
				if ((nPacketStart + Bytes) <= (DWORD)AUDIOBUF)
				{
					memcpy(m_pRenderBuf + nPacketStart, lpTemp, Bytes);
					m_ReceiveIndexRV = nPacketStart + Bytes;
				}
				else
				{
					nTemp = AUDIOBUF - nPacketStart;
					memcpy(m_pRenderBuf + nPacketStart, lpTemp, nTemp);
					memcpy(m_pRenderBuf, lpTemp + nTemp, Bytes - nTemp);
					m_ReceiveIndexRV = Bytes - nTemp;
				}
			}
			else	
			{
				memcpy(m_pRenderBuf + m_ReceiveIndexRV, lpTemp, Bytes);
				m_ReceiveIndexRV += Bytes;
				m_ReceiveIndexRV = m_ReceiveIndexRV % AUDIOBUF;
			}
		}
	}
	else
	{
		if (m_bOpenPlayThread)
		{
			if ((Bytes >= (m_rIndexRV + AUDIOBUF - m_ReceiveIndexRV))
				|| (m_rIndexRV >= m_ReceiveIndexRV))
			{	//buffer2 overflow
				TRACE("buffer2 overflow");
				::SetEvent(m_hHaveRDataRV);
				if (m_rIndexRV != 0)
				{
					nPacketStart = (m_rIndexRV - AUDDECSIZE + m_ReceiveIndexRV % AUDDECSIZE);
				}
				else
				{
					nPacketStart = (m_rIndexRV + AUDIOBUF - AUDDECSIZE + m_ReceiveIndexRV % AUDDECSIZE);
				}
				if ((nPacketStart + Bytes) <= (DWORD)AUDIOBUF)
				{
					memcpy(m_pRenderBuf + nPacketStart, lpTemp, Bytes);
					m_ReceiveIndexRV = nPacketStart + Bytes;
				}
				else
				{
					nTemp = AUDIOBUF - nPacketStart;
					memcpy(m_pRenderBuf + nPacketStart, lpTemp, nTemp);
					memcpy(m_pRenderBuf, lpTemp + nTemp, Bytes - nTemp);
					m_ReceiveIndexRV = Bytes - nTemp;
				}
			}
			else
			{
				memcpy(m_pRenderBuf + m_ReceiveIndexRV, lpTemp, nTemp = AUDIOBUF - m_ReceiveIndexRV);
				memcpy(m_pRenderBuf, lpTemp + nTemp, Bytes - nTemp);
				m_ReceiveIndexRV = Bytes - nTemp;
			}
		}
	}

	TRACE("number:%d, m_nBufNo:%d\n", (m_ReceiveIndexRV + AUDIOBUF - m_rIndexRV) % (AUDIOBUF), m_nBufNo*AUDDECSIZE);
	if ((((m_ReceiveIndexRV + AUDIOBUF - m_rIndexRV) % (AUDIOBUF)) >= (m_nBufNo * AUDDECSIZE)))
	{
		::SetEvent(m_hHaveRDataRV);
		m_nBufNo = 1;
		if (!m_bOpenPlayThread)
		{
			AfxBeginThread(PlayAudioThread, (LPVOID)this);
			m_bOpenPlayThread = TRUE;
		}
	}

	return TRUE;
}

/*********************************************************
  Function:	CopyAudioData
  Desc:		deal the audio data from device/从接收缓冲区中拷贝数据出来解码
  Input:	lpTemp, data buffer; dwReadLength, data length;
  Output:	none
  Return:	TRUE/FALSE
**********************************************************/
BOOL CDlgTalkMR::CopyAudioData(PBYTE lpTemp, DWORD dwReadLength)
{
	DWORD dwTemp;
	int  dwPacketNumber = 0;
	int itemp = 0;
	__try
	{
		if (m_rIndexRV == m_ReceiveIndexRV)
		{
			dwPacketNumber = 0;
			m_nBufNo = 6;
			::ResetEvent(m_hHaveRDataRV);
			itemp = 0;
			return FALSE;
		}
		else if (m_rIndexRV < m_ReceiveIndexRV)    //read < write
		{
			if (dwReadLength > (DWORD)(m_ReceiveIndexRV-m_rIndexRV))
			{
				dwPacketNumber = 0;
				m_nBufNo = 6;
				::ResetEvent(m_hHaveRDataRV);
				itemp = 0;
				return FALSE;
			}
			else
			{
				CopyMemory(lpTemp, m_pRenderBuf + m_rIndexRV, dwReadLength);
				m_rIndexRV += dwReadLength;
				dwPacketNumber = (m_ReceiveIndexRV - m_rIndexRV) / dwReadLength;
				itemp = 1;
			}
		}
		else	//read > write
		{
			if (dwReadLength > (DWORD)(AUDIOBUF - m_rIndexRV))
			{
				dwTemp = AUDIOBUF - m_rIndexRV;
				if ((dwReadLength-dwTemp) < (DWORD)(m_ReceiveIndexRV + 1))
				{
					CopyMemory(lpTemp, m_pRenderBuf + m_rIndexRV, dwTemp);
					CopyMemory(lpTemp + dwTemp, m_pRenderBuf, dwReadLength - dwTemp);
					m_rIndexRV = dwReadLength - dwTemp;
					dwPacketNumber = (m_ReceiveIndexRV-m_rIndexRV) / dwReadLength;
					itemp = 2;
				}
				else
				{
					dwPacketNumber = 0;
					::ResetEvent(m_hHaveRDataRV);
					m_nBufNo = 6;
					itemp = 3;
					return FALSE;	
				}
			}
			else
			{
				itemp = 4;
				CopyMemory(lpTemp, m_pRenderBuf + m_rIndexRV, dwReadLength);
				m_rIndexRV += dwReadLength;
				dwPacketNumber = (AUDIOBUF + m_ReceiveIndexRV - m_rIndexRV) / dwReadLength;
			}
		}
	}
	__except(EXCEPTION_EXECUTE_HANDLER)
	{
		return FALSE;
	}
	return TRUE;
}

/*********************************************************
  Function:	InputAudioData
  Desc:		input the device audio data to decoder and decode/取出音频数据并解码
  Input:	none
  Output:	none
  Return:	none
**********************************************************/
void CDlgTalkMR::InputAudioData()
{
	HANDLE hWaitEvents[2];
	hWaitEvents[0] = m_hExitEvent;
	hWaitEvents[1] = m_hHaveRDataRV;

	DWORD dwReadLength = AUDDECSIZE;
	BYTE  lpTemp[AUDDECSIZE] = {0};
	DWORD dwWaitResult = 0;
	int i = 0;

	try
	{
		while (1)
		{
			dwWaitResult = WaitForMultipleObjects(2, hWaitEvents, FALSE, INFINITE);
			if (WAIT_OBJECT_0 == dwWaitResult)
			{
				m_bOpenPlayThread = FALSE;
				ResetEvent(m_hExitEvent);
				return ;
			}

			if (CopyAudioData(lpTemp, dwReadLength))
			{
				NET_DVR_DecodeG722Frame(m_pDecoder, (BYTE*)lpTemp, m_byDecBuf);
			//	NET_DVR_DecodeG711Frame(0,(BYTE*)lpTemp,m_byG711DecBuf);			
				for (i=0; i<35; i++)
				{
					if (m_SoundOut.InputData((BYTE*)m_byDecBuf, 0))
				//	if (m_SoundOut.InputData((BYTE*)m_byG711DecBuf, 0))
					{
						break;
					}
					Sleep(1);
				}
			}
		}
	
	}
	catch (...)
	{
		TRACE("InputAudioData exception\n");
		m_bOpenPlayThread = FALSE;
		return ;
	}

	m_bOpenPlayThread = FALSE;
	return ;
}

/*********************************************************
  Function:	PlayAudioThread
  Desc:		play the audio data from device
  Input:	pParam, point to current dialog
  Output:	none
  Return:	0
**********************************************************/
UINT CDlgTalkMR::PlayAudioThread(LPVOID pParam)
{
	ASSERT(pParam);
	CDlgTalkMR * pClient = (CDlgTalkMR *)pParam;
	try
	{
		pClient->InputAudioData();
	}
	catch (...)
	{
		TRACE("Input data exception\n");
		return 1;
	}
	
	return 0;
}

/*********************************************************
  Function:	OnBtnExit
  Desc:		exit the dialog
  Input:	none
  Output:	none
  Return:	none
**********************************************************/
void CDlgTalkMR::OnBtnExit() 
{
	if (m_hExitEvent)
	{
		SetEvent(m_hExitEvent);
	}
	int i=0;
	int j=0;
	for (i=0; i<MAX_DEVICES; i++)
	{
		if (g_struDeviceInfo[i].lLoginID >= 0)
		{
			for (j=0; j<g_struDeviceInfo[i].iAudioNum; j++)
			{
				if (g_struDeviceInfo[i].lVoiceCom[j]>=0)
				{
					if (!NET_DVR_StopVoiceCom(g_struDeviceInfo[i].lVoiceCom[j]))
					{
						g_pMainDlg->AddLog(i, OPERATION_FAIL_T, "NET_DVR_StopVoiceCom audioindex[%d]", j);
					}
					else
					{
						g_struDeviceInfo[i].lVoiceCom[j] = -1;
						g_pMainDlg->AddLog(i, OPERATION_SUCC_T, "NET_DVR_StopVoiceCom audioindex[%d]", j);
					}
					
				}
			}
		}
	}

	if (m_bOpenWavOut)
	{
		m_SoundOut.CloseSound();
		m_bOpenWavOut = FALSE;
	}
	
	if (m_bOpenWavIn)
	{
		m_SoundIn.Stop();
		m_bOpenWavIn = FALSE;

#ifdef RECORD
		if(m_hFile)
		{
			::mmioAscend(m_hFile, &m_MMCKInfoChild, 0);
			::mmioAscend(m_hFile, &m_MMCKInfoParent, 0);
			::mmioClose(m_hFile, 0);
			m_hFile = NULL;
		}
#endif
	}

	if (m_pDecoder)
	{
		NET_DVR_ReleaseG722Decoder(m_pDecoder);
		m_pDecoder = NULL;
	}
	
	if (m_pEncoder)
	{
		NET_DVR_ReleaseG722Encoder(m_pEncoder);
		m_pEncoder = NULL;
	}
	
	if (m_pG726Enc)
	{
		NET_DVR_ReleaseG726Encoder(m_pG726Enc);
		m_pG726Enc = NULL;
		m_pG726EncM = NULL;
	}

	if (m_hExitEvent)
	{
		CloseHandle(m_hExitEvent);	
		m_hExitEvent = NULL;
	}

	if (m_hHaveRDataRV)
	{
		CloseHandle(m_hHaveRDataRV);	
		m_hHaveRDataRV = NULL;
	}
	
	if (m_pRenderBuf)
	{
		::VirtualFree(m_pRenderBuf, 0, MEM_RELEASE);
		m_pRenderBuf = NULL;
	}
	CDialog::OnCancel();
}

/*********************************************************
  Function:	CreateTree
  Desc:		create the voice channels of all devices/创建语音通道树
  Input:	none
  Output:	none
  Return:	none
**********************************************************/
void CDlgTalkMR::CreateTree(void)
{
	char szLan[1024] = {0};
	g_StringLanType(szLan, "所有设备", "All Devices");
	m_treeBroadCast.DeleteAllItems();
	HTREEITEM hRoot = m_treeBroadCast.InsertItem(szLan, TREE_ALL, TREE_ALL,TVI_ROOT);
	CString strTemp =_T("");
	CString strChanTmp = _T("");
	int i = 0;
	int iData =0;
	int j = 0;
	HTREEITEM hDevice = NULL;
	HTREEITEM hChanItem = NULL;
	NET_DVR_WORKSTATE_V30 struWorkState;
	for (i = 0; i < MAX_DEVICES; i++)
	{
		if (g_struDeviceInfo[i].iDeviceChanNum != -1)
		{
			strTemp.Format("%s", g_struDeviceInfo[i].chLocalNodeName);
			if (g_struDeviceInfo[i].lLoginID >= 0)
			{
				hDevice =  m_treeBroadCast.InsertItem(strTemp, DEVICE_LOGIN, DEVICE_LOGIN, hRoot);
				m_treeBroadCast.SetItemData(hDevice, DEVICE_LOGIN*1000 + g_struDeviceInfo[i].iDeviceIndex);

				memset(&struWorkState, 0, sizeof(NET_DVR_WORKSTATE_V30));
				if (!NET_DVR_GetDVRWorkState_V30(g_struDeviceInfo[i].lLoginID, &struWorkState))
				{
					g_pMainDlg->AddLog(i, OPERATION_FAIL_T, "NET_DVR_GetDVRWorkState_V30 before Talk MR");
				}
							
				for (j=0; j<g_struDeviceInfo[i].iAudioNum; j++)
				{
					if (struWorkState.byAudioChanStatus[j] == 1)
					{
						strTemp.Format("audio%d-used", j+1);
						iData = 3*1000 + struWorkState.byAudioChanStatus[j]*100 + j;
					}
					else if (struWorkState.byAudioChanStatus[j] == 0)
					{
						strTemp.Format("audio%d-not used", j+1);
						iData = 3*1000 + struWorkState.byAudioChanStatus[j]*100 + j;
					}
					else if (struWorkState.byAudioChanStatus[j] == 0xff)
					{
						strTemp.Format("audio%d", j+1);
						iData = 3*1000 + j;
					}
					 			
					hChanItem =  m_treeBroadCast.InsertItem(strTemp, 3, 3, hDevice);
					m_treeBroadCast.SetItemData(hChanItem, iData);
					//is talking, set check box
					if (g_struDeviceInfo[i].lVoiceCom[j] >= 0)
					{
						m_treeBroadCast.SetCheck(hChanItem, TRUE);
					}				
				}
				m_treeBroadCast.Expand(hDevice,TVE_EXPAND);
			}
			else
			{
				hDevice =  m_treeBroadCast.InsertItem(strTemp, DEVICE_LOGOUT, DEVICE_LOGOUT,hRoot);
				m_treeBroadCast.SetItemData(hDevice, DEVICE_LOGOUT*1000 + g_struDeviceInfo[i].iDeviceIndex);
			}	
		}
	}
	m_treeBroadCast.Expand(hRoot,TVE_EXPAND);
	m_treeBroadCast.Expand(m_treeBroadCast.GetRootItem(),TVE_EXPAND);
}

/*********************************************************
  Function:	OnClickTreeDev
  Desc:		create the device tree
  Input:	pNMHDR, point the NMHEADER which contains the click information;
			pResult, point to the result;
  Output:	none
  Return:	none
**********************************************************/
void CDlgTalkMR::OnClickTreeDev(NMHDR* pNMHDR, LRESULT* pResult) 
{
	CPoint pt(0,0);
	CRect rc(0,0,0,0);
	GetCursorPos(&pt);
	GetDlgItem(IDC_TREE_DEV)->GetWindowRect(&rc);
	ScreenToClient(&rc);
	ScreenToClient(&pt);
	pt.x = pt.x - rc.left;
	pt.y = pt.y - rc.top;

	UINT uFlag = 0;
	HTREEITEM hSelect= m_treeBroadCast.HitTest(pt, &uFlag);

	if (NULL == hSelect) 
	{
		return;
	}
	
	m_treeBroadCast.SelectItem(hSelect);

	BOOL bCheck = m_treeBroadCast.GetCheck(hSelect);
	bCheck = !bCheck;
	int iDevIndex = 0;
	int iType = m_treeBroadCast.GetItemData(hSelect)/1000;
	if (TREE_ALL_T == iType)
	{
		CheckAllDevState(hSelect, bCheck, uFlag);
	}
	else if (DEVICE_LOGIN == iType)
	{
		CheckAllAudioState(hSelect, bCheck, uFlag);
	}
	else if (3 == iType)
	{
		HTREEITEM hDevItem = m_treeBroadCast.GetParentItem(hSelect);
		int iAudioIndex = m_treeBroadCast.GetItemData(hSelect)%1000;
		iDevIndex = m_treeBroadCast.GetItemData(hDevItem)%1000;

		if ((m_treeBroadCast.GetItemData(hDevItem)%1000)/100 ==1)
		{
			AfxMessageBox("the audio port of device is using!");
		}
		if (uFlag != LVHT_TOLEFT )
		{
			m_treeBroadCast.SetCheck(hSelect, bCheck);
		}
		else
		{
			m_treeBroadCast.SetCheck(hSelect, !bCheck);
		}
		StartMR(iDevIndex, iAudioIndex, bCheck);
	}

	*pResult = 0;
}

/*********************************************************
  Function:	CheckAllDevState
  Desc:		check the status of all devices
  Input:	hRoot, root node;bCheck, status of the check box; uFlag, the click item flag data
  Output:	none
  Return:	none
**********************************************************/
void CDlgTalkMR::CheckAllDevState(HTREEITEM hRoot, BOOL bCheck, int uFlag)
{
	if (uFlag == LVHT_TOLEFT)
	{
		m_treeBroadCast.SetCheck(hRoot, !bCheck);
	}
	else
	{
		m_treeBroadCast.SetCheck(hRoot, bCheck);
	}	

	HTREEITEM hChild = m_treeBroadCast.GetChildItem(hRoot);
	int iDevIndex = 0;
	while (hChild)
	{
		iDevIndex = m_treeBroadCast.GetItemData(hChild)%1000;
		
		if (g_struDeviceInfo[iDevIndex].lLoginID >= 0)
		{
			m_treeBroadCast.SetCheck(hChild, bCheck);
			CheckAllAudioState(hChild, bCheck, 0);
		}

		hChild = m_treeBroadCast.GetNextSiblingItem(hChild);
	}
}

/*********************************************************
  Function:	LoadTreeImage
  Desc:		load the tree image
  Input:	none
  Output:	none
  Return:	none
**********************************************************/
void CDlgTalkMR::LoadTreeImage(void)
{
	CBitmap bmp[4];

	m_TreeImage.Create(16,16,ILC_COLOR32 | ILC_MASK,1,1);
	bmp[TREE_ALL].LoadBitmap(IDB_BITMAP_TREE);
	m_TreeImage.Add(&bmp[TREE_ALL],RGB(1,1,1));
	bmp[DEVICE_LOGOUT].LoadBitmap(IDB_BITMAP_LOGOUT);
	m_TreeImage.Add(&bmp[DEVICE_LOGOUT],RGB(1,1,1));
	bmp[DEVICE_LOGIN].LoadBitmap(IDB_BITMAP_LOGIN);
	m_TreeImage.Add(&bmp[DEVICE_LOGIN],RGB(1,1,1));
	bmp[3].LoadBitmap(IDB_BITMAP_AUDIO);
	m_TreeImage.Add(&bmp[3],RGB(1,1,1));
	
	m_treeBroadCast.SetImageList(&m_TreeImage, LVSIL_NORMAL);
}
 
/*********************************************************
  Function:	StartMR
  Desc:		start to create redirect transmission/开始创建语音转发通道
  Input:	iDeviceIndex,device index;
			iAudiIndex, audio index;
			bCheck, begin transmiting or not;
  Output:	
  Return:	
**********************************************************/
BOOL CDlgTalkMR::StartMR(int iDeviceIndex, int iAudioIndex, BOOL bCheck)
{
	BOOL bRet = FALSE;
	DWORD dwUserData = iDeviceIndex*100+iAudioIndex;
	if (bCheck)
	{
		if (g_struDeviceInfo[iDeviceIndex].lVoiceCom[iAudioIndex] < 0)  
		{
			//g_struDeviceInfo[iDeviceIndex].lVoiceCom[iAudioIndex] = NET_DVR_StartVoiceCom_MR_V30(g_struDeviceInfo[iDeviceIndex].lLoginID, iAudioIndex+1, fVoiceDataCallBack, (void *)&dwUserData);
			g_struDeviceInfo[iDeviceIndex].lVoiceCom[iAudioIndex] = NET_DVR_StartVoiceCom_MR_V30(g_struDeviceInfo[iDeviceIndex].lLoginID, iAudioIndex+1, NULL, (void *)&dwUserData);
			if (g_struDeviceInfo[iDeviceIndex].lVoiceCom[iAudioIndex] >=0 )
			{
				g_pMainDlg->AddLog(iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_StartVoiceCom_MR_V30 audio index[%d]", iAudioIndex);
				bRet = TRUE;

				DWORD dwReturned;
				NET_DVR_COMPRESSION_AUDIO struCodeType;
				memset(&struCodeType,0,sizeof(NET_DVR_COMPRESSION_AUDIO));
				if (!NET_DVR_GetDVRConfig(g_struDeviceInfo[iDeviceIndex].lLoginID, NET_DVR_GET_COMPRESSCFG_AUD, 0, &struCodeType, sizeof(NET_DVR_COMPRESSION_AUDIO), &dwReturned))
				{
					g_pMainDlg->AddLog(iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_COMPRESSCFG_AUD");
				}
				else
				{
					g_struDeviceInfo[iDeviceIndex].iAudioEncType = struCodeType.byAudioEncType;
					g_pMainDlg->AddLog(iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GET_COMPRESSCFG_AUD");
				}
				
			}
			else
			{
				g_pMainDlg->AddLog(iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_StartVoiceCom_MR_V30 audio index[%d]", iAudioIndex);
			}
		}
	}
	else
	{
		//delete device from broadcast list
		if (g_struDeviceInfo[iDeviceIndex].lVoiceCom[iAudioIndex] >= 0)
		{
			bRet = NET_DVR_StopVoiceCom(g_struDeviceInfo[iDeviceIndex].lVoiceCom[iAudioIndex]);	
			if (bRet)
			{
				g_pMainDlg->AddLog(iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_StopVoiceCom");
				g_struDeviceInfo[iDeviceIndex].lVoiceCom[iAudioIndex] = -1;
			}
			else
			{
				g_pMainDlg->AddLog(iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_StopVoiceCom");
			}
		}
	}

	return bRet;
}

/*********************************************************
  Function:	CheckAllDevState
  Desc:		begin to redirect audio data 
  Input:	hDev, device node item; bCheck, add or delete
  Output:	none
  Return:	none
**********************************************************/
void CDlgTalkMR::CheckAllAudioState(HTREEITEM hDev, BOOL bCheck, int uFlag)
{
	if (uFlag == LVHT_TOLEFT)
	{
		m_treeBroadCast.SetCheck(hDev, !bCheck);
	}
	else
	{
		m_treeBroadCast.SetCheck(hDev, bCheck);
	}	
	int iAudioIndex = 0;
	int iDevIndex = m_treeBroadCast.GetItemData(hDev)%1000;
	if (iDevIndex < 0)
	{
		return;
	}
	HTREEITEM hChild = m_treeBroadCast.GetChildItem(hDev);
	while (hChild)
	{
		iAudioIndex = m_treeBroadCast.GetItemData(hChild)%1000;
		m_treeBroadCast.SetCheck(hChild, bCheck);
		g_struDeviceInfo[iDevIndex].bCheckBroadcast[iAudioIndex] = bCheck;
		StartMR(iDevIndex, iAudioIndex, bCheck);
		hChild = m_treeBroadCast.GetNextSiblingItem(hChild);
	}
}

/*********************************************************
  Function:	OnBtnRefresh
  Desc:		refresh the state of the device audio channels
  Input:	none
  Output:	none
  Return:	none
**********************************************************/
void CDlgTalkMR::OnBtnRefresh() 
{
	// TODO: Add your control notification handler code here
	CreateTree();
}

/***************************************************************
Function:     AudioBufDownScale
Description:  音频数据减少一倍
Input:        in:       数据输入
inputLen: 输入数据长度
Output:    out:      数据输出
Returns:      void
****************************************************************/
void CDlgTalkMR::AudioBufDownScale(short const*in, short* out, int inbufLen) const
{
	int i = 0;
	for(i = 0;i < inbufLen / 2;i++)
	{
		out[i] = in[i * 2];
	}
}
