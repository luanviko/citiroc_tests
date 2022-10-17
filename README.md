# citiroc_tests
A bunch of programs to test communication with and data acquisition from the WEEROC CITIROC 1A board.

# Communicating with the board

Use the FTD2XX methods to find the CITIROC1A board's serial number and handle.
You may then use FTD2XX itself to communicate with the board via the handle, 
or you may use the LALUsb library to communicate through the serial number. 

## Basics of the FTD2XX library

The following is based on the [FTD2XX documentation (pdf)](https://www.ftdichip.com/Support/Documents/ProgramGuides/D2XX_Programmer's_Guide(FT_000071).pdf). 
Please take your time to download and read it. 
In the context of this library, a DWORD is an unsigned integer (4 bytes).
Each of the FTD2XX methods will return a DWORD called FT_STATUS. 


# Copyright 
The _Makefile_ and _ftd2xx.h_ files are not mine. They were copied from the examples shipped with the FTD2XX drivers. 
Please visit the [FTDI website](https://ftdichip.com/drivers/d2xx-drivers/) for details. 