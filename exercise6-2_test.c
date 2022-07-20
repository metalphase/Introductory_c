#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h> /* for atof() */

#define MAXVAL 100 /* maximum depth of val stack */
#define BUFSIZE 100
#define MAXWORD 100

char buf[BUFSIZE]; /* buffer for ungetch */
int bufp = 0;      /* next free position in buf */

int getch(void);
void ungetch(int);

int getword(char *word, int lim);

struct Node
{
    char *word;
    struct Node *next;
};

// Declaring Node functions
void printList(struct Node *n);
void freeList(struct Node *n);
void push(struct Node **head_ref, char *new_word);
void insertAfter(struct Node *prev_node, char *new_word);
void deleteNode(struct Node **head_ref, char *keyword);
void append(struct Node **head_ref, char *new_word);

void test1()
{

    // Testing printList on NULL node
    struct Node *list = NULL;
    printf("Test 1\n");
    printList(list);
    printf("\n");
}

void test2()
{
    struct Node node1;

    node1.next = NULL;
    node1.word = "aaa";

    printf("Test 2\n");
    printList(&node1);
    printf("\n");
}

void test3()
{
    struct Node node1;
    struct Node node2;

    node1.next = &node2;
    node1.word = "aaa";

    node2.next = NULL;
    node2.word = "bbb";

    printf("Test 3\n");
    printList(&node1);
    printf("\n");
}

void test4()
{
    struct Node node1;
    struct Node node2;
    struct Node node3;

    node1.next = &node2;
    node1.word = "aaa";

    node2.next = &node3;
    node2.word = "bbb";

    node3.next = NULL;
    node3.word = "ccc";

    printf("Test 4\n");
    printList(&node1);
    printf("\n");
}

void test5()
{
    struct Node *head_ref = NULL;

    printf("Test 5\n");
    printList(head_ref);
    printf("\n");

    free(head_ref);
}

void test6()
{
    struct Node *head_ref = (struct Node *)malloc(sizeof(struct Node));
    head_ref->next = NULL;
    head_ref->word = NULL;

    printf("Test 6\n");
    printList(head_ref);
    printf("\n");

    free(head_ref);
}

void test7()
{
    struct Node *head_ref = (struct Node *)malloc(sizeof(struct Node));
    head_ref->next = NULL;
    head_ref->word = "aaa";

    printf("Test 7\n");
    printList(head_ref);
    printf("\n");

    free(head_ref);
}

void test8()
{
    struct Node *head_ref = (struct Node *)malloc(sizeof(struct Node));
    head_ref->next = NULL;
    head_ref->word = "aaa";

    printf("Test 8\n");
    printList(head_ref);
    push(&head_ref, "bbb");

    printList(head_ref);
    printf("\n");

    free(head_ref);
}

void test9()
{
    struct Node *head_ref = (struct Node *)malloc(sizeof(struct Node));
    head_ref->next = NULL;
    head_ref->word = "aaa";

    printf("Test 9\n");
    printList(head_ref);
    printf("\n");
    push(&head_ref, "bbb");

    printList(head_ref);
    printf("\n");
    push(&head_ref, "ccc");

    
    printList(head_ref);
    printf("\n");
    push(&head_ref, "ddd");

    printList(head_ref);
    printf("\n");
    push(&head_ref, "eee");

    printList(head_ref);
    printf("\n");
    
    free(head_ref);
}

void test10()
{
    struct Node *head_ref = (struct Node *)malloc(sizeof(struct Node));
    head_ref->next = NULL;
    head_ref->word = "aaa";

    printf("Test 10\n");
    push(&head_ref, "bbb");
    push(&head_ref, "ccc");
    push(&head_ref, "ddd");
    push(&head_ref, "eee");

    printList(head_ref);
    printf("\n");

    freeList(head_ref);
    printf("head_ref address: %p\n", head_ref);
}

void test11()
{
    struct Node *head_ref = (struct Node *)malloc(sizeof(struct Node));
    head_ref->next = NULL;
    head_ref->word = "aaa";

    printf("Test 11\n");
    insertAfter(head_ref, "bbb");

    printList(head_ref);
    printf("\n");
}

void test12()
{
    struct Node *head_ref = (struct Node *)malloc(sizeof(struct Node));
    head_ref->next = NULL;
    head_ref->word = "aaa";

    printf("Test 12\n");
    insertAfter(head_ref, "bbb");
    insertAfter(head_ref, "ccc");
    insertAfter(head_ref, "ddd");
    insertAfter(head_ref, "eee");

    printList(head_ref);
    printf("\n");
}

void test13()
{
    struct Node *head_ref = (struct Node *)malloc(sizeof(struct Node));
    head_ref->next = NULL;
    
    printf("Test 13\n");
    append(&head_ref, "aaa");
    printList(head_ref);    
    printf("\n");
}

