# Level 05 asm analysis

```console
main()
0x08048444 <+0>:    push   ebp  
0x08048445 <+1>:    mov    ebp,esp  
0x08048447 <+3>:    push   edi  
0x08048448 <+4>:    push   ebx  
0x08048449 <+5>:    and    esp,0xfffffff0           Bit alignment
0x0804844c <+8>:    sub    esp,0x90                 Buffer 144 bytes for local variable
0x08048452 <+14>:   mov    DWORD PTR [esp+0x8c],0x0 copy 0 into [esp+0x8c] (l_var1)
0x0804845d <+25>:   mov    eax,ds:0x80497f0         copy "stdin" into eax
0x08048462 <+30>:   mov    DWORD PTR [esp+0x8],eax  put eax ("stdin") as 3rd arg for fgets
0x08048466 <+34>:   mov    DWORD PTR [esp+0x4],0x64 put 100 as 2nd arg for fgets
0x0804846e <+42>:   lea    eax,[esp+0x28]           load address of [esp+0x28] (l_var2) into eax (should be a buffer with 100 bytes)
0x08048472 <+46>:   mov    DWORD PTR [esp],eax      put eax (l_var2) as 1st arg for fgets
0x08048475 <+49>:   call   0x8048350 <fgets@plt>    call function fgets
0x0804847a <+54>:   mov    DWORD PTR [esp+0x8c],0x0 copy 0 into [esp+0x8c] (l_var1)
0x08048485 <+65>:   jmp    0x80484d3 <main+143>     jump to line 143
0x08048487 <+67>:   lea    eax,[esp+0x28]           load address of [esp+0x28] (l_var2) into eax
0x0804848b <+71>:   add    eax,DWORD PTR [esp+0x8c] add l_var1 into l_var2 (l_var2[l_var1])
0x08048492 <+78>:   movzx  eax,BYTE PTR [eax]       copy the content of l_var2
0x08048495 <+81>:   cmp    al,0x40                  compare if l_var2 = '@'
0x08048497 <+83>:   jle    0x80484cb <main+135>     jump if less equal to line 135
0x08048499 <+85>:   lea    eax,[esp+0x28]           load address of [esp+0x28] (l_var2) into eax
0x0804849d <+89>:   add    eax,DWORD PTR [esp+0x8c] add l_var1 into l_var2 (l_var2[l_var1])
0x080484a4 <+96>:   movzx  eax,BYTE PTR [eax]       copy the content of l_var2
0x080484a7 <+99>:   cmp    al,0x5a                  compare if l_var2 = 'Z'
0x080484a9 <+101>:  jg     0x80484cb <main+135>     jump if greater to line 135
0x080484ab <+103>:  lea    eax,[esp+0x28]           load address of [esp+0x28] (l_var2) into eax
0x080484af <+107>:  add    eax,DWORD PTR [esp+0x8c] add l_var1 into l_var2 (l_var2[l_var1])
0x080484b6 <+114>:  movzx  eax,BYTE PTR [eax]       copy the content of l_var2
0x080484b9 <+117>:  mov    edx,eax                  copy eax (l_var2) into edx
0x080484bb <+119>:  xor    edx,0x20                 do xor operation on edx (l_var2) with 0x20 (basically tolower())
0x080484be <+122>:  lea    eax,[esp+0x28]           load address of [esp+0x28] (l_var2) into eax
0x080484c2 <+126>:  add    eax,DWORD PTR [esp+0x8c] add l_var1 into l_var2 (l_var2[l_var1])
0x080484c9 <+133>:  mov    BYTE PTR [eax],dl        copy dl (result of xor operation) into the content of l_var2
0x080484cb <+135>:  add    DWORD PTR [esp+0x8c],0x1 add 1 into [esp+0x8c] (l_var1)
0x080484d3 <+143>:  mov    ebx,DWORD PTR [esp+0x8c] copy [esp+0x8c] (l_var1) into ebx
0x080484da <+150>:  lea    eax,[esp+0x28]           load address of [esp-0x28] (l_var2)
0x080484de <+154>:  mov    DWORD PTR [esp+0x1c],0xffffffff  put number -1 into [esp+0x1c]
0x080484e6 <+162>:  mov    edx,eax                  copy eax (l_var2) into edx
0x080484e8 <+164>:  mov    eax,0x0                  copy number 0 into eax
0x080484ed <+169>:  mov    ecx,DWORD PTR [esp+0x1c] copy [esp+0x1c] (-1) into ecx
0x080484f1 <+173>:  mov    edi,edx                  copy edx (l_var2) to edi (destionation index)
0x080484f3 <+175>:  repnz scas al,BYTE PTR es:[edi] repeat not zero Scan String Operands (scas) on edi, repeat until zero flag is not set and cx is not zero,
                                                    each iteration decrements ecx, since ecx start from -1 (max int) it will make sure to loop the max time possible
                                                    scas compare each bytes in edi vs al, since eax was set to 0, al the lower part of ax must be 0 as well
                                                    as long as the edi[i] is not 0, the loop will keep repeating, (al vs edi[i]) -> (0 vs edi[i])
                                                    zero flag will be set if the two values equal and the operation will stop, and ecx will contain the total count of the loop, thus the total length of edi
0x080484f5 <+177>:  mov    eax,ecx                  copy ecx (counter) into eax
0x080484f7 <+179>:  not    eax                      reverse the bit inside eax (counter)
0x080484f9 <+181>:  sub    eax,0x1                  since ecx counts down from 0xffffffff (also known as -1), all the operation from line 150-181 is to get the real counter result from the repnz scas
                                                    all those above is equal to strlen(l_var2)
0x080484fc <+184>:  cmp    ebx,eax                  compare eax (len of l_var2) with ebx (l_var1)
0x080484fe <+186>:  jb     0x8048487 <main+67>      jump if below to line 67
0x08048500 <+188>:  lea    eax,[esp+0x28]           load address of [esp-0x28] (l_var2)
0x08048504 <+192>:  mov    DWORD PTR [esp],eax      put eax (l_var2) as 1st arg for printf
0x08048507 <+195>:  call   0x8048340 <printf@plt>   call function printf
0x0804850c <+200>:  mov    DWORD PTR [esp],0x0      put 0 as 1st arg for exit
0x08048513 <+207>:  call   0x8048370 <exit@plt>     call function exit
```