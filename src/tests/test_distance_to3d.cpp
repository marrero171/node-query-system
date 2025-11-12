#include "test_distance_to3d.h"
using namespace godot;

void CTestDistanceTo::_bind_methods()
{
    ClassDB::bind_method(D_METHOD("get_scoring_curve"), &CTestDistanceTo::get_scoring_curve);
    ClassDB::bind_method(D_METHOD("set_scoring_curve", "curve"), &CTestDistanceTo::set_scoring_curve);

    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "scoring_curve", PROPERTY_HINT_RESOURCE_TYPE, "Curve"), "set_scoring_curve", "get_scoring_curve");
}

CTestDistanceTo::CTestDistanceTo()
{
}

CTestDistanceTo::~CTestDistanceTo()
{
}

Ref<Curve> CTestDistanceTo::get_scoring_curve() const
{
    return scoring_curve;
}

void godot::CTestDistanceTo::set_scoring_curve(Ref<Curve> curve)
{
    scoring_curve = curve;
}

void CTestDistanceTo::perform_test(CQueryItem &projection)
{
    UtilityFunctions::print_rich("Testing the tested test to test");
}

void CTestDistanceTo::_ready()
{
    if (scoring_curve.is_null())
    {
        scoring_curve = Ref<Curve>();
        scoring_curve.instantiate();
        scoring_curve->add_point(Vector2(0, 0));
        scoring_curve->add_point(Vector2(1, 1));
    }
    scoring_curve->bake();
}
