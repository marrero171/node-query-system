#include "contexts/query_context3d.h"
#include <godot_cpp/core/class_db.hpp>

void QueryContext3D::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_context"), &QueryContext3D::get_context);
	ClassDB::bind_method(D_METHOD("get_context_positions"), &QueryContext3D::get_context_positions);
}