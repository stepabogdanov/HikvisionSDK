/**********************************************************
FileName:    DlgHardDiskCfg.cpp
Description:  disk config    
Date:        2008/06/03
Note: 		 <global>struct, define refer to GeneralDef.h, global variables and functions refer to ClientDemo.cpp     
Modification History:      
    <version> <time>         <desc>
    <1.0    > <2008/06/03>       <created>
***********************************************************/
#include "stdafx.h"
#include "ClientDemo.h"
#include "DlgHardDiskCfg.h"
#include ".\dlgharddiskcfg.h"

#define  EXPAND_TIMER 1
#define  UNMOUNT_TIMER WM_USER +101
// CDlgHardDiskCfg dialog
/*********************************************************
  Function:	CDlgHardDiskCfg
  Desc:		Constructor
  Input:	pParent, parent window pointer
  Output:	none
  Return:	none
**********************************************************/
IMPLEMENT_DYNAMIC(CDlgHardDiskCfg, CDialog)
CDlgHardDiskCfg::CDlgHardDiskCfg(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgHardDiskCfg::IDD, pParent)
	, m_iSelHDNum(0)
	, m_bChkCyclicRecord(FALSE)
	, m_iSpaceThreshold(0)
	, m_dwChanCount(0)
	, m_iHDAttr(0)
	, m_iSelGroup(0)
	, m_iSelHDIndex(0)
    , m_lExapandHandle(-1)
	,m_lRemoteUnmountHandle(-1)
{
	m_bBackuping = FALSE;
	m_hBackupThread = NULL;
	m_lBackupHandle = 0;
	memset(&m_struDiskList, 0, sizeof(m_struDiskList));
}

/*********************************************************
  Function:	~CDlgHardDiskCfg
  Desc:		Destructor
  Input:	none
  Output:	none
  Return:	none
**********************************************************/
CDlgHardDiskCfg::~CDlgHardDiskCfg()
{
}

/*********************************************************
  Function:	DoDataExchange
  Desc:		the map between control and variable
  Input:	pDX, CDataExchange,pass the data exchange object to the window CWnd::DoDataExchange
  Output:	none
  Return:	none
**********************************************************/
void CDlgHardDiskCfg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgHardDiskCfg)
    DDX_Control(pDX, IDC_COMBO_DISK_LIST, m_cmbDiskList);
	DDX_Control(pDX, IDC_COMBO_HD_GROUP, m_cmbHDCFGGroup);
	DDX_Control(pDX, IDC_LIST_DISK, m_listDisk);
	DDX_Control(pDX, IDC_LIST_CHAN, m_listChan);
	DDX_Control(pDX, IDC_COMBO_GROUP, m_comboGroup);
	DDX_Control(pDX, IDC_COMBO_BELONG_GROUP, m_comboBelongGroup);
	DDX_Control(pDX, IDC_COMBO_DISK, m_comboDisk);
	DDX_Check(pDX, IDC_CHK_CONTINUE_BACKUP, m_bContinueBackup);
	DDX_Check(pDX, IDC_CHECK_DEL_ALL, m_bDelAllInvalidDisk);
	//}}AFX_DATA_MAP
}

/*********************************************************
  Function:	BEGIN_MESSAGE_MAP
  Desc:		the map between control and function
  Input:	first parameter:name of current class; second: name of base class
  Output:	none
  Return:	none
**********************************************************/
BEGIN_MESSAGE_MAP(CDlgHardDiskCfg, CDialog)
	//{{AFX_MSG_MAP(CDlgHardDiskCfg)	
	ON_BN_CLICKED(IDC_BTN_ONE_HD_OK, OnBnClickedBtnOneHdOk)
	ON_BN_CLICKED(IDC_BTN_HD_REFRESH, OnBtnHdRefresh)
	ON_BN_CLICKED(IDC_RADIO_NONE, OnRadioNone)
	ON_BN_CLICKED(IDC_RADIO_READ_ONLY, OnRadioReadOnly)
	ON_BN_CLICKED(IDC_RADIO_REDUND, OnRadioRedund)
	ON_NOTIFY(NM_CLICK, IDC_LIST_DISK, OnClickListDisk)
	ON_NOTIFY(NM_CLICK, IDC_LIST_CHAN, OnClickListChan)
	ON_CBN_SELCHANGE(IDC_COMBO_GROUP, OnSelchangeComboGroup)
	ON_CBN_SELCHANGE(IDC_COMBO_DISK, OnSelchangeComboDisk)
	ON_BN_CLICKED(IDC_BTN_SET_GROUP, OnBtnSetGroup)
	ON_BN_CLICKED(IDC_CHK_ALL_CHAN, OnChkAllChan)
	ON_BN_CLICKED(IDC_BTN_HD_SET, OnBtnHdSet)
	ON_BN_CLICKED(IDC_BTN_EXPAND, OnBtnExpand)
	ON_WM_TIMER()
        ON_BN_CLICKED(IDC_BTN_BACKUP_LOG, OnBtnBackupLog)
        ON_CBN_SELCHANGE(IDC_COMBO_DISK_LIST, OnSelchangeComboDiskList)
	ON_BN_CLICKED(IDC_BTN_DEL_HD, OnBtnDelHd)
	ON_BN_CLICKED(IDC_BTN_UNMOUNT, OnBtnUnmount)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BTN_MOUNT, OnBtnMount)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


// CDlgHardDiskCfg message handlers
/*********************************************************
  Function:	OnInitDialog
  Desc:		Initialize the dialog
  Input:	none
  Output:	none
  Return:	none
**********************************************************/
BOOL CDlgHardDiskCfg::OnInitDialog()
{
	CDialog::OnInitDialog();
	m_listDisk.SetExtendedStyle(m_listDisk.GetExtendedStyle()|LVS_EX_FULLROWSELECT);
	char szLan[128] = {0};
	g_StringLanType(szLan, "����", "HD Name");
	m_listDisk.InsertColumn(0,szLan,LVCFMT_LEFT,50,-1);
	g_StringLanType(szLan, "����", "Capacity");
	m_listDisk.InsertColumn(1, szLan,LVCFMT_LEFT,80,-1);
	g_StringLanType(szLan, "ʣ��ռ�", "Last Capacity");
	m_listDisk.InsertColumn(2, szLan, LVCFMT_LEFT, 90,-1);
	g_StringLanType(szLan, "״̬", "HD Status");
	m_listDisk.InsertColumn(3, szLan, LVCFMT_LEFT,100,-1);
	g_StringLanType(szLan, "����", "HD Group");
	m_listDisk.InsertColumn(4, szLan,LVCFMT_LEFT,50,-1);
	g_StringLanType(szLan, "����", "Attr");
	m_listDisk.InsertColumn(5, szLan, LVCFMT_LEFT,50,-1);
    g_StringLanType(szLan, "����", "Disk driver");
	m_listDisk.InsertColumn(6, szLan, LVCFMT_LEFT,50,-1);
	g_StringLanType(szLan, "�̷�", "Disk driver");
	m_listDisk.InsertColumn(7, szLan, LVCFMT_LEFT,70,-1);
	g_StringLanType(szLan, "Ӳ��ͼƬ����", "Picture Capacity");
	m_listDisk.InsertColumn(8, szLan, LVCFMT_LEFT,100,-1);
	g_StringLanType(szLan, "ʣ��ͼƬ�ռ�", "Free Picture Space");
	m_listDisk.InsertColumn(9, szLan, LVCFMT_LEFT,100,-1);

	m_listChan.SetExtendedStyle(m_listChan.GetExtendedStyle()|LVS_EX_CHECKBOXES);

	m_cmbHDCFGGroup.SetCurSel(0);
	return TRUE;  
}

