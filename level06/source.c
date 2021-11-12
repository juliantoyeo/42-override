#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/ptrace.h>

int auth(char* login, int serial) {
  int len;       // ebp-0xc
  int result;    // ebp-0x10

  login[strcspn(login, "\n")] = '\0'
  len = strnlen(login, 32);
  if (len <= 5)
    return (1);
  if (ptrace(0, 0, 1, 0) == -1) {
    return (1);
  }
  // This part is abit complicated to revert, but the idea will be to use login and serial to go through
  // a series of checking (base on ghidra decompiled result) so i represent it with the hash()
  // after ward, it will perform a checking between len and result and return 0 if they are equal
  result = hash(login, serial);
  if (serial == result) {
    return (0);
  }
  return (1);
}

int main() {
  char login[32];
  int serial;

  puts("***********************************");
  puts("*\t\tlevel06\t\t  *");
  puts("***********************************");
  printf("-> Enter Login: ");
  fgets(login, 32, stdin);
  puts("***********************************");
  puts("***** NEW ACCOUNT DETECTED ********");
  puts("***********************************");
  printf("-> Enter Serial: ");
  scanf("%u", &serial);
  if (auth(login, serial) == 0) {
    puts("Authenticated!");
    system("/bin/sh");
    return (0);
  }
  return (1);
}