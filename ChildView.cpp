
// ChildView.cpp : implementation of the CChildView class
//

#include "pch.h"
#include "graphics/OpenGLRenderer.h"
#include "CMyRaytraceRenderer.h"
#include "framework.h"
#include "Project1.h"
#include "ChildView.h"
#include "graphics/GrTexture.h"
#include <cmath>
#include "suisei.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

void AddSphere(CGrComposite* comp, double cx, double cy, double cz, double r, int slices, int stacks, CGrTexture* texture = nullptr) {
    for (int i = 0; i < stacks; i++) {
        double lat0 = M_PI * (-0.5 + (double)(i) / stacks);
        double y0  = r * sin(lat0);
        double zr0 = r * cos(lat0);

        double lat1 = M_PI * (-0.5 + (double)(i+1) / stacks);
        double y1  = r * sin(lat1);
        double zr1 = r * cos(lat1);

        for (int j = 0; j < slices; j++) {
            double lng0 = 2 * M_PI * (double)(j) / slices;
            double x0 = zr0 * cos(lng0);
            double z0 = zr0 * sin(lng0);

            double lng1 = 2 * M_PI * (double)(j+1) / slices;
            double x1 = zr0 * cos(lng1);
            double z1 = zr0 * sin(lng1);

            double x2 = zr1 * cos(lng1);
            double z2 = zr1 * sin(lng1);

            double x3 = zr1 * cos(lng0);
            double z3 = zr1 * sin(lng0);

            CGrPoint p0(cx + x0, cy + y0, cz + z0);
            CGrPoint p1(cx + x1, cy + y0, cz + z1);
            CGrPoint p2(cx + x2, cy + y1, cz + z2);
            CGrPoint p3(cx + x3, cy + y1, cz + z3);

            if (i == 0) {
                comp->Poly3(p0, p3, p2, texture);
            } else if (i == stacks - 1) {
                comp->Poly3(p0, p3, p1, texture);
            } else {
                comp->Poly4(p0, p3, p2, p1, texture);
            }
        }
    }
}

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
    redpaint->Specular(0.8f, 0.8f, 0.8f);
    redpaint->Shininess(40.0f);
    scene->Child(redpaint);

    CGrPtr<CGrTexture> marble = new CGrTexture;
    marble->LoadFile(L"textures/marble02.bmp");

    CGrPtr<CGrComposite> redbox = new CGrComposite;
    redpaint->Child(redbox);
    redbox->Box(1, 1, 1, 5, 5, 5, marble);

    // A white box
    CGrPtr<CGrMaterial> whitepaint = new CGrMaterial;
    whitepaint->AmbientAndDiffuse(0.8f, 0.8f, 0.8f);
    whitepaint->Specular(0.1f, 0.1f, 0.1f);  // reduced specular for wood, so it won't reflect perfectly
    whitepaint->Shininess(10.0f);
    scene->Child(whitepaint);

    CGrPtr<CGrTexture> plank = new CGrTexture;
    plank->LoadFile(L"textures/plank01.bmp");

    CGrPtr<CGrComposite> whitebox = new CGrComposite;
    whitepaint->Child(whitebox);
    whitebox->Box(-10, -10, -10, 5, 5, 5, plank);

    // A blue sphere
    CGrPtr<CGrMaterial> bluepaint = new CGrMaterial;
    // Ambient and diffuse is handled by texture mostly if present, but base color adds mod. Use white to keep texture colors.
    bluepaint->AmbientAndDiffuse(0.8f, 0.8f, 0.8f);
    bluepaint->Specular(0.9f, 0.9f, 0.9f);
    bluepaint->Shininess(80.0f);
    scene->Child(bluepaint);

    CGrPtr<CGrTexture> worldmap = new CGrTexture;
    worldmap->LoadFile(L"textures/worldmap.bmp");

    CGrPtr<CGrComposite> spherecomp = new CGrComposite;
    bluepaint->Child(spherecomp);

    // AddSphere(comp, cx, cy, cz, r, slices, stacks, texture)
    AddSphere(spherecomp, -4, 2, 8, 4, 30, 30, worldmap);

    // Provide a massive floor slightly beneath both boxes to catch their shadows safely!
    //CGrPtr<CGrMaterial> floorpaint = new CGrMaterial;
    //floorpaint->AmbientAndDiffuse(0.6f, 0.6f, 0.6f);
    //floorpaint->Specular(0.2f, 0.2f, 0.2f);
    //floorpaint->Shininess(50.0f);
    //scene->Child(floorpaint);
    //
    //CGrPtr<CGrComposite> floorbox = new CGrComposite;
    //floorpaint->Child(floorbox);
    //floorbox->Box(-50, -15, -50, 100, 2, 100);

    AddSteve(scene, 24, -7, -8);
    AddCrescentBardiche(scene, 15, -5, -4);

    m_raytrace = false;
}

