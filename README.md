# Time Clock
It is simple training project for STM32f051r8t6.

It shows the time on the display, it uses TIM6 for time counting. 
 Time can be setted.
 
To set the time: 
  - press "*" on the keyboard
  - enter seconds and press "*" again
  - enter minutes and press "*" one more time
  - enter hours and press "*". The time is set.
 
It also has alarm.
To set alarm time:
  - press "#" on the keyboard
  - enter seconds and press "*" again
  - enter minutes and press "*" one more time
  - enter hours and press "*". The alarm time is set.
  
When alarm time comes, it show some simple animation on display and running line "HELLO PEOPLE ".

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

