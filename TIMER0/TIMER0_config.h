
#ifndef TIMER0_CONFIG_H_
#define TIMER0_CONFIG_H_

#define TIMER0_F_CPU                16000000UL

/*
 *   choose prescaler form
 *   no_prescaller - prescaller_8 - prescaller_64 - prescaller_256
 *   prescaller_1024
 */
#define TIMER0_PRESCALER            prescaller_1024

/*
 *  choose Mode:
 *  TIMER0_NORMAL_MODE - TIMER0_CTC_MODE - TIMER0_PHASE_CORCT_MODE
 *  TIMER0_FAST_PWM_MODE 
 */
#define TIMER0_MODE                  TIMER0_NORMAL_MODE

#define TIMER0_INTERRUPT_STATUS      TIMER0_INT_ENABLED

/*
 *  Choose timer0 OC0 mode:
 * with PWM mode:
 * TIMER0_DISCONNECT_OC0 - TIMER0_PWM_NONINVERTED_OC0 - TIMER0_PWM_
 */
#define TIMER0_OC0_MODE             TIMER0_DISCONNECT_OC0  

#define TIMER0_OCR0_VALUE           200







#endif  /* TIMER0_CONFIG_H_ */
