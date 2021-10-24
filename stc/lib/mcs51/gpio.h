#ifndef GPIO_H
#define GPIO_H

#include <compiler.h>
#include <types.h>
#include <lint.h>

#define GPIO_LOW  0
#define GPIO_HIGH 1

#define	GPIO_INPUT(port_m1, port_m0, pin)               port_m1 |= 1 << pin,	port_m0 &= ~(1 << pin);
#define	GPIO_INPUT_PULL_UP(port_m1, port_m0, pin)  	    port_m1 &= ~(1 << pin),	port_m0 &= ~(1 << pin);
#define	GPIO_OUT_PUSH_PULL(port_m1, port_m0, pin)		port_m1 |= 1 << pin,	port_m0 |= 1 << pin;
#define	GPIO_OUT_OPEN_DRAIN(port_m1, port_m0, pin))		port_m1 &= ~(1 << pin),	port_m0 |= 1 << pin;	

#endif
