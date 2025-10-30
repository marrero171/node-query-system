class_name ContextInGroup
extends GQueryContext

@export var the_group: StringName

func get_context() -> Array[Node3D]:
	# TODO: Figure out why the casting didn't work
	# return get_tree().get_nodes_in_group(the_group) as Array[Node3D]
	var result: Array[Node3D]
	
	for node in get_tree().get_nodes_in_group(the_group):
		result.append(node as Node3D)
	
	return result
