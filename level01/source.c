#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char a_user_name[100];

int verify_user_name(void) {
    puts("verifying username....\n");
    return strncmp(a_user_name, "dat_wil", 7);
}

int verify_user_pass(char *pass) {
    return strncmp(pass, "admin", 5);
}

int main() {
  char    pass[64] = { };
  int     check = 0;

  memset(str, 0, 64);
  puts("********* ADMIN LOGIN PROMPT *********");
  printf("Enter Username: ");
  fgets(a_user_name, 256, stdin);
  check = verify_user_name();
  if (check != 0) {
    puts("nope, incorrect username...\n");
    return (1);
  }
  puts("Enter Password: ");
  fgets(pass, 100, stdin);
  check = verify_user_pass(pass);
  if (check == 0) {
    puts("nope, incorrect password...\n");
    return (1);
  }
  if (check == 0)
    return (0);
}