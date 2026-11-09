# TERA-UNRN
Taller Espacial de la Region Andina
# 🛰️ Proyecto CanSat - [TERA]

Repositorio oficial de software, diseño mecánico y documentación técnica para el proyecto CanSat del equipo.
(Participantes: Violeta Reser, Nicolas Rivera, Natanael Crespo, Katherina Soto, Tiziano Ulloa)			

---

## 📋 Descripción del Proyecto
Este proyecto consiste en el diseño, construcción y programación de un **CanSat** (un satélite del tamaño de una lata de refresco) desarrollado para cumplir con los requerimientos de la competencia de la CONAE. El sistema integra un microcontrolador ESP32, múltiples sensores ambientales e inerciales, cámaras de video y un sistema de telemetría de largo alcance mediante **LoRa**.

---

## ⚙️ Arquitectura del Hardware
El sistema está construido en torno a los siguientes componentes principales:
* **Microcontrolador:** ESP32 (Procesador principal y gestión de tareas).
* **Sensores Ambientales/Navegación:** BMP280 (Presión/Temperatura/Altitud), MPU-6050 (Acelerómetro/Giroscopio), GPS NEO-6M.
* **Telemetría:** Módulo LoRa SX1278 (915 MHz) para comunicación Punto a Punto con la Estación de Tierra.
* **Actuadores y Mecánica:** Mini servo (TowerPro SG90/MG90S) para el despliegue del sistema de recuperación y resortes de torsión para el despliegue del trípode.
* **Cámaras:** 2 módulos ESP32-CAM (Cenit y Nadir) para registro visual en alta definición.
* **Alimentación:** Baterías Li-Ion 18650 con regulación de voltaje (3.3V y 5V).

---

## 📁 Estructura del Repositorio
```text
cansat-project/
│
├── README.md                 # Documentación principal del repositorio
├── /firmware                 # Código fuente para el ESP32
│   ├── /main_flight_code     # Código principal de misión (Máquina de estados y telemetría)
│   └── /tests                # Códigos de prueba individuales (I2C scanner, sensores, LoRa)
│
├── /docs                     # Documentación técnica, matrices de componentes y manuales
│   └── Matriz_Componentes.pdf
│
├── /cad                      # Diseños 3D de la carcasa, bandejas internas y mecanismos
│   └── /stl                  # Archivos .STL listos para impresión 3D (PLA / PETG)
│
└── /ground_station           # Código y scripts de la estación de tierra para recepción LoRa
