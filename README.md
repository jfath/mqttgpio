# mqttgpio  

D1 mini code for control of an antenna switch using mqtt. Intended for use with up to 4 single pole double throw latching RF relays.  
  
#### Setup  

Edit WiFi ssid and password for your network  
Edit commandTopic and statusTopic to suit your environment  
Edit mqtt_server to match address of your mqtt broker  
Compile and flash code to D1 mini  
  
#### Usage  

Use an MQTT client to send four character control string to your command topic  
Optionally, check your status topic to see if the control string was received   
Each character of the control string corresponds with a single relay and can be '1' , '2', or 'x' to set position 1, position 2, or as-is  
  
#### Hardware  

[Schematic](https://github.com/jfath/mqttgpio/blob/master/Schematic_antennaSwitch_Sheet-1_20180430083315.png)
  
[PCB](https://github.com/jfath/mqttgpio/blob/master/PCB_antennaSwitch-PCB_20180430085031.png)
  
[Gerber](https://github.com/jfath/mqttgpio/blob/master/Gerber_antennaSwitch_PCB_20180430083238.zip)
  
#### Credits  

Thanks to knolleary for Arduino MQTT client: (https://github.com/knolleary/pubsubclient)  
  

