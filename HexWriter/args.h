#pragma once
#include <stdint.h>
#include <string.h>

#define ARGUMENT_SIZE 20
#define ARGUMENT_COUNT 5

;typedef struct CommandArguments {
	uint32_t count;
	char **arguments;
} cmd_args_t;


char* alloc_string() {
	return malloc(ARGUMENT_SIZE);
}

cmd_args_t to_pretty_arguments(const char* data) {
	cmd_args_t arguments;
	arguments.count = 0;
	arguments.arguments = malloc(ARGUMENT_COUNT * 4);
	int iter = 0, symbol_iter = 0;
	arguments.arguments[0] = alloc_string();
	for (int i = 0; i < strlen(data); i++) {
		if (data[i] == ' ') {
			arguments.arguments[iter][symbol_iter] = 0x00;
			iter++;
			arguments.arguments[iter] = alloc_string();
			symbol_iter = 0;
			arguments.count++;
			continue;
		}
		arguments.arguments[iter][symbol_iter] = data[i];
		symbol_iter++;
	}
	arguments.count++;
	arguments.arguments[iter][symbol_iter] = 0x00;
	return arguments;
}

void free_arguments(cmd_args_t cmd) {
	for (int i = 0; i < cmd.count; i++) {
		free(cmd.arguments[i]);
	}
	free(cmd.arguments);
}