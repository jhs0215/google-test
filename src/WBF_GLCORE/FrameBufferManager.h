#pragma once

#include "HeaderPre.h"

enum E_FRAMEBUFFER_TYPE
{
	E_FBO_SCREEN = 0,
	E_FBO_MODEL,
	E_FBO_NUM
};

class CFrameBuffer;
class __MY_EXT_CLASS__ CFrameBufferManager
{
public:
	CFrameBufferManager();
	virtual ~CFrameBufferManager();

public:
	void GLCreate();
	void GLDelete();
	void GLResize(int x, int y);
	void GLBind(UINT uiType);
	void GLUnbind(UINT uiType);
	void GLBindColorTex2D(UINT uiType);
	void GLUnbindColorTex2D(UINT uiType);

protected:
	CFrameBuffer* m_aFBO[E_FBO_NUM];

};

#include "HeaderPost.h"