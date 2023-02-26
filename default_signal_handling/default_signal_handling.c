#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

/* Choose ONE of the examples below */

/* child ends normally with it's return code */
#define EXAMPLE_CHILD_EXIT_NORMALLY

/* child ends with segmentation fault */
//#define EXAMPLE_CHILD_SIGSEGV

/* child ends with floating point fault */
//#define EXAMPLE_CHILD_SIGFPE

/* child is killed with "kill" command. Ex: "kill -TERM 8626" | "kill -HUP 8806"
 */
//#define EXAMPLE_CHILD_KILL


int main(int argc, char **argv)
{
  int status;
  int a, b, c;

  if (fork())
  {
    /* Parent */
    wait(&status);
    if (WIFEXITED(status))
    {
      printf("[PARENT] Child exited normally with exit status: %d\n",
             WEXITSTATUS(status));
    }
    if (WIFSIGNALED(status))
    {
      printf("[PARENT] Child exited on signal: %d - %s\n", WTERMSIG(status),
             strsignal(WTERMSIG(status)));
    }
  }
  else
  {
    /* Child */
    printf("[CHILD] PID: %d\n", getpid());
#if defined EXAMPLE_CHILD_EXIT_NORMALLY
    sleep(3);
#elif defined EXAMPLE_CHILD_SIGSEGV
    *(int *) 0 = 99;
#elif defined EXAMPLE_CHILD_SIGFPE
    a = 1;
    b = 0;
    c = a / b;
#elif defined EXAMPLE_CHILD_KILL
    pause();
#endif
    exit(5);
  }

  return 0;
}