#pragma once
#include <list>
#include "graphics/GrRenderer.h"
#include "graphics/RayIntersection.h"
class CMyRaytraceRenderer :
    public CGrRenderer
{
private:
    int     m_rayimagewidth = 0;
    int     m_rayimageheight = 0;
    BYTE** m_rayimage = nullptr;
    CWnd* m_window = nullptr;
    CGrMaterial* m_material;
    CRayIntersection m_intersection;
    std::list<CGrTransform> m_mstack;
    void RayColor(const CRay& ray, double color[3], int recursionLevel, const CRayIntersection::Object* ignore);
public:
    CMyRaytraceRenderer() { }
    // setter
    void SetWindow(CWnd* p_window) { m_window = p_window; }
    void SetImage(BYTE** rayimage, int imagewidth, int imageheight) { m_rayimage = rayimage; m_rayimagewidth = imagewidth; m_rayimageheight = imageheight; }
    void RendererMaterial(CGrMaterial* p_material);
    void RendererPushMatrix();
    void RendererPopMatrix();
    void RendererRotate(double angle, double x, double y, double z);
    void RendererTranslate(double x, double y, double z);
    void RendererEndPolygon();
    bool RendererStart();
    bool RendererEnd();
};


