#include "namo_serial_proto.h"  // Include the Namo Protocol library
#include "DHT.h"                 // Include the DHT library for sensor functions

// Define the DHT pin and sensor type (DHT11 or DHT22)
#define DHTPIN 16              // Pin where DHT11 is connected on grove shield for pico 2
#define BUZZER_PIN 18            // Pin where buzzer is connected on grove shield for pico 2   
#define DHTTYPE DHT11           // We have DHT sensor version 11 

// Define the LED pin for the Raspberry Pi Pico onboard LED
#define LED_PIN_PICO_BOARD 25  // GPIO pin for the onboard LED (GP25)
float tempThreshold = 22.0;

DHT dht(DHTPIN, DHTTYPE);  // Create an instance of the DHT sensor

namo::SerialProtocol serialProto;

bool core0_led_state = false;  // Tracks LED state for Core 0

// Function to toggle the onboard LED on Core 0
void toggleCore0LED() {
  core0_led_state = !core0_led_state;  // Toggle the LED state
  digitalWrite(LED_PIN_PICO_BOARD, core0_led_state ? HIGH : LOW);  // Update the LED state
}

void dht11_get_data() {
  // Reading the humidity and temperature
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();
  

  // Check if the reading is valid
  if (isnan(humidity) || isnan(temperature)) {
    serialProto.sendText("Error", "Failed to read from DHT sensor");
    return;
  }
if (temperature > tempThreshold){

  digitalWrite(BUZZER_PIN, HIGH);
    delay(200);
    digitalWrite(BUZZER_PIN, LOW);
  
}
  // Sending the data to the serial protocol
  char buffer[30];
  snprintf(buffer, sizeof(buffer), "%.1f", temperature);
  serialProto.sendText("Temperature", buffer);  // Send temperature

  snprintf(buffer, sizeof(buffer), "%.1f", humidity);
  serialProto.sendText("Humidity", buffer);  // Send humidity
  snprintf(buffer, sizeof(buffer), "%.1f", tempThreshold);
  serialProto.sendText("Turn on AC Exceeded Temp Threshold", buffer); 
  //Send temperature
Serial.print("Temperature: ");
Serial.print(temperature);
Serial.print(" Humidity: ");
Serial.print(humidity);
Serial.print("Threshold: ");
Serial.print(tempThreshold);


}

void setup() {
  Serial.begin(9600);
  while (!Serial) delay(10);  // Wait for serial to be ready

  dht.begin();  // Initialize DHT sensor

  pinMode(LED_PIN_PICO_BOARD, OUTPUT);  // Configure onboard LED pin
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(SPEAKER_PIN, OUTPUT);
  toggleCore0LED();
  delay(500);
  toggleCore0LED();

  serialProto.begin(onMessageReceived);  // Start the NAMO Protocol
}

void loop() {  
  serialProto.process();  // Continuously process incoming messages
}

void processMsg(const char* key, const uint8_t* value, uint32_t valueLen, uint8_t msgType) {
  if (msgType == namo::SerialProtocol::MSG_TYPE_BINARY && strncmp(key, "DHT11_GETDATA", 8) == 0) {
    dht11_get_data();  // Get data from DHT11 sensor
  }
  else if (msgType == namo::SerialProtocol::MSG_TYPE_BINARY && strncmp(key, "LED_TOGGLE", 8) == 0) {
    int waitVal = 10 * value[1];
    for (uint8_t i = 0; i < value[0] && i < 255; i++) { 
      toggleCore0LED();
      delay(waitVal);
      toggleCore0LED();
      delay(waitVal);
    }
  }
}

void onMessageReceived(const char* key, const uint8_t* value, uint32_t valueLen, uint8_t msgType) {
  processMsg(key, value, valueLen, msgType);
  
  char newKey[namo::SerialProtocol::MAX_KEY_SIZE];
  snprintf(newKey, sizeof(newKey), "%s_ack", key);
  
  if (msgType == namo::SerialProtocol::MSG_TYPE_TEXT) {
    char newValue[namo::SerialProtocol::MAX_VALUE_SIZE];
    snprintf(newValue, sizeof(newValue), "%s_ack", (char*)value);
    serialProto.sendText(newKey, newValue);
  }
  else if (msgType == namo::SerialProtocol::MSG_TYPE_BINARY) {
    serialProto.sendBinary(newKey, value, valueLen);
  }
}
