@abstract
class_name Generator
extends Node3D

enum RaycastMode {BODY, AREA, BODY_AREA}

@export_group("Projection Data")
@export var raycast_mode: RaycastMode

@abstract
func get_generation() -> Array[GEQSProjection]