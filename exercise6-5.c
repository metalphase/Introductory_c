#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define HASHSIZE 101
#define MAXVAL 100  /* maximum depth of val stack */
#define BUFSIZE 100
#define MAXWORD 100

/* 
    Basic I/O Functions
*/

char buf[BUFSIZE]; /* buffer for ungetch */
int bufp = 0;      /* next free position in buf */

int getch(void);
void ungetch1(int);
int getword(char *word, int lim);

/*
    Hashtable implementation
*/

/* Definition of a node entry into the has table */
struct nlist 
{
    struct nlist *next; /* next entry in chain*/
    char *name;         /* defined name */
    char *defn;         /* replacement text */
};

/* Static hashtable for the program */
static struct nlist *hashtab[HASHSIZE];

/* Basic hashtable methods */
void print_table(void);
unsigned hash(char *s);
struct nlist *lookup(char *s);
struct nlist *install(char *name, char *defn);
void undef(char *remove_s);
void list_definitions(void);
void test1(void);
void test2(void);
void test3(void);
void test4(void);
void test5(void);
void test6(void);

/*
    Unit tests
*/
void test1(void)
{
    printf("Test 1\n");

    unsigned hash_val = hash("Little");
    
    hashtab[hash_val] = (struct nlist *) malloc(sizeof(struct nlist));
    hashtab[hash_val]->name = (char *) malloc(sizeof(char) * strlen("Little"));
    hashtab[hash_val]->defn = (char *) malloc(sizeof(char) * strlen("Dark"));

    strcpy(hashtab[hash_val]->name , "Little");
    strcpy(hashtab[hash_val]->defn , "Dark");

    print_table();
    printf("\n");
    
    free(hashtab[hash_val]->name);
    free(hashtab[hash_val]->defn);
    free(hashtab[hash_val]);
    
    hashtab[hash_val] = NULL;
}

void test2(void)
{
    unsigned hash_val1 = hash("Little");
    unsigned hash_val2 = hash("Dark");
    
    hashtab[hash_val1] = (struct nlist *) malloc(sizeof(struct nlist));
    hashtab[hash_val1]->name = (char *) malloc(sizeof(char) * strlen("Little"));
    hashtab[hash_val1]->defn = (char *) malloc(sizeof(char) * strlen("Dark"));
    
    hashtab[hash_val2] = (struct nlist *) malloc(sizeof(struct nlist));
    hashtab[hash_val2]->name = (char *) malloc(sizeof(char) * strlen("Dark"));
    hashtab[hash_val2]->defn = (char *) malloc(sizeof(char) * strlen("Age"));
    
    strcpy(hashtab[hash_val1]->name , "Little");
    strcpy(hashtab[hash_val1]->defn , "Dark");
    strcpy(hashtab[hash_val2]->name , "Dark");
    strcpy(hashtab[hash_val2]->defn , "Age");

    printf("Test 2\n");
    print_table();
    printf("\n");
    
    free(hashtab[hash_val1]->name);
    free(hashtab[hash_val1]->defn);
    free(hashtab[hash_val1]);
    free(hashtab[hash_val2]->name);
    free(hashtab[hash_val2]->defn);
    free(hashtab[hash_val2]);
    
    hashtab[hash_val1] = NULL;
    hashtab[hash_val2] = NULL;
}

