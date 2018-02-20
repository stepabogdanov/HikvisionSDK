// JPEGPicDownload.cpp : implementation file
//

#include "stdafx.h"
#include "ClientDemo.h"
#include "JPEGPicDownload.h"
#include "Picture.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CJPEGPicDownload *g_pDlgRemoteFile;

/////////////////////////////////////////////////////////////////////////////
// CJPEGPicDownload dialog
// extern	SERVER_INFO serverinfo[MAXIPNUMBER];
// extern	CLIENTPARAM	ClientParam;
// extern	LOCAL_PARAM ClientParam;
// LOCAL_PARAM
CPicture *picture = NULL;

LONG lNumber = 0;

UINT GetPicThread(LPVOID pParam)
{
	CJPEGPicDownload *GetPic = (CJPEGPicDownload *)pParam;
	CString csFileName;
	CString csPicTime;
	CString csCardNum;
	CString csTemp,csDir;
	char nFileName[256] = {0};
	char sMessageCn[256] = {0};
	char sMessageEn[256] = {0};
	int fileselpos = 0;
	
	char szLan[256] = {0};

	while (GetPic->pos)
	{
		if (!GetPic->m_bDown)
		{			
			break;	
		}
		fileselpos = GetPic->m_PicList.GetNextSelectedItem(GetPic->pos);
		csFileName.Format("%s",GetPic->m_PicList.GetItemText(fileselpos,0));
		if (csFileName.IsEmpty())
		{
			g_StringLanType(szLan, "����", "Download");
			GetPic->GetDlgItem(IDC_DOWNLOAD)->SetWindowText(szLan);
			GetPic->GetDlgItem(IDC_STATICSTATE2)->ShowWindow(SW_HIDE);
			GetPic->m_downProgress.SetPos(0);
			GetPic->m_bDown = FALSE;
			CloseHandle(GetPic->m_hGetThread);
			GetPic->m_hGetThread = NULL;
			g_StringLanType(szLan, "�ļ���Ϊ��!", "File name is blank!");
			AfxMessageBox(szLan);
			return 1;
		}
			
		csPicTime.Format("%s", GetPic->m_PicList.GetItemText(fileselpos,2));
		csCardNum.Format("%s", GetPic->m_PicList.GetItemText(fileselpos,3));
		sprintf(GetPic->filenamedownload, "%s", csFileName);
		
		csDir.Format("%s\\", g_struLocalParam.chPictureSavePath);
		
		sprintf(nFileName, "%s%s_%02d_D%s_%s_%d.jpg",csDir, g_struDeviceInfo[GetPic->m_iDeviceIndex].chDeviceIP, GetPic->m_iChannel, csPicTime,csCardNum, fileselpos + 1);
		
    	if (NET_DVR_GetPicture(GetPic->m_lServerID, GetPic->filenamedownload, nFileName))
		{			
     		Sleep(10);
			GetPic->nDownPics++;
			GetPic->m_downProgress.SetPos(GetPic->nDownPics*100/GetPic->nSelPics);
		}
	}
	
	GetPic->m_downProgress.SetPos(0);
	g_StringLanType(szLan, "����", "Download");
	GetPic->GetDlgItem(IDC_DOWNLOAD)->SetWindowText(szLan);
	GetPic->GetDlgItem(IDC_STATICSTATE2)->ShowWindow(SW_HIDE);
	GetPic->m_bDown = FALSE;
	CloseHandle(GetPic->m_hGetThread);
	GetPic->m_hGetThread = NULL;
	sprintf(sMessageCn, "ѡ���� %d ��ͼƬ,������ %d ��ͼƬ", GetPic->nSelPics, GetPic->nDownPics);
	sprintf(sMessageEn, "selected %d picture��downloaded %d picture", GetPic->nSelPics, GetPic->nDownPics);
	g_StringLanType(szLan, sMessageCn, sMessageEn);
	AfxMessageBox(szLan);	
	GetPic->nSelPics = 0;
	GetPic->nDownPics = 0;	
	return 0;
}


