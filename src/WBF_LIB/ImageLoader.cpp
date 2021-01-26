#include "stdafx.h"
#include "ImageLoader.h"
#include "StringConverter.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CImageLoader::CImageLoader()
{
	m_strFilePath = _T("");
	m_pBuffer = nullptr;
	m_nWidth = m_nHeight = m_nBytes = 0;
}

CImageLoader::~CImageLoader()
{
	_SAFE_DELETE_ARRAY(m_pBuffer);
}

void CImageLoader::Import(const CString& strFilePath)
{
	m_strFilePath = strFilePath;

	std::string conv;
	CStringConverter::CSTR2STR(strFilePath, conv);

	stbi_set_flip_vertically_on_load(true);
	BYTE* data = stbi_load(conv.c_str(), &m_nWidth, &m_nHeight, &m_nBytes, 0);
	{
		auto szData = m_nWidth * m_nHeight * m_nBytes;
		m_pBuffer = new BYTE[szData];
		std::copy(data, data + szData, m_pBuffer);
	}
	stbi_image_free(data);
}