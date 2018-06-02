# Pinout
![TSDZ2 plugs](/images/tsdz2-plug.jpg)

## LCD connector
* Type (at motor): female (right in picture)

color | type | pullup resistor | voltage level | description
----- | ---- | --------------- | ------------- | -----------
black | - |  |  | GROUND (-) / battery -
brown | OUTPUT | ≈5k | 5V | serial TX
green | OUTPUT |  | e.g. 36V | V_BATT / battery +
orange | INPUT | ≈5.5k | 5V | serial RX
purple | INPUT | ≈9.5k | 5V | brake switch input / motor cutoff / low active
white | INPUT |  | ≈V_BATT | controller enable / high active

* Throttle version:
The throttle version of the motor has a 8-pin connector instead of a 6-pin connector.   
The additional pins are probably:
  * 5V supply voltage for the hall sensor (SS49E?)
  * Analog INPUT

## Speedsensor connector
 * Type (at motor): male (left in picture)

color | type | pullup resistor | voltage level | description
----- | ---- | --------------- | ------------- | -----------
black | IN/OUT | ≈48k | 5V | SWIM (programming interface)
brown | IN/OUT |  | 5V | V_MCU (e.g. supply for programming)
green | OUTPUT |  | ≈6V | V_HEADLIGHT
orange | - |  |  | GROUND
purple | INPUT | ≈10.5k | 5V | RST (programming interface)
white | INPUT | ≈8k | 5V | speed sensor / low active
