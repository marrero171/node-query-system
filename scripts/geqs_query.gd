@tool
class_name GEQSQuery
extends Node

@export var use_debug_shapes: bool = false

var generator: Generator

func _ready() -> void:
	if Engine.is_editor_hint():
		return
	init_generator()

func init_generator():
	if get_children().is_empty():
		return
	
	generator = get_child(0)

func request_query():
	var gen_result: Array[GEQSProjection] = generator.get_generation()
	for result in gen_result:
		for test in generator.get_children():
			test.perform_test(result)
		
		if use_debug_shapes:
			draw_debug(result)


# DEBUG PURPOSE
func draw_debug(projection: GEQSProjection):
	var shape: CSGPrimitive3D

	if projection.is_filtered:
		shape = CSGBox3D.new()
	else:
		shape = CSGSphere3D.new()

	shape.position = projection.projection_position
	get_tree().root.add_child(shape)

	var text_label: Label3D = Label3D.new()
	shape.add_child(text_label)
	text_label.set_deferred("billboard", BaseMaterial3D.BILLBOARD_ENABLED)
	text_label.set_deferred("position", Vector3.UP * 0.75)

	if projection.is_filtered:
		text_label.set_deferred("text", "Filtered (0)")
	else:
		text_label.set_deferred("text", "%0.2f" % projection.score)


	# Remove ball after a bit
	await get_tree().create_timer(2).timeout
	shape.queue_free()
	

func _notification(what: int) -> void:
	if !Engine.is_editor_hint():
		return
	match what:
		NOTIFICATION_CHILD_ORDER_CHANGED:
			update_configuration_warnings()
		NOTIFICATION_ENTER_TREE:
			update_configuration_warnings()

func _get_configuration_warnings() -> PackedStringArray:
	var result: Array = []
	
	if get_children().is_empty():
		result.append("Query needs a Generator node.")
	else:
		if get_child(0) is not Generator:
			result.append("Child node is not a Generator.")
	if get_child_count() > 1:
		result.append("Query may have only one Generator child at a time.")

	return result
