
#pragma once
#include "debug/geqo_debug_spheres.h"
#include "query_result.h"
#include <godot_cpp/classes/gradient.hpp>
#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/classes/ref.hpp>
#include <godot_cpp/variant/array.hpp>
#include <vector>
using std::vector;
using namespace godot;

class GEQODebugSpheres2D : public Node, public GEQODebugSpheresBase<Vector2> {
	GDCLASS(GEQODebugSpheres2D, Node)

private:
public:
	GEQODebugSpheres2D() {}
	~GEQODebugSpheres2D() {}

	void draw_items(vector<QueryItem<Vector2>> &query_items_list, double time_to_destroy = 2.0);

	void _ready() override;

protected:
	static void _bind_methods();
};