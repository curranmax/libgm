CC = g++
MCC_FLAGS = -I/usr/local/include/usbhid -I/usr/local/include/libusb-1.0 -L/usr/local/lib -lusb-1.0 -lhidapi-libusb
CFLAGS = -static -c -fPIC -Wall -std=c++11
INSTALL_PATH = /usr/local
PYTHON_INSTALL_PATH = /usr/lib/python2.7/dist-packages

HEADERS = gm.h diode.h usb_handle_registry.h pmd.h usb-3100.h usb-1608G.h
SOURCES = extern.cpp gm.cpp diode.cpp usb_handle_registry.cpp pmd.cpp usb-3100.cpp usb-1608G.cpp
OBJECTS = $(SOURCES:.cpp=.o)

all: $(SOURCES) libgm.a libgm.so

libgm.a: $(OBJECTS)
	ar rcs libgm.a $(OBJECTS)

libgm.so: $(OBJECTS)
	$(CC) -shared -Wl,-soname,libgm.so -o libgm.so $(OBJECTS)

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@ $(MCC_FLAGS)

clean:
	rm -rf *o

install: clean all
	# Place shared library
	mv libgm.so $(INSTALL_PATH)/lib/libgm.so
	mv libgm.a $(INSTALL_PATH)/lib/libgm.a
	# Add header files
	mkdir -p $(INSTALL_PATH)/include/gm
	cp $(HEADERS) $(INSTALL_PATH)/include/gm/
	# Install python module
	mkdir -p $(PYTHON_INSTALL_PATH)/gm
	cp gm.py $(PYTHON_INSTALL_PATH)/gm/gm.py

uninstall:
	# Remove shared library
	rm -f $(INSTALL_PATH)/lib/libgm.so
	rm -f $(INSTALL_PATH)/lib/libgm.a
	# Remove header files
	rm -rf $(INSTALL_PATH)/include/gm
	# Remove python module
	rm -rf $(PYTHON_INSTALL_PATH)/gm/