UINT SearchPicThread(LPVOID pParam)
{
	CJPEGPicDownload *RPic = (CJPEGPicDownload *)pParam;
	LONG bRet = -1;
	NET_DVR_FIND_PICTURE strFileInfo;
	CString tempstring;
	char tempfile[100];

    char szLan[256] = {0};
	
	while (1)
	{	
		if (!RPic->m_bSearchDown)
		{
			return 0;	
		}
		bRet = NET_DVR_FindNextPicture(RPic->m_lFileHandle, &strFileInfo);
		if (bRet == NET_DVR_FILE_SUCCESS)
		{			
			strcpy(tempfile,strFileInfo.sFileName);
			RPic->m_PicList.InsertItem(RPic->m_iFileNum,tempfile,0);	
			
			tempstring.Format("%d",strFileInfo.dwFileSize);
			RPic->m_PicList.SetItemText(RPic->m_iFileNum,1,tempstring);

			tempstring.Format("%04d%02d%02d%02d%02d%02d",strFileInfo.struTime.dwYear, strFileInfo.struTime.dwMonth,strFileInfo.struTime.dwDay,strFileInfo.struTime.dwHour,strFileInfo.struTime.dwMinute,strFileInfo.struTime.dwSecond);
			RPic->m_PicList.SetItemText(RPic->m_iFileNum,2,tempstring);

			tempstring.Format("%s",strFileInfo.sCardNum);
			RPic->m_PicList.SetItemText(RPic->m_iFileNum,3,tempstring);

			RPic->m_iFileNum++;
			TRACE("m_iFileNum is %d\n", RPic->m_iFileNum);
		}
		else
		{
			if (bRet == NET_DVR_ISFINDING)
			{
				Sleep(5);
				continue;
			}
			if ( (bRet == NET_DVR_NOMOREFILE) || (bRet == NET_DVR_FILE_NOFIND) )
			{
				g_StringLanType(szLan, "����", "search");
				RPic->GetDlgItem(IDC_SEARCHLIST)->SetWindowText(szLan);
				RPic->m_bSearchDown = FALSE;
				(RPic->GetDlgItem(IDC_STATICSTATE))->ShowWindow(SW_HIDE);
				g_StringLanType(szLan, "���ҵ�ͼƬ��:", "Searched picture sum:");
				tempstring.Format("%s%d", szLan, RPic->m_iFileNum);
				AfxMessageBox(tempstring);
				RPic->m_iFileNum = 0;
				break;
			}
			else
			{
				g_StringLanType(szLan, "����", "search");
				RPic->GetDlgItem(IDC_SEARCHLIST)->SetWindowText(szLan);
				RPic->m_bSearchDown = FALSE;
				(RPic->GetDlgItem(IDC_STATICSTATE))->ShowWindow(SW_HIDE);
				AfxMessageBox("exception end!");
				break;
			}
		}
	}
	CloseHandle(RPic->m_hFileThread);
	RPic->m_hFileThread = NULL;
	NET_DVR_CloseFindPicture(RPic->m_lFileHandle);
	
	return 0;
}

