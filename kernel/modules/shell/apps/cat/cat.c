#include <shell.h>
#include <fs.h>
#include <screen.h>
#include <gui.h>

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