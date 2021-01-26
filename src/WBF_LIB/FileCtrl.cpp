#include "stdafx.h"
#include "FileCtrl.h"

#define D_EMPTY _T("")
#define D_BACKSLASH _T("\\")
#define D_CURRENT _T(".\\")
#define D_PARENT _T("..\\")

CFileCtrl::CFileCtrl()
{
	m_strFullPath = D_EMPTY;
	m_strPath = D_EMPTY;
	m_strName = D_EMPTY;
	m_strExt = D_EMPTY;
}

CFileCtrl::CFileCtrl(const CString & strFilePath)
{
	m_strFullPath = D_EMPTY;
	m_strPath = D_EMPTY;
	m_strName = D_EMPTY;
	m_strExt = D_EMPTY;

	SetFilePath(strFilePath);
}

CFileCtrl::~CFileCtrl()
{
}

void CFileCtrl::SetFilePath(const CString & strFullPath)
{
	if (strFullPath.IsEmpty())
	{
		ASSERT(g_warning);
		return;
	}

	m_strFullPath = strFullPath;

	auto item = m_strFullPath.ReverseFind('\\');
	if (item != -1)
	{
		m_strPath = m_strFullPath.Left(item + 1);

		auto strNameExt = m_strFullPath.Right(m_strFullPath.GetLength() - item - 1);
		auto itemExt = strNameExt.ReverseFind('.');

		if (itemExt != -1)
		{
			m_strName = strNameExt.Left(itemExt);
			m_strExt = strNameExt.Left(strNameExt.GetLength() - itemExt - 1);
		}
	}
}

BOOL CFileCtrl::Exist()
{
	CFileStatus FileStatus;
	return CFile::GetStatus(m_strFullPath, FileStatus);
}

CString CFileCtrl::GetPathNameExt()
{
	return m_strFullPath;
}

CString CFileCtrl::GetPathName()
{
	return m_strPath + m_strName;
}

CString CFileCtrl::GetPath()
{
	return m_strPath;
}

CString CFileCtrl::GetName()
{
	return m_strName;
}

CString CFileCtrl::GetExt()
{
	return m_strExt;
}

BOOL CFileCtrl::Exist(const CString& strFullPath)
{
	CFileStatus FileStatus;
	return CFile::GetStatus(strFullPath, FileStatus);
}

CString CFileCtrl::Absolute2Relative(const CString & src, const CString & trg)
{
	if (src.IsEmpty() || trg.IsEmpty())
	{
		ASSERT(g_warning);
		return D_CURRENT;
	}
	else if (src.CompareNoCase(trg) == 0)
		return D_CURRENT;

	CString strSrc = src;
	CString strTrg = trg;
	auto lambda_path = [](CString& strPath)
	{
		auto item = strPath.ReverseFind('\\');
		if (item != -1)
			strPath = strPath.Left(item + 1);
	};
	lambda_path(strSrc);
	lambda_path(strTrg);

	std::vector<CString> aSrcSplit;
	std::vector<CString> aTrgSplit;
	auto lambda_split = [](const CString& strPath, std::vector<CString>& aSplit)
	{
		int nSub = 0;
		CString strSub = D_EMPTY;
		while (AfxExtractSubString(strSub, strPath, nSub++, '\\'))
		{
			if (strSub.IsEmpty())
				continue;

			aSplit.push_back(strSub);
		}
	};
	lambda_split(strSrc, aSrcSplit);
	lambda_split(strTrg, aTrgSplit);

	CString strSame = D_EMPTY;

	CString strSrcUpper = strSrc;
	strSrcUpper.MakeUpper();
	for (auto strSplit : aTrgSplit)
	{
		strSplit.MakeUpper();

		auto strDiff = strSame + strSplit;
		auto item = strSrcUpper.Find(strDiff);
		if (item != 0)
			break;

		strSame += strSplit + D_BACKSLASH;
	}

	if (strSame.IsEmpty()) // Different Directory 
	{
		ASSERT(g_warning);
		return strSrc;
	}

	CString strRelative = D_EMPTY;

	CString strCompTrg = D_EMPTY;
	for (auto strSplit : aTrgSplit)
	{
		auto strUpper = strSplit;
		strUpper.MakeUpper();

		auto strDiff = strCompTrg + strUpper;
		auto item = strSame.Find(strDiff);
		if (item != 0)
			strRelative += D_PARENT;

		strCompTrg += strUpper + D_BACKSLASH;
	}
	CString strCompSrc = D_EMPTY;
	for (auto strSplit : aSrcSplit)
	{
		auto strUpper = strSplit;
		strUpper.MakeUpper();

		auto strDiff = strCompSrc + strUpper;
		auto item = strSame.Find(strDiff);
		if (item != 0)
			strRelative += strSplit + D_BACKSLASH;

		strCompSrc += strUpper + D_BACKSLASH;
	}

	return strRelative;
}