/*
 *
 *  It is simple template project.
 *  RCC configured in config.c file.
 *
 */


#include "config.h"
#include "irq_handlers.h"
#include "dyn_display.h"

int main(void)
{
	rcc_config();
	gpio_config();
	timer6_config();
	while(1)
	{
		display_number(disp_number);
	}
}
