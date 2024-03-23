#include <stdio.h>
#include <string.h>

char *tmpnam(char *s) {
	char *str;
	fs_node_t *exists0 = finddir_fs(fs_root, "tmpfile0");
	if (exists0 == NULL) {
		strcat(s, "tmpfile0");
		return s; 
	}
	fs_node_t *exists1 = finddir_fs(fs_root, "tmpfile1");
	if (exists1 == NULL) {
		strcat(s, "tmpfile1");
		return s; 
	}
	fs_node_t *exists2 = finddir_fs(fs_root, "tmpfile2");
	if (exists2 == NULL) {
		strcat(s, "tmpfile2");
		return s; 
	}
	fs_node_t *exists3 = finddir_fs(fs_root, "tmpfile3");
	if (exists3 == NULL) {
		strcat(s, "tmpfile3");
		return s; 
	}
	fs_node_t *exists4 = finddir_fs(fs_root, "tmpfile4");
	if (exists4 == NULL) {
		strcat(s, "tmpfile4");
		return s; 
	}
}