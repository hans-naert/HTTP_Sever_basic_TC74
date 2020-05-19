#include "cmsis_os2.h"                                           // CMSIS RTOS header file
 
 #include "Board_LED.h" 
 static int timer_cnt = 0;
 uint8_t Temperatuur;
 extern uint32_t Temp_Read();
/*----------------------------------------------------------------------------
 *      Timer: Sample timer functions
 *---------------------------------------------------------------------------*/
 
/*----- One-Shoot Timer Example -----*/
static void Timer1_Callback (void const *arg);                  // prototype for timer callback function
 
osTimerId_t tim_id1;                                            // timer id
static uint32_t  exec1;                                         // argument for the timer call back function

// One-Shoot Timer Function
static void Timer1_Callback (void const *arg) {
  // add user code here
}
 
/*----- Periodic Timer Example -----*/
static void Timer2_Callback (void const *arg);                  // prototype for timer callback function
 
osTimerId_t tim_id2;                                            // timer id
static uint32_t  exec2;                                         // argument for the timer call back function
 
// Periodic Timer Example
static void Timer2_Callback (void const *arg) {
  // add user code here
//	timer_cnt++; 
//	if (timer_cnt & 1) 
//		LED_On (0); 
//	else LED_Off(0);
	Temp_Read(&Temperatuur);
}
 
// Example: Create and Start timers
int Init_Timers (void) {
  osStatus_t status;                                            // function return status
 
  // Create one-shoot timer
  exec1 = 1;
  tim_id1 = osTimerNew ((osTimerFunc_t)&Timer1_Callback, osTimerOnce, &exec1, NULL);
  if (tim_id1 != NULL) {    // One-shot timer created
    // start timer with delay 100ms
    status = osTimerStart (tim_id1, 100);            
    if (status != osOK) {
      return -1;
    }
  }
 
  // Create periodic timer
  exec2 = 2;
  tim_id2 = osTimerNew((osTimerFunc_t)&Timer2_Callback, osTimerPeriodic, &exec2, NULL);
  if (tim_id2 != NULL) {    // Periodic timer created
    // start timer with periodic 1000ms interval
    status = osTimerStart (tim_id2, 1000);            
    if (status != osOK) {
      return -1;
    }
  }
  return NULL;
}
