# mqttgpio  

D1 mini code for control of an antenna switch using mqtt. Intended for use with up to 4 single pole double throw latching RF relays.  
  
#### Setup  

Edit Wifi ssid and password for your network  
Edit commandTopic and statusTopic to suit your environment  
Edit mqtt_server to match address of your mqtt broker  
Compile and flash code to D1 mini  
  
#### Usage  

Use an MQTT client to send four character control string to topic barn/iot/antSwitchCommand  
Each character of the control string corresponds with a single relay and can be '1' , '2', or 'x' to set position 1, position 2, or as-is  
  
#### Hardware  

[Schematic](https://i.imgur.com/pxae8wm.png)
  
[PCB](https://i.imgur.com/wOAe9j4.png)
  
[Gerber](https://drive.google.com/file/d/1SJwJE5P14cPRr-Dynpui_YQx7vtM8f5s/view?usp=sharing)
  
#### Credits  

Thanks to knolleary for Arduino MQTT client: (https://github.com/knolleary/pubsubclient)  
  

