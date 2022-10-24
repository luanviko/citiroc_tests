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

// Main function
int main() {

    // FTD2XX variables
    FT_STATUS status;
    FT_DEVICE_LIST_INFO_NODE* deviceList;
    unsigned int numberOfDevices;
    FT_HANDLE temporaryHandle;
    FT_HANDLE deviceHandle;
    DWORD flags;
    DWORD id;
    DWORD type;
    DWORD localID;
    char serialNumber[16];
    char description[1024];

    // Find number of devices
    status = FT_CreateDeviceInfoList(&numberOfDevices);
    
    // Allocate memory for device info    
    deviceList = calloc((size_t)numberOfDevices, sizeof(FT_DEVICE_LIST_INFO_NODE));
    if (deviceList == NULL) {
        printf("C error: Unable to allocate memory for device info.\n");
    }

    // Fetch information about devices
    status = FT_GetDeviceInfoList(deviceList, &numberOfDevices);    

    // Catch the exception
    if (status != FT_OK) {
        printf("Error code not zero. FT_STATUS = %d.\n", (int) status);
        return 1;
    }

    // Keep details for device 0.
    status = FT_GetDeviceInfoDetail(0, &flags, &type, &id, &localID, &serialNumber, &description, temporaryHandle); 
    
    if (status != FT_OK) {
        printf("FTD2XX error: No compatible devices found.\n");
        exit(1);
    }

    // Attempt connection with board.
    printf("Trying to connect with device of serial number %s...\n", serialNumber);
    status = FT_OpenEx(&serialNumber, FT_OPEN_BY_SERIAL_NUMBER, &deviceHandle);
    if (status != FT_OK) {
        printf("FT_OpenEx status: %ld. Unable to open device by serial number.\n");
        exit(2);
    }

    // Do stuff with your device
    printf("Connection established.\n");

    // Close connection using handle
    printf("Closing device of serial number %s.\n", serialNumber);
    FT_Close(&deviceHandle);
    return 0;

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