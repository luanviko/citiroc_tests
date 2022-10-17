#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "ftd2xx.h"
#include "LALUsb.h"

// Function declarators
FT_STATUS makeList(int* numberOfDevices);
int printDevicesInfo(FT_DEVICE_LIST_INFO_NODE* deviceList, unsigned int* numberOfDevices);
void findBoard(char* serialNumber, int* numberOfDevices, FT_DEVICE_LIST_INFO_NODE* deviceList);
void connectBoard(char* serialNumber, int* usbDeviceId, bool* connected);
void disconnectBoard(int* usbDeviceId);

// Main function
int main() {

    // FTD2XX variables
    FT_STATUS status;
    FT_DEVICE_LIST_INFO_NODE* deviceList;
    unsigned int numberOfDevices;
    char* serialNumber = "invalid serial number";

    // LALUsb variables
    int numberOfUSBDevices;

    // Fetch serial number of board
    findBoard(serialNumber, &numberOfDevices, deviceList); 

    // Print device information
    printDevicesInfo(deviceList, &numberOfDevices);

    numberOfUSBDevices = USB_GetNumberOfDevs();
    printf("Number of USB devices: %d.\n", numberOfUSBDevices);

}

void findBoard(char* serialNumber, int* numberOfDevices, FT_DEVICE_LIST_INFO_NODE* deviceList) {
    
    // Find number of devices
    status = FT_CreateDeviceInfoList(&numberOfDevices);
    
    // Allocate memory for device info
    deviceList = (FT_DEVICE_LIST_INFO_NODE*)malloc(sizeof(FT_DEVICE_LIST_INFO_NODE)*numberOfDevices);

    // Fetch information about devices
    status = FT_GetDeviceInfoList(deviceList, &numberOfDevices);    
    printf("%d %d\n", (int) status, (int) numberOfDevices);

    // Catch the exception
    if (status != FT_OK) {
        printf("Error code not zero. FT_STATUS = %d.\n", (int) status);
        return 1;
    }

    

    // strcpy(serialNumber, deviceList[0].SerialNumber);

}

int printDevicesInfo(FT_DEVICE_LIST_INFO_NODE* deviceList, unsigned int* numberOfDevices) {
    if (*numberOfDevices < 0){printf("Negative number of devices. Something is wrong.\n"); return 1;}
    else if (*numberOfDevices == 0){printf("No devices found. Nothing to print out.\n"); return 0;}
    else if (*numberOfDevices > 0) {
        // Start of copy from the documentation pdf.
        for (int i = 0; i < *numberOfDevices; i++) {  
            printf("Dev %d:\n",i);  
            printf("  Flags=0x%x\n",deviceList[i].Flags);
            printf("  Type=0x%x\n",deviceList[i].Type);
            printf("  ID=0x%x\n",deviceList[i].ID);
            printf("  LocId=0x%x\n",deviceList[i].LocId);
            printf("  SerialNumber=%s\n",deviceList[i].SerialNumber);
            printf("  Description=%s\n",deviceList[i].Description);
            printf("  ftHandle=0x%x\n",deviceList[i].ftHandle);
        } // End of copy.
        return 0;
    }
}

void connectBoard(char* serialNumber, int* usbDeviceId, bool* connected){
    
    // Disconnect board if it is already connected.
    if (*usbDeviceId > 0) {
        disconnectBoard(*usbDeviceId);
        *usbDeviceId = 0;
    }

    // Try and open the CITIROC board. Catch the error.
    *usbDeviceId = OpenUsbDevice(serialNumber);
    if (usbDeviceId < 0) {
        USB_Perror(USB_GetLastError());
        exit (1);
    }

    // Initialize board. Catch any error.
    *connected = false;
    bool verbosity = true;
    *connected = USB_Init( (int)usbDeviceId, verbosity);
    if (connected == false) {
        USB_Perror(USB_GetLastError());
        exit (1);
    }

}

void disconnectBoard(int* usbDeviceId) {
    // Add here anything else required for disconnecting the board.
    CloseUsbDevice( (int)usbDeviceId);
}