/*********************************************************
  Function: CheckInitParam	
  Desc:		check and initialize the paramters
  Input:	none
  Output:	none
  Return:	none
**********************************************************/
void CDlgHardDiskCfg::CheckInitParam()
{
	UpdateData(TRUE);
	DWORD dwGroupNo = m_cmbHDCFGGroup.GetCurSel();
	CString csTemp;
	int i = 0;
	DWORD dwReturned = 0;
	char szLan[32] = {0};
	m_iSelHDNum = 0;
	m_iSelHDIndex = 0;
	ShowWindow(SW_SHOW);
	i = g_pMainDlg->GetCurDeviceIndex();
	if (i == -1/*||g_pMainDlg->IsCurDevMatDec(i)*/)
	{
		EnableWindow(FALSE);
		return;
	}

	EnableWindow(TRUE);
	((CButton *)GetDlgItem(IDC_RADIO_NONE))->SetCheck(FALSE);
	((CButton *)GetDlgItem(IDC_RADIO_REDUND))->SetCheck(FALSE);
	((CButton *)GetDlgItem(IDC_RADIO_READ_ONLY))->SetCheck(FALSE);
	m_listDisk.DeleteAllItems();
	m_comboGroup.ResetContent();
	m_dwDevIndex = i;
	m_lLoginID = g_struDeviceInfo[m_dwDevIndex].lLoginID;
	if (!NET_DVR_GetDVRConfig(m_lLoginID, NET_DVR_GET_HDCFG_V40, dwGroupNo, &m_struHDCfg, sizeof(NET_DVR_HDCFG), &dwReturned))
	{
		g_pMainDlg->AddLog(m_dwDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_HDCFG_V40"); 
		GetDlgItem(IDC_BTN_ONE_HD_OK)->EnableWindow(FALSE);
		if (NET_DVR_GetLastError() == NET_DVR_NOSUPPORT)
		{
			EnableWindow(FALSE);
		}
		return;
	}
	else
	{
		GetDlgItem(IDC_BTN_ONE_HD_OK)->EnableWindow(TRUE);
		g_pMainDlg->AddLog(m_dwDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_HDCFG_V40");

		
		
		//��0��
		if (0 == dwGroupNo)
		{
			m_comboDisk.ResetContent();
			for (i = 0; i < (int)m_struHDCfg.dwHDCount; i++)
			{
				csTemp.Format("%d", m_struHDCfg.struHDInfo[i].dwHDNo);
				m_listDisk.InsertItem(i, csTemp, 0);
				csTemp.Format("%dMB", m_struHDCfg.struHDInfo[i].dwCapacity);
				m_listDisk.SetItemText(i, 1, csTemp);
				csTemp.Format("%dMB", m_struHDCfg.struHDInfo[i].dwFreeSpace);
				m_listDisk.SetItemText(i, 2, csTemp);
				switch(m_struHDCfg.struHDInfo[i].dwHdStatus)//disk state 0-normal, 1-unformatted, 2-error, 3-SMART state, 4-unmatched, 5-idle
				{
				case 0:
					g_StringLanType(szLan, "����", "Normal");
					csTemp.Format(szLan);
					break;
				case 1:
					g_StringLanType(szLan, "δ��ʽ��", "Unformat");
					csTemp.Format(szLan);
					break;
				case 2:
					g_StringLanType(szLan, "����", "Error");
					csTemp.Format(szLan);
					break;
				case 3:
					g_StringLanType(szLan, "SMART״̬", "Smart Status");
					csTemp.Format(szLan);
					break;
				case 4:
					g_StringLanType(szLan, "��ƥ��", "Mismatch");
					csTemp.Format(szLan);
					break;
				case 5:
					g_StringLanType(szLan, "����", "Sleep");
					csTemp.Format(szLan);
					break;
				case 6:
					g_StringLanType(szLan, "δ����", "Offline");
					csTemp.Format(szLan);
					break;
				case 7:
					g_StringLanType(szLan, "������֧������", "Normal-Expand");
					csTemp.Format(szLan);
					break;
				case 10:
					g_StringLanType(szLan, "Ӳ�������޸�", "Repairing");
					csTemp.Format(szLan);
					break;
				case 11:
					g_StringLanType(szLan, "Ӳ�����ڸ�ʽ��", "Formating");
					csTemp.Format(szLan);
					break;
				case 12:
					g_StringLanType(szLan, "Ӳ�����ڵȴ���ʽ��", "Waiting for format");
					csTemp.Format(szLan);
					break;
				case 13:
					g_StringLanType(szLan, "Ӳ����ж��", "Disk is unload");
					csTemp.Format(szLan);
					break;
				case 14:
					g_StringLanType(szLan, "����Ӳ�̲�����", "Disk is not exist");
					csTemp.Format(szLan);
					break;
				case 15:
					g_StringLanType(szLan, "����ɾ��(����Ӳ��)","network hard  being deleted");
					csTemp.Format(szLan);
					break;
				default:
					g_StringLanType(szLan, "δ֪", "Unknow");
					csTemp.Format(szLan);
					break;
				}
				m_listDisk.SetItemText(i, 3, csTemp);

				csTemp.Format("%d", m_struHDCfg.struHDInfo[i].dwHdGroup);
				m_listDisk.SetItemText(i, 4, csTemp);
				
				switch(m_struHDCfg.struHDInfo[i].byHDAttr)
				{
				case 0:
					g_StringLanType(szLan, "��ͨ", "Normal");
					csTemp.Format(szLan);
					break;
				case 1:
					g_StringLanType(szLan, "����", "redundancy");
					csTemp.Format(szLan);
					break;
				case 2:
					g_StringLanType(szLan, "ֻ��", "Readonly");
					csTemp.Format(szLan);
					break;
				default:
					break;
				}
				m_listDisk.SetItemText(i, 5, csTemp);
				//save the index of hard disk
				m_listDisk.SetItemData(i,i);

				switch(m_struHDCfg.struHDInfo[i].byHDType)
				{
				case 0:
					g_StringLanType(szLan, "����Ӳ��", "Local");
					csTemp.Format(szLan);
					break;
				case 1:
					g_StringLanType(szLan, "ESATAӲ��", "EStata");
					csTemp.Format(szLan);
					break;
				case 2:
					g_StringLanType(szLan, "NFSӲ��", "NFS");
					csTemp.Format(szLan);
					break;
				case 3:
					g_StringLanType(szLan, "iSCSIӲ��", "iSCSI");
					csTemp.Format(szLan);
					break;
				case 4:
					g_StringLanType(szLan, "RAID�������", "RAID�������");
					csTemp.Format(szLan);
					break;
				default:
					break;
				}
				m_listDisk.SetItemText(i, 6, csTemp);
            
				m_listDisk.SetItemText(i, 7, (char*)&m_struHDCfg.struHDInfo[i].byDiskDriver);
				csTemp.Format("%d", m_struHDCfg.struHDInfo[i].dwPictureCapacity);
				m_listDisk.SetItemText(i, 8, csTemp);
				
				csTemp.Format("%d", m_struHDCfg.struHDInfo[i].dwFreePictureSpace);
				m_listDisk.SetItemText(i, 9, csTemp);


				csTemp.Format("%d", m_struHDCfg.struHDInfo[i].dwHDNo);
				m_comboDisk.AddString(csTemp);
				m_comboDisk.SetItemData(i, m_struHDCfg.struHDInfo[i].dwHDNo);

            
			}
		}
		else 
		{
			if (m_struHDCfg.dwHDCount > MAX_DISKNUM_V30*dwGroupNo)
			{
				for (i = 0; i < (int)m_struHDCfg.dwHDCount-MAX_DISKNUM_V30*dwGroupNo; i++)
				{
					csTemp.Format("%d", m_struHDCfg.struHDInfo[i].dwHDNo);
					m_listDisk.InsertItem(i, csTemp, 0);
					csTemp.Format("%dMB", m_struHDCfg.struHDInfo[i].dwCapacity);
					m_listDisk.SetItemText(i, 1, csTemp);
					csTemp.Format("%dMB", m_struHDCfg.struHDInfo[i].dwFreeSpace);
					m_listDisk.SetItemText(i, 2, csTemp);
					switch(m_struHDCfg.struHDInfo[i].dwHdStatus)//disk state 0-normal, 1-unformatted, 2-error, 3-SMART state, 4-unmatched, 5-idle
					{
					case 0:
						g_StringLanType(szLan, "����", "Normal");
						csTemp.Format(szLan);
						break;
					case 1:
						g_StringLanType(szLan, "δ��ʽ��", "Unformat");
						csTemp.Format(szLan);
						break;
					case 2:
						g_StringLanType(szLan, "����", "Error");
						csTemp.Format(szLan);
						break;
					case 3:
						g_StringLanType(szLan, "SMART״̬", "Smart Status");
						csTemp.Format(szLan);
						break;
					case 4:
						g_StringLanType(szLan, "��ƥ��", "Mismatch");
						csTemp.Format(szLan);
						break;
					case 5:
						g_StringLanType(szLan, "����", "Sleep");
						csTemp.Format(szLan);
						break;
					case 6:
						g_StringLanType(szLan, "δ����", "Offline");
						csTemp.Format(szLan);
						break;
					case 7:
						g_StringLanType(szLan, "������֧������", "Normal-Expand");
						csTemp.Format(szLan);
						break;
					case 10:
						g_StringLanType(szLan, "Ӳ�������޸�", "Repairing");
						csTemp.Format(szLan);
						break;
					case 11:
						g_StringLanType(szLan, "Ӳ�����ڸ�ʽ��", "Formating");
						csTemp.Format(szLan);
						break;
					case 12:
						g_StringLanType(szLan, "Ӳ�����ڵȴ���ʽ��", "Waiting for format");
						csTemp.Format(szLan);
						break;
					case 13:
						g_StringLanType(szLan, "Ӳ����ж��", "Disk is unload");
						csTemp.Format(szLan);
						break;
					case 14:
						g_StringLanType(szLan, "����Ӳ�̲�����", "Disk is not exist");
						csTemp.Format(szLan);
						break;
					case 15:
						g_StringLanType(szLan, "����ɾ��(����Ӳ��)","network hard  being deleted");
						csTemp.Format(szLan);
						break;
					default:
						g_StringLanType(szLan, "δ֪", "Unknow");
						csTemp.Format(szLan);
						break;
					}
					m_listDisk.SetItemText(i, 3, csTemp);

					csTemp.Format("%d", m_struHDCfg.struHDInfo[i].dwHdGroup);
					m_listDisk.SetItemText(i, 4, csTemp);
					
					switch(m_struHDCfg.struHDInfo[i].byHDAttr)
					{
					case 0:
						g_StringLanType(szLan, "��ͨ", "Normal");
						csTemp.Format(szLan);
						break;
					case 1:
						g_StringLanType(szLan, "����", "redundancy");
						csTemp.Format(szLan);
						break;
					case 2:
						g_StringLanType(szLan, "ֻ��", "Readonly");
						csTemp.Format(szLan);
						break;
					default:
						break;
					}
					m_listDisk.SetItemText(i, 5, csTemp);
					//save the index of hard disk
					m_listDisk.SetItemData(i,i);

					switch(m_struHDCfg.struHDInfo[i].byHDType)
					{
					case 0:
						g_StringLanType(szLan, "����Ӳ��", "Local");
						csTemp.Format(szLan);
						break;
					case 1:
						g_StringLanType(szLan, "ESATAӲ��", "EStata");
						csTemp.Format(szLan);
						break;
					case 2:
						g_StringLanType(szLan, "NFSӲ��", "NFS");
						csTemp.Format(szLan);
						break;
					case 3:
						g_StringLanType(szLan, "iSCSIӲ��", "iSCSI");
						csTemp.Format(szLan);
						break;
					case 4:
						g_StringLanType(szLan, "RAID�������", "RAID�������");
						csTemp.Format(szLan);
						break;
					default:
						break;
					}
					m_listDisk.SetItemText(i, 6, csTemp);
            
					m_listDisk.SetItemText(i, 7, (char*)&m_struHDCfg.struHDInfo[i].byDiskDriver);
					csTemp.Format("%d", m_struHDCfg.struHDInfo[i].dwPictureCapacity);
					m_listDisk.SetItemText(i, 8, csTemp);
					
					csTemp.Format("%d", m_struHDCfg.struHDInfo[i].dwFreePictureSpace);
					m_listDisk.SetItemText(i, 9, csTemp);

					csTemp.Format("%d", m_struHDCfg.struHDInfo[i].dwHDNo);
					m_comboDisk.AddString(csTemp);
					m_comboDisk.SetItemData(i, m_struHDCfg.struHDInfo[i].dwHDNo);
            
				}
			}
		}


	}
	

	m_iSelHDIndex = 0;
 	m_comboDisk.SetCurSel(m_iSelHDIndex);
 	m_iSelHDNum = m_comboDisk.GetItemData(m_iSelHDIndex);	

	m_comboBelongGroup.ResetContent();
	for (i=0; i<MAX_HD_GROUP; i++)
	{
		csTemp.Format("%d", i+1);
		m_comboBelongGroup.AddString(csTemp);
	}

	//get disk group configuration
	if (!NET_DVR_GetDVRConfig(m_lLoginID, NET_DVR_GET_HDGROUP_CFG, 0, &m_struHDGroupCfg, sizeof(NET_DVR_HDGROUP_CFG), &dwReturned))
	{
		g_pMainDlg->AddLog(m_dwDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_HDGROUP_CFG"); 
		GetDlgItem(IDC_BTN_SET_GROUP)->EnableWindow(FALSE);
	}
	else
	{
		GetDlgItem(IDC_BTN_SET_GROUP)->EnableWindow(TRUE);
		g_pMainDlg->AddLog(m_dwDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_HDGROUP_CFG"); 
		for (i = 0; i < (int)m_struHDGroupCfg.dwHDGroupCount; i++)
		{
			csTemp.Format("%d", m_struHDGroupCfg.struHDGroupAttr[i].dwHDGroupNo);
			m_comboGroup.AddString(csTemp);
			m_comboGroup.SetItemData(i, m_struHDGroupCfg.struHDGroupAttr[i].dwHDGroupNo);
		}
		m_iSelGroup = 0;
		m_comboGroup.SetCurSel(m_iSelGroup);
		m_iGroupNum = m_comboGroup.GetItemData(m_iSelGroup);
		UpdataChanStatus();
	}

	if (!NET_DVR_GetDiskList(m_lLoginID, &m_struDiskList))
    {
        g_pMainDlg->AddLog(m_dwDevIndex, OPERATION_FAIL_T, "NET_DVR_GetDiskList");
    }
    else
    {
        g_pMainDlg->AddLog(m_dwDevIndex, OPERATION_SUCC_T, "NET_DVR_GetDiskList");
    }

	m_cmbDiskList.ResetContent();
    for (int j = 0; j < m_struDiskList.dwNodeNum; j++)
    {
        m_cmbDiskList.AddString((char*)m_struDiskList.struDescNode[j].byDescribe);
        m_cmbDiskList.SetItemData(j, m_struDiskList.struDescNode[j].iValue);
    }
    m_cmbDiskList.SetCurSel(0);
    OnSelchangeComboDiskList();

	UpdateData(FALSE);
}

/*********************************************************
  Function:	UpdataChanStatus
  Desc:		update the status of all channels
  Input:	none
  Output:	none
  Return:	none
**********************************************************/
void CDlgHardDiskCfg::UpdataChanStatus()
{
	int iIndex = 0;
	int i = 0;
	CString csTemp;
	m_listChan.DeleteAllItems();
	//get the whole state of all channels
	m_bChkAllChan = TRUE;
	for (i=0; i<MAX_CHANNUM_V30; i++)
	{
		if (g_struDeviceInfo[m_dwDevIndex].struChanInfo[i].bEnable)
		{
			if (!m_struHDGroupCfg.struHDGroupAttr[m_iSelGroup].byHDGroupChans[i])
			{
				m_bChkAllChan = FALSE;
				break;
			}
		}
	}

	//insert all channel node
	m_listChan.InsertItem(iIndex, "All Chan");
	if (m_bChkAllChan)
	{
		m_listChan.SetCheck(iIndex, TRUE);
	}
	
	m_listChan.SetItemData(iIndex, 0xffff);
	iIndex ++;	

	for (i=0; i<MAX_CHANNUM_V30; i++)
	{
		if (g_struDeviceInfo[m_dwDevIndex].struChanInfo[i].bEnable)
		{
			if (i<g_struDeviceInfo[m_dwDevIndex].iDeviceChanNum)
			{
				csTemp.Format(ANALOG_C_FORMAT, g_struDeviceInfo[m_dwDevIndex].iStartChan+i);
			}
			else
			{
				csTemp.Format(DIGITAL_C_FORMAT, g_struDeviceInfo[m_dwDevIndex].iStartChan+i-MAX_ANALOG_CHANNUM);
			}
			
			m_listChan.InsertItem(iIndex, csTemp);
			if (m_struHDGroupCfg.struHDGroupAttr[m_iSelGroup].byHDGroupChans[i])
			{
				m_listChan.SetCheck(iIndex, TRUE);
			}
			
			m_listChan.SetItemData(iIndex, i);
			iIndex ++;			
		}
	}
}

/*********************************************************
  Function:	OnBnClickedBtnOneHdOk
  Desc:		save the current select disk config
  Input:	none
  Output:	none
  Return:	none
**********************************************************/
void CDlgHardDiskCfg::OnBnClickedBtnOneHdOk()
{
	UpdateData(TRUE);
	CString csTemp = _T("");
	m_iSelHDIndex = m_comboDisk.GetCurSel();
	m_iSelHDNum = m_comboDisk.GetItemData(m_iSelHDIndex);//

	m_struHDCfg.struHDInfo[m_iSelHDIndex].byHDAttr = (BYTE)m_iHDAttr;
	m_struHDCfg.struHDInfo[m_iSelHDIndex].dwHdGroup = m_comboBelongGroup.GetCurSel()+1;
}

/*********************************************************
  Function:	OnBtnHdRefresh
  Desc:		refresh the paramters of the channels
  Input:	none
  Output:	none
  Return:	none
**********************************************************/
void CDlgHardDiskCfg::OnBtnHdRefresh() 
{
	// TODO: Add your control notification handler code here
	CheckInitParam();
}

void CDlgHardDiskCfg::OnRadioNone() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	m_iHDAttr = 0;
	UpdateData(FALSE);
}

/*********************************************************
  Function:	OnRadioRedund
  Desc:		choose the redundancy attribute 
  Input:	none
  Output:	none
  Return:	none
**********************************************************/
void CDlgHardDiskCfg::OnRadioRedund() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	m_iHDAttr = 1;
	UpdateData(FALSE);
}

/*********************************************************
  Function:	OnRadioReadOnly
  Desc:		choose the read-only attribute
  Input:	none
  Output:	none
  Return:	none
**********************************************************/
void CDlgHardDiskCfg::OnRadioReadOnly() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	m_iHDAttr = 2;
	UpdateData(FALSE);
}

/*********************************************************
  Function:	SetRadioChk
  Desc:		set the attribute status
  Input:	iAttr, switch the status of the hard disk attributes
  Output:	none
  Return:	none
**********************************************************/
void CDlgHardDiskCfg::SetRadioChk(int iAttr)
{
	switch(iAttr)
	{
	case 0:
		((CButton *)GetDlgItem(IDC_RADIO_NONE))->SetCheck(TRUE);
		((CButton *)GetDlgItem(IDC_RADIO_REDUND))->SetCheck(FALSE);
		((CButton *)GetDlgItem(IDC_RADIO_READ_ONLY))->SetCheck(FALSE);
		m_iHDAttr = 0;
		break;
	case 1:
		((CButton *)GetDlgItem(IDC_RADIO_NONE))->SetCheck(FALSE);
		((CButton *)GetDlgItem(IDC_RADIO_REDUND))->SetCheck(TRUE);
		((CButton *)GetDlgItem(IDC_RADIO_READ_ONLY))->SetCheck(FALSE);
		m_iHDAttr = 1;
		break;
	case 2:
		((CButton *)GetDlgItem(IDC_RADIO_NONE))->SetCheck(FALSE);
		((CButton *)GetDlgItem(IDC_RADIO_REDUND))->SetCheck(FALSE);
		((CButton *)GetDlgItem(IDC_RADIO_READ_ONLY))->SetCheck(TRUE);
		m_iHDAttr = 2;
	    break;
	default:
	    break;
	}
}

/*********************************************************
  Function:	OnClickListDisk
  Desc:		update the control status of the choose disk
  Input:	pNMHDR, Contains the click information
  Output:	pResult, result after handle notification	
  Return:	none
**********************************************************/
void CDlgHardDiskCfg::OnClickListDisk(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
//	LPNMHEADER phdr = reinterpret_cast<LPNMHEADER>(pNMHDR);
 	POSITION  iPos = m_listDisk.GetFirstSelectedItemPosition();
 	if (iPos == NULL)
 	{
 		return;
 	}
	CString csTmp;
	int iData = m_listDisk.GetItemData(m_listDisk.GetNextSelectedItem(iPos));
	m_iSelHDIndex = iData;
	m_struHDCfg.struHDInfo[m_iSelHDIndex].dwHdGroup;
	m_iSelHDNum = m_struHDCfg.struHDInfo[m_iSelHDIndex].dwHDNo;
	m_comboDisk.SetCurSel(m_iSelHDIndex);
	SetRadioChk(m_struHDCfg.struHDInfo[m_iSelHDIndex].byHDAttr);
	m_comboBelongGroup.SetCurSel(m_struHDCfg.struHDInfo[m_iSelHDIndex].dwHdGroup - 1);
	UpdateData(FALSE);
	*pResult = 0;
}

/*********************************************************
  Function:	OnClickListChan
  Desc:		update the status of the choosed channels
  Input:	pNMHDR, Contains the click information
  Output:	pResult, result after handle notification	
  Return:	none
**********************************************************/
void CDlgHardDiskCfg::OnClickListChan(NMHDR* pNMHDR, LRESULT* pResult) 
{
	UpdateData(TRUE);
	
	//POSITION  iPos = m_listChan.GetFirstSelectedItemPosition();//is not useful for small icon list
//	LPNMHEADER phdr = reinterpret_cast<LPNMHEADER>(pNMHDR);
	DWORD dwPos = GetMessagePos();
	CPoint point( LOWORD(dwPos), HIWORD(dwPos));

	m_listChan.ScreenToClient(&point);
 	
	UINT uFlag = 0;
	int iSel = m_listChan.HitTest(point, &uFlag);//
	if (iSel < 0)
	{
		return;
	}

	CString csTmp;
	int iData = m_listChan.GetItemData(iSel);
	if (iData == 0xffff)
	{
		m_bChkAllChan = !m_bChkAllChan;
		if (uFlag == LVHT_ONITEMLABEL)
		{
			m_listChan.SetCheck(iSel, m_bChkAllChan);
		}
		OnChkAllChan();
		return;
	}
	if (m_listChan.GetCheck(iSel))
	{
		m_struHDGroupCfg.struHDGroupAttr[m_iSelGroup].byHDGroupChans[iData] = 0;
	}
	else
	{
		m_struHDGroupCfg.struHDGroupAttr[m_iSelGroup].byHDGroupChans[iData] = 1;
	}
	
	if (uFlag == LVHT_ONITEMLABEL)
	{
		m_listChan.SetCheck(iSel, m_struHDGroupCfg.struHDGroupAttr[m_iSelGroup].byHDGroupChans[iData]);
	}
	UpdateData(FALSE);

	*pResult = 0;
}

/*********************************************************
  Function:	OnSelchangeComboGroup
  Desc:		update the group index
  Input:	none
  Output:	none
  Return:	none
**********************************************************/
void CDlgHardDiskCfg::OnSelchangeComboGroup() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	m_iSelGroup = m_comboGroup.GetCurSel();
	m_iGroupNum = m_comboGroup.GetItemData(m_iSelGroup);
	UpdataChanStatus();
}

