//#define __CRTDBG_MAP_ALLOC
//#include <crtdbg.h>
//#define DEBUG_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__)
//#define new DEBUG_NEW
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "args.h"

int hex_open(cmd_args_t arguments);

int hex_create(cmd_args_t arguments);

int hex_exit();

FILE* fp;

int main() {
	struct {
		int command_name; 
		int (*command_f)(cmd_args_t arguments); /*Функция обработки*/
	} m[3] = {
	{'o', hex_open }, {'c', hex_create }, {'e', hex_exit}};

	char command_buffer[64] = {0x00};
	while (true) {
		printf("XHE $> ");
		gets(command_buffer);
		//putchar('\n');
		for (int i = 0; i < 2; i++) {
			if (m[i].command_name == command_buffer[0]) {
				cmd_args_t cmd = to_pretty_arguments(command_buffer);
				m[i].command_f(cmd);
				free_arguments(cmd);
				break;
			}
		}
	}
	//_CrtDumpMemoryLeaks();
	return 0;
}

int hex_open(cmd_args_t arguments) {
	printf("Arguments(%d):\n", arguments.count);
	for (int i = 0; i < arguments.count; i++)
		printf("[%d] %s\n", i + 1, arguments.arguments[i]);
	return 1;
}

int hex_create(cmd_args_t arguments) {
	printf("Arguments for test_2: %s\n", arguments);
	return 0;
}


int hex_exit() {
	system("pause");
	exit(0);
	return 0;
}