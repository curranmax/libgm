CC = g++
MCC_FLAGS = -I/usr/local/include/usbhid
CFLAGS = -static -c -fPIC -Wall
INSTALL_PATH = /usr/local
PYTHON_INSTALL_PATH = /usr/lib/python2.7/dist-packages

HEADERS = FSO.h simplefso.h gm.h gm_utils.h pmd.h usb-3100.h
SOURCES = FSO.cpp simplefso.cpp extern.cpp gm.cpp gm_utils.cpp usb-3100.cpp pmd.cpp
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
