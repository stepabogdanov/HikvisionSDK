// MatDecoderStatus.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "MatDecoderStatus.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#define DEVICESTATUS_TIMER	WM_USER + 1
/////////////////////////////////////////////////////////////////////////////
// CMatDecoderStatus dialog

BYTE g_MatrixDecAudioStatus[32] = {0xff};//0 - not used;1 - used; 0xff - not support

CMatDecoderStatus::CMatDecoderStatus(CWnd* pParent /*=NULL*/)
	: CDialog(CMatDecoderStatus::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMatDecoderStatus)
	//}}AFX_DATA_INIT
}


void CMatDecoderStatus::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMatDecoderStatus)
	DDX_Control(pDX, IDC_COMBOAUDIO2, m_Audio2Ctrl);
	DDX_Control(pDX, IDC_COMBOAUDIO1, m_Audio1Ctrl);
	DDX_Control(pDX, IDC_LIST_SUBWND, m_SubWndList);
	//DDX_Control(pDX, IDC_COMBOAUDIO, m_comboAudio);
	DDX_Control(pDX, IDC_COMBO_SUBWND, m_SubWndCtrl);
	DDX_Control(pDX, IDC_LIST_ALARMSTATUS, m_AlarmList);
	DDX_Control(pDX, IDC_LIST_DISPCHANSTATUS, m_DispList);
	DDX_Control(pDX, IDD_DECODECHANSTATUS, m_DecList);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMatDecoderStatus, CDialog)
	//{{AFX_MSG_MAP(CMatDecoderStatus)
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_CBN_SELCHANGE(IDC_COMBO_SUBWND, OnSelchangeComboSubwnd)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_EXIT, OnExit)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMatDecoderStatus message handlers

