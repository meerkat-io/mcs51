#ifndef CPU_H
#define CPU_H

#define GPIO_LOW  0
#define GPIO_HIGH 1

#define	GPIO_INPUT(port, pin)                   P##port##M1 |= BitMasks[pin], P##port##M0 &= ~BitMasks[pin]
#define	GPIO_INPUT_PULL_UP(port, pin)  	        P##port##M1 &= ~BitMasks[pin), P##port##M0 &= ~BitMasks[pin]
#define	GPIO_OUTPUT_PUSH_PULL(port, pin)		P##port##M1 |= BitMasks[pin], P##port##M0 |= BitMasks[pin]
#define	GPIO_OUTPUT_OPEN_DRAIN(port, pin))		P##port##M1 &= ~BitMasks[pin], P##port##M0 |= BitMasks[pin]	

#define TIMER_CLOCK_DIVISION_1()    CLK_DIV &= ~BIT_MASK_2, CLK_DIV &= ~BIT_MASK_1, CLK_DIV &= ~BIT_MASK_0
#define TIMER_CLOCK_DIVISION_2()    CLK_DIV &= ~BIT_MASK_2, CLK_DIV &= ~BIT_MASK_1, CLK_DIV |= BIT_MASK_0
#define TIMER_CLOCK_DIVISION_4()    CLK_DIV &= ~BIT_MASK_2, CLK_DIV |= BIT_MASK_1, CLK_DIV &= ~BIT_MASK_0
#define TIMER_CLOCK_DIVISION_8()    CLK_DIV &= ~BIT_MASK_2, CLK_DIV |= BIT_MASK_1, CLK_DIV |= BIT_MASK_0
#define TIMER_CLOCK_DIVISION_16()   CLK_DIV |= BIT_MASK_2, CLK_DIV &= ~BIT_MASK_1, CLK_DIV &= ~BIT_MASK_0
#define TIMER_CLOCK_DIVISION_32()   CLK_DIV |= BIT_MASK_2, CLK_DIV &= ~BIT_MASK_1, CLK_DIV |= BIT_MASK_0
#define TIMER_CLOCK_DIVISION_64()   CLK_DIV |= BIT_MASK_2, CLK_DIV |= BIT_MASK_1, CLK_DIV &= ~BIT_MASK_0
#define TIMER_CLOCK_DIVISION_128()  CLK_DIV |= BIT_MASK_2, CLK_DIV |= BIT_MASK_1, CLK_DIV |= BIT_MASK_0

#define ENTER_CRITICAL()  EA = 0, CriticalCount++              /* disable interrupt */
#define EXIT_CRITICAL()   if (--CriticalCount == 0) EA = 1     /* enable interrupt */

#endif