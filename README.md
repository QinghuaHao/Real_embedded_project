# Subway Door Anti-Trap Control System

## Description
The design of the subway door anti-trap control system in real-time embedded systems considered the hardware configuration, Raspberry Pi control, and effective integration of software algorithms.

In the hardware segment, the team selected high-sensitivity, rapid-response pressure sensors evenly distributed on both sides of the door to ensure complete coverage. Additionally, the human detection module covered the entire height of the door to form a continuous infrared barrier that can effectively detect objects of any size. As the control core, the team used a Raspberry Pi to connect all sensors and transmit data to the servo motor, ensuring precise control of the doors.

The control management software was developed using Raspberry Pi's GPIO library and the C++ programming language to process and respond to sensor signals. The software's decision logic was programmed based on sensor data. The system immediately executes exception processing, including pausing door closure and reopening, upon detecting abnormal pressure or objects.

After integrating all hardware and software components, the team conducted integration testing to verify the system's real-time responsiveness. The team optimized software parameters and algorithms through simulation tests and continuous adjustments of sensor sensitivity, servo moto rotation angles, and response thresholds, significantly enhancing the system's accuracy and reliability.


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
- **Robust Memory Management**: Utilizes destructor `~CPointSwitch` to ensures all dynamically allocated resources are properly released, preventing memory leaks. 

#### 2. Steering Engine Control Module

**Files**: `SteeringEngine.h`, `SteeringEngine.cpp`

The `CSteeringEngine` class within this module handles the control over the door's steering engine.

**Key Features**:

- **PWM Control**: Provides interfaces for adjusting and controlling the servo angles connected to GPIO ports, including servo initialization and position adjustment through PWM signals.
- **Encapsulation**: Includes members like `m_Frequency`, `m_Range`, `m_PinNumber`, and `m_InitStatus` for better data management.
- **Memory Leak Prevention**: Utilizes destructor `~CSteeringEngine` to ensures all dynamically allocated resources are properly released, preventing memory leaks. 

#### 3. Main Control Module

**File**: `main.cpp`

Serves as the application's entry point, initializing GPIOs, configuring point switches and steering engines, and processing server commands to manage the door's movements.

**Key Features**:

- **Initialization and Configuration**: Initializes GPIOs and configures both point switches and steering engines to their initial states for immediate readiness.
- **Socket Communication**: Receives and processes commands from TCP clients to control the door.
- **Resource Management**: Implements a signal handling function `signal_handler` for safe system resource management upon termination.
- **TCP Server Setup**: Facilitates network instruction reception for servo control.
- **Multi-Threading for Concurrent Processing**: Utilizes the POSIX thread library (`pthread`) to create a separate thread for message sending. Each thread handles sending messages from a buffer to connected clients over a network socket. This separation allows the main thread to concurrently accept new connections and perform additional tasks without blocking on network I/O operations.


#### 4. XML Parsing and Handling Module

**File**: `parseXmlApi.h`, `parseXmlApi.cpp`

Provides functionality for parsing and handling XML files, utilizing the TinyXML library.

**Key Features**:

- **XML Loading and Saving**: Utilizes functions like `load_xml` and `save_xml` to manage loading from XML files or string data and saving XML structures back to files, ensuring data persistence.
- **XML Manipulation**: Offers the `add_xml` function for merging XML structures, which aids in dynamically modifying XML configurations at runtime.
- **Data Retrieval**: Features functions such as `GetValue` and `GetChild` to facilitate easy access to attributes and child elements within an XML document, crucial for configuration and settings management.
- **Data Export**: Provides `GetData` and `GetXmlData` functions for extracting XML data into strings, enabling the transfer or storage of XML content in various formats or mediums.



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
Open config.xml, change IP and port

```
cd server
make
sudo ./server
```

After running the program, there will be a success message. Then the user can switch to release file and click the TCP.exe (The operating system must be Windows). Enter the IP address and Port ID, after connecting successfully, the connect button cannot be used anymore until clicking the close button. As the figure shows below, it can control the door open and close successfully.
![5811713142118_ pic](https://github.com/QinghuaHao/Real_embedded_project/assets/128492068/1717ee74-5db1-4d21-8367-db03433ded3d)
Notes: if the TCP.exe cannot work, it can be compiled by QT6. The source code of the client is placed in the TCP folder. Open the client and the project with QT, and compile it.
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

## Gantt Chart-Timeline 
![2581713136614_ pic](https://github.com/QinghuaHao/Real_embedded_project/assets/128492068/f448c8eb-148a-4a87-aff2-8be54fe60f67)

## Our Social Media and Demo


![1681713052606_ pic](https://github.com/QinghuaHao/Real_embedded_project/assets/128492068/2d0bd6a8-9dac-4fde-bb1c-8b47dc7fde26)

[![Demo](/images/Youtube.png)(https://youtu.be/kTEyXDGin4w)


## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

