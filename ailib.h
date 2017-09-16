#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define   PRIVATE   static

#define   NIL    	-1
#define   ATOMTYPE	10
#define	  TYNAME	1
#define   TYNUMBER	2

#define   MAXCELL	20000
#define   MAXSTRING	10000

#define   nl()      printf("\n")

// function prototypes

int head(int ls);
int tail(int ls);
int isatom(int a);
int islist(int a);
int name(char *str);
int number(int n);
int cons(int a, int ls);
int list(int a);
int clone_atom(int a);
int clone(int ls);
void print_list(int a);
void sethead(int ls, int v);
void settail(int ls, int v);
char *get_string(int a);
