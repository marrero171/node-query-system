#ifndef QUERYGENERATOR3D_H
#define QUERYGENERATOR3D_H

#include "query_result.h"
#include <godot_cpp/classes/node3d.hpp>
#include <godot_cpp/variant/array.hpp>
#include <vector>
using namespace godot;

class QueryGenerator3D : public Node3D {
	GDCLASS(QueryGenerator3D, Node3D)

public:
	enum RaycastMode {
		BODY,
		AREA,
		BODY_AREA
	};

private:
	RaycastMode raycast_mode = BODY;
	std::vector<QueryItem> *query_items_ref = nullptr;

public:
	QueryGenerator3D() {}
	~QueryGenerator3D() {}

	void set_query_items_ref(std::vector<QueryItem> &query_items) { query_items_ref = &query_items; }
	std::vector<QueryItem> &get_query_items_ref() { return *query_items_ref; }

	void set_raycast_mode(RaycastMode mode);
	RaycastMode get_raycast_mode() const { return raycast_mode; }

	virtual void perform_generation(uint64_t initial_time_usec, int time_budget_ms) = 0;
	void perform_tests(std::vector<QueryItem> &query_item_list);
	Dictionary cast_ray_projection(Vector3 start_pos, Vector3 end_pos, Array exclusions, int col_mask = 1);
	bool has_time_left(uint64_t initial_time_usec, uint64_t current_time_usec, int time_budget_ms);

protected:
	static void _bind_methods();
	void _notification(int p_what);
};

VARIANT_ENUM_CAST(QueryGenerator3D::RaycastMode);
#endif