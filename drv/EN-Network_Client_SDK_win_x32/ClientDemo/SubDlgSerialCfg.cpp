/**********************************************************
FileName:    SubDlgSerialCfg.cpp
Description: Serial Port Config      
Date:        2008/05/17
Note: 		<Global>struct, macro refer to GeneralDef.h, global variants and API refer to ClientDemo.cpp   
Modification History:      
    <version> <time>         <desc>
    <1.0    > <2008/05/17>       <created>
***********************************************************/


#include "stdafx.h"
#include "ClientDemo.h"
#include "SubDlgSerialCfg.h"
#include ".\subdlgserialcfg.h"
#include "DlgSerialTrans.h"

CSubDlgSerialCfg *pSerialCFG;

/*********************************************************
  Function:	fSerialDataCallBack
  Desc:		Serial Port Data Callback
  Input:	lSerialHandle�� serial port handle
			pRecvDataBuffer�� buffer of received data
			dwBufSzie�� received data size
			dwUser��relative function set by the baclback��
  Output:	none
  Return:	none
**********************************************************/
void CALLBACK fSerialDataCallBack(LONG lSerialHandle,char *pRecvDataBuffer,DWORD dwBufSize,DWORD dwUser)
{
	char pRecv[2048] = {0}; 
	CString csTemp;
	DWORD i = 0;
	for (i=0;i<dwBufSize && i < 1024;i++)
	{
		if ((pRecvDataBuffer+i) != NULL )
		{
		}
		sprintf(pRecv+i*2, "0x%02x", char(*(pRecvDataBuffer+i)));
	}
		
	sprintf(pRecv, pRecvDataBuffer, dwBufSize);
	csTemp.Format("%s", pRecv);
	g_pMainDlg->AddLog(-1, OPERATION_SUCC_T, "data from serial %s", csTemp);
}
// CSubDlgSerialCfg dialog

/*********************************************************
  Function:	CSubDlgSerialCfg
  Desc:		Constructor
  Input:	
  Output:	
  Return:	
**********************************************************/
IMPLEMENT_DYNAMIC(CSubDlgSerialCfg, CDialog)
CSubDlgSerialCfg::CSubDlgSerialCfg(CWnd* pParent /*=NULL*/)
	: CDialog(CSubDlgSerialCfg::IDD, pParent)
	, m_iDecodeAddr(0)
	, m_iDeviceIndex(-1)
	, m_lLoginID(-1)
	, m_iChanCount(0)
	, m_lStartChannel(0)
	, m_bGet232Serial(FALSE)
	, m_bSetSerial232(FALSE)
	, m_iSel232(0)
{
	memset(&m_struRS232Cfg, 0, sizeof(m_struRS232Cfg));
	memset(&m_stru485DecoderCfg, 0, sizeof(m_stru485DecoderCfg));
}

/*********************************************************
  Function:	~CSubDlgSerialCfg
  Desc:		destructor
  Input:	
  Output:	
  Return:	
**********************************************************/
CSubDlgSerialCfg::~CSubDlgSerialCfg()
{
}

/*********************************************************
Function:	DoDataExchange
Desc:		the map between control and variable
Input:	
Output:	
Return:	
**********************************************************/
void CSubDlgSerialCfg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSubDlgSerialCfg)
	DDX_Control(pDX, IDC_COMBO_232_CHANNEL, m_combo232Chan);
	DDX_Control(pDX, IDC_COMBO_232_BAUD, m_combo232Baud);
	DDX_Control(pDX, IDC_COMBO_232_CHECK_BIT, m_combo232CheckBit);
	DDX_Control(pDX, IDC_COMBO_232_DATA_BIT, m_combo232DataBit);
	DDX_Control(pDX, IDC_COMBO_232_STOP_BIT, m_combo232StopBit);
	DDX_Control(pDX, IDC_COMBO_232_FLOW, m_combo232Flow);
	DDX_Control(pDX, IDC_COMBO_232_OPERATE_MODE, m_combo232OperateMode);
	DDX_Control(pDX, IDC_COMBO_485_CHANNEL, m_comboChannel);
	DDX_Control(pDX, IDC_COMBO_485_BAUD, m_combo485Baud);
	DDX_Control(pDX, IDC_COMBO_485_DATA_BIT, m_combo485DataBit);
	DDX_Control(pDX, IDC_COMBO_485_STOP_BIT, m_combo485StopBit);
	DDX_Control(pDX, IDC_COMBO_485_CHECK_BIT, m_combo485CheckBit);
	DDX_Control(pDX, IDC_COMBO_485_FLOW, m_combo485Flow);
	DDX_Control(pDX, IDC_COMBO_DECODE_TYPE, m_combo485DecodeType);
	DDX_Text(pDX, IDC_EDIT_DECODE_ADDRESS, m_iDecodeAddr);
	DDX_Control(pDX, IDC_COMBO_485_COPY_CFG, m_combo485CfgCopy);
	//}}AFX_DATA_MAP
}


