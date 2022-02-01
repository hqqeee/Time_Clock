/*
 * This file contains display funtions.
 * 	display_number(disp_num):
 *		disp_num - number (0 ... 999999) to displayed.
 *		It shows separately each digit.
 *	startup_animation():
 *		A few simple animations showing if the indicators are connected correctly.
 *		And display running line "HELLO PEOLPLE ".
 */

#include "main.h"

static const uint16_t numbers[10] = {
		DISP_0,
		DISP_1,
		DISP_2,
		DISP_3,
		DISP_4,
		DISP_5,
		DISP_6,
		DISP_7,
		DISP_8,
		DISP_9
};	

static const uint16_t digits_masks[6] = {
		DIG1_MSK,
		DIG2_MSK,
		DIG3_MSK,
		DIG4_MSK,
		DIG5_MSK,
		DIG6_MSK
};

void display_number(uint32_t disp_num)
{
		/* digit - digit number(1...6) */
		uint8_t digit = 0;
		uint8_t tmp_number = 0;
		/* Loop separately displays a number on each indicator. */
		while(disp_num)
		{
				tmp_number = disp_num % 10;
				disp_num = disp_num / 10;
				digit = digit + 1;
				switch(digit)
				{
					case 1:
							WRITE_REG(GPIOB -> ODR, (~numbers[tmp_number] & ~digits_masks[0]));
							break;
					case 2:
							WRITE_REG(GPIOB -> ODR, (~numbers[tmp_number] & ~digits_masks[1]));
							break;
					case 3:
							WRITE_REG(GPIOB -> ODR, (~numbers[tmp_number] & ~digits_masks[2]));
							break;
					case 4:
							WRITE_REG(GPIOB -> ODR, (~numbers[tmp_number] & ~digits_masks[3]));
							break;
					case 5:
							WRITE_REG(GPIOB -> ODR, (~numbers[tmp_number] & ~digits_masks[4]));
							break;
					case 6:
							WRITE_REG(GPIOB -> ODR, (~numbers[tmp_number] & ~digits_masks[5]));
							break;
					default: break;		
				}
		}
		/* Disable indicators */
		CLEAR_REG(GPIOB -> ODR);
}

static void running_line(void)
{
	uint16_t message[13] = {
	DISP_H, // H
	DISP_E, // E
	DISP_L, // L
	DISP_L, // L
	DISP_0, // O
	0x0,    // space
	DISP_P, // P
	DISP_E, // E
	DISP_0, // O
	DISP_P, // P
	DISP_L, // L
	DISP_E, // E
	0x0     // space
	};
	uint8_t counter = 13;
	while(counter)
	{
		counter--;	
		uint16_t delay_count = 10000;
		while(delay_count != 0){ 
			uint8_t dig_num = 6;
			while(dig_num != 0)
			{
				dig_num--;
				if(counter - 7 - dig_num >= 0)
				{
					WRITE_REG(GPIOB->ODR, ~digits_masks[dig_num] & ~message[counter - 7 - dig_num]);
				}
				else
				{
					WRITE_REG(GPIOB->ODR, ~digits_masks[dig_num] & ~message[counter - 7 - dig_num + 13]);
				}
			}
		delay_count--;
		}
	}
	CLEAR_REG(GPIOB -> ODR);
}


__attribute__((naked)) static void delay(void)
{
	asm ("push {r7,lr}"); //setting lr and r7 on the top of stack
	asm ("ldr r6, [pc, #8]"); //loading .word(#8) to r6
	asm ("sub r6, #1"); //sub 1 from r6
	asm ("cmp r6, #0"); //check if r6 is equel to 0
	asm ("bne delay+0x4"); //if not go to delay 0x4(repeat)
	asm ("pop {r7,pc}"); //returning to function start point
	asm (".word 0x43870");
}


void startup_animation(void)
{
	WRITE_REG(GPIOB->ODR, 0x0);
	/* Spinning line on each indicator */
	for(int i = 0; i < 6; i++)
	{
		for(int j = 0; j < 6; j++)
		{
			WRITE_REG(GPIOB->ODR, (~digits_masks[i] & ~(0x1<<j)));
			delay();
		}	
	}
	WRITE_REG(GPIOB->ODR, 0x0);
	running_line();
	WRITE_REG(GPIOB->ODR, 0x0);
	/* Upper horizontal line from right to left */
	for(int i = 0; i < 6; i++)
	{
		WRITE_REG(GPIOB->ODR, (~digits_masks[i] & ~(0x1)));
		delay();
	}
	/* Middle horizontal  line from left to righ */ 
	for(int i = 5; i >= 0; i--)
	{
		WRITE_REG(GPIOB->ODR, (~digits_masks[i] & ~(0x40)));
		delay();
	}
	/* Lower horizontal line from right to left */
	for(int i = 0; i < 6; i++)
	{
		WRITE_REG(GPIOB->ODR, (~digits_masks[i] & ~(0x8)));
		delay();
	}
	WRITE_REG(GPIOB->ODR, 0x0);
	
}

