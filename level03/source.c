#include <time.h>
#include <stdlib.h>

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