/*********************************************************
  Function:	OnSelchangeComboDisk
  Desc:		none
  Input:	none
  Output:	none
  Return:	none
**********************************************************/
void CDlgHardDiskCfg::OnSelchangeComboDisk() 
{
	// TODO: Add your control notification handler code here
	
}

/*********************************************************
  Function:	OnBtnSetGroup
  Desc:		setup the configure of the hard disk group
  Input:	none
  Output:	none
  Return:	none
**********************************************************/
void CDlgHardDiskCfg::OnBtnSetGroup() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	CString csTemp = _T("");
	m_iSelGroup = m_comboGroup.GetCurSel();
	m_iGroupNum = m_comboGroup.GetItemData(m_iSelGroup);
	char szLan[128] = {0};
	if (!NET_DVR_SetDVRConfig(m_lLoginID, NET_DVR_SET_HDGROUP_CFG, 0, &m_struHDGroupCfg, sizeof(NET_DVR_HDGROUP_CFG)))
	{
		g_pMainDlg->AddLog(m_dwDevIndex, OPERATION_FAIL_T, "NET_DVR_SET_HDGROUP_CFG"); 
		g_StringLanType(szLan, "�������ʧ��", "Save parameter failed");
		AfxMessageBox(szLan);
	}
	else
	{
		g_pMainDlg->AddLog(m_dwDevIndex, OPERATION_SUCC_T, "NET_DVR_SET_HDGROUP_CFG"); 
		g_StringLanType(szLan, "��������ɹ�,������!", "Save parameter successfully, please reboot!");
		AfxMessageBox(szLan);
	}	
}

