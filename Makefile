MCU = atmega328p
CC = avr-gcc
CFLAGS = -mmcu=$(MCU) -Os -DF_CPU=16000000UL
OBJ = main.o
TARGET = toggleled

all: $(TARGET).hex

$(TARGET).hex: $(TARGET).elf
	avr-objcopy -O ihex -R .eeprom $(TARGET).elf $(TARGET).hex

$(TARGET).elf: $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET).elf $(OBJ)

main.o: main.c
	$(CC) $(CFLAGS) -c main.c

clean:
	rm -f $(OBJ) $(TARGET).elf $(TARGET).hex

upload: $(TARGET).hex
	avrdude -c usbasp -p $(MCU) -U flash:w:$(TARGET).hex

.PHONY: all clean upload
