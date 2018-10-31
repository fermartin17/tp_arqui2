#include "SysCallDispatcher.h"

#define BLACK_BACKGROUND 0x000000 

void setCursor(int x, int y)
{
	SysCallDispatcher(6, (uint64_t)x, (uint64_t)y, 0);
}

void beep()
{
	SysCallDispatcher(5, 0, 0, 0);
}

int screen_width()
{
	int ret_value;
	SysCallDispatcher(7,0,(uint64_t)&ret_value,0);
	return ret_value;
}

int screen_height()
{
	int ret_value;
	SysCallDispatcher(7, 1, (uint64_t)&ret_value, 0);
	return ret_value;
}

int char_width()
{
	int ret_value;
	SysCallDispatcher(7,2,(uint64_t)&ret_value,0);
	return ret_value;
}

int char_height()
{
	int ret_value;
	SysCallDispatcher(7, 3, (uint64_t)&ret_value, 0);
	return ret_value;
}

void clearScreen() {
	for(int x=0;x<screen_width();x++) {
		for(int y=0;y<screen_height();y++) {
			SysCallDispatcher(1,x,y,BLACK_BACKGROUND);
		}
	}
}
