# Arduino Temperature, Watch and Display

Build a watch with temperature sensor and never lost the time data when power off. Work with display scroll information.

## Components

- Temperature and Humidity Sensor: DHT11
- RTC Module: DS1307
- Arduino Uno
- LCD 16x2 with I2C interface

## Libraries

- Import _libraries_ from folder 

## Connections

Respect connections according with Arduino code. 

Temp/Hum Sensor DHT11
- Pin1 = Vcc
- Pin2 = Pin7 (Arduino) and 10K (resistor) > Vcc
- Pin4 = Gnd

RTC DS1307
- Vcc = Vcc
- Gnd = Gnd
- Scl = A3 (Arduino)
- Sda = A2 (Arduino)

I2C Display interface
- Vcc = Vcc
- Gnd = Gnd
- Scl = A5 (Arduino)
- Sda = A4 (Arduino)

Arduino Uno
- A2 = Sda RTC
- A3 = Scl RTC
- A4 = Sda I2C
- A5 = Scl I2C
- D7 = Sensor Pin2
- Gnd = Gnd External Power Supply
- Vin = +5v External Power Supply

Follow pictures from real project: 
