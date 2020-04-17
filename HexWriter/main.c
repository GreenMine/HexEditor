#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "args.h"
#include "utilities.h"

#define COMMAND_COUNT 5

#define TABLE_NUMBERS_COUNT 16

int hex_open(cmd_args_t arguments);

int hex_watch();

int hex_create(cmd_args_t arguments);

int hex_exit();

int hex_help();

FILE* fp;

struct {
	int name;
	const char* description;
	int (*f)(cmd_args_t arguments);
} commands[COMMAND_COUNT] = {
	{'o', "Opening .bin file", hex_open}, {'w', "Watching file", hex_watch}, {'c', "Create new .bin file", hex_create},  {'h', "Information about commands", hex_help}, {'e', "Close program", hex_exit}
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
	if ((fp = fopen(arguments.arguments[1], "r+b")) == NULL) {
		printf("File %s is not exists\n", arguments.arguments[1]);
		return 1;
	}
	fseek(fp, 0, SEEK_END);
	printf("File success opened. Size of file %s: %ldb.\n", arguments.arguments[1], ftell(fp));
	return 0;
}

int hex_watch() {
	if (fp == NULL) {
		printf("File is not opened. Write 'o filename' to open file.");
		return 1;
	}
	char current_bits, ascii_buffer[TABLE_NUMBERS_COUNT + 1];
	ascii_buffer[TABLE_NUMBERS_COUNT] = 0x00;
	int iterator = 0, ascii_iterator = 0;
	fseek(fp, 0, SEEK_SET);
	while ((current_bits = fgetc(fp)) != EOF ) {
		printf("%02X ", current_bits);
		ascii_buffer[ascii_iterator++] = to_table_format(current_bits);
		if (!(++iterator % TABLE_NUMBERS_COUNT)) {
			printf("\t%s\n", ascii_buffer);
			ascii_iterator = 0;
			memset(ascii_buffer, '.', TABLE_NUMBERS_COUNT);
		}
	}

	for (int i = ascii_iterator; i < TABLE_NUMBERS_COUNT; i++) {
		printf("00 ");
	}
	printf("\t%s\n", ascii_buffer);
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