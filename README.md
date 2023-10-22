# Electra_IOT

Electra IOT is an sample implementation of a home automation system. Here you can find the Codes used for the microcontrollers used in the project.

# 1.Electra_Node_code.ino

## Overview

The `Electra_Node_code.ino` file contains the main code for a NodeMCU, which is used to control and monitor various components. The code is primarily written in C/C++. Here is a breakdown of the key functionalities:

## Included Libraries

The code utilizes several libraries for specific functionalities:

- `ESP8266WiFi.h`: Handles WiFi connectivity for the NodeMCU.
- `WiFiClient.h`: Manages WiFi client connections.
- `ESP8266HTTPClient.h`: Provides HTTP client functionality for making web requests.
- `DHT.h`: Library for interfacing with DHT11 temperature and humidity sensor.

## Pin Definitions

The code defines several constants representing pin configurations for different components connected to the NodeMCU, such as LEDs, ultrasonic sensor (HC-SR04), relay switches, MQ2 gas sensor, and a buzzer.

## WiFi Configuration

SSID and password for the WiFi network are specified, and the NodeMCU is configured to connect to the network.

## Setup Function

The `setup()` function performs the following tasks:

1. Initializes serial communication for debugging.
2. Configures WiFi mode and connects to the specified WiFi network.
3. Sets up pin modes for various components (LEDs, switches, sensors).
4. Initializes the DHT sensor.
5. Waits for the WiFi connection to be established, flashing an onboard LED as an indicator.

## Sensor Functions

- `DHT11sensor()`: Reads temperature from the DHT11 sensor.
- `GetDistance()`: Uses an ultrasonic sensor to measure distance.
- `gassensor()`: Reads values from the MQ2 gas sensor and controls a buzzer based on the gas level.

## Loop Function

The `loop()` function is the main execution loop that performs the following actions:

1. Periodically reads distance from the ultrasonic sensor, sends the data to a web server, and prints the result to the serial monitor.
2. Reads the status of relay switches from a web server and controls the corresponding switches accordingly.
3. Reads temperature from the DHT11 sensor, sends the data to a web server.
4. Reads gas levels from the MQ2 sensor, sends the data to a web server, and controls a buzzer based on the gas level.
5. Reads the status of lights and locks from a web server and controls the corresponding switches accordingly.

## Conclusion

The code essentially turns the NodeMCU into a smart device that monitors environmental conditions, interacts with relay switches based on web server commands, and reports sensor data to a remote server. It demonstrates the integration of various sensors and actuators in an IoT (Internet of Things) application.

# 2. Con_Web.ino

## Overview

The `Con_Web.ino` file, part of a series with different versions, represents a crucial component of the code responsible for communicating with a web server. The code utilizes the `HTTPClient` library to send requests and receive responses from a specified server. Here is an explanation of the key functionalities:

## Function: `String Con_Web(int id)`

This function is designed to communicate with a web server to retrieve data related to lights or lock status from a MySQL database. It takes an `id` parameter, which is used to identify the specific data to be retrieved.

### Steps:

1. **HTTPClient Initialization**: Creates an instance of the `HTTPClient` class named `http`.

2. **Server Connection Setup**:
   - Constructs the server address (`LinkGet`) by combining the `host` and a specific address (`ArduiT2/GetData2.php`).
   - Constructs the data to be sent in the request (`getData`) by appending the `id` parameter.
   - Prints debug information about the connection attempt.

3. **HTTP Request Setup**:
   - Specifies the request destination using `http.begin(LinkGet)`.
   - Adds a header specifying the content type.

4. **Sending Request and Receiving Response**:
   - Sends the HTTP POST request with the constructed data.
   - Retrieves the response payload from the server.

5. **Debug Printing**:
   - Prints the HTTP return code and the received payload for debugging purposes.

6. **Closing Connection (Unreachable Code)**:
   - Despite being present in the code, the statements after the `return` are unreachable. The function exits before reaching this part.

7. **Return**:
   - Returns the received payload as a `String`.

## Conclusion

The `Con_Web.ino` file, through the `Con_Web` function, encapsulates the logic for interacting with a web server to obtain information related to lights or lock status based on a provided `id`. It demonstrates the use of HTTP requests to communicate with a cloud server, showcasing an integral part of the overall IoT functionality. Note that the statements after the `return` statement are never executed, as the function exits before reaching that part.
