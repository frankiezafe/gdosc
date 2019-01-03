extends Object

var oscrcv
var cube
var sky

func _ready():
	
	cube = get_node( "../cube" )
	sky = get_node( "../env" ).get_environment().background_sky
	print( sky )
	oscrcv = load("res://addons/gdosc/bin/gdoscreceiver.gdns").new()
	oscrcv.max_queue( 20 ) 			# maximum number of messages in the buffer, default is 100
	oscrcv.avoid_duplicate( true )	# receiver will only keeps the "latest" message for each address
	oscrcv.setup( 14000 )			# listening to port 14000
	oscrcv.start()					# starting the reception of messages

func _process(delta):
		
	while( oscrcv.has_message() ): 	# check if there are pending messages
		var msg = oscrcv.get_next()	# retrieval of the messages as a dictionary
		# using message data
		var args = msg["args"]
		if msg["address"] == "/cube/pos" and cube != null:
			cube.translation = Vector3( args[0], args[1], args[2] )
		elif msg["address"] == "/cube/col" and cube != null:
			cube.get_surface_material(0).albedo_color = Color( args[0], args[1], args[2] )
		elif msg["address"] == "/cube/visible" and cube != null:
			cube.visible = args[0]
		elif msg["address"] == "/sky/horizon" and sky != null:
			var c = Color( args[0], args[1], args[2] )
			sky.sky_horizon_color = c
			sky.ground_horizon_color = c
		else:
			print( msg["address"] + "?" )
	
	pass
	
func _exit_tree ( ):
	oscrcv.stop()					# stops listening to port, highly recommended!