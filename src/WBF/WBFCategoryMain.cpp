#include "stdafx.h"
#include "WBFCategoryMain.h"
#include "Resource.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CWBFCategoryMain::CWBFCategoryMain()
	: m_pRibbonBar(nullptr), m_pCategory(nullptr), m_pPanel(nullptr), m_pButton(nullptr)
{
}


CWBFCategoryMain::~CWBFCategoryMain()
{
}

void CWBFCategoryMain::OnInitial(CMFCRibbonBar * pRibbonBar)
{
	ASSERT(pRibbonBar);

	m_pRibbonBar = pRibbonBar;
	m_pCategory = pRibbonBar->AddCategory(_T("Main Category"), IDB_WRITESMALL, IDB_WRITELARGE);

	m_pPanel = m_pCategory->AddPanel(_T("Panel"));
	m_pPanel->SetCenterColumnVert(TRUE);

	m_pButton = new CMFCRibbonButton(ID_WBF_CAT_MAIN_BUTTON, _T("Button"), 0, -1);
	m_pButton->SetToolTipText(_T("Button ToolTip"));
	m_pButton->SetDescription(_T("Button Description"));
	m_pPanel->Add(m_pButton);
}