void CDlgHardDiskCfg::OnChkAllChan() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	CString csTmp;
	int iSel = 0;
	int iChanIndex = 0;
	int i = 0;

	for (i = 0; i<MAX_CHANNUM_V30; i++)
	{
		if (g_struDeviceInfo[m_dwDevIndex].struChanInfo[i].bEnable)
		{
			iSel++;
			m_listChan.SetCheck(iSel, m_bChkAllChan);
			iChanIndex = m_listChan.GetItemData(iSel);
			if (m_bChkAllChan)
			{
				m_struHDGroupCfg.struHDGroupAttr[m_iSelGroup].byHDGroupChans[iChanIndex] = 1;
			}
			else
			{
				m_struHDGroupCfg.struHDGroupAttr[m_iSelGroup].byHDGroupChans[iChanIndex] = 0;
			}
		}
	}

	UpdateData(FALSE);	
}

/*********************************************************
  Function:	
  Desc:		
  Input:	none
  Output:	none
  Return:	none
**********************************************************/
void CDlgHardDiskCfg::OnBtnHdSet() 
{
	// TODO: Add your control notification handler code here
	OnBnClickedBtnOneHdOk();
	UpdateData(TRUE);
	DWORD dwGroup = m_comboGroup.GetCurSel();
	char szLan[128] = {0};
	if (!NET_DVR_SetDVRConfig(m_lLoginID, NET_DVR_SET_HDCFG_V40, dwGroup, &m_struHDCfg, sizeof(NET_DVR_HDCFG)))
	{
		g_pMainDlg->AddLog(m_dwDevIndex, OPERATION_FAIL_T, "NET_DVR_SET_HDCFG_V40"); 
		g_StringLanType(szLan, "�������ʧ��", "Save parameter failed");
		AfxMessageBox(szLan);
	}
	else
	{
		g_pMainDlg->AddLog(m_dwDevIndex, OPERATION_SUCC_T, "NET_DVR_SET_HDCFG_V40"); 
		g_StringLanType(szLan, "��������ɹ�,������!", "Save parameter successfully, please reboot!");
		AfxMessageBox(szLan);
	}
}

