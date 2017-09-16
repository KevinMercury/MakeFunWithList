// ai programming in c
//     tools:  list processing
//     Prabhas Chongstitvatana      27 Sept 2011
//     last update   12 Oct 2011

#include "ailib.h"

PRIVATE int cell[MAXCELL];
PRIVATE int freecell = ATOMTYPE;
PRIVATE char stringtable[MAXSTRING];
PRIVATE int freestring = 1;

/* available  functions
     head(a)
	 tail(a)
	 sethead(a,v)
	 settail(a,v)
	 isatom(a)		check a is atom
	 islist(a)		check a is list
	 name(str)		make name-atom
	 number(n)		make number-atom
	 cons(a,ls)		construct a list a:ls
	 list(a)		make list from atom
	 appenda(ls,a)	append list with atom
	 clone(ls)		clone list
	 print_list(ls)
*/

// a cell is a pair of integer
PRIVATE int newcell(int type, int value){
	int a;
	if(freecell > MAXCELL){
		fprintf(stderr,"out of cell memory");
		exit(1);
	}
	a = freecell;
	cell[a] = type;
	cell[a+1] = value;
	freecell += 2;
	return a;
}

// store string in the string buffer
// update freestring
PRIVATE int storestring(char *str){
	int idx;
	if(freestring > MAXSTRING){
		fprintf(stderr,"out of string memory");
		exit(1);
	}
	idx = freestring;
	strcpy(&stringtable[freestring],str);
	freestring += strlen(str) + 1;
	return idx;
}

char *get_string(int a){
	return &stringtable[tail(a)];
}

int head(int ls){
	return cell[ls];
}

int tail(int ls){
	return cell[ls+1];
}

void sethead(int ls, int v){
	cell[ls] = v;
}

void settail(int ls, int v){
	cell[ls+1] = v;
}

int isatom(int a){
	return head(a) < ATOMTYPE;
}

int islist(int a){
	return head(a) >= ATOMTYPE;
}

int name(char *str){
	return newcell(TYNAME, storestring(str));
}

int number(int n){
	return newcell(TYNUMBER, n);
}

// a is atom, ls is a list
int cons(int a, int ls){
	return newcell(a,ls);
}

int list(int a){
    return newcell(a, NIL);
}

int clone_atom(int a){
	return newcell(head(a),tail(a));
}

int clone(int ls){
	if( ls == NIL ) return NIL;
	if( isatom(ls)) return clone_atom(ls);
	else return cons(clone(head(ls)), clone(tail(ls)));
}

PRIVATE int gotoend(int ls){
	if( ls == NIL ) return NIL;
	if( tail(ls) == NIL ) return  ls;
	return gotoend(tail(ls));
}

// append atom a at the end of list
int appenda(int ls, int a){
	if( a == NIL ) return ls;
	settail(gotoend(ls), list(a));
	return ls;
}

PRIVATE void printstring(int a){
	printf("%c%s%c", 34,&stringtable[a],34);
}

PRIVATE void print_atom(int a){
	switch( head(a) ){
	case TYNAME: printstring(tail(a)); break;
	case TYNUMBER: printf("%d",tail(a)); break;
	}
}

void print_list(int a){
	if( a == NIL ) return;
	if( isatom(a) ){
		print_atom(a);
		printf(" ");
	}else{
		printf("(");
		while(a != NIL){
			print_list(head(a));
			a = tail(a);
		}
		printf(")");
	}
}
/*
void testlist(void){
	int a,b,c,d,e,f,g;
	a = number(1);
	print_list(a);
	nl();
	b = cons(a,NIL);
	print_list(b);
	nl();
	c = cons(number(1), cons(name("abc"), NIL));
	print_list(c);
	nl();
	d = appenda(c,number(4));
	print_list(d);
	nl();
	e = clone(d);
	print_list(e);
	nl();
	f = cons(d,e);
	g = clone(f);
	print_list(g);
	nl();
}


//int main(void){
//	testlist();
//}

*/
