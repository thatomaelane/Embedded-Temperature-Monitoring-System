# Embedded Temperature Monitoring System

> An AVR-based embedded temperature monitoring system that uses an LM35 temperature sensor, ADC-based temperature measurement, and dual 7-segment displays to display the measured temperature in real time. The project was implemented in C, simulated in Proteus, and physically assembled and soldered on a veroboard.

![C](https://img.shields.io/badge/C-Embedded%20C-blue)
![AVR](https://img.shields.io/badge/Microcontroller-AVR-red)
![ADC](https://img.shields.io/badge/ADC-10--bit-green)
![Sensor](https://img.shields.io/badge/Sensor-LM35-orange)
![Proteus](https://img.shields.io/badge/Simulation-Proteus-purple)
![Hardware](https://img.shields.io/badge/Hardware-Veroboard-yellow)
![Status](https://img.shields.io/badge/Status-Completed-brightgreen)

---

## Project Overview

This project is an **embedded temperature monitoring system** developed using an AVR microcontroller and an LM35 temperature sensor.

The system measures temperature using the microcontroller's built-in **Analog-to-Digital Converter (ADC)** and displays the measured temperature on two 7-segment displays.

The project was developed through three stages:

1. **Embedded C firmware development**
2. **Proteus circuit simulation**
3. **Physical hardware implementation on a veroboard**

The project demonstrates the integration of:

- Analog sensors
- ADC
- Embedded C programming
- Microcontroller I/O
- 7-segment displays
- Digital hardware
- Circuit simulation
- Hardware construction and soldering

---

## Project Objectives

The main objectives of the project were to:

- Measure temperature using an LM35 temperature sensor.
- Convert the sensor's analog output into a digital value using the AVR ADC.
- Convert the ADC measurement into temperature in degrees Celsius.
- Display the temperature using two 7-segment displays.
- Develop the embedded firmware in C.
- Simulate the circuit using Proteus.
- Build the circuit physically on a veroboard.
- Test the complete embedded system using real hardware.

---

## System Architecture

The system follows the following signal flow:

```
        Temperature
             ↓
        ┌─────────┐
        │  LM35   │
        │ Sensor  │
        └────┬────┘
             │
       Analog Voltage
             │
             ↓
        ┌─────────┐
        │   ADC   │
        │ AVR MCU │
        └────┬────┘
             │
        Digital Value
             │
             ↓
        ┌──────────────┐
        │ Temperature  │
        │ Calculation  │
        └──────┬───────┘
               │
               ↓
        ┌──────────────┐
        │  7-Segment   │
        │   Display    │
        └──────────────┘
               │
               ↓
      Temperature Display
```

---

## Hardware Components

The project uses the following main components:

- AVR microcontroller
- LM35 temperature sensor
- Two 7-segment displays
- Resistors
- Breadboard/veroboard during construction
- Jumper wires
- Power supply
- Solder
- Electronic components and connecting wires

---

## Main Components

### LM35 Temperature Sensor

The LM35 is used to measure temperature.

The sensor produces an analog voltage proportional to temperature.

The project uses the relationship:

```
10 mV / °C
```

Therefore:

```
Temperature (°C) ≈ Sensor Voltage / 10 mV
```

The analog sensor output is connected to the AVR's ADC input.

### Analog-to-Digital Conversion

The microcontroller reads the LM35 output using its internal ADC. The ADC converts the analog sensor voltage into a digital value.

The firmware uses the ADC measurement to calculate temperature:

```
Temperature = (ADC Value × 500) / 1023
```

The calculated temperature is then separated into two digits:

```
Tens Digit = Temperature / 10
Ones Digit = Temperature % 10
```

These digits are sent to the corresponding 7-segment displays.

### 7-Segment Display

The project uses two 7-segment displays to represent the temperature.

For example, for Temperature = 25°C, the displays show:

```
┌─────┐ ┌─────┐
│  2  │ │  5  │
└─────┘ └─────┘

     25°C
```

The firmware contains segment codes for the digits 0–9.

```c
unsigned char TENS[] =
{
    0x40,
    0x79,
    0x24,
    0x30,
    0x19,
    0x12,
    0x02,
    0x78,
    0x00,
    0x10
};

unsigned char ONES[] =
{
    0x40,
    0x79,
    0x24,
    0x30,
    0x19,
    0x12,
    0x02,
    0x78,
    0x00,
    0x10
};
```

The segment patterns correspond to the digits displayed by the common-anode 7-segment configuration.

---

## Microcontroller Configuration

The firmware configures the microcontroller ports for the sensor and display interfaces.

```c
DDRB |= 0x07;
DDRC |= 0x0F;
DDRD |= 0xFF;
```

The configuration uses:

- **PORTB** → Tens digit high-nibble output
- **PORTC** → Tens digit low-nibble output
- **PORTD** → Ones digit output

### ADC Configuration

The ADC is enabled using:

```c
ADCSRA = 0x87;
```

The ADC reference and input channel are configured using:

```c
ADMUX = 0x44;
```

The ADC conversion is then started using:

```c
ADCSRA |= (1 << ADSC);
```

The program waits for the conversion to complete before reading the ADC value.

```c
while (ADCSRA & (1 << ADSC));
```

---

## Temperature Calculation

The ADC value is stored in:

```c
unsigned int adc_value = ADC;
```

The temperature is calculated using:

```c
unsigned char temperature =
    (adc_value * 500) / 1023;
```

The temperature is then divided into two digits:

```c
ones = temperature % 10;
tens = temperature / 10;
```

The resulting digits are sent to the displays.

---

## Firmware Workflow

```
Start
  ↓
Configure I/O Ports
  ↓
Configure ADC
  ↓
Start ADC Conversion
  ↓
Wait for Conversion
  ↓
Read ADC Value
  ↓
Convert ADC Value to Temperature
  ↓
Separate Temperature into Tens and Ones
  ↓
Send Segment Codes to Displays
  ↓
Wait
  ↓
Repeat
```

---

## Embedded C Code

The main firmware is contained in:

`src/Practicum1.c`

The program performs the following operations:

```
ADC Reading
      ↓
Temperature Calculation
      ↓
Digit Separation
      ↓
7-Segment Encoding
      ↓
Display Output
```

---

## Simulation

The circuit was simulated using **Proteus** before the physical implementation.

The Proteus simulation was used to verify:

- Microcontroller connections
- LM35 sensor operation
- ADC measurement
- 7-segment display operation
- Temperature calculation
- Port configuration
- Firmware behaviour

The Proteus project files are included in the repository.

---

## Physical Hardware Implementation

After completing the simulation, the circuit was physically assembled on a veroboard.

The physical implementation involved:

- Component placement
- Circuit wiring
- Soldering
- Continuity checking
- Microcontroller programming
- Sensor testing
- Display testing
- Temperature measurement

The repository includes photographs and video of the completed physical circuit.

### Hardware Development Process

```
Circuit Design
      ↓
Proteus Simulation
      ↓
Firmware Development
      ↓
Simulation Testing
      ↓
Component Preparation
      ↓
Veroboard Assembly
      ↓
Soldering
      ↓
Hardware Testing
      ↓
Temperature Measurement
```

---

## Repository Structure

```
Embedded-Temperature-Sensor/
│
├── README.md
│
├── src/
│   └── Practicum1.c
│
├── proteus/
│   └── Temperature_Sensor.pdsprj
│
├── images/
│   ├── circuit.jpg
│   ├── veroboard_front.jpg
│   ├── veroboard_back.jpg
│   ├── proteus_simulation.png
│   └── temperature_display.jpg
│
├── video/
│   └── hardware_demo.mp4
│
└── docs/
    └── project_report.pdf
```

---

## Technologies Used

**Programming**
- C
- Embedded C

**Microcontroller**
- AVR

**Sensors**
- LM35 Temperature Sensor

**Display**
- 7-Segment Display

**Simulation**
- Proteus Design Suite

**Hardware**
- Veroboard
- Soldering
- Electronic components

---

## Embedded Systems Concepts Demonstrated

This project demonstrates practical understanding of:

- Microcontroller programming
- Embedded C
- Digital I/O
- Analog input
- ADC configuration
- Sensor interfacing
- Temperature measurement
- 7-segment display interfacing
- Bit manipulation
- Register configuration
- Timing and delays
- Embedded debugging
- Circuit simulation
- Hardware prototyping
- PCB/veroboard construction
- Soldering
- Hardware testing

---

## Key Code Concepts

### Port Configuration

```c
DDRB |= 0x07;
DDRC |= 0x0F;
DDRD |= 0xFF;
```

Configures the required microcontroller pins as outputs.

### ADC Conversion

```c
ADCSRA |= (1 << ADSC);

while (ADCSRA & (1 << ADSC));
```

Starts an ADC conversion and waits until the conversion is completed.

### ADC Reading

```c
unsigned int adc_value = ADC;
```

Reads the converted ADC value.

### Temperature Conversion

```c
unsigned char temperature =
    (adc_value * 500) / 1023;
```

Converts the ADC reading into the corresponding temperature value used by the display logic.

### Digit Extraction

```c
ones = temperature % 10;
tens = temperature / 10;
```

Separates the temperature into individual digits.

### Display Output

```c
PORTD = ONES[ones];

PORTB = (TENS[tens] & 0xF0) >> 4;

PORTC = (TENS[tens] & 0x0F);
```

Sends the appropriate segment patterns to the display hardware.

---

## Skills Demonstrated

- Embedded Systems
- Embedded C Programming
- AVR Microcontrollers
- Sensor Interfacing
- ADC
- Digital Electronics
- Analog Electronics
- Microcontroller I/O
- Hardware Debugging
- Circuit Simulation
- Proteus
- Veroboard Construction
- Soldering
- Electronic Hardware Testing
- Firmware Development
- Hardware-Software Integration
- Problem Solving

---

## Project Learning Outcomes

Through this project, I gained practical experience in moving from a software implementation to a physical embedded system.

The project involved the complete development cycle:

```
Software
   +
Simulation
   +
Hardware
   +
Testing
```

This helped strengthen my understanding of how embedded software interacts with physical electronic components.

---

## Future Improvements

Potential improvements to the project include:

- Add a third display digit for decimal temperature values.
- Display negative temperatures.
- Add temperature threshold alarms.
- Add an LED warning indicator.
- Add a buzzer for high-temperature alerts.
- Improve ADC calibration.
- Add digital filtering to reduce sensor noise.
- Add data logging.
- Add an LCD or OLED display.
- Add UART communication.
- Add Bluetooth or Wi-Fi connectivity.
- Send temperature measurements to a cloud dashboard.
- Implement real-time temperature monitoring.
- Add battery-powered operation.
- Design a dedicated PCB version of the circuit.

---

## Project Demonstration

### Proteus Simulation

The Proteus simulation demonstrates the complete circuit operation before physical construction.

Place the simulation screenshots in:

`images/proteus_simulation.png`

### Physical Hardware

The completed circuit was assembled and soldered onto a veroboard.

Hardware photographs are available in:

`images/`

### Hardware Demonstration Video

A video demonstrating the completed physical temperature sensor can be placed in:

`video/hardware_demo.mp4`

The demonstration shows the physical circuit operating and displaying the measured temperature.

---

## Project Status

| Task | Status |
|---|---|
| Hardware Design | ✓ Completed |
| Embedded C Firmware | ✓ Completed |
| Proteus Simulation | ✓ Completed |
| Veroboard Assembly | ✓ Completed |
| Soldering | ✓ Completed |
| Hardware Testing | ✓ Completed |
| Documentation | ✓ Completed |

---

## Author

**Thato Maelane**

Electrical Engineering
Tshwane University of Technology
South Africa

---

## Academic Project

This project was developed as part of my Electrical Engineering / Embedded Systems practical work and represents hands-on experience combining embedded software, electronics, simulation and physical hardware development.

---

⭐ If you find this research useful, consider giving the repository a star.