/*********************************************************
Function:	BEGIN_MESSAGE_MAP
Desc:		the map between control and function
Input:	
Output:	
Return:	
**********************************************************/
BEGIN_MESSAGE_MAP(CSubDlgSerialCfg, CDialog)
	//{{AFX_MSG_MAP(CSubDlgSerialCfg)	
	ON_CBN_SELCHANGE(IDC_COMBO_232_OPERATE_MODE, OnCbnSelchangeCombo232OperateMode)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BTN_TRANSPARENT_TRANSPORT, OnBnClickedBtnTransparentTransport)
	ON_BN_CLICKED(IDC_BTN_PPP_SETUP, OnBnClickedBtnPppSetup)
	ON_CBN_SELCHANGE(IDC_COMBO_485_CHANNEL, OnCbnSelchangeCombo485Channel)
	ON_BN_CLICKED(IDC_BTN_485_OK, OnBnClickedBtn485Ok)
	ON_BN_CLICKED(IDC_BTN_485_COPY, OnBnClickedBtn485Copy)
	ON_BN_CLICKED(ID_BTN_SERIAL_232_OK, OnBnClickedBtn232Ok)
	ON_CBN_SELCHANGE(IDC_COMBO_232_CHANNEL, OnSelchangeCombo232Channel)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// CSubDlgSerialCfg message handlers

/*********************************************************
Function:	OnInitDialog
Desc:		Initialize the dialog
Input:	
Output:	
Return:	
**********************************************************/
BOOL CSubDlgSerialCfg::OnInitDialog()
{
	CDialog::OnInitDialog();

	CRect rc(0, 0, 0, 0);
	GetParent()->GetClientRect(&rc);
	((CTabCtrl*)GetParent())->AdjustRect(FALSE, &rc);
	MoveWindow(&rc);
	return TRUE;
}

