


#ifndef TIMER0_INT_H_
#define TIMER0_INT_H_

void TIMER0_voidInitializtion(void);
void TIMER0_voidTimerStart(void);
void TIMER0_voidTimerStop(void);


/* timer0 normal mode*/
#if (TIMER0_MODE == TIMER0_NORMAL_MODE)

void TIMER0_voidSetDesiredTime_ms(u32 Copy_Time_ms);
void TIMER0_voidSetDesiredTime_us(u32 Copy_Time_us);

/* timer0 over flow interrupt */
void TIMER0_voidOverFlowCallBack(void(*Copy_ptr)(void));


/* timer0 CTC Mode */
#elif (TIMER0_MODE == TIMER0_CTC_MODE)

void TIMER0_voidSetDesiredTime_ms(u32 Copy_Time_ms);
void TIMER0_voidSetDesiredTime_us(u32 Copy_Time_us);
#endif



#endif  /* TIMER0_INT_H_ */
