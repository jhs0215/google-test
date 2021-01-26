#include "stdafx.h"
#include "ObjectBufferFactory.h"

CObjectBufferFactory & CObjectBufferFactory::GetInstance()
{
	static CObjectBufferFactory inst;
	return inst;
}

CObjectBufferFactory::CObjectBufferFactory()
{
}


CObjectBufferFactory::~CObjectBufferFactory()
{
}
