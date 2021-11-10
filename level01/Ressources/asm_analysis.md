# Level 01 asm analysis

```console
verify_user_name()    
0x08048464 <+0>:    push   ebp  
0x08048465 <+1>:    mov    ebp,esp  
0x08048467 <+3>:    push   edi  
0x08048468 <+4>:    push   esi  
0x08048469 <+5>:    sub    esp,0x10                               Buffer 16 bytes for local variable
0x0804846c <+8>:    mov    DWORD PTR [esp],0x8048690              put "verifying username....\n" to 1st arg of function puts
0x08048473 <+15>:   call   0x8048380 <puts@plt>                   call function puts
0x08048478 <+20>:   mov    edx,0x804a040                          copy global var a_user_name into edx
0x0804847d <+25>:   mov    eax,0x80486a8                          copy "dat_wil" into eax
0x08048482 <+30>:   mov    ecx,0x7                                copy number 7 into ecx
0x08048487 <+35>:   mov    esi,edx                                copy edx (pointer to local variable1) into esi (source index)
0x08048489 <+37>:   mov    edi,eax                                copy eax ("dat_wil") into edi (destination index)
0x0804848b <+39>:   repz cmps BYTE PTR ds:[esi],BYTE PTR es:[edi] repeat Compare String Operands (cmps) on esi and edi
0x0804848d <+41>:   seta   dl                                     set dl (lower part of dx) to 1 if the above flag is set, or dl to 0 if not
0x08048490 <+44>:   setb   al                                     set al (lower part of ax) to 1 if the below flag is set, or al to 0 if not
0x08048493 <+47>:   mov    ecx,edx                                copy edx (pointer to local variable1) into ecx
0x08048495 <+49>:   sub    cl,al                                  subtract al (lower part of ax) with cl (lower part of cx)
0x08048497 <+51>:   mov    eax,ecx                                copy ecx (after the lower part gets substracted by al) into eax
0x08048499 <+53>:   movsx  eax,al                                 movsx is to copy a smaller memory to bigger memory by sign extension (al is lower part of ax)
0x0804849c <+56>:   add    esp,0x10                               all those operation above is just to check if the result of the cmp is equal to 0
0x0804849f <+59>:   pop    esi  
0x080484a0 <+60>:   pop    edi  
0x080484a1 <+61>:   pop    ebp  
0x080484a2 <+62>:   ret 


verify_user_pass()    
0x080484a3 <+0>:    push   ebp  
0x080484a4 <+1>:    mov    ebp,esp  
0x080484a6 <+3>:    push   edi  
0x080484a7 <+4>:    push   esi  
0x080484a8 <+5>:    mov    eax,DWORD PTR [ebp+0x8]                load address of [ebp+0x8] (arg1) into eax
0x080484ab <+8>:    mov    edx,eax                                copy the eax (arg1) to edx
0x080484ad <+10>:   mov    eax,0x80486b0                          copy "admin" into eax
0x080484b2 <+15>:   mov    ecx,0x5                                copy number 5 into ecx
0x080484b7 <+20>:   mov    esi,edx                                copy edx (pointer to local variable1) into esi (source index)
0x080484b9 <+22>:   mov    edi,eax                                copy eax ("admin") into edi (destination index)
0x080484bb <+24>:   repz cmps BYTE PTR ds:[esi],BYTE PTR es:[edi] repeat Compare String Operands (cmps) on esi and edi
0x080484bd <+26>:   seta   dl                                     set dl (lower part of dx) to 1 if the above flag is set, or dl to 0 if not
0x080484c0 <+29>:   setb   al                                     set al (lower part of ax) to 1 if the below flag is set, or al to 0 if not
0x080484c3 <+32>:   mov    ecx,edx                                copy edx (pointer to local variable1) into ecx
0x080484c5 <+34>:   sub    cl,al                                  subtract al (lower part of ax) with cl (lower part of cx)
0x080484c7 <+36>:   mov    eax,ecx                                copy ecx (after the lower part gets substracted by al) into eax
0x080484c9 <+38>:   movsx  eax,al                                 movsx is to copy a smaller memory to bigger memory by sign extension (al is lower part of ax)
0x080484cc <+41>:   pop    esi                                    all those operation above is just to check if the result of the cmp is equal to 0
0x080484cd <+42>:   pop    edi  
0x080484ce <+43>:   pop    ebp  
0x080484cf <+44>:   ret 


main()    
0x080484d0 <+0>:    push   ebp  
0x080484d1 <+1>:    mov    ebp,esp  
0x080484d3 <+3>:    push   edi  
0x080484d4 <+4>:    push   ebx  
0x080484d5 <+5>:    and    esp,0xfffffff0                         Bit alignment
0x080484d8 <+8>:    sub    esp,0x60                               Buffer 96 bytes for local variable
0x080484db <+11>:   lea    ebx,[esp+0x1c]                         load address from [esp+0x1c] (l_var1) to ebx (should be a buffer with 64 bytes (0x5c - 0x1c))
0x080484df <+15>:   mov    eax,0x0                                copy 0 to eax
0x080484e4 <+20>:   mov    edx,0x10                               copy 16 to edx
0x080484e9 <+25>:   mov    edi,ebx                                copy ebx to edi
0x080484eb <+27>:   mov    ecx,edx                                copy edx to ecx
0x080484ed <+29>:   rep stos DWORD PTR es:[edi],eax               repeat store string operation on eax (0) to edi
                                                                  line 11 - 29 basically mean this (memset(buffer, 0, 16 * 4)
0x080484ef <+31>:   mov    DWORD PTR [esp+0x5c],0x0               copy 0 into [esp+0x5c] (l_var2)
0x080484f7 <+39>:   mov    DWORD PTR [esp],0x80486b8              put "********* ADMIN LOGIN PROMPT *********" to 1st arg of function puts
0x080484fe <+46>:   call   0x8048380 <puts@plt>                   call function puts
0x08048503 <+51>:   mov    eax,0x80486df                          copy "Enter Username: " to eax
0x08048508 <+56>:   mov    DWORD PTR [esp],eax                    put eax ("Enter Username: ") to 1st arg of function printf
0x0804850b <+59>:   call   0x8048360 <printf@plt>                 call function printf
0x08048510 <+64>:   mov    eax,ds:0x804a020                       copy "stdin" into eax
0x08048515 <+69>:   mov    DWORD PTR [esp+0x8],eax                put eax ("stdin") to 3rd arg of function fgets
0x08048519 <+73>:   mov    DWORD PTR [esp+0x4],0x100              put 256 to 2nd arg of function fgets
0x08048521 <+81>:   mov    DWORD PTR [esp],0x804a040              put global var a_user_name to 1st arg of function fgets
0x08048528 <+88>:   call   0x8048370 <fgets@plt>                  call function fgets
0x0804852d <+93>:   call   0x8048464 <verify_user_name>           call function verify_user_name
0x08048532 <+98>:   mov    DWORD PTR [esp+0x5c],eax               save eax (return of verify_user_name) into [esp+0x5c] (l_var2)
0x08048536 <+102>:  cmp    DWORD PTR [esp+0x5c],0x0               compare eax (l_var2) with 0
0x0804853b <+107>:  je     0x8048550 <main+128>                   jump equal to line main+128
0x0804853d <+109>:  mov    DWORD PTR [esp],0x80486f0              put "nope, incorrect username...\n" to 1st arg of function puts
0x08048544 <+116>:  call   0x8048380 <puts@plt>                   call function puts
0x08048549 <+121>:  mov    eax,0x1                                return 1
0x0804854e <+126>:  jmp    0x80485af <main+223>                   jump equal to line main+223 (end the program)
0x08048550 <+128>:  mov    DWORD PTR [esp],0x804870d              put "Enter Password: " to 1st arg of function puts
0x08048557 <+135>:  call   0x8048380 <puts@plt>                   call function puts
0x0804855c <+140>:  mov    eax,ds:0x804a020                       copy "stdin" into eax
0x08048561 <+145>:  mov    DWORD PTR [esp+0x8],eax                put eax ("stdin") to 3rd arg of function fgets
0x08048565 <+149>:  mov    DWORD PTR [esp+0x4],0x64               put 100 to 2nd arg of function fgets
0x0804856d <+157>:  lea    eax,[esp+0x1c]                         load address of [esp+0x1c] (l_var1) to eax
0x08048571 <+161>:  mov    DWORD PTR [esp],eax                    put eax (l_var1) to 1st arg of function fgets
0x08048574 <+164>:  call   0x8048370 <fgets@plt>                  call function fgets
0x08048579 <+169>:  lea    eax,[esp+0x1c]                         load address of [esp+0x1c] (l_var1) to eax
0x0804857d <+173>:  mov    DWORD PTR [esp],eax                    put eax (l_var1) to 1st arg of function verify_user_pass
0x08048580 <+176>:  call   0x80484a3 <verify_user_pass>           call function verify_user_pass
0x08048585 <+181>:  mov    DWORD PTR [esp+0x5c],eax               save eax (return of verify_user_pass) into [esp+0x5c] (l_var2)
0x08048589 <+185>:  cmp    DWORD PTR [esp+0x5c],0x0               compare eax (l_var2) with 0
0x0804858e <+190>:  je     0x8048597 <main+199>                   jump equal to line main+199
0x08048590 <+192>:  cmp    DWORD PTR [esp+0x5c],0x0               compare eax (l_var2) with 0
0x08048595 <+197>:  je     0x80485aa <main+218>                   jump equal to line main+218
0x08048597 <+199>:  mov    DWORD PTR [esp],0x804871e              put "nope, incorrect password...\n" to 1st arg of function puts
0x0804859e <+206>:  call   0x8048380 <puts@plt>                   call function puts
0x080485a3 <+211>:  mov    eax,0x1                                return 1
0x080485a8 <+216>:  jmp    0x80485af <main+223>                   jump to line main+223 (end the program)
0x080485aa <+218>:  mov    eax,0x0                                return 0
0x080485af <+223>:  lea    esp,[ebp-0x8]  
0x080485b2 <+226>:  pop    ebx  
0x080485b3 <+227>:  pop    edi  
0x080485b4 <+228>:  pop    ebp  
0x080485b5 <+229>:  ret 
```