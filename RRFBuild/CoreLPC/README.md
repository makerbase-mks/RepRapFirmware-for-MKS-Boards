# CoreLPC for RepRapFirmware

This is an experimental port of DC42's [CoreNG](https://github.com/dc42/CoreNG) for LPC1768/LPC1769 based boards that is required build the [LPC Port of RepRapFirmware v3](https://github.com/sdavi/RepRapFirmware/tree/v3-dev-lpc) (forked from DC42s [RepRapFirmware](https://github.com/dc42/RepRapFirmware/)). This project also contains [FreeRTOS](https://www.freertos.org/) and [FreeRTOS+TCP](https://www.freertos.org/FreeRTOS-Plus/FreeRTOS_Plus_TCP/index.html) (with additions to work with RepRapFirmware and a ported 17xx networking driver based on the FreeRTOS+TCP 18xx driver).

**The LPC port is experimental and are likely to contain bugs - Use at your own risk - All configuration/settings etc should be checked in the source code to ensure they are correct**

## Compiling RepRapFirmware for LPC

Clone this repository, along with the following:
* [RRFLibraries](https://github.com/sdavi/RRFLibraries)
* [LPC port of RepRapFirmware v3 RTOS](https://github.com/sdavi/RepRapFirmware/tree/v3-dev-lpc)
* If building in ESP8266 WiFI support [DuetWiFiSocketServer](https://github.com/sdavi/DuetWiFiSocketServer)  

The ARM toolchain needs to be installed to build the firmware - the makefiles assumes it is available in the path environment variable. An example makefile has been included and should be edited to suit your settings, board selection, check all paths etc are correct before running make. If all is successful you should get a firmware.bin file in the same directory as the makefile.

Built upon open source projects including [Explore-M3](https://github.com/ExploreEmbedded/Explore-M3), [CoreNG](https://github.com/dc42/CoreNG), [MBED](https://github.com/ARMmbed/mbed-os), [Smoothieware](https://github.com/Smoothieware/Smoothieware), [FreeRTOS](https://www.freertos.org/), [FreeRTOS+TCP](https://www.freertos.org/FreeRTOS-Plus/FreeRTOS_Plus_TCP/index.html) and [LPCOpen](https://www.nxp.com/support/developer-resources/software-development-tools/lpc-developer-resources-/lpcopen-libraries-and-examples/lpcopen-software-development-platform-lpc17xx:LPCOPEN-SOFTWARE-FOR-LPC17XX)

License: GPLv3, see http://www.gnu.org/licenses/gpl-3.0.en.html. This project includes source code from the above 3rd party projects and are covered by their respective licenses.
