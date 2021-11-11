#include <string.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
	char	str_username[112];
	char	str_file[48];
	char	str_password[112];
	FILE	*fd;
	size_t	read_char;

	memset(str_username, 48);
	memset(str_file, 20);
	memset(str_password, 48);
	if ((fd = fopen("/home/users/level03/.pass", "r")) == NULL) {
		fwrite("ERROR: failed to open password file\n", 1, 36, stderr);
		exit(1);
	}
	read_char = fread(str_file, 1, 41, fd);
	str_file[strcspn(str_file, "\n")] = '\0';
	if (read_char != 41) {
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