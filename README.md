# IoT-Task1
IoT Task 1 — Arduino and Tinkercad Project
# IoT Task 1: Arduino-Based Automatic Object Length Sorter

 1. Project Overview

This project implements an *automatic object length sorting system* using an Arduino UNO, an HC-SR04 ultrasonic sensor, a servo motor, and an L293D motor driver.

The system detects objects moving along a conveyor belt, estimates their lengths based on the time they remain in front of the ultrasonic sensor, and classifies them into three categories: **Short, Medium, and Long**.

A servo motor acts as a diverter, while LEDs indicate the detected category. The Arduino also maintains the count of objects classified in each category and displays the measurements and counts through the Serial Monitor.

 2. Components Used

* Arduino UNO
* HC-SR04 ultrasonic distance sensor
* Servo motor
* L293D motor driver IC
* DC motor for the conveyor belt
* Three indicator LEDs
* Current-limiting resistors for LEDs
* Breadboard and jumper wires
* Power supply for the motor
* Tinkercad Circuits for simulation

 3. Circuit Connections

The following table describes the pin assignments used in the Arduino source code.

| Component         | Component Pin           | Arduino Connection  |
| ----------------- | ----------------------- | ------------------- |
| HC-SR04           | TRIG                    | Digital pin 10      |
| HC-SR04           | ECHO                    | Digital pin 11      |
| Servo motor       | Signal                  | Digital pin 9       |
| L293D             | Enable 1,2              | Digital pin 5 (PWM) |
| L293D             | Input 1                 | Digital pin 7       |
| L293D             | Input 2                 | Digital pin 8       |
| Short-object LED  | Anode, through resistor | Digital pin 2       |
| Medium-object LED | Anode, through resistor | Digital pin 3       |
| Long-object LED   | Anode, through resistor | Digital pin 4       |

Ensure the Arduino, motor driver, and external motor supply share a common ground. The motor supply must be appropriate for the motor and driver.

 4. Working Principle

Step 1: Object Detection

The HC-SR04 ultrasonic sensor measures the distance between itself and an object using ultrasonic pulses.

The Arduino calculates the distance from the time taken by the sound wave to travel to the object and return. An object is considered detected when its measured distance is greater than zero and less than 100 cm.

Step 2: Conveyor Belt Operation

The DC motor drives the conveyor belt through the L293D motor driver. The Arduino sets the motor direction using digital pins 7 and 8 and controls its speed through PWM on pin 5.

The PWM value is set to 150 out of 255.

Step 3: Object Length Estimation

When an object is detected, the Arduino records the start time and measures how long the object remains in front of the sensor.

The measurement ends after three consecutive readings fail to detect the object.

The estimated object length is calculated using:

*Object Length = Belt Speed × Detection Time*

The code assumes a belt speed of 10 cm/s. This value should be measured and calibrated for a real conveyor belt.

Step 4: Object Classification

The estimated length determines the object's category.

| Estimated Length         | Category | LED        | Servo Angle |
| ------------------------ | -------- | ---------- | ----------- |
| Less than 10 cm          | Short    | Short LED  | 30°         |
| 10 cm to less than 20 cm | Medium   | Medium LED | 90°         |
| 20 cm or greater         | Long     | Long LED   | 150°        |

Measurements below 1 cm are ignored as potential noise.

Step 5: Sorting and Indication

After classification, the Arduino:

* Moves the servo to the angle associated with the category.
* Turns on the corresponding LED.
* Prints the estimated length and category counts to the Serial Monitor.
* Waits 1.5 seconds to allow the object to reach the sorting area.
* Turns off the LED and returns the servo to its neutral position of 90°.

Step 6: Object Counting

Three variables maintain separate counts for short, medium, and long objects.

After each successful classification, the Serial Monitor displays the estimated length, category counts, and total number of classified objects.

 5. Tinkercad Simulation

**Simulation Link:** https://www.tinkercad.com/things/ezNftw1GyYq-prodextask01lengthsorter?sharecode=TN97cTCUhKgmDwHbXN8zgATLawwrTi_xo3DAEJjmtOY

6. Further Applications

This project demonstrates the basic principles of sensor-based automation and object classification. Its approach can be extended to several practical applications:

Industrial sorting systems: Automated classification of products according to their dimensions on conveyor belts.

Packaging and manufacturing: Sorting objects into different groups before packaging or further processing.

Smart material handling:Integrating sensors and actuators to automate the movement and routing of objects.

Educational robotics:Demonstrating ultrasonic sensing, PWM motor control, servo actuation, and embedded programming.

Automated inspection systems:Extending the design with additional sensors to classify objects using multiple properties.




