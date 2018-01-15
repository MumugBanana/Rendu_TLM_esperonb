/********************************************************************
 * Copyright (C) 2009, 2012 by Verimag                              *
 * Initial author: Matthieu Moy                                     *
 ********************************************************************/

/*!
 \file hal.h
 \brief Harwdare Abstraction Layer : implementation for MicroBlaze
 ISS.
 */

#ifndef HAL_H
#define HAL_H

#include <stdint.h>

/* Dummy implementation of abort(): invalid instruction */
#define abort() do {				\
	printf("abort() function called\r\n");  \
	_hw_exception_handler();		\
} while (0)

/* HAL primitives for cross-compilation */

unsigned int hal_read32(unsigned int a) {
	unsigned int *ptr = (void*) a;
	return *ptr;
}

void hal_write32(unsigned int a, unsigned int d) {
	unsigned int *ptr = (void*) a;
	*ptr = d;
}

void microblaze_enable_interrupts(void) {
	__asm("ori     r3, r0, 2\n"
			"mts     rmsr, r3");
}

#define printf(str) printf_uart(str)

void printf_uart(char* str) {
	int i;
	char *ptr = (void*) (UART_BASEADDR + UART_FIFO_WRITE);
	for (i = 0; str[i] != '\0'; i++) {
		*ptr = str[i];
	}
}

void hal_cpu_relax() {
}

void hal_wait_for_irq() {
	while (!irq_received)
		hal_cpu_relax();
	irq_received = 0;
}

#endif /* HAL_H */
