extends Spatial

var oscrcv
var cube

func _ready():
	
	cube = get_node( "../cube" )
	
	oscrcv = load("res://bin/gdoscreceiver.gdns").new()
	oscrcv.setup( 14000 )
	oscrcv.start()

func _process(delta):

	pass