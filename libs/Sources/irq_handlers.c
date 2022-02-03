/*
 * Source file with IRQ Handlers.
 * It contains:
 * 		disp_number - variable to display, also it used in time format.
 *		key_pressed - variable which can be equal from 0 to 100, it stores 2 digit that user entered.
 *			      when equal to 100 it is waiting for first digit to input 
 *		seconds, minutes, hours - variables for time clock.
 *		set_time_f - variable for setting-time mode. it can be 0..3
 *			     0 - setting-time mode disable
 *			     1 - setting-time mode enable. wait for seconds input.
 *			     2 - wait for minutes input.
 *			     3 - wait for hours input.
 *		alarm_time_f - variable for alarm-setting mode. It can be 0..3(ref. set_time_f).
 *		alarm_time - alarm time value variable. It does not necessarily match the time format, if so,
 *							  the alarm is disabled . 
 *		TIM2_Handler - Timer 2 handler. It reads input from keyboard and assign key_pressed value.
 *				if "*" is pressed it starts setting-time mode, if "#" - alarm-setting mode.
 *				TIM2 counter is used for delay-debounce.
 *		TIM6_DAC_IRQHandler - Timer6 handler. It counts time and assigns it to disp_number.
 *		SysTick_Handler - It scans keyboard columns.
 * 		Default system handlers: NMI, HardFault, SVC, PendSV.
 */

#include "main.h"

/* Macro for reading a two-digit number from the keyboard */
#define READ_2DIG(KEY_NUM) 	if(key_pressed > 99) \
				{ \
					key_pressed = KEY_NUM*10; \
				} \
				else if(key_pressed >= 10) key_pressed = key_pressed + KEY_NUM;  \
				else if(key_pressed == 0) key_pressed = KEY_NUM;

volatile uint32_t disp_number;
volatile uint8_t set_time_f = 0;
volatile uint32_t alarm_time = 1999999;
volatile uint8_t alarm_time_f = 0;
volatile uint8_t key_pressed;
static volatile uint16_t seconds = 0;
static volatile uint16_t minutes = 0;
static volatile uint16_t hours = 0;


void TIM6_DAC_IRQHandler(void)
{
	WRITE_REG(GPIOC-> ODR, (GPIOC -> ODR ^ (0x1<<8))); // PC8 LED toggle every seconds.
	seconds = seconds + 1;
	if(seconds > 59)
	{
		minutes = minutes + 100;
		seconds = 0;
	}
	if(minutes > 5900)
	{
		hours = hours + 100;
		minutes = 0;
	}
	if(hours > 2300)
	{
		hours = 0;
	}
	/* 1 000 000 to show all zero digits */
	disp_number = 1000000 + (hours * 100)+ minutes + seconds;
	
	/* Clear Update Interrupt flag */
	CLEAR_BIT(TIM6->SR, 0x1U);
}

