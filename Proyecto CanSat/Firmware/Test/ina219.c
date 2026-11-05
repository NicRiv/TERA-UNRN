#include <Wire.h>
#include <Adafruit_INA219.h>

// Crear objeto del sensor
Adafruit_INA219 ina219;

void setup(void) {
  Serial.begin(115200);
  // Inicializar el sensor (por defecto: 32V, 2A)
  if (! ina219.begin()) {
    Serial.println("No se encontro el chip INA219");
    while (1);
  }
  // Opcional: Ajustar calibración para mayor precisión en rangos menores
  // ina219.setCalibration_32V_1A();
  // ina219.setCalibration_16V_400mA();
}

void loop(void) {
  // Leer valores brutos
  float shuntvoltage = ina219.getShuntVoltage_mV();
  float busvoltage = ina219.getBusVoltage_V();
  float current_mA = ina219.getCurrent_mA();
  float power_mW = ina219.getPower_mW();
  
  // Calcular voltaje de carga
  float loadvoltage = busvoltage + (shuntvoltage / 1000);

  // Imprimir resultados
  Serial.print("Bus Voltaje:   "); Serial.print(busvoltage); Serial.println(" V");
  Serial.print("Shunt Voltaje: "); Serial.print(shuntvoltage); Serial.println(" mV");
  Serial.print("Load Voltaje:  "); Serial.print(loadvoltage); Serial.println(" V");
  Serial.print("Corriente:     "); Serial.print(current_mA); Serial.println(" mA");
  Serial.print("Potencia:      "); Serial.print(power_mW); Serial.println(" mW");
  Serial.println("");

  delay(2000);
}   