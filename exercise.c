

// recursive example
#include <stdlib.h>
#include "ailib.h"

int count1(int ls){
	int s = 0;
	while( ls != NIL ){
		s++;
		ls = tail(ls);
	}
	return s;
}

int count2(int ls){
	if( ls == NIL ) return 0;
	return 1 + count2(tail(ls));
}

int count3(int ls){
	if( ls == NIL ) return 0;
	if( isatom(head(ls)) ) return 1 + count3(tail(ls));
	return count3(head(ls)) + count3(tail(ls));
}

int count4(int ls){
	if( ls == NIL ) return 0;
	if( isatom(ls) ) return 1;
	return count4(head(ls)) + count4(tail(ls));
}

int unum1(int n){
	int ls;
	ls = NIL;
	while(n > 0){
		ls = cons(number(1),ls);
		n--;
	}
	return ls;
}

int unum2(int n){
	if( n == 0 ) return NIL;
	return cons(number(1), unum2(n-1));
}

int cat2(int a, int b){
	if( a == NIL ) return b;
	return cat2( tail(a), cons(head(a),b) );
}

int uadd(int n, int m){
	if( m == NIL ) return n;
	if( n == NIL ) return m;
	return uadd( tail(n), cons(head(n),m) );
}

int usub(int n, int m){            // assume n >= m
	if( m == NIL ) return n;
	return usub( tail(n), tail(m) );
}

int reverse2(int ls, int ls1){
	if( ls == NIL ) return ls1;
	return reverse2(tail(ls), cons(head(ls),ls1));
}

int reverse(int ls){
	return reverse2(ls, NIL);
}

/* Answer for Dr.Prabhas C.'s Exercises. '*/

int umul(int n, int m){
	if( n == NIL ) return NIL;
	if( m == NIL ) return NIL;
	int count = count4(m) - 1;
	while(count > 0){
		n = cat2(n,n);
		count = count - 1;
	}

	return n;
}

int append(int list, int element){
	if(element == NIL) return list;
	return cat2(list,cons(element,NIL));
}

int cloneComplex(int list){
	if(list == NIL) return list;
	int newlist = NIL;
	while(list != NIL){
		newlist = cons(head(list),newlist);
		list = tail(list);
	}

	return reverse(newlist);
}

int compareList(int list1,int list2){
	if(list1 == NIL && list2 == NIL) return 1;
	if(list1 == NIL && list2 != NIL) return 0;
	if(list1 != NIL && list2 == NIL) return 0;
	while(list1 != NIL){
			if(isatom(head(list1))){
				if(!isatom(head(list2))) return 0;
				list1 = tail(list1);
				list2 = tail(list2);
			} else {
				if(!islist(head(list2))) return 0;
				return compareList(head(list1),head(list2));
			}
	}

	if(list2 == NIL) return 1;
	return 0;
}

int flattenList(int list){
	if(list == NIL) return list;
	int newlist = NIL;
	while(list != NIL){
		if(isatom(head(list))){
			newlist = append(newlist,head(list));
		} else {
			int t = flattenList(head(list));
			print_list(t);
			printf(" | ");
			newlist = cat2(t,newlist);
			print_list(newlist);
			printf("\n");
		}
		list = tail(list);
	}

	return newlist;
}

/*
int main(void){
	int a, b, c;
	a = cons(number(2),cons(number(3),NIL));
	b = cons(number(1),list(a));
//	print_list(b);
//	printf("%d\n", cnt4(b));
	a = unum1(4);
//	b = unum2(3);
	c = cat2(a,b);
	c = uadd(a,b);
	c = usub(a,b);
	c = reverse(b);
	print_list(c);
}
*/

int main(void){
	int a,b,c;

	printf("1.Multiply List of a and b.\n");
	a = unum1(4);
	b = unum1(2);
	c = umul(a,b);
	print_list(c);
	printf("\n");

	printf("2.Append List with an element 5.\n");
	c = append(a,number(5));
	print_list(c);
	printf("\n");

	printf("3.Clone List of ");
	int original = cat2(unum1(2),unum1(3));
	original = cons(original,cons(unum1(4),NIL));
	print_list(original);
	printf("\n");
	c = cloneComplex(original);
	print_list(c);
	printf("\n");

	printf("4.Compare Equality from 3.\n");
	printf("%d",compareList(original,c));
	printf("\nIf we try to change something in c as");
	//c = cons(number(4),c);
	c = append(c,number(4));
	print_list(c);
	printf("\n%d",compareList(original,c));
	printf("\nIf we try to change something in original as");
	//original = cons(number(4),original);
	original = append(original,number(4));
	print_list(original);
	printf("\n%d",compareList(original,c));
	printf("\n");

	printf("5.Flatten a Complex List of ");
	int k = NIL;
	for(int i = 0; i < 3; i++){
		k = cons(number(5),k);
	}
	c = cons(k,c);
	print_list(c);
	c = cons(number(3),c);
	print_list(c);
	c = cons(number(100),c);
	print_list(c);
	printf("\n");
	print_list(flattenList(c));
	printf("\n");
}
