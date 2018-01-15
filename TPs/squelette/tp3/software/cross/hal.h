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

/* TODO: implement HAL primitives for cross-compilation */
// #define hal_read32(a)   abort()
// #define hal_write32(a, d)  abort()
// #define hal_wait_for_irq() abort()
// #define hal_cpu_relax()    abort()

unsigned int hal_read32(unsigned int a) {
	unsigned int *ptr = (void*) a;
	return *ptr;
}

void hal_write32(unsigned int a, unsigned int d) {
	unsigned int *ptr = (void*) a;
	*ptr = d;
}

void hal_wait_for_irq() {
}

void hal_cpu_relax() {
}

void microblaze_enable_interrupts(void) {
	__asm("ori     r3, r0, 2\n"
	      "mts     rmsr, r3");
}

/* TODO: printf is disabled, for now ... */
#define printf(str) printf_uart(str)

void printf_uart(char* str2) {
	int i;

	/*char *str = "ab";
	str[0] = (int) str[0];
	str[1] = (int) str[1];
	str[2] = (int) str[2];*/
	char* str = (void*) str2;
	char *ptr = (void*) (UART_BASEADDR+UART_FIFO_WRITE);
	for(i = 0; str[i] != '\0'; i++) {
	    *ptr = str[i];
	}
}

#endif /* HAL_H */
