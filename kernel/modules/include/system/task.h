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

//thought being a monotasking system, we still want the OS to be able to give us useful info about the current running in the event of a error

//a sturcture for a task
typedef struct {
	char* name;
	char* state;
	int id;
	int priority;
	int caller;
} task_t;

//the amount of currently running tasks
int running_tasks;

//the task pool
task_t taskpool[15];

//task init
void task_init();

//a task creator
task_t create_task(char* name, int priority, int caller, int id);

//a function to modify running tasks
void modify_task(task_t task, int state);

#endif