DWORD  GetBackupPicThread(LPVOID pParam)
{
     CJPEGPicDownload *pDlgRemotPlay = ( CJPEGPicDownload*)pParam;
    pDlgRemotPlay->GetDlgItem(IDC_STATIC_BACK_STATE)->ShowWindow(SW_SHOW);
    DWORD dwState = 0;
    char szLan[256] = {0};
    while (1)
    {
		if (!NET_DVR_GetBackupProgress(pDlgRemotPlay->m_lBackupHandle, &dwState))
        {
			DWORD dwErr = NET_DVR_GetLastError();
			//may be successful too quick
			g_StringLanType(szLan, "�������", "Succ to backup");
			pDlgRemotPlay->GetDlgItem(IDC_STATIC_BACK_STATE)->SetWindowText(szLan);
			g_StringLanType(szLan, "ͼƬ����", "Backup");
			pDlgRemotPlay->GetDlgItem(IDC_BTN_BACKUP)->SetWindowText(szLan);
			pDlgRemotPlay->GetDlgItem(IDC_STATIC_BACK_STATE)->ShowWindow(SW_HIDE);
			g_pMainDlg->AddLog(pDlgRemotPlay->m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GetBackupProgress");	
			
			break;
        }
		g_pMainDlg->AddLog(pDlgRemotPlay->m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GetBackupProgress [%d]", dwState);	


		if (dwState == 100)
        {
            g_StringLanType(szLan, "�������", "Succ to backup");
            pDlgRemotPlay->GetDlgItem(IDC_STATIC_BACK_STATE)->SetWindowText(szLan);
            g_StringLanType(szLan, "ͼƬ����", "Backup");
            pDlgRemotPlay->GetDlgItem(IDC_BTN_BACKUP)->SetWindowText(szLan);
            pDlgRemotPlay->GetDlgItem(IDC_STATIC_BACK_STATE)->ShowWindow(SW_HIDE);
            break;
        }
        else if (dwState == 400)
        {
            g_StringLanType(szLan, "�����쳣", "backup exception");
            pDlgRemotPlay->GetDlgItem(IDC_STATIC_BACK_STATE)->SetWindowText(szLan);
            g_StringLanType(szLan, "ͼƬ����", "Backup");
            pDlgRemotPlay->GetDlgItem(IDC_BTN_BACKUP)->SetWindowText(szLan);
            pDlgRemotPlay->GetDlgItem(IDC_STATIC_BACK_STATE)->ShowWindow(SW_HIDE);
            break;
        }
        else if (dwState == 500)
        {
            g_StringLanType(szLan, "����ʧ��", "Failed to backup");
            pDlgRemotPlay->GetDlgItem(IDC_STATIC_BACK_STATE)->SetWindowText(szLan);
            g_StringLanType(szLan, "ͼƬ����", "Backup");
            pDlgRemotPlay->GetDlgItem(IDC_BTN_BACKUP)->SetWindowText(szLan);
            pDlgRemotPlay->GetDlgItem(IDC_STATIC_BACK_STATE)->ShowWindow(SW_HIDE);
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
            pDlgRemotPlay->GetDlgItem(IDC_STATIC_BACK_STATE)->SetWindowText(szLan);
        }
		//�м����
		else if(dwState == BACKUP_SEARCH_DEVICE)
		{
            g_StringLanType(szLan, "�������������豸", "searching backup device");
            pDlgRemotPlay->GetDlgItem(IDC_STATIC_BACK_STATE)->SetWindowText(szLan);
		}
		else if(dwState == BACKUP_SEARCH_FILE)
		{
            g_StringLanType(szLan, "��������ͼƬ", "searching picture files");
            pDlgRemotPlay->GetDlgItem(IDC_STATIC_BACK_STATE)->SetWindowText(szLan);
		}
		//����ֵ
		else if(dwState >= BACKUP_TIME_SEG_NO_FILE)
		{
            char szLanCn[128] = {0};
            char szLanEn[128] = {0};
            sprintf(szLanCn, "����ʧ��, ����ֵ[%d]", dwState);
            sprintf(szLanEn, "Backup failed, ErrorCode[%d]", dwState);
			g_StringLanType(szLan, szLanCn, szLanEn);
            pDlgRemotPlay->GetDlgItem(IDC_STATIC_BACK_STATE)->SetWindowText(szLan);
			
            g_StringLanType(szLan, "ͼƬ����", "Backup");
            pDlgRemotPlay->GetDlgItem(IDC_BTN_BACKUP)->SetWindowText(szLan);
            pDlgRemotPlay->GetDlgItem(IDC_STATIC_BACK_STATE)->ShowWindow(SW_HIDE);
            break;
		}
		else if(dwState ==  BACKUP_CHANGE_DEVICE)
		{
			g_StringLanType(szLan, "�����豸����, ������豸��������", "Device of backup is full, change another device and continue backuping");
			pDlgRemotPlay->GetDlgItem(IDC_STATIC_BACK_STATE)->SetWindowText(szLan);
			g_StringLanType(szLan, "����", "Backup");
			pDlgRemotPlay->GetDlgItem(IDC_BTN_BACKUP)->SetWindowText(szLan);
			pDlgRemotPlay->m_bBackuping = FALSE;
			break;
		}
		
        Sleep(100);
    }

	Sleep(2000);
	if (!NET_DVR_StopBackup(pDlgRemotPlay->m_lBackupHandle))
	{
		g_pMainDlg->AddLog(pDlgRemotPlay->m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GetBackupProgress");
	}
	pDlgRemotPlay->m_lBackupHandle = -1;
	pDlgRemotPlay->m_bBackuping = FALSE;

    CloseHandle(g_pDlgRemoteFile->m_hBackupThread);
    g_pDlgRemoteFile->m_hBackupThread = NULL;
	
    return 0;
}


CJPEGPicDownload::CJPEGPicDownload(CWnd* pParent /*=NULL*/)
	: CDialog(CJPEGPicDownload::IDD, pParent)
{
	//{{AFX_DATA_INIT(CJPEGPicDownload)
	m_sCardNum = _T("");
	m_bChkCard = FALSE;
	m_ctDateStart = 0;
	m_ctDateStop = 0;
	m_ctTimeStart = 0;
	m_ctTimeStop = 0;
	m_bContinue = FALSE;
	//}}AFX_DATA_INIT
    m_lBackupHandle = -1;
	m_bBackuping = FALSE;
	m_hBackupThread = NULL;
    memset(&m_struFindPictureParam, 0, sizeof(m_struFindPictureParam));
    memset(&m_struDiskList, 0, sizeof(m_struDiskList));
}


void CJPEGPicDownload::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CJPEGPicDownload)
	DDX_Control(pDX, IDC_COMBO_DISK_LIST, m_comboDiskList);
	DDX_Control(pDX, IDC_SHOWJPEG, m_ShowJpegCtrl);
	DDX_Control(pDX, IDC_DOWNPROGRESS, m_downProgress);
	DDX_Control(pDX, IDC_REMOTEPICLIST, m_PicList);
	DDX_Control(pDX, IDC_PICTYPE, m_PicTypeCtrl);
	DDX_Control(pDX, IDC_COMBOPORT, m_ChannelCtrl);
	DDX_Text(pDX, IDC_CARDNUM, m_sCardNum);
	DDX_Check(pDX, IDC_CHECKCARD, m_bChkCard);
	DDX_DateTimeCtrl(pDX, IDC_DATESTART, m_ctDateStart);
	DDX_DateTimeCtrl(pDX, IDC_DATESTOP, m_ctDateStop);
	DDX_DateTimeCtrl(pDX, IDC_TIMESTART, m_ctTimeStart);
	DDX_DateTimeCtrl(pDX, IDC_TIMESTOP, m_ctTimeStop);
	DDX_Check(pDX, IDC_CHK_CONTINUE_BACKUP, m_bContinue);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CJPEGPicDownload, CDialog)
	//{{AFX_MSG_MAP(CJPEGPicDownload)
	ON_BN_CLICKED(IDC_SEARCHLIST, OnSearchlist)
	ON_BN_CLICKED(IDC_DOWNLOAD, OnDownload)
	ON_BN_CLICKED(IDC_CHECKCARD, OnCheckcard)
	ON_NOTIFY(NM_CLICK, IDC_REMOTEPICLIST, OnClickRemotepiclist)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BTN_BACKUP, OnBtnBackup)
	ON_CBN_SELCHANGE(IDC_COMBO_DISK_LIST, OnSelchangeComboDiskList)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CJPEGPicDownload message handlers

