#include <includes.h>
/* Configuracion global de las tareas */
/* variables globales */
INT16U err;
/* Comunicacion de tareas */
OS_EVENT *getimg;
OS_EVENT *saveimg;

#define   TASK_STACKSIZE       2048
OS_STK    initialize_task_stk[TASK_STACKSIZE];
OS_STK    image_task_stk[TASK_STACKSIZE];
OS_STK    save_task_stk[TASK_STACKSIZE];

// Prioridades
#define INITIALIZE_TASK_PRIORITY   6
#define IMAGE_TASK_PRIORITY   15
#define SAVE_TASK_PRIORITY   16

/* Lanza la tarea que crea el resto.
 * Esta tarea debe autodestruirse al iniciar a las dem�s */
void CreateTasks (void);
void TaskInit(void* pdata);
int initCreateTasks();