void CDlgHardDiskCfg::OnBtnExpand() 
{
    POSITION  iPos = m_listDisk.GetFirstSelectedItemPosition();
    if (iPos == NULL)
    {
        return;
    }
    CString csTmp;
    int iData = m_listDisk.GetItemData(m_listDisk.GetNextSelectedItem(iPos));
    m_iSelHDIndex = iData;

    if (7 != m_struHDCfg.struHDInfo[m_iSelHDIndex].dwHdStatus) // 
    {
        AfxMessageBox("Not support expand");
        return;
    }
    
    m_lExapandHandle = NET_DVR_ExpandDisk(m_lLoginID, m_struHDCfg.struHDInfo[m_iSelHDIndex].dwHDNo);
    
    if (-1 == m_lExapandHandle)
    {
        g_pMainDlg->AddLog(m_dwDevIndex, OPERATION_FAIL_T, "NET_DVR_ExpandDisk");
        return;
    }
    else
    {
        g_pMainDlg->AddLog(m_dwDevIndex, OPERATION_SUCC_T, "NET_DVR_ExpandDisk");
        SetTimer(EXPAND_TIMER, 1000, NULL);
    }
    
}

void CDlgHardDiskCfg::OnTimer(UINT nIDEvent) 
{
	char szLan[128] = {0};
    if (nIDEvent == EXPAND_TIMER && m_lExapandHandle >= 0)
    {
        DWORD dwState = 0;
        char szLan[128] = {0};
        NET_DVR_GetExpandProgress(m_lExapandHandle, &dwState);
        
        if (dwState >= 0 && dwState < 100)
        {
            //TRACE("dwState = %d", dwState); 

            sprintf(szLan, "Process:%d%", dwState);
            GetDlgItem(IDC_STATIC_EXPAND_STATUS)->SetWindowText(szLan);
        }
        else if (dwState == PROCESS_SUCCESS)
        {
            TRACE("Expand succ");
            GetDlgItem(IDC_STATIC_EXPAND_STATUS)->SetWindowText("Success");
            NET_DVR_CloseExpandHandle(m_lExapandHandle); 
            KillTimer(EXPAND_TIMER);
        }
        else if (dwState == PROCESS_EXCEPTION)
        {
            GetDlgItem(IDC_STATIC_EXPAND_STATUS)->SetWindowText("Expand exception");
            NET_DVR_CloseExpandHandle(m_lExapandHandle); 
            KillTimer(EXPAND_TIMER);
        }
        else if (dwState == PROCESS_FAILED)
        {
            GetDlgItem(IDC_STATIC_EXPAND_STATUS)->SetWindowText("Expand Failed");
            NET_DVR_CloseExpandHandle(m_lExapandHandle); 
            KillTimer(EXPAND_TIMER);
        }
        else
        {
            GetDlgItem(IDC_STATIC_EXPAND_STATUS)->SetWindowText("Expand Failed");
            NET_DVR_CloseExpandHandle(m_lExapandHandle); 
            KillTimer(EXPAND_TIMER);
        }
    }
	else if (UNMOUNT_TIMER == nIDEvent)
	{
		DWORD dwState = 0;
		if (!NET_DVR_GetRemoteConfigState(m_lRemoteUnmountHandle,&dwState))
		{
			g_pMainDlg->AddLog(m_dwDevIndex, OPERATION_FAIL_T, "NET_DVR_RemoteConfigGetState NET_DVR_UNMOUNT_DISK ");
			GetDlgItem(IDC_STATIC_UNMOUNT_STATUS)->SetWindowText("״̬�� ��ȡʧ��");
			NET_DVR_StopRemoteConfig(m_lRemoteUnmountHandle);
			//�رռ�ʱ��
			KillTimer(UNMOUNT_TIMER);
		}
		
		
		if (NET_SDK_CALLBACK_STATUS_FAILED == dwState )
		{
			GetDlgItem(IDC_STATIC_UNMOUNT_STATUS)->SetWindowText("״̬��ʧ��");
			NET_DVR_StopRemoteConfig(m_lRemoteUnmountHandle);
			//�رռ�ʱ��
			KillTimer(UNMOUNT_TIMER);
		}
		else if (NET_SDK_CALLBACK_STATUS_PROCESSING == dwState)
		{
			GetDlgItem(IDC_STATIC_UNMOUNT_STATUS)->SetWindowText("״̬��������...");
		}
		else if (NET_SDK_CALLBACK_STATUS_SUCCESS == dwState)
		{
			GetDlgItem(IDC_STATIC_UNMOUNT_STATUS)->SetWindowText("״̬���ɹ�");
			NET_DVR_StopRemoteConfig(m_lRemoteUnmountHandle);
			//�رռ�ʱ��
			KillTimer(UNMOUNT_TIMER);
		}
		else
		{
			sprintf(szLan, "״̬:%d", dwState);
			GetDlgItem(IDC_STATIC_UNMOUNT_STATUS)->SetWindowText(szLan);//"״̬��δ֪״̬"
			//NET_DVR_StopRemoteConfig(m_lRemoteUnmountHandle);
			//�رռ�ʱ��
			//KillTimer(UNMOUNT_TIMER);
		}
		
	}
    // 	   if (nIDEvent == EXPAND_TIMER)
//        {
//            DWORD dwState = 0;
//            char szLan[128] = {0};
//            NET_DVR_FastConfigProcess(m_lFastConfigHandle, &dwState);
//            
//            
//            if (dwState >= 0 && dwState < 100)
//            {
//                //TRACE("dwState = %d", dwState); 
//                sprintf(szLan, "Process:%d%", dwState);
//                GetDlgItem(IDC_STATIC_PROCESS)->SetWindowText(szLan);
//            }
//            else if (dwState == PROCESS_SUCCESS)
//            {
//                TRACE("Fastconfig succ");
//                GetDlgItem(IDC_STATIC_PROCESS)->SetWindowText("Success");
//                NET_DVR_CloseFastConfig(m_lFastConfigHandle); 
//                KillTimer(EXPAND_TIMER);
//                CurCfgUpdate();
//            }
//            else if (dwState == PROCESS_EXCEPTION)
//            {
//                GetDlgItem(IDC_STATIC_PROCESS)->SetWindowText("Fastconfig exception");
//                NET_DVR_CloseFastConfig(m_lFastConfigHandle);
//                KillTimer(EXPAND_TIMER);
//            }
//            else if (dwState == PROCESS_FAILED)
//            {
//                GetDlgItem(IDC_STATIC_PROCESS)->SetWindowText("Fastconfig Failed");
//                NET_DVR_CloseFastConfig(m_lFastConfigHandle);
//                KillTimer(EXPAND_TIMER);
//            }
//            else
//            {
//                GetDlgItem(IDC_STATIC_PROCESS)->SetWindowText("Fastconfig Failed");
//                NET_DVR_CloseFastConfig(m_lFastConfigHandle);
//                KillTimer(EXPAND_TIMER);
//            }
//            //UpdateData(FALSE);
//     }
	UpdateData(FALSE);
	CDialog::OnTimer(nIDEvent);
}

