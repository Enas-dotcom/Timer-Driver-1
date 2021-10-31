
#ifndef TIMER0_PREV_H_
#define TIMER0_PREV_H_


/*************************************
 *Prescaler Macros
 *************************************/
#define No_prescaller                1
#define prescaller_8                 2
#define prescaller_64                3
#define prescaller_256               4
#define prescaller_1024              5
/*************************************
 * Timer0 Modes
 * ***********************************/
#define TIMER0_NORMAL_MODE           0
#define TIMER0_CTC_MODE              1
#define TIMER0_FAST_PWM_MODE         2
#define TIMER0_PHASE_CORCT_MODE      3
/*************************************/


/*==========================================*/
/*              OC0 Non PWM Modes */        
/*==========================================*/
#define TIMER0_DISCONNECT_OC0        0
#define TIMER0_TOGGLE_OC0            1
#define TIMER0_CLEAR_OC0             2
#define TIMER0_SET_OC0               3
/**********************************************
 *              OC0 Fast PWM                 *   
***********************************************/
#define TIMER0_PWM_INVERTED_OC0      2
#define TIMER0_PWM_NON_INVERTED_OC0  3
/*********************************************/


/****************TCCR0_REGISTER***************/
#define TIMER0_WGM00                 6
#define TIMER0_WGM01                 3
/****************TIMSK_REGISTER***************/
#define TIMER0_TOIE0                 0
#define TIMER0_OCIE0                 1
/**********************************************/

/* value to masked with TCNT to stop counter */
#define TIMER0_STOP_MASK             0xf8
#define TIMER0_TCCR0_MASK            0xf8

/* access com bits */
#define TIMER0_COM_MASK              0b11001111

#define TIMER0_SREG_I                7

#define TIMER0_REG_CAPACITY          256 

#define TIMER0_INT_ENABLED			 1
#define TIMER0_INT_DISABLE			 0


#define SREG_Bit    7






#endif  /* TIMER0_PREV_H_ */
