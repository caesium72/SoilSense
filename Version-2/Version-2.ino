#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEScan.h>
#include <BLEAdvertisedDevice.h>

#include <WiFi.h>
#include <DHT.h>
#include <ESPAsyncWebServer.h>

// Pin Definitions
#define SOIL_MOISTURE_PIN 34   // GPIO34 for Soil Moisture (Analog)
#define DHT_PIN 4              // GPIO4 for DHT11
#define RELAY_PIN 19           // GPIO19 for Relay
#define BUZZER_PIN 21          // GPIO21 for Buzzer
#define LED_PIN 22             // GPIO22 for LED

// DHT11 Setup
#define DHT_TYPE DHT11
DHT dht(DHT_PIN, DHT_TYPE);

// Wi-Fi Credentials
const char* ssid = "Caesium";
const char* password = "helloworld";

// Threshold for soil moisture sensor
int soilMoistureThreshold = 2000; // Adjust based on sensor calibration

// Create an instance of the server
AsyncWebServer server(80);

void setup() {
    // Start Serial Monitor
    Serial.begin(115200);

    // Set pin modes
    pinMode(SOIL_MOISTURE_PIN, INPUT);
    pinMode(RELAY_PIN, OUTPUT);
    pinMode(BUZZER_PIN, OUTPUT);
    pinMode(LED_PIN, OUTPUT);

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

    // Handle root URL
    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
        String html = "<html><body><h1>Smart Irrigation System</h1>";
        
        // Read Soil Moisture
        int soilMoistureValue = analogRead(SOIL_MOISTURE_PIN);
        html += "<p>Soil Moisture: " + String(soilMoistureValue) + "</p>";

        // Read Temperature and Humidity
        float humidity = dht.readHumidity();
        float temperature = dht.readTemperature();

        if (isnan(humidity) || isnan(temperature)) {
            html += "<p>Failed to read from DHT sensor!</p>";
        } else {
            html += "<p>Temperature: " + String(temperature) + " °C</p>";
            html += "<p>Humidity: " + String(humidity) + " %</p>";
        }

        // Control the Pump, Buzzer, and LED based on Soil Moisture
        if (soilMoistureValue > soilMoistureThreshold) {  // If soil is dry
            html += "<p>Soil Moisture Low! Watering...</p>";
            digitalWrite(RELAY_PIN, HIGH);  // Turn on the pump
            digitalWrite(BUZZER_PIN, HIGH); // Turn on buzzer
            digitalWrite(LED_PIN, HIGH);    // Turn on LED
        } else {  
            html += "<p>Soil Moisture Sufficient.</p>";
            digitalWrite(RELAY_PIN, LOW);  // Turn off the pump
            digitalWrite(BUZZER_PIN, LOW); // Turn off buzzer
            digitalWrite(LED_PIN, LOW);    // Turn off LED
        }
        
        html += "</body></html>";
        
        // Send the HTML content as the response
        request->send(200, "text/html", html);
    });

    // Start the server
    server.begin();
}

void loop() {
    // Nothing needed here for now; all logic is handled by the web server
}