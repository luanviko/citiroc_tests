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
    char serialNumber[16];
    char description[1024]; 
    // Eeprom_Generic      *eeprom = NULL;

    // LALUsb variables
    int numberOfUSBDevices;

    // Find CITIROC 1A device using FTD2XX libraries.
    // Look into FTD2XX documentation for details. 

    // Find number of devices
    status = FT_CreateDeviceInfoList(&numberOfDevices);
    
    // Allocate memory for device info
    // Apparently there are two ways for memory allocation
    
    deviceList = calloc((size_t)numberOfDevices, sizeof(FT_DEVICE_LIST_INFO_NODE));
    if (deviceList == NULL) {
        printf("Allocation failure.\n");
    }
    
    // deviceList = (FT_DEVICE_LIST_INFO_NODE*)malloc(sizeof(FT_DEVICE_LIST_INFO_NODE)*numberOfDevices);

    // Fetch information about devices
    status = FT_GetDeviceInfoList(deviceList, &numberOfDevices);    

    // deviceList[0].flag

    // Catch the exception
    if (status != FT_OK) {
        printf("Error code not zero. FT_STATUS = %d.\n", (int) status);
        return 1;
    }

    // Print device information
    // printDevicesInfo(deviceList, &numberOfDevices);
    printf("Number of devices found: %ld.\n", numberOfDevices);
    for (int i = 0; i < numberOfDevices; i++) {
        status = FT_GetDeviceInfoDetail(i, &flags, &type, &id, &localID, &serialNumber, &description, temporaryHandle); 
        printf("Device no. %d:\n", i);
        printf("   Serial no.: %s\n", serialNumber);
        printf("   Id: %ld\n", id);
        printf("   Description: %s\n", description);
    }

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