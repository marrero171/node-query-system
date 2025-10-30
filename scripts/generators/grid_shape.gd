class_name GridShape extends Generator

@export_group("Generator")
@export var grid_half_size: float = 20
@export var space_between: float = 5
@export var generate_around: GQueryContext

@export_group("Projection Data")
@export var project_down: float = 100.0
@export var project_up: float = 100.0
@export var post_projection_vertical_offset: float = 0.0

func get_generation() -> Array[GEQSProjection]:
	var grid_size: int = roundi(grid_half_size * 2 / space_between) + 1
	var contexts: Array[Node3D] = generate_around.get_context()
	var final_result: Array[GEQSProjection] = []

	for context: Node3D in contexts:
		var starting_pos = context.global_position
		starting_pos.x -= grid_half_size
		starting_pos.z -= grid_half_size
		for z in grid_size:
			for x in grid_size:
				var ray_pos_x: float = starting_pos.x + (x * space_between)
				var ray_pos_z: float = starting_pos.z + (z * space_between)
				var ray_pos: Vector3 = Vector3(ray_pos_x, starting_pos.y, ray_pos_z)
				
				var ray_result: Dictionary = cast_ray(ray_pos + (Vector3.UP * project_up), ray_pos + (Vector3.DOWN * project_down), contexts)
				if ray_result:
					final_result.append(GEQSProjection.new(ray_result.position + Vector3.UP * post_projection_vertical_offset, ray_result.collider))
	return final_result


func cast_ray(start_pos: Vector3, end_pos: Vector3, exclusions: Array) -> Dictionary:
	var space_state: PhysicsDirectSpaceState3D = get_world_3d().direct_space_state
	var query: PhysicsRayQueryParameters3D = PhysicsRayQueryParameters3D.create(start_pos, end_pos)
	var exclusion_rids: Array[RID] = []

	for exclusion in exclusions:
		exclusion_rids.append(exclusion.get_rid())
	query.exclude = exclusion_rids

	return space_state.intersect_ray(query)
