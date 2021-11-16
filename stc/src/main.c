#include <os.h>
#include <pwm.h>

void task0(void);
void task1(void);
void (* const tasks[OS_TASKS])(void) = {task0};

const u8 HALF_DUTY = 127;

void main(void)
{
    enter_critical();

    gpio_mode(GPIO_OUTPUT_PUSH_PULL, 2, 6);
    gpio_mode(GPIO_OUTPUT_PUSH_PULL, 2, 7);

    //set_duty(0, HALF_DUTY);
    //set_tone(1, 440);
    //start_pwm();
    P26 = 1;
   
    os_start();

/*
    AUXR &= 0x7f;
    TMOD = 0x00;
    TL0 = 55000 & 0xff;
    TH0 = 55000 >> 8;
    TR0 = 1;
    ET0 = 1;
    EA = 1;*/  
}

void task0(void)
{
    while (1)
    {
        P27 = 0;
        os_wait(15);
        P27 = 1;
        os_wait(15);
        P27 = 0;
        os_wait(15);
        P27 = 1;
        os_wait(15);
        P27 = 0;
        os_wait(15);
        P27 = 1;
        os_wait(100);
    }
}

void task1(void)
{
    while (1)
    {
        P26 = 0;
        os_wait(100);
        P26 = 1;
        os_wait(100);
    }
}