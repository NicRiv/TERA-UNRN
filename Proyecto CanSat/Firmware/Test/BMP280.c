#include <Wire.h>
#include <Adafruit_BMP280.h>

Adafruit_BMP280 bmp;

void setup() {
  Serial.begin(9600);
  // Inicia el sensor en dirección 0x76 o 0x77
  if (!bmp.begin(0x76)) { 
    Serial.println("No se encontró BMP280");
    while (1);
  }
  // Configuración para alta precisión
  bmp.setSampling(Adafruit_BMP280::MODE_NORMAL,
                  Adafruit_BMP280::SAMPLING_X2,
                  Adafruit_BMP280::SAMPLING_X16,
                  Adafruit_BMP280::FILTER_X16,
                  Adafruit_BMP280::STANDBY_MS_500);
}

void loop() {
  float temp = bmp.readTemperature();
  float pres = bmp.readPressure() / 100.0; // Pa a hPa
  float alt  = bmp.readAltitude(1013.25);  // Altitud respecto al nivel del mar

  Serial.print("Temp: "); Serial.print(temp); Serial.println(" °C");
  Serial.print("Pres: "); Serial.print(pres); Serial.println(" hPa");
  Serial.print("Alt:  "); Serial.print(alt); Serial.println(" m");
  Serial.println();
  delay(2000);
}   