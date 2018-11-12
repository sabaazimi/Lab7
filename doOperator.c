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
static int op_diff(struct tokenStack *stack);
static int op_product(struct tokenStack *stack);
static int op_quotient(struct tokenStack *stack);
static int op_gt(struct tokenStack *stack);
static int op_lt(struct tokenStack *stack);
static int op_ge(struct tokenStack *stack);
static int op_le(struct tokenStack *stack);
static int op_eq(struct tokenStack *stack);
static int op_rem_quotient(struct tokenStack *stack);

static struct operator_struct {
  char *name;
  int (*fn_ptr)(struct tokenStack *);
} ops[] = {
  {"quit", op_quit},
  {"print", op_print},
  {"dump", op_dump},
  {"+", op_add},
  {"-", op_diff},
  {"*", op_product},
  {"/", op_quotient},
  {">", op_gt},
  {"<", op_lt},
  {">=", op_ge},
  {"=<", op_le},
  {"==", op_eq},
  {"%", op_rem_quotient},
  {(char *)NULL, (int(*)(struct tokenStack *)) NULL}
};


/* YOU WRITE THIS */
static int popInt(struct tokenStack *s)
{
	
	struct lexToken *tocken;
	
	if(token == (struct lexToken *) NULL)
    fprintf(fd, "dumpToken: null token\n");
  else {
    switch(token->kind) {
    case LEX_TOKEN_EOF :
      ops[0];
      break;
    case LEX_TOKEN_IDENTIFIER:
      fprintf(fd, "dumpToken: identifier token |%s|\n", token->symbol);
      break;
    case LEX_TOKEN_OPERATOR:
      fprintf(fd, "dumpToken: operator token |%s|\n", token->symbol);
      break;
    case LEX_TOKEN_NUMBER:
      fprintf(fd, "dumpToken: number token |%s|\n", token->symbol);
      break;
    default:
      fprintf(fd, "dumpToken: bad token type %d\n", token->kind);
    }
  }
	





	
  if( s == NULL ) {
		fputs( "Error: bottom of stack!\n", stderr );
		exit( 1 );
	} else {
		struct tokenStack* top1 = s;
		int value = top1->e[top1->top]->kind;
		/*s->e[--(s->top)];*/
		free( top1 );
		return value;
	}
	
}

/* YOU WRITE THIS */
static void pushInt(struct tokenStack *s, int v)
{

	struct tokenStack* node = malloc( sizeof(struct tokenStack) );
	struct lexToken *lt = malloc( sizeof(struct lexToken) );
	
	lt->kind = v ;
	

	if( node == NULL ) {
		fputs( "Error: Out of memory\n", stderr );
		exit( 1 );
	} else {
		/*node->e[s->top]->kind = v;*/
		s->e[s->top++] = lt ;
		/*node->e[node->top++]= s->e;*/
	
		
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

static int op_diff(struct tokenStack *stack)
{
  int v1, v2;
  v1 = popInt(stack);
  v2 = popInt(stack);
  pushInt(stack, v1-v2);
  return(0);
}


static int op_product(struct tokenStack *stack)
{
  int v1, v2;
  v1 = popInt(stack);
  v2 = popInt(stack);
  pushInt(stack, v1*v2);
  return(0);
}

static int op_quotient(struct tokenStack *stack)
{
  int v1, v2;
  v1 = popInt(stack);
  v2 = popInt(stack);
  pushInt(stack, v1/v2);
  return(0);
}

static int op_gt(struct tokenStack *stack)
{
  int v1, v2;
  v1 = popInt(stack);
  v2 = popInt(stack);
  if(v1 > v2){
	pushInt(stack, 1);}
  else{
	pushInt(stack, 0);}	
  return(0);
}

static int op_lt(struct tokenStack *stack)
{
  int v1, v2;
  v1 = popInt(stack);
  v2 = popInt(stack);
  if(v1 > v2){
	pushInt(stack, 0);}
  else{
	pushInt(stack, 1);}	
  return(0);
}


static int op_ge(struct tokenStack *stack)
{
  int v1, v2;
  v1 = popInt(stack);
  v2 = popInt(stack);
  if(v1 >= v2){
	pushInt(stack, 1);}
  else{
	pushInt(stack, 0);}	
  return(0);
}

static int op_le(struct tokenStack *stack)
{
  int v1, v2;
  v1 = popInt(stack);
  v2 = popInt(stack);
  if(v1 >= v2){
	pushInt(stack, 0);}
  else{
	pushInt(stack, 1);}	
  return(0);
}



static int op_eq(struct tokenStack *stack)
{
  int v1, v2;
  v1 = popInt(stack);
  v2 = popInt(stack);
  if(v1 == v2){
	pushInt(stack, 1);}
  else{
	pushInt(stack, 0);}	
  return(0);
}

static int op_rem_quotient(struct tokenStack *stack)
{
  int v1, v2;
  v1 = popInt(stack);
  v2 = popInt(stack);
  pushInt(stack, v1%v2);
  return(0);
}

