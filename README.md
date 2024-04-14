# Subway Door Anti-Trap Control System

## Description
The real-time embedded system completes the design of the metro door anti-pinch control system taking into account the hardware configuration, Raspberry Pi control and the effective integration of software algorithms.

In the hardware part, the team selected high sensitivity and fast response pressure sensors evenly distributed on both sides of the door to ensure complete coverage. In addition, infrared sensors were applied to the human detection module, covering the entire height of the door to form a continuous infrared barrier for effective detection of objects regardless of their size. As the core part of the control, the team used a Raspberry Pi to connect all the sensors and transmit the data to servomoto to ensure precise control of the door. The team used the Raspberry Pi's GPIO library and the C++ programming language to develop the control management software to process and respond to the sensor signals.4 The software decision logic is programmed based on the sensor data, and as soon as an abnormal pressure or infrared interruption is detected the system performs an immediate exception, which can include pausing to close the door or reopening it.

After integrating all hardware and software components, the team performed integration testing to verify the system's real-time responsiveness. Through simulation testing and continuous adjustment of the sensor sensitivity, servo moto rotation angle and response thresholds, the team optimised the software parameters and algorithms to significantly improve the accuracy and reliability of the system.

![Equipment_Diagram_3D](/images/Equipment_Diagram_3D.png)


## Hardware Connection

![Hardware Connection](/images/Hardware_Connection.png) 

### Limit Switch:
The driving voltage is 3.3V, and the other port is connected to the Raspberry PI GPIO port. The switch status is obtained by monitoring the value of the GPIO port.

### Moving Human Detection:
The driving voltage is 5V, and one end is grounded. The signal cable in the middle is the detection module, connecting the Raspberry PI GPIO port.

### Servo Moto:
There are three terminals, one for the drive voltage 5V, one for the GND, and the last for the signal interface. The Raspberry PI receives the signals of the two detection devices, processes them, and sends them to Servo Moto through the signal line to adjust the angle of the door opening.

![Equipment Diagram](/images/Equipment_Diagram.png)

## Software Development

### Development Overview

This project is designed and implemented with strict adherence to development requirements, emphasizing the principles of software engineering, particularly the Single Responsibility Principle (SRP). The project is structured into three main functional modules:

- Switch Status Monitoring Module
- Steering Engine Control Module
- Main Control Module

Each module has been developed to fulfill a specific responsibility within the project, ensuring a clean, maintainable codebase.

### Components

#### 1. Switch Status Monitoring Module

**Files**: `PointSwitch.h`, `PointSwitch.cpp`

This module consists of the `CPointSwitch` class, which is responsible for managing interactions with the door's physical switches.

**Key Features**:

- **GPIO Interaction**: Manages electrical level signals related to the door's physical switches, including initialization of port modes and statuses.
- **Encapsulation**: Private data members like `m_PinNumber`, `m_PinMode`, and `m_PullAndDown` are securely accessed and modified via `getValue` and `setValue` methods.
- **Real-Time Event Handling**: Utilizes `gpioSetAlertFunc` for immediate response to GPIO port status changes.

#### 2. Steering Engine Control Module

**Files**: `SteeringEngine.h`, `SteeringEngine.cpp`

The `CSteeringEngine` class within this module handles the control over the door's steering engine.

**Key Features**:

- **PWM Control**: Provides interfaces for adjusting and controlling the servo angles connected to GPIO ports, including servo initialization and position adjustment through PWM signals.
- **Encapsulation**: Includes members like `m_Frequency`, `m_Range`, `m_PinNumber`, and `m_InitStatus` for better data management.

#### 3. Main Control Module

**File**: `main.cpp`

Serves as the application's entry point, initializing GPIOs, configuring point switches and steering engines, and processing server commands to manage the door's movements.

**Key Features**:

- **Initialization and Configuration**: Creates instances of `CPointSwitch` and `CSteeringEngine`, setting up their initial states.
- **Socket Communication**: Receives and processes commands from TCP clients to control the door.
- **Resource Management**: Implements a signal handling function `signal_handler` for safe system resource management upon termination.
- **TCP Server Setup**: Facilitates network instruction reception for servo control.


## Installation Guide

### Step 1: Download the Files via Git

```
git clone https://github.com/QinghuaHao/Real_embedded_project.git
```

In the repository, you'll find three key files: gpioTest, pwmTest, and server. 

### Step 2: gpioTest

gpioTest is used for testing the GPIO ports on the Raspberry Pi.
After compiling, you can run the gpioTest executable file:


```
cd /gpioTest
make
sudo ./gpioTest
```

### Step 3: pwmTest
This program tests the rotation of servos.

You can change the macro definitions to set the servo to rotate to 0 degrees or 180 degrees:

```
cd pwmTest
make
sudo ./pwmTest
```

### Step 4: server
This is the complete program for our project.

Change the macro definitions in the main file to the IP address of this Raspberry Pi, with the port set to 10000:

```
cd server
make
sudo ./server
```

After running the program, you will see a success message.

Then, connect to this program using a TCP client (e.g., TCPclient). Send '0' or '1' to control switches.


## Evaluation

### Basic Module Tests

