#include "stdafx.h"
#include "DocBase.h"
#include "ViewBase.h"
#include "FileCtrlManager.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CDocBase::CDocBase()
{
	m_pFileCtrlManager = new CFileCtrlManager(this);
}

CDocBase::~CDocBase()
{
	_SAFE_DELETE(m_pFileCtrlManager);
}

CViewBase * CDocBase::GetActiveView()
{
	auto pos = GetFirstViewPosition();
	while (pos != nullptr)
	{
		auto pView = GetNextView(pos);
		if (pView->IsKindOf(RUNTIME_CLASS(CViewBase)))
			return static_cast<CViewBase*>(pView);
	}

	ASSERT(g_warning);
	return nullptr;
}

CFileCtrlManager * CDocBase::GetFileCtrlManager()
{
	return m_pFileCtrlManager;
}
