#include <stdio.h>
#include <string.h>

typedef struct	s_msg { // total size 192 base on the buffer in handle_msg
	char		msg[140];     // [0x0]
	char		username[40]; // [0x8c]
	size_t	len;          // [0xb4]
}				        t_msg;

void secret_backdoor(void) {
	char str[128];

	fgets(str, 128, stdin); 
	system(str);
}

void set_msg(t_msg* msg) {
	char	str[1024];

	memset(str, 0, 1024);
	puts(">: Msg @Unix-Dude");
	printf(">>: ");
	fgets(str, 1024, stdin);
	strncpy(msg->msg, str, msg->len);
}

void set_username(t_msg* msg){
	int index;
	char str[128];

	memset(str, 0, 128);
	puts(">: Enter your username");
	printf(">>: ");
	fgets(str, 128, stdin);

  index = 0;
	while (index < 41 && str[index] != '\0')
	{
		msg->username[index] = str[index];
		index++;
	}
	printf(">: Welcome, %s", msg->username);
}

void handle_msg(void) {
	t_msg msg;
	msg->len = 140;
  memset(msg.username, 0, 40);
	set_username(&msg);
	set_msg(&msg);
	puts(">: Msg sent!");
}

int main(void) {
  puts("--------------------------------------------
        \n|~Welcome to l33t-m$n ~    v1337        |\n
        --------------------------------------------");
  handle_msg();
  return (0);
}