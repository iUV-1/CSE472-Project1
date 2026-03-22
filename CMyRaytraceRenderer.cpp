#include "pch.h"
#include "CMyRaytraceRenderer.h"

void CMyRaytraceRenderer::RendererMaterial(CGrMaterial* p_material)
{
    m_material = p_material;
}

void CMyRaytraceRenderer::RendererPushMatrix() 
{
    m_mstack.push_back(m_mstack.back());
}

void CMyRaytraceRenderer::RendererPopMatrix() 
{
    m_mstack.pop_back();
}

void CMyRaytraceRenderer::RendererRotate(double angle, double x, double y, double z) 
{
    CGrTransform t;
    CGrPoint p{ x, y, z };
    t.SetRotate(angle, p);
    m_mstack.push_back(t);
}

void CMyRaytraceRenderer::RendererTranslate(double x, double y, double z) 
{
    CGrTransform t;
    t.SetTranslate(x, y, z);
    m_mstack.push_back(t);
}

bool CMyRaytraceRenderer::RendererStart()
{
    m_mstack.clear();
    // We have to do all of the matrix work ourselves.
       // Set up the matrix stack.

    CGrTransform t;
    t.SetLookAt(Eye().X(), Eye().Y(), Eye().Z(),
        Center().X(), Center().Y(), Center().Z(),
        Up().X(), Up().Y(), Up().Z());
    m_mstack.push_back(t);
    return true;
}

//
// Name : CMyRaytraceRenderer::RendererEndPolygon()
// Description : End definition of a polygon. The superclass has
// already collected the polygon information
//

void CMyRaytraceRenderer::RendererEndPolygon()
{
    const std::list<CGrPoint>& vertices = PolyVertices();
    const std::list<CGrPoint>& normals = PolyNormals();
    const std::list<CGrPoint>& tvertices = PolyTexVertices();

    // Allocate a new polygon in the ray intersection system
    m_intersection.PolygonBegin();
    m_intersection.Material(m_material);

    if (PolyTexture())
    {
        m_intersection.Texture(PolyTexture());
    }

    std::list<CGrPoint>::const_iterator normal = normals.begin();
    std::list<CGrPoint>::const_iterator tvertex = tvertices.begin();

    for (std::list<CGrPoint>::const_iterator i = vertices.begin(); i != vertices.end(); i++)
    {
        if (normal != normals.end())
        {
            m_intersection.Normal(m_mstack.back() * *normal);
            normal++;
        }

        if (tvertex != tvertices.end())
        {
            m_intersection.TexVertex(*tvertex);
            tvertex++;
        }

        m_intersection.Vertex(m_mstack.back() * *i);
    }

    m_intersection.PolygonEnd();
}
bool CMyRaytraceRenderer::RendererEnd()
{
    m_intersection.LoadingComplete();
    double angle = ProjectionAngle();
    double ratio = ProjectionAspect();


    return false;
}