DWORD  GetBackupLogThread(LPVOID pParam)
{
     CDlgHardDiskCfg *pThis = ( CDlgHardDiskCfg*)pParam;
    pThis->GetDlgItem(IDC_STATIC_BACK_STATE)->ShowWindow(SW_SHOW);
    DWORD dwState = 0;
    char szLan[256] = {0};
    while (1)
    {
		if (!NET_DVR_GetBackupProgress(pThis->m_lBackupHandle, &dwState))
        {
			DWORD dwErr = NET_DVR_GetLastError();
			//may be successful too quick
			g_StringLanType(szLan, "�������", "Succ to backup");
			pThis->GetDlgItem(IDC_STATIC_BACK_STATE)->SetWindowText(szLan);
			g_StringLanType(szLan, "��־����", "Backup");
			pThis->GetDlgItem(IDC_BTN_BACKUP_LOG)->SetWindowText(szLan);
			pThis->GetDlgItem(IDC_STATIC_BACK_STATE)->ShowWindow(SW_HIDE);
			g_pMainDlg->AddLog(pThis->m_dwDevIndex, OPERATION_FAIL_T, "NET_DVR_GetBackupProgress");	
			
			break;
        }
		g_pMainDlg->AddLog(pThis->m_dwDevIndex, OPERATION_SUCC_T, "NET_DVR_GetBackupProgress [%d]", dwState);	


		if (dwState == 100)
        {
            g_StringLanType(szLan, "�������", "Succ to backup");
            pThis->GetDlgItem(IDC_STATIC_BACK_STATE)->SetWindowText(szLan);
            g_StringLanType(szLan, "��־����", "Backup");
            pThis->GetDlgItem(IDC_BTN_BACKUP_LOG)->SetWindowText(szLan);
            pThis->GetDlgItem(IDC_STATIC_BACK_STATE)->ShowWindow(SW_HIDE);
            break;
        }
        else if (dwState == 400)
        {
            g_StringLanType(szLan, "�����쳣", "backup exception");
            pThis->GetDlgItem(IDC_STATIC_BACK_STATE)->SetWindowText(szLan);
            g_StringLanType(szLan, "��־����", "Backup");
            pThis->GetDlgItem(IDC_BTN_BACKUP_LOG)->SetWindowText(szLan);
            pThis->GetDlgItem(IDC_STATIC_BACK_STATE)->ShowWindow(SW_HIDE);
            break;
        }
        else if (dwState == 500)
        {
            g_StringLanType(szLan, "����ʧ��", "Failed to backup");
            pThis->GetDlgItem(IDC_STATIC_BACK_STATE)->SetWindowText(szLan);
            g_StringLanType(szLan, "��־����", "Backup");
            pThis->GetDlgItem(IDC_BTN_BACKUP_LOG)->SetWindowText(szLan);
            pThis->GetDlgItem(IDC_STATIC_BACK_STATE)->ShowWindow(SW_HIDE);
            break;
        }
		//����ֵ
        else if (dwState >= 0 && dwState < 100)
        {
            char szLanCn[128] = {0};
            char szLanEn[128] = {0};
            sprintf(szLanCn, "���ڱ���[%d]", dwState);
            sprintf(szLanEn, "backuping[%d]", dwState);
            g_StringLanType(szLan, szLanCn, szLanCn);
            pThis->GetDlgItem(IDC_STATIC_BACK_STATE)->SetWindowText(szLan);
        }
		//�м����
		else if(dwState == BACKUP_SEARCH_DEVICE)
		{
            g_StringLanType(szLan, "�������������豸", "searching backup device");
            pThis->GetDlgItem(IDC_STATIC_BACK_STATE)->SetWindowText(szLan);
		}
		else if(dwState ==  BACKUP_SEARCH_LOG_FILE)
		{
            g_StringLanType(szLan, "����������־", "searching log files");
            pThis->GetDlgItem(IDC_STATIC_BACK_STATE)->SetWindowText(szLan);
		}
		//����ֵ
		else if(dwState >= BACKUP_TIME_SEG_NO_FILE)
		{
            char szLanCn[128] = {0};
            char szLanEn[128] = {0};
            sprintf(szLanCn, "����ʧ��, ����ֵ[%d]", dwState);
            sprintf(szLanEn, "Backup failed, ErrorCode[%d]", dwState);
			g_StringLanType(szLan, szLanCn, szLanEn);
            pThis->GetDlgItem(IDC_STATIC_BACK_STATE)->SetWindowText(szLan);
			
            g_StringLanType(szLan, "��־����", "Backup");
            pThis->GetDlgItem(IDC_BTN_BACKUP_LOG)->SetWindowText(szLan);
            pThis->GetDlgItem(IDC_STATIC_BACK_STATE)->ShowWindow(SW_HIDE);
            break;
		}
		else if(dwState ==  BACKUP_CHANGE_DEVICE)
		{
			g_StringLanType(szLan, "�����豸����, ������豸��������", "Device of backup is full, change another device and continue backuping");
			pThis->GetDlgItem(IDC_STATIC_BACK_STATE)->SetWindowText(szLan);
			g_StringLanType(szLan, "����", "Backup");
			pThis->GetDlgItem(IDC_BTN_BACKUP_LOG)->SetWindowText(szLan);
			pThis->m_bBackuping = FALSE;
			break;
		}
		
        Sleep(100);
    }

	Sleep(2000);
	if (!NET_DVR_StopBackup(pThis->m_lBackupHandle))
	{
		g_pMainDlg->AddLog(pThis->m_dwDevIndex, OPERATION_FAIL_T, "NET_DVR_GetBackupProgress");
	}
	pThis->m_lBackupHandle = -1;
	pThis->m_bBackuping = FALSE;

    CloseHandle(pThis->m_hBackupThread);
    pThis->m_hBackupThread = NULL;
	
    return 0;
}

