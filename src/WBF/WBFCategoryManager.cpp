#include "stdafx.h"
#include "WBFCategoryManager.h"
#include "WBFCategoryMain.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CWBFCategoryManager::CWBFCategoryManager()
{
	m_mCategory[E_CAT_MAIN] = new CWBFCategoryMain;
}

CWBFCategoryManager::~CWBFCategoryManager()
{
	for (long indx = E_CATEGORY_TYPE::E_CAT_MAIN; indx < E_CATEGORY_TYPE::E_CAT_NUM; ++indx)
	{
		_SAFE_DELETE(m_mCategory[indx]);
	}
}

void CWBFCategoryManager::OnInitial(CMFCRibbonBar* pRibbonBar)
{
	for (long indx = E_CATEGORY_TYPE::E_CAT_MAIN; indx < E_CATEGORY_TYPE::E_CAT_NUM; ++indx)
		m_mCategory[indx]->OnInitial(pRibbonBar);
}
