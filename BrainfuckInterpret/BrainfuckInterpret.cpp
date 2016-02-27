#include "stdafx.h"
#include <conio.h>
#include <stdio.h>
#include "BrainfuckMachine.h"

int main()
{
	//char* script = "++++>,>,<<[>------------<-]++++[>>------------<<-]>[>+<-]++++[>++++++++++++<-]>."; const int script_length = strlen(script);
	char* script = "++++>,>,<<[>------------<-]++++[>>------------<<-]>[>+<-]++++[>++++++++++++<-]>."; const int script_length = strlen(script);
	char* input = "32";
	char* output = BrainfuckMachine().interpret(script, input, script_length);
	
	printf("%s", (output));
	_getch();
    return 0;
}

