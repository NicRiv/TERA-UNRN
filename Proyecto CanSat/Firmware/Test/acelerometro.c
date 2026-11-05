#include "I2Cdev.h"
#include "MPU6050_6Axis_MotionApps20.h"
#include "Wire.h"

const int MPU_ADDR = 0x68;
MPU6050 mpu;

#define INTERRUPT_PIN 2
bool dmpReady = false;
uint8_t mpuIntStatus;
uint16_t packetSize;
uint16_t fifoCount;
uint8_t fifoBuffer[64];

Quaternion q;
VectorInt16 aa;
VectorFloat gravity;
float ypr[3]; // [yaw, pitch, roll]

volatile bool mpuInterrupt = false;
void dmpDataReady() {
    mpuInterrupt = true;
}

void setup() {
  Wire.begin();
  Wire.setClock(400000);
  Serial.begin(9600);

  mpu.initialize();
  Serial.println(mpu.testConnection() ? "Conexión exitosa" : "Fallo de conexión");

  // Iniciar DMP
  uint8_t devStatus = mpu.dmpInitialize();
  
  // Calibración básica (valores de ejemplo, ajustar según necesidad)
  mpu.setXGyroOffset(220);
  mpu.setYGyroOffset(76);
  mpu.setZGyroOffset(-85);
  mpu.setZAccelOffset(1688);

  if (devStatus == 0) {
    mpu.setDMPEnabled(true);
    attachInterrupt(digitalPinToInterrupt(INTERRUPT_PIN), dmpDataReady, RISING);
    mpuIntStatus = mpu.getIntStatus();
    dmpReady = true;
    packetSize = mpu.dmpGetFIFOPacketSize();
    Serial.println("DMP listo");
  }
}

void loop() {
  if (!dmpReady) return;

  while (!mpuInterrupt && fifoCount < packetSize) {
    // Esperar interrupción
  }
  
  mpuInterrupt = false;
  mpuIntStatus = mpu.getIntStatus();
  fifoCount = mpu.getFIFOCount();

  if ((mpuIntStatus & 0x10) || fifoCount == 1024) {
    mpu.resetFIFO();
    Serial.println("Desbordamiento FIFO");
  } 
  else if (mpuIntStatus & 0x02) {
    while (fifoCount < packetSize) fifoCount = mpu.getFIFOCount();
    mpu.getFIFOBytes(fifoBuffer, packetSize);
    fifoCount -= packetSize;

    mpu.dmpGetQuaternion(&q, fifoBuffer);
    mpu.dmpGetGravity(&gravity, &q);
    mpu.dmpGetYawPitchRoll(ypr, &q, &gravity);

    Serial.print("Yaw: "); Serial.print(ypr[0] * 180/M_PI);
    Serial.print(" Pitch: "); Serial.print(ypr[1] * 180/M_PI);
    Serial.print(" Roll: "); Serial.println(ypr[2] * 180/M_PI);
  }
}   

"Consideraciones Importantes
Calibración: Es crucial calibrar los offsets del acelerómetro y giroscopio antes de usar los datos para control de vuelo o navegación precisa. 
Filtros: Si no se usa el DMP, se recomienda implementar un filtro complementario o Kalman para combinar los datos del acelerómetro (bueno para ángulos estáticos) y el giroscopio (bueno para movimientos rápidos).
Conexión: Asegúrese de conectar SDA al pin A4 y SCL al pin A5 en Arduino Uno, y verificar la dirección I2C (0x68 o 0x69) según el estado del pin AD0."