/*********************************************************
  Function:	CheckInitParam
  Desc:		
  Input:	
  Output:	
  Return:	
**********************************************************/
BOOL CSubDlgSerialCfg::CheckInitParam()
{
	DWORD dwReturned = 0;
	int i =0;
	int iDeviceIndex = g_pMainDlg->GetCurDeviceIndex();
	if (iDeviceIndex == -1)
	{
		return FALSE;
	}

// 	if (m_iDeviceIndex == iDeviceIndex)
// 	{
// 		return TRUE;
// 	}
// 	else
	{
		m_iDeviceIndex = iDeviceIndex;
		m_lLoginID = g_struDeviceInfo[m_iDeviceIndex].lLoginID;

		m_lStartChannel = g_struDeviceInfo[m_iDeviceIndex].iStartChan;
		m_iChanCount = g_struDeviceInfo[m_iDeviceIndex].iDeviceChanNum;
	
	}
	m_combo232Baud.SetCurSel(-1);
	m_combo232CheckBit.SetCurSel(-1);
	m_combo232DataBit.SetCurSel(-1);
	m_combo232StopBit.SetCurSel(-1);
	m_combo232Flow.SetCurSel(-1);
	m_combo232OperateMode.SetCurSel(-1);
	
	m_comboChannel.SetCurSel(-1);
	m_combo485Baud.SetCurSel(-1);
	m_combo485DataBit.SetCurSel(-1);
	m_combo485StopBit.SetCurSel(-1);
	m_combo485CheckBit.SetCurSel(-1);
	m_combo485Flow.SetCurSel(-1);
	m_combo485DecodeType.SetCurSel(-1);
	m_iDecodeAddr = 0;
	m_combo232Chan.ResetContent();
	m_combo485CfgCopy.ResetContent();
	m_comboChannel.ResetContent();	
	if (m_lLoginID < 0)
	{
		return FALSE;
	}
	CString sTemp;

	int iChanShow = 0;
	int iCopyIndex = 0;
	char szPtz[DESC_LEN+1] = {0};
	m_iCurChanIndex = g_struDeviceInfo[m_iDeviceIndex].lFirstEnableChanIndex;
	m_iSel232 = 0;
	m_lSerial = -1;
	m_iCopyChanIndex = -1;

// 	if (g_pMainDlg->IsCurDevMatDec(m_iDeviceIndex))
// 	{
// 		m_comboChannel.EnableWindow(FALSE);
// 		m_combo485DecodeType.EnableWindow(FALSE);
// 		GetDlgItem(IDC_EDIT_DECODE_ADDRESS)->EnableWindow(FALSE);
// 	}
// 	else
	{
		m_comboChannel.EnableWindow(TRUE);
		m_combo485DecodeType.EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_DECODE_ADDRESS)->EnableWindow(TRUE);
	}
	char szLan[128] = {0};
	g_StringLanType(szLan, "ȫ��ͨ��", "All Channels");
	m_combo485CfgCopy.AddString(szLan);
	m_combo485CfgCopy.SetItemData(iCopyIndex, -1);
	for (i=0; i<MAX_SERIAL_PORT; i++)
	{
		sTemp.Format("SerialPort%d", i+1);
		m_combo232Chan.AddString(sTemp);
	}	
	m_combo232Chan.SetCurSel(m_iSel232);

	m_bSetSerial232 = FALSE;
	m_bGet232Serial = FALSE;
	memset(&m_struPtzCfg, 0, sizeof(NET_DVR_PTZCFG));
	if (!NET_DVR_GetPTZProtocol(m_lLoginID, &m_struPtzCfg))
	{		
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GetPTZProtocol");
	}
	else
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GetPTZProtocol");
		m_combo485DecodeType.ResetContent();
		for (i = 0; i < (int)m_struPtzCfg.dwPtzNum; i++)
		{
			memset(szPtz, 0, DESC_LEN);
			memcpy(szPtz, m_struPtzCfg.struPtz[i].byDescribe, DESC_LEN);
			m_combo485DecodeType.AddString(szPtz);
			m_combo485DecodeType.SetItemData(i, m_struPtzCfg.struPtz[i].dwType);
		}
	}
	memset(&m_struRS232Cfg, 0, sizeof(NET_DVR_RS232CFG_V30));//
	if (!NET_DVR_GetDVRConfig(m_lLoginID, NET_DVR_GET_RS232CFG_V30, 0, &m_struRS232Cfg, sizeof(NET_DVR_RS232CFG_V30), &dwReturned))
	{
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GET_RS232CFG_V30");
		g_StringLanType(szLan, "��ȡ232���ڲ�������", "Get Rs232 parameter failed");
		AfxMessageBox(szLan);	
		//return FALSE;
	}
	else
	{
		m_bGet232Serial = TRUE;
	}

	for (i=0; i<MAX_CHANNUM_V30; i++)//PTZ parameter settings only valid for analog channels
	{
		m_bGet485Serial[i] = FALSE;
		m_bSet485Serial[i] = FALSE;
		m_i485ChannelNO[i] = -1;
		
		if (g_struDeviceInfo[m_iDeviceIndex].struChanInfo[i].bEnable)
		{
			iChanShow = g_struDeviceInfo[m_iDeviceIndex].struChanInfo[i].iChannelNO;
			sTemp.Format("%s", g_struDeviceInfo[m_iDeviceIndex].struChanInfo[i].chChanName);

			m_i485ChannelNO[i] = iChanShow;
			m_comboChannel.AddString(sTemp);
			m_comboChannel.SetItemData(iCopyIndex, i);

			iCopyIndex++;
			m_combo485CfgCopy.AddString(sTemp);
			m_combo485CfgCopy.SetItemData(iCopyIndex, i);
			if (!NET_DVR_GetDVRConfig(m_lLoginID, NET_DVR_GET_DECODERCFG_V30, iChanShow, &m_stru485DecoderCfg[i], sizeof(NET_DVR_DECODERCFG_V30), &dwReturned))
			{		
				g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "Serial 485[%d] NET_DVR_GET_DECODERCFG_V30", iChanShow);
				g_StringLanType(szLan, "��ȡ485���ڲ�������", "Get Rs485 parameter failed");
				AfxMessageBox(szLan);	
				//return FALSE;
			}
			else
			{
				m_bGet485Serial[i] = TRUE;
			}
		}
	}
	return TRUE;
}

