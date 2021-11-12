#include <string.h>
#include <stdio.h>

int get_unum(void)
{
  int nb = 0;
  fflush(stdout);
  scanf("%u", &nb);
  clear_stdin();
  return nb;
}

int store_number(unsigned int *data)
{
	unsigned int nb = 0;
	unsigned int index = 0;

	printf(" Number: ");
	nb = get_unum();
	printf(" Index: ");
	index = get_unum();
	if (index % 3 == 0 || nb >> 24 == 183 ) {
		puts(" *** ERROR! ***");
		puts("   This index is reserved for wil!");
		puts(" *** ERROR! ***");
		return (1);
	}
	data[index] = nb;
	return (0);
}

int read_number(unsigned int *data) {
	int index = 0;     // [ebp-0xc]

	printf(" Index: ");
	index = get_unum();
	printf(" Number at data[%u] is %u\n", index, data[index]);
	return (0);
}

int main(int argc, char** argv) {
	unsigned int	data[100];    // [esp+0x24]
	int				    res = 0;      // [esp+0x1b4]
	char			    input[20];    // [esp+0x1b8]

	puts("----------------------------------------------------\n"
       "  Welcome to wil\'s crappy numberstorage service!   \n"
       "----------------------------------------------------\n"
       " Commands:                                          \n"
       "    store - store a number into the data storage    \n"
       "   read  - read a number from the data storage      \n"
       "    quit  - exit the program                        \n"
       "----------------------------------------------------\n"
       "   wil has reserved somestorage :>                  \n"
       "----------------------------------------------------\n");
	while(1) {
		printf("Input command: ");
		res = 1;
		fgets(input, 20, stdin);
		if (strncmp(input, "store", 5) == 0) {
      res = store_number(data);
    }
		else if (strncmp(input, "read", 4) == 0) {
      res = read_number(data);
    }
		else if (strncmp(input, "quit", 4) == 0)
			break;
		if (res != 0) {
			printf(" Failed to do %s command\n", input);
		}
		else {
			printf(" Completed %s command successfully\n", input);
		}
	}
	return (0);
}