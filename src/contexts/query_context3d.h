#pragma once
#include "contexts/query_context.h"
#include <godot_cpp/classes/node3d.hpp>
#include <godot_cpp/variant/array.hpp>
#include <godot_cpp/variant/packed_vector3_array.hpp>
using namespace godot;
class QueryContext3D : public Node3D, QueryContextBase<Node3D, PackedVector3Array, Variant::VECTOR3> {
	GDCLASS(QueryContext3D, Node3D)

public:
	QueryContext3D() { set_base_owner(this); }
	~QueryContext3D() {}

	virtual Array get_context() = 0;
	PackedVector3Array get_context_positions() { return _get_context_positions(); }

protected:
	static void _bind_methods();
};