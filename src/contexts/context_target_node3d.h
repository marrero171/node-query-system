#pragma once
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

    void set_target_node(const NodePath &target);
    NodePath get_target_node();

    Array get_context() override;

private:
    NodePath target_node;
};
