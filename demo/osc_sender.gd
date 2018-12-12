extends Spatial

var oscsender
var cube

func _ready():
	
	cube = get_node( "../cube" )
	
	oscsender = load("res://bin/gdoscsender.gdns").new()
	oscsender.setup( "127.0.0.1", 12000 )
	oscsender.start()

func _process(delta):
	cube.rotate_y( delta * 1 )
	oscsender.msg("/gdosc")
	oscsender.add( self )
	oscsender.add( cube.rotation )
	oscsender.add( cube.translation )
	oscsender.send()
	pass