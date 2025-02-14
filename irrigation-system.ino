// Define the pins
int soilMoisturePin = A0;    // Soil moisture sensor connected to analog pin A0
int relayPin = 3;            // Relay control connected to digital pin 3
int buzzerPin = 4;           // Buzzer connected to digital pin 4
int soilMoistureValue = 0;   // Variable to store the soil moisture sensor value

// Define a threshold for dryness (you can adjust this value)
int drySoilThreshold = 400;   // Moisture value below which the soil is considered dry

void setup() {
  pinMode(soilMoisturePin, INPUT);  // Set soil moisture sensor as input
  pinMode(relayPin, OUTPUT);        // Set relay pin as output
  pinMode(buzzerPin, OUTPUT);       // Set buzzer pin as output

  Serial.begin(9600);               // Start serial communication (for debugging)

  // Initial states
  digitalWrite(relayPin, LOW);      // Ensure pump is off at startup
  digitalWrite(buzzerPin, LOW);     // Ensure buzzer is off at startup
}

void loop() {
  soilMoistureValue = analogRead(soilMoisturePin);  // Read moisture sensor value

  // Print the moisture value for debugging
  Serial.print("Soil Moisture: ");
  Serial.println(soilMoistureValue);

  // Check if the soil is dry
  if (soilMoistureValue > drySoilThreshold ) { 
    // If moisture value is below the threshold, the soil is dry.
    digitalWrite(relayPin, HIGH);  // Turn on water pump (relay activated)
    digitalWrite(buzzerPin, HIGH); // Activate buzzer
    Serial.println("Soil is DRY, turning ON the water pump and buzzer.");
  }
  else {
    // If moisture value is above the threshold, the soil is wet.
    digitalWrite(relayPin, LOW);   // Turn off water pump (relay deactivated)
    digitalWrite(buzzerPin, LOW); // Deactivate buzzer
    Serial.println("Soil is WET, turning OFF the water pump and buzzer.");
  }

  delay(1000);  // Delay for 1 second before taking another reading
}
