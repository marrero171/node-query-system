class_name TestDistanceTo
extends GEQSTest


@export var distance_to: GQueryContext
@export var min_distance: float = 0.0
@export var max_distance: float = 10

@export_group("Score")
@export var scoring_curve: Curve
func perform_test(projection: GEQSProjection):
	var context_nodes: Array[Node3D] = distance_to.get_context()
	var scores: Array[float] = []

	for node: Node3D in context_nodes:
		var distance: float = projection.projection_position.distance_to(node.global_position)
		
		var linear_score: float = clamp(distance / max_distance, 0.0, 1.0)
		var curve_score: float = scoring_curve.sample(linear_score)

		scores.append(curve_score)
	
	var result: float = 0.0
	match multiple_context_operator:
		ScoreOperator.AVERAGE_SCORE:
			var total_score: float = scores.reduce(sum_f)
			result = total_score / scores.size()
		ScoreOperator.MAX_SCORE:
			result = scores.max()
		ScoreOperator.MIN_SCORE:
			result = scores.min()
		
	projection.add_score(result)
