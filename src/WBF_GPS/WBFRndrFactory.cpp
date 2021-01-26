#include "stdafx.h"
#include "WBFRndrFactory.h"


CWBFRndrFactory * CWBFRndrFactory::GetInstance()
{
	static CWBFRndrFactory instance;
	return &instance;
}

CWBFRndrFactory::CWBFRndrFactory()
{
}


CWBFRndrFactory::~CWBFRndrFactory()
{
}

void CWBFRndrFactory::AddRegister(CRuntimeClass * pClass)
{
	auto itr = std::find(m_vObject.begin(), m_vObject.end(), pClass);
	if (m_vObject.end() != itr)
	{
		ASSERT(g_flag_warning);
		return;
	}

	m_vObject.push_back(pClass);
}
