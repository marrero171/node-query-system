#include "context_target_node3d.h"
#include <godot_cpp/classes/node.hpp>

void CContextTargetNode3D::_bind_methods()
{
    ClassDB::bind_method(D_METHOD("get_target_node"), &CContextTargetNode3D::get_target_node);
    ClassDB::bind_method(D_METHOD("set_target_node", "target"), &CContextTargetNode3D::set_target_node);

    ADD_PROPERTY(PropertyInfo(Variant::NODE_PATH, "target_node", PROPERTY_HINT_NODE_PATH_VALID_TYPES, "Node3D"), "set_target_node", "get_target_node");
}

CContextTargetNode3D::CContextTargetNode3D()
{
}

CContextTargetNode3D::~CContextTargetNode3D()
{
}

void CContextTargetNode3D::set_target_node(const NodePath &target)
{
    target_node = target;
}

NodePath CContextTargetNode3D::get_target_node()
{
    return target_node;
}

Array CContextTargetNode3D::get_context()
{
    Array result = Array();
    if (target_node.is_empty())
    {
        print_error("No target node what the hecc");
        return Array();
    }
    Node3D *target_node_ref = get_node<Node3D>(target_node);
    result.append(target_node_ref);
    return result;
}
