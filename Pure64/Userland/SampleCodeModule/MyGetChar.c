#include "SysCallDispatcher.h"
//Devuelve el primer caracter que hay en el buffer.
char myGetChar()
{
  char c=0;
    SysCallDispatcher(3,(uint64_t)&c,0,0);
  return c;
}
