/* Takes input lines and removes blanks and tabs from each line , and delete
    entirely blank lines. This is ex1-18 on p.31 K&R*/

#include <stdio.h>

#define MAXLINE 1000 /* max input line size*/
#define TARGET 1 /* lines above this target will be remembered and printed */

int getline(char s[], int maxline); /* note, need to have char's here, not int's */
int copy(char from[], char to[]);

int main()
{
    int i, len, max, iter;
    char line[MAXLINE];
    char above_target[MAXLINE][MAXLINE];

    max = iter = 0;
    while ((len = getline(line, MAXLINE)) > 0) /* note > 0 until there is new line, also no [] after line */
        if (len > TARGET)
        {
            copy(line, above_target[iter]);
            ++iter;
        }
    if ((iter > 0) || (len > 0)){ /* to make sure some input was made initially */
        for (i = 0; i < iter; ++i)
            printf("%s\n", above_target[i]); /* note no [] after longest */
    }
    return 0;
}

/* getline: get input into s up to limit, return length */
int getline(char s[], int limit)
{
    int i, blank, c;

    blank = 0;
    for(i = 0; i < limit - 1 && ((c = getchar()) != EOF) && c != '\n'; ++i)
    {
        if ((c == ' ') || (c == '\t'))
            ++blank;
        else
            s[i-blank] = c;
    }
    s[i] = '\0';
    return i;
}

/* copy: copy string from from[] to to[], assume to[] is big enough */
int copy(char from[], char to[])
{
    int i = 0;
    while ((to[i] = from[i]) != '\0')
        ++i;
    return 0; /*dummy return */
}
