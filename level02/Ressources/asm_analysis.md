# Level 02 asm analysis

```console
main()    
0x0000000000400814 <+0>:    push   rbp  
0x0000000000400815 <+1>:    mov    rbp,rsp  
0x0000000000400818 <+4>:    sub    rsp,0x120                      Buffer 288 bytes for local variable
0x000000000040081f <+11>:   mov    DWORD PTR [rbp-0x114],edi  
0x0000000000400825 <+17>:   mov    QWORD PTR [rbp-0x120],rsi  
0x000000000040082c <+24>:   lea    rdx,[rbp-0x70]                 load address [rbp-0x70] (l_var1) (112 bytes buffer (0x70))
0x0000000000400830 <+28>:   mov    eax,0x0  
0x0000000000400835 <+33>:   mov    ecx,0xc  
0x000000000040083a <+38>:   mov    rdi,rdx  
0x000000000040083d <+41>:   rep stos QWORD PTR es:[rdi],rax 
0x0000000000400840 <+44>:   mov    rdx,rdi  
0x0000000000400843 <+47>:   mov    DWORD PTR [rdx],eax  
0x0000000000400845 <+49>:   add    rdx,0x4  
                                                                  line 24-49 will be equal to memset(l_var1, 0, 12 * 4)
0x0000000000400849 <+53>:   lea    rdx,[rbp-0xa0]                 load address [rbp-0xa0] (l_var2) (48 bytes buffer (0xa0 - 0x70))
0x0000000000400850 <+60>:   mov    eax,0x0  
0x0000000000400855 <+65>:   mov    ecx,0x5  
0x000000000040085a <+70>:   mov    rdi,rdx  
0x000000000040085d <+73>:   rep stos QWORD PTR es:[rdi],rax 
0x0000000000400860 <+76>:   mov    rdx,rdi  
0x0000000000400863 <+79>:   mov    BYTE PTR [rdx],al  
0x0000000000400865 <+81>:   add    rdx,0x1  
                                                                  line 53-81 will be equal to memset(l_var2, 0, 5 * 4)
0x0000000000400869 <+85>:   lea    rdx,[rbp-0x110]                load address [rbp-0x110] (l_var3) (112 bytes buffer (0x110-0xa0))
0x0000000000400870 <+92>:   mov    eax,0x0  
0x0000000000400875 <+97>:   mov    ecx,0xc  
0x000000000040087a <+102>:  mov    rdi,rdx  
0x000000000040087d <+105>:  rep stos QWORD PTR es:[rdi],rax 
0x0000000000400880 <+108>:  mov    rdx,rdi  
0x0000000000400883 <+111>:  mov    DWORD PTR [rdx],eax  
0x0000000000400885 <+113>:  add    rdx,0x4  
                                                                  line 85-113 will be equal to memset(l_var3, 0, 12 * 4)
0x0000000000400889 <+117>:  mov    QWORD PTR [rbp-0x8],0x0        copy 0 to [rbp-0x8] (l_var4 8bytes should be FILE datatype)
0x0000000000400891 <+125>:  mov    DWORD PTR [rbp-0xc],0x0        copy 0 to [rbp-0xc] (l_var5)
0x0000000000400898 <+132>:  mov    edx,0x400bb0                   copy "r" into edx, 2nd arg for fopen
0x000000000040089d <+137>:  mov    eax,0x400bb2                   copy "/home/users/level03/.pass" in eax, 1st arg for fopen
0x00000000004008a2 <+142>:  mov    rsi,rdx                        copy rdx into rsi
0x00000000004008a5 <+145>:  mov    rdi,rax                        copy rax into rdi
0x00000000004008a8 <+148>:  call   0x400700 <fopen@plt>           call function fopen
0x00000000004008ad <+153>:  mov    QWORD PTR [rbp-0x8],rax        save return from fopen to [rbp-0x8] (l_var4)
0x00000000004008b1 <+157>:  cmp    QWORD PTR [rbp-0x8],0x0        compare if [rbp-0x8] (l_var4) is 0
0x00000000004008b6 <+162>:  jne    0x4008e6 <main+210>            jump not equal to line 210
0x00000000004008b8 <+164>:  mov    rax,QWORD PTR [rip+0x200991]   # 0x601250 <stderr@@GLIBC_2.2.5> 
0x00000000004008bf <+171>:  mov    rdx,rax                        copy rax (stderr) into rdx, 4th arg for fwrite
0x00000000004008c2 <+174>:  mov    eax,0x400bd0                   copy "ERROR: failed to open password file\n" into eax, 1st arg for fwrite
0x00000000004008c7 <+179>:  mov    rcx,rdx                        copy rdx into rcx
0x00000000004008ca <+182>:  mov    edx,0x24                       copy number 36 into edx, 3rd arg for write
0x00000000004008cf <+187>:  mov    esi,0x1                        copy number 1 into esi, 2nd arg for fwrite
0x00000000004008d4 <+192>:  mov    rdi,rax                        copy rax into rdi
0x00000000004008d7 <+195>:  call   0x400720 <fwrite@plt>          call function fwrite
0x00000000004008dc <+200>:  mov    edi,0x1                        copy number 1 into edi, 1st arg for exit
0x00000000004008e1 <+205>:  call   0x400710 <exit@plt>            call function exit
0x00000000004008e6 <+210>:  lea    rax,[rbp-0xa0]                 load address [rbp-0xa0] (l_var2) into rax, 1st arg for fread
0x00000000004008ed <+217>:  mov    rdx,QWORD PTR [rbp-0x8]        copy [rbp-0x8] (l_var4) into rdx, 4th arg for fread
0x00000000004008f1 <+221>:  mov    rcx,rdx                        copy rdx into rcx
0x00000000004008f4 <+224>:  mov    edx,0x29                       copy number 41 into edx, 3rd arg for write
0x00000000004008f9 <+229>:  mov    esi,0x1                        copy number 1 into esi, 2nd arg for fwrite
0x00000000004008fe <+234>:  mov    rdi,rax                        copy rax into rdi
0x0000000000400901 <+237>:  call   0x400690 <fread@plt>           call function fread
0x0000000000400906 <+242>:  mov    DWORD PTR [rbp-0xc],eax        save return from fread to [rbp-0xc] (l_var5)
0x0000000000400909 <+245>:  lea    rax,[rbp-0xa0]                 load address [rbp-0xa0] (l_var2) into rax, 1st arg for strcspn
0x0000000000400910 <+252>:  mov    esi,0x400bf5                   copy "\n" into esi, 2nd arg for strcspn
0x0000000000400915 <+257>:  mov    rdi,rax                        copy rax into rdi
0x0000000000400918 <+260>:  call   0x4006d0 <strcspn@plt>         call function strcspn
0x000000000040091d <+265>:  mov    BYTE PTR [rbp+rax*1-0xa0],0x0  l_var2[return of strcspn] = '\0'
0x0000000000400925 <+273>:  cmp    DWORD PTR [rbp-0xc],0x29       compare if [rbp-0xc] (l_var5) is 41
0x0000000000400929 <+277>:  je     0x40097d <main+361>            jump equal to line 361
0x000000000040092b <+279>:  mov    rax,QWORD PTR [rip+0x20091e]   # 0x601250 <stderr@@GLIBC_2.2.5> 
0x0000000000400932 <+286>:  mov    rdx,rax                        copy rax (stderr) into rdx, 4th arg for fwrite
0x0000000000400935 <+289>:  mov    eax,0x400bf8                   copy "ERROR: failed to read password file\n" into eax, 1st arg for fwrite
0x000000000040093a <+294>:  mov    rcx,rdx                        copy rdx into rcx
0x000000000040093d <+297>:  mov    edx,0x24                       copy number 36 into edx, 3rd arg for write
0x0000000000400942 <+302>:  mov    esi,0x1                        copy number 1 into esi, 2nd arg for fwrite
0x0000000000400947 <+307>:  mov    rdi,rax                        copy rax into rdi
0x000000000040094a <+310>:  call   0x400720 <fwrite@plt>          call function fwrite
0x000000000040094f <+315>:  mov    rax,QWORD PTR [rip+0x2008fa]   # 0x601250 <stderr@@GLIBC_2.2.5> 
0x0000000000400956 <+322>:  mov    rdx,rax                        copy rax (stderr) into rdx, 4th arg for fwrite
0x0000000000400959 <+325>:  mov    eax,0x400bf8                   copy "ERROR: failed to read password file\n" into eax, 1st arg for fwrite
0x000000000040095e <+330>:  mov    rcx,rdx                        copy rdx into rcx
0x0000000000400961 <+333>:  mov    edx,0x24                       copy number 36 into edx, 3rd arg for write
0x0000000000400966 <+338>:  mov    esi,0x1                        copy number 1 into esi, 2nd arg for fwrite
0x000000000040096b <+343>:  mov    rdi,rax                        copy rax into rdi
0x000000000040096e <+346>:  call   0x400720 <fwrite@plt>          call function fwrite
0x0000000000400973 <+351>:  mov    edi,0x1                        copy number 1 into edi, 1st arg for exit
0x0000000000400978 <+356>:  call   0x400710 <exit@plt>            call function exit
0x000000000040097d <+361>:  mov    rax,QWORD PTR [rbp-0x8]        copy [rbp-0x8] (l_var4) into rax, 1st arg for fclose
0x0000000000400981 <+365>:  mov    rdi,rax                        copy rax into rdi
0x0000000000400984 <+368>:  call   0x4006a0 <fclose@plt>          call function fclose
0x0000000000400989 <+373>:  mov    edi,0x400c20                   put "===== [ Secure Access System v1.0 ] =====" as 1st arg for puts
0x000000000040098e <+378>:  call   0x400680 <puts@plt>            call function puts
0x0000000000400993 <+383>:  mov    edi,0x400c50                   put "/***************************************\\" as 1st arg for puts
0x0000000000400998 <+388>:  call   0x400680 <puts@plt>            call function puts
0x000000000040099d <+393>:  mov    edi,0x400c80                   put "| You must login to access this system. |" as 1st arg for puts
0x00000000004009a2 <+398>:  call   0x400680 <puts@plt>            call function puts
0x00000000004009a7 <+403>:  mov    edi,0x400cb0                   put "\\**************************************/" as 1st arg for puts
0x00000000004009ac <+408>:  call   0x400680 <puts@plt>            call function puts
0x00000000004009b1 <+413>:  mov    eax,0x400cd9                   put "--[ Username: " to eax, as 1st arg for printf
0x00000000004009b6 <+418>:  mov    rdi,rax                        copy rax into rdi
0x00000000004009b9 <+421>:  mov    eax,0x0                        copy 0 to eax
0x00000000004009be <+426>:  call   0x4006c0 <printf@plt>          call function printf
0x00000000004009c3 <+431>:  mov    rax,QWORD PTR [rip+0x20087e]   # 0x601248 <stdin@@GLIBC_2.2.5>  
0x00000000004009ca <+438>:  mov    rdx,rax                        copy rax (stdin) into rdx, 3rd arg for fwrite
0x00000000004009cd <+441>:  lea    rax,[rbp-0x70]                 load address [rbp-0x70] (l_var1) into rax, as 1st arg for fgets
0x00000000004009d1 <+445>:  mov    esi,0x64                       copy number 100 into esi, 2nd arg for fwrite
0x00000000004009d6 <+450>:  mov    rdi,rax                        copy rax into rdi
0x00000000004009d9 <+453>:  call   0x4006f0 <fgets@plt>           call function fgets
0x00000000004009de <+458>:  lea    rax,[rbp-0x70]                 load address [rbp-0x70] (l_var1) into rax, as 1st arg for strcspn
0x00000000004009e2 <+462>:  mov    esi,0x400bf5                   copy "\n" into esi, 2nd arg for strcspn
0x00000000004009e7 <+467>:  mov    rdi,rax                        copy rax into rdi
0x00000000004009ea <+470>:  call   0x4006d0 <strcspn@plt>         call function strcspn
0x00000000004009ef <+475>:  mov    BYTE PTR [rbp+rax*1-0x70],0x0  l_var1[return of strcspn] = '\0'
0x00000000004009f4 <+480>:  mov    eax,0x400ce8                   put "--[ Password: " to eax, as 1st arg for printf
0x00000000004009f9 <+485>:  mov    rdi,rax                        copy rax into rdi
0x00000000004009fc <+488>:  mov    eax,0x0                        copy 0 to eax
0x0000000000400a01 <+493>:  call   0x4006c0 <printf@plt>          call function printf
0x0000000000400a06 <+498>:  mov    rax,QWORD PTR [rip+0x20083b]   # 0x601248 <stdin@@GLIBC_2.2.5>  
0x0000000000400a0d <+505>:  mov    rdx,rax                        copy rax (stdin) into rdx, 3rd arg for fwrite
0x0000000000400a10 <+508>:  lea    rax,[rbp-0x110]                load address [rbp-0x110] (l_var3) into rax, as 1st arg for fgets
0x0000000000400a17 <+515>:  mov    esi,0x64                       copy number 100 into esi, 2nd arg for fgets
0x0000000000400a1c <+520>:  mov    rdi,rax                        copy rax into rdi
0x0000000000400a1f <+523>:  call   0x4006f0 <fgets@plt>           call function fgets
0x0000000000400a24 <+528>:  lea    rax,[rbp-0x110]                load address [rbp-0x110] (l_var3) into rax, as 1st arg for strcspn
0x0000000000400a2b <+535>:  mov    esi,0x400bf5                   copy "\n" into esi, 2nd arg for strcspn
0x0000000000400a30 <+540>:  mov    rdi,rax                        copy rax into rdi
0x0000000000400a33 <+543>:  call   0x4006d0 <strcspn@plt>         call function strcspn
0x0000000000400a38 <+548>:  mov    BYTE PTR [rbp+rax*1-0x110],0x0 l_var3[return of strcspn] = '\0'
0x0000000000400a40 <+556>:  mov    edi,0x400cf8                   put "*****************************************" as 1st arg for puts
0x0000000000400a45 <+561>:  call   0x400680 <puts@plt>            call function puts
0x0000000000400a4a <+566>:  lea    rcx,[rbp-0x110]                load address [rbp-0x110] (l_var3) into rcx, as 2nd arg for strncmp
0x0000000000400a51 <+573>:  lea    rax,[rbp-0xa0]                 load address [rbp-0xa0] (l_var2) into rax, 1st arg for strncmp
0x0000000000400a58 <+580>:  mov    edx,0x29                       copy number 41 into edx, 3rd arg for strncmp
0x0000000000400a5d <+585>:  mov    rsi,rcx                        copy rcx into rsi
0x0000000000400a60 <+588>:  mov    rdi,rax                        copy rax into rdi
0x0000000000400a63 <+591>:  call   0x400670 <strncmp@plt>         call function strncmp
0x0000000000400a68 <+596>:  test   eax,eax                        test if 0
0x0000000000400a6a <+598>:  jne    0x400a96 <main+642>            jump not equal to line 642
0x0000000000400a6c <+600>:  mov    eax,0x400d22                   copy "Greetings, %s!\n" into eax, 1st arg for printf
0x0000000000400a71 <+605>:  lea    rdx,[rbp-0x70]                 load address [rbp-0x70] (l_var1) into rdx, 2nd arg for printf
0x0000000000400a75 <+609>:  mov    rsi,rdx                        copy rdx into rsi
0x0000000000400a78 <+612>:  mov    rdi,rax                        copy rax into rdi
0x0000000000400a7b <+615>:  mov    eax,0x0                        copy 0 to eax
0x0000000000400a80 <+620>:  call   0x4006c0 <printf@plt>          call function printf
0x0000000000400a85 <+625>:  mov    edi,0x400d32                   put "/bin/sh" as 1st arg for system
0x0000000000400a8a <+630>:  call   0x4006b0 <system@plt>          call function system
0x0000000000400a8f <+635>:  mov    eax,0x0                        return 0
0x0000000000400a94 <+640>:  leave 
0x0000000000400a95 <+641>:  ret 
0x0000000000400a96 <+642>:  lea    rax,[rbp-0x70]                 load address [rbp-0x70] (l_var1) into rdx, 1st arg for printf
0x0000000000400a9a <+646>:  mov    rdi,rax                        copy rax into rdi
0x0000000000400a9d <+649>:  mov    eax,0x0                        copy 0 to eax
0x0000000000400aa2 <+654>:  call   0x4006c0 <printf@plt>          call function printf
0x0000000000400aa7 <+659>:  mov    edi,0x400d3a                   put " does not have access!" as 1st arg for puts
0x0000000000400aac <+664>:  call   0x400680 <puts@plt>            call function puts
0x0000000000400ab1 <+669>:  mov    edi,0x1                        copy number 1 into edi, 1st arg for exit
0x0000000000400ab6 <+674>:  call   0x400710 <exit@plt>            call function exit
```