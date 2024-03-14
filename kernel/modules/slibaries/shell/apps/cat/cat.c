#include <slibaries/shell.h>
#include <drivers/fs/fs.h>
#include <drivers/vga.h>
#include <libtui.h>
#include <system/kernel.h>

void cat(char s[]) {

  lastcatfile = s;

  char buf[4096];
  fs_node_t *fsnode = finddir_fs(fs_root, s);
  uint32_t sz = read_fs(fsnode, 0, 4096, buf);

 
  make_tui(themeindex, themeindex, 0, 2);
  make_tui_windows("Cat", buf, 4, 3, 70, 20);
  int j;
  for (j = 0; j < sz; j++) {
	putstrpos(buf[j], 7, 6, 8, 7, 7);
  }
}