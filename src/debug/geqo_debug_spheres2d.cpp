#include "debug/geqo_debug_spheres2d.h"
#include <godot_cpp/classes/label.hpp>
#include <godot_cpp/classes/standard_material3d.hpp>
#include <godot_cpp/variant/color_names.inc.hpp>
#include <iomanip>

#include "query_result.h"

void GEQODebugSpheres2D::draw_items(vector<QueryItem<Vector2>> &query_items_list, double time_to_destroy) {
	remove_labels();

	for (QueryItem<Vector2> &query_item : query_items_list) {
		Label *text_label = memnew(Label);
		text_labels.append(text_label);
		add_child(text_label);

		if (query_item.is_filtered) {
			text_label->set_deferred("text", "Filtered");
			//draw_debug_sphere(query_item.projection_position, 0.5, Color(0, 0, 1));
		} else {
			if (query_item.has_score) {
				// TODO: Set the precision to 2 decimals
				text_label->set_deferred("text", query_item.score);
				//draw_debug_sphere(query_item.projection_position, 0.5, debug_color->sample(query_item.score));
			} else {
				//draw_debug_sphere(query_item.projection_position, 0.5, Color(0, 1, 1));
			}
		}
		text_label->set_deferred("global_position", query_item.projection_position);
	}
}
void GEQODebugSpheres2D::_ready() {
	debug_color = Ref<Gradient>();
	debug_color.instantiate();
	PackedColorArray colors = PackedColorArray();
	// Red
	colors.append(Color(1.0, 0.0, 0.0));
	// Yellow
	colors.append(Color(1.0, 1.0, 0.0));
	// Green
	colors.append(Color(0.0, 1.0, 0.0));

	debug_color->set_colors(colors);

	PackedFloat32Array offsets = PackedFloat32Array();
	offsets.append(0.0);
	offsets.append(0.5);
	offsets.append(1.0);

	debug_color->set_offsets(offsets);
}

void GEQODebugSpheres2D::_bind_methods() {
}