#include <stdio.h>
#include "../inc/task_config.h"
#include "../inc/alt_ucosii_simple_error_check.h"
#include "ucos_ii.h"

void CreateTasks (void){
	INT8U return_code = OS_NO_ERR;
	return_code= OSTaskCreateExt(TaskInit,
		                  NULL,
		                  (void *)&initialize_task_stk[TASK_STACKSIZE-1],
						  INITIALIZE_TASK_PRIORITY,
						  INITIALIZE_TASK_PRIORITY,
						  initialize_task_stk,
		                  TASK_STACKSIZE,
		                  NULL,
		                  0);

	alt_ucosii_check_return_code(return_code);
}

void TaskInit(void* pdata)
{
  INT8U return_code = OS_NO_ERR;
  while (1)
  {
		OSSchedLock();	 /* entramos en seccion critica*/
		printf("Hola, soy la tarea inicial\n");
		OSSchedUnlock(); /* salimos SC */
	    /*create os data structures */
	    //initOSDataStructs();

	    /* create the tasks */
	    initCreateTasks();

	    /*This task is deleted because there is no need for it to run again */
	    return_code = OSTaskDel(OS_PRIO_SELF);
	    alt_ucosii_check_return_code(return_code);
  }
}

int initCreateTasks(){
  return 0;
}
