# Level 09 asm analysis

```console
secret_backdoor()
0x000000000000088c <+0>:    push   rbp  
0x000000000000088d <+1>:    mov    rbp,rsp  
0x0000000000000890 <+4>:    add    rsp,0xffffffffffffff80         Buffer 128 bytes for local variable
0x0000000000000894 <+8>:    mov    rax,QWORD PTR [rip+0x20171d] # 0x201fb8 copy "stdin" into rax as 3rd arg for fgets
0x000000000000089b <+15>:   mov    rax,QWORD PTR [rax]  
0x000000000000089e <+18>:   mov    rdx,rax  
0x00000000000008a1 <+21>:   lea    rax,[rbp-0x80]                 load address of [rbp-0x80] (l_var1) into rax as 1st arg for fgets
0x00000000000008a5 <+25>:   mov    esi,0x80                       copy 128 into esi as 2nd arg for fgets
0x00000000000008aa <+30>:   mov    rdi,rax  
0x00000000000008ad <+33>:   call   0x770 <fgets@plt>              call function fgets
0x00000000000008b2 <+38>:   lea    rax,[rbp-0x80]                 load address of [rbp-0x80] (l_var1) into rax as 1st arg for system
0x00000000000008b6 <+42>:   mov    rdi,rax  
0x00000000000008b9 <+45>:   call   0x740 <system@plt>             call function system
0x00000000000008be <+50>:   leave 
0x00000000000008bf <+51>:   ret 


handle_msg()
0x00000000000008c0 <+0>:    push   rbp  
0x00000000000008c1 <+1>:    mov    rbp,rsp  
0x00000000000008c4 <+4>:    sub    rsp,0xc0                       Buffer 192 bytes for local variable
0x00000000000008cb <+11>:   lea    rax,[rbp-0xc0]                 load [rbp-0xc0] (l_var1) into rax
0x00000000000008d2 <+18>:   add    rax,0x8c                       add 140 bytes into rax (l_var1)
0x00000000000008d8 <+24>:   mov    QWORD PTR [rax],0x0  
0x00000000000008df <+31>:   mov    QWORD PTR [rax+0x8],0x0  
0x00000000000008e7 <+39>:   mov    QWORD PTR [rax+0x10],0x0 
0x00000000000008ef <+47>:   mov    QWORD PTR [rax+0x18],0x0 
0x00000000000008f7 <+55>:   mov    QWORD PTR [rax+0x20],0x0       add another 40 bytes of 0 into (l_var1)
0x00000000000008ff <+63>:   mov    DWORD PTR [rbp-0xc],0x8c       copy 140 into [rbp-0xc] (l_var1[12] = 140)
0x0000000000000906 <+70>:   lea    rax,[rbp-0xc0]                 load [rbp-0xc0] (l_var1) into rax as 1st arg for set_username
0x000000000000090d <+77>:   mov    rdi,rax  
0x0000000000000910 <+80>:   call   0x9cd <set_username>           call function set_username
0x0000000000000915 <+85>:   lea    rax,[rbp-0xc0]                 load [rbp-0xc0] (l_var1) into rax as 1st arg for set_msg
0x000000000000091c <+92>:   mov    rdi,rax  
0x000000000000091f <+95>:   call   0x932 <set_msg>                call function set_msg
0x0000000000000924 <+100>:  lea    rdi,[rip+0x295]        # 0xbc0 copy ">: Msg sent!" as 1st arg for puts
0x000000000000092b <+107>:  call   0x730 <puts@plt>               call function puts
0x0000000000000930 <+112>:  leave 
0x0000000000000931 <+113>:  ret 


set_msg()   
0x0000000000000932 <+0>:    push   rbp  
0x0000000000000933 <+1>:    mov    rbp,rsp  
0x0000000000000936 <+4>:    sub    rsp,0x410                      Buffer 1040 bytes for local variable
0x000000000000093d <+11>:   mov    QWORD PTR [rbp-0x408],rdi      copy rdi (1st arg) into [rbp-0x408]
0x0000000000000944 <+18>:   lea    rax,[rbp-0x400]                load address of [rbp-0x400] (l_var1) into rax
0x000000000000094b <+25>:   mov    rsi,rax  
0x000000000000094e <+28>:   mov    eax,0x0  
0x0000000000000953 <+33>:   mov    edx,0x80 
0x0000000000000958 <+38>:   mov    rdi,rsi  
0x000000000000095b <+41>:   mov    rcx,rdx  
0x000000000000095e <+44>:   rep stos QWORD PTR es:[rdi],rax       memset(l_var1, 0, 1024)
0x0000000000000961 <+47>:   lea    rdi,[rip+0x265]        # 0xbcd copy ">: Msg @Unix-Dude" into rdi as 1st arg for puts
0x0000000000000968 <+54>:   call   0x730 <puts@plt>               call function puts
0x000000000000096d <+59>:   lea    rax,[rip+0x26b]        # 0xbdf copy ">>: " into rax as 1st arg for printf
0x0000000000000974 <+66>:   mov    rdi,rax  
0x0000000000000977 <+69>:   mov    eax,0x0  
0x000000000000097c <+74>:   call   0x750 <printf@plt>             call function printf
0x0000000000000981 <+79>:   mov    rax,QWORD PTR [rip+0x201630] # 0x201fb8 copy "stdin" in rax as 3rd arg for fgets
0x0000000000000988 <+86>:   mov    rax,QWORD PTR [rax]  
0x000000000000098b <+89>:   mov    rdx,rax  
0x000000000000098e <+92>:   lea    rax,[rbp-0x400]                load address of [rbp-0x400] (l_var1) into rax as 1st arg for fgets
0x0000000000000995 <+99>:   mov    esi,0x400                      put 1024 as 2nd arg for fgets
0x000000000000099a <+104>:  mov    rdi,rax  
0x000000000000099d <+107>:  call   0x770 <fgets@plt>              call function fgets
0x00000000000009a2 <+112>:  mov    rax,QWORD PTR [rbp-0x408]      copy 1st arg into rax
0x00000000000009a9 <+119>:  mov    eax,DWORD PTR [rax+0xb4]       copy 1st arg[180] into eax as 3rd arg for strncpy
0x00000000000009af <+125>:  movsxd rdx,eax  
0x00000000000009b2 <+128>:  lea    rcx,[rbp-0x400]                load address of [rbp-0x400] (l_var1) into rcx as 2nd arg for strncpy
0x00000000000009b9 <+135>:  mov    rax,QWORD PTR [rbp-0x408]      copy 1st arg into rax as 1st arg for strncpy
0x00000000000009c0 <+142>:  mov    rsi,rcx  
0x00000000000009c3 <+145>:  mov    rdi,rax  
0x00000000000009c6 <+148>:  call   0x720 <strncpy@plt>            call function strncpy
0x00000000000009cb <+153>:  leave 
0x00000000000009cc <+154>:  ret 


set_username()
0x00000000000009cd <+0>:    push   rbp  
0x00000000000009ce <+1>:    mov    rbp,rsp  
0x00000000000009d1 <+4>:    sub    rsp,0xa0                       Buffer 160 bytes for local variable
0x00000000000009d8 <+11>:   mov    QWORD PTR [rbp-0x98],rdi       copy rdi (arg1) into [rbp-0x98]
0x00000000000009df <+18>:   lea    rax,[rbp-0x90]                 load [rbp-0x90] (l_var1) into rax
0x00000000000009e6 <+25>:   mov    rsi,rax  
0x00000000000009e9 <+28>:   mov    eax,0x0  
0x00000000000009ee <+33>:   mov    edx,0x10 
0x00000000000009f3 <+38>:   mov    rdi,rsi  
0x00000000000009f6 <+41>:   mov    rcx,rdx  
0x00000000000009f9 <+44>:   rep stos QWORD PTR es:[rdi],rax       memset(l_var1, 0, 128)
0x00000000000009fc <+47>:   lea    rdi,[rip+0x1e1]        # 0xbe4 copy ">: Enter your username" into rdi as 1st arg for puts
0x0000000000000a03 <+54>:   call   0x730 <puts@plt>               call function puts
0x0000000000000a08 <+59>:   lea    rax,[rip+0x1d0]        # 0xbdf copy ">>: " as 1st arg for printf
0x0000000000000a0f <+66>:   mov    rdi,rax  
0x0000000000000a12 <+69>:   mov    eax,0x0  
0x0000000000000a17 <+74>:   call   0x750 <printf@plt>             call function printf
0x0000000000000a1c <+79>:   mov    rax,QWORD PTR [rip+0x201595] # 0x201fb8 copy "stdin" into rax as 3rd arg for fgets
0x0000000000000a23 <+86>:   mov    rax,QWORD PTR [rax]  
0x0000000000000a26 <+89>:   mov    rdx,rax  
0x0000000000000a29 <+92>:   lea    rax,[rbp-0x90]                 load address of [rbp-0x90] (l_var1) into rax as 1st arg for fgets
0x0000000000000a30 <+99>:   mov    esi,0x80                       copy 128 into esi as 2nd arg for fgets
0x0000000000000a35 <+104>:  mov    rdi,rax  
0x0000000000000a38 <+107>:  call   0x770 <fgets@plt>              call function fgets
0x0000000000000a3d <+112>:  mov    DWORD PTR [rbp-0x4],0x0        copy 0 into [rbp-0x4] (l_var2)
0x0000000000000a44 <+119>:  jmp    0xa6a <set_username+157>       jump to line 157
0x0000000000000a46 <+121>:  mov    eax,DWORD PTR [rbp-0x4]        copy [rbp-0x4] (l_var2) into eax
0x0000000000000a49 <+124>:  cdqe  
0x0000000000000a4b <+126>:  movzx  ecx,BYTE PTR [rbp+rax*1-0x90]  move zero extend -> l_var1[l_var2] into ecx
0x0000000000000a53 <+134>:  mov    rdx,QWORD PTR [rbp-0x98]       copy [rbp-0x98] (1st arg) into rdx
0x0000000000000a5a <+141>:  mov    eax,DWORD PTR [rbp-0x4]        copy [rbp-0x4] (l_var2) into eax
0x0000000000000a5d <+144>:  cdqe  
0x0000000000000a5f <+146>:  mov    BYTE PTR [rdx+rax*1+0x8c],cl   copy cl l_var1[l_var2] into 1st arg[l_var2 + 140]
0x0000000000000a66 <+153>:  add    DWORD PTR [rbp-0x4],0x1        add 1 into [rbp-0x4] (l_var2)
0x0000000000000a6a <+157>:  cmp    DWORD PTR [rbp-0x4],0x28       compare [rbp-0x4] (l_var2) with 40
0x0000000000000a6e <+161>:  jg     0xa81 <set_username+180>       jump if greater to line 180
0x0000000000000a70 <+163>:  mov    eax,DWORD PTR [rbp-0x4]        copy [rbp-0x4] (l_var2) into eax
0x0000000000000a73 <+166>:  cdqe  
0x0000000000000a75 <+168>:  movzx  eax,BYTE PTR [rbp+rax*1-0x90]  move zero extend -> l_var1[l_var2] into eax
0x0000000000000a7d <+176>:  test   al,al                          test if 0 -> if l_var1[l_var2] == 0
0x0000000000000a7f <+178>:  jne    0xa46 <set_username+121>       jump not equal to line 121
0x0000000000000a81 <+180>:  mov    rax,QWORD PTR [rbp-0x98]       copy 1st arg into rax
0x0000000000000a88 <+187>:  lea    rdx,[rax+0x8c]                 load address of rax (1st arg[140]) into rdx as 2nd arg for printf
0x0000000000000a8f <+194>:  lea    rax,[rip+0x165]        # 0xbfb load address of ">: Welcome, %s" into rax as 1st arg for printf
0x0000000000000a96 <+201>:  mov    rsi,rdx  
0x0000000000000a99 <+204>:  mov    rdi,rax  
0x0000000000000a9c <+207>:  mov    eax,0x0  
0x0000000000000aa1 <+212>:  call   0x750 <printf@plt>             call function printf
0x0000000000000aa6 <+217>:  leave 
0x0000000000000aa7 <+218>:  ret 


main()
0x0000000000000aa8 <+0>:    push   rbp  
0x0000000000000aa9 <+1>:    mov    rbp,rsp  
0x0000000000000aac <+4>:    lea    rdi,[rip+0x15d]        # 0xc10 
0x0000000000000ab3 <+11>:   call   0x730 <puts@plt>               call function puts
0x0000000000000ab8 <+16>:   call   0x8c0 <handle_msg>             call function handle_msg
0x0000000000000abd <+21>:   mov    eax,0x0  return 0
0x0000000000000ac2 <+26>:   pop    rbp  
0x0000000000000ac3 <+27>:   ret 
```