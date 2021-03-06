#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "doOperator.h"
#include "tokenStack.h"
#include "lexical.h"

static int op_quit(struct tokenStack *stack);
static int op_print(struct tokenStack *stack);
static int op_dump(struct tokenStack *stack);
static int op_add(struct tokenStack *stack);

static struct operator_struct {
  char *name;
  int (*fn_ptr)(struct tokenStack *);
} ops[] = {
  {"quit", op_quit},
  {"print", op_print},
  {"dump", op_dump},
  {"+", op_add},
  {(char *)NULL, (int(*)(struct tokenStack *)) NULL}
};


/* YOU WRITE THIS */
static int popInt(struct tokenStack *s)
{
  if( s == NULL ) {
		fputs( "Error: bottom of stack!\n", stderr );
		exit( 1 );
	} else {
		struct tokenStack* top1 = s;
		int value = top1->top;
		s->e[--(s->top)];
		free( top1 );
		return value;
	}
	
}

/* YOU WRITE THIS */
static void pushInt(struct tokenStack *s, int v)
{

struct tokenStack* node = malloc( sizeof(struct tokenStack) );

	if( node == NULL ) {
		fputs( "Error: Out of memory\n", stderr );
		exit( 1 );
	} else {
		node->top = v;
		node->e = s;
		s = node;
}

}

int doOperator(struct tokenStack *stack, char *o) 
{
  struct operator_struct *op = ops;
  for(op=ops;op->name != (char *)NULL; op++) {
    if(!strcmp(op->name, o))
      return op->fn_ptr(stack);
  }
  return(-1);
}

/*ARGSUSED*/
static int op_quit(struct tokenStack *stack)
{
  printf("[quit]\n");
  exit(0);
  /*NOTREACHED*/
}

static int op_print(struct tokenStack *stack)
{
  struct lexToken *t = popTokenStack(stack);
  printToken(stdout, t);
  freeToken(t);
  return(0);
}

static int op_dump(struct tokenStack *stack)
{
  struct lexToken *t = popTokenStack(stack);
  dumpToken(stdout, t);
  freeToken(t);
  return(0);
}

static int op_add(struct tokenStack *stack)
{
  int v1, v2;
  v1 = popInt(stack);
  v2 = popInt(stack);
  pushInt(stack, v1+v2);
  return(0);
}
