# STM32F051R8T6_Template_Project
It is simple template project for STM32f051r8t6.
It contains:
  - /boot/:
    - core_cm0.h - Definitions of the Cortex M0 core addresses and structures of registers . Functions for working with NVIC and SysTick.
    - core_cmFunc.h - Core register access functions.
    - core_cmInstr.h - Definitions of core instructions.
    - linker.ld - Linker script.
    - startup_ARMCM0.S - startup file. Contains Reset_Handler fucntion, which copy dato to RAM and clear BSS.
    - stm32f0xx.h - Contains addresses and structs of STM peripheral registers. Peripheral Registers Bits Definition.
  - /libs/: 
    - /Sources/:
      - config.c contains RCC reset and setup(for sys clock 48 MHz).
    - /Includes/:
      - bit_operations.h contains macros for basic bit operations.
      - config.h declares rcc_config().
  - main.c contains main function which calls after reset handler.
  - Makefile file for building project.

Make commands:
 - make - complie programm into a binary format.
 - make clean - delete all *.bin, *.elf, *.asm, *.o files.
 - make asm - creates assembly file.
 - make flash - load binary file to MCU's flash.
 - make erase - erase STM32 flash memory.
 - make gdbs - provides a gdb server. 
 - make gdbr - connect to the gdb server at port 4242, load executable to the STM32 ﬂash memory. (in another terminal after make gdbs)

Needed tools:
 - arm-none-eabi
 - stlink

To changle MCU:
 1. Specify the memory initialization(RAM, FLASH) in the linker file (.ld) with the values(ORIGIN, LENGTH) in the reference manual memory map.
 1. Edit startup file with new MCU specific interrupts and def_irq_handler macros. 
 1. Edit makefile MCU specificatation.
 1. Add Peripheral Access Layer Header File(stm32f0xx.h etc) for new MCU.
 1. Config RCC in libs/Sources/config.c file.
