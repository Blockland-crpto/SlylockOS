#include <modules.h>
#include <shell.h>
#include <timer.h>
#include <ports.h>
#include <string.h>
#include <memory.h>
#include <fs.h>
#include <panic.h>
#include <screen.h>
#include <gui.h>
#include <kernel.h>
#include <drivers/acpi.h>
#include <drivers/video.h>
#include <drivers/cpuid.h>
#include <keyboard.h>

#define NULL ((char *)0)

int cf = 1;
int dfs = 1;
void shell_init(){
	module_t modules_shell_shell = MODULE("kernel.modules.shell.shell", "User command line for the kernel (CORE)");
	char** deps;
	deps[0] = "kernel.modules.timer.timer";
	DEPS(modules_shell_shell, deps);
	INIT(modules_shell_shell);
}

void shell(char s[], int i){
	char* start = "";
	char* two = "";
	char* cmdnamee_dup = "";
	strcpy(start, s);
	strcpy(two, s);
  char* cmdnamee = strtok(start, " ");
	strcpy(cmdnamee_dup, cmdnamee);
  if(strcmp(s, "clear")==0){
  	clear_scr();
  } else if(strcmp(s, "help")==0){ // print help information
    avaliable_commands(1);
  } else if(strcmp(s, "about")==0){ // print info about computer
  	about(1);
  } else if(strcmp(s, "reboot")==0){ // reboot computer
  	reboot();
  } else if(strcmp(s, "shutdown")==0){ // shutdown computer
    shutdown();
  } else if(strcmp(cmdnamee, "ls")==0) { // list files and kprintf it
    ls(0, LS_APP_ID, 1);
  } else if(strcmp(cmdnamee, "cat")==0) { // read file and kprintf it
	
	textbox("cat", "Enter the file location", CAT_APP_ID);
	//cat(cmdnamee_dup);
  } else if(strcmp(cmdnamee, "\\\/")==0 || strcmp(s, "")==0) { // comment
  } else { // unknown command 
  }

  for(int j=0; s[j]!='\0'; j++){
  	s[j]='\0';
  }
  // strcat(strcat(strcat(strcat("[", username), "("), errorcode), ")]$")
  kprintf(">");
}

void clear_scr(){
  clear(COLOR_WHT, COLOR_BLK);
  set_cursor_pos(0,0);
}