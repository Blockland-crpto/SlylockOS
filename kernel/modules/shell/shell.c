#include <modules.h>
#include <shell.h>
#include <timer.h>
#include <ports.h>
#include <string.h>
#include <memory.h>
#include <fs.h>
#include <panic.h>
#include <screen.h>
#include <kernel.h>
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
    avaliable_commands();
  } else if(strcmp(s, "about")==0){ // print info about computer
  	about();
  } else if(strcmp(s, "reboot")==0){ // reboot computer
  	reboot();
  } else if(strcmp(s, "shutdown")==0){ // shutdown computer
    shutdown();
  } else if(strcmp(cmdnamee, "ls")==0) { // list files and kprintf it
	  ls();
  } else if(strcmp(cmdnamee, "cat")==0) { // read file and kprintf it
    cat(cmdnamee_dup);
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

void reboot(){
    clear_scr();
  	kprintf("Rebooting...\n");
  	//using 8042 keyboard controller to pulse the CPU's RESET Pin
  	unsigned char temp = 0x02;
  	while(temp & 0x02)
  		temp = in_port_byte(0x64);
  	out_port_byte(0x64, 0xFE);
  	asm volatile("hlt");	
}

//Help main page
void avaliable_commands(){
  userinputmode = HELP_APP_ID;
  char helpstr[350] = "`help` Shows this screen.\n\n`clear` Clears the screen\n\n`about` Shows information about the OS.\n\n`reboot` Reboots the computer.\n\n`cat <[Any] file>` Prints the contents of the file `file`.\n\nPress tab to continue";
  
  make_gui("Help", 3, 3, 1, 0);
  make_gui_windows("Avaliable Commands:", helpstr, 3, 3, 70, 22);
}

//Help second page
void avaliable_commands_two(){
  userinputmode = HELP_APP_ID_TW;
  char helpstr[300] = "`ls` Prints a list of all the files and directories\n in the current directory.\n\n`shutdown` Shuts down the computer.\n\nPress tab to continue";

  make_gui("Help", 3, 3, 1, 1);
  make_gui_windows("Avaliable Commands:", helpstr, 3, 3, 70, 22);
}

void about() {
  char *buf;
  char aboutstr[300];
  userinputmode = ABOUT_APP_ID;
  strcat(aboutstr, "MiniOS\nA Operating System written in C\nand ASM for lightweight computers.\n");
  
  strcat(aboutstr, "Ram Size: ");
  strcat(aboutstr, itoa(ram_size(), buf, 10));
  strcat(aboutstr, " Bytes\n");
  
  strcat(aboutstr, "Uptime: ");
  strcat(aboutstr, itoa(get_tracked_seconds(), buf, 10));
  strcat(aboutstr, " Seconds\n");
  
  strcat(aboutstr, "Kernel Version: ");
  strcat(aboutstr, KERNEL_VERSION);
  
  strcat(aboutstr, "Shell Version: ");
  strcat(aboutstr, SHELL_VERSION);

  strcat(aboutstr, CREDITS);
  
  clear_scr();
 
  make_gui("About", 3, 3, 0, 0);

  make_gui_windows("About OS:", aboutstr, 4, 3, 70, 22);
  
  for (int i = 0; i < strlen(aboutstr); i++) {
    aboutstr[i] = '\0';
  }
}

void shutdown() {
  clear_scr();

  make_gui("Shutdown", 3, 3, 0, 0);

  make_gui_windows("Shutting Down...", "Its safe to turn off your computer now", 19, 10, 60, 20);
  
  asm volatile("hlt");
}

void ls() {
  userinputmode = LS_APP_ID;
  struct dirent *node = 0;
  int i=0;
  while ( (node = readdir_fs(fs_root, i)) != 0)
  {
    fs_node_t *fsnode = finddir_fs(fs_root, node->name);
    kprintf(node->name);
    if(((fsnode->flags&0x7) == FS_DIRECTORY)) 
    {
      kprintf("/");
    }
    kprintf("\n");
    i++;
    
  } 
  kprintf("Press Tab To Continue...");
}

void cat(char s[]) {
  userinputmode = CAT_APP_ID;
  char buf[4096];
  fs_node_t *fsnode = finddir_fs(fs_root, strtok(s, " "));
  uint32_t sz = read_fs(fsnode, 0, 4096, buf);
  int j;
  for (j = 0; j < sz; j++)
    kprintc(buf[j]);
  kprintf("\n");
  kprintf("Press Tab To Continue...");
}