void CJPEGPicDownload::OnOK() 
{
	// TODO: Add extra validation here
	
	//CDialog::OnOK();
}

void CJPEGPicDownload::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	//CDialog::OnCancel();
}

BOOL CJPEGPicDownload::OnInitDialog() 
{
	CDialog::OnInitDialog();
	CRect rc(0, 0, 0, 0);
	GetParent()->GetClientRect(&rc);
	((CTabCtrl*)GetParent())->AdjustRect(FALSE, &rc);
	MoveWindow(&rc);
	
	// TODO: Add extra initialization here
	g_pDlgRemoteFile = this;
	
	picture = NULL;
	m_bDown = FALSE;
	m_hFileThread = NULL;
	m_hGetThread = NULL;
	m_iFileNum = 0;
	m_lFileHandle = 0;
	nSelPics = 0;
	nDownPics = 0;
	m_lServerID = -1;
	m_bSearchDown = FALSE;
	m_downProgress.SetRange(0,100);
	m_downProgress.SetPos(0);

	m_ChannelCtrl.SetCurSel(1);
	m_iChannel = 0;
	m_PicList.SetExtendedStyle(m_PicList.GetExtendedStyle()|LVS_EX_FULLROWSELECT); 

	char szLan[128] = {0};

	g_StringLanType(szLan, "ͼƬ����", "pic name");
	m_PicList.InsertColumn(0,szLan,LVCFMT_LEFT,140,-1);

	g_StringLanType(szLan, "ͼƬ��С", "pic size");
	m_PicList.InsertColumn(1,szLan,LVCFMT_LEFT,60,-1);

	g_StringLanType(szLan, "ͼƬʱ��", "pic time");
	m_PicList.InsertColumn(2,szLan,LVCFMT_LEFT,110,-1);

	g_StringLanType(szLan, "����", "card num");
	m_PicList.InsertColumn(3,szLan,LVCFMT_LEFT,80,-1);
	
	CTime time1 = CTime::GetCurrentTime();
	CTime time(time1.GetYear(),time1.GetMonth(),time1.GetDay(),0,0,0);
	CTime time0(time1.GetYear(),time1.GetMonth(),time1.GetDay(),23,59,59);
	m_ctDateStart = time;
	m_ctTimeStart = time;
	m_ctDateStop = time;
	m_ctTimeStop = time0;
	m_lStartChan = 0;	
	
	m_PicTypeCtrl.ResetContent();

	g_StringLanType(szLan, "ȫ��", "All");
	m_PicTypeCtrl.AddString(szLan);
	m_PicTypeCtrl.SetItemData(0, 0xff);

	g_StringLanType(szLan, "��ʱץͼ", "Schedule");
	m_PicTypeCtrl.AddString(szLan);
	m_PicTypeCtrl.SetItemData(1, 0);

	g_StringLanType(szLan, "�ƶ����", "Motion Detect");
	m_PicTypeCtrl.AddString(szLan);
	m_PicTypeCtrl.SetItemData(2, 1);

	g_StringLanType(szLan, "��������", "Alarm");
	m_PicTypeCtrl.AddString(szLan);
	m_PicTypeCtrl.SetItemData(3, 2);

	g_StringLanType(szLan, "����|����", "Alarm|Motion");
	m_PicTypeCtrl.AddString(szLan);
	m_PicTypeCtrl.SetItemData(4, 3);

	g_StringLanType(szLan, "����&����", "Alarm&Motion");
	m_PicTypeCtrl.AddString(szLan);
	m_PicTypeCtrl.SetItemData(5, 4);

	g_StringLanType(szLan, "�ֶ�ץͼ", "Manual Capture");
	m_PicTypeCtrl.AddString(szLan);
	m_PicTypeCtrl.SetItemData(6, 6);

	g_StringLanType(szLan, "PIR����", "PIR Alarm");
	m_PicTypeCtrl.AddString(szLan);
	m_PicTypeCtrl.SetItemData(7, 10);

	g_StringLanType(szLan, "���߱���", "Wireless alarm");
	m_PicTypeCtrl.AddString(szLan);
	m_PicTypeCtrl.SetItemData(8, 11);

	g_StringLanType(szLan, "���ȱ���", "Call help alarm");
	m_PicTypeCtrl.AddString(szLan);
	m_PicTypeCtrl.SetItemData(9, 12);

	g_StringLanType(szLan, "Ԥ��ʱ��ͼ", "Preview capture");
	m_PicTypeCtrl.AddString(szLan);
	m_PicTypeCtrl.SetItemData(10, 0xa);

	m_PicTypeCtrl.SetCurSel(0);
		
    UpdateData(FALSE); 
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


BOOL CJPEGPicDownload::GetDiskList(NET_DVR_DISKABILITY_LIST &struDiskList)
{
    if (!NET_DVR_GetDiskList(m_lServerID, &struDiskList))
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GetDiskList");
        return FALSE;
    }
    else
    {
        g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_GetDiskList");
        return TRUE;
    }
}