/*********************************************************
Function:	CurCfgUpdate
Desc:		Update device parameters and refresh control settings
Input:	
Output:	
Return:	
**********************************************************/
void CSubDlgSerialCfg::CurCfgUpdate()
{
	if (!CheckInitParam())
	{
		m_iDeviceIndex = -1;
		EnableWindow(FALSE);
		UpdateData(FALSE);
		return;
	}
	EnableWindow(TRUE);

	if (m_bGet232Serial)
	{
		m_combo232Baud.SetCurSel(m_struRS232Cfg.struRs232[m_iSel232].dwBaudRate);
		m_combo232DataBit.SetCurSel(m_struRS232Cfg.struRs232[m_iSel232].byDataBit);
		m_combo232StopBit.SetCurSel(m_struRS232Cfg.struRs232[m_iSel232].byStopBit);
		m_combo232CheckBit.SetCurSel(m_struRS232Cfg.struRs232[m_iSel232].byParity);
		m_combo232Flow.SetCurSel(m_struRS232Cfg.struRs232[m_iSel232].byFlowcontrol);
		m_combo232OperateMode.SetCurSel(m_struRS232Cfg.struRs232[m_iSel232].dwWorkMode);
		if (m_struRS232Cfg.struRs232[m_iSel232].dwWorkMode == 0)//narrow band work mode for port 1
		{
			GetDlgItem(IDC_BTN_PPP_SETUP)->EnableWindow(TRUE);
		}
		else//control or transparentr channel mode
		{
			GetDlgItem(IDC_BTN_PPP_SETUP)->EnableWindow(FALSE);
		}
		GetDlgItem(ID_BTN_SERIAL_232_OK)->EnableWindow(TRUE);
	}

	if (m_bGet485Serial[m_iCurChanIndex])
	{
		m_iChanShowNum = g_struDeviceInfo[m_iDeviceIndex].struChanInfo[m_iCurChanIndex].iChannelNO;
		m_combo485Baud.SetCurSel(m_stru485DecoderCfg[m_iCurChanIndex].dwBaudRate);
		m_combo485DataBit.SetCurSel(m_stru485DecoderCfg[m_iCurChanIndex].byDataBit);
		m_combo485StopBit.SetCurSel(m_stru485DecoderCfg[m_iCurChanIndex].byStopBit);
		m_combo485CheckBit.SetCurSel(m_stru485DecoderCfg[m_iCurChanIndex].byParity);
		m_combo485Flow.SetCurSel(m_stru485DecoderCfg[m_iCurChanIndex].byFlowcontrol);
		int i = 0;
		for (i=0; i<m_struPtzCfg.dwPtzNum; i++)
		{
			if (m_stru485DecoderCfg[m_iCurChanIndex].wDecoderType == m_struPtzCfg.struPtz[i].dwType)
			{
				m_combo485DecodeType.SetCurSel(i);
				break;
			}
		}
		//m_combo485DecodeType.SetCurSel(m_stru485DecoderCfg[m_iCurChanIndex].wDecoderType);
		m_iDecodeAddr = (BYTE)m_stru485DecoderCfg[m_iCurChanIndex].wDecoderAddress;
		GetDlgItem(IDC_BTN_485_COPY)->EnableWindow(TRUE);
		GetDlgItem(IDC_BTN_485_OK)->EnableWindow(TRUE);	
	}	
	
	m_comboChannel.SetCurSel(0);
	m_combo485CfgCopy.SetCurSel(0);
	UpdateData(FALSE);
}

