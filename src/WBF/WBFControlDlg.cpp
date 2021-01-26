#include "stdafx.h"
#include "resource.h"
#include "WBFControlDlg.h"
#include "WBFDoc.h"
#include "WBFView.h"

#include <gtest\gtest.h>

#include "..\WBF_LIB\FileCtrl.h"
#include "..\WBF_BASE\FileCtrlManager.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

enum E_CONTROL_TYPE
{
	E_CTRL_GTEST = 0,
	E_CTRL_NUM
};

CWBFControlDlg::CWBFControlDlg(CDocBase * pDoc, CViewBase * pView, CWnd * pParent)
	: CWBFDialog(CWBFControlDlg::IDD, pDoc, pParent), m_pView(pView)
{
	m_bInitGTest = FALSE;
}

CWBFControlDlg::~CWBFControlDlg()
{
	if(m_bInitGTest)
	{
		if (m_pConsoleStream != nullptr)
		{
			fclose(m_pConsoleStream);
			m_pConsoleStream = nullptr;

			FreeConsole();
		}
	}
}

void CWBFControlDlg::DoDataExchange(CDataExchange * pDX)
{
	CWBFDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_WBF_TYPE_COBX, m_cobxType);
	DDX_Control(pDX, IDC_WBF_POLY_FACE_COBX, m_cobxPolyFace);
	DDX_Control(pDX, IDC_WBF_POLY_MODE_COBX, m_cobxPolyMode);
	DDX_Control(pDX, IDC_WBF_RATIO_SLID, m_slidRatio);
}

BEGIN_MESSAGE_MAP(CWBFControlDlg, CWBFDialog)
	ON_BN_CLICKED(IDC_UPDATE_BTN, OnClickedUpdate)
	ON_WM_DESTROY()
END_MESSAGE_MAP()

BOOL CWBFControlDlg::Create(CWnd * pParent)
{
	return CWBFDialog::Create(CWBFControlDlg::IDD, pParent);
}

BOOL CWBFControlDlg::OnInitDialog()
{
	CWBFDialog::OnInitDialog();

	SetControl();

	Data2Dlg();

	return TRUE;
}

BOOL CWBFControlDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: Add your specialized code here and/or call the base class

	return CWBFDialog::PreTranslateMessage(pMsg);
}

void CWBFControlDlg::OnOK()
{
	//CWBFDialog::OnOK();
}

void CWBFControlDlg::OnCancel()
{
	CWBFDialog::OnCancel();
}

void CWBFControlDlg::SetControl()
{
	auto lambda_cobx = [](CComboBox& cobx, long uiNum, CString aName[])
	{
		cobx.ResetContent();
		for (auto indx = 0; indx < uiNum; ++indx)
		{
			auto item = cobx.AddString(aName[indx]);
			cobx.SetItemData(item, indx);
		}
		cobx.SetCurSel(0);
	};

	CString aTypeName[] = {_T("gTest"), _T("ContainerBox"), _T("Assimp")};
	lambda_cobx(m_cobxType, E_CTRL_NUM, aTypeName);

	//CString aPolyFaceName[] = {_T("Front/Back"), _T("Front"), _T("Back")};
	//UINT aPolyFaceData[] = {GL_FRONT_AND_BACK , GL_FRONT, GL_BACK,};
	//lambda_cobx(m_cobxPolyFace, sizeof(aPolyFaceData) / sizeof(UINT), aPolyFaceName, aPolyFaceData);

	//CString aPolyModeName[] = {_T("Fill"), _T("Line")};
	//UINT aPolyModeData[] = {GL_FILL, GL_LINE};
	//lambda_cobx(m_cobxPolyMode, sizeof(aPolyModeData) / sizeof(UINT), aPolyModeName, aPolyModeData);

	m_slidRatio.SetRange(0, 100);
	m_slidRatio.SetRangeMin(0);
	m_slidRatio.SetRangeMax(100);
	m_slidRatio.SetPos(50);
	m_slidRatio.SetTicFreq(10);
	m_slidRatio.SetLineSize(1);
	m_slidRatio.SetPageSize(10);
}

void CWBFControlDlg::Data2Dlg()
{
	CString strFullPath = _T("D:\\Cloud\\Git\\GraphicLibrary\\WBF\\file\\crysis-nano-suit-2.zip");
	CString strBasePath = _T("D:\\Cloud\\Git\\GraphicLibrary\\WBF\\bin\\v141\\Debug\\x64\\");

	CFileCtrl fCtrl;
	fCtrl.SetFilePath(strFullPath);

	CString strRelative = CFileCtrl::Absolute2Relative(strBasePath, strFullPath);
	
	////////////////////////////////////////////////

	m_cobxType.SetCurSel(E_CTRL_GTEST); // TEST Default ComboBox
}

BOOL CWBFControlDlg::Dlg2Data()
{
	if (!CheckData())
		return FALSE;

	auto lambda_cobx = [](CComboBox& cobx)
	{
		auto item = cobx.GetCurSel();
		return (UINT)cobx.GetItemData(item);
	};

	lambda_cobx(m_cobxType);

	//auto pModelMgr = m_pMyDoc->GetModelManager();
	//auto pModel = pModelMgr->GetModel(uiType);
	//auto pOption = (CWBFGPSOption*)pModel->GetOption();

	//pOption->uiPolygonFace = lambda_cobx(m_cobxPolyFace);
	//pOption->uiPolygonMode = lambda_cobx(m_cobxPolyMode);

	//pOption->fRatio = (float)m_slidRatio.GetPos() / 100.f;

	//pModelMgr->OnUpdateOnly((UINT)uiType);

	return TRUE;
}

BOOL CWBFControlDlg::CheckData()
{
	auto lambda_cobx = [](CComboBox& cobx)
	{
		auto item = cobx.GetCurSel();
		return (UINT)cobx.GetItemData(item);
	};

	auto uiType = lambda_cobx(m_cobxType);
	switch (uiType)
	{
	case E_CTRL_GTEST:
		break;
	default:
		{
			ASSERT(g_warning);
		}
		break;
	}

	return TRUE;
}

BOOL CWBFControlDlg::Execute()
{
	if (!Dlg2Data())
		return TRUE;

	auto lambda_cobx = [](CComboBox& cobx)
	{
		auto item = cobx.GetCurSel();
		return (UINT)cobx.GetItemData(item);
	};


	auto uiType = lambda_cobx(m_cobxType);
	switch (uiType)
	{
	case E_CTRL_GTEST:
		{
			if (!m_bInitGTest)
			{
				if (!AllocConsole())
				{
					ASSERT(g_warning);
				}
				else
				{
					freopen_s(&m_pConsoleStream, "CONOUT$", "wt", stdout);
					m_bInitGTest = TRUE;
					
					::testing::InitGoogleTest();

					RUN_ALL_TESTS();
				}
			}
			else
			{
				if (m_pConsoleStream != nullptr)
				{
					fclose(m_pConsoleStream);
					m_pConsoleStream = nullptr;

					FreeConsole();
				}

				m_bInitGTest = FALSE;
			}
		}
		break;
	default:
		{
			ASSERT(g_warning);
		}
		break;
	}

	return TRUE;
}

void CWBFControlDlg::OnClickedUpdate()
{
	if (!Execute())
	{
		// Unknown
	}
}

void CWBFControlDlg::OnDestroy()
{
	CWBFDialog::OnDestroy();
}