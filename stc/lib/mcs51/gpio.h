#ifndef GPIO_H
#define GPIO_H

#define GPIO_LOW  0
#define GPIO_HIGH 1

#define	GPIO_INPUT(port, pin)                   P##port##M1 |= 1 << pin, P##port##M0 &= ~(1 << pin)
#define	GPIO_INPUT_PULL_UP(port, pin)  	        P##port##M1 &= ~(1 << pin), P##port##M0 &= ~(1 << pin)
#define	GPIO_OUTPUT_PUSH_PULL(port, pin)		P##port##M1 |= 1 << pin, P##port##M0 |= 1 << pin
#define	GPIO_OUTPUT_OPEN_DRAIN(port, pin))		P##port##M1 &= ~(1 << pin), P##port##M0 |= 1 << pin	

#endif
