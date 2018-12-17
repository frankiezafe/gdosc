extends Object

var oscsndr

func _ready():
	
	oscsndr = load("res://bin/gdoscsender.gdns").new()
	# [mandatory] will send messages to ip:port
	oscsndr.setup( "127.0.0.1", 12000 )
	# [mandatory] enabling emission
	oscsndr.start()

func _process(delta):
	# creation of new message
	oscsndr.msg("/hello")
	# adding an object, will send its name
	oscsndr.add( self )
	# adding a float
	oscsndr.add( delta )
	# adding a Vector2
	oscsndr.add( Vector2( randf(), randf() ) )
	# adding a Vector3 (position, scale, rotation, etc)
	oscsndr.add( Vector3( randf(), randf(), randf() ) )
	# sending the message
	oscsndr.send()
	pass
	
func _exit_tree ( ):
	# disable the sender, highly recommended!
	oscsndr.stop()