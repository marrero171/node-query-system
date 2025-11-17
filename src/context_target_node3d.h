#pragma once
#include <godot_cpp/classes/node3d.hpp>
#include <godot_cpp/variant/array.hpp>
#include "query_context3d.h"
using namespace godot;

class CContextTargetNode3D : public CQueryContext3D
{
    GDCLASS(CContextTargetNode3D, CQueryContext3D)

protected:
    static void _bind_methods();

public:
    CContextTargetNode3D();
    ~CContextTargetNode3D();

    void set_target_node(Node3D *target);
    Node3D *get_target_node();

    Array get_context() override;

private:
    Node3D *target_node = nullptr;
};
