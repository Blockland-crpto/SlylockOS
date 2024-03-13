#ifndef __SYSTEM_TASK_H
#define __SYSTEM_TASK_H

// Task ID's
#define TASK_ID_KERNEL 0

// Task Priorities
#define TASK_PRIORITY_KERNEL 0
#define TASK_PRIORITY_APP 1

// Task States
#define TASK_STATE_STARTING 0
#define TASK_STATE_RUNNING 1
#define TASK_STATE_ENDED 2
#define TASK_STATE_ERRORED 3
#define TASK_STATE_FREE 4

//thought being a monotasking system, we still want the OS to be able to give us useful info about the current running in the event of a error and jail unauthorized apps

//a sturcture for a task
typedef struct {
	char* name;
	char* state;
	int id;
	int priority;
	int caller;
	int priviledge;
} task_t;

//a free task slot
task_t free_task;

//the amount of currently running tasks
int running_tasks;

//the id of the SLIM task
int slim_task_id;

//a array of irq handler process id's
int irq_process_id[16];

//the current task
task_t current_task;

//the task pool
task_t taskpool[256];

//task init
void task_init();

//a task creator
task_t create_task(char* name, int priority, int caller);

//a function to modify running tasks
void modify_task(int state);

//a function to find a task
task_t find_task(char* name);

#endif