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

struct wordcount
{
    char *word;
    int count;

    struct wordcount *higher;
    struct wordcount *lower;
};

void printlist(struct wordcount *head);
struct wordcount *search(struct wordcount *head, char *search_word);
struct wordcount *create_node(char *word);
void delete(struct wordcount *head);
void insert(struct wordcount **head, char *insert_word);

void test1()
{
    // Testing creating a head node
    struct wordcount head;
    char word[6] = "first";

    head.count = 1;
    head.word = &word[0];

    head.higher = NULL;
    head.lower = NULL;
    
    printf("Test 1\n");
    printf("head word = %s, count = %d\n", head.word, head.count);
    printf("Success\n");
    printf("\n");
}

void test2()
{
    // Testing adding to the count
    struct wordcount head;
    char word[6] = "first";

    head.count = 1;
    head.word = &word[0];

    head.higher = NULL;
    head.lower = NULL;
    
    head.count += 1;
    printf("Test 2\n");
    printf("head word = %s, count = %d\n", head.word, head.count);
    printf("Success\n");
    printf("\n");
}

void test3()
{
    // Testing adding more wordcounts to head
    struct wordcount a;
    struct wordcount c;
    struct wordcount b;

    char a_word[6] = "first";
    char c_word[10] = "higher";
    char b_word[10] = "lower";

    a.count = 1;
    c.count = 1;
    b.count = 1;

    a.word = &a_word[0];
    c.word = &c_word[0];
    b.word = &b_word[0];

    a.higher = &c;
    a.lower = &b;
    c.higher = NULL;
    c.lower = NULL;
    b.higher = NULL;
    b.lower = NULL;
    
    
    a.count += 1;
    printf("Test 3\n");
    printf("head_word = %s, count = %d\n", a.word, a.count);
    printf("higher_word = %s, count = %d\n", a.higher->word, a.higher->count);
    printf("lower word = %s, count = %d\n", a.lower->word, a.lower->count);
    printf("Success\n");
    printf("\n");
}

void test4()
{
    // Testing searching for word: find match
    struct wordcount a;
    struct wordcount c;
    struct wordcount b;
    struct wordcount d;

    char a_word[6] = "centre";
    char c_word[10] = "deal";
    char b_word[10] = "calibrate";
    char d_word[10] = "accept";
    char search_word[10] = "accept";

    a.count = 1;
    c.count = 1;
    b.count = 1;
    d.count = 1;

    a.word = &a_word[0];
    c.word = &c_word[0];
    b.word = &b_word[0];
    d.word = &d_word[0];

    a.higher = &c;
    a.lower = &b;
    c.higher = NULL;
    c.lower = NULL;
    b.higher = NULL;
    b.lower = &d;
    d.lower = NULL;
    d.higher = NULL;
    
    
    a.count += 1;
    printf("Test 4\n");

    struct wordcount *match = search(&a, &search_word[0]);

    if(match == NULL)
        printf("NULL\n");
    else
        printf("match word: %s, match count: %d\n", match->word, match->count);
    
    printf("Success\n");
    printf("\n");
}

void test5()
{
    // Testing searching for word: find non-match
    struct wordcount a;
    struct wordcount c;
    struct wordcount b;
    struct wordcount d;

    char a_word[6] = "centre";
    char c_word[10] = "deal";
    char b_word[10] = "calibrate";
    char d_word[10] = "accept";
    char search_word[10] = "altogether";

    a.count = 1;
    c.count = 1;
    b.count = 1;
    d.count = 1;

    a.word = &a_word[0];
    c.word = &c_word[0];
    b.word = &b_word[0];
    d.word = &d_word[0];
    
    a.higher = &c;
    a.lower = &b;
    c.higher = NULL;
    c.lower = NULL;
    b.higher = NULL;
    b.lower = &d;
    d.lower = NULL;
    d.higher = NULL;
    
    
    a.count += 1;
    printf("Test 5\n");

    struct wordcount *match = search(&a, &search_word[0]);

    if(match == NULL)
        printf("NULL\n");
    else
        printf("match word: %s, match count: %d\n", match->word, match->count);
    
    printf("Success\n");
    printf("\n");
}

