#include <unistd.h>
#include <stdio.h>

#include <sys/prctl.h>
#include <sys/ptrace.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(void) {
  int   status;     // esp+0x1c
  char  str[128];   // esp+0x20
  int   res         // esp+0xa8
  pid_t pid;        // esp+0xac
  


  pid = fork();
  memset(str, 0, 128);
  res = 0;
  startus = 0;
  if (pid == 0) {
    prctl(1, 1);
    ptrace(0, 0, 0, 0);
    puts("Give me some shellcode, k");
    gets(str);
  }
  else {
    while ((ptrace(3, pid, 44, 0) != 0xb))
    {
      wait(&status);
      if ((status & 0x7f) == 0)
      {
        puts("child is exiting...");
        return (0);
      } 
    }
    puts("no exec() for you");
    kill(pid, 9);
  }
  return (0);
}

