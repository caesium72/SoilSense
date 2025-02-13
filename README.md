# SoilSense

**SoilSense** is a microprocessor and microcontroller project based on a smart irrigation and monitoring system.

## Introduction

Plants are crucial for the survival of our environment, but irregular watering often leads to poor plant health and resource wastage. In drought-prone areas, conserving water is essential. To address these challenges, we have developed an Arduino-based Smart Irrigation System that automates irrigation based on soil moisture levels. This minimizes human intervention while maximizing water use efficiency.

## Objective

The Smart Irrigation System aims to:
- Automatically detect soil moisture levels and control irrigation.
- Prevent overwatering or underwatering of plants.
- Integrate remote monitoring using an ESP8266 Wi-Fi module.
- Improve water efficiency, especially in drought-affected areas.
- Reduce human intervention in plant care.
- Provide an affordable and scalable solution for home gardens and agriculture.

## Required Components

| COMPONENT             | QUANTITY      | DESCRIPTION                                         |
| --------------------- | ------------- | --------------------------------------------------- |
| Arduino Uno           | 1             | Microcontroller for the system                      |
| Soil Moisture Sensor  | As Required   | Measures soil moisture                              |
| Relay Module          | 1             | Controls the water pump                             |
| ESP8266 Wi-Fi Module  | 1             | Wi-Fi integration                                   |
| Water Pump            | 1             | Supplies water                                      |
| DHT Sensor            | As Required   | Measures temperature & humidity                     |
| Buzzer                | 2             | Provides alerts in case of issues                   |
| LED                   | As Required   | Indicates system status or alerts                   |
| Power Supply          | 1             | Provides power to the system                        |
| Jumper Wires          | As Required   | For connections                                     |
| Resistors             | As Required   | Electrical resistance components                    |
| Water Tubes           | As Required   | Distributes water via pump                          |
| Breadboard            | 1             | For connection purposes                             |
| Other Components      | As Required   | Miscellaneous needs                                 |

## Working Procedure

1. **Soil Moisture Sensing:**  
   - The soil moisture sensor detects the water content in the soil.  
   - If the moisture is below a certain threshold (21%-40%), the Arduino triggers the relay to turn on the water pump.

2. **Water Pump Activation:**  
   - The relay module acts as a switch, turning the pump on or off based on sensor readings.

3. **DHT Sensor Monitoring:**  
   - Measures temperature and humidity for environmental tracking.

4. **Buzzer & LED Alerts:**  
   - The buzzer sounds and the LED blinks if the soil moisture is critically low.  
   - A different buzzer sound indicates if the water tank is empty.

5. **Ultrasonic Sensor:**  
   - The ultrasonic sensor is placed on the water tank to indicate whether the tank needs refilling.

6. **Wi-Fi Connectivity (ESP8266):**  
   - Sends real-time data to a cloud server or mobile application for remote monitoring. In this project, the Blynk app is used.

7. **Automatic & Manual Mode:**  
   - Users can switch between automatic irrigation and manual control via the Wi-Fi module.

## Usage

1. **Hardware Setup:**  
   - Connect all components according to the provided circuit diagram.
   - Ensure that all wiring is secure and matches the schematic.

2. **Software Setup:**  
   - Install the Arduino IDE and necessary libraries for the sensors and ESP8266 module.
   - Upload the Arduino sketch to the Arduino Uno.
   - Configure the Blynk app (or your preferred platform) to monitor and control the system.

3. **Operation:**  
   - Once powered, the system will continuously monitor soil moisture.
   - The water pump will activate automatically when moisture levels fall below the preset threshold.
   - Alerts via buzzer and LED will notify you of critical conditions, such as low soil moisture or an empty water tank.

## Contributing

Contributions are welcome! Feel free to fork this repository and submit pull requests with improvements or additional features.

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.


Conclusion
The Smart Irrigation System using Arduino is a cost-effective, automated solution for efficient water management. By integrating soil moisture sensing, remote monitoring, and automation, it enhances agricultural productivity and supports sustainable water usage. Future advancements, such as AI-based scheduling and solar power, will further improve its efficiency and make it a powerful tool in modern irrigation practices.


### Overview
1. [Presentation](https://docs.google.com/presentation/d/1TBcVj-FMSX9GrTplZ_tyU9wid7fbfIdF/edit#slide=id.p2)