void CJPEGPicDownload::OnSearchlist() 
{
	// TODO: Add your control notification handler code here
	char szLan[128] = {0};

	UpdateData(TRUE);
	if (m_lServerID == -1)
	{
		g_StringLanType(szLan, "��ѡ�������", "Please select server!");
		AfxMessageBox(szLan);
		return;
	}
	if (!m_bSearchDown)
	{
		m_iChannel = m_ChannelCtrl.GetCurSel()+m_lStartChan;
        GetFindPictureParamFromWnd(m_struFindPictureParam);

        m_lFileHandle = NET_DVR_FindPicture(m_lServerID, &m_struFindPictureParam);

		if (m_lFileHandle < 0)
		{
			g_StringLanType(szLan, "��ȡͼƬ�б�ʧ��", "Get picture list failed!");
			AfxMessageBox(szLan);
			return;
		}
		m_PicList.DeleteAllItems();
		m_iFileNum = 0;
		DWORD dwThreadId;
		if (m_hFileThread == NULL)
			m_hFileThread = CreateThread(NULL,0,LPTHREAD_START_ROUTINE(SearchPicThread),this,0,&dwThreadId);
		if (m_hFileThread == NULL)
		{
			g_StringLanType(szLan, "�����߳�ʧ��", "Open thread failed!");
			AfxMessageBox(szLan);
			return;
		}
		m_bSearchDown = TRUE;
		g_StringLanType(szLan, "ֹͣ����", "Stop search");
		GetDlgItem(IDC_SEARCHLIST)->SetWindowText(szLan);		
		GetDlgItem(IDC_STATICSTATE)->ShowWindow(SW_SHOW);
	}
	else
	{		
		m_bSearchDown = FALSE;
		if (m_lFileHandle != -1)
		{
			NET_DVR_CloseFindPicture(m_lFileHandle);
		}	
		CloseHandle(m_hFileThread);
		m_hFileThread = NULL;
		g_StringLanType(szLan, "����", "Search");
		GetDlgItem(IDC_SEARCHLIST)->SetWindowText(szLan);	
		GetDlgItem(IDC_STATICSTATE)->ShowWindow(SW_HIDE);
		g_StringLanType(szLan, "������ͼƬ��Ŀ:", "Search picture sum:");
		CString tempstring;
		tempstring.Format("%s[%d]", szLan, m_iFileNum);		
		AfxMessageBox(tempstring);
		m_iFileNum = 0;
	}
}

void CJPEGPicDownload::OnDownload() 
{
	UpdateData(TRUE);
	char szLan[128] = {0};

	if (!m_bDown)
	{
		pos = m_PicList.GetFirstSelectedItemPosition();
		if (pos == NULL)
		{
			g_StringLanType(szLan, "��ѡ���ļ�!", "Please select the file!");
			AfxMessageBox(szLan);
			return;
		}
		m_bDown = TRUE;
		nSelPics = m_PicList.GetSelectedCount();
		nDownPics = 0;

		DWORD dwThreadId;
		if (!m_hGetThread)
		{
			m_hGetThread = CreateThread(NULL,0,LPTHREAD_START_ROUTINE(GetPicThread),this,0,&dwThreadId);
		}
		else
		{
			TerminateThread(m_hGetThread, 0);
			m_hGetThread = CreateThread(NULL,0,LPTHREAD_START_ROUTINE(GetPicThread),this,0,&dwThreadId);
		}
		GetDlgItem(IDC_DOWNLOAD)->SetWindowText("Stop download");
		GetDlgItem(IDC_STATICSTATE2)->ShowWindow(SW_SHOW);
	}
	else
	{
		if (!m_hGetThread)
		{
			g_StringLanType(szLan, "��ѡ���ļ�!", "Please select the file!");
			AfxMessageBox(szLan);
			return;
		}
		m_bDown = FALSE;
	}
	UpdateData(FALSE);
}

