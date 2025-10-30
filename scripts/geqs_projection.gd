class_name GEQSProjection
extends RefCounted

var projection_position: Vector3
var score = null
var collided_with: Node3D
var is_filtered = false

func _init(pos: Vector3, collided_with: Node3D, new_score = null) -> void:
    projection_position = pos
    score = new_score
    
func add_score(incoming_score: float):
    if score == null:
        score = 0.0
    score += incoming_score