#include <godot_cpp/core/class_db.hpp>
#include "query_context3d.h"

using namespace godot;

void CQueryContext3D::_bind_methods()
{
}

CQueryContext3D::CQueryContext3D()
{
}

CQueryContext3D::~CQueryContext3D()
{
}

Array CQueryContext3D::get_context()
{
    return Array();
}

PackedVector3Array CQueryContext3D::get_context_positions()
{
    Array contexts = get_context();
    PackedVector3Array results = PackedVector3Array();

    for (Variant context : contexts)
    {
        if (context.get_type() == Variant::VECTOR3)
        {
            results.append(context);
            continue;
        }

        Node3D *current_context = Object::cast_to<Node3D>(context);
        results.append(current_context->get_global_position());
    }
    return results;
}
