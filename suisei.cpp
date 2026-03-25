#include "pch.h"
#include "suisei.h"
#include "graphics/GrTexture.h"

namespace
{
    struct UvRect
    {
        double u0;
        double v0;
        double u1;
        double v1;
    };

    void AddFace(CGrComposite* root,
        const CGrPoint& a, const CGrPoint& b, const CGrPoint& c, const CGrPoint& d,
        CGrTexture* texture, int texW, int texH, const UvRect& uv)
    {
        CGrPtr<CGrPolygon> poly = new CGrPolygon;
        poly->AddVertices4(a, b, c, d, true);
        if (texture)
        {
            poly->Texture(texture);
            poly->AddTex2d(uv.u0 / texW, uv.v0 / texH);
            poly->AddTex2d(uv.u1 / texW, uv.v0 / texH);
            poly->AddTex2d(uv.u1 / texW, uv.v1 / texH);
            poly->AddTex2d(uv.u0 / texW, uv.v1 / texH);
        }

        root->Child(poly);
    }

    void AddUvBox(CGrComposite* root, double x, double y, double z, double dx, double dy, double dz,
        CGrTexture* texture, int texW, int texH,
        const UvRect& front, const UvRect& right, const UvRect& back,
        const UvRect& left, const UvRect& top, const UvRect& bottom)
    {
        const CGrPoint f0(x, y, z + dz);
        const CGrPoint f1(x + dx, y, z + dz);
        const CGrPoint f2(x + dx, y + dy, z + dz);
        const CGrPoint f3(x, y + dy, z + dz);

        const CGrPoint r0(x + dx, y, z + dz);
        const CGrPoint r1(x + dx, y, z);
        const CGrPoint r2(x + dx, y + dy, z);
        const CGrPoint r3(x + dx, y + dy, z + dz);

        const CGrPoint b0(x + dx, y, z);
        const CGrPoint b1(x, y, z);
        const CGrPoint b2(x, y + dy, z);
        const CGrPoint b3(x + dx, y + dy, z);

        const CGrPoint l0(x, y, z);
        const CGrPoint l1(x, y, z + dz);
        const CGrPoint l2(x, y + dy, z + dz);
        const CGrPoint l3(x, y + dy, z);

        const CGrPoint t0(x, y + dy, z + dz);
        const CGrPoint t1(x + dx, y + dy, z + dz);
        const CGrPoint t2(x + dx, y + dy, z);
        const CGrPoint t3(x, y + dy, z);

        const CGrPoint d0(x, y, z);
        const CGrPoint d1(x + dx, y, z);
        const CGrPoint d2(x + dx, y, z + dz);
        const CGrPoint d3(x, y, z + dz);

        AddFace(root, f0, f1, f2, f3, texture, texW, texH, front);
        AddFace(root, r0, r1, r2, r3, texture, texW, texH, right);
        AddFace(root, b0, b1, b2, b3, texture, texW, texH, back);
        AddFace(root, l0, l1, l2, l3, texture, texW, texH, left);
        AddFace(root, t0, t1, t2, t3, texture, texW, texH, top);
        AddFace(root, d0, d1, d2, d3, texture, texW, texH, bottom);
    }

    void FillRect(CGrTexture* texture, int x, int y, int w, int h, int r, int g, int b)
    {
        for (int yy = y; yy < y + h; yy++)
        {
            for (int xx = x; xx < x + w; xx++)
            {
                texture->Set(xx, yy, r, g, b);
            }
        }
    }

    CGrTexture* CreateSteveTexture()
    {
        CGrPtr<CGrTexture> skin = new CGrTexture;
        skin->SetSize(64, 64);
        skin->Fill(0, 0, 0);

        FillRect(skin, 0, 0, 64, 64, 170, 170, 170);

        FillRect(skin, 8, 8, 8, 8, 220, 170, 140);   // head front
        FillRect(skin, 20, 20, 8, 12, 70, 175, 185); // torso front
        FillRect(skin, 44, 20, 4, 12, 220, 170, 140); // right arm front
        FillRect(skin, 4, 20, 4, 12, 95, 95, 200);   // right leg front

        FillRect(skin, 24, 8, 8, 8, 180, 130, 105);  // head back
        FillRect(skin, 32, 20, 8, 12, 55, 130, 140);  // torso back

        return skin;
    }