void CJPEGPicDownload::OnCheckcard() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	if (m_bChkCard)
	{
		GetDlgItem(IDC_CARDNUM)->EnableWindow(TRUE);
	}
	else
	{
		GetDlgItem(IDC_CARDNUM)->EnableWindow(FALSE);	
	}
	UpdateData(FALSE);	
}

void CJPEGPicDownload::OnClickRemotepiclist(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	POSITION tempPos;
	tempPos = m_PicList.GetFirstSelectedItemPosition();
	if (tempPos == NULL)
	{
		return;
	}
	CString csFileName;
	CString csPicTime;
	CString csCardNum;
	CString csTemp,csDir;
	char nFileName[256];
	CString csMessage;
	int fileselpos = 0;

	fileselpos = m_PicList.GetNextSelectedItem(tempPos);
	csFileName.Format("%s",m_PicList.GetItemText(fileselpos,0));
	if (csFileName.IsEmpty())
	{
		return;
	}
	csPicTime.Format("%s", m_PicList.GetItemText(fileselpos,2));
	csCardNum.Format("%s", m_PicList.GetItemText(fileselpos,3));
	sprintf(filenamedownload, "%s", csFileName);
	csDir.Format("%s\\", g_struLocalParam.chDownLoadPath);
	sprintf(nFileName, "%s%s_%02d_D%s_%sjpg",csDir, g_struDeviceInfo[m_iDeviceIndex].chDeviceIP, m_iChannel, csPicTime, csCardNum);
	if(!NET_DVR_GetPicture(m_lServerID, filenamedownload, nFileName))
	{
       g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_GetPicture");
	 	*pResult = 0;
	   return;
	}
	
	CRect rc;
	CDC* pDC = m_ShowJpegCtrl.GetDC();
	m_ShowJpegCtrl.GetClientRect(&rc);
	pDC->SetViewportOrg(rc.left, rc.top);
	rc.bottom = -rc.bottom;	
	if (!picture)
	{
		picture = new CPicture;	
	}	
	picture->LoadPicture(nFileName, pDC->m_hDC, abs(rc.Width()), abs(rc.Height()));
	
    DeleteFile(nFileName);
	*pResult = 0;
}

void CJPEGPicDownload::F_Close()
{
	if (m_hGetThread)
	{
		TerminateThread(m_hGetThread, 0);	
		CloseHandle(m_hGetThread);
		m_hGetThread = NULL;
	}

	if (m_hFileThread)
	{
		TerminateThread(m_hFileThread, 0);
		CloseHandle(m_hFileThread);
		m_hFileThread = NULL;
	}

	if (picture)
	{
		picture->FreePicture();
		delete picture;
		picture = NULL;		
	}
}

