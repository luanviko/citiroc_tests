DEPENDENCIES := -lpthread
UNAME := $(shell uname)

# Assume target is Mac OS if build host is Mac OS; any other host targets Linux
ifeq ($(UNAME), Darwin)
	DEPENDENCIES += -lobjc -framework IOKit -framework CoreFoundation
else
	DEPENDENCIES += -lrt
endif

CFLAGS = -Wall -Wextra

DYNAMIC_LINK_OPTIONS := -Wl,-rpath /usr/local/lib

APP = list_devices
STATIC_APP = $(APP)-static
DYNAMIC_APP = $(APP)-dynamic

all: $(APP)-static $(APP)-dynamic 

$(STATIC_APP): list_devices.c
	$(CC) list_devices.c -o $(STATIC_APP) ../build/libftd2xx.a $(CFLAGS) $(DEPENDENCIES)

$(DYNAMIC_APP): list_devices.c	
	$(CC) list_devices.c -o $(DYNAMIC_APP) $(CFLAGS) -lftd2xx $(DEPENDENCIES) $(DYNAMIC_LINK_OPTIONS)
	
clean:
	-rm -f *.o ; rm $(STATIC_APP); rm $(DYNAMIC_APP)
