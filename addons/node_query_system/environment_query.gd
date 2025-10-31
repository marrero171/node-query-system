@tool
class_name EnvironmentQuery
extends Node

signal query_finished(result: QueryResult)

@export var use_debug_shapes: bool = false
@export var debug_color: Gradient

var query_items: Array[QueryItem]

func _ready() -> void:
	if Engine.is_editor_hint():
		return
	init_generator()

func init_generator():
	query_items = []
	

func request_query() -> QueryResult:
	query_items.clear()
	var result: QueryResult
	
	for generator: Generator in get_children():
		generator.perform_generation(query_items)

	if use_debug_shapes:
		draw_debug(query_items)

	result = QueryResult.new(query_items)

	query_finished.emit(result)
	return result


# DEBUG PURPOSE
func draw_debug(query_items_list: Array[QueryItem]):
	var shape: CSGPrimitive3D
	var balls: Array

	for item: QueryItem in query_items_list:
		if item.is_filtered:
			shape = CSGBox3D.new()
		else:
			shape = CSGSphere3D.new()

		shape.position = item.projection_position
		get_tree().root.add_child(shape)

		var text_label: Label3D = Label3D.new()
		shape.add_child(text_label)
		text_label.set_deferred("billboard", BaseMaterial3D.BILLBOARD_ENABLED)
		text_label.set_deferred("position", Vector3.UP * 0.75)

		if item.is_filtered:
			text_label.set_deferred("text", "Filtered (0)")
			text_label.set_deferred("modulate", Color.BLUE)
		else:
			if item.score:
				text_label.set_deferred("text", "%0.2f" % item.score)
				text_label.set_deferred("modulate", debug_color.sample(item.score))
		balls.append(shape)


	# Remove balls after a bit
	await get_tree().create_timer(2).timeout
	for ball in balls:
		ball.queue_free()
	

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
		result.append("Query needs at least one Generator node.")
	else:
		var has_invalid_node: bool = false
		for child in get_children():
			if child is not Generator:
				has_invalid_node = true
				break
		if has_invalid_node:
			result.append("EnvironmentQuery can only have Generator children.")
		if !check_has_tests():
			result.append("Query needs at least one test on any Generator")
		

	return result

# Recursively check if there are any tests at all
func check_has_tests() -> bool:
	var has_test: bool = false
	
	var nodes: Array = get_all_children(self)
	
	for node in nodes:
		if node is QueryTest:
			has_test = true
			break
	
	return has_test
			

func get_all_children(node) -> Array:
	var nodes: Array = []

	for n in node.get_children():
		if n.get_child_count() > 0:
			nodes.append(n)
			nodes.append_array(get_all_children(n))
		else:
			nodes.append(n)

	return nodes

class QueryResult extends RefCounted:
	var query_items: Array[QueryItem]
	# TODO: Maybe a function to get copy of the results
	func _init(val: Array[QueryItem]):
		query_items = val
		
	func get_highest_score():
		var highest: float
		for item: QueryItem in query_items:
			if highest == null:
				highest = item.score
			else:
				if item.score > highest:
					highest = item.score
		return highest
