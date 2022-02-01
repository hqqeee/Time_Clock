/*
 * Source file with IRQ Handlers.
 * It contains:
 * 		Default system handlers: NMI, HardFault, SVC, PendSV.
 */

#include "main.h"

volatile uint32_t disp_number = 0;

void TIM6_DAC_IRQHandler(void)
{
	WRITE_REG(GPIOC-> ODR, (GPIOC -> ODR ^ (0x1<<8)));	
	static uint16_t seconds = 0;
	static uint16_t minutes = 0;
	static uint16_t hours = 0;
	seconds = seconds + 1;
	if(seconds > 59)
	{
		minutes = minutes + 100;
		seconds = 0;
		if(minutes > 5900)
		{
			hours = hours + 100;
			minutes = 0;
			if(hours > 2300)
			{
				hours = 0;
			}
			disp_number = disp_number + hours;
		}
		disp_number = disp_number + minutes;
	}
	/* 1 000 000 to show all zero digits */
	disp_number = 1000000 + (hours * 100)+ minutes + seconds;
	/* Clear Update Interrupt flag */
	CLEAR_BIT(TIM6->SR, 0x1U);
	
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

