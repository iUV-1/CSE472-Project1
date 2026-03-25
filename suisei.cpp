#include "pch.h"
#include "suisei.h"

namespace
{
    void BuildHead(CGrComposite* root, CGrMaterial* skin)
    {
        CGrPtr<CGrComposite> head = new CGrComposite;
        skin->Child(head);
        head->Box(-1.5, 8, -1.5, 3, 3, 3);
    }

    void BuildBody(CGrComposite* root, CGrMaterial* shirt)
    {
        CGrPtr<CGrComposite> body = new CGrComposite;
        shirt->Child(body);
        body->Box(-1.5, 4, -0.75, 3, 4, 1.5);
    }

    void BuildArms(CGrComposite* root, CGrMaterial* skin, CGrMaterial* shirt)
    {
        CGrPtr<CGrComposite> leftArm = new CGrComposite;
        skin->Child(leftArm);
        leftArm->Box(-2.5, 4, -0.75, 1, 4, 1.5);

        CGrPtr<CGrComposite> rightArm = new CGrComposite;
        skin->Child(rightArm);
        rightArm->Box(1.5, 4, -0.75, 1, 4, 1.5);
    }

    void BuildLegs(CGrComposite* root, CGrMaterial* pants)
    {
        CGrPtr<CGrComposite> leftLeg = new CGrComposite;
        pants->Child(leftLeg);
        leftLeg->Box(-1.4, 0, -0.75, 1.2, 4, 1.5);

        CGrPtr<CGrComposite> rightLeg = new CGrComposite;
        pants->Child(rightLeg);
        rightLeg->Box(0.2, 0, -0.75, 1.2, 4, 1.5);
    }
}

