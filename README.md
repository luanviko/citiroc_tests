# citiroc_tests
A bunch of programs to test communication with and data acquisition from the WEEROC CITIROC 1A board.

# Communicating with the board

Use the FTD2XX methods to find the CITIROC1A board's serial number and handle.
You may then use FTD2XX itself to communicate with the board via the handle, 
or the LALUsb library through the serial number. 

## Basics of the FTD2XX library

The following is based on the [FTD2XX documentation (pdf)](https://www.ftdichip.com/Support/Documents/ProgramGuides/D2XX_Programmer's_Guide(FT_000071).pdf). 
Please take your time to download and read it. 
In the context of this library, a DWORD is an unsigned integer (4 bytes).
Each of the FTD2XX methods will return a DWORD called FT_STATUS. 
If the function worked as expected, then `FT_STATUS == FT_OK`, 
but there are other values that you must pay attention to:
```
FT_OK = 0
FT_INVALID_HANDLE = 1
FT_DEVICE_NOT_FOUND = 2
FT_DEVICE_NOT_OPENED = 3
FT_IO_ERROR = 4
FT_INSUFFICIENT_RESOURCES = 5
FT_INVALID_PARAMETER = 6
FT_INVALID_BAUD_RATE = 7
FT_DEVICE_NOT_OPENED_FOR_ERASE = 8
FT_DEVICE_NOT_OPENED_FOR_WRITE = 9
FT_FAILED_TO_WRITE_DEVICE = 10
FT_EEPROM_READ_FAILED = 11
FT_EEPROM_WRITE_FAILED = 12
FT_EEPROM_ERASE_FAILED = 13
FT_EEPROM_NOT_PRESENT = 14
FT_EEPROM_NOT_PROGRAMMED = 15
FT_INVALID_ARGS = 16
FT_NOT_SUPPORTED = 17
FT_OTHER_ERROR = 18
```


# Copyright 
The _Makefile_ and _ftd2xx.h_ files are not mine. They were copied from the examples shipped with the FTD2XX drivers. 
Please visit the [FTDI website](https://ftdichip.com/drivers/d2xx-drivers/) for details. 