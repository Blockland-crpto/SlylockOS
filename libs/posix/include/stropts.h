/*
* Author: Alexander Herbert <herbgamerwow@gmail.com>
* License: MIT
*
* Permission is hereby granted, free of charge, to any person obtaining a copy of this 
* software and associated documentation files (the “Software”), to deal in the Software
* without restriction, including without limitation the rights to use, copy, modify, merge,
* publish, distribute, sublicense, and/or sell copies of the Software, and to permit 
* persons to whom the Software is furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in 
* all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
* INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR
* PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE
* FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
* OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR 
* OTHER DEALINGS IN THE SOFTWARE.
*/
#ifndef __STROPTS_H
#define __STROPTS_H


//In progress

#define FMNAMESZ 128

//i flush stuff
enum i_flush_data {
	FLUSHR = 3,
	FLUSHW = 4,
	FLUSHRW = 3
};

//i setsig stuff
enum i_setsig_data {
	S_BANDURG,
	S_ERROR,
	S_HANGUP,
	S_HIPRI,
	S_INPUT,
	S_MSG,
	S_OUTPUT,
	S_RDBAND,
	S_RDNORM,
	S_WRBAND,
	S_WRNORM
};

enum i_peek_data {
	RS_HIPRI
};

enum i_srdopt_data {
	RMSGD,
	RMSGN,
	RNORM,
	RPROTDAT,
	RPROTDIS,
	RPROTNORM
};

enum i_swopt_data {
	SNDZERO
};

enum i_atmark_data {
	ANYMARK,
	LASTMARK
};

enum i_unlink_data {
	MUXID_ALL
};

enum msg_data {
	MORECTL,
	MOREDATA,
	MSG_ANY,
	MSG_BAND,
	MSG_HIPRI
};

enum {
	I_ATMARK = 0,
	I_CANPUT = 1,
	I_CKBAND = 2,
	I_FDINSERT = 3,
	I_FIND = 4,
	I_FLUSH = 5,
	I_FLUSHBAND = 6,
	I_GETBAND = 7,
	I_GETCLTIME = 8,
	I_GETSIG = 9,
	I_GRDOPT = 10,
	I_GWROPT = 11,
	I_LINK = 12,
	I_LIST = 13,
	I_LOOK = 14,
	I_NREAD = 15,
	I_PEEK = 16,
	I_PLINK = 17,
	I_POP = 18,
	I_PUNLINK = 19,
	I_PUSH = 20,
	I_RECVFD = 21,
	I_SENDFD = 22,
	I_SETCLTIME = 23,
	I_SETSIG = 24,
	I_SRDOPT = 25,
	I_STR = 26,
	I_SWROPT = 27,
	I_UNLINK = 28
};

#if defined(__cplusplus)
extern "C" {
#endif

	typedef int t_scalar_t;
	typedef unsigned int t_uscalar_t;
	typedef int gid_t;
	typedef int uid_t;
	
	struct bandinfo {
		int bi_flag;
		unsigned char bi_pri;
	};

	struct strbuf {
		char* buf;
		int len;
		int maxlen;
	};
	
	struct strpeek {
		struct strbuf ctlbuf;
		struct strbuf databuf;
		t_uscalar_t flags;
	};

	struct strfdinsert {
		struct strbuf ctlbuf;
		struct strbuf datauf;
		int fildes;
		t_uscalar_t flags;
		int offset;
	};

	struct strioctl {
		int ic_cmd;
		char* ic_dp;
		int ic_len;
		int ic_timeout;
	};

	struct strrecvfs {
		int fd;
		gid_t gid;
		uid_t uid;
	};

	struct str_mlist {
		char l_name[FMNAMESZ+1];
	};

	struct str_list {
		struct str_mlist *sl_modlist;
		int sl_nmods;
	};
	
	
#if defined(__cplusplus)
} /* extern "C" */
#endif

#endif
