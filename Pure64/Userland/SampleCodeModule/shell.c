#include "myPrintf.h"
#include "myScanf.h"
#include "myPutchar.h"
#include "myGetChar.h"
#include "time.h"
#include "stdlib.h"
#include "exception.h"

#define START 0
#define HELP 1
#define EXCEPTION_ZERO_DIVISION 2
#define EXCEPTION_INVALID_COMMAND 3
#define CLOCK 4
#define DIGITAL_CLOCK 5
#define BACKSPACE 14
#define BUFFER_SIZE 80

void invalid_command(char * s) {
	myPrintf("%s: command not found\n",s);
	return;
}

void Help() {
	myPutchar('\n');
	myPrintf("   zeroException\n\n");
	myPrintf("   opException\n\n");
	myPrintf("   clock\n\n");
	myPrintf("   digitalclock\n\n");
	myPutchar('\n');
}

void zeroDivision() {
	int i = 0;
	i = 10/i;
	return;
}

void interprete(char * s) {
	//myPrintf("\n");
	//myPrintf("");
	int estado = START;
	char * help = "help";
	char * zeroException = "zeroException";
	char * opException = "opException";
	char * clock = "clock";
	char * digitalclock = "digitalclock";
	int dim = strlen(s);
	for(int i=0;i<dim;i++) {
		switch(estado) {
			case START:
					if(s[i] == help[i]) {
						estado = HELP;
					} else if(s[i] == zeroException[i]) {
						estado = EXCEPTION_ZERO_DIVISION;
					} else if(s[i] == opException[i]) {
						estado = EXCEPTION_INVALID_COMMAND;
					} else if(s[i] == clock[i]) {
						estado = CLOCK;
					} else if(s[i] == digitalclock[i]) {
						estado = DIGITAL_CLOCK;
					} else {
						invalid_command(s);
						return;
					}
					break;
			case HELP:
					//if command is longer or doesn't match help
					if(help[i] == 0 || s[i] != help[i] || s[i+1] != help[i+1]) {
						invalid_command(s);
						return;
					}
					break;
			case EXCEPTION_ZERO_DIVISION:
					//if command is longer or doesn't match zeroException
					if(zeroException[i] == 0 || s[i] != zeroException[i] || s[i+1] != zeroException[i+1]) {
						invalid_command(s);
						return;
					}
					break;
			case EXCEPTION_INVALID_COMMAND:
					//if command is longer or doesn't match opException
					if(opException[i] == 0 || s[i] != opException[i] || s[i+1] != opException[i+1]) {
						invalid_command(s);
						return;
					}
					break;
			case CLOCK:
					//if command is longer or doesn't match clock
					if(clock[i] == 0 || s[i] != clock[i] || s[i+1] != clock[i+1]) {
						invalid_command(s);
						return;
					}
					break;
			case DIGITAL_CLOCK:
					//if command is longer or doesn't match digitalclock
					if(digitalclock[i] == 0 || s[i] != digitalclock[i] || s[i+1] != digitalclock[i+1]) {
						invalid_command(s);
						return;
					}
					break;
		}
	}
	//
	switch(estado) {
		//shows all possible commands
		case HELP:
			Help();
			break;
		//shows an example of zero division
		case EXCEPTION_ZERO_DIVISION:
			zeroDivision();
			break;
		//shows an example of invalid command
		case EXCEPTION_INVALID_COMMAND:
			_throwInvalidopCode();
			break;
		//shows the time
		case CLOCK:
			watch();
			break;
		//shows the virtual clock with colors
		case DIGITAL_CLOCK:
			digitalClock();
			break;
	}
	return;
}

void shell() {
	setCursor(0, screen_height()-char_height());
	char c;
	int i=0;
	char string[BUFFER_SIZE]={0};
	while(1) {
		myPrintf("%s$: ","user");
		while(((c=myGetChar()) != '\n') && i<BUFFER_SIZE){
			if(c == BACKSPACE) {
				if(i != 0) {
					i--;
					setCursor(char_width()*(i+7),screen_height()-char_height());
					myPutchar(' ');
					setCursor(char_width()*(i+7),screen_height()-char_height());
				}
			} else if(c!=0) {
				string[i++]=c;
				myPutchar(c);
			}
		}
		string[i]=0;
		i=0;
		//myPrintf("   %s", string);
		myPutchar('\n');
		interprete(string);
	}
}