void test3(void)
{
    unsigned hash_val1 = hash("Little");
    unsigned hash_val2 = hash("Dark");
    unsigned hash_val3 = hash("Age");
    
    hashtab[hash_val1] = (struct nlist *) malloc(sizeof(struct nlist));
    hashtab[hash_val1]->name = (char *) malloc(sizeof(char) * strlen("Little"));
    hashtab[hash_val1]->defn = (char *) malloc(sizeof(char) * strlen("Dark"));
    
    hashtab[hash_val2] = (struct nlist *) malloc(sizeof(struct nlist));
    hashtab[hash_val2]->name = (char *) malloc(sizeof(char) * strlen("Dark"));
    hashtab[hash_val2]->defn = (char *) malloc(sizeof(char) * strlen("Age"));
    
    
    hashtab[hash_val3] = (struct nlist *) malloc(sizeof(struct nlist));
    hashtab[hash_val3]->name = (char *) malloc(sizeof(char) * strlen("Age"));
    hashtab[hash_val3]->defn = (char *) malloc(sizeof(char) * strlen("Little"));
    
    strcpy(hashtab[hash_val1]->name , "Little");
    strcpy(hashtab[hash_val1]->defn , "Dark");
    strcpy(hashtab[hash_val2]->name , "Dark");
    strcpy(hashtab[hash_val2]->defn , "Age");
    strcpy(hashtab[hash_val3]->name , "Age");
    strcpy(hashtab[hash_val3]->defn , "Little");

    printf("Test 3\n");
    print_table();
    printf("\n");
    
    free(hashtab[hash_val1]->name);
    free(hashtab[hash_val1]->defn);
    free(hashtab[hash_val1]);
    free(hashtab[hash_val2]->name);
    free(hashtab[hash_val2]->defn);
    free(hashtab[hash_val2]);
    free(hashtab[hash_val3]->name);
    free(hashtab[hash_val3]->defn);
    free(hashtab[hash_val3]);
    
    hashtab[hash_val1] = NULL;
    hashtab[hash_val2] = NULL;
    hashtab[hash_val3] = NULL;
}

void test4(void)
{
    printf("Test 4\n");
    print_table();
    printf("\n");
}


void test5(void)
{
    install("Little", "Dark");
    
    unsigned hash_val1 = hash("Little");
    
    printf("Test 5\n");
    print_table();
    printf("\n");
    
    free(hashtab[hash_val1]->name);
    free(hashtab[hash_val1]->defn);
    free(hashtab[hash_val1]);
    
    hashtab[hash_val1] = NULL;
}

void test6(void)
{
    install("Little", "Dark");
    install("Dark", "Age");
    
    unsigned hash_val1 = hash("Little");
    unsigned hash_val2 = hash("Dark");

    printf("Test 6\n");
    print_table();
    printf("\n");
    
    free(hashtab[hash_val1]->name);
    free(hashtab[hash_val1]->defn);
    free(hashtab[hash_val1]);
    free(hashtab[hash_val2]->name);
    free(hashtab[hash_val2]->defn);
    free(hashtab[hash_val2]);
    
    hashtab[hash_val1] = NULL;
    hashtab[hash_val2] = NULL;
}

void test7(void)
{
    install("Little", "Dark");
    install("Dark", "Age");
    install("Age", "Little");
    
    unsigned hash_val1 = hash("Little");
    unsigned hash_val2 = hash("Dark");
    unsigned hash_val3 = hash("Age");

    printf("Test 7\n");
    print_table();
    printf("\n");
    
    free(hashtab[hash_val1]->name);
    free(hashtab[hash_val1]->defn);
    free(hashtab[hash_val1]);
    free(hashtab[hash_val2]->name);
    free(hashtab[hash_val2]->defn);
    free(hashtab[hash_val2]);
    free(hashtab[hash_val3]->name);
    free(hashtab[hash_val3]->defn);
    free(hashtab[hash_val3]);
    
    hashtab[hash_val1] = NULL;
    hashtab[hash_val2] = NULL;
    hashtab[hash_val3] = NULL;
}

void test8(void)
{
    install("cut", "a");
    install("occasions", "b");
    install("them", "c");
    
    unsigned hash_val1 = hash("cut");

    printf("Test 8\n");
    print_table();
    printf("\n");
    
    free(hashtab[hash_val1]->next->next->name);
    free(hashtab[hash_val1]->next->next->defn);
    free(hashtab[hash_val1]->next->name);
    free(hashtab[hash_val1]->next->defn);
    free(hashtab[hash_val1]->name);
    free(hashtab[hash_val1]->defn);

    free(hashtab[hash_val1]->next->next);
    free(hashtab[hash_val1]->next);
    free(hashtab[hash_val1]);
    
    hashtab[hash_val1] = NULL;
}

