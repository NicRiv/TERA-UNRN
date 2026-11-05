#include "Wire.h"
#include "I2Cdev.h"
#include "HMC5883L.h"

HMC5883L compass;
int16_t mx, my, mz;

// Declinación magnética en grados para tu ubicación (ejemplo: Valencia)
const float declinacion = 0.13; 

void setup() {
    Serial.begin(9600);
    Wire.begin();
    compass.initialize();
}

void loop() {
    // Obtener componentes del campo magnético
    compass.getHeading(&mx, &my, &mz);

    // Calcular el ángulo del eje X respecto al norte
    float angulo = atan2(my, mx);
    angulo = angulo * (180.0 / 3.14159); // Convertir a grados
    angulo = angulo - declinacion;        // Corregir declinación

    if (angulo < 0) angulo = angulo + 360; // Ajustar a 0-360

    Serial.print("N: ");
    Serial.println(angulo, 0);
    delay(100);
}   