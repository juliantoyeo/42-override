# Level 04 asm analysis

```console
main()  
0x080486c8 <+0>:      push   ebp    
0x080486c9 <+1>:      mov    ebp,esp    
0x080486cb <+3>:      push   edi    
0x080486cc <+4>:      push   ebx    
0x080486cd <+5>:      and    esp,0xfffffff0               Bit alignment
0x080486d0 <+8>:      sub    esp,0xb0                     Buffer 176 bytes for local variable
0x080486d6 <+14>:     call   0x8048550 <fork@plt>         call function fork
0x080486db <+19>:     mov    DWORD PTR [esp+0xac],eax     copy eax (return of fork) to [esp+0xac] (l_var1)
0x080486e2 <+26>:     lea    ebx,[esp+0x20]               load address of [esp+0x20] (l_var2) to eax (should be a buffer with 128 bytes)
0x080486e6 <+30>:     mov    eax,0x0                      copy 0 to eax
0x080486eb <+35>:     mov    edx,0x20                     copy 32 to edx
0x080486f0 <+40>:     mov    edi,ebx                      copy ebx to edi
0x080486f2 <+42>:     mov    ecx,edx                      copy edx to ecx
0x080486f4 <+44>:     rep stos DWORD PTR es:[edi],eax     repeat store string operation on eax (0) to edi
                                                          line 26 - 44 basically mean this (memset(buffer, 0, 32 * 4)
0x080486f6 <+46>:     mov    DWORD PTR [esp+0xa8],0x0     copy 0 to [esp+0xa8] (lvar_3)
0x08048701 <+57>:     mov    DWORD PTR [esp+0x1c],0x0     copy 0 to [esp+0x1c] (lvar_4)
0x08048709 <+65>:     cmp    DWORD PTR [esp+0xac],0x0     compare if [esp+0xac] is equal to 0
0x08048711 <+73>:     jne    0x8048769 <main+161>         jump not equal to line 161
0x08048713 <+75>:     mov    DWORD PTR [esp+0x4],0x1      put 1 as 2nd arg for prtcl
0x0804871b <+83>:     mov    DWORD PTR [esp],0x1          put 1 as 1st arg for prtcl
0x08048722 <+90>:     call   0x8048540 <prctl@plt>        call function prtcl
0x08048727 <+95>:     mov    DWORD PTR [esp+0xc],0x0      put 0 as 4th arg for ptrace
0x0804872f <+103>:    mov    DWORD PTR [esp+0x8],0x0      put 0 as 3rd arg for ptrace
0x08048737 <+111>:    mov    DWORD PTR [esp+0x4],0x0      put 0 as 2nd arg for ptrace
0x0804873f <+119>:    mov    DWORD PTR [esp],0x0          put 0 as 1st arg for ptrace
0x08048746 <+126>:    call   0x8048570 <ptrace@plt>       call function ptrace
0x0804874b <+131>:    mov    DWORD PTR [esp],0x8048903    put "Give me some shellcode, k" as 1st arg for puts
0x08048752 <+138>:    call   0x8048500 <puts@plt>         call function puts
0x08048757 <+143>:    lea    eax,[esp+0x20]               load address of [esp+0x20] (l_var2) to eax
0x0804875b <+147>:    mov    DWORD PTR [esp],eax          put [esp+0x20] (l_var2) as 1st arg for gets
0x0804875e <+150>:    call   0x80484b0 <gets@plt>         call function gets
0x08048763 <+155>:    jmp    0x804881a <main+338>         jump to line 338 (end the program)
0x08048768 <+160>:    nop   
0x08048769 <+161>:    lea    eax,[esp+0x1c]               load address of [esp+0x1c] (lvar_4) to eax
0x0804876d <+165>:    mov    DWORD PTR [esp],eax          put [esp+0x1c] (lvar_4) as 1st arg for wait
0x08048770 <+168>:    call   0x80484f0 <wait@plt>         call function wait
0x08048775 <+173>:    mov    eax,DWORD PTR [esp+0x1c]     copy [esp+0x1c] (lvar_4) to eax
0x08048779 <+177>:    mov    DWORD PTR [esp+0xa0],eax     copy eax (l_var4) to [esp+0xa0]
0x08048780 <+184>:    mov    eax,DWORD PTR [esp+0xa0]     copy [esp+0xa0] (l_var4) to eax
0x08048787 <+191>:    and    eax,0x7f                     do and operation (l_var4 & 0x7f)
0x0804878a <+194>:    test   eax,eax                      test if 0
0x0804878c <+196>:    je     0x80487ac <main+228>         jump if equal to line 228
0x0804878e <+198>:    mov    eax,DWORD PTR [esp+0x1c]     copy [esp+0x1c] (lvar_4) to eax
0x08048792 <+202>:    mov    DWORD PTR [esp+0xa4],eax     copy eax (l_var4) to [esp+0xa4]
0x08048799 <+209>:    mov    eax,DWORD PTR [esp+0xa4]     copy [esp+0xa4] (l_var4) to eax
0x080487a0 <+216>:    and    eax,0x7f                     do and operation (l_var4 & 0x7f)
0x080487a3 <+219>:    add    eax,0x1                      add 1 to eax (l_var4)
0x080487a6 <+222>:    sar    al,1                         shift al by 1 bit
0x080487a8 <+224>:    test   al,al                        test if 0
0x080487aa <+226>:    jle    0x80487ba <main+242>         jump if less equal to line 242
0x080487ac <+228>:    mov    DWORD PTR [esp],0x804891d    puts "child is exiting..." as 1st arg for puts
0x080487b3 <+235>:    call   0x8048500 <puts@plt>         call function puts
0x080487b8 <+240>:    jmp    0x804881a <main+338>         jump to line 338 (end the program)
0x080487ba <+242>:    mov    DWORD PTR [esp+0xc],0x0      put 0 as 4th arg for ptrace
0x080487c2 <+250>:    mov    DWORD PTR [esp+0x8],0x2c     put 44 as 3rd arg for ptrace
0x080487ca <+258>:    mov    eax,DWORD PTR [esp+0xac]     copy [esp+0xac] (l_var1) into eax
0x080487d1 <+265>:    mov    DWORD PTR [esp+0x4],eax      put eax (l_var1) as 2nd arg for ptrace
0x080487d5 <+269>:    mov    DWORD PTR [esp],0x3          put 3 as 1st arg for ptrace
0x080487dc <+276>:    call   0x8048570 <ptrace@plt>       call function ptrace
0x080487e1 <+281>:    mov    DWORD PTR [esp+0xa8],eax     save eax (result of ptrace) into [esp+0xa8] (l_var3)
0x080487e8 <+288>:    cmp    DWORD PTR [esp+0xa8],0xb     compare [esp+0xa8] (l_var3) if equal to 0xb
0x080487f0 <+296>:    jne    0x8048768 <main+160>         jump not equal to line 160
0x080487f6 <+302>:    mov    DWORD PTR [esp],0x8048931    put "no exec() for you" as 1st arg for puts
0x080487fd <+309>:    call   0x8048500 <puts@plt>         call function puts
0x08048802 <+314>:    mov    DWORD PTR [esp+0x4],0x9      put 9 as 2nd arg for kill
0x0804880a <+322>:    mov    eax,DWORD PTR [esp+0xac]     copy [esp+0xac] (l_var1) into eax
0x08048811 <+329>:    mov    DWORD PTR [esp],eax          put eax (l_var1) as 1st arg for kill
0x08048814 <+332>:    call   0x8048520 <kill@plt>         call function kill
0x08048819 <+337>:    nop   
0x0804881a <+338>:    mov    eax,0x0    return 0
0x0804881f <+343>:    lea    esp,[ebp-0x8]    
0x08048822 <+346>:    pop    ebx    
0x08048823 <+347>:    pop    edi    
0x08048824 <+348>:    pop    ebp    
0x08048825 <+349>:    ret   
```