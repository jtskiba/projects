/*
K&R Ch4,p.64

Given the basic framework, it's straightforward to extend the calculator. 
Add the modulus (%) operator and provisions for negative numbers.
*/

#include <stdio.h>
#include <stdlib.h> /* for atof() */
#include <ctype.h> /* for isdigit()? */


#define MAXOP 100 /* max size of operand or operator */
#define NUMBER '0' /* signal that a number was found */
#define MAXVAL 100 /* maximum depth of val stack */
#define BUFSIZE 100


int getop(char []);
void push(double);
double pop(void);
int getch(void);
void ungetch(int);

int sp = 0; /* next free stack position */
double val[MAXVAL]; /* value stack */
char buf[BUFSIZE]; /* buffer for ungetch */
int bufp = 0; /* next free position in buf */

/* reverse Polish calculator */
int main(void)
{
	int type;
	double op2, op1;
	char s[MAXOP];
	//char temp[] = "-2.3";
	
	//printf("%f\n",atof(temp));

	while ((type = getop(s)) != EOF) {
		switch (type) {
			case NUMBER:
				push(atof(s));
				break;
			case '+':
				push(pop() + pop());
				break;
			case '*':
				push(pop() * pop());
				break;
			case '-': /* cheating - this is new minus */
				op2 = pop();
				push(pop() - op2);
				break;
			case '%':
				op2 = pop();
				op1 = pop();
				push((double)((int)op1 % (int)op2));
				break;	
			case '/':
				op2 = pop();
				if (op2 != 0.0)
					push(pop() / op2);
				else
					printf("error: zero divisor\n");
				break;
			case '\n':
				printf("\t%.8g\n", pop());
				break;
			default:
				printf("error: unknown command %s\n", s);
			break;
		}
	}
	return 0;
}


/* push: push f onto value stack */
void push(double f)
{
	if (sp < MAXVAL)
		val[sp++] = f;
	else
		printf("error: stack full, can't push %g\n", f);
}

/* pop: pop and return top value from stack */
double pop(void)
{
	if (sp > 0)
		return val[--sp];
	else {
		printf("error: stack empty\n");
		return 0.0;
	}
}

/* getop: get next character or numeric operand */
int getop(char s[])
{
	int i, c;

	while ((s[0] = c = getch()) == ' ' || c == '\t')
		;
	s[1] = '\0';
	
	i = 0;
	
	if (!isdigit(c) && c != '.' && c != '-')
		return c; /* not a number */
	

	// this piece i stole from web
	if(c=='-')
        if(isdigit(c = getch()) || c == '.')
            s[++i] = c;
        else
        {
            if(c!=EOF)
                ungetch(c);
            return '-';
        }
	// end of thing stolen
	

	if (isdigit(c)) /* collect integer part */ 
	    while (isdigit(s[++i] = c = getch()))
		    ;
	
			
	if (c == '.') /* collect fraction part */
		while (isdigit(s[++i] = c = getch()))
			;
	s[i] = '\0';
	
		
	if (c != EOF)
		ungetch(c);
	return NUMBER;
}

int getch(void) /* get a (possibly pushed-back) character */
{
	return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c) /* push character back on input */
{
	if (bufp >= BUFSIZE)
		printf("ungetch: too many characters\n");
	else
		buf[bufp++] = c;
}
