
// ChildView.cpp : implementation of the CChildView class
//

#include "pch.h"
#include "framework.h"
#include "Project1.h"
#include "ChildView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChildView

CChildView::CChildView()
{
    m_camera.Set(20, 10, 50, 0, 0, 0, 0, 1, 0);

    CGrPtr<CGrComposite> scene = new CGrComposite;
    m_scene = scene;

    // A red box
    CGrPtr<CGrMaterial> redpaint = new CGrMaterial;
    redpaint->AmbientAndDiffuse(0.8f, 0.0f, 0.0f);
    scene->Child(redpaint);

    CGrPtr<CGrComposite> redbox = new CGrComposite;
    redpaint->Child(redbox);
    redbox->Box(1, 1, 1, 5, 5, 5);

    // A white box
    CGrPtr<CGrMaterial> whitepaint = new CGrMaterial;
    whitepaint->AmbientAndDiffuse(0.8f, 0.8f, 0.8f);
    scene->Child(whitepaint);

    CGrPtr<CGrComposite> whitebox = new CGrComposite;
    whitepaint->Child(whitebox);
    whitebox->Box(-10, -10, -10, 5, 5, 5);
}

CChildView::~CChildView()
{
}


BEGIN_MESSAGE_MAP(CChildView, COpenGLWnd)
	ON_WM_PAINT()
    ON_WM_LBUTTONDOWN()
    ON_WM_MOUSEMOVE()
    ON_WM_RBUTTONDOWN()
END_MESSAGE_MAP()



// CChildView message handlers

BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!COpenGLWnd::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		::LoadCursor(nullptr, IDC_ARROW), reinterpret_cast<HBRUSH>(COLOR_WINDOW+1), nullptr);

	return TRUE;
}

void CChildView::OnGLDraw(CDC* pDC)
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //
// Set up the camera
//
    int width, height;
    GetSize(width, height);
    m_camera.Apply(width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // Determine the screen size so we can determine the aspect ratio
    GetSize(width, height);
    m_camera.Apply(width, height);

    //GLdouble aspectratio = GLdouble(width) / GLdouble(height);

    //// Set the camera parameters
    //gluPerspective(25.,         // Vertical FOV degrees.
    //    aspectratio, // The aspect ratio.
    //    10.,         // Near clipping 40/130
    //    200.);       // Far clipping

    //// Set the camera location
    //glMatrixMode(GL_MODELVIEW);
    //glLoadIdentity();

    gluLookAt(20., 10., 50.,    // eye x,y,z
        0., 0., 0.,       // center x,y,z
        0., 1., 0.);      // Up direction

    //
    // Some standard parameters
    //

    // Enable depth test
    glEnable(GL_DEPTH_TEST);

    // Cull backfacing polygons
    glCullFace(GL_BACK);
    glEnable(GL_CULL_FACE);
    // Enable lighting
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    // Draw a coordinate axis
    glColor3d(0., 1., 1.);

    glBegin(GL_LINES);
    glVertex3d(0., 0., 0.);
    glVertex3d(12., 0., 0.);
    glVertex3d(0., 0., 0.);
    glVertex3d(0., 12., 0.);
    glVertex3d(0., 0., 0.);
    glVertex3d(0., 0., 12.);
    glEnd();

    m_scene->glRender();
}
void CChildView::OnLButtonDown(UINT nFlags, CPoint point)
{
    m_camera.MouseDown(point.x, point.y);

    COpenGLWnd::OnLButtonDown(nFlags, point);
}


void CChildView::OnMouseMove(UINT nFlags, CPoint point)
{
    if (m_camera.MouseMove(point.x, point.y, nFlags))
        Invalidate();

    COpenGLWnd::OnMouseMove(nFlags, point);
}

void CChildView::OnRButtonDown(UINT nFlags, CPoint point)
{
    m_camera.MouseDown(point.x, point.y, 2);

    COpenGLWnd::OnRButtonDown(nFlags, point);
}
