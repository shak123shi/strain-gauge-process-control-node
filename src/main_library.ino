#include "HX711.h"

// Pin definitions
const int DOUT_PIN = 3;
const int SCK_PIN = 2;
const int BUZZER_PIN = 9;
const int TTL_PIN = 8;

// Process threshold and calibration
const float THRESHOLD = 2000.0;     // Trigger threshold in grams
float calibration_factor = -7050.0; // Derived via calibration procedure

HX711 scale;

void setup() {
  Serial.begin(9600);
  
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(TTL_PIN, OUTPUT);
  
  scale.begin(DOUT_PIN, SCK_PIN);
  scale.set_scale(calibration_factor);
  scale.tare(); // Zero the scale on startup
}

void loop() {
  // Read average of 5 samples for digital smoothing
  float weight = scale.get_units(5);
  
  Serial.print("Weight: ");
  Serial.print(weight, 1);
  Serial.println(" g");
  
  // Real-time threshold evaluation & digital interlock
  if (weight >= THRESHOLD) {
    digitalWrite(BUZZER_PIN, HIGH);
    digitalWrite(TTL_PIN, HIGH);
  } else {
    digitalWrite(BUZZER_PIN, LOW);
    digitalWrite(TTL_PIN, LOW);
  }
  
  delay(100);
}
