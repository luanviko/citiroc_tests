# Assume OS to be Linux.

# Flags:
DEPENDENCIES := -lpthread
CFLAGS = -Wall -Wextra
DYNAMIC_LINK_OPTIONS := -Wl,-rpath /usr/local/lib -lftd2xx -llalusb20

# Rules:
all: list_devices.exe open_devices.exe

list_devices.exe: list_devices.c	
	$(CC) list_devices.c -o list_devices.exe $(CFLAGS) $(DEPENDENCIES) $(DYNAMIC_LINK_OPTIONS) 

open_devices.exe: open_devices.c	
	$(CC) open_devices.c -o open_devices.exe $(CFLAGS) $(DEPENDENCIES) $(DYNAMIC_LINK_OPTIONS) 

clean:
	-rm -f *.o ; rm *.exe
