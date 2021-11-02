
;****************************************************************************************
;/*********************************************************************************************************
;** 函数名称: LoadCtx
;** 功能描述: 任务环境恢复函数
;** 输　入: OSTaskID,OSFastSwap
;** 输　出 : 无
;** 全局变量: 无
;** 调用模块: 无
;** 
;** 作　者: 陈明计
;** 日　期: 2002年2月22日
;**-------------------------------------------------------------------------------------------------------
;** 修　改: 陈明计
;** 日　期: 2002年12月2日
;**-------------------------------------------------------------------------------------------------------
;** 修　改: 陈明计
;** 日　期: 2003年2月5日
;**-------------------------------------------------------------------------------------------------------
;** 修　改:
;** 日　期:
;**-------------------------------------------------------------------------------------------------------
;********************************************************************************************************/

	RSEG  ?PR?LoadCtx?OS_CPU_A
LoadCtx:
	USING	0
	   
    POP     CriticalCount           ;恢复关中断计数器
                                    ;判断是否需要恢复所有寄存器
    MOV     A,OSTaskID
    CJNE    A,#OS_MAX_TASKS,LoadCtx_0
    SJMP    LoadCtx_2
LoadCtx_0:
    MOV     DPTR,#OSMapTbl
    MOVC    A,@A+DPTR
    ANL     A,OSFastSwap
    JNZ     LoadCtx_2
                                    ;恢复寄存器
    POP     7
    POP     6
    POP     5
    POP     4
    POP     3
    POP     2
    POP     1
    POP     0
    POP     PSW
    POP     DPL
    POP     DPH
    POP     B
    POP     ACC

LoadCtx_2:                                    ;判断是否需要开中断
    INC     CriticalCount
    DJNZ    CriticalCount, LoadCtx_Exit
    SET_EA                          ;开中断

LoadCtx_Exit:
    RET

;****************************************************************************************
;/*********************************************************************************************************
;** 函数名称: OSCtxSw
;** 功能描述: 任务主动放弃CPU环境保存函数
;** 输　入: OSTaskID
;** 输　出 : 无
;** 全局变量: OSFastSwap
;** 调用模块: 无
;** 
;** 作　者: 陈明计
;** 日　期: 2002年2月22日
;**-------------------------------------------------------------------------------------------------------
;** 修　改:
;** 日　期:
;**-------------------------------------------------------------------------------------------------------
;********************************************************************************************************/
    RSEG  ?PR?OSCtxSw?OS_CPU_A
OSCtxSw:
    USING	0
                                    ;设置标志：任务再次恢复运行时不必恢复所有寄存器
    MOV     DPTR,#OSMapTbl
    MOV     A,OSTaskID

;堆栈处理函数
    PUSH    Os_Enter_Sum            ;保存关中断计数器
    mov     r2,sp
    
;     cp1 = (unsigned char idata *)SP +1;
    MOV     R0,SP

    INC     R0
;     temp = (unsigned char )OSTsakStackBotton[OSNextTaskID+1];
    MOV     A,#LOW (OSTsakStackBotton+01H)
    ADD     A,OSNextTaskID
    MOV     R1,A
    MOV     A,@R1
    MOV     R7,A
;     cp2 = OSTsakStackBotton[OSTaskID+1];
    MOV     A,#LOW (OSTsakStackBotton+01H)
    ADD     A,OSTaskID
    MOV     R1,A
    MOV     A,@R1
    MOV     R1,A
;     if( OSNextTaskID > OSTaskID)
    MOV     A,OSNextTaskID
    SETB    C
    SUBB    A,OSTaskID
    JC      ?C0001