void test9(void)
{
    printf("Test 9\n");
    char search[10] = "Little";
    struct nlist *location = lookup(&search[0]);
    
    if(location == NULL)
        printf("Word, %s, not found\n", search);
    else
        printf("Found %s\n", location->name);
    
    printf("\n");
}

void test10(void)
{
    install("Little", "Dark");
    print_table();
    
    printf("Test 10\n");
    char search[10] = "Little";
    struct nlist *location = lookup(&search[0]);
    
    if(location == NULL)
        printf("Word, %s, not found\n", search);
    else
        printf("Found %s\n", location->name);
    
    unsigned hash_val1 = hash("Little");
    
    free(hashtab[hash_val1]->name);
    free(hashtab[hash_val1]->defn);
    free(hashtab[hash_val1]);
    
    hashtab[hash_val1] = NULL;
    print_table();
    printf("\n");
}

void test11(void)
{
    install("Little", "Dark");
    install("Dark", "Age");
    print_table();
    printf("\n");
    
    printf("Test 11\n");
    char search1[10] = "Little";
    char search2[10] = "Dark";

    struct nlist *location1 = lookup(&search1[0]);
    struct nlist *location2 = lookup(&search2[0]);
    
    if(location1 == NULL)
        printf("Word, %s, not found\n", search1);
    else
        printf("Found %s\n", location1->name);
    
    if(location2 == NULL)
        printf("Word, %s, not found\n", search2);
    else
        printf("Found %s\n", location2->name);
    
    unsigned hash_val1 = hash("Little");
    unsigned hash_val2 = hash("Dark");
    
    free(hashtab[hash_val1]->name);
    free(hashtab[hash_val1]->defn);
    free(hashtab[hash_val1]);
    free(hashtab[hash_val2]->name);
    free(hashtab[hash_val2]->defn);
    free(hashtab[hash_val2]);
    
    hashtab[hash_val1] = NULL;
    hashtab[hash_val2] = NULL;
    
    print_table();
    printf("\n");
}

void test12(void)
{
    printf("Test 12\n");
    char search[10] = "Little";
    struct nlist *location = lookup(&search[0]);
    
    undef("Little");
    
    if(location == NULL)
        printf("Word, %s, not found\n", &search[0]);
    else
        printf("Found %s\n", location->name);
    
    print_table();
    printf("\n");
}

void test13(void)
{
    printf("Test 13\n");
    install("Little", "Dark");
    printf("Before\n");
    print_table();
    printf("\n");
    
    char search[10] = "Little";
    struct nlist *location = lookup(&search[0]);
    
    undef("Little");
    
    location = lookup(&search[0]);
    
    if(location == NULL)
        printf("Word, %s, not found\n\n", &search[0]);
    else
        printf("Found %s\n\n", location->name);
    
    printf("After\n");
    print_table();
    printf("\n");
}
 
void test14(void)
{
    printf("Test 14\n");
    install("them", "1");
    install("cut", "2");
    
    printf("Before\n");
    print_table();
    printf("\n");
    
    char search[10] = "Little";
    struct nlist *location = lookup(&search[0]);
    
    undef("Little");
    
    location = lookup(&search[0]);
    
    if(location == NULL)
        printf("Word, %s, not found\n\n", &search[0]);
    else
        printf("Found %s\n\n", location->name);
    
    printf("After\n");
    print_table();
    printf("\n");
}

