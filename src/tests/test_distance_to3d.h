#pragma once
#include "query_test3d.h"

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

        void perform_test(CQueryItem &projection);

    private:
    };

}