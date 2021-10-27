


        void OSIdle(void)
{
    while(1)
    {
        PCON = PCON | 0x01;                     /* CPU进入休眠状态 */
    }
}