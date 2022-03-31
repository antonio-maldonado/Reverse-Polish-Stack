
#include "stack.h"

bool empty(Stack *S )
{    return (S->top == -1);    }

bool pop( Stack *S, TIPO *valor )
{
  if ( empty(S) == true )
    return true;
  *(valor) = S->items[(S->top)--];
  return false;
}

bool push( Stack *S, TIPO valor )
{
  if ( S->top == STACKSIZE - 1 )
    return true;
  S->items[++(S->top)] = valor;
  return false;
}


