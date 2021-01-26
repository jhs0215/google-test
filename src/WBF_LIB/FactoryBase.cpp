#include "stdafx.h"
#include "FactoryBase.h"


CFactoryBase::CFactoryBase()
{
}


CFactoryBase::~CFactoryBase()
{
	m_mObject.clear();
}

BOOL CFactoryBase::Register(UINT uiType, CRuntimeClass * pRuntime)
{
	auto itr = m_mObject.find(uiType);
	if (itr != m_mObject.end())
	{
		ASSERT(g_warning);
		m_mObject.erase(itr);
	}

	m_mObject[uiType] = pRuntime;
	return TRUE;
}

void CFactoryBase::Unregister(UINT uiType)
{
	auto itr = m_mObject.find(uiType);
	if (itr != m_mObject.end())
		m_mObject.erase(itr);
}

CFactoryObjectBase * CFactoryBase::CreateObject(UINT uiType)
{
	auto itr = m_mObject.find(uiType);
	if (itr == m_mObject.end())
	{
		ASSERT(g_warning);
		return nullptr;
	}

	auto pObject = itr->second->CreateObject();
	return (CFactoryObjectBase*)pObject;
}

long CFactoryBase::GetTypeList(std::vector<UINT>& lstType)
{
	lstType.clear();

	auto itr = m_mObject.begin();
	while (itr != m_mObject.end())
	{
		auto itrFind = std::find(lstType.begin(), lstType.end(), itr->first);
		if (itrFind == lstType.end()) lstType.push_back(itr->first);

		itr++;
	}

	return (long)lstType.size();
}