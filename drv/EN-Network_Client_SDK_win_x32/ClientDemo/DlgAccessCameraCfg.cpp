// DlgAccessCameraCfg.cpp : implementation file
//

#include "stdafx.h"
#include "clientdemo.h"
#include "DlgAccessCameraCfg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgAccessCameraCfg dialog

void __stdcall cbSetAccessCameraState(LONG lHandle, DWORD dwState, LPVOID pUser)
{
	CDlgAccessCameraCfg *pThis = (CDlgAccessCameraCfg*)pUser;
	HWND hWnd = pThis->GetSafeHwnd();
	if (NULL == hWnd)
	{
		return;
	}

// 	char szPrint[64] = {0};
// 	sprintf(szPrint, "demo cbSetAccessCameraState state = %d\n", dwState);
// 	OutputDebugString(szPrint);
	
	::SendMessage(hWnd, MSG_SET_ACCESS_CAMERA_STATE, (WPARAM)&dwState, NULL);
}


CDlgAccessCameraCfg::CDlgAccessCameraCfg(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgAccessCameraCfg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgAccessCameraCfg)
	m_strAccessCameraInfo = _T("");
	m_strSetAccessCameraState = _T("");
	//}}AFX_DATA_INIT
}

CDlgAccessCameraCfg::~CDlgAccessCameraCfg()
{
	if (!NET_DVR_CloseLongCfgHandle(m_iHandle))
	{
		g_pMainDlg->AddLog(m_dwDevIndex, OPERATION_FAIL_T, "NET_DVR_CloseLongCfgHandle");
	}
}


void CDlgAccessCameraCfg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgAccessCameraCfg)
	DDX_Control(pDX, IDC_COMBO_INTERFACE_TYPE, m_cmbInferfaceType);
	DDX_Text(pDX, IDC_EDIT_ACCESS_CAMERA_INFO, m_strAccessCameraInfo);
	DDX_Text(pDX, IDC_STATIC_STATE, m_strSetAccessCameraState);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgAccessCameraCfg, CDialog)
	//{{AFX_MSG_MAP(CDlgAccessCameraCfg)
	ON_MESSAGE(MSG_SET_ACCESS_CAMERA_STATE, OnSetAccessCameraState)
	ON_BN_CLICKED(ID_BTN_SET, OnBtnSet)
	ON_BN_CLICKED(ID_BTN_GET, OnBtnGet)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgAccessCameraCfg message handlers


LRESULT CDlgAccessCameraCfg::OnSetAccessCameraState(WPARAM wParam, LPARAM lParam)
{
	DWORD dwState = *(DWORD *)wParam;
// 	char szPrint[64] = {0};
// 	sprintf(szPrint, "demo MSG OnSetAccessCameraState state = %d\n", dwState);
// 	OutputDebugString(szPrint);
	switch (dwState)
	{
	case SET_CAMERA_TYPE_SUCCESS:
		m_strSetAccessCameraState = "���óɹ�";
		break;
	case SET_CAMERA_TYPE_FAIL:
		m_strSetAccessCameraState = "����ʧ��";
		break;
	case SET_CAMERA_TYPE_PROCESSING:
		m_strSetAccessCameraState = "���ڴ���...";
		break;
	default:
		m_strSetAccessCameraState = "��֧��";
		break;
		
	}
	
	UpdateData(FALSE);
	return NULL;

}

void CDlgAccessCameraCfg::OnBtnSet() 
{
	// TODO: Add your control notification handler code here

	// ��ʼ���ؼ�
	m_strSetAccessCameraState = "";
	UpdateData(FALSE);

	// �ͷ���һ�β�����Դ
	if (m_iHandle >= 0)
	{
		if (!NET_DVR_CloseLongCfgHandle(m_iHandle))
		{
			g_pMainDlg->AddLog(m_dwDevIndex, OPERATION_FAIL_T, "NET_DVR_CloseLongCfgHandle");
		}

		m_iHandle = -1;
	}

	// ��ʼ����
	UpdateData(TRUE);
	char szLan[128] = {0};
	NET_DVR_ACCESS_CAMERA_INFO struAccessCameraInfo;
	memset(&struAccessCameraInfo, 0, sizeof(NET_DVR_ACCESS_CAMERA_INFO));

	struAccessCameraInfo.dwSize = sizeof(NET_DVR_ACCESS_CAMERA_INFO);
	strncpy(struAccessCameraInfo.sCameraInfo, m_strAccessCameraInfo.GetBuffer(0), 32);
	struAccessCameraInfo.byInterfaceType = m_cmbInferfaceType.GetCurSel()+1;

	m_iHandle = NET_DVR_SetAccessCameraInfo(m_lUserID, m_lChannel, &struAccessCameraInfo, cbSetAccessCameraState, this);
	
	if(-1 == m_iHandle)
	{
		g_pMainDlg->AddLog(m_dwDevIndex, OPERATION_FAIL_T, "NET_DVR_SetAccessCameraInfo");
		g_StringLanType(szLan, "����ǰ�������Ϣʧ��!", "Fail to set access camera info");
		AfxMessageBox(szLan);
	}
}

void CDlgAccessCameraCfg::OnBtnGet() 
{
	// TODO: Add your control notification handler code here
	char szLan[128] = {0};
	NET_DVR_ACCESS_CAMERA_INFO struAccessCameraInfo;
	memset(&struAccessCameraInfo, 0, sizeof(NET_DVR_ACCESS_CAMERA_INFO));

	DWORD dwReturnedBytes = 0;

	if(TRUE == NET_DVR_GetDVRConfig(m_lUserID, NET_DVR_GET_ACCESS_CAMERA_INFO, m_lChannel, &struAccessCameraInfo, sizeof(NET_DVR_ACCESS_CAMERA_INFO), &dwReturnedBytes))
	{
		g_pMainDlg->AddLog(m_dwDevIndex, OPERATION_SUCC_T, "NET_DVR_GET_ACCESS_CAMERA_INFO");
		g_StringLanType(szLan, "��ȡǰ�������Ϣ�ɹ�!", "Success to get access camera info");
		AfxMessageBox(szLan);
	}
	else
	{
		g_pMainDlg->AddLog(m_dwDevIndex, OPERATION_FAIL_T, "NET_DVR_GET_ACCESS_CAMERA_INFO");
		g_StringLanType(szLan, "��ȡǰ�������Ϣʧ��!", "Fail to get access camera info");
		AfxMessageBox(szLan);
	}

	strncpy(m_strAccessCameraInfo.GetBuffer(0), struAccessCameraInfo.sCameraInfo, 32);
	m_cmbInferfaceType.SetCurSel(struAccessCameraInfo.byInterfaceType-1);

	UpdateData(FALSE);
}

BOOL CDlgAccessCameraCfg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	//OnBtnGet();
	m_cmbInferfaceType.SetCurSel(0);
	m_iHandle = -1;
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
