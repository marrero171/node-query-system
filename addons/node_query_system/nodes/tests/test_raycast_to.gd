class_name TestRaycastTo
extends QueryTest

@export var context: QueryContext
## Start raycast from context's position instead
@export var hitting_is_true: bool = true
@export var cast_from_context: bool = false
@export var exclusions: Array[Node3D]
@export_flags_3d_physics var collision_mask: int = 1

func perform_test(projection: QueryItem):
	var context_nodes: Array[Node3D] = context.get_context()
	if context_nodes.size() > 1:
		return

	var space_state: PhysicsDirectSpaceState3D = get_world_3d().direct_space_state
	var start_pos: Vector3
	var end_pos: Vector3
	
	if cast_from_context:
		start_pos = context_nodes[0].global_position
		end_pos = projection.projection_position
	else:
		start_pos = projection.projection_position
		end_pos = context_nodes[0].global_position
		
	var query: PhysicsRayQueryParameters3D = PhysicsRayQueryParameters3D.create(start_pos, end_pos)
	query.collision_mask = collision_mask
	var exclusion_rids: Array[RID]
	for exclusion in exclusions:
		exclusion_rids.append(exclusion.get_rid())
	query.exclude = exclusion_rids

	var result = space_state.intersect_ray(query)
	
	if result.get("collider") == context_nodes[0]:
		match test_purpose:
			TestPurpose.FILTER_SCORE:
				projection.add_score(1 if hitting_is_true else 0)
				projection.is_filtered = true if hitting_is_true else false
			TestPurpose.FILTER_ONLY:
				projection.is_filtered = true if hitting_is_true else false
			TestPurpose.SCORE_ONLY:
				projection.add_score(1 if hitting_is_true else 0)
