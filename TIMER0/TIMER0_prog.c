
#include "STD_Types.h"
#include "BIT_Math.h"
#include "TIMER0_prev.h"
#include "TIMER0_config.h"
#include "TIMER0_int.h"

#include <avr/io.h>
#include "avr/interrupt.h"


/* timer0 interrupt ISR */

//void __vector_10 (void) __attribute__ ((signal,used)); //T1 CTC ISR
//void __vector_11 (void) __attribute__ ((signal,used)); //T0 Overflow  ISR

/* call back function */
static void (*TIMER0_OverFlowCallBackPointer) (void);
static void (*TIMER0_CTCCallBackPointer) (void);


static volatile u32 TIMER0_u32OverFlowNo    = 0;
static u8           TIMER0_u8TCNT0Preload   = 0;
static u8           TIMER0_u8TCCR0Value     = 0;
static u16          TIMER0_u16Prescaler     = 1;



void TIMER0_voidInitializtion(void)
{
    /* re check already 0 */
    /* Clear 3 bit of prescaller to stop count  */
    TIMER0_u8TCCR0Value &= TIMER0_TCCR0_MASK;
    /* Mask prescaller value */
    TIMER0_u8TCCR0Value |= TIMER0_PRESCALER;

    TIMER0_u16Prescaler = 1;
    #if(TIMER0_PRESCALER == No_prescaller)
        TIMER0_u16Prescaler = TIMER0_F_CPU/1000000;

    #elif(TIMER0_PRESCALER == prescaller_8)
        TIMER0_u16Prescaler = 8;
    
    /* set prescaller value */
    #elif(TIMER0_PRESCALER > prescaller_8 && TIMER0_PRESCALER <= prescaller_1024)

        /* calculate prescaller = 2^(2*prescaller_) */
        for(u8 i = 0; i<(TIMER0_PRESCALER*2); i++)
        {
            TIMER0_u16Prescaler *=2;
        }
    #else
        #error "Wrong Prescaller"
    #endif

    /**************************************
    *   Choose Timer0 Mode
    ****************************************/

   /* Normal Mode */
   #if (TIMER0_MODE == TIMER0_NORMAL_MODE)

        CLRBIT(TIMER0_u8TCCR0Value, TIMER0_WGM00);
        CLRBIT(TIMER0_u8TCCR0Value, TIMER0_WGM01);

        #if (TIMER0_INTERRUPT_STATUS == TIMER0_INT_ENABLED)
            /* enable global interrupt */
            SETBIT(SREG, SREG_Bit);
            /* enable timer0 overflow interrupt */
            SETBIT(TIMSK, TIMER0_TOIE0);
            #endif

    /* CTC MODE */
    #elif (TIMER0_MODE == TIMER0_CTC_MODE)

        CLRBIT(TIMER0_u8TCCR0Value, TIMER0_WGM00);
        SETBIT(TIMER0_u8TCCR0Value, TIMER0_WGM01);
        
        /* Set initial value of OCR0 as configuration */
        OCR0 = TIMER0_OCR0_VALUE;

        #if (TIMER0_INTERRUPT_STATUS == TIMER0_INT_ENABLED)
            /**/
            SETBIT(SREG, SREG_I);
            /**/
            SETBIT(TIMSK, TIMER0_OCIE0);
            #endif

    /* phase correct PWM mode */
    #elif (TIMER0_MODE == TIMER0_PHASE_CORCT_MODE)

        SETBIT(TIMER0_u8TCCR0Value, TIMER0_WGM00);
        CLRBIT(TIMER0_u8TCCR0Value, TIMER0_WGM01);

    /* fast PWM mode */
    #elif (TIMER0_MODE == TIMER0_FAST_PWM_MODE)

        SETBIT(TIMER0_u8TCCR0Value, TIMER0_WGM00);
        SETBIT(TIMER0_u8TCCR0Value, TIMER0_WGM01);
    
    #else
        #error "Wrong Timer0 Mode"

	#endif

    /* CLEAR COM00 - COM01 */
    TIMER0_u8TCCR0Value &= TIMER0_COM_MASK;
    /* SETBIT com00 */
    TIMER0_u8TCCR0Value |= (TIMER0_OC0_MODE<<4);

}   /* TIMER0_voidInitializtion */


void TIMER0_voidTimerStart(void)
{
    TCCR0 = TIMER0_u8TCCR0Value;
}   /* TIMER0_voidTimerStart */


void TIMER0_voidTimerStop(void)
{
    TCCR0 = TIMER0_u8TCCR0Value & TIMER0_STOP_MASK;
}   /* TIMER0_voidTimerStop */


void TIMER0_voidSetDesiredTime_ms(u32 Copy_Time_ms)
{
    TIMER0_voidSetDesiredTime_us(Copy_Time_ms*1000);

}   /* TIMER0_voidSetDesiredTime_ms */


void TIMER0_voidSetDesiredTime_us(u32 Copy_Time_us)
{   
    u32 Local_u32TickTime           = (TIMER0_u16Prescaler  * 1000000)/TIMER0_F_CPU;
    u32 Local_u32OverFlowTime       = Local_u32TickTime * TIMER0_REG_CAPACITY;
    u32 Local_u32DesiredTime        = Copy_Time_us;

    TIMER0_u32OverFlowNo            = Local_u32DesiredTime / Local_u32OverFlowTime;
    u32 TIMER0_u32OverRemainderTime = Local_u32DesiredTime % Local_u32OverFlowTime;
    u32 TIMER0_u32OverFlowRemCount  = ((float)TIMER0_u32OverRemainderTime / Local_u32OverFlowTime)*TIMER0_REG_CAPACITY;

    TCNT0 = 0;
    if(TIMER0_u32OverRemainderTime > 0)
    {
        TIMER0_u8TCNT0Preload =  TIMER0_REG_CAPACITY - TIMER0_u32OverFlowRemCount;
        TCNT0 = TIMER0_u8TCNT0Preload;
        TIMER0_u32OverFlowNo++;
    }

    TIMER0_voidTimerStart();

}   /* TIMER0_voidSetDesiredTime_us */


void TIMER0_voidOverFlowCallBack(void(*Copy_ptr)(void))
{
    TIMER0_OverFlowCallBackPointer = Copy_ptr;
}


ISR(TIMER0_OVF_vect)
{
    static u32 Local_u32Counter = 0;
    Local_u32Counter++;

    if(Local_u32Counter == TIMER0_u32OverFlowNo)
    {
        TIMER0_OverFlowCallBackPointer();

        Local_u32Counter = 0;
        TCNT0 = TIMER0_u8TCNT0Preload; 
        
    }
    
}