void test15(void)
{
    printf("Test 15\n");
    install("them", "1");
    install("cut", "2");
    
    printf("Before\n");
    print_table();
    printf("\n");
    
    char search[10] = "them";
    struct nlist *location = lookup(&search[0]);
    
    undef("them");
    
    location = lookup(&search[0]);
    
    if(location == NULL)
        printf("Word, %s, not found\n\n", &search[0]);
    else
        printf("Found %s\n\n", location->name);
    
    printf("After\n");
    print_table();
    printf("\n");
}

void test16(void)
{
    printf("Test 16\n");
    install("them", "1");
    install("cut", "2");
    
    printf("Before\n");
    print_table();
    printf("\n");
    
    char search[10] = "cut";
    struct nlist *location = lookup(&search[0]);
    
    undef("cut");
    
    location = lookup(&search[0]);
    
    if(location == NULL)
        printf("Word, %s, not found\n\n", &search[0]);
    else
        printf("Found %s\n\n", location->name);
    
    printf("After\n");
    print_table();
    printf("\n");
}

void test17(void)
{
    printf("Test 17\n");
    install("them", "1");
    install("cut", "2");
    install("occasions", "3");
    
    printf("Before\n");
    print_table();
    printf("\n");
    
    char search[10] = "cut";
    struct nlist *location = lookup(&search[0]);
    
    undef("cut");
    
    location = lookup(&search[0]);
    
    if(location == NULL)
        printf("Word, %s, not found\n\n", &search[0]);
    else
        printf("Found %s\n\n", location->name);
    
    printf("After\n");
    print_table();
    printf("\n");
}

void test18(void)
{
    printf("Test 18\n");
    install("them", "1");
    install("cut", "2");
    install("occasions", "3");
    
    printf("Before\n");
    print_table();
    printf("\n");
    
    char search[10] = "them";
    struct nlist *location = lookup(&search[0]);
    
    undef("them");
    
    location = lookup(&search[0]);
    
    if(location == NULL)
        printf("Word, %s, not found\n\n", &search[0]);
    else
        printf("Found %s\n\n", location->name);
    
    printf("After\n");
    print_table();
    printf("\n");
}

void test19(void)
{
    printf("Test 19\n");
    install("them", "1");
    install("cut", "2");
    install("occasions", "3");
    
    printf("Before\n");
    print_table();
    printf("\n");
    
    char search[10] = "occasions";
    struct nlist *location = lookup(&search[0]);
    
    undef("occasions");
    
    location = lookup(&search[0]);
    
    if(location == NULL)
        printf("Word, %s, not found\n\n", &search[0]);
    else
        printf("Found %s\n\n", location->name);
    
    printf("After\n");
    print_table();
    printf("\n");
}

/* print: print hashtable */
void print_table()
{
    for(int i = 0; i < HASHSIZE; i++)
    {
        struct nlist *current;
        if(hashtab[i])
        {
            printf("%d ", i);
            current = hashtab[i];
            while(current != NULL)
            {
                printf("%s: %s, ", current->name, current->defn);
                current = current->next;
            }
            
            printf("\n");
        }
    }
}

/* hash: form hash value for string s */
unsigned hash(char *s)
{
    unsigned hashval;
    
    for (hashval = 0; *s != '\0'; s++)
        hashval = *s + 31 * hashval;
    
    return hashval % HASHSIZE;
}

/* lookup: look for s in hashtab */
struct nlist *lookup(char *s)
{
    unsigned hashval = hash(s);
    struct nlist *np;
    
    for (np = hashtab[hashval]; np != NULL; np = np->next)
        if (np->name && strcmp(s, np->name) == 0)
            return np; /* found */
    return NULL;
}

/* install: put (name, defn) in hashtab */
struct nlist *install(char *name, char *defn)
{
    struct nlist *np;
    unsigned hashval;
    
    if((np = lookup(name)) == NULL)
    {
        /* not found */
        np = (struct nlist *) malloc(sizeof(*np));
        if (np == NULL || (np->name = strdup(name)) == NULL)
            return NULL;
        hashval = hash(name);
        np->next = hashtab[hashval];
        hashtab[hashval] = np;
    }
    else /* already there */
        free((void *) np->defn); /* free previous defn */
    if ((np->defn = strdup(defn)) == NULL)
        return NULL;
    return np;
}

