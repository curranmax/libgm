
INC_PATH = -I /usr/local/include/gm -I /user/include
LIB_PATH = -L /usr/local/lib -l gm -l usb-1.0  -l hidapi-libusb

CC = g++-4.9
CFLAGS = -Wall -std=c++11 $(INC_PATH)

SOURCES = main.cpp
OBJECTS = $(SOURCES:.cpp=.o)
NAME = mod-gm

all: clean $(NAME)

$(NAME): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) $(LIB_PATH) -o $(NAME)

.cpp.o:
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(NAME) *.o