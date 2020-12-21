/*
K&R Ch6, p.110
The keyword counting program begins with the definition of keytab. The main routine reads
the input by repeatedly calling a function getword that fetches one word at a time. Each word
is looked up in keytab with a version of the binary search function that we wrote in Chapter 3.
The list of keywords must be sorted in increasing order in the table.
*/

#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAXWORD 100
#define BUFSIZE 100
#define NKEYS 11 //need to update manually as you change the number of items in keytab

struct key {
	char *word;
	int count;
	} keytab[] = { //words need to be sorted in order for binsearch to work
		"auto", 0,
		"break", 0,
		"case", 0,
		"char", 0,
		"const", 0,
		"continue", 0,
		"default", 0,
		/* ... */
		"unsigned", 0,
		"void", 0,
		"volatile", 0,
		"while", 0
		};

int getword(char *word, int lim);
int binsearch(char *word, struct key tab[], int n);
int getword(char *word, int lim);
int getch(void);
void ungetch(int c);

char buf[BUFSIZE]; /* buffer for ungetch */
int bufp = 0; /* next free position in buf */


/* count C keywords */
int main(void)
{
	int n;
	char word[MAXWORD];
	
	while (getword(word, MAXWORD) != EOF)
		if (isalpha(word[0]))
			if ((n = binsearch(word, keytab, NKEYS)) >= 0)
				keytab[n].count++;
	for (n = 0; n < NKEYS; n++)
		if (keytab[n].count > 0)
			printf("%4d %s\n", keytab[n].count, keytab[n].word);
	return 0;
}

/* binsearch: find word in tab[0]...tab[n-1] */
int binsearch(char *word, struct key tab[], int n)
{
	int cond;
	int low, high, mid;
	
	low = 0;
	high = n - 1;
	
	while (low <= high) {
		mid = (low+high) / 2;
		if ((cond = strcmp(word, tab[mid].word)) < 0)
			high = mid - 1;
		else if (cond > 0)
			low = mid + 1;
		else
			return mid;
	}
	return -1;
}


/* getword: get next word or character from input */
int getword(char *word, int lim)
{
	int c, getch(void);
	void ungetch(int);
	char *w = word;
	
	while (isspace(c = getch()))
		;	
	if (c != EOF)
		*w++ = c;
	if (!isalpha(c)) {
		*w = '\0';
		return c;
	}
	
	for ( ; --lim > 0; w++)
		if (!isalnum(*w = getch())) {
			ungetch(*w);
			break;
		}
	*w = '\0';
	return word[0];
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

