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
DYNAMIC_APP = $(APP)-dynamic

all: $(APP)-dynamic 

$(DYNAMIC_APP): list_devices.c	
	$(CC) list_devices.c -o $(DYNAMIC_APP) $(CFLAGS) -lftd2xx -llalusb20 $(DEPENDENCIES) $(DYNAMIC_LINK_OPTIONS)
	
clean:
	-rm -f *.o ; rm $(DYNAMIC_APP)
