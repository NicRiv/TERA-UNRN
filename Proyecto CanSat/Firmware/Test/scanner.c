#include <Wire.h>

#define SDA_PIN 21
#define SCL_PIN 22

void setup() {
  Serial.begin(115200);
  while (!Serial) delay(10);
  
  Serial.println("\n=== I2C Scanner para ESP32 ===");
  Serial.printf("SDA: GPIO %d | SCL: GPIO %d\n", SDA_PIN, SCL_PIN);
  
  Wire.begin(SDA_PIN, SCL_PIN);
  Wire.setClock(100000); // 100 kHz estándar
  
  scanI2C();
}

void loop() {
  delay(5000); // Escanea cada 5 segundos
  scanI2C();
}

void scanI2C() {
  byte error, address;
  int deviceCount = 0;

  Serial.println("Escaneando direcciones...");

  for (address = 1; address < 127; address++) {
    Wire.beginTransmission(address);
    error = Wire.endTransmission();

    if (error == 0) {
      Serial.print("Dispositivo encontrado en 0x");
      if (address < 16) Serial.print("0");
      Serial.println(address, HEX);
      deviceCount++;
    } else if (error == 4) {
      Serial.print("Error desconocido en 0x");
      if (address < 16) Serial.print("0");
      Serial.println(address, HEX);
    }
  }

  if (deviceCount == 0) {
    Serial.println("No se encontraron dispositivos I2C.");
  } else {
    Serial.printf("Total: %d dispositivo(s) encontrado(s).\n", deviceCount);
  }
  Serial.println("--------------------------");
}   