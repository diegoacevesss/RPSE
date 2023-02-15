/*
 * proyect_task.h
 *
 *  Created on: 7 feb 2023
 *      Author: garci
 */

#ifndef PROYECT_TASK_H_
#define PROYECT_TASK_H_

/* Fwk */
#include "TimersManager.h"
#include "FunctionLib.h"
#include "LED.h"
/* KSDK */
#include "fsl_common.h"
#include "EmbeddedTypes.h"
#include "fsl_os_abstraction.h"

#define gMyTaskPriority_c 	3
#define gMyTaskStackSize_c 	400

#define WAIT_TIME 3000

/* Define the available Task's Events */
#define gTimer_init_event_c (1 << 0)
#define gSW3TaskEvent_c 	(1 << 1)
#define gSW4TaskEvent_c 	(1 << 2)
#define gTimerStop_c 		(1 << 3)
#define gTimer_task_event_c (1 << 4)

//Task prototype definition
void MyTaskTimer_Start(void);
void MyTaskTimer_Stop(void);
void Proyect_task_Init(void);

void sw3_function(void);
void sw4_function(void);

void myTaskTimerCallback(void *param);

/* Main custom task */
void Proyect_task(osaTaskParam_t argument);

void timer_callback(void);

void set_funtion_pointer(void (*ptr)(void));

uint8_t* get_message_to_send(void);


#endif /* PROYECT_TASK_H_ */
