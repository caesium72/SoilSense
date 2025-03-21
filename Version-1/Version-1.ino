// version 1.0
#include <WiFi.h>
#include <DHT.h>

// Pin Definitions
#define SOIL_MOISTURE_PIN 34   // GPIO34 for Soil Moisture (Analog)
#define DHT_PIN 4              // GPIO4 for DHT11
#define RELAY_PIN 19           // GPIO19 for Relay
#define BUZZER_PIN 21          // GPIO21 for Buzzer
#define LED_PIN 22             // GPIO22 for LED

// Ultrasonic Sensor (Water Level) Pins
#define TRIG_PIN 5  // GPIO5 for Trigger
#define ECHO_PIN 18 // GPIO18 for Echo

// DHT11 Setup
#define DHT_TYPE DHT11
DHT dht(DHT_PIN, DHT_TYPE);

// Wi-Fi Credentials
const char* ssid = "Caesium";
const char* password = "helloworld";

// Threshold for soil moisture sensor
int soilMoistureThreshold = 1500; // Adjust based on sensor calibration

void setup() {
    // Start Serial Monitor
    Serial.begin(115200);

    // Set pin modes
    pinMode(SOIL_MOISTURE_PIN, INPUT);
    pinMode(RELAY_PIN, OUTPUT);
    pinMode(BUZZER_PIN, OUTPUT);
    pinMode(LED_PIN, OUTPUT);
    pinMode(TRIG_PIN, OUTPUT);
    pinMode(ECHO_PIN, INPUT);

    // Start DHT sensor
    dht.begin();

    // Start Wi-Fi with a timeout
    Serial.println("Connecting to WiFi...");
    WiFi.begin(ssid, password);
    
    int timeout = 20; // 20 seconds timeout
    while (WiFi.status() != WL_CONNECTED && timeout > 0) {
        delay(1000);
        Serial.print(".");
        timeout--;
    }
    
    if (WiFi.status() == WL_CONNECTED) {
        Serial.println("\nWiFi connected!");
        Serial.print("IP Address: ");
        Serial.println(WiFi.localIP());
    } else {
        Serial.println("\nWiFi connection failed! Running offline mode.");
    }
}

// Function to measure water level using Ultrasonic Sensor
float getWaterLevel() {
    digitalWrite(TRIG_PIN, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIG_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG_PIN, LOW);
  
    long duration = pulseIn(ECHO_PIN, HIGH);
    float distance = duration * 0.034 / 2;  // Convert to cm
    float distanceInches = distance * 0.3937; // Convert cm to inches
  
    return distance;
    //return distanceInches;

}

void loop() {
    // Read Soil Moisture
    int soilMoistureValue = analogRead(SOIL_MOISTURE_PIN);
    Serial.print("Soil Moisture: ");
    Serial.println(soilMoistureValue);

    // Read Temperature and Humidity
    float humidity = dht.readHumidity();
    float temperature = dht.readTemperature();
    
    if (isnan(humidity) || isnan(temperature)) {
        Serial.println("Failed to read from DHT sensor!");
    } else {
        Serial.print("Temperature: ");
        Serial.print(temperature);
        Serial.print(" °C, Humidity: ");
        Serial.print(humidity);
        Serial.println(" %");
    }

    // Control the Pump, Buzzer, and LED based on Soil Moisture
    if (soilMoistureValue > soilMoistureThreshold) {  // If soil is dry (adjust condition if needed)
        digitalWrite(RELAY_PIN, HIGH);  // Turn on the pump
        digitalWrite(BUZZER_PIN, HIGH); // Turn on buzzer
        digitalWrite(LED_PIN, HIGH);    // Turn on LED
        Serial.println("Soil Moisture Low! Watering...");
    } else {  
        digitalWrite(RELAY_PIN, LOW);  // Turn off the pump
        digitalWrite(BUZZER_PIN, LOW); // Turn off buzzer
        digitalWrite(LED_PIN, LOW);    // Turn off LED
        Serial.println("Soil Moisture Sufficient.");
    }

        // Read Water Level
    float waterLevel = getWaterLevel();
    Serial.print("Water Level: ");
    Serial.print(waterLevel);
    Serial.println(" Inch");

    // Delay before reading again
    delay(1000);
}