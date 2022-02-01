#ifndef __IRQ_HANDLERS_H
#define __IRQ_HANDLERS_H

#include "main.h"

extern volatile uint32_t disp_number;
void TIM6_DAC_IRQHandler(void);
void SysTick_Handler(void);
void NMI_Handler(void);
void HardFault_Handler(void);
void SVC_Handler(void);
void PendSV_Handle(void);

#endif /* __IRQ_HANDLERS_H  */
