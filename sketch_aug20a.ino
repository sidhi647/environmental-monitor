#include <Wire.h>
#include <Adafruit_BME280.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
Adafruit_BME280 bme;

void setup() {
  Serial.begin(115200);
  delay(1000);

  // Start I2C
  Wire.begin(21, 22);

  // Start BME280
  if (!bme.begin(0x76)) {
    Serial.println("Could not find BME280!");
    while (1);
  }

  Serial.println("BME280 found!");

  // Start OLED
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("Could not find OLED!");
    while (1);
  }

  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.println("Environmental");
  display.println("Monitor");
  display.display();

  delay(2000);
}

void loop() {

  float temperature = bme.readTemperature() * 9.0 / 5.0 + 32.0;
  float humidity = bme.readHumidity();
  float pressure = bme.readPressure() / 100.0F;

  // Print to Serial Monitor
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" °C");

  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.println(" %");

  Serial.print("Pressure: ");
  Serial.print(pressure);
  Serial.println(" hPa");

  Serial.println("-------------------");

  // Print to OLED
  display.clearDisplay();

  display.setTextSize(1);

  display.setCursor(0, 0);
  display.println("ENVIRONMENT MONITOR");

  display.setCursor(0, 18);
  display.print("Temp: ");
  display.print(temperature, 1);
  display.println(" F");

  display.setCursor(0, 34);
  display.print("Humidity: ");
  display.print(humidity, 1);
  display.println(" %");

  display.setCursor(0, 50);
  display.print("Pressure: ");
  display.print(pressure, 1);
  display.println(" hPa");

  display.display();

  delay(2000);
}