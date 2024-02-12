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
#include <screen.h>
#include <gui.h>

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
void avaliable_commands(int page){
  char helpstrpgo[235] ="Avaliable Commands\n\n`help` Shows this screen.\n\n`clear` Clears the screen\n\n`about` Shows information about the OS.\n\n`reboot` Reboots the computer.\n\n`cat <[Any] file>` Prints the contents of the file `file`.\n\nPress enter to continue";
  char helpstrpgt[200] = "Avaliable Commands\n\n`ls` Prints a list of all the files and directories\n in the current directory.\n\n`shutdown` Shuts down the computer.\n\nPress enter to continue";
  if (page == 1) {
	userinputmode = HELP_APP_ID;
	make_gui(3, 3, 1);
	make_gui_windows("", helpstrpgo, 3, 3, 70, 22);
  } else if (page == 2) {
	userinputmode = HELP_APP_ID_TW;
	make_gui(3, 3, 2);
	make_gui_windows("", helpstrpgt, 3, 3, 70, 22);
  }

}


void about(int page) {
  char aboutstr[220] = "MiniOS\nA Operating System written in C\nand ASM for lightweight computers.\n\nKernel Version: v1.0.0\nShell Version: v1.0.0\n\nMade Possible by:\n1. Abrid OS\n2. OSDEV.org\nThank you!\nPress Enter To Continue..."; 
  char buf;


  if (page == 1) {
	userinputmode = ABOUT_APP_ID;
	clear_scr();
	make_gui(3, 3, 1);
	make_gui_windows("About OS:", aboutstr, 4, 3, 70, 22);
  } else if (page == 2) {
	 char aboutstrt[180] = "Hardware:\n\nRAM: "; 
	 strcat(aboutstrt, itoa(ram_size(), buf, 10));
	 strcat(aboutstrt, "\nUptime: ");
	 strcat(aboutstrt, itoa(get_tracked_seconds(), buf, 10));
     userinputmode = ABOUT_APP_ID_TW;
	 make_gui(3, 3, 2);
	 make_gui_windows("About OS:", aboutstrt, 4, 3, 70, 22);
  }
  return 0;
}


void shutdown() {
  clear_scr();

  make_gui(3, 3, 0);

  make_gui_windows("Shutting Down...", "Its safe to turn off your computer now", 19, 10, 60, 20);
  
  asm volatile("hlt");
}


/**       LS command        **/
void ls(int start, int id, int page) {
  userinputmode = id;
  struct dirent *node = 0;
  int i= start;
  make_gui(3, 3, page);
  make_gui_windows("LS", " ", 4, 3, 70, 22);
  for (int j = 5; j < 21; j++) {
	while ( (node = readdir_fs(fs_root, i)) != 0 && j < 21)
	{
		fs_node_t *fsnode = finddir_fs(fs_root, node->name);
		putstrpos(node->name, 7, j, 8, 7, 7);
		if(((fsnode->flags&0x7) == FS_DIRECTORY)) 
		{
			putstrpos("/", 7, j, 8, 7, 7);
		}
		putstrpos("\n", 7, j, 8, 7, 7);
		i++;
		j++;
	} 
  }
}

void cat(char s[]) {
  
  
  char buf[4096];
  fs_node_t *fsnode = finddir_fs(fs_root, s);
  uint32_t sz = read_fs(fsnode, 0, 4096, buf);

  make_gui(3, 3, 0);
  make_gui_windows("Cat", buf, 4, 3, 70, 22);
  int j;
  for (j = 0; j < sz; j++) {
	putstrpos(buf[j], 7, 6, 8, 7, 7);
  }
}