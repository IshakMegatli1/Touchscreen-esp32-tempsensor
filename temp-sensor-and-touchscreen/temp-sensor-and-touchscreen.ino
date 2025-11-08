#include <TFT_eSPI.h>
#include <SPI.h>
#include <DHT.h>

#define DHTPIN 18       // ✅ Using GPIO18
#define DHTTYPE DHT11   // or DHT11 if that’s your sensor

TFT_eSPI tft = TFT_eSPI();
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(115200);
  dht.begin();
  tft.init();
  tft.setRotation(1);
  tft.fillScreen(TFT_BLACK);
  tft.setTextColor(TFT_CYAN, TFT_BLACK);
  tft.setTextDatum(MC_DATUM);
}

void loop() {
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Failed to read from DHT sensor!");
    tft.drawString("Sensor error!", 160, 120, 4);
    delay(2000);
    return;
  }

  tft.fillScreen(TFT_BLACK);
  tft.setTextSize(2);
  tft.drawString("Temperature:", 160, 80, 2);
  tft.drawFloat(temperature, 1, 160, 100, 4);
  tft.drawString("C", 240, 100, 4);

  tft.drawString("Humidity:", 160, 140, 2);
  tft.drawFloat(humidity, 1, 160, 160, 4);
  tft.drawString("%", 240, 160, 4);

  delay(3000);
}
