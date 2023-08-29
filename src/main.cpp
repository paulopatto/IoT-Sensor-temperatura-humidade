#include <Arduino.h>
#include<DHT.h>                 // Arduino library for DHT11, DHT22, etc Temp & Humidity Sensors
#include<Wire.h>                // This library allows you to communicate with I2C/TWI devices.
#include<Adafruit_GFX.h>        // Adafruit GFX graphics core library, this is the 'core' class that all our other graphics libraries derive from.
#include<Adafruit_SSD1306.h>    // SSD1306 oled driver library for monochrome 128x64 and 128x32 displays

#define SERIAL_SPEED 115200
#define LED_BUILTIN 2

#define DHT_PORT D3
#define DHT_TYPE DHT22
#define IN_CELSIUS false // Define a leitura para celsius
DHT dht(DHT_PORT, DHT_TYPE);

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET LED_BUILTIN
#define DISPLAY_VOLTAGE_3v3 0x3C

#define LABEL_TEXT_SIZE 1
#define MAIN_MESSAGE_TEXT_SIZE 5
#define SCALE_SYMBOL_MESSAGE_SIZE 2

/// Pinagem do protocolo I²C
#define DISPLAY_SLC_PORT D1 // SCK or SCL: Serial Clock
#define DISPLAY_SDA_PORT D2 // SDA: Serial Data
/// DOC: https://randomnerdtutorials.com/guide-for-oled-display-with-arduino/
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

struct Measure {
  String label;
  float value;
  char scaleSymbol;
};


Measure checkTemperature() {
  Measure value = {
    "Temperatura",
    dht.readTemperature(IN_CELSIUS),
    'C'
  };

  return value;
}

Measure checkHumidity() {
  Measure value = {
    "Humidade",
    dht.readHumidity(),
    '%'
  };

  return value;
}

/**
 * Configura o display OLED 0.96 I²C SSD1306
 */
void setupDisplay() {
  Serial.println("[INFO] Setting display OLED...");
  // Usa 3.3v internamente
  if(!display.begin(SSD1306_SWITCHCAPVCC, DISPLAY_VOLTAGE_3v3)) {
    Serial.println(F("[ERROR] Display: SSD1306 allocation failed"));
    for(;;);
  }

  display.setTextColor(WHITE);
  display.setTextSize(LABEL_TEXT_SIZE);
  display.setCursor(0,0);
  display.print("OK! OK! OK!");

  Serial.println("[INFO] Display OLED OK!");

  display.setTextColor(WHITE);
  display.clearDisplay();
}

void printMeasure(const Measure measure) {
  display.clearDisplay();

  display.setTextSize(LABEL_TEXT_SIZE);
  display.setCursor(0,0);
  display.print(measure.label);

  display.setTextSize(MAIN_MESSAGE_TEXT_SIZE);
  display.setCursor(20,20);
  display.print(String(measure.value));

  display.setTextSize(SCALE_SYMBOL_MESSAGE_SIZE);
  display.print(measure.scaleSymbol);

  Serial.println("[DEBUG] " + String(measure.label) + ": " + String(measure.value) + String(measure.scaleSymbol));
}

void printMessage() {
  Measure temp = checkTemperature();
  Measure humi = checkHumidity();

  if(isnanf(temp.value)) { 
    Serial.println(F("[ERROR] DHT temperature error NaN..."));
    delay(1000);
  } else {
    printMeasure(temp);
    delay(2000);
  }

  if(isnanf(humi.value)) { 
    Serial.println(F("[ERROR] DHT humidity error NaN..."));
    delay(1000);
  } else {
    printMeasure(humi);
    delay(2000);
  }
  
}

/**
 * put your setup code here, to run once
 */
void setup() {
  Serial.begin(SERIAL_SPEED);
  delay(2000);
  Serial.println("[INFO] Starting...");
  setupDisplay();
  //pinMode(LED_BUILTIN, OUTPUT);
}

/**
 * put your main code here, to run repeatedly
 */
void loop() {
  printMessage();
}