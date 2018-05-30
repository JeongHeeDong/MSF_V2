
#ifndef __CMISC_H__
#define __CMISC_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <unistd.h>
#include <string>
#include <netdb.h>
#include <ctype.h>

/**
 * Directory scan�� �ʿ��� ����ü\n
 * ���� ������ �����ϴ� ����ü.
 */
typedef struct _st_scan_dir {
    char fullpath[256];
    char filename[256];
    struct stat sbuf;
}st_scan_dir;

/**
 * �־��� �޽����� delimeter�� ���� �и��س��� �Լ�.
 */
int hrsplit(char *msg, char *del, char data[][1024]);
/**
 * �Ϲ� ���μ����� ���� ���μ����� ��ȯ�ϴ� �Լ�.
 *	@param �Ľ��� ���ڿ�.
 *	@param delimeter.
 *	@param �Ľ̵� �����Ͱ� ����� �����.
 *	@return �Ľ̵� ������ ����.
 */
void initDaemonProc();
/**
 *	���� �ð� ������ ������ �Լ�.
 *	@param seconds.
 *	@param micro seconds.
 */
void getTime(unsigned long *sec, unsigned long *usec);
/**
 *	sleep function for milli seconds.
 *	@param milli seconds.
 */
void msleep(unsigned long milliseconds);
/**
 *	directory scan�� ���� ���� �Լ�.
 *	@param previous file.
 *	@param next file.
 *	@return 1 if s1 > s2, 0 if s1 == s2, -1 if s1 < s2
 */
int sortScanDir(const void *s1, const void *s2);
/**
 *	directory scan �Լ�.
 *	@param scan�� directory.
 *	@param scan�� directory�� ���� ����Ʈ.
 *	@param scan�� ���� ����Ʈ�� �����ϴ� �Լ� ������.
 *	@return scan�� ���� ����.
 */
int scanDir(char *dir, st_scan_dir **namelist, int (*handler)(const void *, const void *));
/**
 *	ȣ��Ʈ IP �ּҸ� ������ �Լ�.
 *	@param ���� IP address ���ڿ�.
 *	@return -1 if error occurred, else success.
 */
int gethostipaddr(char *haddr);
/**
 *	Shell command�� ������ �� ������� ������ �Լ�.
 *	@param shell command.
 *	@param mode("r", "w", "r+", "w+", ...)
 *	@return NULL if error occurred, else return message.
 */
char *get_popen_result(char *cmd, char *mode);

#endif /* __CMISC_H__ */