void test14()
{
    struct Node *head_ref = (struct Node *)malloc(sizeof(struct Node));
    head_ref->next = NULL;
    
    printf("Test 14\n");
    append(&head_ref, "aaa");
    append(&head_ref, "bbb");
    append(&head_ref, "ccc");
    printList(head_ref);    
    printf("\n");
}
/* Write a program that reads a C program and prints in alphabetical order
each group of variable names that are identical in the first 6 characters,
but different somewhere thereafter. Don't count words within strings and
comments. Make 6 a parameter that can be set from the command line. */
int main(int argc, char *argv[])
{
    test1();
    test2();
    test3();
    test4();
    test5();
    test6();
    test7();
    test8();
    test9();
    test10();
    test11();
    test12();
    test13();
    test14();

    return 0;
}

void printList(struct Node *n)
{

    if (n == NULL)
        printf("Node is NULL\n");
    else
    {
        struct Node *tmp = n;

        while (tmp != NULL)
        {
            printf("address: %p ", tmp);
            if ((tmp->word) != NULL)
            {
                printf("word: %s", tmp->word);
            }
            printf("\n");
            tmp = tmp->next;
        }
    }
}

void freeList(struct Node *n)
{

    if (n == NULL)
        printf("Node is NULL\n");
    else
    {
        struct Node *current_node = n;
        struct Node *next_node = NULL;

        while (current_node != NULL)
        {   
            // Assign address of the next node of current_node to next node
            next_node = current_node->next;

            printf("current_node address: %p ", current_node);
            printf("current_node word: %s ", current_node->word);
            printf("Freeing current_node memory");
            free(current_node);
            current_node = next_node;

            printf("\n");
        }
    }
}
void push(struct Node **head_ref, char *new_word)
{
    /* Create a new node with word, new_word and
    insert it before the head_ref node. */

    /* 1. allocate node */
    struct Node *new_node = (struct Node *)malloc(sizeof(struct Node));

    /* 2. put in the data */
    new_node->word = new_word;

    /* 3. Make next of new node as head */
    new_node->next = *head_ref;

    /* 4. move the head to point to the new node */
    *head_ref = new_node;
}

void append(struct Node **head_ref, char *new_word)
{
    /* Create a new node with new_word. If the head_ref is NULL, we let it to be
    our new node. Otherwise, we traverse the node tree until we find the last node
    and insert our new node after the last node.*/

    /* 1. allocate node */
    struct Node *new_node = (struct Node *)malloc(sizeof(struct Node));

    /* 2. put in the data  */
    new_node->word = new_word;

    /* 3. This new node is going to be the last node, so make next
          of it as NULL*/
    new_node->next = NULL;

    /* 4. If the Linked List is empty, then make the new node as head */
    if (*head_ref == NULL)
    {
        *head_ref = new_node;
        return;
    }

    /* 5. Iterate to last node */
    struct Node *last = *head_ref;

    while (last->next != NULL)
        last = last->next;

    /* 6. Change the next of last node */
    last->next = new_node;
    return;
}

void insertAfter(struct Node *prev_node, char *new_word)
{
    /* If the previous node is null, we return an error. Otherwise
    we create a new node and insert it after prev_node and attach the
    previous next node from prev_node and attach it to the next of the new
    node */

    /*1. check if the given prev_node is NULL */
    if (prev_node == NULL)
    {
        printf("the given previous node cannot be NULL");
        return;
    }

    /* 2. allocate new node */
    struct Node *new_node = (struct Node *)malloc(sizeof(struct Node));

    /* 3. put in the data */
    new_node->word = new_word;

    /* 4. Make next of new node as next of prev_node */
    new_node->next = prev_node->next;

    /* 5. move the next of prev_node as new_node */
    prev_node->next = new_node;
}

void deleteNode(struct Node **head_ref, char *keyword)
{
    /* Delete the node with the key, key. Restructures the tree around
    the deleted node. */

    if (*head_ref == NULL)
        return;

    // Store head node
    struct Node *prev = head_ref[0];
    struct Node *current = *head_ref;

    while (current != NULL)
    {
        if (strcmp(current->word, keyword) == 0)
        {
            if (current->word != NULL)
                free(current->word);

            prev->next = current->next;

            struct Node *tmp = current;
            current = current->next;

            free(tmp);
        }
    }
}

int getword(char *word, int lim)
{
    /*
        Returns a char pointer to the next word with max length, lim.
    */
    int c, getch(void);
    void ungetch(int);
    char *w = word;

    while (isspace(c = getch()))
        ;
    // Skip comments of the type '//' and '/* */'
    if (c == '/')
    {
        c = getch();
        if (c == '/')
            while ((c = getch()) != '\n')
                ;
        else if (c == '*')
            while ((c = getch()) != '/')
                ;
    }
    // Check for preprocessor control lines, for which we skip entire to the
    // next line
    if (c == '#')
        while ((c = getch()) != '\n')
            ;
    // We include underscores in our string when encountered
    if (c != EOF && (isalpha(c) || c == '_'))
        *w++ = c;
    if (c != '_' && !isalpha(c))
    {
        *w = '\0';
        return c;
    }
    for (; --lim > 0; w++)
        if (!isalnum(*w = getch()) && (*w != '_'))
        {
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