void CJPEGPicDownload::OnDestroy() 
{
	CDialog::OnDestroy();
	
	// TODO: Add your message handler code here
	
}
/*********************************************************
Function:	CheckInitParam
Desc:		check device parameters and initialize dialog parameters
Input:	
Output:	
Return:	    TRUE,check correct, parameters initialized; FALSE,check error, not initialized;
**********************************************************/
BOOL CJPEGPicDownload::CheckInitParam()
{
	int iDeviceIndex = g_pMainDlg->GetCurDeviceIndex();
	if (iDeviceIndex == -1)
	{
		UpdateData(FALSE);
		return FALSE;
	}
	if ( m_iDeviceIndex == -1 || m_iDeviceIndex != iDeviceIndex)
	{
		// m_iChanIndex = -1;
	}
	int iChanIndex = g_pMainDlg->GetCurChanIndex();
	if (iChanIndex == -1)
	{
		iChanIndex = 0;
	}
	
	UpdateData(TRUE);
	char szLan[128] = {0};

	m_iDeviceIndex = iDeviceIndex;
	m_lServerID = g_struDeviceInfo[m_iDeviceIndex].lLoginID;
	int m_iChanNum = g_struDeviceInfo[m_iDeviceIndex].iDeviceChanNum;
	m_lServerType = g_struDeviceInfo[m_iDeviceIndex].iDeviceType;
	m_lStartChan = g_struDeviceInfo[m_iDeviceIndex].iStartChan;

    m_ChannelCtrl.ResetContent();
    CString sTemp;
    for (int i = 0; i < m_iChanNum; i++)
    {
        sTemp.Format("%d", i+m_lStartChan);
        m_ChannelCtrl.AddString(sTemp);
    }
    m_iChannel = 0;
    m_ChannelCtrl.SetCurSel(m_iChannel);
	
	if (m_lServerID < 0)
	{
		UpdateData(FALSE);
		return FALSE;
	}

	GetDiskList(m_struDiskList); 
    m_comboDiskList.ResetContent();
    for (int j = 0; j < m_struDiskList.dwNodeNum; j++)
    {
        m_comboDiskList.AddString((char*)m_struDiskList.struDescNode[j].byDescribe);
        m_comboDiskList.SetItemData(j, m_struDiskList.struDescNode[j].iValue);
    }
    m_comboDiskList.SetCurSel(0);
    OnSelchangeComboDiskList();

	UpdateData(FALSE); 
	return TRUE;
}
/*********************************************************
  Function:	SetParentWnd
  Desc:		transmit the handle of parent dialog box
  Input:	hhWnd, pointer to handle array
  Output:	
  Return:	
**********************************************************/
void CJPEGPicDownload::SetParentWnd(HWND *hhWnd, int iParentNum)
{
	VERIFY(iParentNum==2);
	m_hPareDlgWnd=hhWnd[0];
	m_hPareTabWnd=hhWnd[1];
}

void CJPEGPicDownload::GetFindPictureParamFromWnd(NET_DVR_FIND_PICTURE_PARAM &struPictureParam)
{
    //struPictureParam.lChannel = m_ChannelCtrl.GetCurSel()+m_lStartChan;
	int iChanIndex = g_pMainDlg->GetCurChanIndex();
    struPictureParam.lChannel = g_struDeviceInfo[m_iDeviceIndex].struChanInfo[iChanIndex].iChannelNO;

    struPictureParam.byFileType = m_PicTypeCtrl.GetItemData(m_PicTypeCtrl.GetCurSel());   

    struPictureParam.byNeedCard = m_bChkCard;
    strncpy((char*)struPictureParam.sCardNum, m_sCardNum.GetBuffer(0), sizeof(struPictureParam.sCardNum));
    struPictureParam.struStartTime.dwYear = (WORD)m_ctDateStart.GetYear();
    struPictureParam.struStartTime.dwMonth = (WORD)m_ctDateStart.GetMonth();
    struPictureParam.struStartTime.dwDay = (WORD)m_ctDateStart.GetDay();
    struPictureParam.struStartTime.dwHour = (char)m_ctTimeStart.GetHour();
    struPictureParam.struStartTime.dwMinute = (char)m_ctTimeStart.GetMinute();
    struPictureParam.struStartTime.dwSecond = (char)m_ctTimeStart.GetSecond();
    struPictureParam.struStopTime.dwYear = (WORD)m_ctDateStop.GetYear();
    struPictureParam.struStopTime.dwMonth = (WORD)m_ctDateStop.GetMonth();
    struPictureParam.struStopTime.dwDay = (WORD)m_ctDateStop.GetDay();
    struPictureParam.struStopTime.dwHour = (char)m_ctTimeStop.GetHour();
    struPictureParam.struStopTime.dwMinute = (char)m_ctTimeStop.GetMinute();
    struPictureParam.struStopTime.dwSecond = (char)m_ctTimeStop.GetSecond();
}

/******************************************
����:	ProcessFileSize
����:	
����:	
���:	
����ֵ: 
******************************************/
DWORD CJPEGPicDownload::ProcessFileSize(CString csFileSize)
{
    DWORD dwFileSize = 0;
    if (csFileSize[csFileSize.GetLength()-1] == 'M')
    {
        dwFileSize = atoi(csFileSize.GetBuffer(csFileSize.GetLength() - 1));
        dwFileSize *= (1024*1024);
    }
    else if (csFileSize[csFileSize.GetLength()-1] == 'K')
    {
        dwFileSize = atoi(csFileSize.GetBuffer(csFileSize.GetLength() - 1));
        dwFileSize *= 1024;
    }
    else
    {
        dwFileSize = atoi(csFileSize.GetBuffer(csFileSize.GetLength()));
    }
    return dwFileSize;
}

