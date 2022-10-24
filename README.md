# citiroc_tests
A bunch of programs to test communication with and data acquisition from the WEEROC CITIROC 1A board.

# Communicating with the board

Use the FTD2XX methods to find the CITIROC1A board's serial number and handle.
You may then use FTD2XX itself to communicate with the board via the handle, 
or the LALUsb library through the serial number. 

# Basics of the FTD2XX library
The following is based on the [FTD2XX documentation (pdf)](https://www.ftdichip.com/Support/Documents/ProgramGuides/D2XX_Programmer's_Guide(FT_000071).pdf). 
Please take your time to download and read it. 

### FT_STATUS values
In the context of this library, a DWORD is an unsigned integer (4 bytes). Each of the FTD2XX methods will return a DWORD called FT_STATUS. 
If the function worked as expected, then `FT_STATUS == FT_OK == 0`. 
These are a few of `FT_STATUS` values you can encounter:
```
FT_OK = 0
FT_INVALID_HANDLE = 1
FT_DEVICE_NOT_FOUND = 2
FT_DEVICE_NOT_OPENED = 3
FT_IO_ERROR = 4
...
FT_INVALID_PARAMETER = 6
FT_INVALID_BAUD_RATE = 7
FT_DEVICE_NOT_OPENED_FOR_ERASE = 8
FT_DEVICE_NOT_OPENED_FOR_WRITE = 9
...
FT_INVALID_ARGS = 16
FT_NOT_SUPPORTED = 17
FT_OTHER_ERROR = 18
```

### FT_CreateDeviceInfoList
Description: Creates and updates the list of FTD2XX devices.
Output: number of FTD2XX devices connected,

### FT_GetDeviceInfoDetail
Description: Gives you the info about a given device.
Input: index of a given FTD2XX device.
Output: flags, type, id, local id, serial number, description and handle.

### FT_OpenEx
Description: Attempts to open communication with a device.
Inputs: serial number, how-to-open-device flag.
Output: device handle.

### FT_SetLatencyTimer
Description: Sets the latency in ms.
Inputs: handle, latency in between 2-255 ms.

### FT_SetUSBParameters
Description: Sets USB transfer sizes.
Inputs: handle, transfer size of USB IN request, transfer size of USB out request.

### FT_SetTimeouts
Description: Set the timeout values.
Inputs: handle, read time out in ms, write timeout in ms.

### FT_Close
Description: Closes connection with a given device.
Input: handle.

# Copyright 
Codes and Makefile are somewhat based on the sample codes 
provided by FTDI and Weeroc.  
Please visit the [FTDI website](https://ftdichip.com/drivers/d2xx-drivers/) for details and documentation.
Please contact [Weeroc](https://www.weeroc.com/) for details about the CitirocUI software.