void CDlgHardDiskCfg::OnBtnBackupLog() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	char szLan[256] = {0};
	if (!m_bBackuping)
    {
		memset(&m_struBackupLogParam, 0, sizeof(m_struBackupLogParam));

		CString csDiskDesc = "";
		char szLan[128] = {0};
		if (m_cmbDiskList.GetCurSel() != CB_ERR)
		{
			m_cmbDiskList.GetLBText(m_cmbDiskList.GetCurSel(), csDiskDesc);
		}
		else
		{
			g_StringLanType(szLan, "��ѡ����̱����б�", "Please select backup disk");
			AfxMessageBox(szLan);
			return;
		}
		
		m_struBackupLogParam.dwSize = sizeof(m_struBackupLogParam);
		
		strncpy((char*)(m_struBackupLogParam.byDiskDesc), (char*)csDiskDesc.GetBuffer(0), sizeof(m_struBackupLogParam.byDiskDesc));
		m_struBackupLogParam.byContinue = m_bContinueBackup;
		
		int iItemCount = 0;
		int iIndex = 0;
		POSITION pos = m_listDisk.GetFirstSelectedItemPosition();

		while ((pos != NULL) && (iItemCount < ARRAY_SIZE(m_struBackupLogParam.byHardDisk)))
		{
			iIndex = m_listDisk.GetNextSelectedItem(pos);

			m_struBackupLogParam.byHardDisk[iItemCount] = atoi(m_listDisk.GetItemText(iIndex, 0).GetBuffer(0));
			
			iItemCount++;
		}
		m_struBackupLogParam.byBackupHardDiskNum = iItemCount; 


		m_lBackupHandle = NET_DVR_Backup(m_lLoginID, BACKUP_LOG, &m_struBackupLogParam, sizeof(m_struBackupLogParam));
		
		if (m_lBackupHandle == -1)
		{
			g_pMainDlg->AddLog(m_dwDevIndex, OPERATION_FAIL_T, "NET_DVR_Backup");
			return;
		}
		else
		{
			g_pMainDlg->AddLog(m_dwDevIndex, OPERATION_SUCC_T, "NET_DVR_Backup");
		} 
        
        DWORD dwThreadId = 0;
        if (m_hBackupThread == NULL)
        {
            m_hBackupThread = CreateThread(NULL,0,LPTHREAD_START_ROUTINE(GetBackupLogThread),this,0,&dwThreadId);		
        }
        if (m_hBackupThread  == NULL)
        {
            char szLan[256] = {0};
            g_StringLanType(szLan, "�򿪱����߳�ʧ��!", "Fail to open backup thread!");
            AfxMessageBox(szLan);
            return;
        }
        g_StringLanType(szLan, "ֹͣ����", "Stop Bakcup");
        GetDlgItem(IDC_BTN_BACKUP_LOG)->SetWindowText(szLan);
        m_bBackuping = TRUE;
        GetDlgItem(IDC_STATIC_BACK_STATE)->ShowWindow(SW_SHOW);
    }
    else
    {
        if (m_hBackupThread)
        {
            TerminateThread(m_hBackupThread, 0);
        }
		
        CloseHandle(m_hBackupThread);
        m_hBackupThread = NULL;
        NET_DVR_StopBackup(m_lBackupHandle);
        g_StringLanType(szLan, "��־����", "Backup");
        GetDlgItem(IDC_BTN_BACKUP_LOG)->SetWindowText(szLan);
        m_bBackuping = FALSE;
        GetDlgItem(IDC_STATIC_BACK_STATE)->ShowWindow(SW_HIDE);
    }
}

