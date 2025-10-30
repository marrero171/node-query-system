@abstract
class_name GEQSTest
extends Node

enum TestPurpose {FILTER_SCORE, FILTER_ONLY, SCORE_ONLY}
enum ScoreOperator {AVERAGE_SCORE, MAX_SCORE, MIN_SCORE}

@export var test_purpose: TestPurpose

@export_group("Score")
@export var multiple_context_operator: ScoreOperator

@abstract
func perform_test(projection: GEQSProjection)

func sum_f(accum: float, number: float) -> float:
    return accum + number