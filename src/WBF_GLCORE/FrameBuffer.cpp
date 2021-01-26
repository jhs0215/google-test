#include "stdafx.h"
#include "FrameBuffer.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CFrameBuffer::CFrameBuffer()
{
	m_uiPrevFBO = 0;
	m_uiFBO = 0;
	m_uiColorTex2D = 0;
	m_uiDepthStencilTex2D = 0;
	m_uiDepthStencilRender = 0;

	m_uiScreenFullSize[0] = GetSystemMetrics(SM_CXFULLSCREEN);
	m_uiScreenFullSize[1] = GetSystemMetrics(SM_CYFULLSCREEN);
}

CFrameBuffer::~CFrameBuffer()
{
}

void CFrameBuffer::GLBind()
{
	GLint uiFBO;
	glGetIntegerv(GL_FRAMEBUFFER_BINDING, &uiFBO);
	if ((UINT)uiFBO != m_uiFBO)
	{
		glBindFramebuffer(GL_FRAMEBUFFER, m_uiFBO);
		m_uiPrevFBO = uiFBO;
	}
	else
	{
		glBindFramebuffer(GL_FRAMEBUFFER, m_uiFBO);
	}
}

void CFrameBuffer::GLUnbind()
{
	if (m_uiPrevFBO != m_uiFBO)
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0); // Screen Buffer
		glBindFramebuffer(GL_FRAMEBUFFER, m_uiPrevFBO);
	}
}

void CFrameBuffer::GLBindColorTex2D()
{
	glBindTexture(GL_TEXTURE_2D, m_uiColorTex2D);
}

void CFrameBuffer::GLUnbindColorTex2D()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}

void CFrameBuffer::GLGeneralFrameBuffer()
{
	glGenFramebuffers(1, &m_uiFBO);
}

void CFrameBuffer::GLDeleteFrameBuffer()
{
	if (glIsFramebuffer(m_uiFBO))
		glDeleteFramebuffers(1, &m_uiFBO);

	m_uiFBO = 0;
}

BOOL CFrameBuffer::IsValidFrameBuffer()
{
	// Frame Buffer Bind 이후에 확인이 가능하다.

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
	{
		ASSERT(g_warning);
		return FALSE;
	}

	return TRUE;
}

BOOL CFrameBuffer::GLAttachColorTexture2D(UINT uiAttachment, int x, int y)
{
	glGenTextures(1, &m_uiColorTex2D);
	glBindTexture(GL_TEXTURE_2D, m_uiColorTex2D);
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, x != 0 ? x : m_uiScreenFullSize[0], y != 0 ? y : m_uiScreenFullSize[1], 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	}
	glBindTexture(GL_TEXTURE_2D, 0);

	glFramebufferTexture2D(GL_FRAMEBUFFER, uiAttachment, GL_TEXTURE_2D, m_uiColorTex2D, 0);

	return m_uiColorTex2D != 0;
}

void CFrameBuffer::GLResizeColorTexture2D(int x, int y)
{
	glBindTexture(GL_TEXTURE_2D, m_uiColorTex2D);
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, x != 0 ? x : m_uiScreenFullSize[0], y != 0 ? y : m_uiScreenFullSize[1], 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	}
	glBindTexture(GL_TEXTURE_2D, 0);
}

void CFrameBuffer::GLDeleteColorTexture2D()
{
	if (glIsTexture(m_uiColorTex2D))
		glDeleteTextures(1, &m_uiColorTex2D);

	m_uiColorTex2D = 0;
}

BOOL CFrameBuffer::GLAttachDepthStencilRender(int x, int y)
{
	glGenRenderbuffers(1, &m_uiDepthStencilRender);
	glBindRenderbuffer(GL_RENDERBUFFER, m_uiDepthStencilRender);
	{
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, x != 0 ? x : m_uiScreenFullSize[0], y != 0 ? y : m_uiScreenFullSize[1]);
	}
	glBindRenderbuffer(GL_RENDERBUFFER, 0);

	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_uiDepthStencilRender);

	return m_uiDepthStencilRender != 0;
}

void CFrameBuffer::GLResizeDepthStencilRender(int x, int y)
{
	glBindRenderbuffer(GL_RENDERBUFFER, m_uiDepthStencilRender);
	{
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, x != 0 ? x : m_uiScreenFullSize[0], y != 0 ? y : m_uiScreenFullSize[1]);
	}
	glBindRenderbuffer(GL_RENDERBUFFER, 0);
}

void CFrameBuffer::GLDeleteDepthStencilRender()
{
	if (glIsRenderbuffer(m_uiDepthStencilRender))
		glDeleteRenderbuffers(1, &m_uiDepthStencilRender);

	m_uiDepthStencilRender = 0;
}

UINT CFrameBuffer::GLCreateTexture2D(UINT uiInternalFormat, UINT uiFormat, UINT uiType, int x, int y)
{
	UINT uiTextureBuffer = 0;

	glGenTextures(1, &uiTextureBuffer);
	glBindTexture(GL_TEXTURE_2D, uiTextureBuffer);
	glTexImage2D(GL_TEXTURE_2D, 0, uiInternalFormat, x != 0 ? x : m_uiScreenFullSize[0], y != 0 ? y : m_uiScreenFullSize[1], 0, uiFormat, uiType, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBindTexture(GL_TEXTURE_2D, 0);

	return uiTextureBuffer;
}

void CFrameBuffer::GLAttachTexture2D(UINT uiTextureBuffer, UINT uiAttachment)
{
	glFramebufferTexture2D(GL_FRAMEBUFFER, uiAttachment, GL_TEXTURE_2D, uiTextureBuffer, 0);
}

UINT CFrameBuffer::GLCreateRenderBuffer(UINT uiInternalFormat, int x, int y)
{
	UINT uiRenderBuffer = 0;

	glGenRenderbuffers(1, &uiRenderBuffer);
	glBindRenderbuffer(GL_RENDERBUFFER, uiRenderBuffer);
	glRenderbufferStorage(GL_RENDERBUFFER, uiInternalFormat, x != 0 ? x : m_uiScreenFullSize[0], y != 0 ? y : m_uiScreenFullSize[1]);
	glBindRenderbuffer(GL_RENDERBUFFER, 0);

	return uiRenderBuffer;
}

void CFrameBuffer::GLAttachRenderBuffer(UINT uiRenderBuffer, UINT uiAttachment)
{
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, uiAttachment, GL_RENDERBUFFER, uiRenderBuffer);
}