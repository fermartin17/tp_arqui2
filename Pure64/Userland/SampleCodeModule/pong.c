#include "myPrintf.h"
#include "myPutchar.h"
#include "stdlib.h"
#include "SysCallDispatcher.h"
#include "myGetChar.h"

void digitalClock() {
  int x1o=screen_width()-(screen_width()-10);
  int x1f=screen_width()-(screen_width()-17);
  int x2o,x2f,y2o,y2f;
  int y1o=((screen_height()-10)/2)+10; //revisar ejes
  int y1f=((screen_height()-10)/2)-10;
  int puntaje1=0,puntaje2=0;
  int jug1,jug2;
	int aux;
	char c;
	clearScreen();
	setCursor(screen_width()-(screen_width()-1),screen_height());
	myPrintf("Jueguito Pong (presione Enter para salir)\n");
	setCursor(screen_width()-(screen_width()/2),screen_height()-5);
	myPrintf("jugador 1 =%d\n");
		while((c=myGetChar()) != '\n') {
      for(int i = x1o;i<= x1f;i++){
        for(int j = )
      }
			if(c == ' ')
			{
				if(color == 5) {
					color = 1;
				} else {
					color++;
				}
				beep();
			}
			if(hour < 10) {
				myPutcharBig('0',color);
				myPutcharBig(hour+'0',color);
			} else {
				aux = hour%10;
				myPutcharBig((hour/10)+'0',color);
				myPutcharBig(aux+'0',color);
			}
			myPutcharBig(':',color);
			if(minute < 10) {
				myPutcharBig('0',color);
				myPutcharBig(minute+'0',color);
			} else {
				aux = minute%10;
				myPutcharBig((minute/10)+'0',color);
				myPutcharBig(aux+'0',color);
			}
			myPutcharBig(':',color);
			if(seconds < 10) {
				myPutcharBig('0',color);
				myPutcharBig(seconds+'0',color);
			} else {
				aux = seconds%10;
				myPutcharBig((seconds/10)+'0',color);
				myPutcharBig(aux+'0',color);
			}
		}
	clearScreen();
	setCursor(0, screen_height()-char_height());
	return;
}