/*********************************************************
Function:	CfgSetup
Desc:		Set serial port configuration
Input:	
Output:	
Return:	TRUE,setting succeeds;FALSE,setting failed;
**********************************************************/
BOOL CSubDlgSerialCfg::CfgSetup()
{
	CString sTemp;
	int i = 0;
	int iChanShow = 0;
	char szLan[128] = {0};

	if (m_bSetSerial232)
	{
		if (!NET_DVR_SetDVRConfig(m_lLoginID, NET_DVR_SET_RS232CFG_V30, 0, &(m_struRS232Cfg), sizeof(NET_DVR_RS232CFG)))
		{
			g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_RS232CFG_V30"); 
			g_StringLanType(szLan, "��������ʧ��", "Save parameter failed");
			AfxMessageBox(szLan);
			return FALSE;
		}
		m_bSetSerial232 = FALSE;
	}
	
	for (i=0; i<MAX_CHANNUM_V30; i++)
	{
		if (m_bSet485Serial[i] && g_struDeviceInfo[m_iDeviceIndex].struChanInfo[i].bEnable)
		{
			iChanShow = m_i485ChannelNO[i];
			if (!NET_DVR_SetDVRConfig(m_lLoginID, NET_DVR_SET_DECODERCFG_V30, iChanShow,&(m_stru485DecoderCfg[i]), sizeof(NET_DVR_DECODERCFG_V30)))
			{		
				g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_SET_DECODERCFG_V30 %s", g_struDeviceInfo[m_iDeviceIndex].struChanInfo[i].chChanName); 
				g_StringLanType(szLan, "��������ʧ��", "Save parameter failed");
				AfxMessageBox(szLan);	
				return FALSE;
			}
			m_bSet485Serial[i] = FALSE;
		}
	}
	return TRUE;
}

/*********************************************************
  Function:	OnCbnSelchangeCombo485Channel
  Desc:		update 485 serial port parameters
  Input:	
  Output:	
  Return:	
**********************************************************/
void CSubDlgSerialCfg::OnCbnSelchangeCombo485Channel()
{
	UpdateData(TRUE);
	int iSel = m_comboChannel.GetCurSel();
	m_iCurChanIndex = m_comboChannel.GetItemData(iSel);	
	m_iChanShowNum = g_struDeviceInfo[m_iDeviceIndex].struChanInfo[m_iCurChanIndex].iChannelNO;
	
	m_combo485Baud.SetCurSel(m_stru485DecoderCfg[m_iCurChanIndex].dwBaudRate);
	m_combo485DataBit.SetCurSel(m_stru485DecoderCfg[m_iCurChanIndex].byDataBit);
	m_combo485StopBit.SetCurSel(m_stru485DecoderCfg[m_iCurChanIndex].byStopBit);
	m_combo485CheckBit.SetCurSel(m_stru485DecoderCfg[m_iCurChanIndex].byParity);
	m_combo485Flow.SetCurSel(m_stru485DecoderCfg[m_iCurChanIndex].byFlowcontrol);
	int i = 0;
	for (i=0; i<m_struPtzCfg.dwPtzNum; i++)
	{
		if (m_stru485DecoderCfg[m_iCurChanIndex].wDecoderType == m_struPtzCfg.struPtz[i].dwType)
		{
			m_combo485DecodeType.SetCurSel(i);
			break;
		}
	}
//	m_combo485DecodeType.SetCurSel(m_stru485DecoderCfg[m_iCurChanIndex].wDecoderType);
	m_iDecodeAddr = (BYTE)m_stru485DecoderCfg[m_iCurChanIndex].wDecoderAddress;
	UpdateData(FALSE);
}

/*********************************************************
  Function:	OnBnClickedBtn485Ok
  Desc:		confirm 485serial port configuration
  Input:	
  Output:	
  Return:	
**********************************************************/
void CSubDlgSerialCfg::OnBnClickedBtn485Ok()
{
	UpdateData(TRUE);
	m_iCurChanIndex = m_comboChannel.GetItemData(m_comboChannel.GetCurSel());
	if (m_bGet485Serial[m_iCurChanIndex])
	{		
		m_stru485DecoderCfg[m_iCurChanIndex].dwBaudRate = m_combo485Baud.GetCurSel();
		m_stru485DecoderCfg[m_iCurChanIndex].byDataBit = (BYTE)m_combo485DataBit.GetCurSel();
		m_stru485DecoderCfg[m_iCurChanIndex].byStopBit = (BYTE)m_combo485StopBit.GetCurSel();
		m_stru485DecoderCfg[m_iCurChanIndex].byParity = (BYTE)m_combo485CheckBit.GetCurSel();
		m_stru485DecoderCfg[m_iCurChanIndex].byFlowcontrol = (BYTE)m_combo485Flow.GetCurSel();
	//	m_stru485DecoderCfg[m_iCurChanIndex].wDecoderType = (WORD)m_combo485DecodeType.GetCurSel();
		m_stru485DecoderCfg[m_iCurChanIndex].wDecoderType = (WORD)m_combo485DecodeType.GetItemData(m_combo485DecodeType.GetCurSel());
		m_stru485DecoderCfg[m_iCurChanIndex].wDecoderAddress = (WORD)m_iDecodeAddr;
		g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "save CurChanIndex%d", m_iCurChanIndex);
		m_bSet485Serial[m_iCurChanIndex] = TRUE;
	}
}

