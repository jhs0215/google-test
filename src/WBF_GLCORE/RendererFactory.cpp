#include "stdafx.h"
#include "RendererFactory.h"


CRendererFactory & CRendererFactory::GetInstance()
{
	static CRendererFactory inst;
	return inst;
}

CRendererFactory::CRendererFactory()
{
}


CRendererFactory::~CRendererFactory()
{
}
