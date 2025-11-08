#pragma once
#include <godot_cpp/classes/node3d.hpp>

namespace godot
{
    class CQueryGenerator3D : public Node3D
    {
        GDCLASS(CQueryGenerator3D, Node)

    protected:
        static void _bind_methods();

    public:
        CQueryGenerator3D();
        ~CQueryGenerator3D();

    private:
    };

}