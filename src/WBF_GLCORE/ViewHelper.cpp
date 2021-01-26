#include "stdafx.h"
#include "ViewHelper.h"
#include "GLCtrlView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CViewHelper::CViewHelper()
	: m_pView(nullptr)
{
}

CViewHelper::~CViewHelper()
{
}

CDocument * CViewHelper::GetDocument()
{
	if (!IsValidData()) return nullptr;
		
	auto pDoc = m_pView->GetDocument();
	ASSERT(pDoc != nullptr);

	return pDoc;
}

CView * CViewHelper::GetView()
{
	if (!IsValidData()) return nullptr;

	ASSERT(m_pView != nullptr);

	return m_pView;
}

CFrameBufferManager * CViewHelper::GetFrameBufferManager()
{
	if (!IsValidData()) return nullptr;

	auto pCtrlView = (CGLCtrlView*)m_pView;
	auto pFrameBufferManager = pCtrlView->GetFrameBufferManager();
	ASSERT(pFrameBufferManager != nullptr);

	return pFrameBufferManager;
}

CObjectBufferManager * CViewHelper::GetObjectBufferManager()
{
	if (!IsValidData()) return nullptr;

	auto pCtrlView = (CGLCtrlView*)m_pView;
	auto pObjectBufferManager = pCtrlView->GetObjectBufferManager();
	ASSERT(pObjectBufferManager != nullptr);

	return pObjectBufferManager;
}

CRendererManager * CViewHelper::GetRendererManager()
{
	if (!IsValidData()) return nullptr;

	auto pCtrlView = (CGLCtrlView*)m_pView;
	auto pRendererManager = pCtrlView->GetRendererManager();
	ASSERT(pRendererManager != nullptr);

	return pRendererManager;
}

CShaderManager * CViewHelper::GetShaderManager()
{
	if (!IsValidData()) return nullptr;

	auto pCtrlView = (CGLCtrlView*)m_pView;
	auto pShaderManager = pCtrlView->GetShaderManager();
	ASSERT(pShaderManager != nullptr);

	return pShaderManager;
}

BOOL CViewHelper::IsValidData()
{
	if (m_pView != nullptr && IsWindow(m_pView->GetSafeHwnd()) == FALSE)
	{
		ASSERT(g_warning);
		return FALSE;
	}

	return TRUE;
}
