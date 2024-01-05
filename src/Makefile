MCU=atmega328p
F_CPU=16000000UL
CC=avr-g++
OBJCOPY=avr-objcopy
CFLAGS=-std=c++14 -g -Wall -Os -mmcu=${MCU} -DF_CPU=${F_CPU} 
PORT=/dev/ttyACM0
TARGET=main
SRCS=./*.cpp 
BAUD=9600

all: $(DEPS)
	${CC} ${CFLAGS} -o ${TARGET}.bin $(SRCS) 
	${OBJCOPY} -O ihex -R .eeprom ${TARGET}.bin ${TARGET}.hex

flash:
	avrdude -F -V -c arduino -p ATMEGA328P -P /dev/ttyACM${PORT_NUM} -b 115200 -U flash:w:${TARGET}.hex

debug:
	screen ${PORT} ${BAUD}

run: all flash clean debug


test: 
	g++ -g test_*.c circularbuffer.cpp -o test.o

clean:
	rm -f *.bin *.hex *.o
