#include "SysCallDispatcher.h"

void myPutchar(int character)
{
  if(character=='\n')
    SysCallDispatcher(4,2,0,0);
  else
    SysCallDispatcher(4,0,(uint64_t)&character,1);
  return;
}

void myPutcharBig(int character,int color) {
	if(character=='\n')
    	SysCallDispatcher(8,0,0,0);
  	else
   		SysCallDispatcher(8,color,(uint64_t)&character,1);
  	return;	
}
