#ifndef __IRQ_HANDLERS_H
#define __IRQ_HANDLERS_H

#include "main.h"

extern volatile uint32_t disp_number;
extern volatile uint32_t alarm_time;
extern volatile uint8_t set_time_f;
extern volatile uint8_t key_pressed;
extern volatile uint8_t alarm_time_f;
extern void TIM6_DAC_IRQHandler(void);
extern void TIM2_IRQHandler(void);
extern void SysTick_Handler(void);
extern void NMI_Handler(void);
extern void HardFault_Handler(void);
extern void SVC_Handler(void);
extern void PendSV_Handle(void);

#endif /* __IRQ_HANDLERS_H  */
