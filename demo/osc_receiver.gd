extends Spatial

var receiver;

func _ready():
	
	receiver = load("res://bin/OSCreceiver.gdns").new()
	pass # Replace with function body.

# Called every frame. 'delta' is the elapsed time since the previous frame.
#func _process(delta):
#	pass