    void BuildSteveTextured(CGrComposite* root)
    {
        const int texSize = 64;
        CGrPtr<CGrTexture> steveTexture = CreateSteveTexture();

        AddUvBox(root, -1.5, 8, -1.5, 3, 3, 3, steveTexture, texSize, texSize,
            {8, 8, 16, 16}, {0, 8, 8, 16}, {24, 8, 32, 16},
            {16, 8, 24, 16}, {8, 0, 16, 8}, {16, 0, 24, 8});

        AddUvBox(root, -1.5, 4, -0.75, 3, 4, 1.5, steveTexture, texSize, texSize,
            {20, 20, 28, 32}, {16, 20, 20, 32}, {32, 20, 40, 32},
            {28, 20, 32, 32}, {20, 16, 28, 20}, {28, 16, 36, 20});

        AddUvBox(root, -2.5, 4, -0.75, 1, 4, 1.5, steveTexture, texSize, texSize,
            {44, 20, 48, 32}, {40, 20, 44, 32}, {52, 20, 56, 32},
            {48, 20, 52, 32}, {44, 16, 48, 20}, {48, 16, 52, 20});

        AddUvBox(root, 1.5, 4, -0.75, 1, 4, 1.5, steveTexture, texSize, texSize,
            {44, 20, 48, 32}, {40, 20, 44, 32}, {52, 20, 56, 32},
            {48, 20, 52, 32}, {44, 16, 48, 20}, {48, 16, 52, 20});

        AddUvBox(root, -1.4, 0, -0.75, 1.2, 4, 1.5, steveTexture, texSize, texSize,
            {4, 20, 8, 32}, {0, 20, 4, 32}, {12, 20, 16, 32},
            {8, 20, 12, 32}, {4, 16, 8, 20}, {8, 16, 12, 20});

        AddUvBox(root, 0.2, 0, -0.75, 1.2, 4, 1.5, steveTexture, texSize, texSize,
            {4, 20, 8, 32}, {0, 20, 4, 32}, {12, 20, 16, 32},
            {8, 20, 12, 32}, {4, 16, 8, 20}, {8, 16, 12, 20});
    }
}

void AddSteve(CGrComposite* scene, double x, double y, double z)
{
    CGrPtr<CGrTranslate> steveTrans = new CGrTranslate(x, y, z);
    scene->Child(steveTrans);

    CGrPtr<CGrComposite> steveRoot = new CGrComposite;
    steveTrans->Child(steveRoot);

    CGrPtr<CGrMaterial> steveMaterial = new CGrMaterial;
    steveMaterial->AmbientAndDiffuse(1.f, 1.f, 1.f);
    steveMaterial->Specular(0.05f, 0.05f, 0.05f);
    steveMaterial->Shininess(8.0f);
    steveRoot->Child(steveMaterial);

    CGrPtr<CGrComposite> steveMesh = new CGrComposite;
    steveMaterial->Child(steveMesh);
    BuildSteveTextured(steveMesh);
}

