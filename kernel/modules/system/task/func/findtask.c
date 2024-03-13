#include <system/task.h>
#include <string.h>

task_t find_task(char* name) {

	for (int i = 0; i < 256; i++) {
		if (strcmp(taskpool[i].name, name) == 0) {
			return taskpool[i];
		}
	}
}