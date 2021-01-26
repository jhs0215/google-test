#pragma once

#include "HeaderPre.h"

class __MY_EXT_CLASS__ CShader
{
public:
	CShader();
	virtual ~CShader();

public:
	void GLCreate();
	void GLDelete();
	void GLAttachShader(UINT nShaderType, UINT uiResID);
	void GLLinkShader();

	void GLBind();
	void GLUnbind();
	BOOL GLSetInt(const char* aName, int nData);
	BOOL GLSetBoolean(const char* aName, bool bData);
	BOOL GLSetFloat(const char* aName, float fData);
	BOOL GLSetDouble(const char* aName, double dData);
	BOOL GLSetVector3(const char* aName, glm::vec3& vec3);
	BOOL GLSetMatrix4(const char* aName, glm::mat4& mat4);

protected:
	unsigned int m_nProg;
	std::vector<UINT> m_vShader;
};

#include "HeaderPost.h"