;     {
;         while(cp2 != (unsigned char idata *)temp)
;         {
;             *cp1++ = *cp2++;
;         }
    MOV     A,R7
    CLR     C
    SUBB    A,R1
    MOV     R6,A
?C0002:
    MOV     A,@R1
    MOV     @R0,A
    INC     R0
    INC     R1
    DJNZ    R6,?C0002
?C0003:
;         temp = OSTsakStackBotton[OSTaskID+1] - (unsigned char idata *)SP-1;
    MOV     A,#LOW (OSTsakStackBotton+1)
    ADD     A,OSTaskID
    MOV     R1,A
    MOV     A,@R1
    SETB    C
    ;SUBB    A,sp
    SUBB    A,r2
    MOV     R7,A
;         SP = (unsigned char )cp1 - 1;
    DEC     R0;
    MOV     SP,R0
;         for(i = OSTaskID+1;i < OSNextTaskID+1; i++)
;         {
;             OSTsakStackBotton[i] -= temp;
;         }
    MOV     A,OSNextTaskID
    CLR     C
    SUBB    A,OSTaskID
    MOV     R6,A
    JZ      ?C0005

    MOV     A,#LOW (OSTsakStackBotton)
    ADD     A,OSTaskID
    MOV     R1,A    
    MOV     A,R7
    CPL     A
    INC     A
    MOV     R7,A
?C0004:
    INC     R1
    MOV     A,R7
    ADD     A,@R1    
    MOV     @R1,A
    DJNZ    R6,?C0004
?C0005:
;         OSTaskID = OSNextTaskID;
    MOV     OSTaskID,OSNextTaskID
;         LoadCtx();    
    LJMP    LoadCtx
;     }
?C0001:
; 
;     if( OSNextTaskID != OSTaskID)
    MOV     A,OSNextTaskID
    XRL     A,OSTaskID
    JZ      ?C000r
;     {
;          cp2--;
;          cp1--;
;         while(cp2 != (unsigned char idata *)temp)
;         {
;             *cp2-- = *cp1--;
;         }
    ;MOV     A,R7
    ;CLR     C
    ;SUBB    A,R1
    ;MOV     R6,A
    mov     a,r0
    clr     c
    subb    a,r7
    mov     r6,a
?C0008:
    DEC     R0
    DEC     R1
    MOV     A,@R0
    MOV     @R1,A
    DJNZ    R6,?C0008
?C0009:
;         temp = OSTsakStackBotton[OSTaskID+1] - (unsigned char idata *)SP-1;
    MOV     A,#LOW (OSTsakStackBotton+01H)
    ADD     A,OSTaskID
    MOV     R1,A
    MOV     A,@R1
    SETB    C
    ;SUBB    A,SP
    SUBB    A,r2
    MOV     R7,A
;         SP = (unsigned char )OSTsakStackBotton[OSNextTaskID+1];
    MOV     A,#LOW (OSTsakStackBotton+01H)
    ADD     A,OSNextTaskID
    MOV     R1,A
    MOV     A,@R1
    MOV     SP,A
;         for(i = OSNextTaskID+1;i < OSTaskID+1; i++)
;         {
;             OSTsakStackBotton[i] += temp;
;         }

    MOV     A,OSTaskID
    CLR     C
    SUBB    A,OSNextTaskID
    JZ      ?C0011

    MOV     R6,A
    MOV     A,#LOW (OSTsakStackBotton)
    ADD     A,OSNextTaskID
    MOV     R1,A    
?C0010:
    INC     R1
    MOV     A,R7
    ADD     A,@R1    
    MOV     @R1,A
    DJNZ    R6,?C0010

?C0011:
;         OSTaskID = OSNextTaskID;        
    MOV  	OSTaskID,OSNextTaskID
;         SP--;
    DEC  	SP
;     }
?C0007:
;     LoadCtx();
    LJMP 	LoadCtx
?C000r:
IF EN_SP2  <> 0
    mov     SP,r2
ENDIF
    LJMP 	LoadCtx


    /*
void OS_TICK_ISR (void) __interrupt(OS_TIMER_ISR)
{
    //OS_INT_ENTER();                                    
    //OSTimeTick();                         
    //OSIntExit(); 
}*/

/* OS start

#ifdef MODE_1T

Mode_bit = 1
#endif

TMOD = 0  // mode 0, 16 bit auto reload
TL0= T1MS
TH0=T1MS >> 8
TR0=1 // start runing
EA = 1

*/