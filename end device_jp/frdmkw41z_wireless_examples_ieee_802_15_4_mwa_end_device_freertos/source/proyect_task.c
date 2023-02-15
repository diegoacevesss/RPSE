/*
 * proyect_task.c
 *
 *  Created on: 7 feb 2023
 *      Author: garci
 */

#include "proyect_task.h"

void (*set_event_ptr)(void);

/*Variables */
osaEventId_t    Proyect_events;
/* Global Variable to store our TimerID */
tmrTimerID_t proyect_timer = gTmrInvalidTimerID_c;
/* Handler ID for task */
osaTaskId_t gMyTaskHandler_ID;

static uint8_t counter = '4';


/*Definitions*/
/* OSA Task Definition*/
OSA_TASK_DEFINE(Proyect_task, gMyTaskPriority_c, 1, gMyTaskStackSize_c, FALSE );



/* Main custom task */
void Proyect_task(osaTaskParam_t argument)
{
	osaEventFlags_t customEvent;
	proyect_timer = TMR_AllocateTimer();

while(1)
{

	OSA_EventWait(Proyect_events, osaEventFlagsAll_c, FALSE, osaWaitForever_c,
	&customEvent);
	TurnOffLeds(); /* Ensure all LEDs are turned off */
	  /* Depending on the received event */
	  switch(customEvent){
		  case gTimer_init_event_c:
		   TMR_StartIntervalTimer(proyect_timer, /*myTimerID*/
				   WAIT_TIME, /* Timer's Timeout */
			 myTaskTimerCallback, /* pointer to
		myTaskTimerCallback function */
			 NULL
		   );
		   TurnOffLeds(); /* Ensure all LEDs are turned off */
		   break;

		  case gSW3TaskEvent_c: /* Event called from myTaskTimerCallback */
			  counter = '2';
			   TMR_StartIntervalTimer(proyect_timer, /*myTimerID*/
					   WAIT_TIME, /* Timer's Timeout */
				 myTaskTimerCallback, /* pointer to
			myTaskTimerCallback function */
				 NULL
			   );
			   Led_TurnOn(LED4);//Turn on green led
			   set_event_ptr();
		   break;

		  case gSW4TaskEvent_c:
			  counter = '1';
			   TMR_StartIntervalTimer(proyect_timer, /*myTimerID*/
					   WAIT_TIME, /* Timer's Timeout */
				 myTaskTimerCallback, /* pointer to
			myTaskTimerCallback function */
				 NULL
			   );
			   set_event_ptr();
			   Led_TurnOn(LED3);//Turn on green led
			  break;

		  case gTimerStop_c: /* Event to stop the timer */
		   TurnOffLeds();

		   TMR_StopTimer(proyect_timer);
		   break;

		  case gTimer_task_event_c:
				  counter++;
				  if('3' < counter) counter = '0';
				  TurnOffLeds();
				  switch(counter)
				  {
					  case '0':
						  Led_TurnOn(LED2);//Turn on red led

						  break;
					  case '1':
						  Led_TurnOn(LED3);//Turn on green led

						  break;
					  case '2':
						  Led_TurnOn(LED4);//Turn on blue led

						  break;
					  case '3':
						  Led_TurnOn(LED2);//Turn on all RGB LEDs
						  Led_TurnOn(LED3);
						  Led_TurnOn(LED4);

					  break;

					  default:
					  break;
				  }

				  //let the app there is something to process
				  set_event_ptr();
			  break;

		  default:
		   break;
	  }
	}
}

void Proyect_task_Init(void)
{
	Proyect_events = OSA_EventCreate(TRUE);
	/* The instance of the MAC is passed at task creaton */
	gMyTaskHandler_ID = OSA_TaskCreate(OSA_TASK(Proyect_task), NULL);
}

/*Defined Prototyped*/
/* This is the function called by the Timer each time it expires */
void myTaskTimerCallback(void *param)
{
	OSA_EventSet(Proyect_events, gTimer_task_event_c);
}

/* Public function to send an event to stop the timer */
void MyTaskTimer_Stop(void)
{
	OSA_EventSet(Proyect_events, gTimerStop_c);
}

void MyTaskTimer_Start(void)
{
	OSA_EventSet(Proyect_events, gTimer_init_event_c);
}

void sw3_function(void)
{
	OSA_EventSet(Proyect_events, gSW3TaskEvent_c);
}

void sw4_function(void)
{
	OSA_EventSet(Proyect_events, gSW4TaskEvent_c);
}

void set_funtion_pointer(void (*ptr)(void))
{
	set_event_ptr = ptr;
}

uint8_t* get_message_to_send(void)
{
	return &counter;
}