void TIM2_IRQHandler(void)
{
	static uint32_t last_cnt_value = 0; // updates with tim2 counter value each time one of the buttons is pressed
	/* CC channel 1 Handler Row1 */
	if(READ_BIT(TIM2->SR, (0x1U<<1)))
	{	
		/* Debounce delay check (ms)*/
		if(TIM2->CNT-last_cnt_value > 100)
		{
			if(CHECK_COL1 && (set_time_f || alarm_time_f))
			{
				READ_2DIG(1)
			}
			else if(CHECK_COL2 && (set_time_f || alarm_time_f))
			{
				READ_2DIG(2)
			}
			else if(CHECK_COL3 && (set_time_f || alarm_time_f))
			{
				READ_2DIG(3)
			}
		}
		TIM2->CNT = last_cnt_value;	
		/* Reset CC1 channel interrupt flag */
		CLEAR_BIT(TIM2->SR, (0x1<<1));
	}
	/* CC channel 2 Handler Row 4 */
	if(READ_BIT(TIM2->SR, (0x1U<<2)))
	{	
	/* Debounce delay check (ms)*/
		if(TIM2->CNT-last_cnt_value > 100)
		{
			/* if "*" is pressed set flag set_time_f */
			if(CHECK_COL1)
			{
				switch(set_time_f)
				{
					case 0:
					set_time_f = 1;
					key_pressed = 100;
					break;
					case 1:
					seconds = key_pressed;
					key_pressed = 100;
					set_time_f = 2;
					break;
					case 2:
					minutes = 100*key_pressed;
					key_pressed = 100;
					set_time_f = 3;
					break;
					case 3:
					hours = 100*key_pressed;
					key_pressed = 100;
					set_time_f = 0;
					break;
					default:
					break;
				}
			}
			else if(CHECK_COL2 && (set_time_f || alarm_time_f))
			{
				READ_2DIG(0);		
			}
			/* if "#" is pressed start alarm-setting mode */
			else if(CHECK_COL3)
			{
				switch(alarm_time_f)
				{
					case 0:
					alarm_time_f = 1;
					key_pressed = 100;
					break;
					case 1:
					alarm_time = key_pressed;
					key_pressed = 100;
					alarm_time_f = 2;
					break;
					case 2:
					alarm_time = alarm_time + 100*key_pressed;
					key_pressed = 100;
					alarm_time_f = 3;
					break;
					case 3:
					alarm_time = alarm_time + 10000*key_pressed + 1000000;
					key_pressed = 100;
					alarm_time_f = 0;
					break;
					default:
					break;
				}
			}
		}
		TIM2->CNT = last_cnt_value;	
		/* Reset CC2 channel interrupt flag */
		CLEAR_BIT(TIM2->SR, (0x1<<2));
	}
	/* CC channel 3 Handler Row 3 */
	if(READ_BIT(TIM2->SR, (0x1U<<3)))
	{	
		/* Debounce delay */
		if(TIM2->CNT-last_cnt_value > 100)
		{
			if(CHECK_COL1 && (set_time_f || alarm_time_f))
			{
				READ_2DIG(7);
			}
			else if(CHECK_COL2 && (set_time_f || alarm_time_f))
			{
				READ_2DIG(8);
			}
			else if(CHECK_COL3 && (set_time_f || alarm_time_f))
			{
				READ_2DIG(9);
			}
		}
		TIM2->CNT = last_cnt_value;
		/* Reset CC3 channel interrupt flag */
		CLEAR_BIT(TIM2->SR, (0x1<<3));
	}
	/* CC channel 4 Hadnler Row 2 */
	if(READ_BIT(TIM2->SR, (0x1U<<4)))
	{	
		/* Delay debounce */
		if(TIM2->CNT-last_cnt_value > 100)
		{
			if(CHECK_COL1 && (set_time_f || alarm_time_f))
			{
				READ_2DIG(4);
			}
			else if(CHECK_COL2 && (set_time_f || alarm_time_f))
			{
				READ_2DIG(5);
			}
			else if(CHECK_COL3 && (set_time_f || alarm_time_f))
			{
				READ_2DIG(6);
			}
		}
		TIM2->CNT = last_cnt_value;
		/* Reset CC1 channel interrupt flag */
		CLEAR_BIT(TIM2->SR, (0x1<<4));
	}


}

void SysTick_Handler(void)
{
	/* Scan Col1 */
	if(CHECK_COL3)
	{
		REV_MODIFY_REG(GPIOC->ODR, 0x7U, 0x1U);
	}
	/* Scan Col2 */
	else if(CHECK_COL1)
	{
		REV_MODIFY_REG(GPIOC->ODR, 0x7U, (0x1U<<1));
	}
	/* Scan Col3 */
	else if(CHECK_COL2)
	{
		REV_MODIFY_REG(GPIOC->ODR, 0x7U, (0x1U<<2));
	}
}

/* System Handlers */

void NMI_Hander(void)
{
}

void HardFault_Handler(void)
{
	while(1);
}

void SVC_Handler(void)
{
}

void PendSV_Handler(void)
{
}

