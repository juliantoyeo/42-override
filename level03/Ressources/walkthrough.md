# Level 03

<h3>source.c</h3>

```console
void decrypt(int nb)
{
	char* str = "Q}|u`sfg~sf{}|a3";
	int len;
	int i;

	len = strlen(str);
	i = 0;
	while (i < len) {
		str[i] = nb ^ str[i];
		i++;
	}
	if (strncmp("Congratulations!", str, 17) == 0) {
		system("/bin/sh");
	}
	else {
		puts("\nInvalid Password");
	}
}

void test(int nb, int huge_number) {
	int res;

	res = huge_number - nb;
	if (res <= 21) {
			decrypt(res);
	}
	decrypt(rand());
}

int main(){
	int	nb;

	srand(time(0));
	puts("***********************************");
	puts("*\t\tlevel03\t\t**");
	puts("***********************************");
	printf("Password:");
	scanf("%d", &nb);
	test(nb, 322424845);
  return (0);
}
```

<h3>Analysis</h3>

This program asm code is quite a mess and hard to reserver, so the source might not be very accurate, but it contains at least the essential info

We are expecting to put a number and this number will be use to deducting the huge_number `322424845`, we need to input some number to make the result inside the `test()` to be <= 21

Else the program will run the `decrypt()` with random number, which will guarantee that it will resulted in `\nInvalid Password`

Next, when the program start the `decrypt()`,  there is a weird string "Q}|u`sfg~sf{}|a3" and the function will use the number (huge_number - input number) as the variable to carry out xor

The target this time will be to find the correct number which will turn "Q}|u`sfg~sf{}|a3" into "Congratulations!" and we will get a shell

<h3>Exploit</h3>

To solve this problem, we need to know how `xor` work

`xor` will compare 2arg bit by bit, as long as either bit is 1, the result will be 1, but if both are 0, then it will be 0

example below

```console
1 = 0001
     xor
2 = 0010
     res
    0011 -> 3
```

After testing some different value form number 21 downward, it seems that number `18` is the golden number which could translate the whole weird string to `Congratulations!`

```console
Q (0x51) ^ 18 (0x12) = C (0x43)
} (0x7D) ^ 18 (0x12) = o (0x6F)
| (0x7C) ^ 18 (0x12) = n (0x6E)
```

Which this finding, we can could get the password by `322424845 - 18 = 322424827`, lets try it!

```console
level03@OverRide:~$ ./level03
***********************************
*		level03		**
***********************************
Password:322424827
$ whoami
level04
$ cat /home/users/level04/.pass
kgv3tkEb9h2mLkRsPkXRfc2mHbjMxQzvb2FrgKkf
```
