## Setup instructions

NOTE: This MUST be compiled with Arduino IDE v2, as the newer version of the STM32 MCU board libraries are not supported in Arduino IDE v1.x since STM board v2.8.x

### Prerequisites:

You'll need an [ST-Link v2](https://www.aliexpress.com/item/1005003575620794.html?spm=a2g0o.order_list.order_list_main.61.4fa01802JWw688) to flash the STM32.

You will also need to install the [STM32CubeIDE](https://www.st.com/en/development-tools/stm32cubeide.html) . The CLI version of this tool is used by the ST-Link to flash the STM32.

It requires a disposable email address in order to download the STM32CubeIDE. Download it, and run through the installer, the defaults are fine.

Add it to your path with either:
<pre>export STM32_PRG_PATH=~/.STM32Cube/STM32CubeProgrammer/bin
export PATH=~/.STM32Cube/STM32CubeProgrammer:$PATH</pre>

Or in Windows:
System Properties -> Advanced -> Environment Variables -> Under Sytem Variables select Path and choose Edit
Then add two new lines:
<pre>
C:\ST\STM32CubeIDE_1.18.0\STM32CubeIDE\plugins\com.st.stm32cube.ide.mcu.externaltools.cubeprogrammer.win32_2.2.100.202412061334\tools

C:\ST\STM32CubeIDE_1.18.0\STM32CubeIDE\plugins\com.st.stm32cube.ide.mcu.externaltools.cubeprogrammer.win32_2.2.100.202412061334\tools\bin
</pre>
![image](https://github.com/user-attachments/assets/a79c1623-8015-485b-ab69-3b8f9bc2ad2f)

## Arduino IDE setup

You'll need to install a few libraries and boards to get ready for installing the STM32 firmware

Board manager:
<pre>
https://github.com/stm32duino/BoardManagerFiles/raw/main/package_stmicroelectronics_index.json
https://raw.githubusercontent.com/stm32duino/Arduino_Core_STM32/refs/heads/main/package.json
https://static-cdn.m5stack.com/resource/arduino/package_m5stack_index.json
</pre>

Install the STM32 MCU based boards from Board Manager:

![image](https://github.com/user-attachments/assets/015923ab-6cc1-43ed-93c8-881c7364a0dc)

Install STM32duino FreeRTOS library:

![image](https://github.com/user-attachments/assets/b00f7875-fa54-4326-bcdf-e583048261f7)

## Installing the firmware to the STM32

Open the autobatchdoser.ino sketch

Then choose Tools -> Board -> Generic STM32F4 series

Then select Tools -> Board Part Number -> Generic F401VCTx

You'll need to power the STM32 by connecting the Grove cable to an M5Stack device such as a PoESP32 or Atom Lite. The STM32 is powered separately from the 5v on the Grove cable, and not from the 24v input for the pumps.

You should now be able to click "Upload":

![image](https://github.com/user-attachments/assets/3deb2927-0cb5-4116-94a1-d1e79448044b)

If you run into issues, double-check your PATH variable to ensure it knows where to find the STM32CubeIDE_CLI. You may need to add the EXPORT commands to your ~/.bashrc on linux.

The Upload Method should be "STM32CubeProgrammer (SWD)"

## ESPHome setup

Create your M5Stack PoESP32 or Atom Lite device.

Add the supplementary yaml from the supplied .txt file

The unit will provide the firmware version on boot. When the direction is "on" it operates in the forward direction. When it is "off" it operates in reverse. We use text-sensors as the method for establishing direction:

![image](https://github.com/user-attachments/assets/b5280282-fa53-4f75-9780-80af478b2000)

When you are happy with the pumps, you should modify the "motor_4_power" and remove the "on_turn_on" which is included by default to benchmark and ensure you are getting 600mL from 60s of power.
