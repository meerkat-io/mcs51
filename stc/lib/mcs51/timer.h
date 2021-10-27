#ifndef TIMER_H
#define TIMER_H

#include <types.h>
#include "config.h"

#define TIMER_CLOCK_DIVISION_1()    CLK_DIV &= ~BIT_MASK_2, CLK_DIV &= ~BIT_MASK_1, CLK_DIV &= ~BIT_MASK_0
#define TIMER_CLOCK_DIVISION_2()    CLK_DIV &= ~BIT_MASK_2, CLK_DIV &= ~BIT_MASK_1, CLK_DIV |= BIT_MASK_0
#define TIMER_CLOCK_DIVISION_4()    CLK_DIV &= ~BIT_MASK_2, CLK_DIV |= BIT_MASK_1, CLK_DIV &= ~BIT_MASK_0
#define TIMER_CLOCK_DIVISION_8()    CLK_DIV &= ~BIT_MASK_2, CLK_DIV |= BIT_MASK_1, CLK_DIV |= BIT_MASK_0
#define TIMER_CLOCK_DIVISION_16()   CLK_DIV |= BIT_MASK_2, CLK_DIV &= ~BIT_MASK_1, CLK_DIV &= ~BIT_MASK_0
#define TIMER_CLOCK_DIVISION_32()   CLK_DIV |= BIT_MASK_2, CLK_DIV &= ~BIT_MASK_1, CLK_DIV |= BIT_MASK_0
#define TIMER_CLOCK_DIVISION_64()   CLK_DIV |= BIT_MASK_2, CLK_DIV |= BIT_MASK_1, CLK_DIV &= ~BIT_MASK_0
#define TIMER_CLOCK_DIVISION_128()  CLK_DIV |= BIT_MASK_2, CLK_DIV |= BIT_MASK_1, CLK_DIV |= BIT_MASK_0


#define FOSC 22118400L          //系统频率
#define T0_TIM (65536-(Fosc/1/200))</code></pre> 
<pre class="has"><code class="language-cpp language-objc">sfr AUXR &#61; 0x8e;                    //Auxiliary register

void tm0_init()                     //定时器0初始化函数
{
    AUXR |&#61; 0x80;                   //定时器0为1T分频模式
//  AUXR &amp;&#61; 0x7f;                   //定时器0为12T分频模式

    TMOD &#61; 0x01;                    //设置定时器为模式0(16位手动重装载)
    TL0 &#61; T0_TIM%256;  //装载低8位计时值
    TH0 &#61; T0_TIM/256;  //装载高8位
    TR0 &#61; 1;                        //定时器0开始计时
    ET0 &#61; 1;                        //使能定时器0中断
    EA &#61; 1;
}</code></pre> 
<p> </p> 
<pre class="has"><code class="language-cpp">void tm0_isr() interrupt 1 using 1
{
   //定时器到执行这里


    TL0 &#61; T0_TIM%256;//装载计时值
    TH0 &#61; T0_TIM/256;
}

#endif