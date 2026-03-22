#pragma once
#include "graphics/GrRenderer.h"
class CMyRaytraceRenderer :
    public CGrRenderer
{
private:
    int     m_rayimagewidth = 0;
    int     m_rayimageheight = 0;
    BYTE** m_rayimage = nullptr;
    CWnd* m_window = nullptr;
public:
    CMyRaytraceRenderer() { }
    // setter
    void SetWindow(CWnd* p_window) { m_window = p_window; }
    void SetImage(BYTE** rayimage, int imagewidth, int imageheight) { m_rayimage = rayimage; m_rayimagewidth = imagewidth; m_rayimageheight = imageheight; }
};

