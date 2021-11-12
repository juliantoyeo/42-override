#include <stdio.h>
#include <string.h>

void log_wrapper(FILE* file, char* msg, char* filename) {
	char	str[264];  // [rbp-0x110]

	strcpy(str, msg);
	snprintf(str[strlen(str)], 254 - strlen(str), filename);
	str[strcspn(str, "\n")] = '\0';
	fprintf(file, "LOG: %s\n", str);
}

int main(int argc, char **argv) {
  FILE* fs_1;      // [rbp-0x88]
  FILE* fs_2;      // [rbp-0x80]
  int   fd = -1;   // [rbp-0x78]
  char  c = -1;    // [rbp-0x71]
  char* path;      // [rbp-0x70]

  if (argc != 2) {
    printf("Usage: %s filename\n", argv[0]);
  }

  fs_1 = fopen("./backups/.log","w");
  if (fs_1 == 0) {
    printf("ERROR: Failed to open %s\n", "./backups/.log");
    exit(1);
  }

  log_wrapper(fs_1, "Starting back up: ", argv[1]);

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

  log_wrapper(fs_1, "Finished back up ", argv[1]);

  fclose(fs_2);
  close(fd);
  return 0;
}