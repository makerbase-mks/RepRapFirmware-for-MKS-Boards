# RepRapFirmware-for-MKS-Boards
This is a cloned version from https://github.com/gloomyandy/RepRapFirmware. And we want to make it support some MKS boards. 
So far, it has supported MKS Robin Nano V3 board, and please notice:
1. You should use MKS Robin Wifi at the same time, which uses spi connection with the Nano V3.
2. Using on MKS Robin Nano V3, you cannot display with the MKS TS35 so far, but only the 4.3/5.0/7.0 inch serial LCD like the Duet2Wifi board.
3. Just like gloomyandy reminded, this firmware is experimental and is likely to contain bugs - Use at your own risk.

# Using on MKS Robin Nano V3
## Update Mainboard bootloader
The original bootloader on Nano V3 does not support RRF, so the BootLoader needs to be updated first. This is only a one-time step. The updated BootLoader will support both Marlin firmware and RRF firmware.
Copy all the [booloader files](https://github.com/makerbase-mks/RepRapFirmware-for-MKS-Boards/tree/main/bootloader) to the TF card, insert the card into the motherboard, then power on and wait the update to be finished.

## Update mainboard RRF firmware
Copy all the [released files and folders](https://github.com/makerbase-mks/RepRapFirmware-for-MKS-Boards/tree/main/release%20firmware/rrf_v3.2) to the TF card, then power on until the “FAN1” light on the motherboard flashes, which means update RRF firmware complete.

## Wifi firmware update and wifi configuration
1. make sure that the wifi firmware "DuetWiFiServer.bin" is in the firmware folder of TF card. Use the Pronterface or other host on PC to connect to the motherboard, and then send the command:
 
``` M997 S1 ```

to update the wifi firmware. The firmware update process will display the update progress on the Pronterface.

3. Wifi name and wifi password settings, send the command :

``` M587 S "wifi name" P "wifi password" ```

Modify wifi name and wifi password according to your actual situation.

4. Wfi IP query, the host computer sends instructions:

``` M552 S1 ```

5. Web page control connection, enter the IP in the browser to login

6. Enter the login password, which is set in the configuration file: release firmware/rrf_v3.2/sys/config.g

For more usage and configuration, please refer to the [Using Manual](https://github.com/makerbase-mks/RepRapFirmware-for-MKS-Boards/blob/main/MKS%20Robin%20nano%20V3%20use%20RRF%20firmware%20manual.pdf).

