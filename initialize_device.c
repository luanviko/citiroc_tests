#include <stdio.h>
#include <stdlib.h>
#include "ftd2xx.h"
#include "LALUsb.h"

// Following examples/Simple
// provided by FTD2XX driver
// and Citiroc UI 

// Function declarators
FT_STATUS makeList(int* numberOfDevices);
int printDevicesInfo(FT_DEVICE_LIST_INFO_NODE* deviceList, unsigned int* numberOfDevices);
void findBoard(DWORD* numberOfDevices, char* serialNumber, FT_HANDLE* deviceHandle);
void connectBoard(char* serialNumber, FT_HANDLE* deviceHandle);
void initializeBoard(FT_HANDLE* deviceHandle, char* serialNumber);
void disconnectBoard(FT_HANDLE* deviceHandle, char* serialNumber);
void errorHandler(char* function_name, DWORD* status, FT_HANDLE* deviceHandle, char* serialNumber);

// Main function
int main() {

    // FTD2XX variables
    FT_HANDLE deviceHandle;
    DWORD numberOfDevices;
    char serialNumber[16];

    // Basic communication
    findBoard(&numberOfDevices, &serialNumber, &deviceHandle);
    connectBoard(&serialNumber, &deviceHandle);
    initializeBoard(&deviceHandle, &serialNumber);
    disconnectBoard(&deviceHandle, &serialNumber);
    return 0;

}

void findBoard(DWORD* numberOfDevices, char* serialNumber, FT_HANDLE* deviceHandle) {

    // Private variables
    FT_HANDLE temporaryHandle;
    FT_STATUS status;
    FT_DEVICE_LIST_INFO_NODE* deviceList;
    DWORD flags;
    DWORD id;
    DWORD type;
    DWORD localID;

    // Find number of devices
    status = FT_CreateDeviceInfoList(&numberOfDevices);
    
    // Allocate memory for device info    
    deviceList = calloc((size_t)numberOfDevices, sizeof(FT_DEVICE_LIST_INFO_NODE));
    if (deviceList == NULL) {
        printf("calloc error: Unable to allocate memory for device info.\n");
    }

    // Fetch information about devices
    status = FT_GetDeviceInfoList(deviceList, numberOfDevices);    

    // Catch the exception
    if (status != FT_OK) {
        printf("FT_GetDeviceInfoList code not zero. FT_STATUS = %d.\n", (int) status);
        exit(1);
    }

    // Keep details for device 0.
    status = FT_GetDeviceInfoDetail(0, &flags, &type, &id, &localID, serialNumber, NULL, &temporaryHandle); 
    
    if (status != FT_OK) {
        printf("FT_GetDeviceInfoDetail error: No compatible devices found.\n");
        exit(2);
    }

}

void connectBoard(char* serialNumber, FT_HANDLE* deviceHandle) {

    // Private variables
    FT_STATUS status;

    // Attempt connection with board.
    printf("Trying to connect with device of serial number %s...\n", serialNumber);
    status = FT_OpenEx(&serialNumber, FT_OPEN_BY_SERIAL_NUMBER, &deviceHandle);
    if (status != FT_OK) {
        printf("FT_OpenEx status: %ld. Unable to open device by serial number.\n");
        exit(3);
    }

    printf("Connection established. Handle: %x.\n", deviceHandle);
}

void initializeBoard(FT_HANDLE* deviceHandle, char* serialNumber) {

    // Private variables
    FT_STATUS status;

    // Set latency timer. Latency in between 2 to 255 ms.
    status = FT_SetLatencyTimer(deviceHandle, 2);
    errorHandler("FT_SetLatencyTimer", status, deviceHandle, serialNumber);
    
    // Set Xfer size
    status = FT_SetUSBParameters(deviceHandle, 8192, 32768);
    errorHandler("FT_SetUSBParameters", status, deviceHandle, serialNumber);

    // status_timeout Set time outs
    status = FT_SetTimeouts(deviceHandle, 20, 20);
    errorHandler("FT_SetTimeouts", status, deviceHandle, serialNumber);

}

void disconnectBoard(FT_HANDLE* deviceHandle, char* serialNumber) {
    // Close connection using handle
    printf("Closing device of serial number %s.\n", serialNumber);
    FT_Close(&deviceHandle);
    return 0;
}

void errorHandler(char* function_name, DWORD* status, FT_HANDLE* deviceHandle, char* serialNumber) {
    if (status != FT_OK) {
        printf("%s status: %ld.\n", function_name, status);
        disconnectBoard(deviceHandle, serialNumber);
        exit(4);
    }
}