#define __CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#define DEBUG_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__)
#define new DEBUG_NEW
#include <stdio.h>
#include <stdbool.h>
#include "args.h"

int hex_open(cmd_args_t arguments);

int hex_create(cmd_args_t arguments);

FILE* fp;

int main() {
	struct {
		int command_name; 
		int (*command_f)(cmd_args_t arguments); /*Функция обработки*/
	} m[2] = {
	{ 'o', hex_open }, { 'c', hex_create }};

	char opcode;
	printf("Press enter to start:D");
	while (true) {
		getchar();
		printf("XHE $> ");
		opcode = getchar();
		//putchar('\n');
		for (int i = 0; i < 2; i++) {
			if (m[i].command_name == opcode) {
				cmd_args_t cmd = to_pretty_arguments("o t t");
				m[i].command_f(cmd);
				free_arguments(cmd);
				break;
			}
		}
		if (opcode == 'e') break;
	}
	_CrtDumpMemoryLeaks();
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