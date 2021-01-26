#pragma once

#include "HeaderPre.h"
class __MY_EXT_CLASS__ CFrameBuffer
{
public:
	CFrameBuffer();
	virtual ~CFrameBuffer();

public:
	void GLBind();
	void GLUnbind();
	void GLBindColorTex2D();
	void GLUnbindColorTex2D();

	void GLGeneralFrameBuffer();
	void GLDeleteFrameBuffer();
	BOOL IsValidFrameBuffer();

	BOOL GLAttachColorTexture2D(UINT uiAttachment, int x, int y);
	void GLResizeColorTexture2D(int x, int y);
	void GLDeleteColorTexture2D();
	BOOL GLAttachDepthStencilRender(int x, int y);
	void GLResizeDepthStencilRender(int x, int y);
	void GLDeleteDepthStencilRender();

protected:
	UINT GLCreateTexture2D(UINT uiInternalFormat, UINT uiFormat, UINT uiType, int x, int y);
	void GLAttachTexture2D(UINT uiTextureBuffer, UINT uiAttachment);

	UINT GLCreateRenderBuffer(UINT uiInternalFormat, int x, int y);
	void GLAttachRenderBuffer(UINT uiRenderBuffer, UINT uiAttachment);

protected:
	UINT m_uiPrevFBO;
	UINT m_uiFBO;
	UINT m_uiColorTex2D;
	UINT m_uiDepthStencilTex2D;
	UINT m_uiDepthStencilRender;

	UINT m_uiScreenFullSize[2];
};
#include "HeaderPost.h"