/*********************************************************
  Function:	OnBnClickedBtn485Copy
  Desc:		copy 485portconfigurtaion to other channels
  Input:	
  Output:	
  Return:	
**********************************************************/
void CSubDlgSerialCfg::OnBnClickedBtn485Copy()
{
	UpdateData(TRUE);
	int iSel = m_combo485CfgCopy.GetCurSel();
	m_iCopyChanIndex = m_combo485CfgCopy.GetItemData(iSel);
	if (m_iCopyChanIndex == m_iCurChanIndex)
	{
		return;
	}
	if (m_iCopyChanIndex == -1)
	{
		for (int i=0; i<m_iChanCount; i++)
		{
			if (i == m_iCurChanIndex)
			{
				continue;
			}
			if (m_bGet485Serial[i])
			{		
				m_stru485DecoderCfg[i].dwBaudRate = m_combo485Baud.GetCurSel();
				m_stru485DecoderCfg[i].byDataBit = (BYTE)m_combo485DataBit.GetCurSel();
				m_stru485DecoderCfg[i].byStopBit = (BYTE)m_combo485StopBit.GetCurSel();
				m_stru485DecoderCfg[i].byParity = (BYTE)m_combo485CheckBit.GetCurSel();
				m_stru485DecoderCfg[i].byFlowcontrol = (BYTE)m_combo485Flow.GetCurSel();
				m_stru485DecoderCfg[i].wDecoderType = (WORD)m_combo485DecodeType.GetItemData(m_combo485DecodeType.GetCurSel());
				m_stru485DecoderCfg[i].wDecoderAddress = (WORD)m_iDecodeAddr;
				m_bSet485Serial[i] = TRUE;
			}
		}		
	}
	else
	{
		if (m_bGet485Serial[m_iCopyChanIndex] && g_struDeviceInfo[m_iDeviceIndex].struChanInfo[m_iCopyChanIndex].bEnable)
		{		
			m_stru485DecoderCfg[m_iCopyChanIndex].dwBaudRate = m_combo485Baud.GetCurSel();
			m_stru485DecoderCfg[m_iCopyChanIndex].byDataBit = (BYTE)m_combo485DataBit.GetCurSel();
			m_stru485DecoderCfg[m_iCopyChanIndex].byStopBit = (BYTE)m_combo485StopBit.GetCurSel();
			m_stru485DecoderCfg[m_iCopyChanIndex].byParity = (BYTE)m_combo485CheckBit.GetCurSel();
			m_stru485DecoderCfg[m_iCopyChanIndex].byFlowcontrol = (BYTE)m_combo485Flow.GetCurSel();
			m_stru485DecoderCfg[m_iCopyChanIndex].wDecoderType = (WORD)m_combo485DecodeType.GetItemData(m_combo485DecodeType.GetCurSel());
			m_stru485DecoderCfg[m_iCopyChanIndex].wDecoderAddress = (WORD)m_iDecodeAddr;
			m_bSet485Serial[m_iCopyChanIndex] = TRUE;
		}
	}
}

