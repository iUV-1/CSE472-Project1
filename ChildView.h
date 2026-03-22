
// ChildView.h : interface of the CChildView class
//


#pragma once
#include "graphics/OpenGLWnd.h"
#include "graphics/GrObject.h"
#include "graphics/GrCamera.h"

// CChildView window

class CChildView : public COpenGLWnd
{
// Construction
public:
	CChildView();

// Attributes
public:

// Operations
public:

// Overrides
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	
private:
	CGrPtr<CGrObject> m_scene;
	CGrCamera m_camera;
	BYTE** m_rayimage = nullptr;
	int         m_rayimagewidth;
	int         m_rayimageheight;
// Implementation
public:
	virtual ~CChildView();
	void ConfigureRenderer(CGrRenderer* p_renderer);
	virtual void OnGLDraw(CDC* pDC);

	// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	bool m_raytrace;
	afx_msg void OnRenderRaytrace();
	afx_msg void OnUpdateRenderRaytrace(CCmdUI* pCmdUI);
};

