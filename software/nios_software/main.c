#include "inc/task_config.h"
#include "inc/app_config.h"

int main(void)
{
	//En app_config
	Init_App();
	//En task_config
	CreateTasks();

	OSStart();

	return 0;
}
