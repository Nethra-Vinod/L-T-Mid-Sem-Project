# L-T-Mid-Sem-Project
# ESP32 Smart Lawn Mower

A prototype autonomous grass-cutting robot powered by an **ESP32 microcontroller**. This project demonstrates obstacle detection, motor control, and servo-actuated steering for mowing small patches of grass.

---

## 🚀 Features

* **Autonomous Navigation** using an ultrasonic sensor (HC-SR04)
* **Grass Cutting Mechanism** with a dedicated DC motor driving a blade
* **Dual DC Motors** for wheel drive, controlled via an L298N H-Bridge
* **Servo Motor** for sensor rotation (to scan left/right)
* **ESP32 Microcontroller** for remote monitoring/control

---

## 🛠️ Components Used

* **ESP32 DevKit V1** (main controller)
* **L298N H-Bridge Motor Driver** (controls two drive DC motors)
* **2 × DC Motors with Wheels** (drive motors)
* **1 × DC Motor with Blade** (grass cutting motor)
* **HC-SR04 Ultrasonic Sensor** (for obstacle detection)
* **SG90 Servo Motor** (to rotate ultrasonic sensor for wider coverage)
* **Voltage Regulator Module** (to step down battery voltage to 5V)
* **Battery Pack** (primary power supply)

---

## ⚙️ Working Principle

1. The **ESP32** controls the mower’s movement using the **L298N H-Bridge** to drive the two DC wheel motors.
2. The **ultrasonic sensor**, mounted on a servo, continuously scans for obstacles.
3. If an obstacle is detected, the ESP32 makes the mower stop, turn, and continue in a new direction.
4. A **separate DC motor spins the cutting blade**, enabling grass cutting while the mower moves.
5. Power is distributed through a **regulatorr**, ensuring stable 5V for the ESP32, servo, and sensors.
6. Future improvements can integrate **IoT features** for remote monitoring and scheduling.

---

## 📦 Future Improvements

* Add GPS navigation for precise mowing patterns
* Solar panel integration for extended operation
* Mobile app or web dashboard for remote control
* Automatic charging dock system

---

## ⚡ Wiring Diagram

See the schematic (included in this repo) for all pin connections and power management details.

---

## 👥 Contributors

- Nethra Vinod 
- S.Mayuri Darshini
- MadhavAmrith
- TejasKumar
- Thilak

## 📝 License

This project is open-source and available under the MIT License.
