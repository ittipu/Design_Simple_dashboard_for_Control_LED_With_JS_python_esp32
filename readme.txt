
Introduction:
Control an LED from browser and also send some command to device. 
We have used several programming language to do this project. Like Python for handleing websocket request from web browser,
Arduino IDE for program the esp32, and HTML, CSS, JavaScript for design a web page.


How it works:

	1. Here we are using JavaScript Paho mqtt client for publish and receiving data.

	2. We use python as worker which task is handle the request from devices and web-browser call dashboard.
	   we use this worker beacause browser works via websocket but our esp32 or physical devices can't 
	   work websocket directly, pythsical devices works as TCP port. So we run a python script which 
	   receive those command from web browser and send it to esp32 in TCP format.
	
	3. For designing the simple dashboard we use HTML, CSS and JavaScript. We run paho mqtt client in
	   script which send the dashboard command in python.

	4. And finally esp32 pubsub mqtt client receive from python and works as command.

	5. Python send data to esp32 in JSON format.

	6. ArduinoJson Library has used for handle those json data.