| Test ID | Description      | Preconditions                              | Test Steps                                                               | Expected Result                       | Actual Result     | Tester   |
|---------|------------------|--------------------------------------------|--------------------------------------------------------------------------|---------------------------------------|-------------------|----------|
| TC01    | GPIO Test        | 1. System powered off<br />2. Servo connected to GPIO port             | 1. Power on<br />2. Compile the program<br />3. Run the program<br />4. Observe the printout | Printout: “pigpio initialisation ok” | As expected       | Qianyi Bu |
| TC02    | TCP Debugging    | 1. System powered off<br />2. Raspberry Pi connected to network        | 1. Power on<br />2. Adjust Raspberry Pi IP address<br />3. Compile the program<br />4. Run the program<br />5. Connect using tcp client | Printout: “new client connected”     | As expected       | Yikun Fan |
| TC03    | Micro Switch Test| 1. System powered off<br />2. Micro switch connected correctly         | 1. Power on<br />2. Compile the program<br />3. Run the program<br />4. Press the micro switch | Printout: GPIO port value is 1        | GPIO port value is 1 | Qianyi Bu |
| TC04    | Servo Test       | 1. System powered off<br />2. Servo module connected correctly         | 1. Power on<br />2. Set rotation angle to 0<br />3. Compile the program<br />4. Run the program<br />5. Observe the servo<br />6. Change rotation angle<br />7. Recompile and run<br />8. Observe the servo | Servo rotates                         | Servo rotates     | Yikun Fan |



### Human Detection Device Sensitivity Tests

| Test ID | Description           | Preconditions                                  | Test Steps                                                                | Expected Result              | Actual Result | Tester      |
|---------|-----------------------|------------------------------------------------|---------------------------------------------------------------------------|------------------------------|---------------|-------------|
| HM01    | Human Detection Module Test | 1. System powered off<br />2. Human detection module set up correctly | 1. Power on<br />2. Compile the program<br />3. Run the program<br />4. Block detection module at 15 cm | Printout: GPIO port number is 1 | Printed as 1  | Yuelian Zhang |
| HM02    | Human Detection Module Test | 1. System powered off<br />2. Human detection module set up correctly | 1. Power on<br />2. Compile the program<br />3. Run the program<br />4. Block detection module at 15 cm | Printout: GPIO port number is 1 | Printed as 0  | Yuelian Zhang |
| HM03    | Human Detection Module Test | 1. System powered off<br />2. Human detection module set up correctly | 1. Power on<br />2. Compile the program<br />3. Run the program<br />4. Block detection module at 10 cm | Printout: GPIO port number is 1 | Printed as 1  | Yuelian Zhang |


### System Integration Tests

| Test ID | Description       | Preconditions                    | Test Steps                                                                             | Expected Result              | Actual Result   | Tester      |
|---------|-------------------|----------------------------------|----------------------------------------------------------------------------------------|------------------------------|-----------------|-------------|
| TA01    | Door Frame Closure| 1. Power off the system<br />2. Hardware installation complete | 1. Power on<br />2. Set left and right servos to close door angles<br />3. Recompile<br />4. Run the program<br />5. Connect client<br />6. Send 0, 1 | Door closes without triggering the limit switch | Triggered limit switch | Yuelian Zhang |
| TA02    | Door Frame Closure| 1. Power off the system<br />2. Hardware installation complete | 1. Power on<br />2. Set left and right servos to close door angles<br />3. Recompile<br />4. Run the program<br />5. Connect client<br />6. Send 0, 1 | Door closes without triggering the limit switch | Triggered limit switch | Yikun Fan    |
| TA03    | Door Frame Closure| 1. Power off the system<br />2. Hardware installation complete | 1. Power on<br />2. Set left and right servos to close door angles<br />3. Recompile<br />4. Run the program<br />5. Connect client<br />6. Send 0, 1 | Door closes without triggering the limit switch | Triggered limit switch | Qianyi Bu    |
| TA04    | Door Frame Closure| 1. Power off the system<br />2. Hardware installation complete | 1. Power on<br />2. Set left and right servos to close door angles<br />3. Recompile<br />4. Run the program<br />5. Connect client<br />6. Send 0, 1 | Door closes without triggering the limit switch | Triggered limit switch | Yuelian Zhang |

## Outlook of Future Work

- Server functions can be enhanced to improve reliability and security. This could include implementing better error handling, hardening communication channels, or adding new features such as remote monitoring or control capabilities.

- The system can be prepared for deployment includes finalizing the hardware setup, optimizing the software for production, and testing it under real-world conditions similar to the intended use case.

- Internet of Things (IoT) capabilities can be added to enable the system to communicate with other devices or over the Internet.


## Team Introduction 

| Name          | Email                    |         Github                                    |
|-------------- |--------------------------|---------------------------------------------------|
| Qinghua Hao   |2645408h@student.gla.ac.uk|[QinghuaHao](https://github.com/QinghuaHao)        |
| Yuelian Zhang |2737199z@student.gla.ac.uk|[Yoli1219](https://github.com/Yoli1219)            |
| Yikun Fan     |2857239f@student.gla.ac.uk|[LuMingJun62511](https://github.com/LuMingJun62511)|
| Qianyi Bu     |2921072B@student.gla.ac.uk|[Buqianyi](https://github.com/Buqianyi)            |



## Our Social Media and Demo


![1681713052606_ pic](https://github.com/QinghuaHao/Real_embedded_project/assets/128492068/2d0bd6a8-9dac-4fde-bb1c-8b47dc7fde26)

[![Demo](/images/Youtube.png)(https://youtu.be/kTEyXDGin4w)


## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.
