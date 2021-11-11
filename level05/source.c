#include <stdio.h>
#include <string.h>

int main(void) {
  char str[100];       // esp+0x28
  int  index;             // esp+0x8c

  fgets(str, 100, stdin);
  index = 0;
  while (index < strlen(str)) {
    if ('@' < str[index] && str[index] < 'Z') {
      str[index] = tolower(str[index]);
    }
    index += 1;
  };
  printf(str);
  exit(0);
}