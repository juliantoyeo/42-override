# Level 00

<h3>source.c</h3>

```console
int main(void) {
  int nb;

  puts("***********************************");
  puts("* \t     -Level00 -\t\t  *");
  puts("***********************************");
  printf("Password:");
  scanf("%d", &nb);
  if (nb == 5276) {
    puts("\nAuthenticated!");
    system("/bin/sh");
    return (0);
  }
  puts("\nInvalid Password!");
  return (1);
}
```

<h3>Analysis</h3>

This program will await user input via `scanf()` and will read any input given as a `digit`

Base on this finding, as long as we give `5276` as input, it should spawn a shell

<h3>Exploit</h3>

```console
level00@OverRide:~$ ./level00
***********************************
* 	     -Level00 -		  *
***********************************
Password:5276

Authenticated!
$ whoami
level01
$ cat /home/users/level01/.pass
uSq2ehEGT6c9S24zbshexZQBXUGrncxn5sD5QfGL
```