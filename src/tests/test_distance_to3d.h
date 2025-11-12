#pragma once
#include "query_test3d.h"
#include <godot_cpp/classes/curve.hpp>

namespace godot
{
    class CTestDistanceTo : public CQueryTest3D
    {
        GDCLASS(CTestDistanceTo, CQueryTest3D)

    protected:
        static void _bind_methods();

    public:
        CTestDistanceTo();
        ~CTestDistanceTo();

        Ref<Curve> get_scoring_curve() const;
        void set_scoring_curve(Ref<Curve> curve);

        void perform_test(CQueryItem &projection);
        void _ready() override;

    private:
        Ref<Curve> scoring_curve;
    };

}