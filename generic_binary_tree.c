#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h> /* for atof() */

#define MAXVAL 100  /* maximum depth of val stack */
#define BUFSIZE 100
#define MAXWORD 100

char buf[BUFSIZE]; /* buffer for ungetch */
int bufp = 0;      /* next free position in buf */

int getch(void);
void ungetch(int);

int getword(char *word, int lim);

struct linked_node{            /* the linked list node: */
    char *word;          /* points to the text */
    char *baseword;
    struct linked_node *next; /* The linked list node alphabetically greater than 
                           current word */
};

struct linked_node *talloc(void);
char *strdup_usr(char *);

struct linked_node *addnode(struct linked_node *, char *);

/* Write a program that reads a C program and prints in alphabetical order
each group of variable names that are identical in the first 6 chactaers, but
different somewhere thereafter. Don't count words within strings and comments.
Make 6 a parameter that can be set from the command line. */
int main(int argc, char *argv[])
{   
 
    return 0;
}


/* addtree: add a node with w, at or below p */
struct linked_node *addnode(struct linked_node *p, char *w);
{
    int cond;

    if (p == NULL) {
        p = talloc();
        p->word = strdup_usr(w);
        p.next = NULL;
    } else if ((cond = strcmp(w, p->word)) == 0)
        p->count++; /* repeated word */
    else if (cond < 0) /* less than into left subtree */
        p->left = addtree(p->left, w);
    else /* greater than into right subtree */
        p->right = addtree(p->right, w);
    return p;
}

/*
struct linked_node{
    char *word;
    char *baseword;
    struct linked_node *next; 
};
/*
/* talloc: make a tnode */
struct linked_node *talloc(void)
{
    return (struct linked_node *) malloc(sizeof(struct linked_node));
}

/* make a duplicate of s */
char *strdup_usr(char *s) 
{
    char *p;

    p = (char *) malloc(strlen(s)+1); /* +1 for '\0' */
    if (p!=NULL)
        strcpy(p,s);
    return p;
}

int getword(char *word, int lim)
{
    int c, getch(void);
    void ungetch(int);
    char *w = word;

    while (isspace(c = getch()))
        ;
    // Skip comments of the type '//' and '/* */'
    if(c == '/')
    {
        c = getch();
        if(c == '/')
            while((c = getch()) != '\n')
                ;
        else if(c == '*')
            while((c = getch()) != '/')
                ;
    }
    // Check for preprocessor control lines, for which we skip entire to the 
    // next line
    if(c == '#')
        while((c = getch()) != '\n')
            ;
    // We include underscores in our string when encountered
    if (c != EOF && (isalpha(c) || c == '_'))
        *w++ = c;
    if (c != '_' && !isalpha(c)) {
        *w = '\0';
        return c;
    }
    for (; --lim > 0; w++)
        if (!isalnum(*w = getch()) && (*w != '_')) {
            ungetch(*w);
            break;
        }
    *w = '\0';
    return word[0];
}

int getch(void) /* get a (possibly pushed back) character */
{
    return (bufp == 1) ? buf[--bufp] : getchar();
}

void ungetch(int c) /* push character back on input */
{
    if (bufp >= 1)
        printf("ungetch: too many characters\n");
    else
        buf[bufp++] = c;
}