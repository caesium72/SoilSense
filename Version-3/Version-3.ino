// Version 1.1 with Blynk Integration

// Blynk Credentials
#define BLYNK_TEMPLATE_ID "TMPL6oLHTE8SV"
#define BLYNK_TEMPLATE_NAME "Irrigation Monitoring"
#define BLYNK_AUTH_TOKEN "vYcbYnCjJ6nCWpk7gCmDe0bOF95dKs-x"

// Libraries
#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
#include <DHT.h>

// Pin Definitions
#define SOIL_MOISTURE_PIN 34   // GPIO34 for Soil Moisture (Analog)
#define DHT_PIN 4              // GPIO4 for DHT11
#define RELAY_PIN 19           // GPIO19 for Relay
#define BUZZER_PIN 21          // GPIO21 for Buzzer
#define LED_PIN 22             // GPIO22 for LED
#define TRIG_PIN 5             // GPIO5 for Ultrasonic Trigger
#define ECHO_PIN 18            // GPIO18 for Ultrasonic Echo

// DHT11 Setup
#define DHT_TYPE DHT11
DHT dht(DHT_PIN, DHT_TYPE);

// Wi-Fi Credentials
const char* ssid = "Caesium";       // Replace with your Wi-Fi SSID
const char* password = "helloworld"; // Replace with your Wi-Fi password

// Threshold for soil moisture sensor
int soilMoistureThreshold = 1500; // Adjust based on sensor calibration

// Global variable for relay state (manual control via Blynk)
bool relayState = false;

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
        Blynk.begin(BLYNK_AUTH_TOKEN, ssid, password); // Connect to Blynk
    } else {
        Serial.println("\nWiFi connection failed! Running offline mode.");
    }
}

// Blynk Virtual Pin Handler for Manual Relay Control
BLYNK_WRITE(V0) {
    int value = param.asInt(); // Get value from Blynk app (0 or 1)
    if (value == 1) {
        digitalWrite(RELAY_PIN, HIGH); // Turn relay ON
        relayState = true;             // Set to manual control
    } else {
        digitalWrite(RELAY_PIN, LOW);  // Turn relay OFF
        relayState = false;            // Return to automatic control
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
    float distance = duration * 0.034 / 2;  // Distance in cm
    // float distanceInches = distance * 0.3937; // Uncomment to return inches
    return distance;
}

void loop() {
    Blynk.run(); // Handle Blynk communication

    // Read Soil Moisture
    int soilMoistureValue = analogRead(SOIL_MOISTURE_PIN);
    float moisturePercentage = map(soilMoistureValue, 4095, 0, 0, 100); // Convert to percentage

    // Read Temperature and Humidity
    float humidity = dht.readHumidity();
    float temperature = dht.readTemperature();

    // Read Water Level
    float waterLevel = getWaterLevel();

    // Send data to Blynk
    Blynk.virtualWrite(V3, moisturePercentage); // Soil moisture percentage
    Blynk.virtualWrite(V4, temperature);        // Temperature in °C
    Blynk.virtualWrite(V5, humidity);           // Humidity in %
    Blynk.virtualWrite(V6, waterLevel);         // Water level in cm

    // Print to Serial Monitor
    Serial.print("Soil Moisture: ");
    Serial.print(soilMoistureValue);
    Serial.print(" (");
    Serial.print(moisturePercentage);
    Serial.println("%)");

    if (isnan(humidity) || isnan(temperature)) {
        Serial.println("Failed to read from DHT sensor!");
    } else {
        Serial.print("Temperature: ");
        Serial.print(temperature);
        Serial.print(" °C, Humidity: ");
        Serial.print(humidity);
        Serial.println(" %");
    }

    Serial.print("Water Level: ");
    Serial.print(waterLevel);
    Serial.println(" cm");

    // Control Buzzer and LED based on Soil Moisture
    if (soilMoistureValue > soilMoistureThreshold) {
        digitalWrite(BUZZER_PIN, HIGH);
        digitalWrite(LED_PIN, HIGH);
        Serial.println("Soil Moisture Low! Watering...");
    } else {
        digitalWrite(BUZZER_PIN, LOW);
        digitalWrite(LED_PIN, LOW);
        Serial.println("Soil Moisture Sufficient.");
    }

    // Control Relay (Pump) - Automatic mode if not manually controlled
    if (!relayState) {
        if (soilMoistureValue > soilMoistureThreshold) {
            digitalWrite(RELAY_PIN, HIGH); // Turn on the pump
        } else {
            digitalWrite(RELAY_PIN, LOW);  // Turn off the pump
        }
    }

    delay(1000); // Update every 1 second
}