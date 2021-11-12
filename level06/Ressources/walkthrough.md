# Level 06

<h3>source.c</h3>

```console
int auth(char* login, int serial) {
  int len;       // ebp-0xc
  int result;    // ebp-0x10

  login[strcspn(login, "\n")] = '\0'
  len = strnlen(login, 32);
  if (len <= 5)
    return (1);
  if (ptrace(0, 0, 1, 0) == -1) {
    return (1);
  }
  result = hash(login, serial);
  if (serial == result) {
    return (0);
  }
  return (1);
}

int main() {
  char login[32];
  int serial;

  puts("***********************************");
  puts("*\t\tlevel06\t\t  *");
  puts("***********************************");
  printf("-> Enter Login: ");
  fgets(login, 32, stdin);
  puts("***********************************");
  puts("***** NEW ACCOUNT DETECTED ********");
  puts("***********************************");
  printf("-> Enter Serial: ");
  scanf("%u", &serial);
  if (auth(login, serial) == 0) {
    puts("Authenticated!");
    system("/bin/sh");
    return (0);
  }
  return (1);
}
```

<h3>Analysis</h3>

In this program, we are asked to give 2 input, the `login` and `serial`

Afterward, it will go through `auth()` to check if we are authorized and if yes, we will be able to spawn a shell

The correct serial will be different depending on what we give as the `login` as it will go through a `hash()` and the result will be checked againts the `serial` that we give

Since there is no exploit that we could do in this program, the only way to get a shell is to input the right `serial`

<h3>Exploit</h3>

Now the question will be how we can get the `serial` as it will be close to impossible to guess it

But base on the analysis on the asm code, we can see that the result of the `hash()` is stored inside `[ebp-0x10]`

I think we could set a breakpoint there and print out the content of it!

Since there is a `ptrace()` that protect againts debugging, we need to disable it first

```console
catch syscall ptrace
commands 1
set ($eax) = 0
continue
end
```

Next we will set a breakpoint when the program is doing the comparison of serial vs result

```console
(gdb) break *0x08048866
Breakpoint 2 at 0x8048866
(gdb) r
Starting program: /home/users/level06/level06
***********************************
*		level06		  *
***********************************
-> Enter Login: aaaaaa                          -> doesn't matter but we need to remember this, as the result will be depending on the login string
***********************************                but at least we need 6 char, as anything lower then this will be rejected
***** NEW ACCOUNT DETECTED ********
***********************************
-> Enter Serial: 123456                         -> this on really really doesn't matter

Breakpoint 2, 0x08048866 in auth ()
(gdb) x/d $ebp-0x10
0xffffd658:	6231562
```

Great! we have the result, now lets test it!

```console
level06@OverRide:~$ ./level06
***********************************
*		level06		  *
***********************************
-> Enter Login: aaaaaa
***********************************
***** NEW ACCOUNT DETECTED ********
***********************************
-> Enter Serial: 6231562
Authenticated!
$ whoami
level07
$ cat /home/users/level07/.pass
GbcPDRgsFK77LNnnuh7QyFYA2942Gp8yKj9KrWD8
```