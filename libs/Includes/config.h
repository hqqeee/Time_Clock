#ifndef __CONFIG_H
#define __CONFIG_H

#include "main.h"
void rcc_config(void);
void gpio_config(void);
void timer6_config(void);
void timer2_config(void);
extern uint32_t SystemCoreClock;
#endif /* __CONFIG_H */
