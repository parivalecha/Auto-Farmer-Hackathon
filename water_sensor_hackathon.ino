#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

int lowerThreshold = 280;
int upperThreshold = 480;

// Sensor pins
#define sensorPower 7
#define sensorPin A0
int val = 0; // Value for storing water level

void setup() {
  Serial.begin(9600);

  // Initialize with the I2C addr 0x3C (for the 128x64)
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  delay(2000);
  display.clearDisplay();

  pinMode(sensorPower, OUTPUT);
  digitalWrite(sensorPower, LOW);
}

void loop() {
  int level = readSensor();

  if (level == 0) {
    Serial.println("Water Level: Empty");
    display.clearDisplay();
    display.setTextSize(2); // I used this to increase text size on the oled
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0,0);
    display.println(" H2O LEVEL");
    display.println(" EMPTY");
  }
  else if (level > 0 && level <= lowerThreshold) {
    Serial.println("Water Level: Low");
    display.clearDisplay();
    display.setTextSize(2); 
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0,0);
    display.println(" H2O LEVEL");
    display.println("  LOW");
  }
  else if (level > lowerThreshold && level <= upperThreshold) {
    Serial.println("Water Level: Medium");
    display.clearDisplay();
    display.setTextSize(1.5); 
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0,0);
    display.println("   H2O LEVEL");
    display.println("     MEDIUM");
  }
  else if (level > upperThreshold) {
    Serial.println("Water Level: High");
    display.clearDisplay();
    display.setTextSize(1.5); // 
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0,0);
    display.println("   H2O LEVEL");
    display.println("     FULL");
  }
  display.display();
  delay(1000);
}

//This is a function used to get the reading
int readSensor() {
  digitalWrite(sensorPower, HIGH);
  delay(10);
  val = analogRead(sensorPin);
  digitalWrite(sensorPower, LOW);
  return val;
}
