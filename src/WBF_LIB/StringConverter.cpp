#include "stdafx.h"
#include "StringConverter.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CStringConverter::CStringConverter()
{
}


CStringConverter::~CStringConverter()
{
}

void CStringConverter::CSTR2WSTR(IN const CString & cstr, OUT std::wstring wstr)
{
	wstr = CSTR2WSTR(cstr);
}

void CStringConverter::WSTR2CSTR(IN const std::wstring & wstr, OUT CString & cstr)
{
	cstr = WSTR2CSTR(wstr);
}

void CStringConverter::CSTR2STR(IN const CString & cstr, OUT std::string & str, UINT CodePage)
{
	str = CSTR2STR(cstr, CodePage);
}

void CStringConverter::STR2CSTR(IN const std::string & str, OUT CString & cstr, UINT CodePage)
{
	cstr = STR2CSTR(str, CodePage);
}

void CStringConverter::STR2WSTR(IN const std::string & str, OUT std::wstring wstr, UINT CodePage)
{
	wstr = STR2WSTR(str, CodePage);
}

void CStringConverter::WSTR2STR(IN const std::wstring wstr, OUT std::string & str, UINT CodePage)
{
	str = WSTR2STR(wstr, CodePage);
}

std::wstring CStringConverter::CSTR2WSTR(IN const CString & cstr)
{
	return std::wstring(cstr.operator LPCWSTR());
}

CString CStringConverter::WSTR2CSTR(IN const std::wstring & wstr)
{
	return CString::CStringT(wstr.c_str());
}

std::string CStringConverter::CSTR2STR(IN const CString & cstr, UINT CodePage)
{
	return std::string(CT2CA(cstr.operator LPCWSTR(), CodePage));
}

CString CStringConverter::STR2CSTR(IN const std::string & str, UINT CodePage)
{
	return CString::CStringT(CA2CT(str.c_str(), CodePage));
}

std::wstring CStringConverter::STR2WSTR(IN const std::string & str, UINT CodePage)
{
	return std::wstring(CA2CT(str.c_str(), CodePage));
}

std::string CStringConverter::WSTR2STR(IN const std::wstring wstr, UINT CodePage)
{
	return std::string(CT2CA(wstr.c_str(), CodePage));
}