void CDlgHardDiskCfg::OnSelchangeComboDiskList() 
{
	// TODO: Add your control notification handler code here

	DWORD dwDiskFreeSpace = m_struDiskList.struDescNode[m_cmbDiskList.GetCurSel()].dwFreeSpace;
    char szLanCn[256] = {0};
    char szLanEn[256] = {0};
    char szLan[256] = {0};
    sprintf(szLanCn, "ʣ����̿ռ�%dM", dwDiskFreeSpace);
    sprintf(szLanEn, "Free Disk Spcace%dM", dwDiskFreeSpace);
    g_StringLanType(szLan, szLanCn, szLanEn);
    GetDlgItem(IDC_STATIC_BACKUP_DISK_SIZE)->ShowWindow(SW_SHOW);
    GetDlgItem(IDC_STATIC_BACKUP_DISK_SIZE)->SetWindowText(szLan);
}

void CDlgHardDiskCfg::OnBtnDelHd() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	NET_DVR_INVALID_DISK_PARAM struInvalidDiskParam;
	memset(&struInvalidDiskParam, 0, sizeof(NET_DVR_INVALID_DISK_PARAM));
	struInvalidDiskParam.struStructHead.wLength = sizeof(NET_DVR_INVALID_DISK_PARAM);
	struInvalidDiskParam.byDelAll = m_bDelAllInvalidDisk;
	struInvalidDiskParam.dwDiskNo = m_iSelHDNum;

	if (!NET_DVR_RemoteControl(m_lLoginID, NET_DVR_DEL_INVALID_DISK, &struInvalidDiskParam, sizeof(struInvalidDiskParam)))
	{
		g_pMainDlg->AddLog(m_dwDevIndex, OPERATION_FAIL_T, "NET_DVR_RemoteControl NET_DVR_DEL_INVALID_DISK ");
	}
	else
	{
		g_pMainDlg->AddLog(m_dwDevIndex, OPERATION_SUCC_T, "NET_DVR_RemoteControl NET_DVR_DEL_INVALID_DISK");
	}
	

}

void CDlgHardDiskCfg::OnBtnUnmount() 
{
	// TODO: Add your control notification handler code here
	NET_DVR_MOUNT_DISK_PARAM struMountDisk;
	memset(&struMountDisk, 0, sizeof(NET_DVR_MOUNT_DISK_PARAM));
	struMountDisk.struStructHead.wLength = sizeof(NET_DVR_MOUNT_DISK_PARAM);
	struMountDisk.dwDiskNo = m_iSelHDNum;
	
// 	//ʹ�ó����ӽ��в�������
// 	m_lRemoteUnmountHandle = NET_DVR_StartRemoteConfig(m_lLoginID,NET_DVR_UNMOUNT_DISK,&struMountDisk,sizeof(struMountDisk),NULL,this);
// 	if (m_lRemoteUnmountHandle < 0)
// 	{
// 		g_pMainDlg->AddLog(m_dwDevIndex, OPERATION_FAIL_T, "NET_DVR_RemoteControl NET_DVR_UNMOUNT_DISK ");
// 	}
	if (!NET_DVR_RemoteControl(m_lLoginID, NET_DVR_UNMOUNT_DISK, &struMountDisk, sizeof(struMountDisk)))
	{
		g_pMainDlg->AddLog(m_dwDevIndex, OPERATION_FAIL_T, "NET_DVR_RemoteControl NET_DVR_UNMOUNT_DISK ");
	}
	else
	{
		g_pMainDlg->AddLog(m_dwDevIndex, OPERATION_SUCC_T, "NET_DVR_RemoteControl NET_DVR_UNMOUNT_DISK ");
// 		m_timerHandle =	SetTimer(UNMOUNT_TIMER, 50, NULL);
// 		//����֤���ļ�ֻ�м�KB����С���ʶ���sleep�������ϴ����
//  		Sleep(500);
	}
}

void CDlgHardDiskCfg::OnBtnMount() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	CString strDiskNo;
	m_comboDisk.GetWindowText(strDiskNo);


	NET_DVR_MOUNT_DISK_PARAM struMountDisk;
	memset(&struMountDisk, 0, sizeof(NET_DVR_MOUNT_DISK_PARAM));
	struMountDisk.struStructHead.wLength = sizeof(NET_DVR_MOUNT_DISK_PARAM);
	struMountDisk.dwDiskNo = atoi(strDiskNo);

	if (!NET_DVR_RemoteControl(m_lLoginID, NET_DVR_MOUNT_DISK, &struMountDisk, sizeof(struMountDisk)))
	{
		g_pMainDlg->AddLog(m_dwDevIndex, OPERATION_FAIL_T, "NET_DVR_RemoteControl NET_DVR_MOUNT_DISK ");
	}
	else
	{
		g_pMainDlg->AddLog(m_dwDevIndex, OPERATION_SUCC_T, "NET_DVR_RemoteControl NET_DVR_MOUNT_DISK ");
	}
}
