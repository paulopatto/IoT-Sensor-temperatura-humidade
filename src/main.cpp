#include <Arduino.h>
#include<DHT.h>

#define LED_BUILTIN 2
#define DHT_PORT D3
#define DHT_TYPE DHT22
#define SERIAL_SPEED 115200
#define IN_CELSIUS false // Define a leitura para celsius

DHT dht(DHT_PORT, DHT_TYPE);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(SERIAL_SPEED);
  pinMode(LED_BUILTIN, OUTPUT);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(LED_BUILTIN, HIGH);
  
  Serial.flush();
  Serial.println("================================================");
  Serial.println("|\tTemperatura: " + String(dht.readTemperature(IN_CELSIUS)) + " ºC");
  Serial.println("|\tHumidade: " + String(dht.readHumidity()) + "%");
  Serial.println("================================================\n\n\n\n");
  delay(1500);
  digitalWrite(LED_BUILTIN, LOW);

  delay(5000);
}