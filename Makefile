CC = loongarch64-linux-gnu-gcc
CFLAGS = -Wall -Wextra -O2
SOURCES = main.c draw.c bmp.c
HEADERS = draw.h
TARGET = graphics_app

all: $(TARGET)

$(TARGET): $(SOURCES) $(HEADERS)
	$(CC) $(CFLAGS) -o $(TARGET) $(SOURCES)

clean:
	rm -f $(TARGET)