/*********************************************************
  Function:	OnBnClickedBtn232Ok
  Desc:		confirm 232 configuration
  Input:	
  Output:	
  Return:	
**********************************************************/
void CSubDlgSerialCfg::OnBnClickedBtn232Ok()
{
	UpdateData(TRUE);

	if (m_bGet232Serial)
	{		
		m_struRS232Cfg.struRs232[m_iSel232].dwBaudRate = m_combo232Baud.GetCurSel();
		m_struRS232Cfg.struRs232[m_iSel232].byDataBit = (BYTE)m_combo232DataBit.GetCurSel();
		m_struRS232Cfg.struRs232[m_iSel232].byStopBit = (BYTE)m_combo232StopBit.GetCurSel();
		m_struRS232Cfg.struRs232[m_iSel232].byParity = (BYTE)m_combo232CheckBit.GetCurSel();
		m_struRS232Cfg.struRs232[m_iSel232].byFlowcontrol = (BYTE)m_combo232Flow.GetCurSel();
		m_struRS232Cfg.struRs232[m_iSel232].dwWorkMode = m_combo232OperateMode.GetCurSel();
	}
	m_bSetSerial232 = TRUE;
}

/*********************************************************
  Function:	OnCbnSelchangeCombo232OperateMode
  Desc:		set 232 port working mode
  Input:	
  Output:	
  Return:	
**********************************************************/
void CSubDlgSerialCfg::OnCbnSelchangeCombo232OperateMode()
{
	UpdateData(TRUE);
	int iOperateSel = 0;
	iOperateSel = m_combo232OperateMode.GetCurSel();
	if (iOperateSel == 0 && m_iSel232 == 0)
	{
		GetDlgItem(IDC_BTN_PPP_SETUP)->EnableWindow(TRUE);
	}
	else
	{
		GetDlgItem(IDC_BTN_PPP_SETUP)->EnableWindow(FALSE);
	}
	g_bMustReboot = g_pMainDlg->IsNeedRebootDevType();//modification on 232 port do not require a device reboot
}



/*********************************************************
  Function:	OnBnClickedBtnTransparentTransport
  Desc:		transparent channel transmission
  Input:	
  Output:	
  Return:	
**********************************************************/
void CSubDlgSerialCfg::OnBnClickedBtnTransparentTransport()
{
	UpdateData(TRUE);

	CTransparentTrans dlg;
	dlg.m_lServerID = m_lLoginID;
	dlg.m_iDeviceIndex = m_iDeviceIndex;
	dlg.DoModal();
}

/*********************************************************
  Function:	OnBnClickedBtnPppSetup
  Desc:		PPP configuration
  Input:	none
  Output:	none
  Return:	none	
**********************************************************/
void CSubDlgSerialCfg::OnBnClickedBtnPppSetup()
{
	CDlgPPPCfg dlg;
	memcpy(&(dlg.m_struPPPConfig), &(m_struRS232Cfg.struPPPConfig), sizeof(NET_DVR_PPPCFG_V30));
	if (dlg.DoModal() == IDOK)
	{
		memcpy(&(m_struRS232Cfg.struPPPConfig), &(dlg.m_struPPPConfig), sizeof(NET_DVR_PPPCFG_V30));
	}	
}

/*********************************************************
  Function:	OnSelchangeCombo232Channel
  Desc:		change the Index of Serial 232
  Input:	none
  Output:	none
  Return:	none
**********************************************************/
void CSubDlgSerialCfg::OnSelchangeCombo232Channel() 
{	
	UpdateData(TRUE);
	m_iSel232 = m_combo232Chan.GetCurSel();
	m_combo232Baud.SetCurSel(m_struRS232Cfg.struRs232[m_iSel232].dwBaudRate);
	m_combo232DataBit.SetCurSel(m_struRS232Cfg.struRs232[m_iSel232].byDataBit);
	m_combo232StopBit.SetCurSel(m_struRS232Cfg.struRs232[m_iSel232].byStopBit);
	m_combo232CheckBit.SetCurSel(m_struRS232Cfg.struRs232[m_iSel232].byParity);
	m_combo232Flow.SetCurSel(m_struRS232Cfg.struRs232[m_iSel232].byFlowcontrol);
	m_combo232OperateMode.SetCurSel(m_struRS232Cfg.struRs232[m_iSel232].dwWorkMode);
	if (m_struRS232Cfg.struRs232[m_iSel232].dwWorkMode == 0)
	{
		GetDlgItem(IDC_BTN_PPP_SETUP)->EnableWindow(TRUE);
	}
	else
	{
		GetDlgItem(IDC_BTN_PPP_SETUP)->EnableWindow(FALSE);
	}
	UpdateData(FALSE);
}
