#pragma once

#ifndef DEF_IMG_LOADER
#define DEF_IMG_LOADER

#define WBFIMG_RED 1
#define WBFIMG_RGB 3
#define WBFIMG_RGBA 4

#include "HeaderPre.h"

class __MY_EXT_API__ CImageLoader
{
public:
	CImageLoader();
	virtual ~CImageLoader();

public:
	void Import(const CString& strFilePath);

	const BYTE* GetBuffer() { return m_pBuffer; }
	const int GetWidth() { return m_nWidth; }
	const int GetHeight() { return m_nHeight; }
	const int GetByte() { return m_nBytes; }

protected:
	CString m_strFilePath;
	BYTE* m_pBuffer;
	int m_nWidth;
	int m_nHeight;
	int m_nBytes;
};

#include "HeaderPost.h"

#endif // !DEF_IMG_LOADER