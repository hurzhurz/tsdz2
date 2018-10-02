# Programming interface
* **DISCONNECT BATTERY WHILE PROGRAMMING**
* The speed sensor input plug has the SWIM programming interface of the STM8 microcontroller exposed
* See [pinout](pinout.md)
* As a programmer, you can use a ST-Link V2 (or a clone)

* Connect the programmer to speed sensor plug:   
![ST-Link Connection](/images/stlink-connection.jpg)
  * SWIM to black
  * VCC/5V to brown
  * GND to orange
  * optional: SWIM_RST to purple
  * <ins>use a short cable, preferably not longer than about 20cm</ins>

* Software
 * Get STVP (ST Visual Programmer STM32) from here:   
 http://www.st.com/en/development-tools/stvp-stm32.html
 * Setup Programmer and device (STM8S105x4) like here:
 ![STVP device selection](/images/stvp_device.PNG)  
 **Note:** For flashing the [Flexible OpenSource firmware](https://github.com/OpenSource-EBike-firmware/TSDZ2_wiki/wiki), you need to select STM8S105x6 as device because of the firmware size ([incorrect type, but works](https://endless-sphere.com/forums/viewtopic.php?f=30&t=93818&start=50#p1374884)) 
 * You can then be able to read/write:
   * PROGRAM MEMORY (=Flash)
   * DATA MEMORY (=EEPROM)
   * OPTION BYTE
 * Before programming/writing anything else, I would recommend to:
   * Read all three multiple times
   * Compare if all reads are identical
   * Save at least one copy at a save place in case you have to restore anything
