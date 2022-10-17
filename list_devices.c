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
    DWORD flags;
    DWORD id;
    DWORD type;
    DWORD localID;
    char serialNumber[1024];
    char description[1024]; 

    // LALUsb variables
    int numberOfUSBDevices;

    // Find CITIROC 1A device using FTD2XX libraries.
    // Look into FTD2XX documentation for details. 

    // Find number of devices
    status = FT_CreateDeviceInfoList(&numberOfDevices);
    
    // Allocate memory for device info
    deviceList = (FT_DEVICE_LIST_INFO_NODE*)malloc(sizeof(FT_DEVICE_LIST_INFO_NODE)*numberOfDevices);

    
    
    // TOMORROW: TRY USING FT_GETDEVICEINFODETAIL
    //           as on line 2218 de FTD2XX_NET.cs 






    // Fetch information about devices
    status = FT_GetDeviceInfoList(deviceList, &numberOfDevices);    

    // Catch the exception
    if (status != FT_OK) {
        printf("Error code not zero. FT_STATUS = %d.\n", (int) status);
        return 1;
    }

    // Print device information
    // printDevicesInfo(deviceList, &numberOfDevices);

    if (numberOfDevices > 0) { 
        status = FT_GetDeviceInfoDetail(1, &flags, &type, &id, &localID, serialNumber, description, temporaryHandle); 
        if (status == FT_OK) {
            printf("Serial number: %s", serialNumber);
        }
    } else {
        printf("No devices found.\n");
        return 1;
    }

    return 0;
    // Try to communicate with USB now.
    // Look for the LALUsb library documentation for details.

    // numberOfUSBDevices = USB_GetNumberOfDevs();
    // printf("Number of USB devices: %d.\n", numberOfUSBDevices);

    



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