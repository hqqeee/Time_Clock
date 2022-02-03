#include "config.h"
#include "irq_handlers.h"
#include "dyn_display.h"

int main(void)
{
	rcc_config();
	gpio_config();
	timer6_config();
	timer2_config();
	SysTick_Config(SystemCoreClock/1000);
	while(1)
	{
		if(set_time_f)
		{
			/* while time-setting mode is on last 2 digit is blinking */
			for(int i = 0; i < 8000; i++)
			{
				display_number(key_pressed);
			}
			for(int i = 0; i < 160000; i++)
			{
			}
		}
		if(alarm_time_f)
		{
			/* blink in alarm-setting mode */
			for(int i = 0; i < 8000; i++)
			{
				display_number(alarm_time);
			}
			for(int i = 0; i < 160000; i++)
			{
			}
		}
		/* if alarm time has come show some animations on display */
		if(disp_number == alarm_time)
		{
			startup_animation();
		}
		display_number(disp_number);
	}
}
