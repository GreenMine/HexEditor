#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "args.h"

#define COMMAND_COUNT 4

int hex_open(cmd_args_t arguments);

int hex_create(cmd_args_t arguments);

int hex_exit();

int hex_help();

FILE* fp;

struct {
	int name;
	const char* description;
	int (*f)(cmd_args_t arguments);
} commands[COMMAND_COUNT] = {
	{'o', "Opening .bin file", hex_open}, {'c', "Create new .bin file", hex_create}, {'e', "Close program", hex_exit}, {'h', "Information about commands", hex_help}
};

int main() {
	char command_buffer[64] = {0x00};
	bool cmd_exists;
	while (true) {
		cmd_exists = false;
		printf("XHE $> ");
		gets(command_buffer);
		for (int i = 0; i < COMMAND_COUNT; i++) {
			if (commands[i].name == command_buffer[0]) {
				cmd_args_t cmd = to_pretty_arguments(command_buffer);
				commands[i].f(cmd);
				free_arguments(cmd);
				cmd_exists = true;
				break;
			}
		}
		if (!cmd_exists)
			printf("Command not exists.\nType 'h' to get all commands\n");
	}
	return 0;
}

int hex_open(cmd_args_t arguments) {
	printf("Arguments(%d):\n", arguments.count);
	for (int i = 0; i < arguments.count; i++)
		printf("[%d] %s\n", i + 1, arguments.arguments[i]);
	return 0;
}

int hex_create(cmd_args_t arguments) {
	return 0;
}

int hex_help() {
	printf("Commands(%d):\n", COMMAND_COUNT);
	for (int i = 0; i < COMMAND_COUNT; i++)
		printf("%c - %s\n", commands[i].name, commands[i].description);
	return 0;
}

int hex_exit() {
	system("pause");
	exit(0);
	return 0;
}