void undef(char *remove_s)
{
    // Search for remove_s within hashtab
    struct nlist *head;
    struct nlist *current, *previous;
    
    unsigned hashval= hash(remove_s);
    head = hashtab[hashval];
    
    // If not found, we return and complete the function
    if(head == NULL)
        return;
    
    // If we have a match at head and the head has no proceeding next 
    // entries, we can free *name, *defn with no need to preserve order. 
    if(head->next == NULL && strcmp(head->name, remove_s) == 0)
    {
        free(head->name);
        free(head->defn);
        free(head);
        
        head->name = NULL;
        head->defn = NULL;
        head->next = NULL;
        head = NULL;
        
        hashtab[hashval] = NULL;
        return;
    }
    
    // Otherwise, we want to find the location of the entry with name remove_s
    // while also taking note of the previous entry, if necessary, to preserve
    // ordering
    else
    {
        // Set current to the head and previous to NULL
        current = head;
        previous = head;
        
        // Loop while we haven't found an entry with name remove_s 
        while(strcmp(current->name, remove_s) != 0)
        {
            // If we end up with *current == NULL, we have reached the end
            // without finding a matching entry. We can return and provide a
            // message
            if(current == NULL)
            {   
                printf("Couldn't find string in hashtable");
                return;
            }
            
            // Otherwise, we increment our previous and current pointers
            previous = current;
            current = current->next;
        }
        
        
        printf("Found: %s\n", current->name);
        printf("Previous: %s\n", previous->name);
        
        // If we are at the beggining of the linked list, we don't have to
        // be careful about preserving the order with the previous entry
        if(current == hashtab[hashval])
        {
            printf("first value with hashvalue: %d\n", hashval);
            hashtab[hashval] = current->next;

            free(current->name);
            free(current->defn);
        }
        // Otherwise, we are somewhere in the middle or end of the linked list
        else
        {
            printf("value with hashvalue: %d\n", hashval);
            printf("previous->next: %s\n", previous->name);
            printf("current->next: %s\n", current->name);
            previous->next = current->next;

            free(current->name);
            free(current->defn);
        }
        
    }
}


int getword(char *word, int lim)
{
    int c;
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
            ungetch1(*w);
            break;
        }
    *w = '\0';
    return word[0];
}

int getch(void) /* get a (possibly pushed back) character */
{
    return (bufp == 1) ? buf[--bufp] : getchar();
}

void ungetch1(int c) /* push character back on input */
{
    if (bufp >= 1)
        printf("ungetch: too many characters\n");
    else
        buf[bufp++] = c;
}

/* Write a function undef that will remove a name and definition from the
 table maintained by lookup and install */
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
    test15();
    test16();
    test17();
    test18();
    test19();
    
    /*    
    int lim = 1000;
    char current_word[lim];

    // Have to make sure that the pointer for the word has pre-allocated 
    // space to store the words, in this case, with size lim.
    char first_letter = getword(&current_word[0], lim);

    while(first_letter != EOF)
    {   
        install(&current_word[0], "A");

        // get new word
        first_letter = getword(&current_word[0], lim);
    }

    printf("%s\n",hashtab[3]->name);
    printf("%s\n",hashtab[3]->next->name);
    printf("%s\n",hashtab[3]->next->next->name);
    
    undef("occasions");

    struct nlist *search;
    printf("\n");

    if(search == NULL)
        printf("Successfully undefined!\n");
    if((search = lookup("occasions")) != NULL)
        printf("Found 'occasions\n");

    printf("\n");
    printf("%s\n",hashtab[3]->name);
    printf("%s\n",hashtab[3]->next->name);
    printf("%s\n",hashtab[3]->next->next->name);
    */


    return 0;
}