void test6()
{   
    // testing creating create_node
    printf("Test 6\n");

    char insert[10] = "testing";
    struct wordcount *head = create_node(&insert[0]);

    printf("head word: %s, head count: %d\n", head->word, head->count);
    printf("Success\n");
    printf("\n");
}   

void test7()
{   
    // testing create_node with NULL char pointer
    printf("Test 7\n");

    char *insert = NULL;
    struct wordcount *head = create_node(insert);

    if(head == NULL)
        printf("New wordcount node is NULL\n");
    
    printf("Success\n");
    printf("\n");
} 

void test8()
{
    // testing insert with NULL string
    printf("Test 8\n");

    char *word = NULL;
    struct wordcount *head = NULL;

    insert(&head, word);
    if(head == NULL)
        printf("New wordcount node is NULL\n");
    
    printf("Success\n");
    printf("\n");
}

void test9()
{
    // testing insert with string
    printf("Test 9\n");

    char word[10] = "testing";
    struct wordcount *head = NULL;

    insert(&head, word);
    if(head == NULL)
        printf("New wordcount node is NULL\n");
    else
    {
        printf("wordcount node word: %s\n", head->word);
    }

    printf("Success\n");
    printf("\n");
}

void test10()
{
    // testing insert with two strings string
    printf("Test 10\n");

    char word_1[10] = "cabriolet";
    char word_2[15] = "applesauce";
    struct wordcount *head = NULL;

    insert(&head, word_1);
    insert(&head, word_2);

    if(head == NULL)
    {
        printf("New wordcount node is NULL\n");
        printf("Fail\n");
    }
    else
    {
        printf("wordcount node word: %s\n", head->word);
        printf("wordcount node word: %s\n", head->lower->word);
        printf("Success\n");
    }

    printf("\n");
}

void test11()
{
    // testing insert with two strings string
    printf("Test 11\n");

    char word_1[10] = "cabriolet";
    char word_2[15] = "applesauce";
    char word_3[15] = "butterscotch";
    char word_4[15] = "captain";
    char word_5[15] = "picard";

    struct wordcount *head = NULL;

    insert(&head, word_1);
    insert(&head, word_2);
    insert(&head, word_3);
    insert(&head, word_4);
    insert(&head, word_5);

    if(head == NULL)
    {
        printf("New wordcount node is NULL\n");
        printf("Fail\n");
    }
    else
    {
        printf("wordcount node word: %s\n", head->lower->word);
        printf("wordcount node word: %s\n", head->lower->higher->word);
        printf("wordcount node word: %s\n", head->word);
        printf("wordcount node word: %s\n", head->higher->word);
        printf("wordcount node word: %s\n", head->higher->higher->word);
        printf("Success\n");
    }

    printf("\n");
}

void test12()
{
    // testing printlist with two strings
    printf("Test 12\n");

    char word_1[10] = "cabriolet";
    char word_2[15] = "applesauce";
    struct wordcount *head = NULL;

    insert(&head, word_1);
    insert(&head, word_2);

    if(head == NULL)
    {
        printf("New wordcount node is NULL\n");
        printf("Fail\n");
    }
    else
    {
        printlist(head);
        printf("Success\n");
    }

    printf("\n");
}

void test13()
{
    // testing printlist with five strings
    printf("Test 13\n");

    char word_1[10] = "cabriolet";
    char word_2[15] = "applesauce";
    char word_3[15] = "butterscotch";
    char word_4[15] = "captain";
    char word_5[15] = "picard";

    struct wordcount *head = NULL;

    insert(&head, word_1);
    insert(&head, word_2);
    insert(&head, word_3);
    insert(&head, word_4);
    insert(&head, word_5);

    if(head == NULL)
    {
        printf("New wordcount node is NULL\n");
        printf("Fail\n");
    }
    else
    {
        printlist(head);
        printf("Success\n");
    }

    printf("\n");
}

