#include "pch.h"
#include <cmath>
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

constexpr double M_PI = 3.1415; // blah blah blah

double degToRad(double angle) {
    return angle * M_PI / 180;
}

void setPixel(BYTE** image, int x, int y, BYTE r, BYTE g, BYTE b) {
    image[y][x * 3] = r;
    image[y][x * 3 + 1] = g;
    image[x][x * 3 + 2] = b;
}

bool CMyRaytraceRenderer::RendererEnd()
{
    m_intersection.LoadingComplete();
    
    double tanAngle = tan( degToRad(ProjectionAngle() / 2) );
    double yhit = tanAngle * 2; // beneath is jst 1
    double ymin = -tanAngle;

    double xmin = ymin * ProjectionAspect();
    double xwid = -xmin * 2;


    for (int r = 0; r < m_rayimageheight; r++) {
        for (int c = 0; c < m_rayimagewidth; c++) {
            // we choose center of the square per pixel
            double x = xmin + (c + 0.5) / m_rayimagewidth * xwid;
            double y = ymin + (r + 0.5) / m_rayimageheight * yhit;

            //Construct a Ray
            CRay ray(CGrPoint(0, 0, 0), Normalize3(CGrPoint(x, y, -1, 0)));

            double t;                                   // Will be distance to intersection
            CGrPoint intersect;                         // Will by x,y,z location of intersection
            const CRayIntersection::Object* nearest;    // Pointer to intersecting object
            if (m_intersection.Intersect(ray, 1e20, NULL, nearest, t, intersect))
            {
                // We hit something...
                // Determine information about the intersection
                CGrPoint N;
                CGrMaterial* material;
                CGrTexture* texture;
                CGrPoint texcoord;

                m_intersection.IntersectInfo(ray, nearest, t,
                    N, material, texture, texcoord);

                if (material != NULL)
                {
                    double color[3] = { 0.0, 0.0, 0.0 };

                    // View vector V: from intersect to eye (which is at 0,0,0)
                    CGrPoint V = Normalize3(-intersect);

                    // Iterate over all lights
                    for (int i = 0; i < LightCnt(); i++)
                    {
                        const Light& light = GetLight(i);
                        
                        // Add light's ambient component
                        color[0] += material->Ambient(0) * light.m_ambient[0];
                        color[1] += material->Ambient(1) * light.m_ambient[1];
                        color[2] += material->Ambient(2) * light.m_ambient[2];

                        CGrPoint L;
                        if (light.m_pos.W() == 0.0) {
                            // Directional light
                            L = Normalize3(light.m_pos);
                        } else {
                            // Point light
                            L = Normalize3(light.m_pos - intersect);
                        }

                        // Diffuse term
                        double NdotL = Dot3(N, L);
                        if (NdotL > 0.0) {
                            color[0] += material->Diffuse(0) * light.m_diffuse[0] * NdotL;
                            color[1] += material->Diffuse(1) * light.m_diffuse[1] * NdotL;
                            color[2] += material->Diffuse(2) * light.m_diffuse[2] * NdotL;

                            // Specular term
                            CGrPoint H = Normalize3(L + V);
                            double NdotH = Dot3(N, H);
                            if (NdotH > 0.0 && material->Shininess() > 0.0) {
                                double spec = pow(NdotH, material->Shininess());
                                color[0] += material->Specular(0) * light.m_specular[0] * spec;
                                color[1] += material->Specular(1) * light.m_specular[1] * spec;
                                color[2] += material->Specular(2) * light.m_specular[2] * spec;
                            }
                        }
                    }

                    // Clamp to 0-1 and scale to 0-255
                    for (int i = 0; i < 3; i++) {
                        if (color[i] > 1.0) color[i] = 1.0;
                        if (color[i] < 0.0) color[i] = 0.0;
                    }

                    m_rayimage[r][c * 3] = BYTE(color[0] * 255.0);
                    m_rayimage[r][c * 3 + 1] = BYTE(color[1] * 255.0);
                    m_rayimage[r][c * 3 + 2] = BYTE(color[2] * 255.0);
                }
            }
            else
            {
                // We hit nothing...
                m_rayimage[r][c * 3] = 0;
                m_rayimage[r][c * 3 + 1] = 0;
                m_rayimage[r][c * 3 + 2] = 0;
            }
        }
        if ((r % 50) == 0)
        {
            m_window->Invalidate();
            MSG msg;
            while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
                DispatchMessage(&msg);
        }
    }


    return true;
}
