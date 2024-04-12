# Metro Door Anti-pinch Control System

## Description
The real-time embedded system completes the design of the metro door anti-pinch control system taking into account the hardware configuration, Raspberry Pi control and the effective integration of software algorithms.

In the hardware part, the team selected high sensitivity and fast response pressure sensors evenly distributed on both sides of the door to ensure complete coverage. In addition, infrared sensors were applied to the human detection module, covering the entire height of the door to form a continuous infrared barrier for effective detection of objects regardless of their size. As the core part of the control, the team used a Raspberry Pi to connect all the sensors and transmit the data to servomoto to ensure precise control of the door. The team used the Raspberry Pi's GPIO library and the C++ programming language to develop the control management software to process and respond to the sensor signals.4 The software decision logic is programmed based on the sensor data, and as soon as an abnormal pressure or infrared interruption is detected the system performs an immediate exception, which can include pausing to close the door or reopening it.

After integrating all hardware and software components, the team performed integration testing to verify the system's real-time responsiveness. Through simulation testing and continuous adjustment of the sensor sensitivity, servo moto rotation angle and response thresholds, the team optimised the software parameters and algorithms to significantly improve the accuracy and reliability of the system.

## Hardware Connection
### Limit Switch:
The driving voltage is 3.3V, and the other port is connected to the Raspberry PI GPIO port. The switch status is obtained by monitoring the value of the GPIO port.

### Moving Human Detection:
The driving voltage is 5V, and one end is grounded. The signal cable in the middle is the detection module, connecting the Raspberry PI GPIO port.

### Servo Moto:
There are three terminals, one for the drive voltage 5V, one for the GND, and the last for the signal interface. The Raspberry PI receives the signals of the two detection devices, processes them, and sends them to Servo Moto through the signal line to adjust the angle of the door opening.

## Software Introduction
### The Application of SOLID Principle:

#### The Best Choice of Class:
Our system implements two main classes: CPointSwitch for handling point switching logic, and CSteeringEngine for managing the steering engine (gate mechanism). These classes follow the principle of single responsibility and the open-close principle, allowing extensions without modifying the existing code base.


### Encapsulation and data management:

#### Data encapsulation in class:
All members of the CPointSwitch and CSteeringEngine are private, ensuring encapsulation. Accessors (getters) and modifiers (setters) are provided to manipulate these members safely.

#### Secure Use of Getters, Setters, Callbacks, and Data Management:
Class provides a secure interface to the client, with exposed methods for securely setting and obtaining pin values. Error checking is simple but present, ensuring that unexpected values do not disrupt GPIO operation.

### Memory Management:

#### Memory Management:
The code does not use dynamic memory allocation and relies on stack and static allocation, minimizing the risk of memory leaks. The pigpio library is used to manage low-level hardware interactions, which abstracts the details of memory management from the user.


### Real-time Coding and Event Processing:

#### Real-time Codeing:
We used the capabilities of the pigpio library to handle GPIO interrupts and signal callbacks, allowing our system to react to real-time events with little to no significant delay.

#### Real-time Event Processing:
gpioSetAlertFunc is used to set callback functions for specific GPIO pins, allowing our system to handle events in real time, such as the opening and closing of door switches.


### Project Structure:

The project consists of multiple components working together to ensure efficient and reliable operation.

#### main.cpp:
It is the entry point to the application. It initializes the GPIO, sets the point switch and steering engine, and listens for server commands to control the door.

#### PointSwitch.h & PointSwitch.cpp:
These files define the CPointSwitch class and its methods for interacting with the door switch.

#### SteeringEngine.h & SteeringEngine.cpp:
These files define the CSteeringEngine class responsible for controlling the steering engine of the gate.

#### gpioTest.cpp, pwmTest.cpp & pmwTest.cpp:
These test files demonstrate the ability to control GPIO and PWM through the pigpio library.