void AddSteve(CGrComposite* scene, double x, double y, double z)
{
    CGrPtr<CGrTranslate> steveTrans = new CGrTranslate(x, y, z);
    scene->Child(steveTrans);

    CGrPtr<CGrComposite> steveRoot = new CGrComposite;
    steveTrans->Child(steveRoot);

    CGrPtr<CGrMaterial> skin = new CGrMaterial;
    skin->AmbientAndDiffuse(0.86f, 0.67f, 0.53f);
    steveRoot->Child(skin);

    CGrPtr<CGrMaterial> shirt = new CGrMaterial;
    shirt->AmbientAndDiffuse(0.0f, 0.68f, 0.71f);
    steveRoot->Child(shirt);

    CGrPtr<CGrMaterial> pants = new CGrMaterial;
    pants->AmbientAndDiffuse(0.2f, 0.17f, 0.57f);
    steveRoot->Child(pants);

    BuildHead(steveRoot, skin);
    BuildBody(steveRoot, shirt);
    BuildArms(steveRoot, skin, shirt);
    BuildLegs(steveRoot, pants);
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

    CGrPtr<CGrComposite> b_ornament1_11c264dd = new CGrComposite;
    bardiche->Child(b_ornament1_11c264dd);
    b_ornament1_11c264dd->Box(3.35, 7.30, 3.60, 0.60, 2.70, 0.60);
    CGrPtr<CGrComposite> b_ornament2_ae3b1681 = new CGrComposite;
    bardiche->Child(b_ornament2_ae3b1681);
    b_ornament2_ae3b1681->Box(3.35, 10.20, 3.60, 0.60, 2.30, 0.60);
    CGrPtr<CGrComposite> b_ornament3_7058703f = new CGrComposite;
    bardiche->Child(b_ornament3_7058703f);
    b_ornament3_7058703f->Box(3.30, 6.85, 3.55, 0.70, 0.50, 0.70);
    CGrPtr<CGrComposite> b_ornament4_514ff80d = new CGrComposite;
    bardiche->Child(b_ornament4_514ff80d);
    b_ornament4_514ff80d->Box(3.30, 9.85, 3.55, 0.70, 0.50, 0.70);
    CGrPtr<CGrComposite> b_leverage1_3ff91814 = new CGrComposite;
    CGrPtr<CGrTranslate> t1_3ff91814 = new CGrTranslate(3.65, 12.20, 4.95);
    CGrPtr<CGrRotate> rot_3ff91814 = new CGrRotate(0, 0, 1, 0);
    CGrPtr<CGrTranslate> t2_3ff91814 = new CGrTranslate(-3.65, -12.20, -4.95);
    t1_3ff91814->Child(rot_3ff91814);
    rot_3ff91814->Child(t2_3ff91814);
    t2_3ff91814->Child(b_leverage1_3ff91814);
    bardiche->Child(t1_3ff91814);
    b_leverage1_3ff91814->Box(3.5, 11.70, 2.85, 0.30, 0.40, 2.15);
    CGrPtr<CGrComposite> b_leverage2_74f38785 = new CGrComposite;
    CGrPtr<CGrTranslate> t1_74f38785 = new CGrTranslate(3.65, 12.20, 4.95);
    CGrPtr<CGrRotate> rot_74f38785 = new CGrRotate(0, 0, 1, 0);
    CGrPtr<CGrTranslate> t2_74f38785 = new CGrTranslate(-3.65, -12.20, -4.95);
    t1_74f38785->Child(rot_74f38785);
    rot_74f38785->Child(t2_74f38785);
    t2_74f38785->Child(b_leverage2_74f38785);
    bardiche->Child(t1_74f38785);
    b_leverage2_74f38785->Box(3.5, 8.80, 2.85, 0.30, 0.40, 1.20);
    CGrPtr<CGrComposite> b_bladesmall_a8ad9ceb = new CGrComposite;
    CGrPtr<CGrTranslate> t1_a8ad9ceb = new CGrTranslate(3.65, 11.90, 4.95);
    CGrPtr<CGrRotate> rot_a8ad9ceb = new CGrRotate(-22.5, 1, 0, 0);
    CGrPtr<CGrTranslate> t2_a8ad9ceb = new CGrTranslate(-3.65, -11.90, -4.95);
    t1_a8ad9ceb->Child(rot_a8ad9ceb);
    rot_a8ad9ceb->Child(t2_a8ad9ceb);
    t2_a8ad9ceb->Child(b_bladesmall_a8ad9ceb);
    bardiche->Child(t1_a8ad9ceb);
    b_bladesmall_a8ad9ceb->Box(3.45, 11.10, 4.70, 0.40, 1.40, 0.70);
    CGrPtr<CGrComposite> b_bladesmall_6d2d0a55 = new CGrComposite;
    CGrPtr<CGrTranslate> t1_6d2d0a55 = new CGrTranslate(3.65, 11.90, 4.95);
    CGrPtr<CGrRotate> rot_6d2d0a55 = new CGrRotate(0, 0, 1, 0);
    CGrPtr<CGrTranslate> t2_6d2d0a55 = new CGrTranslate(-3.65, -11.90, -4.95);
    t1_6d2d0a55->Child(rot_6d2d0a55);
    rot_6d2d0a55->Child(t2_6d2d0a55);
    t2_6d2d0a55->Child(b_bladesmall_6d2d0a55);
    bardiche->Child(t1_6d2d0a55);
    b_bladesmall_6d2d0a55->Box(3.45, 10.35, 5, 0.40, 1.00, 0.70);
    CGrPtr<CGrComposite> b_bladesmall_39699aa2 = new CGrComposite;
    CGrPtr<CGrTranslate> t1_39699aa2 = new CGrTranslate(3.65, 11.90, 4.95);
    CGrPtr<CGrRotate> rot_39699aa2 = new CGrRotate(0, 0, 1, 0);
    CGrPtr<CGrTranslate> t2_39699aa2 = new CGrTranslate(-3.65, -11.90, -4.95);
    t1_39699aa2->Child(rot_39699aa2);
    rot_39699aa2->Child(t2_39699aa2);
    t2_39699aa2->Child(b_bladesmall_39699aa2);
    bardiche->Child(t1_39699aa2);
    b_bladesmall_39699aa2->Box(3.65, 8.60, 4.80, 0.00, 4.50, 1.65);
    CGrPtr<CGrComposite> b_bladebeeg_1961ce46 = new CGrComposite;
    CGrPtr<CGrTranslate> t1_1961ce46 = new CGrTranslate(3.65, 12.20, 4.95);
    CGrPtr<CGrRotate> rot_1961ce46 = new CGrRotate(0, 0, 1, 0);
    CGrPtr<CGrTranslate> t2_1961ce46 = new CGrTranslate(-3.65, -12.20, -4.95);
    t1_1961ce46->Child(rot_1961ce46);
    rot_1961ce46->Child(t2_1961ce46);
    t2_1961ce46->Child(b_bladebeeg_1961ce46);
    bardiche->Child(t1_1961ce46);
    b_bladebeeg_1961ce46->Box(3.45, 8.775, 2.125, 0.40, 3.600, 1.000);
    CGrPtr<CGrComposite> b_bladebeeg_296a42be = new CGrComposite;
    CGrPtr<CGrTranslate> t1_296a42be = new CGrTranslate(3.65, 12.20, 4.95);
    CGrPtr<CGrRotate> rot_296a42be = new CGrRotate(0, 0, 1, 0);
    CGrPtr<CGrTranslate> t2_296a42be = new CGrTranslate(-3.65, -12.20, -4.95);
    t1_296a42be->Child(rot_296a42be);
    rot_296a42be->Child(t2_296a42be);
    t2_296a42be->Child(b_bladebeeg_296a42be);
    bardiche->Child(t1_296a42be);
    b_bladebeeg_296a42be->Box(3.65, 6.275, 0.325, 0.00, 9.725, 3.850);
    CGrPtr<CGrComposite> b_part_19f6d771 = new CGrComposite;
    bardiche->Child(b_part_19f6d771);
    b_part_19f6d771->Box(3.30, 11.5, 3.55, 0.70, 0.60, 0.70);
    CGrPtr<CGrComposite> b_part_83ff5d45 = new CGrComposite;
    bardiche->Child(b_part_83ff5d45);
    b_part_83ff5d45->Box(3.25, 12.10, 3.5, 0.80, 0.20, 0.80);
    CGrPtr<CGrComposite> b_part_bbdeb6bd = new CGrComposite;
    bardiche->Child(b_part_bbdeb6bd);
    b_part_bbdeb6bd->Box(3.25, 9.25, 3.5, 0.80, 0.15, 0.80);
    CGrPtr<CGrComposite> b_part_4da54a70 = new CGrComposite;
    bardiche->Child(b_part_4da54a70);
    b_part_4da54a70->Box(3.25, 8.55, 3.5, 0.80, 0.15, 0.80);
    CGrPtr<CGrComposite> b_part_47777d24 = new CGrComposite;
    bardiche->Child(b_part_47777d24);
    b_part_47777d24->Box(3.30, 8.60, 3.55, 0.70, 0.80, 0.70);
    CGrPtr<CGrComposite> b_pole_4224fe2a = new CGrComposite;
    bardiche->Child(b_pole_4224fe2a);
    b_pole_4224fe2a->Box(3.40, -2.85, 3.65, 0.50, 15.30, 0.50);
    CGrPtr<CGrComposite> b_part_a7e1426e = new CGrComposite;
    CGrPtr<CGrTranslate> t1_a7e1426e = new CGrTranslate(0, 1.60, 0);
    CGrPtr<CGrRotate> rot_a7e1426e = new CGrRotate(0, 0, 1, 0);
    CGrPtr<CGrTranslate> t2_a7e1426e = new CGrTranslate(0, -1.60, 0);
    t1_a7e1426e->Child(rot_a7e1426e);
    rot_a7e1426e->Child(t2_a7e1426e);
    t2_a7e1426e->Child(b_part_a7e1426e);
    bardiche->Child(t1_a7e1426e);
    b_part_a7e1426e->Box(3.30, -3.40, 3.55, 0.70, 0.80, 0.70);
    CGrPtr<CGrComposite> b_part_8ed9d772 = new CGrComposite;
    CGrPtr<CGrTranslate> t1_8ed9d772 = new CGrTranslate(0, 1.60, 0);
    CGrPtr<CGrRotate> rot_8ed9d772 = new CGrRotate(0, 0, 1, 0);
    CGrPtr<CGrTranslate> t2_8ed9d772 = new CGrTranslate(0, -1.60, 0);
    t1_8ed9d772->Child(rot_8ed9d772);
    rot_8ed9d772->Child(t2_8ed9d772);
    t2_8ed9d772->Child(b_part_8ed9d772);
    bardiche->Child(t1_8ed9d772);
    b_part_8ed9d772->Box(3.25, -3.45, 3.5, 0.80, 0.15, 0.80);
    CGrPtr<CGrComposite> b_star_db39469e = new CGrComposite;
    CGrPtr<CGrTranslate> t1_db39469e = new CGrTranslate(0, 1.60, 0);
    CGrPtr<CGrRotate> rot_db39469e = new CGrRotate(0, 0, 1, 0);
    CGrPtr<CGrTranslate> t2_db39469e = new CGrTranslate(0, -1.60, 0);
    t1_db39469e->Child(rot_db39469e);
    rot_db39469e->Child(t2_db39469e);
    t2_db39469e->Child(b_star_db39469e);
    bardiche->Child(t1_db39469e);
    b_star_db39469e->Box(3.30, -5.25, 3.55, 0.70, 1.175, 0.70);
    CGrPtr<CGrComposite> b_star_4880dbf7 = new CGrComposite;
    CGrPtr<CGrTranslate> t1_4880dbf7 = new CGrTranslate(0, 1.60, 0);
    CGrPtr<CGrRotate> rot_4880dbf7 = new CGrRotate(0, 0, 1, 0);
    CGrPtr<CGrTranslate> t2_4880dbf7 = new CGrTranslate(0, -1.60, 0);
    t1_4880dbf7->Child(rot_4880dbf7);
    rot_4880dbf7->Child(t2_4880dbf7);
    t2_4880dbf7->Child(b_star_4880dbf7);
    bardiche->Child(t1_4880dbf7);
    b_star_4880dbf7->Box(3.40, -5.85, 3.65, 0.50, 2.475, 0.50);
    CGrPtr<CGrComposite> b_star_8905daa4 = new CGrComposite;
    CGrPtr<CGrTranslate> t1_8905daa4 = new CGrTranslate(0, 1.60, 0);
    CGrPtr<CGrRotate> rot_8905daa4 = new CGrRotate(0, 0, 1, 0);
    CGrPtr<CGrTranslate> t2_8905daa4 = new CGrTranslate(0, -1.60, 0);
    t1_8905daa4->Child(rot_8905daa4);
    rot_8905daa4->Child(t2_8905daa4);
    t2_8905daa4->Child(b_star_8905daa4);
    bardiche->Child(t1_8905daa4);
    b_star_8905daa4->Box(3.45, -6.40, 3.70, 0.40, 1.275, 0.40);
    CGrPtr<CGrComposite> b_star_fb567e19 = new CGrComposite;
    CGrPtr<CGrTranslate> t1_fb567e19 = new CGrTranslate(3.65, -5.188, 3.90);
    CGrPtr<CGrRotate> rot_fb567e19 = new CGrRotate(0, 1, 0, 0);
    CGrPtr<CGrTranslate> t2_fb567e19 = new CGrTranslate(-3.65, 5.188, -3.90);
    t1_fb567e19->Child(rot_fb567e19);
    rot_fb567e19->Child(t2_fb567e19);
    t2_fb567e19->Child(b_star_fb567e19);
    bardiche->Child(t1_fb567e19);
    b_star_fb567e19->Box(3.40, -4.988, 2.888, 0.50, 0.500, 2.125);
    CGrPtr<CGrComposite> b_star_87768940 = new CGrComposite;
    CGrPtr<CGrTranslate> t1_87768940 = new CGrTranslate(3.65, -5.188, 3.90);
    CGrPtr<CGrRotate> rot_87768940 = new CGrRotate(0, 1, 0, 0);
    CGrPtr<CGrTranslate> t2_87768940 = new CGrTranslate(-3.65, 5.188, -3.90);
    t1_87768940->Child(rot_87768940);
    rot_87768940->Child(t2_87768940);
    t2_87768940->Child(b_star_87768940);
    bardiche->Child(t1_87768940);
    b_star_87768940->Box(3.45, -4.938, 2.338, 0.40, 0.400, 3.225);
    CGrPtr<CGrComposite> b_star2_b95d1313 = new CGrComposite;
    CGrPtr<CGrTranslate> t1_b95d1313 = new CGrTranslate(4.25, -5.188, 3.925);
    CGrPtr<CGrRotate> rot_b95d1313 = new CGrRotate(-45, 1, 0, 0);
    CGrPtr<CGrTranslate> t2_b95d1313 = new CGrTranslate(-4.25, 5.188, -3.925);
    t1_b95d1313->Child(rot_b95d1313);
    rot_b95d1313->Child(t2_b95d1313);
    t2_b95d1313->Child(b_star2_b95d1313);
    bardiche->Child(t1_b95d1313);
    b_star2_b95d1313->Box(3.85, -5.20, 4, 0.60, 0.925, 0.80);
    CGrPtr<CGrComposite> b_star2_5320203f = new CGrComposite;
    CGrPtr<CGrTranslate> t1_5320203f = new CGrTranslate(4.25, -5.188, 3.925);
    CGrPtr<CGrRotate> rot_5320203f = new CGrRotate(-45, 1, 0, 0);
    CGrPtr<CGrTranslate> t2_5320203f = new CGrTranslate(-4.25, 5.188, -3.925);
    t1_5320203f->Child(rot_5320203f);
    rot_5320203f->Child(t2_5320203f);
    t2_5320203f->Child(b_star2_5320203f);
    bardiche->Child(t1_5320203f);
    b_star2_5320203f->Box(3.95, -5.038, 3.538, 0.40, 0.600, 1.725);
    CGrPtr<CGrComposite> b_star2_c93ac333 = new CGrComposite;
    CGrPtr<CGrTranslate> t1_c93ac333 = new CGrTranslate(4.25, -5.188, 3.925);
    CGrPtr<CGrRotate> rot_c93ac333 = new CGrRotate(-45, 1, 0, 0);
    CGrPtr<CGrTranslate> t2_c93ac333 = new CGrTranslate(-4.25, 5.188, -3.925);
    t1_c93ac333->Child(rot_c93ac333);
    rot_c93ac333->Child(t2_c93ac333);
    t2_c93ac333->Child(b_star2_c93ac333);
    bardiche->Child(t1_c93ac333);
    b_star2_c93ac333->Box(4, -4.988, 3.138, 0.30, 0.500, 2.525);
    CGrPtr<CGrComposite> b_star2_255466d2 = new CGrComposite;
    CGrPtr<CGrTranslate> t1_255466d2 = new CGrTranslate(4.25, -5.188, 3.925);
    CGrPtr<CGrRotate> rot_255466d2 = new CGrRotate(-45, 1, 0, 0);
    CGrPtr<CGrTranslate> t2_255466d2 = new CGrTranslate(-4.25, 5.188, -3.925);
    t1_255466d2->Child(rot_255466d2);
    rot_255466d2->Child(t2_255466d2);
    t2_255466d2->Child(b_star2_255466d2);
    bardiche->Child(t1_255466d2);
    b_star2_255466d2->Box(3.95, -5.65, 4.10, 0.40, 1.825, 0.60);
    CGrPtr<CGrComposite> b_star2_259767ba = new CGrComposite;
    CGrPtr<CGrTranslate> t1_259767ba = new CGrTranslate(4.25, -5.188, 3.925);
    CGrPtr<CGrRotate> rot_259767ba = new CGrRotate(-45, 1, 0, 0);
    CGrPtr<CGrTranslate> t2_259767ba = new CGrTranslate(-4.25, 5.188, -3.925);
    t1_259767ba->Child(rot_259767ba);
    rot_259767ba->Child(t2_259767ba);
    t2_259767ba->Child(b_star2_259767ba);
    bardiche->Child(t1_259767ba);
    b_star2_259767ba->Box(4.05, -6, 4.20, 0.20, 2.575, 0.40);
    CGrPtr<CGrComposite> b_part_7f965487 = new CGrComposite;
    CGrPtr<CGrTranslate> t1_7f965487 = new CGrTranslate(3.65, 13.624, 3.90);
    CGrPtr<CGrRotate> rot_7f965487 = new CGrRotate(0, 0, 0, 1);
    CGrPtr<CGrTranslate> t2_7f965487 = new CGrTranslate(-3.65, -13.624, -3.90);
    t1_7f965487->Child(rot_7f965487);
    rot_7f965487->Child(t2_7f965487);
    t2_7f965487->Child(b_part_7f965487);
    bardiche->Child(t1_7f965487);
    b_part_7f965487->Box(3.35, 12.5, 3.60, 0.60, 1.05, 0.60);
    CGrPtr<CGrComposite> b_part_5fd0dd48 = new CGrComposite;
    CGrPtr<CGrTranslate> t1_5fd0dd48 = new CGrTranslate(3.65, 13.624, 3.90);
    CGrPtr<CGrRotate> rot_5fd0dd48 = new CGrRotate(45, 0, 0, 1);
    CGrPtr<CGrTranslate> t2_5fd0dd48 = new CGrTranslate(-3.65, -13.624, -3.90);
    t1_5fd0dd48->Child(rot_5fd0dd48);
    rot_5fd0dd48->Child(t2_5fd0dd48);
    t2_5fd0dd48->Child(b_part_5fd0dd48);
    bardiche->Child(t1_5fd0dd48);
    b_part_5fd0dd48->Box(3.390, 13.339, 3.60, 0.450, 0.450, 0.60);
}
