#
# 		Variable Assignments.
#


PROJECT = project_name

# MCU specification:
# MCU = STM32F051R8T6
CORTEX_M = 0
ARCH_FLAGS = -mthumb -mcpu=cortex-m$(CORTEX_M)
MCU_DEFINES = -DSTM32F0 -DSTM32F051
FLASH_START = 0x08000000

# Tools:
CC = arm-none-eabi-gcc
LD = arm-none-eabi-gcc
GDB = arm-none-eabi-gdb
OBJC = arm-none-eabi-objcopy
OBJD = arm-none-eabi-objdump
SIZE = arm-none-eabi-size
STW = st-flash write
STE = st-flash erase
STU = st-util
RM = rm

# Sources:
SOURCE_S = $(wildcard boot/*.S)
SOURCE_LIB = $(wildcard libs/Sources/*.c)
SOURCE_BOOT = $(wildcard boot/*.c)
SOURCE_C = $(wildcard *.c)
SOURCE_C += $(SOURCE_BOOT)
SOURCE_C += $(SOURCE_LIB)

OBJS = $(SOURCE_C:.c=.o) $(SOURCE_S:.s=.o)
LDFILE = $(wildcard boot/*.ld)

# Includes:
IBOOT = -Iboot
ILIBS = -Ilibs/Includes
INCLUDES += $(IBOOT)
INCLUDES += $(ILIBS)

DEFINES = -D__STARTUP_CLEAR_BSS -D__START=main
DEFINES += -DSYSCLK48 -D__NO_SYSTEM_INIT

# Option flags:
MCUFLAGS = $(ARCH_FLAGS) $(MCU_DEFINES)
LDFLAGS = -T$(LDFILE) $(MCUFLAGS)
DBGFLAGS = -g -O0 -ggdb -gdwarf-2
CFLAGS += $(DBGFLAGS) $(MCUFLAGS) $(INCLUDES) $(DEFINES)
CFLAGS += -Wall -Wextra -pedantic
CFLAGS += -nostartfiles -nodefaultlibs -nostdlib



#
# 		Rules.
#



.PHONY: all, clean, asm, flash, erase, gdbs, gdbr

all: $(PROJECT).bin
	$(SIZE) $(PROJECT).elf
clean: 
	$(RM) -f *.bin *.elf *.asm *.o boot/*.o libs/Sources/*.o
asm: $(PROJECT).asm
flash: 
	$(STW) $(PROJECT).bin $(FLASH_START)
erase:
	st-flash erase
gdbs: 
	$(STU)
gdbr: $(PROJECT).elf
	$(GDB) -ex 'target extended-remote :4242' \
		   -ex 'load'  $(PROJECT).elf
	

# Source Rules

# Object file assembling
%.o: %.s
	$(CC) $(CFLAGS) -c -o $@ $<
%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

# ELF and Binary
$(PROJECT).elf: $(OBJS)
	$(LD) $(LDFLAGS) $^ $(CFLAGS) -o $@ -lgcc
%.bin: %.elf
	$(OBJC) -O binary $< $@

# Disassemling
%.asm: %.elf
	$(OBJD) -dwh $< > $@