BOOL CMatDecoderStatus::OnInitDialog() 
{
    CDialog::OnInitDialog();
    
    // TODO: Add extra initialization here
    CString tmp;
    
    memset(&m_Ability, 0, sizeof(NET_DVR_MATRIX_ABILITY_V41));
    if (!NET_DVR_GetDeviceAbility(m_lServerID, MATRIXDECODER_ABILITY_V41, NULL, 0, (char*)&m_Ability, sizeof(NET_DVR_MATRIX_ABILITY_V41)))
    {
        tmp.Format("Error code:%d", NET_DVR_GetLastError());
        AfxMessageBox(tmp);
        return FALSE;
    }
    else
    {        
        m_lStartChan = m_Ability.byStartChan;
        m_iChannelNumber = m_Ability.byDecChanNums;
        m_iVGANums = m_Ability.struVgaInfo.byChanNums;
        m_iBNCNums = m_Ability.struBncInfo.byChanNums;
		m_iHDMINums = m_Ability.struHdmiInfo.byChanNums;
		m_iDVINums = m_Ability.struDviInfo.byChanNums;
    }
    
	memset(&m_struDeviceCfg, 0, sizeof(m_struDeviceCfg));
	m_struDeviceCfg.dwSize = sizeof(m_struDeviceCfg);
	DWORD dwReturned = 0;
	if (!NET_DVR_GetDVRConfig(m_lServerID, NET_DVR_GET_DEVICECFG_V40, -1, &m_struDeviceCfg, sizeof(m_struDeviceCfg), &dwReturned))
	{
		MessageBox(NET_DVR_GetErrorMsg());
		return FALSE;
	}
    char szLan[128] = {0};
	int ChanNo = 0;
    int i;

	for(i = 0; i < m_iVGANums; i++)
    {
        //ChanNo = m_lStartChan + i;
        g_StringLanType(szLan, "VGA", "VGA");
        //tmp.Format("%s %d", szLan, ChanNo);
		tmp.Format("%s %d", szLan, i+1);
        m_SubWndCtrl.InsertString(i, tmp);
    }    

	for(i = 0; i < m_iBNCNums; i++)
    {
        //ChanNo = m_lStartChan + i;
        g_StringLanType(szLan, "BNC", "BNC");
        //tmp.Format("%s %d", szLan, ChanNo - m_iVGANums);
        tmp.Format("%s %d", szLan, i+1);
		m_SubWndCtrl.InsertString(i+m_iVGANums, tmp);
    }	
    

	for(i = 0; i < m_iHDMINums; i++)
    {
        ChanNo = m_lStartChan + i;
        g_StringLanType(szLan, "HDMI", "HDMI");
        //tmp.Format("%s %d", szLan, ChanNo - m_iVGANums - m_iBNCNums);
        tmp.Format("%s %d", szLan, i+1);
		m_SubWndCtrl.InsertString(i+m_iVGANums+m_iBNCNums, tmp);
    }

	for(i = 0; i < m_iDVINums; i++)
    {
        ChanNo = m_lStartChan + i;
        g_StringLanType(szLan, "DVI", "DVI");
        //tmp.Format("%s %d", szLan, ChanNo - m_iVGANums - m_iBNCNums - m_iHDMINums);
        tmp.Format("%s %d", szLan, i+1);
		m_SubWndCtrl.InsertString(i+m_iVGANums+m_iBNCNums+m_iHDMINums, tmp);
    }
    m_SubWndCtrl.SetCurSel(0);
    
    m_DecList.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
    g_StringLanType(szLan, "����ͨ��", "Decoder Chan");
    m_DecList.InsertColumn(0, szLan, LVCFMT_LEFT, 70, -1);
    g_StringLanType(szLan, "����״̬", "Dec Status");
    m_DecList.InsertColumn(1, szLan, LVCFMT_LEFT, 70, -1);
    g_StringLanType(szLan, "��������", "StreamType");
    m_DecList.InsertColumn(2, szLan, LVCFMT_LEFT, 70, -1);
    g_StringLanType(szLan, "�����ʽ", "PacketType");
    m_DecList.InsertColumn(3, szLan, LVCFMT_LEFT, 70, -1);
    g_StringLanType(szLan, "DSP CPU������", "Cpu Use");
    m_DecList.InsertColumn(4, szLan, LVCFMT_LEFT, 100, -1);
    g_StringLanType(szLan, "��Ƶ֡��", "Vedio Frame");
    m_DecList.InsertColumn(5, szLan, LVCFMT_LEFT, 70, -1);
    g_StringLanType(szLan, "��Ƶ֡��", "Audio Frame");
    m_DecList.InsertColumn(6, szLan, LVCFMT_LEFT, 70, -1);
    g_StringLanType(szLan, "�ѽ���Ƶ֡", "Passed Vedio");
    m_DecList.InsertColumn(7, szLan, LVCFMT_LEFT, 80, -1);
    g_StringLanType(szLan, "�ѽ���Ƶ֡", "Passed Audio");
    m_DecList.InsertColumn(8, szLan, LVCFMT_LEFT, 80, -1);
    g_StringLanType(szLan, "ͼ���", "ImageW");
    m_DecList.InsertColumn(9, szLan, LVCFMT_LEFT, 50, -1);
    g_StringLanType(szLan, "ͼ���", "ImageH");
    m_DecList.InsertColumn(10, szLan, LVCFMT_LEFT, 50, -1);
    g_StringLanType(szLan, "��Ƶ��ʽ", "PAL/NTSC");
    m_DecList.InsertColumn(11, szLan, LVCFMT_LEFT, 50, -1);
    
    m_DispList.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
    g_StringLanType(szLan, "��ʾͨ��", "Disp Chan");
    m_DispList.InsertColumn(0, szLan, LVCFMT_LEFT, 70, -1);
    g_StringLanType(szLan, "��ʾ״̬", "Disp Status");
    m_DispList.InsertColumn(1, szLan, LVCFMT_LEFT, 70, -1);
    g_StringLanType(szLan, "ͨ������", "Chan Type");
    m_DispList.InsertColumn(2, szLan, LVCFMT_LEFT, 80, -1);
    g_StringLanType(szLan, "��Ƶ��ʽ", "PAL/NTSC");
    m_DispList.InsertColumn(3, szLan, LVCFMT_LEFT, 70, -1);
    g_StringLanType(szLan, "��ǰ����ģʽ", "Sub Window");
    m_DispList.InsertColumn(4, szLan, LVCFMT_LEFT, 90, -1);
    g_StringLanType(szLan, "��Ļģʽ", "Screen Mode");
    m_DispList.InsertColumn(5, szLan, LVCFMT_LEFT, 70, -1);
    
    m_AlarmList.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
    g_StringLanType(szLan, "���������", "AlarmIn Chan");
    m_AlarmList.InsertColumn(0, szLan, LVCFMT_LEFT, 80, -1);
    g_StringLanType(szLan, "��������״̬", "AlarmIn Chan Status");
    m_AlarmList.InsertColumn(1, szLan, LVCFMT_LEFT, 100, -1);
    g_StringLanType(szLan, "���������", "AlarmOut Chan");
    m_AlarmList.InsertColumn(2, szLan, LVCFMT_LEFT, 80, -1);
    g_StringLanType(szLan, "�������״̬", "AlarmOut Chan Status");
    m_AlarmList.InsertColumn(3, szLan, LVCFMT_LEFT, 100, -1);

    m_SubWndList.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
    g_StringLanType(szLan, "�ӻ����", "Disp Chan");
    m_SubWndList.InsertColumn(0, szLan, LVCFMT_LEFT, 90, -1);
    g_StringLanType(szLan, "��������ͨ��", "Join DecChan");
    m_SubWndList.InsertColumn(1, szLan, LVCFMT_LEFT, 100, -1);
    g_StringLanType(szLan, "��ʾ֡��", "Disp Frame");
    m_SubWndList.InsertColumn(2, szLan, LVCFMT_LEFT, 80, -1);
    
	OnButton1();
	
	SetTimer(NULL, 10000, NULL);
	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CMatDecoderStatus::OnButton1() 
{
	// TODO: Add your control notification handler code here
    CString tmp;
    char szLan[128] = {0};
    m_SubWndList.DeleteAllItems();
    m_AlarmList.DeleteAllItems();
    m_DecList.DeleteAllItems();
    m_DispList.DeleteAllItems();

	BYTE byVGA = 1;
	BYTE byDVI = 1;
	BYTE byHDMI = 1;
	BYTE byBNC = 1;

	memset(&m_DecoderWorkStatus, 0, sizeof(NET_DVR_DECODER_WORK_STATUS_V41));
    if (!NET_DVR_MatrixGetDeviceStatus_V41(m_lServerID, &m_DecoderWorkStatus))
    {
        tmp.Format("Error: NET_DVR_MatrixGetDeviceStatus = %d", NET_DVR_GetLastError());
        AfxMessageBox(tmp);
    }
    else
    {
        m_Audio1Ctrl.SetCurSel(m_DecoderWorkStatus.byAudioInChanStatus&0x1);
        m_Audio2Ctrl.SetCurSel((m_DecoderWorkStatus.byAudioInChanStatus >> 1)&0x1);
		int j = 0;
        for(j = 0; j < 32; j++)
        {
            g_MatrixDecAudioStatus[j] = (m_DecoderWorkStatus.byAudioInChanStatus >> j)&0x1;
        }
		int i = 0;
        for(i = 0;i < m_iChannelNumber; i++)
        {
            tmp.Empty();
            tmp.Format("%d", i + m_lStartChan);
            m_DecList.InsertItem(i, tmp, 0);
            
            tmp.Empty();
            if (m_DecoderWorkStatus.struDecChanStatus[i].byDecodeStatus == 0)
            {
                g_StringLanType(szLan, "δ����", "not started");
                tmp = "δ����";
            }
            else
            {
                g_StringLanType(szLan, "������", "already started");
                tmp = "������";
            }
            m_DecList.SetItemText(i, 1, szLan);
            
            tmp.Empty();
            if (m_DecoderWorkStatus.struDecChanStatus[i].byStreamType == 0)
            {
                tmp = "Unknown";
            }
            else if (m_DecoderWorkStatus.struDecChanStatus[i].byStreamType == 1)
            {
                tmp = "Private H264";
            }
            else if (m_DecoderWorkStatus.struDecChanStatus[i].byStreamType == 2)
            {
                tmp = "Standard H264";
            }
            else if (m_DecoderWorkStatus.struDecChanStatus[i].byStreamType == 3)
            {
                tmp = "MPEG4";
            }
			else if (m_DecoderWorkStatus.struDecChanStatus[i].byStreamType == 4)
            {
                tmp = "Original Stream";
            }
            else if (m_DecoderWorkStatus.struDecChanStatus[i].byStreamType == 5)
            {
                tmp = "Picture";
            }
			else if (m_DecoderWorkStatus.struDecChanStatus[i].byStreamType == 6)
			{
				tmp = "MJPEG";
			}
			else if (m_DecoderWorkStatus.struDecChanStatus[i].byStreamType == 7)
			{
				tmp = "MPEG2";
			}
            m_DecList.SetItemText(i, 2, tmp);

            tmp.Empty();
            if (m_DecoderWorkStatus.struDecChanStatus[i].byPacketType == 0)
            {
                tmp = "Unknown";
            }
            else if (m_DecoderWorkStatus.struDecChanStatus[i].byPacketType == 1)
            {
                tmp = "PRIVT";
            }
            else if (m_DecoderWorkStatus.struDecChanStatus[i].byPacketType == 7)
            {
                tmp = "TS";
            }
            else if (m_DecoderWorkStatus.struDecChanStatus[i].byPacketType == 8)
            {
                tmp = "PS";
            }
            else if (m_DecoderWorkStatus.struDecChanStatus[i].byPacketType == 9)
            {
                tmp = "RTP";
            }
			else if (m_DecoderWorkStatus.struDecChanStatus[i].byPacketType == 10)
			{
				tmp = "Origin";
			}
            m_DecList.SetItemText(i, 3, tmp);

            tmp.Empty();
            tmp.Format("%d", m_DecoderWorkStatus.struDecChanStatus[i].byCpuLoad);
            m_DecList.SetItemText(i, 4, tmp);

			tmp.Empty();
			switch(m_DecoderWorkStatus.struDecChanStatus[i].byFpsDecV)
			{
			case LOW_DEC_FPS_1_2:
				tmp.Format("1/2");
				break;
				
			case LOW_DEC_FPS_1_4:
				tmp.Format("1/4");
				break;
				
			case LOW_DEC_FPS_1_8:
				tmp.Format("1/8");
				break;
				
			case LOW_DEC_FPS_1_16:
				tmp.Format("1/16");
				break;
				
			default:
				tmp.Format("%d", m_DecoderWorkStatus.struDecChanStatus[i].byFpsDecV);
				break;
			}   
            m_DecList.SetItemText(i, 5, tmp);
            
			tmp.Empty();
			switch(m_DecoderWorkStatus.struDecChanStatus[i].byFpsDecA)
			{
			case LOW_DEC_FPS_1_2:
				tmp.Format("1/2");
				break;
				
			case LOW_DEC_FPS_1_4:
				tmp.Format("1/4");
				break;
				
			case LOW_DEC_FPS_1_8:
				tmp.Format("1/8");
				break;
				
			case LOW_DEC_FPS_1_16:
				tmp.Format("1/16");
				break;
				
			default:
				tmp.Format("%d", m_DecoderWorkStatus.struDecChanStatus[i].byFpsDecA);
				break;
			}   
            m_DecList.SetItemText(i, 6, tmp);
           
            
            tmp.Empty();
            tmp.Format("%d", m_DecoderWorkStatus.struDecChanStatus[i].dwDecodedV);
            m_DecList.SetItemText(i, 7, tmp);
            
            tmp.Empty();
            tmp.Format("%d", m_DecoderWorkStatus.struDecChanStatus[i].dwDecodedA);
            m_DecList.SetItemText(i, 8, tmp);     
            
            tmp.Empty();
            tmp.Format("%d", m_DecoderWorkStatus.struDecChanStatus[i].wImgW);
            m_DecList.SetItemText(i, 9, tmp);
            
            tmp.Empty();
            tmp.Format("%d", m_DecoderWorkStatus.struDecChanStatus[i].wImgH);
            m_DecList.SetItemText(i, 10, tmp);
            
            tmp.Empty();
            if (m_DecoderWorkStatus.struDecChanStatus[i].byVideoFormat == 2)
            {
                tmp = "PAL";
            }
            else if(m_DecoderWorkStatus.struDecChanStatus[i].byVideoFormat == 1)
            {
                tmp = "NTSC";
            }
            else
            {
                tmp = "NULL";
            }
            m_DecList.SetItemText(i, 11, tmp);

			tmp.Empty();

        }
        
// 		if (DS630X_D == m_struDeviceCfg.byDVRType || DS_6504D_B10 == m_struDeviceCfg.byDVRType)
// 		{
// 			for (i = 0; i < m_iVGANums; i++)
// 			{
// 				tmp.Empty();
// 				tmp.Format("VGA%d", i + 1);
// 				m_DispList.InsertItem(i, tmp, 0);
// 				
// 				tmp.Empty();
// 				if (m_DecoderWorkStatus.struDispChanStatus[i].byDispStatus == 0)
// 				{
// 					g_StringLanType(szLan, "δ��ʾ", "not displayed");
// 					tmp = "δ��ʾ";
// 				}
// 				else
// 				{
// 					g_StringLanType(szLan, "����ʾ", "already displayed");
// 					tmp = "����ʾ";
// 				}
// 				m_DispList.SetItemText(i, 1, szLan);
// 				
// 				tmp.Empty();
// 				if (m_DecoderWorkStatus.struDispChanStatus[i].byBVGA == 0)
// 				{
// 					tmp = "BNC";
// 				}
// 				else
// 				{
// 					tmp = "VGA";
// 				}
// 				m_DispList.SetItemText(i, 2, tmp);
// 				
// 				tmp.Empty();
// 				if (m_DecoderWorkStatus.struDispChanStatus[i].byVideoFormat == 1)
// 				{
// 					tmp = "NTSC";
// 				}
// 				else if(m_DecoderWorkStatus.struDispChanStatus[i].byVideoFormat == 2)
// 				{
// 					tmp = "PAL";
// 				}
// 				else
// 				{
// 					tmp = "NULL";
// 				}
// 				m_DispList.SetItemText(i, 3, tmp);
// 				
// 				tmp.Empty();
// 				TRACE("lk---- %d ----- i %d", m_DecoderWorkStatus.struDispChanStatus[i].byWindowMode, i);
// 				tmp.Format("%d", m_DecoderWorkStatus.struDispChanStatus[i].byWindowMode);
// 				m_DispList.SetItemText(i, 4, tmp);
// 			}
// 			
// 			for (i = m_iVGANums; i < m_iVGANums + m_iBNCNums; i++)
// 			{
// 				tmp.Empty();
// 				tmp.Format("BNC%d", i - m_iVGANums + 1);
// 				m_DispList.InsertItem(i, tmp, 0);
// 				
// 				tmp.Empty();
// 				if (m_DecoderWorkStatus.struDispChanStatus[i + 8 - m_iVGANums].byDispStatus == 0)
// 				{
// 					g_StringLanType(szLan, "δ��ʾ", "not displayed");
// 					tmp = "δ��ʾ";
// 				}
// 				else
// 				{
// 					g_StringLanType(szLan, "����ʾ", "already displayed");
// 					tmp = "����ʾ";
// 				}
// 				m_DispList.SetItemText(i, 1, szLan);
// 				
// 				tmp.Empty();
// 				if (m_DecoderWorkStatus.struDispChanStatus[i + 8 - m_iVGANums].byBVGA == 0)
// 				{
// 					tmp = "BNC";
// 				}
// 				else
// 				{
// 					tmp = "VGA";
// 				}
// 				m_DispList.SetItemText(i, 2, tmp);
// 				
// 				tmp.Empty();
// 				if (m_DecoderWorkStatus.struDispChanStatus[i + 8 - m_iVGANums].byVideoFormat == 1)
// 				{
// 					tmp = "NTSC";
// 				}
// 				else if(m_DecoderWorkStatus.struDispChanStatus[i + 8 - m_iVGANums].byVideoFormat == 2)
// 				{
// 					tmp = "PAL";
// 				}
// 				else
// 				{
// 					tmp = "NULL";
// 				}
// 				m_DispList.SetItemText(i, 3, tmp);
// 				
// 				tmp.Empty();
// 				tmp.Format("%d", m_DecoderWorkStatus.struDispChanStatus[i + 8 - m_iVGANums].byWindowMode);
// 				m_DispList.SetItemText(i, 4, tmp);
// 			}
// 		}
// 		else if (DS610X_D ==m_struDeviceCfg.byDVRType || DS640X_HD == m_struDeviceCfg.byDVRType || DS64XXHD_T == m_struDeviceCfg.wDevType ||DS63XXD_T == m_struDeviceCfg.wDevType ||DS_65XXD == m_struDeviceCfg.wDevType)
// 		{    
			for (i = 0; i < m_iBNCNums + m_iVGANums + m_iHDMINums + m_iDVINums; i++)
			{
				tmp.Empty();
				if (m_DecoderWorkStatus.struDispChanStatus[i].byBVGA == 0)
				{
					tmp.Format("BNC%d", byBNC);
					m_DispList.InsertItem(i, tmp, 0);
					tmp = "BNC";
					byBNC++;
				}
				else if (m_DecoderWorkStatus.struDispChanStatus[i].byBVGA == 1)
				{
					tmp.Format("VGA%d", byVGA);
					m_DispList.InsertItem(i, tmp, 0);
					tmp = "VGA";
					byVGA++;
				}
				else if (m_DecoderWorkStatus.struDispChanStatus[i].byBVGA == 2)
				{
					tmp.Format("HDMI%d", byHDMI);
					m_DispList.InsertItem(i, tmp, 0);
					tmp = "HDMI";
					byHDMI++;
				}
				else if (m_DecoderWorkStatus.struDispChanStatus[i].byBVGA == 3)
				{
					tmp.Format("DVI%d", byDVI);
					m_DispList.InsertItem(i, tmp, 0);
					tmp = "DVI";
					byDVI++;
				}
				m_DispList.SetItemText(i, 2, tmp);
				
				tmp.Empty();
				if (m_DecoderWorkStatus.struDispChanStatus[i].byDispStatus == 0)
				{
					g_StringLanType(szLan, "δ��ʾ", "not displayed");
					tmp = "δ��ʾ";
				}
				else
				{
					g_StringLanType(szLan, "����ʾ", "already displayed");
					tmp = "����ʾ";
				}
				m_DispList.SetItemText(i, 1, szLan);
				
				tmp.Empty();
				if (m_DecoderWorkStatus.struDispChanStatus[i].byVideoFormat == 1)
				{
					tmp = "NTSC";
				}
				else if(m_DecoderWorkStatus.struDispChanStatus[i].byVideoFormat == 2)
				{
					tmp = "PAL";
				}
				else
				{
					tmp = "NULL";
				}
				m_DispList.SetItemText(i, 3, tmp);
				
				tmp.Empty();
				tmp.Format("%d", m_DecoderWorkStatus.struDispChanStatus[i].byWindowMode);
				m_DispList.SetItemText(i, 4, tmp);

				tmp.Empty();
				if (m_DecoderWorkStatus.struDispChanStatus[i].byScreenMode == 1)
				{
					tmp.Format("%s", "����");
				}
				else
				{
					tmp.Format("%s", "��ͨ");
				}
				m_DispList.SetItemText(i, 5, tmp);
			}
	/*	}*/
       
        for (i = 0; i < 32; i++)
        {
            tmp.Empty();
            tmp.Format("%d", i + m_lStartChan);
            m_AlarmList.InsertItem(i, tmp, 0);
            
            tmp.Empty();
            tmp.Format("%d", m_DecoderWorkStatus.byAlarmInStatus[i]);
            m_AlarmList.SetItemText(i, 1, tmp);
            
            tmp.Empty();
            tmp.Format("%d", i + m_lStartChan);
            m_AlarmList.SetItemText(i, 2, tmp);
            
            tmp.Empty();
            tmp.Format("%d", m_DecoderWorkStatus.byAlarmOutStatus[i]);
            m_AlarmList.SetItemText(i, 3, tmp);
        }
    
		OnSelchangeComboSubwnd();
		/*int iSubWnd = m_SubWndCtrl.GetCurSel();
        for (i = 0; i < MAX_WINDOWS; i++)
        {
            tmp.Empty();
            tmp.Format("%d", i + m_lStartChan);
            m_SubWndList.InsertItem(i, tmp, 0);
            
            tmp.Empty();
            tmp.Format("%d", m_DecoderWorkStatus.struDispChanStatus[iSubWnd].byJoinDecChan[i]);
            m_SubWndList.SetItemText(i, 1, tmp);
            
            tmp.Empty();
            tmp.Format("%d", m_DecoderWorkStatus.struDispChanStatus[iSubWnd].byFpsDisp[i]);
            m_SubWndList.SetItemText(i, 2, tmp);
        }*/
      }
    
      UpdateData(FALSE);
      OnSelchangeComboSubwnd();
}

void CMatDecoderStatus::OnSelchangeComboSubwnd() 
{
	UpdateData(TRUE);
    CString tmp;
    m_SubWndList.DeleteAllItems();
	if (DS630X_D == m_struDeviceCfg.byDVRType)
	{
		if (m_SubWndCtrl.GetCurSel() < m_iVGANums)
		{
			for (int i = 0; i < 16; i++)
			{
				tmp.Empty();
				tmp.Format("%d", i + m_lStartChan);
				m_SubWndList.InsertItem(i, tmp, 0);
				
				tmp.Empty();
				tmp.Format("%d", m_DecoderWorkStatus.struDispChanStatus[m_SubWndCtrl.GetCurSel()].byJoinDecChan[i]);
				m_SubWndList.SetItemText(i, 1, tmp);
				
				tmp.Empty();
				tmp.Format("%d", m_DecoderWorkStatus.struDispChanStatus[m_SubWndCtrl.GetCurSel()].byFpsDisp[i]);
				m_SubWndList.SetItemText(i, 2, tmp);
			}
		}
		else
		{
			for (int i = 0; i < 4; i++)
			{
				tmp.Empty();
				tmp.Format("%d", i + m_lStartChan);
				m_SubWndList.InsertItem(i, tmp, 0);
				
				tmp.Empty();
				tmp.Format("%d", m_DecoderWorkStatus.struDispChanStatus[m_SubWndCtrl.GetCurSel() + 8 - m_iVGANums].byJoinDecChan[i]);
				m_SubWndList.SetItemText(i, 1, tmp);
				
				tmp.Empty();
				tmp.Format("%d", m_DecoderWorkStatus.struDispChanStatus[m_SubWndCtrl.GetCurSel() + 8 - m_iVGANums].byFpsDisp[i]);
				m_SubWndList.SetItemText(i, 2, tmp);
			}
		}
	}
	else
	{
		/*if (m_SubWndCtrl.GetCurSel() < m_iVGANums)
		{
			for (int i = 0; i < 16; i++)
			{
				tmp.Empty();
				tmp.Format("%d", i + m_lStartChan);
				m_SubWndList.InsertItem(i, tmp, 0);
				
				tmp.Empty();
				tmp.Format("%d", m_DecoderWorkStatus.struDispChanStatus[m_SubWndCtrl.GetCurSel()].byJoinDecChan[i]);
				m_SubWndList.SetItemText(i, 1, tmp);
				
				tmp.Empty();
				tmp.Format("%d", m_DecoderWorkStatus.struDispChanStatus[m_SubWndCtrl.GetCurSel()].byFpsDisp[i]);
				m_SubWndList.SetItemText(i, 2, tmp);
			}
		}
		else
		{
			for (int i = 0; i < 16; i++)
			{
				tmp.Empty();
				tmp.Format("%d", i + m_lStartChan);
				m_SubWndList.InsertItem(i, tmp, 0);
				
				tmp.Empty();
				tmp.Format("%d", m_DecoderWorkStatus.struDispChanStatus[m_SubWndCtrl.GetCurSel()].byJoinDecChan[i]);
				m_SubWndList.SetItemText(i, 1, tmp);
				
				tmp.Empty();
				tmp.Format("%d", m_DecoderWorkStatus.struDispChanStatus[m_SubWndCtrl.GetCurSel()].byFpsDisp[i]);
				m_SubWndList.SetItemText(i, 2, tmp);
			}
		}*/
		for (int i = 0; i < MAX_WINDOWS; i++)
		{
			tmp.Empty();
			tmp.Format("%d", i + m_lStartChan);
			m_SubWndList.InsertItem(i, tmp, 0);
			
			tmp.Empty();
			tmp.Format("%d", m_DecoderWorkStatus.struDispChanStatus[m_SubWndCtrl.GetCurSel()].byJoinDecChan[i]);
			m_SubWndList.SetItemText(i, 1, tmp);
			
			tmp.Empty();
			tmp.Format("%d", m_DecoderWorkStatus.struDispChanStatus[m_SubWndCtrl.GetCurSel()].byFpsDisp[i]);
			m_SubWndList.SetItemText(i, 2, tmp);
		}	
	}	
	
    UpdateData(FALSE);
}

void CMatDecoderStatus::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	OnButton1();
	CDialog::OnTimer(nIDEvent);
}

void CMatDecoderStatus::OnExit() 
{
	// TODO: Add your control notification handler code here
    CDialog::OnCancel();
}
