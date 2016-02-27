#pragma once
#include <string>

class BrainfuckMachine {
	const char END_OF_LINE = '\0';
	const char* ERROR_MESSAGE_OUT_OF_TOP_BOUNDS              = "Error. Out of bounds. Access through address lower than first memory cell address.";
	const char* ERROR_MESSAGE_OUT_OF_BOT_BOUNDS              = "Error. Out of bounds. Access through address lower than first memory cell address.";
	const char* ERROR_MESSAGE_NO_CLOSING_BRACKET             = "Error. No closing bracket.";
	const char* ERROR_MESSAGE_REQUESTED_INPUT_DOES_NOT_EXIST = "Error. The requested input data does not exist.";
	const char* ERROR_MESSAGE_OUTPUT_BUFFER_OVERFLOW         = "Error. Output buffer overflow.";
	const char* ERROR_MESSAGE_UNABLE_TO_INTERPRET_SYMBOL     = "Error. Symbol can't be interpreted.";
	static const int OUTPUT_SIZE = 512;
	static const int MEMORY_SIZE = 3000;

	char memory[MEMORY_SIZE];
	char* memory_ptr;
	char * const memory_first_cell_ptr = &memory[0];
	char * const memory_last_cell_ptr  = &memory[OUTPUT_SIZE - 1];

	char output[OUTPUT_SIZE];
	char* output_ptr;
	char * const output_first_el_ptr = &output[0];
	char * const output_last_el_ptr  = &output[OUTPUT_SIZE - 1];

	void fill_buffer_with_nulls(char* carr, int size);

	int read_cycle_body_size(char* script);

	void write_error_to_output(const char* error_msg);
public:
	BrainfuckMachine();
	char* interpret(char*& script, char* input, int size);
};
