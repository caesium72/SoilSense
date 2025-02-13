# SoilSense
A microprocessor and microcontroller project based on smart irrigation and monitoring system 
Introduction
Plants are Important for the survival of our environment, though we hardly get to water them regularly. This leads to poor plant health and wastage of resources. In drought-prone areas, conserving water is becoming more essential. To tackle these problems, we have developed an Arduino-based Smart Irrigation System that automates irrigation depending on soil moisture levels, which is simple for human interference and gives the greatest water use efficiency.

**Objective**
The Smart Irrigation System aims to:
•	Automatically detect soil moisture levels and control irrigation.
•	Prevent overwatering or underwatering of plants.
•	Integrate remote monitoring using ESP8266 Wi-Fi module.
•	Improve water efficiency, especially in drought-affected areas.
•	Reduce human intervention in plant care.
•	Provide an affordable and scalable solution for home gardens and agriculture.



_Required Components_****
COMPONENT	QUANTITY	DESCRIPTION
Arduino Uno	1	Microcontroller for the system 
Soil Moisture Sensor	As Required	Measures soil moisture
Relay Module	1	Controls the water pump
ESP8266 Wi-Fi Module	1	Wi-Fi integration
Water Pump	1	Supplies Water
DHT Sensor	As Required	Measures temperature & humidity
Buzzer	2	Provides alerts in case of issues
LED	As Required	Indicates system status or any alerts
Power Supply	1	Provides power to the system
Jumper Wires	As Required	For Connections
Resistors	As Required	Electrical resistance components
Water Tubes	As Required	Distributes water via pump
Breadboard	1	For Connection purposes
Other Purposes	As Required	Miscellaneous needs

Working Procedure
1.	Soil Moisture Sensing: 
o	The soil moisture sensor detects the water content in the soil.
o	If the moisture is below a certain threshold (21%-40%), the Arduino triggers the relay to turn on the water pump.

2.	Water Pump Activation: 
o	The relay module acts as a switch, turning the pump ON or OFF based on sensor readings.
3.	DHT Sensor Monitoring: 
o	Measures temperature and humidity for environmental tracking like Temperatures and Humidity
4.	Buzzer & LED Alerts: 
o	The buzzer sounds and LED blinks if the soil moisture is critically low .
o	If the water tank is empty it will sound the buzzer to a different sound .
5.	Ultrasonic sensor:
o	The sonar will be placed on the water tank to indicate whether the tank needs to be filled or not.
6.	Wi-Fi Connectivity (ESP8266): 
o	Sends real-time data to a cloud server or a mobile application for remote monitoring. For this case Blynk app will be used.
7.	Automatic & Manual Mode: 
o	Users can switch between automatic irrigation and manual control using the Wi-Fi module.

Conclusion
The Smart Irrigation System using Arduino is a cost-effective, automated solution for efficient water management. By integrating soil moisture sensing, remote monitoring, and automation, it enhances agricultural productivity and supports sustainable water usage. Future advancements, such as AI-based scheduling and solar power, will further improve its efficiency and make it a powerful tool in modern irrigation practices.


### Overview
1. [Presentation](https://docs.google.com/presentation/d/1TBcVj-FMSX9GrTplZ_tyU9wid7fbfIdF/edit#slide=id.p2)
2. [Report]([https://docs.google.com/presentation/d/1TBcVj-FMSX9GrTplZ_tyU9wid7fbfIdF/edit#slide=id.p2](https://drive.google.com/file/d/1T-q967cDF0wvnzSc4jQwOPCbLksL-jbN/view?usp=sharing))

