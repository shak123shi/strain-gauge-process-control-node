// Direct bit-bang implementation of the HX711 24-bit serial interface
const int DOUT = 3;
const int PD_SCK = 2;
const int TTL_PIN = 8;
const int BUZZER_PIN = 9;

void setup() {
  Serial.begin(9600);
  pinMode(DOUT, INPUT);
  pinMode(PD_SCK, OUTPUT);
  pinMode(TTL_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
}

long read_raw_hx711() {
  // Wait until DOUT goes LOW indicating conversion completion
  while (digitalRead(DOUT) == HIGH);
  
  long raw_data = 0;
  
  // Clock in 24 bits MSB-first
  for (int i = 0; i < 24; i++) {
    digitalWrite(PD_SCK, HIGH);
    raw_data = (raw_data << 1) | digitalRead(DOUT);
    digitalWrite(PD_SCK, LOW);
  }
  
  // 25th clock pulse: locks channel A input gain to 128 for next conversion
  digitalWrite(PD_SCK, HIGH);
  digitalWrite(PD_SCK, LOW);
  
  // Sign extend 24-bit two's complement integer to 32-bit
  if (raw_data & 0x800000) {
    raw_data |= 0xFF000000;
  }
  
  return raw_data;
}

void loop() {
  long raw = read_raw_hx711();
  Serial.print("Raw ADC Counts: ");
  Serial.println(raw);
  delay(100);
}