CChildView::~CChildView()
{
    delete[] m_rayimage[0];
    delete[] m_rayimage;
}

//
// Name :         CChildView::ConfigureRenderer()
// Description :  Configures our renderer so it is able to render the scene.
//                Indicates how we'll do our projection, where the camera is,
//                and where any lights are located.
//
void CChildView::ConfigureRenderer(CGrRenderer* p_renderer)
{
    // Determine the screen size so we can determine the aspect ratio
    int width, height;
    GetSize(width, height);
    double aspectratio = double(width) / double(height);

    //
    // Set up the camera in the renderer
    //

    p_renderer->Perspective(m_camera.FieldOfView(),
        aspectratio, // The aspect ratio.
        20., // Near clipping
        1000.); // Far clipping

    // m_camera.FieldOfView is the vertical field of view in degrees.

    //
    // Set the camera location
    //

    p_renderer->LookAt(
        m_camera.Eye()[0], m_camera.Eye()[1], m_camera.Eye()[2],
        m_camera.Center()[0], m_camera.Center()[1], m_camera.Center()[2],
        m_camera.Up()[0], m_camera.Up()[1], m_camera.Up()[2]
    );

    //
    // Set the light locations and colors
    //

    float dimd = 0.5f;
    GLfloat dim[] = { dimd, dimd, dimd, 1.0f };
    GLfloat brightwhite[] = { 1.f, 1.f, 1.f, 1.0f };

    p_renderer->AddLight(CGrPoint(1, 0.5, 1.2, 0),
        dim, brightwhite, brightwhite);

    // Add a second light array
    GLfloat dim2[] = { 0.1f, 0.1f, 0.1f, 1.0f };
    GLfloat secondlight[] = { 0.6f, 0.6f, 0.6f, 1.0f };
    p_renderer->AddLight(CGrPoint(-1, 0.5, -1.2, 0),
        dim2, secondlight, secondlight);

}
BEGIN_MESSAGE_MAP(CChildView, COpenGLWnd)
	ON_WM_PAINT()
    ON_WM_LBUTTONDOWN()
    ON_WM_MOUSEMOVE()
    ON_WM_RBUTTONDOWN()
    ON_COMMAND(ID_RENDER_RAYTRACE, &CChildView::OnRenderRaytrace)
    ON_UPDATE_COMMAND_UI(ID_RENDER_RAYTRACE, &CChildView::OnUpdateRenderRaytrace)
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
    if (m_raytrace)
    {
        // Clear the color buffer
        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Set up for parallel projection
        int width, height;
        GetSize(width, height);

        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(0, width, 0, height, -1, 1);

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        // If we got it, draw it
        if (m_rayimage)
        {
            glRasterPos3i(0, 0, 0);
            glDrawPixels(m_rayimagewidth, m_rayimageheight,
                GL_RGB, GL_UNSIGNED_BYTE, m_rayimage[0]);
        }

        glFlush();
    }
    else
    {
        //
        // Instantiate a renderer
        //

        COpenGLRenderer renderer;

        // Configure the renderer
        ConfigureRenderer(&renderer);

        //
        // Render the scene
        //

        renderer.Render(m_scene);
    }

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

void CChildView::OnRenderRaytrace()
{
    // TODO: Add your command handler code here
    m_raytrace = !m_raytrace;
    Invalidate();
    if (!m_raytrace)
        return;

	// delete the old ray image if it exists
    if(m_rayimage)
    {
        delete[] m_rayimage[0];
        delete[] m_rayimage;
        m_rayimage = nullptr;
	}

    GetSize(m_rayimagewidth, m_rayimageheight);
    m_rayimage = new BYTE * [m_rayimageheight];
    int rowwid = m_rayimagewidth * 3;
    while (rowwid % 4)
        rowwid++;
    m_rayimage[0] = new BYTE[m_rayimageheight * rowwid];

    for (int i = 1; i < m_rayimageheight; i++)
    {
		// Set up the row pointers for the image
        m_rayimage[i] = m_rayimage[0] + i * rowwid;
    }

    for (int i = 0; i < m_rayimageheight; i++)
    {
        // Fill the image with blue
        for (int j = 0; j < m_rayimagewidth; j++)
        {
            m_rayimage[i][j * 3] = 0;               // red
            m_rayimage[i][j * 3 + 1] = 0;           // green
            m_rayimage[i][j * 3 + 2] = BYTE(255);   // blue
        }
    }

    // Instantiate a raytrace object
    CMyRaytraceRenderer raytrace;

    // Generic configurations for all renderers
    ConfigureRenderer(&raytrace);

    //
    // Render the Scene
    //
    raytrace.SetImage(m_rayimage, m_rayimagewidth, m_rayimageheight);
    raytrace.SetWindow(this);
    raytrace.Render(m_scene);
    Invalidate();
}

void CChildView::OnUpdateRenderRaytrace(CCmdUI* pCmdUI)
{
    pCmdUI->SetCheck(m_raytrace);

}
