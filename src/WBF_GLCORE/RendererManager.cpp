#include "stdafx.h"
#include "RendererManager.h"
#include "DataRenderer.h"
#include "ViewHelper.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CRendererManager::CRendererManager()
	: m_pView(nullptr)
{
}

CRendererManager::~CRendererManager()
{

}

void CRendererManager::InitialData(CView * pView)
{
	m_pView = pView;
}

void CRendererManager::CreateRenderer()
{
	auto& fact = CRendererFactory::GetInstance();

	std::vector<UINT> lstType;
	auto lSize = fact.GetTypeList(lstType);

	for (auto indx = 0; indx < lSize; ++indx)
	{
		auto pObject = fact.CreateObject(lstType[indx]);
		if (pObject != nullptr)
		{
			m_mRenderer[lstType[indx]] = (CDataRenderer*)pObject;
		}
	}
}

void CRendererManager::GLBuild(UINT uiFlag)
{
	CViewHelper tHelper;
	tHelper.InitialData(m_pView);

	auto itr = m_mRenderer.begin();
	while (itr != m_mRenderer.end())
	{
		auto pObject = itr->second;
		if (pObject != nullptr)
		{
			pObject->GLRelease();
			pObject->GLBuild(&tHelper, uiFlag);
		}

		itr++;
	}
}

void CRendererManager::GLDelete()
{
	auto itr = m_mRenderer.begin();
	while (itr != m_mRenderer.end())
	{
		auto pObject = itr->second;
		if (pObject != nullptr)
			pObject->GLRelease();

		_SAFE_DELETE(itr->second);

		itr++;
	}

	m_mRenderer.clear();
}

void CRendererManager::GLDrawScene()
{
	CViewHelper tHelper;
	tHelper.InitialData(m_pView);

	auto itr = m_mRenderer.begin();
	while (itr != m_mRenderer.end())
	{
		auto pObject = itr->second;
		if (pObject != nullptr)
			pObject->GLDraw(&tHelper);

		itr++;
	}
}
