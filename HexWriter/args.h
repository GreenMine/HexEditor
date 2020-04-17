#pragma once
#include <stdint.h>
#include <string.h>

#define ARGUMENT_SIZE 20
#define ARGUMENT_COUNT 5

;typedef struct CommandArguments {
	uint32_t count;
	const char **arguments;
} cmd_args_t;


char* alloc_string() {
	return malloc(ARGUMENT_SIZE);
}

cmd_args_t to_pretty_arguments(const char* data) {
	cmd_args_t arguments;
	arguments.count = 0;
	char** args = malloc(ARGUMENT_COUNT * 4);
	int iter = 0, symbol_iter = 0;
	args[0] = alloc_string();
	for (int i = 0; i < strlen(data) + 1; i++) {
		if (data[i] == ' ' || data[i] == 0x00) {
			args[iter][symbol_iter] = 0x00;
			iter++;
			args[iter] = alloc_string();
			symbol_iter = 0;
			arguments.count++;
			continue;
		}
		args[iter][symbol_iter] = data[i];
		symbol_iter++;
	}
	arguments.arguments = args;
	return arguments;
}

void free_arguments(cmd_args_t cmd) {
	
	for (int i = 0; i < cmd.count; i++) {
		free(cmd.arguments[i]);
	}
	free(cmd.arguments);
}