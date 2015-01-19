/*
 * =====================================================================================
 *
 *       Filename:  vfork2.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  01/18/2015 20:58:53
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int glob = 1;

int main(void) {
    int var;
    int pid;
    var = 88;
    if ((pid = vfork()) < 0) {
        printf("vfork error");
        exit(-1);
    } else if (pid == 0) { /* 子进程 */
        var++;
        _exit(0);
    }
    printf("pid=%d, glob=%d, var=%d\n", getpid(), glob, var);
    return 0;
}
