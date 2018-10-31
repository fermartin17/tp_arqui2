#include <time.h>
#include <read.h>
#include <write.h>
#include <naiveConsole.h>
#include <speaker.h>
#include <stdint.h>
#include <font.h>

#define PAINT 1
#define CLOCK 2
#define READ 3
#define WRITE 4
#define SPEAKER 5
#define CURSOR 6
#define INFO 7
#define WRITE_BIG 8

static void info_handler(int p1, int* p2);

/*
	1 =	PAINT PIXEL					p1 = x
													p2 = y
													p3 = color

	2 = GET CLOCK						Saves (H:M:S) in (p1:p2:p3) pointers

	3 = READ FROM KEYBOARD	p1 				Where to save next char in buffer

	4 = PRINT ON SCREEN			p1 = 0		Print message
													p1 = 1		Print error
													p1 = 2		New line
													p2 				String to print
													p3				How many chars to print

	5 = USE SPEAKER

	6 = CURSOR							p1 = x
													p2 = y

	7 = INFO								p1 = 0		SCREEN_WIDTH
													p1 = 1		SCREEN_HEIGHT
													p1 = 2		CHAR_WIDTH
													p1 = 3		CHAR_HEIGHT
													p1 = 4		CURSOR_X
													p1 = 5		CURSOR_Y
													p2				where to save result

	8 = BIG TEXT						p1 = 0		New line
													p1 = 1		White color
													p1 = 2		Red color
													p1 = 3		Blue color
													p1 = 4		Green color
													p1 = 5		Yellow color
													p2 				String to print
													p3				How many chars to print
*/

void SysCallDispatcher(uint64_t id, uint64_t p1, uint64_t p2, uint64_t p3) {
	switch (id)
	{
		case PAINT:
								putpixel((unsigned int)p1, (unsigned int)p2, (int)p3);
								break;
		case CLOCK:
								clock_handler((int*) p1, (int*) p2, (int*) p3);
								break;
		case READ:
								read_buffer_handler((char*) p1);
								break;
		case WRITE:
								write_handler(p1, (char*) p2, (int) p3);
								break;
		case SPEAKER:
								speaker_handler();
								break;
		case CURSOR:
								setCursor((unsigned int)p1, (unsigned int)p2);
								break;
		case INFO:
								info_handler((int) p1, (int*) p2);
								break;
		case WRITE_BIG:
								big_handler(p1, (char*)p2, (int)p3);
								break;
	}
}

static void info_handler(int p1, int* p2)
{
	switch(p1)
	{
		case 0:	*p2 = getScreenWidth();
						break;
		case 1:	*p2 = getScreenHeight();
						break;
		case 2: *p2 = getCharWidth();
						break;
		case 3:	*p2 = getCharHeight();
						break;
		case 4:	*p2 = getCursorX();
						break;
		case 5: *p2 = getCursorY();
						break;
	}
}
