#include <includes.h>
/* Configuracion global de las tareas */
/* variables globales */
INT16U err;
/* Comunicacion de tareas */
OS_EVENT *getimg;
OS_EVENT *saveimg;
OS_EVENT *drawHist;

#define   TASK_STACKSIZE       2048
OS_STK    initialize_task_stk[TASK_STACKSIZE];
OS_STK    image_task_stk[TASK_STACKSIZE];
OS_STK    save_task_stk[TASK_STACKSIZE];
OS_STK    poll_task_stk[TASK_STACKSIZE];
OS_STK    hist_task_stk[TASK_STACKSIZE];


// Prioridades
#define INITIALIZE_TASK_PRIORITY   6
#define IMAGE_TASK_PRIORITY   15
#define SAVE_TASK_PRIORITY   16
#define POLL_TASK_PRIORITY	18
#define HIST_TASK_PRIORITY 17

/* Lanza la tarea que crea el resto.
 * Esta tarea debe autodestruirse al iniciar a las dem�s */
void CreateTasks (void);
void TaskInit(void* pdata);
int initCreateTasks();