BOOL CJPEGPicDownload::GetBackupPictureParamFromWnd_FILE(NET_DVR_BACKUP_PICTURE_PARAM &struBackPicturParam)
{
	UpdateData(TRUE);

    CString csDiskDesc = "";
    char szLan[128] = {0};
    if (m_comboDiskList.GetCurSel() != CB_ERR)
    {
        m_comboDiskList.GetLBText(m_comboDiskList.GetCurSel(), csDiskDesc);
    }
    else
    {
        g_StringLanType(szLan, "��ѡ����̱����б�", "Please select backup disk");
        AfxMessageBox(szLan);
		return FALSE;
    }

	struBackPicturParam.dwSize = sizeof(struBackPicturParam);

    strncpy((char*)(struBackPicturParam.byDiskDes), (char*)csDiskDesc.GetBuffer(0), sizeof(struBackPicturParam.byDiskDes));
    struBackPicturParam.byContinue = m_bContinue;
    
    int iItemCount = 0;
    int iIndex = 0;
    POSITION pos = m_PicList.GetFirstSelectedItemPosition();
    CString csFileSize;
	CString csFileTime;
    while ((pos != NULL) && (iItemCount < ARRAY_SIZE(struBackPicturParam.struPicture)))
    {
        iIndex = m_PicList.GetNextSelectedItem(pos);
        sprintf(struBackPicturParam.struPicture[iItemCount].sFileName, "%s", m_PicList.GetItemText(iIndex, 0));

		csFileSize = m_PicList.GetItemText(iIndex, 1);
        struBackPicturParam.struPicture[iItemCount].dwFileSize = ProcessFileSize(csFileSize);

		csFileTime = m_PicList.GetItemText(iIndex, 2);
		sscanf(csFileTime, "%04d%02d%02d%02d%02d%02d", &(struBackPicturParam.struPicture[iItemCount].struTime.dwYear),\
			                                           &(struBackPicturParam.struPicture[iItemCount].struTime.dwMonth),\
													   &(struBackPicturParam.struPicture[iItemCount].struTime.dwDay),\
													   &(struBackPicturParam.struPicture[iItemCount].struTime.dwHour),\
													   &(struBackPicturParam.struPicture[iItemCount].struTime.dwMinute),\
													   &(struBackPicturParam.struPicture[iItemCount].struTime.dwSecond));

        iItemCount++;
    }
    struBackPicturParam.dwPicNum = iItemCount; 
	return TRUE;
}

void CJPEGPicDownload::OnBtnBackup() 
{
    char szLan[256] = {0};
	if (!m_bBackuping)
    {
		//backup by file
		NET_DVR_BACKUP_PICTURE_PARAM struBackupPictureParam = {0};
		if(!GetBackupPictureParamFromWnd_FILE(struBackupPictureParam))
		{
			return;
		}
		m_lBackupHandle = NET_DVR_BackupPicture(m_lServerID, &struBackupPictureParam);
	
		if (m_lBackupHandle == -1)
		{
			g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_FAIL_T, "NET_DVR_BackupPicture");
			return;
		}
		else
		{
			g_pMainDlg->AddLog(m_iDeviceIndex, OPERATION_SUCC_T, "NET_DVR_BackupPicture");
		} 
        
        DWORD dwThreadId = 0;
        if (m_hBackupThread == NULL)
        {
            m_hBackupThread = CreateThread(NULL,0,LPTHREAD_START_ROUTINE(GetBackupPicThread),this,0,&dwThreadId);		
        }
        if (m_hBackupThread  == NULL)
        {
            char szLan[256] = {0};
            g_StringLanType(szLan, "�򿪱����߳�ʧ��!", "Fail to open backup thread!");
            AfxMessageBox(szLan);
            return;
        }
        g_StringLanType(szLan, "ֹͣ����", "Stop Bakcup");
        GetDlgItem(IDC_BTN_BACKUP)->SetWindowText(szLan);
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
        g_StringLanType(szLan, "ͼƬ����", "Backup");
        GetDlgItem(IDC_BTN_BACKUP)->SetWindowText(szLan);
        m_bBackuping = FALSE;
        GetDlgItem(IDC_STATIC_BACK_STATE)->ShowWindow(SW_HIDE);
    }
}

void CJPEGPicDownload::OnSelchangeComboDiskList() 
{
    DWORD dwDiskFreeSpace = m_struDiskList.struDescNode[m_comboDiskList.GetCurSel()].dwFreeSpace;
    char szLanCn[256] = {0};
    char szLanEn[256] = {0};
    char szLan[256] = {0};
    sprintf(szLanCn, "ʣ����̿ռ�%dM", dwDiskFreeSpace);
    sprintf(szLanEn, "Free Disk Spcace%dM", dwDiskFreeSpace);
    g_StringLanType(szLan, szLanCn, szLanEn);
    GetDlgItem(IDC_STATIC_BACKUP_DISK_SIZE)->ShowWindow(SW_SHOW);
    GetDlgItem(IDC_STATIC_BACKUP_DISK_SIZE)->SetWindowText(szLan);
}	

void CJPEGPicDownload::PostNcDestroy() 
{
	
	CDialog::PostNcDestroy();
}
