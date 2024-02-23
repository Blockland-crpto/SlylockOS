#include <shell.h>
#include <fs.h>
#include <screen.h>
#include <gui.h>
#include <keyboard.h>


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