#include "stdafx.h"
#include "ObjectBufferManager.h"
#include "ObjectBuffer.h"
#include "ViewHelper.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CObjectBufferManager::CObjectBufferManager()
	: m_pView(nullptr)
{
}

CObjectBufferManager::~CObjectBufferManager()
{

}

void CObjectBufferManager::InitialData(CView * pView)
{
	m_pView = pView;
}

void CObjectBufferManager::Create()
{
	auto& fact = CObjectBufferFactory::GetInstance();

	std::vector<UINT> lstType;
	auto lSize = fact.GetTypeList(lstType);

	for (auto indx = 0; indx < lSize; ++indx)
	{
		auto pObject = fact.CreateObject(lstType[indx]);
		if (pObject != nullptr)
		{
			m_mObjectBuffer[lstType[indx]] = (CObjectBuffer*)pObject;
		}
	}
}

BOOL CObjectBufferManager::Exist(UINT uiType)
{
	auto itr = m_mObjectBuffer.find(uiType);
	return itr != m_mObjectBuffer.end();
}

CObjectBuffer * CObjectBufferManager::LookUp(UINT uiType)
{
	auto itr = m_mObjectBuffer.find(uiType);
	if (itr == m_mObjectBuffer.end())
	{
		ASSERT(g_warning);
		return nullptr;
	}

	return itr->second;
}

void CObjectBufferManager::GLBuild(UINT uiFlag)
{
	CViewHelper tHelper;
	tHelper.InitialData(m_pView);
	
	auto itr = m_mObjectBuffer.begin();
	while (itr != m_mObjectBuffer.end())
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

void CObjectBufferManager::GLDelete()
{
	auto itr = m_mObjectBuffer.begin();
	while (itr != m_mObjectBuffer.end())
	{
		auto pObjectBuffer = itr->second;
		if (pObjectBuffer != nullptr)
			pObjectBuffer->GLRelease();

		_SAFE_DELETE(pObjectBuffer);

		itr++;
	}

	m_mObjectBuffer.clear();
}
