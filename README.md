# Usefull Note

<h3>GDB</h3>

Common command

```console
gdb -q [binary]                                                   -> for quiet flag so there is no annoying message at the start of the debugger
info functions                                                    -> to list out all the functions information inside this binary
disas or disassemble [func_name]                                  -> to disassemble the function into assembly command
```

GDB Flavor

```console
set disassembly-flavor att
set disassembly-flavor intel
show disassembly-flavor
```

GDB hook-stop

```console
define hook-stop                                                  -> command that run at every break point
info registers                                                    -> show all register information
x/24wx $esp                                                       -> examine 24 (w) 32bit words as (x) hex start from the adress of esp
x/2i $eip                                                         -> examine next 2 instructions of eip
end
```

(clean version)

```console
define hook-stop
info registers
x/24wx $esp
x/2i $eip
end
```

Input bunch of characther into a program in gdb

```console
r <<< $(python -c "print 'a'*64")                                 -> as a file, for program that use gets or fgets
r `python -c "print 'a' * 64"`                                   -> as argv, for program that take input from argv
```

Reversing c++ name mangling

https://demangler.com/

AAAABBBBCCCCDDDDEEEEFFFFGGGGHHHHIIIIJJJJKKKKLLLLMMMMNNNNOOOOPPPPQQQQRRRRSSSSTTTTUUUUUVVVVWWWWXXXXYYYYZZZZ0000111122223333444455556666777788889999
1   2   3   4   5   6   7   8   9   10  11  12  13  14  15  16  17  18  19  20  21   22  23  24  25  26  27  28  29  30  31  32  33  34  35  36