void AddCrescentBardiche(CGrComposite* scene, double x, double y, double z)
{
    CGrPtr<CGrMaterial> bardicheMat = new CGrMaterial;
    bardicheMat->AmbientAndDiffuse(0.4f, 0.7f, 1.0f);
    bardicheMat->Specular(0.8f, 0.8f, 0.8f);
    bardicheMat->Shininess(90.0f);
    scene->Child(bardicheMat);

    CGrPtr<CGrComposite> bardiche = new CGrComposite;
    CGrPtr<CGrTranslate> bardicheTrans = new CGrTranslate(x, y, z);
    bardicheTrans->Child(bardiche);
    bardicheMat->Child(bardicheTrans);

    CGrPtr<CGrTexture> texSmallblade = new CGrTexture; texSmallblade->LoadFile(L"textures/item/custom/smallblade.bmp");
    CGrPtr<CGrTexture> texSmallblade1 = new CGrTexture; texSmallblade1->LoadFile(L"textures/item/custom/smallblade1.bmp");
    CGrPtr<CGrTexture> texSmallblade2 = new CGrTexture; texSmallblade2->LoadFile(L"textures/item/custom/smallblade2.bmp");
    CGrPtr<CGrTexture> texOrnament1 = new CGrTexture; texOrnament1->LoadFile(L"textures/item/custom/ornament1.bmp");
    CGrPtr<CGrTexture> texOrnament2 = new CGrTexture; texOrnament2->LoadFile(L"textures/item/custom/ornament2.bmp");
    CGrPtr<CGrTexture> texOrnament3 = new CGrTexture; texOrnament3->LoadFile(L"textures/item/custom/ornament3.bmp");
    CGrPtr<CGrTexture> texOrnament4 = new CGrTexture; texOrnament4->LoadFile(L"textures/item/custom/ornament4.bmp");
    CGrPtr<CGrTexture> texPole = new CGrTexture; texPole->LoadFile(L"textures/item/custom/pole.bmp");
    CGrPtr<CGrTexture> texCrystal1 = new CGrTexture; texCrystal1->LoadFile(L"textures/item/custom/crystal1.bmp");
    CGrPtr<CGrTexture> texCrystal2 = new CGrTexture; texCrystal2->LoadFile(L"textures/item/custom/crystal2.bmp");
    CGrPtr<CGrTexture> texLeverage1 = new CGrTexture; texLeverage1->LoadFile(L"textures/item/custom/leverage1.bmp");
    CGrPtr<CGrTexture> texLeverage2 = new CGrTexture; texLeverage2->LoadFile(L"textures/item/custom/leverage2.bmp");
    CGrPtr<CGrTexture> texBladebeeg = new CGrTexture; texBladebeeg->LoadFile(L"textures/item/custom/bladebeeg.bmp");
    CGrPtr<CGrTexture> texBladebeeg1 = new CGrTexture; texBladebeeg1->LoadFile(L"textures/item/custom/bladebeeg1.bmp");
    CGrPtr<CGrTexture> texCube1 = new CGrTexture; texCube1->LoadFile(L"textures/item/custom/cube1.bmp");
    CGrPtr<CGrTexture> texCube2 = new CGrTexture; texCube2->LoadFile(L"textures/item/custom/cube2.bmp");
    CGrPtr<CGrTexture> texCube1down = new CGrTexture; texCube1down->LoadFile(L"textures/item/custom/cube1down.bmp");
    CGrPtr<CGrTexture> texCube2down = new CGrTexture; texCube2down->LoadFile(L"textures/item/custom/cube2down.bmp");
    CGrPtr<CGrTexture> texStar1 = new CGrTexture; texStar1->LoadFile(L"textures/item/custom/star1.bmp");
    CGrPtr<CGrTexture> texStar1p = new CGrTexture; texStar1p->LoadFile(L"textures/item/custom/star1p.bmp");
    CGrPtr<CGrTexture> texStar1q = new CGrTexture; texStar1q->LoadFile(L"textures/item/custom/star1q.bmp");
    CGrPtr<CGrTexture> texStar1m = new CGrTexture; texStar1m->LoadFile(L"textures/item/custom/star1m.bmp");
    CGrPtr<CGrTexture> texStar1n = new CGrTexture; texStar1n->LoadFile(L"textures/item/custom/star1n.bmp");
    CGrPtr<CGrTexture> texStar2 = new CGrTexture; texStar2->LoadFile(L"textures/item/custom/star2.bmp");
    CGrPtr<CGrTexture> texStar2p = new CGrTexture; texStar2p->LoadFile(L"textures/item/custom/star2p.bmp");
    CGrPtr<CGrTexture> texStar2q = new CGrTexture; texStar2q->LoadFile(L"textures/item/custom/star2q.bmp");
    CGrPtr<CGrTexture> texStar2m = new CGrTexture; texStar2m->LoadFile(L"textures/item/custom/star2m.bmp");
    CGrPtr<CGrTexture> texStar2n = new CGrTexture; texStar2n->LoadFile(L"textures/item/custom/star2n.bmp");

    CGrPtr<CGrComposite> b_ornament1_11c264dd = new CGrComposite;
    bardiche->Child(b_ornament1_11c264dd);
    b_ornament1_11c264dd->Box(3.35, 7.30, 3.60, 0.60, 2.70, 0.60, texOrnament1);
    CGrPtr<CGrComposite> b_ornament2_ae3b1681 = new CGrComposite;
    bardiche->Child(b_ornament2_ae3b1681);
    b_ornament2_ae3b1681->Box(3.35, 10.20, 3.60, 0.60, 2.30, 0.60, texOrnament2);
    CGrPtr<CGrComposite> b_ornament3_7058703f = new CGrComposite;
    bardiche->Child(b_ornament3_7058703f);
    b_ornament3_7058703f->Box(3.30, 6.85, 3.55, 0.70, 0.50, 0.70, texOrnament3);
    CGrPtr<CGrComposite> b_ornament4_514ff80d = new CGrComposite;
    bardiche->Child(b_ornament4_514ff80d);
    b_ornament4_514ff80d->Box(3.30, 9.85, 3.55, 0.70, 0.50, 0.70, texOrnament4);
    CGrPtr<CGrComposite> b_leverage1_3ff91814 = new CGrComposite;
    CGrPtr<CGrTranslate> t1_3ff91814 = new CGrTranslate(3.65, 12.20, 4.95);
    CGrPtr<CGrRotate> rot_3ff91814 = new CGrRotate(0, 0, 1, 0);
    CGrPtr<CGrTranslate> t2_3ff91814 = new CGrTranslate(-3.65, -12.20, -4.95);
    t1_3ff91814->Child(rot_3ff91814);
    rot_3ff91814->Child(t2_3ff91814);
    t2_3ff91814->Child(b_leverage1_3ff91814);
    bardiche->Child(t1_3ff91814);
    b_leverage1_3ff91814->Box(3.5, 11.70, 2.85, 0.30, 0.40, 2.15, texLeverage1);
    CGrPtr<CGrComposite> b_leverage2_74f38785 = new CGrComposite;
    CGrPtr<CGrTranslate> t1_74f38785 = new CGrTranslate(3.65, 12.20, 4.95);
    CGrPtr<CGrRotate> rot_74f38785 = new CGrRotate(0, 0, 1, 0);
    CGrPtr<CGrTranslate> t2_74f38785 = new CGrTranslate(-3.65, -12.20, -4.95);
    t1_74f38785->Child(rot_74f38785);
    rot_74f38785->Child(t2_74f38785);
    t2_74f38785->Child(b_leverage2_74f38785);
    bardiche->Child(t1_74f38785);
    b_leverage2_74f38785->Box(3.5, 8.80, 2.85, 0.30, 0.40, 1.20, texLeverage2);
    CGrPtr<CGrComposite> b_bladesmall_a8ad9ceb = new CGrComposite;
    CGrPtr<CGrTranslate> t1_a8ad9ceb = new CGrTranslate(3.65, 11.90, 4.95);
    CGrPtr<CGrRotate> rot_a8ad9ceb = new CGrRotate(-22.5, 1, 0, 0);
    CGrPtr<CGrTranslate> t2_a8ad9ceb = new CGrTranslate(-3.65, -11.90, -4.95);
    t1_a8ad9ceb->Child(rot_a8ad9ceb);
    rot_a8ad9ceb->Child(t2_a8ad9ceb);
    t2_a8ad9ceb->Child(b_bladesmall_a8ad9ceb);
    bardiche->Child(t1_a8ad9ceb);
    b_bladesmall_a8ad9ceb->Box(3.45, 11.10, 4.70, 0.40, 1.40, 0.70, texSmallblade1);
    CGrPtr<CGrComposite> b_bladesmall_6d2d0a55 = new CGrComposite;
    CGrPtr<CGrTranslate> t1_6d2d0a55 = new CGrTranslate(3.65, 11.90, 4.95);
    CGrPtr<CGrRotate> rot_6d2d0a55 = new CGrRotate(0, 0, 1, 0);
    CGrPtr<CGrTranslate> t2_6d2d0a55 = new CGrTranslate(-3.65, -11.90, -4.95);
    t1_6d2d0a55->Child(rot_6d2d0a55);
    rot_6d2d0a55->Child(t2_6d2d0a55);
    t2_6d2d0a55->Child(b_bladesmall_6d2d0a55);
    bardiche->Child(t1_6d2d0a55);
    b_bladesmall_6d2d0a55->Box(3.45, 10.35, 5, 0.40, 1.00, 0.70, texSmallblade2);
    CGrPtr<CGrComposite> b_bladesmall_39699aa2 = new CGrComposite;
    CGrPtr<CGrTranslate> t1_39699aa2 = new CGrTranslate(3.65, 11.90, 4.95);
    CGrPtr<CGrRotate> rot_39699aa2 = new CGrRotate(0, 0, 1, 0);
    CGrPtr<CGrTranslate> t2_39699aa2 = new CGrTranslate(-3.65, -11.90, -4.95);
    t1_39699aa2->Child(rot_39699aa2);
    rot_39699aa2->Child(t2_39699aa2);
    t2_39699aa2->Child(b_bladesmall_39699aa2);
    bardiche->Child(t1_39699aa2);
    b_bladesmall_39699aa2->Box(3.65, 8.60, 4.80, 0.00, 4.50, 1.65, texSmallblade);
    CGrPtr<CGrComposite> b_bladebeeg_1961ce46 = new CGrComposite;
    CGrPtr<CGrTranslate> t1_1961ce46 = new CGrTranslate(3.65, 12.20, 4.95);
    CGrPtr<CGrRotate> rot_1961ce46 = new CGrRotate(0, 0, 1, 0);
    CGrPtr<CGrTranslate> t2_1961ce46 = new CGrTranslate(-3.65, -12.20, -4.95);
    t1_1961ce46->Child(rot_1961ce46);
    rot_1961ce46->Child(t2_1961ce46);
    t2_1961ce46->Child(b_bladebeeg_1961ce46);
    bardiche->Child(t1_1961ce46);
    b_bladebeeg_1961ce46->Box(3.45, 8.775, 2.125, 0.40, 3.600, 1.000, texBladebeeg);
    CGrPtr<CGrComposite> b_bladebeeg_296a42be = new CGrComposite;
    CGrPtr<CGrTranslate> t1_296a42be = new CGrTranslate(3.65, 12.20, 4.95);
    CGrPtr<CGrRotate> rot_296a42be = new CGrRotate(0, 0, 1, 0);
    CGrPtr<CGrTranslate> t2_296a42be = new CGrTranslate(-3.65, -12.20, -4.95);
    t1_296a42be->Child(rot_296a42be);
    rot_296a42be->Child(t2_296a42be);
    t2_296a42be->Child(b_bladebeeg_296a42be);
    bardiche->Child(t1_296a42be);
    b_bladebeeg_296a42be->Box(3.65, 6.275, 0.325, 0.00, 9.725, 3.850, texBladebeeg1);
    CGrPtr<CGrComposite> b_part_19f6d771 = new CGrComposite;
    bardiche->Child(b_part_19f6d771);
    b_part_19f6d771->Box(3.30, 11.5, 3.55, 0.70, 0.60, 0.70, texCube1);
    CGrPtr<CGrComposite> b_part_83ff5d45 = new CGrComposite;
    bardiche->Child(b_part_83ff5d45);
    b_part_83ff5d45->Box(3.25, 12.10, 3.5, 0.80, 0.20, 0.80, texCube2);
    CGrPtr<CGrComposite> b_part_bbdeb6bd = new CGrComposite;
    bardiche->Child(b_part_bbdeb6bd);
    b_part_bbdeb6bd->Box(3.25, 9.25, 3.5, 0.80, 0.15, 0.80, texCube2);
    CGrPtr<CGrComposite> b_part_4da54a70 = new CGrComposite;
    bardiche->Child(b_part_4da54a70);
    b_part_4da54a70->Box(3.25, 8.55, 3.5, 0.80, 0.15, 0.80, texCube2);
    CGrPtr<CGrComposite> b_part_47777d24 = new CGrComposite;
    bardiche->Child(b_part_47777d24);
    b_part_47777d24->Box(3.30, 8.60, 3.55, 0.70, 0.80, 0.70, texCube1);
    CGrPtr<CGrComposite> b_pole_4224fe2a = new CGrComposite;
    bardiche->Child(b_pole_4224fe2a);
    b_pole_4224fe2a->Box(3.40, -2.85, 3.65, 0.50, 15.30, 0.50, texPole);
    CGrPtr<CGrComposite> b_part_a7e1426e = new CGrComposite;
    CGrPtr<CGrTranslate> t1_a7e1426e = new CGrTranslate(0, 1.60, 0);
    CGrPtr<CGrRotate> rot_a7e1426e = new CGrRotate(0, 0, 1, 0);
    CGrPtr<CGrTranslate> t2_a7e1426e = new CGrTranslate(0, -1.60, 0);
    t1_a7e1426e->Child(rot_a7e1426e);
    rot_a7e1426e->Child(t2_a7e1426e);
    t2_a7e1426e->Child(b_part_a7e1426e);
    bardiche->Child(t1_a7e1426e);
    b_part_a7e1426e->Box(3.30, -3.40, 3.55, 0.70, 0.80, 0.70, texCube1down);
    CGrPtr<CGrComposite> b_part_8ed9d772 = new CGrComposite;
    CGrPtr<CGrTranslate> t1_8ed9d772 = new CGrTranslate(0, 1.60, 0);
    CGrPtr<CGrRotate> rot_8ed9d772 = new CGrRotate(0, 0, 1, 0);
    CGrPtr<CGrTranslate> t2_8ed9d772 = new CGrTranslate(0, -1.60, 0);
    t1_8ed9d772->Child(rot_8ed9d772);
    rot_8ed9d772->Child(t2_8ed9d772);
    t2_8ed9d772->Child(b_part_8ed9d772);
    bardiche->Child(t1_8ed9d772);
    b_part_8ed9d772->Box(3.25, -3.45, 3.5, 0.80, 0.15, 0.80, texCube2down);
    CGrPtr<CGrComposite> b_star_db39469e = new CGrComposite;
    CGrPtr<CGrTranslate> t1_db39469e = new CGrTranslate(0, 1.60, 0);
    CGrPtr<CGrRotate> rot_db39469e = new CGrRotate(0, 0, 1, 0);
    CGrPtr<CGrTranslate> t2_db39469e = new CGrTranslate(0, -1.60, 0);
    t1_db39469e->Child(rot_db39469e);
    rot_db39469e->Child(t2_db39469e);
    t2_db39469e->Child(b_star_db39469e);
    bardiche->Child(t1_db39469e);
    b_star_db39469e->Box(3.30, -5.25, 3.55, 0.70, 1.175, 0.70, texStar1);
    CGrPtr<CGrComposite> b_star_4880dbf7 = new CGrComposite;
    CGrPtr<CGrTranslate> t1_4880dbf7 = new CGrTranslate(0, 1.60, 0);
    CGrPtr<CGrRotate> rot_4880dbf7 = new CGrRotate(0, 0, 1, 0);
    CGrPtr<CGrTranslate> t2_4880dbf7 = new CGrTranslate(0, -1.60, 0);
    t1_4880dbf7->Child(rot_4880dbf7);
    rot_4880dbf7->Child(t2_4880dbf7);
    t2_4880dbf7->Child(b_star_4880dbf7);
    bardiche->Child(t1_4880dbf7);
    b_star_4880dbf7->Box(3.40, -5.85, 3.65, 0.50, 2.475, 0.50, texStar1p);
    CGrPtr<CGrComposite> b_star_8905daa4 = new CGrComposite;
    CGrPtr<CGrTranslate> t1_8905daa4 = new CGrTranslate(0, 1.60, 0);
    CGrPtr<CGrRotate> rot_8905daa4 = new CGrRotate(0, 0, 1, 0);
    CGrPtr<CGrTranslate> t2_8905daa4 = new CGrTranslate(0, -1.60, 0);
    t1_8905daa4->Child(rot_8905daa4);
    rot_8905daa4->Child(t2_8905daa4);
    t2_8905daa4->Child(b_star_8905daa4);
    bardiche->Child(t1_8905daa4);
    b_star_8905daa4->Box(3.45, -6.40, 3.70, 0.40, 1.275, 0.40, texStar1q);
    CGrPtr<CGrComposite> b_star_fb567e19 = new CGrComposite;
    CGrPtr<CGrTranslate> t1_fb567e19 = new CGrTranslate(3.65, -5.188, 3.90);
    CGrPtr<CGrRotate> rot_fb567e19 = new CGrRotate(0, 1, 0, 0);
    CGrPtr<CGrTranslate> t2_fb567e19 = new CGrTranslate(-3.65, 5.188, -3.90);
    t1_fb567e19->Child(rot_fb567e19);
    rot_fb567e19->Child(t2_fb567e19);
    t2_fb567e19->Child(b_star_fb567e19);
    bardiche->Child(t1_fb567e19);
    b_star_fb567e19->Box(3.40, -4.988, 2.888, 0.50, 0.500, 2.125, texStar1m);
    CGrPtr<CGrComposite> b_star_87768940 = new CGrComposite;
    CGrPtr<CGrTranslate> t1_87768940 = new CGrTranslate(3.65, -5.188, 3.90);
    CGrPtr<CGrRotate> rot_87768940 = new CGrRotate(0, 1, 0, 0);
    CGrPtr<CGrTranslate> t2_87768940 = new CGrTranslate(-3.65, 5.188, -3.90);
    t1_87768940->Child(rot_87768940);
    rot_87768940->Child(t2_87768940);
    t2_87768940->Child(b_star_87768940);
    bardiche->Child(t1_87768940);
    b_star_87768940->Box(3.45, -4.938, 2.338, 0.40, 0.400, 3.225, texStar1n);
    CGrPtr<CGrComposite> b_star2_b95d1313 = new CGrComposite;
    CGrPtr<CGrTranslate> t1_b95d1313 = new CGrTranslate(4.25, -5.188, 3.925);
    CGrPtr<CGrRotate> rot_b95d1313 = new CGrRotate(-45, 1, 0, 0);
    CGrPtr<CGrTranslate> t2_b95d1313 = new CGrTranslate(-4.25, 5.188, -3.925);
    t1_b95d1313->Child(rot_b95d1313);
    rot_b95d1313->Child(t2_b95d1313);
    t2_b95d1313->Child(b_star2_b95d1313);
    bardiche->Child(t1_b95d1313);
    b_star2_b95d1313->Box(3.85, -5.20, 4, 0.60, 0.925, 0.80, texStar2);
    CGrPtr<CGrComposite> b_star2_5320203f = new CGrComposite;
    CGrPtr<CGrTranslate> t1_5320203f = new CGrTranslate(4.25, -5.188, 3.925);
    CGrPtr<CGrRotate> rot_5320203f = new CGrRotate(-45, 1, 0, 0);
    CGrPtr<CGrTranslate> t2_5320203f = new CGrTranslate(-4.25, 5.188, -3.925);
    t1_5320203f->Child(rot_5320203f);
    rot_5320203f->Child(t2_5320203f);
    t2_5320203f->Child(b_star2_5320203f);
    bardiche->Child(t1_5320203f);
    b_star2_5320203f->Box(3.95, -5.038, 3.538, 0.40, 0.600, 1.725, texStar2p);
    CGrPtr<CGrComposite> b_star2_c93ac333 = new CGrComposite;
    CGrPtr<CGrTranslate> t1_c93ac333 = new CGrTranslate(4.25, -5.188, 3.925);
    CGrPtr<CGrRotate> rot_c93ac333 = new CGrRotate(-45, 1, 0, 0);
    CGrPtr<CGrTranslate> t2_c93ac333 = new CGrTranslate(-4.25, 5.188, -3.925);
    t1_c93ac333->Child(rot_c93ac333);
    rot_c93ac333->Child(t2_c93ac333);
    t2_c93ac333->Child(b_star2_c93ac333);
    bardiche->Child(t1_c93ac333);
    b_star2_c93ac333->Box(4, -4.988, 3.138, 0.30, 0.500, 2.525, texStar2q);
    CGrPtr<CGrComposite> b_star2_255466d2 = new CGrComposite;
    CGrPtr<CGrTranslate> t1_255466d2 = new CGrTranslate(4.25, -5.188, 3.925);
    CGrPtr<CGrRotate> rot_255466d2 = new CGrRotate(-45, 1, 0, 0);
    CGrPtr<CGrTranslate> t2_255466d2 = new CGrTranslate(-4.25, 5.188, -3.925);
    t1_255466d2->Child(rot_255466d2);
    rot_255466d2->Child(t2_255466d2);
    t2_255466d2->Child(b_star2_255466d2);
    bardiche->Child(t1_255466d2);
    b_star2_255466d2->Box(3.95, -5.65, 4.10, 0.40, 1.825, 0.60, texStar2m);
    CGrPtr<CGrComposite> b_star2_259767ba = new CGrComposite;
    CGrPtr<CGrTranslate> t1_259767ba = new CGrTranslate(4.25, -5.188, 3.925);
    CGrPtr<CGrRotate> rot_259767ba = new CGrRotate(-45, 1, 0, 0);
    CGrPtr<CGrTranslate> t2_259767ba = new CGrTranslate(-4.25, 5.188, -3.925);
    t1_259767ba->Child(rot_259767ba);
    rot_259767ba->Child(t2_259767ba);
    t2_259767ba->Child(b_star2_259767ba);
    bardiche->Child(t1_259767ba);
    b_star2_259767ba->Box(4.05, -6, 4.20, 0.20, 2.575, 0.40, texStar2n);
    CGrPtr<CGrComposite> b_part_7f965487 = new CGrComposite;
    CGrPtr<CGrTranslate> t1_7f965487 = new CGrTranslate(3.65, 13.624, 3.90);
    CGrPtr<CGrRotate> rot_7f965487 = new CGrRotate(0, 0, 0, 1);
    CGrPtr<CGrTranslate> t2_7f965487 = new CGrTranslate(-3.65, -13.624, -3.90);
    t1_7f965487->Child(rot_7f965487);
    rot_7f965487->Child(t2_7f965487);
    t2_7f965487->Child(b_part_7f965487);
    bardiche->Child(t1_7f965487);
    b_part_7f965487->Box(3.35, 12.5, 3.60, 0.60, 1.05, 0.60, texCrystal1);
    CGrPtr<CGrComposite> b_part_5fd0dd48 = new CGrComposite;
    CGrPtr<CGrTranslate> t1_5fd0dd48 = new CGrTranslate(3.65, 13.624, 3.90);
    CGrPtr<CGrRotate> rot_5fd0dd48 = new CGrRotate(45, 0, 0, 1);
    CGrPtr<CGrTranslate> t2_5fd0dd48 = new CGrTranslate(-3.65, -13.624, -3.90);
    t1_5fd0dd48->Child(rot_5fd0dd48);
    rot_5fd0dd48->Child(t2_5fd0dd48);
    t2_5fd0dd48->Child(b_part_5fd0dd48);
    bardiche->Child(t1_5fd0dd48);
    b_part_5fd0dd48->Box(3.390, 13.339, 3.60, 0.450, 0.450, 0.60, texCrystal2);
}