void testing_suite()
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
}

/* Write a cross-referemcer that prints a list of all words in a document, and, for
each word, a list of the line numbers on which it occurs. Remove noise words like
"the", "and", and so on. */
int main(int argc, char *argv[])
{   
    // Make sure all tests are successful
    testing_suite();


    // Number of identical beginning characters to consider
    int min_identical = 3;
    if (argc > 1)
        min_identical = atoi(argv[1]);

    
    int lim = 1000;
    char current_word[lim];

    // Have to make sure that the pointer for the word has pre-allocated 
    // space to store the words, in this case, with size lim.
    char first_letter = getword(&current_word[0], lim);
    
    // create a Node * structure and tie it to head_ref
    struct wordcount *head_ref = (struct wordcount *)malloc(sizeof(struct wordcount));
    struct wordcount **current = (struct wordcount **)malloc(sizeof(struct wordcount *));
    head_ref = NULL;
    *current = head_ref;

    while(first_letter != EOF)
    {   
        if(strlen(&current_word[0]) >= min_identical)
        {
            *current = search(head_ref, current_word);

            if(*current == NULL)
                insert(&head_ref, &current_word[0]);
            else
                (*current)->count++;
        }

        // get new word
        first_letter = getword(&current_word[0], lim);
    }

    printlist(head_ref);
    return 0;
}

void printlist(struct wordcount *head)
{
    if(head == NULL)
        return;

    // print the lower alphabetical value words
    printlist(head->lower);

    // print the head word
    printf("%s %d\n", head->word, head->count);

    // print the higher alphabetical value words
    printlist(head->higher);
}

struct wordcount *create_node(char *word)
{   
    if(word == NULL)
        return NULL;

    int word_len = strlen(word);
    struct wordcount *temp = (struct wordcount*) malloc(sizeof(struct wordcount));
    struct wordcount *current;
    struct wordcount *parent;


    temp->word = (char*) malloc(word_len * sizeof(char)) ;
    strcpy(temp->word, word);

    temp->count = 1;
    temp->higher = NULL;
    temp->lower = NULL;

    return temp;
}

void delete(struct wordcount *head)
{
    free(head->word);
    free(&(head->count));
    free(head->higher);
    free(head->lower);
    printf("Deleted node contents\n");

    free(head);
    printf("Deleted node pointer\n");
}

struct wordcount *search(struct wordcount *head, char *search_word)
{   
    if(head == NULL)
        return NULL;

    struct wordcount *head_ptr;

    head_ptr = head;

    while(strcmp(head_ptr->word, search_word) != 0)
    {
        if(head_ptr->word != NULL)
        {
            //go to right tree
            if(strcmp(head_ptr->word, search_word) < 0)
                head_ptr = head_ptr->higher;
            //go to left tree
            else if(strcmp(head_ptr->word, search_word) > 0)
                head_ptr = head_ptr->lower;

            if(head_ptr == NULL)
                return NULL;
        }


    }
    return head_ptr;
}

void insert(struct wordcount **head, char *insert_word)
{
    if(insert_word == NULL)
        return;

    struct wordcount *temp = create_node(insert_word);
    struct wordcount *current;
    struct wordcount *parent;

    //if tree is empty
    if(*head == NULL)
    {
        *head = temp;
    }
    else
    {
        current = *head;
        parent = NULL;

        while(1)
        {
            parent = current;

            //go to left of the tree
            if(strcmp(parent->word, insert_word) > 0)
            {
                current = current->lower;
                //insert to the left

                if(current == NULL)
                {
                    parent->lower = temp;
                    return;
                }
            }
            //go to right of the tree
            else if(strcmp(parent->word, insert_word) < 0)
            {
                current = current->higher;

                //insert to the right
                if(current == NULL)
                {
                    parent->higher = temp;
                    return;
                }
            }
            else
            {
                parent->count+=1;
                return;
            }
        }
    }
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