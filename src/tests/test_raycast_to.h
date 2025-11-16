#pragma once
#include "query_test3d.h"
#include "query_context3d.h"
#include <godot_cpp/classes/curve.hpp>

namespace godot
{
    class CTestRaycastTo : public CQueryTest3D
    {
        GDCLASS(CTestRaycastTo, CQueryTest3D)

    protected:
        static void _bind_methods();

    public:
        CTestRaycastTo();
        ~CTestRaycastTo();

        CQueryContext3D *get_context();
        void set_context(CQueryContext3D *context_node) { context = context_node; }

        void perform_test(CQueryItem &projection);
        void _ready() override;

    private:
        CQueryContext3D *context = nullptr;
        bool hitting_is_true = true;
        bool cast_from_context = false;
        Array exclusions;
    };

}