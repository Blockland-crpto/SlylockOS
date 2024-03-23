#ifndef __SYS_WAIT_H__
#define __SYS_WAIT_H__

#define WEXITSTATUS(status) (((status) & 0xff00) >> 8)
#define WIFEXITED(status) (((status) & 0x7f) == 0)
#define WIFSIGNALED(status) (((status) & 0x7f) && !WIFSTOPPED(status))
#define WIFSTOPPED(status) (((status) & 0xff) == 0x7f)
#define WNOHANG 1
#define WSTOPSIG(status) (((status) & 0xff00) >> 8)
#define WTERMSIG(status) (((status) & 0x7f))
#define WUNTRACED 2

#endif