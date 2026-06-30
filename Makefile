TARGET = firmware
TOOLCHAIN = arm-none-eabi

CC = $(TOOLCHAIN)-gcc
OBJCOPY = $(TOOLCHAIN)-objcopy

SRCS = src/main.c src/startup.s
OBJS = src/main.o src/startup.o

CFLAGS = -mcpu=cortex-m4 \
         -mthumb \
         -mfpu=fpv4-sp-d16 \
         -mfloat-abi=hard \
         -fdata-sections \
         -ffunction-sections \
         -Wall \
         -O0 -g

LDFLAGS = -T linker.ld \
          -Wl,--gc-sections \
          -Wl,-Map=$(TARGET).map

.PHONY: all clean flash


all: $(TARGET).bin

$(TARGET).elf: $(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^

$(TARGET).bin: $(TARGET).elf
	$(OBJCOPY) -O binary $< $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

%.o: %.s
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET).elf $(TARGET).bin $(TARGET).map


flash: $(TARGET).bin
	openocd -f interface/stlink.cfg \
			-f target/stm32f4x.cfg \
			-c "program $(TARGET).bin 0x08000000 verify reset exit"