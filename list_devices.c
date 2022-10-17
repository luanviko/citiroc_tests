#include <stdio.h>
#include <stdlib.h>
#include "ftd2xx.h"

// Following examples/Simple
// provided by FTD2XX driver
// and Citiroc UI 

// Function declarators
FT_STATUS makeList(int* numberOfDevices);
int printDevicesInfo(FT_DEVICE_LIST_INFO_NODE* deviceList, unsigned int* numberOfDevices);

// Main function
int main() {
    FT_STATUS status;
    FT_DEVICE_LIST_INFO_NODE* deviceList;
    unsigned int numberOfDevices;

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

    // Print information about devices
    if (status == FT_OK) {
        printDevicesInfo(deviceList, &numberOfDevices);
    }

    // Find the device with the right info
    if (status == FT_OK) {
        // Try strstr if ID or vendor are string type.
        // Try something else if hexadecimal.
        // strstr(original)
    }

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