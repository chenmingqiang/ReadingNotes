# vfork and fork, exit and return

## vfork注意问题

下面是man fork的输出

     Vfork() can be used to create new processes without fully copying the address space of the old process, which is horren-
     dously inefficient in a paged environment.  It is useful when the purpose of fork(2) would have been to create a new system
     context for an execve.  Vfork() differs from fork in that the child borrows the parent's memory and thread of control until
     a call to execve(2) or an exit (either by a call to exit(2) or abnormally.)  The parent process is suspended while the
     child is using its resources.

     Vfork() returns 0 in the child's context and (later) the pid of the child in the parent's context.

     Vfork() can normally be used just like fork.  It does not work, however, to return while running in the childs context from
     the procedure that called vfork() since the eventual return from vfork() would then return to a no longer existent stack
     frame.  Be careful, also, to call _exit rather than exit if you can't execve, since exit will flush and close standard I/O
     channels, and thereby mess up the parent processes standard I/O data structures.  (Even with fork it is wrong to call exit
     since buffered data would then be flushed twice.)

从上面的文字，我们可看到vfork又如下特点:
1. 常用来执行exec系统调用
2. 子进程先于父进程运行,并且子进程借用父进程的内存以及控制线程
3. 不能在子进程中调用return
4. 在vfork或者fork中不要调用exit，应该调用_exit

现面3个程序，在vfork的子进程中分别调用了return, _exit, 以及execve


    #include <stdio.h>
    #include <stdlib.h>
    #include <unistd.h>
    int main(void) {
        int var;
        var = 88;
        if ((pid = vfork()) < 0) {
            printf("vfork error");
            exit(-1);
        } else if (pid == 0) { /* 子进程 */
            var++;
            return 0;
        }
        printf("pid=%d, glob=%d, var=%d\n", getpid(), glob, var);
        return 0;
    }

输出:

    pid=22110, glob=1, var=0
    Segmentation fault: 11


    #include <stdio.h>
    #include <stdlib.h>
    #include <unistd.h>

    int glob = 1;

    int main(int argc, char *argv[]) {
        int var;
        int pid;
        var = 88;
        if ((pid = vfork()) < 0) {
            printf("vfork error");
            exit(-1);
        } else if (pid == 0) { /* 子进程 */
            var++;
            execve("/bin/echo", argv, NULL);
        }
        printf("pid=%d, glob=%d, var=%d\n", getpid(), glob, var);

        return 0;
    }

当参数为"hello world" 输出 :
    
    pid=22087, glob=1, var=89
    hello world

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

输出:

    pid=22087, glob=1, var=89

上面两个正常的输出中，var都为89，说明子进程和父进程共享内存

## 参考

[1] http://coolshell.cn/articles/12103.html#more-12103
