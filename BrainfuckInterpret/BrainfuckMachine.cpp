#include "stdafx.h"
#include <iostream>
#include "BrainfuckMachine.h"

BrainfuckMachine::BrainfuckMachine() {
	memory_ptr = memory_first_cell_ptr;
	output_ptr = output_first_el_ptr;

	fill_buffer_with_nulls(memory, MEMORY_SIZE);
	fill_buffer_with_nulls(output, OUTPUT_SIZE);
}
void BrainfuckMachine::fill_buffer_with_nulls(char* buffer, int size) {
	for (int i = 0; i < size; i++)
		buffer[i] = '\0';
}
void BrainfuckMachine::write_error_to_output(const char* error_msg) {
	if ((&output[OUTPUT_SIZE - 1] - output_ptr) / sizeof(char) > strlen(error_msg))
		strcpy_s(output_ptr, strlen(error_msg) + 1, error_msg);
	else
		strcpy_s(&output[0], strlen(error_msg) + 1, error_msg);
}
int BrainfuckMachine::read_cycle_body_size(char* script) {
	int _size = 0;
	int open_brackets = 1;
	script++;
	if (!(*script))
		return -1;
	while (open_brackets) {
		if (*script == '[')
			open_brackets++;
		if (*script == ']')
			open_brackets--;

		script++;
		_size++;

		if (!(*script))
			return -1;
	}
	return _size - 1;
}
char* BrainfuckMachine::interpret(char*& script, char* input, int size) {
	int count = 0;

	while (*script) {
		bool symbol_interpreted = false;

		if ((++count) > size)
			return output_first_el_ptr;

		char script_c = *script;

		if (script_c == '>')
			if (memory_ptr != memory_last_cell_ptr) {
				memory_ptr++;
				symbol_interpreted = true;
			}
			else {
				write_error_to_output(ERROR_MESSAGE_OUT_OF_TOP_BOUNDS);
				return output_first_el_ptr;
			}
	
		if (script_c == '<')
			if (memory_ptr != memory_first_cell_ptr) {
				memory_ptr--;
				symbol_interpreted = true;
			}
			else {
				write_error_to_output(ERROR_MESSAGE_OUT_OF_BOT_BOUNDS);
				return output_first_el_ptr;
			}

			if (script_c == '+') {
				(*memory_ptr)++;
				symbol_interpreted = true;
			}
			if (script_c == '-') {
				(*memory_ptr)--;
				symbol_interpreted = true;
			}

		if (script_c == '[') {
			int _size;
			char* cycle_body = script + 1;
			char* cycle_body_first = cycle_body;
			if ((_size = read_cycle_body_size(script)) == -1) {
				write_error_to_output(ERROR_MESSAGE_NO_CLOSING_BRACKET);
				return output_first_el_ptr;
			}
			while (*memory_ptr) {
				cycle_body = cycle_body_first;
				interpret(cycle_body, input, _size);
			}
			script = cycle_body;
			symbol_interpreted = true;
		}
		if (script_c == ',')
			if (!((*memory_ptr) = (*(input++)))) {
				write_error_to_output(ERROR_MESSAGE_REQUESTED_INPUT_DOES_NOT_EXIST);
				return output_first_el_ptr;
			} 
			else {
				symbol_interpreted = true;
			}
		if (script_c == '.')
			if (output_ptr <= output_last_el_ptr) {
				(*(output_ptr++)) = (*memory_ptr);
				symbol_interpreted = true;
			}
			else {
				write_error_to_output(ERROR_MESSAGE_OUTPUT_BUFFER_OVERFLOW);
				return output_first_el_ptr;
			}
		if (!symbol_interpreted) {
			write_error_to_output(ERROR_MESSAGE_UNABLE_TO_INTERPRET_SYMBOL);
			return output_first_el_ptr;
		}
		script++;
	}
	(*(++output_ptr)) = END_OF_LINE;
	return output_first_el_ptr;
}