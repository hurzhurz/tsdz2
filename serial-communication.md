# Serial communication
The communication between LCD and motor controller is a simple serial TTL-level connection with a baudrate of 9600.
For each direction (motor to LCD / LCD to motor), There is one data message/packet format, that is repeated multiple times per second.

## Motor to LCD
Example message:
```
43 00 01 51 51 00 07 07 F4
```
Send frequency: 8 per second
Content:

Byte No. | example | description
-------- | ------- | -----------
1 | 0x43 | Start-Byte
2 | 0x00 | Battery level
3 | 0x01 | Motor status flags
4 | 0x51 | Pedal torque-sensor "tara" value
5 | 0x51 | Pedal torque-sensor actual value
6 | 0x00 | Error code
7 | 0x07 | Speedsensor (LOW part of 16bit int)
8 | 0x07 | Speedsensor (HIGH part of 16bit int)
9 | 0xF4 | [Checksum](#Checksum)

## LCD to motor
Example message:
```
59 40 00 1C 00 1B D0
```
Send frequency: 15 per second

Content:

Byte No. | example | description
-------- | ------- | -----------
1 | 0x59 | Start-Byte
2 | 0x40 | Motor control flags
3 | 0x00 | unused
4 | 0x1C | Wheel size
5 | 0x00 | unknown, probably unused by LCD
6 | 0x1B | Maximum speed
7 | 0xD0 | [Checksum](#Checksum)


## Details
### Motor status flags

Bit | description
--- | -----------
\#0 | low voltage
\#1 | unknown
\#2 | motor running (if not in speed limit)
\#3 | PAS status / pedals spinning

### Motor control flags

Bit | description
--- | -----------
\#0 | headlight
\#1 | assist level 2
\#2 | assist level 3
\#3 | assist level 4
\#4 | assist off
\#5 | 6kph mode
\#6 | assist level 1

### Wheel size
Wheel size in inch, e.g. 0x1C in decimal are 28inch   
TODO: document limits accepted by firmware
### Maximum speed
Speed in kph, e.g. 0x1B in decimal is 27kph   
TODO: document limits accepted by firmware
### Pedal torque
#### first byte / "tara" value:
The torque sensor is read when motor is powered on.  
This value is used as reference to detect if force is applied to the pedals.  
Value can change a little bit after a stop.
#### second byte / current value:
This is the current value of the sensor.  
To get the applied force, you have to subtract the first byte / "tara" value.

The exact conversion factor has to be tested.   
The value increases by about 2.7 for every kg added load on a pedal at a pedal arm length of 17cm length.
That should be about 3.6 Nm per unit on the axis?

### Speed
The speed is basically a 16bit integer that contains the time between two trigger events of the speed sensor = one rotation.   
Each unit stands for about 2.04 ms time.   
Example calculation:
```
28 inch wheel = 2.24 m per rotation
Value: "89 01" = 0x0189 = 393 units
Time per ration: 393 units * 2.04 ms = 801.72 ms
Rotations per second: 1000 ms / 801.72 ms = 1.247 rotations/second
Speed: 1.247 rotations/second * 2.24 m per rotation = 2.79 m/s * 3.6 = 10kph
```
### Error code
code | description
---- | -----------
08 | undervoltage

more: https://opensourceebikefirmware.bitbucket.io/development_tsdz2/About_Tongsheng_TSDZ2_mid_drive_motors--LCD_-_VLCD5.html

### Checksum
The checksum is basically the sum of previous bytes as 8bit unsigned integer.   
See "1 byte checksum" described here: https://www.lammertbies.nl/comm/info/crc-calculation.html
